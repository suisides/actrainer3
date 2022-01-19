#include "stdafx.h"
#include "mem.h"
#include "proc.h"

#define PI 3.1415927f

void mem::PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess)
{
	DWORD oldprotect;
	VirtualProtectEx(hProcess, dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	WriteProcessMemory(hProcess, dst, src, size, nullptr);
	VirtualProtectEx(hProcess, dst, size, oldprotect, &oldprotect);
}

void mem::NopEx(BYTE* dst, unsigned int size, HANDLE hProcess)
{
	BYTE* nopArray = new BYTE[size];
	memset(nopArray, 0x90, size);

	PatchEx(dst, nopArray, size, hProcess);
	delete[] nopArray;
}

vec3 mem::GetSelfCoords(HANDLE hProcess, uintptr_t localPlayerPtr)
{
	vec3 coords;
	uintptr_t locX, locY, locZ;
	locX = FindDMAAddy(hProcess, localPlayerPtr, { 0x4 });
	locY = locX + 0x4;
	locZ = locY + 0x4;
	ReadProcessMemory(hProcess, (LPVOID)locX, &(coords.x), sizeof(coords.x), NULL);
	ReadProcessMemory(hProcess, (LPVOID)locY, &(coords.y), sizeof(coords.y), NULL);
	ReadProcessMemory(hProcess, (LPVOID)locZ, &(coords.z), sizeof(coords.z), NULL);
	return coords;
}

vec3 mem::GetEntCoords(HANDLE hProcess, uintptr_t entityPtr, unsigned int index)
{
	vec3 coords;
	uintptr_t entX, entY, entZ;
	entX = FindDMAAddy(hProcess, entityPtr, { index * 4, 0x4 });
	entY = entX + 0x4;
	entZ = entY + 0x4;
	ReadProcessMemory(hProcess, (LPVOID)entX, &(coords.x), sizeof(coords.x), NULL);
	ReadProcessMemory(hProcess, (LPVOID)entY, &(coords.y), sizeof(coords.x), NULL);
	ReadProcessMemory(hProcess, (LPVOID)entZ, &(coords.z), sizeof(coords.x), NULL);

	return coords;
}

vec3 mem::Subtract(vec3 src, vec3 dst)
{
	vec3 diff;
	diff.x = src.x - dst.x;
	diff.y = src.y - dst.y;
	diff.z = src.z - dst.z;
	return diff;
}

float mem::Magnitude(vec3 vec)
{
	return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

float mem::GetDistance(vec3 src, vec3 dst)
{
	vec3 diff = Subtract(src, dst);
	return Magnitude(diff);
}

vec3 mem::GetAngle(vec3 src, vec3 dst)
{
	vec3 angle;
	angle.x = -atan2f(dst.x - src.x, dst.y - src.y) / PI * 180.0f + 180.0f;
	angle.y = asinf((dst.z - src.z) / GetDistance(src, dst)) * 180.0f / PI;
	angle.z = 0.0f;
	
	return angle;
}

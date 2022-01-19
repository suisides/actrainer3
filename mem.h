#pragma once



struct vec3
{
	float x, y, z;
};


namespace mem
{
	void PatchEx(BYTE* dst, BYTE* src, unsigned int size, HANDLE hProcess);
	void NopEx(BYTE* dst, unsigned int size, HANDLE hProcess);
	
	vec3 GetSelfCoords(HANDLE hProcess, uintptr_t localPlayerPtr);
	vec3 GetEntCoords(HANDLE hProcess, uintptr_t entityPtr, unsigned int index);
	
	vec3 Subtract(vec3 src, vec3 dst);
	float Magnitude(vec3 vec);
	float GetDistance(vec3 src, vec3 dst);

	vec3 GetAngle(vec3 enemyCoord, vec3 selfCoord);
}
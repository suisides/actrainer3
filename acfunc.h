#pragma once

void GetLocalTeam();
void GetLocalHealth();
void GetTeam();
void GetHealth();
void AimAt(float pitch, float yaw);

////skip if dead
//uintptr_t localPlayerHealth;
//ReadProcessMemory(hProcess, (LPVOID)localPlayerPtr, &localPlayerHealth, sizeof(localPlayerPtr + 0xF8), NULL);
//if (!localPlayerHealth)
//continue;
//
////get amount of players 
//uintptr_t playerAmountAddr;
//ReadProcessMemory(hProcess, (LPVOID)moduleBase, &playerAmountAddr, sizeof(moduleBase + 0x10F500), NULL);
//
////find closest enemy
//for (uintptr_t i = 0; i < playerAmountAddr; i += 0x4)
//{
//	uintptr_t localPlayerX, localPlayerY, localPlayerZ;
//	ReadProcessMemory(hProcess, (LPVOID)localPlayerPtr, &localPlayerX, sizeof(localPlayerPtr + 0x4), NULL);
//	ReadProcessMemory(hProcess, (LPVOID)localPlayerPtr, &localPlayerY, sizeof(localPlayerPtr + 0x8), NULL);
//	ReadProcessMemory(hProcess, (LPVOID)localPlayerPtr, &localPlayerZ, sizeof(localPlayerPtr + 0xC), NULL);
//
//	uintptr_t enemyX, enemyY, enemyZ;
//	ReadProcessMemory(hProcess, (LPVOID)(moduleBase + 0x4), &enemyX, sizeof(entityPtr + 0x4 + i), NULL);
//	ReadProcessMemory(hProcess, (LPVOID)(moduleBase + 0x4), &enemyY, sizeof(entityPtr + 0x8 + i), NULL);
//	ReadProcessMemory(hProcess, (LPVOID)(moduleBase + 0x4), &enemyZ, sizeof(entityPtr + 0xC + i), NULL);
//
//	float a, b, c, a1, b1, c1, distance = 99999999;
//
//	a = abs((float)enemyX - (float)localPlayerX);
//	b = abs((float)enemyY - (float)localPlayerY);
//	c = sqrt((a * a) + (b * b));
//	a1 = c;
//	b1 = abs((float)enemyX - (float)localPlayerX);
//	c1 = sqrt((c * c) + (b1 * b1));
//	if (c1 < distance)
//		distance = c1;
//}
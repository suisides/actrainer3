
#include <thread>
#include "stdafx.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <Windows.h>
#include <WinUser.h>
#include "proc.h"
#include "mem.h"

#define PI 3.14159265

struct Pos
{
	float x;
	float y;
	float z;

};

float GetDistance(float localX, float localY, float localZ, float enemyX, float enemyY, float enemyZ)
	{
		float distance, a1, b1, b2; //c2 = distance
		
		a1 = enemyY - localY;
		b1 = enemyX - localX;
		b2 = enemyZ - localZ;
		distance = sqrt((a1 * a1) + (b1 * b1) + (b2 * b2));
		
		return distance;
	}
	



void Clear()
{
	std::system("cls");
}



void updateKeys(bool health, bool ammo, bool recoil, bool speedhack, bool grenade, bool aimbot)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	Clear();
	std::cout << "Numpad 1: Freeze Health at 1337: ";
	if (health)
	{
		SetConsoleTextAttribute(hConsole, 10);
		std::cout << "Enabled!\n";
		SetConsoleTextAttribute(hConsole, 15);
	}
	else
	{
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "Disabled!\n";
		SetConsoleTextAttribute(hConsole, 15);
	}
	std::cout << "Numpad 2: Infinite Ammo: ";
	if (ammo)
	{
		SetConsoleTextAttribute(hConsole, 10);
		std::cout << "Enabled!\n";
		SetConsoleTextAttribute(hConsole, 15);
	}
	else
	{
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "Disabled!\n";
		SetConsoleTextAttribute(hConsole, 15);
	}
	std::cout << "Numpad 3: Disable Recoil: ";
	if (recoil)
	{
		SetConsoleTextAttribute(hConsole, 10);
		std::cout << "Enabled!\n";
		SetConsoleTextAttribute(hConsole, 15);
	}
	else
	{
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "Disabled!\n";
		SetConsoleTextAttribute(hConsole, 15);
	}
	std::cout << "Numpad 4: Speedhack (ctrl): ";
	if (speedhack)
	{
		SetConsoleTextAttribute(hConsole, 10);
		std::cout << "Enabled!\n";
		SetConsoleTextAttribute(hConsole, 15);
	}
	else
	{
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "Disabled!\n";
		SetConsoleTextAttribute(hConsole, 15);
	}
	std::cout << "Numpad 5: Infinite Grenades: ";
	if (grenade)
	{
		SetConsoleTextAttribute(hConsole, 10);
		std::cout << "Enabled!\n";
		SetConsoleTextAttribute(hConsole, 15);
	}
	else
	{
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "Disabled!\n";
		SetConsoleTextAttribute(hConsole, 15);
	}
	std::cout << "Numpad 6: Aimbot(Caps-Lock): ";
	if (aimbot)
	{
		SetConsoleTextAttribute(hConsole, 10);
		std::cout << "Enabled!\n";
		SetConsoleTextAttribute(hConsole, 15);
	}
	else
	{
		SetConsoleTextAttribute(hConsole, 12);
		std::cout << "Disabled!\n";
		SetConsoleTextAttribute(hConsole, 15);
	}
	std::cout << "Insert: Exit\n";
}

int main()
{
	HANDLE hProcess = 0;

	uintptr_t moduleBase = 0, localPlayerPtr = 0, healthAddr = 0, speedAddr = 0, grenadeAddr = 0, entityPtr = 0, localPlayerYawAddr = 0, playersNumAddr = 0, localPlayerPitchAddr = 0, localPlayerXAddr = 0, localPlayerYAddr = 0, localPlayerZAddr = 0, localPlayerTeamAddr = 0;
	bool bHealth = false, bAmmo = false, bRecoil = false, bSpeedhack = false, bGrenadeAmmo = false, bAimbot = false;

	const int newValue = 1337, newSpeed = 3, oldSpeed = 0;

	DWORD procId = GetProcId(L"ac_client.exe");

	if (procId)
	{

		std::cout << "Process found!\n";
		updateKeys(bHealth, bAmmo, bRecoil, bSpeedhack, bGrenadeAmmo, bAimbot);
		

		hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);

		moduleBase = GetModuleBaseAddress(procId, L"ac_client.exe");

		localPlayerPtr = moduleBase + 0x10f4f4;

		entityPtr = moduleBase + 0x110D90;

		healthAddr = FindDMAAddy(hProcess, localPlayerPtr, { 0xf8 });

		speedAddr = FindDMAAddy(hProcess, localPlayerPtr, { 0x80 });

		localPlayerYawAddr = FindDMAAddy(hProcess, localPlayerPtr, { 0x40 });

		localPlayerPitchAddr = FindDMAAddy(hProcess, localPlayerPtr, { 0x44 });

		localPlayerXAddr = FindDMAAddy(hProcess, localPlayerPtr, { 0x04 });

		localPlayerYAddr = FindDMAAddy(hProcess, localPlayerPtr, { 0x08 });

		localPlayerZAddr = FindDMAAddy(hProcess, localPlayerPtr, { 0x0C });

		localPlayerTeamAddr = FindDMAAddy(hProcess, localPlayerPtr, { 0x32c });
		
		playersNumAddr = FindDMAAddy(hProcess, moduleBase + 0x1170, { 0x42C });

	}

	else 
	{
		std::cout << "Process not found, press enter to exit\n";
		getchar();
		return 0;
	}

	DWORD dwExit = 0;

	Pos self;

	Pos currEnemy;

	while (GetExitCodeProcess(hProcess, &dwExit) && dwExit == STILL_ACTIVE)
	{
		//godmode
		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		{
			bHealth = !bHealth;
			updateKeys(bHealth, bAmmo, bRecoil, bSpeedhack, bGrenadeAmmo, bAimbot);

		}
		
		//increment ammo
		if (GetAsyncKeyState(VK_NUMPAD2) & 1)
		{
			bAmmo = !bAmmo;
			updateKeys(bHealth, bAmmo, bRecoil, bSpeedhack, bGrenadeAmmo, bAimbot);
			if (bAmmo)
			{
				mem::PatchEx((BYTE*)(moduleBase + 0x637e9), (BYTE*)"\xFF\x06", 2, hProcess);
			}
			else
			{

				mem::PatchEx((BYTE*)(moduleBase + 0x637e9), (BYTE*)"\xFF\x0E", 2, hProcess);
			}
		}
		
		//disable/enable recoil
		if (GetAsyncKeyState(VK_NUMPAD3) & 1)
		{
			bRecoil = !bRecoil;
			updateKeys(bHealth, bAmmo, bRecoil, bSpeedhack, bGrenadeAmmo, bAimbot);
			if (bRecoil)
			{
				mem::NopEx((BYTE*)(moduleBase + 0x63786), 10, hProcess);
			}
			else
			{
				mem::PatchEx((BYTE*)(moduleBase + 0x63786), (BYTE*)"\x50\x8d\x4c\x24\x1c\x51\x8b\xce\xff\xd2", 10, hProcess);
			}
		}
		
		//speedhack
		if (GetAsyncKeyState(VK_NUMPAD4) & 1)
		{
			bSpeedhack = !bSpeedhack;
			updateKeys(bHealth, bAmmo, bRecoil, bSpeedhack, bGrenadeAmmo, bAimbot);
		}
		
		//increment grenades
		if (GetAsyncKeyState(VK_NUMPAD5) & 1)
		{
			bGrenadeAmmo = !bGrenadeAmmo;
			updateKeys(bHealth, bAmmo, bRecoil, bSpeedhack, bGrenadeAmmo, bAimbot);
			if (bGrenadeAmmo)
			{
				mem::PatchEx((BYTE*)(moduleBase + 0x63378), (BYTE*)"\xFF\x00", 2, hProcess);
			}
			else
			{
				mem::PatchEx((BYTE*)(moduleBase + 0x63378), (BYTE*)"\xFF\x08", 2, hProcess);
			}
		}
		
		//aimbot
		if (GetAsyncKeyState(VK_NUMPAD6) & 1)
		{
			bAimbot = !bAimbot;
			updateKeys(bHealth, bAmmo, bRecoil, bSpeedhack, bGrenadeAmmo, bAimbot);
		}
		
		//exit
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			return 0;
		}
		
		//continuous write/freeze
		if (bHealth)
		{
			mem::PatchEx((BYTE*)healthAddr, (BYTE*)&newValue, sizeof(newValue), hProcess);
		}
		
		if (bSpeedhack)
		{
			if(GetAsyncKeyState(VK_CONTROL))
				mem::PatchEx((BYTE*)speedAddr, (BYTE*)&newSpeed, sizeof(newSpeed), hProcess);
		}
		
		if (bAimbot)
		{
			if (GetAsyncKeyState(VK_CAPITAL)) {
				
				//check for local Health
				int health;
				ReadProcessMemory(hProcess, (LPVOID)healthAddr, &health, sizeof(healthAddr), NULL);
				if (!health)
					continue;
				
				//get local team
				int localTeam;
				ReadProcessMemory(hProcess, (LPVOID)localPlayerTeamAddr, &localTeam, sizeof(localTeam), NULL); 
				

				//Get number of players
				int playersNum;
				ReadProcessMemory(hProcess, (LPVOID)playersNumAddr, &playersNum, sizeof(playersNum), NULL);
				
				//get local position
				float selfX, selfY, selfZ;
				ReadProcessMemory(hProcess, (LPVOID)localPlayerXAddr, &selfX, sizeof(selfX), NULL);
				ReadProcessMemory(hProcess, (LPVOID)localPlayerYAddr, &selfY, sizeof(selfY), NULL);
				ReadProcessMemory(hProcess, (LPVOID)localPlayerZAddr, &selfZ, sizeof(selfZ), NULL);
				
				self.x = selfX;
				self.y = selfY;
				self.z = selfZ;
				
				//Get closest enemy
				float distance = 9999999;
				unsigned int enemyIndex = 0;
				for (unsigned int i = 0; i < playersNum; i++)
				{
					uintptr_t currEnemyAddr = FindDMAAddy(hProcess, entityPtr, { i * 4 });


					bool currPlayerTeam;
					uintptr_t currPlayerTeamAddr = FindDMAAddy(hProcess, entityPtr, { i * 4 , 0x32C });
					ReadProcessMemory(hProcess, (LPVOID)currPlayerTeamAddr, &currPlayerTeam, sizeof(currPlayerTeam), NULL);

					if (currPlayerTeam != localTeam)
					{
						float enemyX, enemyY, enemyZ, currDist;
						uintptr_t currentenemyXaddr, currentenemyYaddr, currentenemyZaddr;
						currentenemyXaddr = FindDMAAddy(hProcess, entityPtr, { i * 4, 0x4 });
						currentenemyYaddr = FindDMAAddy(hProcess, entityPtr, { i * 4, 0x8 });
						currentenemyZaddr = FindDMAAddy(hProcess, entityPtr, { i * 4, 0xC });
						ReadProcessMemory(hProcess, (LPVOID)currentenemyXaddr, &enemyX, sizeof(enemyX), NULL);
						ReadProcessMemory(hProcess, (LPVOID)currentenemyYaddr, &enemyY, sizeof(enemyY), NULL);
						ReadProcessMemory(hProcess, (LPVOID)currentenemyZaddr, &enemyZ, sizeof(enemyZ), NULL);
						currEnemy.x = enemyX;
						currEnemy.y = enemyY;
						currEnemy.z = enemyZ;
						

						currDist = GetDistance(self.x, self.y, self.z, currEnemy.x, currEnemy.y, currEnemy.z);

						if (currDist < distance)
						{
							distance = currDist;
							enemyIndex = (i * 4);
						}

					}
					else
					{
						continue;
					}
				}
				//get Angles
				uintptr_t currentenemyXaddr, currentenemyYaddr, currentenemyZaddr;
				currentenemyXaddr = FindDMAAddy(hProcess, entityPtr, { enemyIndex * 4, 0x4 });
				currentenemyYaddr = FindDMAAddy(hProcess, entityPtr, { enemyIndex * 4, 0x8 });
				currentenemyZaddr = FindDMAAddy(hProcess, entityPtr, { enemyIndex * 4, 0xC });;
				float yaw, pitch, enemyX, enemyY, enemyZ, distX, distY, distZ;
				ReadProcessMemory(hProcess, (LPVOID)currentenemyXaddr, &enemyX, sizeof(enemyX), NULL);
				ReadProcessMemory(hProcess, (LPVOID)currentenemyYaddr, &enemyY, sizeof(enemyY), NULL);
				ReadProcessMemory(hProcess, (LPVOID)currentenemyZaddr, &enemyZ, sizeof(enemyZ), NULL);
				
				distX = enemyX - self.x;	
				distY = enemyY - self.y;
				distZ = enemyZ - self.z;

				//pitch
				float hypotenuseXZ;
				hypotenuseXZ = sqrt((distX * distX) + (distZ * distZ));
				pitch = asin(distZ / hypotenuseXZ) * 180 / PI;

				//yaw
				yaw = -(atan2((enemyX - self.x), (enemyY - self.y))) * (180 / PI) - 180.f;
				if(yaw > 360)
					yaw -= 360;
				

				//set angles
				WriteProcessMemory(hProcess, (LPVOID)localPlayerYawAddr, &yaw, sizeof(yaw), NULL);
				WriteProcessMemory(hProcess, (LPVOID)localPlayerPitchAddr, &pitch, sizeof(pitch), NULL);
			}
		}

		if (GetAsyncKeyState(VK_NUMPAD7) & 1)
		{
			//get Self Coords
			float selfX, selfY, selfZ;
			ReadProcessMemory(hProcess, (LPVOID)localPlayerXAddr, &selfX, sizeof(selfX), NULL);
			ReadProcessMemory(hProcess, (LPVOID)localPlayerYAddr, &selfY, sizeof(selfY), NULL);
			ReadProcessMemory(hProcess, (LPVOID)localPlayerZAddr, &selfZ, sizeof(selfZ), NULL);
			std::cout <<std::endl<< "local x: " << selfX << std::endl;
			std::cout << "local y: " << selfY << std::endl;
			std::cout << "local z: " << selfZ << std::endl << std::endl;



			//Get number of players
			int playersNum;
			ReadProcessMemory(hProcess, (LPVOID)playersNumAddr, &playersNum, sizeof(playersNum), NULL);
			std::cout << "number of players: " << playersNum <<std::endl;

			//get localteam
			int localTeam;
			ReadProcessMemory(hProcess, (LPVOID)localPlayerTeamAddr, &localTeam, sizeof(localTeam), NULL); 
			std::cout << "local team: " << localTeam << std::endl<< std::endl;
			
			float distance = 9999999;
			unsigned int enemyIndex;
			
			//get local position
			ReadProcessMemory(hProcess, (LPVOID)localPlayerXAddr, &selfX, sizeof(selfX), NULL);
			ReadProcessMemory(hProcess, (LPVOID)localPlayerYAddr, &selfY, sizeof(selfY), NULL);
			ReadProcessMemory(hProcess, (LPVOID)localPlayerZAddr, &selfZ, sizeof(selfZ), NULL);

			self.x = selfX;
			self.y = selfY;
			self.z = selfZ;

			for (unsigned int i = 0; i < playersNum; i++)
			{
				uintptr_t currEnemyAddr = FindDMAAddy(hProcess, entityPtr, { i * 4 });
				std::cout << "address of current enemy: " << currEnemyAddr << std::endl;
				

				bool currPlayerTeam;
				uintptr_t currPlayerTeamAddr = FindDMAAddy(hProcess, entityPtr, { i * 4 , 0x32C});
				ReadProcessMemory(hProcess, (LPVOID)currPlayerTeamAddr, &currPlayerTeam, sizeof(currPlayerTeam), NULL);
				std::cout << "team of current player: " << currPlayerTeam << std::endl;

				if (currPlayerTeam != localTeam)
				{
					float enemyX, enemyY, enemyZ, currDist;
					uintptr_t currentenemyXaddr, currentenemyYaddr, currentenemyZaddr;
					currentenemyXaddr = FindDMAAddy(hProcess, entityPtr, { i * 4, 0x4 });
					currentenemyYaddr = FindDMAAddy(hProcess, entityPtr, { i * 4, 0x8 });
					currentenemyZaddr = FindDMAAddy(hProcess, entityPtr, { i * 4, 0xC });
					ReadProcessMemory(hProcess, (LPVOID)currentenemyXaddr, &enemyX, sizeof(enemyX), NULL);
					ReadProcessMemory(hProcess, (LPVOID)currentenemyYaddr, &enemyY, sizeof(enemyY), NULL);
					ReadProcessMemory(hProcess, (LPVOID)currentenemyZaddr, &enemyZ, sizeof(enemyZ), NULL);
					currEnemy.x = enemyX;
					currEnemy.y = enemyY;
					currEnemy.z = enemyZ;
					std::cout << "current enemy x: " << currEnemy.x << std::endl;
					std::cout << "current enemy y: " << currEnemy.y << std::endl;
					std::cout << "current enemy x: " << currEnemy.z << std::endl;

					currDist = GetDistance(self.x, self.y, self.z, currEnemy.x, currEnemy.y, currEnemy.z);
					std::cout << "distance to current enemy: " << currDist << std::endl<< std::endl;

					if (currDist < distance)
					{
						distance = currDist;
						enemyIndex = i * 4;
					}

				}
				else
				{
					continue;
				}
			}

		}

		if (GetAsyncKeyState(VK_NUMPAD8) & 1)
		{
			
		}
		Sleep(10);
	}

	std::cout << "Process not found, press enter to exit\n";
	getchar();
	return 0;

}




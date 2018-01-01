#include "ProcMem.h" // memory header
DWORD bSpotted = 0x939; // radar point
DWORD LocalPlayer = 0xAAFD7C; // local player offset
DWORD EntityList = 0x4A8D13C; // all players offset
DWORD iTeam = 0xF0; // team num offset
DWORD oDormant = 0xE9; // offset to check if the object is player
DWORD bClient, LocalBase; // some values
ProcMem vam; // memory object

int main() // main function
{
	vam.Process("csgo.exe"); // get cs go process
	bClient = vam.Module("client.dll"); // get client dll
	while (true) // infinite loop
	{
		LocalBase = vam.Read<int>(bClient + LocalPlayer); // get local base
		int myteam = vam.Read<int>(LocalBase + iTeam); // get our player's team
		for (int i = 1; i <= 64; i++) // loop for all players
		{
			int player = vam.Read<int>(bClient + EntityList + (i - 1) * 0x10); // get player's base
			int playerteam = vam.Read<int>(player + iTeam); // get player's team
			int playerdormant = vam.Read<int>(player + oDormant); // get player's dormant
			if (playerteam != myteam && !playerdormant) // if player is enemy and he is a player
				vam.Write<int>(player + bSpotted, 1); // write 1 to let us see him on radar
		}
		Sleep(10); // sleep to decrease cpu loading
	}
}
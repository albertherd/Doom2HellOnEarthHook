#include <Windows.h>
#include <TlHelp32.h>
#include <tchar.h>
#include "main.h"

_TCHAR *processName = _TEXT("dosbox.exe");

DWORD baseAddress = 0x006D16A0;
DWORD bulletsOffset = 0x001CDF14;
DWORD shellOffset = 0x001CDF18;
DWORD rocketOffset = 0x001CDF22;
DWORD cellOffset = 0x001CDF26;
DWORD healthOffset = 0x001CDE98;
DWORD dataToSet = 200;
SIZE_T dataToSetLength = sizeof(dataToSet);

int main(int argc, _TCHAR *argv)
{
	DWORD dosBoxPId = GetProcessIdByName(processName);
	if (!dosBoxPId)
		return;

	HANDLE dosBoxProcessHandle = OpenProcessById(dosBoxPId);
	
	DWORD userDataAddress;
	SIZE_T userDataAddressLength = sizeof(userDataAddress);
	ReadProcessMemory(dosBoxProcessHandle, (LPCVOID)baseAddress, &userDataAddress, userDataAddressLength, 0);

	DWORD bulletsAddresss = userDataAddress + bulletsOffset;
	DWORD shellAddresss = userDataAddress + shellOffset;
	DWORD rocketAddresss = userDataAddress + rocketOffset;
	DWORD cellAddresss = userDataAddress + cellOffset;
	DWORD healthAddresss = userDataAddress + healthOffset;

	while (1) {
		Sleep(1000);		
		WriteProcessMemory(dosBoxProcessHandle, (LPCVOID)bulletsAddresss, &dataToSet, dataToSetLength, 0);
		WriteProcessMemory(dosBoxProcessHandle, (LPCVOID)shellAddresss, &dataToSet, dataToSetLength, 0);
		WriteProcessMemory(dosBoxProcessHandle, (LPCVOID)rocketAddresss, &dataToSet, dataToSetLength, 0);
		WriteProcessMemory(dosBoxProcessHandle, (LPCVOID)cellAddresss, &dataToSet, dataToSetLength, 0);
		WriteProcessMemory(dosBoxProcessHandle, (LPCVOID)healthAddresss, &dataToSet, dataToSetLength, 0);
	}
	
	CloseHandle(dosBoxProcessHandle);
}

DWORD GetProcessIdByName(_TCHAR *processName)
{
	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 processEntry = { sizeof(processEntry) };
	do
	{
		if (!_tcscmp(processEntry.szExeFile, processName))
		{
			CloseHandle(processesSnapshot);
			return processEntry.th32ProcessID;
		}
	} while (Process32Next(processesSnapshot, &processEntry));

	CloseHandle(processesSnapshot);
	return 0;
}

HANDLE OpenProcessById(DWORD processId)
{
	return OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
}

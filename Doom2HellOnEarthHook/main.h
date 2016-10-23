#pragma once
DWORD GetProcessIdByName(_TCHAR *processName);
HANDLE OpenProcessById(DWORD processId);
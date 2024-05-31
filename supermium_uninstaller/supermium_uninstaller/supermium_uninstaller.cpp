// supermium_uninstaller.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <strsafe.h>
#include <Shlobj.h>

void DeleteSupermiumRegKeys()
// The registry keys are deleted even during an install to avoid cluttering registries with junk from
// the old Chromium installer. All known key formats are deleted so only the current Supermium format will be present.
{
	LONG lResultHKCU, lResultHKLM, lResultUninstall;
	HKEY hKeyCU = 0;
	HKEY hKeyLM = 0;
	PWSTR InstallPath = NULL;

	// Open HKEY_CURRENT_USER\Software\Clients\StartMenuInternet
	lResultHKCU = RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Clients\\StartMenuInternet", 0, KEY_READ, &hKeyCU);

	lResultHKLM = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Software\\Clients\\StartMenuInternet", 0, KEY_READ, &hKeyLM);



	// Open HKEY_LOCAL_MACHINE\Software\Clients\StartMenuInternet
	if (lResultHKLM != ERROR_SUCCESS && lResultHKCU != ERROR_SUCCESS) {
		return;
	}

	// Buffer for subkey names
	wchar_t szSubkey[100];
	DWORD dwIndex = 0;
	DWORD dwSize = 100;

	// Iterate through subkeys of HKEY_CURRENT_USER
	while (lResultHKCU == ERROR_SUCCESS && RegEnumKeyEx(hKeyCU, dwIndex, szSubkey, &dwSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
		if (wcsstr(szSubkey, L"Supermium") || wcsstr(szSubkey, L"Supemium")) {
			RegDeleteKeyW(HKEY_CURRENT_USER, std::wstring(std::wstring(L"SOFTWARE\\Clients\\StartMenuInternet\\") + std::wstring(szSubkey) + std::wstring(L"\\Capabilities\\FileAssociations")).c_str());
			RegDeleteKeyW(HKEY_CURRENT_USER, std::wstring(std::wstring(L"SOFTWARE\\Clients\\StartMenuInternet\\") + std::wstring(szSubkey) + std::wstring(L"\\Capabilities\\Startmenu")).c_str());
			RegDeleteKeyW(HKEY_CURRENT_USER, std::wstring(std::wstring(L"SOFTWARE\\Clients\\StartMenuInternet\\") + std::wstring(szSubkey) + std::wstring(L"\\Capabilities\\URLAssociations")).c_str());
			RegDeleteKeyW(HKEY_CURRENT_USER, std::wstring(std::wstring(L"SOFTWARE\\Clients\\StartMenuInternet\\") + std::wstring(szSubkey) + std::wstring(L"\\Capabilities")).c_str());
			RegDeleteKeyW(HKEY_CURRENT_USER, std::wstring(std::wstring(L"SOFTWARE\\Clients\\StartMenuInternet\\") + std::wstring(szSubkey) + std::wstring(L"\\DefaultIcon")).c_str());
			RegDeleteKeyW(HKEY_CURRENT_USER, std::wstring(std::wstring(L"SOFTWARE\\Clients\\StartMenuInternet\\") + std::wstring(szSubkey) + std::wstring(L"\\InstallInfo")).c_str());
			RegDeleteKeyW(HKEY_CURRENT_USER, std::wstring(std::wstring(L"SOFTWARE\\Clients\\StartMenuInternet\\") + std::wstring(szSubkey) + std::wstring(L"\\shell\\open\\command")).c_str());
			RegDeleteKeyW(HKEY_CURRENT_USER, std::wstring(std::wstring(L"SOFTWARE\\Clients\\StartMenuInternet\\") + std::wstring(szSubkey) + std::wstring(L"\\shell\\open")).c_str());
			RegDeleteKeyW(HKEY_CURRENT_USER, std::wstring(std::wstring(L"SOFTWARE\\Clients\\StartMenuInternet\\") + std::wstring(szSubkey) + std::wstring(L"\\shell")).c_str());
			RegDeleteKeyW(HKEY_CURRENT_USER, std::wstring(std::wstring(L"SOFTWARE\\Clients\\StartMenuInternet\\") + std::wstring(szSubkey)).c_str());
			RegDeleteKeyW(HKEY_CURRENT_USER, std::wstring(std::wstring(L"Software\\Classes\\") + std::wstring(szSubkey) + std::wstring(L"\\DefaultIcon")).c_str());
			RegDeleteKeyW(HKEY_CURRENT_USER, std::wstring(std::wstring(L"Software\\Classes\\") + std::wstring(szSubkey) + std::wstring(L"\\shell\\open\\command")).c_str());
			RegDeleteKeyW(HKEY_CURRENT_USER, std::wstring(std::wstring(L"Software\\Classes\\") + std::wstring(szSubkey) + std::wstring(L"\\shell\\open")).c_str());
			RegDeleteKeyW(HKEY_CURRENT_USER, std::wstring(std::wstring(L"Software\\Classes\\") + std::wstring(szSubkey) + std::wstring(L"\\shell")).c_str());
			RegDeleteKeyW(HKEY_CURRENT_USER, std::wstring(std::wstring(L"Software\\Classes\\") + std::wstring(szSubkey)).c_str());
			--dwIndex;
		}
		dwIndex++;
		dwSize = ARRAYSIZE(szSubkey);
	}

	if (!InstallPath)
	{
		// Reset index and size for HKEY_LOCAL_MACHINE
		dwIndex = 0;
		dwSize = 100;

		// Iterate through subkeys of HKEY_LOCAL_MACHINE
		while (lResultHKLM == ERROR_SUCCESS && RegEnumKeyEx(hKeyLM, dwIndex, szSubkey, &dwSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
			if (wcsstr(szSubkey, L"Supermium") || wcsstr(szSubkey, L"Supemium")) {
				RegDeleteKeyW(HKEY_LOCAL_MACHINE, std::wstring(std::wstring(L"SOFTWARE\\Clients\\StartMenuInternet\\") + std::wstring(szSubkey) + std::wstring(L"\\Capabilities\\FileAssociations")).c_str());
				RegDeleteKeyW(HKEY_LOCAL_MACHINE, std::wstring(std::wstring(L"SOFTWARE\\Clients\\StartMenuInternet\\") + std::wstring(szSubkey) + std::wstring(L"\\Capabilities\\Startmenu")).c_str());
				RegDeleteKeyW(HKEY_LOCAL_MACHINE, std::wstring(std::wstring(L"SOFTWARE\\Clients\\StartMenuInternet\\") + std::wstring(szSubkey) + std::wstring(L"\\Capabilities\\URLAssociations")).c_str());
				RegDeleteKeyW(HKEY_LOCAL_MACHINE, std::wstring(std::wstring(L"SOFTWARE\\Clients\\StartMenuInternet\\") + std::wstring(szSubkey) + std::wstring(L"\\Capabilities")).c_str());
				RegDeleteKeyW(HKEY_LOCAL_MACHINE, std::wstring(std::wstring(L"SOFTWARE\\Clients\\StartMenuInternet\\") + std::wstring(szSubkey) + std::wstring(L"\\DefaultIcon")).c_str());
				RegDeleteKeyW(HKEY_LOCAL_MACHINE, std::wstring(std::wstring(L"SOFTWARE\\Clients\\StartMenuInternet\\") + std::wstring(szSubkey) + std::wstring(L"\\InstallInfo")).c_str());
				RegDeleteKeyW(HKEY_LOCAL_MACHINE, std::wstring(std::wstring(L"SOFTWARE\\Clients\\StartMenuInternet\\") + std::wstring(szSubkey) + std::wstring(L"\\shell\\open\\command")).c_str());
				RegDeleteKeyW(HKEY_LOCAL_MACHINE, std::wstring(std::wstring(L"SOFTWARE\\Clients\\StartMenuInternet\\") + std::wstring(szSubkey) + std::wstring(L"\\shell\\open")).c_str());
				RegDeleteKeyW(HKEY_LOCAL_MACHINE, std::wstring(std::wstring(L"SOFTWARE\\Clients\\StartMenuInternet\\") + std::wstring(szSubkey) + std::wstring(L"\\shell")).c_str());
				RegDeleteKeyW(HKEY_LOCAL_MACHINE, std::wstring(std::wstring(L"SOFTWARE\\Clients\\StartMenuInternet\\") + std::wstring(szSubkey)).c_str());
				RegDeleteKeyW(HKEY_LOCAL_MACHINE, std::wstring(std::wstring(L"Software\\Classes\\") + std::wstring(szSubkey) + std::wstring(L"\\DefaultIcon")).c_str());
				RegDeleteKeyW(HKEY_LOCAL_MACHINE, std::wstring(std::wstring(L"Software\\Classes\\") + std::wstring(szSubkey) + std::wstring(L"\\shell\\open\\command")).c_str());
				RegDeleteKeyW(HKEY_LOCAL_MACHINE, std::wstring(std::wstring(L"Software\\Classes\\") + std::wstring(szSubkey) + std::wstring(L"\\shell\\open")).c_str());
				RegDeleteKeyW(HKEY_LOCAL_MACHINE, std::wstring(std::wstring(L"Software\\Classes\\") + std::wstring(szSubkey) + std::wstring(L"\\shell")).c_str());
				RegDeleteKeyW(HKEY_LOCAL_MACHINE, std::wstring(std::wstring(L"Software\\Classes\\") + std::wstring(szSubkey)).c_str());
				RegDeleteKeyW(HKEY_CLASSES_ROOT, std::wstring(std::wstring(szSubkey) + std::wstring(L"\\DefaultIcon")).c_str());
				RegDeleteKeyW(HKEY_CLASSES_ROOT, std::wstring(std::wstring(szSubkey) + std::wstring(L"\\shell\\open\\command")).c_str());
				RegDeleteKeyW(HKEY_CLASSES_ROOT, std::wstring(std::wstring(szSubkey) + std::wstring(L"\\shell\\open")).c_str());
				RegDeleteKeyW(HKEY_CLASSES_ROOT, std::wstring(std::wstring(szSubkey) + std::wstring(L"\\shell")).c_str());
				RegDeleteKeyW(HKEY_CLASSES_ROOT, szSubkey);
				--dwIndex;
			}
			dwIndex++;
			dwSize = ARRAYSIZE(szSubkey);
		}
	}

	RegDeleteKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Supermium");

	// Close registry keys
	if (lResultHKCU == ERROR_SUCCESS)
		RegCloseKey(hKeyCU);
	if (lResultHKLM == ERROR_SUCCESS)
		RegCloseKey(hKeyLM);
}

// Function to retrieve the command value from a specified subkey
PWSTR GetCommandValue(HKEY hKey, PCWSTR subkey) {
	HKEY hSubkey;
	if (RegOpenKeyExW(hKey, subkey, 0, KEY_READ, &hSubkey) != ERROR_SUCCESS) {
		return NULL;
	}
	PWSTR szValue = (PWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_PATH * sizeof(WCHAR));
	LONG dwType = MAX_PATH * sizeof(WCHAR);

	if (RegQueryValueW(hSubkey, L"shell\\open\\command", szValue, &dwType) != ERROR_SUCCESS) {
		RegCloseKey(hSubkey);
		HeapFree(GetProcessHeap(), 0, szValue);
		return NULL;
	}
	RegCloseKey(hSubkey);

	return szValue;
}

PWSTR SupermiumPreviousInstallPath(PBOOL IsHKCU)
{
	LONG lResultHKCU, lResultHKLM;
	HKEY hKeyCU = 0;
	HKEY hKeyLM = 0;
	PWSTR InstallPath = NULL;

	// Open HKEY_CURRENT_USER\Software\Clients\StartMenuInternet
	lResultHKCU = RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Clients\\StartMenuInternet", 0, KEY_READ, &hKeyCU);

	lResultHKLM = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Software\\Clients\\StartMenuInternet", 0, KEY_READ, &hKeyLM);

	// Open HKEY_LOCAL_MACHINE\Software\Clients\StartMenuInternet
	if (lResultHKLM != ERROR_SUCCESS && lResultHKCU != ERROR_SUCCESS) {
		return NULL;
	}

	// Buffer for subkey names
	wchar_t szSubkey[MAX_PATH];
	DWORD dwIndex = 0;
	DWORD dwSize = ARRAYSIZE(szSubkey);

	// Iterate through subkeys of HKEY_CURRENT_USER
	while (RegEnumKeyEx(hKeyCU, dwIndex, szSubkey, &dwSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
		if (wcsstr(szSubkey, L"Supermium") || wcsstr(szSubkey, L"Supemium")) {
			InstallPath = GetCommandValue(hKeyCU, szSubkey);
			if (InstallPath)
				break;
		}
		dwIndex++;
		dwSize = ARRAYSIZE(szSubkey);
	}

	if (!InstallPath)
	{
		// Reset index and size for HKEY_LOCAL_MACHINE
		dwIndex = 0;
		dwSize = ARRAYSIZE(szSubkey);

		// Iterate through subkeys of HKEY_LOCAL_MACHINE
		while (RegEnumKeyEx(hKeyLM, dwIndex, szSubkey, &dwSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
			if (wcsstr(szSubkey, L"Supermium") || wcsstr(szSubkey, L"Supemium")) {
				InstallPath = GetCommandValue(hKeyLM, szSubkey);
				if (InstallPath)
					break;
			}
			dwIndex++;
			dwSize = ARRAYSIZE(szSubkey);
		}
	}

	// Close registry keys
	if (lResultHKCU == ERROR_SUCCESS)
		RegCloseKey(hKeyCU);
	if (lResultHKLM == ERROR_SUCCESS)
		RegCloseKey(hKeyLM);

	if (!InstallPath)
		return NULL;

	int i = 0;
	int idxLastSlash = 0;

	while (InstallPath[i] != L'\0')
	{
		if (InstallPath[i] == L'\\')
			idxLastSlash = i;
		i++;
	}
	InstallPath[idxLastSlash] = L'\0';

	return InstallPath;
}


int main()
{
	PWSTR InstallPath;
	BOOL IsHKCU;
	int argc;
	WCHAR TempPath[MAX_PATH]{ 0 }, CurrentExecutablePath[MAX_PATH]{ 0 }, TempFilePath[MAX_PATH]{ 0 }, CommandLine[MAX_PATH]{ 0 };
	STARTUPINFOW si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	LPWSTR* Path = CommandLineToArgvW(GetCommandLineW(), &argc);

	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			if (wcsstr(Path[i], L"--payload"))
			{
				InstallPath = SupermiumPreviousInstallPath(&IsHKCU);
				if (!InstallPath)
				{
					MessageBoxW(NULL, L"A formally installed copy of Supermium could not be located. Now exiting the uninstaller.", L"Supermium Setup", 0);
					return 1;
				}
				int mb_response = MessageBoxW(NULL, L"Would you like to uninstall Supermium?", L"Supermium Setup", MB_YESNO);
				if (mb_response == IDYES)
				{
					mb_response = MessageBoxW(NULL, L"Would you like to keep your user data?", L"Supermium Setup", MB_YESNO);

					if (mb_response == IDNO)
					{
						SHFILEOPSTRUCTW ShFileOp;
						RtlZeroMemory(&ShFileOp, sizeof(SHFILEOPSTRUCTW));
						WCHAR DestPath[MAX_PATH + 2]{ 0 };
						GetEnvironmentVariableW(L"LOCALAPPDATA", DestPath, MAX_PATH + 2);
						StringCbCatW(DestPath, MAX_PATH, L"\\Supermium\\User Data");
						ShFileOp.pFrom = DestPath;
						ShFileOp.wFunc = FO_DELETE;
						ShFileOp.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR;
						SHFileOperation(&ShFileOp);
						RemoveDirectoryW(DestPath);

						RegDeleteKeyW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\App Management\\ARPCache\\Supermium");
						RegDeleteKeyW(HKEY_CURRENT_USER, L"Software\\Supermium\\PreferenceMACs\\Default\\extensions.settings");
						RegDeleteKeyW(HKEY_CURRENT_USER, L"Software\\Supermium\\PreferenceMACs\\Default");
						RegDeleteKeyW(HKEY_CURRENT_USER, L"Software\\Supermium\\PreferenceMACs\\System Profile");
						RegDeleteKeyW(HKEY_CURRENT_USER, L"Software\\Supermium\\PreferenceMACs");
						RegDeleteKeyW(HKEY_CURRENT_USER, L"Software\\Supermium\\BLBeacon");
						RegDeleteKeyW(HKEY_CURRENT_USER, L"Software\\Supermium\\StabilityMetrics");
						RegDeleteKeyW(HKEY_CURRENT_USER, L"Software\\Supermium\\ThirdParty");
						RegDeleteKeyW(HKEY_CURRENT_USER, L"Software\\Supermium");
					}

				}
				else
					return 1;

				SHFILEOPSTRUCTW ShFileOp;
				RtlZeroMemory(&ShFileOp, sizeof(SHFILEOPSTRUCTW));
				WCHAR DestPath[MAX_PATH + 2]{ 0 };
				StringCbCopyW(DestPath, MAX_PATH, InstallPath);
			//	StringCbCatW(DestPath, MAX_PATH, L"\\");
				ShFileOp.pFrom = &DestPath[1];
				ShFileOp.wFunc = FO_DELETE;
				ShFileOp.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR;
				SHFileOperation(&ShFileOp);
				if ((GetFileAttributesW(&DestPath[1]) == - 1)|| RemoveDirectoryW(&DestPath[1]))
				{
					DeleteSupermiumRegKeys();
					WCHAR DesktopPath[MAX_PATH];
					WCHAR StartMenuPath[MAX_PATH];
					SHGetFolderPathW(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, DesktopPath);
					SHGetFolderPathW(NULL, CSIDL_PROGRAMS, NULL, 0, StartMenuPath);
					StringCbCatW(DesktopPath, MAX_PATH, L"\\Supermium.lnk");
					StringCbCatW(StartMenuPath, MAX_PATH, L"\\Supermium.lnk");
					DeleteFileW(DesktopPath);
					DeleteFileW(StartMenuPath);
				}
				else
				{
					MessageBoxW(NULL, L"Unable to remove the Supermium directory.", L"Supermium Setup", MB_ICONHAND);
					HeapFree(GetProcessHeap(), 0, InstallPath);
					return 0;
				}

				MessageBoxW(NULL, L"Supermium has been uninstalled.", L"Supermium Setup", 0);
				HeapFree(GetProcessHeap(), 0, InstallPath);
				return 1;
			}
		}
	}
  

	// Get the temporary folder path
	if (!GetTempPathW(MAX_PATH, TempPath)) {
		MessageBoxW(NULL, L"Failed to get the temporary folder path", L"Uninstaller", MB_ICONERROR);
		return 1;
	}

	// Get the current executable path
	if (!GetModuleFileNameW(NULL, CurrentExecutablePath, MAX_PATH)) {
		MessageBoxW(NULL, L"Failed to get the current executable path", L"Uninstaller", MB_ICONERROR);
		return 1;
	}

	StringCchCopyW(TempFilePath, MAX_PATH, TempPath);
	StringCchCatW(TempFilePath, MAX_PATH, L"\\uninstall.exe");

	// Copy the executable to the temporary folder
	if (!CopyFileW(CurrentExecutablePath, TempFilePath, FALSE)) {
		MessageBoxW(NULL, L"Failed to copy the executable to the temporary folder", L"Uninstaller", MB_ICONERROR);
		return 1;
	}

	StringCchCatW(TempFilePath, MAX_PATH, L" --payload");

	// Run the copied executable with the --payload switch
	if (!CreateProcessW(NULL, TempFilePath, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
		MessageBoxW(NULL, TempFilePath, L"Uninstaller", MB_ICONERROR);
		return 1;
	}

	// Close process and thread handles
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return 0;
}
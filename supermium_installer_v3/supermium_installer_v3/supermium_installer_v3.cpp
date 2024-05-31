#include <string>
#include <Windows.h>
#include <Commctrl.h>
#include <strsafe.h>
#include <Shlobj.h>

#define ID_TEXTFIELD 1001
#define ID_CHECKBOX1 1002
#define ID_CHECKBOX2 1003
#define ID_CHECKBOX3 1004
#define ID_CHECKBOX4 1005
#define ID_CHECKBOX5 1009
#define ID_BUTTON1   1006
#define ID_BUTTON2   1007
#define ID_PROGRESS  1008

HWND g_hProgressBar;
HWND g_TextField;
HWND g_cb1;
HWND g_cb2;
HWND g_cb3;
HWND g_cb4;
HWND g_cb5;
HFONT hFont;

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

	if(!InstallPath)
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

	if (lResultHKCU == ERROR_SUCCESS)
		RegCloseKey(hKeyCU);
	if (lResultHKLM == ERROR_SUCCESS)
		RegCloseKey(hKeyLM);
}


BOOL InstallSupermium(HWND hwnd, LPCWSTR PathDest, BOOL InstallEmoji, BOOL Default, BOOL InstallWithoutRegistry, BOOL MakeUngoogled, BOOL ClassicTheme70)
// The previous Supermium install directory is deleted and then a new one is copied.
{
	WCHAR FontPath [MAX_PATH]{0};
	WCHAR PathDestZZ [MAX_PATH + 1] {0};
	WCHAR DefaultIconStr [MAX_PATH + 256]{0};
	WCHAR CommandStr [MAX_PATH + 256]{0};
	WCHAR HideIcons [MAX_PATH + 256]{0};
	WCHAR ReinstallCommand [MAX_PATH + 256]{0};
	WCHAR ShowIcons [MAX_PATH + 256]{0};
	WCHAR InstallSource [MAX_PATH]{0};
	WCHAR ExePath[MAX_PATH]{ 0 };
	WCHAR UninstallPath[MAX_PATH]{ 0 };
	DWORD dwShowIcons = 1;
	DWORD dwEstimatedSize = 250000;
	SHFILEOPSTRUCTW ShFileOp;
	HKEY SupermiumClassBase, SupermiumStartMenuInternetBase, SupermiumCapabilities, SupermiumInstallInfo,
		 SupermiumFileAssociations, SupermiumStartMenu, SupermiumUrlAssociations, SupermiumHklmClass,
		 SupermiumRegisteredApplications, SupermiumUninstallInfo;
	IShellLink* psl;

	SendMessage(g_hProgressBar, PBM_SETPOS, 10, 0);

	StringCchCopyW(PathDestZZ, MAX_PATH, PathDest);
	RtlZeroMemory(&ShFileOp, sizeof(SHFILEOPSTRUCTW));
	ShFileOp.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR;
	if (GetFileAttributesW(PathDest) != INVALID_FILE_ATTRIBUTES) {
		ShFileOp.pFrom = PathDestZZ;
		ShFileOp.wFunc = FO_DELETE;
		SHFileOperation(&ShFileOp);
		RemoveDirectoryW(PathDest);
	}

	if(!GetCurrentDirectoryW(MAX_PATH, InstallSource))
	{
		MessageBoxW(hwnd, std::wstring(L"Error. Win32 error code is " + std::to_wstring(GetLastError())).c_str(), L"Error", MB_ICONERROR);
		SendMessage(g_hProgressBar, PBM_SETPOS, 0, 0);
		return FALSE;
	}

	if((LOBYTE(LOWORD(GetVersion()))) >= 6)
		StringCchCatW(InstallSource, MAX_PATH, L"\\Supermium\\*\0\0"); // Vista and up allow wild cards for the source directory.
	else
		StringCchCatW(InstallSource, MAX_PATH, L"\\Supermium\0\0"); // Although XP and below are generally reliable in this case.

	ShFileOp.pFrom = InstallSource;
	ShFileOp.pTo = PathDestZZ;

	ShFileOp.wFunc = FO_COPY;

	if(SHFileOperation(&ShFileOp))
	{
		MessageBoxW(hwnd, std::wstring(L"Error. Win32 error code is " + std::to_wstring(GetLastError())).c_str(), L"Error", MB_ICONERROR);
		SendMessage(g_hProgressBar, PBM_SETPOS, 0, 0);
		return FALSE;
	}
	
	SendMessage(g_hProgressBar, PBM_SETPOS, 50, 0);

	if(!InstallWithoutRegistry)
	{
		DeleteSupermiumRegKeys();
	

	if(RegCreateKeyW(HKEY_CLASSES_ROOT, L"SupermiumHTM", &SupermiumClassBase) == ERROR_SUCCESS)
	{
		StringCbCopyW(DefaultIconStr, MAX_PATH + 256, PathDest);
		StringCbCopyW(CommandStr, MAX_PATH + 256, L"\"");
		StringCbCatW(CommandStr, MAX_PATH + 256, PathDest);
		StringCbCatW(DefaultIconStr, MAX_PATH + 256, L"\\chrome.exe,0");
		StringCbCatW(CommandStr, MAX_PATH + 256, L"\\chrome.exe\" --single-argument %1");

		StringCbCopyW(HideIcons, MAX_PATH + 256, L"\"");
		StringCbCopyW(ReinstallCommand, MAX_PATH + 256, L"\"");
		StringCbCopyW(ShowIcons, MAX_PATH + 256, L"\"");

		StringCbCatW(HideIcons, MAX_PATH + 256, PathDest);
		StringCbCatW(ReinstallCommand, MAX_PATH + 256, PathDest);
		StringCbCatW(ShowIcons, MAX_PATH + 256, PathDest);

		StringCbCatW(HideIcons, MAX_PATH + 256, L"\\chrome.exe\" --hide-icons");
		StringCbCatW(ReinstallCommand, MAX_PATH + 256, L"\\chrome.exe\" --make-default-browser");
		StringCbCatW(ShowIcons, MAX_PATH + 256, L"\\chrome.exe\" --show-icons");

		RegSetValueW(SupermiumClassBase, NULL, REG_SZ, L"Supermium HTML Document", sizeof(L"Supermium HTML Document"));
		RegSetValueW(SupermiumClassBase, L"DefaultIcon", REG_SZ, DefaultIconStr, wcslen(DefaultIconStr)*sizeof(WCHAR));
		RegSetValueW(SupermiumClassBase, L"shell\\open\\command", REG_SZ, CommandStr, wcslen(CommandStr)*sizeof(WCHAR));

		RegCreateKeyW(HKEY_LOCAL_MACHINE, L"Software\\Classes\\SupermiumHTM", &SupermiumHklmClass);
		RegSetValueW(SupermiumHklmClass, NULL, REG_SZ, L"Supermium HTML Document", sizeof(L"Supermium HTML Document"));
		RegSetValueW(SupermiumHklmClass, L"DefaultIcon", REG_SZ, DefaultIconStr, wcslen(DefaultIconStr)*sizeof(WCHAR));
		RegSetValueW(SupermiumHklmClass, L"shell\\open\\command", REG_SZ, CommandStr, wcslen(CommandStr)*sizeof(WCHAR));

		if(RegCreateKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Clients\\StartMenuInternet\\Supemium", &SupermiumStartMenuInternetBase) == ERROR_SUCCESS)
		{
			RegSetValueW(SupermiumStartMenuInternetBase, NULL, REG_SZ, L"Supermium", sizeof(L"Supermium"));
			RegSetValueW(SupermiumStartMenuInternetBase, L"shell\\open\\command", REG_SZ, CommandStr, wcslen(CommandStr)*sizeof(WCHAR));
			RegSetValueW(SupermiumStartMenuInternetBase, L"DefaultIcon", REG_SZ, DefaultIconStr, wcslen(DefaultIconStr)*sizeof(WCHAR));
			RegCreateKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Clients\\StartMenuInternet\\Supemium\\Capabilities", &SupermiumCapabilities);
			RegCreateKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Clients\\StartMenuInternet\\Supemium\\Capabilities\\FileAssociations", &SupermiumFileAssociations);
			RegCreateKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Clients\\StartMenuInternet\\Supemium\\Capabilities\\Startmenu", &SupermiumStartMenu);
			RegCreateKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Clients\\StartMenuInternet\\Supemium\\Capabilities\\URLAssociations", &SupermiumUrlAssociations);

			RegSetValueExW(SupermiumCapabilities, L"ApplicationDescription", 0, REG_SZ, (const PBYTE)L"Supermium is a web browser targetting legacy versions of Windows and has various other important features.",
				sizeof(L"Supermium is a web browser targetting legacy versions of Windows and has various other important features."));
			RegSetValueExW(SupermiumCapabilities, L"ApplicationIcon", 0, REG_SZ, (const PBYTE)DefaultIconStr, wcslen(DefaultIconStr)*sizeof(WCHAR));
			RegSetValueExW(SupermiumCapabilities, L"ApplicationName", 0, REG_SZ, (const PBYTE)L"Supermium", sizeof(L"Supermium"));

			RegSetValueExW(SupermiumFileAssociations, L".htm", 0, REG_SZ, (const PBYTE)L"SupermiumHTM", sizeof(L"SupermiumHTM"));
			RegSetValueExW(SupermiumFileAssociations, L".html", 0, REG_SZ, (const PBYTE)L"SupermiumHTM", sizeof(L"SupermiumHTM"));
			RegSetValueExW(SupermiumFileAssociations, L".pdf", 0, REG_SZ, (const PBYTE)L"SupermiumHTM", sizeof(L"SupermiumHTM"));
			RegSetValueExW(SupermiumFileAssociations, L".shtml", 0, REG_SZ, (const PBYTE)L"SupermiumHTM", sizeof(L"SupermiumHTM"));
			RegSetValueExW(SupermiumFileAssociations, L".svg", 0, REG_SZ, (const PBYTE)L"SupermiumHTM", sizeof(L"SupermiumHTM"));
			RegSetValueExW(SupermiumFileAssociations, L".webp", 0, REG_SZ, (const PBYTE)L"SupermiumHTM", sizeof(L"SupermiumHTM"));
			RegSetValueExW(SupermiumFileAssociations, L".xht", 0, REG_SZ, (const PBYTE)L"SupermiumHTM", sizeof(L"SupermiumHTM"));
			RegSetValueExW(SupermiumFileAssociations, L".xhtml", 0, REG_SZ, (const PBYTE)L"SupermiumHTM", sizeof(L"SupermiumHTM"));

			RegSetValueExW(SupermiumStartMenu, L"StartMenuInternet", 0, REG_SZ, (const PBYTE)L"Supemium", sizeof(L"Supemium"));

			RegSetValueExW(SupermiumUrlAssociations, L"http", 0, REG_SZ, (const PBYTE)L"SupermiumHTM", sizeof(L"SupermiumHTM"));
			RegSetValueExW(SupermiumUrlAssociations, L"https", 0, REG_SZ, (const PBYTE)L"SupermiumHTM", sizeof(L"SupermiumHTM"));
			RegSetValueExW(SupermiumUrlAssociations, L"irc", 0, REG_SZ, (const PBYTE)L"SupermiumHTM", sizeof(L"SupermiumHTM"));
			RegSetValueExW(SupermiumUrlAssociations, L"mailto", 0, REG_SZ, (const PBYTE)L"SupermiumHTM", sizeof(L"SupermiumHTM"));
			RegSetValueExW(SupermiumUrlAssociations, L"mms", 0, REG_SZ, (const PBYTE)L"SupermiumHTM", sizeof(L"SupermiumHTM"));
			RegSetValueExW(SupermiumUrlAssociations, L"news", 0, REG_SZ, (const PBYTE)L"SupermiumHTM", sizeof(L"SupermiumHTM"));
			RegSetValueExW(SupermiumUrlAssociations, L"nntp", 0, REG_SZ, (const PBYTE)L"SupermiumHTM", sizeof(L"SupermiumHTM"));
			RegSetValueExW(SupermiumUrlAssociations, L"sms", 0, REG_SZ, (const PBYTE)L"SupermiumHTM", sizeof(L"SupermiumHTM"));
			RegSetValueExW(SupermiumUrlAssociations, L"smsto", 0, REG_SZ, (const PBYTE)L"SupermiumHTM", sizeof(L"SupermiumHTM"));
			RegSetValueExW(SupermiumUrlAssociations, L"snews", 0, REG_SZ, (const PBYTE)L"SupermiumHTM", sizeof(L"SupermiumHTM"));
			RegSetValueExW(SupermiumUrlAssociations, L"tel", 0, REG_SZ, (const PBYTE)L"SupermiumHTM", sizeof(L"SupermiumHTM"));
			RegSetValueExW(SupermiumUrlAssociations, L"urn", 0, REG_SZ, (const PBYTE)L"SupermiumHTM", sizeof(L"SupermiumHTM"));
			RegSetValueExW(SupermiumUrlAssociations, L"webcal", 0, REG_SZ, (const PBYTE)L"SupermiumHTM", sizeof(L"SupermiumHTM"));

			RegCreateKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Clients\\StartMenuInternet\\Supemium\\InstallInfo", &SupermiumInstallInfo);
			RegSetValueExW(SupermiumInstallInfo, L"HideIconsCommand", 0, REG_SZ, (const PBYTE)HideIcons, wcslen(HideIcons)*sizeof(WCHAR));
			RegSetValueExW(SupermiumInstallInfo, L"ShowIconsCommand", 0, REG_SZ, (const PBYTE)ShowIcons, wcslen(ShowIcons)*sizeof(WCHAR));
			RegSetValueExW(SupermiumInstallInfo, L"ReinstallCommand", 0, REG_SZ, (const PBYTE)ReinstallCommand, wcslen(ReinstallCommand)*sizeof(WCHAR));
			RegSetValueExW(SupermiumInstallInfo, L"IconsVisible", 0, REG_DWORD, (const PBYTE)&dwShowIcons, sizeof(DWORD));

			RegCreateKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Supermium", &SupermiumUninstallInfo);
			StringCbCopyW(ExePath, MAX_PATH, PathDest);
			StringCbCatW(ExePath, MAX_PATH, L"\\chrome.exe");
			RegSetValueExW(SupermiumUninstallInfo, L"DisplayIcon", 0, REG_SZ, (const PBYTE)ExePath, wcslen(ExePath) * sizeof(WCHAR));
			RegSetValueExW(SupermiumUninstallInfo, L"DisplayName", 0, REG_SZ, (const PBYTE)L"Supermium", sizeof(L"Supermium"));
			RegSetValueExW(SupermiumUninstallInfo, L"InstallLocation", 0, REG_SZ, (const PBYTE)PathDest, wcslen(PathDest) * sizeof(WCHAR));
			RegSetValueExW(SupermiumUninstallInfo, L"NoModify", 0, REG_DWORD, (const PBYTE)&dwShowIcons, sizeof(DWORD));
			RegSetValueExW(SupermiumUninstallInfo, L"NoRepair", 0, REG_DWORD, (const PBYTE)&dwShowIcons, sizeof(DWORD));
			RegSetValueExW(SupermiumUninstallInfo, L"EstimatedSize", 0, REG_DWORD, (const PBYTE)&dwEstimatedSize, sizeof(DWORD));
			RegSetValueExW(SupermiumUninstallInfo, L"DisplayVersion", 0, REG_SZ, (const PBYTE)L"122.0.6261.152", sizeof(L"122.0.6261.152"));
			StringCbCopyW(UninstallPath, MAX_PATH, PathDest);
			StringCbCatW(UninstallPath, MAX_PATH, L"\\uninstall.exe");
			RegSetValueExW(SupermiumUninstallInfo, L"UninstallString", 0, REG_SZ, (const PBYTE)UninstallPath, wcslen(UninstallPath) * sizeof(WCHAR));

			if(RegOpenKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\RegisteredApplications", &SupermiumRegisteredApplications) == ERROR_SUCCESS)
			{
				RegSetValueExW(SupermiumRegisteredApplications, L"Supemium", 0, REG_SZ, (const PBYTE)L"Software\\Clients\\StartMenuInternet\\Supemium\\Capabilities",
							   sizeof(L"Software\\Clients\\StartMenuInternet\\Supemium\\Capabilities"));
			}
		}
	  }
    }
	SendMessage(g_hProgressBar, PBM_SETPOS, 70, 0);

	if(InstallEmoji)
	{
		GetWindowsDirectoryW(FontPath, MAX_PATH);
		StringCbCatW(FontPath, MAX_PATH, L"\\Fonts\\NotoEmoji.ttf");
		MoveFileExW(L"NotoEmoji.ttf", FontPath, MOVEFILE_COPY_ALLOWED);
		AddFontResourceW(FontPath);
	}
	SendMessage(g_hProgressBar, PBM_SETPOS, 85, 0);
	if(Default)
	{
		HRESULT hres = CoInitialize(NULL);
		if (SUCCEEDED(hres)) 
		{ 
			   hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl); 
				if (SUCCEEDED(hres)) 
				{ 
				IPersistFile* ppf; 
				WCHAR ShortcutPath [MAX_PATH];
				StringCbCopyW(ShortcutPath, MAX_PATH, PathDest);
				StringCbCatW(ShortcutPath, MAX_PATH, L"\\chrome.exe");
		 
				// Set the path to the shortcut target and add the description. 
				psl->SetPath(ShortcutPath); 
				psl->SetDescription(L"Supermium Web Browser"); 

				if (MakeUngoogled)
				{
					psl->SetArguments(L"--ungoogled-supermium");
				}

				if (ClassicTheme70)
				{
					psl->SetArguments(L"--classic-omnibox --classic-omnibox-border --compact-ui --disable-features=DownloadBubble,TabHoverCards,PowerBookmarksSidePanel --enable-features=SupermiumCustomTabs");
				}

				if (ClassicTheme70 && MakeUngoogled)
				{
					psl->SetArguments(L"--ungoogled-supermium --classic-omnibox --classic-omnibox-border --compact-ui --disable-features=DownloadBubble,TabHoverCards,PowerBookmarksSidePanel --enable-features=SupermiumCustomTabs");
				}
		 
				// Query IShellLink for the IPersistFile interface, used for saving the 
				// shortcut in persistent storage. 
				hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf); 
		 
				if (SUCCEEDED(hres)) 
				{ 
					WCHAR DesktopPath [MAX_PATH];
					WCHAR StartMenuPath[MAX_PATH];
					SHGetFolderPathW(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, DesktopPath);
					SHGetFolderPathW(NULL, CSIDL_PROGRAMS, NULL, 0, StartMenuPath);
					StringCbCatW(DesktopPath, MAX_PATH, L"\\Supermium.lnk");
					StringCbCatW(StartMenuPath, MAX_PATH, L"\\Supermium.lnk");
					hres = ppf->Save(DesktopPath, TRUE); 
					hres = ppf->Save(StartMenuPath, TRUE);
					ppf->Release(); 
				} 
				psl->Release(); 
				} 
			CoUninitialize();
		}
	}

	SendMessage(g_hProgressBar, PBM_SETPOS, 100, 0);
	return TRUE;
}
// Earlier releases of Supermium on Windows XP dumped the user profile in the temporary directory because the LOCALAPPDATA environment variable was not available.
// Eventually this was resolved and now Supermium will migrate such a profile to the path pointed to by CSIDL_APPDATA.
void MigrateSupermiumSettingsFromTemp()
{
	WCHAR TempPath [MAX_PATH];
	WCHAR DestPath [MAX_PATH];
	GetTempPathW(MAX_PATH, TempPath);
	StringCbCatW(TempPath, MAX_PATH, L"\\Supermium");
	SHGetFolderPathW(NULL, CSIDL_APPDATA, NULL, 0, DestPath);
	StringCbCatW(DestPath, MAX_PATH, L"\\Supermium");
	MoveFileExW(TempPath, DestPath, MOVEFILE_COPY_ALLOWED);
}

// Function to retrieve the command value from a specified subkey
PWSTR GetCommandValue(HKEY hKey, PCWSTR subkey) {
    HKEY hSubkey;
    if (RegOpenKeyExW(hKey, subkey, 0, KEY_READ, &hSubkey) != ERROR_SUCCESS) {
        return NULL;
    }
    PWSTR szValue = (PWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_PATH*sizeof(WCHAR));
	LONG dwType = MAX_PATH*sizeof(WCHAR);

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
			if(InstallPath)
				break;
        }
        dwIndex++;
        dwSize = ARRAYSIZE(szSubkey);
    }

	if(!InstallPath)
	{
		// Reset index and size for HKEY_LOCAL_MACHINE
		dwIndex = 0;
		dwSize = ARRAYSIZE(szSubkey);

		// Iterate through subkeys of HKEY_LOCAL_MACHINE
		while (RegEnumKeyEx(hKeyLM, dwIndex, szSubkey, &dwSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
			if (wcsstr(szSubkey, L"Supermium") || wcsstr(szSubkey, L"Supemium")) {
				InstallPath = GetCommandValue(hKeyLM, szSubkey);
				if(InstallPath)
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

	if(!InstallPath)
		return NULL;

	int i = 0;
	int idxLastSlash = 0;

	while(InstallPath[i] != L'\0')
	{
		if(InstallPath[i] == L'\\')
			idxLastSlash = i;
		i++;
	}
	InstallPath[idxLastSlash] = L'\0';

    return InstallPath;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	WCHAR DefaultPath [MAX_PATH];
	WCHAR* Path;
	int PathLen;
	WCHAR* PreviousSupermiumInstallPath;
	int MessageBoxResult;
	BOOL IsHKCU;
    switch (msg)
    {
    case WM_CREATE:
    {
		/*
			Here in the WM_CREATE message, we are going to do a couple of things:
			-check for a Supermium settings folder in Temp, which will be moved to %LOCALAPPDATA%\CSIDL_APPDATA on Windows XP
			-check for an existing Supermium install using the registry and offer to uninstall or upgrade.
			The upgrade path goes directly to the setup window with the existing path in the text field.
			The uninstall path brings up an extra message box asking if the user wants to retain their data.
		*/
		MigrateSupermiumSettingsFromTemp();
		PreviousSupermiumInstallPath = SupermiumPreviousInstallPath(&IsHKCU);
		hFont = CreateFont(
            14,                         // Height of font
            0,                          // Width of font
            0,                          // Angle of escapement
            0,                          // Orientation angle
            FW_NORMAL,                  // Font weight
            FALSE,                      // Italic
            FALSE,                      // Underline
            FALSE,                      // Strikeout
            DEFAULT_CHARSET,            // Character set identifier
            OUT_DEFAULT_PRECIS,         // Output precision
            CLIP_DEFAULT_PRECIS,        // Clipping precision
            DEFAULT_QUALITY,            // Output quality
            DEFAULT_PITCH | FF_DONTCARE,// Pitch and family
            L"Tahoma"                   // Font name
        );

        // Create text field
		SendMessage(CreateWindowW(L"STATIC", L"Specify the location of the Supermium folder.", WS_VISIBLE | WS_CHILD,
            10, 10, 300, 25, hwnd, (HMENU)ID_TEXTFIELD, NULL, NULL), WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
        g_TextField = CreateWindowW(L"EDIT", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            10, 50, 350, 25, hwnd, (HMENU)ID_TEXTFIELD, NULL, NULL);
		SendMessage(g_TextField, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		if(PreviousSupermiumInstallPath)
		{
			SetWindowText(g_TextField, &PreviousSupermiumInstallPath[1]);
		}
		else
		{
			SHGetFolderPathW(NULL, CSIDL_PROGRAM_FILES, NULL, 0, DefaultPath);
			StringCbCatW(DefaultPath, MAX_PATH, L"\\Supermium");
			SetWindowText(g_TextField, DefaultPath);
		}

        // Create checkboxes
        g_cb1 = CreateWindowW(L"BUTTON", L"Install Noto Emoji font", WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
            10, 90, 200, 25, hwnd, (HMENU)ID_CHECKBOX1, NULL, NULL);
        g_cb2 = CreateWindowW(L"BUTTON", L"Create shortcuts for Supermium", WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
            10, 120, 300, 25, hwnd, (HMENU)ID_CHECKBOX2, NULL, NULL);
        g_cb3 = CreateWindowW(L"BUTTON", L"Install without modifying the registry", WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
            10, 150, 300, 25, hwnd, (HMENU)ID_CHECKBOX3, NULL, NULL);
        g_cb4 = CreateWindowW(L"BUTTON", L"Enable Ungoogled Supermium mode in shortcut", WS_VISIBLE | WS_CHILD | BS_CHECKBOX | WS_DISABLED,
            10, 180, 300, 25, hwnd, (HMENU)ID_CHECKBOX4, NULL, NULL);
        g_cb5 = CreateWindowW(L"BUTTON", L"Enable classic v60 interface mode in shortcut", WS_VISIBLE | WS_CHILD | BS_CHECKBOX | WS_DISABLED,
            10, 210, 300, 25, hwnd, (HMENU)ID_CHECKBOX5, NULL, NULL);

		SendMessage(g_cb1, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		SendMessage(g_cb2, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		SendMessage(g_cb3, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		SendMessage(g_cb4, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		SendMessage(g_cb5, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

        // Create buttons
        SendMessage(CreateWindowW(L"BUTTON", L"OK", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            90, 280, 100, 25, hwnd, (HMENU)ID_BUTTON1, NULL, NULL), WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
        SendMessage(CreateWindowW(L"BUTTON", L"Cancel", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            220, 280, 100, 25, hwnd, (HMENU)ID_BUTTON2, NULL, NULL), WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

		SendMessage(g_TextField, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));
		SendMessage(g_TextField, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

        // Create progress bar
        g_hProgressBar = CreateWindowW(PROGRESS_CLASS, NULL, WS_VISIBLE | WS_CHILD,
            10, 240, 300, 20, hwnd, (HMENU)ID_PROGRESS, NULL, NULL);
        SendMessage(g_hProgressBar, PBM_SETPOS, 0, 0); // Set initial position

		
    }
    break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_BUTTON1:
			PathLen = GetWindowTextLengthW(g_TextField);
			Path = (PWCHAR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (PathLen + 1)*sizeof(WCHAR));
			if (Path) {
				GetWindowTextW(g_TextField, Path, PathLen + 1);
				if(InstallSupermium(hwnd, Path, SendMessage(g_cb1, BM_GETCHECK, 0, 0), SendMessage(g_cb2, BM_GETCHECK, 0, 0), SendMessage(g_cb3, BM_GETCHECK, 0, 0),
					                SendMessage(g_cb4, BM_GETCHECK, 0, 0), SendMessage(g_cb5, BM_GETCHECK, 0, 0)))
				{
					MessageBoxW(hwnd, L"Supermium setup has successfully completed.", L"Supermium Setup", MB_OK);
					HeapFree(GetProcessHeap(), 0, Path);
					PostQuitMessage(0);
					break;
				}
				HeapFree(GetProcessHeap(), 0, Path);
			}
		break;
		case ID_BUTTON2:
			MessageBoxResult = MessageBoxA(hwnd, "Would you like to cancel Supermium Setup?", "Supermium Setup", MB_YESNO);
			if(MessageBoxResult == IDYES)
			{
				DeleteObject(hFont);
				PostQuitMessage(0);
				break;
			}
		break;
		case ID_CHECKBOX1:
            if(SendMessage(g_cb1, BM_GETCHECK, 0, 0) == BST_CHECKED)
				SendMessage(g_cb1, BM_SETCHECK, BST_UNCHECKED, 0);
			else 
				SendMessage(g_cb1, BM_SETCHECK, BST_CHECKED, 0);
		break;
		case ID_CHECKBOX2:
            if(SendMessage(g_cb2, BM_GETCHECK, 0, 0) == BST_CHECKED)
			{
				EnableWindow(g_cb4, FALSE);
				EnableWindow(g_cb5, FALSE);
				SendMessage(g_cb2, BM_SETCHECK, BST_UNCHECKED, 0);
				SendMessage(g_cb4, BM_SETCHECK, BST_UNCHECKED, 0);
			}
			else 
			{
				EnableWindow(g_cb4, TRUE);
				EnableWindow(g_cb5, TRUE);
				SendMessage(g_cb2, BM_SETCHECK, BST_CHECKED, 0);
			}
		break;
		case ID_CHECKBOX3:
            if(SendMessage(g_cb3, BM_GETCHECK, 0, 0) == BST_CHECKED)
				SendMessage(g_cb3, BM_SETCHECK, BST_UNCHECKED, 0);
			else 
				SendMessage(g_cb3, BM_SETCHECK, BST_CHECKED, 0);
		break;
		case ID_CHECKBOX4:
            if(SendMessage(g_cb4, BM_GETCHECK, 0, 0) == BST_CHECKED)
				SendMessage(g_cb4, BM_SETCHECK, BST_UNCHECKED, 0);
			else 
				SendMessage(g_cb4, BM_SETCHECK, BST_CHECKED, 0);
		break;
		case ID_CHECKBOX5:
            if(SendMessage(g_cb5, BM_GETCHECK, 0, 0) == BST_CHECKED)
				SendMessage(g_cb5, BM_SETCHECK, BST_UNCHECKED, 0);
			else 
				SendMessage(g_cb5, BM_SETCHECK, BST_CHECKED, 0);
		break;
		}
	break;
    case WM_DESTROY:
		DeleteObject(hFont);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
/*
	There are two options: install with the use of the GUI or use command-line commands to 
*/
{
    WNDCLASSW wc = { 0 };
    wc.lpszClassName = L"MyWindowClass";
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(0, IDC_ARROW);
	int argc;
	PWSTR InstallPath = NULL;
	BOOL IsHKCU, isSilent = FALSE, bInstallEmoji = FALSE, bDefault = FALSE, bInstallWithoutRegistry = FALSE, bMakeUngoogled = FALSE, bClassicTheme70 = FALSE, PathFromCmdLine = FALSE;

	LPWSTR* Path = CommandLineToArgvW(GetCommandLineW(), &argc);

	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			if (wcsstr(Path[i], L"--silent"))
				isSilent = TRUE;

			if (wcsstr(Path[i], L"--path=") && wcslen(Path[i]) > 7)
			{
				if (!InstallPath) 
				{
				   PathFromCmdLine = TRUE;
				   InstallPath = &Path[i][7]; // Format is --path=%InstallPath%.
				}
			}

			if (wcsstr(Path[i], L"--system-level")) // This flag is preserved from the original Chromium installer
			{ 
				if (!InstallPath) 
				{
					InstallPath = (PWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, MAX_PATH * sizeof(WCHAR));
					if (!InstallPath)
					{
						MessageBoxA(NULL, "Failed to allocate memory.", "Supermium Setup", MB_ICONERROR);
						return 0;
					}
					SHGetFolderPathW(NULL, CSIDL_PROGRAM_FILES, NULL, 0, InstallPath);
					StringCbCatW(InstallPath, MAX_PATH, L"\\Supermium");
				}
			}
			// both --path and --system-level flags can coexist but are redundant; the first one to be ennumerated will be the one that will be used to 
			// determine Supermium's path.
			if (wcsstr(Path[i], L"--install_emoji"))
				bInstallEmoji = TRUE;
			if (wcsstr(Path[i], L"--shortcuts"))
				bDefault = TRUE;
			if (wcsstr(Path[i], L"--no_registry_writes"))
				bInstallWithoutRegistry = TRUE;
			if (wcsstr(Path[i], L"--ungoogled"))
				bMakeUngoogled = TRUE;
			if (wcsstr(Path[i], L"--classic_theme"))
				bClassicTheme70 = TRUE;
		}
		if (!InstallPath && isSilent)
		{
			MessageBoxA(NULL, "Failed to specify a valid path for unattended mode. Please provide a valid path and try again.", "Supermium Setup", MB_ICONERROR);
			return 0;
		}
		if(isSilent)
		{ 
		   InstallSupermium(NULL, InstallPath, bInstallEmoji, bDefault, bInstallWithoutRegistry, bMakeUngoogled, bClassicTheme70);
		   if (InstallPath && !PathFromCmdLine)
			   HeapFree(GetProcessHeap(), 0, InstallPath);
		   return 1;
		}
	}

    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"Supermium Setup", WS_POPUPWINDOW | WS_CAPTION | WS_VISIBLE,
        100, 100, 400, 360, 0, 0, hInstance, 0);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}


#include"windowsApi.h"
#include"class.h"
#include"interface.h"

using namespace std;
//全局变量
Buffer cfgBuf;
void LoadConfigBuf(const char *path, const char *section, HWND hdlg, INIEdit *edit, int item_count)
{
	char buffer[MAX_PATH] = { 0 };
	int hex_val = 0;
	FILE* cfgFile = fopen(path, "r");
	if (!cfgFile)
		return;
	if (section == NULL)
		return;
	for (int i = 0; i < item_count; i++)
	{
		if (edit[i].type == NULL || edit[i].var == NULL) break;
		GetPrivateProfileString(section, edit[i].name, NULL, buffer, MAX_PATH, path);
		switch (edit[i].type)
		{
		case DLGTYPE_CHECK_BOOL:
			*((int *)(edit[i].var)) = atoi(buffer);
			if (hdlg == NULL) break;
			SendDlgItemMessage(hdlg, edit[i].idc, BM_SETCHECK, atoi(buffer) ? BST_CHECKED : BST_UNCHECKED, 0);
			break;

		case DLGTYPE_INPUT_INT:
			*((int *)(edit[i].var)) = atoi(buffer);
			if (hdlg == NULL) break;
			SetDlgItemText(hdlg, edit[i].idc, buffer);
			break;

		case DLGTYPE_INPUT_FLOAT:
			*((float *)(edit[i].var)) = atof(buffer);
			if (hdlg == NULL) break;
			SetDlgItemText(hdlg, edit[i].idc, buffer);
			break;

		case DLGTYPE_INPUT_DOUBLE:
			*((double *)(edit[i].var)) = atof(buffer);
			if (hdlg == NULL) break;
			SetDlgItemText(hdlg, edit[i].idc, buffer);
			break;

		case DLGTYPE_INPUT_STRING:
			strcpy((char *)(edit[i].var), buffer);
			if (hdlg == NULL) break;
			SetDlgItemText(hdlg, edit[i].idc, buffer);
			break;

		case DLGTYPE_INPUT_HEX:
			sscanf(buffer, "%hx", &hex_val);
			*((int *)(edit[i].var)) = hex_val;
			memset(buffer, 0, sizeof(buffer));
			sprintf(buffer, "%02x", hex_val);
			if (hdlg == NULL) break;
			SetDlgItemText(hdlg, edit[i].idc, buffer);
			break;

		case DLGTYPE_INPUT_HEX4:
			sscanf(buffer, "%hx", &hex_val);
			*((int *)(edit[i].var)) = hex_val;
			memset(buffer, 0, sizeof(buffer));
			sprintf(buffer, "%04x", hex_val);
			if (hdlg == NULL) break;
			SetDlgItemText(hdlg, edit[i].idc, buffer);
			break;

		case DLGTYPE_COMBO_INT:
			*((int *)(edit[i].var)) = atoi(buffer);
			if (hdlg == NULL) break;
			SendDlgItemMessage(hdlg, edit[i].idc, CB_SETCURSEL, atoi(buffer), 0L);
			break;

		case DLGTYPE_COMBO_INPUT_INT: {
			char str[100] = { 0 };
			int val1 = atoi(buffer);
			*((int *)(edit[i].var)) = val1;
			if (hdlg == NULL) break;
			int val2 = 0;
			int n = SendDlgItemMessage(hdlg, edit[i].idc, CB_GETCURSEL, 0, 0L);
			for (int j = 0; j < n; j++)
			{
				SendDlgItemMessage(hdlg, edit[i].idc, CB_GETLBTEXT, j, (LPARAM)str);
				val2 = atoi(str);
				if (val1 == val2) {
					SendDlgItemMessage(hdlg, edit[i].idc, CB_SETCURSEL, atoi(buffer), 0L);
					break;
				}
			}
		}
		break;

		case DLGTYPE_RADIO_BOOL:
		{
			int idc_1 = LOWORD(edit[i].idc);
			int idc_2 = HIWORD(edit[i].idc);
			*((int *)(edit[i].var)) = atoi(buffer);
			if (hdlg == NULL) break;
			if (atoi(buffer) == 0) {
				SendMessage(GetDlgItem(hdlg, idc_1), BM_SETCHECK, BST_CHECKED, 0);
				SendMessage(GetDlgItem(hdlg, idc_2), BM_SETCHECK, BST_UNCHECKED, 0);
			}
			else {
				SendMessage(GetDlgItem(hdlg, idc_2), BM_SETCHECK, BST_CHECKED, 0);
				SendMessage(GetDlgItem(hdlg, idc_1), BM_SETCHECK, BST_UNCHECKED, 0);
			}
		}
		break;
		}
	}
}

void SaveConfigBuf(const char *path, const char *section, HWND hdlg, INIEdit *edit, int item_count)
{
	char buffer[MAX_PATH] = { 0 };
	BOOL is_checked = FALSE;
	char hex[20] = { 0 };
	FILE* cfgFile = fopen(path, "w");
	if (!cfgFile)
		return;
	if (section == NULL)
		return;
	for (int i = 0; i < item_count; i++)
	{
		if (edit[i].idc == NULL || edit[i].type == NULL || edit[i].var == NULL || edit[i].var == NULL) break;

		switch (edit[i].type)
		{
		case DLGTYPE_CHECK_BOOL:
			if (edit[i].idc != NULL) {
				is_checked = SendDlgItemMessage(hdlg, edit[i].idc, BM_GETCHECK, 0, 0);
				*((int *)(edit[i].var)) = (is_checked ? 1 : 0);
				WritePrivateProfileString(section, edit[i].name, (is_checked ? "1" : "0"), path);
			}
			break;

		case DLGTYPE_INPUT_INT:
			if (edit[i].idc != NULL) {
				GetDlgItemText(hdlg, edit[i].idc, buffer, MAX_PATH);
				*((int *)(edit[i].var)) = atoi(buffer);
				WritePrivateProfileString(section, edit[i].name,buffer, path);
			}		
			break;

		case DLGTYPE_INPUT_FLOAT:
			if (edit[i].idc != NULL) {
				GetDlgItemText(hdlg, edit[i].idc, buffer, MAX_PATH);
				*((float *)(edit[i].var)) = atof(buffer);
				WritePrivateProfileString(section, edit[i].name, buffer, path);
			}			
			break;

		case DLGTYPE_INPUT_DOUBLE:
			if (edit[i].idc != NULL) {
				GetDlgItemText(hdlg, edit[i].idc, buffer, MAX_PATH);
				*((double *)(edit[i].var)) = atof(buffer);
				WritePrivateProfileString(section, edit[i].name, buffer, path);
			}
			break;

		case DLGTYPE_INPUT_STRING:
			if (edit[i].idc != NULL) {
				GetDlgItemText(hdlg, edit[i].idc, buffer, MAX_PATH);
				strcpy((char *)(edit[i].var), buffer);
				WritePrivateProfileString(section, edit[i].name, buffer, path);
			}
			break;

		case DLGTYPE_INPUT_HEX:
		case DLGTYPE_INPUT_HEX4:
			if (edit[i].idc != NULL) {
				GetDlgItemText(hdlg, edit[i].idc, buffer, MAX_PATH);
				sprintf(hex, "0X%s", buffer);
				WritePrivateProfileString(section, edit[i].name, hex, path);
			}
			break;

		case DLGTYPE_COMBO_INT:
			if (edit[i].idc != NULL) {
				*((int *)(edit[i].var)) = SendDlgItemMessage(hdlg, edit[i].idc, CB_GETCURSEL, 0, 0L);
				sprintf(buffer, "%d", *((int*)edit[i].var));
				WritePrivateProfileString(section, edit[i].name, buffer, path);
			}
			break;

		case DLGTYPE_COMBO_INPUT_INT:
			if (edit[i].idc != NULL) {
				char str[100] = { 0 };
				int n = SendDlgItemMessage(hdlg, edit[i].idc, CB_GETCURSEL, 0, 0L);
				SendDlgItemMessage(hdlg, edit[i].idc, CB_GETLBTEXT, n, (LPARAM)str);
				*((int *)(edit[i].var)) = atoi(str);
				WritePrivateProfileString(section, edit[i].name, str, path);
			}
			break;

		case DLGTYPE_RADIO_BOOL:
			if (edit[i].idc != NULL) {
				int b = (int)SendMessage(GetDlgItem(hdlg, LOWORD(edit[i].idc)), BM_GETCHECK, 0, 0);
				*((int *)(edit[i].var)) = (b ? 0 : 1);
				sprintf(buffer, "%d", (b ? 0 : 1));
				WritePrivateProfileString(section, edit[i].name, buffer, path);
			}
			break;
		}
	}
}

void SetIcon(HWND hwnd, int large_icon_id, int small_icon_id)
{
	OSVERSIONINFO version_info;

	ZeroMemory(&version_info, sizeof(version_info));
	*(int *)(&version_info) = sizeof(version_info);

	GetVersionEx(&version_info);

	if ((version_info.dwPlatformId == VER_PLATFORM_WIN32_NT) && (version_info.dwMajorVersion <= 3) &&
		(version_info.dwMinorVersion <= 51)) {
		SetClassLong(hwnd, GCL_HICON, (LONG)LoadIcon(m_instance, MAKEINTRESOURCE(large_icon_id)));
	}
	else {
		SendMessage(hwnd, WM_SETICON, TRUE, (LPARAM)LoadIcon(m_instance, MAKEINTRESOURCE(large_icon_id)));
		SendMessage(hwnd, WM_SETICON, FALSE, (LPARAM)LoadIcon(m_instance, MAKEINTRESOURCE(small_icon_id)));
	}
}

HMENU CreateMenu(HWND hwnd, int id)
{
	HINSTANCE hinst = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
	HMENU hmenu = LoadMenu(hinst, MAKEINTRESOURCE(id));
	SetMenu(hwnd, hmenu);

	return hmenu;
}

HWND CreateStatusbar(HWND hwnd, const int *sub_w, int cnt, unsigned int id)//底部信息条
{
	HWND hstatusbar = CreateStatusWindow(WS_CHILD | WS_VISIBLE | WS_BORDER, "", hwnd, id);
	SendMessage(hstatusbar, SB_SETPARTS, cnt, (LPARAM)sub_w);

	for (int i = 0; i < cnt; i++) {
		SendMessage(hstatusbar, SB_SETTEXT, i, (LPARAM)"");
	}

	return hstatusbar;
}

void GetVersion(HMODULE hmodule, BOOL show_buildnum, char *ver)
{
	VisionData	  Version;
	unsigned long	  versionSize = 0;
	unsigned long	  versionHandle;
	VS_FIXEDFILEINFO *file_info = NULL;
	HANDLE			  hglobal_memory;
	void			 *memory;
	unsigned int	  info_size = 0;
	char			  buffer[100] = { 0 };
	string fullPath;

	GetModuleFileName(hmodule, fullPath.data, sizeof(fullPath));//注意与GetCurrentDirectoryA区别
	versionSize = GetFileVersionInfoSize(fullPath.data, &versionHandle);

	if (versionSize) {
		hglobal_memory = GlobalAlloc(GMEM_MOVEABLE, versionSize);
		memory = GlobalLock(hglobal_memory);

		GetFileVersionInfo(fullPath.data, versionHandle, versionSize, memory);
		VerQueryValue(memory, (LPTSTR)_T("\\"), (void**)&file_info, &info_size);

		Version.wFuction = HIWORD(file_info->dwFileVersionMS);
		Version.wModel   = LOWORD(file_info->dwFileVersionMS);
		Version.wVersion = HIWORD(file_info->dwFileVersionLS);
		Version.wReserve = LOWORD(file_info->dwFileVersionLS);

		GlobalUnlock(hglobal_memory);
		GlobalFree(hglobal_memory);
	}

	wsprintf(buffer, "%d.%d.%d.%d", Version.wFuction, Version.wModel, Version.wVersion, Version.wReserve);
	memcpy(ver, buffer, strlen(buffer));
}

void UpdateMdlgTitle(HWND hdlg)
{
	char str[100] = { 0 };
	sprintf(str, "Saker AA Software [%s]", ModelName);
	SetWindowText(hdlg, str);
}
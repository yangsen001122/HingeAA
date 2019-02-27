#ifndef _WINDOWSAPI_
#define _WINDOWSAPI_
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_DEPRECATE
#include<Windows.h>
#include<string.h>
#include<stdio.h>
#include<iostream>
#include<tchar.h>
#include<windowsx.h>
#include <math.h>
#include <direct.h>
#include <assert.h>
#include <CommCtrl.h>
#include <io.h>

#define DLGTYPE_CHECK_BOOL			0
#define DLGTYPE_INPUT_INT				1
#define DLGTYPE_INPUT_FLOAT			2
#define DLGTYPE_INPUT_STRING			3
#define DLGTYPE_INPUT_HEX				4
#define DLGTYPE_COMBO_INT				5
#define DLGTYPE_COMBO_INPUT_INT	6
#define DLGTYPE_INPUT_HEX4				7
#define DLGTYPE_RADIO_BOOL			8
#define DLGTYPE_INPUT_DOUBLE		9


#define MENU_BMP(hwnd, id, bmp_id)					SetMenuItemBitmaps(GetMenu(hwnd), (id), MF_BYCOMMAND, LoadBitmap((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(bmp_id)), NULL)
#define HANDLE_DLGMSG(hWnd, Msg, Fn)	case (Msg): return (SetDlgMsgResult(hWnd, Msg,	HANDLE_##Msg((hWnd), (wParam), (lParam), (Fn))))



typedef struct _INIEdit
{
	int idc;
	int type;
	void *var;
	char name[50];

}INIEdit;

typedef struct _VisionData
{
	WORD wFuction;
	WORD wModel;
	WORD wVersion;
	WORD wReserve;
} VisionData;




extern void LoadConfigBuf(const char *path, const char *section, HWND hdlg, INIEdit *edit, int item_count);
extern void SaveConfigBuf(const char *path, const char *section, HWND hdlg, INIEdit *edit, int item_count);
extern void SetIcon(HWND hwnd, int large_icon_id, int small_icon_id);
extern HMENU CreateMenu(HWND hwnd, int id);
extern HWND CreateStatusbar(HWND hwnd, const int *sub_w, int cnt, unsigned int id);//底部信息条
extern void GetVersion(HMODULE hmodule, BOOL show_buildnum, char *ver);
extern void UpdateMdlgTitle(HWND hdlg);


#endif // !_WINDOWSAPI_

#pragma once

#ifndef _CLASS_H_
#define _CLASS_H_
#pragma once
#include<Windows.h>
#include<iostream>
#include<string.h>
#include"define.h"
#include"interface.h"
#include"windowsApi.h"

using namespace std;

class Status 
{
public:
	Status();
	void SetMotionResult(int i, bool result);
	void SetAppStatus(int status);
	void SetTestResult(int i, bool result);
	bool GetMotionResult(int result);
	int    GetAppStatus(void);
	bool GetTestResult(int result);

private:
	int	resultNum;
	bool motionResult[20];//contact motion; motor motion; manual motion.
	int    appStatus;
	bool testResult[20];//diff timer
};

class Path 
{
public:
	Path();
	void initPath(void);
	void GetCurrentDir(void);
	string GetFullPath(void);
	string GetBasePath(void);
	string GetImgSourcePath(void);
	string GetTestConfigPath(void);
private:
	string fullPath;
	string currentDir;
	string basePath;
	string imgSourcePath;
	string testConfigPath;
	string path;

};

class ScreenSize 
{
public:
	ScreenSize();
	int GetScreenX();
	int GetScreenY();
private:
	int cx;
	int cy;
};

class Buffer 
{
public:
	Buffer();

private:
	BYTE imgBuf[MAX_IMG_SIZE * 3];
	BYTE bmpBuf[MAX_IMG_SIZE * 3];
	BYTE yBuf[MAX_IMG_SIZE];
	string configBuf;
};

class Wnd
{
public:
	BOOL create(HWND hwnd, LPCREATESTRUCT lpcs);
	void size(HWND hwnd, UINT state, int cx, int cy);
	void hscroll(HWND hwnd, HWND hctrl, UINT code, int pos);
	void vscroll(HWND hwnd, HWND hctrl, UINT code, int pos);
	void command(HWND hwnd, int id, HWND hctrl, unsigned int code_notify);
	void paint(HWND hwnd);
	void timer(HWND hwnd, unsigned int id);
	void close(HWND hwnd);

private:
	SCROLLINFO si;
	int pos_x;
	int pos_y;
	HANDLE unique_mutex;
};

class Display 
{
public:
	Display();
	~Display();
	virtual void DrawOnWindow(HDC memdc, LPVOID temp) { return; }
	int DisplayImg(HWND hwnd, const BYTE *bmp_source, int img_w, int img_h, int img_ch = 3, int start_x = 0, int start_y = 0, int is_full_sized = FALSE, int stretch_mode = HALFTONE, LPVOID temp = NULL);

protected:
	BOOL	mBuilt;
	HBITMAP hbitmap;
	BYTE *  biBuf;
};

class Dlg
{
public:
	virtual BOOL init(HWND hdlg, HWND hfocus, LPARAM linit);
	virtual void command(HWND hdlg, int id, HWND hctrl, UINT code_notify);
	virtual void paint(HWND hdlg);
	virtual BOOL notify(HWND hdlg, int idctrl, LPNMHDR pnmh);
	virtual void hscroll(HWND hdlg, HWND hctrl, UINT code, int pos);
	virtual void timer(HWND hdlg, unsigned int id);
	virtual void mouseMove(HWND hdlg, int x, int y, unsigned int key_flags);
	virtual void drawItem(HWND hdlg, const DRAWITEMSTRUCT *pdis);
	virtual void size(HWND hdlg, unsigned int state, int width, int height);
	virtual void close(HWND hdlg);

	virtual LRESULT ctlcolorDlg(HWND hdlg, HDC hdc, HWND hcolor, int mark = CTLCOLOR_DLG);
	virtual LRESULT ctlcolorStatic(HWND hdlg, HDC hdc, HWND hcolor, int mark = CTLCOLOR_STATIC);
	virtual LRESULT ctlcolorEdit(HWND hdlg, HDC hdc, HWND hcolor, int mark = CTLCOLOR_EDIT);
	virtual LRESULT ctlcolorListbox(HWND hdlg, HDC hdc, HWND hcolor, int mark = CTLCOLOR_LISTBOX);
};

//main dialog
class MainDlg :public Dlg
{
public:
	MainDlg();
	virtual BOOL	init(HWND hdlg, HWND hfocus, LPARAM linit);
	virtual void	command(HWND hdlg, int id, HWND hctrl, unsigned int code_notify);
	virtual LRESULT ctlcolorStatic(HWND hdlg, HDC hdc, HWND hcolor, int mark = CTLCOLOR_STATIC);
	virtual LRESULT ctlcolorDlg(HWND hdlg, HDC hdc, HWND hcolor, int mark = CTLCOLOR_DLG);
	virtual void	drawItem(HWND hdlg, const DRAWITEMSTRUCT *pdis);
	virtual void	size(HWND hdlg, unsigned int state, int width, int height);
	virtual void	close(HWND hdlg);
	virtual LRESULT ctlcolorListbox(HWND hdlg, HDC hdc, HWND hcolor, int mark/* =CTLCOLOR_EDIT */);

private:
	HBRUSH static_brush;
	HMENU menu_handle;
	HBRUSH dlg_brush, old_dlg_brush;
	DLGINFO dlgInfo;
	//	BOOL open_single_img_file(HWND hdlg);
};

class LogDlg :public Dlg
{
public:
	virtual BOOL init(HWND hdlg, HWND hfocus, LPARAM linit);
	virtual void command(HWND hdlg, int id, HWND hctrl, unsigned int code_notify);
	virtual void size(HWND hwnd, unsigned int state, int width, int height);
	virtual void close(HWND hdlg);
	virtual LRESULT ctlcolor_listbox(HWND hdlg, HDC hdc, HWND hcolor, int mark/* =CTLCOLOR_EDIT */);

private:
	HBRUSH mybrush;
};


#endif
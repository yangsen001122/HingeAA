#include"class.h"

bool Status::GetMotionResult(int i)
{
	return motionResult[i];
}

Status::Status()
{
	resultNum = 5;
	for (resultNum = 0; resultNum < 5; resultNum++) {
		motionResult[resultNum] = 0;
		testResult[resultNum] = 0;
	}	
	appStatus = 0;
}

void Status::SetMotionResult(int i, bool result)
{
	if(i<resultNum)
		motionResult[i] = result;
	
}

void Status::SetAppStatus(int status)
{
	appStatus = status;
}

void Status::SetTestResult(int i, bool result)
{
	if (i < resultNum)
		testResult[i] = result;
}

int Status::GetAppStatus(void)
{
	return appStatus;
}

bool Status::GetTestResult(int i)
{
	return testResult[i];
}

Path::Path()
{
	path					= "%s\\recipe\\";
	currentDir			= "0";
	basePath			= "0";
	imgSourcePath = "0";
	testConfigPath	= "0";
}

void Path::initPath(void)
{
	currentDir = "0";
	basePath = "0";
	imgSourcePath = "0";
	testConfigPath = "0";
}

void Path::GetCurrentDir(void)
{
	GetCurrentDirectoryA(MAX_PATH, currentDir.data);
}

string Path::GetFullPath(void)
{
	GetModuleFileName(NULL, fullPath.data, sizeof(fullPath));
	return fullPath;
}

string Path::GetBasePath(void)
{
	if(currentDir != "0")
		basePath = currentDir + path + "base.ini";
	return basePath;
}

string Path::GetImgSourcePath(void)
{
	if(currentDir != "0")
		imgSourcePath = currentDir + path + "imgSource.ini";
	return imgSourcePath;
}

string Path::GetTestConfigPath(void)
{
	if (currentDir != "0")
		testConfigPath = currentDir + path + "testConfig.ini";
	return testConfigPath;
}

ScreenSize::ScreenSize()
{
	cx = GetSystemMetrics(SM_CXSCREEN);
	cy = GetSystemMetrics(SM_CYSCREEN);
}

int ScreenSize::GetScreenX()
{
	return cx;
}

int ScreenSize::GetScreenY()
{
	return cy;
}

Buffer::Buffer()
{
	BYTE imgBuf[MAX_IMG_SIZE * 3] = { 0 };
	BYTE bmpBuf[MAX_IMG_SIZE * 3] = { 0 };
	BYTE yBuf[MAX_IMG_SIZE] = { 0 };
	string configBuf="0";
}

BOOL Wnd::create(HWND hwnd, LPCREATESTRUCT lpcs)
{
		// make sure no duplicated program running at same time.
	unique_mutex = CreateMutex(NULL, FALSE, "hingeAA");
	DWORD err_code = GetLastError();
	if (err_code == ERROR_ALREADY_EXISTS) {
		Sleep(2000);
		CloseHandle(unique_mutex);
		unique_mutex = CreateMutex(NULL, FALSE, "hingeAA");
		err_code = GetLastError();
		if (err_code == ERROR_ALREADY_EXISTS) {
			MessageBox(hwnd, "hingeAA is running!", "Warning", 0);
			CloseHandle(unique_mutex);
			PostQuitMessage(0);
		}
	}
	return TRUE;
}

void Wnd::size(HWND hwnd, UINT state, int cx, int cy)
{
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_RANGE;
	si.nMin  = 0;
	si.nMax = 0;
	SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_RANGE;
	si.nMin = 0;
	si.nMax = 0;
	SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
}

void Wnd::hscroll(HWND hwnd, HWND hctrl, UINT code, int pos)
{

}

void Wnd::vscroll(HWND hwnd, HWND hctrl, UINT code, int pos)
{
	si.cbSize = sizeof(si);
	si.fMask = SIF_ALL;
	GetScrollInfo(hwnd, SB_VERT, &si);

	switch (code)
	{
	case SB_TOP:		si.nPos = si.nMin;		break;
	case SB_BOTTOM:		si.nPos = si.nMax;		break;
	case SB_LINEUP:		si.nPos -= 1;			break;
	case SB_LINEDOWN:	si.nPos += 1;			break;
	case SB_PAGEUP:		si.nPos -= si.nPage;	break;
	case SB_PAGEDOWN:	si.nPos += si.nPage;	break;
	case SB_THUMBTRACK:	si.nPos = si.nTrackPos;	break;
	default: break;
	}
	si.fMask = SIF_POS;
	SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
	GetScrollInfo(hwnd, SB_VERT, &si);

}

void Wnd::command(HWND hwnd, int id, HWND hctrl, unsigned int code_notify)
{
}

void Wnd::paint(HWND hwnd)
{

}

void Wnd::timer(HWND hwnd, unsigned int id)
{
}

void Wnd::close(HWND hwnd)
{
	PostQuitMessage(0);
}

Display::Display()
{
	mBuilt = FALSE;
	hbitmap = NULL;
	biBuf = new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];
}

Display::~Display()
{
	delete[] biBuf;
}

int Display::DisplayImg(HWND hwnd, const BYTE * bmp_source, int img_w, int img_h, int img_ch, int start_x, int start_y, int is_full_sized, int stretch_mode, LPVOID temp)
{

	if (bmp_source == NULL || img_w == 0 || img_h == 0) {
		char err_str[MAX_PATH] = { 0 };
		sprintf(err_str, "Invalid Image! bmp_source:%d, img_w:%d, img_h:%d", bmp_source, img_w, img_h);
		MessageBox(NULL, err_str, "Error", 0);
		return FALSE;
	}
	return TRUE;
}

BOOL Dlg::init(HWND hdlg, HWND hfocus, LPARAM linit)
{
	return TRUE;
}

void Dlg::command(HWND hdlg, int id, HWND hctrl, UINT code_notify)
{
}

void Dlg::paint(HWND hdlg)
{
}

BOOL Dlg::notify(HWND hdlg, int idctrl, LPNMHDR pnmh)
{
	return 0;
}

void Dlg::hscroll(HWND hdlg, HWND hctrl, UINT code, int pos)
{
}

void Dlg::timer(HWND hdlg, unsigned int id)
{
}

void Dlg::mouseMove(HWND hdlg, int x, int y, unsigned int key_flags)
{
}

void Dlg::drawItem(HWND hdlg, const DRAWITEMSTRUCT * pdis)
{
}

void Dlg::size(HWND hdlg, unsigned int state, int width, int height)
{
}

void Dlg::close(HWND hdlg)
{
}

LRESULT Dlg::ctlcolorDlg(HWND hdlg, HDC hdc, HWND hcolor, int mark)
{
	return LRESULT();
}

LRESULT Dlg::ctlcolorStatic(HWND hdlg, HDC hdc, HWND hcolor, int mark)
{
	return LRESULT();
}

LRESULT Dlg::ctlcolorEdit(HWND hdlg, HDC hdc, HWND hcolor, int mark)
{
	return LRESULT();
}

LRESULT Dlg::ctlcolorListbox(HWND hdlg, HDC hdc, HWND hcolor, int mark)
{
	return LRESULT();
}




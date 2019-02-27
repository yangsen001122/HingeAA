#define _CRT_SECURE_NO_WARNINGS
#include "interface.h"
#include "class.h"
#include"windowsApi.h"

#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#define MAX_LOADSTRING 100
// 主窗口类名
LPCSTR  m_WndClass;            
//全局变量
Path					m_path;
ScreenSize		m_Screen;
HINSTANCE		m_instance;
HANDLE			m_uniqueMutex;
HMENU			m_menu;

ImgCapDev				*cap_dev;
//ImgFile						img_file;
//CVBS_TSW_306E		img_hw_cvbs_tsw_306e;
//CTS							cts;
//Hinge						hinge;

ATOM               MyRegisterClass(HINSTANCE hInstance);//注册窗口类。
BOOL                InitInstance(HINSTANCE, int);//保存实例句柄并创建主窗口

char ModelName[100];
double varDouble[RAM_DOUBLE_NUM] = { 0 };
int varInt[RAM_INT_NUM] = { 0 };
HWND hwnd[100] = { NULL };

INIEdit mDlgConfig[] = {


	{NULL,  NULL, NULL, NULL},
};


int WINAPI WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in LPSTR lpCmdLine, __in int nShowCmd)
{
	MyRegisterClass(hInstance);//注册窗口类
	   // 执行应用程序初始化:
	if (!InitInstance(hInstance, nShowCmd))
	{
		return FALSE;
	}

	m_path.GetCurrentDir();
	LoadConfigBuf(m_path.GetBasePath, "mDlg", HWND_MAIN, mDlgConfig, sizeof(mDlgConfig)/sizeof(mDlgConfig[0]));

	MSG msg;
	HWND_MAIN = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, (DLGPROC)MainDlgProcess);
	RECT rt_mdlg;
	GetWindowRect(HWND_MAIN, &rt_mdlg);
	MoveWindow(HWND_MAIN, 0, 0, rt_mdlg.right-rt_mdlg.left, rt_mdlg.bottom-rt_mdlg.top, FALSE);
	while(GetMessage(&msg, NULL, 0, 0)){
		if(!IsDialogMessage(HWND_APP, &msg)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return	msg.wParam;
}

//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wndClass;
	m_WndClass = "hingeAA";

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_LOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndClass.lpszClassName = m_WndClass;
	wndClass.lpszMenuName = NULL;
	wndClass.hIconSm = LoadIcon(wndClass.hInstance, (LPCTSTR)IDI_LOGO);

	if (!RegisterClassEx(&wndClass)) {
		MessageBox(NULL, "App Error!", m_WndClass, 0);
		return 0;
	}
	else
		return RegisterClassEx(&wndClass);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	m_instance = hInstance; // 将实例句柄存储在全局变量中
	HWND_APP = CreateWindowEx(WS_EX_ACCEPTFILES,
		m_WndClass, "ImageScenery",
		WS_THICKFRAME,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!HWND_APP)
	{
		return FALSE;
	}

	ShowWindow(HWND_APP, nCmdShow);
	UpdateWindow(HWND_APP);

	return TRUE;
}

Wnd wnd;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, wnd.create);
		HANDLE_MSG(hWnd, WM_SIZE, wnd.size);
		HANDLE_MSG(hWnd, WM_HSCROLL, wnd.hscroll);
		HANDLE_MSG(hWnd, WM_VSCROLL, wnd.vscroll);
		HANDLE_MSG(hWnd, WM_PAINT, wnd.paint);
		HANDLE_MSG(hWnd, WM_CLOSE, wnd.close);

	case WM_DROPFILES:
	{

		
	}
	break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}





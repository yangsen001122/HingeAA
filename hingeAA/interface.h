#ifndef _INTERFACE_H_
#define _INTERFACE_H_
#include"windowsApi.h"
#include "resource.h"
#include "img_cap_device.h"
#include "class.h"
#include "define.h"


extern Path				m_path;
extern ScreenSize		m_Screen;
extern HINSTANCE	m_instance;
extern HANDLE			m_uniqueMutex;
extern HMENU			m_menu;

extern ImgCapDev			*cap_dev;
extern ImgFile					imgFile;
extern CVBS_TSW_306E		imgTSW306E;
extern CTS						cts;
extern Hinge						hinge;

extern char ModelName[100];
extern double varDouble[RAM_DOUBLE_NUM];
extern int varInt[RAM_INT_NUM];
extern HWND hwnd[100];

constexpr auto WINDOW_INITIAL_WIDTH = 1024;
constexpr auto WINDOW_INITIAL_HEIGHT = 768;
constexpr auto MDLG_DEFAULT_HEIGHT = 140;
constexpr auto MDLG_EXTEND_HEIGHT = 210;

#define APP_ERR						-1
#define APP_READY					0
#define APP_START					1
#define APP_STOP					2
#define APP_NEXT					3
#define APP_NOTHOME			4
#define APP_INIT						10
#define APP_TESTING				11
#define APP_RESET					12
#define APP_FAIL						99
#define APP_PASS					100

#define USE_FINE_CROSS_SEARCH

#define PACK_SIZE		256


//extern DWORD CALLBACK ShowTimeThread(LPVOID temp);
//extern DWORD CALLBACK MouseOperationThread(LPVOID temp);
//extern DWORD CALLBACK TestThread(LPVOID temp);
//extern DWORD CALLBACK ErrorMonitorThread(LPVOID temp);
//
//extern DWORD CALLBACK GetImageThread(LPVOID temp);
//extern DWORD CALLBACK DisplayImageThread(LPVOID temp);
//extern DWORD CALLBACK StdChartTestThread(LPVOID temp);
//extern DWORD CALLBACK RegMarkChartTestThread(LPVOID temp);
//
//extern DWORD CALLBACK ExternInHandshakeThread(LPVOID temp);
//extern DWORD CALLBACK ImageInfoThread(LPVOID temp);
//
//extern DWORD CALLBACK VisionLinkThread(LPVOID temp);
//extern DWORD CALLBACK PlcLinkThread(LPVOID temp);
//extern DWORD CALLBACK VisionRecvThread(LPVOID temp);
//extern DWORD CALLBACK VisionCmdThread(LPVOID temp);
//extern DWORD CALLBACK PlcOnlineCheckThread(LPVOID temp);
//extern DWORD CALLBACK PlcOnlineCountingThread(LPVOID temp);
//extern DWORD CALLBACK PlcReadThread(LPVOID temp);
////extern DWORD CALLBACK web_cam_thread(LPVOID temp);
//extern DWORD CALLBACK CheckImgExistThread(LPVOID temp);
//extern DWORD CALLBACK IoStatusThread(LPVOID temp);
//extern DWORD CALLBACK PowerSupplyLinkThread(LPVOID temp);
//
extern BOOL CALLBACK MainDlgProcess(HWND hdlg, unsigned int message, WPARAM wParam, LPARAM lParam);
//extern BOOL CALLBACK DlgGuideLineProcess(HWND hdlg, unsigned int message, WPARAM wParam, LPARAM lParam);
//extern BOOL CALLBACK DlgHistogramProcess(HWND hdlg, unsigned int message, WPARAM wParam, LPARAM lParam);
//extern BOOL CALLBACK DlgMeasureProcess(HWND hdlg, unsigned int message, WPARAM wParam, LPARAM lParam);
//extern BOOL CALLBACK DlgManualButton(HWND hdlg, unsigned int message, WPARAM wParam, LPARAM lParam);
//extern BOOL CALLBACK DlgImgInfo(HWND hdlg, unsigned int message, WPARAM wParam, LPARAM lParam);
extern BOOL CALLBACK DlgLog(HWND hdlg, unsigned int message, WPARAM wParam, LPARAM lParam);
//extern BOOL CALLBACK DlgRecipe(HWND hdlg, unsigned int message, WPARAM wParam, LPARAM lParam);
//extern BOOL CALLBACK DlgHwConfig(HWND hdlg, unsigned int message, WPARAM wParam, LPARAM lParam);
//extern BOOL CALLBACK DlgTestConfig(HWND hdlg, unsigned int message, WPARAM wParam, LPARAM lParam);
//extern BOOL CALLBACK DlgStdChartSettingProcess(HWND hdlg, unsigned int message, WPARAM wParam, LPARAM lParam);
//extern BOOL CALLBACK DlgRegMarkChartSettingProcess(HWND hdlg, unsigned int message, WPARAM wParam, LPARAM lParam);
//extern BOOL CALLBACK DlgRegMarkChartSfrCurveProcess(HWND hdlg, unsigned int message, WPARAM wParam, LPARAM lParam);
//extern BOOL CALLBACK DlgMotionAAProcess(HWND hdlg, unsigned int message, WPARAM wParam, LPARAM lParam);
//extern BOOL CALLBACK DlgRegMarkFocusScanProcess(HWND hdlg, unsigned int message, WPARAM wParam, LPARAM lParam);
//extern BOOL CALLBACK DlgIoStatusProcess(HWND hdlg, unsigned int message, WPARAM wParam, LPARAM lParam);
extern LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
typedef struct _tag_TCPIP_V
{
	int is_linked;
	int port;
	char ip[20];
	char pack[PACK_SIZE];
	int  is_pack_empty;
}TCPIP_V;

typedef struct DEVICE_INFO
{
	//	CChannelWnd	*m_pWnd;
	int dwHeight;
	int dwWidth;
	float dwFrameRate;
	int dwColorspace;
	int dwVidStandard;
	unsigned  dwOpenDevState;
	BOOL dwConnectState;
	BOOL  dwPrviewState;
	HANDLE dwChannelHandle;
	HWND dwPrvHandle;
	RECT dwPrvRect;
	PRECT dwSnapPicRect;

	DWORD			dwDispWidth;                     //预览显示宽度
	DWORD			dwDispHeight;                    //预览显示高度
	DWORD			dwDispPosX;                      //预览显示水平起始位置
	DWORD			dwDispPosY; 

}Device_Info;


typedef struct _DlgInfo
{
	int dlgX;
	int dlgY;
	int dlgW;
	int dlgH;
	RECT rt_win;
	int dlgShow;
	int showLog;
}DLGINFO;



/************************************************************************/
/* test on/off: normal test process on and off status control
   test stop: sometimes we need sudden stop or interrupt test process.	
*/
/************************************************************************/


//////////////////////////////////////////////////////////////////////////
//image.cpp

//////////////////////////////////////////////////////////////////////////
//standard sfr chart

//reg mark chart



#endif
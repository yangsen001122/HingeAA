#define _CRT_SECURE_NO_WARNINGS
#include "interface.h"
#include "class.h"
#include "windowsApi.h"
/*各窗口功能线程及主界面显示*/
extern HINSTANCE m_instance;


MainDlg mdlg;
BOOL CALLBACK MainDlgProcess(HWND hdlg, unsigned int message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_DLGMSG(hdlg, WM_INITDIALOG,			mdlg.init);
		HANDLE_DLGMSG(hdlg, WM_COMMAND,		    mdlg.command);
		HANDLE_DLGMSG(hdlg, WM_CTLCOLORSTATIC,  mdlg.ctlcolorStatic);
		HANDLE_DLGMSG(hdlg, WM_CTLCOLORDLG,		 mdlg.ctlcolorDlg);
		HANDLE_DLGMSG(hdlg, WM_CTLCOLORLISTBOX, mdlg.ctlcolorListbox);
		HANDLE_DLGMSG(hdlg, WM_DRAWITEM,	    mdlg.drawItem);
		//		HANDLE_DLGMSG(hdlg, WM_SIZE,		    mdlg.size);
		HANDLE_DLGMSG(hdlg, WM_CLOSE,		    mdlg.close);

	case WM_LBUTTONDBLCLK:
		MOUSE_LDBCLICK = TRUE;
		break;

	case WM_LBUTTONDOWN:
		{
			MEASURE_DRAW_RECT_DONE = FALSE;
			RECT rt;
			GetClientRect(GetDlgItem(hdlg, IDC_DISPLAY), &rt);
			IMG_RATIO_X = (float)DISPLAY_IMG_WIDTH/(rt.right-rt.left);
			IMG_RATIO_Y = (float)DISPLAY_IMG_HEIGHT/(rt.bottom-rt.top);
			MOUSE_X = LOWORD(lParam);
			MOUSE_Y = HIWORD(lParam);
			MOUSE_LDOWN = TRUE;
		}

		break;

	case WM_MOUSEMOVE:
		if ((wParam&MK_LBUTTON)){
			MOUSE_LDOWN_MOVE = TRUE;
			MOUSE_X = LOWORD(lParam);
			MOUSE_Y = HIWORD(lParam)-MYTOOLBAR_HEIGHT;
		}


		if ((wParam&MK_LBUTTON) && ENABLE_IMG_ZOOM_IN && DRAW_ZOOM_IN_AREA_DONE == FALSE){
			MOUSE_END_X = LOWORD(lParam);
			MOUSE_END_Y = HIWORD(lParam)-MYTOOLBAR_HEIGHT;
			DRAW_MOVING_MOUSE = TRUE;
		}

		if ((wParam&MK_LBUTTON) && ENABLE_MEASURE == TRUE){
			MEASURE_END_X = LOWORD(lParam);
			MEASURE_END_Y = HIWORD(lParam)-MYTOOLBAR_HEIGHT;
		}
		break;

	case WM_LBUTTONUP:
		MOUSE_X = LOWORD(lParam);
		MOUSE_Y = HIWORD(lParam)-MYTOOLBAR_HEIGHT;
		MOUSE_LUP = TRUE;

		if (ENABLE_MEASURE == TRUE){
			MEASURE_END_X = LOWORD(lParam);
			MEASURE_END_Y = HIWORD(lParam)-MYTOOLBAR_HEIGHT;

			if (MEASURE_END_X>MEASURE_START_X && MEASURE_END_Y>MEASURE_START_Y){
				MEASURE_DRAW_RECT_DONE = TRUE;
			}
		}
		break;
	}

	return FALSE;
}

MainDlg::MainDlg()
{
	dlgInfo.dlgH = 0;
	dlgInfo.dlgW = 0;
	dlgInfo.dlgX = 0;
	dlgInfo.dlgY = 0;
	dlgInfo.dlgShow = 0;
	static_brush = NULL;
}

LRESULT MainDlg::ctlcolorDlg(HWND hdlg, HDC hdc, HWND hcolor, int mark /* =CTLCOLOR_DLG */)
{
	if (dlg_brush != NULL){
		DeleteObject(dlg_brush);
	}

	dlg_brush = CreateSolidBrush(RGB(0xbd, 0xc7, 0xd7));//主窗口背景色
	old_dlg_brush = (HBRUSH)SelectObject(hdc, (HBRUSH)dlg_brush);

	return (LRESULT)dlg_brush;
}

LRESULT MainDlg::ctlcolorListbox(HWND hdlg, HDC hdc, HWND hcolor, int mark)//主界面log窗口背景色
{
	DeleteObject(dlg_brush);
	SetBkMode(hdc, TRANSPARENT);
	dlg_brush = CreateSolidBrush(RGB(156,170,193));
	HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, dlg_brush);

	HFONT font     = CreateFont(15, 0, 0, 0, FW_BLACK, 0,0,0, ANSI_CHARSET, 0,0,0,0, "黑体");
	HFONT old_font = (HFONT)SelectObject(hdc, font);
	SendDlgItemMessage(hdlg, IDC_LOG, LB_SETITEMHEIGHT, 0, 17);
	SetTextColor(hdc, COLOR_WHITE);

	DeleteObject(font);

	return (LRESULT)dlg_brush;
}


BOOL MainDlg::init(HWND hdlg, HWND hfocus, LPARAM linit)
{
	MENUINFO mi;//Menu

	SetIcon(hdlg, IDI_LOGO, IDI_LOGO);
	m_menu = CreateMenu(hdlg, IDR_MENU);
	mi.fMask   = MIM_BACKGROUND;
	mi.hbrBack = CreateSolidBrush(RGB(255, 0, 0));
	SetMenuInfo(m_menu, &mi);
	DrawMenuBar(hdlg);

	MENU_BMP(hdlg, ID_MULTI_SETTING,				IDB_T_MSFR		);
	MENU_BMP(hdlg, ID_TOOLS_SINGLESFR,			IDB_T_SFR		);
	MENU_BMP(hdlg, ID_FOCUS_SETTING,				IDB_T_ST		);
	MENU_BMP(hdlg, ID_FILE_LOG,						IDB_T_LOG		);
	MENU_BMP(hdlg, ID_MULTI_SFR_CURVE1,		IDB_T_CURVE	);
	MENU_BMP(hdlg, ID_MULTI_SFR_CURVE2,		IDB_T_CURVE	);
	MENU_BMP(hdlg, ID_FOCUS_FOCUSCURVE,		IDB_T_CURVE	);
	MENU_BMP(hdlg, ID_TEST_CONFIG,					IDB_T_CONFIG	);
	MENU_BMP(hdlg, ID_SETTING_RECIPE,				IDB_T_RECIPE	);
	MENU_BMP(hdlg, ID_FILE_LOGIN,						IDB_T_LOGIN	);
	MENU_BMP(hdlg, ID_EDIT_IMAGEINFO,			IDB_T_IMG_INFO	);
	MENU_BMP(hdlg, ID_TOOL_HISTOGRAM,			IDB_T_HISTOGRAM);
	MENU_BMP(hdlg, ID_EDIT_GUIDELINE,				IDB_T_GUIDE	);
	MENU_BMP(hdlg, ID_TOOL_MEASURE,				IDB_T_MEASURE	);
	MENU_BMP(hdlg, ID_FILE_SAVEINFOIMAGE,    IDB_T_SAVE		);

	//status bar
	int sub_width[4] = {90, 150, 270, 390};
	HWND_STATUS = CreateStatusbar(hdlg, sub_width, sizeof(sub_width)/sizeof(int), 0);
	char version[20] = {0};
	GetVersion(NULL, TRUE, version);

	char sVersion[100] = {0};
	sprintf(sVersion, " %s", version);

	SendMessage(HWND_STATUS, SB_SETTEXT, 0, (LPARAM)" @2019");
	SendMessage(HWND_STATUS, SB_SETTEXT, 1, (LPARAM)sVersion);
	SendMessage(HWND_STATUS, SB_SETTEXT, 2, (LPARAM)"");
	SendMessage(HWND_STATUS, SB_SETTEXT, 3, (LPARAM)"");


	//main dlg layout
	RECT rt, rt_m;
	GetClientRect(hdlg, &rt_m);
	GetClientRect(HWND_STATUS, &rt);
	//MoveWindow(GetDlgItem(hdlg, IDC_STATUS), 1, 1, 150, MYTOOLBAR_HEIGHT-2, FALSE);

	//create sub dlg
	HWND_LOG		 = CreateDialog(m_instance, MAKEINTRESOURCE(IDD_LOG),		    hdlg, (DLGPROC)DlgLog);
	//MoveWindow(HWND_LOG, s_aa::dinfo.rt_log.left,	
	//					 s_aa::dinfo.rt_log.top,	
	//					 s_aa::dinfo.rt_log.right-s_aa::dinfo.rt_log.left,	
	//					 s_aa::dinfo.rt_log.bottom-s_aa::dinfo.rt_log.top, FALSE);
	CheckMenuItem(m_menu, ID_FILE_LOG,	  dlgInfo.dlgShow?MF_CHECKED:MF_UNCHECKED);
	ShowWindow(HWND_LOG, dlgInfo.dlgShow?SW_NORMAL:SW_HIDE);
	//log("===Start Saker AA Software===");


	//COMBO_SETCURSEL(hdlg, IDC_SELECT_IMG_DEVICE, SELECT_IMG_SOURCE);
	//if (SELECT_IMG_SOURCE == IMG_DEV_FILE){
	//	cap_dev = (ImgCapDev *)&imgFile;
	//	SendMessage(HWND_STATUS, SB_SETTEXT, 2, (LPARAM)"Image Files");
	//}
	//else if (SELECT_IMG_SOURCE == IMG_HINGE_CAM){
	//	cap_dev = (ImgCapDev *)&hinge;
	//	SendMessage(HWND_STATUS, SB_SETTEXT, 2, (LPARAM)"Hinge_Cam");
	//}

	
//编辑菜单
//	HWND_RECIPE						= CreateDialog(m_instance, MAKEINTRESOURCE(IDD_RECIPE),						hdlg, (DLGPROC)DlgRecipe);
//	HWND_IMG_INFO				= CreateDialog(m_instance, MAKEINTRESOURCE(IDD_IMAGE_INFO),			hdlg, (DLGPROC)DlgImgInfo);
//	HWND_GUIDELINE				= CreateDialog(m_instance, MAKEINTRESOURCE(IDD_GUIDE_LINE),				hdlg, (DLGPROC)DlgGuideLineProcess);
////AA设定菜单
//	HWND_TEST_CONFIG			= CreateDialog(m_instance, MAKEINTRESOURCE(IDD_TEST_CONFIG),			hdlg, (DLGPROC)DlgTestConfig);
//	HWND_REG_MARK_CHART	= CreateDialog(m_instance,MAKEINTRESOURCE(IDD_REG_MARK_CHART),	hdlg, (DLGPROC)DlgRegMarkChartSettingProcess);
//	HWND_AA_MOTION				= CreateDialog(m_instance, MAKEINTRESOURCE(IDD_AA_CONFIG),				hdlg, (DLGPROC)DlgMotionAAProcess);
//	HWND_IO_CONFIG				= CreateDialog(m_instance, MAKEINTRESOURCE(IDD_IO_CONFIG),				hdlg, (DLGPROC)DlgIoStatusProcess);
////工具菜单
//	HWND_HISTOGRAM				= CreateDialog(m_instance, MAKEINTRESOURCE(IDD_HISTOGRAM),				hdlg, (DLGPROC)DlgHistogramProcess);
//	HWND_MEASURE					= CreateDialog(m_instance, MAKEINTRESOURCE(IDD_MEASURE),					hdlg, (DLGPROC)DlgMeasureProcess);
////采集菜单
//	HWND_MANUAL_MD			= CreateDialog(m_instance, MAKEINTRESOURCE(IDD_MANUAL_BUTTON),	hdlg, (DLGPROC)DlgManualButton);
//移放到各自dlg init步骤
	//CheckMenuItem(m_menu, ID_SETTING_RECIPE,		dlgInfo.dlgShow?MF_CHECKED:MF_UNCHECKED);
	//CheckMenuItem(m_menu, ID_EDIT_IMAGEINFO,		dlgInfo.dlgShow?MF_CHECKED:MF_UNCHECKED);
	//CheckMenuItem(m_menu,ID_EDIT_GUIDELINE,			dlgInfo.dlgShow?MF_CHECKED:MF_UNCHECKED);

	//CheckMenuItem(m_menu, ID_TEST_CONFIG,			s_aa::dinfo.show_tc?MF_CHECKED:MF_UNCHECKED);
	//CheckMenuItem(m_menu,ID_REGMARKCHART_CONFIGURE,s_aa::dinfo.show_reg_chart?MF_CHECKED:MF_UNCHECKED);
	//CheckMenuItem(m_menu,ID_AA_CONFIG,				s_aa::dinfo.show_aa_dlg?MF_CHECKED:MF_UNCHECKED);
	//CheckMenuItem(m_menu,ID_IO,								s_aa::dinfo.show_io_dlg?MF_CHECKED:MF_UNCHECKED);

	//CheckMenuItem(m_menu,ID_TOOL_HISTOGRAM,	s_aa::dinfo.show_histogram?MF_CHECKED:MF_UNCHECKED);
	//CheckMenuItem(m_menu,ID_TOOL_MEASURE,		s_aa::dinfo.show_measure?MF_CHECKED:MF_UNCHECKED);

	//ShowWindow(HWND_RECIPE		,								s_aa::dinfo.show_recipe?SW_NORMAL:SW_HIDE);	
	//ShowWindow(HWND_IMG_INFO	,							s_aa::dinfo.show_img_info?SW_NORMAL:SW_HIDE);	
	//ShowWindow(HWND_GUIDELINE,								s_aa::dinfo.show_guide_line?SW_NORMAL:SW_HIDE);	
	//ShowWindow(HWND_TEST_CONFIG		,					s_aa::dinfo.show_tc?SW_NORMAL:SW_HIDE);	
	//ShowWindow(HWND_REG_MARK_CHART,				s_aa::dinfo.show_reg_chart?SW_NORMAL:SW_HIDE);	
	//ShowWindow(HWND_AA_MOTION		,					s_aa::dinfo.show_aa_dlg?SW_NORMAL:SW_HIDE);
	//ShowWindow(HWND_IO_CONFIG			,					s_aa::dinfo.show_io_dlg?SW_NORMAL:SW_HIDE);	
	//ShowWindow(HWND_HISTOGRAM	,						s_aa::dinfo.show_histogram?SW_NORMAL:SW_HIDE);	
	//ShowWindow(HWND_MEASURE		,						s_aa::dinfo.show_measure?SW_NORMAL:SW_HIDE);	

	UpdateMdlgTitle(hdlg);

	//Create thread
#define PLC_LINK_ON
#define THREAD_NUM	20
	DWORD ThreadID[THREAD_NUM] = {0};
	HANDLE ThreadHandle[THREAD_NUM] = {NULL};

	//ThreadHandle[0]  = CreateThread(NULL, 0, TestThread,							(LPVOID)hdlg, 0, &ThreadID[0]);
	//ThreadHandle[1]  = CreateThread(NULL, 0, ShowTimeThread,				(LPVOID)hdlg, 0, &ThreadID[1]);
	//ThreadHandle[2]  = CreateThread(NULL, 0, MouseOperationThread,		(LPVOID)hdlg, 0, &ThreadID[2]);
	//ThreadHandle[3]  = CreateThread(NULL, 0, ErrorMonitorThread,			(LPVOID)hdlg, 0, &ThreadID[3]);
	//ThreadHandle[4]  = CreateThread(NULL, 0, GetImageThread,				(LPVOID)hdlg, 0, &ThreadID[4]);
	//ThreadHandle[5]  = CreateThread(NULL, 0, DisplayImageThread,			(LPVOID)hdlg, 0, &ThreadID[5]);
	//ThreadHandle[6]  = CreateThread(NULL, 0, StdChartTestThread,			(LPVOID)hdlg, 0, &ThreadID[6]);
	//ThreadHandle[7]  = CreateThread(NULL, 0, RegMarkChartTestThread,	(LPVOID)hdlg, 0, &ThreadID[7]);
	//ThreadHandle[8]  = CreateThread(NULL, 0, PowerSupplyLinkThread,		(LPVOID)hdlg, 0, &ThreadID[8]);
	//ThreadHandle[10] = CreateThread(NULL, 0, IoStatusThread,					(LPVOID)hdlg, 0, &ThreadID[10]);
#ifdef PLC_LINK_ON
	//ThreadHandle[11] = CreateThread(NULL, 0, PlcLinkThread,					(LPVOID)hdlg, 0, &ThreadID[11]);
	//ThreadHandle[12] = CreateThread(NULL, 0, PlcOnlineCheckThread,		(LPVOID)hdlg, 0, &ThreadID[12]);
	//ThreadHandle[13] = CreateThread(NULL, 0, PlcOnlineCountingThread,	(LPVOID)hdlg, 0, &ThreadID[13]);
	//ThreadHandle[14] = CreateThread(NULL, 0, PlcReadThread,					(LPVOID)hdlg, 0, &ThreadID[14]);
#endif

	for (int i=0; i<THREAD_NUM; i++){
		CloseHandle(ThreadHandle[i]);
	}
	log("Dlg: Main UI init OK.");

	return TRUE;
}

void MainDlg::size(HWND hdlg, unsigned int state, int width, int height)
{
	RECT rt;

}

void MainDlg::command(HWND hdlg, int id, HWND hctrl, unsigned int code_notify)
{
	int result = 0;
	char config_path[MAX_PATH] = {0};

	switch (code_notify){
	case CBN_SELCHANGE:
		{

		}
		break;
	}
	
	switch (id)
	{
	//menu

	case ID_FILE_SAVEINFOIMAGE:
	
		break;

	case ID_FILE_LOG:
		dlgInfo.showLog ^= TRUE;
		CheckMenuItem(m_menu, id, dlgInfo.showLog?MF_CHECKED:MF_UNCHECKED);
		/*ShowWindow(HWND_LOG, dlgInfo.showLog?SW_NORMAL:SW_HIDE);*/
		break;
//edit
	case ID_SETTING_RECIPE:

		break;

	case ID_EDIT_GUIDELINE:

		break;

	case ID_EDIT_IMAGEINFO:

		break;
	//test
	case ID_TEST_CONFIG:

		break;

	case ID_AA_CONFIG:

		break;

	case ID_REGMARKCHART_CONFIGURE:

		break;

	case ID_IO:		

		break;

	case ID_MANUAL_BOTTON:		

		break;

	//tool
	case ID_TOOL_HISTOGRAM:

		break;

	case ID_TOOL_MEASURE:

		break;

	//mdlg items
	case IDC_OPEN_AA://auto model

		break;
	case IDC_CLOSE_AA://manual model

		break;
	case IDC_CLEAR_ERR:

		break;

	case IDC_START:	

		break;

	case IDC_STOP:

		break;

	case IDC_SNAPSHOT:

		break;

	case IDC_SAVE:

		break;

	case IDC_DATA_RESET:
		result = MessageBox( NULL , TEXT("是否清除数据") , TEXT("提示") , MB_ICONINFORMATION|MB_YESNO);
		switch(result)/*注意！使用Unicode应用TEXT包围字串*/
		{
		case IDYES:

			break;
		}
		break;
	default:

	}
}

LRESULT MainDlg::ctlcolorStatic(HWND hdlg, HDC hdc, HWND hcolor, int mark /* = CTLCOLOR_STATIC */ )
{	
	COLORREF cr;
	char text[20] = {0};
	if (static_brush != NULL) DeleteObject(static_brush);

	static_brush = CreateSolidBrush(GetSysColor(COLOR_BTNFACE)/*BRUSH_LIGHTGRAY*/);
	HBRUSH old_brush = (HBRUSH)SelectObject(hdc, (HBRUSH)static_brush);
	HFONT hfont = CreateFont(14, 0,0,0,20,0,0,0,ANSI_CHARSET,3,2,1, VARIABLE_PITCH | FF_ROMAN, "黑体");
	HFONT old_font = (HFONT)SelectObject(hdc, hfont);

	SetBkMode(hdc, TRANSPARENT);

	switch (GetDlgCtrlID(hcolor))
	{
	case IDC_STATUS:
		DeleteObject(hfont);
		hfont = CreateFont(26, 0,0,0,20,0,0,0,ANSI_CHARSET,3,2,1, VARIABLE_PITCH | FF_ROMAN, "黑体");
		old_font = (HFONT)SelectObject(hdc, hfont);
		DeleteObject(static_brush);
		SetTextColor(hdc, COLOR_LIGHT_DARK);
		switch (APP_STATUS)
		{
		case APP_ERR:	  cr = COLOR_RED;				strcpy(text, "Error");		break;
		case APP_NOTHOME:  cr = COLOR_TOMATO;			strcpy(text, "Not home");	break;
		case APP_READY:	  cr = COLOR_MEDIUM_STATE_BLUE;	strcpy(text, "Ready");		break;
		case APP_INIT:	  cr = COLOR_MAGENTA;			strcpy(text, "Init...");	break;
		case APP_TESTING: cr = COLOR_GOLD;				strcpy(text, "Test...");	break;
		case APP_START:	  cr = COLOR_YELLOW_GREEN;		strcpy(text, "Start");		break;
		case APP_NEXT:	  cr = COLOR_MAGENTA;			strcpy(text, "Next");		break;
		case APP_STOP:	  cr = COLOR_TOMATO;			strcpy(text, "Stop");		break;
		case APP_PASS:    cr = COLOR_GREEN;				strcpy(text, "Pass");		break;
		case APP_FAIL:	  cr = COLOR_RED;				strcpy(text, "Fail");		break;
		case APP_RESET:	  cr = COLOR_PLUM;				strcpy(text, "Reset");		break;

		default:		  cr = COLOR_RED;				strcpy(text, "Unknown");	break;
		}
		static_brush = CreateSolidBrush(cr);
		SetDlgItemText(hdlg, IDC_STATUS, text);
		break;

	case IDC_STATIC_result:
	case IDC_STATIC_mtfScore:
	case IDC_STATIC_process:
	case IDC_STATIC_sn:
	case IDC_STATIC_PLC:
	case IDC_STATIC_IMG_SOURCE:
	case IDC_STATIC_c:
	case IDC_STATIC_lt:
	case IDC_STATIC_rt:
	case IDC_STATIC_lb:
	case IDC_STATIC_rb:
	case IDC_STATIC1:
	case IDC_STATIC2:
	case IDC_STATIC3:
	case IDC_STATIC4:
	case IDC_STATIC5:
	case IDC_STATIC6:
	case IDC_STATIC7:
	case IDC_STATIC8:
	case IDC_STATIC9:
	case IDC_STATIC10:
	case IDC_STATIC11:
	case IDC_STATIC12:
	case IDC_STATIC13:
	case IDC_STATIC14:
	case IDC_STATIC15:
	case IDC_STATIC16:
		SetTextColor(hdc, RGB(0x00, 0x00, 0x00));
		DeleteObject(static_brush);
		static_brush = CreateSolidBrush(RGB(189,199,215));//注释背景色
		break;

	case IDC_LINK_PLC:
		GetDlgItemText(hdlg, GetDlgCtrlID(hcolor), text, sizeof(text));
		DeleteObject(static_brush);
		if (!strcmp(text, "Connected")){
			static_brush = CreateSolidBrush(RGB(0x70, 0xad, 0x47));
		}
		else{
			static_brush = CreateSolidBrush(RGB(0xff, 0x11, 0x11));
		}
		break;
	
	case IDC_REPORT_SFR_C:

		break;
	case IDC_REPORT_SFR_RB:

		break;
	case IDC_REPORT_SFR_RT:

		break;
	case IDC_REPORT_SFR_LB:

		break;
	case IDC_REPORT_SFR_LT:

		break;
	case IDC_REPORT_CENTER_X:

		break;	
	case IDC_REPORT_CENTER_Y:

		break;	
	case IDC_REPORT_eCoorDiff:

		break;	
	case IDC_REPORT_eSfrDiff:

		break;
	case IDC_REPORT_SFR_CENTER:

		break;
	case IDC_REPORT_SFR_EDGE:

		break;
	case IDC_STEP1:
	case IDC_STEP2:
	case IDC_STEP3:
	case IDC_STEP4:
	case IDC_STEP5:
	case IDC_STEP6:

		break;
	case IDC_MANUAL_STATUS:

		break;
	case IDC_AUTO_STATUS:

		break;
	case IDC_PS_STATUS:

		break;
}


	DeleteObject(hfont);
	SelectObject(hdc, (HFONT)old_font);
	return (LRESULT)static_brush;
}

void MainDlg::drawItem(HWND hdlg, const DRAWITEMSTRUCT *pdis)
{
	int icon_id = 0;
	switch (pdis->CtlID)
	{
	case IDC_START:		icon_id = IDI_START; break;
	case IDC_STOP:		icon_id = IDI_STOP;	 break;
	case IDC_NEXT:		icon_id = IDI_NEXT;	 break;
	case IDC_SAVE:		icon_id = IDI_SAVE;	 break;
	case IDC_SNAPSHOT:	icon_id = IDI_SNAPSHOT;	 break;
	default:
		return;
		break;
	}
}

void MainDlg::close(HWND hdlg)
{
	Sleep(100);

//保存窗口坐标

	PostQuitMessage(0);
}

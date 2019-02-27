//=========================================================================================  
//	Project:		
//	Program:		
//	date:			
//===========================================================================================
#include"windowsApi.h"
#include"interface.h"
#include"class.h"

#ifndef EXTERN
#define EXTERN extern
#endif

/* define machine status flags */
#ifndef NULL
#define NULL     0
#endif

#define HWND_APP								hwnd[0]
#define HWND_MAIN							hwnd[1]
#define HWND_STATUS						hwnd[2]
#define HWND_LOG								hwnd[3]
#define HWND_TEST_CONFIG				hwnd[4]
															
#define HWND_RECIPE							hwnd[5]
#define HWND_HISTOGRAM				hwnd[6]
#define HWND_MEASURE						hwnd[7]
#define HWND_GUIDELINE					hwnd[8]
#define HWND_IMG_INFO					hwnd[9]
#define HWND_HW_CONFIG				hwnd[10]
#define HWND_MANUAL_MD				hwnd[11]
#define HWND_IO_CONFIG					hwnd[12]
															
#define HWND_STD_CHART					hwnd[13]
#define HWND_STD_CURVE					hwnd[14]
#define HWND_REG_MARK_CHART		hwnd[15]
#define HWND_REG_MARK_SFRCURVE	hwnd[16]
#define HWND_WHITE							hwnd[17]
#define HWND_AA_MOTION				hwnd[18]
#define HWND_REG_MARK_TF				hwnd[19]

#define MOUSE_START_X						varInt[0]
#define MOUSE_START_Y						varInt[1]
#define MOUSE_END_X						varInt[2]
#define MOUSE_END_Y						varInt[3]
#define MOUSE_LDOWN						varInt[4]
#define MOUSE_LDOWN_MOVE			varInt[5]
#define MOUSE_LUP								varInt[6]
#define MOUSE_LDBCLICK					varInt[7]
#define MOUSE_X									varInt[8]
#define MOUSE_Y									varInt[9]

#define DISPLAY_IMG_START_X			varInt[10]
#define DISPLAY_IMG_START_Y			varInt[11]
#define DISPLAY_IMG_WIDTH				varInt[12]
#define DISPLAY_IMG_HEIGHT				varInt[13]

#define ENABLE_IMG_ZOOM_IN			varInt[16]
#define APP_STATUS							varInt[20]
#define DRAW_ZOOM_IN_AREA_DONE	varInt[23]
#define DRAW_MOVING_MOUSE			varInt[24]

#define ENABLE_MEASURE					varInt[30]
#define MEASURE_START_X					varInt[31]
#define MEASURE_START_Y					varInt[32]
#define MEASURE_END_X						varInt[33]
#define MEASURE_END_Y						varInt[34]
#define MEASURE_DRAW_RECT_DONE varInt[35]

#define IMG_RATIO_X							varDouble[0]
#define IMG_RATIO_Y							varDouble[1]

//color define
#define COLOR_BLACK							RGB(0,     0,   0)
#define COLOR_WHITE							RGB(255, 255, 255)
#define COLOR_RED							RGB(255,   0,   0)
#define COLOR_GREEN							RGB(0,   255,   0)
#define COLOR_BLUE							RGB(0,     0, 255)
#define COLOR_DODGER_BLUE					RGB( 30, 144, 255)
#define COLOR_MEDIUM_STATE_BLUE				RGB(123, 104, 238)
#define COLOR_MAGENTA						RGB(255,   0, 255)
#define COLOR_YELLOW_GREEN					RGB(154, 205,  50)
#define COLOR_TOMATO						RGB(255,  99,  71)
#define COLOR_GHOST_WHITE					RGB(248, 248, 255)
#define COLOR_LIGHT_DARK					RGB(68,   68,  68)
#define COLOR_YELLOW						RGB(255, 255,   0)
#define COLOR_DARK_ORANGE					RGB(255, 140,   0)
#define COLOR_SADDLE_BROWN					RGB(139,  69,  19)

#define COLOR_LIME_GREEN					RGB( 50, 205,  50)
#define COLOR_DEEP_PINK						RGB(255,  20, 147)
#define COLOR_FIRE_BRICK					RGB(178,  34,  34)
#define COLOR_GOLD							RGB(255, 215,   0)
#define COLOR_PLUM							RGB(255, 215,   0)

// General Define
#define ENABLE					1
#define DISABLE					0
#define	UNCERTAIN				0

#define MYTOOLBAR_HEIGHT		70
#define PI						(acos(-1.0)) //3.1415926535    

#define RAM_INT_NUM			500
#define RAM_FLOAT_NUM		300
#define RAM_DOUBLE_NUM		300

#define MAX_IMG_WIDTH		3000
#define MAX_IMG_HEIGHT		2000
#define MAX_IMG_SIZE		(MAX_IMG_WIDTH*MAX_IMG_HEIGHT*3)

#define EXIT_NUMBER				999
#define ENDING_FINISH			888
#define EXIT_CONFIRM			9999
#define OPEN_FINISH				22733
#define ESC_NUMBER				1999

#define UV_FIXED_MODE			0
#define UV_POINTS_MODE			1
#define UV_ROTATE_MODE			2


#define TF_BACK_STAY			0
#define TF_BACK_CENTER_PEAK		1
#define TF_BACK_START_POS		2
#define TF_BACK_FIRST_PEAK		3

/*****************************/
/* M/C STATE definition		 */
/*****************************/
#define INITIAL_STATE				0x0001
#define READY_STATE					0x0002
#define ALARM_STATE					0x0004
#define STOP_STATE					0x0008
#define RUN_STATE					0x0010
#define MANUAL_STATE				0x0020
#define WARNING_STATE				0x0040
#define FINISH_STATE				0x0080

/*****************************/
/* TASK STATE definition	 */
/*****************************/
#define READY_TO_ROTATE			1
#define READY_TO_PROCESS		2
#define UNDER_PROCESSING		3
#define PROCESSED				4	

/*********************************/
/* SITE Test Result Definition	 */
/*********************************/
#define DEVICE_NOT_TESTED		31
#define DEVICE_TEST_OK			32
#define DEVICE_TEST_NG			33

/*********************************/
/* Result Display Trigger Definition	 */
/*********************************/
#define DISPLAY_NOT_CHANGE		0
#define DISPLAY_CLEAR			1
#define DISPLAY_UPDATE_NEW		2
//=== Auto task command list ===================
//=== Focus adjust unit command list ===========
#define AUTO_FOCUS_UNIT_READY_FOR_COMMAND			2

#define AUTO_FOCUS_X_MOVE_HOME						10
#define AUTO_FOCUS_X_MOVE_VISION					11
#define AUTO_FOCUS_X_OFFSET_MOVE_FROM_VISION		12
#define AUTO_FOCUS_X_MOVE_LASER						13
#define AUTO_FOCUS_X_MOVE_CONE						14

#define AUTO_FOCUS_Y_MOVE_HOME						20
#define AUTO_FOCUS_Y_MOVE_VISION					21
#define AUTO_FOCUS_Y_OFFSET_MOVE_FROM_VISION		22
#define AUTO_FOCUS_Y_MOVE_LASER						23
#define AUTO_FOCUS_Y_MOVE_CONE						24

#define AUTO_FOCUS_Z_MOVE_HOME						30
#define AUTO_FOCUS_Z_MOVE_VISION					31
#define AUTO_FOCUS_Z_MOVE_LASER						32
#define AUTO_FOCUS_Z_MOVE_CONE_Z_LASER_OFFSET		33

#define AUTO_FOCUS_R_MOVE_HOME						40

#define AUTO_FOCUS_XY_MOVE_HOME						50
#define AUTO_FOCUS_XY_MOVE_VISION					51
#define AUTO_FOCUS_XY_OFFSET_MOVE_FROM_VISION		52
#define AUTO_FOCUS_XY_MOVE_LASER					53
#define AUTO_FOCUS_XY_MOVE_CONE						54

#define AUTO_FOCUS_XYR_MOVE_HOME					60
#define AUTO_FOCUS_XYR_MOVE_VISION					61
#define AUTO_FOCUS_XY_MOVE_CONE_R_OFFSET			62

#define AUTO_FOCUS_XYR_OFFSET_MOVE_FROM_CONE		63

#define AUTO_FOCUS_R_ROTATE							64

#define AUTO_FOCUS_VISION_LIGHTSOURCE_ON			70
#define AUTO_FOCUS_VISION_LIGHTSOURCE_OFF			71 

#define AUTO_FOCUS_CL_MOVE_LEFT						80
#define AUTO_FOCUS_CL_MOVE_RIGHT					81

#define AUTO_FOCUS_UNIT_DONE						92

//////////////////////////////////////////////////////////////////////////
//define for auto focus process
#define AUTO_FOCUS_PROGRAM_READY					2
#define AUTO_FOCUS_PROGRAM_PROCESS					3
#define AUTO_FOCUS_PROGRAM_DONE						4 

//=== AF Test unit command list =============
#define AUTO_AF_TSET_UNIT_READY_FOR_COMMAND			3

#define AUTO_AF_TEST_UNIT_LIGHT_MOVE_LEFT			10
#define AUTO_AF_TEST_UNIT_LIGHT_MOVE_RIGHT			11

#define AUTO_AF_TEST_UNIT_DONE						93

//=== Dispenser unit command list ==============
#define AUTO_DISPENSER_UNIT_READY_FOR_COMMAND		4

#define AUTO_DISPENSER_UNIT_X_MOVE_HOME				10
#define AUTO_DISPENSER_UNIT_X_MOVE_VISION			11
#define AUTO_DISPENSER_UNIT_X_MOVE_LASER			12

#define AUTO_DISPENSER_UNIT_Y_MOVE_HOME				20
#define AUTO_DISPENSER_UNIT_Y_MOVE_VISION			21
#define AUTO_DISPENSER_UNIT_Y_MOVE_LASER			22

#define AUTO_DISPENSER_UNIT_Z_MOVE_HOME				30
#define AUTO_DISPENSER_UNIT_Z_MOVE_VISION			31
#define AUTO_DISPENSER_UNIT_Z_MOVE_LASER			32

#define AUTO_DISPENSER_UNIT_R_MOVE_HOME				40

#define AUTO_DISPENSER_UNIT_XY_MOVE_HOME			50
#define AUTO_DISPENSER_UNIT_XY_MOVE_VISION			51
#define AUTO_DISPENSER_UNIT_XY_MOVE_LASER			52

#define AUTO_IMAGE_UNIT_MOVE_LEFT					60
#define AUTO_IMAGE_UNIT_MOVE_RIGHT					61
#define AUTO_IMAGE_UNIT_MOVE_DOWN					62
#define AUTO_IMAGE_UNIT_MOVE_UP						63

#define AUTO_DISPENSER_UNIT_DONE					94

//====================================================
//=== Manual task command list =======================
//=== Focus adjust unit command list =================
#define MANUAL_OPERATION_READY_FOR_COMMAND			200

#define MANUAL_FOCUS_X_MOVE_HOME					210
#define MANUAL_FOCUS_X_MOVE_VISION					211
#define MANUAL_FOCUS_X_OFFSET_MOVE_FROM_VISION		212
#define MANUAL_FOCUS_X_MOVE_LASER					213
#define MANUAL_FOCUS_X_MOVE_CONE					214

#define MANUAL_FOCUS_Y_MOVE_HOME					220
#define MANUAL_FOCUS_Y_MOVE_VISION					221
#define MANUAL_FOCUS_Y_OFFSET_MOVE_FROM_VISION		222
#define MANUAL_FOCUS_Y_MOVE_LASER					223
#define MANUAL_FOCUS_Y_MOVE_CONE					224

#define MANUAL_FOCUS_Z_MOVE_HOME					230
#define MANUAL_FOCUS_Z_MOVE_VISION					231
#define MANUAL_FOCUS_Z_MOVE_LASER					232
#define MANUAL_FOCUS_Z_MOVE_CONE_Z_LASER_OFFSET		233

#define MANUAL_FOCUS_R_MOVE_HOME					240

#define MANUAL_FOCUS_XY_MOVE_HOME					250
#define MANUAL_FOCUS_XY_MOVE_VISION					251
#define MANUAL_FOCUS_XY_OFFSET_MOVE_FROM_VISION		252
#define MANUAL_FOCUS_XY_MOVE_LASER					253
#define MANUAL_FOCUS_XY_MOVE_CONE					254

#define MANUAL_FOCUS_XYR_MOVE_HOME					260
#define MANUAL_FOCUS_XYR_MOVE_VISION				261
#define MANUAL_FOCUS_XY_MOVE_CONE_R_OFFSET			262

#define MANUAL_FOCUS_VISION_LIGHTSOURCE_ON			263
#define MANUAL_FOCUS_VISION_LIGHTSOURCE_OFF			264

//=== AF Test unit command list =============
#define MANUAL_AF_TEST_UNIT_LIGHT_MOVE_LEFT			270
#define MANUAL_AF_TEST_UNIT_LIGHT_MOVE_RIGHT		280

//=== Dispenser unit command list ==============
#define MANUAL_DISPENSER_UNIT_X_MOVE_HOME							290
#define MANUAL_DISPENSER_UNIT_X_MOVE_VISION							291
#define MANUAL_DISPENSER_UNIT_X_MOVE_LASER							292
#define MANUAL_DISPENSER_UNIT_X_MOVE_GLASS							293
#define MANUAL_DISPENSER_UNIT_X_MOVE_VISION_ON_GLASS				294
#define MANUAL_DISPENSER_UNIT_X_MOVE_LASER_ON_GLASS					295
#define MANUAL_DISPENSER_UNIT_X_MOVE_VISION_CENTER					296

#define MANUAL_DISPENSER_UNIT_Y_MOVE_HOME							300
#define MANUAL_DISPENSER_UNIT_Y_MOVE_VISION							301
#define MANUAL_DISPENSER_UNIT_Y_MOVE_LASER							302
#define MANUAL_DISPENSER_UNIT_Y_MOVE_GLASS							303
#define MANUAL_DISPENSER_UNIT_Y_MOVE_VISION_ON_GLASS				304
#define MANUAL_DISPENSER_UNIT_Y_MOVE_LASER_ON_GLASS					305
#define MANUAL_DISPENSER_UNIT_Y_MOVE_VISION_CENTER					306

#define MANUAL_DISPENSER_UNIT_Z_MOVE_HOME							310
#define MANUAL_DISPENSER_UNIT_Z_MOVE_VISION							311
#define MANUAL_DISPENSER_UNIT_Z_MOVE_LASER							312
#define MANUAL_DISPENSER_UNIT_Z_MOVE_GLASS							313
#define MANUAL_DISPENSER_UNIT_Z_MOVE_VISION_ON_GLASS				314
#define MANUAL_DISPENSER_UNIT_Z_MOVE_LASER_ON_GLASS					315

#define MANUAL_DISPENSER_UNIT_R_MOVE_HOME							320

#define MANUAL_DISPENSER_UNIT_XY_MOVE_HOME							331
#define MANUAL_DISPENSER_UNIT_XY_MOVE_VISION						332
#define MANUAL_DISPENSER_UNIT_XY_MOVE_LASER							333
#define MANUAL_DISPENSER_UNIT_XY_MOVE_GLASS							334
#define MANUAL_DISPENSER_UNIT_XY_MOVE_VISION_ON_GLASS				335
#define MANUAL_DISPENSER_UNIT_XY_MOVE_LASER_ON_GLASS				336
#define MANUAL_DISPENSER_UNIT_XY_MOVE_VISION_CENTER_ON_GLASS		337
#define MANUAL_DISPENSER_UNIT_XY_MOVE_VISION_CENTER					338

#define MANUAL_DISPENSER_UNIT_DISPENSE_ONE_CYCLE					340 //  with dispensing time at OnePointDispensingTime, shm->RAM_INT[172]	// unit = 1ms
#define MANUAL_DISPENSER_UNIT_DISPENSE_VALVE_ON						341 
#define MANUAL_DISPENSER_UNIT_DISPENSE_VALVE_OFF					342 

#define MANUAL_DISPENSER_UNIT_VISION_LIGHTSOURCE_ON					343
#define MANUAL_DISPENSER_UNIT_VISION_LIGHTSOURCE_OFF				344


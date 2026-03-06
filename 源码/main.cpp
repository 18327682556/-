///*****************************
//* 作品名称：李白向前冲鸭
//* 开发环境：vs2022 + easyx
//* 存储方式：结构体、数组
//* 作者：宋加斌、章冻、王荷丽
//******************************/
////取消unicode字符集
//#ifdef UNICODE
//#undef UNICODE
//#endif 
//#include <stdio.h>		//格式化输入输出
//#include <graphics.h>	//easyx图形库
//#include <string>		
//#include <thread>		//多线程
//#include <vector>		//容器
//#include <time.h>
//#include <conio.h>
//#include "tools.h"		//自己封装的功能函数
//using namespace std;
//
///******************
//*
//	游戏设定宏
//*******************/
//
//
////游戏屏幕宽高
//#define WIN_WIDTH 1100
//#define WIN_HEIGHT 450
//
///******************
//*
//	设置结构体数组
//	最大容量、值
//*******************/
//
//
////game1
//#define MAP_COUNT 2			//地图类型
//#define PIECE_COUNT 5		//背景图层
//#define ROLE_COUNT 2		//角色类型
//#define OBSTACLE_COUNT 11	//最多障碍
//#define MAX_SCORE 20		//通关分数
//
///**********************
//*
//	功能菜单跳转、刷新
//***********************/
//
//
////全局鼠标
//ExMessage msg;
//
////初始图片
//IMAGE initialface;	//减轻卡顿
//
////判断
//bool endTrailer1;	//宣传片1是否结束
//bool endTrailer2;	//宣传片2是否结束
//bool game1_update;	//游戏1 是否需要马上刷新
//bool game2_update;	//游戏2 是否需要马上刷新
//
////----菜单选项类型
//enum MenuOp {
//
//	START,			//0开始游戏
//	AUTHOR,			//1作者
//	DESCRIPTION,	//2情节描述
//	ABOUT,			//3关于
//	OPERATE,		//4操作描述
//	HOME,			//5主页
//
//	OPTION_COUNT	//选项个数为 6
//};
//
//IMAGE imgHome[6];			//菜单主、分页图片 
//unsigned short menuOpType;	//菜单选项类型
//
////----游戏类型
//enum gameMenu {
//	FUNMENU,		//0在功能菜单
//	GAME1,			//1在游戏一
//
//	BUILD			//待开发
//};
//
//unsigned short gameOrder;	//游戏序号
//
////宣传片切换板
//typedef struct MouseRectBox {
//
//	unsigned short isInRectBox : 3;	//1在 0不在 2结束
//	unsigned short x;	//x坐标
//	unsigned short y;	//y坐标
//	unsigned short w;	//整体宽度
//	unsigned short h;	//整体高度
//	unsigned short lw;	//左按钮宽度(距离x)
//	unsigned short rw;	//右按钮宽度(距离x)
//}MsRecBox;
//
///********************************************
//*		↓游戏结构体与全局变量
//	/********************
//	*
//		游戏界面、人、物
//		用结构体设定
//	*********************/
//
//	//game1
//IMAGE imgScore[10];	//分数图片
//IMAGE imgButton[4];
//unsigned short groundHeight[2];	//地面高度(y坐标)
//
////----按钮类型
//enum button_type {
//	ESC,				//0退出
//	CHANGE_MAP,			//1切换地图
//	OPEMUSIC,			//2音乐开着
//	CLOMUSIC,			//3音乐关着
//
//	BUTTON_COUNT		//按键数
//};
//
////----背景类型
//enum map_type {
//
//	GRASSLAND,		//0草原
//	UNIVERSE,		//1宇宙
//
//	MAP_TYPE_COUNT	//地图数
//};
//
////背景
//vector<vector<IMAGE>> game1_bgImg;	//存放不同地图的多层背景
//
//short game1_mapType;					//地图类型
//typedef struct background {
//
//	unsigned short piece : 4;	//最大图层数为2^3-1=7
//	short x[PIECE_COUNT];		//图层x坐标
//	unsigned short speed[PIECE_COUNT];	//图层速度
//}background;
//background game1_bg[MAP_COUNT];
//
////----角色类型
//enum role_type {
//
//	LIBAI,			//0李白
//	GIRL,			//1女孩
//
//	ROLE_TYPE_COUNT
//};
//
////主角
//IMAGE imgMyRun[ROLE_COUNT][15];		//不同角色奔跑帧图
//IMAGE imgMyTurn[ROLE_COUNT][12];	//不同角色翻转帧图
//IMAGE imgMyDown[ROLE_COUNT][3];		//不同角色下蹲帧图
//IMAGE imgMyAttack[ROLE_COUNT][6];	//角色攻击
//IMAGE imgMyShoot[ROLE_COUNT][6];	//角色射击
//IMAGE imgMyHit[ROLE_COUNT];			//角色被撞伤
//IMAGE imgMyFly[ROLE_COUNT];			//角色保持腾空
//
//
//unsigned short myType;				//我的角色类型
//
//typedef struct myselfTrait {
//	//特性	//技能待加
//	unsigned short runPiece : 5;	//加载奔跑图数
//	unsigned short downPiece : 3;	//加载下蹲图数
//	unsigned short turnPiece : 5;	//加载翻转图数
//
//	unsigned short step : 5;	//步帧: 角色实时图片下标
//	short blood;		//血量
//
//	short jumpMinY;		//跳越最高点
//	short startJumpDy;	//起跳起落增量
//	short jumpDy;		//起落增量
//}myTrait;
//
//typedef struct myself {
//
//	unsigned short num : 3;		//加载角色数
//
//	//属性
//	unsigned short x[ROLE_COUNT];	//x坐标.(按照不同角色区分)
//	unsigned short y[ROLE_COUNT];	//y坐标.(按照不同角色区分)
//
//	unsigned short score;		//得分
//
//	bool jump : 1;				//是否跳越状态
//
//	bool down : 1;				//是否下蹲状态
//	short downX[ROLE_COUNT];	//下蹲x坐标.(按照不同角色区分)
//	short downY[ROLE_COUNT][3];	//下蹲y坐标.(按照不同角色区分)
//
//	bool keep : 1;				//是否保持动作
//	bool attack : 1;			//是否进攻状态
//	bool hit : 1;				//被攻击
//
//	//角色特性
//	myTrait trait[ROLE_COUNT];	//特性
//}myself;
//myself my;
//
////----障碍物类型
//typedef enum obs_type {
//
//	LION,			//0狮子
//	WOLF,			//1狼
//	WALL1,			//2墙一
//	WALL2,			//3墙二
//	WALL3,			//4墙三
//	WALL4,			//5墙四
//
//	OBS_TYPE_COUNT
//}obs_type;
//
////障碍物
//vector<vector<IMAGE>> obsImg;	//存放不同障碍物的行走帧图
//
//short lastObsIndex;			//前一个障碍物的角标
//short obstacleExist[11];
//typedef struct obstacle
//{
//	unsigned short type : 5;		//随机产生的障碍物类型
//	unsigned short step : 5;		//步帧
//
//	bool exist : 1;			//是否存在
//	bool hited : 1;			//是否被碰撞过
//	bool passed : 1;		//是否被通过
//	bool attacked : 1;		//是否被攻击
//	bool killed : 1;		//是否被杀死
//
//	short x, y;				//坐标.
//	unsigned int blood;		//血量
//	unsigned short speed;	//速度
//	unsigned short power;   //伤害
//
//}obstacle;
//obstacle  obs[OBSTACLE_COUNT];	//随机障碍物结构体数组
//
///********************************************
//*		↓函	数	部	分				    *
//											*
//	/********************					*
//	*										*
//		加载与初始化						*
//	逻辑处理与图像显示						*
//	********************/
//
//
//	//初始化宣传片、加载主页
//void initSurPage()
//{
//	//加载主页和分页
//	loadimage(&imgHome[0], "res/ui/home/start.bmp", 1100, 450);
//	loadimage(&imgHome[1], "res/ui/home/author.bmp", 1100, 450);
//	loadimage(&imgHome[2], "res/ui/home/description.bmp", 1100, 450);
//	loadimage(&imgHome[3], "res/ui/home/about.bmp", 1100, 450);
//	loadimage(&imgHome[4], "res/ui/home/operate.bmp", 1100, 450);
//	loadimage(&imgHome[5], "res/ui/home/home.bmp", 1100, 450);
//	preLoadSound("res/ui/home/click.mp3");
//
//	//字符短片初始为未播放
//	endTrailer1 = false;
//	endTrailer2 = false;
//
//	//初始位置为功能菜单的主页
//	gameOrder = 0;
//	menuOpType = HOME;
//}
//
////改变鼠标样式
//void changeMouse()
//{
//	HWND hwnd = GetHWnd();			//获取当前窗口句柄
//	HCURSOR hcur = LoadCursorFromFile("res/mb.cur");	//改变鼠标样式
//	SetClassLong(hwnd, GCL_HCURSOR, (long)hcur);	//第二个参数是鼠标样式
//	CloseHandle(hwnd);
//}
//
////多线程 判断在鼠标在短片切换框内
//DWORD WINAPI isInRectBox(LPVOID mrb1)
//{
//	MsRecBox* pm = (MsRecBox*)mrb1;
//	while (1)
//	{
//		if (pm->isInRectBox == 2)
//		{
//			while (msg.message == WM_LBUTTONDOWN)
//			{
//				//清空鼠标左键消息
//				while (peekmessage(&msg, EM_MOUSE) && msg.message == WM_LBUTTONDOWN);
//			}
//			return 0;
//		}
//
//		if (peekmessage(&msg, EM_MOUSE))
//		{
//			if (msg.message != WM_LBUTTONDOWN)
//			{
//				if ((msg.x > pm->x && msg.x < pm->x + pm->w)
//					&& (msg.y > pm->y && msg.y < pm->y + pm->h))
//				{
//					pm->isInRectBox = true;
//				}
//				else
//				{
//					pm->isInRectBox = false;
//				}
//			}
//			else
//			{
//				if ((msg.x > pm->x && msg.x < pm->x + pm->w)
//					&& (msg.y > pm->y && msg.y < pm->y + pm->h)
//					&& (endTrailer1 == false))
//				{
//					endTrailer1 = true;
//					Sleep(210);
//				}
//				else if ((msg.x > pm->x && msg.x < pm->x + pm->lw)
//					&& (msg.y > pm->y && msg.y < pm->y + pm->h)
//					&& (endTrailer1 == true))
//				{
//					endTrailer1 = false;
//					endTrailer2 = true;
//					Sleep(210);
//				}
//				else if ((msg.x > pm->x + pm->rw && msg.x < pm->x + pm->w)
//					&& (msg.y > pm->y && msg.y < pm->y + pm->h)
//					&& (endTrailer1 == true))
//				{
//					endTrailer2 = true;
//					Sleep(210);
//				}
//			}
//		}
//	}
//}
//
////鼠标是否在某个矩形区域(显红框)
//bool isInRect(ExMessage* msg, int x, int y, int w, int h, bool sleep)
//{
//	if ((msg->x > x && msg->x < x + w)
//		&& (msg->y > y && msg->y < y + h))
//	{
//		if (sleep)
//		{
//			playSound("res/ui/home/click.mp3",0);
//			setlinecolor(RED);
//			roundrect(x, y, x + w, y + h, 3, 3);
//			Sleep(210);
//		}
//		else
//		{
//			for (int i = 0; i < 2; i++)
//			{
//				roundrect(x, y, x + w, y + h, 3, 3);
//				Sleep(20);
//			}
//		}
//		while (msg->message == WM_LBUTTONDOWN)
//		{
//			//清空鼠标左键消息
//			while (peekmessage(msg, EM_MOUSE) && msg->message == WM_LBUTTONDOWN);
//		}
//		return true;
//	}
//	return false;
//}
//
////字符宣传片
//void trailer()
//{
//	closegraph();
//	initgraph(962, 542);	//962,522是视频的像素宽高 进度条高为12 上下距离=4
//	setbkcolor(RGB(235, 210, 80));	//淡黄背景
//	settextstyle(4, 2, "幼圆");
//	settextcolor(RGB(62, 10, 98));	//深蓝文字
//	cleardevice();					//刷新屏幕
//
//	//加载音乐
//	mciSendString("open res/ui/trailer/txt/1.mp3", NULL, 0, NULL);
//	mciSendString("open res/ui/trailer/txt/2.mp3", NULL, 0, NULL);
//	mciSendString("open res/ui/trailer/txt2/3.mp3", NULL, 0, NULL);
//
//	IMAGE imgSwitchBoard[2];	//加载短片切换板
//	loadimage(&imgSwitchBoard[0], "res/ui/trailer/switch1.bmp");
//	loadimage(&imgSwitchBoard[1], "res/ui/trailer/switch2.bmp");
//
//	FILE* fp;
//	char a[482];
//	char name[48];
//
//	MsRecBox mrb;
//	mrb.isInRectBox = 0;
//	mrb.x = 820;
//	mrb.y = 0;
//	mrb.w = 142;
//	mrb.h = 50;
//	mrb.lw = 65;
//	mrb.rw = 75;
//
//	HANDLE hTread = CreateThread(NULL, 0, isInRectBox, &mrb, 0, NULL);	//多线程获取鼠标是否在选框信息
//	CloseHandle(hTread);
//
//	while (msg.message == WM_LBUTTONDOWN)
//	{
//		//清空鼠标左键消息
//		while (peekmessage(&msg, EM_MOUSE) && msg.message == WM_LBUTTONDOWN);
//	}
//	BeginBatchDraw();
//	while (endTrailer1 == false)
//	{
//		endTrailer2 = false;	//可以播放短片2
//
//		//宣传片1:古代汉字
//		for (int i = 1; i <= 1800; i++)
//		{
//			if (i == 1)
//			{
//				mciSendString("play res/ui/trailer/txt/1.mp3 repeat", NULL, 0, NULL);
//				clearrectangle(20, 526, 962, 538);	//清空进度条
//			}
//			else if (i == 701)
//			{
//				mciSendString("close res/ui/trailer/txt/1.mp3", NULL, 0, NULL);
//				mciSendString("play res/ui/trailer/txt/2.mp3 repeat", NULL, 0, NULL);
//			}
//			else if (i == 1800)
//			{
//				endTrailer1 = true;
//			}
//
//			if (endTrailer1)
//			{
//				if (i <= 700)
//				{
//					mciSendString("close res/ui/trailer/txt/1.mp3", NULL, 0, NULL);
//				}
//				else
//				{
//					mciSendString("close res/ui/trailer/txt/2.mp3", NULL, 0, NULL);
//				}
//				break;
//			}
//
//			memset(a, 0, sizeof(a));//清空字符串
//			int y = 0;				//文字y坐标归零
//
//			sprintf_s(name, 48, "res/ui/trailer/txt/(%d).txt", i);
//			fopen_s(&fp, name, "rt");
//			if (fp == NULL)
//			{
//				return;
//			}
//			else
//			{
//				while (!feof(fp))
//				{
//					//按行读取 并打印一页
//					fgets(a, sizeof(a) - 1, fp);
//					outtextxy(0, y * 2, a);
//					y++;
//				}
//			}
//
//			//切换板白红闪 鼠标在选框时 显绿色
//			if (i % 3 != 0)
//			{
//				setbkcolor(WHITE);
//			}
//			else
//			{
//				setbkcolor(RGB(255, 50, 0));
//			}
//			if (mrb.isInRectBox)
//			{
//				setbkcolor(RGB(0, 200, 255));
//			}
//			clearrectangle(818, 0, 962, 52);	//清空切换板 
//			putimage(820, 0, &imgSwitchBoard[0]);	//贴切换板 宽140 高50
//
//			//20, 522 + 4, 962 - 20*2, 12 进度条:边框红 空条灰 实条绿
//			drawReadBar(20, 526, 922, 12, 2,
//				RGB(0, 60, 255), RGB(83, 83, 83), RGB(65, 206, 88), i / 1800.0);
//
//			if (fp != NULL)
//			{
//				fclose(fp);
//			}
//			FlushBatchDraw();
//			setbkcolor(RGB(235, 210, 80));	//淡黄背景
//			Sleep(22);
//		}
//
//		//宣传片2:李白语录
//		for (int i = 1; i <= 670; i++)
//		{
//			if (i == 1)
//			{
//				mciSendString("play res/ui/trailer/txt2/3.mp3 repeat", NULL, 0, NULL);
//				clearrectangle(20, 526, 962, 538);	//清空进度条
//			}
//			else if (i == 670)
//			{
//				endTrailer2 = true;
//			}
//			if (endTrailer2)
//			{
//				mciSendString("close res/ui/trailer/txt2/3.mp3", NULL, 0, NULL);
//				if (endTrailer1)
//				{
//					mrb.isInRectBox = 2;
//
//					//提前加载下一页图片
//					loadimage(&initialface, "res/ui/plot/(0).bmp");
//					Sleep(210);
//					EndBatchDraw();
//					return;
//				}
//				break;
//			}
//
//			memset(a, 0, sizeof(a));//清空字符串
//			short y = 0;			//文字y坐标归零
//			sprintf_s(name, 48, "res/ui/trailer/txt2/(%d).txt", i);
//			fopen_s(&fp, name, "rt");
//			if (fp == NULL)
//			{
//				return;
//			}
//			else
//			{
//				while (!feof(fp))
//				{
//					//按行读取并打印
//					fgets(a, sizeof(a) - 1, fp);
//					outtextxy(0, y * 2, a);
//					y++;
//				}
//			}
//
//			//切换板白红闪
//			if (i % 3 != 0)
//			{
//				setbkcolor(WHITE);
//			}
//			else
//			{
//				setbkcolor(RGB(255, 50, 0));
//			}
//			if (mrb.isInRectBox)//鼠标在选框时 显绿色
//			{
//				setbkcolor(RGB(0, 200, 255));
//			}
//			clearrectangle(818, 0, 962, 52);	//清空切换板 
//			putimage(820, 0, &imgSwitchBoard[1]);	//贴切换板 宽140 高50
//
//			//20, 522 + 4, 962 - 20*2, 12 进度条:色 边框 空条 实条
//			drawReadBar(20, 526, 922, 12, 2,
//				RGB(255, 0, 255), RGB(83, 83, 83), RGB(255, 120, 0), i / 670.0);
//
//			if (fp != NULL)
//			{
//				fclose(fp);
//			}
//			FlushBatchDraw();
//			setbkcolor(RGB(235, 210, 80));	//淡黄背景
//			Sleep(50);
//		}
//	}
//}
//
////剧情介绍ppt
//void plot()
//{
//	mciSendString("open res/ui/plot/1.mp3", NULL, 0, NULL);	//背景音
//	mciSendString("play res/ui/plot/1.mp3 repeat", NULL, 0, NULL);
//
//	//改变窗口大小
//	closegraph();
//	initgraph(WIN_WIDTH, WIN_HEIGHT);
//	putimage(0, 0, &initialface);	//贴初始页
//
//	unsigned short which = 0;
//	IMAGE imgPlot[4];	//情节	
//	char name[48];	//加载情节 与配音
//	for (int i = 0; i < 4; i++)
//	{
//		sprintf_s(name, 48, "res/ui/plot/(%d).bmp", i + 1);
//		loadimage(&imgPlot[i], name);
//	}
//
//	putimage(0, 0, &imgPlot[which]);//贴第一张图
//
//	//播放配音1
//	sprintf_s(name, 48, "open res/ui/plot/dub%d.mp3", which + 1);
//	mciSendString(name, NULL, 0, NULL);
//	sprintf_s(name, 48, "play res/ui/plot/dub%d.mp3", which + 1);
//	mciSendString(name, NULL, 0, NULL);
//
//	while (msg.message == WM_LBUTTONDOWN)
//	{
//		//清空鼠标左键消息
//		while (peekmessage(&msg, EM_MOUSE) && msg.message == WM_LBUTTONDOWN);
//	}
//	while (1)
//	{
//		peekmessage(&msg, EM_MOUSE);
//		if (msg.message == WM_LBUTTONDOWN)	//切换画面
//		{
//			if (which <= 2)
//			{
//				slipImage(&imgPlot[which], &imgPlot[which + 1], 0, 0, 1100, 450, 'L');
//
//				//播放配音
//				sprintf_s(name, 48, "close res/ui/plot/dub%d.mp3", which + 1);
//				mciSendString(name, NULL, 0, NULL);
//				sprintf_s(name, 48, "open res/ui/plot/dub%d.mp3", which + 2);
//				mciSendString(name, NULL, 0, NULL);
//				sprintf_s(name, 48, "play res/ui/plot/dub%d.mp3", which + 2);
//				mciSendString(name, NULL, 0, NULL);
//
//				which++;
//				putimage(0, 0, &imgPlot[which]);
//				while (msg.message == WM_LBUTTONDOWN || msg.message == WM_RBUTTONDOWN)
//				{
//					//清空鼠标消息
//					while (peekmessage(&msg, EM_MOUSE)
//						&& (msg.message == WM_LBUTTONDOWN || msg.message == WM_RBUTTONDOWN));
//				}
//				Sleep(210);
//			}
//			else
//			{
//				mciSendString("close res/ui/plot/1.mp3", NULL, 0, NULL);
//				mciSendString("close res/ui/plot/dub4.mp3", NULL, 0, NULL);
//				return;
//			}
//
//		}
//		else if (msg.message == WM_RBUTTONDOWN && which > 0)
//		{
//			slipImage(&imgPlot[which - 1], &imgPlot[which], 0, 0, 1100, 450, 'R');
//
//			//播放配音
//			sprintf_s(name, 48, "close res/ui/plot/dub%d.mp3", which + 1);
//			mciSendString(name, NULL, 0, NULL);
//			sprintf_s(name, 48, "open res/ui/plot/dub%d.mp3", which);
//			mciSendString(name, NULL, 0, NULL);
//			sprintf_s(name, 48, "play res/ui/plot/dub%d.mp3", which);
//			mciSendString(name, NULL, 0, NULL);
//
//			which--;
//			putimage(0, 0, &imgPlot[which]);
//			while (msg.message == WM_LBUTTONDOWN || msg.message == WM_RBUTTONDOWN)
//			{
//				//清空鼠标消息
//				while (peekmessage(&msg, EM_MOUSE)
//					&& (msg.message == WM_LBUTTONDOWN || msg.message == WM_RBUTTONDOWN));
//			}
//			Sleep(210);
//		}
//	}
//}
//
////初始化图标
//void initImagIco()
//{
//	//游戏一
//	loadimage(&imgButton[ESC], "res/game1/bg/esc.png");
//	loadimage(&imgButton[CHANGE_MAP], "res/game1/bg/changemap.png");
//	loadimage(&imgButton[OPEMUSIC], "res/game1/bg/openmusic.png");
//	loadimage(&imgButton[CLOMUSIC], "res/game1/bg/closemusic.png");
//}
//
////初始化背景
//void initBackground()
//{
//	//初始化地图类型
//	game1_mapType = UNIVERSE;
//	char name[PIECE_COUNT][48];
//
//	//----加载地图1			//GRASSLAND
//	//图层数
//	game1_bg[GRASSLAND].piece = 2;
//
//	game1_bg[GRASSLAND].speed[0] = 1;
//	game1_bg[GRASSLAND].speed[1] = 3;
//
//	//x坐标归零
//	for (int i = 0; i < game1_bg[GRASSLAND].piece; i++)
//	{
//		game1_bg[GRASSLAND].x[i] = 0;
//	}
//
//	IMAGE imggame1_bg;
//
//	sprintf_s(name[0], 48, "res/game1/bg/a/1.bmp");
//	sprintf_s(name[1], 48, "res/game1/bg/a/2.png");
//
//	//用容器收纳
//	vector<IMAGE> imgGame1_bgArrayA;
//	for (int i = 0; i < game1_bg[GRASSLAND].piece; i++)
//	{
//		loadimage(&imggame1_bg, name[i]);
//
//		imgGame1_bgArrayA.push_back(imggame1_bg);
//	}
//	game1_bgImg.push_back(imgGame1_bgArrayA);
//
//
//	//----加载地图2			//UNIVERSE
//	//图层数
//	game1_bg[UNIVERSE].piece = 5;
//
//	game1_bg[UNIVERSE].speed[0] = 1;
//	game1_bg[UNIVERSE].speed[1] = 2;
//	game1_bg[UNIVERSE].speed[2] = 2;
//	game1_bg[UNIVERSE].speed[3] = 3;
//	game1_bg[UNIVERSE].speed[4] = 3;
//
//	//x坐标归零
//	for (int i = 0; i < game1_bg[UNIVERSE].piece; i++)
//	{
//		game1_bg[UNIVERSE].x[i] = 0;
//	}
//
//	IMAGE imggame1_bg2;
//
//	sprintf_s(name[0], 48, "res/game1/bg/b/1.bmp");
//	sprintf_s(name[1], 48, "res/game1/bg/b/2.png");
//	sprintf_s(name[2], 48, "res/game1/bg/b/3.bmp");
//	sprintf_s(name[3], 48, "res/game1/bg/b/4.png");
//	sprintf_s(name[4], 48, "res/game1/bg/b/5.bmp");
//
//	//用容器收纳
//	vector<IMAGE> imgGame1_bg2ArrayA;
//	for (int i = 0; i < game1_bg[UNIVERSE].piece; i++)
//	{
//		loadimage(&imggame1_bg2, name[i]);
//
//		imgGame1_bg2ArrayA.push_back(imggame1_bg2);
//	}
//	game1_bgImg.push_back(imgGame1_bg2ArrayA);
//}
//
////初始化自己
//void initMyself()
//{
//	//初始化角色类型
//	myType = LIBAI;
//	char name[48];
//
//	//角色数
//	my.num = 1;		//可自行添加
//
//	//各角色奔跑帧图个数
//	my.trait[LIBAI].runPiece = 10;
//	//my.trait[GIRL].runPiece = 12;
//
//	//各角色下蹲帧图个数
//	my.trait[LIBAI].downPiece = 3;
//	//my.trait[GIRL].downPiece = 2;
//
//	//各角色翻转帧图个数
//	my.trait[LIBAI].turnPiece = 9;
//	//my.trait[GIRL].downPiece = 11;
//
//	//加载保持动作帧图
//	loadimage(&imgMyFly[LIBAI], "res/game1/my/0/fly.png");
//	loadimage(&imgMyHit[LIBAI], "res/game1/my/0/hit.png");
//
//	//----加载角色图片 初始化常规特性
//	for (int n = 0; n < my.num; n++)
//	{
//		for (int i = 0; i < my.trait[n].runPiece; i++)
//		{
//			//加载角色奔跑图片	或一阶跳
//			sprintf_s(name, 48, "res/game1/my/%d/run/(%d).png", n, i + 1);
//			loadimage(&imgMyRun[n][i], name);
//		}
//		for (int i = 0; i < my.trait[n].downPiece; i++)
//		{
//			//加载角色下蹲图片
//			sprintf_s(name, 48, "res/game1/my/%d/down/(%d).png", n, i + 1);
//			loadimage(&imgMyDown[n][i], name);
//		}
//		for (int i = 0; i < my.trait[n].turnPiece; i++)
//		{
//			//加载角色翻转图片
//			sprintf_s(name, 48, "res/game1/my/%d/down/(%d).png", n, i + 1);
//			loadimage(&imgMyTurn[n][i], name);
//		}
//		for (int i = 0; i < 6; i++)
//		{
//			//加载角色攻击图片
//			sprintf_s(name, 48, "res/game1/my/%d/attach/(%d).png", n, i + 1);
//			loadimage(&imgMyAttack[n][i], name);
//		}
//
//		//初始化常规特性
//		my.trait[n].step = 0;
//	}
//
//	//跳越最高点
//	my.trait[LIBAI].jumpMinY = groundHeight[game1_mapType] - (short)(2.2 * imgMyRun[LIBAI][0].getheight());
//	//my.trait[GIRL].jumpMinY = groundHeight[game1_mapType] - 2 * imgMyRun[GIRL][0].getheight();
//
//	my.trait[LIBAI].blood = 200;
//	//my.trait[GIRL].blood = 100;
//
//	//起跳速度
//	my.trait[LIBAI].jumpDy = my.trait[LIBAI].startJumpDy = -10;
//	//my.trait[GIRL].jumpDy = my.trait[LIBAI].startJumpDy = -7;
//
//
//	//----初始化角色属性
//	my.score = 0;
//	my.down = false;
//	my.jump = false;
//	my.keep = false;
//	my.attack = false;
//	my.hit = false;
//
//	//定位角色坐标
//	for (int i = 0; i < my.num; i++)
//	{
//		//站立
//		my.x[i] = (short)(0.5 * WIN_WIDTH - 0.5 * imgMyRun[i][0].getwidth());
//		my.y[i] = groundHeight[game1_mapType] - imgMyRun[i][0].getheight();
//
//		my.downX[i] = (short)(0.5 * WIN_WIDTH - 0.5 * imgMyDown[i][0].getwidth());
//	}
//
//	//设置角色下蹲y坐标
//	my.downY[LIBAI][0] = groundHeight[game1_mapType] - 118;
//	my.downY[LIBAI][1] = groundHeight[game1_mapType] - 95;
//	my.downY[LIBAI][2] = groundHeight[game1_mapType] - 67;
//
//	//加载分数图片
//	for (int i = 0; i < 10; i++)
//	{
//		sprintf_s(name, 48, "res/game1/score/%d.png",i);
//		loadimage(&imgScore[i], name);
//	}
//}
//
//void initEnemy()
//{
//	char name[48];
//
//	//加载狮子 和狼 图片帧素材
//	vector<IMAGE> imgLionArray;
//	vector<IMAGE> imgWolfArray;
//	IMAGE imgLion;
//	IMAGE imgWolf;
//	for (int i = 0; i < 8; i++)
//	{
//
//		sprintf_s(name, 48, "res/game1/enemy/lion/(%d).png", i + 1);
//		loadimage(&imgLion, name);
//
//		sprintf_s(name, 48, "res/game1/enemy/wolf/(%d).png", i + 1);
//		loadimage(&imgWolf, name);
//
//		imgLionArray.push_back(imgLion);
//		imgWolfArray.push_back(imgWolf);
//	}
//
//	obsImg.push_back(imgLionArray);
//	obsImg.push_back(imgWolfArray);
//
//	//加载墙素材
//	IMAGE imgWall;
//	for (int i = 0; i < 4; i++)
//	{
//		vector<IMAGE> imgWallArray;
//		sprintf_s(name, 48, "res/game1/enemy/wall/(%d).png", i + 1);
//		loadimage(&imgWall, name);
//
//		imgWallArray.push_back(imgWall);
//		obsImg.push_back(imgWallArray);
//	}
//
//	//初始化 不存在敌人
//	for (int i = 0; i < OBSTACLE_COUNT; i++)
//	{
//		obs[i].exist = false;
//	}
//
//	//之前无怪
//	lastObsIndex = -1;
//
//}
//
////初始化游戏1
//void initGame1()
//{
//	//初始化界面修饰量
//	game1_update = true;	//游戏1开始刷新
//	groundHeight[GRASSLAND] = 390;	//地面高度
//	groundHeight[UNIVERSE] = 420;
//
//	//初始化图标
//	initImagIco();
//
//	//初始化背景
//	initBackground();
//
//	//初始化自己
//	initMyself();
//
//	//初始化敌方
//	initEnemy();
//}
//
////初始化
//void init()
//{
//	//初始化宣传片和主页
//	initSurPage();
//
//	//加载游戏资源
//	initGame1();
//}
//
//void thematicDisplay()
//{
//	//显示海报
//	initgraph(WIN_WIDTH, WIN_HEIGHT);//设置窗口大小
//	loadimage(&initialface, "res/ui/poster/1.bmp");
//	putimage(0, 0, &initialface);
//
//	//改变鼠标样式
//	changeMouse();
//
//	//任意键进入
//	while (_kbhit() == 0);
//
//	//字符宣传片 
//	trailer();
//
//	//剧情ppt
//	plot();
//}
//
///****************
//*
//	游戏内鼠标操作
//*****************/
//
//
//
//
//void game1_mouse(bool* open_music)
//{
//	if (isInRect(&msg, 0, 0, 70, 70, false))
//	{
//		gameOrder = 0;
//	}
//	else if (isInRect(&msg, 100, 20, 70, 70, false))
//	{
//		game1_update = true;
//		short h = my.y[myType];		//记录当前y位置
//		short dh[3] = { 0 };			//记录当前下蹲高度
//		for (int j = 0; j < my.trait[LIBAI].downPiece; j++)
//		{
//			dh[j] = my.downY[myType][j];
//		}
//
//		//切换地图
//		game1_mapType = (game1_mapType + 1) % MAP_COUNT;
//		my.trait[LIBAI].jumpMinY = groundHeight[game1_mapType] - (short)(2.2 * imgMyRun[LIBAI][0].getheight());
//
//		//调整为对应位置
//		if (game1_mapType == GRASSLAND)
//		{
//			my.y[myType] = h - (groundHeight[1] - groundHeight[0]);
//			for (int j = 0; j < my.trait[LIBAI].downPiece; j++)
//			{
//				my.downY[myType][j] = dh[j] - (groundHeight[1] - groundHeight[0]);
//			}
//		}
//		else if (game1_mapType == UNIVERSE)
//		{
//			my.y[myType] = h + (groundHeight[1] - groundHeight[0]);
//			for (int j = 0; j < my.trait[LIBAI].downPiece; j++)
//			{
//				my.downY[myType][j] = dh[j] + (groundHeight[1] - groundHeight[0]);
//			}
//		}
//	}
//	else if (isInRect(&msg, 200, 20, 70, 70, false))
//	{
//		if (*open_music)
//		{
//			*open_music = false;
//		}
//		else
//		{
//			*open_music = true;
//		}
//	}
//	while (msg.message == WM_LBUTTONDOWN)
//	{
//		//清空鼠标左键消息
//		while (peekmessage(&msg, EM_MOUSE) && msg.message == WM_LBUTTONDOWN);
//	}
//}
//
///****************
//*
//	判断与显示
//*****************/
//
//
////判断背景运动
//void game1_bgMotion()
//{
//	//图上的x处
//	for (int i = 0; i < game1_bg[game1_mapType].piece; i++)
//	{
//		game1_bg[game1_mapType].x[i] += game1_bg[game1_mapType].speed[i];
//		if (game1_bg[game1_mapType].x[i] > WIN_WIDTH)
//		{
//			game1_bg[game1_mapType].x[i] = 0;
//		}
//	}
//}
//
////显示背景运动
//void showGame1_bgMotion()
//{
//	if (game1_mapType == GRASSLAND)
//	{
//		putimage(0, 0,
//			WIN_WIDTH, 350,
//			&game1_bgImg[game1_mapType][0], game1_bg[game1_mapType].x[0], 0);
//
//		putBgPNG(0, 243,
//			WIN_WIDTH, 207,
//			&game1_bgImg[game1_mapType][1], game1_bg[game1_mapType].x[1], 0);
//	}
//	else if (game1_mapType == UNIVERSE)
//	{
//		putimage(0, 0,
//			WIN_WIDTH, 182,
//			&game1_bgImg[game1_mapType][0], game1_bg[game1_mapType].x[0], 0);
//		putBgPNG(0, 91,
//			WIN_WIDTH, 71,
//			&game1_bgImg[game1_mapType][1], game1_bg[game1_mapType].x[1], 0);
//		putBgPNG(0, 162,
//			WIN_WIDTH, 207,
//			&game1_bgImg[game1_mapType][2], game1_bg[game1_mapType].x[2], 0);
//		putBgPNG(0, 282,
//			WIN_WIDTH, 168,
//			&game1_bgImg[game1_mapType][3], game1_bg[game1_mapType].x[3], 0);
//		putBgPNG(0, 366,
//			WIN_WIDTH, 168,
//			&game1_bgImg[game1_mapType][4], game1_bg[game1_mapType].x[4], 0);
//	}
//}
//
////判断我的运动
//void game1_myMotion()
//{
//	if (my.hit)
//	{
//		//被攻击
//		static int HitCount = 0;
//		short delays = 6;	//维持帧数
//
//		if (HitCount >= delays)	//卡步帧
//		{
//			my.hit = false;
//			HitCount = 0;
//			my.trait[myType].step = 0;
//		}
//		else
//		{
//			HitCount++;
//		}
//	}
//	else if (my.keep)
//	{
//		//不变图片
//	}
//	else if (my.jump)
//	{
//		//跳越
//		if (my.y[myType] < my.trait[myType].jumpMinY)
//		{
//			//上顶
//			my.trait[myType].jumpDy = -(my.trait[myType].startJumpDy + 6);
//		}
//
//		my.y[myType] += my.trait[myType].jumpDy;
//
//		if (my.y[myType] > groundHeight[game1_mapType] - imgMyRun[myType][0].getheight())
//		{
//			//下抵
//			my.y[myType] = groundHeight[game1_mapType] - imgMyRun[myType][0].getheight();
//			my.jump = false;
//			my.trait[myType].jumpDy = my.trait[myType].startJumpDy;
//		}
//	}
//	else if (my.down)
//	{
//		//下蹲
//		static int DownCount = 0;
//		short delays[3] = { 2,5,26 };	//三张图的维持帧数
//
//		if (DownCount >= delays[my.trait[myType].step])	//卡步帧
//		{
//			DownCount = 0;
//			my.trait[myType].step++;
//		}
//		else
//		{
//			DownCount++;
//		}
//
//		if (my.trait[myType].step >= my.trait[myType].downPiece)
//		{
//			game1_update = true;
//			my.down = false;
//			my.trait[myType].step = 0;
//		}
//	}
//	else if (my.attack)
//	{
//		//攻击
//		static int AttackCount = 0;
//		short delays[6] = { 2,3,4,6,24 };	//6张图的维持帧数
//
//		if (AttackCount >= delays[my.trait[myType].step])	//卡步帧
//		{
//			AttackCount = 0;
//			my.trait[myType].step++;
//		}
//		else
//		{
//			AttackCount++;
//		}
//
//		if (my.trait[myType].step >= 6)
//		{
//			game1_update = true;
//			my.attack = false;
//			my.trait[myType].step = 0;
//		}
//	}
//	else //奔跑
//	{
//		my.trait[myType].step = (my.trait[myType].step + 1) % my.trait[myType].runPiece;
//	}
//}
//
////显示我的运动
//void showMyMotion()
//{
//	if (my.hit)
//	{
//		//被攻击
//		putimagePNG(my.x[myType], my.y[myType], &imgMyHit[myType]);
//	}
//	else if (my.attack)
//	{
//		//发起攻击
//		putimagePNG(my.x[myType], my.y[myType], &imgMyAttack[myType][my.trait[myType].step]);
//	}
//	else if (my.keep && my.jump)
//	{
//		//跳越保持
//		putimagePNG(my.x[myType], my.y[myType], &imgMyFly[myType]);
//	}
//	else if (my.down)
//	{
//		//下蹲
//		putimagePNG(my.downX[myType], my.downY[myType][my.trait[myType].step],
//			&imgMyDown[myType][my.trait[myType].step]);
//	}
//	else
//	{
//		//普通奔跑
//		putimagePNG(my.x[myType], my.y[myType], &imgMyRun[myType][my.trait[myType].step]);
//	}
//}
//
////随机生成障碍物
//void creatObstacle(short i)
//{
//	obs[i].exist = true;
//	obs[i].hited = false;//被撞过
//	obs[i].passed = false;//被通过
//	obs[i].passed = false;//被攻击
//	obs[i].passed = false;//被杀死
//	obs[i].step = 0;	//开始走
//
//	//敌方随机类型的判定
//	obs[i].type = rand() % (WALL1 + 1);
//
//	if (obs[i].type == WALL1)	//控制墙的出现频率
//	{
//		obs[i].type += rand() % 4;
//	}
//	if (
//		lastObsIndex >= 0
//		&& obs[lastObsIndex].type >= WALL1
//		&& obs[lastObsIndex].type <= WALL4
//		&& obs[i].type == LION
//		&& obs[lastObsIndex].x > (short)(0.5 * WIN_WIDTH)
//		)
//	{
//		obs[i].type = WOLF;
//	}
//
//	lastObsIndex = i;
//
//	//产生的坐标
//	obs[i].x = WIN_WIDTH;
//	if (obs[i].type == LION)
//	{
//		obs[i].y = groundHeight[game1_mapType] - 93;
//	}
//	else if (obs[i].type == WOLF)
//	{
//		obs[i].y = groundHeight[game1_mapType] - 120;
//	}
//
//	//赋予敌方特性
//	if (obs[i].type == LION)
//	{
//		obs[i].blood = 200;
//		obs[i].speed = 3;
//		obs[i].power = 17;
//	}
//	else if (obs[i].type == WOLF)
//	{
//		obs[i].blood = 100;
//		obs[i].speed = 2;
//		obs[i].power = 9;
//	}
//	else	//墙
//	{
//		//特殊处理y坐标
//		obs[i].y = 0;
//		obs[i].speed = 5;
//		obs[i].power = 22;
//	}
//}
//
////是否生成障碍物
//short isCreat()
//{
//	static short frameCount = 0;//计次
//	frameCount++;
//	static short enemyFre = 60;//出现阈值
//	if (frameCount <= enemyFre)
//	{
//		//不产生敌方
//		return -1;
//	}
//
//	//重新计算帧数、设置出现频率
//	frameCount = 0;
//	enemyFre = 60 + rand() % 350;
//
//	short i;
//	for (i = 0; i < OBSTACLE_COUNT; i++)
//	{
//		if (obs[i].exist == false)
//		{
//			//寻找敌方池中还未出现的
//			break;
//		}
//	}
//	if (i >= OBSTACLE_COUNT)
//	{
//		//不产生敌方
//		return -1;
//	}
//	return i;
//}
//
////判断敌方的状态
//void game1_enemyStatus()
//{
//	//初始化敌方存活名单数组
//	obstacleExist[10] = 0;
//
//	//所有敌方向左走
//	for (int i = 0; i < OBSTACLE_COUNT; i++)
//	{
//		if (obs[i].exist)
//		{
//			obstacleExist[obstacleExist[10]] = i;
//			obstacleExist[10]++;
//			short bgSpeed = game1_bg[game1_mapType].speed[game1_bg[game1_mapType].piece - 1];
//			//向左移动
//			obs[i].x -= obs[i].speed + bgSpeed;
//
//			//完全离开
//			if (obs[i].x < -obsImg[obs[i].type][0].getwidth())
//			{
//				obs[i].exist = false;
//			}
//
//			//换帧动画
//			if (getDelay(68, 1)
//				&& (obs[i].type == LION || obs[i].type == WOLF))
//			{
//				obs[i].step = (obs[i].step + 1) % 8;
//			}
//			//墙不换帧
//		}
//	}
//}
//
////显示敌方的运动
//void showEnemyStatus()
//{
//	for (int i = 0; i < obstacleExist[10]; i++)
//	{
//		putimagePNG2(obs[obstacleExist[i]].x, obs[obstacleExist[i]].y, WIN_WIDTH,
//			&obsImg[obs[obstacleExist[i]].type][obs[obstacleExist[i]].step]);
//	}
//}
//
////判断游戏是否结束
//void checkOver()
//{
//	if (my.trait[myType].blood <= 0)
//	{
//		//loadimage(0, "res/over.png");
//		//FlushBatchDraw();
//
//		mciSendString("stop res/bg/alcohol.mp3", 0, 0, 0);
//		system("pause");
//
//		//复活
//		my.trait[myType].blood = 180;
//		my.score = 0;
//		mciSendString("play res/bg/alcohol.mp3 repeat", 0, 0, 0);
//	}
//}
//
//void checkBlood()
//{
//	setbkmode(TRANSPARENT);
//	//血量文字
//	settextcolor(RED);
//	settextstyle(13, 0, "宋体");
//	char score[24];
//	sprintf_s(score, 24, "剩余血量: %d", my.trait[myType].blood);
//	outtextxy(my.x[myType] + 60, my.y[myType] - 45, score);
//
//	setbkmode(OPAQUE);
//	//人物昵称
//	settextstyle(22,0,"宋体");
//	settextcolor(YELLOW);
//	outtextxy(my.x[myType] + 60, my.y[myType] - 30, "谪仙李白");
//
//	//画血条
//	drawReadBar(my.x[myType] + 50, my.y[myType] - 10, 
//		100, 5, 2, BLUE, DARKGRAY, RED, my.trait[myType].blood / 200.0);
//}
//
////检测攻击
//void checkAttached()
//{
//	for (int j = 0; j < obstacleExist[10]; j++)
//	{
//		short i = obstacleExist[j];
//
//	}
//}
//
////检测分数
//void showScore()
//{
//	char str[5];
//	sprintf_s(str, 5, "%d", my.score);
//	int x = 450;
//	int y = 20;
//	for (int i = 0; str[i] != '\0'; i++)
//	{
//		int sz = str[i] - '0';
//		putimagePNG(x, y, &imgScore[sz]);
//		x += imgScore[sz].getwidth() + 5;
//	}
//}
//
////检测通过
//void checkPassed()
//{
//	for (int j = 0; j < obstacleExist[10]; j++)
//	{
//		short i = obstacleExist[j];
//		if (
//			obs[i].exist
//			&& obs[i].hited == false
//			&& obs[i].passed == false
//			&& obs[i].x + obsImg[obs[i].type][0].getwidth() < my.x[myType] + 30
//			)
//		{
//			my.score++;
//			if (my.score >300)
//			{
//				my.score = 300;
//			}
//
//			obs[i].passed = true;
//			playSound("res/game1/recover.wav", 5);
//			my.trait[myType].blood += 5;
//		}
//	}
//}
//
////碰撞检测
//void checkHit()
//{
//	for (int j = 0; j < obstacleExist[10]; j++)
//	{
//		short i = obstacleExist[j];
//
//		short off = 30;	//碰撞容错 缩框
//		//抽帧	取坐标
//
//		short a1x, a1y, a2x, a2y;
//		if (!my.down)//非下蹲
//		{
//			a1x = (short)(1.5 * my.x[myType]);
//			a1y = my.y[myType] + off;
//			a2x = my.x[myType] + imgMyRun[myType][0].getwidth() - 2*off;
//			a2y = my.y[myType] + imgMyRun[myType][0].getheight() - off;
//		}
//		else
//		{
//			a1x = my.y[myType] + (short)(0.5*off);
//			a1y = my.y[myType] + off;
//			a2x = my.y[myType] + imgMyDown[myType][0].getwidth() - 2*off;
//			a2y = my.y[myType] + imgMyDown[myType][0].getheight() - off;
//		}
//
//		IMAGE img = obsImg[obs[i].type][obs[i].step];
//		short b1x = obs[i].x + 2*off;
//		short b1y = obs[i].y + off;
//		short b2x = obs[i].x + img.getwidth() - 2*off;
//		short b2y = obs[i].y + img.getheight() - off;
//
//		if (rectIntersect(a1x, a1y, a2x, a2y, b1x, b1y, b2x, b2y)
//			&& obs[i].hited == false)
//		{
//			if (obs[i].type <= 1)
//			{
//				playSound("res/game1/hit.mp3", 1);
//			}
//			else
//			{
//				playSound("res/game1/hitwall.mp3", 2);
//			}
//			
//			my.trait[myType].blood -= obs[i].power;
//			obs[i].hited = true;
//			my.hit = true;
//			my.trait[myType].step = 0;
//			game1_update = true;
//		}
//	}
//}
//
////伤害计算
//void injuryCalculation()
//{
//	//通过
//	checkPassed();
//	//碰撞
//	checkHit();
//	//被攻击
//	checkAttached();
//	//检查血条
//	checkBlood();
//
//	//判断是否结束 结束后任意键继续
//	checkOver();
//}
//
//void dealMusic(bool* open_music)
//{
//	static bool pre_isopen = true;
//	if (*open_music != pre_isopen)
//	{
//		if (*open_music)
//		{
//			mciSendString("resume res/game1/bg/alcohol.mp3", NULL, 0, NULL);
//		}
//		else
//		{
//			mciSendString("pause res/game1/bg/alcohol.mp3", NULL, 0, NULL);
//		}
//		pre_isopen = *open_music;
//	}
//}
//
////显示图标,音乐处理
//void showIco(bool* open_music)
//{
//	//贴图标
//	putimagePNG(0, 0, &imgButton[ESC]);
//	putimagePNG(100, 20, &imgButton[CHANGE_MAP]);
//	if (*open_music)
//	{
//		putimagePNG(200, 20, &imgButton[OPEMUSIC]);
//	}
//	else
//	{
//		putimagePNG(200, 20, &imgButton[CLOMUSIC]);
//	}
//}
//
////判断与显示(游戏核心处理）
//void judgeDisplay(bool* open_music)
//{
//	//背景音处理
//	dealMusic(open_music);
//
//	//设置随机数种子
//	srand((unsigned)time(NULL));
//
//	short i = isCreat();
//	if (i != -1)	//生成障碍物
//	{
//		creatObstacle(i);
//	}
//
//	//游戏背景
//	game1_bgMotion();		//背景移动
//	thread bgThread(showGame1_bgMotion);
//	bgThread.join();
//
//	//人物运动
//	game1_myMotion();		//我的动作
//	thread myMotionThread(showMyMotion);
//	myMotionThread.detach();
//
//	//障碍物运动与状态 录下敌方名单
//	thread eneStaThread(game1_enemyStatus);//敌方移动
//	eneStaThread.detach();
//
//	//显示敌方
//	thread eneThread(showEnemyStatus);
//	eneThread.join();
//
//	injuryCalculation();	//赏罚计算
//
//	//显示分数
//	showScore();
//
//	//加载按钮图标
//	showIco(open_music);
//}
//
///****************
//*
//	处理键盘输入
//*****************/
//
////游戏1的键盘处理
//void keyEvent1(char ch)
//{
//	if (ch == 27)	//esc键值 退出游戏
//	{
//		gameOrder = 0;
//		return;
//	}
//
//	if ((ch == 'q' || ch == 'Q'))	//切换地图
//	{
//		game1_update = true;
//		short h = my.y[myType];		//记录当前y位置
//		short dh[3] = { 0 };			//记录当前下蹲高度
//		for (int j = 0; j < my.trait[LIBAI].downPiece; j++)
//		{
//			dh[j] = my.downY[myType][j];
//		}
//
//		//切换地图
//		game1_mapType = (game1_mapType + 1) % MAP_COUNT;
//		my.trait[LIBAI].jumpMinY = groundHeight[game1_mapType] - (short)(2.2 * imgMyRun[LIBAI][0].getheight());
//
//		//调整为对应位置
//		if (game1_mapType == GRASSLAND)
//		{
//			my.y[myType] = h - (groundHeight[1] - groundHeight[0]);
//			for (int j = 0; j < my.trait[LIBAI].downPiece; j++)
//			{
//				my.downY[myType][j] = dh[j] - (groundHeight[1] - groundHeight[0]);
//			}
//		}
//		else if (game1_mapType == UNIVERSE)
//		{
//			my.y[myType] = h + (groundHeight[1] - groundHeight[0]);
//			for (int j = 0; j < my.trait[LIBAI].downPiece; j++)
//			{
//				my.downY[myType][j] = dh[j] + (groundHeight[1] - groundHeight[0]);
//			}
//		}
//	}
//	else if ((ch == 's' || ch == 'S')	//维持在空中 双按无效
//		&& my.jump
//		&& my.keep == false)
//	{
//		//保持
//		game1_update = true;
//		my.keep = true;
//	}
//	else if ((ch == 'a' || ch == 'A')
//		&&(!my.jump) 
//		&&(!my.down))	//攻击状态
//	{
//		game1_update = true;
//		my.keep = false;
//		my.attack = true;
//		my.trait[myType].step = 0;
//	}
//	else if (ch == ' '
//		&&(!my.attack))		//跳越可取消下蹲和保持
//	{
//		//跳越
//		game1_update = true;
//		my.keep = false;
//		my.down = false;
//		my.jump = true;
//		my.y[myType]--;
//	}
//	else if (ch == 'w' || ch == 'W'
//		&& (!my.attack))	//下蹲可以加快降落
//	{
//		my.keep = false;
//
//		//下蹲
//		if (my.jump)	//如果在跳越就降落	
//		{
//			if (my.trait[myType].jumpDy < 12)
//			{
//				//快速下落
//				game1_update = true;
//				my.trait[myType].jumpDy = 12;
//			}
//		}
//		else if (my.y[myType] == groundHeight[game1_mapType] - imgMyRun[myType][0].getheight())
//		{
//			//在地面就下蹲
//			game1_update = true;
//			my.trait[myType].step = 0;
//			my.down = true;
//		}
//	}
//}
//
////游戏1
//void playGame1()
//{
//	myType = LIBAI;	//调试初始人物
//	mciSendString("open res/game1/bg/alcohol.mp3", NULL, 0, NULL);
//	mciSendString("play res/game1/bg/alcohol.mp3 repeat", NULL, 0, NULL);
//	preLoadSound("res/game1/click.mp3");
//	preLoadSound("res/game1/hit.mp3");
//	preLoadSound("res/game1/hitwall.mp3");
//	preLoadSound("res/game1/attack.mp3");
//	preLoadSound("res/game1/key.mp3");
//	preLoadSound("res/game1/recover.wav");
//	BeginBatchDraw();
//	cleardevice();
//	while (gameOrder != 0)
//	{
//		static bool open_music = true;
//
//		//游戏1内鼠标
//		if (peekmessage(&msg, EM_MOUSE)
//			&& msg.message == WM_LBUTTONDOWN)
//		{
//			playSound("res/game1/click.mp3", 3);
//			thread Game1MousThread(game1_mouse, &open_music);
//			Game1MousThread.detach();
//		}
//		if (_kbhit())
//		{
//			char ch = _getch();
//			playSound("res/game1/key.mp3", 4);
//			thread keyThread(keyEvent1, ch);
//			keyThread.detach();
//		}
//		if (getDelay(35, 0))
//		{
//			game1_update = true;
//		}
//		if (game1_update)
//		{
//			game1_update = false;
//			judgeDisplay(&open_music);
//			FlushBatchDraw();
//		}
//	}
//	EndBatchDraw();
//	mciSendString("close res/game1/bg/alcohol.mp3", NULL, 0, NULL);
//}
//
////功能菜单
//void funMenu()
//{
//	mciSendString("open res/ui/home/1.mp3", NULL, 0, NULL);
//	mciSendString("play res/ui/home/1.mp3 repeat", NULL, 0, NULL);
//
//	closegraph();
//	initgraph(WIN_WIDTH, WIN_HEIGHT);
//
//	putimage(0, 0, &imgHome[menuOpType]);//贴第一张图
//	while (msg.message == WM_LBUTTONDOWN)
//	{
//		//清空鼠标左键消息
//		while (peekmessage(&msg, EM_MOUSE) && msg.message == WM_LBUTTONDOWN);
//	}
//	while (gameOrder == 0)
//	{
//		//鼠标左键点击---->切换画面
//		peekmessage(&msg, EM_MOUSE);
//		if (msg.message == WM_LBUTTONDOWN)
//		{
//			if (isInRect(&msg, 50, 50, 150, 125, true))//单独解决回到home功能
//			{
//				menuOpType = HOME;
//				putimage(0, 0, &imgHome[menuOpType]);
//			}
//			else if (menuOpType == HOME)
//			{
//				//主页菜单功能
//				if (isInRect(&msg, 250, 100, 150, 100, true))
//				{
//					menuOpType = AUTHOR;
//				}
//				else if (isInRect(&msg, 300, 250, 150, 100, true))
//				{
//					menuOpType = DESCRIPTION;
//				}
//				else if (isInRect(&msg, 700, 100, 150, 100, true))
//				{
//					menuOpType = OPERATE;
//				}
//				else if (isInRect(&msg, 650, 250, 150, 100, true))
//				{
//					menuOpType = ABOUT;
//				}
//				else if (isInRect(&msg, 450, 100, 200, 150, true))
//				{
//					menuOpType = START;
//				}
//				putimage(0, 0, &imgHome[menuOpType]);
//			}
//			else if (menuOpType == START)
//			{
//				//开始菜单功能
//				if (isInRect(&msg, 350, 166, 124, 86, true))
//				{
//					gameOrder = 1;
//				}
//				else if (isInRect(&msg, 478, 166, 122, 86, true))
//				{
//					//gameOrder = 2;
//				}
//				else if (isInRect(&msg, 945, 166, 95, 86, true))
//				{
//					//gameOrder = 3;
//				}
//
//			}
//		}
//	}
//	mciSendString("close res/ui/home/1.mp3", NULL, 0, NULL);
//}
//
////主菜单
//void mainMenu()
//{
//	while (1)
//	{
//		if (gameOrder == 0)
//		{
//			funMenu();
//		}
//		else
//		{
//			if (gameOrder == 1)
//			{
//				playGame1();
//			}
//			else if (gameOrder == 2)
//			{
//
//			}
//			else if (gameOrder == 3)
//			{
//
//			}
//		}
//	}
//}
//
//int main0()
//{
//	//后台初始化
//	thread initThread(init);
//	initThread.detach();
//
//	//主题展示
//	thematicDisplay();
//
//	//主菜单
//	mainMenu();
//	return 0;
//}
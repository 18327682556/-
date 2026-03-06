#ifdef UNICODE//取消unicode字符集
#undef UNICODE
#endif
#include <stdio.h>
#include <time.h>
#include "tools.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

//5个计时器
bool getDelay(short duration, short id)
{
	static unsigned long long startTime[5] = { 0 };
	unsigned int endTime = clock();
	if ((endTime - startTime[id]) >= (unsigned short)duration)
	{
		startTime[id] = endTime;
		return true;
	}
	return false;
}

//滑动动作 x0,y0是设定贴图位置 w,h为合图的宽与高 ch标记左 右
void slipImage(IMAGE* picLeft, IMAGE* picRight, short x0, short y0, short w, short h, char ch)
{
	mciSendString("open res/ui/plot/slip.mp3", NULL, 0, NULL);
	mciSendString("play res/ui/plot/slip.mp3", NULL, 0, NULL);

	//向右滑
	if (ch == 'R')
	{
	BeginBatchDraw();
	short x = 1;

	while (x < w)
	{
		putimage(0, 0, x, h, picLeft, w - x, 0);
		putimage(x0 + x, y0, w - x, h, picRight, 0, 0);
		FlushBatchDraw();

		if(x > w / 4 && x < w * 3 / 4)
		{
			x += 2;
		}
		else
		{
			x += 1;
		}
		Sleep(1);
	}
	EndBatchDraw();
	}

	if (ch == 'L')
	{
		BeginBatchDraw();
		short x = w - 1;

		while (x > 1)
		{
			putimage(0, 0, x, h, picLeft, w - x, 0);
			putimage(x0 + x, y0, w - x, h, picRight, 0, 0);
			FlushBatchDraw();

			if (x > w / 4 && x < w * 3 / 4)
			{
				x -= 2;
			}
			else
			{
				x -= 1;
			}
			Sleep(1);
		}
		EndBatchDraw();
	}
	mciSendString("close res/ui/plot/slip.mp3", NULL, 0, NULL);
}

// PNG图去除透明部分
void putimagePNG(int  picture_x, int picture_y, IMAGE* picture) //x为载入图片的X坐标，y为Y坐标
{
	DWORD* dst = GetImageBuffer();    // GetImageBuffer()函数，用于获取绘图设备的显存指针，EASYX自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(picture); //获取picture的显存指针
	int picture_width = picture->getwidth(); //获取picture的宽度，EASYX自带
	int picture_height = picture->getheight(); //获取picture的高度，EASYX自带
	int graphWidth = getwidth();       //获取绘图区的宽度，EASYX自带
	int graphHeight = getheight();     //获取绘图区的高度，EASYX自带
	int dstX = 0;    //在显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < picture_height; iy++)
	{
		for (int ix = 0; ix < picture_width; ix++)
		{
			int srcX = ix + iy * picture_width; //在显存里像素的角标
			int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA是透明度
			int sr = ((src[srcX] & 0xff0000) >> 16); //获取RGB里的R
			int sg = ((src[srcX] & 0xff00) >> 8);   //G
			int sb = src[srcX] & 0xff;              //B
			if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
			{
				dstX = (ix + picture_x) + (iy + picture_y) * graphWidth; //在显存里像素的角标
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}

//裁剪再贴，精准大小
void putBgPNG(short x, short y, short w, short h, IMAGE* picture, short xx, short yy) {
	IMAGE imgTmp;
	SetWorkingImage(picture);
	getimage(&imgTmp, xx, yy, w, h);
	SetWorkingImage();

	putimagePNG(x, y, &imgTmp);
}

//x > w或 x < 0 右屏幕外不绘图
void putimagePNG2(short x, short y, int winWidth, IMAGE* picture) {
	IMAGE imgTmp;
	if (x < -picture->getwidth() || x >= winWidth){
		return;
	}
	else if (x < 0) {
		SetWorkingImage(picture);
		getimage(&imgTmp, -x, 0, picture->getwidth() + x, picture->getheight());
		SetWorkingImage();
		x = 0;
		picture = &imgTmp;
	}
	else if (x > winWidth - picture->getwidth()) {
		SetWorkingImage(picture);
		getimage(&imgTmp, 0, 0, winWidth - x, picture->getheight());
		SetWorkingImage();
		picture = &imgTmp;
	}
	putimagePNG(x, y, picture);
}

//矩形相交
bool rectIntersect(short x01, short y01, short x02, short y02,
	short x11, short y11, short x12, short y12)
{
	short zx = abs(x01 + x02 - x11 - x12);
	short x = abs(x01 - x02) + abs(x11 - x12);
	short zy = abs(y01 + y02 - y11 - y12);
	short y = abs(y01 - y02) + abs(y11 - y12);
	return  (zx <= x && zy <= y);
}

//首次加载音效(重命名)
void  preLoadSound(const char* name) {
	char cmd[128];
	sprintf_s(cmd, sizeof(cmd), "open %s alias %s-1", name, name);//a.mp3-1 重命名1
	mciSendString(cmd, 0, 0, 0);
	sprintf_s(cmd, sizeof(cmd), "open %s alias %s-2", name, name);//a.mp3-2 重命名2
	mciSendString(cmd, 0, 0, 0);
}

//多次放音效不冲突 7个循环音箱
void  playSound(const char* name, short id) {
	static short index[7] = { 1,1,1,1,1,1,1 };
	char cmd[128];

	if (index[id] == 1) {
		sprintf_s(cmd, sizeof(cmd), "play %s-1", name);
		mciSendString(cmd, 0, 0, 0);
		sprintf_s(cmd, sizeof(cmd), "close %s-2", name);
		mciSendString(cmd, 0, 0, 0);
		sprintf_s(cmd, sizeof(cmd), "open %s alias %s-2", name, name);
		mciSendString(cmd, 0, 0, 0);
		index[id]++;
	}
	else if (index[id] == 2) {
		sprintf_s(cmd, sizeof(cmd), "play %s-2", name);
		mciSendString(cmd, 0, 0, 0);
		sprintf_s(cmd, sizeof(cmd), "close %s-1", name);
		mciSendString(cmd, 0, 0, 0);
		sprintf_s(cmd, sizeof(cmd), "open %s alias %s-1", name, name);
		mciSendString(cmd, 0, 0, 0);
		index[id] = 1;
	}
}

//血条、进度条
void drawReadBar(short x, short y, short w, short h, short lineWidth, int boardColor, int emptyColor, int fillColor, double percent) {
	LINESTYLE lineStyle;	//创建对象

	getlinestyle(&lineStyle);	//保存样式
	int lineColor = getlinecolor();	//存储线框颜色
	int fileColor = getfillcolor();	//存储填充颜色

	if (percent < 0) {
		percent = 0;
	}

	setlinecolor(boardColor);
	setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, lineWidth);	//实线 圆结点
	setfillcolor(emptyColor);
	fillroundrect(x, y, x + w, y + h, 4, 4);	//圆角矩形外框

	setfillcolor(fillColor);
	if (percent > 0) {
		short fillx = (short)(x + 0.5 * lineWidth);
		short filly = (short)(y + 0.5 * lineWidth);
		short fillw = w - lineWidth;
		short fillh = h - lineWidth;
		//画内框 无框线
		solidroundrect(fillx, filly, x + (int)(fillw * percent), y + fillh, 3, 3);
	}

	setlinecolor(lineColor);	//恢复原来样式
	setfillcolor(fileColor);
	setlinestyle(&lineStyle);	
}

//画
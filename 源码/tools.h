#pragma once            //编译时 只被包含一次
#include <graphics.h>   //IMAGE类型用到

//不同时间间隔的定时器
bool getDelay(short duration, short id);

//滑动动作 x0,y0是设定贴图位置 w,h为合图的宽与高 ch标记左 右
void slipImage(IMAGE* picLeft, IMAGE* pic, short x0, short y0, short w, short h, char ch);

//透明贴图
void putimagePNG(int  picture_x, int picture_y, IMAGE* picture);

//支持y<0 以及 x<0 裁剪精准绘图 x,y为打印再屏幕位置 w为宽度 h为 高度 xx yy为图片上的坐标
//裁剪再贴，精准大小
void putBgPNG(short x, short y, short w, short h, IMAGE* picture, short xx, short yy);

//x > w或 x < 0 右屏幕外不绘图
void putimagePNG2(short x, short y, int winWidth, IMAGE* picture);

// 判断两个矩形是否相交
bool rectIntersect(short x01, short y01, short x02, short y02,
	short x11, short y11, short x12, short y12);

//第一次音效
void  preLoadSound(const char* name);

//播放音效
void  playSound(const char* name, short id);

//画血条
void drawReadBar(short x, short y, short w, short h, short lineWidth, int boardColor, int emptyColor, int fillColor, double percent);
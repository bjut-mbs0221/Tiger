#ifndef _PANEL_H_
#define _PANEL_H_

#include <graphics.h>
#include "Lable.h"
#include "Button.h"

typedef struct{
	int x, y, width, height;	//尺寸
	COLORREF background;		//背景色
	IMAGE *image;				//背景图片
}Panel;

// 构造函数
Panel *CreatePanel(int x, int y, IMAGE *img);
Panel *CreatePanel(int x, int y, int w, int h);
Panel *CreatePanel(int x, int y, int w, int h, IMAGE *img);

// 成员方法
void add(Panel *root, Panel *p);
void add(Panel *root, Lable *p);
void add(Panel *root, Button *p);

void setSize(Panel *p, int w, int h);
void setLocation(Panel *p, int x, int y);
void setBackground(Panel *p, COLORREF color);
void setBackground(Panel *p, IMAGE *img);
void setDefaultProperty(Panel *p);
void display(Panel *p);

#endif
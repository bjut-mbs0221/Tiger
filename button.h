#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <graphics.h>
#include <stdio.h>

#define BUTTON_TEXT_WIDTH 16
static int INT_BUTTON_COUNT = 0;

typedef struct{
	int x, y, width, height;
	bool OnClicked, OnHover;
	char text[BUTTON_TEXT_WIDTH];
	COLORREF background;
	COLORREF foreground;
	COLORREF focuscolor;
	int linestyle;
	IMAGE *image;
}Button;

// 构造函数
Button *CreateButton(int x, int y);
Button *CreateButton(int x, int y, char *str);
Button *CreateButton(int x, int y, IMAGE *img);
Button *CreateButton(int x, int y, char *str, IMAGE *img);

// 成员方法
void setText(Button *p, char *s);
void setSize(Button *B);
void setSize(Button *B, int w, int h);
void setLocation(Button *p, int x, int y);
void setLineStyle(Button *p, int i);
void setForeground(Button *p, COLORREF color);
void setBackground(Button *p, COLORREF color);
void setFocusColor(Button *p, COLORREF color);
void setBackground(Button *p, IMAGE *img);
void setDefalutProperty(Button *B);
void display(Button *B);
void MouseEvent(Button *B, MOUSEMSG m);

#endif
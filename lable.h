#ifndef _LABLE_H_
#define _LABLE_H_

#include <stdio.h>
#include "graphics.h"

#define LABLE_TEXT_WIDTH 16
typedef struct{
	int x, y, width, height;
	char text[LABLE_TEXT_WIDTH];
	COLORREF background;
	COLORREF foreground;
	COLORREF focuscolor;
	IMAGE *image;
}Lable;

Lable *CreateLable(int x, int y, char *s);
Lable *CreateLable(int x, int y, char *s, IMAGE *img);

void setText(Lable *p, char *s);
void setTextStyle(int w, int h, char *lpface);
void setIcon(Lable *p, IMAGE *img);
void setSize(Lable *p);
void setSize(Lable *p, int w, int h);
void setLocation(Lable *p, int x, int y);
void setForeground(Lable *p, COLORREF color);
void setBackground(Lable *p, COLORREF color);
void setDefalutProperty(Lable *p);
void display(Lable *p);

#endif
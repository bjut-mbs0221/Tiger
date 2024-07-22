#include "lable.h"

// 带文字
Lable *CreateLable(int x, int y, char *s)
{
	Lable *p = (Lable*)malloc(sizeof(Lable));
	setDefalutProperty(p);
	setText(p, s);
	setLocation(p, x, y);
	setSize(p);
	return p;
}

// 带图标文字
Lable *CreateLable(int x, int y, char *s, IMAGE *img)
{
	Lable *p = (Lable*)malloc(sizeof(Lable));
	setDefalutProperty(p);
	setText(p, s);
	setIcon(p, img);
	setLocation(p, x, y);
	setSize(p);
	return p;
}

// 文本
void setText(Lable *p, char *s)
{
	memset(p->text, 0, sizeof(p->text));
	sprintf(p->text, "%s", s);
}

// 字体
void setTextStyle(int w, int h, char *lpface)
{
	settextstyle(w, h, lpface);
}

// 图标
void setIcon(Lable *p, IMAGE *img)
{
	p->image = img;
}

// 自适应尺寸
void setSize(Lable *p)
{
	if (p->image != NULL){
		p->width += p->image->getwidth();
		p->height += p->image->getheight();
	}
	if (strlen(p->text)>0){
		p->width += 80;//  textwidth(p->text);
	}
}

// 尺寸
void setSize(Lable *p, int w, int h)
{
	p->width = w;
	p->height = h;
}

// 位置
void setLocation(Lable *p, int x, int y)
{
	p->x = x;
	p->y = y;
}

// 前景色
void setForeground(Lable *p, COLORREF color)
{
	p->foreground = color;
}

// 背景色
void setBackground(Lable *p, COLORREF color)
{
	p->background = color;
}

// 默认属性
void setDefalutProperty(Lable *p)
{
	p->x = 0;
	p->y = 0;
	p->width = 0;
	p->height = 0;
	p->image = NULL;
	p->foreground = 0xffccff;
	p->background = 0x000000;
	p->focuscolor = 0xccffff;
}

// 显示
void display(Lable *p)
{
	setlinestyle(0, 0);
	setlinecolor(p->background);
	setfillcolor(p->background);
	fillrectangle(p->x, p->y, p->x+p->width, p->y+p->height);
	setcolor(p->foreground);
	if (p->image != NULL)
	{
		putimage(p->x, p->y, p->image, SRCCOPY);
		if (strlen(p->text)>0)
		{
			settextcolor(p->foreground);
			outtextxy(p->x + p->image->getwidth(), p->y, p->text);
		}//有文字
	}// 有图片
	else if (strlen(p->text)>0)
	{
		settextcolor(p->foreground);
		outtextxy(p->x, p->y, p->text);
	}// 无图片 有文字
}
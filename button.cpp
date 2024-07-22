#include "button.h"
// 带参构造函数x, y;
Button *CreateButton(int x, int y)
{
	Button *p = (Button*)malloc(sizeof(Button));
	setDefalutProperty(p);
	setText(p, "Button");
	setLocation(p, x, y);
	setSize(p);
	return p;
}
// 带参构造函数x, y, str;
Button *CreateButton(int x, int y, char *str)
{
	Button *p = (Button*)malloc(sizeof(Button));
	setDefalutProperty(p);
	setText(p, str);
	setLocation(p, x, y);
	return p;
}
// 带参构造函数x, y, image;
Button *CreateButton(int x, int y, IMAGE *image)
{
	Button *p = (Button*)malloc(sizeof(Button));
	setDefalutProperty(p);
	setBackground(p, image);
	setText(p, "");
	setLocation(p, x, y);
	setSize(p);
	return p;
}
// 带参构造函数x, y, str, path;
Button *CreateButton(int x, int y, char *str, IMAGE *image)
{
	Button *p = (Button*)malloc(sizeof(Button));
	setDefalutProperty(p);
	setText(p, str);
	setBackground(p, image);
	setLocation(p, x, y);
	setSize(p);
	return p;
}
// 文本
void setText(Button *p, char *s)
{
	memset(p->text, 0, sizeof(p->text));
	sprintf(p->text, "%s", s);
}
// 尺寸
void setSize(Button *p)
{
	if(p->image != NULL){
		p->width += p->image->getwidth();
		p->height += p->image->getheight();
	}// 图片尺寸
	if (strlen(p->text) > 0){
		p->width += textwidth(p->text);
	}// 文字尺寸
}
// 设置大小
void setSize(Button *B, int w, int h)
{
	B->width = w;
	B->height = h;
}
// 位置
void setLocation(Button *p, int x, int y)
{
	p->x = x;
	p->y = y;
}
// 线条样式
void setLineStyle(Button *p, int i)
{
	p->linestyle = i;
}
// 前景色
void setForeground(Button *p, COLORREF color)
{
	p->foreground = color;
}
// 背景色
void setBackground(Button *p, COLORREF color)
{
	p->background = color;
}
// 获得焦点颜色
void setFocusColor(Button *p, COLORREF color){
	p->focuscolor = color;
}
// 背景图片
void setBackground(Button *p, IMAGE *image)
{
	p->image = image;
}
// 默认属性
void setDefalutProperty(Button *p)
{
	p->x = 0;
	p->y = 0;
	p->width = 0;
	p->height = 0;
	p->image = NULL;
	p->foreground = 0xffccff;
	p->background = 0xffffcc;
	p->focuscolor = 0xccffff;
	p->linestyle = 2;
	p->OnClicked = false;
	p->OnHover = false;
}
// 显示
void display(Button *p){
	setlinestyle(2, p->linestyle);
	if(p->image != NULL){// 有图片
		putimage(p->x, p->y, p->image, SRCCOPY);
		if(p->text != NULL){//有文字、
			settextcolor(p->foreground);
			outtextxy(p->x + p->image->getwidth(), p->y, p->text);
		}
	}else if(p->text != NULL){// 无图片 有文字
		setcolor(p->background);
		rectangle(p->x, p->y, p->x + p->width, p->y + p->height);
		settextcolor(p->foreground);
		outtextxy(p->x, p->y, p->text);
	}
	if(p->OnHover){
		setcolor(p->foreground);
		rectangle(p->x, p->y, p->x + p->width, p->y + p->height);
	}//悬浮时边框
	if(p->OnClicked){
		setcolor(p->focuscolor);
		rectangle(p->x, p->y, p->x + p->width, p->y + p->height);
	}//点击时边框
	setlinestyle(2, 0);
}
// 鼠标事件
void MouseEvent(Button *p, MOUSEMSG m)
{
	p->OnClicked = false;
	p->OnHover = false;
	p->linestyle = 0;
	if(m.x > p->x&&m.y > p->y&&m.x < p->x + p->width&&m.y< p->y + p->height){
		if(m.mkLButton){
			p->OnClicked = true;
			p->linestyle = 3;
		}else{
			p->OnHover = true;
			p->linestyle = 4;
		}
	}
}

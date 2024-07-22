#include "panel.h"

Panel *CreatePanel(int x, int y, int w, int h)
{
	Panel *p = (Panel*)malloc(sizeof(Panel));
	setDefaultProperty(p);
	setSize(p, w, h);
	setLocation(p, x, y);
	return p;
}

Panel *CreatePanel(int x, int y, IMAGE *img)
{
	Panel *p = (Panel*)malloc(sizeof(Panel));
	setDefaultProperty(p);
	setSize(p, img->getwidth(), img->getheight());
	setLocation(p, x, y);
	setBackground(p, img);
	return p;
}

Panel *CreatePanel(int x, int y, int w, int h, IMAGE *img)
{
	Panel *p = (Panel*)malloc(sizeof(Panel));
	setDefaultProperty(p);
	setSize(p, w, h);
	setLocation(p, x, y);
	setBackground(p, img);
	return p;
}

void add(Panel *root, Button *B)
{

}

void add(Panel *root, Panel *p)
{

}

void add(Panel *root, Lable *L)
{

}

void setSize(Panel *p, int w, int h){
	p->width = w;
	p->height = h;
}

void setLocation(Panel *p, int x, int y){
	p->x = x;
	p->y = y;
}

void setBackground(Panel *p, COLORREF color)
{
	p->background = color;
}

void setBackground(Panel *p, IMAGE *img){
	p->image = img;
}

void setDefaultProperty(Panel *p){
	p->image = NULL;
	p->background = BLACK;
}

void display(Panel *p)
{
	if (p->image != NULL){
		for(int x = 0; x < p->width; x += p->image->getwidth()){
			for(int y = 0; y < p->height; y += p->image->getheight()){
				putimage(p->x + x, p->y + y, p->image, SRCCOPY);
			}
		}
	}//Ìî³äÍ¼Æ¬
	else
	{
		setfillcolor(p->background);
		fillrectangle(p->x, p->y, p->x + p->width, p->y + p->height);
	}//Ìî³ä±³¾°É«
}
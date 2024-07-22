#include "tiger.h"

Tiger* CreateTiger(int x, int y, IMAGE *img)
{
	Tiger *tiger = (Tiger*)malloc(sizeof(Tiger));
	tiger->x = x;
	tiger->y = y;
	tiger->score = 50;
	tiger->name = (char*)malloc(16 * sizeof(char));
	tiger->img = img;
	tiger->w = tiger->img->getwidth();
	tiger->h = tiger->img->getheight();
	tiger->flag = true;
	return tiger;
}//初始化老虎

void display(Tiger *t)
{
	if(t->img){
		putimage(t->x, t->y, t->img, SRCCOPY);
	}
}//显示老虎
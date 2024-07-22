#ifndef _TIGER_H_
#define _TIGER_H_

#include <graphics.h>

typedef struct
{
	int x, y, w, h;
	int score;
	char *name;
	bool flag;
	IMAGE *img;
}Tiger;

Tiger* CreateTiger(int x, int y, IMAGE *img);

void display(Tiger *t);

#endif
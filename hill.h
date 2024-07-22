#ifndef _HILL_H_
#define _HILL_H_

#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

typedef struct{
	int x, y, type;
	IMAGE *image;
}Hill;

Hill *CreateHill(int x, int y, int type, IMAGE *img);

void display(Hill *H);

#endif
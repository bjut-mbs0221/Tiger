#include "hill.h"

Hill *CreateHill(int x, int y, int type, IMAGE *img)
{
	Hill *H = (Hill*)malloc(sizeof(Hill));
	H->x = x;
	H->y = y;
	H->type = type;
	H->image = img;
	return H;
}

void display(Hill *H)
{
	putimage(H->x, H->y, H->image, SRCCOPY);
}
#include "bonus.h"

void move(Node *p, int dx, int dy)
{
	p->x += dx;
	p->y += dy;
}

void display(Node *p, IMAGE *img)
{
	putimage(p->x, p->y, img, SRCCOPY);
}

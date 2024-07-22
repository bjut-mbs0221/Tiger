#include <graphics.h>
#ifndef _BONUS_
#define _BONUS_

// ����ڵ���
typedef struct
{
	int x, y, w, h, type, state;
}Node;

typedef struct List
{
	Node data;
	List *next;
}List;

void move(Node *p, int dx, int dy);
void display(Node *p, IMAGE *img);

#endif
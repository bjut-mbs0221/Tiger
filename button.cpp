#include "button.h"
// ���ι��캯��x, y;
Button *CreateButton(int x, int y)
{
	Button *p = (Button*)malloc(sizeof(Button));
	setDefalutProperty(p);
	setText(p, "Button");
	setLocation(p, x, y);
	setSize(p);
	return p;
}
// ���ι��캯��x, y, str;
Button *CreateButton(int x, int y, char *str)
{
	Button *p = (Button*)malloc(sizeof(Button));
	setDefalutProperty(p);
	setText(p, str);
	setLocation(p, x, y);
	return p;
}
// ���ι��캯��x, y, image;
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
// ���ι��캯��x, y, str, path;
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
// �ı�
void setText(Button *p, char *s)
{
	memset(p->text, 0, sizeof(p->text));
	sprintf(p->text, "%s", s);
}
// �ߴ�
void setSize(Button *p)
{
	if(p->image != NULL){
		p->width += p->image->getwidth();
		p->height += p->image->getheight();
	}// ͼƬ�ߴ�
	if (strlen(p->text) > 0){
		p->width += textwidth(p->text);
	}// ���ֳߴ�
}
// ���ô�С
void setSize(Button *B, int w, int h)
{
	B->width = w;
	B->height = h;
}
// λ��
void setLocation(Button *p, int x, int y)
{
	p->x = x;
	p->y = y;
}
// ������ʽ
void setLineStyle(Button *p, int i)
{
	p->linestyle = i;
}
// ǰ��ɫ
void setForeground(Button *p, COLORREF color)
{
	p->foreground = color;
}
// ����ɫ
void setBackground(Button *p, COLORREF color)
{
	p->background = color;
}
// ��ý�����ɫ
void setFocusColor(Button *p, COLORREF color){
	p->focuscolor = color;
}
// ����ͼƬ
void setBackground(Button *p, IMAGE *image)
{
	p->image = image;
}
// Ĭ������
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
// ��ʾ
void display(Button *p){
	setlinestyle(2, p->linestyle);
	if(p->image != NULL){// ��ͼƬ
		putimage(p->x, p->y, p->image, SRCCOPY);
		if(p->text != NULL){//�����֡�
			settextcolor(p->foreground);
			outtextxy(p->x + p->image->getwidth(), p->y, p->text);
		}
	}else if(p->text != NULL){// ��ͼƬ ������
		setcolor(p->background);
		rectangle(p->x, p->y, p->x + p->width, p->y + p->height);
		settextcolor(p->foreground);
		outtextxy(p->x, p->y, p->text);
	}
	if(p->OnHover){
		setcolor(p->foreground);
		rectangle(p->x, p->y, p->x + p->width, p->y + p->height);
	}//����ʱ�߿�
	if(p->OnClicked){
		setcolor(p->focuscolor);
		rectangle(p->x, p->y, p->x + p->width, p->y + p->height);
	}//���ʱ�߿�
	setlinestyle(2, 0);
}
// ����¼�
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

#ifndef _GAME_H_
#define _GAME_H_

#include <graphics.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "panel.h"
#include "button.h"
#include "lable.h"
#include "tiger.h"
#include "bonus.h"

#define WIDTH 40		//�����
#define HEIGHT 24		//�����
#define W 20			//ͼƬ�ߴ�

#define PAGE 6			//��20ҳ
#define COUNT 12		//ÿҳ6������
#define M 34			//��Ϸ���ݳߴ�
#define N 20			//��Ϸ���ݳߴ�

// ��������
#define CMD_NONE  0x0000 //�˳�
#define CMD_MOVE  0x0001 //�ƶ�
#define CMD_EXIT  0x1000 //�˳�
#define CMD_START 0x1001 //��ʼ
#define CMD_PAUSE 0x1002 //��ͣ
#define CMD_REPLAY 0x1003 //����

// ��̬�ַ�����Դ
static char *ID_TITLE = "�ɻ���ð��";
static char *ID_START = "��ʼ��Ϸ";
static char *ID_PAUSE = "��ͣ��Ϸ";
static char *ID_EXIT = "�˳���Ϸ";

// ��̬ͼ����Դ
static IMAGE IMG_BARRIER;	// �ϰ�
static IMAGE IMG_DIAMOND;	// ��ʯ
static IMAGE IMG_RIVER;		// ����
static IMAGE IMG_HILL;		// ɽ��
static IMAGE IMG_SIDE;		// �߽�
static IMAGE IMG_TIGER;		// �ϻ�
static IMAGE IMG_START;		// ��ʼ
static IMAGE IMG_PAUSE;		// ��ͣ
static IMAGE IMG_EXIT;		// �˳�
static IMAGE IMG_REPLAY;	// ����
static IMAGE IMG_DESIGN;	// ���
static IMAGE IMG_RECORD;	// ��¼

// ��Ϸ�ṹ�嶨��
typedef struct{
	char *title;
	bool state;
	int width, height, cmd, index, maxscore;
	List *list;
	MOUSEMSG m;
	Tiger *tiger;
	Panel *river, *side[2], *toolbar;
	Button *start, *pause, *replay, *record, *design, *exit;
	Lable *info, *player, *score, *lmax;
}Game;

// ���캯��
Game* CreateGame(int w, int h, char *title);

// ��Ա����
void InitImage();
void InitResouses(Game *G);
void InitRoles(Game *G);
void InitGame(Game *G);
void FreeGame(Game *G);
void BeginGame(Game *G);
void NextGame(Game *G);
bool JudgeGame(Game *G);
void UpdataToolPanel(Game *G);
void UpdateInfoPanel(Game *G);
void UpdataGamePanel(Game *G);
void KeyEvent(Game *G);
void MouseEvent(Game *G);

#endif
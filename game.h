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

#define WIDTH 40		//界面宽
#define HEIGHT 24		//界面高
#define W 20			//图片尺寸

#define PAGE 6			//共20页
#define COUNT 12		//每页6个物体
#define M 34			//游戏内容尺寸
#define N 20			//游戏内容尺寸

// 命令声明
#define CMD_NONE  0x0000 //退出
#define CMD_MOVE  0x0001 //移动
#define CMD_EXIT  0x1000 //退出
#define CMD_START 0x1001 //开始
#define CMD_PAUSE 0x1002 //暂停
#define CMD_REPLAY 0x1003 //重玩

// 静态字符串资源
static char *ID_TITLE = "巧虎大冒险";
static char *ID_START = "开始游戏";
static char *ID_PAUSE = "暂停游戏";
static char *ID_EXIT = "退出游戏";

// 静态图像资源
static IMAGE IMG_BARRIER;	// 障碍
static IMAGE IMG_DIAMOND;	// 宝石
static IMAGE IMG_RIVER;		// 河流
static IMAGE IMG_HILL;		// 山脉
static IMAGE IMG_SIDE;		// 边界
static IMAGE IMG_TIGER;		// 老虎
static IMAGE IMG_START;		// 开始
static IMAGE IMG_PAUSE;		// 暂停
static IMAGE IMG_EXIT;		// 退出
static IMAGE IMG_REPLAY;	// 重来
static IMAGE IMG_DESIGN;	// 设计
static IMAGE IMG_RECORD;	// 记录

// 游戏结构体定义
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

// 构造函数
Game* CreateGame(int w, int h, char *title);

// 成员方法
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
#include "game.h"

Game* CreateGame(int w, int h, char *title)
{
	Game *G = (Game*)malloc(sizeof(Game));
	G->maxscore = 0;
	G->width = w;
	G->height = h;
	G->cmd = CMD_PAUSE;
	G->index = 0;
	G->title = title;
	G->state = true;
	G->list = (List*)malloc(sizeof(List));
	return G;
}// 创建游戏空间

void InitImages()
{
	loadimage(&IMG_BARRIER, ".\\barrier.bmp", 20, 20, false);//背景
	loadimage(&IMG_DIAMOND, ".\\diamond.bmp", 20, 20, false);//宝石
	loadimage(&IMG_RIVER, ".\\river.bmp", 40, 40, false);//河流
	loadimage(&IMG_HILL, ".\\hill.bmp", 80, 80, false);//山脉
	loadimage(&IMG_SIDE, ".\\side.bmp", 40, 40, false);
	loadimage(&IMG_TIGER, ".\\Tiger.bmp", 40, 40, false);
	loadimage(&IMG_START, ".\\Start.bmp", 80, 20, false);
	loadimage(&IMG_PAUSE, ".\\Pause.bmp", 80, 20, false);
	loadimage(&IMG_REPLAY, ".\\replay.bmp", 80, 20, false);
	loadimage(&IMG_EXIT, ".\\Exit.bmp", 80, 20, false);
	loadimage(&IMG_DESIGN, ".\\design.bmp", 80, 20, false);
	loadimage(&IMG_RECORD, ".\\record.bmp", 80, 20, false);
}// 读取图片资源

void InitResouses(Game *G)
{
	// 面板
	G->side[0] = CreatePanel(0, 0, 680, 40, &IMG_SIDE);			// 上边岸
	G->river = CreatePanel(0, 40, 680, 400, &IMG_RIVER);		// 河流
	G->side[1] = CreatePanel(0, 440, 680, 40, &IMG_SIDE);		// 下边岸
	G->toolbar = CreatePanel(680, 0, 100, 480, &IMG_SIDE);		// 工具栏
	// 按钮
	G->start = CreateButton(G->width - 100, 50, &IMG_START);	// 开始游戏
	G->pause = CreateButton(G->width - 100, 75, &IMG_PAUSE);	// 暂停游戏
	G->replay = CreateButton(G->width - 100, 100, &IMG_REPLAY);	// 重玩游戏
	G->design = CreateButton(G->width - 100, 125, &IMG_DESIGN);	// 设计地图
	G->record =  CreateButton(G->width - 100, 150, &IMG_RECORD);// 记录地图
	G->exit = CreateButton(G->width - 100, 175, &IMG_EXIT);		// 退出游戏
	// 标签
	G->info = CreateLable(G->width - 100, 240, "信息:");		// 信息
	setSize(G->info, 80, 20);
	G->player = CreateLable(G->width - 100, 265, "玩家:");		// 玩家
	setSize(G->player, 80, 20);
	G->score = CreateLable(G->width - 100, 290, "分数:");		// 分数
	setSize(G->score, 80, 20);
	G->lmax = CreateLable(G->width - 100, 315, "尺寸:");		// 尺寸
	setSize(G->lmax, 80, 20);
}// 加载游戏资源

void GenerateMap(Game *G)
{
	Node p;
	FILE *fout = fopen(".\\map.dat", "wb");
	if(fout == NULL){
		printf("Open File Failed!\n");
	}
	for (int i = 0; i < PAGE; i++){
		for (int j = 0; j < COUNT; j++){
			p.x = i * M * W + rand()%(M * W);
			p.y = rand()%(N * W);
			p.type = rand()%4;
			p.w = p.type == 3 ? W*2 : W/2;
			p.h = p.type == 3 ? W*2 : W/2;
			p.state = 1;
			fwrite(&p, sizeof(Node), 1, fout);
		}
	}
	printf("Create Map Finished!\n");
	fclose(fout);
}// 生成地图

void InitMap(Game *G)
{
	printf("Read Map Finished!\n");
	List *l = G->list;
	FILE *fin = fopen(".\\map.dat", "rb");
	if(fin == NULL){
		printf("Open File Failed!\n");
	}
	for (int i = 0; i < COUNT * PAGE; i++){
		fread(&l->data, sizeof(Node), 1, fin);
		l->next = (List*)malloc(sizeof(List));
		l = l->next;
	}
	l->next = NULL;
	printf("Read Map Finished!\n");
	printf("Count:%d\n", i);
	fclose(fin);
}//读取地图

void InitRoles(Game *G)
{
	G->tiger = CreateTiger(0, 200, &IMG_TIGER);
	G->tiger->name = "Tiger";
}//初始化角色

void InitGame(Game *G)
{
	InitImages();		//加载图片
	InitResouses(G);	//加载组件资源
	GenerateMap(G);		//生成地图
	InitMap(G);			//加载地图
	InitRoles(G);		//加载角色
	InputBox(G->player->text, 16, "请输入玩家：", "Dialog");
}//初始化游戏

void SaveState(Game *G)
{

}//保存当前状态

void FreeGame(Game *G)
{
	printf("delete G->tiger\n");
	delete G->tiger;
	printf("delete G->river\n");
	delete G->river;
	printf("delete G->start\n");
	delete G->start;
	printf("delete G->pause\n");
	delete G->pause;
	printf("delete G->exit\n");
	delete G->exit;
	printf("delete G->player\n");
	delete G->player;
	printf("delete G->score\n");
	delete G->score;
}// 释放游戏资源

void BeginGame(Game *G)
{
	srand(time(0));
	InitGame(G);
	initgraph(G->width, G->height); 
	while(G->cmd != CMD_EXIT){
		BeginBatchDraw();
		KeyEvent(G);			// 按键操作
		MouseEvent(G);			// 鼠标事件
		JudgeGame(G);			// 游戏判分
		NextGame(G);			// 下一局
		UpdataGamePanel(G);		// 游戏元素
		UpdataToolPanel(G);		// 工具栏
		UpdateInfoPanel(G);		// 提示信息
		FlushMouseMsgBuffer();
		FlushBatchDraw();
		EndBatchDraw();
		Sleep(25);
	}
	closegraph();
	FreeGame(G);
}// 开始游戏

void NextGame(Game *G)
{
	if(G->tiger->x < M*N && G->tiger->score > 0) return;
	G->tiger->x = M * N;
	if(G->tiger->score > G->maxscore){
		G->maxscore = G->tiger->score;
	}
	int result = MessageBox(GetHWnd(), TEXT("继续"), TEXT("继续：YES / NO"), MB_YESNO);
	if(result == IDYES){
		G->cmd = CMD_REPLAY;
		G->index = 0;
		InitMap(G);
		InitRoles(G);
	}else if(result == IDNO){
		exit(0);
	}
}

bool JudgeGame(Game *G)
{
	if (G->cmd == CMD_PAUSE || !G->cmd == CMD_MOVE)return false;//暂停或是不移动则不更新界面
	List *p = G->list;
	bool result = false;
	int x1 = G->tiger->x + G->index*W + G->tiger->w / 2;
	int y1 = G->tiger->y + G->tiger->h / 2;
	int r0 = (p->data.w + G->tiger->w) / 2;
	while (p){
		int x0 = p->data.x + p->data.w / 2;
		int y0 = p->data.y + p->data.h / 2;
		if((x1 - x0)*(x1 - x0)+(y1 - y0)*(y1 - y0) < r0 * r0){
			switch(p->data.type){
			case 1:
				G->tiger->score+=5;
				p->data.type = 0;
				break;
			case 2:
				G->tiger->score-=5;
				result = true;
				break;
			case 3:
				G->tiger->score-=5;
				result = true;
				break;
			default:
				break;
			}
		}
		p = p->next;
	}
	if(G->score < 0) G->tiger->score = 0;
	return result;
}// 游戏判断

void UpdataToolPanel(Game *G)
{
	display(G->side[0]);
	display(G->side[1]);
	display(G->toolbar);
	display(G->start);
	display(G->pause);
	display(G->replay);
	display(G->design);
	display(G->record);
	display(G->exit);
}// 显示界面

void UpdateInfoPanel(Game *G)
{
	sprintf(G->score->text, "分数:%d", G->tiger->score);
	sprintf(G->lmax->text, "最高分:%d", G->maxscore);
	display(G->info);
	display(G->player);
	display(G->score);
	display(G->lmax);
}// 显示标签

void UpdataGamePanel(Game *G)
{
	if (G->cmd == CMD_PAUSE || !G->cmd == CMD_MOVE)return;//暂停或是不移动则不更新界面
	clearrectangle(G->river->x, G->river->y, G->river->width, G->river->height);
	display(G->river);
	for (List *p = G->list; p; p = p->next){
		switch(p->data.type){
		case 1:
			putimage(p->data.x - G->index*W, p->data.y, &IMG_DIAMOND, SRCCOPY);
			break;
		case 2:
			putimage(p->data.x - G->index*W, p->data.y, &IMG_BARRIER, SRCCOPY);
			break;
		case 3:
			putimage(p->data.x - G->index*W, p->data.y, &IMG_HILL, SRCCOPY);
			break;
		default:
			break;
		}
	}
	display(G->tiger);// 显示角色
}// 显示游戏内容

void KeyEvent(Game *G)
{
	if(G->cmd == CMD_PAUSE) return;
	int i = (G->tiger->x - G->river->x) / 20;
	int j = (G->tiger->y - G->river->y) / 20;
	G->cmd = CMD_NONE;
	if (GetAsyncKeyState(VK_UP)){
		G->cmd = CMD_MOVE;
		if(G->tiger->y > W*2)G->tiger->y -= 5;
	}
	if (GetAsyncKeyState(VK_DOWN)){
		G->cmd = CMD_MOVE;
		if(G->tiger->y < W*N)G->tiger->y += 5;
	}
	if (GetAsyncKeyState(VK_LEFT)){
		G->cmd = CMD_MOVE;
		if(G->tiger->x > 0){
			G->tiger->x -= 5;
		}else if(G->index > 0){
			G->index--;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT)){
		if(G->tiger->x + G->index * W > W * M * (PAGE - 1)){
			if(G->tiger->x < (W-1) * M){
				G->tiger->x += 5;
				G->cmd = CMD_MOVE;
			}
		}else{
			G->index++;
			G->cmd = CMD_MOVE;
		}
	}
	if(GetAsyncKeyState(VK_RETURN)) G->cmd = CMD_START;
	if(GetAsyncKeyState(VK_SPACE)) G->cmd = CMD_PAUSE;
	if(GetAsyncKeyState(VK_ESCAPE)) G->cmd = CMD_EXIT;
}// 按键事件

void MouseEvent(Game *G)
{
	if (MouseHit()){
		G->m = GetMouseMsg();
		MouseEvent(G->start, G->m);
		MouseEvent(G->pause, G->m);
		MouseEvent(G->replay, G->m);
		MouseEvent(G->exit, G->m);
		MouseEvent(G->record, G->m);
		MouseEvent(G->design, G->m);
		//MouseEvent(G->tiger, G->m);
		if(G->m.mkLButton){
		if( G->m.x > G->tiger->x + G->tiger->w){
			if(G->tiger->x + G->index * W > W * M * (PAGE - 1)){
				if(G->tiger->x < (W-1) * M){
					G->tiger->x += 5;
					G->cmd = CMD_MOVE;
				}
			}else{
				G->index++;
				G->cmd = CMD_MOVE;
			}
		}// 向右
		if( G->m.x > G->tiger->x &&  G->m.x < G->tiger->x + G->tiger->w &&  G->m.y > G->tiger->y + G->tiger->h){
			G->cmd = CMD_MOVE;
			if(G->tiger->y < W*N)G->tiger->y += 5;
		}// 向下
		if( G->m.x > G->tiger->x &&  G->m.x < G->tiger->x + G->tiger->w &&  G->m.y < G->tiger->y){
			G->cmd = CMD_MOVE;
			if(G->tiger->y > W*2)G->tiger->y -= 5;
		}// 向上
		}
	}
	if(G->start->OnClicked){
		G->cmd = CMD_START;
	}
	if(G->pause->OnClicked){
		G->cmd = CMD_PAUSE;
	}
	if (G->replay->OnClicked){
		G->cmd = CMD_REPLAY;
		G->index = 0;
		InitMap(G);
		InitRoles(G);
	}
	if(G->exit->OnClicked){
		G->cmd = CMD_EXIT;
	}
}// 鼠标事件
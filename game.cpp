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
}// ������Ϸ�ռ�

void InitImages()
{
	loadimage(&IMG_BARRIER, ".\\barrier.bmp", 20, 20, false);//����
	loadimage(&IMG_DIAMOND, ".\\diamond.bmp", 20, 20, false);//��ʯ
	loadimage(&IMG_RIVER, ".\\river.bmp", 40, 40, false);//����
	loadimage(&IMG_HILL, ".\\hill.bmp", 80, 80, false);//ɽ��
	loadimage(&IMG_SIDE, ".\\side.bmp", 40, 40, false);
	loadimage(&IMG_TIGER, ".\\Tiger.bmp", 40, 40, false);
	loadimage(&IMG_START, ".\\Start.bmp", 80, 20, false);
	loadimage(&IMG_PAUSE, ".\\Pause.bmp", 80, 20, false);
	loadimage(&IMG_REPLAY, ".\\replay.bmp", 80, 20, false);
	loadimage(&IMG_EXIT, ".\\Exit.bmp", 80, 20, false);
	loadimage(&IMG_DESIGN, ".\\design.bmp", 80, 20, false);
	loadimage(&IMG_RECORD, ".\\record.bmp", 80, 20, false);
}// ��ȡͼƬ��Դ

void InitResouses(Game *G)
{
	// ���
	G->side[0] = CreatePanel(0, 0, 680, 40, &IMG_SIDE);			// �ϱ߰�
	G->river = CreatePanel(0, 40, 680, 400, &IMG_RIVER);		// ����
	G->side[1] = CreatePanel(0, 440, 680, 40, &IMG_SIDE);		// �±߰�
	G->toolbar = CreatePanel(680, 0, 100, 480, &IMG_SIDE);		// ������
	// ��ť
	G->start = CreateButton(G->width - 100, 50, &IMG_START);	// ��ʼ��Ϸ
	G->pause = CreateButton(G->width - 100, 75, &IMG_PAUSE);	// ��ͣ��Ϸ
	G->replay = CreateButton(G->width - 100, 100, &IMG_REPLAY);	// ������Ϸ
	G->design = CreateButton(G->width - 100, 125, &IMG_DESIGN);	// ��Ƶ�ͼ
	G->record =  CreateButton(G->width - 100, 150, &IMG_RECORD);// ��¼��ͼ
	G->exit = CreateButton(G->width - 100, 175, &IMG_EXIT);		// �˳���Ϸ
	// ��ǩ
	G->info = CreateLable(G->width - 100, 240, "��Ϣ:");		// ��Ϣ
	setSize(G->info, 80, 20);
	G->player = CreateLable(G->width - 100, 265, "���:");		// ���
	setSize(G->player, 80, 20);
	G->score = CreateLable(G->width - 100, 290, "����:");		// ����
	setSize(G->score, 80, 20);
	G->lmax = CreateLable(G->width - 100, 315, "�ߴ�:");		// �ߴ�
	setSize(G->lmax, 80, 20);
}// ������Ϸ��Դ

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
}// ���ɵ�ͼ

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
}//��ȡ��ͼ

void InitRoles(Game *G)
{
	G->tiger = CreateTiger(0, 200, &IMG_TIGER);
	G->tiger->name = "Tiger";
}//��ʼ����ɫ

void InitGame(Game *G)
{
	InitImages();		//����ͼƬ
	InitResouses(G);	//���������Դ
	GenerateMap(G);		//���ɵ�ͼ
	InitMap(G);			//���ص�ͼ
	InitRoles(G);		//���ؽ�ɫ
	InputBox(G->player->text, 16, "��������ң�", "Dialog");
}//��ʼ����Ϸ

void SaveState(Game *G)
{

}//���浱ǰ״̬

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
}// �ͷ���Ϸ��Դ

void BeginGame(Game *G)
{
	srand(time(0));
	InitGame(G);
	initgraph(G->width, G->height); 
	while(G->cmd != CMD_EXIT){
		BeginBatchDraw();
		KeyEvent(G);			// ��������
		MouseEvent(G);			// ����¼�
		JudgeGame(G);			// ��Ϸ�з�
		NextGame(G);			// ��һ��
		UpdataGamePanel(G);		// ��ϷԪ��
		UpdataToolPanel(G);		// ������
		UpdateInfoPanel(G);		// ��ʾ��Ϣ
		FlushMouseMsgBuffer();
		FlushBatchDraw();
		EndBatchDraw();
		Sleep(25);
	}
	closegraph();
	FreeGame(G);
}// ��ʼ��Ϸ

void NextGame(Game *G)
{
	if(G->tiger->x < M*N && G->tiger->score > 0) return;
	G->tiger->x = M * N;
	if(G->tiger->score > G->maxscore){
		G->maxscore = G->tiger->score;
	}
	int result = MessageBox(GetHWnd(), TEXT("����"), TEXT("������YES / NO"), MB_YESNO);
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
	if (G->cmd == CMD_PAUSE || !G->cmd == CMD_MOVE)return false;//��ͣ���ǲ��ƶ��򲻸��½���
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
}// ��Ϸ�ж�

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
}// ��ʾ����

void UpdateInfoPanel(Game *G)
{
	sprintf(G->score->text, "����:%d", G->tiger->score);
	sprintf(G->lmax->text, "��߷�:%d", G->maxscore);
	display(G->info);
	display(G->player);
	display(G->score);
	display(G->lmax);
}// ��ʾ��ǩ

void UpdataGamePanel(Game *G)
{
	if (G->cmd == CMD_PAUSE || !G->cmd == CMD_MOVE)return;//��ͣ���ǲ��ƶ��򲻸��½���
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
	display(G->tiger);// ��ʾ��ɫ
}// ��ʾ��Ϸ����

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
}// �����¼�

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
		}// ����
		if( G->m.x > G->tiger->x &&  G->m.x < G->tiger->x + G->tiger->w &&  G->m.y > G->tiger->y + G->tiger->h){
			G->cmd = CMD_MOVE;
			if(G->tiger->y < W*N)G->tiger->y += 5;
		}// ����
		if( G->m.x > G->tiger->x &&  G->m.x < G->tiger->x + G->tiger->w &&  G->m.y < G->tiger->y){
			G->cmd = CMD_MOVE;
			if(G->tiger->y > W*2)G->tiger->y -= 5;
		}// ����
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
}// ����¼�
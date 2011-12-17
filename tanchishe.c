#define N 200 
#include<graphics.h>
#include<stdlib.h>
#include<dos.h>
#define LEFT 0x4b00 
#define RIGHT 0x4d00 
#define DOWN 0x5000 
#define UP 0x4800 
#define ESC 0x011b 
int i,key; 
int score=0;/*�÷�*/ 
int gamespeed=50000;/*��Ϸ�ٶ��Լ�����*/ 
struct Food 
{ 
int x;/*ʳ��ĺ�����*/ 
int y;/*ʳ���������*/ 
int yes;/*�ж��Ƿ�Ҫ����ʳ��ı���*/ 
}food;/*ʳ��Ľṹ��*/ 
struct Snake 
{ 
int x[N]; 
int y[N]; 
int node;/*�ߵĽ���*/ 
int direction;/*���ƶ�����*/ 
int life;/* �ߵ�����,0����,1����*/ 
}snake; 
void Init(void);/*ͼ������*/ 
void Close(void);/*ͼ�ν���*/ 
void DrawK(void);/*��ʼ����*/ 
void GameOver(void);/*������Ϸ*/ 
void GamePlay(void);/*����Ϸ�������*/ 
void PrScore(void);/*����ɼ�*/ 
/*������*/ 
void main(void) 
{ 
Init();/*ͼ������*/ 
DrawK();/*��ʼ����*/ 
GamePlay();/*����Ϸ�������*/ 
Close();/*ͼ�ν���*/ 
} 
/*ͼ������*/ 
void Init(void) 
{ 
int gd=DETECT,gm; 
initgraph(&gd,&gm,"c:\tc"); 
cleardevice(); 
} 
/*��ʼ���棬���Ͻ�����Ϊ��50��40�������½�����Ϊ��610��460����Χǽ*/ 
void DrawK(void) 
{ 
/*setbkcolor(LIGHTGREEN);*/ 
setcolor(11); 
setlinestyle(SOLID_LINE,0,THICK_WIDTH);/*��������*/ 
for(i=50;i<=600;i+=10)/*��Χǽ*/ 
{ 
rectangle(i,40,i+10,49); /*�ϱ�*/ 
rectangle(i,451,i+10,460);/*�±�*/ 
} 
for(i=40;i<=450;i+=10) 
{ 
rectangle(50,i,59,i+10); /*���*/ 
rectangle(601,i,610,i+10);/*�ұ�*/ 
} 
} 
/*����Ϸ�������*/ 
void GamePlay(void) 
{ 
randomize();/*�����������*/ 
food.yes=1;/*1��ʾ��Ҫ������ʳ��,0��ʾ�Ѿ�����ʳ��*/ 
snake.life=0;/*����*/ 
snake.direction=1;/*��������*/ 
snake.x[0]=100;snake.y[0]=100;/*��ͷ*/ 
snake.x[1]=110;snake.y[1]=100; 
snake.node=2;/*����*/ 
PrScore();/*����÷�*/ 
while(1)/*�����ظ�����Ϸ,ѹESC������*/ 
{ 
while(!kbhit())/*��û�а����������,���Լ��ƶ�����*/ 
{ 
if(food.yes==1)/*��Ҫ������ʳ��*/ 
{ 
food.x=rand()%400+60; 
food.y=rand()%350+60; 
while(food.x%10!=0)/*ʳ��������ֺ������ʳ���ܹ���������,�����ſ������߳Ե�*/ 
food.x++; 
while(food.y%10!=0) 
food.y++; 
food.yes=0;/*��������ʳ����*/ 
} 
if(food.yes==0)/*��������ʳ���˾�Ҫ��ʾ*/ 
{ 
setcolor(GREEN); 
rectangle(food.x,food.y,food.x+10,food.y-10); 
} 
for(i=snake.node-1;i>0;i--)/*�ߵ�ÿ��������ǰ�ƶ�,Ҳ����̰���ߵĹؼ��㷨*/ 
{ 
snake.x[i]=snake.x[i-1]; 
snake.y[i]=snake.y[i-1]; 
} 
/*1,2,3,4��ʾ��,��,��,���ĸ�����,ͨ������ж����ƶ���ͷ*/ 
switch(snake.direction) 
{ 
case 1:snake.x[0]+=10;break; 
case 2: snake.x[0]-=10;break; 
case 3: snake.y[0]-=10;break; 
case 4: snake.y[0]+=10;break; 
} 
for(i=3;i<snake.node;i++)/*���ߵĵ��Ľڿ�ʼ�ж��Ƿ�ײ���Լ��ˣ���Ϊ��ͷΪ���ڣ������ڲ����ܹչ���*/ 
{ 
if(snake.x[i]==snake.x[0]&&snake.y[i]==snake.y[0]) 
{ 
GameOver();/*��ʾʧ��*/ 
snake.life=1; 
break; 
} 
} 
if(snake.x[0]<55||snake.x[0]>595||snake.y[0]<55|| 
snake.y[0]>455)/*���Ƿ�ײ��ǽ��*/ 
{ 
GameOver();/*������Ϸ����*/ 
snake.life=1; /*����*/ 
} 
if(snake.life==1)/*���������ж��Ժ�,���������������ѭ�������¿�ʼ*/ 
break; 
if(snake.x[0]==food.x&&snake.y[0]==food.y)/*�Ե�ʳ���Ժ�*/ 
{ 
setcolor(0);/*�ѻ����ϵ�ʳ�ﶫ��ȥ��*/ 
rectangle(food.x,food.y,food.x+10,food.y-10); 
snake.x[snake.node]=-20;snake.y[snake.node]=-20; 
/*�µ�һ���ȷ��ڿ�������λ��,�´�ѭ����ȡǰһ�ڵ�λ��*/ 
snake.node++;/*�ߵ����峤һ��*/ 
food.yes=1;/*��������Ҫ�����µ�ʳ��*/ 
score+=10; 
PrScore();/*����µ÷�*/ 
} 
setcolor(4);/*������*/ 
for(i=0;i<snake.node;i++) 
rectangle(snake.x[i],snake.y[i],snake.x[i]+10, 
snake.y[i]-10); 
delay(gamespeed); 
setcolor(0);/*�ú�ɫȥ���ߵĵ����һ��*/ 
rectangle(snake.x[snake.node-1],snake.y[snake.node-1], 
snake.x[snake.node-1]+10,snake.y[snake.node-1]-10); 
} /*endwhile����kbhit��*/ 
if(snake.life==1)/*�������������ѭ��*/ 
break; 
key=bioskey(0);/*���հ���*/ 
if(key==ESC)/*��ESC���˳�*/ 
break; 
else 
if(key==UP&&snake.direction!=4) 
/*�ж��Ƿ����෴�ķ����ƶ�*/ 
snake.direction=3; 
else 
if(key==RIGHT&&snake.direction!=2) 
snake.direction=1; 
else 
if(key==LEFT&&snake.direction!=1) 
snake.direction=2; 
else 
if(key==DOWN&&snake.direction!=3) 
snake.direction=4; 
}/*endwhile(1)*/ 
} 
/*��Ϸ����*/ 
void GameOver(void) 
{ 
cleardevice(); 
PrScore(); 
setcolor(RED); 
settextstyle(0,0,4); 
outtextxy(200,200,"GAME OVER"); 
getch(); 
} 
/*����ɼ�*/ 
void PrScore(void) 
{ 
char str[10]; 
setfillstyle(SOLID_FILL,YELLOW); 
bar(50,15,220,35); 
setcolor(6); 
settextstyle(0,0,2); 
sprintf(str,"score:%d",score); 
outtextxy(55,20,str); 
} 
/*ͼ�ν���*/ 
void Close(void) 
{ 
getch(); 
closegraph(); 
}

#ifndef JUDGE_H_
#define JUDGE_H_

typedef struct Game Game;

//玩家状态
#define NORMAL 0
#define INHOSPITAL 1
#define INPRISON 2
#define Out 3

//空地上的道具种类
#define EMPTY 0
#define BARRIER 1
#define BOMB 2

int IsInPrison(struct Game* game);
int IsInHospital(struct Game* game);
int IsInMine(struct Game* game);
int IsInSpace(struct Game* game);
int IsInBomb(struct Game* game);
int IsBankrupt(struct Game* game);
#endif

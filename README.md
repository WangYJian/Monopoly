包含了有关地皮、破产、游戏结束的判别机制，包括以下函数：

int IsInPrison(struct Game* game);

int IsInHospital(struct Game* game);

int IsInMine(struct Game* game);

int IsInSpace(struct Game* game);

int IsInBomb(struct Game* game);

int JudgeStatus(struct Game* game);

int IsBankrupt(struct Game* game);

int IsGameOver(struct Game *game);
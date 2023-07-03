#ifndef DEVELOPMENT_GAME_H
#define DEVELOPMENT_GAME_H
#include "map.h"
#include "Player.h"
#include "Property.h"

// typedef struct Player Player;
// typedef struct Map Map;

#define MAP_SIZE 70 // 地图大小
#define PLAYERS_SIZE 4 //最大玩家人数
#define HOSPITAL 'H'    // hospital
#define TOOL 'T'        // tools
#define SPACE '0'       // space
#define GIFT 'G'        // gift house
#define MAGIC 'M'       // magic house
#define PRISON 'P'      // prison
#define MINERAL '$'     // mineral area
#define START 's'       // start area


// 定义游戏的结构体
typedef struct Game {
    Player* players[PLAYERS_SIZE]; // 游戏中的玩家
    int player_count; // 游戏中的玩家数量
    int init_cash; // 初始化资金
    Map* map[MAP_SIZE]; // 游戏地图
    int current_player_index; // 当前行动的玩家的索引
} Game;

void GameInitialize(struct Game* game);  // 初始化游戏
void GameAddPlayer(struct Game* game, struct Player* player);  // 向游戏添加玩家
void GameRemovePlayer(struct Game* game, int playerID);  // 从游戏中移除玩家
void GameStart(struct Game* game);  // 开始游戏
void GameEnd(struct Game* game);  // 结束游戏
void GameDisplayMap(const struct Game* game);  // 显示游戏地图
void GameRollDice(struct Game* game);  // 掷骰子

#endif

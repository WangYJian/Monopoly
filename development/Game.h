#ifndef DEVELOPMENT_GAME_H
#define DEVELOPMENT_GAME_H


typedef struct Player Player;
typedef struct Map Map;

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
#define NODICE -1 // 不需要外部输入色子
#define NOCOMMAND "NULL" // 没有指令
#define YES 1
#define NO 0
#define INPUTERROR -1
#define GAME_INPUT -1
// 定义游戏的结构体
typedef struct Game {
    Player* players[PLAYERS_SIZE]; // 游戏中的玩家
    int player_count; // 游戏中的玩家数量
    int init_cash; // 初始化资金
    Map* map[MAP_SIZE]; // 游戏地图
    int current_player_index; // 当前行动的玩家的索引
    char* output_file_path ;
    char* log_file_path ;
} Game;

Game* GameInitialize(int initcash,char* player_nums);  // 初始化游戏
void GameAddPlayer(struct Game* game, struct Player* player);  // 向游戏添加玩家
void GameRemovePlayer(struct Game* game, Player *player);  // 从游戏中移除玩家
Player* GameStart(struct Game* game);  // 开始游戏
Player* GamePlayerRound(struct Game* game,struct Player* player); // 进入某一个玩家的回合 然后询问玩家的操作,command用在测试人员中
int GameEnd(struct Game* game);  // 结束游戏
void GameDisplayMap(const struct Game* game);  // 显示游戏地图
Player* GameGetPlayerByName(const struct Game* game, char name); // 通过玩家name获取玩家
Player* GameRollDice(struct Game* game, int dice_num);  // 掷骰子
void GameTriggerEvent(struct Game* game, struct Player* player, int dice_num, int YesOrNo);  // 触发事件


#endif
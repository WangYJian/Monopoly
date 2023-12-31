#ifndef DEVELOPMENT_PLAYER_H
#define DEVELOPMENT_PLAYER_H

#define BANKRUPT -1
#define NORMAL 0
#define INHOSPITAL 1
#define INPRISON 2
#define Out 3


#define GIFT_CASH 2000
#define GIFT_POINTS 200
#define GIFT_GOD_ROUND 5

typedef struct Property Property;
typedef struct Tool Tool;
typedef struct Map Map;

// 定义玩家的结构体
typedef struct Player {
    char name; // 玩家名称
    int id; // 玩家ID
    int points; // 玩家积分
    int cash; // 玩家现金
    int status; // 玩家状态：如正常、住院、坐牢等
    int stop_rounds; // 停留在医院或监狱的回合数
    int position; // 玩家在地图上的位置
    int god_rounds; // 财神回合数
    // 炸弹、路障、机器娃娃

    // Tool* bomb[10];
    Tool* barrier[10];
    Tool* robot[10];
    // 对应的道具数量、
    // int bomb_count;
    int barrier_count;
    int robot_count;
} Player;

// 方法
void PlayerInitialize(struct Player* player, int playerID, int cash, int points);  // 初始化玩家
void PlayerMove(struct Player* player, int steps);  // 玩家移动一定的步数
void PlayerBuyProperty(struct Player* player, Property *property);  // 玩家购买物业
void PlayerUpgradeProperty(struct Player* player, Property *property);  // 玩家升级物业
void PlayerSellProperty(struct Player* player, Property *property);  // 玩家出售物业
void PlayerPayRent(struct Player* player, int amount);  // 玩家支付租金
void PlayerReceiveRent(struct Player* player, int amount);  // 玩家接收租金
void PlayerBuyTool(struct Player* player, int toolID);  // 玩家购买道具
void PlayerUseBombOrBarrier(struct Player* player, int toolID, Map *map);  // 玩家使用炸弹或路障
void PlayerGoBankrupt(struct Player* player);  // 玩家破产
void PlayerDisplayInfo(const struct Player* player);  // 显示玩家信息
void PlayerGetBomb(struct Player* player); // 获取炸弹
void PlayerGetBarrier(struct Player* player); // 获取路障
void PlayerGetRobot(struct Player* player); // 获取机器娃娃
void PlayerGiftHouse(struct Player* player);  //玩家遇到礼品屋
void PlayerMineral(struct Player* player);   //玩家遇到矿地
void PlayerTool(struct Player* player);
void PlayerPrison(struct Player* player);
void PlayerMagic(struct Player* player); // 玩家在魔法屋能做的事情
void PlayerHelp(); // 帮助文档

#endif

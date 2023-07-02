#ifndef DEVELOPMENT_PLAYER_H
#define DEVELOPMENT_PLAYER_H

// 定义玩家的结构体
typedef struct Player {
    char name[50]; // 玩家名称
    int id; // 玩家ID
    int points; // 玩家积分
    int cash; // 玩家现金
    int status; // 玩家状态：如正常、住院、坐牢等
    int position; // 玩家在地图上的位置
    struct Property* properties; // 玩家拥有的土地
    struct Tool* tools; // 玩家拥有的道具
} Player;

// 方法
void PlayerInitialize(struct Player* player, int playerID, int cash, int points);  // 初始化玩家
void PlayerMove(struct Player* player, int steps);  // 玩家移动一定的步数
void PlayerBuyLand(struct Player* player, int landID);  // 玩家购买土地
void PlayerUpgradeProperty(struct Player* player, int propertyID);  // 玩家升级物业
void PlayerSellProperty(struct Player* player, int propertyID);  // 玩家出售物业
void PlayerPayRent(struct Player* player, int amount);  // 玩家支付租金
void PlayerReceiveRent(struct Player* player, int amount);  // 玩家接收租金
void PlayerBuyTool(struct Player* player, int toolID);  // 玩家购买道具
void PlayerUseTool(struct Player* player, int toolID, int targetLocation);  // 玩家使用道具
void PlayerGoBankrupt(struct Player* player);  // 玩家破产
void PlayerDisplayInfo(const struct Player* player);  // 显示玩家信息

#endif

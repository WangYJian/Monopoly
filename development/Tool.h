#ifndef DEVELOPMENT_TOOL_H
#define DEVELOPMENT_TOOL_H

#define NOTOOL 0
#define BARRIER 1
#define ROBOT 2
#define BOMB 3

#define BARRIER_POINTS 50
#define ROBOT_POINTS 30
#define BOMB_POINTS 50

typedef struct Player Player;
// 定义道具的结构体
typedef struct Tool {
    int id; // 道具ID
    char name[50]; // 道具名称
    int points; // 道具所需积分
    Player* owner; // 道具的拥有者
} Tool;


// 方法
void ToolInitialize(struct Tool* tool, int toolID, const char* name, int points, Player* owner);  // 初始化道具
Tool *BombInitialize(Player *owner); // 初始化炸弹
Tool *BarrierInitialize(Player *owner); // 初始化路障
Tool *RobotInitialize(Player *owner); // 初始化机器娃娃
void ToolActivate(struct Tool* tool, int playerID, int targetLocation);  // 激活道具
void ToolDeactivate(struct Tool* tool);  // 禁用道具


#endif

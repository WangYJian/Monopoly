#include "Tool.h"
#include "Player.h"
#include <string.h>
#include <stdlib.h>

// 初始化道具
void ToolInitialize(struct Tool* tool, int toolID, const char* name, int points, Player* owner){
    tool->id = toolID;
    strcpy(tool->name, name);
    tool->points = points;
    tool->owner = owner;
}

// 初始化炸弹
Tool *BombInitialize(Player *owner){
    Tool *bomb = (Tool *)malloc(sizeof(Tool));
    ToolInitialize(bomb, BOMB, "bomb", BOMB_POINTS, owner);
    return bomb;
}

// 初始化路障
Tool *BarrierInitialize(Player *owner){
    Tool *barrier = (Tool *)malloc(sizeof(Tool));
    ToolInitialize(barrier, BARRIER, "barrier", BARRIER_POINTS, owner);
    return barrier;
}

// 初始化机器娃娃
Tool *RobotInitialize(Player *owner){
    Tool *robot = (Tool *)malloc(sizeof(Tool));
    ToolInitialize(robot, ROBOT, "robot", ROBOT_POINTS, owner);
    return robot;
}
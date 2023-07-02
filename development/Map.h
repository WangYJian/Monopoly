#ifndef DEVELOPMENT_MAP_H
#define DEVELOPMENT_MAP_H

#include "Property.h"
#include "Tool.h"
#include "Player.h"

// 定义地图单元的结构体
typedef struct Map {
    int id; // 地图单元ID
    Property* property; // 如果有土地，土地的信息
    Tool* tool; // 如果有道具，道具的信息
    Player* player; // 如果有玩家，玩家的信息
} Map;

#endif

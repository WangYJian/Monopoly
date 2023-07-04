#ifndef DEVELOPMENT_MAP_H
#define DEVELOPMENT_MAP_H



typedef struct Property Property;
typedef struct Tool Tool;
typedef struct Player Player;

// 定义地图单元的结构体
typedef struct Map {
    int id; // 地图单元ID
    char land_type; //地图的样式
    int is_tool; // 是否存放道具 0 无道具，1 防止路障
    int player_nums; // 玩家数量
    Property* property; // 如果有土地，土地的信息
    Tool* tool; // 如果有道具，道具的信息
    Player* player[4]; // 如果有玩家，玩家的信息
}Map;

#endif

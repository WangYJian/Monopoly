#ifndef DEVELOPMENT_MAP_H
#define DEVELOPMENT_MAP_H

// 定义游戏地图的结构体
typedef struct Map {
    struct MapCell* cells; // 地图单元
    int size; // 地图大小
} Map;


#endif

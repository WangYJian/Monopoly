#include "Game.h"
#include <stdio.h>
#include <malloc.h>
void GameInitialize(struct Game* game){
    /*
    初始化游戏的函数要求，game已经在外部malloc
    1. 询问人数
    2. 初始化最开始游玩的玩家索引
    3. 初始化地图的数据
    */
    int i = 0;
    printf("请输入玩家人数：");
    scanf("%d", &game->current_player_index);
    printf("地图初始化中\n");
    for(i = 0; i < MAP_SIZE; i++){
        game->map[i] = malloc(sizeof(struct Map));
        game->map[i]->id = i;
        if(i == 0){
            game->map[i]->land_type = START;
            continue;
        }
        if(i < 14){
            game->map[i]->land_typt = SPACE;
            continue;
        }
        if(i == 14){

        }
        
    }
    printf("初始化完成！\n");
}

void GameStart(struct Game* game){
    /*
    开始游戏
    1. 添加人物
    2. 打印地图
    3. 进入第一个玩家回合
    */
}

void GameDisplayMap(const struct Game* game){
    /*
    仅仅显示地图
    1. 注意显示覆盖的优先级
    */
}
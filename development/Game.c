#include "Game.h"
#include "map.h"
#include "Player.h"
#include "Property.h"
#include <stdio.h>
#include <malloc.h>
Game* GameInitialize(int initcash,int player_nums){
    /*
    初始化游戏的函数要求，game已经在外部malloc
    1. 询问人数
    2. 初始化最开始游玩的玩家索引
    3. 初始化地图的数据
    */
    int i = 0;
    Property* temp = NULL;
    struct Game* game = malloc(sizeof(Game));
    game->init_cash = initcash;
    game->player_count = player_nums;
    game->current_player_index = 0;
    printf("初始化地图 ...\n");
    for(i = 0; i < MAP_SIZE; i++){
        game->map[i] = malloc(sizeof(Map));
        game->map[i]->id = i;
        game->map[i]->player = NULL;
        //初始化地皮
        temp = malloc(sizeof(Property));
        temp->id = i;
        temp->level = 0;
        temp->owner = NULL;
        // TODO price 和 rent 的初始化
        game->map[i]->property = temp;
        if(i == 0){
            game->map[i]->land_type = START;
        }else if(i < 14){
            game->map[i]->land_type = SPACE;
            continue;
        }else if(i == 14){
            game->map[i]->land_type = HOSPITAL;
        }else if(i < 28){
            game->map[i]->land_type = SPACE;
        }else if(i == 28){
            game->map[i]->land_type = TOOL;
        }else if(i < 35){
            game->map[i]->land_type = SPACE;
        }else if(i == 35){
            game->map[i]->land_type = GIFT;
        }else if(i < 49){
            game->map[i]->land_type = SPACE;
        }else if(i == 49){
            game->map[i]->land_type = PRISON;
        }else if(i < 63){
            game->map[i]->land_type = SPACE;
        }else if(i == 63){
            game->map[i]->land_type = MAGIC;
        }else if(i< 70){
            game->map[i]->land_type = MINERAL;
        }
    }
    printf("地图加载完成! \n");
    //system("cls");
    return game;

    
}

void GameStart(struct Game* game){
    /*
    开始游戏
    1. 添加人物
    2. 进入第一个玩家回合
    */
    int i = 0;
    char name[4] = {'A','Q','S','J'};
    for(i = 0; i < game->player_count; i++){
        game->players[i] = malloc(sizeof(Player));
        game->players[i]->bomb_count = 0;
        game->players[i]->barrier_count = 0;
        game->players[i]->robot_count = 0;
        game->players[i]->god_count = 0;
        game->players[i]->status = 0;
        game->players[i]->stop_rounds = 0;
        game->players[i]->position = 0;
        game->players[i]->cash = game->init_cash;
        game->players[i]->name = name[i];
        game->players[i]->id = i;
        game->players[i]->points = 0;
    }
    GameDisplayMap(game);
    // TODO 进入玩家回合
}
char level_char(int level){
    char ch;
    switch (level)
    {
    case 0:
        ch = '0';
        break;
    case 1:
        ch = '1';
        break;
    case 2:
        ch = '2';
        break;
    
    case 3:
        ch = '3';
        break;
    }
    return ch;
}
char Tool_char(int idx){
    char ch;
    switch (idx)
    {
    case 1:
        ch = '#';
        break;
    case 2:
        ch = '@';
        break;
    default:
        ch = '0';
        break;
    }
    return ch;
}

void GameDisplayMap(const struct Game* game){
    /*
    仅仅显示地图
    1. 注意显示覆盖的优先级
    2. 地皮颜色，todo
    编程逻辑
    先将对应字符放到二维数组对应的位置，然后将这些位置打印
    */
    int i = 0;
    int j = 0;
    char drawmap[8][30];
     for(i = 0; i < 8; i++){
        for(j = 0; j < 30; j++){
            drawmap[i][j] = ' ';
        }
    }
    // 这里打印第一行，其中除了14号，都可以有道具
    for(i = 0; i < 29; i++){
        if(game->map[i]->player != NULL){
            drawmap[0][i] = game->map[i]->player->name;
        }else if(game->map[i]->land_type == SPACE && game->map[i]->is_tool)
            drawmap[0][i] = Tool_char(game->map[i]->is_tool);
        else if(game->map[i]->land_type == SPACE && !game->map[i]->property->level){
            drawmap[0][i] = level_char(game->map[i]->property->level);
        }
        else 
            drawmap[0][i] = game->map[i]->land_type;
    }
    for(i = 0; i < 8; i++)
        drawmap[i][29] = '\n';

    // 打印右边，
    for(i = 0; i < 8; i++){
        if(game->map[28+i]->player != NULL){
            drawmap[i][28] = game->map[28+i]->player->name;
        }else if(game->map[28+i]->is_tool && game->map[28+i]->land_type == SPACE)
            drawmap[i][28] = Tool_char(game->map[28+i]->is_tool);
        else if(!game->map[28+i]->property->level && game->map[28+i]->land_type == SPACE)
            drawmap[i][28] = level_char(game->map[28+i]->property->level);
        else
            drawmap[i][28] = game->map[28+i]->land_type;
    }

    //打印下边
    for(i = 28; i >=0; i--){
        j = 28 - i;
        if(game->map[35+j]->player != NULL){
            drawmap[7][i] = game->map[35+j]->player->name;
        }else if(game->map[35+j]->land_type == SPACE && game->map[35+j]->is_tool)
            drawmap[7][i] = Tool_char(game->map[35+j]->is_tool);
        else if(game->map[35+j]->land_type == SPACE && !game->map[35+j]->property->level)
            drawmap[7][i] = level_char(game->map[35+j]->property->level);
        else
            drawmap[7][i] = game->map[35+j]->land_type;
    }

    // 打印左边,矿区不能够买地皮，所以只需要管一部分
    for(i = 6; i >= 1;i--){
        j = 7 - i;
        if(game->map[63+j]->player != NULL){
            drawmap[i][0] = game->map[63+j]->player->name;
        }else if(game->map[63+j]->land_type == SPACE && game->map[63+j]->is_tool)
            drawmap[i][0] = Tool_char(game->map[63+j]->is_tool);
        else
            drawmap[i][0] = game->map[63+j]->land_type;
    }


    for(i = 0; i < 8; i++){
        for(j = 0; j < 30; j++){
            printf("%c",drawmap[i][j]);
        }
    }
        
    
}
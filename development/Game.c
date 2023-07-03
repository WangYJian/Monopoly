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
    game->current_player_index = 0;
    printf("请输入玩家人数：");
    scanf("%d", &game->player_count);
    printf("请输入期望的初始化资金：");
    scanf("%d",&game->init_cash);
    printf("地图初始化中\n");
    for(i = 0; i < MAP_SIZE; i++){
        game->map[i] = malloc(sizeof(Map));
        game->map[i]->id = i;
        game->map[i]->is_player = -1;
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
    printf("初始化完成！\n");
    system("cls");
    GameStart(game);

    
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
char PlayerChar(int idx){
    char ch;
    switch (idx)
    {
    case 0:
        ch = 'A';
        break;
    case 1:
        ch = 'Q';
        break;
    case 2:
        ch = 'S';
        break;
    
    case 3:
        ch = 'J';
        break;
    }
    return ch;
}
void GameDisplayMap(const struct Game* game){
    /*
    仅仅显示地图
    1. 注意显示覆盖的优先级
    编程逻辑
    先将对应字符放到二维数组对应的位置，然后将这些位置打印
    */
    int i = 0;
    
    char drawmap[8][30];
    // 这里打印第一行，其中除了14号，都可以有道具
    for(i = 0; i < 29; i++){
        if(game->map[i]->is_player != -1){
            drawmap[0][i] = PlayerChar(game->map[i]->is_player);
        }else if(game->map[i]->land_type == SPACE && game->map[i]->is_tool)
            drawmap[0][i] = Tool_char(game->map[i]->is_tool)
        else
            drawmap[0][i] = game->map[i]->land_type;
    }
    for(i = 0; i < 8; i++)
        drawmap[i][29] = '\n';

    // 打印右边，
    for(i = 0; i < 8; i++){
        if(game->map[28+i]->is_player != -1){
            drawmap[i][28] = PlayerChar(game->map[28+i]->is_player);
        }else if(game->map[28+i]->is_tool && game->map[28+i]->land_type == SPACE)
            drawmap[i][28] = Tool_char(game->map[28+i]->is_tool);
        else
            drawmap[i][28] = game->map[28+i]->land_type;
    }

    //打印下边
    for(i = 28; i >=0; i--){
        int j = 28 - i;
        if(game->map[35+j]->is_player != -1){
            drawmap[7][i] = PlayerChar(game->map[35+j]->is_player);
        }else if(game->map[35+j]->land_type == SPACE && game->map[35+j]->is_tool)
            drawmap[7][i] = Tool_char(game->map[35+j]->is_tool);
        else
            drawmap[7][i] = game->map[35+j]->land_type;
    }

    // 打印左边
    for(i = 6; i >= 0;i--){
        int j = 6 - i;
        if(game->map[63+j]->is_player != -1){
            drawmap[i][0] = PlayerChar(game->map[63+j]->is_player);
        }else if(game->map[63+j]->land_type == SPACE && game->map[63+j]->is_tool)
            drawmap[i][0] = Tool_char(game->map[63+j]->is_tool);
        else
            drawmap[i][0] = game->map[63+j]->land_type;
    }

    int j = 0;
    for(i = 0; i < 8; i++){
        for(j = 0; j < 30; j++){
            printf("%c",drawmap[i][j]);
        }
    }
        
    
}
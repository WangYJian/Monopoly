#include "Game.h"
#include "map.h"
#include "Tool.h"
#include "Player.h"
#include "Property.h"
#include <stdio.h>
#include<string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
char player_char(char num);

Game* GameInitialize(int initcash,char* player_nums){
    /*
    初始化游戏的函数要求，game已经在外部malloc
    1. 询问人数
    2. 初始化最开始游玩的玩家索引
    3. 初始化地图的数据
    */
    int i = 0;
    char name[4] = {'A','Q','S','J'};
    Property* temp = NULL;
    struct Game* game = malloc(sizeof(Game));
    game->init_cash = initcash;
    game->player_count = strlen(player_nums);
    printf("初始化地图 ...\n");
    for(i = 0; i < MAP_SIZE; i++){
        game->map[i] = malloc(sizeof(Map));
        game->map[i]->id = i;
        game->map[i]->player = NULL;
        game->map[i]->tool = NULL;
        game->map[i]->is_tool = 0;
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
            game->map[i]->property = PropertyInitialize(i, 100); // 初始化地皮
            game->map[i]->land_type = SPACE;
            continue;
        }else if(i == 14){
            game->map[i]->land_type = HOSPITAL;
        }else if(i < 28){
            game->map[i]->property = PropertyInitialize(i, 100); // 初始化地皮
            game->map[i]->land_type = SPACE;
        }else if(i == 28){
            game->map[i]->land_type = TOOL;
        }else if(i < 35){
            game->map[i]->property = PropertyInitialize(i, 500); // 初始化地皮
            game->map[i]->land_type = SPACE;
        }else if(i == 35){
            game->map[i]->land_type = GIFT;
        }else if(i < 49){
            game->map[i]->property = PropertyInitialize(i, 300); // 初始化地皮
            game->map[i]->land_type = SPACE;
        }else if(i == 49){
            game->map[i]->land_type = PRISON;
        }else if(i < 63){
            game->map[i]->property = PropertyInitialize(i, 300); // 初始化地皮
            game->map[i]->land_type = SPACE;
        }else if(i == 63){
            game->map[i]->land_type = MAGIC;
        }else if(i< 70){
            game->map[i]->land_type = MINERAL;
        }
    }
    printf("地图加载完成! \n");
    game->current_player_index = 0; // 这游戏开始确定当前回合的id
    for(i = 0; i < game->player_count; i++){
        game->players[i] = malloc(sizeof(Player));
        game->players[i]->bomb_count = 0;
        game->players[i]->barrier_count = 0;
        game->players[i]->robot_count = 0;
        game->players[i]->god_rounds = 0;
        game->players[i]->status = 0;
        game->players[i]->stop_rounds = 0;
        game->players[i]->position = 0;
        game->players[i]->cash = game->init_cash;
        game->players[i]->name = player_char(player_nums[i]);
        game->players[i]->id = i;
        game->players[i]->points = 0;
        // TODO 玩家的工具和其他指针的初始化
    }
    //system("cls");
    return game;

    
}

Player* GameStart(struct Game* game){
    /*
    开始游戏
    1. 添加人物
    2. 进入第一个玩家回合
    */

    GameDisplayMap(game);
    return game->players[0]; // 进入第一个玩家的回合,也就是返回这个玩家指针，放到roll里面
    // TODO 进入玩家回合
}
char player_char(char num){
    char ch;
    switch (num)
    {
    case '0':
        ch = 'A';
        break;
    case '1':
        ch = 'Q';
        break;
    case '2':
        ch = 'S';
        break;
    
    case '3':
        ch = 'J';
        break;
    }
    
    return ch;
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

// 通过名字获取玩家
Player* GameGetPlayerByName(const struct Game* game, char name){
    int i = 0;
    for(i = 0; i < 4; i++){
        if(game->players[i]->name == name)
            return game->players[i];
    }
    return NULL;
}

Player* GameRollDice(struct Game* game, int dice_num){
    int actual_num = 0;
    int i = 0,player_id = game->current_player_index;
    
    int pos_in_map = 0; // 也就是玩家从此出发偏移量
    Player* cur_player = game->players[player_id];
    // 判断轮空
    if(cur_player->stop_rounds != 0){
        printf("当前你(%c)还处于轮空状态，无法行动，进入下一个玩家回合\n",cur_player->name);
        cur_player->stop_rounds--;
        game->current_player_index = (++game->current_player_index)%4;
        player_id = game->current_player_index;
        return game->players[player_id]; // 返回下一个玩家
    }

    //投掷色子
    if(dice_num == NODICE)
        actual_num = dice_num;
    else{
        srand((unsigned)time( NULL ) );
        actual_num = rand()%6+1;
        printf("当前你色子的点数为: %d\n",actual_num);
    }
    // 下面只写了投色子之后需要走的步数，后序还需要添加一个读取指令的东西

    for(i = 0; i < actual_num; i++){
        pos_in_map = cur_player->position;
        //TODO 如果玩家有娃娃，可以无视路径上的障碍，直接到达
        
         // 这里只考虑路障和炸弹
        switch(game->map[pos_in_map+i]->is_tool)
        {
        case 0: // 啥都没有 TODO 考虑特殊地皮
            break;
        case 1: // 有路障
        {
            game->map[pos_in_map+i]->is_tool = 0; // 踩掉了
            free(game->map[pos_in_map+i]->tool);
            game->map[pos_in_map+i]->tool = NULL;
            cur_player->position += i;
            break;
        }
        case 2: // 有炸弹
        {
            game->map[pos_in_map+i]->is_tool = 0;
            free(game->map[pos_in_map+i]->tool); // 删掉地图上的道具信息
            game->map[pos_in_map+i]->tool = NULL;
            cur_player->position = 14; // 进入医院
            cur_player->stop_rounds += 3; // 添加轮空
            break;
        }
        }
    }
    game->map[cur_player->position]->player = cur_player; // 在地图的位置上更新玩家显示
    GameDisplayMap(game); // 从新打印地图
    printf("你(%c)已经到达相应的位置，接下来请输入你需要进行的操作：\n",cur_player->name);
    return cur_player; // 这个玩家投完色子之后，返回当前玩家
}

Player* GamePlayerRound(struct Game* game,struct Player* player,const char command[16]){
    if(player == NULL || game == NULL){
        printf("NULL ptr!!");
        return NULL;
    }
    Player* player_next = NULL;
    char real_command[16];
    int symbol = 0;
    int num[2] = {0},i = 0,j = 0;
    char ch;
    int loop = 1;
    while(loop){
        if(command != NULL){
            strcpy(real_command,command);
            loop = 0;
        }
        else{
            printf("%c> ", player->name);
            i = 0;
            symbol = 0;
            while(ch = getchar()!= '\n'){
                if(ch >= '0'&& ch <= '9'){
                    num[i] = ch -48;
                    i++;
                    continue;
                }else if(ch == '-')
                    symbol = 1;
                else{
                    if(ch == ' '){
                        continue;
                    }
                    else{
                        real_command[j++] = ch;
                    }
                }
            }
            real_command[j] = '\0';
        
        }
        if(player->stop_rounds == 0){
            if(strcmp(real_command,"query") == 0)
                PlayerDisplayInfo(player);
            else if(strcmp(real_command,"roll") == 0){
                GameRollDice(game,NODICE);

            }else if(strcmp(real_command,"bomb") == 0){
                int pos_for_tool = 0,tool_place = 0;
                Tool* temp;
                if(num[0]&&num[1]){
                    pos_for_tool = num[0]*10 + num[1];
                }else
                    pos_for_tool = num[0]+ num[1];
                if(symbol){
                    pos_for_tool = -pos_for_tool;
                }
                tool_place = (player->position + pos_for_tool + MAP_SIZE)%MAP_SIZE;
                
                // 使用toolactivate？
            
                temp = malloc(sizeof(Tool));
                temp->id = 3;
                strcpy(temp->name,"bomb");
                temp->points = 50;
                temp->owner = player;
                player->bomb[player->bomb_count++] = temp;

                game->map[tool_place]->is_tool = 1;
                game->map[tool_place]->tool = temp; // 这里直接通过配合bomb——count和bomb来实现？，或者这个炸弹都初始化为空
            }
        }else{
            // TODO 当权处于轮空状态
            printf("你当前处于轮空状态！");
            player_next = GameRollDice(game,NODICE);
                
        }
    }
    return player_next;
}
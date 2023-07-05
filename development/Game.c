#include "Game.h"
#include "Map.h"
#include "Tool.h"
#include "Player.h"
#include "Property.h"
#include <stdio.h>
#include<string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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
        if(i == 0)
            game->map[i]->player_nums = game->player_count;
        else
            game->map[i]->player_nums = 0;
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
            game->map[i]->land_type = SPACE;
            game->map[i]->property->price = 200;
        }else if(i == 14){
            game->map[i]->land_type = HOSPITAL;
        }else if(i < 28){
            game->map[i]->land_type = SPACE;
            game->map[i]->property->price = 200;
        }else if(i == 28){
            game->map[i]->land_type = TOOL;
        }else if(i < 35){
            game->map[i]->land_type = SPACE;
            game->map[i]->property->price = 500;
        }else if(i == 35){
            game->map[i]->land_type = GIFT;
        }else if(i < 49){
            game->map[i]->land_type = SPACE;
            game->map[i]->property->price = 300;
        }else if(i == 49){
            game->map[i]->land_type = PRISON;
        }else if(i < 63){
            game->map[i]->land_type = SPACE;
            game->map[i]->property->price = 300;
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
        game->players[i]->status = NORMAL;
        game->players[i]->stop_rounds = 0;
        game->players[i]->position = 0;
        game->players[i]->cash = game->init_cash;
        game->players[i]->name = player_char(player_nums[i]);
        game->players[i]->id = i;
        game->players[i]->points = 0;
        game->map[0]->player[i] = game->players[i];
        // TODO 玩家的工具和其他指针的初始化
    }
    // printf("final");
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
int GameEnd(struct Game* game){
    return 1;
}
char player_char(char num){
    char ch;
    switch (num)
    {
    case '1':
        ch = 'A';
        break;
    case '2':
        ch = 'Q';
        break;
    case '3':
        ch = 'S';
        break;
    
    case '4':
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

void GameDisplayMap(const struct Game* game) {
    /*
    仅仅显示地图
    1. 注意显示覆盖的优先级
    2. 地皮颜色，todo
    编程逻辑
    先将对应字符放到二维数组对应的位置，然后将这些位置打印
    */
    int i = 0;
    int j = 0;
    int player_on_map = 0;
    char drawmap[8][30];
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 30; j++) {
            drawmap[i][j] = ' ';
        }
    }
    // 这里打印第一行，其中除了14号，都可以有道具
    for (i = 0; i < 29; i++) {
        player_on_map = game->map[i]->player_nums;
        if (player_on_map != 0) {
            drawmap[0][i] = game->map[i]->player[player_on_map - 1]->name; // 需要删除玩家，走出去了
        } else if (game->map[i]->land_type == SPACE && game->map[i]->is_tool)
            drawmap[0][i] = Tool_char(game->map[i]->is_tool);
        else if (game->map[i]->land_type == SPACE && !game->map[i]->property->level) {
            drawmap[0][i] = level_char(game->map[i]->property->level);
        } else
            drawmap[0][i] = game->map[i]->land_type;
    }
    for (i = 0; i < 8; i++)
        drawmap[i][29] = '\n';

    // 打印右边，

    for (i = 0; i < 8; i++) {
        player_on_map = game->map[28 + i]->player_nums;
        if (player_on_map != 0) {
            drawmap[i][28] = game->map[28 + i]->player[player_on_map - 1]->name;
        } else if (game->map[28 + i]->is_tool && game->map[28 + i]->land_type == SPACE)
            drawmap[i][28] = Tool_char(game->map[28 + i]->is_tool);
        else if (!game->map[28 + i]->property->level && game->map[28 + i]->land_type == SPACE)
            drawmap[i][28] = level_char(game->map[28 + i]->property->level);
        else
            drawmap[i][28] = game->map[28 + i]->land_type;
    }

    //打印下边
    for (i = 28; i >= 0; i--) {
        j = 28 - i;
        player_on_map = game->map[35 + j]->player_nums;
        if (player_on_map != 0) {
            drawmap[7][i] = game->map[35 + j]->player[player_on_map-1]->name;
        } else if (game->map[35 + j]->land_type == SPACE && game->map[35 + j]->is_tool)
            drawmap[7][i] = Tool_char(game->map[35 + j]->is_tool);
        else if (game->map[35 + j]->land_type == SPACE && !game->map[35 + j]->property->level)
            drawmap[7][i] = level_char(game->map[35 + j]->property->level);
        else
            drawmap[7][i] = game->map[35 + j]->land_type;
    }

    // 打印左边,矿区不能够买地皮，所以只需要管一部分
    for (i = 6; i >= 1; i--) {
        j = 7 - i;
        player_on_map = game->map[63 + j]->player_nums;
        if (player_on_map != 0) {
            drawmap[i][0] = game->map[63 + j]->player[player_on_map-1]->name;
        } else if (game->map[63 + j]->land_type == SPACE && game->map[63 + j]->is_tool)
            drawmap[i][0] = Tool_char(game->map[63 + j]->is_tool);
        else
            drawmap[i][0] = game->map[63 + j]->land_type;
    }


    for (i = 0; i < 8; i++) {
        for (j = 0; j < 30; j++) {
            printf("%c", drawmap[i][j]);
        }
    }
}

// 通过名字获取玩家
Player* GameGetPlayerByName(const struct Game* game, char name){
    int i = 0;
    for(i = 0; i < game->player_count; i++){
        if(game->players[i]->name == name)
            return game->players[i];
    }
    return NULL;
}

Player* GameRollDice(struct Game* game, int dice_num){
    int actual_num = 0;
    int i = 0,player_id = game->current_player_index;
    
    int pos_in_map = 0,pos_next_map = 0; // 也就是玩家从此出发偏移量
    Player* cur_player = game->players[player_id];
    Map* cur_map = NULL, *pre_map = NULL;
    // 判断轮空
    if(cur_player->stop_rounds != 0){
        printf("当前你(%c)还处于轮空状态，无法行动，进入下一个玩家回合\n",cur_player->name);
        cur_player->stop_rounds--;
        game->current_player_index = (++game->current_player_index)%4;
        player_id = game->current_player_index;
        return game->players[player_id]; // 返回下一个玩家
    }
    
    //投掷色子
    if(dice_num != NODICE)
        actual_num = dice_num;
    else{
        srand((unsigned)time( NULL ));
        actual_num = rand()%6+1;
        printf("当前你色子的点数为: %d\n",actual_num);
    }
    // 下面只写了投色子之后需要走的步数，后序还需要添加一个读取指令的东西
    pos_in_map = cur_player->position;
    pos_next_map =cur_player->position + actual_num; // 这里进行一个初始化，然后后面要是又特殊的情况就修改
    for(i = 0; i < actual_num; i++) {
        pos_next_map = pos_in_map + i+1;
        //TODO 如果玩家有娃娃，可以无视路径上的障碍，直接到达
        cur_map = game->map[pos_next_map];

        // 这里只考虑路障和炸弹
        // TODO 一个地皮上有道具了就不能放了
        switch (cur_map->is_tool) {
            case NOTOOL: // 啥都没有 TODO 考虑特殊地皮
                break;


            case BARRIER: // 有路障
            {
                cur_map->is_tool = 0; // 踩掉了
                free(cur_map->tool);
                cur_map->tool = NULL;
                pos_next_map = i + 1;
                break;
            }
            case BOMB: // 有炸弹
            {
                //  添加status
                cur_player->status = INHOSPITAL;
                cur_map->is_tool = 0;
                free(cur_map->tool); // 删掉地图上的道具信息
                cur_map->tool = NULL;
                pos_next_map = 14; // 进入医院
                cur_player->stop_rounds += 3; // 添加轮空
                break;
            }
        }
        // TODO 处理特殊地皮 ,继续使用cur_map
        // cur_map = game->map[pos_next_map]; // 玩家下一个位置
        // TODO 下面的玩家需要把踩到的地图块更新上面的玩家
        switch (cur_map->land_type) {
            case MINERAL: {
                PlayerMineral(cur_player);
                break;
            }
            case MAGIC: {
                PlayerMagic(cur_player);
                break;
            }
            case TOOL: {
                PlayerTool(cur_player);
                break;
            }
            case GIFT: {
                PlayerGiftHouse(cur_player);
                break;
            }
            default: // 其他不作处理
                break;
        }
    }
    // 添加玩家
    pre_map = game->map[pos_in_map];
    cur_player->position = pos_next_map;
    cur_map = game->map[pos_next_map];
    // printf("%d\n",pos_in_map);
    // TODO 下面的玩家需要把踩到的地图块更新上面的玩家
    AddPlayerMap(cur_map,cur_player); // 采用队列的形式添加
    DelPlayerMap(pre_map,cur_player); // 在之前地图上删掉这个玩家
    //game->map[cur_player->position]->player[] = cur_player; // 在地图的位置上更新玩家显示
    GameDisplayMap(game); // 从新打印地图
    printf("你(%c)已经到达相应的位置。\n",cur_player->name);
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
    int num[2] = {-1,-1},i = 0,j = 0;
    char ch;
    int loop = 1;
    int wrong_input = 0;
    int pos_for_tool = 0,tool_place = 0;
    int is_dig = 0; // 用来指定是不是有数字量
    Map* cur_map = game->map[player->position];// // 指向当前地皮，此时玩家已经不会移动了
    while(loop){
        if(strcmp(command,NOCOMMAND) != 0){
            strcpy(real_command,command);
            loop = 0;
        }
        else{
            printf("%c> ", player->name);
            i = 0;
            j = 0;
            symbol = 0;
            fflush(stdin); // 读取上一个空的
            // TODO 读取处理问题
            while((ch = getchar())!= '\n'){
                if(ch >= '0'&& ch <= '9'){
                    if(num[1] != -1 && num[0] != 1){
                        printf("输入的数字有问题！请重新输入！\n");
                        wrong_input = 1;
                        break;
                    }
                    if(i>1){
                        printf("输入的数字个数非法请重新输入！\n");
                        wrong_input = 1;
                        break;
                    }
                    num[i] = ch -48;
                    i++;

                    continue;
                }else if(ch == '-')
                    symbol = 1;
                else{
                    if(ch == ' '){ // 处理空格
                        continue;
                    }
                    else{
                        ch = tolower(ch);
                        real_command[j++] = ch;
                    }
                }
            }
            real_command[j] = '\0';
        
        }
        if(wrong_input) {
            num[0] = -1, num[1] = -1;// 重置
            wrong_input = 0;
            continue;
        } // 检测问题
        // 上面读取完了指令
        if(player->stop_rounds == 0){
            pos_for_tool = 0,tool_place = 0;
            is_dig = 0;
            Tool* temp;

            if(num[0] != -1&&num[1] != -1){
                pos_for_tool = num[0]*10 + num[1];
                is_dig = 1;
            }else if(num[0] != -1) {
                pos_for_tool = num[0];
                is_dig = 1;
            }
            else{ // 没有输入值
                is_dig = 0;// 这一部分不写也可以
            }

            if(symbol){
                pos_for_tool = -pos_for_tool;
            }
            // 重置 nums
            if(is_dig) {
                tool_place = (player->position + pos_for_tool + MAP_SIZE) % MAP_SIZE;
                //target_map = game->map[tool_place];
            }
            if(strcmp(real_command,"query") == 0) {
                if (num[0] != -1 || num[1] != -1) {
                    // 只要有一个加了数字
                    printf("该指令不能附带数字，请重新输入!\n");
                    num[0] = -1, num[1] = -1;
                    continue;
                }
                PlayerDisplayInfo(player);
            }
            else if(strcmp(real_command,"roll") == 0){
                if(num[0] != -1 || num[1] != -1){
                    // 只要有一个加了数字
                    printf("该指令不能附带数字，请重新输入!\n");
                    num[0] = -1, num[1] = -1;
                    continue;
                }
                GameRollDice(game,NODICE);
                // TODO
                printf("玩家%c退出回合\n",player->name);
                loop = 0;
                game->current_player_index = (++game->current_player_index)%game->player_count; // 更新游戏玩家的索引
                player_next = game->players[game->current_player_index]; // 进入下一个玩家的回合
            }else if(strcmp(real_command,"bomb") == 0){
                PlayerUseTool(player,BOMB,tool_place);
                // 下面这一片可以直接放到使用道具中去
                // if(game->map[tool_place]->land_type == HOSPITAL || game->map[tool_place]->land_type || game->map[tool_place]->player_nums!=0){
                //     printf("该地皮不能够放置道具，请重新指令！\n");
                //     continue;
                // }
                // // 使用toolactivate？判断地皮是不是普通的
                // temp = malloc(sizeof(Tool));
                // temp->id = BOMB;
                // strcpy(temp->name,"bomb");
                // temp->points = 50;
                // temp->owner = player;
                // player->bomb[player->bomb_count++] = temp;

                // game->map[tool_place]->is_tool = 1;
                // game->map[tool_place]->tool = temp; // 这里直接通过配合bomb——count和bomb来实现？，或者这个炸弹都初始化为空
            }else if(strcmp(real_command,"barrier") == 0){
                PlayerUseTool(player,BARRIER,tool_place);
                
            }else if(strcmp(real_command,"sell") == 0){
                if(num[0] != -1 || num[1] != -1){
                    // 只要有一个加了数字
                    printf("该指令不能附带数字，请重新输入!\n");
                    num[0] = -1, num[1] = -1;
                    continue;
                }
                PlayerSellProperty(player,cur_map);

            }else if(strcmp(real_command,"help") == 0){
                if(num[0] != -1 || num[1] != -1){
                    // 只要有一个加了数字
                    printf("该指令不能附带数字，请重新输入!\n");
                    num[0] = -1, num[1] = -1;
                    continue;
                }
                PlayerHelp();
            }else if(strcmp(real_command,"robot") == 0){
                PlayerUseTool(player,ROBOT,tool_place);
            }
            else{
                printf("未解析的外部命令！\n");
            }

        }else{
            // TODO 当权处于轮空状态
            printf("你当前处于轮空状态！");
            player_next = GameRollDice(game,NODICE);
                
        }
        num[0] = -1, num[1] = -1; // 最后重置，因为sell里面还需要判断
    }
    return player_next;
}
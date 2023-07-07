#include "Game.h"
#include "Map.h"
#include "Tool.h"
#include "Player.h"
#include "Property.h"
#include<string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
//#include <windows.h>


char player_char(char num);

// 输出玩家信息
void print_player(Game *game, char name, FILE* file) {
    Player* player = GameGetPlayerByName(game, name);
    if (!player) {
        fprintf(file, "alive %d\n", 0);
        fprintf(file, "money %d\n", game->init_cash);
        fprintf(file, "point %d\n", 0);
        fprintf(file, "item1 %d\n", 0);
        fprintf(file, "item2 %d\n", 0);
        fprintf(file, "item3 %d\n", 0);
        fprintf(file, "buff %d\n", 0);
        fprintf(file, "stop %d\n", 0);
        fprintf(file, "userloc %d\n", 0);
        return;
    } else {
        if (player->status == BANKRUPT) {
            fprintf(file, "alive %d\n", 0);
        } else {
            fprintf(file, "alive %d\n", 1);
        }
        fprintf(file, "money %d\n", player->cash);
        fprintf(file, "point %d\n", player->points);
        fprintf(file, "item1 %d\n", player->barrier_count);
        fprintf(file, "item2 %d\n", player->robot_count);
        fprintf(file, "item3 %d\n", player->bomb_count);
        fprintf(file, "buff %d\n", player->god_rounds);
        fprintf(file, "stop %d\n", player->stop_rounds);
        fprintf(file, "userloc %d\n", player->position);
    }

}

Game *GameInitialize(int initcash, char *player_nums) {
    /*
    初始化游戏的函数要求，game已经在外部malloc
    1. 询问人数
    2. 初始化最开始游玩的玩家索引
    3. 初始化地图的数据
    */
    int i = 0;
    // char name[4] = {'A', 'Q', 'S', 'J'};
    Property *temp = NULL;
    struct Game *game = malloc(sizeof(Game));
    game->init_cash = initcash;
    game->player_count = strlen(player_nums);
    printf("初始化地图 ...\n");
    for (i = 0; i < MAP_SIZE; i++) {
        game->map[i] = malloc(sizeof(Map));
        game->map[i]->id = i;
        if (i == 0)
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
        if (i == 0) {
            game->map[i]->land_type = START;
        } else if (i < 14) {
            game->map[i]->land_type = SPACE;
            // game->map[i]->property->price = 200;
            PropertyInitialize(game->map[i]->property, 200);
        } else if (i == 14) {
            game->map[i]->land_type = HOSPITAL;
        } else if (i < 28) {
            game->map[i]->land_type = SPACE;
            // game->map[i]->property->price = 200;
            PropertyInitialize(game->map[i]->property, 200);
        } else if (i == 28) {
            game->map[i]->land_type = TOOL;
        } else if (i < 35) {
            game->map[i]->land_type = SPACE;
            // game->map[i]->property->price = 500;
            PropertyInitialize(game->map[i]->property, 500);
        } else if (i == 35) {
            game->map[i]->land_type = GIFT;
        } else if (i < 49) {
            game->map[i]->land_type = SPACE;
            // game->map[i]->property->price = 300;
            PropertyInitialize(game->map[i]->property, 300);
        } else if (i == 49) {
            game->map[i]->land_type = PRISON;
        } else if (i < 63) {
            game->map[i]->land_type = SPACE;
            // game->map[i]->property->price = 300;
            PropertyInitialize(game->map[i]->property, 300);
        } else if (i == 63) {
            game->map[i]->land_type = MAGIC;
        } else if (i < 70) {
            game->map[i]->land_type = MINERAL;
        }
    }
    printf("地图加载完成! \n");
    game->current_player_index = 0; // 这游戏开始确定当前回合的id
    for (i = 0; i < game->player_count; i++) {
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

Player *GameStart(struct Game *game) {
    /*
    开始游戏
    1. 添加人物
    2. 进入第一个玩家回合
    */

    GameDisplayMap(game);
    return game->players[0]; // 进入第一个玩家的回合,也就是返回这个玩家指针，放到roll里面
    // TODO 进入玩家回合
}

int GameEnd(struct Game *game) {
    return 1;
}

char player_char(char num) {
    char ch;
    switch (num) {
        case '1':
            ch = 'Q';
            break;
        case '2':
            ch = 'A';
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

char level_char(int level) {
    char ch;
    switch (level) {
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

char Tool_char(int idx) {
    char ch;
    switch (idx) {
        case 1:
            ch = '#';
            break;
        case 3:
            ch = '@';
            break;
        default:
            ch = '0';
            break;
    }
    return ch;
}

void GameDisplayMap(const struct Game *game) {
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
    char level_symbols[] = {'0', '1', '2', '3'};
    // 这里打印第一行，其中除了14号，都可以有道具

    for (i = 0; i < 29; i++) {
        player_on_map = game->map[i]->player_nums;
        if (player_on_map != 0) {
            drawmap[0][i] = game->map[i]->player[player_on_map - 1]->name; // 需要删除玩家，走出去了
        } else if (game->map[i]->is_tool) {
            drawmap[0][i] = Tool_char(game->map[i]->is_tool);
        } else if (game->map[i]->land_type == SPACE && game->map[i]->property->level) {
            // 根据房屋等级打印相应的字符
            drawmap[0][i] = level_symbols[game->map[i]->property->level];
        } else {
            drawmap[0][i] = game->map[i]->land_type;
        }
    }

    for (i = 0; i < 8; i++)
        drawmap[i][29] = '\n';

    // 打印右边，

    for (i = 0; i < 8; i++) {
        player_on_map = game->map[28 + i]->player_nums;
        // 同样的更改应用于右边
        if (player_on_map != 0) {
            drawmap[i][28] = game->map[28 + i]->player[player_on_map - 1]->name;
        } else if (game->map[28 + i]->is_tool) {
            drawmap[i][28] = Tool_char(game->map[28 + i]->is_tool);
        } else if (!game->map[28 + i]->property->level && game->map[28 + i]->land_type == SPACE) {
            drawmap[i][28] = level_symbols[game->map[28 + i]->property->level];
        } else {
            drawmap[i][28] = game->map[28 + i]->land_type;
        }
    }

    //打印下边
    for (i = 28; i >= 0; i--) {
        j = 28 - i;
        player_on_map = game->map[35 + j]->player_nums;
        // 同样的更改应用于下边
        if (player_on_map != 0) {
            drawmap[7][i] = game->map[35 + j]->player[player_on_map - 1]->name;
        } else if (game->map[35 + j]->is_tool) {
            drawmap[7][i] = Tool_char(game->map[35 + j]->is_tool);
        } else if (game->map[35 + j]->land_type == SPACE && game->map[35 + j]->property->level) {
            drawmap[7][i] = level_symbols[game->map[35 + j]->property->level];
        } else {
            drawmap[7][i] = game->map[35 + j]->land_type;
        }
    }

    // 打印左边,矿区不能够买地皮，所以只需要管一部分
    for (i = 6; i >= 1; i--) {
        j = 7 - i;
        player_on_map = game->map[63 + j]->player_nums;
        if (player_on_map != 0) {
            drawmap[i][0] = game->map[63 + j]->player[player_on_map - 1]->name;
        } else if (game->map[63 + j]->is_tool)
            drawmap[i][0] = Tool_char(game->map[63 + j]->is_tool);
        else
            drawmap[i][0] = game->map[63 + j]->land_type;
    }

    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 30; j++) {
            // printf("",game->map[i]->property->level);
            if (drawmap[i][j] == 'A') { // 阿土伯（绿色）
                //SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            } else if (drawmap[i][j] == 'Q') { // 钱夫人（红色）
                //SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            } else if (drawmap[i][j] == 'S') { // 孙小美（蓝色）
                //SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
            } else if (drawmap[i][j] == 'J') { // 金贝贝（黄色）
                //SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
            } else {
                //SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            printf("%c", drawmap[i][j]);
        }
        //SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
}

// 通过名字获取玩家
Player *GameGetPlayerByName(const struct Game *game, char name) {
    int i = 0;
    for (i = 0; i < game->player_count; i++) {
        if (game->players[i]->name == name)
            return game->players[i];
    }
    return NULL;
}

Player *GameRollDice(struct Game *game, int dice_num) {
    int actual_num = 0;
    int i = 0, player_id = game->current_player_index;

    int pos_in_map = 0, pos_next_map = 0; // 也就是玩家从此出发偏移量
    Player *cur_player = game->players[player_id];
    Map *cur_map = NULL, *pre_map = NULL;
    // 判断轮空
    if (cur_player->stop_rounds != 0) {
        printf("当前你(%c)还处于轮空状态，无法行动，进入下一个玩家回合\n", cur_player->name);
        cur_player->stop_rounds--;
        game->current_player_index = (++game->current_player_index) % 4;
        player_id = game->current_player_index;
        return game->players[player_id]; // 返回下一个玩家
    }

    //投掷色子
    if (dice_num != NODICE)
        actual_num = dice_num;
    else {
        srand((unsigned) time(NULL));
        actual_num = rand() % 6 + 1;
        printf("当前你色子的点数为: %d\n", actual_num);
    }
    // 下面只写了投色子之后需要走的步数，后序还需要添加一个读取指令的东西
    pos_in_map = cur_player->position;
    pos_next_map = cur_player->position + actual_num; // 这里进行一个初始化，然后后面要是又特殊的情况就修改
    int flag = 0;
    for (i = 0; i < actual_num; i++) {
        pos_next_map = (pos_in_map + i + 1) % 70;
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
                flag = 1;
                printf("你踩到了路障，无法前进\n");
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
                flag = 1;
                printf("你踩到了炸弹，进入医院休息三天\n");
                break;
            }
        }
        if (flag) {
            break;
        }
    }
    // 添加玩家
    pre_map = game->map[pos_in_map];
    cur_player->position = pos_next_map;
    cur_map = game->map[pos_next_map];
    // printf("%d\n",pos_in_map);
    // TODO 下面的玩家需要把踩到的地图块更新上面的玩家
    AddPlayerMap(cur_map, cur_player); // 采用队列的形式添加
    DelPlayerMap(pre_map, cur_player); // 在之前地图上删掉这个玩家
    //game->map[cur_player->position]->player[] = cur_player; // 在地图的位置上更新玩家显示
    GameDisplayMap(game); // 从新打印地图
    if (!flag) {
        printf("你(%c)已经到达相应的位置。\n", cur_player->name);
    }
    return cur_player; // 这个玩家投完色子之后，返回当前玩家
}

Player *GamePlayerRound(struct Game *game, struct Player *player) {
    if (player == NULL || game == NULL) {
        printf("NULL ptr!!");
        return NULL;
    }
    Player *player_next = NULL;

    // 如果轮空或者破产，就直接进入下一个玩家
    if (player->stop_rounds != 0) {
        printf("当前你(%c)还处于轮空状态，还剩余%d轮，无法行动，进入下一个玩家回合\n", player->name, player->stop_rounds);
        player->stop_rounds--;
        game->current_player_index = (++game->current_player_index) % 4;
        player_next = game->players[game->current_player_index];
        return player_next; // 返回下一个玩家
    }
    else if(player->status == BANKRUPT){
        printf("当前你(%c)已经破产，无法行动，进入下一个玩家回合\n", player->name);
        game->current_player_index = (++game->current_player_index) % 4;
        player_next = game->players[game->current_player_index];
        return player_next; // 返回下一个玩家
    }

    char real_command[16];
    int symbol = 0;
    int num[2] = {-1, -1}, i = 0, j = 0;
    char ch;
    int loop = 1;
    int wrong_input = 0;
    int pos_for_tool = 0, tool_place = 0;
    int is_dig = 0; // 用来指定是不是有数字量
    while (loop) {
        //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        if (player->name == 'A') { // 阿土伯（绿色）
            //SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            printf("阿土伯> ");
        } else if (player->name == 'Q') { // 钱夫人（红色）
            //SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            printf("钱夫人> ");
        } else if (player->name == 'S') { // 孙小美（蓝色）
            //SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
            printf("孙小美> ");
        } else if (player->name == 'J') { // 金贝贝（黄色）
            //SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
            printf("金贝贝> ");
        }
        //SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        i = 0;
        j = 0;
        symbol = 0;
        // TODO 读取处理问题
        char line[100];
        fgets(line, 100, stdin);
        printf("%s\n", line);
        fflush(stdout);
        // set money [Q|A|S|J] [value] 设置玩家的资金
        if (strncmp(line, "set money", 9) == 0) {
            char name;
            int value;
            sscanf(line, "set money %c %d", &name, &value);
            GameGetPlayerByName(game, name)->cash = value;
            continue;
        }
        // set point [Q|A|S|J] [value] 设置玩家的点数
        else if (strncmp(line, "set point", 9) == 0) {
            char name;
            int value;
            sscanf(line, "set point %c %d", &name, &value);
            GameGetPlayerByName(game, name)->points = value;
            continue;
        }
        // set item [Q|A|S|J] [(item)1|2|3] [num] 设置玩家的道具数量
        else if (strncmp(line, "set item", 8) == 0) {
            char name;
            int item;
            int num;
            sscanf(line, "set item %c %d %d", &name, &item, &num);
            Player* player = GameGetPlayerByName(game, name);
            if (item == 1) {
                while (player->barrier_count < num) {
                    PlayerGetBarrier(player);
                }
            } else if (item == 2) {
                while (player->robot_count < num) {
                    PlayerGetRobot(player);
                }
            } else if (item == 3) {
                while (player->bomb_count < num) {
                    PlayerGetBomb(player);
                }
            }
            continue;
        }

        // set buff [Q|A|S|J] [n] 设置财神财神效果回合数
        else if (strncmp(line, "set buff", 8) == 0) {
            char name;
            int n;
            sscanf(line, "set buff %c %d", &name, &n);
            GameGetPlayerByName(game, name)->god_rounds = n;
            continue;
        }

        // set map [n] [Q|A|S|J] [level] 设置可购买的地皮n属于某玩家并有level等级(0|1|2|3)的房产
        else if (strncmp(line, "set map", 7) == 0) {
            int n;
            char name;
            int level;
            sscanf(line, "set map %d %c %d", &n, &name, &level);
            PropertySetOwner(game->map[n]->property, GameGetPlayerByName(game, name));
            for (int i = 0; i < level; i++) {
                PropertyUpgrade(game->map[n]->property);
            }
            continue;
        }

        // set unmap [n] 将可购买的地皮n设置为未购买状态
        else if (strncmp(line, "set unmap", 9) == 0) {
            int n;
            sscanf(line, "set unmap %d", &n);
            PropertySetOwner(game->map[n]->property, NULL);
            continue;
        }

        // set bomb [n] 在可放置炸弹的地皮n上放置炸弹
        else if (strncmp(line, "set bomb", 8) == 0) {
            int n;
            sscanf(line, "set bomb %d", &n);
            game->map[n]->tool = BombInitialize(NULL);
            game->map[n]->is_tool = BOMB;
            continue;
        }

        // set barrier [n] 在可放置障碍的地皮n上放置障碍
        else if (strncmp(line, "set barrier", 11) == 0) {
            int n;
            sscanf(line, "set barrier %d", &n);
            game->map[n]->tool = BarrierInitialize(NULL);
            game->map[n]->is_tool = BARRIER;
            continue;
        }

        // set pos [Q|A|S|J] [n] 将玩家移动到地皮n
        else if (strncmp(line, "set pos", 7) == 0) {
            char name;
            int n;
            sscanf(line, "set pos %c %d", &name, &n);
            // 将玩家移动到地皮n
            Player* cur_player = GameGetPlayerByName(game, name);
            Map* cur_map = game->map[n];
            Map* pre_map = game->map[cur_player->position];
            cur_player->position = n;
            AddPlayerMap(cur_map, cur_player); // 采用队列的形式添加
            DelPlayerMap(pre_map, cur_player); // 在之前地图上删掉这个玩家
            continue;
        }

        // set stop [Q|A|S|J] [n] 设置玩家停留时间
        else if (strncmp(line, "set stop", 8) == 0) {
            char name;
            int n;
            sscanf(line, "set stop %c %d", &name, &n);
            GameGetPlayerByName(game, name)->stop_rounds = n;
            continue;
        }

        // dump 打印当前游戏状态
        else if (strncmp(line, "dump", 4) == 0) {
            // 创建输出文件
            FILE* output = fopen(game->output_file_path, "w");
            // 将玩家名字写入文件
            char names[5];
            for (int i = 0; i < game->player_count; i++) {
                names[i] = game->players[i]->name;
            }
            names[game->player_count] = '\0';
            fprintf(output, "user %s\n", names);

            // 目前玩家
            fprintf(output, "preuser %c\n", game->players[game->current_player_index]->name);

            // Q的状态
            fprintf(output, "Q\n");
            print_player(game, 'Q', output);

            // A的状态
            fprintf(output, "A\n");
            print_player(game, 'A', output);

            // S的状态
            fprintf(output, "S\n");
            print_player(game, 'S', output);

            // J的状态
            fprintf(output, "J\n");
            print_player(game, 'J', output);

            fprintf(output, "MAP\n");
            for (int i = 0; i < 70; i++) {
                if (game->map[i]->player_nums != 0) {
                    // 获取所有玩家的名字
                    char names[5];
                    for (int j = 0; j < game->map[i]->player_nums; j++) {
                        names[j] = game->map[i]->player[j]->name;
                    }
                    names[game->map[i]->player_nums] = '\0';
                    fprintf(output, "mapuser %d %s\n", i, names);
                }
            }
            fflush(output);
            continue;
        }
        else if(strncmp(line, "quit", 4) == 0){
            exit(0);
        }
        int n = 0;
        while ((ch = line[n++]) != '\n') {
            if (ch >= '0' && ch <= '9') {
                if (i > 1) {
                    printf("输入的数字个数非法请重新输入！\n");
                    wrong_input = 1;
                    break;
                }
                num[i] = ch - 48;
                i++;

                continue;
            } else if (ch == '-')
                symbol = 1;
            else {
                if (ch == ' ') { // 处理空格
                    continue;
                } else {
                    ch = tolower(ch);
                    real_command[j++] = ch;
                }
            }
        }
        real_command[j] = '\0';


        if (wrong_input) {
            num[0] = -1, num[1] = -1;// 重置
            wrong_input = 0;
            continue;
        } // 检测问题

        // 上面读取完了指令
        if (player->stop_rounds == 0 && player->status == NORMAL) {
            pos_for_tool = 0, tool_place = 0;
            is_dig = 0;
            Tool *temp;

            if (num[0] != -1 && num[1] != -1) {
                pos_for_tool = num[0] * 10 + num[1];
                is_dig = 1;
            } else if (num[0] != -1) {
                pos_for_tool = num[0];
                is_dig = 1;
            } else { // 没有输入值
                is_dig = 0;// 这一部分不写也可以
            }

            if (symbol) {
                pos_for_tool = -pos_for_tool;
            }
            // 重置 nums
            if (is_dig) {
                tool_place = (player->position + pos_for_tool + MAP_SIZE) % MAP_SIZE;
                //target_map = game->map[tool_place];
            }
            if (strcmp(real_command, "query") == 0) {
                if (num[0] != -1 || num[1] != -1) {
                    // 只要有一个加了数字
                    printf("该指令不能附带数字，请重新输入!\n");
                    num[0] = -1, num[1] = -1;
                    continue;
                }
                PlayerDisplayInfo(player);
            } else if (strcmp(real_command, "roll") == 0) {
                if (num[0] != -1 || num[1] != -1) {
                    // 只要有一个加了数字
                    printf("该指令不能附带数字，请重新输入!\n");
                    num[0] = -1, num[1] = -1;
                    continue;
                }
                GameRollDice(game, NODICE);
                // TODO
                // printf("玩家%c退出回合\n", player->name);
                loop = 0;
                game->current_player_index = (++game->current_player_index) % game->player_count; // 更新游戏玩家的索引
                player_next = game->players[game->current_player_index]; // 进入下一个玩家的回合
            } else if (strcmp(real_command, "step") == 0) {
                // 获取数字
                if (!is_dig) {
                    printf("该指令需要附带数字，请重新输入!\n");
                    num[0] = -1, num[1] = -1;
                    continue;
                }
                int step;
                if (num[1] == -1) {
                    step = num[0];
                } else {
                    step = num[0] * 10 + num[1];
                }
                GameRollDice(game, step);
                // printf("玩家%c退出回合\n", player->name);
                loop = 0;
                game->current_player_index = (++game->current_player_index) % game->player_count; // 更新游戏玩家的索引
                player_next = game->players[game->current_player_index]; // 进入下一个玩家的回合
            } else if (strcmp(real_command, "bomb") == 0) {
                // 获取数字
                if (!is_dig) {
                    printf("该指令需要附带数字，请重新输入!\n");
                    num[0] = -1, num[1] = -1;
                    continue;
                }
                if (player->bomb_count == 0) {
                    printf("你没有炸弹，无法使用该道具！\n");
                    continue;
                }
                if ((symbol && pos_for_tool < -10) || !symbol && pos_for_tool > 10) {
                    printf("指令超过范围，请重新输入！\n");
                    wrong_input = 1;
                    continue;
                }
                tool_place = (player->position + pos_for_tool + MAP_SIZE) % MAP_SIZE;
                // 判断地皮是否可以放置道具
                if (game->map[tool_place]->land_type == HOSPITAL || game->map[tool_place]->land_type == PRISON ||
                    game->map[tool_place]->player_nums != 0) {
                    printf("该地皮不能够放置道具，请重新指令！\n");
                    continue;
                }
                PlayerUseBombOrBarrier(player, BOMB, game->map[tool_place]);
            } else if (strcmp(real_command, "barrier") == 0) {
                // 获取数字
                if (!is_dig) {
                    printf("该指令需要附带数字，请重新输入!\n");
                    num[0] = -1, num[1] = -1;
                    continue;
                }
                if (player->barrier_count == 0) {
                    printf("你没有路障，无法使用该道具！\n");
                    continue;
                }
                // 获取相对位置
                if ((symbol && pos_for_tool < -10) || !symbol && pos_for_tool > 10) {
                    printf("指令超过范围，请重新输入！\n");
                    wrong_input = 1;
                    continue;
                }
                tool_place = (player->position + pos_for_tool + MAP_SIZE) % MAP_SIZE;
                // 判断地皮是否可以放置道具
                if (game->map[tool_place]->land_type == HOSPITAL || game->map[tool_place]->land_type == PRISON ||
                    game->map[tool_place]->player_nums != 0) {
                    printf("该地皮不能够放置道具，请重新指令！\n");
                    continue;
                }
                PlayerUseBombOrBarrier(player, BARRIER, game->map[tool_place]);
            } else if (strcmp(real_command, "robot") == 0) {
                // 判断是否有机器人
                if (player->robot_count == 0) {
                    printf("你没有机器人，无法使用该道具！\n");
                    continue;
                }
                // 让玩家前面10格的道具全部清除
                for (int i = 1; i <= 10; ++i) {
                    temp = game->map[(player->position + i + MAP_SIZE) % MAP_SIZE]->tool;
                    if (temp != NULL) {
                        game->map[(player->position + i + MAP_SIZE) % MAP_SIZE]->tool = NULL;
                        free(temp);
                    }
                }
                player->robot_count--;
            } else if (strcmp(real_command, "sell") == 0) {
                // 获取数字
                if (!is_dig) {
                    printf("该指令需要附带数字，请重新输入!\n");
                    num[0] = -1, num[1] = -1;
                    continue;
                }
                int sell_place;
                // 获取相对位置
                if (num[1] == -1) {
                    sell_place = num[0];
                } else {
                    sell_place = num[0] * 10 + num[1];
                }
                // 判断地皮是否可以出售
                if (game->map[sell_place]->property == NULL || game->map[sell_place]->property->owner != player) {
                    printf("该地皮不是你的，请重新输入指令！\n");
                    continue;
                }
                PlayerSellProperty(player, game->map[sell_place]->property);
            } else if (strcmp(real_command, "help") == 0) {
                if (num[0] != -1 || num[1] != -1) {
                    // 只要有一个加了数字
                    printf("该指令不能附带数字，请重新输入!\n");
                    num[0] = -1, num[1] = -1;
                    continue;
                }
                PlayerHelp();
            } else {
                printf("未解析的外部命令！\n");
            }

        } else {
            // TODO 当权处于轮空状态 
            printf("你当前处于轮空状态！");
            player_next = GameRollDice(game, NODICE);

        }
        num[0] = -1, num[1] = -1; // 最后重置，因为sell里面还需要判断
    }
    // 触发地块
    GameTriggerEvent(game, player, player->position, GAME_INPUT);
    printf("玩家%c退出回合\n", player->name);
    return player_next;
}

// 输入是否购买
int Input() {
    char *command = NULL;
    size_t len = 0;
    ssize_t read;
    int result = INPUTERROR; // 默认为错误

    do {
        int count_y = 0; // 计数 'y' 或 'Y'
        int count_n = 0; // 计数 'n' 或 'N'
        read = getline(&command, &len, stdin);
        if (read != -1) {
            //去除可能存在的换行符
            command[strcspn(command, "\n")] = 0;

            for (int i = 0; i < strlen(command); ++i) {
                // 如果字符是 'y' 或 'Y'，计数加1
                if (tolower(command[i]) == 'y') {
                    count_y++;
                } 
                // 如果字符是 'n' 或 'N'，计数加1
                else if (tolower(command[i]) == 'n') {
                    count_n++;
                }
                // 如果字符不是 'y'、'Y'、'n'、'N' 或空格，设置结果为 ERROR
                else if (command[i] != ' ') {
                    result = INPUTERROR;
                    break;
                }

                // 如果只有一个 'y' 或 'Y'，设置结果为 YES
                if (count_y == 1 && count_n == 0) {
                    result = YES;
                } 
                // 如果只有一个 'n' 或 'N'，设置结果为 NO
                else if (count_y == 0 && count_n == 1) {
                    result = NO;
                } 
                // 否则设置结果为 ERROR
                else {
                    result = INPUTERROR;
                }
            }
        }
        // 如果结果为 ERROR，提示用户重新输入
        if (result == INPUTERROR) {
            printf("输入错误，请重新输入：\n");
        }

    } while (result == INPUTERROR); // 当结果为 ERROR 时，继续读取输入

    free(command);
    return result;
}


// 触发地块
void GameTriggerEvent(struct Game* game, struct Player* player, int dice_num, int YesOrNo) {
    Map *map = game->map[dice_num];
    // 如果是普通地皮
    if (map->land_type == SPACE) {
        // 如果是空地皮
        if (map->property->owner == NULL) {
            // 询问是否购买
            if (YesOrNo == GAME_INPUT) {
                printf("是否购买该地皮？(y),其余键自动拒绝\n");
                YesOrNo = Input();
            }
            if (YesOrNo == YES) {
                // 判断是否有足够的钱
                if (player->cash < map->property->price) {
                    printf("你的钱不够，无法购买！\n");
                    return;
                }
                PlayerBuyProperty(player, map->property);
            }
            else {
                printf("你拒绝了购买该地皮！\n");
            }
        }
        // 如果是自己的地皮
        else if (map->property->owner == player) {
            // 询问是否升级
            if (YesOrNo == GAME_INPUT) {
                printf("当前的等级是%d\n", map->property->level);
                printf("是否升级该地皮？(y),其余键自动拒绝\n");
                YesOrNo = Input();
            }
            if (YesOrNo == YES) {
                // 判断是否有足够的钱
                if (player->cash < map->property->price) {
                    printf("你的钱不够，无法升级！\n");
                    return;
                }
                PlayerUpgradeProperty(player, map->property);
            }
            else {
                printf("你拒绝了升级该地皮！\n");
            }
        }
        // 如果是其他玩家的地皮
        else if (map->property->owner != player) {
            // 判断是否有足够的钱支付
            printf("你需要支付%d元给%c\n", map->property->value / 2, map->property->owner->name);
            if (player->cash < map->property->value / 2) {
                // 破产
                printf("你只有%d元，无法支付！\n", player->cash);
                printf("你破产了！\n");
                GameRemovePlayer(game, player);
            } else {
                // 支付钱
                player->cash -= map->property->value / 2;
                map->property->owner->cash += map->property->value / 2;
                printf("你支付了%d元给%c\n", map->property->value / 2, map->property->owner->name);
            }
        }
    }
    // 如果是礼品屋
    else if (map->land_type == GIFT) {
        PlayerGiftHouse(player);
    }
    // 如果是道具屋
    else if (map->land_type == TOOL) {
        PlayerTool(player);
    }
    // 如果是矿场
    else if (map->land_type == MINERAL) {
        PlayerMineral(player);
    }
    // 如果是监狱
    else if (map->land_type == PRISON) {
        PlayerPrison(player);
    }
}

// 移除破产玩家
void GameRemovePlayer(struct Game* game, Player *player) {
    // 将玩家的地皮全部卖出，将玩家的钱设置为0
    for (int i = 0; i < MAP_SIZE; ++i) {
        if (game->map[i]->property != NULL && game->map[i]->property->owner == player) {
            PlayerSellProperty(player, game->map[i]->property);
        }
    }
    player->cash = 0;
    player->status = BANKRUPT;
}
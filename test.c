#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Game.h"
#include "Player.h"
#include "Map.h"
#include "Property.h"
#include "Tool.h"

Game* game;

// 输出玩家信息
void print_player(char name, FILE* file) {
    Player* player = GameGetPlayerByName(game, name);
    if (player) {
        fprintf(file, "alive %d\n", 0);
        fprintf(file, "money %d\n", game->init_cash);
        fprintf(file, "point %d\n", 0);
        fprintf(file, "item1 %d\n", 0);
        fprintf(file, "item2 %d\n", 0);
        fprintf(file, "item3 %d\n", 0);
        fprintf(file, "buff %d\n", 0);
        fprintf(file, "stop %d\n", 0);
        fprintf(file, "userloc %d\n", 0);
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

int main(int argc, char* argv[]) {
    char line[256];
    // 读取文件
    FILE *file = fopen("/Users/wangjian/code/C/dian/Monopoly/test_file/input/input_0", "r");
    if (file == NULL) {
        printf("Error: unable to open test.txt\n");
        return 1;
    }

    // 读第一行，获取初始资金
    fgets(line, sizeof(line), file);
    line[strcspn(line, "\n")] = 0;
    // 将字符串转换为整数
    int money = atoi(line);

    // 读第二行，获取玩家顺序
    fgets(line, sizeof(line), file);
    line[strcspn(line, "\n")] = 0;

    // 初始化游戏
    game = GameInitialize(money, "123");



    while (fgets(line, sizeof(line), file)) {
        // 删除换行符
        line[strcspn(line, "\n")] = 0;

        // set money [Q|A|S|J] [value] 设置玩家的资金
        if (strncmp(line, "set money", 9) == 0) {
            char name;
            int value;
            sscanf(line, "set money %c %d", &name, &value);
            GameGetPlayerByName(game, name)->cash = value;
        }

        // set point [Q|A|S|J] [value] 设置玩家的点数
        if (strncmp(line, "set point", 9) == 0) {
            char name;
            int value;
            sscanf(line, "set point %c %d", &name, &value);
            GameGetPlayerByName(game, name)->points = value;
        }

        // set item [Q|A|S|J] [(item)1|2|3] [num] 设置玩家的道具数量
        if (strncmp(line, "set item", 8) == 0) {
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
        }

        // set buff [Q|A|S|J] [n] 设置财神财神效果回合数
        if (strncmp(line, "set buff", 8) == 0) {
            char name;
            int n;
            sscanf(line, "set buff %c %d", &name, &n);
            GameGetPlayerByName(game, name)->god_rounds = n;
        }

        // set map [n] [Q|A|S|J] [level] 设置可购买的地皮n属于某玩家并有level等级(0|1|2|3)的房产
        if (strncmp(line, "set map", 7) == 0) {
            int n;
            char name;
            int level;
            sscanf(line, "set map %d %c %d", &n, &name, &level);
            PropertySetOwner(game->map[n]->property, GameGetPlayerByName(game, name));
            for (int i = 0; i < level; i++) {
                PropertyUpgrade(game->map[n]->property);
            }
        }

        // set unmap [n] 将可购买的地皮n设置为未购买状态
        if (strncmp(line, "set unmap", 9) == 0) {
            int n;
            sscanf(line, "set unmap %d", &n);
            PropertySetOwner(game->map[n]->property, NULL);
        }

        // set bomb [n] 在可放置炸弹的地皮n上放置炸弹
        if (strncmp(line, "set bomb", 8) == 0) {
            int n;
            sscanf(line, "set bomb %d", &n);
            game->map[n]->tool = BombInitialize(NULL);
        }

        // set barrier [n] 在可放置障碍的地皮n上放置障碍
        if (strncmp(line, "set barrier", 11) == 0) {
            int n;
            sscanf(line, "set barrier %d", &n);
            game->map[n]->tool = BarrierInitialize(NULL);
        }

        // set pos [Q|A|S|J] [n] 将玩家移动到地皮n
        if (strncmp(line, "set pos", 7) == 0) {
            char name;
            int n;
            sscanf(line, "set pos %c %d", &name, &n);
            //game->map[n]->player = GameGetPlayerByName(game, name);
            //game->map[n]->player->position = n;
        }

        // step [n] 让当前玩家向前移动n格,范围为[0,70),效果就是一个能指定步数的roll,step后就不能roll
        if (strncmp(line, "step", 4) == 0) {
            int n;
            sscanf(line, "step %d", &n);
            GameRollDice(game, n);
        }

        // set stop [Q|A|S|J] [n] 设置玩家停留时间
        if (strncmp(line, "set stop", 8) == 0) {
            char name;
            int n;
            sscanf(line, "set stop %c %d", &name, &n);
            GameGetPlayerByName(game, name)->stop_rounds = n;
        }

        // dump 打印当前游戏状态
        if (strncmp(line, "dump", 4) == 0) {
            // 创建输出文件
            FILE* output = fopen("/Users/wangjian/code/C/dian/Monopoly/test_file/dump/dump_0", "w");
            // 将游戏状态写入文件
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
            print_player('Q', output);

            // A的状态
            fprintf(output, "A\n");
            print_player('A', output);

            // S的状态
            fprintf(output, "S\n");
            print_player('S', output);

            // J的状态
            fprintf(output, "J\n");
            print_player('J', output);

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
        }

        // quit 退出游戏
        if (strncmp(line, "quit", 4) == 0) {
            break;
        }
    }

    fclose(file);
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Game.h"
#include "Player.h"
#include "Map.h"
#include "Property.h"
#include "Tool.h"

Game* game;

int main() {
    char line[256];
    // 读取文件
    FILE *file = fopen("test.txt", "r");
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
            game->map[n]->player = GameGetPlayerByName(game, name);
            game->map[n]->player->position = n;
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
    }

    fclose(file);
    return 0;
}

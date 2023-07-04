#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Game.h"

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
    game = GameInitialize(money, 2);



    while (fgets(line, sizeof(line), file)) {
        // 删除换行符
        line[strcspn(line, "\n")] = 0;

        // set money [Q|A|S|J] [value] 设置玩家的资金
        if (strncmp(line, "set money", 9) == 0) {
            char name;
            int value;
            sscanf(line, "set money %c %d", &name, &value);
            GameSetMoney(game, name, value);
        }

        // set point [Q|A|S|J] [value] 设置玩家的点数
        if (strncmp(line, "set point", 9) == 0) {
            char name;
            int value;
            sscanf(line, "set point %c %d", &name, &value);
            GameSetPoint(game, name, value);
        }

        // set item [Q|A|S|J] [(item)1|2|3] [num] 设置玩家的道具数量
        if (strncmp(line, "set item", 8) == 0) {
            char name;
            int item;
            int num;
            sscanf(line, "set item %c %d %d", &name, &item, &num);
            GameSetItem(game, name, item, num);
        }

    }

    fclose(file);
    return 0;
}

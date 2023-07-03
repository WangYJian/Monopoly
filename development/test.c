#include <stdio.h>
#include <string.h>
#include "Game.h"
#include "Tool.h"
#include "Property.h"
#include "Player.h"
#include "Map.h"

// 预设命令
void preset_command(char* command) {
    // 读取命令的第二个词
    char cmd[20];
    sscanf(command, "%*s %s", cmd);

    // 如果是user
    if(strcmp(cmd, "user") == 0) {
        // 将命令的第三个词读取到user中
        char user[20];
        sscanf(command, "%*s %*s %s", user);
        // 初始化用户
        // TODO: initialize user

    } else if(strcmp(cmd, "map") == 0) {
        // 如果是map，将命令的第三，四，五分别读到格子id，玩家名字，等级中
        int cellID, level;
        char player;
        sscanf(command, "%*s %*s %d %s %d", &cellID, player, &level);
        // 初始化地图
        // TODO: initialize map

    } else if(strcmp(cmd, "fund") == 0) {
        // 如果是fund，将命令的第三和第四个词读入到用户和金额中
        char user[20];
        int money;
        sscanf(command, "%*s %*s %s %d", user, &money);
        // 设置用户的资金
        // TODO: set user fund

    } else if(strcmp(cmd, "credit") == 0) {
        // 如果是credit，将命令的第三和第四个词读入到用户和积分中
        char user[20];
        int credit;
        sscanf(command, "%*s %*s %s %d", user, &credit);
        // 设置用户的积分
        // TODO: set user credit

    } else if(strcmp(cmd, "gift") == 0) {
        // 如果是gift，将命令的第三，四，五个词读入到用户，礼物，数量中
        char user[20];
        char gift[20];
        int quantity;
        sscanf(command, "%*s %*s %s %s %d", user, gift, &quantity);
        // 给用户分配礼物
        // TODO: assign gift to user

    } else if(strcmp(cmd, "bomb") == 0) {
        // 如果是bomb，将命令的第三个词读入到位置中
        int location;
        sscanf(command, "%*s %*s %d", &location);
        // 在指定位置设置炸弹
        // TODO: set bomb at location

    } else if(strcmp(cmd, "barrier") == 0) {
        // 如果是barrier，将命令的第三个词读入到位置中
        int location;
        sscanf(command, "%*s %*s %d", &location);
        // 在指定位置设置障碍
        // TODO: set barrier at location

    } else if(strcmp(cmd, "userloc") == 0) {
        // 如果是userloc，将命令的第三，四，五个词读入到用户，位置，天数中
        char user[20];
        int location, days;
        sscanf(command, "%*s %*s %s %d %d", user, &location, &days);
        // 设置用户的位置和停留天数
        // TODO: set user location and stay days

    } else if(strcmp(cmd, "nextuser") == 0) {
        // 如果是nextuser，将命令的第三个词读入到用户中
        char user[20];
        sscanf(command, "%*s %*s %s", user);
        // 设置下一个用户
        // TODO: set next user

    } else {
        // 如果命令未知，打印错误信息或者忽略
        printf("Unknown preset command: %s\n", command);
    }
}

// 输出dump信息
void dump_command(Game* game) {
    FILE* file = fopen("dump.txt", "w");
    if (file == NULL) {
        printf("Failed to open file for writing\n");
        return;
    }

    // 用户
    fprintf(file, "user AQS\n");  // TODO: 只打印参与游戏的用户

    // 地图
    for (int i = 0; i < MAP_SIZE; i++) {
        if (!game->map[i]->player) {
            fprintf(file, "map %d %c %d\n", i, game->map[i]->player->name, game->map[i]->property->level);
        }
    }

    // 用户资金
    for (int i = 0; i < 4; i++) {
        fprintf(file, "fund %c %d\n", game->players[i]->name, game->players[i]->cash);
    }

    // 用户积分
    for (int i = 0; i < 4; i++) {
        fprintf(file, "credit %c %d\n", game->players[i]->name, game->players[i]->points);
    }

    // 用户道具
    for (int i = 0; i < game->player_count; i++) {
        if (game->players[i]->bomb_count > 0) {
            fprintf(file, "gift %c bomb %d\n", game->players[i]->name, game->players[i]->bomb_count);
        }
        if (game->players[i]->barrier_count > 0) {
            fprintf(file, "gift %c barrier %d\n", game->players[i]->name, game->players[i]->barrier_count);
        }
        if (game->players[i]->robot_count > 0) {
            fprintf(file, "gift %c robot %d\n", game->players[i]->name, game->players[i]->robot_count);
        }
        if (game->players[i]->god_count > 0) {
            fprintf(file, "gift %c god %d\n", game->players[i]->name, game->players[i]->god_count);
        }

    }

    // 炸弹位置
    for (int i = 0; i < MAP_SIZE; i++) {
        if (game->map[i]->tool) {
            if (strcmp(game->map[i]->tool->name, "bomb") == 0) {
                fprintf(file, "bomb in %d\n", i);
            }
        }
    }

    // 障碍位置
    for (int i = 0; i < MAP_SIZE; i++) {
        if (game->map[i]->tool) {
            if (strcmp(game->map[i]->tool->name, "barrier") == 0) {
                fprintf(file, "barrier in %d\n", i);
            }
        }
    }

    // 用户位置
    for (int i = 0; i < 4; i++) {
        // 如果用户停留天数大于0，输出用户位置，停留天数
        if (game->players[i]->stop_rounds > 0) {
            fprintf(file, "userloc %c %d %d\n", game->players[i]->name, game->players[i]->position, game->players[i]->stop_rounds);
        }
    }

    // 下一个用户
    fprintf(file, "nextuser %c\n", game->players[game->current_player_index]->name);
    fclose(file);
}

// 函数来执行命令
void execute_command(char* command) {
    char cmd[20];
    sscanf(command, "%s", cmd); // 读取命令的第一个词

    if(strcmp(cmd, "t") == 0) {
        // 如果是t命令，说明是测试命令，直接忽略
        return;
    } else if(strcmp(cmd, "e") == 0) {
        // 如果是e命令，说明是结束命令，直接忽略
        return;
    } else if(strcmp(cmd, "preset") == 0) {
        preset_command(command); // 如果是preset命令，调用preset_command函数

    } else if(strcmp(cmd, "Step") == 0) {
        // 如果是Step命令，获取后面的数字
        int steps;
        sscanf(command, "%*s %d", &steps);
        // 执行相应的操作
        // TODO: execute step command
    } else if(strcmp(cmd, "dump") == 0) {
        // 如果是dump命令，执行相应的操作
        // ...

    } else if(strcmp(cmd, "quit") == 0) {
        // 如果是quit命令，运行程序，将结果保存到文件中

    }
    else {
        // 如果命令未知，打印错误信息或者忽略
        printf("Unknown command: %s\n", command);
    }
}

// 主函数
int main() {
    char command[100];
    FILE* file = fopen("commands.txt", "r");

    if(file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while(fgets(command, sizeof(command), file) != NULL) {
        // 对每一行命令进行操作
        execute_command(command);
    }

    fclose(file);

    return 0;
}

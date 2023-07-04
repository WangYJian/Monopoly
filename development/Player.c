#include <stdlib.h>
#include <stdio.h>
#include "Player.h"
#include "Tool.h"

// 获取炸弹
void PlayerGetBomb(Player* player){
    player->bomb[player->bomb_count] = BombInitialize(player);
    player->bomb_count++;
}

// 获取路障
void PlayerGetBarrier(Player* player){
    player->barrier[player->barrier_count] = BarrierInitialize(player);
    player->barrier_count++;
}

// 获取机器娃娃
void PlayerGetRobot(Player* player){
    player->robot[player->robot_count] = RobotInitialize(player);
    player->robot_count++;
}
//************************
//写礼品屋代码时自己写的读取输入,后续可统一
#define  BUF_SIZE 1024
int GetIntInput()
{
    int input;
    char buf[BUF_SIZE] = {0};

    fgets(buf, BUF_SIZE, stdin);

    for (int i = 0; i < BUF_SIZE; i++) {
        if (buf[i] == '\r' ||
            buf[i] == '\n' ||
            buf[i] == ' '  ||
            buf[i] == '\t' ||
            buf[i] == '\v' ||
            buf[i] == '\f') {

            buf[i] = '\0';
            break;
        }
    }

    input = (int)strtol(buf, '\0', 10);

    return input;
}
//************************

void PlayerGiftHouse(Player* player)
{
    int gift_id;
    printf("欢迎光临礼品屋, 请选择一件您喜欢的礼品\n1.2000元奖金\n2.200点数卡\n3.财神附身\n输入其他自动退出\n请输入:");
    gift_id = GetIntInput();
    if (gift_id == 1){
        player->cash += GIFT_CASH;
        printf("%c获得2000奖金！\n",player->name);
    }
    else if (gift_id == 2){
        player->points += GIFT_POINTS;
        printf("%c获得200点数！\n",player->name);
    }
    else if (gift_id == 3){
        player->god_rounds = GIFT_GOD_ROUND;
        printf("%c财神附体！\n",player->name);
    }
    printf("%c退出了礼品屋.\n",player->name);
}

void PlayerMineral(struct Player* player)
{
    switch (player->position) {
        case 69:
            player->points += 20;
            printf("恭喜%c玩家获得20点数！",player->name);
            break;
        case 68:
            player->points += 80;
            printf("恭喜%c玩家获得80点数！",player->name);
            break;
        case 67:
            player->points += 100;
            printf("恭喜%c玩家获得100点数！",player->name);
            break;
        case 66:
            player->points += 40;
            printf("恭喜%c玩家获得40点数！",player->name);
            break;
        case 65:
            player->points += 80;
            printf("恭喜%c玩家获得80点数！",player->name);
            break;
        case 64:
            player->points += 60;
            printf("恭喜%c玩家获得60点数！",player->name);
            break;
    }
}

// 显示玩家信息
void PlayerDisplayInfo(const Player* player){
    printf("玩家%c的信息:\n", player->name);
    printf("现金: %d元\n", player->cash);
    printf("点数: %d点\n", player->points);
    printf("炸弹: %d个\n", player->bomb_count);
    printf("路障: %d个\n", player->barrier_count);
    printf("机器娃娃: %d个\n", player->robot_count);
    printf("财神附体: %d轮\n", player->god_rounds);
}


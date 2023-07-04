#include "Player.h"
#include <stdio.h>
#include <stdlib.h>

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
        player->god_count = GIFT_GOD_ROUND;
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

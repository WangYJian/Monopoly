#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Player.h"
#include "Property.h"
#include "Tool.h"
#include "Map.h"

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

void PlayerTool(struct Player* player){
    char input[100];
    char* token;
    int tool_id;

    printf("欢迎光临道具屋，请选择您需要的道具:\n");
    printf("1.路障 50点\n");
    printf("2.机器娃娃 30点\n");
    printf("3.炸弹 50点\n");
    printf("您当前拥有点数：%d点\n",player->points);
    printf("每个玩家最多可拥有10个道具，您当前拥有：\n");
    printf("炸弹：%d个\n",player->bomb_count);
    printf("路障：%d个\n",player->barrier_count);
    printf("机器娃娃：%d个\n",player->robot_count);
    printf("共计：%d个\n",player->bomb_count+player->barrier_count+player->robot_count);   
    if (player->points < 30){
        printf("您的点数不足以购买任何道具，自动退出道具屋\n");
        return;
    }
    printf("请输入您要购买的道具编号，按“F”可手工退出道具屋：");
    //实现读取输入和购买功能，可循环读入数字，每次读取一行输入，在一行内识别合法数字，如果出现任何除空格外不合法输入都print输入不合法并提示如何正确输入
    //如果一行内都是合法输入(123)那就分别读出数字并购买，完成后循环读取下一行直到满足两个退出条件之一
    //例(不算引号)：输入"1 2 3  3 4"应该认为合法
    //"1 2 3 4 5"出现4 5 非法
    //”    1  2   “合法
    //”直接回车“非法
    while(fgets(input, 100, stdin)) {
        // 分割输入的字符串
        token = strtok(input, " ");
        if (player->points < 30){
            printf("您的点数不足以购买任何道具，自动退出道具屋\n");
            return;
        }

        while(token != NULL) {
            // 如果输入的是"F"或者"f"，退出
            if (token[0] == 'F' || token[0] == 'f') {
                printf("您已退出道具屋\n");
                return;
            }


            // 尝试将输入的字符串转换为数字
            tool_id = atoi(token);
            if (tool_id < 1 || tool_id > 3) {
                printf("输入的道具编号不合法！请输入1、2或3。\n");
            }

            // 购买道具
            PlayerBuyTool(player, tool_id);

            // 获取下一个分割的部分
            token = strtok(NULL, " ");
        }
    }

};

void PlayerBuyTool(struct Player* player, int toolID){
    // 确保玩家所拥有的道具总数没有超过10个
    int total_tool_count = player->bomb_count + player->barrier_count + player->robot_count;

    if (total_tool_count >= 10) {
        printf("您的道具箱已满，不能继续购买\n");
        return;
    }

    if (toolID == 1) {
        if (player->points >= 50) {
            player->points -= 50;
            player->barrier_count++;
            printf("购买路障成功！\n");
        } else {
            printf("积分不足，无法购买路障！\n");
        }
    } else if (toolID == 2) {
        if (player->points >= 30) {
            player->points -= 30;
            player->robot_count++;
            printf("购买机器娃娃成功！\n");
        } else {
            printf("积分不足，无法购买机器娃娃！\n");
        }
    } else if (toolID == 3) {
        if (player->points >= 50) {
            player->points -= 50;
            player->bomb_count++;
            printf("购买炸弹成功！\n");
        } else {
            printf("积分不足，无法购买炸弹！\n");
        }
    }
}


void PlayerPrison(struct Player* player){
    printf("need to be fill\n"); // TODO
};

void PlayerMagic(struct Player* player){
    printf("need to be fill\n"); // TODO
}
void PlayerUseBombOrBarrier(struct Player* player, int toolID, Map* map){
    // 玩家使用道具
    if (toolID == BOMB) {
        // 玩家使用炸弹
        if (player->bomb_count > 0) {
            // 玩家有炸弹
            map->tool = player->bomb[player->bomb_count - 1];
            map->is_tool = BOMB;
            player->bomb_count--;
        }
    } else if (toolID == BARRIER) {
        // 玩家使用路障
        if (player->barrier_count > 0) {
            // 玩家有路障
            map->tool = player->barrier[player->barrier_count - 1];
            map->is_tool = BARRIER;
            player->barrier_count--;
        }
    }
}

void PlayerBuyProperty(struct Player* player, Property *property){
    property->owner = player;
    player->cash -= property->price;
}

void PlayerSellProperty(struct Player* player, Property *property){
    property->owner = NULL;
    player->cash += 2 * property->value;
    property->level = 0;
    property->value = property->price;
}

// 升级地产
void PlayerUpgradeProperty(struct Player* player, Property *property){
    if (property->level <= 3) {
        if (player->cash >= property->price) {
            player->cash -= property->price;
            property->level++;
            property->value += property->price;
        }
    }
}

void PlayerHelp(){
    printf("help doc to fill\n");
};

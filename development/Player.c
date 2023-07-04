#include <stdlib.h>
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

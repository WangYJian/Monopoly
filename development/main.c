#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Game.h"




int main() {
    Game* game;
    Player* cur_player;
    char nums[5];
    int cash;
    int dice_num; // 色子的点数
    while(1){
        printf("请输入游戏的人数: ");
        scanf("%s", nums);
        if(strlen(nums) <= 4)
            break;
        printf("输入人数超了！请重新输入\n");
    }

    
    while(1){
        printf("请输入初始的金额: ");
        scanf("%d",&cash);
        if(cash > 1000 && cash <= 50000)
            break;
        printf("输入初始化金额有误！请重新输入\n");
    }
    game = GameInitialize(cash,nums);
    cur_player = GameStart(game);
    return 0;
}

#include <stdio.h>
#include<malloc.h>
#include "Game.h"

int main() {
    Game* game;
    int nums;
    int cash;
    while(1){
        printf("请输入游戏的人数: ");
        scanf("%d", &nums);
        if(nums <= 4)
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
    GameDisplayMap(game);
    return 0;
}

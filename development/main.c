#include <stdio.h>
#include<malloc.h>
#include "Game.h"

int main() {
    Game* game;
    int nums;
    int cash;
    while(1){
        printf("��������Ϸ������: ");
        scanf("%d", &nums);
        if(nums <= 4)
            break;
        printf("�����������ˣ�����������\n");
    }

    
    while(1){
        printf("�������ʼ�Ľ��: ");
        scanf("%d",&cash);
        if(cash > 1000 && cash <= 50000)
            break;
        printf("�����ʼ�������������������\n");
    }
    game = GameInitialize(cash,nums);
    GameDisplayMap(game);
    return 0;
}

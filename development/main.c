#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Game.h"
#include"Map.h"
#include"Player.h"

int main() {
    Game* game;
    Player* cur_player;
    char nums[5];
    int cash;
    int dice_num; // 色子的点数
    while(1){
        int i = 0,err = 0;
        printf("请输入游戏的玩家: ");
        scanf("%s", nums);
        // printf("%d",strlen(nums));
        if(strlen(nums) <= 4){
            for(i = 0; i< strlen(nums); i++){
                if(nums[i] >'4' || nums[i] < '1'){
                    err = 1;
                    break;
                }
            }
            if(err != 1){
                break;
            }
            else
                printf("输入的数字有误! 请重新输入\n");
        }
        else
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
    while(1){
        // printf("11\n");
        GameRollDice(game,4);
        GamePlayerRound(game,cur_player,NOCOMMAND);
        if(GameEnd(game))
            break;
    }
    // cur_player->position = 23;
    // game->map[cur_player->position]->player = cur_player;
    // game->map[27]->player = game->players[game->current_player_index+1];
    // GameDisplayMap(game);
    return 0;
}


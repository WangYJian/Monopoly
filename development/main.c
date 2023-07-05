#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Game.h"
#include"Map.h"
#include"Player.h"

int main() {
    Game* game;
    Player* cur_player;
    char nums[5];
    int cash;
    int result;
    int dice_num; // 色子的点数
    while(1){
        int i = 0,err = 0;
        printf("请输入玩家人数(2-4): ");
        scanf("%s", nums);
        fflush(stdin);
        // printf("%d",strlen(nums));
        if(strlen(nums) <= 4){
            for(i = 0; i< strlen(nums); i++){
                if(nums[i] >'4' || nums[i] <= '1'){
                    err = 1;
                    break;
                }
            }
            if(err != 1){
                break;
            }
            else
                printf("输入数字有误! 请重新输入(2-4)\n");
        }
        else
            printf("输入数字有误! 请重新输入(2-4)\n");
    }

    char* input = NULL;
    size_t size = 0;

    while (1) {
        printf("请输入初始金额(1000-50000): ");
        if (getline(&input, &size, stdin) == -1) {
            // 处理输入错误或结束的情况
            printf("无效输入！请重新输入(1000-50000)\n");
            continue;
        }

        result = sscanf(input, "%d", &cash);
        if (result == 1 && cash >= 1000 && cash <= 50000) {
            break;
        }
        printf("输入初始化金额有误！请重新输入(1000-50000)\n");
    }

    printf("初始金额为：%d\n", cash);

    free(input); 

    game = GameInitialize(cash,nums);
    cur_player = GameStart(game);
    GameRollDice(game,37);
    //int i = 0;
//    while(1){
//        // printf("11\n");
//
//        //GamePlayerRound(game,cur_player,NOCOMMAND);
//        if(i > 2)
//            break;
//        i++;
//    }
    // cur_player->position = 23;
    // game->map[cur_player->position]->player = cur_player;
    // game->map[27]->player = game->players[game->current_player_index+1];
    // GameDisplayMap(game);
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Game.h"
#include"Map.h"
#include"Player.h"

int main(int argc, char* argv[]) {
    Game* game;
    if (argc == 2) {
        game->output_file_path = argv[1];
    }
    Player* cur_player;
    char nums[50];
    int cash = 10000;
    int result;
    int dice_num; // 色子的点数
    while(1){
        int i = 0,err = 0;
        printf("选择角色编号(1~4): ");
        scanf("%s", nums);
        fflush(stdin);
        // printf("%d",strlen(nums));
        if(strlen(nums) <= 4 && strlen(nums) >= 2){
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
                printf("输入数字有误! 请重新输入(2-4)\n");
        }
        else
            printf("输入数字有误! 请重新输入(2-4)\n");
    }

    char input[100];
    while (1) {
        printf("请输入初始金额(1000-50000)，直接按回车默认为10000: ");
        if (fgets(input, 100, stdin) == NULL) {
            // 处理输入错误或结束的情况
            printf("输入错误！请重新输入(1000-50000)，直接按回车默认为10000\n");
            continue;
        }

        // 检查是否只是回车（输入长度为1），若是，则使用默认值
        if (input[0] == '\n') {
            break;
        }

        int tempCash;
        char extra;
        result = sscanf(input, "%d%c", &tempCash, &extra);
        if (result != 2) {
            printf("输入金额有误！请重新输入(1000-50000)，直接按回车默认为10000\n");
            continue;
        }
        if (tempCash >= 1000 && tempCash <= 50000 && (extra == ' ' || extra == '\n')) {
            int valid = 1;
            // Check for any non-space characters after the number
            for (char *p = input; *p; p++) {
                if (*p != ' ' && (*p < '0' || *p > '9') && *p != '\n') {
                    valid = 0;
                    break;
                }
            }
            if (valid) {
                cash = tempCash; // 如果有效输入，则更新cash的值
                break;
            }
        }
        printf("输入金额有误！请重新输入(1000-50000)，直接按回车默认为10000\n");
    }


    printf("初始金额为：%d\n", cash);
    game = GameInitialize(cash,nums);
    cur_player = GameStart(game);
    int i = 0;
    while(1){
        // printf("11\n");

        cur_player = GamePlayerRound(game,cur_player);
    }
    // cur_player->position = 23;
    // game->map[cur_player->position]->player = cur_player;
    // game->map[27]->player = game->players[game->current_player_index+1];
    // GameDisplayMap(game);
    return 0;
}

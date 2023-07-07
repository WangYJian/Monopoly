#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
//#include <windows.h>
#include "Game.h"
#include"Map.h"
#include"Player.h"

int checkDuplicate(char* nums, int length);

int main(int argc, char* argv[]) {
    Game* game;
    Player* cur_player;
    char nums[5];
    int cash = 10000;
    int result;
    int dice_num; // 色子的点数
    char input[100];
    while(1){
        printf("hahahahahahahahahahahahahahahahhahahahaha\n");
    }
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


    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //int colors[] = {FOREGROUND_RED, FOREGROUND_GREEN, FOREGROUND_BLUE, FOREGROUND_RED | FOREGROUND_GREEN}; // 钱夫人红色、阿土伯绿色、孙小美蓝色、金贝贝黄色
    char* names[] = {"钱夫人", "阿土伯", "孙小美", "金贝贝"};

    while(1){
        int i = 0, err = 0;
        printf("请选择2~4位不重复玩家，输入编号即可(");
        for(i = 0; i < 4; i++){
            //SetConsoleTextAttribute(hConsole, colors[i]);
            printf("%d、%s;", i+1, names[i]);
            //SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        printf("),如输入:12 ");
        scanf("%s", nums);
        
        int length = strlen(nums);
        if(length <= 4 && length >= 2){
            if(checkDuplicate(nums, length)){
                printf("输入的数字有重复!请重新输入!\n");
                continue;
            }
            for(i = 0; i < length; i++){
                if(nums[i] >'4' || nums[i] < '1'){
                    err = 1;
                    break;
                }
            }
            if(err != 1){
                printf("您选择的角色是: ");
                for(i = 0; i < length; i++){
                    //SetConsoleTextAttribute(hConsole, colors[nums[i] - '1']); // Set color
                    printf("%s ", names[nums[i] - '1']);
                    //SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset color
                }
                printf("\n");
                break;
            }
            else
                printf("输入数字有误,请重新输入!如输入:12\n");
        }
        else
            printf("输入数字有误,请重新输入!如输入:12\n");
            }
    game = GameInitialize(cash,nums);
    if (argc == 2) {
        game->output_file_path = argv[1];
    } else {
        game->output_file_path = "/Users/wangjian/code/C/dian/Monopoly/log";
    }
    cur_player = GameStart(game);
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

int checkDuplicate(char* nums, int length) {
    for(int i = 0; i < length - 1; i++) {
        for(int j = i + 1; j < length; j++) {
            if(nums[i] == nums[j]) {
                return 1;
            }
        }
    }
    return 0;
}


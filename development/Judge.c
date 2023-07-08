#include "Judge.h"
#include "Game.h"
#include "Player.h"
#include "Property.h"
#include "Map.h"
#include <stdio.h>
int IsInPrison(struct Game* game)
{
    if(game->players[game->current_player_index]->position != 49)//玩家处于非监狱
    {    
        printf("Safe\n");
    }
    else if(game->players[game->current_player_index]->position == 49)//玩家处于监狱
    {
        if(game->players[game->current_player_index]->stop_rounds)//仍在监狱中
        {
            game->players[game->current_player_index]->stop_rounds--;
            printf("玩家%c本回合在监狱中，剩余轮空回合数：%d\n",game->players[game->current_player_index]->name,game->players[game->current_player_index]->stop_rounds);
            if(!game->players[game->current_player_index]->stop_rounds)//应该出狱
            {
                game->players[game->current_player_index]->status = NORMAL;
                printf("玩家%c下回合即将出狱，可以正常行动\n",game->players[game->current_player_index]->name);
            }
        }
        else //不在监狱中，坐牢2回合
        {
            game->players[game->current_player_index]->stop_rounds = 2;
            game->players[game->current_player_index]->status = INPRISON;
            printf("寄！玩家%c本回合进入监狱中，剩余轮空回合数：%d\n",game->players[game->current_player_index]->name,game->players[game->current_player_index]->stop_rounds);
        }
    }    
}

int IsInHospital(struct Game* game)
{
    if(game->players[game->current_player_index]->position != 14)//玩家处于非医院
    {    

    }
    else if(game->players[game->current_player_index]->position == 14)//玩家处于医院
    {
        if(game->players[game->current_player_index]->stop_rounds)//玩家处于住院状态
        {
            game->players[game->current_player_index]->stop_rounds--;
            printf("玩家%c本回合在医院中，剩余轮空回合数：%d\n",game->players[game->current_player_index]->name,game->players[game->current_player_index]->stop_rounds);
            if(!game->players[game->current_player_index]->stop_rounds)//应该出院
            {
                game->players[game->current_player_index]->status = NORMAL;
                printf("玩家%c下回合即将出院，可以正常行动\n",game->players[game->current_player_index]->name);
            }
        }
    }
}

int IsInMine(struct Game* game)
{
    if(game->players[game->current_player_index]->position >=64 || game->players[game->current_player_index]->position<=69)//玩家处于矿地
    {    
        switch (game->players[game->current_player_index]->position)
        {
        case 64:
            game->players[game->current_player_index]->points +=60;
            break;
        case 65:
            game->players[game->current_player_index]->points +=80;
            break;
        case 66:
            game->players[game->current_player_index]->points +=40;
            break;
        case 67:
            game->players[game->current_player_index]->points +=100;
            break;
        case 68:
            game->players[game->current_player_index]->points +=80;
            break;
        case 69:
            game->players[game->current_player_index]->points +=20;
            break;
        default:
            break;
        }
    }
}

int IsInBomb(struct Game* game)
{
    if(game->map[game->players[game->current_player_index]->position]->is_tool == BOMB)    
    {
        game->players[game->current_player_index]->position = 14;
        game->players[game->current_player_index]->stop_rounds = 3;
        game->players[game->current_player_index]->status = INHOSPITAL;
        printf("玩家%c被炸伤！即将送往医院......同时轮空3回合\n",game->players[game->current_player_index]->name);
    }
}

int IsBankrupt(struct Game *game)
{
    if(game->players[game->current_player_index]->cash < 0)
    {
        game->player_count -- ;
        game->players[game->current_player_index]->status = Out;//出局标志
        printf("玩家%c破产！其资产将被收回......\n",game->players[game->current_player_index]->name);
        for(int i = 0 ; i < MAP_SIZE ; i++)
        {
            if(game->map[i]->property->owner == game->players[game->current_player_index] )//如果该块地的所有者是破产者，则这块地被收回
            {
                game->map[i]->property->level = 0;//初始化为空地
            }
        }
    }
}

int IsGameOver(struct Game *game)
{
    char winner_real_name;
    if(game->player_count == 1)
    {
        printf("游戏结束!\n");
        for(int i = 0 ; i < 4; i++)
        {
            winner_real_name = (game->players[i]->status != Out ? game->players[i]->name : winner_real_name );
        }
        printf("获胜者是%c\n",winner_real_name);
        
    }
}


int JudgeStatus(struct Game* game)
{
    IsInPrison(game);
    IsInHospital(game);
    IsInMine(game);
    //IsInSpace(game);
    IsInBomb(game);
}

#include "Judge.h"
#include "Game.h"
#include <stdio.h>
int IsInPrison(struct Game* game)
{
    if(game->players[game->current_player_index]->position != 49)//��Ҵ��ڷǼ���
    {    
        printf("Safe\n");
    }
    else if(game->players[game->current_player_index]->position == 49)//��Ҵ��ڼ���
    {
        if(game->players[game->current_player_index]->stop_rounds)//���ڼ�����
        {
            game->players[game->current_player_index]->stop_rounds--;
            printf("���%c���غ��ڼ����У�ʣ���ֿջغ�����%d\n",game->players[game->current_player_index]->name,game->players[game->current_player_index]->stop_rounds);
            if(!game->players[game->current_player_index]->stop_rounds)//Ӧ�ó���
            {
                game->players[game->current_player_index]->status = NORMAL;
                printf("���%c�»غϼ������������������ж�\n",game->players[game->current_player_index]->name);
            }
        }
        else //���ڼ����У�����2�غ�
        {
            game->players[game->current_player_index]->stop_rounds = 2;
            game->players[game->current_player_index]->status = INPRISON;
            printf("�ģ����%c���غϽ�������У�ʣ���ֿջغ�����%d\n",game->players[game->current_player_index]->name,game->players[game->current_player_index]->stop_rounds);
        }
    }    
}

int IsInHospital(struct Game* game)
{
    if(game->players[game->current_player_index]->position != 14)//��Ҵ��ڷ�ҽԺ
    {    

    }
    else if(game->players[game->current_player_index]->position == 14)//��Ҵ���ҽԺ
    {
        if(game->players[game->current_player_index]->stop_rounds)//��Ҵ���סԺ״̬
        {
            game->players[game->current_player_index]->stop_rounds--;
            printf("���%c���غ���ҽԺ�У�ʣ���ֿջغ�����%d\n",game->players[game->current_player_index]->name,game->players[game->current_player_index]->stop_rounds);
            if(!game->players[game->current_player_index]->stop_rounds)//Ӧ�ó�Ժ
            {
                game->players[game->current_player_index]->status = NORMAL;
                printf("���%c�»غϼ�����Ժ�����������ж�\n",game->players[game->current_player_index]->name);
            }
        }
    }
}

int IsInMine(struct Game* game)
{
    if(game->players[game->current_player_index]->position >=64 || game->players[game->current_player_index]->position<=69)//��Ҵ��ڿ��
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
        printf("���%c��ը�ˣ���������ҽԺ......ͬʱ�ֿ�3�غ�\n",game->players[game->current_player_index]->name);
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


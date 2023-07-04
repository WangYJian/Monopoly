#include "Game.h"
#include "map.h"
#include "Player.h"
#include "Property.h"
#include <stdio.h>
#include <malloc.h>
Game* GameInitialize(int initcash,int player_nums){
    /*
    ��ʼ����Ϸ�ĺ���Ҫ��game�Ѿ����ⲿmalloc
    1. ѯ������
    2. ��ʼ���ʼ������������
    3. ��ʼ����ͼ������
    */
    int i = 0;
    Property* temp = NULL;
    struct Game* game = malloc(sizeof(Game));
    game->init_cash = initcash;
    game->player_count = player_nums;
    game->current_player_index = 0;
    printf("��ʼ����ͼ ...\n");
    for(i = 0; i < MAP_SIZE; i++){
        game->map[i] = malloc(sizeof(Map));
        game->map[i]->id = i;
        game->map[i]->player = NULL;
        //��ʼ����Ƥ
        temp = malloc(sizeof(Property));
        temp->id = i;
        temp->level = 0;
        temp->owner = NULL;
        // TODO price �� rent �ĳ�ʼ��
        game->map[i]->property = temp;
        if(i == 0){
            game->map[i]->land_type = START;
        }else if(i < 14){
            game->map[i]->land_type = SPACE;
            continue;
        }else if(i == 14){
            game->map[i]->land_type = HOSPITAL;
        }else if(i < 28){
            game->map[i]->land_type = SPACE;
        }else if(i == 28){
            game->map[i]->land_type = TOOL;
        }else if(i < 35){
            game->map[i]->land_type = SPACE;
        }else if(i == 35){
            game->map[i]->land_type = GIFT;
        }else if(i < 49){
            game->map[i]->land_type = SPACE;
        }else if(i == 49){
            game->map[i]->land_type = PRISON;
        }else if(i < 63){
            game->map[i]->land_type = SPACE;
        }else if(i == 63){
            game->map[i]->land_type = MAGIC;
        }else if(i< 70){
            game->map[i]->land_type = MINERAL;
        }
    }
    printf("��ͼ�������! \n");
    //system("cls");
    return game;

    
}

void GameStart(struct Game* game){
    /*
    ��ʼ��Ϸ
    1. �������
    2. �����һ����һغ�
    */
    int i = 0;
    char name[4] = {'A','Q','S','J'};
    for(i = 0; i < game->player_count; i++){
        game->players[i] = malloc(sizeof(Player));
        game->players[i]->bomb_count = 0;
        game->players[i]->barrier_count = 0;
        game->players[i]->robot_count = 0;
        game->players[i]->god_count = 0;
        game->players[i]->status = 0;
        game->players[i]->stop_rounds = 0;
        game->players[i]->position = 0;
        game->players[i]->cash = game->init_cash;
        game->players[i]->name = name[i];
        game->players[i]->id = i;
        game->players[i]->points = 0;
    }
    GameDisplayMap(game);
    // TODO ������һغ�
}
char level_char(int level){
    char ch;
    switch (level)
    {
    case 0:
        ch = '0';
        break;
    case 1:
        ch = '1';
        break;
    case 2:
        ch = '2';
        break;
    
    case 3:
        ch = '3';
        break;
    }
    return ch;
}
char Tool_char(int idx){
    char ch;
    switch (idx)
    {
    case 1:
        ch = '#';
        break;
    case 2:
        ch = '@';
        break;
    default:
        ch = '0';
        break;
    }
    return ch;
}

void GameDisplayMap(const struct Game* game){
    /*
    ������ʾ��ͼ
    1. ע����ʾ���ǵ����ȼ�
    2. ��Ƥ��ɫ��todo
    ����߼�
    �Ƚ���Ӧ�ַ��ŵ���ά�����Ӧ��λ�ã�Ȼ����Щλ�ô�ӡ
    */
    int i = 0;
    int j = 0;
    char drawmap[8][30];
     for(i = 0; i < 8; i++){
        for(j = 0; j < 30; j++){
            drawmap[i][j] = ' ';
        }
    }
    // �����ӡ��һ�У����г���14�ţ��������е���
    for(i = 0; i < 29; i++){
        if(game->map[i]->player != NULL){
            drawmap[0][i] = game->map[i]->player->name;
        }else if(game->map[i]->land_type == SPACE && game->map[i]->is_tool)
            drawmap[0][i] = Tool_char(game->map[i]->is_tool);
        else if(game->map[i]->land_type == SPACE && !game->map[i]->property->level){
            drawmap[0][i] = level_char(game->map[i]->property->level);
        }
        else 
            drawmap[0][i] = game->map[i]->land_type;
    }
    for(i = 0; i < 8; i++)
        drawmap[i][29] = '\n';

    // ��ӡ�ұߣ�
    for(i = 0; i < 8; i++){
        if(game->map[28+i]->player != NULL){
            drawmap[i][28] = game->map[28+i]->player->name;
        }else if(game->map[28+i]->is_tool && game->map[28+i]->land_type == SPACE)
            drawmap[i][28] = Tool_char(game->map[28+i]->is_tool);
        else if(!game->map[28+i]->property->level && game->map[28+i]->land_type == SPACE)
            drawmap[i][28] = level_char(game->map[28+i]->property->level);
        else
            drawmap[i][28] = game->map[28+i]->land_type;
    }

    //��ӡ�±�
    for(i = 28; i >=0; i--){
        j = 28 - i;
        if(game->map[35+j]->player != NULL){
            drawmap[7][i] = game->map[35+j]->player->name;
        }else if(game->map[35+j]->land_type == SPACE && game->map[35+j]->is_tool)
            drawmap[7][i] = Tool_char(game->map[35+j]->is_tool);
        else if(game->map[35+j]->land_type == SPACE && !game->map[35+j]->property->level)
            drawmap[7][i] = level_char(game->map[35+j]->property->level);
        else
            drawmap[7][i] = game->map[35+j]->land_type;
    }

    // ��ӡ���,�������ܹ����Ƥ������ֻ��Ҫ��һ����
    for(i = 6; i >= 1;i--){
        j = 7 - i;
        if(game->map[63+j]->player != NULL){
            drawmap[i][0] = game->map[63+j]->player->name;
        }else if(game->map[63+j]->land_type == SPACE && game->map[63+j]->is_tool)
            drawmap[i][0] = Tool_char(game->map[63+j]->is_tool);
        else
            drawmap[i][0] = game->map[63+j]->land_type;
    }


    for(i = 0; i < 8; i++){
        for(j = 0; j < 30; j++){
            printf("%c",drawmap[i][j]);
        }
    }
        
    
}
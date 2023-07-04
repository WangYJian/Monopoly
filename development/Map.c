#include "Map.h"
#include "Player.h"
#include<stdio.h>
void AddPlayerMap(Map* map,Player* player){
    int nums = map->player_nums;
    if(nums>4)
        printf("人数超过4！！");
    else{
        
        map->player[nums] = player;
        map->player_nums++;
    }
    
}

void DelPlayerMap(Map* map,Player* player){
    int i = 0;
    for(i = 0; i < map->player_nums; i++){
        if(map->player[i]->name == player->name){
            if(i == 3){
                map->player[i] = NULL;
            }else{
                while(i<map->player_nums-1){
                    map->player[i] = map->player[i+1];
                }
                map->player[i] = NULL; // 最后那个置空
            }
        }
    }
}
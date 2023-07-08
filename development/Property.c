#include <stdlib.h>
#include "Property.h"
#include "Player.h"



// 初始化土地
Property * PropertyInitialize(Property *property, int price){
    property->price = price;
    property->level = 0;
    property->value = price;
    property->owner = NULL;
    return property;
}

// 设置物业所有者
void PropertySetOwner(Property* property, Player *player){
    property->level = 0;
    property->value = property->price;
    property->owner = player;
}

// 升级物业
void PropertyUpgrade(Property* property){
    property->level++;
    property->value += property->price;
}
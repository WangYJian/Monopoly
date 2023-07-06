#ifndef DEVELOPMENT_PROPERTY_H
#define DEVELOPMENT_PROPERTY_H

typedef struct Player Player;

// 定义土地的结构体
    typedef struct Property {
        int id; // 土地ID
        int price; // 土地价格
        int level; // 土地等级：茅屋、洋房、摩天楼
        int value; // 土地总价值
        Player* owner; // 土地的拥有者
    } Property;

// 方法
Property* PropertyInitialize(int id, int price);  // 初始化土地
void PropertySetOwner(struct Property* property, Player *player);  // 设置物业所有者
void PropertyUpgrade(struct Property* property);  // 升级物业
void PropertySell(struct Property* property);  // 出售物业
void PropertyGetRent(const struct Property* property);  // 获取物业的租金


#endif

#ifndef DEVELOPMENT_TOOL_H
#define DEVELOPMENT_TOOL_H

// 定义道具的结构体
typedef struct Tool {
    int id; // 道具ID
    char name[50]; // 道具名称
    int points; // 道具所需积分
} Tool;


// 方法
void ToolActivate(struct Tool* tool, int playerID, int targetLocation);  // 激活道具
void ToolDeactivate(struct Tool* tool);  // 禁用道具


#endif

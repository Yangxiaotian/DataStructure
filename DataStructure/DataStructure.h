//
//  LinkList.h
//  DataStructure
//
//  Created by 杨笑天 on 2016/10/5.
//  Copyright © 2016年 杨笑天. All rights reserved.
//
#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define INIT_LIST_SIZE 3
#define INCREMENT 5
typedef int Status;
typedef struct {
    char name[20];
    int num;
    float price;
    char remark[50];
}ElemType;
typedef struct {
    ElemType *elem;
    int length;
    int listsize;
}SqList;
//元素e2赋值给e1
Status Copy(ElemType *e1, ElemType *e2) {
    strcpy(e1->name, e2->name);
    e1->num = e2->num;
    e1->price = e2->price;
    strcpy(e1->remark, e2->remark);
    return OK;
}
//输出元素
Status PrintElem(ElemType e) {
    printf("%s\t%d\t%.2f\t%s\n", e.name, e.num, e.price, e.remark);
    return OK;
}



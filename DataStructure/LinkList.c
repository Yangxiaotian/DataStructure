//
//  LinkList.c
//  DataStructure
//
//  Created by 杨笑天 on 2016/10/5.
//  Copyright © 2016年 杨笑天. All rights reserved.
//

#include "DataStructure.h"
typedef struct LNode {
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;
//初始化链表
Status InitList_lk(LinkList L) {
    L->next = NULL;
    return OK;
}
//获取第i个元素
Status GetElem_lk(LinkList L, int i, ElemType *e) {
    //L为带头节点的单链表指针
    //当第i个元素存在时，其值赋给e并返回OK，否则返回ERROR
    LinkList p = L->next;
    int j = 1;
    //此while循环最多运行i-1次，（如只有一个元素的链表，取第1个元素运行0次）
    //加上p的意思：p为尾节点指向的next时退出循环，因为有可能i超出链表的长度，用这个p来结束循环可以避免空指针错误
    while(p && j < i) {
        p = p->next;
        ++j;
    }
    /*
     *  !p表示因为p为NULL而跳出循环，即到达了尾节点，当i>n时的情况
     *  如果进了while循环j最大不会超过i，所以这里j>i只表示不进循环的情况即i<1的情况
     *  也可以写成这样，if(!p || i < 1) return ERROR;
     */
    if(!p || j > i) return ERROR;
    Copy(e, &p->data);
    return OK;
}
//从第i个位置插入元素
Status InsertList_lk(LinkList L, int i, ElemType e) {
    LinkList p = L;
    int j = 0;
    //此while循环最多运行i-1次，（如往第1个位置插入元素，不进入循环）
    while(p && j < i-1) {
        p = p->next;
        ++j;
    }
    if(!p || j > i-1) return ERROR;
    LinkList temp = p->next;
    LinkList newNodeP = (LinkList)malloc(sizeof(LNode));
    newNodeP->next = temp;
    Copy(&(newNodeP->data), &e);
    p->next = newNodeP;
    return OK;
}



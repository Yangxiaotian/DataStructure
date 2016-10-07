//
//  main.c
//  DataStructure
//
//  Created by 杨笑天 on 2016/10/3.
//  Copyright © 2016年 杨笑天. All rights reserved.
//
#include "DataStructure.h"
//取值
Status GetElem_sq(SqList L, int i, ElemType *e) {
    if(i<1 || i>L.length) return ERROR;
    Copy(e, L.elem+i-1);
    return OK;
}
//是否相等
Status IsEqual(ElemType e1, ElemType e2) {
    return strcmp(e1.name, e2.name)==0 &&
            e1.num == e2.num &&
            fabs(e1.price-e2.price)<0.001 &&
    strcmp(e1.remark, e2.remark)==0;
}
//比较大小
Status Compare(ElemType e1, ElemType e2) {
    return e1.num < e2.num;
}
//查找元素e的位置
int LocateElem_sq(SqList L, ElemType e, Status (*IsEqual)(ElemType, ElemType)) {
    int i;
    for(i = 1; i <= L.length; ++i) {
        if(IsEqual(L.elem[i-1], e)) return i;
    }
    return 0;
}
//初始化线性表
Status InitList_sq(SqList *L) {
    L->elem = (ElemType*)malloc(sizeof(ElemType)*INIT_LIST_SIZE);
    if(!L->elem) exit(OVERFLOW);
    L->length = 0;
    L->listsize = INIT_LIST_SIZE;
    return OK;
}
//插入线性表
Status InsertList_sq(SqList *L, int i, ElemType e) {
    if(i<1 || i>L->length+1) return ERROR;
    if(L->length >= L->listsize) {
        ElemType *newbase = (ElemType*)realloc(L->elem, sizeof(ElemType)*(L->listsize+INCREMENT));
        if(!newbase) exit(OVERFLOW);
        L->elem = newbase;
        L->listsize += INCREMENT;
    }
    ElemType *q = L->elem+i-1;
    ElemType *p;
    for(p = L->elem+L->length-1; p >= q; --p) {
        Copy(p+1, p);
    }
    Copy(q, &e);
    L->length++;
    return OK;
    
}
//删除线性表元素
Status DeleteList_sq(SqList *L, int i, ElemType *e) {
    if(i<1 || i>L->length) return ERROR;
    ElemType *q = L->elem+L->length-1;
    Copy(e, q);
    ElemType *p;
    for(p = q; p < L->elem+L->length; ++p) {
        Copy(p, p+1);
    }
    L->length--;
    return OK;
}
//A、B两个线性表并集
Status Union_sq(SqList *La, SqList *Lb) {
    int i;
    for(i = 1; i <= Lb->length; ++i) {
        ElemType e;
        GetElem_sq(*Lb, i, &e);
        if(!LocateElem_sq(*La, e, &IsEqual)) {
            InsertList_sq(La, La->length+1, e);
        }
    }
    return OK;
};
//A、B两已排序表归并
Status Merge_sq(SqList La, SqList Lb, SqList *Lc) {
    InitList_sq(Lc);
    int i=1, j=1, k=0;
    ElemType a, b;
    while(i <= La.length && j <= Lb.length) {
        GetElem_sq(La, i, &a);
        GetElem_sq(Lb, j, &b);
        if(Compare(a, b)) {
            InsertList_sq(Lc, ++k, a);
            ++i;
        }else {
            InsertList_sq(Lc, ++k, b);
            ++j;
        }
    }
    while(i <= La.length) {
        GetElem_sq(La, i++, &a);
        InsertList_sq(Lc, ++k, a);
    }
    while(j <= Lb.length) {
        GetElem_sq(Lb, j++, &b);
        InsertList_sq(Lc, ++k, b);
    }
    return OK;
}
//输出列表
Status PrintList_sq(SqList L) {
    int i;
    for(i=0; i<L.length; ++i) {
        printf("%d.\t", i+1);
        PrintElem(L.elem[i]);
    }
    return OK;
}
int main(int argc, const char * argv[]) {
    SqList L;
    InitList_sq(&L);
    ElemType e;
    //插入测试
    printf("插入测试：\n---------------------\n");
    printf("输入名称\t数量\t价格\t备注：");
    scanf("%s%d%f%s", e.name, &e.num, &e.price, e.remark);
    InsertList_sq(&L, 1, e);
    PrintList_sq(L);
    //删除测试
    printf("删除测试：\n---------------------\n");
    ElemType del;
    DeleteList_sq(&L, 1, &del);
    PrintElem(del);
    //并集测试
    printf("并集测试：\n---------------------\n");
    SqList La, Lb;
    InitList_sq(&La);
    InitList_sq(&Lb);
    int i;
    for(i = 0; i < 5; ++i) {
        printf("输入名称\t数量\t价格\t备注：");
        scanf("%s%d%f%s", e.name, &e.num, &e.price, e.remark);
        InsertList_sq(&La, La.length+1, e);
    }
    PrintList_sq(La);
    for(i = 0; i < 5; ++i) {
        printf("输入名称\t数量\t价格\t备注：");
        scanf("%s%d%f%s", e.name, &e.num, &e.price, e.remark);
        InsertList_sq(&Lb, Lb.length+1, e);
    }
    PrintList_sq(Lb);
    printf("-----------------------------------------\n");
    //Union_sq(&La, &Lb);
    PrintList_sq(La);
    //归并测试
    SqList Lc;
    printf("归并测试：\n---------------------\n");
    Merge_sq(La, Lb, &Lc);
    PrintList_sq(Lc);
    return 0;
}

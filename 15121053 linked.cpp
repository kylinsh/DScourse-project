//
//  linked.cpp
//  2018数据结构与算法试验题 链表
//  於肖立 15121053
//
//  Created by Li on 2019/1/10.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define LIST_INIT_SIZE 100
#define LIST_SIZE_INCR 10

typedef int Status;
typedef int ElemType;
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

void InitSet_Lk(LinkList &L){
    L = (LNode *)malloc(sizeof(LNode));
    L->next = NULL;
}

LinkList La, Lb, Lc;

int Search(LinkList L, ElemType a){
    LNode *c = L;
    int i = 0; 
    while (c->data != a) {
        if (c->next == NULL) return ERROR;
        c = c->next;
        i++;
    }
    return i;
}

Status AddElement_Lk(LinkList &L, ElemType e){
    LinkList p = L;
    int j = 0;
    while(p){
        p = p->next;
        ++j;
    }
    if(Search(L, e) == 0) return ERROR;
    else{
        LNode *s;
        s = (LinkList)malloc(sizeof(LNode));
        s->data = e;
        s->next = p->next;
        p->next = s;
        return OK;
    }
}

Status DeleteElement_Lk(LinkList &L, ElemType e){
    LinkList p = L;
    int j = 0;
    int i = Search(L, e);
    while(p->next && j > i-1){
        p = p->next;
        ++j;
    }
    LNode *q = p->next;
    p->next = q->next;
    e = q->data;
    free(q);
    return OK;
}

void Print_Lk(LinkList &L){
    LinkList p;
    if(L->next == NULL) std::cout << "This set is empty.\n";
    else{
        for(p = L->next; p != NULL; p = p->next) printf("%d ", p->data);
        std::cout << "\n";
    }
}

void Union_Lk(LinkList La, LinkList Lb, LinkList &Lc){
    LNode *pa = La->next;
    LNode *pb = Lb->next;
    LNode *pc;
    Lc = pc = La;
    while(pa){
        if(Search(Lb, pa->data) != 0){
            pa = pa->next;
        }
        else{
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
    }
    while(pb){
        pc->next = pb;
        pc = pb;
        pb = pb->next;
    }
    free(Lb);
}

void Intersection_Lk(LinkList La, LinkList Lb, LinkList &Lc){
    LNode *pa = La->next;
    LNode *pc;
    Lc = pc = La;
    while(pa){
        if(Search(Lb, pa->data) != 0){
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
    }
    free(Lb);
}

void Difference_Lk(LinkList La, LinkList Lb, LinkList &Lc){
    LNode *pa = La->next;
    LNode *pc;
    Lc = pc = La;
    while(pa){
        if(Search(Lb, pa->data) != 0){
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
    }
    free(Lb);
}

int main(){
	InitSet_Lk(La);
	InitSet_Lk(Lb);
	InitSet_Lk(Lc);
    AddElement_Lk(La, 1);
    AddElement_Lk(La, 3);
    AddElement_Lk(La, 5);
    AddElement_Lk(La, 7);
    AddElement_Lk(La, 9);
    AddElement_Lk(La, 10);
    AddElement_Lk(Lb, 2);
    AddElement_Lk(Lb, 3);
    AddElement_Lk(Lb, 4);
    AddElement_Lk(Lb, 5);
    AddElement_Lk(Lb, 6);
    AddElement_Lk(Lb, 8);
    AddElement_Lk(Lb, 10);

	while(TRUE){
		InitSet_Lk(Lc);
		printf("Menu\n");
		printf("IA: Insert new elements into set A.          DA: Delete existing elements from set A.\n");
		printf("IB: Insert new elements into set B.          DB: Delete existing elements from set B.\n");
		printf("OU: Take the union of set A and set B.       OI: Take the intersection of set A and set B.\n");
		printf("OD: Take the difference of set B from set A. Q: Quit application.\n");
		printf("Enter command ==>\n");
    
    	std::string s;
    	int e;
    	std::cin >> s;
		if(s == "IA"){
        	printf("Input new element for set A:");
        	scanf("%d", &e);
        	if(AddElement_Lk(La, e) == ERROR) std::cout << "This element already exists in set A.\n";
        	else(printf("Element %d is added to set A successfully.\n", e));
    	}
    	if(s == "DA"){
			printf("Input the element needed to be deleted from set A:");
			scanf("%d", &e);
			if(DeleteElement_Lk(La, e) == ERROR) std::cout << "This element does not exist in set A.\n";
			else(printf("Element %d is deleted from set A successfully.\n", e));
    	}
    	if(s == "IB"){
			printf("Input new element for set B:");
			scanf("%d", &e);
			if(AddElement_Lk(Lb, e) == ERROR) std::cout << "This element already exists in set B.\n";
        	else(printf("Element %d is added to set B successfully.\n", e));
    	}
    	if(s == "DB"){
			printf("Input the element needed to be deleted from set B:");
			scanf("%d", &e);
			if(DeleteElement_Lk(Lb, e) == ERROR) std::cout << "This element does not exist in set B.\n";
			else(printf("Element %d is deleted from set B successfully.\n", e));
    	}
		if(s == "OU"){
        	Union_Lk(La, Lb, Lc);
			printf("The union of set A and B is listed below:\n");
			Print_Lk(Lc);
    	}
		if(s == "OI"){
        	Intersection_Lk(La, Lb, Lc);
			printf("The intersection of set A and B is listed below:\n");
			Print_Lk(Lc);
    	}
		if(s == "OD"){
        	Difference_Lk(La, Lb, Lc);
			printf("The difference of set B from set A is listed below:\n");
			Print_Lk(Lc);
    	}
    	if(s == "Q"){
			std::cout << "You are about to quit this application.";
			return 0;
		}
	}
}

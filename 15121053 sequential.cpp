//
//  sequential.cpp
//  2018数据结构与算法试验题 顺序表
//  於肖立 15121053
//
//  Created by Li on 2018/12/31.
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
typedef struct{
	ElemType *elem;
	int length;
	int listsize;
}SqList;

SqList La, Lb, Lc;

Status InitSet_Sq(SqList &L){
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if(!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

Status AddElement_Sq(SqList &L, ElemType e){
    int *p = 0;
    int *newbase = 0;
    int *q = 0;
	for(p = &(L.elem[0]); p <= &(L.elem[L.length-1]); p++){
		if(*p == e) return ERROR;
	}
	if(L.length >= L.listsize){
		newbase = (ElemType *)realloc(L.elem, (L.listsize + LIST_SIZE_INCR) * sizeof(ElemType));
		if(!newbase) exit(OVERFLOW);
		L.elem = newbase;
		L.listsize += LIST_SIZE_INCR;
	}
	q = &(L.elem[L.length]);
	*q = e;
	++L.length;
	return OK;
}

int Search(SqList L, ElemType a){
    int *p = 0;
	int i = -1;
	for(p = &(L.elem[0]); p <= &(L.elem[L.length-1]); p++){
		if(*p == a){
			i = *p;
			return i;
		}
	}
	return i;
}

Status DeleteElement_Sq(SqList &L, ElemType a){
	int i;
    int *p = 0;
    int e;
    int *q = 0;
	i = Search(L, a);
	if(i == -1) return ERROR;
	p = &(L.elem[i-1]);
	e = *p;
	q = L.elem + L.length - 1;
	for(++p; p <= q; ++p) *(p-1) = *p;
	--L.length;
	return OK;
}

Status Clear_Sq(SqList &L){
	free(L.elem);
	L.elem = NULL;
	return OK;
}

void Print_Sq(SqList L){
	int i;
	for(i = 0; i < L.length; i++) std::cout << L.elem[i] <<" ";
	if(L.length == 0) printf("The set is empty.");
	printf("\nThe number of elements in this set is %d.\n", L.length);
}

void Union_Sq(SqList La, SqList Lb, SqList &Lc){
	int i;
	Lc.length = 0;
	for(i = 0; i < La.length; i++) Lc.elem[Lc.length++] = La.elem[i];
	for(i = 0; i < Lb.length; i++) AddElement_Sq(Lc, Lb.elem[i]);
}

void Intersection_Sq(SqList La, SqList Lb, SqList &Lc){
	int i, j;
	for(i = 0; i < Lb.length; i++){
		for(j = 0; j < La.length; j++){
			if(La.elem[j] == Lb.elem[i]) AddElement_Sq(Lc, Lb.elem[i]);
		}
	}
}

void Difference_Sq(SqList La, SqList Lb, SqList &Lc){
	int i;
	Lc.length = 0;
	for(i = 0; i < La.length; i++) Lc.elem[Lc.length++] = La.elem[i];
	for(i = 0; i < Lb.length; i++) DeleteElement_Sq(Lc, Lb.elem[i]);
}

int main(){
	InitSet_Sq(La);
	InitSet_Sq(Lb);
	InitSet_Sq(Lc);
    AddElement_Sq(La, 1);
    AddElement_Sq(La, 3);
    AddElement_Sq(La, 5);
    AddElement_Sq(La, 7);
    AddElement_Sq(La, 9);
    AddElement_Sq(La, 10);
    AddElement_Sq(Lb, 2);
    AddElement_Sq(Lb, 3);
    AddElement_Sq(Lb, 4);
    AddElement_Sq(Lb, 5);
    AddElement_Sq(Lb, 6);
    AddElement_Sq(Lb, 8);
    AddElement_Sq(Lb, 10);

	while(TRUE){
		InitSet_Sq(Lc);
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
        	if(AddElement_Sq(La, e) == ERROR) std::cout << "This element already exists in set A.\n";
        	else(printf("Element %d is added to set A successfully.\n", e));
    	}
    	if(s == "DA"){
			printf("Input the element needed to be deleted from set A:");
			scanf("%d", &e);
			if(DeleteElement_Sq(La, e) == ERROR) std::cout << "This element does not exist in set A.\n";
			else(printf("Element %d is deleted from set A successfully.\n", e));
    	}
    	if(s == "IB"){
			printf("Input new element for set B:");
			scanf("%d", &e);
			if(AddElement_Sq(Lb, e) == ERROR) std::cout << "This element already exists in set B.\n";
        	else(printf("Element %d is added to set B successfully.\n", e));
    	}
    	if(s == "DB"){
			printf("Input the element needed to be deleted from set B:");
			scanf("%d", &e);
			if(DeleteElement_Sq(Lb, e) == ERROR) std::cout << "This element does not exist in set B.\n";
			else(printf("Element %d is deleted from set B successfully.\n", e));
    	}
		if(s == "OU"){
        	Union_Sq(La, Lb, Lc);
			printf("The union of set A and B is listed below:\n");
			Print_Sq(Lc);
    	}
		if(s == "OI"){
        	Intersection_Sq(La, Lb, Lc);
			printf("The intersection of set A and B is listed below:\n");
			Print_Sq(Lc);
    	}
		if(s == "OD"){
        	Difference_Sq(La, Lb, Lc);
			printf("The difference of set B from set A is listed below:\n");
			Print_Sq(Lc);
    	}
    	if(s == "Q"){
			std::cout << "You are about to quit this application.";
			return 0;
		}
	}
}

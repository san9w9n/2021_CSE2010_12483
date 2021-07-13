#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

typedef struct Node {
    int data;
    struct Node* nextNode;
} Node;

typedef struct LinkedList {
    int curCount;
    Node headNode;
} LinkedList;

typedef struct StackNode {
	int data;
	struct StackNode* next;
} StackNode;

int isEmptyStack(StackNode* top) {
	if (top == NULL)
		return TRUE;
	else
		return FALSE;
}
//stack관련 함수
void pushLinkedStack(StackNode** top, int data) {
	StackNode *pNode = NULL;

	pNode = (StackNode*)malloc(sizeof(StackNode));
	pNode->data = data;
	pNode->next = NULL;

	if(isEmptyStack(*top)) *top = pNode;
	else {
		pNode->next = *top;
		*top = pNode;
	}
}
StackNode* popLinkedStack(StackNode** top) {
	StackNode *pNode = NULL;

	if(isEmptyStack(*top)) {
		printf("The Stack is empty\n");
		return NULL;
	}
	pNode = *top;
	*top = pNode->next;
	pNode->next = NULL;

	return pNode;
}

void showNode(LinkedList* pList) {
    int i=0;

    if(pList==NULL){
        printf("showNode() error\n");
        return;
    }
    
    Node *pNode = NULL;
    printf("현재 Node 개수: %d \n", pList->curCount);
    pNode = pList->headNode.nextNode;

    while(pNode!=NULL) {
        printf("[%d]\n", pNode->data);
        pNode = pNode->nextNode;
    }
    printf("------------------------------\n");
}

int isEmpty(LinkedList* pList) {
    if(pList==NULL) {
        printf("isEmpty() error\n");
        return -1;
    }

    if(pList->headNode.nextNode==NULL) return TRUE;
    else return FALSE;
}

int addNode(LinkedList* pList, int pos, int data) {
    int i=0;
    Node *pNewNode = NULL, *pTmpNode = NULL;
    
    if(pList==NULL) {
        printf("addNode() error1 \n");
        return FALSE;
    }
    if(pos<0 || pos > pList->curCount) {
        printf("addNode() error2: 추가 범위 초과 \n");
        return FALSE;
    }

    pNewNode = (Node*)malloc(sizeof(Node));
    if(!pNewNode) {
        printf("addNode() error3 \n");
        return FALSE;
    }

    pNewNode->data = data;
    pNewNode->nextNode = NULL;

    pTmpNode=&(pList->headNode);
    for(i=0; i<pos; i++){
        pTmpNode = pTmpNode->nextNode;
    }

    pNewNode->nextNode = pTmpNode->nextNode;
    pTmpNode->nextNode = pNewNode;
    pList->curCount++;

    return TRUE;
}

int removeNode(LinkedList* pList, int pos) {
    int i=0;
    Node *pDelNode = NULL, *pTmpNode = NULL;

    if(pList==NULL) {
        printf("removeNode() error1 \n");
        return FALSE;
    }
    if(pos<0 || pos > pList->curCount) {
        printf("removeNode() error2: 삭제 범위 초과 \n");
        return FALSE;
    }

    pTmpNode = &(pList->headNode);
    for(i=0; i<pos; i++) pTmpNode = pTmpNode->nextNode;

    pDelNode = pTmpNode->nextNode;
    pTmpNode->nextNode = pDelNode->nextNode;

    free(pDelNode);
    pList->curCount--;
    return TRUE;
}

int findPos(LinkedList* pList, int data) {
    int pos=0;
    Node *pTmpNode=NULL;
    if(pList == NULL) {
        printf("findPos() error \n");
        return FALSE;
    }
    pTmpNode = pList->headNode.nextNode;

    while(pTmpNode!=NULL){
        if(pTmpNode->data == data) return pos;
        pos++;
        pTmpNode=pTmpNode->nextNode;
    }
    return FALSE;
}

void makeEmpty(LinkedList* pList) {
    Node* pDummyNode = NULL, *pTmpNode = NULL;
    if (pList != NULL) {
        pTmpNode = pList->headNode.nextNode;
        while (pTmpNode!=NULL){
            pDummyNode = pTmpNode;
            pTmpNode = pTmpNode->nextNode;
            free(pDummyNode);
        }
        pList->headNode.nextNode = NULL;
        pList->curCount = 0;
    }
}
void showLInkedStack(StackNode* top) {
	StackNode* pNode = NULL;
	if (isEmptyStack(top)) {
		printf("the stack is empty\n");
		return;
	}

	pNode = top;
	printf("==============Show Stack===============\n");
	while (pNode != NULL) {
		printf("[%d]\n", pNode->data);
		pNode = pNode->next;
	}
	printf("=======================================\n");
}

void reverseList(LinkedList* pList, StackNode** top) {
    Node* pNode = NULL;
    StackNode *sNode = NULL;

    printf("Reverse Linked List!\n");

    pNode = &(pList->headNode);
    pNode = pNode->nextNode;

    while(pNode != NULL) {
        pushLinkedStack(top, pNode->data);
        pNode = pNode->nextNode;
    }
    makeEmpty(pList);
    while(!isEmptyStack(*top)) {
        sNode = popLinkedStack(top);
        addNode(pList, pList->curCount, sNode->data);
    }

}

int main() {
    int pos;
    LinkedList* linkedList = (LinkedList*)malloc(sizeof(LinkedList));
    linkedList->curCount = 0;
    linkedList->headNode.nextNode = NULL;

    StackNode* top = NULL;
    StackNode* pNode;

    // showNode(linkedList);
    addNode(linkedList, 0, 10);
    addNode(linkedList, 5, 100);
    addNode(linkedList, 1, 20);
    addNode(linkedList, 2, 30);
    addNode(linkedList, 1, 50);
    addNode(linkedList, 1, 70);
    addNode(linkedList, 1, 40);

    showNode(linkedList);

    reverseList(linkedList, &top);

    showNode(linkedList);

    // removeNode(linkedList, 1);
    // showNode(linkedList);

    // pos = findPos(linkedList, 30);
    // printf("the location of node with data '30': %d\n", pos);

    makeEmpty(linkedList);
    showNode(linkedList);
    return 0;
}
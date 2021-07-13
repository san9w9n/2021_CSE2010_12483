#define TESTCASE_PATH "testCases.txt"
#define BUFFSIZE 1024

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct polyTerm_ {
	int exp;
	int coeff;
	struct polyTerm_* next;
} polyTerm;

typedef struct poly_ {
	polyTerm* head;
} poly;

void initPoly(poly* A) {
	A->head = NULL;
}

void clearPoly(poly* A) {
	polyTerm *delTerm=NULL, *tmpTerm=NULL;
    tmpTerm=A->head;
    while(tmpTerm!=NULL) {
        delTerm=tmpTerm;
		tmpTerm=tmpTerm->next;
        free(delTerm);
    }
	A->head=NULL;
}

void printPoly_impl(poly A, char* buffer) {
	polyTerm *tmpTerm=NULL;
    char tmp[1024] = "";
    tmpTerm = A.head;
    int i=0;
	if(tmpTerm==NULL) {
		strcat(buffer, "0");
	}
	else{
		while(tmpTerm!=NULL) {
			if(i==0) {
				sprintf(tmp,"%dx^%d",tmpTerm->coeff,tmpTerm->exp);
			}
			else{
				if(tmpTerm->coeff < 0){
					sprintf(tmp,"%dx^%d",tmpTerm->coeff,tmpTerm->exp);
				}
				else if(tmpTerm->coeff > 0){
					sprintf(tmp,"+%dx^%d",tmpTerm->coeff,tmpTerm->exp);
				}
				else {
                    i++;
                    tmpTerm=tmpTerm->next;
                    continue;
                }
			}
			i++;
			tmpTerm=tmpTerm->next;
			strcat(buffer, tmp);
		}
	}
}

void printPoly(poly A) {
	char buffer[BUFFSIZE] = "";
	printPoly_impl(A, buffer);
	printf(buffer);
}

void addTerm(poly* A, int exp, int coeff) {
	polyTerm *tmp=NULL, *newTerm=NULL;
	if(coeff!=0){
		tmp=A->head;
		if(tmp==NULL) {
			A->head=(polyTerm*)malloc(sizeof(polyTerm));
			A->head->coeff=coeff;
			A->head->exp=exp;
			A->head->next=NULL;
		}
		else {
			if(A->head->exp<=exp){
				if(A->head->exp==exp) {
						A->head->coeff += coeff;
				}
				else {
					newTerm = (polyTerm*)malloc(sizeof(polyTerm));
					newTerm->exp = exp;
					newTerm->coeff = coeff;
					newTerm->next = A->head;
					A->head=newTerm;
				}
			}
			else{
				while(tmp->next!=NULL){
					if(tmp->next->exp <= exp) break;
					tmp=tmp->next;
				}
				if(tmp->next==NULL) {
					newTerm = (polyTerm*)malloc(sizeof(polyTerm));
					newTerm->exp = exp;
					newTerm->coeff = coeff;
					newTerm->next = NULL;
					tmp->next = newTerm;
				}
				else if(tmp->next->exp<=exp) {
					if(tmp->next->exp==exp) {
						tmp->next->coeff += coeff;
					}
					else {
						newTerm = (polyTerm*)malloc(sizeof(polyTerm));
						newTerm->exp = exp;
						newTerm->coeff = coeff;
						newTerm->next = tmp->next;
						tmp->next = newTerm;
					}
				}
			}
		}
	}
}

poly multiPoly(poly A, poly B) {
	polyTerm *tmpA=NULL, *tmpB=NULL;

    poly target;
	target.head=NULL;
	
    tmpA=A.head;
    tmpB=B.head;
	if(tmpA!=NULL && tmpB!=NULL) {
		addTerm(&target, tmpA->exp + tmpB->exp, tmpA->coeff * tmpB->coeff);
		while(tmpB->next!=NULL) {
			tmpB=tmpB->next;
			addTerm(&target, tmpA->exp + tmpB->exp, tmpA->coeff * tmpB->coeff);
		}
		while(tmpA->next!=NULL) {
			tmpA=tmpA->next;
			tmpB=B.head;
			addTerm(&target, tmpA->exp + tmpB->exp, tmpA->coeff * tmpB->coeff);
			while(tmpB->next!=NULL) {
				tmpB=tmpB->next;
				addTerm(&target, tmpA->exp + tmpB->exp, tmpA->coeff * tmpB->coeff);
			}
		}
	}
    return target;
}

void testPoly() { //You don't have to use this func.
	int breakFlag = 0;
	int breakPoint = -1;
	FILE* fp = fopen(TESTCASE_PATH, "r");
	poly A, B;
	initPoly(&A);
	initPoly(&B);

	int T;
	fscanf(fp, "%d\n", &T);

	char lastTrue[BUFFSIZE] = "";
	char lastAnswer[BUFFSIZE] = "";

	while (T--) {
		char inputOp0, inputOp1;
		char inputStr[BUFFSIZE] = "";
		char buffer[BUFFSIZE] = "";
		int caseNum;

		fscanf(fp, "%d %c ", &caseNum, &inputOp0);

		if (inputOp0 == 'a') {
			int exp, coeff;
			fscanf(fp, "%c %d %d\n", &inputOp1, &exp, &coeff);
			if (inputOp1 == 'A') {
				addTerm(&A, exp, coeff);
			}
			else if (inputOp1 == 'B') {
				addTerm(&B, exp, coeff);
			}
		}

		else if (inputOp0 == 'p') {
			fscanf(fp, "%c\n%s\n", &inputOp1, inputStr);
			if (inputOp1 == 'A') {
				printPoly_impl(A, buffer);
			}
			else if (inputOp1 == 'B') {
				printPoly_impl(B, buffer);
			}

			if (strcmp(inputStr, buffer) != 0) {
				breakFlag = 1;
				breakPoint = caseNum;
				strcpy(lastTrue, inputStr);
				strcpy(lastAnswer, buffer);
				break;
			}
		}

		else if (inputOp0 == 'c') {
			fscanf(fp, "%c\n", &inputOp1);
			if (inputOp1 == 'A') {
				clearPoly(&A);
			}
			else if (inputOp1 == 'B') {
				clearPoly(&B);
			}
		}

		else if (inputOp0 == 'm') {
			fscanf(fp, "%s\n", inputStr);
			printPoly_impl(multiPoly(A, B), buffer);
			if (strcmp(inputStr, buffer) != 0) {
				breakFlag = 1;
				breakPoint = caseNum;
				strcpy(lastTrue, inputStr);
				strcpy(lastAnswer, buffer);
				break;
			}
		}
	}

	fclose(fp);

	if (breakFlag) {
		printf("Test failed on case# %d\n", breakPoint);
		printf("True: %s\nAnswer: %s", lastTrue, lastAnswer);
	}
	else {
		printf("TEST DONE.\n");
	}
}

int main() {
	testPoly(); //use this function if you want.

	poly A, B;
	initPoly(&A);
	initPoly(&B);

	addTerm(&A, 1, 3);
	addTerm(&A, 0, 1);
	printf("poly A: ");
	printPoly(A);
	printf("\n");

	addTerm(&B, 1, 1);
	addTerm(&B, 0, -1);
	printf("poly B: ");
	printPoly(B);
	printf("\n");

	printf("A*B: ");
	printPoly(multiPoly(A, B));

	return 0;
}
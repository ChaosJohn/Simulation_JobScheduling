#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 

#define RUN 1 
#define WAIT 0 

typedef struct _jcb {
  int jid; 
  char *jname; 
  int entertime; 
  int starttime; 
  int needtime; 
  int status; 
  int waittime; 
  struct _jcb *next; 
} JCBNode, *JCBList, *JCBPointer; 

JCBList jcbList; 
int globalTime; 

void 
input(int jcbSize) {
  int i; 
  JCBPointer pointer; 
  jcbList = (JCBPointer)malloc(sizeof(JCBNode)); 
  jcbList->next = NULL; 
  JCBPointer cursor = jcbList; 
  for (i = 0; i < jcbSize; i++) {
    pointer = (JCBPointer)malloc(sizeof(JCBNode)); 
    printf("建立第  %d  个作业\n", i); 
    pointer->jid = i; 
    printf("\t进入时间: "); scanf("%d", &(pointer->entertime)); fflush(stdin); 
    printf("\t所需时间: "); scanf("%d", &(pointer->needtime)); fflush(stdin); 
    pointer->status = WAIT; 
    pointer->waittime = 0; 
    pointer->next = NULL; 
    cursor->next = pointer; 
    cursor = cursor->next; 
  }
}

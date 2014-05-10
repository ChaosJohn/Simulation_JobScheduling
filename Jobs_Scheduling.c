#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 

#define RUN 1 
#define WAIT 0 
#define FINISH -1 

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

/* 
 * 打印一条横线
 * */
void 
printHorizontalBar() {
  int i; 
  for (i = 0; i <= 33; i++) 
    printf("-"); 
  printf("\n"); 
} 

void 
sortFCFS() {

}

void 
display() {

}

/* 
 * 判断是否所有作业都已经完成
 * */
int 
isAllFinished() {
  JCBPointer cursor = jcbList->next; 
  while(cursor != NULL) {
    if(cursor->status != FINISH) 
      return -1; 
    cursor = cursor->next; 
  }
  return 1; 
}

void 
updateJobs() {
  JCBPointer cursor = jcbList->next; 
  while(cursor != NULL) {
    if (cursor->status != FINISH) {

    }
    cursor = cursor->next; 
  }
}

JCBPointer 
pickRunning() {
  
}

/* 
 * 使用FCFS调度算法进行作业调度*/
void 
runFCFS() {
  JCBPointer head = jcbList; 
  JCBPointer running; 
  while (isAllFinished() != 1) {
    sortFCFS(); 
    running = head->next; 
    running->starttime = globalTime; 
    printf("\n#=>正在运行第  %d  个作业\n", running->jid); 
    display(); 
    sleep(1); 
    running->status = FINISH; 
    globalTime += running->needtime; 
  }
}

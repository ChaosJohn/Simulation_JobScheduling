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
  for (i = 0; i <= 40; i++) 
    printf("-"); 
  printf("\n"); 
} 

void 
sortFCFS() {

}

void 
display() {
  JCBPointer cursor = jcbList->next; 
  printHorizontalBar(); 
  printf("|作业号\t|状态\t|进入\t|需要\t|等待\t|\n"); 
  while(cursor != NULL) {
    char status; 
    if (cursor->status == RUN) 
      status = 'R'; 
    else if (cursor->status == WAIT) 
      status = 'W'; 
    else if (cursor->status == FINISH) 
      status = 'F'; 
    printf("|%d\t|%c\t|%d\t|%d\t|%d\t|\n", 
        cursor->jid, status, cursor->entertime, 
        cursor->needtime, cursor->waittime); 
    cursor = cursor->next; 
  }
  printHorizontalBar(); 
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
      if (cursor->entertime <= globalTime) {
        cursor->waittime = globalTime - cursor->entertime; 
      }
    }
    cursor = cursor->next; 
  }
}

JCBPointer 
pickRunning() {
  updateJobs(); 
  JCBPointer cursor = jcbList->next; 
  JCBPointer running = cursor; 
  while(cursor != NULL) {
    if (cursor->status != FINISH) {
      if (cursor->waittime > running->waittime) {
        running = cursor; 
      } 
    }
  }
  return running; 
}

/* 
 * 使用FCFS调度算法进行作业调度*/
void 
runFCFS() {
  /*JCBPointer head = jcbList; */
  JCBPointer running; 
  while (isAllFinished() != 1) {
    /*sortFCFS(); */
    /*running = head->next; */
    running = pickRunning(); 
    running->starttime = globalTime; 
    printf("\n#=>正在运行第  %d  个作业\n", running->jid); 
    display(); 
    sleep(1); 
    running->status = FINISH; 
    printf("\n#=>第  %d  个作业已经运行结束\n", running->jid); 
    globalTime += running->needtime; 
    sleep(1); 
  }
}

int 
main(int argc, 
    char **argv) {
  int jcbSize = 0; 
  /*int choose = 0; */
  printf("需要建立的作业个数: "); scanf("%d", &jcbSize); fflush(stdin); 
  input(jcbSize); 
  display(); 
  runFCFS(); 

  printf("#=>全部作业已经结束\n"); 

  return 0; 
}

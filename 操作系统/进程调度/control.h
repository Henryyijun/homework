#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "queue.h"

struct PCB {
	int id;
	char name[100];
	int time_start;
	int time_need;
	int time_left;
	int time_used;
	char state;
};

void __sleep(int n) {
	clock_t g;
	g = (clock_t)n *  CLOCKS_PER_SEC + clock();
	while (g > clock());
}

char __keygo() {
	char c;
	printf("按任意键继续.....\n");
	c = getchar();
	return c;
}

int time_unit = 2;
const int MAX_NUM = 100;
const int num = 4;
int order[MAX_NUM];
int ready[MAX_NUM];
struct PCB pcbdata[MAX_NUM] = {
	{1000, "A", 0, 4, 4, 0, 'R'},
	{1001, "B", 1, 3, 3, 0, 'R'},
	{1002, "C", 2, 5, 5, 0, 'R'},
	{1003, "D", 3, 2, 2, 0, 'R'},
	{1004, "E", 4, 4, 4, 0, 'R'}
};

struct PCB pcbdata1[MAX_NUM] = {
	{1000, "Job1", 1, 9, 9, 0, 'R'},
	{1001, "Job2", 1, 16, 16, 0, 'R'},
	{1002, "Job3", 1, 3, 3, 0, 'R'},
	{1003, "Job4", 1, 11, 11, 0, 'R'}
};

struct PCB test[MAX_NUM] = {
	{1000, "A", 800, 200, 200, 0, 'R'},
	{1001, "B", 850, 50, 50, 0, 'R'},
	{1002, "C", 900, 10, 10, 0, 'R'},
	{1003, "D", 950, 20, 20, 0, 'R'}
};

struct PCB test1[MAX_NUM] = {
	{1000, "A", 0, 4, 4, 0, 'R'},
	{1001, "B", 1, 3, 3, 0, 'R'},
	{1002, "C", 3, 4, 4, 0, 'R'},
	{1003, "D", 5, 2, 2, 0, 'R'},
	{1004, "E", 7, 4, 4, 0, 'R'}
};
struct PCB pcbdata2[MAX_NUM] = {
	{1000, "p1", 10, 8, 8, 0, 'R'},
	{1001, "p2", 12, 12, 12, 0, 'R'},
	{1002, "p3", 14, 4, 4, 0, 'R'},
	{1003, "p4", 16, 6, 6, 0, 'R'}
};

struct PCB pcbdata3[MAX_NUM] = {
	{1000, "A", 0, 7, 7, 0, 'R'},
	{1001, "B", 5, 4, 4, 0, 'R'},
	{1002, "C", 7, 13, 13, 0, 'R'},
	{1003, "D", 12, 9, 9, 0, 'R'}
};
	
void input() {
	int i;
	printf("进程总数为:");
	scanf("%d", &num);
	for (i = 0; i < num; i++) {
		pcbdata[i].id = 1000 + i;
		printf("输入第%d个进程名:", i + 1);
		scanf("%s", pcbdata[i].name);
		printf("输入第%d个进程到达的时间：", i + 1);
		scanf("%d", &pcbdata[i].time_start);
		printf("输入第%d个进程的服务时间：", i + 1);
		scanf("%d", &pcbdata[i].time_need);
		pcbdata[i].time_left = pcbdata[i].time_need;
		printf("\n");
		pcbdata[i].time_used = 0;
		pcbdata[i].state = 'R';
	}
}
void print(int temp) {
	int i;
	printf("进程号--进程名--到达时间--运行时间--完成时间--周转时间--带权周转时间\n");
	for (i = 0; i < num; i++) {
		int id = pcbdata[ready[i]].id;
		char *name = pcbdata[ready[i]].name;
		int start = pcbdata[ready[i]].time_start;
		int runtime = pcbdata[ready[i]].time_need;
		temp += pcbdata[ready[i]].time_need;
		int end = temp;
		int cycle = temp - start;
		float weightcycle = (float)cycle / pcbdata[ready[i]].time_need;
		printf("%d------|%s--------|%d--------|%d--------|%2d--------|%2d--------|%f\n", id, name, start, runtime, end, cycle, weightcycle);

	}
}
void show_ready();
void sort_by_start(struct PCB pcb[MAX_NUM]) {
	/*
		对开始时间进行排序。
	*/
	int i, j, temp;
	for (i = 0; i < num; i++) {
		order[i] = pcb[i].time_start;
		ready[i] = i;
	}
	for (i = 1; i < num; i++) {
		for (j = 0; j < num - i; j++) {
			if (order[j] > order[j + 1]) {
				temp = order[j];
				order[j] = order[j + 1];
				order[j + 1] = temp;

				temp = ready[j];
				ready[j] = ready[j + 1];
				ready[j + 1] = temp;
			}
		}
	}
	show_ready();
}

void FCFS() {
	int temp;
	memset(ready, 0, MAX_NUM);
	memset(order, 0, MAX_NUM);
	sort_by_start(pcbdata);
	printf("----FCFS算法调度----\n");
	temp = pcbdata[ready[0]].time_start;
	print(temp);
	printf("-----FCFS算法结束------\n");
}
void show_ready() {
	for (int i = 0; i < num; i++) {
		printf("%d ", ready[i]);
	}
	printf("\n");
}

void SJF(struct PCB pcb[MAX_NUM]) {
	printf("----短作业优先调度---\n");
	sort_by_start(pcb); //首先进行对开始时间排序
	queue readyq;
	creat_queue(&readyq, MAX_NUM);
	for (int i = 0; i < num; i++) {
		push(&readyq, ready[i]);
	}
	//printf("%d %d\n", readyq.front, readyq.tail);
	int temp = pcb[ready[0]].time_start;
	printf("%d\n", ready[0]);
	printf("%s\n", pcb[ready[0]].name);
	printf("进程号--进程名--到达时间--运行时间--完成时间--周转时间--带权周转时间\n");
	for (int i = 0; i < num; i++) {
		int count = 0;
		for (int j = readyq.front; j < readyq.tail; j++) {
			if (pcb[readyq.point[j]].time_start <= temp) {
				count++;
			}
		}	
		for (int j = readyq.front; j < readyq.front + count; j++) {
			for (int k = j + 1; k < readyq.front + count; k++) {
				if (pcb[readyq.point[j]].time_need > pcb[readyq.point[k]].time_need) {
					int t = readyq.point[j];
					readyq.point[j] = readyq.point[k];
					readyq.point[k] = t;
				}
			}
		}

		int front;
		pop(&readyq, &front);	
		int id = pcb[front].id;
		char *name = pcb[front].name;
		int start = pcb[front].time_start;
		int runtime = pcb[front].time_need;
		temp += pcb[front].time_need;
		int end = temp;
		int cycle = temp - start;
		float weightcycle = (float)cycle / pcb[front].time_need;
		printf("%d------|%s--------|%d--------|%d--------|%2d--------|%2d--------|%f\n", id, name, start, runtime, end, cycle, weightcycle);
		
	}

}

void HRF(struct PCB pcb[MAX_NUM]) {
	printf("-----高响应比调度-----\n");
	queue q;
	creat_queue(&q, MAX_NUM);
	sort_by_start(pcb);
	for (int i = 0; i < num; i++) {
		push(&q, ready[i]);
	}
	int temp = pcb[ready[0]].time_start;
	printf("进程号--进程名--到达时间--运行时间--完成时间--周转时间--带权周转时间\n");
	for (int i = 0; i < num; i++) {
		int front;
		pop(&q, &front);
		int id = pcb[front].id;
		char *name = pcb[front].name;
		int start = pcb[front].time_start;
		int runtime = pcb[front].time_need;
		temp += pcb[front].time_need;
		int end = temp;
		int cycle = temp - start;
		float weightcycle = (float)cycle / pcb[front].time_need;
		printf("%d------|%s--------|%d--------|%d--------|%2d--------|%2d--------|%f\n", id, name, start, runtime, end, cycle, weightcycle);
		int count = 0;
		for (int j = q.front; j < q.tail; j++) {
			if (pcb[q.point[j]].time_start <= temp) {
				count++;
			}
		}
		for (int j = q.front; j < q.front + count; j++) {
			for (int k = j + 1; k < q.front + count; k++) {
				float ratek = (pcb[q.point[k]].time_need + (temp - pcb[q.point[k]].time_start)) * 1.0 / (pcb[q.point[k]].time_need);
				float ratej = (pcb[q.point[j]].time_need + (temp - pcb[q.point[j]].time_start)) * 1.0 / (pcb[q.point[j]].time_need);
				if (ratej < ratek) {
					int t = q.point[j];
					q.point[j] = q.point[k];
					q.point[k] = t;
				}
			}
		}
	}
}

void TimeSlice(struct PCB pcb[MAX_NUM]) {
	printf("%d\n", num);
	sort_by_start(pcb);
	queue q;
	creat_queue(&q, MAX_NUM);
	push(&q, ready[0]);
	int temp = pcb[ready[0]].time_start;
	int i = 1;
	while (empty(&q) == false) {
		int front;
		printf("此时队列中有：");
		print_queue(&q);
		pop(&q, &front);
		int id = pcb[front].id;
		char *name = pcb[front].name;
		int start = pcb[front].time_start;
		int runtime = pcb[front].time_need;
		pcb[front].state = 'E';
		if (pcb[front].time_left <= time_unit) {
			temp += pcb[front].time_left;
			pcb[front].time_left = 0;
			pcb[front].time_used = pcb[front].time_need;
			
		} else {
			pcb[front].time_left -= time_unit;
			pcb[front].time_used += time_unit;
			temp += time_unit;
	
		} 
		for (int j = i; j < num; j++) {
			if (i < num && pcb[ready[i]].time_start <= temp && pcb[ready[i]].state != 'F') {
				push(&q, ready[j]);
				i++;
			}
		}
		
		printf("进程%d, 名字为%s, 此时时刻为:%d,使用时间为：%d,剩余时间为: %d 进程状态为:%c: \n\n", id, name, temp,pcb[front].time_used, pcb[front].time_left, pcb[front].state);
		if (pcb[front].time_used == pcb[front].time_need) {
			printf("----进程%s执行结束！！----\n", name);
			pcb[front].state = 'F';
			printf("进程状态为:%c:\n", pcb[front].state);
			printf("----完成时间为：%d, 周转时间为： %d----\n\n", temp, temp - start);
		} else {
			push(&q, front);
		}
			
	}

}

void MALA(struct PCB pcb[MAX_NUM]) {}

int fun(void *a, void *b) {
	int p;
	p = *(int*)a + *(int*)b;
	return p;
}
int func(int (*function)(void *, void * ), int a, int b) 	{
	return function(&a, &b);
}
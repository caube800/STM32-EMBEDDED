#include <stdint.h>
#include<stdio.h>

//stack memory
#define SIZE_TASK_STACK   5*1024
#define SIZE_SCHED_STACK  5*1024

#define SRAM_START        0x20000000U
#define SIZE_SRAM         (128*1024)
#define SRAM_END          (SRAM_START+SIZE_SRAM)

#define T1_STACK_START    SRAM_END
#define T2_STACK_START    (SRAM_END - (1*SIZE_TASK_STACK))
#define T3_STACK_START    (SRAM_END - (2*SIZE_TASK_STACK))
#define T4_STACK_START    (SRAM_END - (3*SIZE_TASK_STACK))
#define SCHED_STACK_START (SRAM_END - (4*SIZE_TASK_STACK))



// task handler function
void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);

int main(void)
{
    /* Loop forever */
	for(;;);
}

void task1_handler(void){
	while(1){
		printf ("Task1\n");
	}
}

void task2_handler(void){
	while(1){
		printf ("Task2\n");
	}
}

void task3_handler(void){
	while(1){
		printf ("Task3\n");
	}
}

void task4_handler(void){
	while(1){
		printf ("Task4\n");
	}
}

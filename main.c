/*---------------------------Initialization and Setup process----------------------------*/
/*-------Include standard libraries and the necessary headers for FreeRTOS----------------------*/
#include <stdio.h>
#include <stdlib.h>
#include "diag/trace.h"
/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"
/*-----------------------------------------------------------------------------------*/
#define CCM_RAM __attribute__((section(".ccmram")))
/*------------------Task, Semaphores and Timer Callbacks Declaration---------------------*/
 void SenderTask1();
 void SenderTask2();
 void SenderTask3();
 void ReceiverTask();

 void SenderTask1TimerCallback( TimerHandle_t xTimerSender1 );
 void SenderTask2TimerCallback( TimerHandle_t xTimerSender2 );
 void SenderTask3TimerCallback( TimerHandle_t MutexSender3 );
 void ReciverTaskTimerCallback( TimerHandle_t MutexResiver );

 SemaphoreHandle_t SemSender1;
 SemaphoreHandle_t SemSender2;
 SemaphoreHandle_t SemSender3;
 SemaphoreHandle_t SemResiver;
 /*-------------Reset function & Random Uniformly Declaration-------------------------------*/
int randomUnformaly();
void reset();
/*--------------------------------Queue implementation-------------------------------------*/
QueueHandle_t testQueue;
/*----------------------Counters Declaration-----------------------------------*/
int C1S,C1F,C2S,C2F,C2S,C2F,C3S,C3F,CreceiverSuccss,CreceiverFailed;
uint32_t  iterative=0;
uint32_t  NoOfMessages=0;
/*-----------------------------------------------------------------------*/
/*----------------Timer's Declaration---------------------------------------*/
static TimerHandle_t xTimerSender1 = NULL;
static TimerHandle_t xTimerSender2 = NULL;
static TimerHandle_t xTimerSender3 = NULL;
static TimerHandle_t xTimerReciver = NULL;
BaseType_t xTimerSender1Started, xTimerSender2Started, xTimerSender3Started, xTimerReciiver;
/*----------------------Counters Declaration-----------------------------------*/
int SumSender1 = 0;
int SumSender2 = 0;
int SumSender3 = 0;
int PeriodsSender1 = 0;
int PeriodsSender2 = 0;
int PeriodsSender3 = 0;
/*-----------------------------------------------------------------------*/
// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int main(int argc, char* argv[])
{
	    BaseType_t status;
	    SemSender1 = xSemaphoreCreateBinary();
	    SemSender2 = xSemaphoreCreateBinary();
	    SemSender3 = xSemaphoreCreateBinary();
	    SemResiver = xSemaphoreCreateBinary();
		testQueue = xQueueCreate( 10, sizeof(char) * 20 ); //queue's size holds 3 or 10
		if( testQueue != NULL ) {
		reset();
		status = xTaskCreate(SenderTask1, "Sender1", 1000,NULL, 1, NULL );
		status = xTaskCreate(SenderTask2, "Sender2", 1000, NULL, 1, NULL );
		status = xTaskCreate(SenderTask3, "Sender3", 1000, NULL, 2, NULL );
		status = xTaskCreate( ReceiverTask, "Receiver", 1000, NULL, 3, NULL );
		}
		else
		{
			trace_printf("There is an evil error in queue's declaration!!\n");
			exit(1);
		}
		xTimerSender1 = xTimerCreate( "TimerSender1", ( pdMS_TO_TICKS(randomUnformaly()) ), pdTRUE,0, SenderTask1TimerCallback);
		xTimerSender2 = xTimerCreate( "TimerSender2", ( pdMS_TO_TICKS(randomUnformaly()) ), pdTRUE,0, SenderTask2TimerCallback);
		xTimerSender3 = xTimerCreate( "TimerSender3", ( pdMS_TO_TICKS(randomUnformaly()) ), pdTRUE,0, SenderTask3TimerCallback);
		xTimerReciver = xTimerCreate( "TimerReciver", ( pdMS_TO_TICKS(100) ), pdTRUE,0, ReciverTaskTimerCallback);
		if( ( xTimerSender1 != NULL ) && ( xTimerSender2 != NULL )  && ( xTimerSender3 != NULL ) && ( xTimerReciver != NULL ))
			{
			xTimerSender1Started = xTimerStart( xTimerSender1, 0 );
			xTimerSender2Started = xTimerStart( xTimerSender2, 0 );
			xTimerSender3Started = xTimerStart( xTimerSender3, 0 );
			xTimerReciiver = xTimerStart( xTimerReciver, 0 );
			}
		if( xTimerSender1Started == pdPASS && xTimerSender2Started == pdPASS && xTimerSender3Started == pdPASS && xTimerReciiver == pdPASS)
			{
				vTaskStartScheduler();
			}

		for( ;; );
}

#pragma GCC diagnostic pop


void vApplicationMallocFailedHook( void )
{
	/* Called if a call to pvPortMalloc() fails because there is insufficient
	free memory available in the FreeRTOS heap.  pvPortMalloc() is called
	internally by FreeRTOS API functions that create tasks, queues, software
	timers, and semaphores.  The size of the FreeRTOS heap is set by the
	configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
volatile size_t xFreeStackSpace;

	/* This function is called on each cycle of the idle task.  In this case it
	does nothing useful, other than report the amout of FreeRTOS heap that
	remains unallocated. */
	xFreeStackSpace = xPortGetFreeHeapSize();

	if( xFreeStackSpace > 100 )
	{
		/* By now, the kernel has allocated everything it is going to, so
		if there is a lot of heap remaining unallocated then
		the value of configTOTAL_HEAP_SIZE in FreeRTOSConfig.h can be
		reduced accordingly. */
	}
}

void vApplicationTickHook(void) {
}

StaticTask_t xIdleTaskTCB CCM_RAM;
StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE] CCM_RAM;

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
  /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
  state will be stored. */
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

  /* Pass out the array that will be used as the Idle task's stack. */
  *ppxIdleTaskStackBuffer = uxIdleTaskStack;

  /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
  Note that, as the array is necessarily of type StackType_t,
  configMINIMAL_STACK_SIZE is specified in words, not bytes. */
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

static StaticTask_t xTimerTaskTCB CCM_RAM;
static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH] CCM_RAM;

/* configUSE_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
application must provide an implementation of vApplicationGetTimerTaskMemory()
to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize) {
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
  *ppxTimerTaskStackBuffer = uxTimerTaskStack;
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
/*--------------------Timer Callback functions---------------------------------------*/
 void SenderTask1TimerCallback( TimerHandle_t xTimerSender1 )
{
	xSemaphoreGive(SemSender1);
	int randomPeriod = randomUnformaly();
	SumSender1 += randomPeriod;
	PeriodsSender1++;
	TickType_t newPeriod = pdMS_TO_TICKS(randomPeriod);
	xTimerChangePeriod(xTimerSender1, newPeriod, 0);

}
 void SenderTask2TimerCallback( TimerHandle_t xTimerSender2 )
{
	xSemaphoreGive(SemSender2);
	int randomPeriod = randomUnformaly();
	SumSender2 += randomPeriod;
	PeriodsSender2++;
	TickType_t newPeriod = pdMS_TO_TICKS(randomPeriod);
	xTimerChangePeriod(xTimerSender2, newPeriod, 0);

}
 void SenderTask3TimerCallback( TimerHandle_t xTimerSender3 )
{
	xSemaphoreGive(SemSender3);
	int randomPeriod = randomUnformaly();
	SumSender3 += randomPeriod;
	PeriodsSender3++;
	TickType_t newPeriod = pdMS_TO_TICKS(randomPeriod);
	xTimerChangePeriod(xTimerSender3, newPeriod, 0);
}
 void ReciverTaskTimerCallback( TimerHandle_t xTimerReciver )
{
	xSemaphoreGive(SemResiver);
	TickType_t newPeriod = pdMS_TO_TICKS(100);
	xTimerChangePeriod(xTimerReciver, newPeriod, 0);
}
/*-----------------------------------------------------------*/
/*-----------------------Sender Tasks------------------------------------*/
void SenderTask1()
{char MessageToSend[20];
TickType_t xTimeNow;
BaseType_t xStatus;
while(1){
	xSemaphoreTake(SemSender1,portMAX_DELAY);
	xTimeNow=xTaskGetTickCount();
	snprintf(MessageToSend, 20, "Time is %u",xTaskGetTickCount() );
	xStatus = xQueueSend( testQueue, &MessageToSend, 0 );
if ( xStatus != pdPASS ) { //failed
C1F++;
}
else
	{ C1S++; }
}
}
/*-----------------------------------------------------------*/
void SenderTask2()
{char MessageToSend[20];
TickType_t xTimeNow;
BaseType_t xStatus;
while(1){
	xSemaphoreTake(SemSender2,portMAX_DELAY);
	xTimeNow=xTaskGetTickCount();
	snprintf(MessageToSend, 20, "Time is %u", xTaskGetTickCount());
	xStatus = xQueueSend( testQueue, &MessageToSend, 0 );
if ( xStatus != pdPASS ) {
C2F++;
}
else
	{ C2S++; }
}
}
/*-----------------------------------------------------------*/
void SenderTask3()
{
	char MessageToSend[20];
	TickType_t xTimeNow;
	BaseType_t xStatus;
while(1){
	xSemaphoreTake(SemSender3,portMAX_DELAY);
	xTimeNow=xTaskGetTickCount();
	snprintf(MessageToSend, 20, "Time is %u", xTaskGetTickCount());
	xStatus = xQueueSend( testQueue, &MessageToSend, 0 );
if ( xStatus != pdPASS ) { //failed
C3F++;}
else
	{ C3S++; }
}
}
/*-----------------------------------------------------------*/
/*-----------------------Receiver Task------------------------------------*/
void ReceiverTask()
{
BaseType_t status;
while(1){
	xSemaphoreTake(SemResiver,portMAX_DELAY);
	char *receivedMessage=(char *)malloc(20);
status = xQueueReceive( testQueue, receivedMessage, 0 );
if( status == pdPASS ){
CreceiverSuccss++;
NoOfMessages++;
trace_printf("%s\n", receivedMessage);
if(NoOfMessages==1000)
{
	trace_printf( "Warning, The Reset function is called!.\r\n" );
	reset();}
free(receivedMessage);
}
else {CreceiverFailed++;}
}
}
/*-----------------------------------------------------------*/
int randomUnformaly(){
	int lower_bounds[] = {50, 80, 110, 140, 170, 200};
	    int upper_bounds[] = {150, 200, 250, 300, 350, 400};
	    int index = iterative - 1;
	    int random_value = lower_bounds[index] + rand() % (upper_bounds[index] - lower_bounds[index] + 1);
	    return random_value;
}
/*-----------------------------------------------------------*/
void reset(){
	trace_printf("Resetting...\n");
	if(iterative!=0){
		Vprint();
	}
	C1S=C2S=C3S=C1F=C2F=C3F=CreceiverSuccss=CreceiverFailed=0;
	SumSender1=SumSender2=SumSender3=PeriodsSender1=PeriodsSender2=PeriodsSender3=0;
				if (xQueueReset(testQueue) == pdPASS) {
					trace_printf("Queue reset successful.\n");
				} else {
					trace_printf("Queue reset failed.\n");
				}

	if(iterative==0){
		iterative++;
		return;}
	iterative++;
	NoOfMessages=0;
	if(iterative==7){
		xTimerDelete( xTimerSender1 ,xTaskGetTickCount());
		xTimerDelete( xTimerSender2 ,xTaskGetTickCount());
		xTimerDelete( xTimerSender3 ,xTaskGetTickCount());
		xTimerDelete( xTimerReciver ,xTaskGetTickCount());
		trace_printf("Game Over.\n");
		exit(0);}
	return;
}
void Vprint(){
	int totalSuccessSent=C1S+C2S+C3S;
		int totalFailedSent=C1F+C2F+C3F;
		trace_printf("The total number of successfully sent messages: %i\n",totalSuccessSent);
		trace_printf("The total number of Blocked sent messages: %i\n",totalFailedSent);
			/*-----------------------------------------------------------*/
		trace_printf("the statistics for sender task 1 :\n");
		trace_printf("          Number of successfully sent messages: %i\n",C1S);
		trace_printf("          Number of failed sent messages: %i\n",C1F);
		trace_printf("          Average period: %i\n", SumSender1/PeriodsSender1);
			/*-----------------------------------------------------------*/
		trace_printf("the statistics for sender task 2 :\n");
		trace_printf("          Number of successfully sent messages: %i\n",C2S);
		trace_printf("          Number of failed sent messages: %i\n",C2F);
		trace_printf("          Average period: %i\n", SumSender2/PeriodsSender2);
			/*-----------------------------------------------------------*/
		trace_printf("the statistics for sender task 3 :\n");
		trace_printf("          Number of successfully sent messages: %i\n",C3S);
		trace_printf("          Number of failed sent messages: %i\n",C3F);
		trace_printf("          Average period: %i\n", SumSender3/PeriodsSender3);

return;
}

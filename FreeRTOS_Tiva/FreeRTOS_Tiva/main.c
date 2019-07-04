

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "FreeRTOS_Files/FreeRTOS.h"
#include "FreeRTOS_Files/task.h"
#include "FreeRTOS_Files/semphr.h"
#include "CAN/CAN.h"
#include "GPIO/GPIO.h"


#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif


extern TaskHandle_t handler_init_CAN_Tx ;   /*Handler of system_init task */
extern TaskHandle_t handler_init_CAN_Rx ;   /*Handler of system_init task */
extern TaskHandle_t handler_init_CAN_send ;   /*Handler of system_init task */
extern TaskHandle_t handler_init_GPIO ;     /*Handler of GPIO_init task */

/* xSemaphoreHandle CAN_semaphore;      /* This semaphore to check if Bottom pressed or not (check event) */

int main(void)
{


    xTaskCreate(init_GPIO,"Init GPIO",80,NULL,1,&handler_init_GPIO); /* init GPIO task creation */
    xTaskCreate(CAN_TX_Init, "CAN TX Init", 80, NULL, 3, &handler_init_CAN_Tx);
  //  xTaskCreate(CAN_RX_Init, "CAN RX Init", 80, NULL, 1, &handler_init_CAN_Rx);
    xTaskCreate(toggle_LED_one,"Toggle LED",80,NULL,0,NULL); /* toggle_LED_one task creation */
    xTaskCreate(CAN0_Send,"CAN0 Send",80,NULL,1,NULL); /* CAN0 send task creation */
    //xTaskCreate(CAN0_Receive,"CAN0 Receive",80,NULL,0,NULL); /* CAN0 Recive task creation */



    /* Start Scheduler */
        vTaskStartScheduler();

}


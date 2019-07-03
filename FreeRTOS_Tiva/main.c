

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "FreeRTOS_Files/FreeRTOS.h"
#include "FreeRTOS_Files/task.h"
#include "CAN/CAN.h"
#include "GPIO/GPIO.h"


#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif


extern TaskHandle_t handler_init_System ;   /*Handler of system_init task */
extern TaskHandle_t handler_init_GPIO ;     /*Handler of GPIO_init task */


int main(void)
{

    xTaskCreate(init_GPIO,"Init GPIO",80,NULL,1,&handler_init_GPIO); /* init GPIO task creation */
    xTaskCreate(system_Init, "System Tint", 80, NULL, 1, &handler_init_System);
    xTaskCreate(toggle_LED_one,"Toggle LED",80,NULL,0,NULL); /* toggle_LED_one task creation */
    xTaskCreate(CAN0_Send,"CAN0 Send",80,NULL,0,NULL); /* CAN0 send task creation */
    xTaskCreate(CAN0_Recive,"CAN0 Recive",80,NULL,0,NULL); /* CAN0 Recive task creation */

    /* Start Scheduler */
        vTaskStartScheduler();

}


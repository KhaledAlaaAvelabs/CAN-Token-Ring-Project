/*
 * CAN.c
 *
 *  Created on: Jul 3, 2019
 *      Author: AVE-LAP-016
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "driverlib/pin_map.h"
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "driverlib/can.h"
#include "driverlib/interrupt.h"

#include "../FreeRTOS_Files/FreeRTOS.h"
#include "../FreeRTOS_Files/task.h"

#include "CAN.h"



TaskHandle_t handler_init_System = NULL;       /* init GPIO task handlar ceariation */

/* System init task for initialize CAN0
 * input ; void
 * output ; void */
void system_Init (void)
{

    tCANMsgObject sCANMessage;
       uint32_t ui32MsgData;
       uint8_t *pui8MsgData;

       pui8MsgData = (uint8_t *)&ui32MsgData;


    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinConfigure(GPIO_PB4_CAN0RX);
    GPIOPinConfigure(GPIO_PB5_CAN0TX);
    PIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
    CANInit(CAN0_BASE);
    CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
    CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
    IntEnable(INT_CAN0);

       /* Enable the CAN for operation. */

       CANEnable(CAN0_BASE);

       /* Initialize the message object that will be used for sending CAN
        messages.  The message will be 4 bytes that will contain an incrementing
        value.  Initially it will be set to 0.
       */
       ui32MsgData = 0;
       sCANMessage.ui32MsgID = 1;
       sCANMessage.ui32MsgIDMask = 0;
       sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
       sCANMessage.ui32MsgLen = sizeof(pui8MsgData);
       sCANMessage.pui8MsgData = pui8MsgData;

        vTaskSuspend(handler_init_System); /* suspend init_system task */
}

void CAN0_Send (void)
{
   /* CANMessageSet(ui32Base, ui32ObjID, psMsgObject, eMsgType);  */

}

void CAN0_Recive (void)
{

    /* CANMessageGet(ui32Base, ui32ObjID, psMsgObject, bClrPendingInt); */
}


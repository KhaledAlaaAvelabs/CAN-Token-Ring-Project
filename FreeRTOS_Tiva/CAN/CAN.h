/*
 * CAN.h
 *
 *  Created on: Jul 3, 2019
 *      Author: AVE-LAP-016
 */

#ifndef CAN_CAN_H_
#define CAN_CAN_H_


/* System init task for initialize CAN0
 * input ; void
 * output ; void */
void system_Init (void);
void CAN0_Send (void);
void CAN0_Recive (void);

#endif /* CAN_CAN_H_ */

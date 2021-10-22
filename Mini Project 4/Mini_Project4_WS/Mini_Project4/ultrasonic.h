 /******************************************************************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for the ULTRASONIC driver
 *
 * Author: Hady Emad
 *
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"

#define ULTRASONIC_TRIG_PORT PORTB_ID
#define ULTRASONIC_TRIG_PIN  PIN5_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Description : Function to initialise the Ultrasonic driver */
void ULTRASONIC_init(void);


/* Description : Function to measure the distance using Ultrasonic sensor */
uint16 ULTRASONIC_readDistance(void);

/* Description : It's the callback function used to measure the pulse width time */
 void ULTRASONIC_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */

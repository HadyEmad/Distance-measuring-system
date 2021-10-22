 /******************************************************************************
 *
 * Module: ULTRASONIC
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the ULTRASONIC driver
 *
 * Author: Hady Emad
 *
 *******************************************************************************/

#include "ultrasonic.h"
#include "icu.h"
#include "gpio.h"
#include <util/delay.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the edge counting and pulse width time of the ICU*/

static uint16 high_time = 0;
static uint8 edge = 0;

/*******************************************************************************
 *                     Static Functions Prototypes                                   *
 *******************************************************************************/

/* Description : Function to trigger the Ultrasonic sensor */
static void ULTRASONIC_trigger(void);

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description : Function to initialise the Ultrasonic driver
 * 	1. Initialise ICU driver by passing ICU configuration structure to ICU_init function.
 * 	2. Set the ICU callback function.
 * 	3. Setup trigger pin.
 */

void ULTRASONIC_init(void) {
	ICU_ConfigType ICU_config = { F_CPU_8, RISING };
	ICU_init(&ICU_config);
	ICU_setCallBack(ULTRASONIC_edgeProcessing);
	GPIO_setupPinDirection(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN,PIN_OUTPUT);
	GPIO_writePin(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, LOGIC_LOW);
}

/*
 * Description : Function to trigger the Ultrasonic sensor.
 *  By applying 10 us pulse on the sensor trig pin,
 * 	then the sensor automatically sends Eight 40 kHz sound wave.
 */

static void ULTRASONIC_trigger(void) {
	GPIO_writePin(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, LOGIC_LOW);
}

/*
 * Description : Function to measure the distance using Ultrasonic sensor.
 *  By dividing the high time in microseconds measured by edge processing function, by
 *  57.8 which is a number calculated from a formula to get the distance in cm.
 */

uint16 ULTRASONIC_readDistance(void) {
	ULTRASONIC_trigger();
	uint16 distance;
	distance = (uint16)(high_time / 57.8);
	return distance;
}

/*
 * Description : It's the callback function used to measure the pulse width time.
 *  1.After detecting first rising edge it clear timer value to begin counting high time and set
 *  the edge detection to falling edge.
 *  2.After detecting the falling edge it updates the high time variable, clear the timer value
 *  and set the edge detection to rising edge and clear edge count.
 */

void ULTRASONIC_edgeProcessing(void) {
	edge++;
	if (edge == 1) {
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING);
	} else if (edge == 2) {
		high_time = ICU_getInputCaptureValue();
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(RISING);
		edge=0;
	}
}

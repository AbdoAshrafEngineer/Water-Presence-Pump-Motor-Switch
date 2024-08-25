/* 
 * File:   application.h
 * Author: Abdelrahman Ashraf
 */

#ifndef APPLICATION_H
#define APPLICATION_H

#include <avr/sleep.h> // Include AVR sleep mode definitions
#include "MCAL_Layer/mcal_std_types.h" // Include standard type definitions
#include "MCAL_Layer/GPIO/hal_gpio.h" // Include GPIO functions
#include "MCAL_Layer/Interrupt/External/ext_interrupt.h" // Include external interrupt functions
#include "MCAL_Layer/Interrupt/Timer/hal_timer.h" // Include timer functions

// Enum to represent the water flow status
typedef enum 
{
    STABLE,      // Water is stable
    NOT_STABLE   // Water is not stable
} Water_Flow;

// Function prototypes
void ext_int0_handler(void); // External interrupt service routine for INT0
void MyCompareMatchCallback(void); // Callback function for Timer0 Compare Match
void switch_motor_if_water_exist(void); // Function to control motor based on water status
void switch_motor_on(void); // Function to turn the motor on
void switch_motor_off(void); // Function to turn the motor off
Water_Flow Is_Water_Stable(void); // Function to check if water is stable

// External interrupt configuration for pin1
ExtIntConfig pin1 = 
{
    .mode = LOGIC_CHANGE,        // Interrupt triggers on logic change (rising or falling edge)
    .callback = ext_int0_handler // Function to be called on interrupt
};

// Timer0 configuration
Timer0_Config timer0 = 
{
    .mode = TIMER0_MODE_CTC,        // Timer mode: Clear Timer on Compare Match
    .prescaler = TIMER0_PRESCALER_1024, // Timer prescaler: divide clock by 1024
    .compareValue = 255,            // Compare match value
    .overflowCallback = NULL,       // No callback function for overflow
    .compareMatchCallback = MyCompareMatchCallback // Function to be called on compare match
};

#endif /* APPLICATION_H */



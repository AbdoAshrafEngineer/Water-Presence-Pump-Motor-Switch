/*
 * File:   hal_timer.h
 * Author: Abdelrahman Ashraf
 *
 * Created on July 31, 2024
 */

/* Header guard to prevent multiple inclusions of this header file */
#ifndef HAL_TIMER_H
#define HAL_TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../mcal_std_types.h"

// Prescaler enum
typedef enum {
    TIMER0_PRESCALER_NO_CLOCK = 0,  // No clock source (Timer stopped)
    TIMER0_PRESCALER_1,
    TIMER0_PRESCALER_8,
    TIMER0_PRESCALER_64,
    TIMER0_PRESCALER_256,
    TIMER0_PRESCALER_1024 
} Timer0_Prescaler;

// Timer modes
#define TIMER0_MODE_NORMAL 0
#define TIMER0_MODE_CTC    1

// Timer0 Configuration Structure
typedef struct {
    uint8_t mode;               // Timer mode (Normal, CTC)
    Timer0_Prescaler prescaler; // Prescaler value
    uint8_t compareValue;       // Compare match value (for CTC mode)
    void (*overflowCallback)(void);   // Callback function for overflow interrupt
    void (*compareMatchCallback)(void); // Callback function for compare match interrupt
} Timer0_Config;

// Function prototypes
void Timer0_Init(const Timer0_Config *config);
void Timer0_SetCompareValue(uint8_t compareValue);
void Timer0_EnableOverflowInterrupt(void);
void Timer0_DisableOverflowInterrupt(void);
void Timer0_EnableCompareMatchInterrupt(void);
void Timer0_DisableCompareMatchInterrupt(void);

// Interrupt service routines
ISR(TIM0_OVF_vect);
ISR(TIM0_COMPA_vect);

#endif // HAL_TIMER_H





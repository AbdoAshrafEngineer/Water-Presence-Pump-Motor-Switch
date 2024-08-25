/*
 * File: hal_timer.c
 * Author: Abdelrahman Ashraf
 */

#include "hal_timer.h"

// Global variables to hold the callback functions
static void (*overflowCallback)(void) = NULL;
static void (*compareMatchCallback)(void) = NULL;

static void Set_PreScaler(const Timer0_Config *config);

// Initialize Timer0 with given configuration
void Timer0_Init(const Timer0_Config *config)
{
    if(NULL != config)
    {
        // Store the callback functions
        overflowCallback = config->overflowCallback;
        compareMatchCallback = config->compareMatchCallback;
        // Set Timer0 mode
        switch (config->mode) 
        {
            case TIMER0_MODE_NORMAL:
                // Normal mode (default)
                TCCR0A = 0x00;
                break;

            case TIMER0_MODE_CTC:
                // CTC mode
                TCCR0A = (1 << WGM01);
                OCR0A = config->compareValue;
                break;

            default:
                // Handle invalid mode
                // Optionally, you can set a default mode or return an error
                break;
        }

        // Set prescaler
        Set_PreScaler(config);
    }
    else {/* Nothing */}
}

// Set the compare match value for CTC mode
void Timer0_SetCompareValue(uint8_t compareValue)
{
    OCR0A = compareValue;
}

// Enable Timer0 overflow interrupt
void Timer0_EnableOverflowInterrupt(void)
{
    TIMSK0 |= (1 << TOIE0);
}

// Disable Timer0 overflow interrupt
void Timer0_DisableOverflowInterrupt(void)
{
    TIMSK0 &= ~(1 << TOIE0);
}

// Enable Timer0 compare match interrupt
void Timer0_EnableCompareMatchInterrupt(void)
{
    TIMSK0 |= (1 << OCIE0A);
}

// Disable Timer0 compare match interrupt
void Timer0_DisableCompareMatchInterrupt(void)
{
    TIMSK0 &= ~(1 << OCIE0A);
}

static void Set_PreScaler(const Timer0_Config *config)
{
    switch(config->prescaler)
    {
        case TIMER0_PRESCALER_NO_CLOCK:
            TCCR0B&=~((1<<CS00));
            TCCR0B&=~((1<<CS01));
            TCCR0B&=~((1<<CS02));
            break;
        case TIMER0_PRESCALER_1:
            TCCR0B|=(1<<CS00);
            TCCR0B&=~((1<<CS01));
            TCCR0B&=~((1<<CS02));
            break;
        case TIMER0_PRESCALER_8:
            TCCR0B&=~((1<<CS00));
            TCCR0B|=(1<<CS01);
            TCCR0B&=~((1<<CS02));
            break;
        case TIMER0_PRESCALER_64:
            TCCR0B|=(1<<CS00);
            TCCR0B|=(1<<CS01);
            TCCR0B&=~((1<<CS02));
            break;
        case TIMER0_PRESCALER_256:
            TCCR0B&=~((1<<CS00));
            TCCR0B&=~((1<<CS01));
            TCCR0B|=(1<<CS02);
            break;            
        case TIMER0_PRESCALER_1024:
            TCCR0B|=(1<<CS00);
            TCCR0B&=~((1<<CS01));
            TCCR0B|=(1<<CS02);
            break;
        default:
            break;            
    }
}
// Timer0 overflow interrupt service routine
ISR(TIM0_OVF_vect)
{
    if (overflowCallback) 
    {
        overflowCallback();
    }
}

// Timer0 compare match interrupt service routine
ISR(TIM0_COMPA_vect)
{
    if (compareMatchCallback) 
    {
        compareMatchCallback();
    }
}
 



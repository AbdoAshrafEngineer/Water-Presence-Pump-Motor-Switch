/* 
 * File:   ext_interrupt.h
 * Author: Abdelrahman Ashraf
 */

#include "ext_interrupt.h"

/* Global pointer to callback function */
static void (*ext_int0_callback)(void) = NULL;

/* Initialize External Interrupt INT0 */
void Init_ExtInterrupt(const ExtIntConfig *config) 
{
    if (config == NULL || config->callback == NULL) 
    {
        /* Handle null pointer error, e.g., logging or setting a default handler */
        return;
    }

    /* Configure INT0 trigger mode */
    switch (config->mode) 
    {
        case FALLING_EDGE:
            MCUCR &=~(1<<ISC00);
            MCUCR |=(1<<ISC01);
            break;
        case RISING_EDGE:
            MCUCR |=(1<<ISC00);
            MCUCR |=(1<<ISC01);
            break;
        case LOGIC_CHANGE:
            MCUCR |=(1<<ISC00);
            MCUCR &=~(1<<ISC01);
            break;
        case LOW_LEVEL:
            MCUCR &=~(1<<ISC00);
            MCUCR &=~(1<<ISC01);
            break;
        default:
            /* Handle invalid mode */
            return;
    }

    /* Store callback function */
    ext_int0_callback = config->callback;

    /* Enable INT0 interrupt */
    GIMSK = (1 << INT0);
}

/* External Interrupt INT0 ISR */
ISR(INT0_vect) 
{
    /* Clear external interrupt flag */
    GIFR |= (1 << INT0);
    if (ext_int0_callback) 
    {
        ext_int0_callback();
    }
}




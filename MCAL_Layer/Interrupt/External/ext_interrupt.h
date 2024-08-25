/* 
 * File:   ext_interrupt.h
 * Author: Abdelrahman Ashraf
 *
 * Created on July 31, 2024, 5:09 AM
 */

#ifndef EXT_INTERRUPT_H
#define EXT_INTERRUPT_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../mcal_std_types.h"  /* Adjusted include path */

/* === Enumeration Definitions === */

/**
 * @brief External Interrupt Triggering Modes
 */
typedef enum
{
    FALLING_EDGE,       /**< Trigger interrupt on falling edge */
    RISING_EDGE,        /**< Trigger interrupt on rising edge */
    LOGIC_CHANGE,        /**< Trigger interrupt on any change */
    LOW_LEVEL    
} ExtIntMode;

/* === Structure Definitions === */

/**
 * @brief External Interrupt Configuration Structure
 *
 * This structure defines the configuration parameters for an external interrupt.
 */
typedef struct
{
    ExtIntMode mode;         /**< Interrupt mode (e.g., FALLING_EDGE, RISING_EDGE, LOGIC_CHANGE) */
    void (*callback)(void);  /**< Function pointer to the callback function to be executed on interrupt */
} ExtIntConfig;

/* === Function Prototypes === */

/**
 * @brief Initialize external interrupt based on the provided configuration.
 *
 * This function configures the external interrupt according to the settings in the
 * provided ExtIntConfig structure and enables the interrupt.
 *
 * @param[in] config  Pointer to an ExtIntConfig structure containing the interrupt settings.
 */
void Init_ExtInterrupt(const ExtIntConfig *config);

#endif /* EXT_INTERRUPT_H */



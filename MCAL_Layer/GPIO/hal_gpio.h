/* 
 * File:   hal_gpio.h
 * Author: Abdelrahman Ashraf
 */

#ifndef HAL_GPIO_H
#define HAL_GPIO_H


#include <avr/io.h>


/* === Enumeration Definitions === */

/**
 * @brief GPIO Pin Modes
 */
typedef enum
{
    GPIO_MODE_INPUT = 0, /**< Pin configured as input */
    GPIO_MODE_OUTPUT     /**< Pin configured as output */
} GpioMode;

/**
 * @brief GPIO Pin Levels
 */
typedef enum
{
    GPIO_LOW = 0, /**< Pin set to low */
    GPIO_HIGH     /**< Pin set to high */
} GpioLevel;

/**
 * @brief GPIO Pin Definitions
 */
typedef enum
{
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5
} GpioPin;

/* === Function Prototypes === */

/**
 * @brief Set the mode of a GPIO pin.
 *
 * @param[in] pin   The GPIO pin to configure.
 * @param[in] mode  The mode to set for the pin.
 */
void Gpio_SetPinMode(GpioPin pin, GpioMode mode);

/**
 * @brief Write a level to a GPIO pin.
 *
 * @param[in] pin   The GPIO pin to write to.
 * @param[in] level The level to write to the pin.
 */
void Gpio_WritePin(GpioPin pin, GpioLevel level);

/**
 * @brief Read the level of a GPIO pin.
 *
 * @param[in] pin   The GPIO pin to read.
 * @return          The level of the pin.
 */
GpioLevel Gpio_ReadPin(GpioPin pin);

#endif /* HAL_GPIO_H */



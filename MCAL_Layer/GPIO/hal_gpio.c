/* 
 * File:   hal_gpio.c
 * Author: Abdelrahman Ashraf
 */

#include "hal_gpio.h"

/* === Function Definitions === */

void Gpio_SetPinMode(GpioPin pin, GpioMode mode)
{
    /* Ensure pin values are within the valid range */
    if (pin <= GPIO_PIN5)
    {
        if (mode == GPIO_MODE_OUTPUT)
        {
            DDRB |= (1U << pin);   /* Set pin as output */
        }
        else
        {
            DDRB &= ~(1U << pin);  /* Set pin as input */
        }
    }
    else
    {
        /* Nothing to do if pin is out of range */
    }
}

void Gpio_WritePin(GpioPin pin, GpioLevel level)
{
    /* Ensure pin values are within the valid range */
    if (pin <= GPIO_PIN5)
    {
        if (level == GPIO_HIGH)
        {
            PORTB |= (1U << pin);  /* Set pin high */
        }
        else
        {
            PORTB &= ~(1U << pin); /* Set pin low */
        }
    }
    else
    {
        /* Nothing to do if pin is out of range */
    }
}

GpioLevel Gpio_ReadPin(GpioPin pin)
{
    /* Default return value to avoid undefined behavior */
    GpioLevel level = GPIO_LOW;

    /* Ensure pin values are within the valid range */
    if (pin <= GPIO_PIN5)
    {
        if ((PINB & (1U << pin)) != 0U)
        {
            level = GPIO_HIGH;
        }
        else
        {
            level = GPIO_LOW;
        }
    }
    else
    {
        /* Nothing to do if pin is out of range */
    }

    return level;
}






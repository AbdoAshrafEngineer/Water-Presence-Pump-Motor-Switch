/* 
 * File:   application.c
 * Author: Abdelrahman Ashraf
 */

#include "application.h"

static uint8 count = 0; // Variable to keep track of the number of stable water detections

int main()
{
    // Initialize GPIO pins
    Gpio_SetPinMode(GPIO_PIN0, GPIO_MODE_OUTPUT); // Set GPIO_PIN0 as output (for controlling the motor)
    Gpio_SetPinMode(GPIO_PIN1, GPIO_MODE_INPUT);  // Set GPIO_PIN1 as input (for water level sensing)
    Gpio_WritePin(GPIO_PIN1, GPIO_HIGH);          // Set GPIO_PIN1 to HIGH (typically used as pull-up resistor)

    // Initialize motor control and external interrupt
    switch_motor_off(); // Ensure the motor is turned off initially
    Init_ExtInterrupt(&pin1); // Initialize external interrupt for pin1 (assumed to be GPIO_PIN1)
    Timer0_Init(&timer0); // Initialize Timer0
    Timer0_EnableCompareMatchInterrupt(); // Enable Timer0 Compare Match interrupt

    sei(); // Enable global interrupts

    set_sleep_mode(SLEEP_MODE_IDLE); // Set the sleep mode to Idle (CPU halts but peripherals run)
    sleep_disable(); // Disable sleep mode initially (to allow normal operation before entering sleep)

    while(1)
    {
        sleep_cpu(); // Enter sleep mode (CPU halts and wakes up only on interrupts)
    }

    return 0; // Main function should never reach this point
}

// External interrupt service routine (ISR) for pin1
void ext_int0_handler(void)
{
    sleep_disable(); // Ensure sleep is disabled when an external interrupt occurs
    Timer0_EnableCompareMatchInterrupt(); // Re-enable Timer0 Compare Match interrupt
}

// Timer0 Compare Match callback function
void MyCompareMatchCallback(void)
{
    // Check if water is stable
    if (STABLE == Is_Water_Stable())
    {
        count++; // Increment count if water is stable

        // Check if the count reaches 3
        if (3 == count)
        {
            switch_motor_on(); // Turn the motor on
            count = 0; // Reset the count
            Timer0_DisableCompareMatchInterrupt(); // Disable Timer0 Compare Match interrupt
            sleep_enable(); // Enable sleep mode (CPU will enter sleep on next sleep_cpu call)
        }
        else
        {
            // Do nothing if count is not yet 3
        }
    }
    else
    {
        count = 0; // Reset count if water is not stable
        switch_motor_off(); // Turn the motor off
        Timer0_DisableCompareMatchInterrupt(); // Disable Timer0 Compare Match interrupt
        sleep_enable(); // Enable sleep mode (CPU will enter sleep on next sleep_cpu call)
    }
}

// Function to turn the motor on
void switch_motor_on(void)
{
    Gpio_WritePin(GPIO_PIN0, GPIO_HIGH); // Set GPIO_PIN0 to HIGH (motor on)
}

// Function to turn the motor off
void switch_motor_off(void)
{
    Gpio_WritePin(GPIO_PIN0, GPIO_LOW); // Set GPIO_PIN0 to LOW (motor off)
}

// Function to check if water is stable
Water_Flow Is_Water_Stable(void)
{
    Water_Flow Water_Stability = NOT_STABLE; // Default to NOT_STABLE
    if (GPIO_LOW == Gpio_ReadPin(GPIO_PIN1)) // Check if GPIO_PIN1 is LOW
    {
        Water_Stability = STABLE; // Set water stability to STABLE
    }
    else
    {
        // Do nothing if the pin is not LOW
    }
    
    return Water_Stability; // Return the water stability status
}

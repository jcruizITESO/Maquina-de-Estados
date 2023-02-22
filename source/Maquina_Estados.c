/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_common.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_LED_GPIO     BOARD_LED_RED_GPIO
#define BOARD_LED_GPIO_PIN BOARD_LED_RED_GPIO_PIN

#define BOARD_SW_GPIO        BOARD_SW3_GPIO
#define BOARD_SW_PORT        BOARD_SW3_PORT
#define BOARD_SW_GPIO_PIN    BOARD_SW3_GPIO_PIN
#define BOARD_SW_IRQ         BOARD_SW3_IRQ
#define BOARD_SW_IRQ_HANDLER BOARD_SW3_IRQ_HANDLER
#define BOARD_SW_NAME        BOARD_SW3_NAME

//Boton 2
#define BOARD_SW_GPIO_2        BOARD_SW2_GPIO
#define BOARD_SW_PORT_2        BOARD_SW2_PORT
#define BOARD_SW_GPIO_PIN_2    BOARD_SW2_GPIO_PIN
#define BOARD_SW_IRQ_2         BOARD_SW2_IRQ
#define BOARD_SW_IRQ_HANDLER_2 BOARD_SW2_IRQ_HANDLER
#define BOARD_SW_NAME_2        BOARD_SW2_NAME

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
void state1(void); //Funciones no toman ningun argumento ni retornan nigun valor
void state2(void);
void state3(void);
void state4(void);
void state5(void);
void state6(void);
void state7(void);
void state8(void);
void state9(void);
void state10(void);
/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Whether the SW button is pressed */
volatile bool g_ButtonPress = false;
volatile bool g_Button2Press = false;

/*Decalaracion de variable tipo entero sin signo de 8 bits para ahorro de memoria */
uint8_t state = 1;

/*Declaracion de puntero a funcion*/
typedef void (*state_func)(void);

/*Arreglo de punteros a funcion*/
state_func states[] = {state1,state2,state3,state4,state5,state6,state7,state8,state9,state10};

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Interrupt service fuction of switch.
 *
 * This function toggles the LED
 */
void BOARD_SW_IRQ_HANDLER(void)
{
#if (defined(FSL_FEATURE_PORT_HAS_NO_INTERRUPT) && FSL_FEATURE_PORT_HAS_NO_INTERRUPT)
    /* Clear external interrupt flag. */
    GPIO_GpioClearInterruptFlags(BOARD_SW_GPIO, 1U << BOARD_SW_GPIO_PIN);
#else
    /* Clear external interrupt flag. */
    GPIO_PortClearInterruptFlags(BOARD_SW_GPIO, 1U << BOARD_SW_GPIO_PIN);
#endif
    /* Change state of button. */
    g_ButtonPress = true;
    SDK_ISR_EXIT_BARRIER;

    /*Aumento de estados si llega a 10 se reinicia a 1*/
    state++;
    if (state > 10)
    {
        state = 1;
    }

    /*se imprime el estado actual*/
    PRINTF("Estado siguiente %d\r\n", state);
    /* Toggle LED. */
    GPIO_PortToggle(BOARD_LED_GPIO, 1U << BOARD_LED_GPIO_PIN);
    /* Reset state of button. */
    g_ButtonPress = false;

}

void BOARD_SW_IRQ_HANDLER_2(void)
{
#if (defined(FSL_FEATURE_PORT_HAS_NO_INTERRUPT) && FSL_FEATURE_PORT_HAS_NO_INTERRUPT)
    /* Clear external interrupt flag. */
    GPIO_GpioClearInterruptFlags(BOARD_SW_GPIO_2, 1U << BOARD_SW_GPIO_PIN_2);
#else
    /* Clear external interrupt flag. */
    GPIO_PortClearInterruptFlags(BOARD_SW_GPIO_2, 1U << BOARD_SW_GPIO_PIN_2);
#endif
    /* Change state of button. */
    g_ButtonPress = true;
    SDK_ISR_EXIT_BARRIER;

    /*Retroceso de estados si llega a 1 se reinicia a 10*/
    state--;
    if (state < 1)
    {
        state = 10;
    }

    /*se imprime el estado actual*/
    PRINTF("Estado anterior %d\r\n", state);
    /* Toggle LED. */
    GPIO_PortToggle(BOARD_LED_GPIO, 1U << BOARD_LED_GPIO_PIN);
    /* Reset state of button. */
    g_ButtonPress = false;
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* Define the init structure for the input switch pin */
    gpio_pin_config_t sw_config = {
        kGPIO_DigitalInput,
        0,
    };

        /* Define the init structure for the input switch pin */
        gpio_pin_config_t sw2_config = {
            kGPIO_DigitalInput,
            0,
        };

    /* Define the init structure for the output LED pin */
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        1,
    };

    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    /* Print a note to terminal. */
    PRINTF("\r\n Maquina de estados\r\n");
    PRINTF("\r\n Presiona %s para avanzar \r\n", BOARD_SW_NAME);
    PRINTF("\r\n Presiona %s para retroceder \r\n", BOARD_SW_NAME_2);

/* Init input switch GPIO. */
#if (defined(FSL_FEATURE_PORT_HAS_NO_INTERRUPT) && FSL_FEATURE_PORT_HAS_NO_INTERRUPT)
    GPIO_SetPinInterruptConfig(BOARD_SW_GPIO, BOARD_SW_GPIO_PIN, kGPIO_InterruptFallingEdge);

    GPIO_SetPinInterruptConfig(BOARD_SW_GPIO_2, BOARD_SW_GPIO_PIN_2, kGPIO_InterruptFallingEdge);
#else
    PORT_SetPinInterruptConfig(BOARD_SW_PORT, BOARD_SW_GPIO_PIN, kPORT_InterruptFallingEdge);

    PORT_SetPinInterruptConfig(BOARD_SW_PORT_2, BOARD_SW_GPIO_PIN_2, kPORT_InterruptFallingEdge);
#endif
    EnableIRQ(BOARD_SW_IRQ);
    GPIO_PinInit(BOARD_SW_GPIO, BOARD_SW_GPIO_PIN, &sw_config);

    EnableIRQ(BOARD_SW_IRQ_2);
    GPIO_PinInit(BOARD_SW_GPIO_2, BOARD_SW_GPIO_PIN_2, &sw2_config);

    /* Init output LED GPIO. */
    GPIO_PinInit(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, &led_config);




}

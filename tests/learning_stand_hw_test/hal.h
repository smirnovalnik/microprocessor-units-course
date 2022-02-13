/**
  ******************************************************************************
  * @file hal.h
  * @brief Hardware Abstraction Level
  * @author Alexander Smirnov
  ******************************************************************************
  */

#ifndef _HAL_H
#define _HAL_H

/* ADC */
#define ADC_INx_PORT    GPIOA
#define ADC_IN0_PIN     (1 << 0)
#define ADC_IN1_PIN     (1 << 1)

/* Switches */
#define SWx_PORT        GPIOA
#define SW1_PIN         (1 << 11)
#define SW2_PIN         (1 << 12)
#define SW3_PIN         (1 << 13)
#define SW4_PIN         (1 << 14)

/* Buttons */
#define SBx_PORT        GPIOB
#define SB1_PIN         (1 << 4)
#define SB2_PIN         (1 << 5)
#define SB3_PIN         (1 << 6)
#define SB4_PIN         (1 << 7)

/* KBY*/
#define KBY_PORT        GPIOB
#define R0_PIN          (1 << 0)
#define R1_PIN          (1 << 1)
#define R2_PIN          (1 << 2)
#define R3_PIN          (1 << 3)
#define C0_PIN          (1 << 4)
#define C1_PIN          (1 << 5)
#define C2_PIN          (1 << 6)
#define C3_PIN          (1 << 7)

/* LEDs */
#define LEDx_PORT       GPIOC
#define LED0_PIN        (1 << 0)
#define LED1_PIN        (1 << 1)
#define LED2_PIN        (1 << 2)
#define LED3_PIN        (1 << 3)
#define LED4_PIN        (1 << 4)
#define LED5_PIN        (1 << 5)
#define LED6_PIN        (1 << 6)
#define LED7_PIN        (1 << 7)
#define LED8_PIN        (1 << 8)
#define LED9_PIN        (1 << 9)
#define LED10_PIN       (1 << 10)
#define LED11_PIN       (1 << 11)
#define LED12_PIN       (1 << 12)
#define LED13_PIN       (1 << 13)
#define LED14_PIN       (1 << 14)
#define LED15_PIN       (1 << 15)

#define LED_COLOR_PORT  GPIOA
#define LED_RED_PIN     (1 << 6)
#define LED_GREEN_PIN   (1 << 7)
#define LED_BLUE_PIN    (1 << 8)
#define LED_WHITE_PIN   (LED_RED_PIN | LED_GREEN_PIN | LED_BLUE_PIN)

/* 7 segment */
#define Dx_PORT        GPIOC
#define D1_PIN         (1 << 8)
#define D2_PIN         (1 << 9)
#define D3_PIN         (1 << 10)
#define D4_PIN         (1 << 11)

#endif /* _HAL_H */

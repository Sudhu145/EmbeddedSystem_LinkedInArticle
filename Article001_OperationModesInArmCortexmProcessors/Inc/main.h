/*
 * main.h
 *
 *  Created on: May 27, 2023
 *      Author: SUDHAKAR
 */

#ifndef MAIN_H_
#define MAIN_H_

/*** Macro Definition ***/

/* IPSR - Interrupt Program Status Register,
 * If the execution is in Handler mode the value present in IPSR is 0 */
#define IPSR_HANDLER_MODE_VALUE (0U)

/* IPSR - Interrupt Program Status Register,
 * From the IPSR value, need to subtract 16U to get in terms of IRQ number */
#define IPSR_IRQ_OFFSET (16U)

/* NVIC ISER0 register address
 * ISER - Interrupt Set-enable Registers*/
#define NVIC_ISER0_REG_ADDR 	(0xE000E100UL)

/* NVIC ISER0 SET IRQ3 BIT - RTC_WKUP*/
#define NVIC_ISER0_SET_IRQ3_BIT ((1<<3U))

/* NVIC STIR register address
 * STIR - Software Trigger Interrupt Register*/
#define NVIC_STIR_REG_ADDR 		(0xE000EF00UL)

/* NVIC STIR INTID IRQ3 - RTC_WKUP
 * INTID[8:0] Interrupt ID of the interrupt to trigger,
 *  in the range 0-239*/
#define NVIC_STIR_SET_INTID_IRQ3 	((3 & 0x1FFU))

#endif /* MAIN_H_ */

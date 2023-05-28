/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>
#include "main.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

/*** Get ISPR register value ***/
static uint32_t __get_IPSR(void)
{
	/* Local variables */
	uint32_t ipsr_value;

	/* Get the value of IPSR */
	/*
	* asm volatile: This is a GCC compiler extension that allows inline assembly code to be included in the C or C++ source code.
	* The volatile keyword ensures that the compiler does not optimize or reorder the assembly instructions.
	*
	* "MRS %0, xPSR\n": This is the assembly instruction itself. It is written as a string literal and represents the ARM assembly instruction "MRS" (Move to Register from Special register).
	* The %0 is a placeholder for the first output operand.
	*
	* : "=r" (ipsr_value): This part is called the output operand specification. It indicates the operand that will hold the value read from the xPSR register.
	* The = sign denotes that it is an output operand, and "r" specifies that it should be allocated a general-purpose register.
	*/
	asm volatile (
		"MRS %0, xPSR\n"
		: "=r" (ipsr_value)
	);

	/* Extract the IPSR bits[8:0] */
	ipsr_value = (ipsr_value & 0x1FF);

	/* Return IPSR value */
	return ipsr_value;
}

/*** Print current operation mode ***/
static void printCurrOperationMode(void)
{
	/* Local variables */
	uint32_t curr_ipsrValue;

	/* Get the current IPSR value */
	curr_ipsrValue = __get_IPSR();

	/* Enter into this condition, if current operation mode is thread */
	if(curr_ipsrValue == IPSR_HANDLER_MODE_VALUE)
	{
		printf("Current Operation Mode : Handler\n");
	}
	/* Enter into this condition, if current operation mode is handler */
	else
	{
		printf("Current Operation Mode : Thread, ISR Number : %ld\n",(curr_ipsrValue - IPSR_IRQ_OFFSET));
	}
}

/*** Generate interrupt using SW for RTC WakeUp ***/
static void generateInterruptForRtcWakeUp(void)
{
	/* Pointers for ISER0 and STIR registers */
	uint32_t *pISER0 = ((uint32_t*)NVIC_ISER0_REG_ADDR);
	uint32_t *pSTIR  = ((uint32_t*)NVIC_STIR_REG_ADDR);

	/* Enable interrupt for IRQ3 (i,e. RTC_WKUP) */
	*pISER0 |= NVIC_ISER0_SET_IRQ3_BIT;

	/* Set SW interrupt for IRQ3 (i,e. RTC_WKUP) */
	*pSTIR  |= NVIC_STIR_SET_INTID_IRQ3;

}

int main(void)
{
	/* Print current operation mode */
	printCurrOperationMode();

	/* Generate RTC WakeUp interrupt */
	generateInterruptForRtcWakeUp();

	/* Print current operation mode */
	printCurrOperationMode();

    /* Loop forever */
	for(;;);
}

void RTC_WKUP_IRQHandler(void)
{
	/* Print current operation mode */
	printCurrOperationMode();
}
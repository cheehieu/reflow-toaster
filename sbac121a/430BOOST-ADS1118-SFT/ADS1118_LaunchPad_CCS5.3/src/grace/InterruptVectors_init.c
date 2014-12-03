/*
 *  This file is automatically generated and does not require a license
 *
 *  ==== WARNING: CHANGES TO THIS GENERATED FILE WILL BE OVERWRITTEN ====
 *
 *  To make changes to the generated code, use the space between existing
 *      "USER CODE START (section: <name>)"
 *  and
 *      "USER CODE END (section: <name>)"
 *  comments, where <name> is a single word identifying the section.
 *  Only these sections will be preserved.
 *
 *  Do not move these sections within this file or change the START and
 *  END comments in any way.
 *  ==== ALL OTHER CHANGES WILL BE OVERWRITTEN WHEN IT IS REGENERATED ====
 *
 *  This file was generated from
 *      C:/ti_5.5/grace_2_20_01_12/packages/ti/mcu/msp430/csl/interrupt_vectors/InterruptVectors_init.xdt
 */
#include <msp430.h>

/* USER CODE START (section: InterruptVectors_init_c_prologue) */
extern volatile unsigned char flag;	//global flag.
/* USER CODE END (section: InterruptVectors_init_c_prologue) */

/*
 *  ======== InterruptVectors_graceInit ========
 */
void InterruptVectors_graceInit(void)
{
}


/* Interrupt Function Prototypes */




/*
 *  ======== PORT1 Interrupt Service Routine ========
 *
 * Here are several important notes on using PORTx interrupt Handler:
 *
 * 1. User must explicitly clear the port interrupt flag before exiting
 *
 *    PxIFG &= ~(BITy);
 *
 * 2. User could also exit from low power mode and continue with main
 *    program execution by using the following instruction before exiting
 *    this interrupt handler.
 *
 *    __bic_SR_register_on_exit(LPMx_bits);
 *
 */
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR_HOOK(void)
{
    /* USER CODE START (section: PORT1_ISR_HOOK) */
	flag ^= BIT0;
	P1IFG &= ~BIT3; // P1.3 IFG cleared
    /* USER CODE END (section: PORT1_ISR_HOOK) */
}

/*
 *  ======== PORT2 Interrupt Service Routine ========
 *
 * Here are several important notes on using PORTx interrupt Handler:
 *
 * 1. User must explicitly clear the port interrupt flag before exiting
 *
 *    PxIFG &= ~(BITy);
 *
 * 2. User could also exit from low power mode and continue with main
 *    program execution by using the following instruction before exiting
 *    this interrupt handler.
 *
 *    __bic_SR_register_on_exit(LPMx_bits);
 *
 */
#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR_HOOK(void)
{
    /* USER CODE START (section: PORT2_ISR_HOOK) */
	P2IE &= ~(BIT1 + BIT2);	// close P2 interrupt
	if (P2IFG&BIT1)
    {
    	flag |= BIT1;		// flag bit 1 is set
    	P2IFG &= ~BIT1; 	// P2.1 IFG cleared
    }
    else if(P2IFG&BIT2)
    {
    	flag |= BIT2;		// flag bit 2 is set
    	P2IFG &= ~BIT2; 	// P2.2 IFG cleared
    }

	P2IE |= BIT1 + BIT2;		// open P2 interrupt
    /* USER CODE END (section: PORT2_ISR_HOOK) */
}

/*
 *  ======== Timer0_A3 Interrupt Service Routine ======== 
 */
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR_HOOK(void)
{
    /* USER CODE START (section: TIMER0_A0_ISR_HOOK) */
	flag |= BIT7;
	flag ^= BIT6;
	if (!(flag & BIT6))
	flag |= BIT3;
    /* USER CODE END (section: TIMER0_A0_ISR_HOOK) */
}


/*
 *  ======== Timer1_A3 Interrupt Service Routine ======== 
 */
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR_HOOK(void)
{
    /* USER CODE START (section: TIMER1_A0_ISR_HOOK) */
	flag |= BIT4;
	flag ^= BIT5;
    /* USER CODE END (section: TIMER1_A0_ISR_HOOK) */
}


/*
 *  ======== NMI_VECTOR Interrupt Service Routine ========
 *
 *  You can check which interrupt flag was triggered here.
 *  Copy and paste the following function as desired.
 *
    if (IFG1 & NMIIFG) {

    }
    else if (IFG1 & OFIFG) {

    }
    else if (IFG1 & ACCVIFG) {

    }
 *
 */
#pragma vector=NMI_VECTOR
__interrupt void NMI_ISR_HOOK(void)
{
    /* USER CODE START (section: NMI_ISR_HOOK) */
    /* replace this comment with your code */
    /* USER CODE END (section: NMI_ISR_HOOK) */
}
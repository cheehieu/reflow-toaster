/*
 * 		- name: main.c
 *		- write data: 19 Nov. 2012
 *		- modification data: 31 Nov. 2012
 *		- author: Wayne Xu (a0219294)
 *		- version: v1.2
 *
 * ***description
 *
 * 1. Program uses GRACE configuration for Device Configuration;
 * 		- SMCLK, DCO at 1MHz
 * 		- ACLK, external oscillator 32.768kHz
 * 		- USCIA0 as UART, 9600, 8 bits Data, No parity, 1 Stop (Hardware Mode)
 * 		- USCIB0 as 3 line SPI, Master Mode, 100kHz SCLK
 * 		- P2.0 as output, is used as CS for ADS1118 ADC device
 * 		- P2.3 as output,is used as RST of LCD
 * 		- P2.4 as output,is used as RS of LCD
 * 		- P2.5 ,is used as CS of LCD
 * 		- P2.1, P2.2 as input: SW1, SW2.
 * 		- P1.0 as output, is used as switch of buzzer
 * 2. this project is used to measure the temperature by type-K thermocouple.
 * 		- far-end temperature is measured by thermocouple, local temperature is measured by the internal sensor of ADS1118
 * 		- ADC mode: inputs are AIN0/AIN1, FS=+/-0.256, SS, DR=128sps, PULLUP on DOUT
 * 		- temperature mode: DR=128sps, PULLUP on DOUT
 * 		- Reference Tables are used to transform ADC code to temperature.
 *
 */

/*
 * ======== Standard MSP430 includes ========
 */
#include <msp430.h>

/*
 * ======== Grace related includes ========
 */
#include <ti/mcu/msp430/csl/CSL.h>
#include "UART_TxRx.h"
#include "ADS1118.h"
#include "LCD_driver.h"

void System_Initial();	//Initialize system
void half_second();
void time_display();
void ADC_display();
void delay();		//delay function
void relayPID(int, int);
void calcSetPoint();


#define BUZZ_ON 	P1OUT &= ~BIT0;	//set P1.0 low
#define BUZZ_OFF 	P1OUT |= BIT0;	//set P1.0 high
#define RELAY_ON	P1OUT |= BIT2	//set P1.2 high
#define RELAY_OFF	P1OUT &= ~BIT2	//set P1.2 low

#define MAX_SECONDS		300

/*
 * ======== global variable ========
 */
/* flag is used to transmit parameter between interrupt service function and main function.
 * the flag will be changed by ISR in InterruptVectors_init.c     ...\grace\InterruptVectors_init.c
 *
 * Bit0, Launchpad S2 is pushed
 * Bit1, SW1 on BoosterPack is pushed
 * Bit2, SW2 on BoosterPack is pushed
 * Bit3, 1 second timer interrupt
 * Bit4, timer for ADC interrupts
 * Bit5, ADC input flag, 0 is internal temperature sensor, 1 is AIN0-AIN1
 * Bit6, make an inversion every half a second
 * Bit7, half a second interrupt
 * Bit8, for Fahrenheit display
 * Bit9, ADC channel flag, 0 for channel 0, 1 for channel 1.
 */
volatile unsigned int  flag = 0;		//global flag.
unsigned long time = 0;				// current time in seconds
signed int temp, sp_temp;
signed int p_gain=400, i_gain=1, d_gain=1;
signed long int p_error=0, i_error=0, d_error=0;
signed long int p_out;
char* Oven_States_Strings[] = {"OFF    ", "PREHEAT", "SOAK   ", "REFLOW1", "REFLOW2", "COOL  "};
enum Oven_States {
	OFF,
	PREHEAT,
	SOAK,
	REFLOW1,
	REFLOW2,
	COOL
};
enum Oven_States oven_state = OFF;
//int measured[MAX_SECONDS], desired[MAX_SECONDS];		//data array for logging temperatures

/*
 *  ======== main ========
 */
main(int argc, char *argv[])
{
	CSL_init();                 // Activate Grace-generated configuration
	delay();					//
    System_Initial();			// initialize system.
   	delay();					// delay and wait the first conversion.
   	_enable_interrupt();		// enable interrupt

   	while(1) {
   		//Half second timer interrupt
   		if(flag & BIT7) {
   			half_second();
   		}

   		//Read ADC result
   		if(flag & BIT4) {
   			ADC_display();			//update the temperature display
   			relayPID(temp, sp_temp);
   			//measured[time] = temp;
   			//desired[time] = sp_temp;
   		}

   		//One second timer interrupt
   		if(flag & BIT3) {
   			time_display();												//update the time display
   			LCD_display_string(0,Oven_States_Strings[oven_state]);		//update the state display
   			if(oven_state==COOL && time>MAX_SECONDS) {					//sound buzzer when soldering is complete
   				BUZZ_ON;
   			}
   		}

   		//SW1 on BoosterPack is pushed
   		if(flag & BIT1) {
   			flag &= ~ BIT1;					//reset flag
   			if(oven_state == OFF) {
   				oven_state = PREHEAT;		//change oven state
   				time = 0;
   			}
   		}

   		//SW2 on BoosterPack is pushed
   		if((flag & BIT2)) {
   			flag &= ~ BIT2;			//reset flag
   			oven_state = OFF;		//turn off oven
   			BUZZ_OFF;				//turn off buzzer
   		}

   		//S2 on LaunchPad is pushed
   		if(flag & BIT0)	{
   			flag &= ~ BIT0;			//reset flag
   			flag ^= BIT8;			//change temperature scale
 /*  			if(flag & BIT8) {		//test GPIO function
   				RELAY_ON;
   			} else {
   				RELAY_OFF;
   			}
*/   		}

   		else
   		__no_operation();
   	}
}


void delay(void) {
	unsigned int k;
	for (k = 1000; k > 0; k--)
		__no_operation();
}

void relayPID(int t, int sp) {
	//Relay control loop
	p_error = sp_temp - temp;
	i_error += p_error;			//windup guard to cap integrated error
	d_error = p_error - d_error;
	p_out = (p_gain * p_error);// + (i_gain * i_error) + (d_gain * d_error);

	if(oven_state==OFF) {
		TA0CCR1 = 0;			//relay off
//	} else if (p_error > 200) {
//	    TA0CCR1 = 15625;
	} else if(p_error>75 || p_out>31249) {
		TA0CCR1 = 31249;
	} else if (p_error<0) {
		TA0CCR1 = 0;
	}
		else {
		TA0CCR1 = p_out;	//x/31249
	}
}

void calcSetPoint() {
	//Reflow solder profile for Chip Quik SMD291AX solder paste Profile-B
	//#ifdef CHIP_QUICK_SMD291AX
	if(oven_state==OFF) {
		sp_temp = 250;
	} else if(oven_state==PREHEAT) {
		sp_temp = 13 * time + 250;				//13.333 ~= ((145-25)/90)*10
	} else if(oven_state==SOAK) {
		sp_temp = 3 * (time-90) + 1450;			//3.166 ~= ((183-145)/(210-90))*10
	} else if(oven_state==REFLOW1) {
		sp_temp = 12 * (time-210) + 1830;		//12.333 ~=((220-183)/(240-210))*10
	} else if(oven_state==REFLOW2) {
		sp_temp = -12 * (time-240) + 2200;		//-12.333 ~= ((183-220)/(270-240))*10
	} else if(oven_state==COOL) {
		sp_temp = -18 * (time-270) + 1830;		//-17.666 ~= ((130-183)/(300-270))*10
	} else {
		sp_temp = temp;
	}
}

void ADC_display() {
	static signed int local_data, far_data;
	signed int adj_temp=250, adj_sp_temp=250;
	flag &= ~ BIT4;					//reset flag

	if (!(flag & BIT5)) {
		local_data = ADS_Read(1);	//read local temperature data,and start a new conversion for far-end temperature sensor
	} else {
		far_data = ADS_Read(0);		//read far-end temperature,and start a new conversion for local temperature sensor.
		temp = far_data + local_compensation(local_data);	// transform the local_data to compensation codes of far-end.
		temp = ADC_code2temp(temp);	// transform the far-end thermocouple codes to temperature.

		calcSetPoint();

		//Display temperatures in Fahrenheit or Celsius
		if(flag & BIT8) {
			adj_temp = temp * 9/5 + 320;
			adj_sp_temp = sp_temp * 9/5 + 320;
			LCD_display_temp(1,0,adj_temp);
			LCD_display_char(1,6,'F');
			LCD_display_temp(1,9, adj_sp_temp);
			LCD_display_char(1,15,'F');
		} else {
			adj_temp = temp;
			adj_sp_temp = sp_temp;
			LCD_display_temp(1,0,adj_temp);
			LCD_display_char(1,6,'C');
			LCD_display_temp(1,9, (int)adj_sp_temp);
			LCD_display_char(1,15,'C');
		}
	}
}

void time_display() {
	flag &= ~BIT3;								//reset flag
	if(oven_state != OFF) {
		time = (time>=86400) ? 0 : time+1;		//increment time
  		LCD_display_time(0,8,time);				//display time on LCD
  		if(time <= 90) {
  			oven_state = PREHEAT;
  		} else if(time <= 210) {
  			oven_state = SOAK;
  		} else if(time <= 240) {
  			oven_state = REFLOW1;
  		} else if(time <= 270) {
  			oven_state = REFLOW2;
  		} else {
  			oven_state = COOL;
  		}
	}
}

/*
 * function name: half_second()
 * description: it is executed every half a second. it has three functions,
 * the first one is to compare the Actual temperature and threshold temperature, if Actual temperature is higher than threshold
 * temperature, buzzer will work
 * the second one is to flicker the threshold temperature bit which is being set.
 * the third one is to flicker the time bit which is being set.
 */

void half_second() {
	flag &= ~ BIT7;
}


/*
 * function name:System_Initial()
 * description: Initialize the system. include I/O, LCD and ADS1118.
 */
void System_Initial() {
	//Initialize IO
	P1OUT = 0x09;
	P2OUT = 0x3F;

/*	//GPIO function
	P1SEL &= ~BIT2;
	P1SEL2 &= ~BIT2;
	P1DIR |= BIT2;
*/
	//PWM for solid state relay control
	P1SEL |= BIT2;
	P1SEL2 &= ~BIT2;
	P1DIR |= BIT2;
    TA0CCTL1 = OUTMOD_7;

	//Initialize LCD
	LCD_init();
	LCD_clear();
	LCD_display_string(0,"TOASTER OVEN");
	LCD_display_time(0,8,time);
	LCD_display_char(1,5,0xDF);
	LCD_display_char(1,6,'C');
	LCD_display_char(1,14,0xDF);
	LCD_display_char(1,15,'C');

	ADS_Config(0);		//set ADS1118 to convert local temperature, and start conversion
}

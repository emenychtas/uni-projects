#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/locktl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

#define PIO(x) ((1)<<(x))

// Input & output lines
#define IBIT 8
#define OBIT 14

// Interrupt controllers
#define PIOA_ID 2
#define TC0_ID 17

void FIQ_handler(void);
void init_pioa(void);
void init_aic(void);
void init_tc(void);

void clear_aic(void);
void clear_tc(void);

void led_on(int pos);
void led_off(int pos);

// Global interrupt timer
unsigned int nfiq = 0;

// Pointers to peripherals
PIO *pioa = NULL;
AIC *aic = NULL;
TC *tc = NULL;

int main(void) {
	char key;
	
	// 1. System initialization
	STARTUP;

	// 2. Initialize peripherals
	init_pioa();

	// 3. Turn led off
	led_off(OBIT);

	// 4. Initialize timer
	init_tc();

	// 5. Initialize interrupt controller
	init_aic();

	tc->Channel_0.CCR = 0x5; // 6. Start the timer

	// 7. Wait until user presses 'x'
	while ( (key == getchar() != 'x') ) { }

	// 8. Then cleanup peripherals and system
	clear_aic();
	clear_tc();
	led_off(OBIT); // 9. Turn off led
	CLEANUP;

	// Exit
	return 0;
}

// Function to initialize PIOA
void init_pioa(void) {
	pioa->PER = PIO(OBIT); // General purpose enable
	pioa->OER = PIO(OBIT); // Output enable

	pioa->PER = PIO(IBIT); // General purpose enable
	pioa->ODR = PIO(IBIT); // Input enable
}

// Function to initialize timer
void init_tc(void) {
	unsigned int tmp;
	
	// TC0 Interrupt enable
	tc->Channel_0.RC = 4096;
	tc->Channel_0.CMR = 0x824;
	tc->Channel_0.IDR = 0xFF;
	tc->Channel_0.IER = 0x10;

	tmp = tc->Channel_0.SR // Clear any pending timer IRQ
}

// Function to initialize aic
void init_aic(void) {
	aic->FFER = (1<<TC0_ID); // TC0 IRQ is FIQ
	aic->IECR = (1<<TC0_ID); // Activate TC0 IRQ
	aic->ICCR = (1<<TC0_ID); // Clear posssible pending IRQ
}

void clear_tc(void) {
	tc->Channel_0.CCR = 0x02;
}

void clear_aic(void) {
	aic->IDCR = (1<<TC0_ID); // Interrupt disable
}

// FIQ Handler
void FIQ_handler(void) {
	unsigned int tmp;
	unsigned int fiq = 0;
	
	fiq = aic->IPR // Read the IRQ source

	if ( fiq & (1<<TC0_ID) ) {
		tmp = tc->Channel_0.SR; // Clear timer IRQ
		tc->Channel_0.CCR = 0x05; // Start the timer
		aic->ICCR = (1<<TC0_ID); // Clear pending timer IRQ

		if ( nfiq & 1 ) {
			led_off(OBIT);
		} else {
			led_on(OBIT);
		}

		nfiq++;
	}
}

void lef_on(int pos) {
	pioa->CODR = PIO(pos); //clear the bit
}

void lef_off(int pos) {
	pioa->SODR = PIO(pos); // Set the bit
}










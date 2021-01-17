#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <header.h>

void FIQ_handler(void);
void Init_PIOA(void);

// Peripheral Pointers
PIO* pioa = NULL;
AIC* aic = NULL;
TC*  tc = NULL;

int main(void)
{
	unsigned int counter = 100;
	unsigned int bitmask, next;

	// System Initialization
	STARTUP;

	// Peripherals Initialization
	Init_PIOA();

	// Run until user enters 'e'.
	while (getchar() != 'e')
	{
		counter++;

		if (counter >= 100) // Start new 100 cycle loop.
		{
			pioa->CODR = 0x7F; // Clear output data.
			bitmask = 1;       // Renew bitmask.
			counter = 0;       // Restart cycle count.
			next = 20;         // Light first LED on cycle 20.
		}
		else if (counter >= next && counter <= 80) // Time to light an LED.
		{
			pioa->SODR = bitmask;   // Light LED indicated by bitmask.
			bitmask = bitmask << 1; // Shift bitmask to the next LED.
			next = next + 10;       // Light next LED in 10 cycles.
		}
	}

	// System Recovery
	CLEANUP;

	return 0;
}

// PIOA Initialization
void Init_PIOA(void)
{
	// Output Lines (Bits 6:0)
	pioa->PER = 0x7F; // General Purpose Enable
	pioa->OER = 0x7F; // Output Enable
}

// FIQ Handler Routine
void FIQ_handler(void)
{
	// Do nothing.
}
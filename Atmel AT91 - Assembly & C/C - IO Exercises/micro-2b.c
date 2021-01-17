#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <header.h>

// Peripheral IDs
#define PIOA_ID              2
#define TC0_ID               17

// PIO Input Line
#define INPUT_BIT            7

// LED States
#define LED_IDLE             0
#define LED_ROTATING_RIGHT   1
#define LED_ROTATING_LEFT    2

// BUTTON States
#define BUT_PRESSED          1
#define BUT_NOT_PRESSED      0

void FIQ_handler(void);
void Init_PIOA(void);
void Init_AIC(void);
void Init_TC(void);
void Timer_Start(void);
void Timer_Stop(void);

// Peripheral Pointers
PIO* pioa = NULL;
AIC* aic = NULL;
TC*  tc = NULL;

unsigned int led_state = LED_IDLE;
unsigned int button_state = BUT_NOT_PRESSED;

unsigned int mask = 1; // Bitmask Source

int main(void)
{
	unsigned int counter = 100;
	unsigned int bitmask, next;

	// System Initialization
	STARTUP;

	// Peripherals Initialization
	Init_PIOA();
	Init_AIC();
	Init_TC();

	// Run until user enters 'e'.
	while (getchar() != 'e')
	{
		counter++;

		if (counter >= 100) // Start new 100 cycle loop.
		{
			pioa->CODR = 0x7F; // Clear output data.
			bitmask = mask;    // Renew bitmask.
			counter = 0;       // Restart cycle count.
			next = 20;         // Light first LED on cycle 20.
		}
		else if (counter >= next && counter <= 80) // Time to light an LED.
		{
			pioa->SODR = bitmask;             // Light LED indicated by bitmask.
			bitmask = bitmask << 1;           // Shift bitmask to the next LED.
			if (bitmask == 0x80) bitmask = 1; // Circular shift on bitmask.
			next = next + 10;                 // Light next LED in 10 cycles.
		}
	}

	// Stop the timer.
	Timer_Stop();

	// System Recovery
	CLEANUP;

	return 0;
}

// PIOA Initialization
void Init_PIOA(void)
{
	unsigned int tmp;

	// Output Lines (Bits 6:0)
	pioa->PER = 0x7F; // General Purpose Enable
	pioa->OER = 0x7F; // Output Enable

	// Input Line
	pioa->PER = (1 << INPUT_BIT);  // General Purpose Enable
	pioa->ODR = (1 << INPUT_BIT);  // Input Enable
	pioa->PUER = (1 << INPUT_BIT); // Pull-Up Enable
	pioa->IDR = 0xFFFFFFFF;        // Disable all PIOA interrupts.
	tmp = pioa->ISR;               // Clear PIOA interrupt status register.
	pioa->IER = (1 << INPUT_BIT);  // Enable Input Line's interrupt.
}

// AIC Initialization
void Init_AIC(void)
{
	aic->ICCR = (1 << PIOA_ID) | (1 << TC0_ID); // Clear PIOA and TC0 interrupts.
	aic->FFER = (1 << PIOA_ID) | (1 << TC0_ID); // Make PIOA and TC0 interrupts FIQs.
	aic->IECR = (1 << PIOA_ID) | (1 << TC0_ID); // Enable PIOA and TC0 interrupts.
}

// TC Initialization
void Init_TC(void)
{
	unsigned int tmp;

	tc->Channel_0.CMR = 0x8084;   // Timer Mode, Stop On RC, 8192 Hz Clock
	tc->Channel_0.RC = 1638;      // 5 Hz Repetition
	tc->Channel_0.IDR = 0xFF;     // Disable all TC interrupts.
	tmp = tc->Channel_0.SR;       // Clear TC status register.
	tc->Channel_0.IER = (1 << 4); // Enable RC compare interrupt.
}

// Clears the timer and starts counting.
void Timer_Start(void)
{
	tc->Channel_0.CCR = 0x5;
}

// Stops the timer.
void Timer_Stop(void)
{
	tc->Channel_0.CCR = 0x2;
}

// FIQ Handler Routine
void FIQ_handler(void)
{
	unsigned int tmp;
	unsigned int irq_buffer;

	irq_buffer = aic->IPR; // Get pending IRQs from AIC.

	// Interrupt from PIOA
	if (irq_buffer & (1 << PIOA_ID))
	{
		tmp = pioa->ISR;            // Clear PIOA IRQ register.
		aic->ICCR = (1 << PIOA_ID); // Wipe the IRQ from the AIC.

		// Button Pressed (previously not pressed)
		if (button_state == BUT_NOT_PRESSED && (pioa->PDSR & (1 << INPUT_BIT)))
		{
			button_state = BUT_PRESSED;

			// Change LED rotation state.
			switch (led_state)
			{
			case LED_IDLE:
				led_state = LED_ROTATING_RIGHT; // LED_IDLE -> LED_ROTATING_RIGHT
				Timer_Start();                  // Restart timer count.
				break;

			case LED_ROTATING_RIGHT:
				led_state = LED_ROTATING_LEFT;  // LED_ROTATING_RIGHT -> LED_ROTATING_LEFT
				Timer_Start();                  // Restart timer count.
				break;

			case LED_ROTATING_LEFT:
				led_state = LED_IDLE;           // LED_ROTATING_LEFT -> LED_IDLE
				Timer_Stop();                   // Stop timer count.
				break;
			}
		}
		// Button Released (previously pressed)
		else if (button_state == BUT_PRESSED && !(pioa->PDSR & (1 << INPUT_BIT)))
		{
			button_state = BUT_NOT_PRESSED;
		}
	}

	// Interrupt from TC0
	if (irq_buffer & (1 << TC0_ID))
	{
		tmp = tc->Channel_0.SR;    // Clear TC status register.
		aic->ICCR = (1 << TC0_ID); // Wipe the IRQ from the AIC.

		// Rotate the mask.
		switch (led_state)
		{
		case LED_ROTATING_RIGHT:
			mask = mask >> 1;              // Right-shift the mask.
			if (mask == 0x00) mask = 0x40; // Circular shift.
			break;

		case LED_ROTATING_LEFT:
			mask = mask << 1;              // Left-shift the mask.
			if (mask == 0x80) mask = 0x01; // Circular shift.
			break;
		}

		// Restart timer count.
		Timer_Start();
	}
}
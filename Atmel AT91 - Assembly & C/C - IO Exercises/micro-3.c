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
#define PIOA_ID            2
#define TC0_ID             17

// SSD States
#define SSD_IDLE           0
#define SSD_HOLD           1

// BUTTON States
#define BUT_PRESSED        1
#define BUT_NOT_PRESSED    0

void FIQ_handler(void);
void Init_PIOA(void);
void Init_AIC(void);
void Init_TC(void);
void Timer_Start(void);
void Timer_Stop(void);
void Count_Increment(void);
void Display_Refresh(void);
void Display_Clear(void);

// Peripheral Pointers
PIO* pioa = NULL;
AIC* aic = NULL;
TC*  tc = NULL;

// PIO Lines
unsigned int SSD_LINES = 0xFF;    // Count Output (Bits 7:0)
unsigned int DOT_LINE = 1 << 8;   // Dot Output   (Bit 8)
unsigned int INPUT_LINE = 1 << 9; // Button Input (Bit 9)

// Program Fields
unsigned int units = 0;           // Count Units   (0-9)
unsigned int decades = 0;         // Count Decades (0-5)
unsigned int timer_irqs = 0;      // Number of timer IRQs

// Peripheral States
unsigned int ssd_state = SSD_IDLE;
unsigned int button_state = BUT_NOT_PRESSED;

int main(void)
{
	// System Initialization
	STARTUP;

	// Peripherals Initialization
	Init_PIOA();
	Init_AIC();
	Init_TC();

	// Run until user enters 'e'.
	while (getchar() != 'e')
	{
		// Do nothing.
	}

	// System Recovery
	Timer_Stop();
	Display_Clear();
	CLEANUP;

	return 0;
}

// PIOA Initialization
void Init_PIOA(void)
{
	unsigned int tmp;

	// Output Lines (Count: Bits 7:0)
	pioa->PER = SSD_LINES; // General Purpose Enable
	pioa->OER = SSD_LINES; // Output Enable

	// Output Line (Dots)
	pioa->PER = DOT_LINE;
	pioa->OER = DOT_LINE;

	// Input Line
	pioa->PER = INPUT_LINE;  // General Purpose Enable
	pioa->ODR = INPUT_LINE;  // Input Enable
	pioa->PUER = INPUT_LINE; // Pull-Up Enable
	pioa->IDR = 0xFFFFFFFF;  // Disable all PIOA interrupts.
	tmp = pioa->ISR;         // Clear PIOA interrupt status register.
	pioa->IER = INPUT_LINE;  // Enable Input Line's interrupt.
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
	tc->Channel_0.RC = 4096;      // 2 Hz Repetition
	tc->Channel_0.IDR = 0xFF;     // Disable all TC interrupts.
	tmp = tc->Channel_0.SR;       // Clear TC status register.
	tc->Channel_0.IER = 1 << 4;   // Enable RC compare interrupt.
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
	if (irq_buffer & 1 << PIOA_ID)
	{
		tmp = pioa->ISR;          // Clear PIOA IRQ register.
		aic->ICCR = 1 << PIOA_ID; // Wipe the IRQ from the AIC.

		// Button Pressed (previously not pressed)
		if (button_state == BUT_NOT_PRESSED && (pioa->PDSR & INPUT_LINE))
		{
			button_state = BUT_PRESSED;

			// Change SSD state.
			switch (ssd_state)
			{
			case SSD_IDLE:
				ssd_state = SSD_HOLD;
				break;

			case SSD_HOLD:
				ssd_state = SSD_IDLE;
				break;
			}
		}
		// Button Released (previously pressed)
		else if (button_state == BUT_PRESSED && !(pioa->PDSR & INPUT_LINE))
		{
			button_state = BUT_NOT_PRESSED;
		}
	}

	// Interrupt from TC0
	if (irq_buffer & 1 << TC0_ID)
	{
		tmp = tc->Channel_0.SR;  // Clear TC status register.
		aic->ICCR = 1 << TC0_ID; // Wipe the IRQ from the AIC.

		timer_irqs++;

		if (timer_irqs % 2 == 1)
		{
			Count_Increment();
		}

		Display_Refresh();

		// Restart timer count.
		Timer_Start();
	}
}

// Increment ongoing count.
void Count_Increment(void)
{
	units++;

	if (units == 10)
	{
		units = 0;
		decades++;

		if (decades == 6)
		{
			decades = 0;
		}
	}
}

// Refresh SSD display.
void Display_Refresh(void)
{
	switch (ssd_state)
	{
	case SSD_IDLE: // Display count.
		Display_Clear();                     // Clear SSD display.
		pioa->SODR = (decades << 4) + units; // Set count output bits.
		break;

	case SSD_HOLD: // Blink SSD dots.
		if (pioa->ODSR & DOT_LINE) // Dots Are On
		{
			pioa->CODR = DOT_LINE; // Turn Off
		}
		else                       // Dots Are Off
		{
			pioa->SODR = DOT_LINE; // Turn On
		}
		break;
	}
}

// Clear SSD display.
void Display_Clear(void)
{
	pioa->CODR = SSD_LINES; // Clear digits.
	pioa->CODR = DOT_LINE;  // Turn off dots.
}
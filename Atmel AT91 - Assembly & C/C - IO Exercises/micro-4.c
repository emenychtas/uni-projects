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

// Button States
#define BUT_PRESSED        1
#define BUT_NOT_PRESSED    0

// [ Light 1 ] [     Light 2    ] [   Light 3  ]
// [Red|Green] [Red|Orange|Green] [Âlink Orange]

#define S0    0x24    // 10 001 0
#define S1    0x25    // 10 001 1
#define S2    0x23    // 10 010 1
#define S3    0x29    // 10 100 1
#define S4    0x19    // 01 100 1
#define S5    0x19    // 01 100 1
#define S6    0x28    // 10 100 0

void FIQ_handler(void);
void Init_PIOA(void);
void Init_AIC(void);
void Init_TC(void);
void Timer_Start(void);
void Timer_Stop(void);
void Output_Refresh(void);
void Output_Clear(void);
void Change_State(int);

// Peripheral Pointers
PIO* pioa = NULL;
AIC* aic  = NULL;
TC*  tc   = NULL;

// PIO Lines
unsigned int BUT_START  = 0x80; // START Button (Bit 7)
unsigned int BUT_STOP   = 0x40; // STOP  Button (Bit 6)
unsigned int LIGHTS     = 0x3F; // Light Bits   (Bits 5:0)
unsigned int ORANGE_BIT = 0x00; // Light 3 Bit  (Bit 0)

// Program Fields
unsigned int temp;                // For Register Wipes
unsigned int irq_buffer;          // Pending IRQs Buffer
unsigned int quarters = 0;        // Quarters of a Second
unsigned int request_service = 0; // Triggers Some State Switches

// Peripheral States
unsigned int lights_state = S0;
unsigned int stop_but_state = BUT_NOT_PRESSED;
unsigned int start_but_state = BUT_NOT_PRESSED;

int main(void)
{
	// System Initialization
	STARTUP;

	// Peripheral Initialization
	Init_PIOA();
	Init_AIC();
	Init_TC();

	// Display the first state and start the timer.
	Output_Refresh();
	Timer_Start();

	// Run until user enters 'e'.
	while (getchar() != 'e')
	{
		// Do nothing.
	}

	// Stop the timer and clear output.
	Timer_Stop();
	Output_Clear();

	// System Recovery
	CLEANUP;

	return 0;
}

// PIOA Initialization
void Init_PIOA(void)
{
	// Output Lines (Lights)
	pioa->PER = LIGHTS; // General Purpose Enable
	pioa->OER = LIGHTS; // Output Enable

	// Input Lines (Buttons)
	pioa->PER  = BUT_START | BUT_STOP; // General Purpose Enable
	pioa->ODR  = BUT_START | BUT_STOP; // Input Enable
	pioa->PUER = BUT_START | BUT_STOP; // Pull-Up Enable

	// Interrupts
	pioa->IDR = 0xFFFFFFFF;           // Disable all PIOA interrupts.
	temp = pioa->ISR;                 // Clear PIOA interrupt status register.
	pioa->IER = BUT_START | BUT_STOP; // Enable button interrupts.
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
	tc->Channel_0.CMR = 0x8084; // Timer Mode, Stop On RC, 8192 Hz Clock
	tc->Channel_0.RC  = 2048;   // 4 Hz Repetition
	tc->Channel_0.IDR = 0xFF;   // Disable all TC interrupts.
	temp = tc->Channel_0.SR;    // Clear TC status register.
	tc->Channel_0.IER = 1 << 4; // Enable RC compare interrupt.
}

// Start counting from zero.
void Timer_Start(void)
{
	tc->Channel_0.CCR = 0x5;
}

// Stop counting.
void Timer_Stop(void)
{
   	tc->Channel_0.CCR = 0x2;
}

// Set output lines.
void Output_Refresh(void)
{
	Output_Clear();

	// Bitmask: & ~(((quarters >> 1) % 2) << ORANGE_BIT)
	//
	// Generates a number full of 1's or a number with just one 0 on
	// the bit that controls Light 3. This is how the blinking works.

	pioa->CODR = lights_state & ~(((quarters >> 1) % 2) << ORANGE_BIT);
}

// Turn off all LEDs.
void Output_Clear(void)
{
	pioa->SODR = LIGHTS;
}

// Change light state.
void Change_State(int next_state)
{
	lights_state = next_state;
	quarters = 0;
}

// FIQ Handler Routine
void FIQ_handler(void)
{
	irq_buffer = aic->IPR; // Get pending IRQs from AIC.

	// Interrupt from PIOA
	if (irq_buffer & 1 << PIOA_ID)
	{
		temp = pioa->ISR;         // Clear PIOA IRQ register.
		aic->ICCR = 1 << PIOA_ID; // Wipe the IRQ from the AIC.

		// START Button Pressed (previously not pressed)
		if (start_but_state == BUT_NOT_PRESSED && !(pioa->PDSR & BUT_START))
		{
			start_but_state = BUT_PRESSED;

            // Set request_service flag.
            request_service = 1;
		}
		// START Button Released (previously pressed)
		else if (start_but_state == BUT_PRESSED && (pioa->PDSR & BUT_START))
		{
			start_but_state = BUT_NOT_PRESSED;
		}

		// STOP Button Pressed (previously not pressed)
		if (stop_but_state == BUT_NOT_PRESSED && !(pioa->PDSR & BUT_STOP))
		{
			stop_but_state = BUT_PRESSED;

            // Clear request_service flag.
            request_service = 0;
		}
		// STOP Button Released (previously pressed)
		else if (stop_but_state == BUT_PRESSED && (pioa->PDSR & BUT_STOP))
		{
			stop_but_state = BUT_NOT_PRESSED;
		}
	}

	// Interrupt from TC0
	if (irq_buffer & 1 << TC0_ID)
	{
		temp = tc->Channel_0.SR; // Clear TC status register.
		aic->ICCR = 1 << TC0_ID; // Wipe the IRQ from the AIC.

		quarters++; // Count quarters of a second.

        switch (lights_state) // Change the state of the LEDs.
        {
        case S0:
            if (request_service) change_state(S1);
            break;

        case S1:
            if (quarters==40) change_state(S2);
            break;

        case S2:
            if (quarters==12) change_state(S3);
            break;

        case S3:
            if (quarters==8) change_state(S4);
            break;

        case S4:
            if (quarters==40) change_state(S5);
            break;

        case S5:
            if (!request_service) change_state(S6);
            break;

        case S6:
            if (quarters==20) change_state(S0);
            break;
        }

		Output_Refresh(); // Refresh (turn on/off, blink) LEDs.

		Timer_Start(); // Restart the timer.
	}
}

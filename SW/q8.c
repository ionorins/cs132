typedef volatile unsigned int ioreg;

#define	PIO_PER  (ioreg *) 0xfffff400	// PIO Enable Registe
#define	PIO_OER  (ioreg *) 0xfffff410	// Output Enable Register
#define	PIO_SODR (ioreg *) 0xfffff430	// Set Output Data Register
#define	PIO_CODR (ioreg *) 0xfffff434	// Clear Output Data Register
#define PMC_PCER (ioreg *) 0xFFFFFC10
#define PIO_IFER (ioreg *) 0xFFFFF420
#define PIO_PDSR (ioreg *) 0xFFFFF43C

#define DRIVE 0x00000001
#define DIR   0x00000002

#define RED_LED		0x00000004
#define AMBER_LED 0x00000008
#define GREEN_LED 0x00000010

#define DELAY 0x00080000	// Long enough to see a change in LED

#define GREEN_SWITCH (1<<20)
#define OPTO (1<<25)

#define INPUTS GREEN_SWITCH|OPTO
#define OUTPUTS DRIVE|DIR|RED_LED|AMBER_LED|GREEN_LED

#define PIO_IDENTIFIER 0x00000004

void delay(int);
int s = 1;

void turn_on(int adr) {
	*PIO_CODR = adr;
	delay(DELAY);
	*PIO_SODR = adr;
}

int main(void)
{
	*PIO_PER = OUTPUTS|INPUTS; // Enable control of I/O pin from PIO Controller
	*PIO_OER = OUTPUTS; // Enable output driver for pin
	*PIO_SODR = OUTPUTS;
	*PIO_IFER = INPUTS;
  *PMC_PCER = PIO_IDENTIFIER; // enable clock for Parallel I/O (so that it responds to inputs)
	*PIO_CODR = RED_LED;
	*PIO_SODR = GREEN_LED;

	while (1) {
		if ((*PIO_PDSR & OPTO) != OPTO) {
			if (s == 1) {
				*PIO_CODR = DIR|RED_LED;
				*PIO_SODR = GREEN_LED;
			}
			else {
				*PIO_SODR = DIR|RED_LED;
				*PIO_CODR = GREEN_LED;
			}

			s = 1 - s;
		}
			*PIO_SODR = *PIO_SODR|DRIVE|AMBER_LED;
			delay(DELAY);
			*PIO_CODR = *PIO_CODR|DRIVE|AMBER_LED;
			delay(DELAY);

	}

}

void delay(int count)
{
	register int i;
	for (i=count;i>0;i--)
       		;
}

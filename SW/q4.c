typedef volatile unsigned int ioreg;

#define	PIO_PER		(ioreg *) 0xfffff400	// PIO Enable Registe
#define	PIO_OER	  	(ioreg *) 0xfffff410	// Output Enable Register
#define	PIO_SODR  	(ioreg *) 0xfffff430	// Set Output Data Register
#define	PIO_CODR  	(ioreg *) 0xfffff434	// Clear Output Data Register

#define RED_LED		0x00000004
#define AMBER_LED 0x00000008
#define GREEN_LED 0x00000016
#define DELAY 		0x00800000	// Long enough to see a change in LED

#define OUTPUTS RED_LED|AMBER_LED|GREEN_LED

void delay(int);

int main(void)
{
	*PIO_PER = OUTPUTS; // Enable control of I/O pin from PIO Controller
	*PIO_OER = OUTPUTS; // Enable output driver for pin

	while (1) {
	      *PIO_SODR = OUTPUTS;
	      delay(DELAY);
	      *PIO_CODR = OUTPUTS;
	      delay(DELAY);
	}
}

void delay(int count)
{
	register int i;
	for (i=count;i>0;i--)
       		;
}

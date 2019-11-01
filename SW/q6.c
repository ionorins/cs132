typedef volatile unsigned int ioreg;

#define	PIO_PER  (ioreg *) 0xfffff400	// PIO Enable Registe
#define	PIO_OER  (ioreg *) 0xfffff410	// Output Enable Register
#define	PIO_SODR (ioreg *) 0xfffff430	// Set Output Data Register
#define	PIO_CODR (ioreg *) 0xfffff434	// Clear Output Data Register
#define PMC_PCER (ioreg *) 0xFFFFFC10

#define DRIVE 0x00000001
#define DIR   0x00000002

#define DELAY 0x00080000	// Long enough to see a change in LED

#define OUTPUTS DRIVE|DIR

#define PIO_IDENTIFIER 0x00000004

void delay(int);
int x;
void turn_on(int adr, int time) {
	*PIO_CODR = adr;
	delay(time);
	*PIO_SODR = adr;
	// delay(time);
}

int main(void)
{
	*PIO_PER = OUTPUTS; // Enable control of I/O pin from PIO Controller
	*PIO_OER = OUTPUTS; // Enable output driver for pin
	*PIO_SODR = OUTPUTS;
  *PMC_PCER = PIO_IDENTIFIER; // enable clock for Parallel I/O (so that it responds to inputs)

	while (1) {
		*PIO_SODR = DRIVE;
		delay(DELAY);
		*PIO_CODR = DRIVE;
		x++;
		delay(DELAY);
	}
}

void delay(int count)
{
	register int i;
	for (i=count;i>0;i--)
       		;
}

#include <msp430.h>

void delay(long int num_of_ops);
int button1();
int button2();
/*
 * main.c
 */
int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;	

  //LED
  P1DIR |= BIT4; 
  P1SEL &= ~BIT4; 
  P1OUT &= ~BIT4; 
  //S1
  P1DIR  &= ~BIT7; 
  P1REN |= BIT7; 
  P1OUT |= BIT7; 
  P1SEL &= ~BIT7;
  //S2
  P2DIR  &= ~BIT2; 
  P2REN |= BIT2; 
  P2OUT |= BIT2; 
  P2SEL &= ~BIT2; 

  _disable_interrupts(); 
  P2IE |= BIT2; 
  P2IES &= ~BIT2; 
  P2IFG &= ~BIT2; 
  _enable_interrupts();

    __no_operation(); 
}
#pragma vector = PORT2_VECTOR 
__interrupt void ISR_S2() 
{
	delay(1000);

	if (!button2())
	{
		if(button1())
		{
			P1OUT ^= BIT4; 
			delay(1000);
		}
	}
	P2IFG &= ~BIT2; 
    return;
}

int button1()
{
	return (P1IN & BIT7) ? 0 : 1;
}

int button2()
{
	return (P2IN & BIT2) ? 0 : 1;
}

void delay(long int num_of_ops)
{
	volatile long int a = 0;
	volatile long int i = 0;
	for(; i < num_of_ops; i++)
	{
		a += i;
	}
}

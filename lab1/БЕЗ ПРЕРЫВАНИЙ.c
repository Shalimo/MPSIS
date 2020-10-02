#include <msp430.h>

void delay(long int num_of_ops);
/*
 * main.c
 */

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;

    // diod
    P1DIR |= BIT4; 
    P1SEL &= ~BIT4;
    P1OUT &= ~BIT4; 
    //S1
    P1DIR  &= ~BIT7; 
    P1REN |= BIT7;
    P1OUT |= BIT7; 
    P1SEL |= BIT7; 
    //S2
    P2DIR  &= ~BIT2; 
    P2REN |= BIT2; 
    P2OUT |= BIT2; 
    P2SEL |= BIT2; 

    int previous = 1;
    int push = 0;
     while(1)
     {
    	 int button1 = (P1IN & BIT7) == 0;
    	 int button2 = (P2IN & BIT2) == 0;

    	 if(button2==1){
    	    		 push = 1;
    	    	 }
    	 if(button2==1&&button1==0){
    		 push=0;
    	 }
    	 if(button1 == 1 && button2 == 0 && push == 1 && previous == 0){
			 previous = 1;
			 P1OUT &= ~BIT4;
			 push = 0;
			 delay(1000);
    	 }
    	 if(button1 == 1 && button2 == 0 && push == 1 && previous == 1)
    	 {
    		 previous = 0;
    		 P1OUT |= BIT4;
    		 push = 0;}
    	 delay(1000);
     }

	return 0;
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

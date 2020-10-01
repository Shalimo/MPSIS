#include <msp430.h>
// volatile - zna4enie peremennoy menyaetsya izvne

void delay(long int num_of_ops);
int button1();
int button2();
/*
 * main.c
 */
int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;	// off timer of real time

  //LED
  P1DIR |= BIT4; // установка направления ножки P1.4 на выход
  P1SEL &= ~BIT4; // установка использования ножки P1.4 в качестве порта ввода-вывода
  P1OUT &= ~BIT4; // установка значения 0 на вывод ножки P1.4
  //S1
  P1DIR  &= ~BIT7; // установка направления ножки P1.7 на вход
  P1REN |= BIT7; // включение подтягивающего резистора ножки P1.7
  P1OUT |= BIT7; // установка значения 0 на вывод ножки P1.7
  P1SEL &= ~BIT7; // установка использования ножки P1.7 в качестве порта ввода-вывода
  //S2
  P2DIR  &= ~BIT2; // установка направления ножки P2.2 на вход
  P2REN |= BIT2; // включение подтягивающего резистора ножки P2.2
  P2OUT |= BIT2; // установка значения 0 на вывод ножки P2.2
  P2SEL &= ~BIT2; // установка использования ножки P2.2 в качестве порта ввода-вывода

  _disable_interrupts(); //запрет на запрос на прерывание
  P2IE |= BIT2; // разрешение прерывания по линии ввода-вывода P2.2
  P2IES &= ~BIT2; // выбор генерации запроса на прерывание по фронту по линии ввода-вывода P2.2
  P2IFG &= ~BIT2; // установка флага запроса на прерывание по линии ввода-вывода P2.2 в 0
  _enable_interrupts(); // разрешение на запрос на прерывание

    __no_operation(); //бесконечный цикл
}
#pragma vector = PORT2_VECTOR //директива для замены вектора прерываний
__interrupt void ISR_S2() //обработчик прерываний для S2
{
	delay(1000);

	if (!button2())
	{
		if(button1())
		{
			P1OUT ^= BIT4; // записываем в бит что отвечает за диод, в регистре out значение тем самым инвертируем прошлое состояние
			delay(1000);
		}
	}
	P2IFG &= ~BIT2; //убираем флаг прерываний для S2
    return;
}

int button1()
{
	return (P1IN & BIT7) ? 0 : 1;
}
// 0 - off / 1 - on
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

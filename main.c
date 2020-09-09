#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	DDRA &=~(1<<PINA1);	//making pina1 as input 
	DDRC=0b00001111;//make the leds and buzzer pins output
	PORTC=0b00000000;
	ADCSRA=0b10000111;//making division factor 128 and enable the adc
	ADMUX=0b11000000;//making the internal 2.56 voltage reference and taking the input from adc1
	while (1)
	{
		ADCSRA |= (1<<ADSC);//start converting
		int temprature=ADCW/4;//every 1 celsius =10mv and our reference is 2.56v and it's 10 bit so (10mv/2.56v)*1023=4 for every degree
		//ADCW=ADCL+ADCH in 16 bit word
		if (temprature<20)
		{
			PORTC&=~(1<<PINC1);//turn off led yellow
			PORTC&=~(1<<PINC0);//turn off led red
			PORTC|=(1<<PINC2);//turn on led green
		    PORTC&=~(1<<PINC3);	//turn off buzzer
		}
		else if(temprature>=20&&temprature<40)
		{	PORTC&=~(1<<PINC0);//turn off led red
			PORTC&=~(1<<PINC2);//turn off led green
			PORTC|=(1<<PINC1);//turn on led yellow
			PORTC&=~(1<<PINC3);//turn off buzzer
		}
		else 
		{
			PORTC&=~(1<<PINC1);//turn off led yellow
			PORTC&=~(1<<PINC2);//turn off led green
			PORTC|=(1<<PINC0);//turn on led red
			PORTC|=(1<<PINC3);//turn on buzzer
		}
	}
}


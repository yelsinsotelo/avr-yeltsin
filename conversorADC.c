#define  F_CPU 20000000
#include <avr/io.h>
#include <stdio.h>
#include "avrpin.h"
#include <util/delay.h>

void initADC () {
	//PRR.PRADC se encuentra en cero por defecto.
    // AREF = AVcc
    ADMUX = (1<<REFS0);
    
    // ADC Enable and prescaler of 128
    // 16000000/128 = 125000
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	ADCSRB &= ~((1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0));
	//Para que se tenga una mejor resolución debemos tener el reloj del ADC entre 50k y 200k por tanto.
	//20000000/128=156.25 KHz por tanto con esto se cumple la condición.
		
}

uint16_t readADC (uint8_t entrada) {
	uint16_t adc_result;
	 ADMUX=(ADMUX & 0b11110000)|(entrada & 0b00001111);
	 ADCSRA|=(1<<ADSC); 
	 while(ADCSRA & (1<<ADSC));
	 // El registro ADC es un registro de doble buffer de 16 bits. Cuando se lee el bit ADCL la actualización del registro se bloquea hasta que 
	 // el registro ADCH se lea, por tanto deben leerse ambos para que se pueda dar lecturas suscesivas.
	 adc_result=ADCL;
	 adc_result += ( ADCH << 8 );
	 return adc_result;
}

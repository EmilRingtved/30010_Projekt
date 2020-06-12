#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "charset.h"
#include <string.h>
#include <stdio.h>

int8_t *cntr;
int8_t k;
int8_t flag = 0;
void setupTimer(){

        // Configuring timer 2:

        RCC->APB1ENR |= RCC_APB1Periph_TIM2;            // Enable clock line to timer 2;

        TIM2->ARR = 63999;                          // Edit these two values to modify the interrupt generation speed.
        TIM2->PSC = 9;                              // See documentation for the formula to calculate the 'interrupt' speed.

                                                        // ARR = 63999, PSC = 9 == 1/100 sec.
        TIM2->DIER |= 0x0001;

        NVIC_SetPriority(TIM2_IRQn, 0x00);              // Set interrupt priority.. Priority: 4 bit. Lower = higher.
        NVIC_EnableIRQ(TIM2_IRQn);                      // Enable interrupt

        TIM2->CR1 |= 0x001;                             // Enable Counter

        // Refer to function: void TIM2_IRQHandler(void), for the upon interrupt, executed function.
}


void TIM2_IRQHandler(void) {

    cntr++;
    uint8_t buffer[512] = {0};
    char str[5] = {0x4C, 0x41, 0x52, 0x53};

    if(cntr == 5){
    lcd_scroll(str,buffer);
    cntr = 0;

    }


    TIM2->SR &= ~0x0001;                                    // Clear interrupt bit
}

void lcd_scroll(char str[],uint8_t *buffer){
	if(k >= 100) flag = 1;
	else if (k <= 0)flag = 0;

	if(0 < k < 108 && flag == 0){
		memset(buffer,0x00,512); // Sets each element of the buffer to 0x00
		lcd_write_string(buffer, str, k, 1);
		lcd_push_buffer(buffer);
		k++;
		printf("%d",k);

		}
	else if(flag == 1){
		memset(buffer,0x00,512); // Sets each element of the buffer to 0x00
		lcd_write_string(buffer, str, k, 1);
		lcd_push_buffer(buffer);
		k--;

		}


}
void lcd_write_string(uint8_t *buffer, char *str, uint8_t slice, uint8_t line){
    int j=0;
    while(str[j] != 0x00){
    int8_t i;
    for(i =0; i < 5; i++){
    buffer[slice + (128 * line) + i +6 * j] = character_data[str[j] - 0x20 ][i];
    }
    j++;
    }

}
int main(void)
{
	uart_init(9600);
	cntr = 0;
	k = 0;
	lcd_init(); //initialize lcd
	setupTimer();
	while(1){

	}
}

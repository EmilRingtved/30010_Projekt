#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "charset.h"
#include <string.h>
void lcd_update();
void lcd_scroll(char str[],uint8_t *buffer){

	for(int i = 1; i < 100 ;i++){
		memset(buffer,0x00,512); // Sets each element of the buffer to 0x00
		lcd_write_string(buffer, str, i, 1);
		lcd_push_buffer(buffer);
		}
		for(int i = 100; i > 1 ;i--){

			memset(buffer,0x00,512); // Sets each element of the buffer to 0x00
			lcd_write_string(buffer, str, i, 1);
			lcd_push_buffer(buffer);
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
	uint8_t buffer[512] = {0};
	uart_init(9600);
	lcd_init(); //initialize lcd
	 char str[5] = {0x4C, 0x41, 0x52, 0x53};


	while(1){
		lcd_scroll(str, buffer);
	}
}

#include<reg52.h>
#define SLEEP_TIME 30000
#define OPEN 0
#define CLOSE 1
sbit led_1 = P0^0;
sbit led_2 = P0^1;
sbit led_3 = P0^2;


void sleep(){
	int i=SLEEP_TIME;
	while(i--){;}	
}

void main(){
	while(1){
		// open light1
		led_1 = OPEN;
		sleep();
		led_1 = CLOSE;
		led_2 = OPEN;
		sleep();
		led_2 = CLOSE;
		led_3 = OPEN;
		sleep();
		led_3 = CLOSE;
	}
}
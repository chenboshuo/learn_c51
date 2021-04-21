#include<reg52.h>
#define SLEEP_TIME 30000
#define OPEN 0
#define CLOSE 1
#define ENABLE_LED_ARRAYS 14 // 01110
#define CLOSE_ALL 255




void sleep(){
	int i=SLEEP_TIME;
	while(i--){;}	
}
void blink(int t){
	unsigned int pre,i;
	for(i=0;i<t;++i){
		sleep();
		pre = P0; //backup
		P0 = CLOSE_ALL;
		sleep();
		P0 = pre;
	}
}

void main(){
    unsigned int mask=1;
	int direct=1;
	P1 = ENABLE_LED_ARRAYS;  // set addr
	while(1){
	    if((mask & CLOSE_ALL) == 0){
		   mask = (direct == 1) ? 128 : 1;
		   direct *= -1;
		}
		P0 = CLOSE_ALL & mask;
		P0 = ~P0;
		blink(3);
		if(direct == 1){
	        mask <<= 1;
		}else{
			mask >>= 1;
		}   
	}
}
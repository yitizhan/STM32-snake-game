//#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stm32f30x.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_nunchuk.h>
#include<stdint.h>
nunchuk_t n;

///////////////////////////////////////////////
uint8_t previous=0; // 1:right, 2:left, 3:up, 4:down   				
uint8_t size = 8;

#define SNAKE_Max_length 320

struct foods{
    uint8_t x;
    uint8_t y;
    uint8_t yes;
}food;

struct snakes{
    uint8_t x[SNAKE_Max_length];
    uint8_t y[SNAKE_Max_length];
    uint8_t length;
    uint8_t life;
    uint8_t score;
    uint8_t level;
}snake;

void draw_snake (uint8_t x,uint8_t y){
	f3d_lcd_drawString(x,y,"*",WHITE,BLACK);
}
void erase_snake (uint8_t x,uint8_t y){
	f3d_lcd_drawString(x,y,"*",BLACK,BLACK);
}

void draw_food (uint8_t x,uint8_t y){
	f3d_lcd_drawString(x,y,"*",RED,BLACK);
}

void init_snake(void){
	uint8_t i;
	f3d_lcd_fillScreen(BLACK);	
    
  	// initialize data for snake
   	snake.length=3;	    			
   	snake.life=1; // 1:alive, 0:dead	    			
   	snake.score=0;
	snake.level=0;
   	food.yes=1;
   	previous = 1; // default moving direction
   	 
   	for(i=0;i<snake.length;i++){
		snake.x[i]=i*size+24;
	   	snake.y[i]=48;
   	}
   	for(i=0;i<snake.length;i++){	
   	     	draw_snake(snake.x[i],snake.y[i]);
   	}
}



void dead(void){
    f3d_lcd_fillScreen(BLACK);
    f3d_lcd_drawString(32,100,"Game Over",WHITE,BLACK);
    srand(pressed());
    init_snake();
}


void pass(void){
    f3d_lcd_fillScreen(BLACK);
    f3d_lcd_drawString(32,100,"WIN !",WHITE,BLACK);
    srand(pressed());
    init_snake();
}






/*******************************************************************************************/
void run_snake(void){
	
	char label[20]="Score: ";
	char d[2];
  	snprintf(d,3,"%.2d",snake.score);
  	strcat(label,d);
  	snprintf(d,3,"%.2d",snake.level);
  	strcat(label," Level: ");
  	strcat(label,d);
  	f3d_lcd_drawString(10,150,label,WHITE,BLACK);
	f3d_nunchuk_read(&n);
	//unsigned char *Key_Value
	//unsigned char *Key_V_temp
	uint8_t i=0;


///////////////////////////////////////////////////////////////////////////////

	if(n.jx>150 && previous!=2){
		previous=1;
	}

	if(n.jx<60 && previous!=1){
		previous=2;
	}

	if(n.jy>150 && previous!=4){
		previous=3;
	}

	if(n.jy<60 && previous!=3){
		previous=4;
	}


	if(previous==1){ //right
		erase_snake(snake.x[0],snake.y[0]); 	       
        	for(i=0;i<snake.length-1;i++){ 
        	    snake.x[i]=snake.x[i+1];
        	    snake.y[i]=snake.y[i+1];
        	}
        
        	snake.x[snake.length-1]=snake.x[snake.length-2]+size;
        	snake.y[snake.length-1]=snake.y[snake.length-2]+0; 
        	
        	for(i=0;i<snake.length;i++){ 	           
        	    draw_snake(snake.x[i],snake.y[i]);
        	}		
	}

	if(previous==2){ //left
		erase_snake(snake.x[0],snake.y[0]); 	       
        	for(i=0;i<snake.length-1;i++){ 
        	    snake.x[i]=snake.x[i+1];
        	    snake.y[i]=snake.y[i+1];
        	}
        
        	snake.x[snake.length-1]=snake.x[snake.length-2]-size;
        	snake.y[snake.length-1]=snake.y[snake.length-2]+0; 
        	
        	for(i=0;i<snake.length;i++){ 	           
        	    draw_snake(snake.x[i],snake.y[i]);
        	}		
	}

	if(previous==3){ //up
		erase_snake(snake.x[0],snake.y[0]); 	       
        	for(i=0;i<snake.length-1;i++){ 
        	    snake.x[i]=snake.x[i+1];
        	    snake.y[i]=snake.y[i+1];
        	}
        
        	snake.x[snake.length-1]=snake.x[snake.length-2]+0;
        	snake.y[snake.length-1]=snake.y[snake.length-2]-size; 
        	
        	for(i=0;i<snake.length;i++){ 	           
        	    draw_snake(snake.x[i],snake.y[i]);
        	}		
	}

	if(previous==4){  //down
		erase_snake(snake.x[0],snake.y[0]); 	       
        	for(i=0;i<snake.length-1;i++){ 
        	    snake.x[i]=snake.x[i+1];
        	    snake.y[i]=snake.y[i+1];
        	}
        
        	snake.x[snake.length-1]=snake.x[snake.length-2]+0;
        	snake.y[snake.length-1]=snake.y[snake.length-2]+size; 
        	
        	for(i=0;i<snake.length;i++){ 	           
        	    draw_snake(snake.x[i],snake.y[i]);
        	}		
	}

/*
	//change the direction of snake depends on joystick
	if(n.jx>180 && previous!=2 ){	
		erase_snake(snake.x[0],snake.y[0]); 	       
        	for(i=0;i<snake.length-1;i++){ 
        	    snake.x[i]=snake.x[i+1];
        	    snake.y[i]=snake.y[i+1];
        	}
        
        	snake.x[snake.length-1]=snake.x[snake.length-2]+size;
        	snake.y[snake.length-1]=snake.y[snake.length-2]+0; 
        	
        	for(i=0;i<snake.length;i++){ 	           
        	    draw_snake(snake.x[i],snake.y[i]);
        	}
        	previous=1;
    	}
 
	if(n.jx<60 && previous!=1){        
        	erase_snake(snake.x[0],snake.y[0]); 		//erase the tail   
        
        	for(i=0;i<snake.length-1;i++){			//moving whole body forward
        	    snake.x[i]=snake.x[i+1];
        	    snake.y[i]=snake.y[i+1];
        	}
        	
        	snake.x[snake.length-1]=snake.x[snake.length-2]-size;
        	snake.y[snake.length-1]=snake.y[snake.length-2]+0;  //move to expect direction
        	
        	for(i=0;i<snake.length;i++){   			//draw new snake      
        	    draw_snake(snake.x[i],snake.y[i]);
        	}
        	previous=2;
    	}

	if(n.jy>180 && previous!=4){
        	erase_snake(snake.x[0],snake.y[0]); 		
        
        	for(i=0;i<snake.length-1;i++){   
        	    snake.x[i]=snake.x[i+1];
        	    snake.y[i]=snake.y[i+1];
        	}
        	
        	snake.x[snake.length-1]=snake.x[snake.length-2]+0;
        	snake.y[snake.length-1]=snake.y[snake.length-2]-size; 
        	
        	for(i=0;i<snake.length;i++){          
        	    draw_snake(snake.x[i],snake.y[i]);
        	}
        	previous=3;
    	}

	if(n.jy<60 && previous!=3){ 
	       	erase_snake(snake.x[0],snake.y[0]); 		 
        	
        	for(i=0;i<snake.length-1;i++){ 
        	    snake.x[i]=snake.x[i+1];
        	    snake.y[i]=snake.y[i+1];
        	}
        	
        	snake.x[snake.length-1]=snake.x[snake.length-2]+0;
        	snake.y[snake.length-1]=snake.y[snake.length-2]+size; 
        	
        	for(i=0;i<snake.length;i++){ 		           
        	    draw_snake(snake.x[i],snake.y[i]);
        	}
        	previous=4;
    	}	
*/
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 	//die or not  v
	if(snake.x[snake.length-1]<=0||snake.x[snake.length-1]>=128||snake.y[snake.length-1]<=0||snake.y[snake.length-1]>=160){//out of stage
		snake.life=0;
  	}
	
	for(i=0;i<snake.length-2;i++){               //eat itself
        	if(snake.x[i]==snake.x[snake.length-1] && snake.y[i]==snake.y[snake.length-1]){
 	        	snake.life=0;
        	}
    	}

  	if(snake.life==0){
 	        dead();
    	}

   	//hit the max?  v
    	if(snake.length==SNAKE_Max_length){
	        pass();
	}


   	// eat a food? 
	if(snake.x[snake.length-1]==food.x && snake.y[snake.length-1]==food.y){
	        erase_snake(food.x,food.y); 	//delete the food	
        	snake.length++;
		snake.score++;
		if(snake.score%5==0){  // level up every 10 foods
			snake.level++; 
		}
        	snake.x[snake.length-1]=food.x;
        	snake.y[snake.length-1]=food.y;
        	food.yes=1; 
    	}

     	// place a new food              
    	if(food.yes==0){ //draw the new food
  		draw_food(food.x,food.y);
    	}
											   
    	if(food.yes==1){ //create a new food
	        while(1){
 	        	food.x=rand()%16*size; 	//get a random number in [0,128]    			
            		food.y=rand()%16*size;     //get a random number in [0,160]
            		for(i=0;i<snake.length;i++){	//food overlap with snake?
      		        	if((food.x==snake.x[i])&&(food.x==snake.y[i])){
                			break;
				}
			}
			if(i==snake.length){
		                food.yes=0;
                		break;		//create valid (x,y) for new food							
            		}
        	}
    	}

	//modified the speed of the game 
    	//delay(100-snake.level*10);    
	delay(10);

}



int pressed() {
  uint8_t count=0;
  while(1) {
    count++;
    while(!n.c && !n.z) f3d_nunchuk_read(&n);
    while(n.c || n.z) f3d_nunchuk_read(&n);;
    return count;
  }
}


int main(void){
	f3d_lcd_init();
    	f3d_i2c1_init();
	delay(10);			
    	f3d_nunchuk_init;

	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	f3d_lcd_fillScreen(BLACK);
  	f3d_lcd_drawString(45,50,"SNAKE",WHITE,BLACK);
  	f3d_lcd_drawString(10,65,"Press C/Z to Start",WHITE,BLACK);

  	srand(pressed());

	f3d_lcd_drawString(45,50,"     ",WHITE,BLACK);
  	f3d_lcd_drawString(10,65,"                  ",WHITE,BLACK);
	init_snake();
	//f3d_nunchuk_read(&n);
	while(1) {
		run_snake();
		delay(0);
	} 
}


#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
  /* Infinite loop */
  /* Use GDB to find out why we're here */
  while (1);
}
#endif

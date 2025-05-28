#include "headers/drawings.h"
#include "headers/timerISR.h"
#include <avr/wdt.h>

using namespace std;


#define NUM_TASKS 1

//Task struct for concurrent synchSMs implmentations
typedef struct _task{
	signed 	 char state; 		//Task's current state
	unsigned long period; 		//Task period
	unsigned long elapsedTime; 	//Time elapsed since last task tick
	int (*TickFct)(int); 		//Task tick function
} task;

task tasks[NUM_TASKS];

//Task Periods
const unsigned long GCD_PERIOD = 100;//TODO:Set the GCD Period
const unsigned long alienPeriod = 100;
//global variables
unsigned char shipSpeed = 5;
Alien aliens[8][9]; // Corrected declaration assuming Alien is a class



//Task state functions
enum Ship_States {Ship_Start, Ship_Move};
int ShipTick(int state);


enum Alien_States {Alien_Start, Alien_Display, Alien_Move};
int AlienTick(int state);
void TimerISR() {
	for ( unsigned int i = 0; i < NUM_TASKS; i++ ) {                   // Iterate through each task in the task array
		if ( tasks[i].elapsedTime == tasks[i].period ) {           // Check if the task is ready to tick
			tasks[i].state = tasks[i].TickFct(tasks[i].state); // Tick and set the next state for this task
			tasks[i].elapsedTime = 0;                          // Reset the elapsed time for the next tick
		}
		tasks[i].elapsedTime += GCD_PERIOD;                        // Increment the elapsed time by GCD_PERIOD
	}
}

int main() {
  MCUSR = 0;           // Clear the watchdog reset flag
  wdt_disable();
  serial_init(9494);       
  DDRB |= (1 << RST_PIN) | // PB0 as Output (RST)
          (1 << A0_PIN)  | // PB1 as Output (DC)
          (1 << CS_PIN)  | // PB2 as Output (CS/SS)
          (1 << PIN_MOSI)       | // PB3 as Output (MOSI)
          (1 << PIN_SCK);  

  PORTB |= (1 << RST_PIN) | // RST to HIGH
           (1 << A0_PIN)  | // DC to HIGH (idle data mode)
           (1 << CS_PIN);

  
  SPI_INIT();
  ST7735_init();

  fillRect(0,0,150,150, COLOR_BLACK);
  
  for(unsigned i = 9; i < 122; i+=13){
        aliens[0][int((i-9)/13)].setX(i);
        aliens[0][int((i-9)/13)].setY(10);
    }

  //Ship myShip = Ship();
  //Bullet bullet = Bullet(60, 100, 1);


  tasks[0].period = alienPeriod;
  tasks[0].state = Alien_Start;
  tasks[0].elapsedTime = tasks[0].period;
  tasks[0].TickFct = &AlienTick;

  
  
  
  

  TimerSet(100);
  TimerOn();
  
  

  while(1) {
    //drawShip(myShip);
    //drawBullet(bullet);
  }
}

int AlienTick(int state) {
  static unsigned char lenAliens;
  static unsigned long count;

  switch(state) {
    
    case(Alien_Start):
      state = Alien_Display;
      count = 0;
      lenAliens = 1;
      break;
    case(Alien_Display):
      serial_println(count);
      if(count<=20){
        state = Alien_Display;
      }
      else if(count > 20){
        state = Alien_Move;
      }
      break;
    case(Alien_Move):
      state = Alien_Display;
      count = 0;
      break;
  }

  switch(state) {
    case(Alien_Display):
      count ++;
      for(unsigned i = 0; i < lenAliens; i ++) {
        for(unsigned j = 0; j < 9; j++){
          drawAlien(aliens[i][j]);
        }
        
      }
      break;
    case(Alien_Move):
      for(unsigned i = 0; i < lenAliens; i++) {
        for(unsigned j = 0; j < 9; j++){
          aliens[i][j].setY(aliens[i][j].getY() + 15);
        }
      }
      for(unsigned i = 9; i < 122; i+=13){
          aliens[lenAliens][int((i-9)/13)].setX(i);
          aliens[lenAliens][int((i-9)/13)].setY(10);
      }
      lenAliens++;
      break;
    }

    return state;

}
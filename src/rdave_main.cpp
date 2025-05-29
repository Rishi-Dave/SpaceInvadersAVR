#include "headers/drawings.h"
#include "headers/timerISR.h"
#include <avr/wdt.h>
#include "headers/periph.h"

using namespace std;


#define NUM_TASKS 5

//Task struct for concurrent synchSMs implmentations
typedef struct _task{
	signed 	 char state; 		//Task's current state
	unsigned long period; 		//Task period
	unsigned long elapsedTime; 	//Time elapsed since last task tick
	int (*TickFct)(int); 		//Task tick function
} task;

task tasks[NUM_TASKS];

//Task Periods
const unsigned long GCD_PERIOD = 50;//TODO:Set the GCD Period
const unsigned long alienPeriod = 50;
const unsigned long readPeriod = 50;
const unsigned long shipPeriod = 50;
const unsigned long shootPeriod = 50;
const unsigned long bulletPeriod = 50;

//global variables
unsigned char shipSpeed = 5;
Alien aliens[7][9]; // Corrected declaration assuming Alien is a class
Bullet* bullets[10] = {nullptr};
unsigned int lenBullets = 0;
unsigned long xVal;
unsigned long yVal;
unsigned char curDirection;
bool endgame = false;
Ship myShip = Ship();


//Task state functions
enum Ship_States {Ship_Start, Ship_Move, Ship_Stop};
int ShipTick(int state);


enum Alien_States {Alien_Start, Alien_Display, Alien_Move, Alien_End, Alien_Win};
int AlienTick(int state);

enum Read_States {Joy_Start, ReadJoyStick};
int Read(int state);

enum Shoot_States {Shoot_Start, Reload, Fire, Shoot_Stop};
int Shoot(int state);

enum Bullet_States {Bullet_Start, No_Bullets, Display_Bullets};
int BulletTick(int state);

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

  DDRD = 0xFF;
  PORTD = 0x00;

  
  

  SPI_INIT();
  ST7735_init();
  ADC_init();
  initializeFontLookup();

  // OCR1A =  /* set your value here */ ;
    //sets duty cycle to 50% since TOP is always 256

  TCCR0A |= (1 << COM0A1);// use Channel A
  TCCR0A |= (1 << WGM01) | (1 << WGM00);// set fast PWM Mode
  TCCR0B = (TCCR0B & 0xF8) | 0x02;
  OCR0A = 128;

  fillRect(0,0,150,150, COLOR_BLACK);
  drawShip(myShip);
  for(unsigned j = 0; j < 4; j ++) {
    for(unsigned i = 9; i < 122; i+=13){
        aliens[j][int((i-9)/13)].setX(i);
        aliens[j][int((i-9)/13)].setY((j)*15 + 10);
    }
  }


  tasks[0].period = alienPeriod;
  tasks[0].state = Alien_Start;
  tasks[0].elapsedTime = tasks[0].period;
  tasks[0].TickFct = &AlienTick;

  tasks[1].period = readPeriod;
  tasks[1].state = Joy_Start;
  tasks[1].elapsedTime = tasks[1].period;
  tasks[1].TickFct = &Read;

  tasks[2].period = shipPeriod;
  tasks[2].state = Ship_Start;
  tasks[2].elapsedTime = tasks[2].period;
  tasks[2].TickFct = &ShipTick;


  tasks[3].period = shootPeriod;
  tasks[3].state = Shoot_Start;
  tasks[3].elapsedTime = tasks[3].period;
  tasks[3].TickFct = &Shoot;


  tasks[4].period = bulletPeriod;
  tasks[4].state = Bullet_Start;
  tasks[4].elapsedTime = tasks[4].period;
  tasks[4].TickFct = &BulletTick;
  
  
  
  

  TimerSet(GCD_PERIOD);
  TimerOn();
  
  

  while(1) {
    //drawShip(myShip);
    //drawBullet(bullet);
  }
}

int AlienTick(int state) {
  static unsigned long count;
  static unsigned long waveLen = 4;
  bool allAliensDestroyed;
  switch(state) {
    
    case(Alien_Start):
      state = Alien_Display;
      count = 0;
      break;
    case(Alien_Display):
      if(count<=50){
        state = Alien_Display;
      }
      else if(count > 50){
        state = Alien_Move;
      }
      break;
    case(Alien_Move):
      state = Alien_Display;
      count = 0;
      break;

    case(Alien_End):
      state = Alien_End;
      break;
    case(Alien_Win):
      state = Alien_Win;
      break;
  }

  switch(state) {
    case(Alien_Display):
      count ++;
      allAliensDestroyed = true;
      for(unsigned i = 0; i < waveLen; i ++) {
        for(unsigned j = 0; j < 9; j++){
          if(aliens[i][j].getState() == 1){
              continue;
          }
          else if(aliens[i][j].getState() == 0) {
            drawAlien(aliens[i][j]);
            allAliensDestroyed = false;
          }
          for(unsigned int k = 0; k < lenBullets; k++){
            if(aliens[i][j].isHit(*bullets[k])){
              aliens[i][j].setState(1);
              drawAlien(aliens[i][j]);
              delete bullets[k];
              bullets[k] = nullptr;
              ShiftLeft(bullets, k, lenBullets);
              lenBullets--;
              break;
            }
          }
          
        }
      }

      if(allAliensDestroyed) {
        state = Alien_Win;
        fillRect(0,0,150,150, COLOR_BLACK);
        endgame = true;
      }
      break;

    case(Alien_Move):
      fillRect(0,0,150,90, COLOR_BLACK);
      for(unsigned i = 0; i < waveLen; i++) {
        for(unsigned j = 0; j < 9; j++){
          if(aliens[i][j].getState() == 0 && aliens[i][j].getY() >90){
            state = Alien_End;
            fillRect(0,0,150,150, COLOR_BLACK);
            
            endgame = true;
            break;
          }
          else if(aliens[i][j].getState() == 0) {
            aliens[i][j].setY(aliens[i][j].getY() + 15);
            drawAlien(aliens[i][j]);
          }
        }
      }
      break;
      case(Alien_End):
        gameOver();
        break;

      case(Alien_Win):
        gameWin();
        break;

    }

    return state;

}

int Read(int state) {
  switch(state){
    case(Joy_Start):
      state = ReadJoyStick;
      break;
    case(ReadJoyStick):
      state = ReadJoyStick;
      break;
    default:
      state = Joy_Start;
      break;
  }
  switch(state) {
    case(ReadJoyStick):
      xVal = ADC_read(0);
      yVal = ADC_read(1);
      curDirection = direction(xVal, yVal);
      break;
    default:
      break;
  } 
  return state;
}

int ShipTick(int state) {
  switch(state){
    case(Ship_Start):
      state = Ship_Move;
      break;
    case(Ship_Move):
      if(endgame) {
        fillRect(myShip.getX(), myShip.getY(), SHIP_WIDTH+2, SHIP_HEIGHT+2, COLOR_BLACK);
        state = Ship_Stop;
      }
      else {
        state = Ship_Move;
      }
      break;
    case(Ship_Stop):
      state = Ship_Stop;
      break;
    default:
      state = Ship_Start;
      break;
  }

  switch(state){
    case(Ship_Move):
      
      if(curDirection == 1){
        fillRect(myShip.getX(), myShip.getY(), SHIP_WIDTH+2, SHIP_HEIGHT+2, COLOR_BLACK);
        myShip.moveLeft();
        drawShip(myShip);
      }
      else if(curDirection == 2){
        fillRect(myShip.getX(), myShip.getY(), SHIP_WIDTH+2, SHIP_HEIGHT+2, COLOR_BLACK);
        myShip.moveRight();
        drawShip(myShip);
      }
    case(Ship_Stop):
      break;
    default:
      break;
  }
  return state;
}

int Shoot(int state) {
  static unsigned char counter;
  switch(state) {
     case(Shoot_Start):
      state = Reload;
      counter = 0;
      break;
    case(Reload):
      if(endgame) {
        state = Shoot_Stop;
      }
      else if(counter > 3) {
        state = Fire;
      }
      else {
        state = Reload;
      }
      break;
    case(Fire):
      state = Reload;
      counter = 0;
      break;
    case(Shoot_Stop):
      state = Shoot_Stop;
      break;
  }

  switch(state) {
    case(Reload):
      OCR0A = 255;
      counter++;
      break;
    case(Fire):
      bullets[lenBullets] = new Bullet(myShip.getX(), myShip.getY() - 10, 0);
      lenBullets++;
      OCR0A = 128;
      break;
    case(Shoot_Stop):
      for(unsigned int i = 0; i < lenBullets; i++){
        delete bullets[i];
      }
      lenBullets = 0;
    default: 
      break;
  }
  return state;
}
int BulletTick(int state) {
  switch(state) {
    case(Bullet_Start):
      state = No_Bullets;
      break;
    case(No_Bullets):
      if(lenBullets > 0){
        state = Display_Bullets;
      }
      else if(lenBullets == 0) {
        state = No_Bullets;
      }
      break;
    case(Display_Bullets):
      if(lenBullets > 0){
        state = Display_Bullets;
      }
      else if(lenBullets == 0) {
        state = No_Bullets;
      }
      break;
  }

  switch(state){
    case(No_Bullets):
      break;
    case(Display_Bullets):
      for(unsigned int i = 0; i < lenBullets; i++){
        if(bullets[i]->getY() < 0) {
          delete bullets[i];
          bullets[i] = nullptr;
          ShiftLeft(bullets, i, lenBullets);
          lenBullets--;
          i--;
          continue;
        }
        if(bullets[i] != nullptr) {
          fillRect(bullets[i]->getX(), bullets[i]->getY(), BULLET_HEIGHT+2, BULLET_WIDTH+2, COLOR_BLACK);
          bullets[i]->moveUp();
          bullets[i]->changeState();
          drawBullet(bullets[i]);
        }
      }
      break;
    default:
      break;
  }
  return state;
}
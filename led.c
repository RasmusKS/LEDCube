#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <C:\cygwin64\home\Rasmus\avr/timer.h>
#include <C:\cygwin64\home\Rasmus\avr/Cube3.h>

unsigned long now = 0;

char map[size][size][size][3];

void clearMap(){
	for (int a = 0; a < size; a++) for (int b = 0; b < size; b++) for (int c = 0; c < size; c++) for (int d = 0; d < 3; d++) map[a][b][c][d] = 0;
}
 
void fade(unsigned int  stateTime){
	int now;
	for (int a = 0; a < 3; a++){
		for (int b = 0; b < analogStates; b++){
			for (int c = 0; c < size; c++){
				for (int d = 0; d < size; d++){
					for (int e = 0; e < size; e++){
						map[c][d][e][a] = b;
					}
				}
			}
			now = milis;
			while (milis - now < stateTime){
				analogWrite(map);
			}
		}
		for (int b = analogStates - 1; b >= 0; b--){
			for (int c = 0; c < size; c++){
				for (int d = 0; d < size; d++){
					for (int e = 0; e < size; e++){
						map[c][d][e][a] = b;
					}
				}
			}
			now = milis;
			while (milis - now < stateTime){
				analogWrite(map);
			}
		}
	}
} 

void randomFade(unsigned int stateTime, unsigned short int states){
	int now;
	clearMap();
	for (int a = 0; a < states; a++){
		int x = random() % size;
		int y = random() % size;
		int z = random() % size;
		int color = random() % 3;
		if (map[x][y][z][color]){
			for (int b = analogStates - 1; b >= 0; b--){ 
				map[x][y][z][color] = b;
				now = milis;
				while (milis - now < stateTime){
					analogWrite(map);
				}
			}
		}
		else{
			for (int b = 0; b < analogStates; b++){ 
				map[x][y][z][color] = b;
				now = milis;
				while (milis - now < stateTime){
					analogWrite(map);
				}
			}
		}
	}
 }
 
void surface(unsigned int stateTime){
	int now;
	for (int a = 0; a < 3; a++){
		for (int b = 0; b < size; b++){
			clearMap();
			for (int c = 0; c < size; c++) for (int d = 0; d < size; d++) map[b][c][d][a] = 1;
			now = milis;
			while (milis - now < stateTime){
				digitalWrite(map);
			}
		}
		for (int b = size - 2; b >= 0; b--){
			clearMap();
			for (int c = 0; c < size; c++) for (int d = 0; d < size; d++) map[b][c][d][a] = 1;
			now = milis;
			while (milis - now < stateTime){
				digitalWrite(map);
			}
		}
		for (int b = 0; b < size; b++){
			clearMap();
			for (int c = 0; c < size; c++) for (int d = 0; d < size; d++) map[c][b][d][a] = 1;
			now = milis;
			while (milis - now < stateTime){
				digitalWrite(map);
			}
		}
		for (int b = size - 2; b >= 0; b--){
			clearMap();
			for (int c = 0; c < size; c++) for (int d = 0; d < size; d++) map[c][b][d][a] = 1;
			now = milis;
			while (milis - now < stateTime){
				digitalWrite(map);
			}
		}
		for (int b = 0; b < size; b++){
			clearMap();
			for (int c = 0; c < size; c++) for (int d = 0; d < size; d++) map[c][d][b][a] = 1;
			now = milis;
			while (milis - now < stateTime){
				digitalWrite(map);
			}
		}
		for (int b = size - 2; b >= 0; b--){
			clearMap();
			for (int c = 0; c < size; c++) for (int d = 0; d < size; d++) map[c][d][b][a] = 1;
			now = milis;
			while (milis - now < stateTime){
				digitalWrite(map);
			}
		}
	}
 }

void randomRain(){
 
 }
 
void randomBlink(unsigned int stateTime, unsigned short int states){
	int now;
	clearMap();
	for (int a = 0; a < states; a++){
		int x = random() % size;
		int y = random() % size;
		int z = random() % size;
		int color = random() % 3;
		map[x][y][z][color] = !map[x][y][z][color];
		now = milis;
		while (milis - now < stateTime){
			digitalWrite(map);
		}
	}
}

int main(void){
   timer0Init();
   cubeInit();
   DDRB |= (1<<PB5);        //Set the pin as an output
 
   while (true){
      fade(50);
	  if (milis - now >= 500){
         now = milis;
         PORTB ^= (1<<PB5);
      }
   }
   return 0;
}
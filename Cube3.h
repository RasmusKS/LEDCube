#include <avr/io.h>

#define clockPin 0
#define dataPin 1
#define latchPin 2

#define setupRegister DDRB
#define outputRegister PORTB
#define setupLayerDataOutputRegister DDRD
#define layerDataOutputRegister PORTD

#define analogStates 16

#define size 3

const int pinLayout[32] = {7,8,5,16,12,3,17,25,14,22,26,24,23,6,4,21,15,13,10,11,18,0,9,20,19,2,1,27,28,29,30,31};
void writeBit(bool state){
	if (state) outputRegister |= _BV(dataPin);
	else outputRegister &= ~_BV(dataPin);
	outputRegister |= _BV(clockPin);
	outputRegister &= ~_BV(clockPin);
}
void latch(){
	outputRegister |= _BV(latchPin);
	outputRegister &= ~_BV(latchPin);
}
void digitalWrite(char map[3][3][3][3]){
	char output[32];
	for (char a = 0; a < 3; a++){
		for (char b = 0; b < 3; b++) for (char c = 0; c < 3; c++) for (char d = 0; d < 3; d++) output[b * 9 + c * 3 + d] = map[a][b][c][d];
        output[27] = a != 0;
        output[28] = a != 1;
        output[29] = a != 2;
		for (int b = 0; b < 32; b++) writeBit(output[pinLayout[b]]);
		latch();
	}
}
void analogWrite(char map[3][3][3][3]){
	char digitalMap[3][3][3][3];
	for (int light = 0; light < analogStates; light++){
		for (char a = 0; a < 3; a++){
			for (char b = 0; b < 3; b++){
				for (char c = 0; c < 3; c++){
					for (char d = 0; d < 3; d++){
						if (map[a][b][c][d] > light) digitalMap[a][b][c][d] = 1;
						else digitalMap[a][b][c][d] = 0;
					}
				}
			}
		}
		digitalWrite(digitalMap);
	}
}
void cubeInit(){
	setupRegister = (1 << clockPin) | (1 << dataPin) | (1 << latchPin);
}
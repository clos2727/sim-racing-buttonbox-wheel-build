
// beginning of code
/*arduino pro micro 16 input Button box with 8 encoders and no led
 * refer to rour pin out diagram to identify pins for bothth leonardo and pro micro
programmed to be compatible with all devices that have keyboard
compatibility
this sketch was created/altered and designed
by Carlos Reyes
with help from the arduino community and libraries
on august 2016
youtube channel "game on"
for the purpose of DIY project on youtube channel
metadata is still in progress so search
2727clos, carlos reyes, clos2727, clos reyes, or game on
email clos2727@yahoo.com */

//
//version 1.0 converted sketch from button box build
// v1.10 removed all unecessary info an commands
// v1.20 removed 25 input keyboard press
// v1.30 added 5 encoders total
// v1.50 added 16 buttons
//v 1.70  removed all led lights.
// v2.0  finalized
//
/* note
* if using leonardo be sure to change pin numbers as pin numbers on pro micro differ.
*/
#include <Keypad.h>
#include <Keyboard.h>
#define ENABLE_PULLUPS
#define NUMROTARIES 5
#define NUMBUTTONS 16
#define NUMROWS 4
#define NUMCOLS 4
//define the symbols on the buttons of the keypads
char buttons[NUMROWS][NUMCOLS] = {
   {'c','d','e','f'},  // 10
   {'a','j','k','l'}, // 14
   {'b','n','o','p'}, // 15
   {'g','h','i','m'}, //16
 // row pins
//   18 19  20  21
};
struct rotariesdef {
 byte pin1;
 byte pin2;
 int ccwchar;
 int cwchar;
 volatile unsigned char state;
};
 //{encoder pins,characters press
rotariesdef rotaries[NUMROTARIES] {
 {0,1,'u','v',}, // encoder connected to pin 0 and 1 middle pin is
 {2,3,'w','x',},// encoder connected to pin 2 and 3 middle pin is
 {4,5,'y','z',},
 {6,7,'s','t',},
 {8,9,'1','2',},

 };

#define DIR_CCW 0x10
#define DIR_CW 0x20
#define R_START 0x0
#define R_CW_FINAL 0x1
#define R_CW_BEGIN 0x2
#define R_CW_NEXT 0x3
#define R_CCW_BEGIN 0x4
#define R_CCW_FINAL 0x5
#define R_CCW_NEXT 0x6

unsigned long loopCount;
unsigned long startTime;
String msg;
const unsigned char ttable[7][4] = {
 // R_START
 {R_START, R_CW_BEGIN, R_CCW_BEGIN, R_START},
 // R_CW_FINAL
 {R_CW_NEXT, R_START, R_CW_FINAL, R_START | DIR_CW},
 // R_CW_BEGIN
 {R_CW_NEXT, R_CW_BEGIN, R_START, R_START},
 // R_CW_NEXT
 {R_CW_NEXT, R_CW_BEGIN, R_CW_FINAL, R_START},
 // R_CCW_BEGIN
 {R_CCW_NEXT, R_START, R_CCW_BEGIN, R_START},
 // R_CCW_FINAL
 {R_CCW_NEXT, R_CCW_FINAL, R_START, R_START | DIR_CCW},
 // R_CCW_NEXT
 {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START},
};
byte rowPins[NUMROWS] = {14,15,}; //connect to the row pinouts of thekeypad
byte colPins[NUMCOLS] = {18,19,20,21,}; //connect to the column pinouts ofthe keypad
//initialize an instance of class NewKeypad
Keypad buttbx = Keypad( makeKeymap(buttons), rowPins, colPins, NUMROWS, NUMCOLS);
void setup() {

  Keyboard.begin();
 rotary_init();
}
void loop() {
 CheckAllEncoders();
 CheckAllButtons();
}
void CheckAllButtons(void) {
 char key = buttbx.getKey();
 if (key == 'a') {
 Keyboard.write(key);
 delay(150);
 Keyboard.release(key);
 }
 if (key == 'b') {
 Keyboard.write(key);
 delay(150);
 Keyboard.release(key);
 }
 
 if (key == 'j') {
 Keyboard.write(key);
 delay(150);
 Keyboard.release(key);
 }
 if (key == 'k') {
 Keyboard.write(key);
 delay(150);
 Keyboard.release(key);
 }
 if (key == 'l') {
 Keyboard.write(key);
 delay(150);
 Keyboard.release(key);
 }
 if (key == 'n') {
 Keyboard.write(key);
 delay(150);
 Keyboard.release(key);
 }
 if (key == 'o') {
 Keyboard.write(key);
 delay(150);
 Keyboard.release(key);
 }
 if (key == 'p') {
 Keyboard.write(key);
 delay(150);
 Keyboard.release(key);
 }
 if (key == 'c') {
 Keyboard.write(key);
 delay(150);
 Keyboard.release(key);
 }
 if (key == 'd') {
 Keyboard.write(key);
 delay(150);
 Keyboard.release(key);
 }
 if (key == 'e') {
 Keyboard.write(key);
 delay(150);
 Keyboard.release(key);
 }
 if (key == 'f') {
 Keyboard.write(key);
 delay(150);
 Keyboard.release(key);
 }
 if (key == 'g') {
 Keyboard.write(key);
 delay(150);
 Keyboard.release(key);
 }
 if (key == 'h') {
 Keyboard.write(key);
 delay(150);
 Keyboard.release(key);
 }
 if (key == 'i') {
 Keyboard.write(key);
 delay(150);
 Keyboard.release(key);
 }
 if (key == 'm') {
 Keyboard.write(key);
 delay(150);
 Keyboard.release(key);
 }

 }
/* Call this once in setup(). */
void rotary_init() {
 for (int i=0;i<NUMROTARIES;i++) {
 pinMode(rotaries[i].pin1, INPUT);
 pinMode(rotaries[i].pin2, INPUT);
 #ifdef ENABLE_PULLUPS
 digitalWrite(rotaries[i].pin1, HIGH);
 digitalWrite(rotaries[i].pin2, HIGH);
 #endif
 }
}
/* Read input pins and process for events. Call this either from a
* loop or an interrupt (eg pin change or timer).
*
* Returns 0 on no event, otherwise 0x80 or 0x40 depending on the
direction.
*/
unsigned char rotary_process(int _i) {
 unsigned char pinstate = (digitalRead(rotaries[_i].pin2) << 1) |
digitalRead(rotaries[_i].pin1);
 rotaries[_i].state = ttable[rotaries[_i].state & 0xf][pinstate];
 return (rotaries[_i].state & 0x30);
}
void CheckAllEncoders(void) {
 for (int i=0;i<NUMROTARIES;i++) {
 unsigned char result = rotary_process(i);
 if (result) {
 Keyboard.write(result == DIR_CCW ? rotaries[i].ccwchar :
rotaries[i].cwchar );
 /*detects array characters assigned to a specific encoders and
blinks led
 // ccw = counter clockwise
 //cw =clock
 // (rotaries[i].ccwchar being used below in the if statement,
 //will call all characters in ccwchar scope.*/
if(rotaries[i].ccwchar == 'u'){ /* blink led from any rotation/*/
 delay(50);
 delay(50);
 }
 if(rotaries[i].ccwchar == 'w'){
 delay(50);
 delay(50);
 }
 if(rotaries[i].ccwchar == 'y'){ /* blink led from any rotation/*/
 delay(50);
 delay(50);
 }
 if(rotaries[i].ccwchar == 's'){ /* blink led from any rotation/*/
 delay(50);
 delay(50);
 }
 if(rotaries[i].ccwchar == '1'){ /* blink led from any rotation/*/
 delay(50);
 delay(50);
 }
  if(rotaries[i].ccwchar == '3'){ /* blink led from any rotation/*/
 delay(50);
 delay(50);
 }
 
}}}


// end code

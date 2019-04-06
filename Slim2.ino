/* Bluetooth section modified from code by vandenbrand
http://www.instructables.com/id/ArduinoAndroid-BLUETOOTH-Servo-Motor-Control-Andro/
Can you create a method to get commands only when there's
a new BT input? then it doesn't have to look at everything
every time it loops
BT Commands:
2= stop
3= tempo down
4= tempo up
10+ = rhythms
*/


#include <SoftwareSerial.h>
#include <Servo.h>

//inputs
Servo servo1; //right hand outside
Servo servo2; //right hand inside
Servo servo3; //left hand inside
Servo servo4; //left hand outside
Servo servo5; //bass
int bluetoothTx = 10;
int bluetoothRx = 11;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

//variables
int btRec; //received bluetooth data
int runStop = 0; //run/stop 'switch'
int bpm =0;
int hitdelay;
int tadjust;
int pattern; // the rhythms
int btCommand = 0;


void setup() {
 servo1.attach(8);  
servo2.attach(9);
servo3.attach(7);  
servo4.attach(12);
servo5.attach(6);
Serial.begin(9600);
bluetooth.begin(9600);
int tempo1 = 60; // ticktock
int tempo2 = 120;
int tempo3 = 90;
int tempo4 = 200;
int tempo5 = 160;
 hitdelay=(60000/bpm)-200;
}

void loop() {
 btCommand = getBTcommand();
   processBTcommand(btCommand);
}


 int getBTcommand(){
   if(bluetooth.available()> 0 ) {
btRec = bluetooth.read();
if(btRec > 0){
 btCommand =btRec; 
return btCommand;
}
 }
 else{
    Serial.println("bt unavailable"); 
   servo1.write(90);
  servo2.write(80);
   servo3.write(90);
  servo4.write(80); 
  servo5.write(90);
  return btCommand;
}  
 }//end getBTcommand
 
 void processBTcommand(int bt){
   //do the thing based on BT command

if(btRec >40){
  bpm = btRec;
}
 else if(btRec > 9 && btRec < 40){//if greater than 40, its a tempo
playRhythm(bt);
}
else{
  //not rhythms
  switch(btRec){
case 2:  //stop
    servo1.write(90);
  servo2.write(80);
   servo3.write(90);
  servo4.write(80); 
 servo5.write(90);
 btCommand = 2;
 //pattern=0;
 break;
 
 case 3://tempo down
 bpm = bpm - 4;
 btCommand = pattern;
 playRhythm(btCommand);
 break;
 
 case 4://tempo up
 bpm = bpm+4;
 btCommand = pattern;
 playRhythm(btCommand);
 break;
  }//end switch
}//end else
   
 }//end processBTcommand

void playRhythm(int bt){
  
  switch(bt){
 //play rhythm
case 10:
// btCommand = 10;
pattern = 10;
//bpm =56;
ticktock();//tick tock
break;
case 11:
// btCommand = 11;
pattern = 11; 
//bpm=210;
boilerplate();//boilerplate
break;
case 12:
 //btCommand = 12;
pattern = 12; 
//bpm=119;
rock();//Frankie and Johnnie
break;
case 13:
pattern = 13; 
 //btCommand = 13;
// bpm=220;
swing();//Trailerpark Vampire
break;
case 14:
// btCommand = 14;
pattern = 14; 
//bpm=240;
jig();//Paddy on the Skyway
break;
case 15:
// btCommand = 15;
pattern =15;
// bpm=164;
waltz();//any waltz
break;
case 16:
pattern=16;
// btCommand = 16;
//bpm=200;
rimshot();
break;
default:
//pattern = 0;
return;
break;
}//end switch
}//end playRhythm



//rhythm patterns--------------------------------------
void rock(){//frankie and johnnie
 bpm = bpm + 60;
move4and5();
  move1and3();

}//end rock

void waltz(){
  bpm = bpm + 100;
 tadjust = hitdelay/5; 
move1and5();
//moveservo3();
delay(tadjust);
moveservo4();
delay(tadjust);
moveservo3();

//---------------
//moveservo5();
//moveservo1();
//delay(tadjust);
//delay(tadjust);
//moveservo2();
//delay(tadjust);
//delay(tadjust);
}//end waltz

void ticktock(){

    moveservo1(); 
 moveservo2(); 

}//end tick tock

void swing(){
  bpm = bpm + 160;
  tadjust = hitdelay/4;
 move4and5();
  delay(hitdelay);
  delay(hitdelay);
  delay(hitdelay);
  move1and3();
  delay(hitdelay);
  moveservo4();
 
}//end swing

void jig(){
  bpm = bpm +180;
 tadjust = hitdelay/2;
move1and5();
 delay(hitdelay);
 delay(tadjust);
moveservo2();
moveservo1();
delay(hitdelay);
delay(hitdelay);
delay(tadjust);
moveservo2();
}//end jig

void boilerplate(){
  bpm = bpm +150;
  tadjust = hitdelay/6;
  move1and5();
  //delay(tadjust);
    move2and4();
 // move1and5();
  //delay(tadjust);
 // delay(tadjust);
 // move2and4();

}//end boilerplate


void rimshot(){
  bpm=260;
  hitdelay=(60000/bpm)-200;
 //servo3.write(20);
moveservo2(); 
 move1and5();
delay(200);
moveservo3();
delay(1000);
btRec=2;
pattern=0;
}//end rimshot

//stick movements------------------------------------


void moveservo1 ()
{
//down
 for(int i=90;i>=75;i--){
 servo1.write(i);
delay(4);
}  
//up
   for(int i=75;i<=90; i++){
 servo1.write(i);
 delay(4);
}
delay(hitdelay);
}//end moveServo1


void moveservo2 ()
{
  //down
   for(int i=85;i<=100; i++){
 servo2.write(i);
 delay(4);
}
//up
 for(int i=100;i>=85;i--){
 servo2.write(i);
delay(4);
}   
delay(hitdelay);

}//end moveServo2


void moveservo3 ()
{  
  //down
 
 for(int i=86;i>=70;i--){
 servo3.write(i);
delay(4);
}  
//up
 for(int i=70;i<=86; i++){
 servo3.write(i);
 delay(4);
}
delay(hitdelay);
  
}//end moveservo3


void moveservo4 ()
{
  //down
   for(int i=85;i<=100; i++){
 servo4.write(i);
 delay(4);
}
//up
 for(int i=100;i>=85;i--){
 servo4.write(i);
delay(4);
}   
delay(hitdelay);

}//end moveServo4


void move1and3(){
  
  //down
  int b=86;
 for(int i=90;i>=75;i--){
   b--;
 servo1.write(i);
 servo3.write(b);
delay(4);
}  
//up
//b=64;
   for(int i=75;i<=90; i++){
     b++;
 servo1.write(i);
 servo3.write(b);
 delay(4);
}
delay(hitdelay);
}//end move1and3

void moveservo5(){ 
  //down
servo5.write(71);
delay(100);
servo5.write(92);
delay(100);
delay(hitdelay);
}//end move bass

void move1and5(){
  //down
  int b=91;
 for(int i=95;i>=75;i--){
 servo1.write(i);
 servo5.write(b);
 b--;
delay(4);
}  
//up
   for(int i=75;i<=95; i++){
 servo1.write(i);
 servo5.write(b);
 b++;
 delay(4);
}
delay(hitdelay); 
}//end move bass and snare

void move4and5(){
   //down
 int b=91;
   for(int i=80;i<=100; i++){
 servo4.write(i);
 b--;
 servo5.write(b);
 delay(4);
}
//up
 for(int i=100;i>=80;i--){
 servo4.write(i);
 b++;
 servo5.write(b);
delay(4);
}   
delay(hitdelay); 
}//end move bass and cymbal

void move2and4(){
  int b = 83;
     for(int i=85;i<=100; i++){
 servo2.write(i);
 servo4.write(b);
 b++;
 delay(4);
}
//up
 for(int i=100;i>=85;i--){
 servo2.write(i);
 servo4.write(b);
 b--;
delay(4);
}   
delay(hitdelay);
}

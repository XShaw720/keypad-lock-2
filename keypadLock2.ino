/*author: seth shaw
 *date: june 25, 2021
 *description: keypad lock 
 *    holds up to an 8 digit passcode
 *    receives a new passcode every time it is locked
 */

#define unlock 11
#define lock 10
#define green 8
#define red 9

void setup() {
  for(int i=0; i<=7; i++) //pins used for buttons
    pinMode(i, INPUT);

  pinMode(8, OUTPUT); //pins for leds
  pinMode(9, OUTPUT);

  //declare pin(s) used to lock and unlock
}

/*pin: pin to write high
 *count: how many times it'll flash
 *duration: delay between flashes
 */
void flash(int pin, int count, int duration){  //used to flash leds
  for(int i=0; i<count; i++){
    digitalWrite(pin, HIGH);
    delay(duration);
    digitalWrite(pin, LOW);    
  }
}

int button(){ //returns what button was pressed
  int ret=-1;
  if(digitalRead(1)==HIGH){
    if(digitalRead(5)==HIGH)
      ret= 1;
    else if(digitalRead(6)==HIGH)
      ret= 2;
    else if(digitalRead(7)==HIGH)
      ret= 3;
  }
  else if(digitalRead(2)==HIGH){
    if(digitalRead(5)==HIGH)
      ret= 4;
    else if(digitalRead(6)==HIGH)
      ret= 5;
    else if(digitalRead(7)==HIGH)
      ret= 6;
  }
  else if(digitalRead(3)==HIGH){
    if(digitalRead(5)==HIGH)
      ret= 7;
    else if(digitalRead(6)==HIGH)
      ret= 8;
    else if(digitalRead(7)==HIGH)
      ret= 9;
  }
  else if(digitalRead(4)==HIGH){
    if(digitalRead(5)==HIGH)
      ret= lock;
    else if(digitalRead(6)==HIGH)
      ret= 0;
    else if(digitalRead(7)==HIGH)
      ret= unlock;
  }
  flash(green, 1, 100); //flash light to show button was registered
  return ret; 
}

bool check(int a[],int b[]){  //retruns true if array a and b a identical
  for(int i=0; i<8; i++){
    if(a[i]!=b[i])
      return false;
  }
  return true;
}

void wipe(int a[]){ //flashes red light twices and wipes array
  flash(red, 2, 200);
  for(int i=0; i<8; i++)
    a[i]=0;
}

/*a: array to be filled by button pressed
 *retbutton: button that will cause the function to return
 *wipeButton: button to wipe array and continue
 */
void fillArray(int a[], int retButton, int wipeButton){
  for(int i=0,butPressed; i<8; i++){ //locked loop
    butPressed=button();
    if(butPressed==retButton)
      return;
    else if(butPressed==wipeButton){
      wipe(a);
      i=0;
    }
    else
      a[i]=butPressed;
  }
  wipe(a);
  fillArray(a, retButton, wipeButton);
}

void locked(int entries[], int passcode[]){
  while(1){
    fillArray(entries, unlock, lock); //receive code
      if(check(entries, passcode)){ //check if code entered was correct
        //action to unlock
        flash(green, 3, 200); //flash light to show its unlocked
        return;
      }
      wipe(entries);  //wipe if code entered if incorrect
  }
}

void loop() {
  int entries[8], passcode[8], i;

  for(i=0; i<8; i++)
    entries[i]=passcode[i]=0;  //set both arrays to zeros

  fillArray(passcode, lock, -1); //get new passcode
  locked(entries, passcode);

}

uint16_t clockSpeed = 0;
int clockLedPin = 2;

int buttonAPin = 3;
int buttonBPin = 4;
bool buttonA;
bool buttonB;

int adderAPin = 5;
int adderBPin = 6;
bool adderALatch;
bool adderBLatch;

int setButPin = 7;
int resetButPin = 8;
bool buttSet;
bool buttReset;

void setup() {
  Serial.begin(9600);              //  setup serial
  pinMode(clockLedPin, OUTPUT);

  pinMode(buttonAPin, INPUT);
  pinMode(buttonBPin, INPUT);

  pinMode(adderAPin, OUTPUT);
  pinMode(adderBPin, OUTPUT);

  pinMode(setButPin, INPUT);
  pinMode(resetButPin, INPUT);
  
  adderALatch = 0;
  adderBLatch = 0;
}

void loop() {
  // INPUT Read
  clockSpeed = analogRead(0);
  buttonA = digitalRead(buttonAPin);
  buttonB = digitalRead(buttonBPin);
  
  buttSet = digitalRead(setButPin);
  buttReset = digitalRead(resetButPin);
  
  delay(clockSpeed/2);
  digitalWrite(clockLedPin, LOW);
  delay(clockSpeed/2);
  digitalWrite(clockLedPin, HIGH);

  // Define and reset vars
  bool digit0;
  bool digit1;

  // ADDER
  if( buttonA && buttonB ){
    digit0 = false;
    digit1 = true;
  }else if(buttonA || buttonB){
    digit0 = true;
    digit1 = false;
  }else{
    digit0 = false;
    digit1 = false;
  }

  // Display Result
  digitalWrite(adderAPin, digit0);
  digitalWrite(adderBPin, digit1);

  // IF input is not used, read and display RAM state
  if(!(buttonA || buttonB)){
    Serial.println("RAM Read");
    if(adderALatch){
      digitalWrite(adderAPin, HIGH);  
    }else{
      digitalWrite(adderAPin, LOW);  
    }
    if(adderBLatch){
      digitalWrite(adderBPin, HIGH);  
    }else{
      digitalWrite(adderBPin, LOW);  
    }
  }
    
  // Write to RAM
  if(buttSet){
    Serial.println("RAM Write");
    adderALatch = digit0;
    adderBLatch = digit1;
  }
  // Erase the RAM
  if(buttReset){
    Serial.println("RAM Erase");
    adderALatch = 0;
    adderBLatch = 0;
  }



  Serial.println("-");
}

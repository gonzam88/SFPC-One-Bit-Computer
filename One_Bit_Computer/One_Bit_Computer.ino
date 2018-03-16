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
  clockSpeed = analogRead(0);     // read the input pin
  buttonA = digitalRead(buttonAPin);
  buttonB = digitalRead(buttonBPin);
  
  buttSet = digitalRead(setButPin);
  buttReset = digitalRead(resetButPin);
  
  Serial.println(clockSpeed);
//  Serial.println(buttSet);
//  Serial.println(buttReset);
  
  delay(clockSpeed/2);
  digitalWrite(clockLedPin, LOW);
  delay(clockSpeed/2);
  digitalWrite(clockLedPin, HIGH);

  bool digit0;
  bool digit1;

  digitalWrite(adderAPin, digit0);
  
  if(buttonA || buttonB){ // MODO SUMA
    Serial.println("SUMA");
    if( buttonA && buttonB ){
      digit0 = false;
      digit1 = true;
    }else{
      digit1 = false;
      if(buttonA || buttonB){
        digit0 = true;
      }else{
        digit0 = false;
      }
    }
    digitalWrite(adderAPin, digit0);
    digitalWrite(adderBPin, digit1);
  }else{
    // MODO RAM
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
  if(buttSet){
    Serial.println("RAM Write");
    adderALatch = digit0;
    adderBLatch = digit1;
  }
  if(buttReset){
    Serial.println("RAM Erase");
    adderALatch = 0;
    adderBLatch = 0;
  }



  Serial.println("-");
}

//DUM: Interrupts are not directly handeled by the void loop or the "main" part of the code
//they are handeled by hardware structures 

const byte encoderPinA = 2;//outputA digital pin2
const byte encoderPinB = 3;//outoutB digital pin3
volatile long count = 0;
long protectedCount = 0;
long previousCount = 0;
const float convRatio = 0.008371;

#define readA bitRead(PIND,2)//faster than digitalRead()
#define readB bitRead(PIND,3)//faster than digitalRead()


void setup() {
  Serial.begin (115200);

  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
 
  attachInterrupt(digitalPinToInterrupt(encoderPinA), isrA, HIGH);
  //attachInterrupt(digitalPinToInterrupt(encoderPinB), isrB, CHANGE);
}

void loop() {
  noInterrupts();
  protectedCount = count;
  interrupts();
 
  if(protectedCount != previousCount) {
    Serial.print(protectedCount * convRatio);
    Serial.print(" / ");
    Serial.println(protectedCount);
  }
  previousCount = protectedCount;
}

void isrA() {
  if(readA != 0) {
    count ++;
  } /*else {
    count --;
  }*/
}
/*void isrB() {
  if (readA == readB) {
    count ++;
  } else {
    count --;
  }
}*/

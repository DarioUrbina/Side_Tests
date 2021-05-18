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

//motor
int PWM = 50;
int enA=5;  // PWM pin
int in1=7;
int in2=8;
float pwmValA=(PWM*255)/100;


void setup() {
  Serial.begin (115200);

  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
 
  attachInterrupt(digitalPinToInterrupt(encoderPinA), isrA, HIGH);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), isrB, HIGH);
  //motor
  pinMode(enA,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  
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
  
            if (protectedCount > 1){
              while (protectedCount > 0){
              noInterrupts();
              protectedCount = count;
              interrupts();
              if(protectedCount != previousCount) {
              Serial.print(protectedCount * convRatio);
              Serial.print(" / ");
              Serial.println(protectedCount);
              }
              analogWrite (enA, pwmValA);
              digitalWrite(in1,HIGH);
              digitalWrite(in2,LOW);
              }
            } else {
              analogWrite (enA, 0);
            }

   previousCount = protectedCount;

}

void isrA() {
  if(readA != readB) {
    count ++;
  } else {
    count --;
  }
}

void isrB() {
  if (readA == readB) {
    count ++;
  } else {
    count --;
  }
}

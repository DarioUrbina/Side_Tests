#include <stdio.h>
#include <Encoder.h>

/////////////////Tunning values///////////////////////////////////////////////////////////

float scaling_factor_1 = 0.7;
float scaling_factor_2 = 0.7;//.75;
float scaling_factor_3 = 0.7;//.75;
float scaling_factor_4 = 0;
float scaling_factor_5 = 0;//.75;
float scaling_factor_6 = 0;//.75;

/////////////////Motor pins///////////////////////////////////////////////////////////
// Left leg (limb0)/
const int motor_1 = 2;  //  4     working
const int in_1 = 30 ;   //  30
const int in_2 = 32 ;   //  31
const int motor_2 = 3 ;  //  3    working
const int in_3 = 34;    //  32
const int in_4 = 36 ;   //  33
const int motor_3 = 5 ;  //  2 
const int in_5 = 38;    //  28
const int in_6 = 40;    //  29

// Right leg (limb1)/
const int motor_4 = 6 ;  //8
const int in_7 = 42;    //38
const int in_8 = 44;    //39
const int motor_5 = 7 ;  //7
const int in_9 = 46 ;   //36
const int in_10 = 48 ;  //37
const int motor_6 = 8 ;  //6      working
const int in_11 = 50 ;  //34
const int in_12 = 52 ;  //35

/////////////////Writting to motors //////////////////////////////////////////////////////////////////
float pwmVal_1;
float pwmVal_2;
float pwmVal_3;
float pwmVal_4;
float pwmVal_5;
float pwmVal_6;

float pwmVal_1_scaled;
float pwmVal_2_scaled;
float pwmVal_3_scaled;
float pwmVal_4_scaled;
float pwmVal_5_scaled;
float pwmVal_6_scaled;

//////////////// Encoders  //////////////////////////////////////////////////////////////////

Encoder left_hip_encoder(31,33);
Encoder left_knee_encoder(35,37);
Encoder right_hip_encoder(39,41);
Encoder right_knee_encoder(43,45);


/////////////////Tracking angle values///////////////////////////////////////////////////////////

long lhe = -999;
long lke = -999;
long rhe = -999;
long rke = -999;

double previous_angle_1 = 0;
double previous_angle_2 = 0;
double previous_angle_3 = 0;
double previous_angle_4 = 0;
double previous_angle_5 = 0;
double previous_angle_6 = 0;

/////////////////Original sine waves///////////////////////////////////////////////////////////
double sin_1;
double sin_2;
double sin_3;
double sin_4;
double sin_5;
double sin_6;

/////////////////Random values///////////////////////////////////////////////////////////
double ran_angle_1;
double ran_angle_2;
double ran_angle_3;
double ran_angle_4;
double ran_angle_5;
double ran_angle_6;

double aditional_ran_angle_1;

////////////////String outputs ///////////////////////////////////////////////////////////

String str_sin_1;  
String str_sin_2;
String str_sin_3;
String str_sin_4;  
String str_sin_5;
String str_sin_6;

String str_pwmVal_1;
String str_pwmVal_2;
String str_pwmVal_3;
String str_pwmVal_4;
String str_pwmVal_5;
String str_pwmVal_6;


String str_randomArray;

String str_new_lhe;       
String str_new_lke;
String str_new_rhe;       
String str_new_rke; 
String str_encoder_readings; 

String output_line;
String elapsed_time;

void setup()
{

  pinMode(motor_1,OUTPUT) ;   
  pinMode(in_1,OUTPUT) ;  
  pinMode(in_2,OUTPUT) ;
  pinMode(motor_2,OUTPUT) ;   
  pinMode(in_3,OUTPUT) ; 
  pinMode(in_4,OUTPUT) ;
  pinMode(motor_3,OUTPUT) ;   
  pinMode(in_5,OUTPUT) ;  
  pinMode(in_6,OUTPUT) ;
  
  pinMode(motor_4,OUTPUT) ;   
  pinMode(in_7,OUTPUT) ; 
  pinMode(in_8,OUTPUT) ;
  pinMode(motor_5,OUTPUT) ;   
  pinMode(in_9,OUTPUT) ;  
  pinMode(in_10,OUTPUT) ;
  pinMode(motor_6,OUTPUT) ;  
  pinMode(in_11,OUTPUT) ;  
  pinMode(in_12,OUTPUT) ;
  
  randomSeed(10);

  Serial.begin(9600);
}

void loop()

{
 //////////////// Random angles ///////////////////////////////////////////////////////////
  
  ran_angle_1 = (random(5,70));     //(5,100) potentially gives higher frequencies than (5,40)
  ran_angle_1 = ran_angle_1/10;
  ran_angle_2 = (random(5,70));
  ran_angle_2 = ran_angle_2/10;
  ran_angle_3 = random(5,70);
  ran_angle_3 = ran_angle_3/10;
  ran_angle_4 = random(5,70);
  ran_angle_4 = ran_angle_4/10;
  ran_angle_5 = random(5,70);
  ran_angle_5 = ran_angle_5/10;
  ran_angle_6 = random(5,70);
  ran_angle_6 = ran_angle_6/10;

// Generating a 180deg sine wave:

for (float angle_rad=0 ; angle_rad <= 3.141516*2 ; angle_rad = angle_rad+0.05) { 
    long new_lhe, new_lke, new_rhe, new_rke;
    
    //////////////// generating sine waves:
  
    sin_1=(sin(previous_angle_1 + (ran_angle_1*angle_rad) )+1);
    sin_2=(sin(previous_angle_2 + (ran_angle_2*angle_rad))+1);
    sin_3=(sin(previous_angle_3 + (ran_angle_3*angle_rad))+1);
  
    sin_4=(sin(previous_angle_4 + (ran_angle_4*angle_rad))+1);   
    sin_5=(sin(previous_angle_5 + (ran_angle_5*angle_rad))+1);    
    sin_6=(sin(previous_angle_6 + (ran_angle_6*angle_rad))+1);   
  
    str_sin_1 = String(sin_1); 
    str_sin_2 = String(sin_2); 
    str_sin_3 = String(sin_3);
     
    str_sin_4 = String(sin_4); 
    str_sin_5 = String(sin_5); 
    str_sin_6 = String(sin_6);  
  
    //////////////// storing angle readings to start next sine period (this happens when 2 pi (~6.25) have been reacehd):
    
    if (angle_rad >= 6.25){
      previous_angle_1 = previous_angle_1 + (ran_angle_1*angle_rad) ;
      previous_angle_2 = previous_angle_2 + (ran_angle_2*angle_rad) ;
      previous_angle_3 = previous_angle_3 + (ran_angle_3*angle_rad) ;
      previous_angle_4 = previous_angle_4 + (ran_angle_4*angle_rad) ;
      previous_angle_5 = previous_angle_5 + (ran_angle_5*angle_rad) ;
      previous_angle_6 = previous_angle_6 + (ran_angle_6*angle_rad) ;
    }
    
    //////////////// scaling up to 255 (max pwm value), also adding tunnning scaling factor:
 
    pwmVal_1 = sin_1 * 125 * scaling_factor_1; //find right value, not 255!!!
    pwmVal_2 = sin_2 * 125 * scaling_factor_2;   
    pwmVal_3 = sin_3 * 125 * scaling_factor_3; 

    //////////////////  Different signals from left leg send to right leg:
    /*pwmVal_4 = sin_4 * 125 * scaling_factor_4;
    pwmVal_5 = sin_5 * 125 * scaling_factor_5;
    pwmVal_6 = sin_6 * 125 * scaling_factor_6;*/

    //////////////////  Same signals from left leg send to right leg (modulated considering left-right assymetries):
    /*pwmVal_4 = pwmVal_1;
    pwmVal_5 = (1.0007248878 * pwmVal_2) - 3.09578874;
    pwmVal_6 = (0.9850763807 * pwmVal_3) + 15.1400705052;*/


    pwmVal_4 = pwmVal_1;
    pwmVal_5 = pwmVal_2;
    pwmVal_6 = pwmVal_3;
    

    str_pwmVal_1 = String(pwmVal_1);
    str_pwmVal_2 = String(pwmVal_2);
    str_pwmVal_3 = String(pwmVal_3);
    str_pwmVal_4 = String(pwmVal_4);
    str_pwmVal_5 = String(pwmVal_5);
    str_pwmVal_6 = String(pwmVal_6);

    //////////////// sending signals to the motors:

    analogWrite(motor_1,pwmVal_1); //Motor 1
    digitalWrite(in_1,HIGH) ;
    digitalWrite(in_2,LOW) ;
    
    analogWrite(motor_2,pwmVal_2); //Motor 2
    digitalWrite(in_3,HIGH) ;
    digitalWrite(in_4,LOW) ;
    
    analogWrite(motor_3,pwmVal_3); //Motor 3
    digitalWrite(in_5,HIGH) ;
    digitalWrite(in_6,LOW) ;
    
    analogWrite(motor_4,pwmVal_4); //Motor 4
    digitalWrite(in_7,HIGH) ;
    digitalWrite(in_8,LOW) ;
    
    analogWrite(motor_5,pwmVal_5); //Motor 5  pwmVal_5
    digitalWrite(in_9,HIGH) ;
    digitalWrite(in_10,LOW) ;
    
    analogWrite(motor_6,pwmVal_6); //Motor 6
    digitalWrite(in_11,HIGH) ;
    digitalWrite(in_12,LOW) ;

    //////////////// Reading encoders:
    for (int i=0; i<=1; i++){
      new_lhe = left_hip_encoder.read();
      new_lke = left_knee_encoder.read();
      new_rhe = right_hip_encoder.read();
      new_rke = right_knee_encoder.read();
      /*
      if (new_lhe != lhe || new_lke !=lke || new_rhe !=rhe || new_rke !=rke) {
        lhe = new_lhe;
        lke = new_lke;
        rhe = new_rhe;
        rke = new_rke;
      }
      */
      str_new_lhe = String(-new_lhe);  //negtive sign to have same angle evolution drirection in all joints
      str_new_lke = String(-new_lke);  //negtive sign to have same angle evolution drirection in all joints
      str_new_rhe = String(new_rhe); 
      str_new_rke = String(new_rke);
  
      elapsed_time = String(millis());

      ////////////////// String values sent to motors:
      
      //str_randomArray = str_sin_1+ "," + str_sin_2 + "," + str_sin_3 + "," + str_sin_4 + "," + str_sin_5 + "," + str_sin_6 + ",";                     //For serial monitor
      //str_randomArray = str_sin_1+ " " + str_sin_2 + " " + str_sin_3 + " " + str_sin_4 + " " + str_sin_5 + " " + str_sin_6 + " ";                     //For serial plotter
      //str_randomArray = str_pwmVal_1 + "," + str_pwmVal_2 + "," + str_pwmVal_3 + "," + str_pwmVal_4 + "," + str_pwmVal_5 + "," + str_pwmVal_6 + "," ;   //For serial monitor
      str_randomArray = str_pwmVal_1 + " " + str_pwmVal_2 + " " + str_pwmVal_3 + " " + str_pwmVal_4 + " " + str_pwmVal_5 + " " + str_pwmVal_6 + " " ;   //For serial plotter

      
      ////////////////// String values, encoder readings:
      
      //str_encoder_readings = str_new_lhe+ "," + str_new_lke + "," + str_new_rhe+ "," + str_new_rke ;      //For serial monitor
      str_encoder_readings = str_new_lhe+ " " + str_new_lke + " " + str_new_rhe+ " " + str_new_rke ;        //For serial plotter

      ////////////////// Output strings:
      //output_line = elapsed_time + "," + str_randomArray + str_encoder_readings;                          //For serial monitor
      output_line =  str_randomArray + str_encoder_readings;                                              //For serial plotter
  
      Serial.println(output_line);                                                                      //Testing output
      //Serial.println(output_line);
      
    }
    
    
}


  //Serial.println("Hi");

}
   

#include <NewPing.h>    //NewPing(초음파 라이브러리) 선언

NewPing sonar[3] =
{
  NewPing (8, 8, 350),
  NewPing (10, 10, 350),
  NewPing (11, 11, 350),
  
};

#define IN1 2// 1번째 모터
#define IN2 3// 1번째 모터
#define ENA 5// 1번째 모터  PWM제어

#define IN3 4   // 2번째 모터
#define IN4 7   // 2번째 모터
#define ENB 6   // 2번째 모터 PWM제어
int speed = 75;



int Motor_1(int direction, int speed)  //1번 후진 2번 전진 3번 정지
{
  switch(direction)
  {
   case 1:digitalWrite(IN1,HIGH);
          digitalWrite(IN2,LOW);
          analogWrite(ENA,speed);
          digitalWrite(IN3,HIGH);
          digitalWrite(IN4,LOW);
          analogWrite(ENB,speed);
          break;

    case 2:digitalWrite(IN1,LOW);
          digitalWrite(IN2,HIGH);
          analogWrite(ENA,speed);
          digitalWrite(IN3,LOW);
          digitalWrite(IN4,HIGH);
          analogWrite(ENB,speed);
          break;
          
    case 3:digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          analogWrite(ENA, 0);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          analogWrite(ENB, 0);
          break;

   }
}

int Motor_2(int direction, int speed)  //1번 좌회전 2번 우회전
{
  switch(direction)
  {
   case 1:digitalWrite(IN1,LOW);
          digitalWrite(IN2,HIGH);
          analogWrite(ENA,speed);
          digitalWrite(IN3,HIGH);
          digitalWrite(IN4,LOW);
          analogWrite(ENB,speed);
           if( F_distance < 200 && L_distance)
          {
          break;
          }       
    
    case 2:digitalWrite(IN1,HIGH);
          digitalWrite(IN2,LOW);
          analogWrite(ENA,speed);
          digitalWrite(IN3,LOW);
          digitalWrite(IN4,HIGH);
          analogWrite(ENB,speed);
          if( F_distance < 200 && R_distance)
          {
          break;
          }
  }       
}

void sonar(Distance_number)
{
  delay(50);          
  Serial.print("Distance");
  Serial.print(sonar[Distance].ping_cm());
  Serial.println("cm");                    
}


void setup()
{
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
     Serial.begin(115200);
}

void loop()

{

   sonar(0)
   sonar(0)
   sonar(0)
                                
                                
  if (F_distance < 250)   // 정면물체 감지
    {
      Motor_1(3, speed);   
      delay(1550);
         if ( L_distance < R_distance )
          {
            Motor_2(2,speed);
            delay(1300);
            Motor_1(2, speed);  
          }
         else if (R_distance < L_distance)
          {
          Motor_2(1,speed);
          delay(1300);
          Motor_1(2, speed);  
                                                
          }

     }
   else
     {                            
        Motor_1(2, speed);
      }
                             
} 
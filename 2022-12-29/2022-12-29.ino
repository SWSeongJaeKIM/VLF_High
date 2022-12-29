#include <NewPing.h>    //NewPing(초음파 라이브러리) 선언

NewPing sonar[3] =
{
  NewPing (8, 8, 500),
  NewPing (10, 10, 500),
  NewPing (11, 11, 500),
  
};

#define IN1 2// 1번째 모터
#define IN2 3// 1번째 모터
#define ENA 5// 1번째 모터  PWM제어

#define IN3 4   // 2번째 모터
#define IN4 7   // 2번째 모터
#define ENB 6   // 2번째 모터 PWM제어
int speed = 0;

double F_distance =0;
double L_distance =0;
double R_distance =0;
int line_sensor[6] = {0,0,0,0,0};


void motor_control_l(int direction, int speed1, int speed2)    //방향 속도 1: 전진 2: 후진 3: 정지
{
  switch(direction)
  {
    case 1: digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
            digitalWrite(IN3, HIGH);
            digitalWrite(IN4, LOW);
            analogWrite(ENA, speed1);
            analogWrite(ENB, speed2);// 0-255까지 입력
            break;

    case 2: digitalWrite(IN1, LOW);
            digitalWrite(IN2, HIGH);
            digitalWrite(IN3, LOW);
            digitalWrite(IN4, HIGH);           
            analogWrite(ENA, speed1);
            analogWrite(ENB, speed2);
            break;

    case 3: digitalWrite(IN1,LOW);
            digitalWrite(IN2,LOW);
            digitalWrite(IN3,LOW);
            digitalWrite(IN4,LOW);
            analogWrite(ENA, 0);
            analogWrite(ENA, 0);
            break;

  }
}

int Motor_1(int direction, int speed)  //1번 후진 2번 전진 3번 정지
{
  switch(direction)
  {
   case 1:digitalWrite(IN1,LOW);
          digitalWrite(IN2,HIGH);
          analogWrite(ENA,speed);
          digitalWrite(IN3,LOW);
          digitalWrite(IN4,HIGH);
          analogWrite(ENB,speed);
          break;

    case 2:digitalWrite(IN1,HIGH);
          digitalWrite(IN2,LOW);
          analogWrite(ENA,speed);
          digitalWrite(IN3,HIGH);
          digitalWrite(IN4,LOW);
          analogWrite(ENB,speed);
          delay(1000);
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
          break;
    
    case 2:digitalWrite(IN1,HIGH);
          digitalWrite(IN2,LOW);
          analogWrite(ENA,speed);
          digitalWrite(IN3,LOW);
          digitalWrite(IN4,HIGH);
          analogWrite(ENB,speed);
          break;
  }       
}
int read_line_sensor()   //라인트레이서 구동 함수
{
  int i = 0;
  int sum = 0;
  int line_index =0;
  for(i=0; i<5; i++)
  {
     line_sensor[i] =  digitalRead(A0+i);    //센서 반전을 위한 1-
     Serial.print(line_sensor[i]);
     Serial.print("   ");
     sum += line_sensor[i];
     
  }
     Serial.println("");
      
    //line_sensor[0]  line_sensor[1]  line_sensor[2]  line_sensor[3]  line_sensor[4]
    //    -4    -3    -2    -1    0    1    2    3     4
  if(sum==1)
  {
    if(line_sensor[0]==1)
    {line_index = -4;}
    if(line_sensor[1]==1)
    {line_index = -2;}
    if(line_sensor[2]==1)
    {line_index = 0;}
    if(line_sensor[3]==1)
    {line_index = 2;}
    if(line_sensor[4]==1)
    {line_index = 4;}
  }
  else if(sum==2)
  {
    if((line_sensor[0]==1) && (line_sensor[1]==1))
    {line_index = -3;}
    if((line_sensor[1]==1) && (line_sensor[2]==1))
    {line_index = -1;}
    if((line_sensor[2]==1) && (line_sensor[3]==1))
    {line_index = 1;}
    if((line_sensor[3]==1) && (line_sensor[4]==1))
    {line_index = 3;}
  }
  else if(sum == 0)
  {
     line_index = -10;
  }
  else if(sum==5)
  {
     line_index = -30;
  }
  Serial.print(line_index);
  Serial.println("");
  return line_index;
 

      
}//라인적외선 센서 구동 함수



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

//sonar_dis(0);

   F_distance = sonar[0].ping_cm() * 10;
   L_distance = sonar[1].ping_cm() * 10;
   R_distance = sonar[2].ping_cm() * 10;      
   int index;
   int ch;
  /*                              
  if (F_distance < 250 && F_distance > 50)   // 정면물체 감지
    {
      Motor_1(3, speed);   
      delay(1550);

         if (R_distance > L_distance && R_distance > 10 && L_distance > 10)
          {  
            sonar_dis(2);
            sonar_dis(1);
            Motor_2(1 ,speed);
            delay(50);          
            Serial.println("L");
            delay(1100);
            Motor_1(2, speed);  
                                                
          }
          else
          {
            sonar_dis(2);
            sonar_dis(1);
            Motor_2(2,speed);          
            Serial.println("R");
            delay(1100);
            Motor_1(2, speed); 
          }

     }
   else
     {                            
        Motor_1(2, speed);
      }
             */     

    if (F_distance < 150 && F_distance > 30)
    {
      ch = 2;
    }
    else
    {
     ch = 1;
    }

    index = read_line_sensor();
    Serial.print(index);
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println(F_distance);
       Serial.println(ch);
    
    
    
    switch(ch)
    {
      case 1:
            switch(index)
            {
              case -10:     // 라인트레이서 가 모두 들어오면 정지
              motor_control_l(2,100,25);
              break;
              break;
              case 0:      // 라인트레이서가 가운데 하나만 들어오면 직진
               motor_control_l(2,70,60);
               break;
              case -4:    // 맨왼쪽만 들어오면 좌회전으로 빡 꺽어야함
              motor_control_l(2,15,200);
              break;
              case -2:    // 맨왼쪽에서 두번재만 들어오면 죄회전 약하게 꺽어야함
              motor_control_l(2,25,120);
              break;
              
              case 4:     // 맨오른쪽만 들어오면 우회전으로 빡 꺽어야함
              motor_control_l(2,150,25);
              break;
              
        
              case 2:     // 맨오른쪽에서 두번째만 들어오면 우회전으로 약하게 꺽어야함
              motor_control_l(2,40,60);
              break;
        
              case -30:
              Motor_1(3,speed);   //
              break;
        
              case -3:  //맨왼쪽 두개 들어오면 적당히 좌회전으로 꺽어야함
              motor_control_l(2,900,25);
              break;
              
              case -1:  //왼쪽 가운데 들어오면 약간 좌회전으로 꺽어야함
              motor_control_l(2,60,35);
              break;
             case 3:                                 //맨오른쪽 두개 들어오면 적당히 우회전으로 꺽어야함
               motor_control_l(2,40,60);
              break;
   
            }
        break;
              case 2:   //장애물 인식 
              motor_control_l(3,0,0);
              break;
              
              }
    






             
} 

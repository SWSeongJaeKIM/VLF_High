#include <NewPing.h>
NewPing sensor(7,8,500);
double b 0.5
double old_avg=0;
double new_avg=0;
double distance=0;

void in_sonar (void)
{
    distance = sensor.ping_cm()*10.0;
}

 void average (float a,float b)
 {
    new_avg = (old_avg*K)+(a*(1-b));
    old_avg=new_avg
 }

void setup()
{ 
Serial.begin(115200);
}

void loop() {
 
  in_sensor();
  average(distance,b);
  Serial.print("average");
  Serial.print("  ");
  Serial.println(new_avg);
  }

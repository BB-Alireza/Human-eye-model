#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define JOY_X A0
#define JOY_Y A1
#define JOY_KEY 2
#define POT   A2
#define SWITCH 3

double Motor[6] = {0,0,0,0,0,0};
int i;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50); 
  pinMode(JOY_KEY ,INPUT_PULLUP);
  pinMode(SWITCH ,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(analogRead(JOY_X));
  Serial.print(",");
  Serial.print(analogRead(JOY_Y));
  Serial.print(",");
  Serial.print(analogRead(POT));
  Serial.print(",");
  Serial.print(digitalRead(JOY_KEY)*1023);
  Serial.print(",");
  Serial.println(digitalRead(SWITCH)*1023);

  Motor[0] = map(analogRead(JOY_Y) , 0 , 1023 , 235 ,370);
  Motor[1] = map(analogRead(JOY_X) , 0 , 1023 , 245 ,360);
  
  for (i = 2; i < 4; i++)
    if ((i & 0x01))
      Motor[i] = map(digitalRead(SWITCH) ? 300 : analogRead(POT), 300 , 600 , 330 ,210); // 330 250
    else
      Motor[i] = map(digitalRead(SWITCH) ? 300 : analogRead(POT), 300 , 600 , 250 ,370); // 250 330

  for (i = 4; i < 6; i++)
    if ((i & 0x01))
      Motor[i] = map((digitalRead(SWITCH)||!digitalRead(JOY_KEY)) ? 300 : analogRead(POT), 300 , 600 , 330 ,210); // 330 250
    else
      Motor[i] = map((digitalRead(SWITCH)||!digitalRead(JOY_KEY)) ? 300 : analogRead(POT), 300 , 600 , 250 ,370); // 250 330

  for (i = 0; i< 6; i++)
    pwm.setPWM(i, 0, Motor[i]);

  delay(10);

}

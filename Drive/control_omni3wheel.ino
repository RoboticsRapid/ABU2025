#include <PS4Controller.h>

//B
#define motor1A 15  
#define motor1B 2
//L
#define motor2A 0  
#define motor2B 4
//R
#define motor3A 5  
#define motor3B 18

int speedLX = 0;
int speedLY = 0;
int speedRX = 0;
int speedRY = 0;

void setup() {
    Serial.begin(115200);
    
    // Motor pins as output
    pinMode(motor1A, OUTPUT);
    pinMode(motor1B, OUTPUT);
    pinMode(motor2A, OUTPUT);
    pinMode(motor2B, OUTPUT);
    pinMode(motor3A, OUTPUT);
    pinMode(motor3B, OUTPUT);

    PS4.begin(); 
    Serial.println("Waiting for PS4 Controller...");

}

void loop() {
  if (PS4.isConnected()) {
        if (ps4IsConnected) { 
            Serial.println("");
            bool ps4IsConnected = true;  
        }

        int leftX = PS4.LStickX();  
        int leftY = PS4.LStickY();
        int rightX = PS4.RStickX();
        int rightY = PS4.RStickY(); 

        int speedLX = map(leftX, -127, 127, -255, 255);
        int speedLY = map(leftY, -127, 127, -255, 255);

        Serial.print("LX: "); Serial.print(leftX);
        Serial.print("\tLY: "); Serial.print(leftY);
        Serial.print("\tRX: "); Serial.print(rightX);
        Serial.print("\tRY: "); Serial.print(rightY);

        Serial.print("\tspeedLX: "); Serial.print(speedLX);
        Serial.print("\tspeedLY: "); Serial.print(speedLY);
        Serial.print("\tspeedRX: "); Serial.print(speedRX);
        Serial.print("\tspeedRY: "); Serial.print(speedRY);

        Serial.println();

        control(speedLX, speedLY);
        delay(100);
    } else {
        if (ps4IsConnected) {  
          Serial.println("PS4 Controller Disconnected!");
          bool ps4IsConnected = false;
        }
    }
}

void control(int speedLX, int speedLY){
  if (speedLY > 10 && abs(speedLX) < 200) {  //move forward
    analogWrite(motor1A, LOW);
    analogWrite(motor1B, LOW);
    analogWrite(motor2A, LOW);
    analogWrite(motor2B, speedLY);
    analogWrite(motor3A, speedLY);
    analogWrite(motor3B, LOW);
  }else if(speedLY < -30 && abs(speedLX) < 200){  //move backward
    analogWrite(motor1A, LOW);
    analogWrite(motor1B, LOW);
    analogWrite(motor2A, abs(speedLY));
    analogWrite(motor2B, LOW);
    analogWrite(motor3A, LOW);
    analogWrite(motor3B, abs(speedLY));
  }else if(speedLX > 0 && abs(speedLY) < 200){  //turn right
    analogWrite(motor1A, speedLX );
    analogWrite(motor1B, LOW);
    analogWrite(motor2A, LOW);
    analogWrite(motor2B, speedLX/2);
    analogWrite(motor3A, LOW);
    analogWrite(motor3B, speedLX/2);
  }else if(speedLX < -50 && abs(speedLY) < 200){   //turn left
    analogWrite(motor1A, LOW);
    analogWrite(motor1B, abs(speedLX));
    analogWrite(motor2A, abs(speedLX/2));
    analogWrite(motor2B, LOW);
    analogWrite(motor3A, abs(speedLX/2));
    analogWrite(motor3B, LOW);
  }else{ // stop
    analogWrite(motor1A, LOW);
    analogWrite(motor1B, LOW);
    analogWrite(motor2A, LOW);
    analogWrite(motor2B, LOW);
    analogWrite(motor3A, LOW);
    analogWrite(motor3B, LOW);
  }
}
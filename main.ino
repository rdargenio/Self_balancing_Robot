#include <Adafruit_MPU6050.h> // https://www.arduino.cc/reference/en/libraries/adafruit-mpu6050/
#include <Adafruit_Sensor.h> // part of above library
#include <Wire.h>

/* IMU parameters */
Adafruit_MPU6050 mpu;
sensors_event_t accelerometer, gyro, temp;

/* L298N Module */
// Right Motor
#define in1 6
#define in2 7
#define enA 5

// Left Motor
#define in3 8
#define in4 9
#define enB 10

double AccX, AccY, AccZ;
double GyroX, GyroY, GyroZ;
double output; // Motor

void setup(void) {
  // Waut for serial monitor to be opened
  Serial.begin(115200);
  while (!Serial)
    delay(10);
  
  // Setup IMU
   mpu.begin();
}


void loop() {   
  mpu.getEvent(&accelerometer, &gyro, &temp);

  // Only the X axis is needed
  AccX = (Wire.read() << 8 | Wire.read()) / 16384.0;
  GyroX = (Wire.read() << 8 | Wire.read()) / 131.0; 

  // Need to pass the IMU values to the neural network and get the "output" for the motors
  
  setMotor(output);

  // Plot
  Serial.print(setpoint);
  Serial.print("\t");
  Serial.print(input);
  Serial.print("\t");
  Serial.println(output);
}


void setMotor(int motorSpeed) {
  analogWrite(enA, abs(motorSpeed));
  analogWrite(enB, abs(motorSpeed));
  
  if(motorSpeed < 0) { // may need to flip
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
}

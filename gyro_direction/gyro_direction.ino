#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 mpu;
//MPU6050 mpu(0x69); // <-- use for AD0 high
#define OUTPUT_READABLE_YAWPITCHROLL
#define INTERRUPT_PIN 2  // use pin 2 on Arduino Uno & most boards

bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}

const int lm = 3;
const int lmr = 5;
const int rm = 6;
const int rmr = 9;
const int left = 8;
const int right = 4;
const int front = 7;
float kP = 0.1;
float kD = 0.1;
int last_value;
int dirValue;

void setup() {
  pinMode(lm, OUTPUT);
pinMode(lmr, OUTPUT);
pinMode(rm, OUTPUT);
pinMode(rmr, OUTPUT);
pinMode(left, INPUT);
pinMode(right, INPUT); 
  pinMode(front, INPUT);
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // initialize serial communication
    // (115200 chosen because it is required for Teapot Demo output, but it's
    // really up to you depending on your project)
    Serial.begin(115200);
    while (!Serial); // wait for Leonardo enumeration, others continue immediately



    // initialize device
    Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();
    pinMode(INTERRUPT_PIN, INPUT);

    // verify connection
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

//    // wait for ready
//    Serial.println(F("\nSend any character to begin DMP programming and demo: "));
//    while (Serial.available() && Serial.read()); // empty buffer
//    while (!Serial.available());                 // wait for data
//    while (Serial.available() && Serial.read()); // empty buffer again

    // load and configure the DMP
    Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // Calibration Time: generate offsets and calibrate our MPU6050
        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
        mpu.PrintActiveOffsets();
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        Serial.print(F("Enabling interrupt detection (Arduino external interrupt "));
        Serial.print(digitalPinToInterrupt(INTERRUPT_PIN));
        Serial.println(F(")..."));
        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }    
}


void loop() {
            int aa;
            Serial.println(aa);
            int leftVal = !digitalRead(left);
            int rightVal = !digitalRead(right);
            int frontVal = !digitalRead(front);
            Serial.print(leftVal);
            Serial.print(rightVal);
            Serial.println(frontVal);

            if((leftVal == HIGH && rightVal == HIGH && frontVal == LOW)){

              if(aa >= 0){
                int err = aa - 0;
                int diff = err * kP + (err - last_value) * kD;
                motor(80-diff,80+diff);
                last_value = err;
                Serial.println(err);
              }
              else if(aa<0){
                int err = 180 + aa;
                int diff = err * kP + (err - last_value) * kD;
                motor(80-diff,80+diff);
                last_value = err;
                Serial.println(err);
              }
            }
            else if((leftVal == HIGH && rightVal == LOW && frontVal == HIGH)){
             // while(int(ypr[0] * 180/M_PI)<91){
                Serial.println(aa);
                motor(0,80);

//                if(aa >= 0){
//                  int err = aa - 0;
//                  int diff = err * kP + (err - last_value) * kD;
//                  motor(80-diff,80+diff);
//                  last_value = err;
//                  Serial.println(err);
//                }
//                else if(aa<0){
//                  int err = 180 + aa;
//                  int diff = err * kP + (err - last_value) * kD;
//                  motor(80-diff,80+diff);
//                  last_value = err;
//                  Serial.println(err);
//                }
              
            }
             
            switch(aa){
              case 0:
                Serial.println("North");
                //digitalWrite(5, HIGH);
                break;
              case 90:
                Serial.println("East");
                //digitalWrite(6, HIGH);
                break;
              case -179:
                Serial.println("South");
                //digitalWrite(7, HIGH);
                break;
              case -90:
                Serial.println("West");
                //digitalWrite(8, HIGH);
                break;
              default:
//                digitalWrite(5, LOW);
//                digitalWrite(6, LOW);
//                digitalWrite(7, LOW);
//                digitalWrite(8, LOW);
                  Serial.println("Westeee");
//              
            }
//              
                
//            Serial.print("\t");
//            Serial.print(ypr[1] * 180/M_PI);
//            Serial.print("\t");
//            Serial.println(ypr[2] * 180/M_PI);
   //     #endif




    }


void motor(int left, int right){
  

  if (left > 0 && right==0){
    Serial.println("rr");
    analogWrite(lm, left);
    analogWrite(lmr, LOW);
    analogWrite(rm, right);
    analogWrite(rmr, LOW);
    
    delay(1);
   // loop();
  }
//  else if(left < 0 && right=0){
//    digitalWrite(lm, LOW);
//    analogWrite(lmr, left * -1);
//  }
  else if(left == 0 && right >0){
    Serial.println("ll");
    analogWrite(lm, left);
    analogWrite(lmr, LOW);
    analogWrite(rm, right);
    analogWrite(rmr, LOW);
    delay(1);
    //loop();
  }
  else if(left > 0 && right >0){
    Serial.println("ff");
    analogWrite(lm, left);
    analogWrite(lmr, LOW);
    analogWrite(rm, right);
    analogWrite(rmr, LOW);
    delay(1);
    //loop();
  }
//  else if(left = 0 && right <0){
//    digitalWrite(rm, LOW);
//    analogWrite(rmr, right * -1);
//  }
  else if((left == 0 && right ==0)|| (left == 255 && right ==255)){
    Serial.println("ss");
    digitalWrite(lm, LOW);
    digitalWrite(lmr, LOW);
    digitalWrite(rm, LOW);
    digitalWrite(rmr, LOW);
  }
}

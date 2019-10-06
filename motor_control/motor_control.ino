const int lm = 3;
const int lmr = 5;
const int rm = 6;
const int rmr = 9;
const int left = 8;
const int right = 4;
const int front = 7;


//3569


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
pinMode(lm, OUTPUT);
pinMode(lmr, OUTPUT);
pinMode(rm, OUTPUT);
pinMode(rmr, OUTPUT);
pinMode(left, INPUT);
pinMode(right, INPUT);
pinMode(front, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //ubata oooooni wdykt cal krpn (-:
  int leftVal = !digitalRead(left);
  int rightVal = !digitalRead(right);
  int frontVal = !digitalRead(front);
  Serial.print(leftVal);
  Serial.print(rightVal);
  Serial.println(frontVal);
  
  if((leftVal == HIGH && rightVal == LOW && frontVal == LOW)){
    //delay(300);
    Serial.println("r");
    //delay(200);
    while(!digitalRead(left)){
      motor(0,80);
    }
     
  }
  else if(leftVal == LOW && rightVal == HIGH && frontVal == LOW){
    //delay(300);
    Serial.println("l");
    //delay(200);
    while(!digitalRead(right)){
      motor(80,0);
    }
    
  }
  else{
    //delay(300);
    Serial.println("f");
    //delay(200);
    motor(70, 80);
  }


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

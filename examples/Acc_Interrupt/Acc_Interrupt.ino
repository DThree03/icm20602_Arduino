#include <icm20602.h>

#define INT_PIN 2
#define AD0_VAL 0

icm20602 ACC(AD0_VAL);

float px, py, pz;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   if(ACC.begin()){
      //Enable Acc interuppt
      ACC.enable_Interrupt(INT_PIN, icmISR, FALLING); //AUTO_CLEAR mode in default
      //ACC.enable_Interrupt(INT_PIN, icmISR, FALLING, AUTO_CLEAR);
      //ACC.enable_Interrupt(INT_PIN, icmISR, FALLING, CLEAR_BY_READ);  //Clear interuppt by read operation

      //Update Acc ISR Sensitive. Default is 0x1F
      //ACC.ISR_Sensitive_Update(0x0F);
   }
   else{
      Serial.println("Chip communication ERROR!");
   }
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()>0){
    char inChar = Serial.read();
    if(inChar == 'a'){
      ACC.icm20602_read_accel(&px, &py, &pz);
      Serial.printf("Acc read: x = %.02f, y = %.02f, z = %.02f", px, py, pz);
      Serial.println();
      Serial.printf("TEMP read = %.02f", ACC.getTemp());
      Serial.println();
    }
    else if(inChar == 'b'){
      ACC.icm20602_read_gyro(&px, &py, &pz);
      Serial.printf("Gyro read: x = %.02f, y = %.02f, z = %.02f", px, py, pz);
      Serial.println();
    }
    else if(inChar == 'c'){
      ACC.ISR_Sensitive_Update(0x0F); //0 ~ 255
    }
    else{
      Serial.printf("INT Status Reg: 0x%2X", ACC.getIntStatus());
      Serial.println();
    }
  }
}
void icmISR( void ){
  //Interrupt code:
  Serial.println("Interuppt ISR!");
  
  
}

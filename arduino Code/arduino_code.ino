#define analogPin 0          
#define chargePin 13         
#define dischargePin 8        
#define resistorValue 10000.0F  
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

struct voltTime
{
  int analogVal;
  int timeVal;
};

void readCap();
void readResistor();
float readResistorsilent();


void setup() {
  // put your setup code here, to run once:
  pinMode(chargePin, OUTPUT);     
  digitalWrite(chargePin, LOW); 
  lcd.begin(16, 2); 
  Serial.begin(9600);
  int threshold = analogRead(A0);

}

void loop() {
  // put your main code here, to run repeatedly:

  lcd.setCursor(0, 0);
  lcd.print("check capacitor");
  lcd.setCursor(0, 1);
  lcd.print("or resistor       ");

  //assuming there is a charged capacitor
  //we need to discharge some of its charge to measure rate of change of voltage
  digitalWrite(chargePin, LOW);            
  pinMode(dischargePin, OUTPUT);            
  digitalWrite(dischargePin, LOW);          
  delay(3000);
  pinMode(dischargePin, INPUT);  


//saving voltage and time initially
voltTime start;
digitalWrite(chargePin, HIGH);
start.timeVal = millis();
start.analogVal = analogRead(A0);

delay(100);

//saving volatge and time finally
voltTime finish;

finish.timeVal = millis();
finish.analogVal = analogRead(A0);
digitalWrite(chargePin, LOW);

//calculating average rate of change
float slope = (float)(finish.analogVal - start.analogVal)/(float)(finish.timeVal - start.timeVal);


if(readResistorsilent() < 1000000.0f)//detecting if nothing is connected
{
    lcd.clear();

    if( slope <= 0.02f)//if low rate of change it is a resistor
    {
      readResistor();
      Serial.println("in Res");
      Serial.println(slope);
      delay(1000);
    }
    else//if high rate of change it is a cap
    {
      Serial.println("in cap");

      digitalWrite(chargePin, LOW);            
      pinMode(dischargePin, OUTPUT);            
      digitalWrite(dischargePin, LOW); 

      //discharging capacitor assuming it was charged         
      while(analogRead(analogPin) > 0){         
      }
    
      pinMode(dischargePin, INPUT);
      Serial.println(slope);

      readCap();
      
      
      delay(1000);
    }

}
else
{
  lcd.setCursor(0, 0);
  lcd.println("nothing is            ");
  lcd.setCursor(0, 1);
  lcd.println(" connected            ");
  Serial.println("nothing is connected");
}

//Serial.println(slope);

delay(3000);
lcd.setCursor(0, 0);
  
  

}


void readCap()
{
  unsigned long startTime;
  unsigned long elapsedTime;
  float microFarads;                
  float nanoFarads;
    
/********setup******************/
  pinMode(chargePin, OUTPUT);     
  digitalWrite(chargePin, LOW); 
  lcd.begin(16, 2); 
  Serial.begin(9600);
  int threshold = analogRead(A0);
  lcd.setCursor(0, 0);
/*****************************/
  lcd.setCursor(0, 0);
  lcd.print(" reading cap ");
  lcd.setCursor(0, 1);
  digitalWrite(chargePin, HIGH);  
  startTime = millis();
  while(analogRead(analogPin) < 648){       
  }
  
  //lcd.print(" while passed");
  

  elapsedTime= millis() - startTime;
  microFarads = ((float)elapsedTime / resistorValue) * 1000; //calculating capacitance
  lcd.print(elapsedTime);       
  lcd.print(" mS");
  delay(3000);  
  lcd.clear();
  delay(500);

  if (microFarads > 1){
    lcd.print(microFarads);       
    lcd.print(" uF");   
    delay(3000);    
  }

  else{
    nanoFarads = microFarads * 1000.0;      
    lcd.print(nanoFarads);         
    lcd.print(" nF");          
    delay(3000); 
  }

  lcd.clear();
  digitalWrite(chargePin, LOW);            
  pinMode(dischargePin, OUTPUT);            
  digitalWrite(dischargePin, LOW);
  lcd.print("discharging cap");          
  while(analogRead(analogPin) > 0){         
  }

  pinMode(dischargePin, INPUT);
  delay(1000);
  lcd.clear();
        
}



 void readResistor()
 {
 /********setup******************/
  lcd.begin(16, 2);
  pinMode(chargePin, OUTPUT);     
  digitalWrite(chargePin, LOW);
  Serial.begin(9600);
/*****************************/

  lcd.setCursor(0, 0);
  lcd.print(" reading res ");
  delay(500);

  digitalWrite(chargePin, HIGH);
  float voltage = (analogRead(A0) * 5.0f)/1023.0f; //maping 10 bit ADC output to 5v
  float resistance = voltage/((5-voltage)/resistorValue);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("resistance =       ");
  lcd.setCursor(0, 1);
  lcd.print(resistance);
  lcd.print(" ohm          ");
  lcd.println("            ");

  Serial.println(voltage);
  Serial.println(resistance);
  delay(1000);
  //lcd.clear();


 }

 float readResistorsilent()
 {
 /********setup******************/

  pinMode(chargePin, OUTPUT);     
  digitalWrite(chargePin, LOW);
 
/*****************************/

  digitalWrite(chargePin, HIGH);
  float voltage = (analogRead(A0) * 5.0f)/1023.0f;
  float resistance = voltage/((5-voltage)/resistorValue);

  return resistance;


 }
 
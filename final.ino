const int Relay=0;
const float potentiometer1 = A0;  // Analog input pin for the 5V potentiometer
const float potentiometer2 = A1;  // Analog input pin for the 3.3V potentiometer
const int led_Pin = 13 ;

const int bpsread = A2;
float potentiometer_value1, potentiometer_value2, brakepressure;
float voltage1, voltage2, voltage3;
float value1, value2, value3;
const int bps;
float brakevalue;
unsigned long previousTime = 0;
const long intervaldifference = 100;

void setup() {
  pinMode(led_Pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  float potentiometer_value1 = analogRead(potentiometer1);  // Read the value from the 5V potentiometer
  float potentiometer_value2 = analogRead(potentiometer2);  // Read the value from the 3.3V potentiometer
  float brakepressure = analogRead(bpsread);                // Read the value from the 5V potentiometer

  voltage1 = float(potentiometer_value1 * (5.0 / 1023));  //Convert analog reading 5V  in (0-676)
  voltage2 = float(potentiometer_value2 * (3.3 / 676));   //convert analog reading 3.3v in (0-1023)
  voltage3 = float(brakepressure * (4.5 / 1023));         //Convert analog reading 5V  in (0-676) to operate (in 0.5-4.5)

  value1 = float(map(potentiometer_value1, 0, 1023, 0, 100));  // Convert analog value to percentage (5V)
  value2 = float(map(potentiometer_value2, 0, 676, 0, 100));   // Convert analog value to percentage (3.3v)
  value3 = float(map(brakepressure, 105, 1023, 0, 100));       // Convert analog value to percentage (5V)

  Serial.print("- Voltage 1: ");
  Serial.print(voltage1);
  Serial.print("- Voltage 2: ");
  Serial.print(voltage2);
  Serial.print("  -per1:   ");
  Serial.print(value1);
  Serial.print("  -per2:  ");
  Serial.print(value2);

  float voltagedifference = float(abs(voltage1 - voltage2));

  Serial.print(" - Voltage Difference: ");
  Serial.print(voltagedifference);

  float percentdiff = abs(value1 - value2);

  Serial.print(" - Percentage Difference: ");
  Serial.print(percentdiff);
  Serial.print("- Voltage 3: ");
  Serial.print(voltage3);
  Serial.print("  -per3:   ");
  Serial.print(value3);
  delay(1000);

  if (value1 > 5 && value2 > 5) 
  {
     if (voltagedifference > 10)
    {
      unsigned long currentTime = millis();
      if (currentTime - previousTime > 100) 
      {
        previousTime = currentTime;
        digitalWrite(Relay,LOW);

        Serial.print("  -previousTime= ");
        Serial.print(previousTime);
        Serial.print("  -currentTime= ");
        Serial.print(currentTime);
      }
                    // else {
                      // (Relay,HIGH);
                    // }
                    //else(Relay,HIGH);
    }
  }
  
      //condition 2 apply here
       // else if (value1 > 5 && value2 > 5) 
         // {
        //    digitalWrite(Relay, HIGH); }

    //sample conditionn 2

    if ((value1 >= 25 && value2 >= 25) && value3 > 15)
    {
          unsigned long newtiming = millis();
          if (newtiming-previousTime>500)
        {
                digitalWrite(Relay,LOW);
        }
        else {
          digitalWrite(Relay,HIGH);
        }
    }
    
  }
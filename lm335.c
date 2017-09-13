


int inputPin;
float getCelciusLM335();


float getCelciusLM335(){
     int rawValue;
     float milliVolts;
     float celcius;

     //read raw adc value
     rawValue = analogRead(inputPin);
     //conert to millivolts
     milliVolts = (5000*rawValue)/1024.0;
     
     //return millivolts converted to celius via lm335 transfer function (10 mV per degree Kelvin)
     return (milliVolts/10) - 273;
  
  }  

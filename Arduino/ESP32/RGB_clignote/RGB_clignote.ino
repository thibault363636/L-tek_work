// the number of the LED pin
const int ledPin = 2;  // 16 corresponds to GPIO16
const int ledPin2 = 4; // 17 corresponds to GPIO17
const int ledPin3 = 12;  // 5 corresponds to GPIO5

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int ledChannel2 = 1;
const int ledChannel3 = 2;
const int resolution = 8;
 
void setup(){
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  ledcSetup(ledChannel2, freq, resolution);
  ledcSetup(ledChannel3, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);
  ledcAttachPin(ledPin2, ledChannel2);
  ledcAttachPin(ledPin3, ledChannel3);
}
 
void loop(){
  // increase the LED brightness
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);
    delay(15);
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);   
    delay(15);
  }

  delay(100);

    // increase the LED brightness
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    // changing the LED brightness with PWM
    ledcWrite(ledChannel2, dutyCycle);
    delay(15);
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    // changing the LED brightness with PWM
    ledcWrite(ledChannel2, dutyCycle);   
    delay(15);
  }

  delay(100);

  // increase the LED brightness
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    // changing the LED brightness with PWM
    ledcWrite(ledChannel3, dutyCycle);
    delay(15);
  }

  // decrease the LED brightness
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    // changing the LED brightness with PWM
    ledcWrite(ledChannel3, dutyCycle);   
    delay(15);
  }
  delay(100);
}
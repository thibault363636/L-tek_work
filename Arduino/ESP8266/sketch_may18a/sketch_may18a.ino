void setup() {
   pinMode(4, OUTPUT);
   pinMode(2, OUTPUT);
   pinMode(12, OUTPUT);
   Serial.begin(9600);
}

void loop() {
   digitalWrite(4, HIGH);
   delay(1000);
   digitalWrite(4, LOW);
   delay(1000);

   digitalWrite(2, HIGH);
   delay(1000);
   digitalWrite(2, LOW);
   delay(1000);

   digitalWrite(12, HIGH);
   delay(1000);
   digitalWrite(12, LOW);
   delay(1000);
   
 Serial.println("hello");
}
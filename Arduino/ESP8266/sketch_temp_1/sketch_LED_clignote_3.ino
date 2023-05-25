int ThermistorPin = 0;
int Vo;
float r;
float a = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 0.0008802379350954048, c2 = 0.00025261779329179923, c3 = 1.8747408754669722e-07;
float b = 440.9030052843748;
float c = 2000;
float e = 881;
float d = 3.3;
void setup() {

  // Initialise la communication avec le PC
  Serial.begin(9600);
}

// Fonction loop(), appelée continuellement en boucle tant que la carte Arduino est alimentée
void loop() {

  // Mesure la tension sur la broche A0
  int valeur = analogRead(A0);

  // Transforme la mesure (nombre entier) en tension via un produit en croix
  float v = valeur * (3.3 / 1023.0);

  // Envoi la mesure au PC pour affichage et attends 250ms
  Serial.println(v);
  delay(250);

 Vo = analogRead(ThermistorPin);
  r  = (e*d*a*b + e*d*a*c - d*a*b*c - e*v*a*b) / (b* (e*v + d*c));
  T = 1.0/(c1 + c2* (log(r)) + c3* (log(r)*log(r)*log(r)));
  Tc = T - 273.15;
  Tf = (Tc * 9.0)/ 5.0 + 32.0; 

  Serial.print("Temperature: ");
  Serial.print(Tf);
  Serial.print(" F; ");
  Serial.print(Tc);
  Serial.println(" C");
  Serial.println( r );
  Serial.println( T );

  delay(500);
}
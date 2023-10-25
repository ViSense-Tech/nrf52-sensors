/* Change these values based on your observations */
#define wetSoil 277   // Define max value we consider soil 'wet'
#define drySoil 380   // Define min value we consider soil 'dry'

// Define analog input
#define sensorPin A0

void setup() {  
  Serial.begin(9600);
}

void loop() {
  // Read the Analog Input and print it
  int moisture = analogRead(sensorPin);
  Serial.print("Analog output: ");
  Serial.println(moisture);
  
  // Determine status of our soil
  if (moisture < wetSoil) {
    Serial.println("Status: Soil is too wet");
  } else if (moisture >= wetSoil && moisture < drySoil) {
    Serial.println("Status: Soil moisture is perfect");
    Serial.println(moisture);
  } else {
    Serial.println("Status: Soil is too dry - time to water!");
    Serial.println(moisture);
  }
  Serial.println();
  
  // Take a reading every second
  delay(1000);
}

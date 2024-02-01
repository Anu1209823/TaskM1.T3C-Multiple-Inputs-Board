// Pin definitions
const int temperatureSensorPin = A0;
const int pirSensorPin = 2;
const int ledPin = 9;

// Threshold temperature in Celsius
const float thresholdTemp = 25.0;

// Flag to indicate motion detection
volatile bool motionDetected = false;

void setup() {
  // Initialize LED pin as output
  pinMode(ledPin, OUTPUT);
  
  // Initialize PIR sensor pin as input
  pinMode(pirSensorPin, INPUT);
  
  // Attach interrupt for motion sensor
  attachInterrupt(digitalPinToInterrupt(pirSensorPin), motionInterrupt, CHANGE);

  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Main program logic
  // Read temperature from sensor
  float temperature = readTemperature();

  // Read PIR sensor
  int pirValue = digitalRead(pirSensorPin);

  // Read LED status
  int ledState = digitalRead(ledPin);

  // Display readings in serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" degrees Celsius");

  Serial.print("PIR Sensor Reading: ");
  Serial.println(pirValue);

  Serial.print("LED Status: ");
  Serial.println(ledState == HIGH ? "ON" : "OFF");

  // Check if temperature exceeds threshold
  if (temperature > thresholdTemp) {
    Serial.println("Temperature exceeded threshold!");
    digitalWrite(ledPin, HIGH); // Turn on LED
  } else {
    digitalWrite(ledPin, LOW); // Turn off LED
  }

  // Add delay for readability
  delay(1000); // Adjust delay time as needed

  // Add any other non-blocking tasks here
}

// Interrupt service routine for motion detection
void motionInterrupt() {
  motionDetected = true;
}

// Function to read temperature from sensor
float readTemperature() {
  int sensorValue = analogRead(temperatureSensorPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperatureC = (voltage - 0.5) * 100.0;
  return temperatureC;
}

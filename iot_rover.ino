#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Define motor control pins
#define MOTOR_A_PIN1 D0
#define MOTOR_A_PIN2 D1
#define MOTOR_B_PIN1 D2
#define MOTOR_B_PIN2 D3

// Define LED pin
#define LED_PIN D4 // GPIO2


#define BLYNK_TEMPLATE_NAME "IOT ROVER"
#define BLYNK_AUTH_TOKEN "NtSKZE0BmMVTZ4jZpmoOipuy6JnguW_G"
#define BLYNK_TEMPLATE_ID "TMPL3ipqaLYVV"

// WiFi credentials
char ssid[] = "IOT";
char pass[] = "iot@1234";
 
// Define a flag to keep track of connection status
bool isConnected = false;

void setup() {
  // Start serial communication
  Serial.begin(9600);

  // Set motor control pins as outputs
  pinMode(MOTOR_A_PIN1, OUTPUT);
  pinMode(MOTOR_A_PIN2, OUTPUT);
  pinMode(MOTOR_B_PIN1, OUTPUT);
  pinMode(MOTOR_B_PIN2, OUTPUT);

  // Set LED pin as output
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, 1); // Initially turn off the LED
  
  // Connect to WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  // Run Blynk
  Blynk.run();
  
  // Check Blynk connection status and update LED state
  if (Blynk.connected() && !isConnected) {
    // Turn on the LED and update the LED widget
    digitalWrite(LED_PIN, 0);
    Blynk.virtualWrite(V4, 1); // Update LED widget to ON
    isConnected = true;
  } else if (!Blynk.connected() && isConnected) {
    // Turn off the LED and update the LED widget
    digitalWrite(LED_PIN, 1);
    Blynk.virtualWrite(V4, 0); // Update LED widget to OFF
    isConnected = false;
  }
}

// Function to control forward movement
BLYNK_WRITE(V0) {
  int value = param.asInt();
  if (value) {
    digitalWrite(MOTOR_A_PIN1, HIGH);
    digitalWrite(MOTOR_A_PIN2, LOW);
    digitalWrite(MOTOR_B_PIN1, HIGH);
    digitalWrite(MOTOR_B_PIN2, LOW);
    Serial.println("Function to control forward movement");

  } else {
    stopCar();
  }
}

// Function to control backward movement
BLYNK_WRITE(V1) {
  int value = param.asInt();
  if (value) {
    digitalWrite(MOTOR_A_PIN1, LOW);
    digitalWrite(MOTOR_A_PIN2, HIGH);
    digitalWrite(MOTOR_B_PIN1, LOW);
    digitalWrite(MOTOR_B_PIN2, HIGH);
    Serial.println("Function to control backward movement");

  } else {
    stopCar();
  }
}

// Function to control left movement
BLYNK_WRITE(V3) {
  int value = param.asInt();
  if (value) {
    digitalWrite(MOTOR_A_PIN1, HIGH);
    digitalWrite(MOTOR_A_PIN2, LOW);
    digitalWrite(MOTOR_B_PIN1, LOW);
    digitalWrite(MOTOR_B_PIN2, HIGH);
    Serial.println("Function to control left movement");

  } else {
    stopCar();
  }
}

// Function to control right movement
BLYNK_WRITE(V2) {
  int value = param.asInt();
  if (value) {
    digitalWrite(MOTOR_A_PIN1, LOW);
    digitalWrite(MOTOR_A_PIN2, HIGH);
    digitalWrite(MOTOR_B_PIN1, HIGH);
    digitalWrite(MOTOR_B_PIN2, LOW);
    Serial.println("Function to control right movement");

  } else {
    stopCar();
  }
}

// Function to stop the car
void stopCar() {
  digitalWrite(MOTOR_A_PIN1, LOW);
  digitalWrite(MOTOR_A_PIN2, LOW);
  digitalWrite(MOTOR_B_PIN1, LOW);
  digitalWrite(MOTOR_B_PIN2, LOW);
  Serial.println("Function to stop");

}

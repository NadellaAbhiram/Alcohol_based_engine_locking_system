// Pin definitions
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

/* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
//#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const int sensorPin = A0;  // Analog input pin for MQ-3 sensor
const int ledPin = 13;     // Digital output pin for LED
int enB = 5;
int in3 = 7;
int in4 = 6;
int buzzer = 4;
// Threshold for alcohol concentration (adjust as needed)
const int thresholdValue = 400; // Example threshold value

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  pinMode(sensorPin, INPUT);  // Set sensor pin as input
  pinMode(ledPin, OUTPUT);     // Set LED pin as output
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(buzzer,OUTPUT);
  display.begin(i2c_Address, true);
  display.clearDisplay();
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(32, 32);
  display.println("ALCOHOL");
  display.display();
  delay(1000); 
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(32, 32);
  display.println("BASED");
  display.display();
  delay(1000); 
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(32, 32);
  display.println("ENGINE");
  display.display();
  delay(1000); 
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(32, 32);
  display.println("LOCKING");
  display.display();
  delay(1000); 
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(32, 32);
  display.println("SYSTEM");
  display.display();
  delay(1000); 
}
void loop() {
  // Read analog value from sensor

  int sensorValue = analogRead(sensorPin);

  // Convert analog value to alcohol concentration
  float alcoholConcentration = map(sensorValue, 0, 1023, 0, 100); // Example mapping

  // Print alcohol concentration to serial monitor
  Serial.print("Alcohol Concentration: ");
  Serial.print(sensorValue);
  Serial.println("%");
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 32);
  display.println("Alcohol Concentration: ");
  display.println(sensorValue);
  display.display();
  delay(1000); 

  // Check if alcohol concentration exceeds threshold
  if (sensorValue > thresholdValue) {
    digitalWrite(ledPin, HIGH);  // Turn on LED
    Serial.println("Warning: Alcohol concentration exceeds threshold!");
    digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 0);
   tone(buzzer, 1000); // tone() is the main function to use with a buzzer, it takes 2 or 3 parameteres (buzzer pin, sound frequency, duration)
 delay(1000);
 tone(buzzer, 2000); // You can also use noTone() to stop the sound it takes 1 parametere which is the buzzer pin
 delay(1000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(15, 32);
  display.println("ENGINE LOCKED");
  display.display();
  delay(1000); 

  } 
  else {
    digitalWrite(ledPin, LOW); 
    digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);  // Turn off LED
  noTone(buzzer);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(15, 32);
  display.println("ENGINE UNLOCKED");
  display.display();
  delay(1000); 
 }
}
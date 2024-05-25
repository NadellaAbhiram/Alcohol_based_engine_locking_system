# Alcohol_based_engine_locking_system

  TABLE OF CONTENT
  Abstract 3
  1. Introduction 4
  2. Block diagram 5
  3. Hardware and Software Requirements 6
  References 7
  DEPARTMENT OF ECE, NMAMIT, NITTE 3
  ABSTRACT
  Drunk driving, a global concern, contributes significantly to road accidents, injuries, 
  and fatalities. This project presents the development of an engine locking system 
  integrated with an alcohol detection sensor, aiming to deter drunk driving and 
  improve road safety. By detecting driver intoxication exceeding a pre-determined 
  threshold, the system utilizes an engine immobilization mechanism to prevent 
  vehicle startup. Additionally, visual and audible alerts are implemented for 
  warnings, and data logging capabilities capture detection events. The project 
  involves selecting and integrating hardware components like the sensor, 
  microcontroller, and immobilization mechanism, alongside software development 
  for data acquisition, analysis, and control logic. While the successful project 
  contributes to potential road safety improvements, ethical considerations and legal 
  implications surrounding such technologies require further research and responsible 
  implementation.
  DEPARTMENT OF ECE, NMAMIT, NITTE 4
  INTRODUCTION
  Drunk driving, a global threat: Globally, drunk driving remains a significant 
  concern, responsible for countless accidents, injuries, and fatalities. This project 
  addresses this critical issue.
  Introducing the Alcohol-Interlock Engine Locking System: We present an alcoholbased engine locking system, a novel technology designed to deter drunk driving 
  and actively contribute to safer roads.
  Functionality: The system integrates an advanced alcohol detection sensor with an 
  engine immobilization mechanism. If the detected BAC exceeds a pre-set threshold, 
  the system immediately immobilizes the engine, preventing vehicle startup. This 
  decisive action discourages driving under the influence.
  Beyond Immobilization: Recognizing the importance of clear communication, the 
  system incorporates visual and audible alerts. Additionally, data logging capabilities 
  record alcohol detection events for further analysis.
  Ethical Considerations and a Responsible Approach: While celebrating the potential 
  of this technology, the project acknowledges the crucial need for ethical 
  considerations and responsible implementation. Careful examination of potential 
  legal implications and adherence to established regulations are crucial.
  DEPARTMENT OF ECE, NMAMIT, NITTE 5
  BLOCK DIAGRAM
  Fig. 1 Basic circuit of alcohol detection and engine wiring
  DEPARTMENT OF ECE, NMAMIT, NITTE 6
  HARDWARE AND SOFTWARE REQUIREMENTS
  1) Arduino Uno
  2) 16×2 LCD Display
  3) MQ -3 Sensor
  4) Sim800L Module
  5) Neo 6M GPS Module
  6) L293D Motor Driver
  7) BO Motor
  8) Buzzer
  9) Red LED
  10) Battery charging Module
  11) Switch
  12) Wheels
  Software:
  1)Arduino IDE (Integrated Development Environment)
  DEPARTMENT OF ECE, NMAMIT, NITTE 7
  REFERENCES
  [1] https://smartembeddedfriends.blogspot.com/2018/08/gps-tracker-and-alcohol-detector-withengine-locking-system-using-gsm.html
  [2] https://indiaaerotech.com/index.php/2023/11/23/alcohal-sensing-alert-with-engine-lockingsystem/
  [3]https://www.researchgate.net/publication/324314274_Alcohol_Detection_of_Drunk_Drivers_
with_Automatic_Car_Engine_Locking_System
[4]https://www.academia.edu/36833854/AUTOMATIC_ENGINE_LOCKING_SYSTEM_THR
OUGH_ALCOHOL_DETECTION_IN_ARDUINO_USING_IOT

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

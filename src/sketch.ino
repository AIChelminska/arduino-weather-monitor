// Arduino Weather Monitor
// Reads temperature and humidity from DHT22 on button press
// and displays data on 1.3" OLED screen via I2C

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define DHT_PIN 2
const int buttonPin = 8;
bool lastButtonState = HIGH;
DHT dht(DHT_PIN, DHT22);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);
  
  if(lastButtonState == HIGH && currentButtonState == LOW){
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.setTextColor(WHITE);
  
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
  
    display.print(F("Temperature: "));
    display.println(temperature);
    display.print(F("Humidity: "));
    display.println(humidity);
    display.display();
    
    delay(200);
  }

  lastButtonState = currentButtonState;
}

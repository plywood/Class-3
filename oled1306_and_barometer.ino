/*********************************************************************
This is an example for SSD1306 based 4 pin OLED 
and BME280 barometric pressure sensor 
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//#undef  SSD1306_128_32
//#define SSD1306_128_64

//#define SSD1306_LCDWIDTH    128
//#define SSD1306_LCDHEIGHT   64

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
// Barometer portion
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
Adafruit_BME280 bme; // I2C
#define SEALEVELPRESSURE_HPA (1013.25)

void setup()   {
  Serial.println("about to start");                
  Serial.begin(9600);
  if (!bme.begin(0x76)) {  
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
  // init done

  // Clear the buffer.
  display.clearDisplay();

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Hello, world!!!!!");
  display.display();
  delay(2000);

}

void loop() {
  float bp   = bme.readPressure();
  float t    = bme.readTemperature();
  float alt  = bme.readAltitude(1013.25);
  float mmHg = bp/133.322365;
  float hum  = bme.readHumidity();
  // Pressure is returned in the SI units of Pascals. 
  // 100 Pascals = 1 hPa = 1 millibar. Often times barometric pressure is reported in millibar or inches-mercury. 
  // For future reference 1 pascal =0.000295333727 inches of mercury, or 1 inch Hg = 3386.39 Pascal. 
  // So if you take the pascal value of say 100734 and divide by 3389.39 you'll get 29.72 inches-Hg.
  // 
  
  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize( 1);
  display.setTextColor(WHITE);
  
  display.setCursor(0,0);
  display.print(    "Pressure Pa");
  display.setCursor(80,0);
  display.print(    bp);
  
  display.setCursor(0,10);
  display.print(    "mm Hg");
  display.setCursor(80,10);
  display.print(    mmHg);


  display.setCursor(0,20);
  display.print(    "Temp C");
  display.setCursor(80,20);
  display.print(    t);

  display.setCursor(0,30);
  display.print(    "Altitude");
  display.setCursor(80,30);
  display.print(    alt);

  display.setCursor(0,40);
  display.print(    "Humidity");
  display.setCursor(80,40);
  display.print(    hum);
  
  
  display.display();
  delay(2000);
}








  

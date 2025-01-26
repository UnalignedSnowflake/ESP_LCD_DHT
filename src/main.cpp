#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include "DHT.h"

int lcdColumns = 16;
int lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

#define GPIO_PIN 19
#define DHT_TYPE DHT22

DHT dht(GPIO_PIN, DHT_TYPE);

void setup()
{
    Serial.begin(115200);

    lcd.init();

    dht.begin(); 

    lcd.backlight();
}

void loop()
{
    lcd.clear();
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
        lcd.setCursor(0, 0);
        lcd.print("Sensor Error");
    } else {
        lcd.setCursor(0, 0);
        lcd.printf("Humidity: %.1f%%", humidity);
        lcd.setCursor(0, 1);
        lcd.printf("Temp: %.1fC", temperature);
    }

    delay(5000);
}

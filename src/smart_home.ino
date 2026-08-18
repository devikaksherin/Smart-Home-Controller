#include "DHT.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

 // =====================================
// PIN DEFINITIONS
// =====================================

#define PIR_PIN 13
#define LDR_PIN 34
#define LIGHT_PIN 26

#define DHT_PIN 14
#define DHT_TYPE DHT22

#define FAN_PIN 25

#define SECURITY_LED 27
#define BUZZER_PIN 33
#define SECURITY_BUTTON 4

// =====================================
// THRESHOLDS
// =====================================

#define DARK_THRESHOLD 600

#define FAN_ON_TEMP 30
#define FAN_OFF_TEMP 28

// =====================================
// OLED DISPLAY
// =====================================

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

// =====================================
// DHT SENSOR
// =====================================

DHT dht(DHT_PIN, DHT_TYPE);

// =====================================
// SYSTEM VARIABLES
// =====================================

bool fanState = false;
bool securityMode = false;

int lastButtonState = HIGH;

unsigned long lastDisplayUpdate = 0;

bool displayPage = false;

// =====================================
// SETUP
// =====================================

void setup() {

  Serial.begin(115200);

  // Sensors
  pinMode(PIR_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);

  // Outputs
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(SECURITY_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Security button
  pinMode(SECURITY_BUTTON, INPUT_PULLUP);

  // Start DHT sensor
  dht.begin();

  // Start OLED
  Wire.begin(21, 22);

  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        0x3C
      )) {

    Serial.println("OLED NOT FOUND");

    while (true);
  }

  // Initial output states
  digitalWrite(LIGHT_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);
  digitalWrite(SECURITY_LED, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  // ===================================
  // STARTUP SCREEN
  // ===================================

  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(2);

  display.setCursor(8, 5);
  display.println("SMART");

  display.setCursor(8, 27);
  display.println("HOME");

  display.setTextSize(1);

  display.setCursor(28, 50);
  display.println("SYSTEM READY");

  display.display();

  delay(2500);

  display.clearDisplay();
  display.display();

  // ===================================
  // SERIAL STARTUP MESSAGE
  // ===================================

  Serial.println();
  Serial.println("==========================================");
  Serial.println("        SMART HOME CONTROLLER");
  Serial.println("==========================================");
  Serial.println("System Started");
  Serial.println("Security Mode: DISARMED");
  Serial.println("==========================================");
}

// =====================================
// MAIN LOOP
// =====================================

void loop() {

  // ===================================
  // READ SENSORS
  // ===================================

  int motion = digitalRead(PIR_PIN);

  int lightValue = analogRead(LDR_PIN);

  float temperature = dht.readTemperature();

  float humidity = dht.readHumidity();


  // ===================================
  // CHECK DHT SENSOR
  // ===================================

  if (isnan(temperature) || isnan(humidity)) {

    Serial.println("ERROR: DHT SENSOR READING FAILED!");

    delay(2000);

    return;
  }


  // ===================================
  // AUTOMATIC LIGHTING
  // ===================================

  bool lightState = false;

  if (
    lightValue > DARK_THRESHOLD &&
    motion == HIGH
  ) {

    lightState = true;

    digitalWrite(LIGHT_PIN, HIGH);

  } else {

    lightState = false;

    digitalWrite(LIGHT_PIN, LOW);
  }


  // ===================================
  // AUTOMATIC FAN
  // ===================================

  if (temperature >= FAN_ON_TEMP) {

    fanState = true;

  }

  else if (temperature <= FAN_OFF_TEMP) {

    fanState = false;
  }

  digitalWrite(
    FAN_PIN,
    fanState ? HIGH : LOW
  );


  // ===================================
  // SECURITY BUTTON
  // =====================================

  int buttonState =
    digitalRead(SECURITY_BUTTON);

  // Detect button press
  if (
    lastButtonState == HIGH &&
    buttonState == LOW
  ) {

    securityMode = !securityMode;

    if (securityMode) {

      Serial.println(
        "SECURITY MODE: ARMED"
      );

    }

    else {

      Serial.println(
        "SECURITY MODE: DISARMED"
      );

      digitalWrite(
        SECURITY_LED,
        LOW
      );

      digitalWrite(
        BUZZER_PIN,
        LOW
      );
    }

    delay(200);
  }

  lastButtonState = buttonState;


  // ===================================
  // SECURITY ALARM
  // ===================================

  bool alarmState = false;

  if (
    securityMode &&
    motion == HIGH
  ) {

    alarmState = true;

    digitalWrite(
      SECURITY_LED,
      HIGH
    );

    digitalWrite(
      BUZZER_PIN,
      HIGH
    );

  }

  else {

    alarmState = false;

    digitalWrite(
      SECURITY_LED,
      LOW
    );

    digitalWrite(
      BUZZER_PIN,
      LOW
    );
  }


  // ===================================
  // SERIAL MONITOR
  // ===================================

  Serial.println();
  Serial.println("------------------------------------------");

  Serial.print("Temperature : ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity    : ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("LDR         : ");
  Serial.println(lightValue);

  Serial.print("Motion      : ");

  if (motion == HIGH) {

    Serial.println("DETECTED");

  } else {

    Serial.println("NOT DETECTED");
  }

  Serial.print("Light       : ");

  if (lightState) {

    Serial.println("ON");

  } else {

    Serial.println("OFF");
  }

  Serial.print("Fan         : ");

  if (fanState) {

    Serial.println("ON");

  } else {

    Serial.println("OFF");
  }

  Serial.print("Security    : ");

  if (securityMode) {

    Serial.println("ARMED");

  } else {

    Serial.println("DISARMED");
  }

  Serial.print("Alarm       : ");

  if (alarmState) {

    Serial.println("ON");

  } else {

    Serial.println("OFF");
  }

  Serial.println("------------------------------------------");


  // ===================================
  // OLED DISPLAY
  // ===================================

  if (
    millis() - lastDisplayUpdate >= 2000
  ) {

    lastDisplayUpdate = millis();

    displayPage = !displayPage;

    display.clearDisplay();

    display.setTextColor(
      SSD1306_WHITE
    );


    // =================================
    // OLED PAGE 1
    // =================================

    if (!displayPage) {

      display.setTextSize(1);

      display.setCursor(25, 0);

      display.println("SMART HOME");

      display.drawLine(
        0, 10,
        127, 10,
        SSD1306_WHITE
      );


      display.setCursor(0, 18);

      display.print("Temp : ");

      display.print(
        temperature,
        1
      );

      display.println(" C");


      display.setCursor(0, 30);

      display.print("Hum  : ");

      display.print(
        humidity,
        0
      );

      display.println(" %");


      display.setCursor(0, 42);

      display.print("Light: ");

      if (lightState) {

        display.println("ON");

      } else {

        display.println("OFF");
      }


      display.setCursor(0, 54);

      display.print("Motion: ");

      if (motion == HIGH) {

        display.println("YES");

      } else {

        display.println("NO");
      }
    }


    // =================================
    // OLED PAGE 2
    // =================================

    else {

      display.setTextSize(1);

      display.setCursor(25, 0);

      display.println("SMART HOME");

      display.drawLine(
        0, 10,
        127, 10,
        SSD1306_WHITE
      );


      display.setCursor(0, 18);

      display.print("Fan     : ");

      if (fanState) {

        display.println("ON");

      } else {

        display.println("OFF");
      }


      display.setCursor(0, 30);

      display.print("Security: ");

      if (securityMode) {

        display.println("ARMED");

      } else {

        display.println("OFF");
      }


      display.setCursor(0, 42);

      display.print("Alarm   : ");

      if (alarmState) {

        display.println("ON");

      } else {

        display.println("OFF");
      }


      display.setCursor(0, 54);

      display.println("System  : OK");
    }


    display.display();
  }


  delay(100);
}

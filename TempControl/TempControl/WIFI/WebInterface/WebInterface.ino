#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <GyverMAX6675.h>
#include "GyverPID.h"
#include <GyverPortal.h>

#include "config.h"

GyverPortal ui;
TaskHandle_t Task0;
GyverMAX6675< CLK_PIN, DATA_PIN, CS_PIN > sens;
LiquidCrystal_I2C lcd(0x27, 16, 2);

struct Flag {
  uint8_t bit_map_flag, wifi_connect_flag, start_heating_flag;
} flag{ .bit_map_flag = 0, .wifi_connect_flag = 0, .start_heating_flag = 0 };

struct Value {
  int temp, SetTemp;
} val{ .temp = 0, .SetTemp = 0 };

struct Time {
  unsigned long startMillis;
} times{ .startMillis = 0 };


const char* names[] = {
  "temp", "humidity", "kek"
};

// конструктор страницы
void bitMap(void) {
  lcd.setCursor(0, 0);
  lcd.print("Real:");

  lcd.setCursor(9, 0);
  lcd.print("Tim:");

  lcd.setCursor(0, 1);
  lcd.print("Set:");
}

void build() {
  GP.BUILD_BEGIN();
  GP.THEME(GP_DARK);

  GP.BUTTON("btn1", "I'm connect");

  GP.TITLE("Temperature control", "t1");
  GP.HR();

  GP.AJAX_PLOT_DARK("plot3", names, 3, 20, 1000);

  GP.LABEL("Real temperature: ");
  GP.LABEL("NAN", "val");
  GP.BREAK();

  GP.NUMBER("num", "Set value", val.SetTemp);
  GP.BREAK();

  GP.BUTTON("btn", "Start heating");

  GP.BUILD_END();
}

void core0(void* pvParameters) {
  // ==========SETUP===========

  // ============LOOP===========
  for (;;) {
    if (!flag.wifi_connect_flag) {
      if (WiFi.status() == WL_CONNECTED) {
        lcd.setCursor(6, 0);
        lcd.print(String(WiFi.localIP()));
        delay(5000);
        flag.wifi_connect_flag = 1;
      }
    }
    if (flag.wifi_connect_flag) {
      if (!flag.bit_map_flag) {
        bitMap();
        flag.bit_map_flag = 1;
      }
      if (millis() - interval2 > times.startMillis) {
        if (sens.readTemp()) {
          val.temp = sens.getTempInt();
          lcd.setCursor(6, 0);
          lcd.print(String(val.temp));
        }
        times.startMillis = millis();
      }
    }
    delay(200);
  }
}

void action() {
  // был клик по компоненту
  if (ui.click()) {
    // проверяем компоненты и обновляем переменные

    if (ui.clickInt("num", val.SetTemp)) {
      Serial.print("Number: ");
      Serial.println(val.SetTemp);
    }

    if (flag.start_heating_flag) {
      if (ui.update("plot3")) {
        int answ[] = { val.temp, val.SetTemp, random(200) };
        ui.answer(answ, 3);
      }
    }
    if (ui.click("btn1")) {
      Serial.println("Button click Temp= " + String(val.temp));
      digitalWrite(GREEN_LED_PIN, !digitalRead(GREEN_LED_PIN));
    }

    if (ui.click("btn")) {
      Serial.println("Button start");
      digitalWrite(RED_LED_PIN, !digitalRead(RED_LED_PIN));
      flag.start_heating_flag = 1;
    }
  }
}

void setup() {
  // init core 0
  xTaskCreatePinnedToCore(core0, "Task0", 10000, NULL, 1, &Task0, 0);
  // init time in firct line
  times.startMillis = millis();
  // init UART with 115200 bout rate
  Serial.begin(115200);
  // init WIFI
  WiFi.mode(WIFI_STA);
  WiFi.begin(AP_SSID, AP_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
  // initialize the lcd
  lcd.init();
  lcd.backlight();
  bitMap();  //print static information
             // init pin
  pinMode(PWM_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  // set pin
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);

  // conetct and start site info
  ui.attachBuild(build);
  ui.attach(action);
  ui.start();
}

void loop() {
  ui.tick();
}
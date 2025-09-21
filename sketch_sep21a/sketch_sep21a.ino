#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Wi-Fi credentials
const char* ssid = "MMR_L2";
const char* password = "Madhan25";

// Flask server details
const char* flaskServerIP = "192.168.29.254:5000"; // Replace with your computer's IP
const int flaskPort = 5000;
const char* updateEndpoint = "/update_status";

// Pin definitions
const int RELAY_PIN = 26;
const int BUTTON_PIN = 27;
const int BUZZER_PIN = 25; // New pin for the buzzer

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// State variables
bool relayState = false; // false = OFF, true = ON
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(115200);

  // Pin setup
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT); // Set buzzer pin as an output
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // OLED setup
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(0.5);
  display.setTextColor(WHITE);
  updateOLED();

  // Connect to Wi-Fi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Read button state
  int currentButtonState = digitalRead(BUTTON_PIN);

  // Debounce logic
  if (currentButtonState != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (currentButtonState == LOW) {
      // Button was pressed, toggle relay state
      relayState = !relayState;
      digitalWrite(RELAY_PIN, relayState ? HIGH : LOW);
      
      // Provide a brief buzzer sound
      digitalWrite(BUZZER_PIN, HIGH);
      delay(100);
      digitalWrite(BUZZER_PIN, LOW);

      // Update OLED display and send JSON
      updateOLED();
      sendJSONtoFlask(relayState ? "ON" : "OFF");
    }
  }

  lastButtonState = currentButtonState;
}

void updateOLED() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Relay Status:");
  display.setTextSize(1);
  display.setCursor(0, 30);
  display.println(relayState ? "ON" : "OFF");
  display.display();
}

void sendJSONtoFlask(const char* status) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String serverUrl = "http://" + String(flaskServerIP) + ":" + String(flaskPort) + String(updateEndpoint);

    http.begin(serverUrl.c_str());
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<200> doc;
    doc["status"] = status;

    String jsonString;
    serializeJson(doc, jsonString);

    int httpResponseCode = http.POST(jsonString);

    if (httpResponseCode > 0) {
      Serial.printf("[HTTP] POST... code: %d\n", httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpResponseCode).c_str());
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}
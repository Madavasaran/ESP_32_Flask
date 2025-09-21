# ESP32 IoT Relay Controller with Flask Web UI

## Project Overview

This project demonstrates a simple yet powerful Internet of Things (IoT) system using an **ESP32** microcontroller, a **relay**, a **push button**, a **buzzer**, and an **OLED display**. The system allows you to physically control a relay and view its status locally on the OLED. The ESP32 also acts as an IoT device, sending the relay's status to a **Flask** web application.

The web application provides a modern, real-time user interface that displays the relay's status without needing a page refresh, making it a responsive and user-friendly solution.

## Key Features

* **Physical Control:** A push button connected to the ESP32 toggles the relay's state.
* **Local Status Display:** An OLED screen provides immediate visual feedback of the relay's ON/OFF status.
* **Audible Feedback:** A buzzer provides an audible cue whenever the relay state changes.
* **Real-time Web UI:** A Flask web server receives status updates from the ESP32 and displays them on a clean, dynamic webpage. The UI updates in real-time using JavaScript without a full page reload.
* **JSON Communication:** The ESP32 sends status data to the Flask app using lightweight JSON payloads over HTTP POST requests.

## Components Used

* **Microcontroller:** ESP32 DevKitC
* **Relay Module:** 5V Relay Module
* **Display:** 0.96-inch I²C OLED Display (SSD1306)
* **Input:** Push Button
* **Audio:** Passive or Active Buzzer
* **Software:** Arduino IDE for ESP32, Python 3 with Flask

## Circuit Diagram



**Pinout Summary:**

* **Relay IN:** GPIO 26
* **Button:** GPIO 27 (with internal pull-up)
* **Buzzer:** GPIO 25
* **OLED (I²C):** SDA (GPIO 21), SCL (GPIO 22)

## Setup and Installation

### 1. ESP32 Code (Arduino IDE)

1.  Open the Arduino IDE and install the required libraries via the Library Manager: `Adafruit_SSD1306`, `Adafruit_GFX`, and `ArduinoJson`.
2.  Copy the code from `esp32_code.ino` into your Arduino sketch.
3.  Modify the Wi-Fi credentials (`ssid` and `password`).
4.  Update the Flask server IP address (`flaskServerIP`) to match your computer's local IP address.
5.  Upload the code to your ESP32 board.

### 2. Flask Web App (Python)

1.  Make sure you have Python 3 installed.
2.  Install Flask using pip:
    ```sh
    pip install Flask
    ```
3.  Create a folder named `templates` in the same directory as your `app.py`.
4.  Save the provided HTML content as `index.html` inside the `templates` folder.
5.  Run the Flask application from your terminal:
    ```sh
    python app.py
    ```

### 3. Usage

1.  Ensure your ESP32 and the computer running the Flask app are on the same Wi-Fi network.
2.  Access the web interface by navigating to `http://<YOUR_COMPUTER_IP_ADDRESS>:5000` in your web browser.
3.  Press the physical push button connected to the ESP32. You will hear a beep, see the OLED display update, and the web UI will change in real-time!

## Code Files

* `esp32_code.ino`: The complete code for the ESP32 microcontroller.
* `app.py`: The Python script for the Flask web server.
* `templates/index.html`: The HTML file for the web UI with real-time updates via JavaScript.

---


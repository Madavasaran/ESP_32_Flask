from flask import Flask, render_template, request, jsonify

app = Flask(__name__)

# Global variable to store the relay status
relay_status = "OFF"

@app.route('/')
def index():
    """
    Renders the main HTML page.
    """
    return render_template('index.html', relay_status=relay_status)

@app.route('/update_status', methods=['POST'])
def update_status():
    """
    Handles the incoming JSON data from the ESP32.
    """
    global relay_status
    if request.is_json:
        data = request.get_json()
        status_from_esp32 = data.get('status')
        if status_from_esp32:
            relay_status = status_from_esp32
            print(f"Received status update from ESP32: {relay_status}")
            return jsonify({"success": True}), 200
        else:
            return jsonify({"success": False, "message": "No 'status' field found in JSON."}), 400
    else:
        return jsonify({"success": False, "message": "Request body must be JSON."}), 400

@app.route('/get_status')
def get_status():
    """
    Provides the current status as a JSON object.
    """
    global relay_status
    return jsonify({"status": relay_status})

if __name__ == '__main__':
    # Run the Flask app on the local network (host='0.0.0.0')
    app.run(host='0.0.0.0', port=5000)
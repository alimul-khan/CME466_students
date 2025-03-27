from flask import Flask, request, jsonify, render_template

app = Flask(__name__)

# Stores last received temperature & humidity from each ESP
sensor_data = {}

# Stores pending commands for each ESP
commands = {}

print(f'use this link: http://127.0.0.1:5000/node/id')
@app.route('/')
def home():
    return "Use /node/<chip_id> to access specific ESP8266 pages."

# Dynamic page for each ESP8266
@app.route('/node/<chip_id>')
def node_page(chip_id):
    return render_template('node.html', chip_id=chip_id)

# Trigger temperature request for specific ESP
@app.route('/trigger_temp')
def trigger_temp():
    chip_id = request.args.get("chip_id")
    if not chip_id:
        return jsonify({"error": "chip_id is required"}), 400
    commands[chip_id] = "get_temp"
    return jsonify({"status": f"Temperature request sent to {chip_id}"})

# Trigger humidity request for specific ESP
@app.route('/trigger_humidity')
def trigger_humidity():
    chip_id = request.args.get("chip_id")
    if not chip_id:
        return jsonify({"error": "chip_id is required"}), 400
    commands[chip_id] = "get_humidity"
    return jsonify({"status": f"Humidity request sent to {chip_id}"})

# ESP checks if there is a command for it
@app.route('/command')
def get_command():
    chip_id = request.args.get("chip_id")
    if not chip_id:
        return jsonify({"error": "chip_id is required"}), 400
    
    if chip_id in commands:
        command = commands.pop(chip_id)  # Retrieve and remove the command
        return jsonify({"command": command})
    return jsonify({"command": "none"})

# Retrieves temperature data for a specific ESP
@app.route('/get_temp')
def get_temp():
    chip_id = request.args.get("chip_id")
    if not chip_id or chip_id not in sensor_data:
        return jsonify({"temperature": "No data received"})
    return jsonify({"temperature": sensor_data[chip_id].get("temperature", "No data")})

# ESP sends temperature data to the server
@app.route('/send_temp', methods=['POST'])
def send_temp():
    chip_id = request.args.get("chip_id")
    if not chip_id:
        return jsonify({"error": "chip_id is required"}), 400

    temp = request.json.get("temperature", "No data")
    if chip_id not in sensor_data:
        sensor_data[chip_id] = {}
    sensor_data[chip_id]["temperature"] = temp
    return jsonify({"status": "OK", "received": temp})

# Retrieves humidity data for a specific ESP
@app.route('/get_humidity')
def get_humidity():
    chip_id = request.args.get("chip_id")
    if not chip_id or chip_id not in sensor_data:
        return jsonify({"humidity": "No data received"})
    return jsonify({"humidity": sensor_data[chip_id].get("humidity", "No data")})

# ESP sends humidity data to the server
@app.route('/send_humidity', methods=['POST'])
def send_humidity():
    chip_id = request.args.get("chip_id")
    if not chip_id:
        return jsonify({"error": "chip_id is required"}), 400

    humidity = request.json.get("humidity", "No data")
    if chip_id not in sensor_data:
        sensor_data[chip_id] = {}
    sensor_data[chip_id]["humidity"] = humidity
    return jsonify({"status": "OK", "received": humidity})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)

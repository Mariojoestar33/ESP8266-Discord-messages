from flask import Flask, jsonify
import time
from flux_led import WifiLedBulb

app = Flask(__name__)

bulbipaddress = "192.168.1.66"
bulb = WifiLedBulb(bulbipaddress)

@app.route('/bulbon', methods=['GET'])
def bulbon():
    bulb.turnOn()
    return jsonify(status="Bulb turned on")

@app.route('/bulboff', methods=['GET'])
def bulboff():
    bulb.turnOff()
    return jsonify(status="Bulb turned off")

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)

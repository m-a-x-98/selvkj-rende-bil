from flask import Flask, jsonify
from flask_cors import CORS
from flask import request
import socket
from gpiozero import LED
import time
from datetime import date

hostname = socket.gethostname()
local_ip = socket.gethostbyname(hostname)

# Autodrive is either HIGH or LOW, TRUE or FALSE


app = Flask(__name__)
CORS(app=app)

def write_log(rawContent, aip = None):
    if aip == None:
        ip = request.remote_addr
    else:
        ip = aip
    with open("log.txt", "a") as f:
        content = str(date.today()) + " " + time.strftime('%H:%M:%S', time.localtime()) + " => " + rawContent + " [" + ip + "] " + "\n"
        f.write(str(content))
        f.close()

try:
    autoDrive = LED(17)
except:
    write_log("Failed to register pins, likely beacuse the script is not running on a rasperry pi with pins", aip="N/A")
    pass

@app.route("/verify", methods=["GET"])
def verify():
    write_log("Verified access")
    return jsonify({"ip": request.remote_addr, "status": 200}), 200


@app.route("/drive/auto/on", methods=["GET"])
def auto_on():
    try:
        autoDrive.on()
        write_log("Turned on auto driver")
        return jsonify({"status": 200}), 200
    except:
        write_log("Failed to turn on auto driver, could the script not be running on a raspberry pi machine?")
        return jsonify({"status": 500}), 500    

@app.route("/drive/auto/off", methods=["GET"])
def auto_off():
    try:
        autoDrive.off()
        write_log("Turned off auto driver")
        return jsonify({"status": 200}), 200
    except:
        write_log("Failed to turn on auto driver, could the script not be running on a raspberry pi machine?")
        return jsonify({"status": 500}), 500    

@app.route("/drive/right", methods=["GET"])
def drive_right():
    try:
        return jsonify({"status": 200}), 200
    except:
        return jsonify({"status": 500}), 500


@app.errorhandler(404)
def page_not_found(error):
    write_log("Encountered a 404")
    return jsonify({"error": str(error), "status": 404}), 404


if __name__ == "__main__":
    write_log("\n" + "\n" + "Started server [V.0.7]. If the ip following is not a 192.168 adress, consider checking ifconfig wlan0", aip=local_ip)
    app.run(host='0.0.0.0')
    pass

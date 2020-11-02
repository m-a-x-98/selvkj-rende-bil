from flask import Flask, jsonify
from flask import request
import socket
import gpiozero

hostname = socket.gethostname()
local_ip = socket.gethostbyname(hostname)
print(local_ip)

app = Flask(__name__)


@app.route("/verify", methods=["GET"])
def verify():
    return jsonify({"ip": request.remote_addr, "status": 200})


@app.route("/drive/right", methods=["GET"])
def drive_right():
    try:
        print("went right")
        return jsonify({"status": 200})
    except:
        return jsonify({"status": 500})


@app.errorhandler(404)
def page_not_found(error):
    return jsonify({"error": str(error), "status": 404})


if __name__ == "__main__":
    app.run(host=local_ip)
    pass

from flask import Flask, jsonify

app = Flask(__name__)

@app.route("/")
def fourofour():
    return jsonify({"statusCode": "404", "message":"not found"})


if __name__ == "__main__":
    app.run(host='0.0.0.0')
    pass
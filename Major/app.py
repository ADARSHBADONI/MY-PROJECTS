from flask import Flask,request,render_template
# from flask_mail import Mail, Message
import pickle
import pandas as pd
import requests
import json

app=Flask(__name__)

@app.route('/bySensors')
def bySensors():
# AUTH_TOKEN = 'lniaVK2UK-idf6zhxy7RrHb-oJvuWEv4'

    VIRTUAL_PINS = ['v5', 'v6', 'v7']
    dataL = []
    model = pickle.load(open('exp/finalized_model.pkl', 'rb'))

    for pin in VIRTUAL_PINS:
        url = f'https://blynk.cloud/external/api/get?token=lniaVK2UK-idf6zhxy7RrHb-oJvuWEv4&pin={pin}'
        response = requests.get(url)

        if response.status_code == 200:
            data = response.json()
            print(f"Data from {pin}: {data}")
            dataL.append(data)

        else:
            return f"Failed to get data from {pin}, response code: {response.status_code}"

    dataS = {"Methane": [float(dataL[0])], "Temperature": [float(dataL[1])], "Humidity": [float(dataL[2])]}
    predicted_days = int(model.predict(pd.DataFrame.from_dict(dataS))[0])
    if predicted_days < 1:
        return render_template("spoiled.html")
    else:
        return render_template("predict.html", days = predicted_days)


@app.route('/byUser', methods = ['GET', 'POST'])
def byUser():
    if request.method == 'POST':
        methane = request.form['methane']
        temperature = request.form['temperature']
        humidity = request.form['humidity']

        model = pickle.load(open('exp/finalized_model.pkl', 'rb'))

        data = {"Methane": [float(methane)], "Temperature": [float(temperature)], "Humidity": [float(humidity)]}

        predicted_days = int(model.predict(pd.DataFrame.from_dict(data))[0])


        if predicted_days < 1:
            return render_template("spoiled.html")
            
        else: 
            return render_template("Predict.html",days=predicted_days)

    return 'Submit your form data'


@app.route('/manual')
def manual():
    return render_template("Manually.html")

@app.route('/fetch')
def fetch():
    return render_template("Sensor.html")

@app.route('/')
def index():
    return render_template("home.html")

if __name__ == '__main__':
    app.run(debug=True)

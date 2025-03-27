#ifndef MYSERVER_HTML_H
#define MYSERVER_HTML_H

const char HTML_HEAD[] PROGMEM = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP8266 Weather Dashboard</title>
    <style>
      body {
        margin: 0;
        font-family: 'Segoe UI', sans-serif;
        background: linear-gradient(to right, #83a4d4, #b6fbff);
        display: flex;
        flex-direction: column;
        align-items: center;
        justify-content: center;
        height: 100vh;
        color: #333;
      }
      .card {
        background: white;
        padding: 30px;
        border-radius: 12px;
        box-shadow: 0 4px 15px rgba(0,0,0,0.2);
        text-align: center;
        max-width: 300px;
        width: 90%;
      }
      h1 {
        margin-top: 0;
        color: #0077aa;
      }
      .value {
        font-size: 2.2em;
        margin: 10px 0;
      }
      .label {
        font-size: 1.1em;
        color: #555;
      }
    </style>
  </head>
  <body>
    <div class="card">
      <h1>ESP8266 Weather</h1>
      <div class="value" id="humidity">--</div>
      <div class="label">Humidity (%)</div>
      <div class="value" id="temperatureC">--</div>
      <div class="label">Temperature (°C)</div>
      <div class="value" id="temperatureF">--</div>
      <div class="label">Temperature (°F)</div>
    </div>
)rawliteral";

const char HTML_SCRIPT[] PROGMEM = R"rawliteral(
    <script>
      function fetchData() {
        fetch("/data")
          .then(response => response.json())
          .then(data => {
            document.getElementById("humidity").textContent = data.humidity.toFixed(2);
            document.getElementById("temperatureC").textContent = data.temperatureC.toFixed(2);
            document.getElementById("temperatureF").textContent = data.temperatureF.toFixed(2);
          });
      }
      setInterval(fetchData, 2000);
      fetchData();
    </script>
  </body>
  </html>
)rawliteral";

#endif

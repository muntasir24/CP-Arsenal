#include <WiFi.h>
#include <SPIFFS.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>


const char* ssid = "The Hotspot";
const char* password = "newtown123";

// CallMeBot API details
const char* phone_number = "+8801305400421";  // Replace with your phone number (include country code)
const char* api_key = "3362013";  // Replace with your API key from CallMeBot

WebServer server(80);
String medicineData = "[]";  // Default empty array for medicine records

// Variables to store the alarm times for Slot 1 and Slot 2
int slot1Hour = -1, slot1Minute = -1;
int slot2Hour = -1, slot2Minute = -1;



void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 16, 17); // RX = GPIO16, TX = GPIO17
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("ESP32 Server IP: ");
  Serial.println(WiFi.localIP());

  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }

  // Clear stored data at startup
  SPIFFS.remove("/medicine.json");

  loadMedicineData();

  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", generateHTML());
  });

  server.on("/update", HTTP_POST, []() {
    if (server.hasArg("plain")) {
      medicineData = server.arg("plain");
      saveMedicineData(medicineData);
      Serial.println("Updated Medicine Data:");
      Serial.println(medicineData);
      checkTotalValues();  // Check for total values and send WhatsApp message
    }
    server.send(200, "text/plain", "Data updated");
  });

  server.on("/data", HTTP_GET, []() {
    server.send(200, "application/json", medicineData);
  });
  server.on("/setAlarm", HTTP_POST, handleSetAlarm);
  server.begin();
}

// Function to handle the /setAlarm route
void handleSetAlarm() {
  // Get the JSON payload from the request
  String jsonBody = server.arg("plain");

  // Parse the incoming JSON
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, jsonBody);

  String slot = doc["slot"];
  int hour = doc["hour"];
  int minute = doc["minute"];

  // Print the received alarm time on Serial Monitor
  if (slot == "slot1") {
    slot1Hour = hour;
    slot1Minute = minute;
    //Serial1.println(slot1Hour);
     //Serial1.println(slot1Minute);
     // Send Slot 1 data (identifier, hour, minute)
  Serial1.println("slot1");  // Slot identifier
  Serial1.println(slot1Hour);  // Send hour for Slot 1
  Serial1.println(slot1Minute);  // Send minute for Slot 1
  
    Serial.print("Alarm for Slot 1: ");
    Serial.print(slot1Hour);
    Serial.print(":");
    Serial.println(slot1Minute);
  } else if (slot == "slot2") {
    slot2Hour = hour;
    slot2Minute = minute;
    Serial.print("Alarm for Slot 2: ");
    Serial.print(slot2Hour);
     //Serial1.println(slot2Hour);
     //Serial1.println(slot2Minute);
      // Send Slot 2 data (identifier, hour, minute)
  Serial1.println("slot2");  // Slot identifier
  Serial1.println(slot2Hour);  // Send hour for Slot 2
  Serial1.println(slot2Minute);  // Send minute for Slot 2

    Serial.print(":");
    Serial.println(slot2Minute);
  }

  // Respond back to the client
  server.send(200, "text/plain", "Alarm updated successfully");
}

void loop() {
  server.handleClient();
   if (Serial1.available()) {
    int receivedData = Serial1.parseInt(); // Read the incoming integer from Arduino
    int which=Serial1.parseInt(); 
    if (receivedData==911) {
      // Print the received data to Serial Monitor
      Serial.print("Received from Arduino: ");
      Serial.println(which);
      String msg="Grandfather forgot to take medicine for the ";
      sendWhatsAppMessage(msg, which);
      receivedData=-1;
    }
  }

}

void loadMedicineData() {
  File file = SPIFFS.open("/medicine.json", "r");
  if (!file) {
    Serial.println("No previous data found, initializing empty list.");
    medicineData = "[]";
    return;
  }
  medicineData = file.readString();
  file.close();
}

void saveMedicineData(String data) {
  File file = SPIFFS.open("/medicine.json", "w");
  if (!file) {
    Serial.println("Failed to save data!");
    return;
  }
  file.print(data);
  file.close();
}

void checkTotalValues() {
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, medicineData);
  
  for (size_t i = 0; i < doc.size(); i++) {
    int total = doc[i]["total"];
    bool sentMessage = doc[i]["sentMessage"] | false;  // Check if message was already sent
    
    if ((total == 1 || total == 0) && !sentMessage) {
      String medicineName = doc[i]["name"].as<String>();
      sendWhatsAppMessage(medicineName, total);

      // Mark the message as sent
      doc[i]["sentMessage"] = true;
    }
  }

  // Save updated data with sentMessage flag
  String updatedData;
  serializeJson(doc, updatedData);
  saveMedicineData(updatedData);
}

void sendWhatsAppMessage(String medicineName, int total) {
   String message;
  if(total==11 or total==12){
    if(total==11){
 message = medicineName + "morning!";

    }
    else{
   message = medicineName + "night!";
 
    }

  }
  else{
   message = medicineName + " left only for " + String(total) + " days.";
   
  }
  // URL encode the message
  String encodedMessage = urlencode(message);
  
  // Correct URL format
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + String(phone_number) + "&text=" + encodedMessage + "&apikey=" + String(api_key);
  
  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    Serial.print("WhatsApp Message Sent! Response code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("Error: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}

String urlencode(String str) {
  String encoded = "";
  char c;
  for (size_t i = 0; i < str.length(); i++) {
    c = str[i];
    if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
      encoded += c;
    } else {
      encoded += "%" + String(c, HEX);
    }
  }
  return encoded;
}


String generateHTML() {
  return R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>PillGuard : Grandpa's smart Pill assitant</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      text-align: center;
      background-color: #f8f9fa;
      margin: 20px;
    }
    h2 {
      color: #343a40;
    }
    table {
      width: 80%;
      margin: auto;
      border-collapse: collapse;
      background: white;
      box-shadow: 0px 0px 10px rgba(0, 0, 0, 0.1);
    }
    th, td {
      padding: 10px;
      border: 1px solid #ddd;
      text-align: center;
    }
    th {
      background-color: #007bff;
      color: white;
    }
    button {
      cursor: pointer;
      padding: 8px 12px;
      font-size: 16px;
      border: none;
      border-radius: 5px;
      margin-top: 10px;
    }
    .add-btn {
      background-color: #28a745;
      color: white;
      font-size: 20px;
      width: 40px;
      height: 40px;
      line-height: 40px;
      border-radius: 50%;
      text-align: center;
    }
    .update-btn {
      background-color: #ffc107;
      color: black;
    }
    input {
      padding: 5px;
      width: 100px;
      text-align: center;
    }
  </style>
  <script>
    let medicineData = [];

    function fetchData() {
      fetch('/data')
        .then(response => response.json())
        .then(data => {
          medicineData = data;
          renderTable();
        });
    }

    function addRow() {
      medicineData.push({ name: '', slot1: '', slot2: '', total: '', sentMessage: false });
      renderTable();
    }

    function updateField(index, key, value) {
      medicineData[index][key] = value;
    }

    function sendUpdate() {
      fetch('/update', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(medicineData)
      }).then(() => {
        alert("Data Updated!");
        fetchData(); // Refresh table
      });
    }

    function setAlarm(slot) {
      const hour = document.getElementById(slot + 'Hour').value;
      const minute = document.getElementById(slot + 'Minute').value;

      fetch('/setAlarm', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ slot: slot, hour: hour, minute: minute })
      }).then(response => response.text())
        .then(data => {
          alert('Alarm for ' + slot + ' set to ' + hour + ':' + minute);
        });
    }

    function renderTable() {
      let table = '<table><tr><th>S.N</th><th>Add Medicine</th><th>Slot 1</th><th>Slot 2</th><th>Total days</th><th>Update</th></tr>';
      
      if (medicineData.length === 0) {
        table += "<tr><td colspan='6'>No data available</td></tr>";
      } else {
        medicineData.forEach((item, index) => {
          table += `<tr>
            <td>${index + 1}</td>
            <td><input type='text' value='${item.name}' oninput='updateField(${index}, "name", this.value)'></td>
            <td><input type='text' value='${item.slot1}' oninput='updateField(${index}, "slot1", this.value)'></td>
            <td><input type='text' value='${item.slot2}' oninput='updateField(${index}, "slot2", this.value)'></td>
            <td><input type='number' value='${item.total}' oninput='updateField(${index}, "total", this.value)'></td>
            <td><button class='update-btn' onclick='sendUpdate()'>Update</button></td>
          </tr>`;
        });
      }

      table += "</table><br><button class='add-btn' onclick='addRow()'>+</button>";
      document.getElementById("table").innerHTML = table;
    }

    window.onload = function() {
      document.getElementById("table").innerHTML = '<table><tr><th>S.N</th><th>Add Medicine</th><th>Slot 1</th><th>Slot 2</th><th>Total</th><th>Update</th></tr></table><br><button class="add-btn" onclick="addRow()">+</button>';
      fetchData();
    };
  </script>
</head>
<body>
  <h2>PillGuard : Grandpa's smart Pill assitant</h2>
  <div id="table"></div>

  <h3>Set Alarm for Slot 1</h3>
  <input type="number" id="slot1Hour" placeholder="Hour" min="0" max="23">
  <input type="number" id="slot1Minute" placeholder="Minute" min="0" max="59">
  <button onclick="setAlarm('slot1')">Set Alarm for Slot 1</button>

  <h3>Set Alarm for Slot 2</h3>
  <input type="number" id="slot2Hour" placeholder="Hour" min="0" max="23">
  <input type="number" id="slot2Minute" placeholder="Minute" min="0" max="59">
  <button onclick="setAlarm('slot2')">Set Alarm for Slot 2</button>
</body>
</html>
)rawliteral";
}


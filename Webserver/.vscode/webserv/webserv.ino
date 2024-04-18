#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>

const int led = 13;
WebServer server(80);

void handleRoot() {
  if (server.method() != HTTP_GET)
    return;
  
  digitalWrite(led, 1);
  String html = "<!DOCTYPE html><html><head><title>Root Page</title>";
  html += "<style>";
  html += ".button {";
  html += "  background-color: #4CAF50; /* Green */";
  html += "  border: none;";
  html += "  color: white;";
  html += "  padding: 15px 32px;";
  html += "  text-align: center;";
  html += "  text-decoration: none;";
  html += "  display: inline-block;";
  html += "  font-size: 16px;";
  html += "  margin: 4px 2px;";
  html += "  cursor: pointer;";
  html += "}";
  html += ".frame {";
  html += "  display: flex;";
  html += "  justify-content: center;";
  html += "  align-items: center;";
  html += "}";
  html += "</style></head><body>";
  html += "<div class='frame'>";
  html += "<button id='button1' class='button' onclick='sendRequest(\"button1\")'>Button 1</button>";
  html += "<button id='button2' class='button' onclick='sendRequest(\"button2\")'>Button 2</button>";
  html += "</div>";
  html += "<div class='frame'>";
  html += "<button id='button3' class='button' onclick='sendRequest(\"button3\")'>Button 3</button>";
  html += "<button id='button4' class='button' onclick='sendRequest(\"button4\")'>Button 4</button>";
  html += "</div>";
  html += "<div class='frame'>";
  html += "<button id='button5' class='button' onclick='sendRequest(\"button5\")'>Button 5</button>";
  html += "<button id='button6' class='button' onclick='sendRequest(\"button6\")'>Button 6</button>";
  html += "</div>";
  html += "<div class='frame'>";
  html += "<button id='button7' class='button' onclick='sendRequest(\"button7\")'>Button 7</button>";
  html += "<button id='button8' class='button' onclick='sendRequest(\"button8\")'>Button 8</button>";
  html += "</div>";
  html += "<script>";
  html += "function sendRequest(buttonId) {";
  html += "  var button = document.getElementById(buttonId);";
  html += "  if (!button.disabled) {";
  html += "    button.disabled = true;"; // Disable the button after it's clicked
  html += "    console.log('request sent');";
  html += "    var xhr = new XMLHttpRequest();";
  html += "    xhr.open('GET', '/' + buttonId);";
  html += "    xhr.onload = function() {";
  html += "      button.disabled = false;";
  html += "    };";
  html += "    xhr.onerror = function() {";
  html += "      button.disabled = false;";
  html += "    };";
  html += "    xhr.send();";
  html += "  }";
  html += "}";
  html += "</script>";
  html += "</body></html>";
  server.send(200, "text/html", html);
  digitalWrite(led, 0);
}

void handleButton() {
  if (server.method() != HTTP_GET)
    return;

  String buttonId = server.uri();
  buttonId.remove(0, 1); // Remove the leading slash (/)
  
  Serial.print("Button ");
  Serial.print(buttonId);
  Serial.println(" pressed");
}

void handleNotFound() {
  if (server.method() != HTTP_GET)
    return;
  
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin("whatever", "12345678");
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println("whatever");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  // Route all button requests to handleButton function
  server.on("/button1", handleButton);
  server.on("/button2", handleButton);
  server.on("/button3", handleButton);
  server.on("/button4", handleButton);
  server.on("/button5", handleButton);
  server.on("/button6", handleButton);
  server.on("/button7", handleButton);
  server.on("/button8", handleButton);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  delay(2); // allow the cpu to switch to other tasks
}

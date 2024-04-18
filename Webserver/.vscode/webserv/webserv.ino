/**
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>
// #include <ESPmDNS.h>
#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#define USE_SERIAL Serial

const int led = 13;
WebServer server(80);

void handleRoot() {
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
  // Additional buttons
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
  html += "  button.disabled = true;"; // Disable the button after it's clicked
  html += "  var xhr = new XMLHttpRequest();";
  html += "  xhr.open('GET', '/' + buttonId);"; // Send a GET request to the server
  html += "  xhr.onload = function() {";
  html += "    button.disabled = false;"; // Re-enable the button after the request completes
  html += "  };";
  html += "  xhr.onerror = function() {"; // Handle request error
  html += "    button.disabled = false;"; // Re-enable the button in case of error
  html += "  };";
  html += "  xhr.send();";
  html += "}";
  html += "</script>";
  html += "</body></html>";
  server.send(200, "text/html", html);
  digitalWrite(led, 0);
}

void handleButton1() {
  Serial.println("button1pressed");
}

void handleButton2() {
  Serial.println("button2pressed");
}

void handleButton3() {
  Serial.println("button3pressed");
}

void handleButton4() {
  Serial.println("button4pressed");
}

void handleButton5() {
  Serial.println("button5pressed");
}

void handleButton6() {
  Serial.println("button6pressed");
}

void handleButton7() {
  Serial.println("button7pressed");
}

void handleButton8() {
  Serial.println("button8pressed");
}

void handleNotFound() {
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

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println("whatever");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // if (MDNS.begin("esp32")) {
  //   Serial.println("MDNS responder started");
  // }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("HTTP server started");
  server.on("/button1", handleButton1);
}

void loop(void) {
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks
}
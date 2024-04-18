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

bool button1Processing = false;
bool button2Processing = false;
// Define similar flags for other buttons if needed

void handleRoot()
{
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
  html += "  if (!button.disabled) {";   // Check if the button is already disabled (indicating a previous request)
  html += "    button.disabled = true;"; // Disable the button after it's clicked
  html += "    console.log('request sent');";
  html += "    var xhr = new XMLHttpRequest();";
  html += "    xhr.open('GET', '/' + buttonId);"; // Send a GET request to the server
  html += "    xhr.onload = function() {";
  html += "      button.disabled = false;"; // Re-enable the button after the request completes
  html += "    };";
  html += "    xhr.onerror = function() {"; // Handle request error
  html += "      button.disabled = false;"; // Re-enable the button in case of error
  html += "    };";
  html += "    xhr.send();";
  html += "  }";
  html += "}";
  html += "</script>";
  html += "</body></html>";
  server.send(200, "text/html", html);
  digitalWrite(led, 0);
}

void handleButton1()
{
  if (server.method() != HTTP_GET)
    return;
  Serial.println("button1pressed");
  delay(200);
}

void handleButton2()
{
  if (server.method() != HTTP_GET)
    return;
  Serial.println("button2pressed");
  delay(200);
}

void handleButton3()
{
  if (server.method() != HTTP_GET)
    return;
  Serial.println("button3pressed");
  delay(200);
}

void handleButton4()
{
  if (server.method() != HTTP_GET)
    return;

  Serial.println("button4pressed");
  delay(200);
}

void handleButton5()
{
  if (server.method() != HTTP_GET)
    return;

  Serial.println("button5pressed");
  delay(200);
}

void handleButton6()
{
  if (server.method() != HTTP_GET)
    return;

  Serial.println("button6pressed");
  delay(200);
}

void handleButton7()
{
  if (server.method() != HTTP_GET)
    return;

  Serial.println("button7pressed");
  delay(200);
}

void handleButton8()
{
  if (server.method() != HTTP_GET)
    return;

  Serial.println("button8pressed");
  delay(200);
}

void handleNotFound()
{
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
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void)
{
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin("whatever", "12345678");
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
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

  server.on("/inline", []()
            { server.send(200, "text/plain", "this works as well"); });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  server.on("/button1", handleButton1);
  server.on("/button2", handleButton2);
  server.on("/button3", handleButton3);
  server.on("/button4", handleButton4);
  server.on("/button5", handleButton5);
  server.on("/button6", handleButton6);
  server.on("/button7", handleButton7);
  server.on("/button8", handleButton8);
}

void loop(void)
{
  server.handleClient();
  delay(2); // allow the cpu to switch to other tasks
}
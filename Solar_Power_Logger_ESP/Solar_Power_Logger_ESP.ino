
// Load Wi-Fi library
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
String voltage = "0.00";
String lastChecked = "";
String readString;
// Replace with your network credentials
const char* ssid     = "Pickle Barrel";
const char* password = "m0987654321H";
bool change = false;
// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
const long utcOffsetInSeconds = -18000;
int timeHours;
// Assign output variables to GPIO pins
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  Serial.begin(9600);
  timeClient.begin();

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  timeClient.update();
  timeHours = timeClient.getHours() + 1;
  lastChecked = String(daysOfTheWeek[timeClient.getDay()]) + ", " + String(timeHours) + ":" + String(timeClient.getMinutes()) + ":" + String(timeClient.getSeconds());
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients



  while (Serial.available()) {
    delay(1);
    if (Serial.available() > 0) {
      char c = Serial.read();  //gets one byte from serial buffer

      readString += c; //makes the string readString
    }
    change = true;
  }
  if (change == true) {
    voltage = "";
    voltage = readString;
    readString = "";
    Serial.println(voltage);
    change = false;
  }



  if (client) {

    // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();



            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;} table, th, td { border:1px solid black; }</style></head>");

            // Web Page Heading
            client.println("<body><h1>ESP8266 Solar System Monitoring Panel</h1><hr><br>");

            // Display current state, and ON/OFF buttons for GPIO 5

            client.println("<table style=\"width:100%\"> <tr> <th>Solar Panel Num.</th> <th>Specs.</th> <th>Voltage</th> </tr> <tr> <td>001</td> <td>20W &nbsp;12V &nbsp;1.2A Max</td> <td id=\"voltage\">" + voltage + "V</td> </tr> </table>");
            client.println("<br><br><sub id=\"updated\">Last checked: " + lastChecked + "</sub>");


            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
    timeClient.update();
    timeHours = timeClient.getHours() + 1;
    lastChecked = String(daysOfTheWeek[timeClient.getDay()]) + ", " + String(timeHours) + ":" + String(timeClient.getMinutes()) + ":" + String(timeClient.getSeconds());
    Serial.print(daysOfTheWeek[timeClient.getDay()]);
    Serial.print(", ");
    Serial.print(timeClient.getHours());
    Serial.print(":");
    Serial.print(timeClient.getMinutes());
    Serial.print(":");
    Serial.println(timeClient.getSeconds());
    //Serial.println(timeClient.getFormattedTime());
  }

}

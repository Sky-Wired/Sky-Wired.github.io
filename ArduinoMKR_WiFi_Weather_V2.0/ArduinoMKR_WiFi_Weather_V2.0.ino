/*

  MKR1000 - MKR WiFi 1010 - MKR VIDOR 4000 WiFi RTC

  This sketch asks NTP for the Linux epoch and sets the internal Arduino MKR1000's RTC accordingly.

  created 08 Jan 2016

  by Arturo Guadalupi <a.guadalupi@arduino.cc>

  modified 26 Sept 2018

  http://arduino.cchttps://www.arduino.cc/en/Tutorial/WiFiRTC

  This code is in the public domain.

*/
#include <ArduinoJson.h>
//open weather map api key
String apiKey = "95611ed6705e02bf854f20b2fcd6c5c4";

//the city you want the weather for
String location = "02155,US";

char server[] = "api.openweathermap.org";

#include <MD_Parola.h>
#include <MD_MAX72xx.h>

#include <SPI.h>
#include <WiFi101.h>
//#include <WiFiNINA.h> //Include this instead of WiFi101.h as needed
#include <WiFiUdp.h>
#include <RTCZero.h>
String theTimeHours;
String theTimeMins;
RTCZero rtc;
WiFiClient client;
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = "Pickle Barrel";        // your network SSID (name)
char pass[] = "m0987654321H";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                           // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

const int GMT = 8; //change this to adapt it to your time zone


// Uncomment according to your hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

// Defining size, and output pins
#define MAX_DEVICES 8
#define CS_PIN 3

// Create a new instance of the MD_Parola class with hardware SPI connection
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

String currentDay;
int daysUntilWeekend;
String daysLeft;





void setup() {

  Serial.begin(115200);
  myDisplay.begin();

  // Set the intensity (brightness) of the display (0-15)
  myDisplay.setIntensity(1);
  myDisplay.setTextAlignment(PA_CENTER);
  // Clear the display
  myDisplay.print("Connecting...");

  // check if the WiFi module works

  if (WiFi.status() == WL_NO_SHIELD) {

    Serial.println("WiFi shield not present");

    // don't continue:

    while (true);

  }

  // attempt to connect to WiFi network:

  while ( status != WL_CONNECTED) {

    Serial.print("Attempting to connect to SSID: ");

    Serial.println(ssid);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:

    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:

    delay(5000);

  }

  // you're connected now, so print out the status:

  printWiFiStatus();

  rtc.begin();

  unsigned long epoch;

  int numberOfTries = 0, maxTries = 6;

  do {

    epoch = WiFi.getTime();

    numberOfTries++;

  }

  while ((epoch == 0) && (numberOfTries < maxTries));

  if (numberOfTries == maxTries) {

    Serial.print("NTP unreachable!!");

    while (1);

  }

  else {

    Serial.print("Epoch received: ");

    Serial.println(epoch);

    rtc.setEpoch(epoch);

    Serial.println();
    myDisplay.displayClear();
  }

}











void loop() {
  printDateAndTime();
  //printTime();
  printDaysTillWeekend();
  //printMessage();
  getWeather();

}






void printDaysTillWeekend() {
  Serial.print("Days till weekend: ");

  myDisplay.displayClear();
  Serial.println(daysUntilWeekend);
  if (daysUntilWeekend != 0) {
    if (daysUntilWeekend == 1) {
      daysLeft = String(daysUntilWeekend) + " day till the weekend!";
    } else {
      daysLeft = String(daysUntilWeekend) + " days till the weekend!";
    }
    String hi2 = daysLeft;
    const char *strHi2 = hi2.c_str();
    //myDisplay.print(theTime);

    myDisplay.displayText  (strHi2,
                            PA_CENTER,
                            50,
                            0,
                            PA_SCROLL_LEFT,
                            PA_SCROLL_LEFT
                           );
    while (1) {
      if (myDisplay.displayAnimate()) {
        myDisplay.displayReset();
        break;

      }

    }
  }
}


void printMessage() {
  myDisplay.displayClear();

  myDisplay.displayText  ("Enjoy Today!",
                          PA_CENTER,
                          60,
                          4000,
                          PA_SCROLL_DOWN,
                          PA_GROW_DOWN
                         );


  while (1) {
    if (myDisplay.displayAnimate()) {
      myDisplay.displayReset();
      break;

    }


  }
}


#define LEAP_YEAR(Y)     ( (Y>0) && !(Y%4) && ( (Y%100) || !(Y%400) ))     // from time-lib

int dayOfWeek(uint16_t year, uint8_t month, uint8_t day)
{
  uint16_t months[] = {
    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365
  };   // days until 1st of month

  uint32_t days = year * 365;        // days until year
  for (uint16_t i = 4; i < year; i += 4) if (LEAP_YEAR(i) ) days++;     // adjust leap years, test only multiple of 4 of course

  days += months[month - 1] + day;  // add the days of this year
  if ((month > 2) && LEAP_YEAR(year)) days++;  // adjust 1 if this year is a leap year, but only after febr

  return days % 7;   // remove all multiples of 7
}

int printTime()
{
  int timeHours = rtc.getHours() + GMT;



  if (timeHours > 12) {
    int the12hrTime = timeHours - 12;
    Serial.println(the12hrTime);
    theTimeHours = String(the12hrTime);
  } else if (timeHours < 10) {
    theTimeHours = "0" + String(timeHours);
  } else {
    theTimeHours = String(timeHours);
  }

  int timeMins = rtc.getMinutes();


  if (timeMins < 10) {
    theTimeMins = "0" + String(timeMins);
  } else {
    theTimeMins = String(timeMins);
  }


  String theTime = theTimeHours + " : " + theTimeMins;
  String hi = theTime;
  const char *strHi = hi.c_str();
  //myDisplay.print(theTime);

  myDisplay.displayText  (strHi,
                          PA_CENTER,
                          40,
                          5000,
                          PA_RANDOM,
                          PA_SCROLL_DOWN
                         );

  //myDisplay.displayScroll(strHi, PA_CENTER, PA_SCROLL_LEFT, 100);

  while (1) {
    if (myDisplay.displayAnimate()) {
      myDisplay.displayReset();
      break;
      return true;
    }
  }
}

int printDateAndTime()
{

  int dayDay = rtc.getDay();

  int dayMonth = rtc.getMonth();

  int dayYear = rtc.getYear();




  String theDate = String(dayMonth) + "/" + String(dayDay) + "/" + String(dayYear);


  //myDisplay.print(theTime);


  // myDisplay.displayScroll(strHi1, PA_CENTER, PA_WIPE_CURSOR , 60);


  int dayOfTheWeek = dayOfWeek(dayYear, dayMonth, dayDay);
  Serial.print("Day of week: ");
  Serial.println(dayOfWeek(dayYear, dayMonth, dayDay));
  if (dayOfTheWeek == 1) {
    currentDay = "Sunday";
    daysUntilWeekend = 0;
  }
  if (dayOfTheWeek == 2) {
    currentDay = "Monday";
    daysUntilWeekend = 5;
  }
  if (dayOfTheWeek == 3) {
    currentDay = "Tuesday";
    daysUntilWeekend = 4;
  }
  if (dayOfTheWeek == 4) {
    currentDay = "Wednesday";
    daysUntilWeekend = 3;
  }
  if (dayOfTheWeek == 5) {
    currentDay = "Thursday";
    daysUntilWeekend = 2;
  }
  if (dayOfTheWeek == 6) {
    currentDay = "Friday";
    daysUntilWeekend = 1;
  }
  if (dayOfTheWeek == 7) {
    currentDay = "Saturday";
    daysUntilWeekend = 0;
  }



  int timeInHours = rtc.getHours() + GMT;
  timeInHours = timeInHours -1;//dayliht savings sutuff


  if (timeInHours > 12) {
    int the12hrTime = timeInHours - 12;
    Serial.println(the12hrTime);
    theTimeHours = String(the12hrTime);
  } else if (timeInHours < 10) {
    theTimeHours = "0" + String(timeInHours);
  } else {
    theTimeHours = String(timeInHours);
  }

  int timeMins = rtc.getMinutes();


  if (timeMins < 10) {
    theTimeMins = "0" + String(timeMins);
  } else {
    theTimeMins = String(timeMins);
  }


  String theTime = theTimeHours + " : " + theTimeMins;
  String hi = theDate;
  String hi1 = theTime;
  const char *strHi = hi.c_str();
  const char *strHi1 = hi1.c_str();
  //myDisplay.print(theTime);


  myDisplay.displayText  (strHi,
                          PA_CENTER,
                          300,
                          5000,
                          PA_FADE,
                          PA_FADE
                         );

  while (1) {
    if (myDisplay.displayAnimate()) {
      myDisplay.displayReset();
      break;

    }
  }

  myDisplay.displayText  (strHi1,
                          PA_CENTER,
                          40,
                          5000,
                          PA_RANDOM,
                          PA_SCROLL_DOWN
                         );

  while (1) {
    if (myDisplay.displayAnimate()) {
      myDisplay.displayReset();
      break;

    }
  }





  Serial.print(rtc.getDay());

  Serial.print("/");

  Serial.print(rtc.getMonth());

  Serial.print("/");

  Serial.print(rtc.getYear());

  Serial.print(" ");

  Serial.println();
}

void printWiFiStatus() {

  // print the SSID of the network you're attached to:

  Serial.print("SSID: ");

  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:

  IPAddress ip = WiFi.localIP();

  Serial.print("IP Address: ");

  Serial.println(ip);

  // print the received signal strength:

  long rssi = WiFi.RSSI();

  Serial.print("signal strength (RSSI):");

  Serial.print(rssi);

  Serial.println(" dBm");
}

void print2digits(int number) {

  if (number < 10) {

    String digit = "0" + number;

  }

  //  return digit;
  // Serial.println(digit);
}



void getWeather() {

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    client.print("GET /data/2.5/forecast?");
    client.print("q=" + location);
    client.print("&appid=" + apiKey);
    client.print("&cnt=3");
    client.println("&units=imperial");
    client.println("Host: api.openweathermap.org");
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("unable to connect");
  }

  delay(1000);
  String line = "";

  while (client.connected()) {
    line = client.readStringUntil('\n');

    //Serial.println(line);
    Serial.println("parsingValues");

    //create a json buffer where to store the json data
    StaticJsonDocument<5000> root;

    DeserializationError error =  deserializeJson(root, line);
    if (error) {
      Serial.println("deserializeJson() failed");
      return;
    }

    //    //get the data from the json tree
    //
    //    String weather = root["list"][0]["weather"][0]["description"];
    //
    //   String temp = root["list"][0]["main"]["temp"];
    //
    //    String humidity = root["list"][0]["main"]["humidity"];
    //
    //    String feels_like = root["list"][0]["main"]["feels_like"];
    //
    //   String wind = root["list"][0]["wind"]["speed"];






    String Weather = root["list"][0]["weather"][0]["description"];

    int Temp = root["list"][0]["main"]["temp"];
    int TempMax = root["list"][0]["main"]["temp_max"];
    int feels_like = root["list"][0]["main"]["feels_like"];
    int Humidity = root["list"][0]["main"]["humidity"];
    int TempMin = root["list"][0]["main"]["temp_min"];
    int Wind = root["list"][0]["wind"]["speed"];
    int WindGust = root["list"][0]["wind"]["gust"];
    int Population = root["city"]["population"];

    String FeelsString = String(feels_like);
    String TempMaxString = String(TempMax);
    String TempMinString = String(TempMin);
    String TempString = String(Temp);
    String WindString = String(Wind);
    String WindGustString = String(WindGust);
    String HumidityString = String(Humidity);
    String PopulationString = String(Population);







    //  Serial.println("Temp C: " + (Weather - 32)/1.8);
    // char* displayOutput1 = "Current weather: " + Weather + "     Current temp: " + Temp + "     Approx. wind speed:" + Wind;
    String Weather1 = Weather;
    String TempF = TempString + " degrees";
    // String TempC = "Temp C: " + Temp − 32 * 5/9;
    String Wind1 =  WindString + " mph";
    String WindGust1 = "Gust: " + WindGustString + " mph";
    String TempMax1 = "Max: " + TempMaxString + " F";
    String TempMin1 = "Min: " + TempMinString + " F";
    String Humidity1 = HumidityString + "%";
    String Population1 = "Pop:" + PopulationString;
    String Feels_likeF =  FeelsString + " degrees";
    //String Feels_likeC = "Feel C: " + feels_like - 32 * 5/9;

    String fullWeather = "Weather:     It is currently " + TempF + ", but feels like " + Feels_likeF + ". The wind is " + Wind1 + ", and the humidity is " + Humidity1;

    const char *charFullWeather = fullWeather.c_str();



    //    String hi3 = weather;//DEXFRIPTiON
    //    const char *descriptionOut = hi3.c_str();
    //
    //    String hi4 = "Temp: " + round(temp.toInt()) + " F";//TEMP
    //    const char *tempOut = hi4.c_str();
    //
    //    String hi5 = "Humidiy: "+humidity + "%";//HUMIDITY
    //    const char *humidityOut = hi5.c_str();
    //
    //    String hi6 = "Feels: " + round(feels_like.toInt()) + " F";//FEELS LIKE
    //    const char *feelsOut = hi6.c_str();
    //
    //    String hi7 = "Wind: " + round(wind.toInt)) + " MPH";//WIND
    //    const char *windOut = hi7.c_str();





    myDisplay.displayText  (charFullWeather,
                            PA_CENTER,
                            40,
                            0,
                            PA_SCROLL_LEFT,
                            PA_SCROLL_LEFT
                           );

    while (1) {
      if (myDisplay.displayAnimate()) {
        myDisplay.displayReset();
        break;

      }
    }



  }

}

#include <Wire.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#define SSID "yang"                                   
#define PASS "00000000"     

ESP8266WebServer server(80);

const int led = BUILTIN_LED;
char led_status[200];
String webSite,jScript;
byte x = 0;

void buildWeb(){

   jScript+="<script>";
   jScript+="function loadDocw(){";
   jScript+="var rad = document.getElementById(\"btnw\");";
   jScript+="var selected =rad.value;";
   jScript+="var http = new XMLHttpRequest();";
   jScript+="var value = \"BTN=\" + selected ;";
   jScript+="http.open(\"POST\",\"ChangeText\",true);";
   jScript+="http.send(value);";
   jScript+="http.onreadystatechange = function(){";
   jScript+="if(http.readyState == 4 && http.status == 200){";
   jScript+="document.getElementById(\"text\").innerHTML = http.responseText;";
   jScript+="}}}";
   
   jScript+="function loadDocs(){";
   jScript+="var rad = document.getElementById(\"btns\");";
   jScript+="var selected =rad.value;";
   jScript+="var http = new XMLHttpRequest();";
   jScript+="var value = \"BTN=\" + selected ;";
   jScript+="http.open(\"POST\",\"ChangeText\",true);";
   jScript+="http.send(value);";
   jScript+="http.onreadystatechange = function(){";
   jScript+="if(http.readyState == 4 && http.status == 200){";
   jScript+="document.getElementById(\"text\").innerHTML = http.responseText;";
   jScript+="}}}";
   
   jScript+="function loadDoca(){";
   jScript+="var rad = document.getElementById(\"btna\");";
   jScript+="var selected =rad.value;";
   jScript+="var http = new XMLHttpRequest();";
   jScript+="var value = \"BTN=\" + selected ;";
   jScript+="http.open(\"POST\",\"ChangeText\",true);";
   jScript+="http.send(value);";
   jScript+="http.onreadystatechange = function(){";
   jScript+="if(http.readyState == 4 && http.status == 200){";
   jScript+="document.getElementById(\"text\").innerHTML = http.responseText;";
   jScript+="}}}";
   
   jScript+="function loadDocd(){";
   jScript+="var rad = document.getElementById(\"btnd\");";
   jScript+="var selected =rad.value;";
   jScript+="var http = new XMLHttpRequest();";
   jScript+="var value = \"BTN=\" + selected ;";
   jScript+="http.open(\"POST\",\"ChangeText\",true);";
   jScript+="http.send(value);";
   jScript+="http.onreadystatechange = function(){";
   jScript+="if(http.readyState == 4 && http.status == 200){";
   jScript+="document.getElementById(\"text\").innerHTML = http.responseText;";
   jScript+="}}}";        
   jScript+="</script>";
  
   webSite+="<html>";
    webSite+="<head>";
    webSite+="<meta name=\"viewport\" content=\"width=device-width, initial-scale=0.5, maximum-scale=0.5\">";
    webSite+="<style>";
    webSite+="body{";
    webSite+="max-width: 908px;";
    webSite+="height: 480px;";
    webSite+="margin:100px auto;";
    webSite+="overflow: hidden;";
    webSite+="}";
    webSite+="img{";
    webSite+="width: 200px;";
    webSite+="height: 200px;";
    webSite+="}";
    webSite+="button{";
    webSite+="display: block;";
    webSite+="width: 232px;";
    webSite+="height: 220px;";
    webSite+="}";
    webSite+=".tb{";
    webSite+="margin-right: 172px;";
    webSite+="float: left;";
    webSite+="}";
    webSite+=".lr{";
    webSite+="float: left;";
    webSite+="margin-top: 129px;";
    webSite+="}";
    webSite+=".b{";
    webSite+="margin-top: 40px;";
    webSite+="}";
    webSite+=".l{";
    webSite+="float: left;";
    webSite+="}";
    webSite+=".r{";
    webSite+="float: left;";
    webSite+="margin-left: 40px;";
    webSite+="}";
    webSite+="</style>";
    webSite+="</head>";
    webSite+="<body onselectstart=\"return false;\" ondragstart=\"return false;\" oncontextmenu=\"return false;\">";
    webSite+="<div class=\"tb\">";
    webSite+="<button id=\"btnw\" class=\"t\" value=\"w\" type=\"button\" ontouchstart=\"loadDocw()\" ontouchend=\"loadDocw()\"> <img src=\"https://cdn3.iconfinder.com/data/icons/google-material-design-icons/48/ic_keyboard_arrow_up_48px-256.png\"> </button>";
    webSite+="<button id=\"btns\" class=\"b\" value=\"s\" type=\"button\" ontouchstart=\"loadDocs()\" ontouchend=\"loadDocs()\"> <img src=\"https://cdn3.iconfinder.com/data/icons/google-material-design-icons/48/ic_keyboard_arrow_down_48px-256.png\"> </button>";
    webSite+="</div>";
    webSite+="<div class=\"lr\">";
    webSite+="<button id=\"btna\" class=\"l\" value=\"a\" type=\"button\" ontouchstart=\"loadDoca()\" ontouchend=\"loadDoca()\"> <img src=\"https://cdn3.iconfinder.com/data/icons/google-material-design-icons/48/ic_keyboard_arrow_left_48px-256.png\"> </button>";
    webSite+="<button id=\"btnd\" class=\"r\" value=\"d\" type=\"button\" ontouchstart=\"loadDocd()\" ontouchend=\"loadDocd()\"> <img src=\"https://cdn3.iconfinder.com/data/icons/google-material-design-icons/48/ic_keyboard_arrow_right_48px-256.png\"> </button>";
    webSite+="</div>";
    webSite+= jScript;
    webSite+="</body>";
    webSite+="</html>";
    
    }

void handleRoot(){
  server.send(200,"text/html",webSite);
}

void ChangeText(){
  if (server.arg("BTN") == "w") {
    Wire.beginTransmission(8); // transmit to device#8
    Wire.write('w'); // sends one byte
    Wire.endTransmission(); // stop transmitting
    Serial.println("w");
  }else if (server.arg("BTN") == "a") {
    Wire.beginTransmission(8); // transmit to device#8
    Wire.write('a'); // sends one byte
    Wire.endTransmission(); // stop transmitting   
    Serial.println("a");
  }else if (server.arg("BTN") == "s") {
    Wire.beginTransmission(8); // transmit to device#8
    Wire.write('s'); // sends one byte
    Wire.endTransmission(); // stop transmitting   
    Serial.println("s");
  }else if (server.arg("BTN") == "d") {
    Wire.beginTransmission(8); // transmit to device#8
    Wire.write('d'); // sends one byte
    Wire.endTransmission(); // stop transmitting    
    Serial.println("d");
  }
  server.send ( 200 , "text/html" , led_status );
}

void handleNotFound(){
  server.send(404,"text/html","404 Error!");
}

void setup() {
  
  Serial.begin(115200);
  // put your setup code here, to run once:
  buildWeb();
  WiFi.begin(SSID, PASS); 
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  server.on("/",handleRoot);
  //server.on("/form1",handleLEDStatus);
  server.on("/ChangeText",ChangeText);
  server.onNotFound(handleNotFound);

  Wire.begin(4,5);
  server.begin();
  Serial.println(WiFi.localIP());  
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();  
}

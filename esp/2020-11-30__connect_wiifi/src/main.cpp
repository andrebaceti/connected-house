#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

int LED_not_connected = D1;
int LED_connected = D2;

const char *ssid =  "Andre b";     // replace with your wifi ssid and wpa2 key
const char *password =  "brisa12345";
const char *token = "Token c38fd1a822c4bc61e9b35c47e63a23a404f2887d";
String public_ip;

String mac_address;
WiFiClient wifiClient;
const size_t capacity = JSON_ARRAY_SIZE(50) + JSON_OBJECT_SIZE(50) + 30;

// Setup the WiFi and get public IP
void setup_wifi() {
  // Connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
  mac_address = WiFi.macAddress();

  while (true){
    int httpResponseCode;
    HTTPClient http;

    http.begin("http://ipinfo.io/ip"); //Specify destination for HTTP request
    httpResponseCode = http.GET();

    if(httpResponseCode>0){
      public_ip = http.getString();  //Get the response to the request

      Serial.print("Ok getting self public IP: ");
      Serial.println(public_ip);           //Print request answer
      break;

    }else{
      Serial.print("Error getting selt public IP: ");
      Serial.println(http.getString());
    }
    http.end();
  }
}


void setup() {
  Serial.begin(9600);
  setup_wifi();

    /////////////////////////
  // Setting pins to output
  pinMode(LED_not_connected, OUTPUT);
  pinMode(LED_connected, OUTPUT);

  digitalWrite(LED_not_connected, HIGH);
  digitalWrite(LED_connected, LOW);
  /////////////////////////
}


void loop()
{
  int httpResponseCode;
  HTTPClient http;

  if (WiFi.status() == WL_CONNECTED){
    Serial.println("WiFi.status() == WL_CONNECTED");

    digitalWrite(LED_not_connected, LOW);
    digitalWrite(LED_connected, HIGH);
  }else {
    digitalWrite(LED_not_connected, HIGH);
    digitalWrite(LED_connected, LOW);
  }

  http.begin("http://192.168.15.6:8080/rest/crawleriotpumpwood/routes/"); //Specify destination for HTTP request
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", token);
  httpResponseCode = http.GET();

  if(httpResponseCode>0){
    String response = http.getString();  //Get the response to the request

    DynamicJsonDocument doc(capacity);
    deserializeJson(doc, response);

    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
    String message = doc["message"];
    Serial.println(message);
  }else{
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  }

  ///////////////////////////////////
  // Limpando os recursos disponíveis
  http.end();
  ///////////////////////////////////

  /////////////////////////
  delay(5000);
}

#include <WiFi.h>
#include <HTTPClient.h>
#ifdef __cplusplus
  extern "C" {
 #endif

  uint8_t temprature_sens_read();

#ifdef __cplusplus
}
#endif

uint8_t temprature_sens_read();

const char ssid[] = "Rede_Wi-Fi";
const char password[] = "Senha_Wi-Fi";

String HOST_NAME = "http://ip_maquina"; // REPLACE WITH YOUR PC's IP ADDRESS
String PHP_FILE_NAME   = "/teste/teste.php";  //REPLACE WITH YOUR PHP FILE NAME

void setup() {
  Serial.begin(115200); 
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.print("Temperature: ");
  // Convert raw temperature in F to Celsius degrees
  double temperature = (temprature_sens_read() - 32) / 1.8;

  String tempQuery = "?temperature=";
  tempQuery.concat(temperature);
  Serial.print(tempQuery);
  Serial.println("\n");

  delay(1000);
  
  HTTPClient http;
  String server = HOST_NAME + PHP_FILE_NAME + tempQuery;
  http.begin(server); 
  int httpCode = http.GET();

  if(httpCode > 0) {
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.printf("HTTP GET... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("HTTP GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
  
}

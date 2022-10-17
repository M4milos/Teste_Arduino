#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#ifdef __cplusplus
  extern "C" {
 #endif

  uint8_t temprature_sens_read();

#ifdef __cplusplus
}
#endif

uint8_t temprature_sens_read();

const char ssid[] = "linksys";
const char password[] = "123456789";

String HOST_NAME = "http://192.168.1.100"; // REPLACE WITH YOUR PC's IP ADDRESS
String PHP_FILE_NAME   = "/teste/teste.php";  //REPLACE WITH YOUR PHP FILE NAME

const int MPU = 0X68;
int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;

void setup() { 
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0X6B);
  Wire.write(0);
  Wire.endTransmission(true);

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
  Wire.beginTransmission(MPU);
  Wire.write(0X3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14 , true);
  AcX = Wire.read()<<8|Wire.read();
  AcY = Wire.read()<<8|Wire.read();
  AcZ = Wire.read()<<8|Wire.read();
  GyX = Wire.read()<<8|Wire.read();
  GyY = Wire.read()<<8|Wire.read();
  GyZ = Wire.read()<<8|Wire.read();

  Serial.print("Temperature: ");
  // Convert raw temperature in F to Celsius degrees
  double temperature = (temprature_sens_read() - 32) / 1.8;

  String tempQuery = "?temperature="; 
  tempQuery.concat(temperature);
  Serial.println(tempQuery);
  Serial.print("AcX = "); Serial.println(AcX);
  Serial.print("AcY = "); Serial.println(AcY);
  Serial.print("AcZ = "); Serial.println(AcZ);
  Serial.print("GyX = "); Serial.println(GyX);
  Serial.print("GyY = "); Serial.println(GyY);
  Serial.print("GyZ = "); Serial.println(GyZ);


  delay(2000);
  
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
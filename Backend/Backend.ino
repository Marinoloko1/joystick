#include <ESPAsyncWebServer.h>


#include <WiFi.h>

#define PIN_A_MOTOR1 19
#define PIN_B_MOTOR1 21
#define PIN_A_MOTOR2 22
#define PIN_B_MOTOR2 23

const char *ssid = "GHOST";
const char *password = "qwerty123";

AsyncWebServer server(80);

float velocidad_Izquierda; 
float velocidad_Derecha; 

void setup() 
{
  Serial.begin(9600);

  pinMode(PIN_A_MOTOR1, OUTPUT);
  pinMode(PIN_B_MOTOR1, OUTPUT);
  pinMode(PIN_A_MOTOR2, OUTPUT);
  pinMode(PIN_B_MOTOR2, OUTPUT);
  
  WiFi.softAP(ssid, password); //ESP32 configurada como punto de acceso 
 
  Serial.println("Punto de acceso iniciado");
  Serial.println("IP del punto de accceso: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET,[](AsyncWebServerRequest *request)
  {
    request->send(200,"text/plain",
    "Servidor ESP32 encendido");
  });

  server.on("/mover",HTTP_GET,[](AsyncWebServerRequest *request)
  {
    String velocidad_str = request->getParam("velocidad")->value();
    float velocidad = velocidad_str.toInt();

    String motores = request->getParam("motor")->value();
    int motor = motores.toInt();

    if(motor == 1)
    {
      if(velocidad > 0)
      {
        digitalWrite(PIN_A_MOTOR1, HIGH);
        digitalWrite(PIN_B_MOTOR1, LOW);
        request->send(200, "text/plain", "OK motor 1 avanza");      
      } 

      if(velocidad < 0)
      {
        digitalWrite(PIN_A_MOTOR1, LOW);
        digitalWrite(PIN_B_MOTOR1, HIGH);
        request->send(200, "text/plain", "OK motor 2 retrocede"); 
      }
      analogWrite(255, 2);
    }    
    
    if(motor == 2)
    {
      if(velocidad > 0)
      {
        digitalWrite(PIN_A_MOTOR1, HIGH);
        digitalWrite(PIN_B_MOTOR1, LOW);
        request->send(200, "text/plain", "OK motor 2 avanza");      
      }

      if(velocidad < 0)
      {
        digitalWrite(PIN_A_MOTOR1, LOW);
        digitalWrite(PIN_B_MOTOR1, HIGH);
        request->send(200, "text/plain", "OK motor 2 retrocede"); 
      } 
      analogWrite(abs(velocidad), 4);  
    }

    request->send(200, "text/plain", velocidad_str);
  });

  server.on("/stop",HTTP_GET,[](AsyncWebServerRequest *request)
  {
    String motores = request->getParam("motor")->value();
    int motor = motores.toInt();

    if(motor == 1)
    {
      digitalWrite(PIN_A_MOTOR1, LOW);
      digitalWrite(PIN_B_MOTOR1, LOW);
      request->send(200, "text/plain", "OK motor 1 se detiene");  
    }

    if(motor == 2)
    {
      digitalWrite(PIN_A_MOTOR2, LOW);
      digitalWrite(PIN_B_MOTOR2, LOW);
      request->send(200, "text/plain", "OK motor 2 se detiene");  
    }       
  });

  server.begin();
}

void loop() 
{

}

//brown wire at out1 and orange wire at out3

#include <WiFi.h>

#define motor1A 26
#define motor1B 27
#define motor2A 32
#define motor2B 33


const char* wifi_name = "yourssid"; //Your Wifi name
const char* wifi_pass = "yourpassword";    //Your Wifi password
WiFiServer server(80);                  //Port 80

String header;

void setup()
{
  Serial.begin(115200);
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);

  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
  // Let's connect to wifi network
  Serial.print("Connecting to ");
  Serial.print(wifi_name);
  WiFi.begin(wifi_name, wifi_pass);       //Connecting to wifi network

  while (WiFi.status() != WL_CONNECTED) { //Waiting for the responce of wifi network
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connection Successful");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());         //Getting the IP address at which our webserver will be created
  Serial.println("Put the above IP address into a browser search bar");
  server.begin();                         //Starting the server
}

void loop()
{
  WiFiClient client = server.available();   //Checking for incoming clients

  if (client)
  {
    Serial.println("new client");
    String currentLine = "";                   //Storing the incoming data in the string
    while (client.connected())
    {
      if (client.available())                 //if there is some client data available
      {

        char c = client.read();
        header += c;//read a byte
        Serial.print(c);

        if (c == '\n')                      //check for newline character,
        {
          if (currentLine.length() == 0)      //if line is blank it means its the end of the client HTTP request
          {

            //            client.print("<title>ESP32 Webserver</title>");
            if (header.indexOf("GET /frwrd") >= 0) {
              frwrd();
            } else if (header.indexOf("GET /stp") >= 0) {
              stp();
            } else if (header.indexOf("GET /left") >= 0) {
              left();
            } else if (header.indexOf("GET /rev") >= 0) {
              rev();
            } else if (header.indexOf("GET /right") >= 0) {
              right();
            }
              
            client.print("<body><a href = \"/frwrd\"><button type=\"button\"  value=\"frwrd\">Forward</a></button>");
            client.print("<body><a href = \"/stp\"><button type=\"button\"  value=\"stp\">Stop</a></button>");
            client.print("<body><br>");
            client.print("<body><a href = \"/left\"><button type=\"button\"  value=\"left\">Left</a></button>");
            client.print("<body><a href = \"/rev\"><button type=\"button\"  value=\"rev\">Reverse</a></button>");
            client.print("<body><a href = \"/right\"><button type=\"button\"  value=\"right\">Right</a></button>");



            break;                            //Going out of the while loop
          }
          else
          {
            currentLine = "";                //if you got a newline, then clear currentLine
          }
        }
        else if (c != '\r')
        {
          currentLine += c;                 //if you got anything else but a carriage return character,
        }
      }

    }
    header = "";
  }
}



void frwrd(){

  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
  Serial.println("Fowrward");    
}

void stp(){
  
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
  Serial.println("Stopped");
}

void left(){
  
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
  Serial.println("Left");
}

void rev(){
  
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
  Serial.println("Reverse");
}

void right(){
  
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
  Serial.println("Right");
}

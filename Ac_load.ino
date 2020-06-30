/*************************************************************
 * Organization Name    : Dot_Hex Pvt. Ltd. 
 * Developer name       : Prashant P. Hirave.
 * Product name         : Home Automation usng Google assitance, android smart phone and local N/W web page.
 * Product Version      : V00.00.01 
 * Software version     : V00.00.01
 * Date                 : 
 * 
 * ************************************************************/


#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define ssid  "Idiot"             // Enter SSID here
#define password  "12345678"      //Enter Password here

ESP8266WebServer server(80);

bool RL1_STATUS;
bool RL2_STATUS; 
bool RL3_STATUS; 
bool RL4_STATUS;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(100);

  pinMode(D0,OUTPUT);
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);

 digitalWrite(D0, LOW);
 digitalWrite(D1, LOW);
 digitalWrite(D2, LOW);
 digitalWrite(D3, LOW);
 
 WiFi.begin(ssid,password);

  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(1000);
    Serial.print("-");
    }

    Serial.println("");
    Serial.print("IP:");Serial.println(WiFi.localIP());

    server.on("/",OnConnect);
    server.on("/Relay1ON",Relay1_ON);
    server.on("/Relay1OFF",Relay1_OFF);
    server.on("/Relay2ON",Relay2_ON);
    server.on("/Relay2OFF",Relay2_OFF);
    server.on("/Relay3ON",Relay3_ON);
    server.on("/Relay3OFF",Relay3_OFF);
    server.on("/Relay4ON",Relay4_ON);
    server.on("/Relay4OFF",Relay4_OFF);    
    
    server.onNotFound(handle_NotFound);
    server.send(302, "text/plain", "Updated-- Press Back Button");
    
    server.begin();       
}

void loop() {
  // put your main code here, to run repeatedly:
server.handleClient();
if(RL1_STATUS)
{
    digitalWrite(D0, HIGH);
  }
  else
  {
    digitalWrite(D0, LOW);
    }

    if(RL2_STATUS)
{
    digitalWrite(D1, HIGH);
  }
  else
  {
    digitalWrite(D1, LOW);
    }

 if(RL3_STATUS)
{
    digitalWrite(D2, HIGH);
  }
  else
  {
    digitalWrite(D2, LOW);
    }

  if(RL4_STATUS)
{
    digitalWrite(D3, HIGH);
  }
  else
  {
    digitalWrite(D3, LOW);
    }     
}

/***************************** Data Handler ****************************/
void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

void OnConnect()
{ 
  RL1_STATUS = RL2_STATUS = RL3_STATUS = RL4_STATUS = LOW;
  
  server.send(200,"text/html",DisplayPage(RL1_STATUS, RL2_STATUS, RL3_STATUS,RL4_STATUS));    
  }

void Relay1_ON()
{
  RL1_STATUS = HIGH;
  server.send(200, "text/html", DisplayPage(true, RL2_STATUS, RL3_STATUS,RL4_STATUS));
  }

void Relay1_OFF()
{
  RL1_STATUS = LOW;
  server.send(200, "text/html", DisplayPage(false, RL2_STATUS, RL3_STATUS,RL4_STATUS));
  
  }
  
void Relay2_ON()
{
  RL2_STATUS = HIGH;
  server.send(200, "text/html", DisplayPage(RL1_STATUS, true, RL3_STATUS,RL4_STATUS));

  }

void Relay2_OFF()
{
  RL2_STATUS = LOW;
  server.send(200, "text/html", DisplayPage(RL1_STATUS, false, RL3_STATUS,RL4_STATUS));
 
  }

void Relay3_ON()
{
  RL3_STATUS = HIGH;
  server.send(200, "text/html", DisplayPage(RL1_STATUS, RL2_STATUS, true,RL4_STATUS));
  
  }

void Relay3_OFF()
{
  RL3_STATUS = LOW;
  server.send(200, "text/html", DisplayPage(RL1_STATUS, RL2_STATUS, false,RL4_STATUS));
  
  }
  
void Relay4_ON()
{
  RL4_STATUS = HIGH;
  server.send(200, "text/html", DisplayPage(RL1_STATUS, RL2_STATUS, RL3_STATUS,true));
  
  }

void Relay4_OFF()
{
  RL4_STATUS = LOW;
  server.send(200, "text/html", DisplayPage(RL1_STATUS, RL2_STATUS, RL3_STATUS,false));
  
  }





/* ************************************ WebPage **************************************************/

String DisplayPage(bool RL1_STATUS, bool RL2_STATUS, bool RL3_STATUS, bool RL4_STATUS)
{
    String WebPage = "<!DOCTYPE html>\n";
    WebPage+="<html>\n";
    WebPage+= "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\">\n";
    WebPage+=                   "<script src='https://kit.fontawesome.com/a076d05399.js'></script>\n";    // link of lightbulb image  
    WebPage+=                   "<script src='https://kit.fontawesome.com/a076d05399.js'></script>\n";    // link of fan rotaion image
    WebPage+=   "<title>Home Automation</title>\n";
    WebPage+=    "<style>html{ font-family: Courier New; color:#6B9ED6; background-color:#efdecd; text-align:center;}\n";    
    WebPage+=                 "body{margin-top: 30px;}\n"; 
    WebPage+=                 ".button {display: inline-block; width: 80px; background-color:#28837f;color: white;margin-top: 90px; padding: 5px 0px; margin: 10px 30px ;text-align:auto ; text-decoration: none;font-size: 20px;cursor: pointer;border-radius: 12px;}\n";
    WebPage+=                 ".button-on {background-color: #975d72;}\n";
    WebPage+=                 ".button-on:active {background-color: #35c95f;}\n";
    WebPage+=                 ".button-off {background-color: #28837f;}\n";
    WebPage+=                 ".button-off:active {background-color: #cb9ed6;}\n";  
    WebPage+=                 "p {font-size: 14px; color:#254114; margin-bottom: 10px;}\n";
    WebPage+=                 ".bottomright{ font-family: color:#8aafe3; Courier New; position: absolute;  bottom: 8px;  left: 16px;  font-size: 18px;}\n";
    WebPage+=    "</style>\n";          
    WebPage+=    "<body>\n";
    WebPage+=            "<h3>----Home is on Internet----</h3>\n";

    if(RL1_STATUS)
    {
      WebPage+=                "<p><b>Switch1</b></p><a class= \"button button-off fas fa-lightbulb\" href=\"/Relay1OFF\"> OFF</a>\n";
    }
    else
    {
      WebPage+=                "<p><b>Switch1</b></p><a class= \"button button-on far fa-lightbulb\" href=\"/Relay1ON\"> ON</a>\n";
    }
    if(RL2_STATUS)
    {
      WebPage+=                "<p><b>Switch2</b></p><a class= \"button button-off fas fa-radiation\" href=\"/Relay2OFF\"> OFF</a>\n";
    }
    else
    {
      WebPage+=                "<p><b>Switch2</b></p><a class= \"button button-on fas fa-radiation\" href=\"/Relay2ON\"> ON</a>\n";
    }
    if(RL3_STATUS)
    {
      WebPage+=                "<p><b>Switch3</b></p><a class= \"button button-off fas fa-lightbulb\" href=\"/Relay3OFF\"> OFF</a>\n";
    }
    else
    {
      WebPage+=                "<p><b>Switch3</b></p><a class= \"button button-on far fa-lightbulb\" href=\"/Relay3ON\"> ON</a>\n";
    }
    if(RL4_STATUS)
    {
      WebPage+=                "<p><b>Switch4</b></p><a class= \"button button-off fas fa-lightbulb\" href=\"/Relay4OFF\"> OFF</a>\n";
    }
    else
    {
      WebPage+=                "<p><b>Switch4</b></p><a class= \"button button-on far fa-lightbulb\" href=\"/Relay4ON\"> ON</a>\n";
    }

    WebPage+=                "<div class=\"bottomright\"><b>!...Dot Hex Pvt. Ltd...!</b> </div>\n";
    WebPage+=     "</body>\n";
    WebPage+= "</head>";          
    WebPage+="</html>"; 

    return WebPage;
}

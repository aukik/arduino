

#include <WiFi.h>
#include <RGBLED.h>
const char* ssid     = "Aukik";
const char* password = "neeha1234";

WiFiServer server(80);
RGBLED rgbLed(2,4,23,COMMON_CATHODE);
int delayMs = 1000;
String light="red";
bool b_random=false;
  bool b_cycle=false;
  bool b_wheel=false;
void setup()
{
    Serial.begin(115200);
    String ledType = (rgbLed.commonType==0) ? "COMMON_CATHODE" : "COMMON_ANODE";
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    server.begin();

}

int value = 0;
bool cycle=false;
int wheel_number=0;
void loop(){
 WiFiClient client = server.available();   // listen for incoming clients
  String currentLine = "";

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
                    // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");

            // Web Page Heading
            client.println("<body><h1>ggezz RGB :3</h1>");

            // the content of the HTTP response follows the header:
            client.print(" <a href=\"/Hred\"><button class=\"button\">Red ON</button></a> <br>");
            client.print(" <a  href=\"/Lred\"><button class=\"button button2\" >Red Off</button></a> <br>");
            client.print(" <a  href=\"/Hgreen\"><button class=\"button\" >Green On</button></a> <br>");
            client.print("<a  href=\"/Lgreen\"><button class=\"button button2\" >Green Off</button></a> <br>");
            client.print(" <a  href=\"/Hblue\"><button class=\"button\" >Blue On</button></a><br> ");

            client.print(" <a  href=\"/Lblue\"><button class=\"button button2\">Blue Off</button></a><br> ");
            client.print(" <a  href=\"/cycle\"><button class=\"button\">Cycle RGB</button></a><br> ");
            client.print(" <a  href=\"/random\"><button class=\"button\">Color Random</button></a><br> ");
            client.print(" <a  href=\"/wheel\"><button class=\"button\">Color Wheel</button></a><br> ");
             client.print(" <a  href=\"/off\"><button class=\"button\">Turn Off</button></a><br> ");
            client.println("</body></html>");
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /Hred")) {
         if(b_cycle==true || b_wheel==true || b_random==true){
            rgbLed.turnOff();
          }
         b_cycle=false ;
         b_wheel=false;
         b_random=false;
          rgbLed.writeRed(255);
               // GET /H turns the LED on
        }

        if (currentLine.endsWith("GET /Lred")) {
          rgbLed.writeRed(0);                // GET /L turns the LED off
        }
        if (currentLine.endsWith("GET /Hgreen")) {
          if(b_cycle==true || b_wheel==true || b_random==true){
            rgbLed.turnOff();
          }

          b_cycle=false ;
         b_wheel=false;
         b_random=false;
          rgbLed.writeGreen(255);              // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /Lgreen")) {
          rgbLed.writeGreen(0);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /Hblue")) {
          if(b_cycle==true || b_wheel==true || b_random==true){
            rgbLed.turnOff();
          }

          b_cycle=false ;
         b_wheel=false;
         b_random=false;
          rgbLed.writeBlue(255);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /Lblue")) {
          rgbLed.writeBlue(0);             // GET /H turns the LED on
        }




        if (currentLine.endsWith("GET /cycle")) {
         cycle=true;
         b_cycle=true ;
         b_wheel=false;
         b_random=false;
        }



        if (currentLine.endsWith("GET /random")) {

          b_random=true;
          b_wheel=false;
          b_cycle=false ;

        }
        if (currentLine.endsWith("GET /wheel")) {
         b_wheel=true ;
         b_random=false;
         b_cycle=false ;
        }
        if (currentLine.endsWith("GET /off")) {
          rgbLed.turnOff();
          b_cycle=false ;
         b_wheel=false;
         b_random=false;
         cycle=true;
          delay(delayMs);
        }

      }

    }
    // close the connection:


    client.stop();


  }
  if(b_random){
          rgbLed.writeRandom();
          delay(delayMs);
          }

  if(b_wheel){

    if(wheel_number==0){

      //rd
       for(int i=255;i>=0;i--){
          rgbLed.writeRGB(i,255,0);

          
          delay(5);
        }
    wheel_number++;
    }else if(wheel_number==1){
      //bu
      for(int i=0;i<=255;i++){
          rgbLed.writeRGB(0,255,i);

          
          delay(5);
        }
        wheel_number++;
    }
    else if(wheel_number==2){
      //gd
      for(int i=255;i>=0;i--){
          rgbLed.writeRGB(0,i,255);

          
          delay(5);
        }
        wheel_number++;
    }else if(wheel_number==3){
      //ru
      for(int i=0;i<=255;i++){
          rgbLed.writeRGB(i,0,255);

          
          delay(5);
        }
    wheel_number++;
    }
    
    else if(wheel_number==4){
      //bd
      for(int i=255;i>=0;i--){
          rgbLed.writeRGB(255,0,i);

         
          delay(5);
        }
wheel_number++;
       }else if(wheel_number==5){
      //gu
      for(int i=0;i<=255;i++){
          rgbLed.writeRGB(255,i,0);

          wheel_number=0;
          delay(5);
        }
        
    }
  }
  if(b_cycle){
    if(cycle){
      rgbLed.turnOff();
          cycle=false;
      }
 int color_code=0;

 if(light=="red"){
      for(int i=0;i<255;i++){
          rgbLed.writeRGB(0,color_code,0);
          color_code++;
          delay(5);
        }
      for(int i=0;i<255;i++){
          rgbLed.writeRGB(0,color_code,0);
          color_code--;
          delay(5);
        }
      light="green";
      } else if(light=="green"){
      for(int i=0;i<255;i++){
          rgbLed.writeRGB(0,0,color_code);
          color_code++;
          delay(5);
        }
      for(int i=0;i<255;i++){
          rgbLed.writeRGB(0,0,color_code);
          color_code--;
          delay(5);
        }
      light="blue";
      }else{
        for(int i=0;i<255;i++){
          rgbLed.writeRGB(color_code,0,0);
          color_code++;
          delay(5);
        }
        for(int i=0;i<255;i++){
          rgbLed.writeRGB(color_code,0,0);
          color_code--;
          delay(5);
        }
      light="red";

        }

            }


}
void printRgbValues() {
  Serial.println("Requested RGB Values:");
  Serial.println("(r,g,b)=(" + String(rgbLed.redValue) + "," + String(rgbLed.greenValue) + "," + String(rgbLed.blueValue) + ")");
  Serial.println("Mapped RGB Values based on type (COMMON_ANODE or COMMON_CATHODE):");
  Serial.println("Mapped(r,g,b)=(" + String(rgbLed.redMappedValue) + "," + String(rgbLed.greenMappedValue) + "," + String(rgbLed.blueMappedValue) + ")");
  Serial.println("------------------------------");
}

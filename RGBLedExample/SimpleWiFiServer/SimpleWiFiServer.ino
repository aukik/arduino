

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
int speed=5;
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
           client.println("<!DOCTYPE html>");
client.println("<html>");

client.println("<head>");
client.println("  <link href='https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css' rel='stylesheet'");
client.println("    integrity='sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3' crossorigin='anonymous'>");
client.println("  <meta name='viewport' content='width=device-width, initial-scale=1'>");

client.println("</head>");

client.println("<body>");
client.println("  <nav class='navbar navbar-light' style='background-color: #8ab4d1;'>");
client.println("    <div class='container-fluid'>");
client.println("      <a class='navbar-brand' href='#'>GG</a>");
client.println("    </div>");
client.println("  </nav>");
client.println("  <div class='container-fluid' align='center' style='padding-top:5px;'>");

client.println("    <div style='padding-bottom: 5px;'>");
client.println("      <a href='Hred'><button class='btn btn-danger'>Red ON</button></a> <br>");
client.println("    </div>");
client.println("    <div style='padding-bottom: 5px;'>");
client.println("      <a href='Lred'><button class='btn btn-dark'>Red Off</button></a> <br>");
client.println("    </div>");
client.println("    <div style='padding-bottom: 5px;'>");
client.println("      <a href='Hgreen'><button class='btn btn-success'>Green On</button></a> <br>");
client.println("    </div>");
client.println("    <div style='padding-bottom: 5px;'>");
client.println("      <a href='Lgreen'><button class='btn btn-dark'>Green Off</button></a> <br>");
client.println("    </div>");
client.println("    <div style='padding-bottom: 5px;'>");
client.println("      <a href='Hblue'><button class='btn btn-primary'>Blue On</button></a><br>");
client.println("    </div>");
client.println("    <div style='padding-bottom: 5px;'>");
client.println("      <a href='Lblue'><button class='btn btn-dark'>Blue Off</button></a><br>");
client.println("    </div>");
client.println("    <div style='padding-bottom: 5px;'>");
client.println("      <a href='cycle'><button class='btn btn-secondary'>Cycle RGB</button></a><br>");
client.println("    </div>");
client.println("    <div style='padding-bottom: 5px;'>");
client.println("      <a href='random'><button class='btn btn-secondary'>Color Random</button></a><br>");
client.println("    </div>");
client.println("    <div style='padding-bottom: 5px;'>");
client.println("      <a href='wheel'><button class='btn btn-secondary'>Color Wheel</button></a><br>");
client.println("    </div>");
client.println("    <div style='padding-bottom: 5px;'>");
client.println("      <a href='off'><button class='btn btn-dark'>Turn Off</button></a><br>");
client.println("    </div>");
client.println("    <script src='https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js'");
client.println("      integrity='sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p' crossorigin='anonymous'>");
client.println(" </script>");
client.println("  </div><div class='container-fluid' align='center' style='padding-top:5px;'><a href='speed_up' style='padding-right:5px;'><button class='btn btn-secondary'>Speed Up</button></a><a href='speed_down'><button class='btn btn-secondary'>Speed Down</button></a></div>");
client.println("</body>");

client.println("</html>");

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
         if (currentLine.endsWith("GET /speed_up")) {
        if(speed>=6){
          speed-=5;
        }
        }
         if (currentLine.endsWith("GET /speed_down")) {
        
          speed+=5;
        
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
          delay(speed*100);
          }

  if(b_wheel){

    if(wheel_number==0){

      //rd
       for(int i=255;i>=0;i--){
          rgbLed.writeRGB(i,255,0);


          delay(speed);
        }
    wheel_number++;
    }else if(wheel_number==1){
      //bu
      for(int i=0;i<=255;i++){
          rgbLed.writeRGB(0,255,i);


          delay(speed);
        }
        wheel_number++;
    }
    else if(wheel_number==2){
      //gd
      for(int i=255;i>=0;i--){
          rgbLed.writeRGB(0,i,255);


          delay(speed);
        }
        wheel_number++;
    }else if(wheel_number==3){
      //ru
      for(int i=0;i<=255;i++){
          rgbLed.writeRGB(i,0,255);


          delay(speed);
        }
    wheel_number++;
    }

    else if(wheel_number==4){
      //bd
      for(int i=255;i>=0;i--){
          rgbLed.writeRGB(255,0,i);


          delay(speed);
        }
wheel_number++;
       }else if(wheel_number==5){
      //gu
      for(int i=0;i<=255;i++){
          rgbLed.writeRGB(255,i,0);

          wheel_number=0;
          delay(speed);
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
          delay(speed);
        }
      for(int i=0;i<255;i++){
          rgbLed.writeRGB(0,color_code,0);
          color_code--;
          delay(speed);
        }
      light="green";
      } else if(light=="green"){
      for(int i=0;i<255;i++){
          rgbLed.writeRGB(0,0,color_code);
          color_code++;
          delay(speed);
        }
      for(int i=0;i<255;i++){
          rgbLed.writeRGB(0,0,color_code);
          color_code--;
          delay(speed);
        }
      light="blue";
      }else{
        for(int i=0;i<255;i++){
          rgbLed.writeRGB(color_code,0,0);
          color_code++;
          delay(speed);
        }
        for(int i=0;i<255;i++){
          rgbLed.writeRGB(color_code,0,0);
          color_code--;
          delay(speed);
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

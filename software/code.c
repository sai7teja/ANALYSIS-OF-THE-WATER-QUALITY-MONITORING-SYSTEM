#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
SoftwareSerial mySerial(8, 9); //GSM


const int ph = A0;
const int turbidity = A1;

int sensor1Value = 1;
int sensor2Value = 1;



void sendwifi(String chr, unsigned int len)
{
  String temp[20];
  Serial.print("AT+CIPSEND=0,");
  Serial.println(len);
  delay(1000);
  Serial.println(chr);
  delay(2000);
}


void setup() {


  pinMode(ph, INPUT);
  pinMode(turbidity, INPUT);


  lcd.begin(16, 2);
  lcd.clear(); lcd.setCursor(0, 0); lcd.print("welcome");
  Serial.begin(9600);
  delay(1000);
  lcd.clear(); lcd.setCursor(0, 0); lcd.print("WIFI INIT");
  Serial.print("AT\r\n");
  delay(1000);
  Serial.print("ATE0\r\n");
  delay(1000);
  Serial.print("AT+CIPMUX=1\r\n");
  delay(1000);
  Serial.print("AT+CIPSERVER=1,23\r\n");
  delay(1000);
  lcd.clear(); lcd.setCursor(0, 0); lcd.print("192.168.4.1");
  lcd.setCursor(0, 1); lcd.print("Port: 23");

  delay(1000);
  lcd.clear(); lcd.setCursor(0, 0); lcd.print("CONNECTED");
  sendwifi("WELCOME\r\n", 9);
  delay(1000);

  mySerial.begin(9600);
  delay(500);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only

  }
  mySerial.println("AT");
  delay(1500);
  mySerial.println("AT+CREG?");
  delay(1500);
  mySerial.println("AT+CMGF=1");
  delay(1500);
  mySerial.println("AT+CNMI=1,2,0,0");
  delay(1500);



}


void loop() {
  //  lcd.begin(16, 2);
  //  lcd.display();
  //  lcd.setCursor(0, 0);
  //  lcd.print("COLLISION" );
  //  lcd.setCursor(0, 1);
  //  lcd.print("      AVOIDANCE" );



  sensor1Value = analogRead(ph) / 100;
  sensor2Value = analogRead(turbidity);
  int turbidity = map(sensor2Value, 0, 750, 100, 0);
  delay(100);

  lcd.begin(16, 2);
  lcd.print("PH:= " );
  lcd.print(sensor1Value);
  delay(1000);
  Serial.print("AT+CIPSEND=0,");
  Serial.println(8);
  delay(1000);
  Serial.println("\r\nPH : ");
  delay(1000);
  Serial.print("AT+CIPSEND=0,");
  Serial.println(4);
  delay(1000);
  Serial.println(sensor1Value);
  delay(1000);

  lcd.begin(16, 2);
  lcd.print("turbidity:= " );
  lcd.print(sensor2Value);
  delay(1000);
  Serial.print("AT+CIPSEND=0,");
  Serial.println(8);
  delay(1000);
  Serial.println("\r\nturbidity : ");
  delay(1000);
  Serial.print("AT+CIPSEND=0,");
  Serial.println(4);
  delay(1000);
  Serial.println(sensor2Value);
  delay(1000);


  if (sensor1Value > 8)
  {
    lcd.begin(16, 2);
    lcd.clear(); lcd.setCursor(0, 0);
    // lcd.setCursor(0, 1);
    lcd.print("pH Value is High");
    sendwifi("\r\nHIGH pH DETECTED\r\n", strlen("\r\nHIGH pH DETECTED\r\n"));
    delay(1000);
    mySerial.println("AT+CMGS=\"9700082044\"\r\n");
    delay(1500);
    mySerial.println("HIGH pH DETECTED\r\n");
    mySerial.println((char)26); delay(500);
  }

  if (turbidity < 20) {
    lcd.begin(16, 2);
    lcd.clear(); lcd.setCursor(0, 0);
    //lcd.setCursor(0, 1);
    lcd.print(" its CLEAR ");
    sendwifi("\r\n its CLEAR \r\n", strlen("\r\n its CLEAR \r\n"));
    delay(1000);
    mySerial.println("AT+CMGS=\"9700082044\"\r\n");
    delay(1500);
    mySerial.println("turbidity: its CLEAR \r\n");
    mySerial.println((char)26); delay(500);
  }
  if ((turbidity > 20) && (turbidity < 50)) {
    lcd.begin(16, 2);
    lcd.clear(); lcd.setCursor(0, 0);
    // lcd.setCursor(0, 1);
    lcd.print(" its CLOUDY ");
    sendwifi("\r\n its CLOUDY \r\n", strlen("\r\n its CLOUDY \r\n"));
    delay(1000);
    mySerial.println("AT+CMGS=\"9700082044\"\r\n");
    delay(1500);
    mySerial.println("turbidity: its CLOUDY \r\n");
    mySerial.println((char)26); delay(500);
  }
  if (turbidity > 50) {
    lcd.begin(16, 2);
    lcd.clear(); lcd.setCursor(0, 0);
    // lcd.setCursor(0, 1);
    lcd.print(" its DIRTY ");
    sendwifi("\r\n its DIRTY \r\n", strlen("\r\n its DIRTY \r\n"));
    delay(1000);
    mySerial.println("AT+CMGS=\"9700082044\"\r\n");
    delay(1500);
    mySerial.println("turbidity: its DIRTY \r\n");
    mySerial.println((char)26); delay(500);
  }
}

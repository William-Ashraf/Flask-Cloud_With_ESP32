void ConnectWifi(char *ssd,char *pass,int wifiLed)
{
  WiFi.disconnect();
  pinMode(wifiLed, OUTPUT);
  Serial.println("start");
  delay(3000);
  Serial.println("connecting");
  WiFi.begin(ssd,pass);
  while ((!(WiFi.status() == WL_CONNECTED))){
    Serial.printf("....");
    digitalWrite(wifiLed,!digitalRead(wifiLed));
    delay(300);
  }
  Serial.println("conected!!!!");
  digitalWrite(wifiLed,HIGH);
  Serial.println((WiFi.localIP()));
}



 #include "LoRa_E22.h"
LoRa_E22 E22(&Serial1);
struct Signal {
  char type[15] = "Fixaj.com";
  byte temp[4];
} data;
 
 
void setup() {
  Serial.begin(9600);
  E22.begin();
  delay(500);
}
 
void loop() {
 
  ResponseStatus rs = E22.sendFixedMessage(0, 1, 65, &data, sizeof(Signal));
  //Serial.println(rs.getResponseDescription());
 
  delay(1000);
 
  while (E22.available()  > 1) {
    ResponseStructContainer rsc = E22.receiveMessage(sizeof(Signal));
    struct Signal data = *(Signal*) rsc.data;
    Serial.print("Yer: ");
    Serial.println(data.type);
    Serial.print("Ortam Sıcaklığı: ");
    Serial.println(*(float*)(data.temp));
    rsc.close();
  }
}
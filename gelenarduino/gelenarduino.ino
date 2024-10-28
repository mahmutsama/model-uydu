#include "LoRa_E22.h"

LoRa_E22 E22(&Serial1);



struct Signal {
  char type[15];
  byte temp[4];
} data;
 
void setup() {
  Serial.begin(9600);
  E22.begin();
  delay(500);
}
 
void loop() {
  while (E22.available()  > 1) {
 
    // Gelen mesaj okunuyor
    ResponseStructContainer rsc = E22.receiveMessage(sizeof(Signal));
    struct Signal data = *(Signal*) rsc.data;
    Serial.print("Gelen Messaj: ");
    Serial.println(data.type);
    rsc.close();
 
    //Gönderilecek paket veri hazırlanıyor
    struct Signal  {
      char type[15] = "Bebek Odası";
      byte temp[4];
    } data2;
 
    *(float*)(data2.temp) = 19.2;
 
 
    ResponseStatus rs = E22.sendFixedMessage(0, 2, 65, &data2, sizeof(Signal));
    Serial.println(rs.getResponseDescription());
 
  }
 
}

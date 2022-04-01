// xoa buffer va them dia chi cura den vao dim_cct

//#include <SoftwareSerial.h>
byte check_node [] = { 0xe8, 0xff, 0x00, 0x00, 0x00, 0x00, 0x02, 0x01, 0xff, 0xff, 0x82, 0x4b };
byte dim_cct []= { 0xe8, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0xff, 0xff, 0x82, 0x5e, 0xff, 0xff, 0x20, 0x03, 0x00, 0x00, 0x00 };// dieu khien cuogn do sang va mau
byte dim_cct1[] = {0xe8, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0xff, 0xff, 0x82, 0x5e, 0x66, 0x26, 0x20, 0x03, 0x00, 0x00, 0x00};
byte dim_cct2[] = {0xe8, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0xff, 0xff, 0x82, 0x5e, 0x66, 0x26, 0x20, 0x4e, 0x00, 0x00, 0x00};
byte dim_cct3[] = {0xe8, 0xff, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0xff, 0xff, 0x82, 0x5e, 0xff, 0xff, 0x20, 0x4e, 0x00, 0x00, 0x00};
byte off []= { 0xe8, 0xff, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0xff, 0xff, 0x82, 0x02, 0x00, 0x00 };// dieu khien on off
byte mac_High;
byte mac_Low;
byte mac_Low_RSP,mac_High_RSP;
byte rxbyte[21];
byte rx[13];
byte rx1[13];
byte rxbyte1[21];
bool time_check=0;
int dem=0;
int reset_main = 0;
bool reset_bit =0;
void setup() {
        Serial2.begin(115200);
        Serial.begin(115200);
     }
void  (*resetFunc) (void)=0;
void loop() {
       unsigned long time1,time2,time3;
       bool crc_rsp;
       Serial.println("main_loop");
      switch(dem)
      {
      case 0: {  
                Serial2.write(check_node,12);
                if(time_check==0)
                {
                  //Serial.println("case 0");
                  time1=millis();
                  time_check=1;
                }
                if(Serial2.available()>0)
                {  
                  time2=millis();
                  crc_rsp=1;
                  //Serial.print("ok");
                  time_check=0;
                }
                else crc_rsp=0;
                if(crc_rsp==1&&(time2-time1<=1500)){
                if(Serial2.read()==0x0a){
                rx[0]=0x0a;
                Serial2.readBytes(rx1,12);
                for(int i=0;i<12;i++) rx[i+1]=rx1[i];
                Serial.println("case 0");
                for(int i=0;i<12;i++) {Serial.print(rx[i],HEX); Serial.print(" ");}
                Serial.print("\r\n");
                if (rx[0] == 0x0a && rx[3] == 0x81) {
                mac_High=rx[5];
                mac_Low=rx[4];  
                dem=1;
                }
                else dem=0;
                for(int i=0;i<12;i++){ rx[i]=0;rx1[i]=0;}
                while((millis()-time1)<=1000);
                }
                crc_rsp=0;
                }
                break;
              }        
      case 1: { 
                dim_cct [8]=mac_Low;
                dim_cct [9]=mac_High;
                if(time_check==0)
                { 
                  Serial2.write(dim_cct,19);  
                  time1=millis();
                  time_check=1;
                }
                if(Serial2.available()>0)
                {  time2=millis();
                   crc_rsp=1;
                } 
                else
                {
                  crc_rsp=0;time3= millis();
                  if((time3-time1)>1500) dem=0;
                }
                if(crc_rsp==1&&(time2-time1<=1500))
                {             
                  if(Serial2.read()==0x0f)
                  { if(Serial2.read()==0x00)
                   { Serial2.readBytes(rxbyte1,19);
                    rxbyte[0]=0x0f;rxbyte[1]=0x00;
                    for(int i=0;i<19;i++) rxbyte[i+2]=rxbyte1[i];
                    Serial.println("case 1");
                    for(int i=0;i<19;i++) {Serial.print(rxbyte[i],HEX); Serial.print(" ");}
                    Serial.print("\r\n");
                    if (rxbyte[0] == 0x0f && rxbyte[3] == 0xb5&&rxbyte[6]==mac_Low&&rxbyte[7]==mac_High) dem=2;
                    else dem=0;
                    for(int i=0;i<19;i++) {rxbyte[i]=0;rxbyte1[i]=0;}
                    while((millis()-time1)<=1500);
                    time_check=0;
                   }
                  }
                  crc_rsp=0;
                }
                break;
              }
      case 2: { dim_cct1 [8]=mac_Low;
                dim_cct1 [9]=mac_High;
                if(time_check==0)
                { 
                  Serial2.write(dim_cct1,19);  
                  time1=millis();
                  time_check=1;
                }
                if(Serial2.available()>0)
                {  time2=millis();
                   crc_rsp=1;
                } 
                else
                {
                  crc_rsp=0;time3= millis();
                  if((time3-time1)>1500) dem=0;
                }
                if(crc_rsp==1&&(time2-time1<=1500))
                {             
                  if(Serial2.read()==0x0f)
                  { if(Serial2.read()==0x00)
                    {Serial2.readBytes(rxbyte1,19);
                    rxbyte[0]=0x0f;rxbyte[1]=0x00;
                    for(int i=0;i<19;i++) rxbyte[i+2]=rxbyte1[i];
                    Serial.println("case 2");
                    for(int i=0;i<19;i++) {Serial.print(rxbyte[i],HEX); Serial.print(" ");}
                    Serial.print("\r\n");
                    if (rxbyte[0] == 0x0f && rxbyte[3] == 0xb5&&rxbyte[6]==mac_Low&&rxbyte[7]==mac_High) dem=3;
                    else dem=0;
                    for(int i=0;i<19;i++) {rxbyte[i]=0;rxbyte1[i]=0;}
                    while((millis()-time1)<=1500);
                    time_check=0;
                    }
                  }
                  crc_rsp=0;
                }
                break;
              }
      case 3: { dim_cct2 [8]=mac_Low;
                dim_cct2 [9]=mac_High;
                if(time_check==0)
                { 
                  Serial2.write(dim_cct2,19);  
                  time1=millis();
                  time_check=1;
                }
                if(Serial2.available()>0)
                {  time2=millis();
                   crc_rsp=1;
                } 
                else
                {
                  crc_rsp=0;time3= millis();
                  if((time3-time1)>1500) dem=0;
                }
                if(crc_rsp==1&&(time2-time1<=1500))
                {             
                  if(Serial2.read()==0x0f)
                  { if(Serial2.read()==0x00)
                    {Serial2.readBytes(rxbyte1,19);
                    rxbyte[0]=0x0f;rxbyte[1]=0x00;
                    for(int i=0;i<19;i++) rxbyte[i+2]=rxbyte1[i];
                    Serial.println("case 3");
                    for(int i=0;i<19;i++) {Serial.print(rxbyte[i],HEX); Serial.print(" ");}
                    Serial.print("\r\n");
                    if (rxbyte[0] == 0x0f && rxbyte[3] == 0xb5&&rxbyte[6]==mac_Low&&rxbyte[7]==mac_High) dem=4;
                    else dem=0;
                    for(int i=0;i<19;i++) {rxbyte[i]=0;rxbyte1[i]=0;}
                    while((millis()-time1)<=1500);
                    time_check=0;
                    }
                  }
                  crc_rsp=0;
                }
                break;
              }
      case 4: { dim_cct3 [8]=mac_Low;
                dim_cct3 [9]=mac_High;
                if(time_check==0)
                { 
                  Serial2.write(dim_cct3,19);  
                  time1=millis();
                  time_check=1;
                }
                if(Serial2.available()>0)
                {  time2=millis();
                   crc_rsp=1;
                } 
                else
                {
                  crc_rsp=0;time3= millis();
                  if((time3-time1)>1500) dem=0;
                }
                if(crc_rsp==1&&(time2-time1<=1500))
                {             
                  if(Serial2.read()==0x0f)
                  { if(Serial2.read()==0x00)
                    {Serial2.readBytes(rxbyte1,19);
                    rxbyte[0]=0x0f;rxbyte[1]=0x00;
                    for(int i=0;i<19;i++) rxbyte[i+2]=rxbyte1[i];
                    Serial.println("case 4");
                    for(int i=0;i<19;i++) {Serial.print(rxbyte[i],HEX); Serial.print(" ");}
                    Serial.print("\r\n");
                    if (rxbyte[0] == 0x0f && rxbyte[3] == 0xb5&&rxbyte[6]==mac_Low&&rxbyte[7]==mac_High) dem=5;
                    else dem=0;
                    for(int i=0;i<19;i++) {rxbyte[i]=0;rxbyte1[i]=0;}
                    while((millis()-time1)<=1500);
                    time_check=0;
                    }
                  }
                  crc_rsp=0;
                }
                break;
              }
      case 5: { 
                off [8]=mac_Low;
                off [9]=mac_High;
                if(time_check==0)
                { 
                  Serial2.write(off,14);  
                  time1=millis();
                  time_check=1;
                }
                if(Serial2.available()>0)
                {  time2=millis();
                   crc_rsp=1;
                } 
                else
                {
                  crc_rsp=0;time3= millis();
                  if((time3-time1)>1500) dem=0;
                }
                if(crc_rsp==1&&(time2-time1<=1500))
                {             
                  if(Serial2.read()==0x0a)
                  {
                    Serial2.readBytes(rxbyte1,14);
                    rxbyte[0]=0x0a;
                    for(int i=0;i<14;i++) rxbyte[i+1]=rxbyte1[i];
                    Serial.println("case 5");
                    for(int i=0;i<14;i++) {Serial.print(rxbyte[i],HEX); Serial.print(" ");}
                    Serial.print("\r\n");
                    if (rxbyte[0] == 0x0a && rxbyte[3] == 0xb5&&rxbyte[4]==mac_Low&&rxbyte[5]==mac_High) dem=0;
                    else dem = 0;
                    for(int i=0;i<19;i++) {rxbyte[i]=0;rxbyte1[i]=0;}
                    while((millis()-time1)<=1000); 
                    reset_bit=1;
                    time_check=0;
                  }
                  crc_rsp=0;
                }
                break;
              }
                
      }
        delay(10);
        if(reset_bit){ Serial.print("millis : ");Serial.print(time1); resetFunc();}
        reset_main++;
        if(reset_main==250) resetFunc();
      //  resetFunc();
        //
}

#define txPin 8 
#define rxPin 2 
//hello
void setup()
          {
              pinMode(rxPin, INPUT);
              pinMode(txPin, OUTPUT);

              Serial.begin(115200); 
              Serial.println("Scan is DEFAULT mode.\nType 'send [code]' to send command.");

              attachInterrupt(0, grab, CHANGE); 
              interrupts();
           }

volatile static long lastCode = 0;

void loop() 
          {
              if (lastCode > 0)
              {
                   Serial.print("Catch:");
                   Serial.println(lastCode & 0xfff);
                   lastCode = 0;
               }

              if(Serial.available()>0)
              {
                   String  cmd = "";
                              while (Serial.available() > 0) 
                              {
                                    char inChar = Serial.read();
                                    cmd += inChar;
                               }

              if(cmd.substring(0, 4)=="send")
              {
                  Serial.println("You are in 'SEND-MODE'\n");
                  String  code = cmd.substring(4);
                  Serial.println("You send:" + code);
                  SendCame4(code.toInt());
                  Serial.println("OK");
                  Serial.println();
              }
/*
              else if(cmd.substring(0, 4)=="brut")
              {
                                        
                  Serial.println("You are in 'Brutforce-MODE'\n");
                                        
                                for(int cu=1000;cu<4094;cu++)
                                {
                                      Serial.print("send: ");
                                      Serial.println(cu);
                                      SendCame4(cu);
                                      delay(800);

                                          if(cu==4093)
                                          {
                                              Serial.print("Brutforce is over\n");
                                              break;
                                           }
                                                                   
                                  }
                                        
                }
*/                                      
                else
                {
                    Serial.println("You are in DEFAULT scan-mode.\nType 'send [code]' to send command.");
                    Serial.println();
                 }
}           
  
delay(1000);

}


void SendCame4(long Code) 
          {
                    for (int j = 0; j < 7; j++) 
                    { 
                              digitalWrite(txPin, HIGH);
                              delayMicroseconds(320);
                              digitalWrite(txPin, LOW);
                                        for (int i = 12; i > 0; i--) 
                                        {
                                                  byte b = bitRead(Code, i - 1); 
                                                  if (b) 
                                                  {
                                                            digitalWrite(txPin, LOW); 
                                                            delayMicroseconds(640);
                                                            digitalWrite(txPin, HIGH);
                                                            delayMicroseconds(320);
                                                  }
                                                  else 
                                                  {
                                                            digitalWrite(txPin, LOW); 
                                                            delayMicroseconds(320);
                                                            digitalWrite(txPin, HIGH);
                                                            delayMicroseconds(640);
                                                  }
                                        }
                              digitalWrite(txPin, LOW);
                              delayMicroseconds(11520);
                    }
          }

#define MAX_DELTA 200
boolean CheckValue(unsigned int base, unsigned int value)
          {
          return ((value == base) || ((value > base) && ((value - base) < MAX_DELTA)) || ((value < base) && ((base - value) < MAX_DELTA)));
          }

volatile unsigned long prevtime;
volatile unsigned int lolen, hilen, state;
volatile static byte cameCounter = 0; 
volatile static long cameCode = 0;

void grab() 
          {
                    state = digitalRead(rxPin);
                    if (state == HIGH)
                              lolen = micros() - prevtime;
                    else
                    hilen = micros() - prevtime;
                    prevtime = micros();

                    if (state == LOW)
                              {
                                        if (CheckValue(320, hilen) && CheckValue(640, lolen))
                                                  {
                                                            cameCode = (cameCode << 1) | 1;
                                                            cameCounter++;
                                                  }
                                        else if (CheckValue(640, hilen) && CheckValue(320, lolen))
                                                  {
                                                            cameCode = (cameCode << 1) | 0;
                                                            cameCounter++;
                                                  }
                                        else cameCounter = 0;
                              } 
                    else if (lolen > 1000 && (cameCounter == 12 || cameCounter == 13) && ((cameCode & 0xfff) != 0xfff))
                              {
                                        lastCode = cameCode & 0xfff;
                                        cameCounter = 0;
                                        cameCode = 0;
                              }
          } 

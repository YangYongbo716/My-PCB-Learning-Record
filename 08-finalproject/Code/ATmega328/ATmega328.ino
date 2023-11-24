#include <Adafruit_AS7341.h>
Adafruit_AS7341 as7341;
int previousValue = 0;    // 上一次的光照强度值
unsigned long previousMillis = 0;  // 上一次记录的时间戳
int frequency = 0;  // 光照强度变化频率

void setup(){
  Serial.begin(115200);
  pinMode(A0,INPUT);

  //Wait for communication with the host computer serial monitor
  while (!Serial) {
    delay(1);
  }
  
  if (!as7341.begin()){
    Serial.println("Could not find AS7341");
    while (1) { delay(10); }
  }

  as7341.setATIME(100);
  as7341.setASTEP(999);
  as7341.setGain(AS7341_GAIN_256X);
}

void loop(){

  int lightIntense = analogRead(A0);

  //Read all channels at the same time and store in as7341 object
  if (!as7341.readAllChannels()){
    Serial.println("Error reading all channels!");
    return;
  }

  unsigned long currentMillis = millis();  // 获取当前时间戳
  int change = abs(lightIntense - previousValue);
  // 如果已经过去了100毫秒
  if (currentMillis - previousMillis >= 100) {
    // 计算光照强度变化频率
    frequency = change / 0.1;  // 这里假设变化是以每100毫秒为单位的

    // 输出结果或进行其他处理
    Serial.print(frequency);
    Serial.print(" ");

    // 更新上一次记录的值和时间戳
    previousValue = lightIntense;
    previousMillis = currentMillis;

  Serial.print(lightIntense);
  Serial.print(" ");

  Serial.print(frequency);
  Serial.print(" ");

  // Print out the stored values for each channel
  Serial.print(as7341.getChannel(AS7341_CHANNEL_415nm_F1));
  Serial.print(" ");
  Serial.print(as7341.getChannel(AS7341_CHANNEL_445nm_F2));
  Serial.print(" ");
  Serial.print(as7341.getChannel(AS7341_CHANNEL_480nm_F3));
  Serial.print(" ");
  Serial.print(as7341.getChannel(AS7341_CHANNEL_515nm_F4));
  Serial.print(" ");
  Serial.print(as7341.getChannel(AS7341_CHANNEL_555nm_F5));
  Serial.print(" ");
  Serial.print(as7341.getChannel(AS7341_CHANNEL_590nm_F6));
  Serial.print(" ");
  Serial.print(as7341.getChannel(AS7341_CHANNEL_630nm_F7));
  Serial.print(" ");
  Serial.println(as7341.getChannel(AS7341_CHANNEL_680nm_F8));

  int vibrationIntense = map(frequency,0,1000,0,255);
  analogWrite(9,vibrationIntense);

  }
  
}
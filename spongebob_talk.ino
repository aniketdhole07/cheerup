#include <M5Core2.h>
#include <driver/i2s.h>
#include <WiFi.h>
//install below libraries
//
//cd ~/Arduino/libraries
//git clone https://github.com/earlephilhower/ESP8266Audio
//git clone https://github.com/Gianbacchio/ESP8266_Spiram


#include "AudioFileSourceSD.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"


AudioGeneratorMP3 *mp3;
AudioFileSourceSD *file;
AudioOutputI2S *out;
AudioFileSourceID3 *id3;

#define OUTPUT_GAIN 10

void setup()
{
  M5.begin();
  M5.Axp.SetSpkEnable(true);

  WiFi.mode(WIFI_OFF); 
  delay(500);
  
  M5.Lcd.setTextFont(2);
  M5.Lcd.printf("Sample MP3 playback begins...\n");
  
  file = new AudioFileSourceSD("/sponge.mp3");
  id3 = new AudioFileSourceID3(file);
  out = new AudioOutputI2S(0, 0); // Output to builtInDAC
  out->SetPinout(12, 0, 2);
  out->SetOutputModeMono(true);
  out->SetGain((float)OUTPUT_GAIN/100.0);
  mp3 = new AudioGeneratorMP3();
  mp3->begin(id3, out);
  M5.Lcd.drawJpgFile(SD, "/b.jpg");
}

void loop()
{
  if (mp3->isRunning()) {
    if (!mp3->loop()) {
      mp3->stop();
    }
  } else {
    file = new AudioFileSourceSD("/sponge.mp3");
  id3 = new AudioFileSourceID3(file);
  mp3 = new AudioGeneratorMP3();
  mp3->begin(id3, out);
    
    Serial.printf("MP3 done\n");
    
  }
}

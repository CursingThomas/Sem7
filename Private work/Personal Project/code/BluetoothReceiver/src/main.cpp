/*#include <Arduino.h>
#include "AudioTools.h"
#include "AudioLibs/AudioA2DP.h"
#include "BluetoothA2DPSink.h"
//BluetoothA2DPSink a2dp_sink;
BluetoothA2DPSink input;
A2DPStream x;
I2SStream output;
StreamCopy copier(output, x);


void setup() {
  // put your setup code here, to run once:
  auto cfg = output.defaultConfig(TX_MODE);
  cfg.pin_bck = 26;
  cfg.pin_ws = 25;
  cfg.pin_data = 22;
  auto cfg1 = x.defaultConfig(RX_MODE);
  x.begin(cfg1);
  output.begin(cfg);
  copier.begin();
}

void loop() {
  copier.copy();
} */

#include "BluetoothA2DPSink.h"
#include "AudioTools.h"
#define BCK_PIN 26
#define WS_PIN 25
#define DATA_PIN 22

BluetoothA2DPSink a2dp_sink;
I2SStream i2s;
AudioEffectStream effects(i2s);
ADSRGain adsr(0.0001,0.0001, 0.9 , 0.0002);
Fuzz fuzz(10, 300);
StreamCopy copier (i2s, effects);
Distortion diss(9000, 10000);
PitchShift shifter (2, 1000);

// Write data to I2S
void read_data_stream(const uint8_t *data, uint32_t length) {
  effects.write(data, length);
}

void setup() {
  Serial.begin(115200);

  // register callback
  a2dp_sink.set_stream_reader(read_data_stream, false);
  
  // Start Bluetooth Audio Receiver
  a2dp_sink.set_auto_reconnect(false);
  a2dp_sink.start("a2dp-i2s");
  
  // setup output
  auto cfg = i2s.defaultConfig();
  cfg.pin_bck = BCK_PIN;
  cfg.pin_ws = WS_PIN;
  cfg.pin_data = DATA_PIN;
  i2s.begin(cfg);
  copier.begin();
  effects.begin(cfg);
  //effects.addEffect(shifter);
  
}

void loop() { 
  copier.copy();
 }
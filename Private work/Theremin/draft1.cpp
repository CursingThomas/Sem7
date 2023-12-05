#include <Arduino.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>

#define SERIAL_BAUD_RATE 9600

#define PIN_BUTTON 33
#define BUTTON_POLL_RATE_MS 50

#define PIN_TRIGGER 31
#define PIN_ECHO 32

#define SAMPLE_RATE_MS 100
#define SAMPLE_MAX 3000

#define TONE_MIN 50
#define TONE_MAX 2000

#define TONE_ADJUSTMENT_INTERVAL_US 1000

AudioSynthWaveform waveform1;
AudioOutputI2S i2s1;
AudioConnection patchCord1(waveform1, 0, i2s1, 0);
AudioConnection patchCord2(waveform1, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1;

uint32_t lastButtonPollTimestamp = 0;
int lastButtonState = LOW;
uint32_t lastSampleTimestamp = 0;
uint32_t frequencyTarget = 0;
uint32_t frequencyCurrent = 0;
uint8_t waveformIndex = 0;

void setup() {
	Serial.begin(SERIAL_BAUD_RATE);
	pinMode(PIN_BUTTON, INPUT_PULLUP);
	pinMode(PIN_TRIGGER, OUTPUT);
	pinMode(PIN_ECHO, INPUT);

	AudioMemory(20);
	sgtl5000_1.enable();
	sgtl5000_1.volume(0.32);
	waveform1.begin(WAVEFORM_SINE);
	waveform1.amplitude(0.75);
	waveform1.frequency(50);
	waveform1.pulseWidth(0.15);
}

void loop() {
	if ((millis() - lastButtonPollTimestamp) >= BUTTON_POLL_RATE_MS) {
		int currentButtonState = digitalRead(PIN_BUTTON);
		if ((lastButtonState != currentButtonState) && (currentButtonState == LOW)) {
			waveformIndex++;
			if (waveformIndex >= 5) {
				waveformIndex = 0;
			}
			switch (waveformIndex) {
			case 0:
				Serial.printf("Waveform: %s\n", "SINE");
				waveform1.begin(WAVEFORM_SINE);
				break;
			case 1:
				Serial.printf("Waveform: %s\n", "WAVEFORM_SQUARE");
				waveform1.begin(WAVEFORM_SQUARE);
				break;
			case 2:
				Serial.printf("Waveform: %s\n", "WAVEFORM_TRIANGLE");
				waveform1.begin(WAVEFORM_TRIANGLE);
				break;
			case 3:
				Serial.printf("Waveform: %s\n", "WAVEFORM_SAWTOOTH");
				waveform1.begin(WAVEFORM_SAWTOOTH);
				break;
			case 4:
				Serial.printf("Waveform: %s\n", "WAVEFORM_SAWTOOTH_REVERSE");
				waveform1.begin(WAVEFORM_SAWTOOTH_REVERSE);
				break;
			default:
				break;
			}
		}
		lastButtonState = currentButtonState;
		lastButtonPollTimestamp = millis();
	}


	if ((millis() - lastSampleTimestamp) >= SAMPLE_RATE_MS) {
		digitalWrite(PIN_TRIGGER, LOW);
		delayMicroseconds(2);
		digitalWrite(PIN_TRIGGER, HIGH);
		delayMicroseconds(10);
		digitalWrite(PIN_TRIGGER, LOW);

		uint32_t duration = pulseIn(PIN_ECHO, HIGH);
		// uint32_t distance = duration * 0.034 / 2; // cm
		if (duration > SAMPLE_MAX) {
			duration = SAMPLE_MAX;
		}

		duration = SAMPLE_MAX - duration; // Reverse tone (low = far, high = close)

		frequencyTarget = map(duration, 0, SAMPLE_MAX, TONE_MIN, TONE_MAX);

		Serial.printf("duration: %u, frequencyTarget: %u, frequencyCurrent: %u\n", duration, frequencyTarget, frequencyCurrent);

		lastSampleTimestamp = millis();
	}

	waveform1.frequency(frequencyCurrent);
	if (frequencyTarget > frequencyCurrent) {
		frequencyCurrent++;
	} else if (frequencyTarget < frequencyCurrent) {
		frequencyCurrent--;
	}

	delayMicroseconds(TONE_ADJUSTMENT_INTERVAL_US);
}

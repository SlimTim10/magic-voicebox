#include <SD.h>
#include <TMRpcm.h>
#include <SPI.h>

enum pins {
	SD_CS_PIN = 4,
	SPEAKER_PIN = 9,
	RF_RX_PIN = 11,
	BTN_PIN = 2,
};

TMRpcm tmrpcm;
uint8_t wavNum;
char *filename;

void setup() {
	pinMode(BTN_PIN, OUTPUT);
	
	tmrpcm.speakerPin = SPEAKER_PIN;

	if (!SD.begin(SD_CS_PIN)) {
		return;
	}

	wavNum = 0;
	filename = (char *) malloc(32 * sizeof(char));
}

void loop() {
	if (digitalRead(BTN_PIN) == HIGH) {
		wavNum = (wavNum % 6) + 1;
		snprintf(filename, 32, "%d.wav", wavNum);
		tmrpcm.play(filename);
		delay(10);
		while (digitalRead(BTN_PIN) == HIGH);
		delay(10);
	}
}

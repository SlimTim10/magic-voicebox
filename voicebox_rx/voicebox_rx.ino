#include <SD.h>
#include <TMRpcm.h>
#include <SPI.h>

enum pins {
	SD_CS_PIN = 4,
	SPEAKER_PIN = 9,
	RF_RX_PIN = 2,
};

enum {
	BUF_SIZE = 32,
};

TMRpcm tmrpcm;
char *buf;

void play_num(uint8_t n) {
	snprintf(buf, BUF_SIZE, "%d.wav", n);
	tmrpcm.play(buf);
	while (tmrpcm.isPlaying());
}

void speak(uint8_t n) {
	if (n >= 1 && n < 20) {
		play_num(n);
	} else if (n >= 20 && n < 100) {
		uint8_t tens = ((uint8_t) (n / 10)) * 10;
		play_num(tens);
		uint8_t ones = (n % 10);
		if (ones > 0) {
			play_num(ones);
		}
	} else if (n == 100) {
		play_num(100);
	} else {
		return;
	}
}


void setup() {
	tmrpcm.speakerPin = SPEAKER_PIN;

	if (!SD.begin(SD_CS_PIN)) {
		return;
	}

	buf = (char *) malloc(BUF_SIZE * sizeof(char));

	uint8_t i;
	for (i = 1; i <= 100; i++) {
		speak(i);
		delay(500);
	}
}

void loop() {
	
}

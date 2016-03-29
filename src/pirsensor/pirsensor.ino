/*
* PIR sensor tester
*/
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6

int ledPin = 13; // Choose the pin for the LED
int inputPin = 2; // Choose the  input pin (for PIR sensor)
int pirState = LOW; // we start, assuming no motion detected
int val = 0; // variable for reading the pin status


Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, PIN, NEO_GRB + NEO_KHZ800);

int colorMatrix[16][3] = {
	{ 0,0,0 },
	{ 255,255,255 },
	{ 255,0,0 },
	{ 0,255,0 },
	{ 0,0,255 },
	{ 255,255,0 },
	{ 0,255,255 },
	{ 255,0,255 },
	{ 192,192,192 },
	{ 128,128,128 },
	{ 128,0,0 },
	{ 128,128,0 },
	{ 0,128,0 },
	{ 128,0,128 },
	{ 0,128,128 },
	{ 0,0,128 }
};





void setup() {
	// put your setup code here, to run once:
	pinMode(ledPin, OUTPUT); // declare LED as output
	pinMode(inputPin, INPUT); // declare sensor as input
	Serial.begin(9600);
	strip.begin();
	strip.show();
}

void loop() {
	// put your main code here, to run repeatedly:
	val = digitalRead(inputPin); // read the INPUT value
	delay(500);
	Serial.println("");
	Serial.print("val: ");
	Serial.println(val);
	if (val == HIGH) {
		digitalWrite(ledPin, HIGH); // turn LED on
		colorWipeLaw(2000);
		rainbow(5000);

		delay(500);


		if (pirState == LOW) {
			// we have just turned on
			Serial.println("Motion detected");
			// we only want to print on the output change, not state
			pirState = HIGH;

		}
	}
	else {
		digitalWrite(ledPin, LOW); // turn LED off
		if (pirState == HIGH) {
			turnLedOff();
			// we have just turned off
			Serial.println("Motion ended!");
			// we only want to print on the output, not state
			pirState = LOW;
			delay(500);
		}

	}


}

void colorWipeLaw(uint16_t wait) {
	uint32_t c;
	int32_t r;
	int32_t g;
	int32_t b;
	int x;
	for (uint16_t i = 0; i<strip.numPixels(); i++) {
		x = random(0, 15);

		r = colorMatrix[x][0];
		g = colorMatrix[x][1];
		b = colorMatrix[x][2];

		Serial.print("x i R G B : ");
		Serial.print(x);
		Serial.print(" ");
		Serial.print(i);
		Serial.print(" ");
		Serial.print(r);
		Serial.print(" ");
		Serial.print(g);
		Serial.print(" ");
		Serial.print(b);
		Serial.println("");
		c = strip.Color(r, g, b);
		strip.setPixelColor(i, c);

	}
	strip.show();
	delay(wait);



}
void turnLedOff() {
	for (uint16_t i = 0; i<strip.numPixels(); i++) {
		strip.setPixelColor(i, 0);
	}
	strip.show();
	delay(500);
}

void rainbow(uint8_t wait) {
	uint16_t i, j;

	for (j = 0; j<256; j++) {
		for (i = 0; i<strip.numPixels(); i++) {
			strip.setPixelColor(i, Wheel((i + j) & 255));
		}
		strip.show();
		delay(wait);
	}
}


uint32_t Wheel(byte WheelPos) {
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85) {
		return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	if (WheelPos < 170) {
		WheelPos -= 85;
		return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
	WheelPos -= 170;
	return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}



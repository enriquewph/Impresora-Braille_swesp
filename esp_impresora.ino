#include <ESP32Encoder.h>

#define ENCODER_A 33
#define ENCODER_B 32

//lucas es un capo


ESP32Encoder encoder;
 
void setup()
{
    // put your setup code here, to run once:
    pinMode(2, OUTPUT);
    // Attache pins for use as encoder pins
	encoder.attachHalfQuad(ENCODER_A, ENCODER_B);
    Serial.begin(115200);

	// set starting count value
	encoder.setCount(37);
	Serial.println("Encoder Start = "+String((int32_t)encoder.getCount()));
}

void loop()
{
    // put your main code here, to run repeatedly:
    Serial.println("Encoder count = "+String((int32_t)encoder.getCount()));
	delay(100);
}

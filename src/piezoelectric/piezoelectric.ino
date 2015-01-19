int sensorPin = A0;
int sensorValue = 0;
int thresold = 200;
int delayTime = 500;

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	sensorValue = analogRead(sensorPin);
	if(sensorValue > thresold){
	    Serial.print("Sensor = ");
	    Serial.println(sensorValue, DEC);
	}
	delay(delayTime);
}
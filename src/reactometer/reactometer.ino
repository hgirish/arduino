int state = 0;
int ledArray[] = {8,9,10,11,12};
int count = 0;
int timer = 50;
int stopLed = 6;
int goLed = 7;
int randMin = 250;
int randMax = 750;
int startDelay;



void setup(){
	Serial.begin(9600);
	Serial.print(state);
	for (count =0; count < 5; count++) {
		pinMode(ledArray[count], OUTPUT);
	}
	attachInterrupt(0, ledOnOff, RISING);
	pinMode(stopLed, OUTPUT);
	pinMode(goLed, OUTPUT);
	randomSeed(analogRead(0));
}

void loop(){
	if(state == 0){
	    digitalWrite(stopLed, HIGH);
	    digitalWrite(goLed, LOW);
	    for(count=0; count<5; count++){
	        digitalWrite(ledArray[count], LOW);
	    }
	}
	if(state == 1){
	    startDelay = random(randMin, randMax);
	    delay(startDelay);
	    digitalWrite(stopLed, LOW);
	    digitalWrite(goLed, HIGH);
	    for( count=0; count<5; count++){
	        digitalWrite(ledArray[count], HIGH);
	        delay(timer);
	        if(state == 2){
	            break;
	        }
	    }
	}
	
}

void ledOnOff() {

	static unsigned long lastMillis = 0;
	unsigned long newMillis = millis();
	if(newMillis - lastMillis < 50){
	    
		Serial.print(state);
		Serial.print(" lt 50 ledOnOff called\n");
	} 
	else {
		Serial.print(state);
		Serial.print("ledOnOff called\n");
		
		state = state + 1;
		Serial.print(state);
		Serial.print("ledOnOff after increment called\n");
		if(state == 3){
		    state = 0;
		}
		lastMillis = newMillis;
		Serial.print(state);
	}
	

}


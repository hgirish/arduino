volatile int state = LOW;
int ledArray[] = {8,9,10,11,12};
int count = 0;
int timer = 75;
int pause = 500;

void setup(){
	for (count =0; count < 5; count++) {
	pinMode(ledArray[count], OUTPUT);
	}
	attachInterrupt(0, ledOnOff, RISING);
}

void loop(){
	if(state){
	    for(int count=0; count<5; count++){
	        digitalWrite(ledArray[count], HIGH);
	        delay(timer);
	    }
	    delay(pause);

	    for(int count=0; count<5; count++){
	        digitalWrite(ledArray[count], LOW);
	        delay(timer);
	    }
	    delay(pause);
	}	
}

void ledOnOff() {
	static unsigned long lastMillis = 0;
	unsigned long newMillis = millis();
	if(newMillis - lastMillis < 50){
	    
	} 
	else {
		state = !state;
		lastMillis = newMillis;
	}
}


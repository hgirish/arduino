volatile int state = 0;
int ledArray[] = {8,9,10,11,12};
int count = 0;
int timer = 50;
int stopLed = 6;
int goLed = 7;
int randMin = 250;
int randMax = 750;
int startDelay;
volatile float time;
float start_time;


void setup(){	
	for (count =0; count < 5; count++) {
		pinMode(ledArray[count], OUTPUT);
	}
	attachInterrupt(0, ledOnOff, RISING);
	pinMode(stopLed, OUTPUT);
	pinMode(goLed, OUTPUT);
	randomSeed(analogRead(0));
	Serial.begin(9600);
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
	    start_time = millis();
	    digitalWrite(stopLed, LOW);
	    digitalWrite(goLed, HIGH);
	    for( count=0; count<5; count++){
	    	delay(timer);
	      
	        if(state == 2){
	        	time = (time - start_time) / 1000;
	        	Serial.print("Reaction time: ");
	        	Serial.print(time);
	        	Serial.println(" seconds");
	        	delay(1000);
	            break;
	        }
	        digitalWrite(ledArray[count], HIGH);
	    }
	}
	
}

void ledOnOff() {

	static unsigned long lastMillis = 0;
	unsigned long newMillis = millis();
	if(newMillis - lastMillis < 50){
	    
		Serial.print(state);
		Serial.println(" lt 50 ledOnOff called");
	} 
	else {
		Serial.print(state);
		Serial.println("ledOnOff called");
		
		state = state + 1;
		Serial.print(state);

		Serial.println("ledOnOff after increment called");
		if(state == 2){
		    time = millis();
		}
		if(state == 3){
		    state = 0;
		}
		lastMillis = newMillis;
		Serial.print(state);
	}
	

}


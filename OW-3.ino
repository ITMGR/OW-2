// This #include statement was automatically added by the Particle IDE.
// This #include statement was automatically added by the Particle IDE.
#include "dht.h"
// This #include statement was automatically added by the Particle IDE.
#include "floatToString.h"
// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain
#define DHTPIN 2     // what pin we're connected to
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11		// DHT 11
#define DHTTYPE DHT11		// DHT 22 (AM2302)
//#define DHTTYPE DHT21		// DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
// Timer
unsigned long lastTime_1 = 0UL;
unsigned long lastTime_2 = 0UL;
unsigned long Timmer_1 = 0UL;
unsigned long Timmer_2 = 0UL;
char publishString[40];
// Timer


DHT dht(DHTPIN, DHTTYPE);
int photoresistor = A0;
int analogvalue;
char buffer[25];

void setup() {
	Serial.begin(9600);
//	Serial.println("DHTxx test!");
	// floatToString(buffer, 1000000.321, 5);
pinMode(photoresistor,INPUT);
	dht.begin();
	//agenda.insert(Hum, 3500,0);
	Timmer_1 = 15*1000UL;
    Timmer_2 = 20*1000UL;

}

void loop() {
// Wait a few seconds between measurements.
	unsigned long now = millis();
    //Every 15 seconds publish uptime
    if (now-lastTime_1>Timmer_1) {
        lastTime_1 = now;
        // now is in milliseconds
        unsigned nowSec = now/1000UL;
        unsigned sec = nowSec%60;
        unsigned min = (nowSec%3600)/60;
        unsigned hours = (nowSec%86400)/3600;
        sprintf(publishString,"%u:%u:%u",hours,min,sec);
        //Particle.publish("Uptime",publishString);
        // Reading temperature or humidity takes about 250 milliseconds!
// Sensor readings may also be up to 2 seconds 'old' (its a
// very slow sensor)
	float h = dht.getHumidity();
// Read temperature as Celsius
	float t = dht.getTempCelcius();
// Read temperature as Farenheit
	float f = dht.getTempFarenheit();
// Check if any reads failed and exit early (to try again).
	if (isnan(h) || isnan(t) || isnan(f)) {
		//Serial.println("Failed to read from DHT sensor!");
		Particle.publish("Error", "Failed to read from DHT sensor!");
		return;
	}

// Compute heat index
// Must send in temp in Fahrenheit!
	float hi = dht.getHeatIndex();
	float dp = dht.getDewPoint();
	float k = dht.getTempKelvin();
	Particle.publish("Humid",/*floatToString(buffer, h, 5)*/ String(h),60,PRIVATE);
	//Particle.publish("Humid", String(h));
    Particle.publish("Temp",String(t),60,PRIVATE);
	Particle.publish("DewP",String(dp),60,PRIVATE);
	Particle.publish("HeatI",String(hi),60,PRIVATE);

    }
    if (now-lastTime_2>Timmer_2) {
        lastTime_2 = now;
        //Particle.publish("Timmer2",String(Timmer_2),60,PRIVATE);
        	 //analogvalue = analogRead(photoresistor) ;

	 Particle.publish("Light",String(analogRead(photoresistor)),60,PRIVATE);
    }
//	delay(60*1000);
}

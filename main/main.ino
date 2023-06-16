#define led LED_BUILTIN
#define SensorForaEsq A4
#define SensorMeioEsq A3
#define SensorMeio    A2
#define SensorMeioDir A1
#define SensorForaDir A0


long now;

void setup() {
pinMode(led, OUTPUT);
now = millis();
Serial.begin(9600);
}

void loop() {
    now = millis();
    delay(1000);
    Serial.println(now);
// put your main code here, to run repeatedly:
// Serial.print(analogRead(SensorForaEsq));
// Serial.print(" | ");
// Serial.print(analogRead(SensorMeioEsq));
// Serial.print(" | ");
// Serial.print(analogRead(SensorMeio));
// Serial.print(" | ");
// Serial.print(analogRead(SensorMeioDir));
// Serial.print(" | ");
// Serial.print(analogRead(SensorForaDir));
// Serial.println();

}
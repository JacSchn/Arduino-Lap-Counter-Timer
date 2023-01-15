int light = 0;
const int ledPin = 13;
const int indPin = 12;

const int startPin = 2;
const int stopPin = 3;

float startMillis = 0;
float currentMillis = 0;
float lastLapMillis = 0;
float lapMillis = 0;
float elapsedMillis = 0;

int startSet = 0;
int lapSet = 0;
int started = 0;

int lapNum;
float overallTime;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0,INPUT);

  pinMode(startPin, INPUT);
  pinMode(stopPin, INPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(indPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  light = analogRead(A0);
  int startState = digitalRead(startPin);
  int stopState = digitalRead(stopPin);

  digitalWrite(ledPin, HIGH);
  if((startState == LOW) && (stopState != LOW)) {
    digitalWrite(indPin, HIGH);
    if (startSet == 0) {
      startMillis = millis();
      currentMillis = 0;
      lastLapMillis = startMillis;
      lapNum = 0;
      lapSet = 0;
      startSet++;
      started++;
      Serial.print("start");
      Serial.print("\n");
    }
  }
  if((stopState == LOW) && (startState != LOW)){
    digitalWrite(indPin, LOW);
    
    if (currentMillis == 0) {
      currentMillis = millis();
      //elapsedMillis = (currentMillis - startMillis);
      Serial.print("Overall Time: ");
      Serial.print(overallTime / 1000);
      Serial.print("\n");
      Serial.print("Laps: ");
      Serial.print(lapNum);
      Serial.print("\n");
      startSet = 0;
      started = 0;
      overallTime = 0;
    }
  }

  if (light < 100) {
    if (lapSet == 0 && started == 1) {
      lapNum++;
      lapSet++;
      currentMillis = millis();
      lapMillis = (currentMillis - lastLapMillis);
      lastLapMillis = currentMillis;
      currentMillis = 0;
      overallTime = overallTime + lapMillis;
      Serial.print("Lap ");
      Serial.print(lapNum);
      Serial.print(": ");
      Serial.print(lapMillis / 1000);
      Serial.print("\n");
    }
  }
  if (light > 300) {
    lapSet = 0;
  }

  //Serial.print(light);
  //Serial.print("\n");
}

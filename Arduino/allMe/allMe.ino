// Defining the frequencies for the musical notes (Happy Birthday song)
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

// Defining pin number for the buzzer
int buzzer = 12;  

// Define array for the melody notes
int melody[] = {
  NOTE_C4, NOTE_C4,
  NOTE_D4, NOTE_C4, NOTE_F4,
  NOTE_E4, NOTE_C4, NOTE_C4,
  NOTE_D4, NOTE_C4, NOTE_G4,
  NOTE_F4, NOTE_C4, NOTE_C4,
  NOTE_C5, NOTE_A4, NOTE_F4,
  NOTE_E4, NOTE_D4, NOTE_AS4, NOTE_AS4,
  NOTE_A4, NOTE_F4, NOTE_G4,
  NOTE_F4
};

// Defining array for the durations of notes
int durations[] = {
  4, 8,
  4, 4, 4,
  2, 4, 8,
  4, 4, 4,
  2, 4, 8,
  4, 4, 4,
  4, 4, 4, 8,
  4, 4, 4,
  2
};

// Defining motor one
int motorPin1 = 8;
int motorPin2 = 9;

// Defining motor two
int motor2Pin1 = 6;
int motor2Pin2 = 2;

// Defining LEDS
int led1 = 3; //Yellow
int led2 = 4; //Red

// Define trig and echo pins for ultrasonic sensor
int echoPin = 11;
int trigPin = 10;

int melodyIndex = 0; // Index for the current note in the melody array
unsigned long noteStartTime = 0; //Start time of the current note
unsigned long noteDuration = 0; //Duration of the current note
bool objectDetected = false; //Indicates whether the ultrasonic detects an object or not

// Function to play the Happy Birthday song
void playMelody() {
  if (melodyIndex >= sizeof(durations) / sizeof(int)) {
    melodyIndex = 0;
    noTone(buzzer);
  }

  noteDuration = 1000 / durations[melodyIndex];
  tone(buzzer, melody[melodyIndex], noteDuration);
  noteStartTime = millis();
  melodyIndex++;
}

// Function to rotate wheels forward
void rotateMotorsForward() {
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

// Function to rotate wheels backwards
void rotateMotorsBackward() {
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

// The initial state of all components are set here
void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(buzzer, OUTPUT);  // Buzzer pin as output
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); //This pin has to be input (ultrasonic sensor)
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

// Where the man instructions for the Arduino are located, and looped
void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

// If object is detected within this range
  if (distance < 10) {

    // Turn on both the lights
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);

// Wheels rotate backwards
    rotateMotorsBackward();
    objectDetected = true;
  }
  else { //If nothing is detected
// Wheels rotate forward
    rotateMotorsForward();

// Melody is played
    playMelody();

    // Alternatively flashing lights one by one (100 milliseconds delay in between)
    digitalWrite(led1, HIGH);
    delay(100);
    digitalWrite(led1, LOW);
    delay(100);
    digitalWrite(led2, HIGH);
    delay(100);
    digitalWrite(led2, LOW);
    objectDetected = false;
  }

// If object is out of range
  if (distance >= 200 || distance <= 0) {
    Serial.println("Out of range");
  }
  else {
// Prints measured distance
    Serial.print(distance);
    Serial.println(" cm");
  }
  }

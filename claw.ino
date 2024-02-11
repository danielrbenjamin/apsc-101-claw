//SERVO
#include <Servo.h>
#define SERVO_PIN 9
Servo myservo;

//SONAR
#include <NewPing.h>
#define VCC_PIN 13
#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define GROUND_PIN 10
#define MAX_DISTANCE 500
#define HEIGHT 17
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

bool open = true;
bool updown = true;

void setup() {
  //SONAR
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(GROUND_PIN, OUTPUT);
  pinMode(VCC_PIN, OUTPUT);
  digitalWrite(GROUND_PIN, LOW);
  digitalWrite(VCC_PIN, HIGH);

  //SERVO
  myservo.attach(SERVO_PIN);
  Serial.begin(9600);
}

void loop() {
  //SONAR DISCRETE
  int DISTANCE_IN_CM = sonar.ping_cm();   // read the sonar sensor

  delay(100);
  Serial.print("Ping: ");
  Serial.print(DISTANCE_IN_CM);
  Serial.println("cm");

  DISTANCE_IN_CM = sonar.ping_cm();  // Update the distance before evaluating conditions

  if (open && DISTANCE_IN_CM < HEIGHT && updown) {
    myservo.write(0); // close the claw
    Serial.println("Claw closed");
    open = false;
    updown = false;
    Serial.println("updown false (closed)");

  } else if (!open && DISTANCE_IN_CM < HEIGHT && updown) {
    myservo.write(180); // open the claw if the distance is greater than or equal to 20 cm
    Serial.println("Claw open");
    open = true;
    updown = false;
    Serial.println("updown false (opened)");
  }

  else if (DISTANCE_IN_CM > (HEIGHT+5)) {
    updown = true;
    Serial.println("updown true reset");
  }

}

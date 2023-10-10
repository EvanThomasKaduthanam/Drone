#include <Servo.h>

#define MIN_PULSE_LENGTH 1000
#define MAX_PULSE_LENGTH 2000

Servo motA, motB, motC, motD;
char data;

void setup()
{
  int iResult = checkWiring();
  if (iResult == 1)
  {
    Serial.println("Check wiring")
  }

  setupESC();
}

void setupESC(void)
{

  motA.attach(4, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
  motB.attach(5, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
  motC.attach(6, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
  motD.attach(7, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);

  displayInstructions();
}

/**
 * Main function
 */
void loop(void)
{
  if (Serial.available())
  {
    data = Serial.read();

    switch (data)
    {
    // 0
    case 48:
      Serial.println("Sending minimum throttle");
      motA.writeMicroseconds(MIN_PULSE_LENGTH);
      motB.writeMicroseconds(MIN_PULSE_LENGTH);
      motC.writeMicroseconds(MIN_PULSE_LENGTH);
      motD.writeMicroseconds(MIN_PULSE_LENGTH);
      break;

    // 1
    case 49:
      Serial.println("Sending maximum throttle");
      applyMaxThrottle();
      break;

    // 2
    case 50:
      Serial.print("Running test in 3");
      delay(1000);
      Serial.print(" 2");
      delay(1000);
      Serial.println(" 1...");
      delay(1000);
      test();
      break;
    }
  }
}

/**
 * Test function: send min throttle to max throttle to each ESC.
 */
void test(void)
{
  for (int i = MIN_PULSE_LENGTH; i <= MAX_PULSE_LENGTH; i += 5)
  {
    Serial.print("Pulse length Incrementing= ");
    Serial.println(i);

    motA.writeMicroseconds(i);
    motB.writeMicroseconds(i);
    motC.writeMicroseconds(i);
    motD.writeMicroseconds(i);

    delay(200);
  }

  Serial.println("STOPPING");
  motA.writeMicroseconds(MIN_PULSE_LENGTH);
  motB.writeMicroseconds(MIN_PULSE_LENGTH);
  motC.writeMicroseconds(MIN_PULSE_LENGTH);
  motD.writeMicroseconds(MIN_PULSE_LENGTH);
}

/**
 * Displays instructions to user
 */
void displayInstructions(void)
{
  Serial.println("READY - PLEASE SEND INSTRUCTIONS AS FOLLOWING :");
  Serial.println("\t0 : Send min throttle");
  Serial.println("\t1 : Send max throttle");
  Serial.println("\t2 : Run test function\n");
}

/**
 * Shit code but works and checks viring
 */
int checkWiring()
{
  if (motA.attached() == 4)
  {
    Serial.println("FL attached to D4");
    if (motB.attached() == 5)
    {
      Serial.println("FR attached to D5");
      if (motC.attached() == 6)
      {
        Serial.println("BL attached to D6");
        if (motD.attached() == 7)
        {
          Serial.println("BR attached to D7");
          return 0;
        }
        else
        {
          Serial.println("Check BR motor");
          return 1;
        }
      }
      else
      {
        Serial.println("Check BL motor");
        return 1;
      }
    }
    else
    {
      Serial.println("Check FR motor");
      return 1;
    }
  }
  else
  {
    Serial.println("Check FL motor");
    return 1;
  }
}

/**
 * To Automatically Stop the drone
 */

void autoStop()
{
  applyMaxThrottle();
  delay(500);
  for (int i = MAX_PULSE_LENGTH; i >= MIN_PULSE_LENGTH; i -= 5)
  {
    Serial.print("Pulse length Decrementing = ");
    Serial.println(i);

    motA.writeMicroseconds(i);
    motB.writeMicroseconds(i);
    motC.writeMicroseconds(i);
    motD.writeMicroseconds(i);

    delay(200);
  }
  Serial.println("STOPPED");
}

/**
 * To Go Front, Back, Left, Right respectivily
 */

void goFront()
{
  Serial.println("Going Front");
  delay(500);
  applyMaxThrottle();
  delay(3000);
  motA.writeMicroseconds(1700);
  motB.writeMicroseconds(1700);
  delay(3000);
  autoStop();
}

void goBack()
{
  Serial.println("Going Back");
  delay(500);
  applyMaxThrottle();
  delay(3000);
  motC.writeMicroseconds(1700);
  motD.writeMicroseconds(1700);
  delay(3000);
  autoStop();
}

void goLeft()
{
  Serial.println("Going Left");
  delay(500);
  applyMaxThrottle();
  delay(3000);
  motA.writeMicroseconds(1700);
  motC.writeMicroseconds(1700);
  delay(3000);
  autoStop();
}

void goRight()
{
  Serial.println("Going Right");
  delay(500);
  applyMaxThrottle();
  delay(2000);
  motB.writeMicroseconds(1700);
  motD.writeMicroseconds(1700);
  delay(3000);
  autoStop();
}

/**
 * Give max throttle
 */

void applyMaxThrottle()
{
  motA.writeMicroseconds(MAX_PULSE_LENGTH);
  motB.writeMicroseconds(MAX_PULSE_LENGTH);
  motC.writeMicroseconds(MAX_PULSE_LENGTH);
  motD.writeMicroseconds(MAX_PULSE_LENGTH);
}
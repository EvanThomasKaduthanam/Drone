#include <Servo.h>
#include <Wire.h>

#define MIN_PULSE_LENGTH 1000
#define MAX_PULSE_LENGTH 2000

char data;

struct Motors
{
  Servo motFL;
  Servo motFR;
  Servo motBL;
  Servo motBR;

} motors;

void setup()
{
  Serial.begin(0);
  int iResult = checkWiring();
  if (iResult == 1)
  {
    Serial.println("Check wiring");
  }
  else
  {
    setupESC();
    delay(3000);
    Serial.println("Done");
  }
}

void setupESC(void)
{
  motors.motFL.attach(4, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
  motors.motFR.attach(5, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
  motors.motBL.attach(6, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
  motors.motBR.attach(7, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
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
      motors.motFL.writeMicroseconds(MIN_PULSE_LENGTH);
      motors.motBR.writeMicroseconds(MIN_PULSE_LENGTH);
      motors.motFR.writeMicroseconds(MIN_PULSE_LENGTH);
      motors.motBL.writeMicroseconds(MIN_PULSE_LENGTH);
      break;

    // 1
    case 49:
      Serial.print("Running less throttle in 3");
      delay(1000);
      Serial.print(" 2");
      delay(1000);
      Serial.println(" 1...");
      delay(1000);
      Serial.println("Sending maximum throttle");
      sendMaxThrottle();
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

    // 3
    case 51:
      Serial.print("Running slow throttle in 3");
      delay(1000);
      Serial.print(" 2");
      delay(1000);
      Serial.println(" 1...");
      delay(1000);
      motors.motFL.writeMicroseconds(1325);
      motors.motBR.writeMicroseconds(1325);
      motors.motFR.writeMicroseconds(1325);
      motors.motBL.writeMicroseconds(1325);
      delay(3000);

      break;

    // 4
    case 52:
      Serial.print("going front in 3");
      delay(1000);
      Serial.print(" 2");
      delay(1000);
      Serial.println(" 1...");
      delay(1000);
      sendMaxThrottle();
      delay(3000);
      void goFront();
      delay(3000);
      break;
    }
  }
  else
  {
    Serial.println("Serial Not Available");
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

    motors.motFL.writeMicroseconds(i);
    motors.motBR.writeMicroseconds(i);
    motors.motFR.writeMicroseconds(i);
    motors.motBL.writeMicroseconds(i);

    delay(200);
  }

  Serial.println("STOPPING");
  autoStop();
}

/**
 * Displays instructions to user
 */
void displayInstructions(void)
{
  Serial.println("READY - PLEASE SEND INSTRUCTIONS AS FOLLOWING :");
  Serial.println("\t0 : Send Min Throttle");
  Serial.println("\t1 : Send Max Throttle");
  Serial.println("\t2 : Run Test Function");
  Serial.println("\t3 : Run Slow Throttle");
  Serial.println("\t4 : Run Test Function\n");
}

/**
 * Shit code but works and checks viring
 */
int checkWiring()
{
  if (motors.motFL.attached() == 4)
  {
    Serial.println("FL attached to D4");
    if (motors.motFR.attached() == 5)
    {
      Serial.println("FR attached to D5");
      if (motors.motBL.attached() == 6)
      {
        Serial.println("BL attached to D6");
        if (motors.motBR.attached() == 7)
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
  motors.motFL.writeMicroseconds(1600);
  motors.motFR.writeMicroseconds(1600);
  motors.motBL.writeMicroseconds(1600);
  motors.motBR.writeMicroseconds(1600);

  for (int i = 1600; i >= MIN_PULSE_LENGTH; i -= 5)
  {
    Serial.print("Pulse length Decrementing = ");
    Serial.println(i);

    motors.motFL.writeMicroseconds(i);
    motors.motFR.writeMicroseconds(i);
    motors.motBL.writeMicroseconds(i);
    motors.motBR.writeMicroseconds(i);

    delay(500);
  }
  Serial.println("STOPPED");
}

/**
 * To Go Front, Back, Left, Right respectivily
 */

/**
 * Go Front
 */

void goFront()
{
  Serial.println("Going Front");
  delay(500);
  sendMaxThrottle();
  delay(2000);
  motors.motFL.writeMicroseconds(1700);
  motors.motFR.writeMicroseconds(1700);
  delay(3000);
}
/**
 * Go Back
 */
void goBack()
{
  Serial.println("Going Back");
  delay(500);
  sendMaxThrottle();
  delay(2000);
  motors.motBL.writeMicroseconds(1700);
  motors.motBR.writeMicroseconds(1700);
  delay(3000);
}
/**
 * Go Left
 */
void goLeft()
{
  Serial.println("Going Left");
  delay(500);
  sendMaxThrottle();
  delay(2000);
  motors.motFL.writeMicroseconds(1700);
  motors.motBL.writeMicroseconds(1700);
  delay(3000);
}
/**
 * Go Right
 */
void goRight()
{
  Serial.println("Going Right");
  delay(1000);
  sendMaxThrottle();
  delay(2000);
  motors.motBR.writeMicroseconds(1700);
  motors.motFR.writeMicroseconds(1700);
  delay(3000);
}

/**
 * Give max throttle
 */

void sendMaxThrottle()
{
  motors.motFL.writeMicroseconds(MAX_PULSE_LENGTH);
  motors.motFR.writeMicroseconds(MAX_PULSE_LENGTH);
  motors.motBL.writeMicroseconds(MAX_PULSE_LENGTH);
  motors.motBR.writeMicroseconds(MAX_PULSE_LENGTH);
}
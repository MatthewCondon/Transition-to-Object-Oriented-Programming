/*
3/c Matthew Condon, Giselle Johnson
Group: 404_Brain_Not_Found
TOOP Final Robot Project
Instructor: LT Wiliams
*/

// Tools
#include <Pololu3piPlus32U4.h>
#include <Arduino.h>
#include <Pololu3piPlus32U4IMU.h>

using namespace Pololu3piPlus32U4;

// global vars
OLED disp;
ButtonA ba;
ButtonB bb;
ButtonC bc;
Motors motor;
IMU imu;
Buzzer buzzer;
BumpSensors bumpers;
LineSensors lineSensors;

// .h files
#include <TurnSensor.h>
#include <CRobot.h> // Contains CRobot class

// Music Function
void playMusic()
{
  // Music Notes Source: https://musescore.com/user/498481/scores/8302178
  buzzer.play("l8 f f f f c f a L2 >C L8 >C >D >C B- >D L1 >C L8 A B- A G >C A G F A G >C B >D L2 >C l8 F F F F C F A >C >C >D >C B- >D L2 >C L8 A B- A G >C A G F >G >A >>C >F >G L1 >F");
  while (buzzer.isPlaying())
    ;
}

// class instances / objects
CRobot juicebox("3/c Matthew Condon", "3/c Giselle Johnson", 30, 30);

// Setup and Loop functions
void setup()
{
  // initialize display
  disp.init();
  disp.setLayout21x8();

  // names must show at all times
  disp.gotoXY(0, 0);
  disp.print(juicebox.getName1());
  disp.gotoXY(0, 1);
  disp.print(juicebox.getName2());
}

// Calibration function for blackline sensing
void calibrateSensors()
{
  // Wait 1 second and then begin automatic sensor calibration
  // by rotating in place to sweep the sensors over the line
  delay(1000);
  for (uint16_t i = 0; i < 80; i++)
  {
    if (i > 20 && i <= 60)
    {
      motor.setSpeeds(-60, 60);
    }
    else
    {
      motor.setSpeeds(60, -60);
    }
    lineSensors.calibrate();
  }
  motor.setSpeeds(0, 0);
}

// Main loop function
void loop()
{
  /*
  Button Logic

  While waiting for user input:
    A: calibrate turn sensor
    B: pre-sumo ritual
    C: fight mode
  */

  // Displaying
  disp.gotoXY(0, 3);
  disp.print("Waiting for input");

  disp.gotoXY(0, 5);
  disp.print("A: Calibrate Tools");

  disp.gotoXY(0, 6);
  disp.print("B: Pre-Match Ritual");

  disp.gotoXY(0, 7);
  disp.print("C: Competition Mode");

  // Bool variables to test buttons
  bool baPressed;
  bool bbPressed;
  bool bcPressed;

  // configurations
  if (ba.isPressed())
  {
    baPressed = true;

    // display settings
    disp.clear();
    disp.gotoXY(0, 0);
    disp.print(juicebox.getName1());
    disp.gotoXY(0, 1);
    disp.print(juicebox.getName2());
    disp.gotoXY(0, 3);
    disp.print("Calibrating...");

    // tools to calibrate
    turnSensorSetup();
    lineSensors.calibrate();
    bumpers.calibrate();
    calibrateSensors();

    baPressed = false;
  }

  // pre-match rituals
  if (bb.isPressed())
  {
    bbPressed = true;

    /*
    Each function is called by the prior function of the ceremony. As such, the program only needs to call the first function.
    fwdUntil() -> turnRight();
    turnRight() -> tunLeft();
    turnLeft() -> aboutFace();
    aboutFace() -> end of pre-ceremony

    playMusic() -> final part
    */
    juicebox.fwdUntil();

    // // Call aboutFace() to face center of arena
    // juicebox.aboutFace();

    // Call the music
    playMusic();

    bbPressed = false;
  }

  // competing
  if (bc.isPressed())
  {
    bcPressed = true;

    // display settings
    disp.clear();
    disp.gotoXY(0, 0);
    disp.print(juicebox.getName1());
    disp.gotoXY(0, 1);
    disp.print(juicebox.getName2());
    disp.gotoXY(0, 3);

    // Competition
    juicebox.competitionMode();

    bcPressed = false;
  }
}

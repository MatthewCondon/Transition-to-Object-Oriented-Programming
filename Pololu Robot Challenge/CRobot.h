// CRobot Class
class CRobot
{
  // private vars
private:
  String name1; // team member name
  String name2; // team member name
  int fwd0;     // value used by right motor to move forward
  int fwd1;     // value used by left motor to move forward

  // public constructors
public:
  // default constructor
  CRobot()
  { 
    name1 = "null";
    name2 = "null";
    fwd0 = 0;
    fwd1 = 0;
  }

  // overloaded constructor
  CRobot(String str1, String str2, int rm, int lm)
  {
    name1 = str1;
    name2 = str2;
    fwd0 = rm;
    fwd1 = lm;
  }

  // public methods
public:
  // primary function: move in a straight path until robot reaches outline ring line
  void fwdUntil()
  {

    // display settings
    disp.clear();
    disp.gotoXY(0, 0);
    disp.print(name1);
    disp.gotoXY(0, 1);
    disp.print(name2);
    disp.gotoXY(0, 3);
    disp.print("Pre-Rituals");
    disp.gotoXY(0, 4);
    disp.print("Moving Forward");

    // used for determining how close to the line the robot is
    uint16_t values[5];
    bool runner = true;
    while (runner)
    {
      // get sensor values
      uint16_t test = lineSensors.readLineBlack(values);
      // if sense any black line stop
      if (test > 1000)
      {
        motor.setSpeeds(0, 0);
        delay(2000);                       // proves robot stops
        motor.setSpeeds(-(fwd0), -(fwd1)); // back up from the edge
        delay(2000);                       // wait two seconds before continuing
        turnRight();                       // call next function of ceremony
        runner = false;                    // end loop
      }
      else
      {
        // move forward until hit black line
        motor.setSpeeds(fwd0, fwd1);
      }
    }
  }

  // primary function: turn robot counter-clockwise predefined amount
  void turnRight()
  {

    delay(1000);
    // display settings
    disp.clear();
    disp.gotoXY(0, 0);
    disp.print(name1);
    disp.gotoXY(0, 1);
    disp.print(name2);
    disp.gotoXY(0, 3);
    disp.print("Pre-Rituals");
    disp.gotoXY(0, 4);
    disp.print("Turning Right");

    // move forward first
    motor.setSpeeds(fwd0, fwd1);
    delay(1000);

    turnSensorReset();

    // Update sensor
    while (heading > -90)
    {
      turnSensorUpdate();
      motor.setSpeeds(fwd0, -fwd1);
    }

    motor.setSpeeds(fwd0, fwd1);
    delay(1000);
    turnLeft(); // call next function of ceremony
  }

  // primary function: turn robot clockwise predefined amount
  void turnLeft()
  {

    // display settings
    disp.clear();
    disp.gotoXY(0, 0);
    disp.print(name1);
    disp.gotoXY(0, 1);
    disp.print(name2);
    disp.gotoXY(0, 3);
    disp.print("Pre-Rituals");

    disp.gotoXY(0, 4);
    disp.print("Turning Left");

    // move forward first
    motor.setSpeeds(fwd0, fwd1);
    delay(1000);

    turnSensorReset();

    // Update sensor
    while (heading < 90)
    {
      turnSensorUpdate();
      motor.setSpeeds(-fwd0, fwd1);
    }

    motor.setSpeeds(fwd0, fwd1);
    delay(1000);
    aboutFace(); // call next function of ceremony
  }

  // primary function: turns 180 degrees either direction
  void aboutFace()
  {

    disp.clear();
    disp.gotoXY(0, 0);
    disp.print(name1);
    disp.gotoXY(0, 1);
    disp.print(name2);
    disp.gotoXY(0, 3);
    disp.print("Pre-Rituals");
    disp.gotoXY(0, 4);
    disp.print("About Face");

    turnSensorReset();

    while (heading > -90)
    {
      turnSensorUpdate();
      motor.setSpeeds(-fwd0, fwd1);
    }

    motor.setSpeeds(fwd0, fwd1);
    delay(1000);
    motor.setSpeeds(0, 0);
  }

  void competitionMode()
  {
    /*
    Code Objectives:
    If hit line, turn around
    Strategy:
        If left sensor hit, turn left and push harder, back up
        Same if right sensor is hit
    Refer to the Code Notes.txt for the Pseudocode
    */

    // display settings
    disp.clear();
    disp.gotoXY(0, 0);
    disp.print(name1);
    disp.gotoXY(0, 1);
    disp.print(name2);
    disp.gotoXY(0, 3);
    disp.print("Competition Mode");

    // used for determining how close to the line the robot is
    uint16_t values[5];
    while (true)
    {
      // get sensor values
      bumpers.read();
      uint16_t test = lineSensors.readLineBlack(values);

      // if sense any black line stop
      if (test > 1000)
      {
        motor.setSpeeds(300, -300); // Adjust the speeds for turning
        delay(100);                 // Adjust the turn duration as needed
        motor.setSpeeds(0, 0);      // Stop the motors after turning
      }

      // if right bumper is pressed
      if (bumpers.rightIsPressed())
      {
        // turn slightly righ0t
        motor.setSpeeds(150, 100);
        delay(100);

        // push forward
        motor.setSpeeds(200, 200);
        delay(200);

        // Stop motors
        motor.setSpeeds(0, 0);
      }

      // if left bumper is pressed
      if (bumpers.leftIsPressed())
      {
        // turn slightly righ0t
        motor.setSpeeds(100, 150);
        delay(100);

        // push forward
        motor.setSpeeds(200, 200);
        delay(200);

        // Stop motors
        motor.setSpeeds(0, 0);
      }

      else
      {
        motor.setSpeeds(100, 100); // move forward
      }
    }
  }

  // extra functions for program
  // Get name functions
  String getName1()
  {
    return name1;
  }
  String getName2()
  {
    return name2;
  }
};

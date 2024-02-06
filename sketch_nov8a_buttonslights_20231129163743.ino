#include <Adafruit_MCP23X17.h> //Using Adafruit library for MCP23017

Adafruit_MCP23X17 mcp0, mcp1; //Instantiate mcp object
const static int buttons[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; // Pins on MCP
const static int lights[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};//Pins on MCP

void setup() {
  mcp0.begin_I2C(0x20);// 000-Gnd,Gnd,Gnd-using chip Address along with hardwiring to declare these seperately.
  mcp0.setupInterrupts(true, true, LOW);
  mcp1.begin_I2C(0x21);// 001-Gnd,Gnd,5v.
 
  for(int x = 0;x < sizeof(buttons)/sizeof(int); x++) // Iterates through all buttons
  {
    mcp0.pinMode(buttons[x], INPUT_PULLUP); // Places Pin "x" into a natural HIGH state
  } 
  for(int x = 0; x < sizeof(lights)/sizeof(int); x++) // Iterates through all LEDs
  {
    mcp1.pinMode(lights[x], OUTPUT); // Set LEDs to output
  } 
}

void loop() {
  for(int x = 0; x < sizeof(buttons)/sizeof(int); x++) // Iterate through all buttons
  {
    if (mcp0.digitalRead(buttons[x]) == LOW) // Check state of buttons
    {
        Serial.write(mcp0.getLastInterruptPin());
        mcp1.digitalWrite(lights[x], HIGH); // Turn on LED
        delay(1000); // Wait
        mcp1.digitalWrite(lights[x], LOW); // Turn off LED
    }
  }
}
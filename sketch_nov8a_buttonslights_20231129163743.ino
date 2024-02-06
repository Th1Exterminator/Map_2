#include <Adafruit_MCP23X17.h> //Using Adafruit library for MCP23017

Adafruit_MCP23X17 mcp0, mcp1; //Instantiate mcp object
const static int pins[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15}; // Pins on MCP

void setup() {
  Serial.begin(9600);
  mcp0.begin_I2C(0x20);// 000-Gnd,Gnd,Gnd-using chip Address along with hardwiring to declare these seperately.
  mcp0.setupInterrupts(true, true, LOW);
  mcp1.begin_I2C(0x21);// 001-Gnd,Gnd,5v.
 
  for(int x = 0;x < sizeof(pins)/sizeof(int); x++) // Iterates through all buttons
  {
    mcp0.pinMode(pins[x], INPUT_PULLUP); // Places Pin "x" into a natural HIGH state
  } 
  for(int x = 0; x < sizeof(pins)/sizeof(int); x++) // Iterates through all LEDs
  {
    mcp1.pinMode(pins[x], OUTPUT); // Set LEDs to output
  } 
}

void loop() {
  uint8_t interPin = mcp0.getLastInterruptPin(); 
  Serial.write(interPin);
  mcp1.digitalWrite(interPin, HIGH);
}
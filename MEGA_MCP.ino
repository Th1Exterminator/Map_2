#include <Adafruit_MCP23X17.h>

Adafruit_MCP23X17 mcp0;
static const unsigned short pinsA[] = {0,1,2,3,4,5,6,7};
static const unsigned short pinsB[] = {8,9,10,11,12,13,14,15};
static const unsigned short pinsMega[] = {30,31,32,33,34,35,36,37};

static unsigned int buff_c = 0;

void setup() {
  // Initalization
  Serial.begin(9600);
  mcp0.begin_I2C(0x20);

  // Setup - MCP
  for (unsigned short x = 0; x < sizeof(pinsB)/sizeof(unsigned short); x++)
    mcp0.pinMode(pinsB[x], OUTPUT);

  // Setup - MEGA
  for (unsigned short x = 0; x < sizeof(pinsMega)/sizeof(unsigned short); x++)
    pinMode(pinsMega[x], INPUT);
}

void loop() {
  unsigned int buff_b = 0;
  
  for (unsigned short x = 0; x < sizeof(pinsB)/sizeof(unsigned short); x++)
  {
    // Header
    unsigned int buff_a = 0;
    mcp0.digitalWrite(pinsB[x], HIGH);
    delay(100);

    // Serial communication
    buff_a = digitalRead(pinsMega[x]);
    Serial.print("pin (");
    Serial.print(x);
    Serial.print(" Reg B) :: VAL Rx: ");
    Serial.print(buff_a);
    Serial.print("\n");

    // Footer
    mcp0.digitalWrite(pinsB[x], LOW);
    delay(100);

    buff_b += buff_a;
  }
  buff_c += buff_b;
  Serial.print("Packet loss: ");
  Serial.print(8-buff_b);
  Serial.print("\n");
/*
  const char* instruct = Serial.read();
  if (instruct == "report")
  {
    Serial.print("Total packet loss: ");
    Serial.print(buff_c);
    Serial.print(" / ");
    Serial.print(sizeof(pinsB)/sizeof(unsigned short));
    Serial.print("\n");
    delay(1000);
  }
 */
}

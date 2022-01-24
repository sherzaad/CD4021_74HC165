//controlling 74HC165/CD4021

#define SELECTED_CHIP 0 //0 = 74HC165, 1 = CD4021

#ifdef SELECTED_CHIP
#if SELECTED_CHIP != 0 && SELECTED_CHIP != 1
#error "Invalid Value Entered For SELECTED_CHIP"
#elif SELECTED_CHIP == 0
// ONLY for 74HC165
// const uint8_t ClkInkPin = 9; CLK_INH(pin 15) Connect to GND if unused
#endif
// Define Connections to   74HC165  |   CD4021
const int SH_LDPin = 4; //  SH_LD(pin 1)| SH_LD(pin 9)
const int clockPin = 3; //  CLK(pin 2)  | CLK(pin 10)
const int dataPin = 2;  //  QH(pin 9) | QH(pin 12)
//74HC165: SH_LD LOW -> load, HIGH-> shift
//CD4021: SH_LD LOW -> shift, HIGH-> load
#else
#error "SELECTED_CHIP Not Defined!"
#endif

const int numBits = 8;   /* Set to 8  -  8*(number of shift registers) */

void setup() {
  Serial.begin(115200);
  pinMode(dataPin, INPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(SH_LDPin, OUTPUT);

  //Load parallel input into register
#if SELECTED_CHIP == 0
  digitalWrite(SH_LDPin, LOW);
#else
  digitalWrite(SH_LDPin, HIGH);
#endif

  Serial.println("PISO example.");
}

void loop() {
  int bytes = 0;
  // Step 1: Sample
  //Set chip for Serial Out read
#if SELECTED_CHIP == 0
  digitalWrite(SH_LDPin, HIGH);
#else
  digitalWrite(SH_LDPin, LOW);
#endif

  // Step 2: Shift
  Serial.print("Bit: ");
  for (int i = 0; i < numBits; i++) {
    bytes <<= 1;
    bytes |= digitalRead(dataPin);
    digitalWrite(clockPin, HIGH); // Shift out the next bit
    digitalWrite(clockPin, LOW);
  }

  //Load parallel input into register
#if SELECTED_CHIP == 0
  digitalWrite(SH_LDPin, LOW);
#else
  digitalWrite(SH_LDPin, HIGH);
#endif

  Serial.println(bytes, BIN);
  delay(500);
}

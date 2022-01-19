//controlling 74HC165/CD4021

#define SELECTED_CHIP 0 //0 = 74HC165, 1 = CD4021

#ifdef SELECTED_CHIP
	#if SELECTED_CHIP != 0 && SELECTED_CHIP != 1
	#error "Invalid Value Entered For SELECTED_CHIP"
	#elif SELECTED_CHIP == 0
	// ONLY for 74HC165
	// const uint8_t ClkInkPin = 9; CLK_INH(pin 15) Connect to GND if unused
	#error "Invalid Value Entered For SELECTED_CHIP"
	#endif
	// Define Connections to 	 74HC165	|	  CD4021
	const int SH_LDPin = 10; //	SH_LD(pin 1)|	SH_LD(pin 9)
	const int clockPin = 11; //	CLK(pin 2)	|	CLK(pin 10)
	const int dataPin = 12;  //	QH(pin 9)	|	QH(pin 12)
	//74HC165: SH_LD LOW -> load, HIGH-> shift
	//CD4021: SH_LD LOW -> shift, HIGH-> load
#else
#error "SELECTED_CHIP Not Defined!"
#endif

void setup() {
  Serial.begin(115200);

  // Setup pins as Outputs
  pinMode(SH_LDPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  //Load parallel input into register
  #if SELECTED_CHIP == 0
  digitalWrite(SH_LDPin, LOW);
  #else
  digitalWrite(SH_LDPin, HIGH);
  #endif

  Serial.println("PISO example.");
}

void loop() {
  uint8_t port_val = 0;

  //Set chip for Serial Out read
  #if SELECTED_CHIP == 0
  digitalWrite(SH_LDPin, HIGH);
  #else
  digitalWrite(SH_LDPin, LOW);
  #endif
  
  //set clock pin is LOW before the first call to shiftIn()
  digitalWrite(clockPin, LOW);
  
  //Shift in the bits
  port_val = shiftIn(dataPin, clockPin, MSBFIRST);

  Serial.println(port_val, BIN);

  //Load parallel input into register
  #if SELECTED_CHIP == 0
  digitalWrite(SH_LDPin, LOW);
  #else
  digitalWrite(SH_LDPin, HIGH);
  #endif

  delay(500);
}


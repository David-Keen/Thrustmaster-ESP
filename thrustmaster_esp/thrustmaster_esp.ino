#define SS 34
#define CLK 35
#define MISO 32

#define BUTTON 21
byte wheelState[64] = {
  1, 1, 0, 1, 0, 0, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1
};

byte defaultState[64] = {
  1, 1, 0, 1, 0, 0, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1
};

boolean isChipSelected = 0;
uint8_t misoFlag;
boolean chipSelected;

uint8_t bitIndex = 0;

const uint8_t PS_BTN = 17;
const uint8_t X_BTN = 9;

int sequence = 0;

void IRAM_ATTR onChipSelectChange() {
  //Set status of slave select
  isChipSelected = digitalRead(SS) == 0;
  //If chip is deselected, reset the miso data
  if(!isChipSelected) {
    bitIndex = 0;
    memcpy(wheelState, defaultState, sizeof(defaultState[0])*64);
    misoFlag = wheelState[0];
  }
}

void IRAM_ATTR onButtonHigh() {
  wheelState[PS_BTN] = 0;
  Serial.println("PS Button Pressed");
}

void IRAM_ATTR onClockLow() {
  //Do nothing if device is not selected
  if(!isChipSelected) return;
  
  //Load the next bit
  bitIndex++;

  if(bitIndex > 63) {
    bitIndex = 0;
  }
  // Set miso data to loaded bit
  misoFlag = wheelState[bitIndex];
}

void setup() {
  //Set miso to first bit
  misoFlag = wheelState[bitIndex];
  
  Serial.begin(115200);
  pinMode(SS, INPUT);
  pinMode(CLK, INPUT);
  pinMode(MISO, OUTPUT);
  pinMode(BUTTON, INPUT);
  digitalWrite(MISO, LOW);

  attachInterrupt(SS, onChipSelectChange, CHANGE);
  attachInterrupt(CLK, onClockLow, FALLING);
}

void loop() {
  if(digitalRead(BUTTON) == 1) {
      wheelState[PS_BTN] = 0;
  }
  digitalWrite(MISO, misoFlag);
}

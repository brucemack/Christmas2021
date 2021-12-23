// Christmas Light Controller
// 2021 Display
//
// Hardware is an Arduio Pro Mini, two 74HCT595 shift registers,
// and 16 solid-state relays. 
//
// GPIO pins for shift register.
// CHANGE THESE ACCORDING TO YOUR HARDWARE SETUP!
#define SRCLK 8
#define RCLK  7
#define SER   9

// String addresses
#define STAR_W1    0x0001
#define STAR_W2    0x0002
#define STAR_W3    0x0004
#define STAR_W4    0x0008
#define STAR_W5    0x0010
#define STAR_R1    0x0020
#define STAR_R2    0x0040
#define STAR_R3    0x0080
#define STAR_R4    0x0100
#define STAR_R5    0x0200
#define STAR_WC    0x0400
#define LEFT_BUSH  0x0800
#define RIGHT_BUSH 0x1000
#define WREATH     0x2000
#define RIGHT_MC   0x4000
#define LEFT_MC    0x8000

void setup() {
  
  pinMode(13,OUTPUT);
  pinMode(SRCLK,OUTPUT);
  pinMode(RCLK,OUTPUT);
  pinMode(SER,OUTPUT);
  digitalWrite(SRCLK,0);
  digitalWrite(RCLK,0);

  int d0 = 1000;

  // Diagnostics on startup
  write(0);
  // Flash on-board LED
  digitalWrite(13,1);
  delay(d0);
  digitalWrite(13,0);
  delay(d0);
  digitalWrite(13,1);
  delay(d0);
  digitalWrite(13,0);
  delay(d0);
  delay(d0);
  // Turn on every string
  write(0xffff);
  delay(d0);
  delay(d0);
  delay(d0);
  // Turn off every string
  write(0);
}

// Single right-shift on shift register
void shift() {
  digitalWrite(SRCLK,1);
  delay(10);
  digitalWrite(SRCLK,0);
}

// Latch output for display
void latch() {
  digitalWrite(RCLK,1);
  digitalWrite(RCLK,0);
}

// Writes a 16-bit value into the register and latches
void write(unsigned int data) {
  for (int i = 0; i < 16; i++) {
    if (data & 1) {
      digitalWrite(SER,1);
    } else {
      digitalWrite(SER,0);
    }
    shift();
    data = data >> 1;
  }
  latch();
}

void showCycle() {

  int df = 75;
  int d0 = 125;
  int d1 = 250;
  int d2 = 500;
  
  write(0);
  delay(d1);

  // Long white
  write(STAR_W1 | STAR_W2 | STAR_W3 | STAR_W4 | STAR_W5 | STAR_WC | WREATH);
  delay(d2);
  // Long red
  write(STAR_R1 | STAR_R2 | STAR_R3 | STAR_R4 | STAR_R5);
  delay(d2);

  // Sweep bush/wreath
  for (int i = 0; i < 2; i++) {
    write(LEFT_MC);
    delay(df);
    write(LEFT_BUSH);
    delay(df);
    write(RIGHT_BUSH);
    delay(df);
    write(WREATH);
    delay(df);
    write(RIGHT_MC);
    delay(df);
    write(WREATH);
    delay(df);
    write(RIGHT_BUSH);
    delay(df);
    write(LEFT_BUSH);
    delay(df);
  }
    
  // Star rotation
  for (int i = 0; i < 2; i++) {
    
    int wc = 0;
    wc = STAR_WC | LEFT_BUSH | RIGHT_BUSH | WREATH;

    // Red background
    wc = STAR_WC | LEFT_BUSH | RIGHT_BUSH | WREATH;
    wc |= (STAR_R1 | STAR_R2 | STAR_R3 | STAR_R4 | STAR_R5);
  
    write(STAR_W1 | wc);
    delay(df);
    write(STAR_W2 | wc);
    delay(df);
    write(STAR_W3 | wc);
    delay(df);
    write(STAR_W4 | wc);
    delay(df);
    write(STAR_W5 | wc);
    delay(df);

    // White background
    wc = STAR_WC | LEFT_BUSH | RIGHT_BUSH | WREATH;
    wc |= (STAR_W1 | STAR_W2 | STAR_W3 | STAR_W4 | STAR_W5);

    write(STAR_R1 | wc);
    delay(df);
    write(STAR_R2 | wc);
    delay(df);
    write(STAR_R3 | wc);
    delay(df);
    write(STAR_R4 | wc);
    delay(df);
    write(STAR_R5 | wc);
    delay(df);
  }

  // Star build
  for (int i = 0; i < 2; i++) {
    
    int wc = 0;
    wc = STAR_WC | LEFT_BUSH | RIGHT_BUSH | WREATH;

    // White
    write(STAR_W1 | wc);
    delay(df);
    write(STAR_W1 | STAR_W2 | wc);
    delay(df);
    write(STAR_W1 | STAR_W2 | STAR_W3 | wc);
    delay(df);
    write(STAR_W1 | STAR_W2 | STAR_W3 | STAR_W4 | wc);
    delay(df);
    write(STAR_W1 | STAR_W2 | STAR_W3 | STAR_W4 | STAR_W5 | wc);
    delay(df);
    
    // Red
    wc = LEFT_MC | RIGHT_MC;
    write(STAR_R1 | wc);
    delay(df);
    write(STAR_R1 | STAR_R2 | wc);
    delay(df);
    write(STAR_R1 | STAR_R2 | STAR_R3 | wc);
    delay(df);
    write(STAR_R1 | STAR_R2 | STAR_R3 | STAR_R4 | wc);
    delay(df);
    write(STAR_R1 | STAR_R2 | STAR_R3 | STAR_R4 | STAR_R5 | wc);
    delay(df);
  }

  // Red/white alt
  for (int i = 0; i < 2; i++) {
    write(STAR_W1 | STAR_W2 | STAR_W3 | STAR_W4 | STAR_W5 | STAR_WC | WREATH);
    delay(d0);
    write(STAR_R1 | STAR_R2 | STAR_R3 | STAR_R4 | STAR_R5);
    delay(d0);  
    write(LEFT_BUSH | RIGHT_BUSH | LEFT_MC | RIGHT_MC);
    delay(d0);  
  }

  // All white
  write(STAR_W1 | STAR_W2 | STAR_W3 | STAR_W4 | STAR_W5 | STAR_WC |
      WREATH);
  delay(d2);
  delay(d2);
  
  // All 
  write(STAR_W1 | STAR_W2 | STAR_W3 | STAR_W4 | STAR_W5 | STAR_WC |
      STAR_R1 | STAR_R2 | STAR_R3 | STAR_R4 | STAR_R5 |
      LEFT_BUSH | RIGHT_BUSH | WREATH |
      LEFT_MC | RIGHT_MC);
  delay(d2);
  delay(d2);
  delay(d2);
}

void loop() {
  showCycle();
}


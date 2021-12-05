#define SRCLK 8
#define RCLK 7
#define SER 9

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

void setup() {
  
  pinMode(13,OUTPUT);
  pinMode(SRCLK,OUTPUT);
  pinMode(RCLK,OUTPUT);
  pinMode(SER,OUTPUT);
  digitalWrite(SRCLK,0);
  digitalWrite(RCLK,0);

  int d0 = 1000;

  // Diagnostics
  write(0);
  digitalWrite(13,1);
  delay(d0);
  digitalWrite(13,0);
  delay(d0);
  digitalWrite(13,1);
  delay(d0);
  digitalWrite(13,0);
  delay(d0);
  delay(d0);
  write(0xffff);
  delay(d0);
  delay(d0);
  delay(d0);
  write(0);
}

void shift() {
  digitalWrite(SRCLK,1);
  delay(10);
  digitalWrite(SRCLK,0);
}

void latch() {
  digitalWrite(RCLK,1);
  digitalWrite(RCLK,0);
}

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

  int d0 = 125;
  int d1 = 250;
  int d2 = 500;
  
  write(0);
  delay(d1);

  // Long white
  write(STAR_W1 | STAR_W2 | STAR_W3 | STAR_W4 | STAR_W5 | STAR_WC);
  delay(d2);
  // Long red
  write(STAR_R1 | STAR_R2 | STAR_R3 | STAR_R4 | STAR_R5);
  delay(d2);

  // Sweep bush/wreath
  for (int i = 0; i < 4; i++) {
    write(LEFT_BUSH);
    delay(d0);
    write(RIGHT_BUSH);
    delay(d0);
    write(WREATH);
    delay(d0);
  }
    
  // Star rotation
  for (int i = 0; i < 4; i++) {
    int wc = 0;
    if (i % 2 == 0) {
      wc = STAR_WC;
    } else {
      wc = LEFT_BUSH | RIGHT_BUSH | WREATH;
    }
    write(STAR_W1 | STAR_R1 | wc);
    delay(d0);
    write(STAR_W2 | STAR_R5 | wc);
    delay(d0);
    write(STAR_W3 | STAR_R4 | wc);
    delay(d0);
    write(STAR_W4 | STAR_R3 | wc);
    delay(d0);
    write(STAR_W5 | STAR_R2 | wc);
    delay(d0);
  }

  for (int i = 0; i < 2; i++) {
    write(STAR_W1 | STAR_W2 | STAR_W3 | STAR_W4 | STAR_W5 | STAR_WC);
    delay(d0);
    write(STAR_R1 | STAR_R2 | STAR_R3 | STAR_R4 | STAR_R5);
    delay(d0);  
    write(LEFT_BUSH | RIGHT_BUSH);
    delay(d0);  
  }

  // All
  write(STAR_W1 | STAR_W2 | STAR_W3 | STAR_W4 | STAR_W5 | STAR_WC |
      STAR_R1 | STAR_R2 | STAR_R3 | STAR_R4 | STAR_R5 |
      LEFT_BUSH | RIGHT_BUSH | WREATH);
  delay(d2);
  delay(d2);
}

void loop() {
  showCycle();
}





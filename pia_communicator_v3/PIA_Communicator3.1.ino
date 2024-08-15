
#include <Arduino.h>
#include <MCP23S17.h>
#include <SPI.h>

#define KBD_SEND_TIMEOUT 250

#define IO_SS 10

#define IO_VIDEO 0
#define IO_VIDEO_D0 0
#define IO_VIDEO_D6 6
#define VIDEO_RDA 5
#define VIDEO_DA 3

#define IO_KBD 1
#define IO_KBD_D0 8
#define IO_KBD_D6 14
#define IO_KBD_DA 15
#define KBD_READY 2
#define KBD_STROBE 4

#define DELAY_VIDEO 10

MCP23S17 bridge(&SPI, IO_SS, 0);

void setup() {
  Serial.begin(115200);
  configure_pins();
  configure_bridge();

  attachInterrupt(digitalPinToInterrupt(VIDEO_DA),video_in, RISING);

  output_status();
  digitalWrite(VIDEO_RDA, HIGH);
}

void video_in()
{
 register uint8_t c;   
   digitalWrite(VIDEO_RDA, LOW);
     c = bridge.readPort(IO_VIDEO) & 127;
     switch(c) {
      case 13:
        Serial.print((char)10); //send linefeed and carrage return
        Serial.print((char)13);
        break;
      case 32 ... 127:
        Serial.print((char)c);
        break;
     }
   delayMicroseconds(DELAY_VIDEO);
   digitalWrite(VIDEO_RDA, LOW); //ok send 10usec pulse to clear video busy D7 on 6821
   delayMicroseconds(10);
   digitalWrite(VIDEO_RDA, HIGH);}

void configure_pins() {
  pinMode(KBD_READY, INPUT);
  pinMode(VIDEO_DA, INPUT);
  pinMode(KBD_STROBE, OUTPUT);
  pinMode(VIDEO_RDA, OUTPUT);
}

void configure_bridge() {
  bridge.begin();

  /* Configure video section */
  for (int i = IO_VIDEO_D0; i <= IO_VIDEO_D6; i++) {
    bridge.pinMode(i, INPUT);
  }
  bridge.pinMode(7, INPUT_PULLUP);

  /* Configure keyboard section */
  for (uint8_t i = 8; i <= 15; i++) {
    bridge.pinMode(i, OUTPUT);
  }
}

void output_status() {
  Serial.println("RC6502 Apple 1 Replica (using interrupts)");
}

void serial_receive() {
  uint8_t c;

  if (Serial.available() > 0) {
    c = Serial.read();
    pia_send(c);
  }
}

void pia_send(uint8_t c) {
  /* Make sure STROBE signal is off */
  digitalWrite(KBD_STROBE, LOW);
  c = map_to_ascii(c);

  /* Output the actual keys as long as it's supported */
  if (c < 96) {
    bridge.writePort(IO_KBD, c | 128);

    digitalWrite(KBD_STROBE, HIGH);
    delayMicroseconds(KBD_SEND_TIMEOUT);
    digitalWrite(KBD_STROBE, LOW);
  }
}

uint8_t map_to_ascii(uint8_t c) {
  /* Convert ESC key */
  if (c == 203) {
    c = 27;
  }

  /* Ctrl A-Z */
  if (c > 576 && c < 603) {
    c -= 576;
  }

  /* Convert lowercase keys to UPPERCASE */
  if (c > 96 && c < 123) {
    c -= 32;
  }

  return c;
}

void loop() {
  serial_receive();
}

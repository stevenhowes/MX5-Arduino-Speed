
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include <math.h>

//Define SPI Connections:
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13

#define LOGO_HEIGHT   64
#define LOGO_WIDTH    64
const unsigned char PROGMEM logo_bmp [] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF0, 0x0F, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x03, 0xF0, 0x0F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x37, 0xE0, 0x07, 0xE8, 0x00, 0x00,
  0x00, 0x00, 0xF7, 0xC0, 0x07, 0xEE, 0x00, 0x00, 0x00, 0x01, 0xEF, 0x80, 0x03, 0xEF, 0x80, 0x00,
  0x00, 0x03, 0xEF, 0x00, 0x01, 0xF7, 0xC0, 0x00, 0x00, 0x07, 0xCF, 0xC0, 0x03, 0xF7, 0xC0, 0x00,
  0x00, 0x07, 0xC7, 0xF8, 0x1F, 0xE3, 0xE0, 0x00, 0x00, 0x17, 0x87, 0xFE, 0x7F, 0xE3, 0xEC, 0x00,
  0x00, 0x37, 0x83, 0xFE, 0x7F, 0xC1, 0xEC, 0x00, 0x00, 0x77, 0xF9, 0xF0, 0x1F, 0xBF, 0xEC, 0x00,
  0x00, 0xF7, 0xFE, 0x00, 0x00, 0xFF, 0xCE, 0x00, 0x00, 0xF3, 0xFE, 0x00, 0x00, 0x7F, 0xCF, 0x00,
  0x00, 0xF1, 0xF8, 0x00, 0x00, 0x3F, 0x0F, 0x00, 0x00, 0xF0, 0xC0, 0x00, 0x00, 0x02, 0x07, 0x00,
  0x03, 0xFF, 0xC0, 0x00, 0x00, 0x03, 0xFF, 0xC0, 0x07, 0xFF, 0xC0, 0x00, 0x00, 0x03, 0xFE, 0xC0,
  0x07, 0xFF, 0x80, 0x00, 0x00, 0x01, 0xFE, 0xE0, 0x0F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xE0,
  0x0F, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x39, 0xF0, 0x0F, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x39, 0xF0,
  0x0F, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x3D, 0xF0, 0x0F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xF0,
  0x0F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xE0, 0x07, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xE0,
  0x03, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x7F, 0xFF, 0xCE, 0xF3, 0xBC, 0x7D, 0xFD, 0xC7, 0x7F, 0xDF, 0xDE, 0xE3, 0xBE, 0xFB, 0xFF, 0xC7,
  0x7F, 0xFB, 0xDE, 0xE3, 0xFF, 0xFB, 0xFF, 0xCF, 0x1E, 0x3B, 0xDD, 0xE7, 0xFF, 0xFB, 0x9F, 0xFF,
  0x1E, 0x3F, 0xDD, 0xE7, 0xFF, 0xFB, 0xFF, 0xFE, 0x1C, 0x3F, 0xBD, 0xC7, 0xFF, 0xF7, 0xFF, 0xFE,
  0x1C, 0x7F, 0x3D, 0xC7, 0xFF, 0xF7, 0xF7, 0x9E, 0x3C, 0x77, 0x39, 0xCF, 0xEF, 0xF7, 0x07, 0x1E,
  0x3C, 0x77, 0xB9, 0xFE, 0xEF, 0xEF, 0x07, 0x1C, 0x38, 0x77, 0xF9, 0xFE, 0xEE, 0xEF, 0x07, 0x1C,
  0x38, 0x73, 0xF8, 0x78, 0xEE, 0xEE, 0x0F, 0x1C, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00,
  0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00,
  0x10, 0x38, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x18, 0x1C, 0x38, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x78,
  0x1F, 0x38, 0x00, 0x00, 0x00, 0x00, 0x3D, 0xF8, 0x1F, 0xBA, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xF0,
  0x0F, 0xFB, 0x00, 0x00, 0x00, 0x01, 0xDF, 0xF0, 0x0F, 0xF3, 0x80, 0x00, 0x00, 0x03, 0xCF, 0xE0,
  0x03, 0xE3, 0xC0, 0x00, 0x00, 0x03, 0xC7, 0xC0, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x03, 0xC0, 0x00,
  0x00, 0xE3, 0xD8, 0x00, 0x00, 0x1B, 0xC7, 0x00, 0x00, 0xFB, 0xDE, 0x00, 0x00, 0x7B, 0xDF, 0x00,
  0x00, 0xFF, 0xDF, 0x00, 0x00, 0xF3, 0xFE, 0x00, 0x00, 0x7F, 0x8F, 0x70, 0x0F, 0xF3, 0xFC, 0x00,
  0x00, 0x3F, 0x8F, 0xFC, 0x7F, 0xF1, 0xFC, 0x00, 0x00, 0x1F, 0x0F, 0xBE, 0xFD, 0xF0, 0xFC, 0x00,
  0x00, 0x00, 0x0F, 0xBF, 0xF9, 0xE0, 0x00, 0x00, 0x00, 0x03, 0xFF, 0x9F, 0xF9, 0xFF, 0xC0, 0x00,
  0x00, 0x03, 0xFF, 0x0F, 0xF1, 0xFF, 0xC0, 0x00, 0x00, 0x01, 0xFF, 0x07, 0xE0, 0xFF, 0x80, 0x00,
  0x00, 0x00, 0xFE, 0xFF, 0xFF, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xC0, 0x00, 0x00,
  0x00, 0x00, 0x03, 0xFE, 0x7F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0x3F, 0x00, 0x00, 0x00
};


Adafruit_SSD1306 display(128, 64, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// Boot graphics and screen refresh
int prettylinecount = 64;
byte screenrefresh = 0;

byte mode = 0; //(0 = bootlogo, 1 = running, 2 = calibrate)

// Pulse counting / pin state
unsigned long pulsecount = 0;
byte lastspeedstate = 0;
byte speedstate = 0;

// Odometer and current mile pulses
unsigned long odometer = 0;
unsigned long currentmile = 0;

// Calibration settings
unsigned long pulsepermile = 0;
byte calmultiplier = 2;

void bootlogo(void)
{
  display.clearDisplay();
  display.drawBitmap((display.width()  - LOGO_WIDTH ) / 2, (display.height() - LOGO_HEIGHT) / 2, logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(1000);
}

void prettyline()
{
  display.clearDisplay();
  display.drawLine(prettylinecount, 45, 128 - prettylinecount, 45, WHITE);
  display.display();
  prettylinecount--;
  prettylinecount--;

}

void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(10);
  Serial.println();
  Serial.println();
  Serial.println("---- stevenhowes/MX5-Arduino-Speed ----");

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  //Initialize with the I2C address 0x3C.

  // Beeper
  pinMode(2, OUTPUT);

  // Speed Input
  pinMode(4, INPUT);


  // Do wanky Triumph Logo
  bootlogo();

  // POST beep
  digitalWrite(2, HIGH);
  delay(50);
  digitalWrite(2, LOW);

  // Get calibrated data and odometer from EEPROM
  EEPROM.get(0, pulsepermile);
  EEPROM.get(4, odometer);

  // Output debug data
  Serial.print("PPM Calibration: ");
  Serial.println(pulsepermile);
  Serial.print("Start Odometer: ");
  Serial.println(odometer);
  Serial.print("Calibration multiplier: ");
  Serial.print(calmultiplier);
  Serial.print(" (");
  Serial.print(1.0/calmultiplier);
  Serial.println(" miles)");

}


void loop()
{
  if (mode == 0)      // Boot mode
  {
    // Boot styling, when it expires default to run
    if (prettylinecount > 0)
    {
      prettyline();
      return;
    } else {
      mode = 1;
    }
  }
  else if (mode == 1) // Run mode
  {
    // If we have serial
    if (Serial.available() > 0)
    {
      String input = Serial.readString();
      // See if it's a cal request
      if (input == "CAL\n")
      {
        // Change to calibrate mode
        mode = 2;

        // Notify user
        Serial.println("---- Calibration Mode ----");
        digitalWrite(2, HIGH);
        delay(500);
        digitalWrite(2, LOW);

        // Draw the calibration screen
        screenrefresh = 1;

      }
      else if (input == "PPM\n")
      {
        // Notify user
        Serial.print("Enter PPM: ");
        digitalWrite(2, HIGH);
        delay(50);
        digitalWrite(2, LOW);

        while (Serial.available() <= 0)
        {}
  
        pulsepermile = Serial.parseInt();
        Serial.println(pulsepermile);
        EEPROM.put(0, pulsepermile);
        Serial.print(pulsepermile);
        Serial.println(" written to EEPROM at address 0");
      }
      else if (input == "ODO\n")
      {
        // Notify user
        Serial.print("Enter ODO: ");
        digitalWrite(2, HIGH);
        delay(50);
        digitalWrite(2, LOW);

        while (Serial.available() <= 0)
        {}
        
        odometer = Serial.parseInt();
        Serial.println(odometer);
        EEPROM.put(4, odometer);
        Serial.print(odometer);
        Serial.println(" written to EEPROM at address 4");
      }
    }
    else
    {
      runmode();
    }
  }
  else if (mode == 2) // Calibration mode
  {
    calmode();
  }
}

void calmode()
{
  // If we're re-drawing the screen
  if (screenrefresh > 0)
  {
    // Clear display and re-draw our dividing line
    display.clearDisplay();
    display.drawLine(0, 45, 127, 45, WHITE);

    // Display our last pulse count
    display.setTextColor(WHITE);
    display.setCursor(10, 10);
    display.setTextSize(2);
    display.println(pulsecount);

    // Mode
    display.setTextSize(1);
    display.setCursor(70, 48);
    display.println("Calibrate");

    // Draw it and clear flag
    display.display();
    screenrefresh = 0;

    // Save our count (will be multipied up later)
    pulsepermile = pulsecount;

    // Reset counter
    pulsecount = 0;
  }

  // until we get serial input, count as quickly as possible
  while (Serial.available() <= 0)
  {
    // Read pin
    speedstate = digitalRead(4);

    // If it has changed
    if (speedstate != lastspeedstate)
    {
      // If we have gone high
      if (speedstate == 1)
      {
        pulsecount++;
      }
    }

    // Record recent state
    lastspeedstate = speedstate;
  }


  if (Serial.readString() == "RUN\n")
  {
    // Calibrate over distances other than one mile (half mile sensible)
    pulsepermile = pulsepermile * calmultiplier;
    EEPROM.put(0, pulsepermile);
    Serial.print(pulsepermile);
    Serial.println(" written to EEPROM at address 0");
    mode = 1;
    screenrefresh = 1;
  } else {
    screenrefresh = 1;
  }
}


void runmode()
{
  screenrefresh = 1;

  // If we're re-drawing the screen
  if (screenrefresh > 0)
  {
    // Used for any strings sent to screen
    char buf[16];

    // Clear display and re-draw our dividing line
    display.clearDisplay();
    display.drawLine(0, 45, 127, 45, WHITE);

    // Display our Speed, offset differently if > 100 (don't routely show third digit)
    display.setTextColor(WHITE);
    if((pulsecount * 2 * 3600 / pulsepermile) > 100)
    {
      display.setCursor(20, 10);
      display.setTextSize(4);
      sprintf(buf,"%03d",(pulsecount * 2 * 3600 / pulsepermile));
    }else{
      display.setCursor(42, 10);
      display.setTextSize(4);
      sprintf(buf,"%02d",(pulsecount * 2 * 3600 / pulsepermile));      
    }
    display.println(buf);
    display.setTextSize(1);
    display.setCursor(90, 32);
    display.println("mph");

    // Display odometer as well
    display.setCursor(5, 48);
    display.setTextSize(1);
    sprintf(buf,"%06d miles",odometer);
    display.println(buf);

    // Draw it and clear flag
    display.display();
    screenrefresh = 0;
  }

  // Add measured pulses to current mile
  currentmile = currentmile + pulsecount;

  // If we have completed a mile
  if (currentmile > pulsepermile)
  {
    // Bump up odometer
    odometer++;

    // Take away a mile
    currentmile = currentmile - pulsepermile;

    // Save to EEPROM
    EEPROM.put(4, odometer);
  }

  // Reset count
  pulsecount = 0;

  // Take samples for half a second
  unsigned long timestamp = micros();
  while (micros() < (timestamp + 500000))
  {
    // Read pin
    speedstate = digitalRead(4);

    // If it has changed
    if (speedstate != lastspeedstate)
    {
      // If we have gone high
      if (speedstate == 1)
      {
        pulsecount++;
      }
    }

    // Record recent state
    lastspeedstate = speedstate;
  }
}

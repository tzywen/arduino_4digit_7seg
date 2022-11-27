int latchPin = 10;  // Latch pin of 74HC595 is connected to Digital pin 5
int clockPin = 12;  // Clock pin of 74HC595 is connected to Digital pin 6
int dataPin = 8;    // Data pin of 74HC595 is connected to Digital pin 4

int sel_8_min = 2;   // select 8mins
int sel_10_min = 3;  // select 8mins
int start_btn = 4;   // start button
int stop_btn = 5;    // stop button

int digits[] = { 252, 96, 218, 242, 102, 182, 190, 224, 254, 246 };          //byte number corresponding to the digit display - obtained thru trial and error
int digits_decimal[] = { 253, 97, 219, 243, 103, 183, 191, 225, 255, 247, 253};  //byte number corresponding to the digit display - obtained thru trial and error

unsigned long previousMillis = 0;  // will store last time counter was updated

const long interval = 1000;  // interval at which to update display and decrement counter (milliseconds)

int reset = 0;
int start = 0;

int counter = 480;
int set_counter = 480;  // initial counter value

byte leds = 0;  // Variable to hold the pattern of which LEDs are currently turned on or off

/*
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */
void setup() {
  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  pinMode(sel_8_min, INPUT_PULLUP);
  pinMode(sel_10_min, INPUT_PULLUP);
  pinMode(start_btn, INPUT_PULLUP);
  pinMode(stop_btn, INPUT_PULLUP);

  pinMode(13, OUTPUT);

  Serial.begin(9600);


}

/*
 * loop() - this function runs over and over again
 */
void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {


    int first_digit = (counter / 60) / 10;
    int second_digit = counter / 60;
    int third_digit = (counter % 60) / 10;
    int fourth_digit = (counter % 60) % 10;

Serial.println(first_digit);
Serial.println(second_digit);
Serial.println(third_digit);
Serial.println(fourth_digit);

    digitalWrite(latchPin, LOW);

    leds = digits[fourth_digit];  // Initially turns all the LEDs off, by giving the variable 'leds' the value 0
    shiftOut(dataPin, clockPin, LSBFIRST, leds);

    leds = digits[third_digit];  // Initially turns all the LEDs off, by giving the variable 'leds' the value 0
    shiftOut(dataPin, clockPin, LSBFIRST, leds);

    leds = digits_decimal[second_digit];  // Initially turns all the LEDs off, by giving the variable 'leds' the value 0
    shiftOut(dataPin, clockPin, LSBFIRST, leds);

    leds = digits[first_digit];  // Initially turns all the LEDs off, by giving the variable 'leds' the value 0
    shiftOut(dataPin, clockPin, LSBFIRST, leds);

    digitalWrite(latchPin, HIGH);

    // save the last time the counter is updated
    previousMillis = currentMillis;
    if ((counter > 0) && (start == 1)) {
      counter = counter - 1;
    }
  }
  if (counter == 0) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }

  if (digitalRead(sel_8_min) == LOW) {
    set_counter = 480;
    counter = set_counter;
    start = 0;
  }

  if (digitalRead(sel_10_min) == LOW) {
    set_counter = 600;
    counter = set_counter;
    start = 0;
  }

  if (digitalRead(start_btn) == LOW) {
    start = 1;
  }

  if (digitalRead(stop_btn) == LOW) {
    start = 0;
  }
}


#include <FastLED.h>
#include <Animation.h>
#include <Button.h>

#define LED_COUNT 60 // BlinkyTape has 60 LEDs!
struct CRGB leds[LED_COUNT]; // this struct contains 60 CRGB values.  This is where 


#define PIN_BUTTON 10
#define PIN_IO_A   7
#define PIN_IO_B   11
#define PIN_SIGNAL 13
#define PIN_INPUT  10

// macros from DateTime.h 
/* Useful Constants */
#define SECS_PER_MIN  (60UL)
#define SECS_PER_HOUR (3600UL)
#define SECS_PER_DAY  (SECS_PER_HOUR * 24L)

/* Useful Macros for getting elapsed time */
#define numberOfSeconds(_time_) (_time_ % SECS_PER_MIN)  
#define numberOfMinutes(_time_) ((_time_ / SECS_PER_MIN) % SECS_PER_MIN) 
#define numberOfHours(_time_) (( _time_% SECS_PER_DAY) / SECS_PER_HOUR)
#define elapsedDays(_time_) ( _time_ / SECS_PER_DAY)  

// set the initial millis value so you don't have to power cycle the blinky tape
long unsigned int initialMillis = 0;

long unsigned int currTime = 0;
CRGB secondsColor = CRGB::White;
CRGB minutesColor = CRGB::Blue;
CRGB hoursColor = CRGB::Red;

// Button Stuff
#define BUTTON_IN    10
Button button = Button(BUTTON_IN, BUTTON_PULLUP_INTERNAL, true, 50);

void reset(Button& b) {
  initialMillis = millis();

  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = CRGB::White;
  }
  LEDS.show();
}

// first, let's get ready to blink using some FastLED routines
// take a look at the FastLED example called Fast2Dev for more usage info
void setup()
{  
  Serial.begin (57600);
  Serial.println("Ready.........FIGHT!");

  //start the timer!
  initialMillis = millis();

  button.pressHandler(reset);
  button.releaseHandler(reset);
  button.holdHandler(reset, 1000); // must be held for at least 1000 ms to trigger

  LEDS.addLeds<WS2812B, PIN_SIGNAL, GRB>(leds, LED_COUNT); // this configures the BlinkyBoard - leave as is.
  LEDS.showColor(CRGB(0, 0, 0)); // set the color for the strip all at once.
//  LEDS.setBrightness(0); // start out with LEDs off
  LEDS.show(); // you'll always need to call this function to make your changes happen.
}


void showTime(long val){  
  int days = elapsedDays(val);
  int hours = numberOfHours(val);
  int minutes = numberOfMinutes(val);
  int seconds = numberOfSeconds(val);

  timeLEDs(days, hours, minutes, seconds);

  // digital clock display of current time
  //  Serial.print(days,DEC);
  //  printDigits(hours);  
  //  printDigits(minutes);
  //  printDigits(seconds);
  //  Serial.println();  
}

void timeLEDs(int days, int hours, int minutes, int seconds) {
  //Seconds
  for (int i = 0; i < LED_COUNT; i++) {
    if(seconds == i) {
      leds[i] = secondsColor;
    } else {
      if(minutes == i+1 && hours == i+1) { //combine hours and minutes for this minute`
        leds[i] = CRGB(255, 0, 255); //violet
      } else if(minutes == i+1) { // set the minute
        leds[i] = minutesColor;
      } else if(hours == i+1) { // set the hour
        leds[i] = hoursColor;
      } else {
        leds[i] = CRGB::Black;
      }
    }
  }

  LEDS.show();

}



//void printDigits(byte digits){
// // utility function for digital clock display: prints colon and leading 0
// Serial.print(":");
// if(digits < 10)
//   Serial.print('0');
// Serial.print(digits,DEC);  
//}

void loop() {
  currTime = ((millis()-initialMillis) / 1000);
  showTime(currTime);
  button.process();
  delay(1000);
//  Serial.print(currTime);
}


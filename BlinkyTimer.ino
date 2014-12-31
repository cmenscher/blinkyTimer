#include <FastLED.h>
#include <Animation.h>

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

int color_set = 0;
long unsigned int currTime = 0;
CRGB secondsColor = CRGB::White;
CRGB minutesColor = CRGB::Blue;
CRGB hoursColor = CRGB::Red;

// first, let's get ready to blink using some FastLED routines
// take a look at the FastLED example called Fast2Dev for more usage info
void setup()
{  
  Serial.begin (57600);
  Serial.println("Ready.........FIGHT!");

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
  Serial.print(days,DEC);
  printDigits(hours);  
  printDigits(minutes);
  printDigits(seconds);
  Serial.println();  
}

void timeLEDs(int days, int hours, int minutes, int seconds) {

  //Seconds
  for (int i = 0; i < LED_COUNT; i++) {
    if(seconds == i) {
      leds[i] = secondsColor;
    } else {
      if(minutes == i+1 && hours == i+1) { //combine hours and minutes for this minute
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


void printDigits(byte digits){
 // utility function for digital clock display: prints colon and leading 0
 Serial.print(":");
 if(digits < 10)
   Serial.print('0');
 Serial.print(digits,DEC);  
}

void loop() {
  currTime = (millis() / 1000);
  showTime(currTime);
  delay(1000);
//  Serial.print(currTime);
}

//
//// set the color for all the LEDs based on the color code
//void setcolor(int colorcode) {
//
//  for (int i = 0; i < LED_COUNT; i++) {
//    // instead of setting the color all at once we're going to step through each LED to show how to set them individually
//    switch(colorcode) { 
//      // there are several ways to set colors. We're going to pass a CRGB here, but there are other methods.  
//      // See the Fast2Dev example for the others
//      case 0: leds[i] = CRGB(i*3+10,0,0); break; // using the 'i' term will create a brightness gradient in active color 
//    
//      case 1: leds[i] = CRGB(0,i*3+10,0); break;
//    
//      case 2: leds[i] = CRGB(0,0,i*3+10); break;
//    }
//  }
//  LEDS.show();
//}
//
//// we'll make the color fade in and out by setting the brightness
//void pulse(int wait_time) {
//  // let's fade up by scaling the brightness - in general, brightness shouldn't go above 93, so the strip won't draw too much power.
//  // Oh, and 93 is plenty bright!
//  for(int scale = 0; scale < 93; scale++) { 
//    LEDS.setBrightness(scale);
//    LEDS.show();
//    delay(wait_time);
//  }
//  // now let's fade down by scaling the brightness
//  for(int scale = 93; scale > 0; scale--) { 
//    LEDS.setBrightness(scale);
//    LEDS.show();
//    delay(wait_time);
//  }
//}
//
//// this is the main loop where we call the other functions. 
//void loop() {
//  int waiting_time = 40; //time in ms for color scaling
//  
//  setcolor(color_set); // we call our color-set routine
//  
//  pulse(waiting_time); // now we make it fade in and out
//
//  color_set++; // OK - next color!
//  color_set = color_set % 3; // modulus, just so we always stay below 2 and our function works.
//}

#include "LedControl.h"

//LedControl lc=LedControl(11din13,9clk14,10cs2,2);  // Pin and # of Displays

LedControl lc=LedControl(13,14,2,2);  // Pin and # of Displays

unsigned long delayTime=1000;  // Delay between Frames

// Put values in arrays
byte invader1a[] =
{
   B00000000,    // First frame of invader #1
   B00000000,
   B00000000,
   B10000000,
   B11000000,
   B01100000,
   B00110000,
   B00110000
};

byte invader1b[] =
{
  B00011000, // Second frame of invader #1
  B00111100,
  B01111110,
  B11011011,
  B11111111,
  B00100100,
  B01011010,
  B01000010
};

byte invader2a[] =
{
   B00000000,  // First frame of invader #2
   B00000000,
   B00000000,
   B00011111,
   B00111111,
   B01100000,
   B11000000,
   B10000000
};

byte invader2b[] =
{
  B00100100, // Second frame of invader #3
  B10100101,
  B11111111,
  B11011011,
  B11111111,
  B01111110,
  B00100100,
  B01000010
};

// Put values in arrays
byte invader3a[] =
{
   B00000000,    // First frame of invader #1
   B00000000,
   B00000000,
   B10000000,
   B11000000,
   B01100000,
   B00110000,
   B00110000
};

byte invader3b[] =
{
  B00011000, // Second frame of invader #1
  B00111100,
  B01111110,
  B11011011,
  B11111111,
  B00100100,
  B01011010,
  B01000010
};

byte invader4a[] =
{
   B00000000,  // First frame of invader #2
   B00000000,
   B00000000,
   B00011111,
   B00111111,
   B01100000,
   B11000000,
   B10000000
};

byte invader4b[] =
{
  B00100100, // Second frame of invader #3
  B10100101,
  B11111111,
  B11011011,
  B11111111,
  B01111110,
  B00100100,
  B01000010
};


void setup()
{
  lc.shutdown(0,false);  // Wake up displays
  lc.shutdown(1,false);
  lc.shutdown(2,false);  
  lc.shutdown(3,false);
  lc.setIntensity(0,5);  // Set intensity levels
  lc.setIntensity(1,5);
  lc.setIntensity(2,5);  
  lc.setIntensity(3,5);
  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
}


//  Take values in Arrays and Display them
void sinvader1a()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,invader1a[i]);
  }
}

void sinvader1b()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0,i,invader1b[i]);
  }
}

void sinvader2a()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(1,i,invader2a[i]);
  }
}

void sinvader2b()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(1,i,invader2b[i]);
  }
}

void sinvader3a()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(3,i,invader3a[i]);
  }
}

void sinvader3b()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(3,i,invader3b[i]);
  }
}

void sinvader4a()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(4,i,invader4a[i]);
  }
}

void sinvader4b()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(4,i,invader4b[i]);
  }
}


void loop()
{
// Put #1 frame on both Display
    sinvader1a();
   // delay(delayTime);
    sinvader2a();
   // delay(delayTime);


// Put #2 frame on both Display
   // sinvader1b();
    //delay(delayTime);
   // sinvader2b();
   // delay(delayTime);

}
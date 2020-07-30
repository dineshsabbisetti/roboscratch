#include "LedControl.h"

//LedControl lc=LedControl(11din13,9clk14,10cs2,2);  // Pin and # of Displays

LedControl lc=LedControl(13,14,2,4);  // Pin and # of Displays

unsigned long delayTime=500;  // Delay between Frames

// Put values in arrays

///////////////////////////////////////////////////////

byte matrix1a[] =
{
   B00000000, 
   B00000000,
   B00000000,
   B11111000,
   B11111100,
   B00000110,
   B00000011,
   B00000001
};

byte matrix2a[] =
{
   B00000000,
   B00000000,
   B00000000,
   B00000001,
   B00000011,
   B00000110,
   B00001100,
   B00001100
};

byte matrix3a[] =
{
   B00000000,
   B00000000,
   B00000000,
   B10000000,
   B11000000,
   B01100000,
   B00110000,
   B00110000
};

byte matrix4a[] =
{
   B00000000,
   B00000000,
   B00000000,
   B00011111,
   B00111111,
   B01100000,
   B11000000,
   B10000000
};

///////////////////////////////////////////////////////

byte matrix1b[] =
{
   B00000000,
   B10000000,
   B11000000,
   B10000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000
};

byte matrix2b[] =
{

   B00000000,
   B00000000,
   B00000001,
   B00000011,
   B00000111,
   B00001110,
   B00011100,
   B00011000
};

byte matrix3b[] =
{
   B00000000,
   B00000000,
   B10000000,
   B11000000,
   B11100000,
   B01110000,
   B00111000,
   B00011000
};

byte matrix4b[] =
{
   B00000000,
   B00000001,
   B00000011,
   B00000001,
   B00000000,
   B00000000,
   B00000000,
   B00000000
};

///////////////////////////////////////////////////////

byte matrix1c[] =
{
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B10000000,
   B11000000,
   B11100000,
   B01100000
};

byte matrix2c[] =
{

   B00000000,
   B00001100,
   B00001110,
   B00000111,
   B00000011,
   B00000001,
   B00000000,
   B00000000
};

byte matrix3c[] =
{
   B00000000,
   B00110000,
   B01110000,
   B11100000,
   B11000000,
   B10000000,
   B00000000,
   B00000000
};

byte matrix4c[] =
{
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000001,
   B00000011,
   B00000111,
   B00000110
};

///////////////////////////////////////////////////////

byte matrix1d[] =
{
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000
};

byte matrix2d[] =
{
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B11111111
};

byte matrix3d[] =
{
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000
};

byte matrix4d[] =
{
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B11111111
};

///////////////////////////////////////////////////////

byte matrix1e[] =
{
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B11111111
};

byte matrix2e[] =
{
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000
};

byte matrix3e[] =
{
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B11111111,
   B11111111
};

byte matrix4e[] =
{
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00000000
};

///////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////

void smatrix1a()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(0,i,matrix1a[i]);
  }
}

void smatrix2a()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(1,i,matrix2a[i]);
  }
}

void smatrix3a()
{
  for (int i = 0; i < 8; i++)  
  {
    lc.setRow(2,i,matrix3a[i]);
  }
}

void smatrix4a()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(3,i,matrix4a[i]);
  }
}

///////////////////////////////////////////////////////

void smatrix1b()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0,i,matrix1b[i]);
  }
}

void smatrix2b()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(1,i,matrix2b[i]);
  }
}

void smatrix3b()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(2,i,matrix3b[i]);
  }
}

void smatrix4b()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(3,i,matrix4b[i]);
  }
}

///////////////////////////////////////////////////////

void smatrix1c()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0,i,matrix1c[i]);
  }
}

void smatrix2c()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(1,i,matrix2c[i]);
  }
}

void smatrix3c()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(2,i,matrix3c[i]);
  }
}

void smatrix4c()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(3,i,matrix4c[i]);
  }
}


///////////////////////////////////////////////////////

void smatrix1d()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0,i,matrix1d[i]);
  }
}

void smatrix2d()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(1,i,matrix2d[i]);
  }
}

void smatrix3d()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(2,i,matrix3d[i]);
  }
}

void smatrix4d()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(3,i,matrix4d[i]);
  }
}

///////////////////////////////////////////////////////

void smatrix1e()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(0,i,matrix1e[i]);
  }
}

void smatrix2e()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(1,i,matrix2e[i]);
  }
}

void smatrix3e()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(2,i,matrix3e[i]);
  }
}

void smatrix4e()
{
  for (int i = 0; i < 8; i++)
  {
    lc.setRow(3,i,matrix4e[i]);
  }
}

///////////////////////////////////////////////////////

void anim1()
{
    smatrix1a();
    smatrix2a();
    smatrix3a();
    smatrix4a();   
}

void anim2()
{
    smatrix1b();
    smatrix2b();
    smatrix3b();
    smatrix4b();   
}

void anim3()
{
    smatrix1c();
    smatrix2c();
    smatrix3c();
    smatrix4c();   
}

void anim4()
{
    smatrix1d();
    smatrix2d();
    smatrix3d();
    smatrix4d();   
}

void anim5()
{
    smatrix1e();
    smatrix2e();
    smatrix3e();
    smatrix4e();   
}

///////////////////////////////////////////////////////

void clear()
{
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
}
///////////////////////////////////////////////////////

void loop()
{
    smatrix1a();  // Put #1 frame on Displays
    smatrix2a();
    smatrix3a();
    smatrix4a();   

    delay(delayTime);

  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);

    delay(delayTime);
  
    smatrix1b();
    smatrix2b();
    smatrix3b();
    smatrix4b();
    
    delay(delayTime);
    
  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
  
    delay(delayTime);
  
    smatrix1c();
    smatrix2c();
    smatrix3c();
    smatrix4c();
    
    delay(delayTime);

  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
  
    delay(delayTime);
  
    smatrix1d();
    smatrix2d();
    smatrix3d();
    smatrix4d();
    
    delay(delayTime);
    
  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
      
    delay(delayTime);
  
    smatrix1e();
    smatrix2e();
    smatrix3e();
    smatrix4e();
    
    delay(delayTime);
    
  lc.clearDisplay(0);  // Clear Displays
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
      
    delay(delayTime);
      anim4();
    delay(delayTime);
      clear();
    delay(delayTime);
      anim5();
    delay(delayTime);
      clear();
    delay(delayTime);
    
}
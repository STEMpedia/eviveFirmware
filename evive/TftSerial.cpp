#include "TftSerial.h"
//	TftSerial :: TftSerial()
//	{
//		tft = TFT_ST7735();
//	}
 
	void TftSerial :: begin()
	{
		//tft.init();
		//tft.setRotation(1);
//		Serial.println(tft.width());
//		Serial.println(tft.height());
		tft.fillRect(0, TOP_MARGIN, TFT_WIDTH, TFT_HEIGHT - TOP_MARGIN - BOTTOM_MARGIN, ST7735_BLACK);
		next_line=2*ROW_HEIGHT;
		next_col=0;
		tft.setTextColor(ST7735_RED);
	}

  void TftSerial :: print(int i)
  {
  	/*
		tft.fillRect(next_col, next_line, tft.width()-next_col, ROW_HEIGHT, ST7735_BLACK);
		tft.fillRect(0, next_line+ROW_HEIGHT, tft.width(), ROW_HEIGHT, ST7735_BLACK);
		tft.setCursor(next_col, next_line);
		if(next_col == 0)	tft.print(">");
		tft.print(i);
		//next_line=next_line+8;
		if(next_col == 0) next_col = next_col + CHAR_WIDTH*(dig(i)+1);
		else next_col = next_col + CHAR_WIDTH*(dig(i));
		
		if(next_line >= TFT_HEIGHT-ROW_HEIGHT)
		  next_line = TOP_MARGIN;
		if(next_col > TFT_WIDTH-CHAR_WIDTH)
		{
				next_col = 0;
				next_line = next_line + ROW_HEIGHT;
		}i
		*/
  	s=String(i);
  	print(s);
  }
	
	// void	TftSerial :: print(int i, int base){
		
	// }
	
   void TftSerial :: println(int i)
   {
		tft.fillRect(next_col, next_line, tft.width()-next_col, ROW_HEIGHT, ST7735_BLACK);
		tft.fillRect(0, next_line+ROW_HEIGHT, tft.width(), ROW_HEIGHT, ST7735_BLACK);
		tft.setCursor(next_col,next_line);
		if(next_col == 0)	tft.print(">");
		tft.print(i);
		next_line=next_line + ROW_HEIGHT;
		//next_col=next_col+CHAR_WIDTH*dig(i);
		next_col = 0;
		if(next_line>TFT_HEIGHT-ROW_HEIGHT)
			next_line=TOP_MARGIN;
		if(next_col>TFT_WIDTH-CHAR_WIDTH)
		{
			next_col=0;
			next_line=next_line+ROW_HEIGHT;
		}

#ifdef __DEBUG__
		Serial.println(freeRam());
#endif
   }	

  void TftSerial :: print(char c)
  {
		tft.setCursor(next_col,next_line);
		tft.fillRect(next_col,next_line,24,8,ST7735_BLACK);
		//tft.print(">");
		tft.print(c);
		//next_line=next_line+8;
		next_col=next_col + CHAR_WIDTH;
		
		if(next_line>=TFT_HEIGHT-ROW_HEIGHT)
		  next_line=2*ROW_HEIGHT;
		if(next_col>TFT_WIDTH-CHAR_WIDTH)
		{
			next_col=0;
			next_line=next_line + ROW_HEIGHT;
		}

#ifdef __DEBUG__
		Serial.println(freeRam());
#endif
  }

  void TftSerial :: print(double d)
  {
  	s=String(d);
  	print(s);
  	#ifdef __DEBUG__
  			Serial.println(freeRam());
  	#endif
  }

  void TftSerial :: print(float f)
  {
  	s=String(f);
  	print(f);

  }

  void TftSerial :: println(double d)
  {
  	s=String(d);
  	println(s);
  }

  void TftSerial :: println(float f)
  {
  	s=String(f);
  	println(f);
  }
   
   void TftSerial :: print(String s)
   {
		for(int j=0;j<s.length();j++)
		{
			tft.print(s[j]);
		}
   }
	 
/* 	size_t TftSerial :: print(double number, uint8_t digits) 
{ 
  size_t n = 0;
  
  if (isnan(number)) return print("nan");
  if (isinf(number)) return print("inf");
  if (number > 4294967040.0) return print ("ovf");  // constant determined empirically
  if (number <-4294967040.0) return print ("ovf");  // constant determined empirically
  
  // Handle negative numbers
  if (number < 0.0)
  {
     n += print('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  n += print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0) {
    n += print("."); 
  }

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    unsigned int toPrint = (unsigned int)(remainder);
    n += print(toPrint);
    remainder -= toPrint; 
  } 
  
  return n;
	} */
   
	void TftSerial :: println(){
		tft.fillRect(next_col, next_line, tft.width()-next_col, ROW_HEIGHT, ST7735_BLACK);
		tft.fillRect(0, next_line+ROW_HEIGHT, tft.width(), ROW_HEIGHT, ST7735_BLACK);
		//tft.setCursor(next_col,next_line);
		//if(next_col == 0)	tft.print(">");
		//tft.print(i);
		next_line=next_line + ROW_HEIGHT;
		//next_col=next_col+CHAR_WIDTH*dig(i);
		next_col = 0;
		if(next_line>TFT_HEIGHT-ROW_HEIGHT)
			next_line=TOP_MARGIN;
		if(next_col>TFT_WIDTH-CHAR_WIDTH)
		{
			next_col=0;
			next_line=next_line+ROW_HEIGHT;
		}
  }
	
	
	
	
	
	
  void  TftSerial :: println(char c)
  {	
		
		next_line=next_line+ROW_HEIGHT;
		tft.setCursor(0,next_line);
		tft.fillRect(0,next_line,tft.width(),24,ST7735_BLACK);
		tft.print(">");
		tft.print(c);
		
		next_col=next_col+8;
		if(next_line>=TFT_HEIGHT-CHAR_HEIGHT)
			next_line=0;
		if(next_col>TFT_WIDTH-CHAR_WIDTH)
		{
			next_col=0;
			next_line=next_line+ROW_HEIGHT;
		}
  }
	
	

   
   void TftSerial :: println(String s)
   {
   		lines=(CHAR_WIDTH*s.length()/128)+1;
   		//Serial.println(lines);
	   next_line=next_line + ROW_HEIGHT;
	   tft.fillRect(0,next_line,tft.width(), 2*lines*ROW_HEIGHT, ST7735_BLACK);
	   next_col=0;
	   
	   
	   print('>');
	   for(int j=0; j<s.length(); j++)
		{
			print(s[j]);
		}
   }
	 
	int dig(int i)
	{
		if(i==0)
			return 1;
		
		int count=0;
			while(i != 0)
		{
			// n = n/10
			i /= 10;
			++count;
		}
		return count;
	}

//TftSerial TftMonitor;

Simplemonitor8x8 : Library for display sequential data on 8x8 LEDs like MAX7219
============

Version 1.0

by Dennis.Kim

contact: bluedskim@gmail.com

See the online documentation here: https://bitbucket.org/bluedskim/simplemonitor8x8
See examples/ directory for simple examples

	#include <LedControl.h>
	#include <SimpleMonitor8x8.h>

	int potpin = 0; //set analog interface #0 to connect photocell
	int val = 0; //define variable val

	// Please refer to http://playground.arduino.cc/Main/LedControlDemos
	LedControl lc=LedControl(12,11,10,1);
	// I think the maximum value is 567
	// If you want to see more dynamic chart, put 'true'
	// but I don't want dynamic rescaling chart(automatic zoom feature), so I put 'true'
	SimpleMonitor8x8 mon8x8 = SimpleMonitor8x8(567, true);

	void setup()
	{
	  /*
	   The MAX72XX is in power-saving mode on startup,
	   we have to do a wakeup call
	   */
	  lc.shutdown(0,false);
	  /* Set the brightness to a medium values */
	  lc.setIntensity(0,8);
	  /* and clear the display */
	  lc.clearDisplay(0);
		
	  mon8x8.demo(lc);  
	}

	void loop()
	{
	  val = analogRead(potpin); //read analog
	  // 1. View 2Digits only 
	  //mon8x8.display2DigitsTo8x8(lc, val);
	  // 2. View line chart only 
	  mon8x8.displayLineChartTo8x8(lc, val);
	  // 3. View 2Digits and line chart in turns
	  //mon8x8.displayTo8x8(lc, val, 500);  
	  delay(250);//delay 0.5 s
	}

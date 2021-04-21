/*
 * SimpleMonitor8x8_h - Library for display sequencial data on 8x8 LEDs like MAX7219
 * Created by Dennis.Kim, Sep 12. 2015
 * Released into the public domain.
*/

#ifndef SimpleMonitor8x8_h
#define SimpleMonitor8x8_h

#include "Arduino.h"
#include "LedControl.h"

class SimpleMonitor8x8
{
  public:
    /*
     * default generator
     */
    SimpleMonitor8x8();
    /*
     * _maxVal : estimated maximum value. if real value is over, the matrix shows wrong data.
     * _rescaleGraphByMaxValInHistory : If you want to see more dynamic chart, put 'true'.
     *                   If you don't want dynamic rescaling chart, put 'false'
     */
    SimpleMonitor8x8(int _maxVal, boolean rescaleGraphByMaxValInHistory);
    // 1. View 2Digits only
    int display2DigitsTo8x8(LedControl lc, int val);
    // 2. View line chart only
    int displayLineChartTo8x8(LedControl lc, int val);
    // 3. View 2Digits and line chart in turns
    int displayTo8x8(LedControl lc, int val, int interVal);
    // Run demo
    void demo(LedControl lc);
    int maxVal;
    boolean rescaleGraphByMaxValInHistory;
    int chartData[8];
    int chartDataScaled[8];
  private:
};

#endif


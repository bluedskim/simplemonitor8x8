/*
 * SimpleMonitor8x8_h - Library for display sequencial data on 8x8 LEDs like MAX7219
 * Created by Dennis.Kim, Sep 12. 2015
 * Released into the public domain.
*/

#include "Arduino.h"
#include "LedControl.h"
#include "SimpleMonitor8x8.h"

/*
 * default generator
 */
SimpleMonitor8x8::SimpleMonitor8x8()
{
  maxVal = 100;
  rescaleGraphByMaxValInHistory = false;
}

SimpleMonitor8x8::SimpleMonitor8x8(int _maxVal, boolean _rescaleGraphByMaxValInHistory)
{
  maxVal = _maxVal;
  rescaleGraphByMaxValInHistory = _rescaleGraphByMaxValInHistory;
  for (int i = 1 ; i < 8 ; i++) {
    chartData[i] = 0;
    chartDataScaled[i] = 0;
  }
}

void SimpleMonitor8x8::demo(LedControl lc)
{
  for (int i = 0 ; i < 100 ; i = i + 10) {
    displayTo8x8(lc, i, 200);
    delay(200);
  }

  for (int i = 1 ; i < 8 ; i++) {
    chartData[i] = 0;
    chartDataScaled[i] = 0;
  }
}

int SimpleMonitor8x8::displayTo8x8(LedControl lc, int val, int interval)
{
  int scaled = display2DigitsTo8x8(lc, val);
  delay(interval);
  displayLineChartTo8x8(lc, val);
  return scaled;
}

int SimpleMonitor8x8::display2DigitsTo8x8(LedControl lc, int val)
{
  if (maxVal > 0) val = map(val, 0, maxVal, 0, 99);
  lc.clearDisplay(0);
  String valString = String(val);
  int fitstDigit = val / 10;
  int secondDigit = val % 10;
  //Serial.print("fitstDigit=");Serial.println(fitstDigit);
  //Serial.print("secondDigit=");Serial.println(secondDigit);
  /* here is the data for the characters */
  byte digits[10][5] = {
    { B11100000  // 0
      , B10100000
      , B10100000
      , B10100000
      , B11100000
    }
    , {
      B00100000  // 1
      , B00100000
      , B00100000
      , B00100000
      , B00100000
    }
    , {
      B11100000  // 2
      , B00100000
      , B11100000
      , B10000000
      , B11100000
    }
    , {
      B11100000  // 3
      , B00100000
      , B11100000
      , B00100000
      , B11100000
    }
    , {
      B10100000  // 4
      , B10100000
      , B11100000
      , B00100000
      , B00100000
    }
    , {
      B11100000  // 5
      , B10000000
      , B11100000
      , B00100000
      , B11100000
    }
    , {
      B11100000  // 6
      , B10000000
      , B11100000
      , B10100000
      , B11100000
    }
    , {
      B11100000  // 7
      , B00100000
      , B00100000
      , B00100000
      , B00100000
    }
    , {
      B11100000  // 8
      , B10100000
      , B11100000
      , B10100000
      , B11100000
    }
    , {
      B11100000  // 9
      , B10100000
      , B11100000
      , B00100000
      , B00100000
    }
  };

  byte firstDigitByte[5], secondDigitByte[5], digit[5];
  memcpy(firstDigitByte, digits[fitstDigit], sizeof(firstDigitByte));
  memcpy(secondDigitByte, digits[secondDigit], sizeof(secondDigitByte));
  //Serial.print("sizeof(firstDigitByte)=");Serial.println(sizeof(firstDigitByte));

  for (int i = 0 ; i < sizeof(firstDigitByte) ; i++) {
    digit[i] = firstDigitByte[i] | (secondDigitByte[i] >> 4);
  }

  for (int i = 0 ; i < sizeof(digit) ; i++) {
    lc.setRow(0, i, digit[i]);
  }
  return val;
}

int SimpleMonitor8x8::displayLineChartTo8x8(LedControl lc, int val) {
  lc.clearDisplay(0);
  byte bars[8] = {
    B00000001
    , B00000011
    , B00000111
    , B00001111
    , B00011111
    , B00111111
    , B01111111
    , B11111111
  };

  //Serial.print("sizeof(chartData)=");Serial.println(sizeof(chartData));
  for (int i = 1 ; i < 8 ; i++) {
    chartData[i - 1] = chartData[i];
  }
  chartData[7] = val;

  int maxValInHistory = maxVal;
  if (rescaleGraphByMaxValInHistory) {
    maxValInHistory = 0;
    for (int i = 0 ; i < 8 ; i++) {
      if (maxValInHistory < chartData[i]) maxValInHistory = chartData[i];
    }
    //Serial.print("maxVal=");Serial.print(maxVal);Serial.print(" minVal=");Serial.println(minVal);
  }

  for (int i = 0 ; i < 8 ; i++) {
    chartDataScaled[i] = map(chartData[i], 0, maxValInHistory, 0, 7);
    //Serial.print("chartDataScaled[i]=");Serial.println(chartDataScaled[i]);
    lc.setColumn(0, i, bars[chartDataScaled[i]]);
  }
  return chartDataScaled[8];
}

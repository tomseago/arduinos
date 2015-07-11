#include "MicroView.h"
#include "stdio.h"
#include "string.h"

char buf[20];

#define HISTORY_MAX 20
char history[HISTORY_MAX+1];

void setup() {
  uView.begin();
  uView.clear(PAGE);
  
  pinMode(A0, INPUT);
  
  for(int i=0; i<HISTORY_MAX; i++) {
    history[i] = 32;
  }
  history[HISTORY_MAX] = 0;
}



char last = 0;
int lastMeasurement = 0;
void loop() {
  int val = analogRead(A0);
  
  sprintf(buf, "%d  ", val);
  
  uView.setCursor(0,0);

  uView.print(buf);
  
  // Debounce by looking for a +/- only 1 or 2 value change
  int delta = val - lastMeasurement;
  lastMeasurement = val;
  
  if (delta > 2 || delta < 2) return;
  
  // Measured divisions are:
  // 930
  //    910 - break
  // 890
  //    870 - break
  // 850
  //    820 - break
  // 785
  //    750 - break
  
  char button = 0;
  if (val > 910) {
    button = 4;
  } else if (val > 870) {
    button = 3;
  } else if (val > 820) {
    button = 2;
  } else if (val > 750) {
    button = 1;
  }
  
  buf[0] = '0' + button;
  buf[1] = 0;
  uView.setCursor(10, 20);
  uView.print(buf);


  if (button != last && button != 0) {
    // Add to the history and output the history
    memmove(history+1, history, HISTORY_MAX-1);
    history[0] = buf[0];
    uView.setCursor(0,30);
    uView.print(history);
  }
  last = button;
  
  uView.display();

}

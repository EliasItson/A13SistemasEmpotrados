#include <Bounce2.h>

const unsigned int PIN_LED_R = 2;
const unsigned int PIN_LED_V = 4;
const unsigned int PIN_SWITCH_R = 5;
const unsigned int PIN_SWITCH_V = 18;

const int FREQUENCY = 5000;
const int CHANNEL_R = 0;
const int CHANNEL_V = 1;
const int RESOLUTION = 8;

const int CT_MIN = 0;
const int CT_MAX = 250;

int CT_R = CT_MAX;
int CT_V = CT_MIN;

const int step = 25;

Bounce debouncer1 = Bounce();
Bounce debouncer2 = Bounce();

void updatePWM();

void setup() {

  ledcAttachChannel(PIN_LED_R, FREQUENCY, RESOLUTION,
                    CHANNEL_R);
  ledcAttachChannel(PIN_LED_V, FREQUENCY, RESOLUTION,
                    CHANNEL_V);

  pinMode(PIN_SWITCH_R, INPUT);
  pinMode(PIN_SWITCH_V, INPUT);

  debouncer1.attach(PIN_SWITCH_R);
  debouncer2.attach(PIN_SWITCH_V);

  debouncer1.interval(25);
  debouncer2.interval(25);

  updatePWM();

}
void loop() {

  debouncer1.update();
  debouncer2.update();


  if(debouncer1.fell()) {
    CT_R = max(CT_R - step, CT_MIN);
    CT_V = min(CT_V + step, CT_MAX);
    updatePWM();
  }

  if(debouncer2.fell()) {
    CT_V = max(CT_V - step, CT_MIN);
    CT_R = min(CT_R + step, CT_MAX);
    updatePWM();
  }

}

void updatePWM() {
  ledcWrite(PIN_LED_R, CT_R);
  ledcWrite(PIN_LED_V, CT_V);
}
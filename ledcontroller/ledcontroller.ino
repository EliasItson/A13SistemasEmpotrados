#include <Arduino.h>

#define LED_A 2  // LED1 (Rojo)
#define LED_B 5  // LED2 (Verde)
#define BOTON_A 18 // S1
#define BOTON_B 4  // S2

#define PWM_CHANNEL_A 0
#define PWM_CHANNEL_B 1
#define PWM_FREQ 5000
#define PWM_RESOLUTION 8
#define STEP 25

int dutyCycleA = 255; 
int dutyCycleB = 0;   

void setup() {
    pinMode(BOTON_A, INPUT_PULLDOWN);
    pinMode(BOTON_B, INPUT_PULLDOWN);

    ledcAttachChannel(LED_A, PWM_FREQ, PWM_RESOLUTION, PWM_CHANNEL_A);
    ledcAttachChannel(LED_B, PWM_FREQ, PWM_RESOLUTION, PWM_CHANNEL_B);
    
    ledcWrite(PWM_CHANNEL_A, dutyCycleA);
    ledcWrite(PWM_CHANNEL_B, dutyCycleB);
}

void loop() {
    if (digitalRead(BOTON_A) == HIGH) { 
        if (dutyCycleA > 0) {
            dutyCycleA -= STEP;
            dutyCycleB += STEP;
            ledcWrite(PWM_CHANNEL_A, dutyCycleA);
            ledcWrite(PWM_CHANNEL_B, dutyCycleB);
            delay(200); 
        }
    }
    
    if (digitalRead(BOTON_B) == HIGH) { 
        if (dutyCycleB > 0) {
            dutyCycleA += STEP;
            dutyCycleB -= STEP;
            ledcWrite(PWM_CHANNEL_A, dutyCycleA);
            ledcWrite(PWM_CHANNEL_B, dutyCycleB);
            delay(200);
        }
    }
}
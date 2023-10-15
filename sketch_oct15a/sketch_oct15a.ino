
const int DELAY = 60;
const int LED_PIN = 9;
const int MOTION_DETECTOR_PIN = 2;

int brightness = 0;
int fadeAmount = 5;

unsigned long lastDebounceTime = 0;
int debounceDelay = 50;
int ledState = HIGH;
int buttonState = HIGH;
int lastButtonState = LOW;
bool motionDetected = false;
unsigned long lastMotionDetectedTime = 0;

unsigned long activatedDuration = 10 * 1000;
int fadingDuration = 2 * 1000;

void setup() {
 Serial.begin(9600);
  // put your setup code here, to run once:
 pinMode(LED_PIN, OUTPUT);
 pinMode(MOTION_DETECTOR_PIN, INPUT);

 analogWrite(LED_PIN, LOW);
 lastMotionDetectedTime = millis() + activatedDuration;
}

void loop() {
  // put your main code here, to run repeatedly:
  // digitalWrite(LED_BUILTIN, HIGH);
  // delay(DELAY);
  // digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  // delay(DELAY);

  // Fading
  // analogWrite(LED_PIN, brightness);
  // if (brightness <= 0 || brightness >= 255) {
  //   delay(1000);
  // }
  // else
  // {
  //   delay(DELAY);
  // }


  // brightness = brightness + fadeAmount;

  // if (brightness <= 0 || brightness >= 255) {
  //   // fadeAmount = -fadeAmount;
  //   fadeAmount = fadeAmount * -1;
  // }
  // int reading = digitalRead(BUTTON_PIN);
  // Serial.println(reading);

  // // if (reading != buttonState) {
  // //   lastDebounceTime = millis();
  // // }


  // // if ((millis() - lastDebounceTime) > debounceDelay) {
  // //   if (reading != buttonState) {
  // //     buttonState = reading;
  // //     Serial.println(buttonState);
  // //   }
  // // }
  int reading = digitalRead(MOTION_DETECTOR_PIN);
  // Serial.println(reading);
  if (reading == HIGH) {
    lastMotionDetectedTime = lastDebounceTime = millis();
  }
/*
  if ((millis() - lastDebounceTime) > debounceDelay){
    if (reading == HIGH && !motionDetected) {
      motionDetected = true;
      lastMotionDetectedTime = millis();
      Serial.println(lastMotionDetectedTime);
      // Serial.println();
    }
    buttonState = reading;
  }
  else {
    motionDetected = false;
  }
  */
  unsigned long now = millis();
  unsigned long activatedTime = now - lastMotionDetectedTime;
  if (activatedTime <= activatedDuration) {
    // Within the activation period
    if (activatedTime < fadingDuration) {
      brightness = (activatedTime / (float)fadingDuration) * 255;
    }
    else if ((activatedDuration - activatedTime) < fadingDuration) {
      brightness = ((activatedDuration - activatedTime)/(float)fadingDuration) * 255;
    }
    else {
      brightness = 255;
    }
  }
  else
  {
    motionDetected = false;
    brightness = 0;
  }

  // buttonState = digitalRead(BUTTON_PIN);
  // Serial.println(brightness);
  // Serial.println(((millis() - lastMotionDetectedTime) > activatedDuration) == true);

  analogWrite(LED_PIN, brightness);
  // delay(debounceDelay);
  // buttonState = !buttonState;
}

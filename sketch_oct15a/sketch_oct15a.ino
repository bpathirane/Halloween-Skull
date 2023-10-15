
const int DELAY = 60;
const int LED_PIN = 9;
const int BUTTON_PIN = 2;

int brightness = 0;
int fadeAmount = 5;

int lastDebounceTime = 0;
int debounceDelay = 50;
int ledState = HIGH;
int buttonState = HIGH;
int lastButtonState = LOW;

void setup() {
  // put your setup code here, to run once:
 pinMode(LED_PIN, OUTPUT);
 pinMode(BUTTON_PIN, INPUT);

 digitalWrite(LED_PIN, buttonState);
 digitalWrite(13, LOW);

 Serial.begin(9600);
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
  int reading = digitalRead(BUTTON_PIN);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay){
    buttonState = reading;
  }

  // buttonState = digitalRead(BUTTON_PIN);

  digitalWrite(LED_PIN, buttonState);
  // delay(debounceDelay);
  // buttonState = !buttonState;

  lastButtonState = reading;
}

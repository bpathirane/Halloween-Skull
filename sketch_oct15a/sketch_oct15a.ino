
const int DELAY = 60;
const int LED_PIN = 9;
const int MOTION_DETECTOR_PIN = 2;
const int FULL_BRIGHTNESS = 255;

int brightness = 0;

unsigned long activatedDuration = 10 * 1000;
unsigned long maxActivatedDuration = activatedDuration * 3;
unsigned long activationBreakTime = 5 * 1000;

int fadingDuration = activatedDuration / 5;

bool isActivated = false;
unsigned long activationStartTime = 0;
unsigned long activationEndTime = 0;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 30;  // the debounce time; increase if the output flickers

int lastMotionReadingState = LOW;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(MOTION_DETECTOR_PIN, INPUT);

  analogWrite(LED_PIN, LOW);
}

void loop() {
  unsigned long now = millis();

  // If time has passed the end time, and we are still activated
  // deactivate now
  if ((millis() > activationEndTime) && isActivated) {
    isActivated = false;
    brightness = 0;
    Serial.println("Deactivating...");
  }

  int reading = digitalRead(MOTION_DETECTOR_PIN);

  if (reading == HIGH) {
    if (!isActivated && lastMotionReadingState != reading) {
      lastDebounceTime = millis();
      lastMotionReadingState = reading;
    }
    // If motion is detected, and we are not currently active,
    // and the required break time since last activation has passed
    // then activate!
    if (!isActivated 
        && (millis() > (activationEndTime + activationBreakTime))
        && ((millis() - lastDebounceTime) > debounceDelay)) 
        {
      // First time activating
      Serial.println("Activating...");
      isActivated = true;
      activationStartTime = millis();
    }
    if (isActivated) {
      // We are in activated mode, yet we keep detecting more motion
      // Extend the activation time, for each motion detection
      activationEndTime = millis() + activatedDuration;
      // Yet, ensure that activation endtime does not pass the maximum
      activationEndTime = activationEndTime > activationStartTime + maxActivatedDuration ? activationStartTime + maxActivatedDuration : activationEndTime;
    }
  }
  lastMotionReadingState = reading;

  if (isActivated) {
    unsigned long activatedTime = now - activationStartTime;
    unsigned long timeToFinish = activationEndTime - millis();

    // We just activated, fade in!
    if (activatedTime < fadingDuration) {
      // Slowly increase brightness
      brightness = (activatedTime / (float)fadingDuration) * FULL_BRIGHTNESS;
    } else if (timeToFinish < fadingDuration) {  // We are deactivating, fade out!
      // Slowly decrease brightness
      brightness = (timeToFinish / (float)fadingDuration) * FULL_BRIGHTNESS;
    } else {
      // Keep brightness constant
      brightness = FULL_BRIGHTNESS;
    }
  }

  analogWrite(LED_PIN, brightness);
}


const int DELAY = 60;
const int LED_PIN = 9;
const int MOTION_DETECTOR_PIN = 2;

int brightness = 0;

unsigned long activatedDuration = 10 * 1000;
unsigned long maxActivatedDuration = activatedDuration * 5;

int fadingDuration = activatedDuration / 5;

bool isActivated = false;
unsigned long activationStartTime = 0;
unsigned long activationEndTime = 0;


void setup() {
 Serial.begin(9600);
  // put your setup code here, to run once:
 pinMode(LED_PIN, OUTPUT);
 pinMode(MOTION_DETECTOR_PIN, INPUT);

 analogWrite(LED_PIN, LOW);
}

void loop() {
  unsigned long now = millis();

  if (millis() > activationEndTime){
    isActivated = false;
    brightness = 0;
  }

  int reading = digitalRead(MOTION_DETECTOR_PIN);
  if (reading == HIGH) {
    if (!isActivated) {
      // First time activating
      isActivated = true;
      activationStartTime = millis();
    }
    // Extend the activation time, for each motion detection
    // TODO: Add a max activation time to prevent 
    // running for too long.
    activationEndTime = millis() + activatedDuration;
  }

  if (isActivated) {
  unsigned long activatedTime = now - activationStartTime;
  unsigned long timeToFinish = activationEndTime - millis();
    // Within the activation period
    if (activatedTime < fadingDuration) {
      // Slowly increase brightness
      brightness = (activatedTime / (float)fadingDuration) * 255;
    }
    else if (timeToFinish < fadingDuration) {
      // Slowly decrease brightness
      brightness = (timeToFinish/(float)fadingDuration) * 255;
    }
    else {
      // Keep brightness constant
      brightness = 255;
    }
  }

  analogWrite(LED_PIN, brightness);
}

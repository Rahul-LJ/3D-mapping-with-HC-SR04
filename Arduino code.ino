const int TRIG_PIN = 4;
const int ECHO_PIN = 2;

// Grid Parameters
const float SCAN_WIDTH_CM = 30.0;
const float Y_STEP_CM = 2.0;
const int TOTAL_ROWS = 4;
const unsigned long SWEEP_TIME_MS = 10000; // 10 seconds per sweep
const unsigned long SAMPLE_RATE_MS = 100;  // 10Hz reading rate

int currentRow = 0;
bool isScanning = false;
unsigned long rowStartTime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.println("--- 3D MANUAL LAWNMOWER SCANNER ---");
  Serial.println("Position sensor at the START (X=0, Y=0).");
  Serial.println("Starting in 5 seconds...");
  delay(5000);
}

void loop() {
  if (currentRow < TOTAL_ROWS) {
    if (!isScanning) {
      // Print instructions for the current row
      Serial.print("START ROW ");
      Serial.print(currentRow);
      
      if (currentRow % 2 == 0) {
        Serial.println(" ---> SWEEP LEFT TO RIGHT (0 to 30cm)!");
      } else {
        Serial.println(" <--- SWEEP RIGHT TO LEFT (30 to 0cm)!");
      }
      
      isScanning = true;
      rowStartTime = millis();
      
    } else {
      // Actively scanning the row
      unsigned long elapsedTime = millis() - rowStartTime;

      if (elapsedTime <= SWEEP_TIME_MS) {
        float currentY = currentRow * Y_STEP_CM;
        float currentX = 0.0;

        // Calculate X based on the direction of the sweep
        if (currentRow % 2 == 0) {
          // Even rows (0, 2): Hand moves Left to Right (0 to 30)
          currentX = ((float)elapsedTime / SWEEP_TIME_MS) * SCAN_WIDTH_CM;
        } else {
          // Odd rows (1, 3): Hand moves Right to Left (30 to 0)
          currentX = SCAN_WIDTH_CM - (((float)elapsedTime / SWEEP_TIME_MS) * SCAN_WIDTH_CM);
        }

        float distanceZ = readDistance();

        // Print data as: X, Y, Z
        Serial.print(currentX); Serial.print(",");
        Serial.print(currentY); Serial.print(",");
        Serial.println(distanceZ);

        delay(SAMPLE_RATE_MS); 
        
      } else {
        // The 10-second sweep is finished
        isScanning = false;
        currentRow++;

        if (currentRow < TOTAL_ROWS) {
           Serial.println("ROW COMPLETE! STOP MOVING.");
           Serial.println("SHIFT SENSOR FORWARD 2cm (Y-axis).");
           Serial.println("Next row starts in 5 seconds...");
           delay(1000); Serial.println("4..."); delay(1000);
           Serial.println("3..."); delay(1000);
           Serial.println("2..."); delay(1000);
           Serial.println("1..."); delay(1000);
        } else {
           Serial.println("--- ALL 4 ROWS COMPLETE! ---");
           Serial.println("Copy your data to generate the 3D Map.");
        }
      }
    }
  }
}

// Distance sensing function
float readDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long dur = pulseIn(ECHO_PIN, HIGH, 30000); 
  if (dur == 0) return -1.0; 
  return dur * 0.034 / 2.0;
}

const uint8_t SENSE_PIN = A0;
const uint8_t STATUS_LED = LED_BUILTIN;

const int ADC_MAX = 1023;
const int FAULT_THRESHOLD = 300;
const float MAX_DISTANCE_KM = 5.0f;

float estimateDistanceKm(int adc)
{
    if (adc <= 0) return 0.0f;
    if (adc >= ADC_MAX) return MAX_DISTANCE_KM;
    return (adc / (float)ADC_MAX) * MAX_DISTANCE_KM;
}

void setup()
{
    pinMode(STATUS_LED, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    const int adc = analogRead(SENSE_PIN);
    const bool fault = adc < FAULT_THRESHOLD;

    digitalWrite(STATUS_LED, fault ? HIGH : LOW);

    Serial.print("ADC=");
    Serial.print(adc);
    Serial.print(" STATUS=");
    Serial.print(fault ? "FAULT" : "NORMAL");

    if (fault)
    {
        Serial.print(" EST_DISTANCE_KM=");
        Serial.print(estimateDistanceKm(adc), 2);
    }

    Serial.println();
    delay(500);
}

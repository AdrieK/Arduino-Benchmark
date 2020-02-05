#define ITER 200000L
#define SCORE_DIVIDER 99999999L
#define MALLOC_SIZE 256

// Scores of some known boards
#define UNO_SCORE 983L // original was 563L?
#define LEONARDO_SCORE 978L
#define NANO_33_IOT_SCORE 3162L
#define ESP32_SCORE 40783L
#define ESP32_MULTICORE_SCORE 62695L
#define MICRO_SCORE 559L // needs verification
#define DUE_SCORE 3301L  // needs verification

#ifdef ESP32
#define ESP32_USE_MULTICORE // comment out or uncomment for single/multi core
#endif

void setup() {
  Serial.begin(115200);
  while (!Serial) {};
  Serial.println(F("Quick & Dirty Benchmark for Arduino & Friends"));
  delay(1000);

  void *v; // placeholder needed for xTaskCreate calls

  long StartTime = millis();

#ifdef ESP32_USE_MULTICORE
  int initialRunningTasks = uxTaskGetNumberOfTasks();

  //Taskhandles
  TaskHandle_t thFloat;
  TaskHandle_t thPI;
  TaskHandle_t thPolar;
  TaskHandle_t thMemory;
  TaskHandle_t thInteger;

  xTaskCreate(taskFloat, "Float", 1023, NULL, 1, &thFloat);
  xTaskCreate(taskPI, "PI", 1023, NULL, 1, &thPI);
  xTaskCreate(taskPolar, "Polar", 1023, NULL, 1, &thPolar);
  xTaskCreate(taskMemory, "Memory", 1023, NULL, 1, &thMemory);
  xTaskCreate(taskInteger, "Integer", 1023, NULL, 1, &thInteger);

  // wait till all tests are finished
  while (uxTaskGetNumberOfTasks() > initialRunningTasks) {
    delay(1); // sometimes the program freezes without this delay
  }
#else
  // Not multicore, sequentially execute all tests
  taskInteger(v);
  taskFloat(v);
  taskPI(v);
  taskPolar(v);
  taskMemory(v);
#endif

  //summary and total
  long score = millis() - StartTime;
  score = SCORE_DIVIDER / score;
  Serial.print(F("Your CPU's score is: "));
  Serial.println(score);
  Serial.print(F("Which relates to Arduino Uno as: "));
  Serial.println(float(score) / UNO_SCORE);
}

void taskFloat(void* pvParamaters) {
  Serial.print(F("float performance using random\n"));
  long increment = 0;
  float f = 0.0f;
  long Millis = millis();
  for (; increment < ITER; increment++) {
    f = random(0.0f, (float)increment);
  }
  Serial.print(F("float performance using random time: "));
  Serial.print(millis() - Millis);
  Serial.print(F(" ms, float result: "));
  Serial.println(f);
#ifdef ESP32_USE_MULTICORE
  vTaskDelete(NULL);
#endif
}

void taskPI(void* pvParamaters) {
  Serial.print(F("calculating PI using Newtonian method\n"));
  float pi = 0.0f;
  float multiplier = 1.0f;
  long Millis2 = millis();
  for (float incrementf = 0.0f, increment = 0; increment < ITER; incrementf += 1.0f, increment++) {
    pi += 4.0f / (incrementf * 2.0f + 1.0f) * multiplier;
    multiplier *= -1.0f;
  }
  Serial.print(F("calculating PI using Newtonian method time: "));
  Serial.print(millis() - Millis2);
  Serial.print(F(" ms, PI estimate: "));
  Serial.println(pi, 8);

#ifdef ESP32_USE_MULTICORE
  vTaskDelete(NULL);
#endif
}

void taskPolar(void* pvParamaters) {
  Serial.print(F("polar to rectangular coordinate conversion\n"));
  float X = 0.0f;
  float Y = 0.0f;
  float f = 0.0f;
  long Millis3 = millis();
  for (long i = 0L; i < ITER / 3; i++, f += PI / 1000.0f) {
    X = cos(f) * ((float)i) / 1000.0f;
    Y = sin(f) * ((float)i) / 1000.0f;
  }
  Serial.print(F("polar to rectangular coordinate converting time: "));
  Serial.print(millis() - Millis3);
  Serial.print(F(" ms, X: "));
  Serial.print(X, 8);
  Serial.print(F(", Y: "));
  Serial.println(Y, 8);
  
#ifdef ESP32_USE_MULTICORE
  vTaskDelete(NULL);
#endif
}

void taskMemory(void* pvParamaters) {
  Serial.print(F("memory write speed using malloc and freeing pointers\n"));
  long Millis4 = millis();
  for (long i = 0; i < ITER / 4; i++) {
    char *j = (char*)malloc(MALLOC_SIZE);
    char *f = j;
    for (int i = 0; i < MALLOC_SIZE; i++) {
      *f = 'n';//just some random value to initialize the whole array of chars with
      f++;
    }
    free(j);
  }
  Serial.print(F("memory write speed using malloc and freeing pointers time: "));
  Serial.print(millis() - Millis4);
  Serial.print(F(" ms, malloc size is: "));
  Serial.println(MALLOC_SIZE);

#ifdef ESP32_USE_MULTICORE
  vTaskDelete(NULL);
#endif
}

void taskInteger(void* pvParamaters) {
  Serial.print(F("integer benchmark\n"));
  long Millis5 = millis();
  long INTEGER_BENCHMARK = random(0L, 2323213);
  for (long i = 0; i < ITER; i++) {
    INTEGER_BENCHMARK *= 10000;
    INTEGER_BENCHMARK /= 5;
    INTEGER_BENCHMARK += 7;
    for (long j = 0; j < 5; j++) {
      INTEGER_BENCHMARK *= 3;
      INTEGER_BENCHMARK /= 4;
    }
  }
  Serial.print(F("integer benchmark time: "));
  Serial.print(millis() - Millis5);
  Serial.print(F(" ms, integer value: "));
  Serial.println(INTEGER_BENCHMARK);
#ifdef ESP32_USE_MULTICORE
  vTaskDelete(NULL);
#endif
}

void loop() {
}

#define ITER 200000L
#define SCORE_DIVIDER 99999999L
#define UNO_SCORE 563L
#define MICRO_SCORE 559L
#define DUE_SCORE 3301L
#define MALLOC_SIZE 256
void setup() {
	Serial.begin(57600);
        long StartTime=millis();
	long Millis=millis();
	long increment = 0;
	float f = 0.0f;
	Serial.println("checking float performance using random");
	for (; increment < ITER; increment++) {
		f = random(0.0f, (float)increment);
	}
	Serial.print("rand performance time taken: ");
	Serial.println(millis() - Millis);
	Millis = millis();
	Serial.println("now calculating PI using Newtonian method...");
	long Millis2 = millis();
	float pi = 0.0f;
	float multiplier = 1.0f;
	for (float incrementf = 0.0f, increment=0; increment < ITER; incrementf+=1.0f, increment++){
		pi += 4.0f / (incrementf*2.0f + 1.0f)*multiplier;
		multiplier *= -1.0f;
	}
	Serial.print("PI estimating time: ");
	Serial.print(millis() - Millis2);
	Millis2 = millis();
	Serial.print(" PI estimate: ");
	Serial.println(pi, 8);
	Serial.println("About to test polar to rectangular coordinate conversion: ");
	long Millis3 = millis();
	float X = 0.0f;
	float Y = 0.0f;
	f = 0.0f;
	for (long i = 0L; i < ITER/3; i++, f+=PI/1000.0f){
		X = cos(f)*((float)i)/1000.0f;
		Y = sin(f)*((float)i) / 1000.0f;
	}
	Serial.print("Polar to rect coords converting time: ");
	Serial.println(millis() - Millis3);
	Serial.print("X: ");
	Serial.println(X, 8);
	Serial.print("Y: ");
	Serial.println(Y, 8);
	Millis3 = millis();
	Serial.println("now testing mem write speed(mallocing and freeing pointers):");
	long Millis4;
	for (long i = 0; i < ITER/4; i++){
		char *j = (char*)malloc(MALLOC_SIZE);
		char *f = j;
		for (int i = 0; i < MALLOC_SIZE; i++){
			*f = 'n';//just some random value to initialize the whole array of chars with
			f++;
		}
		free(j);
	}
	Serial.print("Ram test finished in: ");
	Serial.print(millis() - Millis4);
	Serial.println(" milliseconds");
	Serial.print("malloc size is: ");
	Serial.println(MALLOC_SIZE);
	Millis4 = millis();
	long Millis5 = millis();
	long INTEGER_BENCHMARK=random(0L, 2323213);
	Serial.println("Integer benchmark starting... ");
	for (long i = 0; i < ITER; i++){
		INTEGER_BENCHMARK *= 10000;
		INTEGER_BENCHMARK /= 5;
		INTEGER_BENCHMARK += 7;
		for (long j = 0; j < 5; j++){
			INTEGER_BENCHMARK *= 3;
			INTEGER_BENCHMARK /= 4;
		}
	}
	Serial.print("Integer time: ");
	Serial.println(millis() - Millis5);
	Serial.print("Integer value: ");
	Serial.println(INTEGER_BENCHMARK);
	Millis5 = millis();
	long score = millis()-StartTime;
	score = SCORE_DIVIDER / score;
	Serial.println("Your arduino's score is: ");
	Serial.print(score);
}

void loop() {
}

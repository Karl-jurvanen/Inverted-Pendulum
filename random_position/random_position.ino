


int enablePin = 11;
int motor1 = 10;
int motor2 = 9;

int incomingByte = 0;   // for incoming serial data
//int speed = 0;
int count2 = 0;

int target = 0;

#define encoderI 2
#define encoderQ 3 // Only use one interrupt in this example

volatile int count;

void setup()
{
	Serial.begin(115200);     // opens serial port, sets data rate to 9600 bps

	pinMode(motor1, OUTPUT);
	pinMode(motor2, OUTPUT);
	pinMode(enablePin, OUTPUT);

	count = 0;
	pinMode(encoderI, INPUT); attachInterrupt(digitalPinToInterrupt(2), handleEncoder, CHANGE);
	pinMode(encoderQ, INPUT);


	// Finding home position by driving slowly to both end positions
	setMotor(0);
	Delay(800);
	setMotor(50);
	Delay(1000);
	count2 = count;
	count = 0;
	setMotor(-50);
	Delay(900);
	setMotor(0);
	count = 0;


}

void loop()
{

	target = random(400, 3300);
	driveTo(target);
	Delay(120);



}

void setMotor(int speed)
{

	// make sure  speed variable is within accepted margins

	if (speed == 0)
	{
		analogWrite(enablePin, speed);
		digitalWrite(motor1, HIGH);
		digitalWrite(motor2, LOW);


	}
	else if (speed > 0)
	{

		if (speed >= 255)
		{
			speed = 255;
		}
		speed = map(speed, 0, 255, 80, 255);
		analogWrite(enablePin, speed);
		digitalWrite(motor1, HIGH);
		digitalWrite(motor2, LOW);

	}
	else
	{


		if (speed <= -255)
		{
			speed = -255;
		}
		speed = map(speed, -255, -1, -255, -80);
		analogWrite(enablePin, -1 * speed);
		digitalWrite(motor1, LOW);
		digitalWrite(motor2, HIGH);

	}
}

void handleEncoder()
{

	//if( (PINB & _BV(PD2)) ==  (PINB & _BV(PD3)))
	if (digitalRead(encoderI) == digitalRead(encoderQ))

	{
		count++;
	}
	else
	{
		count--;
	}

}

void Delay(int interval)
{

	unsigned long startTime = millis();

	while (millis() - startTime <= interval)
	{
		// do nothing while waiting for time to pass
		Serial.println(count);
	}
	return;

}

void driveTo(int setpoint)
{
	float gain = 0.08;
	int error = 0;

	error = setpoint - count;

	while (error >= 20 || error <= -20)
	{

		error = setpoint - count;
		int control = gain * error;

		setMotor(control);
		Serial.print(count);
		Serial.print("  ");
		Serial.println(target);

	}

	setMotor(0);

}



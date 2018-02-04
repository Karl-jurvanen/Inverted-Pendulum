//Test program for linear carriage movement
//using measurement for feedback control


int enablePin = 11;
int motor1 = 10;
int motor2 = 9;

int incomingByte = 0;   // for incoming serial data
int count2 = 0;

int target = 1500;

#define encoderI 2
#define encoderQ 3 // Only use one interrupt in this example

volatile int count;

void setup()
{
	Serial.begin(115200);    
	pinMode(motor1, OUTPUT);
	pinMode(motor2, OUTPUT);
	pinMode(enablePin, OUTPUT);

	count = 0;
	pinMode(encoderI, INPUT); 
	pinMode(encoderQ, INPUT);
	attachInterrupt(digitalPinToInterrupt(2), handleEncoder, CHANGE);

	// Finding home position by driving slowly to both end positions
	setMotor(0);
	Delay(800);
	setMotor(50);
	Delay(1000);
	count2 = count;
	count = 0;
	setMotor(-50);
	Delay(1000);
	setMotor(0);
	count = 0;


}

void loop() 
{


	target = random(300, 3400);
	driveTo(target);
	Delay(100);


}

//The motor is driven using an H-bridge. Direction is chosen with values of motor1 and motor2 pins
//and motor speed is chosen with 0-255 value in enablePin. 
//Function converts a single integer value to suitable motor inputs. 
//Mapping is needed because the DC-motor does not turn at low voltages values (-80 < input < 80)
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

	//When the strip moves through the sensor, a pulse is generated to both 
	//encoder inputs. Comparing the inputs we can determine the direction of movement.
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

//Simple way of driving the carriage to a set position using feedback from position measurement
//Serial prints for testing
//This type of control overshoots
//TODO: implement proper P-control
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
		Serial.println(error);

	}

	setMotor(0);

}



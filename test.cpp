#include <iostream>		// Include all needed libraries here
#include <wiringPi.h>

using namespace std;		// No need to keep using “std”

void switchInterrupt(void);	// Function prototype

int main()
{
	wiringPiSetup();		// Setup the library
	pinMode(0, OUTPUT);		// Configure GPIO0 as an output
	pinMode(1, INPUT);		// Configure GPIO1 as an input

	// Cause an interrupt when switch is pressed (0V)
	wiringPiISR (1, INT_EDGE_FALLING, switchInterrupt) ;

	// Main program loop
	while(1)
	{
		// Toggle the LED
		digitalWrite(0, !digitalRead(0));
		delay(500);
	}

	return 0;
}
// Our interrupt routine
void switchInterrupt(void)
{
	cout << "Button pressed" << endl;
}
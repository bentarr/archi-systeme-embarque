#include <iostream>
#include <unistd.h>
#include "libs/i2cControl.hpp"
#include "libs/lcdDriver.hpp"
#include "libs/MFRC522.h"
#include "libs/wiringPi/wiringPi.h"

#define RED 7
#define GREEN 0


void greenLedUp()
{
    digitalWrite(GREEN, HIGH);
}

void greenLedDown()
{
    digitalWrite(GREEN, LOW);
}

void redLedUp()
{
    digitalWrite(RED, HIGH);
}

void redLedDown()
{
    digitalWrite(RED, LOW);
}

void blinkGreenLed(int duration)
{
    cout << "Badge reconnu" << endl;
    redLedDown();
    for (int i = 0; i < duration; i++)
    {
        usleep(500000);
        greenLedUp();
        usleep(500000);
        greenLedDown();
    }
    redLedUp();
}

void blinkRedLed(int duration)
{
    cout << "Badge non reconnu" << endl;
    greenLedDown();
    for (int i = 0; i < duration; i++)
    {
        redLedDown();
        usleep(500000);
        redLedUp();
        usleep(500000);
    }
}

void blinkLedResult(bool checkResult)
{
    if (checkResult)
        blinkGreenLed(3);
    else
        blinkRedLed(3);
}

bool lectureBadge()
{
    MFRC522 mfrc;
    mfrc.PCD_Init();
    bool checkResult = true;
    int badgeConnu[20] = {150, 217, 162, 37, 200};

    while (1)
    {
        checkResult = true;
        if (!mfrc.PICC_IsNewCardPresent() || !mfrc.PICC_ReadCardSerial())
            continue;

        // On compare l'UID du badge passé devant le lecteur avec l'UID du badge connu
        for (int i = 0; i < mfrc.uid.size; ++i) {
            cout << badgeConnu[i] << " " << (int) mfrc.uid.uidByte[i] << endl;
            if (badgeConnu[i] != (int) mfrc.uid.uidByte[i])
            {
                checkResult = false;
                break;
            }
        }
        blinkLedResult(checkResult);
        usleep(1000000);
    }
}

int main(void)
{
    wiringPiSetup();
    pinMode(RED, OUTPUT);  // Red
    pinMode(GREEN, OUTPUT); // Green

    // Par défaut, on allume la led ROUGE
    digitalWrite(RED, HIGH);

    lectureBadge();

    return 0;
}

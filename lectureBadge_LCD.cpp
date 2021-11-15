#include <unistd.h>
#include <wiringPi.h>
#include <iostream>
#include "libs/MFRC522.h"
#include "libs/i2cControl.hpp"
#include "libs/lcdDriver.hpp"

#define RED 7
#define GREEN 0
#define lcdAddress 0x27

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

void printResultLCD(LcdDriver lcd, bool checkResult)
{
    lcd.clearColumnsRowCol(1, 16, 0);
    lcd.clearColumnsRowCol(2, 16, 0);
    if (checkResult) {
	lcd.lcdSendCommand(LCD_BEG_LINE_1);
	lcd.lcdString("Badge OK");
    } else {
	lcd.lcdSendCommand(LCD_BEG_LINE_1);
	lcd.lcdString("Badge KO");
    }
}

void waitingBadgeMessage(LcdDriver lcd)
{
    lcd.clearColumnsRowCol(1, 16, 0);
    lcd.clearColumnsRowCol(2, 16, 0);
    lcd.lcdSendCommand(LCD_BEG_LINE_1);
    lcd.lcdString("En attente d'un");
    lcd.lcdSendCommand(LCD_BEG_LINE_2);
    lcd.lcdString("badge...");
}

bool lectureBadge()
{
    I2cControl *i2c = new I2cControl(1);
    LcdDriver lcd(lcdAddress, i2c);
    MFRC522 mfrc;
    mfrc.PCD_Init();
    bool checkResult = true;
    int badgeConnu[20] = {150, 217, 162, 37, 200};
    waitingBadgeMessage(lcd);

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
	printResultLCD(lcd, checkResult);
        blinkLedResult(checkResult);
        usleep(1000000);
	waitingBadgeMessage(lcd);
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

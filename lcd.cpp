#include "libs/i2cControl.hpp"
#include "libs/lcdDriver.hpp"

#define lcdAddress 0x27

int main(void)
{
    I2cControl *i2c = new I2cControl(1);
    LcdDriver lcd(lcdAddress, i2c);

    lcd.lcdSendCommand(LCD_BEG_LINE_1);
    lcd.lcdString("Plop");

    lcd.lcdSendCommand(LCD_BEG_LINE_2);
    lcd.lcdString("FuckYou");

    delete i2c;

    return 0;
}
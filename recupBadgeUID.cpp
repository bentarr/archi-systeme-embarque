#include <unistd.h>
#include "MFRC522.h"

int main()
{
    MFRC522 mfrc;
    mfrc.PCD_Init();

    while (1)
    {
        // Si aucun badge n'est détecté, on passe le reste
        // du while et on retourne à son départ
        if (!mfrc.PICC_IsNewCardPresent() || !mfrc.PICC_ReadCardSerial())
            continue;

        // Affichage de l'UID dans la console
        for (byte i = 0; i < mfrc.uid.size; ++i)
        {
            if (mfrc.uid.uidByte[i] < 0x10)
            {
                printf(" 0");
                printf("%X", mfrc.uid.uidByte[i]);
            }
            else
            {
                printf(" ");
                printf("%X", mfrc.uid.uidByte[i]);
            }
        }
        printf("\n");
        usleep(1000000);
    }
    return 0;
}

Pour compiler le code :

```
g++ libs/MFRC522.cpp <le nom du fichier> -std=c++11 -lbcm2835 -lwiringPi (-o <nom de fichier de sortie)
```

Pour compiler un code pour afficher des messages sur l'écran LCD :

```
g++ libs/lcdDriver.cpp libs/i2cControl.cpp <nom du fichier> (-o <nom du fichier de sortie>)
```

Pour compiler le tout :

```
g++ libs/MFRC522.cpp libs/lcdDriver.cpp libs/i2cControl.cpp <nom fichier> -std=c++11 -lbcm2835 -lwiringPi (-o <nom fichier de sortie>)
```

Pour exécuter le fichier compilé :
```
sudo ./a.out OU sudo ./<nom de fichier de sortie>
```

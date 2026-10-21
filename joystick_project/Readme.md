C joystick controller

prosty program do czytania wejsc od Logitech extreme 3d pro na raspberry pi
projekt uzywa linux joystick api (/dev/input/js0) zeby czytac osie joysticka

Cechy:
Odczytuje osie:
-X
-Y
-OBROT
-PRZYSPIESZENIE
Odczytuje wejscia z /dev/input/js0
Uzywa structa js_event
Pokazuje dane osie na terminalu 

Mapowanie osi
Numer osi	Funkcja
0		x
1		y
2		obrot
3		przyspieszenie

W jakim zakresie pracuja osie

-32767 - 0 - 32767

Wymagania 
-Raspberry Pi OS
-USB port
-Logitech extreme 3d pro
-GCC
Joystick powinien pokazac sie jako - /dev/input/js0

Kompilowanie 
kompilowac program mozna zapomoca wpisania make albo gcc joystick.c -o joystick

zeby wyczyscic skompilowanie pliki wystarczy
make clean

Czego sie ucze
-struktur
-wskaznikow
-operacji bitowych
-linux
-open()
-read()
-switch

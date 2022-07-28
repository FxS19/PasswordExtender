# PasswordExtender
USB-Gerät, das auf Knopfdruck Passwörter eingibt.
Zur sicherheit sollte immer ein eigenes Passwort vorher in das Passwortfeld eingegeben werden, welches der Stick um sein Passwort erweitert. Der Stick kann somit als Enter-Taste für Passwörter verwendet werden.

# Funktionsweise:

1. Gerät in USB einstecken
2. Gewünschtes Passwort auswählen, hierzu den knopf die gewümschte Anzahl oft drücken (<200 ms).
3. Passwoer eingeben. Hierzu den Knopf mindestens 500 ms drücken.  
   Der Stick gibt daruf hin als Tastatur das Passwort ein, betätigt die Enter-Taste und löscht das Passwort wieder.

Der Stick generiert intern bis zu 255 individuelle Passwörter, die der Stick in ein Gerät eingeben kann. Hierbei ändern sich die Passwörter nicht. Wird der selbe Passwort Slot gewählt, gibt der Stick immer das selbe Passwort aus.

# Features:

1. Passwörter werden asutomatisch eingegeben
2. Falls ein Passwort in ein falsches Feld oder Editor eingegeben wurde, wird es automatisch aus gelöscht.
3. Der Stick kann zurückgesetzt werden. anschließend sind die Slots durch neue Passwörter  belegt.
4. Es werden keine Passwörter im Speicher des Sticks gespeichert, sondern im RAM berechnet
5. Jedes Passwort hat 20 Zeichen
5. Jedes Passwort kann aus folgenden Zeichen bestehen:
   1. Großbuchstaben
   2. Kleinbuchstaben
   3. Zahlen
   4. Sonderzeichen

# Zurücksetzen
1. Den Stick einstecken, so dass dieser Rot leuchtet.
2. Die Taste des Sticks mindestens 30sek durchgängig drücken.
3. Der Stick beginnt einige Sekunden Rot zu blinken. In dieser Zeit kann der Stick noch herauzsgezogen werden und die alten Passwörter bleigen erhalten.
4. Sobald der Stick auhört zu blinken sind die alten Passwörter durch neue ersetzt.

# Hardware
Digispark, basierend auf Attiny85

Modifizierter Bootloader, der ein neu programmieren verhindert, solange beim einschalten P0 nicht auf GND gebrückt ist. Somit muss der Stick gewaltsam geöffnet werden, bevor er umprogrammiert werden kann. Der ROM des ATTiny ist nicht gesperrt, was durch setzen der passenden fuses / lock-bits erreicht werden kann. Falls dies gewünscht ist einfach die passenden parameter dem Uploader mitgeben :), ist aber auch nicht zu 100% sicher.

# Achtung: 

* Der Modifizierte Bootloader verhindert nicht ein Auslesen des ATiny selbst. Hat eine Person physikalischen Zugriff auf den Chip, so kann sie den internen Schlüssel auslesen und damit den Stick replizieren.
* Der modifizierte Bootloader dient zum Schutz, dass kein fremder Code in kürzester Zeit von einer dritten Person aufgespielt werden kann.
* Jeder der Zugriff auf den Stick hat, kann in der Theorie mit etwas Gewalt oder durch das einstechen des sticks in einen Rechner die Passwörter auslesen oder bei der gewaltsammen Methode an das Secret kommen. (hievor schützen auch keine lockbits)

# Selber bauen

1. Arduino-Boardverwalter URL eingeben:  
   https://raw.githubusercontent.com/rsrdesarrollo/DigistumpArduino/master/package_digistump_index.json  
   (Fork von Digistump, mit verschiedenen Tastaturlayouts)
2. USB einstecken
3. Micronucleus herunterladen:  
   https://github.com/micronucleus/micronucleus/releases  
   Hiermit die Firmware des digispark updaten  
   $ micronucleus P0GNDfirmware.hex  
   Warten bis fertig
4. P0 und GND temporär brücken
5. Software mit Arduino aufspielen
6. Taster zwischen GND und P2 einlöten
7. Temporäre Brücke zwischen P0 und GND entfernen.

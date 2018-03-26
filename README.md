# Termostato-Wireless

Inizio progetto. Fase primoridale

Temporanea formula per upload su Arduino Nano:
avrdude -CC:\Program Files (x86)\Arduino\hardware\tools\avr/etc/avrdude.conf -v -patmega328p -carduino -PCOM4 -b57600 -D -Uflash:w:C:\Users\franc\Documents\GitHub\Termostato-Wireless\Atmega328P\Debug\Atmega328P.hex:i

#Wireless Part
          Wireless Network Criptato, Unico, Anti-Maninthemiddle
Elemento distintivo è la codifica per ogni trasmissione via aria
Attacca man in the middle impossibile utilizzando Token Privati, Pubblici, e temporanei (ricavabili tramite formula)
Comunicazione P2P, o in PoverP (network)

P2P = Il messaggio viene scambiato tra due Device
Inizio comunicazione -> Viene mandato un messaggio non criptato in aria con informazioni pubbliche
La risposta significa che la connessione è plausibile e calcola anche la velocità più sicura di trasferimento dati (opzionale)
Non importa verificare la veridicità della risposta, anche non fosse verificato il device non passerebbe le fasi successive
Scambio chiave pubblica (Perchè? Una persona potrebbe benissimo ascoltare la comunicazione wireless, ma intanto permette
                        una prima schermatura e soprattuto permette la unicità del messaggio (non è l'unico sistema per farlo)
                        soprattuto se una persona non ascolta il messaggio fin dall'inizio non potrebbe effettuare alcun attacco MIM)
Anti DDOS ->

Mittete               Ricevitore
Chiave Pubblica       Chiave pubblica
Token                 Token


Device compatibili
-nRF24l01+
#Wireless Part

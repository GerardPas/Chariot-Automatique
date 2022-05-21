/*
 * Communication avec le robot par un module bluetooth BT-06
 * Le robot reçoit 3 octets
 * octet1 : mode
 * octet2 : vitesse
 * octet3 : écart
 * Connexion Rx et Tx sur les broches 0 et 1
 */

#include "Arduino.h"
#include "MotorsIboum17.h"

MotorsIboum17 bot;      // Objet qui permet de commander les mouvements du robot
byte receivedData[2];   // Tableau de 3 octets
byte commande, vitesse;




void setup()
{
// Add your initialization code here
	Serial.begin(9600);  // Lancement de la communication série à 9600 bits par seconde
 Serial.println("Robot CaPs");
}

// The loop function is called in an endless loop
void loop()
{
//Add your repeated code here
	// Si des données arrivent sur le port série
	if(Serial.available()) {
		Serial.readBytes(receivedData,2);  // Lire 2 octets et les enregistrer dans un tableau
    commande = receivedData[0];
    vitesse = receivedData[1];
    Serial.print("Commande recu ");   // Echo pour debug
    Serial.println(commande);
    Serial.print("Vitesse : ");
    Serial.println(vitesse);
	}
	// La case 0 du tableau receivedData contient un caractère qui coorespond à une commande
	// Exécuter un cas selon le caractère reçu

  
	switch (commande) {

	case 'F':              	// Si le caractère reçu est un F 
		bot.forward(200);	// Faire avancer le robot
		break;				// Instruction qui permet de sortir de la structure de décision switch. A ne pas oublier 
	case 'L':
		bot.rotateLeft(100);
		break;
	case 'R':
		bot.rotateRight(100);
		break;
	case 'G':
		bot.turnLeft(50,50);
		break;
   case 'D':
    bot.turnRight(50,50);
    break;
	default :				// Si le caractère reçu ne correspond à aucun des cas précédent (cas par défaut)
		bot.forward(0);		// arrêter le robot

		break;
	}
	Serial.flush();			// Vider le buffer du port série
	commande = 'S';  // Initialiser la commande à 'S'
	delay(100);

}

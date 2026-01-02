#ifndef INC_AEORDERSTAT
#define INC_AEORDERSTAT

/****************************************************************/
/*	   Defines zur Selektion bestimmter Auftragsstati			*/
/****************************************************************/

#define AEORD_ALLESTATIS			"%"
#define AEORD_ZURUECKGESTELLT		"00010000000__%"
#define AEORD_ZURUECKGEST_DAFUE		"00010000000_1%"	
#define AEORD_ZURUECKGEST_PHON		"00010000000_0%"	
#define AEORD_ERFASST           	"0000100000%"
#define AEORD_STORNIERT         	"_________1%"
#define AEORD_KOMMI_ENDE        	"00001_1000%"
#define AEORD_FAKTUR_ENDE       	"00001___10%"
#define AEORD_IN_KOMMI          	"0000110000%"
#define AEORD_BEREIT_ZUR_FAKTUR 	"00001__100%"
#define AEORD_IN_ERFASSUNG      	"01%"
#define AEORD_IN_AENDERUNG      	"001%"

#define AEORD_POS_ZURUECKGESTELLT		3
#define AEORD_POS_ZURUECKGEST_DAFUE		12	
#define AEORD_POS_ERFASST           	4
#define AEORD_POS_STORNIERT         	9
#define AEORD_POS_KOMMI_ENDE        	6
#define AEORD_POS_FAKTUR_ENDE       	8
#define AEORD_POS_IN_KOMMI          	5
#define AEORD_POS_BEREIT_ZUR_FAKTUR 	7
#define AEORD_POS_IN_ERFASSUNG			1	
#define AEORD_POS_IN_AENDERUNG			2	
#define AEORD_POS_PARA_AUFTRAG			14	
#define AEORD_POS_IN_TRANSMIT       	10
#define AEORD_POS_TRANSMITTED	       	11


#endif

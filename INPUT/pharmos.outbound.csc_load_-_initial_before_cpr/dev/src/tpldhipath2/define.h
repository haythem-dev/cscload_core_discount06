#ifndef __DEFINE_H_
#define __DEFINE_H_ __DEFINE_H_

// BB
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PROJECT KD2ORDER
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define		MAX_TRANSAKTION			300

/*****************************************************************************************************/
// Space Character
/*****************************************************************************************************/
#define	TXT_SPACE_CHAR								' '
#define	TXT_SPACE_STRING							" "
#define TXT_EMPTY_STRING							""
#define TXT_DOT_STRING								"."
#define TXT_DOT_CHAR								'.'
#define TXT_COMMA									','
#define TXT_COMMA_STRING							","
#define TXT_EXCLAMATION_MARK						'!'
#define TXT_EXCLAMATION_MARK_STRING					"!"
#define TXT_COLON									':'
#define TXT_COLON_STRING							":"
#define TXT_SLASH									'/'
#define TXT_SLASH_STRING 							"/"
#define TXT_EQUALS_SIGN_CHAR						'='
#define TXT_SEMICOLON								';' 
#define TXT_QUESTIONMARK_STRING						"?"
#define TXT_LEFT_PARENTHESIS						"("
#define TXT_RIGHT_PARENTHESIS						")"

/*****************************************************************************************************/
// rekliefer_upd-specific 
/*****************************************************************************************************/
#define TXT_FIRMA									"Firma"
#define TXT_HERR									"Herr"
#define TXT_FRAU									"Frau"

#define	UNTERENTFELDEN								12
#define	CHAVANNE									13
#define	FEHRALTDORF									14
#define	AMEDIS_SERVICE								15
#define	WIEN										61
#define	GRAZ										62
#define	LINZ										63
#define	TIROL										64
#define	ZLAUSTRIA									69

#define	VORWAHL_NIEDERLANDE							"0031"
#define	VORWAHL_BELGIEN								"0032"
#define	VORWAHL_DEUTSCHLAND							"0049"
#define	VORWAHL_FRANKREICH							"0033"
#define	VORWAHL_IRLAND								"00353"
#define	VORWAHL_LIECHTENSTEIN						"00423"
#define	VORWAHL_OESTERREICH							"0043"
#define	VORWAHL_SCHWEIZ								"0041"
	
#define	LKZ_BELGIEN									"B"
#define	LKZ_DEUTSCHLAND								"D"
#define	LKZ_FRANKREICH								"F"
#define	LKZ_IRLAND									"IRL"
#define	LKZ_LIECHTENSTEIN							"FL"
#define	LKZ_OESTERREICH								"A"
#define	LKZ_SCHWEIZ									"CH"


#define TXT_LIEFERANT_OHNE_VW						"Fuer LiefNr<%ld> mit FaxNr<%s> konnte die land.-spez. VW nicht bestimmt werden!"
/*****************************************************************************************************/
// country-specific car identification code
/*****************************************************************************************************/
#define TXT_CAR_ID_CODE_GERMANY						"D"
#define TXT_CAR_ID_CODE_SWITZERLAND					"CH"
#define TXT_CAR_ID_CODE_AUSTRIA						"A"

/*****************************************************************************************************/
// country-specific prefix of the FaxNo
/*****************************************************************************************************/
#define TXT_COUNTRY_SPECIFIC_PREFIX_A				"0043"
#define TXT_COUNTRY_SPECIFIC_PREFIX_CH				"0041"

/*****************************************************************************************************/
// CmdLine 
/*****************************************************************************************************/
#define TXT_CL_PARA_DBPLUSDBSRV						"-dbplusdbsrv"
#define TXT_CL_PARA_DC								"-dc"
#define TXT_FILE_AND_PATH							"-fileAndPath"
#define TXT_USAGE									"Usage"

/*****************************************************************************************************/
// Formatting Token
/*****************************************************************************************************/
#define TXT_PROZENT_S								"%s"
#define TXT_PROZENT_LD								"%ld"

/*****************************************************************************************************/
// Environment (ENV)
/*****************************************************************************************************/
#define TXT_ENVIRON_VARIABLE						"Environment variable "TXT_PROZENT_S" was not set!"
#define TXT_WWS										"WWS"
#define TXT_LOG_PATH								"LOG_PATH"
#define TXT_DFT_LOG_FILE							"DFT_LOG_FILE"
#define TXT_ORDER_FILE_DEST							"ORDER_FILE_DEST"
#define TXT_NUMBER_TRANSACTIONS						"NUMBER_TRANSACTIONS"

#define	TXT_TAB_HERSTEL_LOAD						"TAB_HERSTEL_LOAD"
#define TXT_TAB_LIEFER_LOAD							"TAB_LIEFER_LOAD"
#define TXT_TAB_BLIEFER_LOAD						"TAB_BLIEFER_LOAD"
#define TXT_TAB_FLIEFER_LOAD						"TAB_FLIEFER_LOAD"

#define TXT_LIEFER_TEL_LOAD							"LIEFER_TEL_LOAD"
#define TXT_BLIEFER_TEL_LOAD						"BLIEFER_TEL_LOAD"

#define TXT_TAB_HERLIEF_LOAD						"TAB_HERLIEF_LOAD"

#define TXT_ON										"ON"

/*****************************************************************************************************/
// relevant defines for logging
/*****************************************************************************************************/
#define TXT_LOG_FILE_EXT							"log"
#define TXT_START									"START"
#define TXT_STOP									"STOP"
#define TXT_STATUS									"Status"
#define TXT_KDDISPOS_SEL_UPD						"KdDispos sel/upd"
#define TXT_SUPP_ORDERS_SEL_UPD						"Supplier orders sel/upd"
#define TXT_NO_KDDISPOS_LOADED						"Keine KdDispos geladen"
#define TXT_NO_DATASETS_LOADED						"No datasets loaded"
#define TXT_FAX_FILE_COULDNT_BE_OPENED				"Fax-Datei: >%s< konnte nicht geöffnet werden!"
#define TXT_DATENSATZ_NICHT_GELADEN					"Datensatz nicht geladen"
#define TXT_DATENSATZ_GELADEN						"Datensatz geladen"
#define TXT_OBJ_WITH_NO_NOT_LOADED					"%s mit Nr.>%ld< nicht geladen!"
#define TXT_DATENSATZ_NICHT_AKTUALISIERT			"Datensatz nicht aktualisiert"
#define TXT_DATENSATZ_NICHT_GESPEICHERT				"Datensatz nicht gespeichert"
#define TXT_CRITERIA								"Kriterien"
#define TXT_PARAMETERKD								"Parameterkd"
#define TXT_ZWECK									"Zweck"	
#define TXT_PARANAME								"Parametername"
#define TXT_AUSPRAEG								"Auspraeg"
#define TXT_VAL_IND_BEG								"<"
#define TXT_VAL_IND_END								">"
#define TXT_KDDISPO									"KdDispo"
#define TXT_KDDISPONR								"KdDispoNr"
#define TXT_FILIALE									"Filiale"
#define TXT_FILNR									"FilNr"
#define TXT_KUNDE									"Kunde"
#define TXT_KDNR									"KdNr"
#define TXT_LIEFERANT								"Lieferant"
#define TXT_ARTIKEL									"Artikel"
#define TXT_NR										"Nr"
#define TXT_LIEFNR									"LiefNr"
#define TXT_FILNR									"FilNr"
#define TXT_ARTIKEL_NR								"ArtikelNr"
#define TXT_INVALID_FAXNO_FOR_OBJ_WITH_NO			"Ungueltige Fax-Nr.>%s< fuer %s mit Nr. >%ld<"
#define TXT_BESTELLUNG								"Bestellung"
#define TXT_BESTELL_NR								"BestellNr"
#define TXT_THE_SUPP_ORDERS_IS_NOT_GENERATED		"Die Bestellungen werden nicht generiert!"
#define TXT_ORDER_MODUS								"Bestell-Art"
#define TXT_CURRENT_STATUS							"Status-Akt"
#define TXT_TEXT_KZ									"Text-Kz"
#define TXT_BESDISP_ALREADY_EXISTS					"KdDispo(Nr.: >%ld<, FilNr.: >%d<) fuer "\
													"BestellPos(Nr.: >%ld<, FilNr.: >%d<, ArtNr.: >%ld<) " \
													"schon in Tab BESDISP vorhanden!"
#define TXT_SUPPORDHD								"Bestellkopf"
#define TXT_SUPPORDITEM								"Bestell-Pos"
#define TXT_KEIN_BESTELLWEG							"Kein Bestellweg feststellbar."

#define TXT_NO_TAB_SEL								"Number %s-Sel: >%ld<!"
#define TXT_NO_TAB_INS								"Number %s-Ins: >%ld<!"
#define TXT_NO_TAB_UPS								"Number %s-Ups: >%ld<!"
#define TXT_NO_TAB_DEL								"Number %s-Del: >%ld<!"
#define TXT_NO_TAB_SER								"Number %s-Serialized: >%ld<!"

#define TXT_LINE_NO									"Line-No"
/*****************************************************************************************************/
// Exceptions / Errors
/*****************************************************************************************************/
#define TXT_UNNAMED_EXCEPTION						"Unnamed Exception!"
#define TXT_NO_PARAMETER_USAGE						"No parameters: usage: %s -dbplusdbsrv <name of db and dbserver> "\
													"-country <country-specific car identification code>!"
#define TXT_INVAL_CMDLINE_PARA						"No valid cmdline parameter!"
#define TXT_TOO_MANY_OBJECTS						"Too Many Objects instantiated!"
#define TXT_UNNAMED_DB_SQLRC						"Unnamed DB-SQLRC!"
#define TXT_UNNAMED_BSN_RC							"Unnamed BSN-RC!"
#define TXT_NOT_IMPLEMENTED							"Not implemented!"
#define TXT_ABSENCE_OF_INIT							"Absence of necessary initialization!"
#define TXT_NO_MATCH								"No Match: "TXT_PROZENT_S
#define TXT_BSN_UNNAMED_STATUS						"Unnamed BSN-Status!"
#define TXT_LINE									"line"
#define TXT_FILE									"file"
#define TXT_NO_PARAMETRIZATION						"No parametrization data sets for printing!"
#define TXT_FILE_AND_LINE_STREAM					TXT_FILE << ": " << __FILE__ << ", " << TXT_LINE << ": " << __LINE__ << "."
#define TXT_NO_VALID_PERS_STATE						"No valid persistence state: "TXT_PROZENT_S"!"
#define TXT_THERE_WERE_NOTHING_TO_SAVE				"There were/is nothing to save!"
#define TXT_FILE_OPEN_ERROR							"Error: open File <%s> with RC:<%ld>!" 
#define TXT_FILE_CLOSE_ERROR						"Error: close File <%s> with RC:<%ld>!"


#define TXT_FETCH_CURSOR_ERROR						"Error: 'FECTH CURSOR'!"
#define TXT_OPEN_CURSOR_ERROR						"Error: 'OPEN CURSOR' using <%d>!"
#define TXT_DECLARE_CURSOR_ERROR					"Error: 'DECLARE CURSOR' for <%s>!"
#define TXT_PREPARE_SELECT_ERROR					"Error: 'PREPARE SELECT' for <%s>!"
#define TXT_PREPARE_UPDATE_ERROR					"Error: 'PREPARE PREUPD' for <%s>!"
#define TXT_PREPARE_INSERT_ERROR					"Error: 'PREPARE PREINS' for <%s>!"
#define TXT_EXECUTE_PREUPD							"Error: 'EXEC SQL EXECUTE preUpd' - SQLCODE:>%ld< for <%s>!"
#define TXT_EXECUTE_PREINS							"Error: 'EXEC SQL EXECUTE preIns' - SQLCODE:>%ld< for <%s>!"
#define TXT_STRUKTUR_VERSCHIEBUNG					"Error: Struktur-Verschiebung in Struct %s mit Wert: %s!"

/*****************************************************************************************************/
// error message defines
/*****************************************************************************************************/
#define TXT_STRING_LEN_EXCEEDED						"Allowed string`s length exceeded!"
#define TXT_BRANCHNO_TOO_LARGE						"Branch no. is too large!"
#define TXT_UNKNOWN_SORT_CRIT						"Unbekannt Sortier-Kriterien!"

/*****************************************************************************************************/
// Database
// delimiter of db name and db server
/*****************************************************************************************************/
#define TXT_DELIMITER_DB_DBSRV						'@'
#define TXT_DB_OPEN_ERROR							"Database <%s> open error:"
#define TXT_SQLCODE									"SQLCODE<%ld>"
#define TXT_ISAMCODE								"ISAMCODE<%ld>"

/*****************************************************************************************************/
// number of the greatest branch (pseudo branch)
/*****************************************************************************************************/
#define NUM_GREATEST_BRANCH							99

/*****************************************************************************************************/
//  
/*****************************************************************************************************/
#define TXT_KD_BEST_KZ_J							'J'
#define TXT_KD_BEST_KZ_N							'N'

/*****************************************************************************************************/
// Text defines used for customer fax printing
/*****************************************************************************************************/
#define TXT_HD_DEC									"* * *"
#define TXT_NEW_LINE								"\n"
#define TXT_FORM_FEED								"\f"
#define TXT_LINE_ELEM								'-'
#define TXT_LINE_ELEM_STRING						"-"

#endif /* __DEFINE_H_ */

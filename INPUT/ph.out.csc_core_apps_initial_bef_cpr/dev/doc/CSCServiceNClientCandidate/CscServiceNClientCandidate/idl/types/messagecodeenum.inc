#ifndef GUARD_MESSAGECODE_ENUM_H
#define GUARD_MESSAGECODE_ENUM_H

/******************************************************************/
/* This file is used in both cpp code (pxverbund) and as part of  */
/* the Thrift IDL.                                                */
/******************************************************************/

#if 0
namespace cpp csc.types
namespace csharp Csc.Types
#endif

/*----------------------------------------------------------------------------*/
/*  Enumeration for message codes.                                            */
/*----------------------------------------------------------------------------*/
enum MessageCodeEnum
{
	CMSG_OK 									= 0,

	CMSG_XMIT									= 20000,	// begin pxOrderTransmit canned message group here
	CMSG_XMIT_ORD_UPD_DENIED					= 20001,	// order update denied, no order open
	CMSG_XMIT_ITEM_REJECT						= 20002,	// Item insert denied, no order open
	CMSG_XMIT_INVALID_CUSTOMER					= 20003,	// Invalid incoming customer
	CMSG_XMIT_NO_CUSTOMER_AVAILABLE				= 20004,	// There is no Customer available
	CMSG_XMIT_SUBORDERTYPE_NOT_AVAILABLE		= 20005,	// SubOrderType must be available
	CMSG_XMIT_ORDERTYPE_NOT_NOT_ALLOWED			= 20006,	// OrderType not allowed
	CMSG_XMIT_MSV3_ORDERTYPE_NOT_ALLOWED		= 20007,	// OrderType not allowed for MSV3
	CMSG_XMIT_MSV3_DUPLICATE_TRANSMISSION		= 20008,	// MSV3 DOPPELTE UEBERTRAGUNG %s
	CMSG_XMIT_MSV3_DUPLICATE_ORDER				= 20009,	// MSV3 DOPPELTER AUFTRAG %s
	CMSG_XMIT_MSV3_ORDER_CANCELLED_LACK			= 20010,	// MSV3 AUFTRAG STORNIERT AUFGRUND DEFEKT
	CMSG_XMIT_MSV3_ORDERPERIOD_NOTFOUND			= 20011,	// MSV3 UNBEKANNTES BESTELLFENSTER %d 

	CMSG_XMIT_HIGH								= 20999,	// end of pxOrderTransmit group

//	CMSG_GEN									= 21000,	// begin generic server messages group here (OBSOLETE)
//	CMSG_GEN_LOCK								= 21001,	// fatal error %d during Lock() (OBSOLETE)
//	CMSG_GEN_UNLOCK								= 21002,	// fatal error %d during UnLock() (OBSOLETE)
//	CMSG_GEN_ISLOCKED							= 21003,	// fatal error %d during IsEqual() (OBSOLETE)
//	CMSG_GEN_HIGH								= 21999,	// end of generic server messages group (OBSOLETE)
	
	
	CMSG_ORDER									= 30000,	// begin pxOrder entry object group here
	CMSG_ORD_NOTFOUND,									// 30001 order %d not found
	CMSG_ORD_STILLOPEN,									// 30002 order %d already open
	CMSG_ORD_LOCKED,									// 30003 order %d locked by another instance
	CMSG_ORD_NOCUSTOMER,								// 30004 could not open order %d, no customer
	CMSG_ORD_NOTOPEN,									// 30005 order %d not open
	CMSG_ORD_TYPE_CUST,									// 30006 order type %s not allowed for customer %d
	CMSG_ORD_TYPE_COMB,									// 30007 invalid order type combination
	CMSG_ORD_TYPE_DENIED,								// 30008 order type change denied
	CMSG_ORD_PROTECTED,									// 30009 order protected against changes
	CMSG_ORD_ENTRY_NOTCLOSED,							// 30010 order entry not closed
	CMSG_ORD_INVALID_OPEN,								// 30011 open denied due to an invalid open type
	CMSG_ORD_INVALID_STATE,								// 30012 attempt to set an invalid order state
	CMSG_ORD_UPDATE_DENIED,								// 30013 order %d update denied
	CMSG_ORD_INVALID_CANCEL,							// 30014 invalid cancel code for order %d
	CMSG_ORD_INVALID_STOCKTRANS,						// 30015 invalid stock transaction type %c
	CMSG_ORD_INVALID_COMMTYPE,							// 30016 invalid commission type %c
	CMSG_ORD_VALDATE_FORMAT,							// 30017 invalid validity date format
	CMSG_ORD_VALDATE_LOW,								// 30018 validity date format < today
	CMSG_ORD_VALDATE_CUST,								// 30019 validity not allowed for customer %d
	CMSG_ORD_VALDATE_ORDERTYPE,							// 30020 validity not allowed for order type %s
	CMSG_ORD_VALDATE_LIMIT,								// 30021 validity high limit for order type %s is %d months.
	CMSG_ORD_ROUTE_INVALID,								// 30022 invalid route id %s
	CMSG_ORD_EVENT_NOTFOUND,							// 30023 order event %d %d %d not found.
	CMSG_ORD_REMARK_NOTFOUND,							// 30024 order remark %d %d %d not found.
	CMSG_ORD_ROUTE_NOENTRY,								// 30025 route assignm. denied, not orderentry
	CMSG_ORD_ROUTE_NOSHIP,								// 30026 route assignm. denied, no shipment
	CMSG_ORD_ROUTE_NOMORE,								// 30027 no more routes available
	CMSG_ORD_ROUTE_TIMEOFF,								// 30028 time limit exceeded for route %s
	CMSG_ORD_CSTGROUP_DISABLED,							// 30029 Customer group disabled from order entry
	CMSG_ORD_NOALTERNCOMPANIES,							// 30030 no alternate companies found
	CMSG_ORD_LOCK_DISAPPEARED,							// 30031 lock entry disappeared
	CMSG_ORD_TRANSFER_POSTING,							// 30032 order deferred because transfer posting
	CMSG_ORD_TRANSMISSION_ABEND,						// 30033 order deferred because transmission abend
	CMSG_ORD_NOMORE_INPROGRESS,							// 30034 order deferred because transmission abend
	CMSG_ORD_REM_NOTFOUND,								// 30035 order %d not found remote
	CMSG_ORD_FH_NOCONNECT,								// 30036 Foreign Host connect error
	CMSG_ORD_FH_NOORDER,								// 30037 Foreign Host Order Open error
	CMSG_ORD_FH_NOORDERTYPE,							// 30038 Foreign Host Order type error
	CMSG_ORD_FH_NOORDERITEM,							// 30039 Foreign Host Order item error
	CMSG_ORD_FH_NOCLOSE,								// 30040 Foreign Host Order Close error
	CMSG_ORD_FH_NODISCONNECT,							// 30041 Foreign Host Order Open error
	CMSG_ORD_DOUBLE_ORDER,								// 30042 Customer sends Order double(Swiss)
	CMSG_ORD_CREDITLIMIT_ONTOP,							// 30043 Customer credit limit reached
	CMSG_ORD_CLOSE_NOT_ALLOWED,							// 30044 Customer credit limit reached
	CMSG_ORD_CUST_NO_ORDERENTRY,						// 30045 Kunde %d ist für AE gesperrt
	CMSG_ORD_ENTRY_NUMBER_ERROR,						// 30046 Keine Auftragsnummer fuer Kunde %d bekommen
	CMSG_ORD_RANGEARTICLE_ERROR,						// 30047 Fehler beim Buchen Rangeartikel %d
	CMSG_ORD_ORDERVALUE_TO_LOW,							// 30048 Odervalue to low(State DF)
	CMSG_ORD_CREDITLIMIT_EXEED_VALUE,					// 30049 Customer credit limit exeede by %d
	CMSG_ORD_CSTDISCACC_EXHAUSTED,						// 30050 Customers Discountaccount exhausted by %d
	CMSG_ORD_CREDITLIMIT_EXHAUSTED,						// 30051 Customers Creditlimit exhausted by %d
	CMSG_ORD_CHANGED_TO_CASHORDER,						// 30052 Order changed to cashorder
	CMSG_ORD_CSTDISCACC_NOENTRIES,						// 30053 Customers Discacc no entries found in period
	CMSG_ORD_CSTDISCACC_NOBALANCE,						// 30054 Customers Discacc balance valu 0.00 or negativ
	CMSG_ORD_ROTIME_NOTINWINDOW,						// 30055 Rebate outside time window
	CMSG_ORD_REBATEORDER_NO_DD,							// 30056 No delayed delivery for order type RO
	CMSG_ORD_NO_DATA_FOR_CREMA,							// 30057 SQL_ERROR | KEINE SMTP GRUPPENDATEN MIT %.2f PROZENT GEFUNDEN.
	CMSG_ORD_TO_MUCH_DATA_FOR_CREMA,					// 30058 SQL_ERROR | ZUVIELE SMTP GRUPPENDATEN MIT %.2f PROZENT GEFUNDEN.
	CMSG_ORD_LIBMAIL_SEND_ERROR_CREMA,					// 30059 CREMA MAIL KONNTE VIA LIBMAIL FUER AUFTRAG %ld MIT %.2f PROZENT NICHT GESENDET WERDEN.
	CMSG_ORD_CREMA_MAILSEND_ERROR,						// 30060 CREMA MAIL KONNTE FUER AUFTRAG %ld MIT %.2f PROZENT NICHT GESENDET WERDEN.
	CMSG_ORD_CREMA_MAILSEND_SUBJECT,					// 30061 Pruefung Kreditlimit: %ld, %ld, %s, %s %s %s
	CMSG_ORD_CREMA_MAILSEND_GREETING,					// 30062 Sehr geehrte Damen und Herren,\n\n
	CMSG_ORD_CREMA_MAILSEND_LINE_ORDER,					// 30063 %s Es gibt für Auftrag %ld für Kunde %s, %s-%s %s eine Überschreitung des Kreditlimits.\n\n
	CMSG_ORD_CREMA_MAILSEND_LINE_LIMIT,					// 30064 %s Kreditlimit:  %s \n
	CMSG_ORD_CREMA_MAILSEND_LINE_LIMIT_USED,			// 30065 %s Beansprucht:  %s %.2f \n
	CMSG_ORD_CREMA_MAILSEND_LINE_ORDER_VALUE,			// 30066 %s Auftragswert: %s \n\n
	CMSG_ORD_CREMA_MAILSEND_LINE_DECISION,				// 30067 %s Bitte entscheiden sie über eine Auslieferung des Auftrags unter: \n\n
	CMSG_ORD_CREMA_MAILSEND_LINE_URL,					// 30068 %s %s\n\n
	CMSG_ORD_CREMA_MAILSEND_LINE_THANKS,				// 30069 %s Vielen Dank
	CMSG_ORD_CREMA_MAILSEND_LINE_WARNING,				// 30070 %s Warnung. Das derzeit noch verfügbare Kreditlimit bei Partner %s ( %ld ) %s, %s ist zu %.2f %% ausgeschöpft. \n\n
	CMSG_ORD_CREMA_MAILSEND_LINE_LIMIT_WARNING,			// 30071 %s Das aktuelle Limit beträgt %s EUR. \n\n
	CMSG_ORD_CREMA_MAILSEND_LINE_BEST_REGARDS,			// 30072 %s Mit freundlichen Grüßen
	CMSG_ORD_NO_PERCENTAGE_DATA_FOR_CREMA,				// 30073 SQL_ERROR | KEINE PROZENTWERTE FUER EMAILVERSANDT GEFUNDEN.
	CMSG_ORD_CREMA_MAILSEND_SUBJECT_WARN,				// 30074 Warnung Kreditlimit Partner %ld %s
	CMSG_ORD_OPENRESTRICTED,							// 30075 Auftrag öffnen ist für Kunde %d nicht erlaubt
	CMSG_ORD_CHANGE_OF_ORDERTYPE_NOT_ALLOWED,			// 30076 Auftragsartwechsel nicht erlaubt wegen bereits verarbeiteten Verbundpositionen
	CMSG_ORD_CHANGE_OF_CUSTOMER_NOT_ALLOWED,			// 30077 Kundenwechsel nicht erlaubt wegen bereits verarbeiteten Verbundpositionen
	CMSG_ORD_CHANGE_OF_BRANCH_NOT_ALLOWED,				// 30078 Filialwechsel nicht erlaubt wegen bereits verarbeiteten Verbundpositionen
	CMSG_ORD_ROUTE_NOPERMISSION,						// 30079 no permission to use the desired tour for this article (no permission for narcotics, cool articles)
	CMSG_ORD_ROUTE_NOIBTTOUR,							// 30080 no ibt tour
	CMSG_ORD_ROUTE_NOIBTCONFIGURATION,					// 30081 no ibt configuration in table ibtbranches available
	CMSG_ORD_CREMA_APPROVAL_MISSING,					// 30082 %ld Approval(s) still missing to %s the order! | count, (close/cancel)
	CMSG_ORD_CREMA_APPROVAL_DISCUSSION,					// 30083 %ld from %ld Approval(s) still missing. %ld voted for close, %ld voted for cancel. | count, closeapprovals, cancelapprovals
	CMSG_ORD_CREMA_APPROVAL_CLOSE,						// 30084 Close
	CMSG_ORD_CREMA_APPROVAL_CANCEL,						// 30085 Cancel
	CMSG_ORD_CREMA_MAILSEND_LINE_AMOUNT,				// 30086 Warnung. Der Kreditlimit-Warnbetrag von %ld wurde bei Partner %s ( %ld ) überschritten. Aktueller Betrag: %ld. \n\n
	CMSG_ORD_LIBMAIL_SEND_ERROR_CREMA_RETCODE,			// 30087 RetCode %ld
	CMSG_ORD_LIBMAIL_MAILSEND_ADDRESS,					// 30088 %s: Level %ld Type %ld SentTo %d : %s
	CMSG_ORD_CREMA_MAILSEND_ERROR_AMOUNT,				// 30089 CREMA MAIL KONNTE FUER AUFTRAG %ld MIT DEM BETRAG %ld NICHT GESENDET WERDEN.
	CMSG_ORD_CREMA_MAILSEND_PARTNER_ERROR,				// 30090 CREMA MAIL KONNTE FUER PARTNER %ld MIT %.2f PROZENT NICHT GESENDET WERDEN.
	CMSG_ORD_CREMA_MAILSEND_PARTNER_ERROR_AMOUNT,		// 30091 CREMA MAIL KONNTE FUER PARTNER %ld MIT DEM BETRAG %ld NICHT GESENDET WERDEN.
	CMSG_ORD_CREMA_PARTNER_VZ_ERROR,					// 30092 CREMA Partner VZs für Partner %ld konnten nicht geladen werden.
	CMSG_ORD_CREMA_CROSS_DB_ERROR,						// 30093 CREMA Cross DB Eintrag konnte nicht selektiert werden.
	CMSG_ORD_CREMA_MAIL_DELETE_ERROR,					// 30094 CREMA Email für Kunde %ld konnte nach Verarbeitung nicht geloescht werden.
	CMSG_ORD_CREMA_GUID_SUBJECT_DISCUSS,				// 30095 Auftragsfreigabe IDF Nr %ld
	CMSG_ORD_CREMA_MAIL_BODY_DISCUSS,					// 30096 Sehr geehrte Damen und Herren,\n\nIn der Auftragsfreigabe der IDF Nr. %ld, Apotheke %s in %s über %s %ld, sind unterschiedliche Entscheidungen getroffen worden. Dies mit dem Resultat, dass der Auftrag nach wie vor blockiert ist.\n\nWir möchten die Genehmigenden daher bitten, die Erfassung zu prüfen, sich abzustimmen und die Entscheidung so anzupassen, dass der Auftrag abgeschlossen oder storniert werden kann.\n\n%s\n\nBesten Dank!
	CMSG_ORD_CREMA_MAIL_GUID_CURRENCY,					// 30097 EUR
	CMSG_ORD_CREMA_GUID_SUBJECT_CLOSE,					// 30098 Freigabe: Auftrag %ld, IDF %ld, %s, %s
	CMSG_ORD_CREMA_MAIL_BODY_CLOSE,						// 30099 Sehr geehrte Damen und Herren,\n\nder Auftrag %ld(Kunde %ld, %s) wurde am %s erfolgreich von Benutzer %s aufgrund \"%s\" geschlossen.\n\nMit freundlichen Gruessen.
	CMSG_ORD_CREMA_GUID_SUBJECT_CANCEL,					// 30100 Stornierung: Auftrag %ld, IDF %ld, %s, %s
	CMSG_ORD_CREMA_MAIL_BODY_CANCEL,					// 30101 Sehr geehrte Damen und Herren,\n\nder Auftrag %ld(Kunde %ld, %s) wurde am %s erfolgreich von Benutzer %s aufgrund \"%s\" storniert.\n\nMit freundlichen Gruessen.
	CMSG_ORD_CREMA_MAIL_GUID_TIME_FILLER,				// 30102 um
	CMSG_ORD_CREMA_MAILSEND_LINE_LIMIT_WARNING_CH,		// 30103 %s Das aktuelle Limit beträgt %s EUR. \n\n


    CMSG_ITEM										= 31000,	// 31 000	beging order item object group here
    CMSG_ITM_UPDATE_DENIED,				// 			item %d in order %d : update denied
    CMSG_ITM_INSERT_DENIED,				// 			item insert for order %d denied
    CMSG_ITM_ORDERQ_DENIED,				//			item %d in order %d : order quantity update denied
    CMSG_ITM_SHIPQ_DENIED,				//			item %d in order %d : ship quantity update denied
    CMSG_ITM_DIK_NOTENTERABLE,			// 31 005	discount in-kind not enterable for order type %s
    CMSG_ITM_NOPRODUCT,					//			value not changeable, no stocked product
    CMSG_ITM_NOVALUEDTEXT,				//			value not changeable, no valued text
    CMSG_ITM_NOTEXT,					//			value not changeable, no text
    CMSG_ITM_ART_INVDIGITS,				//			invalid digits in article number
    CMSG_ITM_ART_MISSING,				// 31 010	article number missing
    CMSG_ITM_INVDIGITS_OQ,				//			invalid digits in order quantity
    CMSG_ITM_OQ_MISSING,				//			order quantity missing
    CMSG_ITM_DISPOART_NOTFOUND,			//			Dispo article not found
    CMSG_ITM_DESC_MISSING,				//			article description missing
    CMSG_ITM_AEP_REQUIRED,				// 31 015
    CMSG_ITM_AEP_NOTGT_GEP,				//			AEP not > GEP
    CMSG_ITM_GEP_REQUIRED,				//
    CMSG_ITM_DSP_NOTDIS,				//			not discountable, direct discount spec
    CMSG_ITM_DIS_OR_PERCENT,			//			direct discount or percent
    CMSG_ITM_DSP_PERCENTHIGH,			// 31 020	discount in % too high
    CMSG_ITM_DSP_AMOUNTHIGH,			//			discount amount too high
    CMSG_ITM_BTYPE_INVALID,				//			invalid booking type
    CMSG_ITM_TAXKEY_INVALID,			//			invalid tax key, must be %d or %d
    CMSG_ITM_QUAN_INVALID,				//			Order quantity %i invalid
    CMSG_ITM_NOT_AUTHORIZED,			// 31 025	Customer not authorized to order product
    CMSG_ITM_ALTERNATE,					//			Alternate article for %d
    CMSG_ITM_RESTDELIVERY,				//			restdelivery
    CMSG_ITM_ACCOUNT_INSERT_DENIED,		//			insert article account denied
    CMSG_ITM_BTM_TOMORROW,				//			BTM delivery tomorrow
    CMSG_ITM_INPUT_TO_LARGE,			// 31 030	Input to large
    CMSG_ITM_EVENTUALLY_PURCHASE,		//			Eventual purchase item
    CMSG_ITM_KONTIGENT_EXCEEDED,		//			kontigent exceeded
    CMSG_ITM_NOT_ONSTOCK,				//			article not on stock
    CMSG_ITM_STOCK_DIFFERENCE,			//			article %d stock difference
    CMSG_ITM_AEP_NOTLESS_GEP,			// 31 035	AEP not < GEP (swiss)
    CMSG_ITM_NOT_AUTHORIZED_DCT,		//			Customer not authorized to order product
    CMSG_ITM_ARTQUOTA_EXEEDED,			//			Customer ArticleQuota exeeds
    CMSG_ITM_PURCHASE_NOTALLOWED,		//			Purchase not for this ordertype
    CMSG_ITM_DELAYEDDELIVERY,			//			Delivery at
    CMSG_ITM_NOT_AUTHORIZED_INFO,		// 31 040	Customer not authorized for product Info
    CMSG_ITM_NO_DISCOUNT_ENTRY,			//			No discount entry for article %d found
    CMSG_ITM_RESTDELIVERY_COMES,		//			Restdelivery is coming
    CMSG_ITM_SEPARATE_ARTGROUP,			//			Separate Article per SeparateArtGroup definition
    CMSG_ITM_SEPARATE_ARTGROUP_S,		//			Separate Article per SeparateArtGroup definition
    CMSG_ITM_ART_NOTOVERDCT,			// 31 045	Article not via DCT or XML
    CMSG_ITM_SEPARATE_AUXDELIVERY_S,	// 			Separate Article per SeparateArtGroup Verbund
    CMSG_ITM_NONARCOTIC_DISCACC_ORDER,	//			No Narcotics within a NR order (Bulgarian apll.)
    CMSG_ITM_NOT_AUTHORIZED_STOTINKI,	//			Customer not authorized to order stotinki product
    CMSG_ITM_REIMPORT_BOOKED_FOR,		//			Reimport booked for %s
    CMSG_ITM_HIGHVALUE_EXCEEDED,		// 31 050	High value on position %d exceeded
    CMSG_ITM_IBTPOS_ALREADY_WORKEDUP,	//			IBTPos(kdverbundpos) processingstatus == 2
    CMSG_ITM_IBTPOS_BOOKED_IN_BRANCH,	//			IBTPos(kdverbundpos) booked in branch  nn
    CMSG_ITM_ARTICLE_NOT_IN_TENDER,		//			Article not included in Tender
    CMSG_ITM_TENDERQTY_EXCEEDED,		//			Tender FreeQty exceeded
	CMSG_ITM_NOTFOUND,                  //          KdAuftrag %d KdAuftragNr %d auf %s nicht gefunden
	CMSG_ITM_SERVICENO_INVALID,			//			service number invalid


    CMSG_CUSTOMER = 32000,              // beging of customer-related group
    CMSG_CST_NOTFOUND,                  // customer %d not found
    CMSG_CST_KGN_NOTFOUND,              // term group %d not found
    CMSG_CST_KDKGN_NOTFOUND,            // no term group for customer %d found
    CMSG_CST_NOTERMS,                   // no terms found for customer %d
    CMSG_CST_NOFLAGS,                   // no flags found for customer %d
    CMSG_CST_NOBTIMES,                  // no business times found for customer %d
    CMSG_CST_GRP_NOTFOUND,              // customer group %s not found
    CMSG_CST_BTM_NOTFOUND,              // business time for customer %d and TagesTyp %s not found
    CMSG_CST_OT_UNKNOWN,                // order type %s unknown
    CMSG_CST_ADSUT_NOTFOUND,            // ADS User times for customer %d and TagesTyp %s not found
    CMSG_CST_ADSUT_NOUTIMES,            // ADS no user times found for customer %d
    CMSG_CST_CHECK_CREDITLIMIT,         // Check CreditLimit
    CMSG_CST_NO_DISCCOUNTCOND,          // No DiscountCondition Entry Available
    CMSG_CST_NO_DISCCOUNTLIST,          // No DiscountList Entry Available
    CMSG_CST_NO_PHARMACYGROUPID,        // No PharmacyGroupId
    CMSG_CST_BLOCKED_FOR_ORDERENTRY,    // Kunde %d Filiale %d gesperrt


    CMSG_ARTICLE = 33000,               // begin of article-related group
    CMSG_ART_NOTFOUND,                  // 33001 article %d not found
    CMSG_ART_QLACK,                     // 33002 article quantity lack
    CMSG_ART_DIK_SCALE_NOTFOUND,        // 33003 discount-in-kind scale %d not found
    CMSG_ART_DIS_SCALE_NOTFOUND,        // 33004 discount price scale for article %d not found
    CMSG_ART_NOBASEPRICES,              // 33005 base prices for article %d not found
    CMSG_ART_ALTERN_NOTFOUND,           // 33006 article %d %d not found
    CMSG_ART_STORELOC_NOTFOUND,         // 33007 article store location %d %d %d %s not found
    CMSG_ART_NOTACTIVE,                 // 33008 article %d not active
    CMSG_ART_REM_NOTFOUND,              // 33009 article %d not found at database %s
    CMSG_ART_REIMPORT_NOTFOUND,         // 33010 No reimport article for %d found
    CMSG_ART_WITHOUT_CERTIFICATE,       // 33011 Artikel %d without certificate
    CMSG_ART_PURCHASE_STOP,             // 33012 Artikel %d purchase stopped
    CMSG_ART_NOHEALTHFUNDCODE,          // 33013 Artikel %d no healthfundcode available
    CMSG_ART_QLACK_DISC_ARTICLE,        // 33014 Discount article quantity lack
    CMSG_ART_REVERSESUBSTITUTION,       // 33015 Reverse Substitution possible
	CMSG_ART_SUBSTARTICLE_NOSTOCK,      // 33016 Substitution article has no quantity on stock
	CMSG_ART_TRANSPORT_EXCLUSION,		// 33017 Transportausschluss (Kunde hat keine Tour mit der der Artikel geliefert werden darf!)


	CMSG_SESS										= 34000,	// begin of session group
	CMSG_SESS_NOBRANCH								= 34001,	// branch %d not found
	CMSG_SESS_NOORDERTYPE							= 34002,	// no order types found
	CMSG_SESS_NOSTOCKTRANS							= 34003,	// no stock transactions found
	CMSG_SESS_NOCOMMTYPE							= 34004,	// no comm types found
	CMSG_SESS_NOORDERVALIDTRANS						= 34005,	// no valid order transactions found
	CMSG_SESS_TEXTTABLE_NOTLOADED					= 34006,	// text table wasn't loaded
	CMSG_SESS_NOBRANCHPARTNER						= 34007,	// no branchpartner found
	CMSG_SESS_NOMODTABENTRY							= 34008,	// no ModemTabEntry found
	CMSG_SESS_NOTIMESET								= 34009,	// could not set time of client
	CMSG_SESS_NOCOMPUTERENTRY						= 34010,	// no Computer entry found
	CMSG_SESS_NOPARAERENTRY							= 34011,	// no ParaAuftrager entry found
	CMSG_SESS_NOHOLIDAYENTRY						= 34012,	// no HoliDay entries found
	CMSG_SESS_NODISCOUNTORDERTYPENTRY				= 34013,	// no DiscountOrdTyp entries found
	CMSG_SESS_DUPLICATECONNECTIONINJECTION			= 34014,	// tried to inject a connection whereas a connection was already there
	CMSG_SESS_NULLCONNECTION						= 34015,	// tried to open a connection that was not injected / set before

	CMSG_DA											= 35000,	// begin Direct Aux Delivery group
	CMSG_DA_ART_NOTIN								= 35001,	// Article  %d  at %d not found
//	CMSG_DA_ART_NOWRITE								= 35002,	// Article  %d  at %d write error (OBSOLETE)
//	CMSG_DA_ART_NOUNBOOK							= 35003,	// Article  %d  at %d write error (OBSOLETE)
//	CMSG_DA_ACC_NOWRITE								= 35004,	// ArtAcct  %d  at %d write error (OBSOLETE)
//	CMSG_DA_ACC_ERROR								= 35005,	// ArtAcct  %d  at %d any error (OBSOLETE)
//	CMSG_DA_VKNOTFOUND								= 35006,	// Aux Rem Header %d  not found (OBSOLETE)
	CMSG_DA_VKNOWRITE								= 35007,	// Aux Rem Header %d  write error
//	CMSG_DA_VPNOTFOUND								= 35008,	// Aux Rem Position %d %d not found (OBSOLETE)
	CMSG_DA_VPNODELETE								= 35009,	// Aux Rem Position %d %d delete error
	CMSG_DA_VPNOWRITE								= 35010,	// Aux Rem Position %d %d write  error
//	CMSG_DA_VLERROR									= 35011,	// Aux Lock %d not found  (filiale) (OBSOLETE)


	CMSG_MISC										= 39000,	// begin of miscellaneous messages group
//	CMSG_MISC_BRANCH_NOTFOUND						= 39001,	// branch %d not found (OBSOLETE)
	CMSG_MISC_EXCEPTION								= 39002,	// exception: %s
	
	CMSG_LOG										= 40000,	// begin of log messages group here
	CMSG_LOG_ORDENTRY								= 40001,	// order %d for customer %d opened for order entry
	CMSG_LOG_ORDUPDATE								= 40002,	// order %d for customer %d opened for order update
	CMSG_LOG_ORDVIEW								= 40003,	// order %d for customer %d opened for viewing
	CMSG_LOG_HIGH									= 50000,	// end of order entry server messages


	CMSG_SDC										= 50000,
	CMSG_SDC_NICHT_NUMERISCH						= 50001,
	CMSG_SDC_PRUEFZIFFER_FALSCH						= 50002,
	CMSG_SDC_NICHT_BERECHTIGT						= 50003,
	CMSG_SDC_AUSSER_HANDEL							= 50004,
	CMSG_SDC_FEHLT_ZUR_ZEIT							= 50005,
	CMSG_SDC_NICHT_LIEFERBAR_HERSTELLER				= 50006,
	CMSG_SDC_NICHT_GELIEFERT_HERSTELLER				= 50007,
	CMSG_SDC_NICHT_GEFUEHRT							= 50008,
	CMSG_SDC_NR_UNBEKANNT							= 50009,
	CMSG_SDC_AUFTRAGSBESTAETIGUNG					= 50010,
	CMSG_SDC_DELIVER_TODAY							= 50011,
	CMSG_SDC_DELIVER_TOMORROW						= 50012,
	CMSG_SDC_DISCONTINUED_ARTICLE					= 50013,	// Auslaufartikel
	CMSG_SDC_AUSWEICHARTIKEL_GEBUCHT				= 50014,
	CMSG_SDC_RESTDELIVERY							= 50015,
	CMSG_SDC_PURCHASEORDER							= 50016,
	CMSG_SDC_QUANTITYRAISED							= 50017,
	CMSG_SDC_VERFUEGBAR								= 50018,
	CMSG_SDC_NICHT_VERFUEGBAR						= 50019,
	CMSG_SDC_NO_ORDER								= 50020,
	CMSG_SDC_ALTERNATE_ARTICLE						= 50021,
	CMSG_SDC_AUXPOSTED								= 50022,
	CMSG_SDC_AUXPOSTPOSSIBLE						= 50023,
	CMSG_SDC_CENTRAL_STORE							= 50024,
	CMSG_SDC_NUR_DIREKT								= 50025,
	CMSG_SDC_NACHLIEFERN_MOEGLICH					= 50026,
	CMSG_SDC_VOM_HERSTELLER							= 50027,
	CMSG_SDC_DISPO_MOEGLICH							= 50028,
	CMSG_SDC_CALLBACK								= 50029,
	CMSG_SDC_AUSWEICHARTIKEL						= 50030,
	CMSG_SDC_WIRD_BEARBEITET						= 50031,
	CMSG_SDC_SPEZIAL_BESTAETIGUNG					= 50032,
	CMSG_SDC_AUXPOSTED_NEW							= 50033,
	CMSG_SDC_AUXPOSTPOSSIBLE_NEW					= 50034,
	CMSG_SDC_CENTRAL_STORE_NEW						= 50035,
	CMSG_SDC_ARTIKEL_NO_CERTIFICAT					= 50036,
	CMSG_SDC_ALTER_REIMPORT_ARTIKEL					= 50037,
	CMSG_SDC_RUECKRUF_FIXTEXT						= 50038,
//	CMSG_SDC_ARTICLETEXT_FOR						= 50039,	// OBSOLETE (nur hmk)
	CMSG_SDC_ART_DELAYED_DELIVERED					= 50040,
//	CMSG_SDC_ART_NOT_OVERDCT						= 50041,	// OBSOLETE
	CMSG_SDC_REIMPORT_ARTIKEL_GEBUCHT				= 50042,
	CMSG_SDC_REIMPORTARTIKEL						= 50043,
	CMSG_SDC_ARTQUOTA_EXEEDED						= 50044,
	CMSG_SDC_CSTDISCACC_EXCEEDED					= 50045,
	CMSG_SDC_NONARCOTIC_DISCACC_ORDER				= 50046,
	CMSG_SDC_CUSTOMER_NONARCOTICS					= 50047,
	CMSG_SDC_NO_PERMISSION_HEALTHFUND				= 50048,
	CMSG_SDC_NO_PERMISSION_RETAIL					= 50049,
	CMSG_SDC_PSEUDO_STORAGE_LOCATION				= 50050,
	CMSG_SDC_NO_BATCH_PROVIDED						= 50051,
	CMSG_SDC_BATCH_GIVEN_BUT_NOT_PERMITTED			= 50052,
	CMSG_SDC_DESIRED_BATCH_GIVEN_ONLY_FIXED_ALLOWED = 50053,
	CMSG_SDC_FIXED_BATCH_GIVEN_BUT_NOT_ALLOWED		= 50054,
	CMSG_SDC_BATCH_PROCESSING_NOT_POSSIBLE			= 50055,
    CMSG_SDC_QUOTA_ARTICLE_SUPPLIER                 = 50056,
	CMSG_SDC_DEFAULT								= 50005,	// CMSG_SDC_FEHLT_ZUR_ZEIT,


	CMSG_PXDCPOOL									= 51000,	// begin of pxdcpool messagenumbers
	CMSG_PXDC_ENTRY_NOTFOUND						= 51001,	// table entry %s not found


//	CMSG_LOCKMAN									= 52000,	// begin of lockmanager-related group (OBSOLETE)
//	CMSG_LCK_SYSERROR,											// system error (OBSOLETE)
//	CMSG_LCK_FULLTABLE											// lock table full (OBSOLETE)


//	CMSG_PXVENDOR									= 54000,	// begin of pxvendor messagenumbers (OBSOLETE)
//	CMSG_PXVEND_ENTRY_NOTFOUND						= 54001,	// table entry %s not found (OBSOLETE)


//	CMSG_PXARTDEA									= 55000,	// begin of pxartdealer messagenumbers (OBSOLETE)
//	CMSG_PXDEA_ENTRY_NOTFOUND						= 55001,	// table entry %s not found (OBSOLETE)


	CMSG_TIMETYPE									= 60000,	// begin TimeType group
	CMSG_TMT_ENTRY_NOTFOUND							= 60001,	// Tabelle Zeitarten  %d, %s, %s not found
//	CMSG_TMT_CUSTOMER_NOTFOUND						= 60002,	// Customer  %d, %s, %s not found (OBSOLETE)
//	CMSG_TMT_COMPANY_NOTFOUND						= 60003,	// Company   %d, %s, %s not found (OBSOLETE)
	CMSG_TMT_NOTIMETYPES							= 60004,	// No TimeTypes  found


    CMSG_ADMESSAGE									= 61000,	// 61000 begin Alternate Delivery group
    CMSG_AD_COMPANY_NOTFOUND,           // 61001 ADC  %d      not found
    CMSG_AD_DELPOS_NOTFOUND,            // 61002 ADC  %d %d   not found
    CMSG_AD_CST_NOTIN,                  // 61003 Customer %d  not in   AlternDelService
    CMSG_AD_ART_NOTIN,                  // 61004 Article  %d  is not a AlternDelProduct
    CMSG_AD_NOTPOSSIBLE,                // 61005 Alternate Posting not possible
    CMSG_AD_CMP_NOTIN,                  // 61006 Company  %d  not ins  AlternDelService
    CMSG_AD_STOCKTOLOW,                 // 61007 Company  %d  stock does not satisfy
    CMSG_AD_VKNOTFOUND,                 // 61008 Aux Rem Header %d  not found
    CMSG_AD_VPNOTFOUND,                 // 61009 Aux Rem Position %d %d not found
    CMSG_AD_VPNODELETE,                 // 61010 Aux Rem Position %d %d delete error
    CMSG_AD_VPNOWRITE,                  // 61011 Aux Rem Position %d %d write  error
    CMSG_AD_VLNOTFOUND,                 // 61012 Aux Lock %d not found
    CMSG_AD_CST_NO_RESTDELIVERY,        // 61013 Customer is no restdelivery user
    CMSG_AD_ART_AUSSERHANDEL,           // 61014 Article is out of trading
    CMSG_AD_ART_AUSLAUFARTIKEL,         // 61015 Article is expired
    CMSG_AD_ART_EINKAUFSPERRE,          // 61016 Article is purchasing locked
    CMSG_AD_ART_OPIAT,                  // 61017 Article is opiat
    CMSG_AD_ART_NO_RESTDELIVERY,        // 61018 Article not allowed for restdelivery
    CMSG_AD_OT_NO_RESTDEL_TYPE,         // 61019 Type of order not allowed for restdelivery
    CMSG_AD_IBTREQ_NODELETE,            // 61020 IBT Request %d %d delete error
    CMSG_AD_IBTREQ_NOWRITE,             // 61021 IBT Request %d %d write error
    CMSG_AD_IBTDISCOUNTREQ_NOWRITE,     // 61022 IBT Discount Request %d %d write error


	CMSG_ACC										= 62000,	// begin ArticleAccount group (DUPLICATE!)
	CMSG_ACC_ENTRY_NOTFOUND							= 62001,	// ACC  %d not found  (DUPLICATE!)


	CMSG_OCL										= 62000,	// begin OrderCloseParam group
	CMSG_OCL_PARAM_NOTFOUND							= 62001,	// OCL  %d      not found


//	CMSG_BRPMESSAGE									= 63000,	// begin pxBranchPartner group (OBSOLETE)
//	CMSG_BRP_ENTRY_NOTFOUND							= 63001,	// entry  not found %d (OBSOLETE)


	CMSG_COMP										= 65000,	// begin Computer group
	CMSG_COMP_ENTRY_NOTFOUND						= 65001,	// entry not found


	CMSG_TASKCNTL									= 66000,	// begin TaskControl group
	CMSG_TASKCNTL_NOTFOUND							= 66001,	// TASKCONTROL %s %s   not found


	CMSG_CUSTONR									= 68000,	// begin Group
	CMSG_CUSTONR_ENTRY_NOTFOUND 					= 68001,	// entry not found


	CMSG_CUSTINFO									= 69000,	// begin pxCustOrderInfo Group
	CMSG_CUSTINFO_ENTRY_NOTFOUND					= 69001,	// entry not found


	CMSG_ARTEAN 									= 70000,	// begin Group
	CMSG_ARTEAN_ENTRY_NOTFOUND						= 70001,	// entry not found


	CMSG_ARTPREDEL									= 71000,	// begin Group
	CMSG_ARTPREDEL_ENTRY_NOTFOUND					= 71001,	// entry not found


//	CMSG_CSTREC										= 72000,	// begin pxCustRecode Group (OBSOLETE)
//	CMSG_CSTREC_ENTRY_NOTFOUND						= 72001,	// entry not found (OBSOLETE)


	CMSG_CUSTROUTING								= 73000,	// begin Group
	CMSG_CUSTROUTING_ENTRY_NOTFOUND					= 73001,	// entry not found


//	CMSG_CUSTPHARMGROUP								= 74000,	// begin pxCustPharmGroup Group (OBSOLETE)
//	CMSG_CUSTPHARMGROUP_ENTRY_NOTFOUND				= 74001,	// entry not found (OBSOLETE)


	CMSG_VALDISCINFO								= 75000,	// begin Group
	CMSG_VALDISCINFO_ENTRY_NOTFOUND					= 75001,	// entry not found


	CMSG_STOCKENTRY									= 76000,	// begin Stockentry group
	CMSG_STOCKENTRY_NOTFOUND						= 76001,	// Stockentry  %d %d   not found


	CMSG_DEBITLIMIT									= 77000,	// begin debtlimit group
	CMSG_DEBITLIMIT_NOTFOUND						= 77001,	// Debitlimit  %d not found


//	CMSG_ARTICLEQUOTA								= 78000,	// begin ArticleQuota  group (OBSOLETE)
//	CMSG_AQUOT_ENTRY_NOTFOUND						= 78001,	// ArticleQuotaentry %d  %d %d not found (OBSOLETE)


//	CMSG_KDAUFTRAGPOSRAB							= 79000,	// begin of kdauftragposrab group (OBSOLETE) (DUPLICATE!)
//	CMSG_KDAUFTRAGPOSRAB_DBWRITEERROR				= 79001,	// DB write error (OBSOLETE) (DUPLICATE!)


//	CMSG_DELAYEDDELIVERYART							= 79000,	// begin DELAYDDELIVERYART group (OBSOLETE) (DUPLICATE!)
//	CMSG_DDELART_ENTRY_NOTFOUND						= 79001,	// DELAYDDELIVERYART %d  %d %d not found (OBSOLETE) (DUPLICATE!)


	CMSG_NARC										= 79000,	// begin pxNarcTransfer group
	CMSG_NARC_ENTRY_NOTFOUND						= 79001,	// NARC  %d not found

//	CMSG_PARMESSAGE									= 79000,	// begin Parameter group (OBSOLETE) (DUPLICATE!)
//	CMSG_PAR_ENTRY_NOTFOUND 						= 79001,	// PARAMETERENTRY  %d      not found (OBSOLETE) (DUPLICATE!)

	CMSG_TCACCESS									= 80000,	// begin of message group here
	CMSG_TCACCESS_ERROR								= 80001,	// Tcaccess error during connect: %s
	CMSG_TCACCESS_NO_INIFILE						= 80001,	// Tcaccess no Ini-File for Branch %d
	CMSG_TCACCESS_HIGH								= 80999,

	CMSG_LIBCSC_CONTACT								= 81001,	// Ansprechpartner
	CMSG_LIBCSC_CREATOR								= 81002,	// Eingestellt von
	CMSG_LIBCSC_TELEFON								= 81003,	// Telefon
	CMSG_LIBCSC_SPEEDDIAL							= 81004,	// Kurzwahl
	CMSG_LIBCSC_CUSTOMERNO							= 81005,	// IDF-Nummer
	CMSG_LIBCSC_MOREINFO							= 81006,	// Zusätzliche Info
	CMSG_LIBCSC_LINK								= 81007,	// Um den Rückruf zu bearbeiten, folgen Sie bitte diesem Link

	CMSG_LIBCSC_CALLBACK_NOTFOUND					= 81100,	// 
	CMSG_LIBCSC_CALLBACK_LOCKED						= 81101,	// 
	CMSG_LIBCSC_CALLBACK_CUSTOMERNOTFOUND			= 81102,	// 

	CMSG_HIGH										= 99999	
}

// dirty hack to get a ";" for the CPP code after the enum definition
#include "semikolon.h"

#endif // GUARD_MESSAGECODE_ENUM_H

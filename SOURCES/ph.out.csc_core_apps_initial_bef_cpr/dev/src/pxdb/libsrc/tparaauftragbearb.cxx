#include <stddef.h>         /* standard C run-time header */
#include <stdio.h>          /* standard C run-time header */
#include <string.h>
#include <pxrecord.h>       /* all record structures */
#include "pxdbxx.h"
#include "pxdbfunc.h"
#include <ndefs.h>
#include <pxenv.h>
#include "tparaauftragbearb.h"
#include "keys.h"

/* Global variables */
extern int  functionnr;

#define UNUSED(x) (void)(x)

/*-------------------------------------------------------------------*/
int pxParaAuftragBearbRead( struct tPARAAUFTRAGBEARB* record, const char* dbname )
{
	int retval = cDBXR_NORMAL;

    EXEC SQL BEGIN DECLARE SECTION;
    struct C_PARAAUFTRAGBEARB * recordp;
	char query[4096] = {' '};
    EXEC SQL END DECLARE SECTION;

    functionnr = F_PARAAUFTRAGBEARB*10+F_Read;
    recordp = (struct C_PARAAUFTRAGBEARB *) record;			

	sprintf( query, "SELECT filialnr, kdauftragart, buchart, koart, durchlaufnormal, durchlaufeilbote, karenztourschein, ssammelkommi, svorfaktura, sbtmschein, "
					"swerbung, pznkuehlbox1, pznkuehlbox2, pznbtmschein, pznwerbefach, pznwerbefach2, anzartalphawsort, maxposmenge, tourwochentag, tourverspaetung, "
					"bahnhofdoppelkontr, serweitertetouranz, sauftragzusammen, auftragzusammenmmm, auftragzusammenhhh, ssepwanneneilbote, sepwannentyp, sepwannenrestzeit, skdauftragsplit, "
					"tourenkippzeit, automnachlief, dafueentsdiornl, defwertkeinabschl, maxposverbund, skuehlu8grad, srrsa02, strennbei10ner, stext99nak, sbearb06, btm_extra, time_no_btm, "
					"sverbunddirekt, pznzytostatika, defektdispo, svorausbezg, sbtmkommi, snotoak, maxposauftrag, anzposzu, maxposeil, snewdiscount, noroutingmm, sbatchteilmenge, sverunden, "
					"pluszeitbtm, etartnonatra, mindestbestellwert, pznaddoncharge, reserveperiod, reservemaxqty, rangepricepct, snarctrans, spossplit, sdaynight, tourchecktime, pznfranko, "
					"pznfreightage, anzaufclose, anzposclose, snochangeval, skumpos, sanzprintcode, sklclose, sordercriteria, maxlinevalue, waketime1, waketime2, containerlevel, "
					"sibtcstorg, maxsurcharge, sdeforderdf, enclosertilttime, screma, maxqtyrequest, checktimetoclose, maxdpodays, delayeddays, sdiscountlocal, sdeferorders, "
					"sdaynightmerge, scloseibtatonce, consolidationdelay, autoibtsubst, swnewcallback, srangecalcbase, sdiscountcalcbase, msv3deliverytimeframe, sendmsv3deliverytime, "
					"msv3touroption, usetourmanager, tourweekday, orderperiodtourassignment, msv3orderperiodclosure, msv3closuretimeadjustment, useibtcustfordeliverytime, usenewdiscountcalc, "
					"nlevelibt, ibtqtyavailabilitypercentage, reversesubstitutiondays, sstopcrema, timecancelcremaorder, snodispoclosed, ibtnormaltouractive, scloserestdeliveryatonce, "
					"sclosedispoatonce, scool20, disablegt24toursforholiday, snewf6, sdispoimport, dayshandovertodelivery, uselatestibttour "
					"FROM %s:paraauftragbearb WHERE FILIALNR = ?;", dbname );

	EXEC SQL PREPARE pxparaauftragbearbread_stmt FROM :query;
	EXEC SQL DECLARE pxparaauftragbearbread_cur CURSOR WITH HOLD FOR pxparaauftragbearbread_stmt;

	EXEC SQL OPEN pxparaauftragbearbread_cur USING :recordp->FILIALNR;

	EXEC SQL FETCH pxparaauftragbearbread_cur INTO
		:recordp->FILIALNR, :recordp->KDAUFTRAGART, :recordp->BUCHART, :recordp->KOART, :recordp->DURCHLAUFNORMAL, :recordp->DURCHLAUFEILBOTE,
        :recordp->KARENZTOURSCHEIN, :recordp->SSAMMELKOMMI, :recordp->SVORFAKTURA, :recordp->SBTMSCHEIN, :recordp->SWERBUNG, :recordp->PZNKUEHLBOX1,
        :recordp->PZNKUEHLBOX2, :recordp->PZNBTMSCHEIN, :recordp->PZNWERBEFACH, :recordp->PZNWERBEFACH2, :recordp->ANZARTALPHAWSORT, :recordp->MAXPOSMENGE,
        :recordp->TOURWOCHENTAG, :recordp->TOURVERSPAETUNG, :recordp->BAHNHOFDOPPELKONTR, :recordp->SERWEITERTETOURANZ, :recordp->SAUFTRAGZUSAMMEN, 
        :recordp->AUFTRAGZUSAMMENMMM, :recordp->AUFTRAGZUSAMMENHHH, :recordp->SSEPWANNENEILBOTE, :recordp->SEPWANNENTYP, :recordp->SEPWANNENRESTZEIT,
        :recordp->SKDAUFTRAGSPLIT, :recordp->TOURENKIPPZEIT, :recordp->AUTOMNACHLIEF, :recordp->DAFUEENTSDIORNL, :recordp->DEFWERTKEINABSCHL, :recordp->MAXPOSVERBUND,
        :recordp->SKUEHLU8GRAD, :recordp->SRRSA02, :recordp->STRENNBEI10NER, :recordp->STEXT99NAK, :recordp->SBEARB06, :recordp->BTM_EXTRA, :recordp->TIME_NO_BTM,
        :recordp->SVERBUNDDIREKT, :recordp->PZNZYTOSTATIKA, :recordp->DEFEKTDISPO, :recordp->SVORAUSBEZG, :recordp->SBTMKOMMI, :recordp->SNOTOAK, :recordp->MAXPOSAUFTRAG,
        :recordp->ANZPOSZU, :recordp->MAXPOSEIL, :recordp->SNEWDISCOUNT, :recordp->NOROUTINGMM, :recordp->SBATCHTEILMENGE, :recordp->SVERUNDEN, :recordp->PLUSZEITBTM,
        :recordp->ETARTNONATRA, :recordp->MINDESTBESTELLWERT, :recordp->PZNADDONCHARGE, :recordp->RESERVEPERIOD, :recordp->RESERVEMAXQTY, :recordp->RANGEPRICEPCT,
        :recordp->SNARCTRANS, :recordp->SPOSSPLIT, :recordp->SDAYNIGHT, :recordp->TOURCHECKTIME, :recordp->PZNFRANKO, :recordp->PZNFREIGHTAGE, :recordp->ANZAUFCLOSE,
        :recordp->ANZPOSCLOSE, :recordp->SNOCHANGEVAL, :recordp->SKUMPOS, :recordp->SANZPRINTCODE, :recordp->SKLCLOSE, :recordp->SORDERCRITERIA, :recordp->MAXLINEVALUE,
        :recordp->WAKETIME1, :recordp->WAKETIME2, :recordp->CONTAINERLEVEL, :recordp->SIBTCSTORG, :recordp->MAXSURCHARGE, :recordp->SDEFORDERDF, :recordp->ENCLOSERTILTTIME,
        :recordp->SCREMA, :recordp->MAXQTYREQUEST, :recordp->CHECKTIMETOCLOSE, :recordp->MAXDPODAYS, :recordp->DELAYEDDAYS, :recordp->SDISCOUNTLOCAL, :recordp->SDEFERORDERS,
        :recordp->SDAYNIGHTMERGE, :recordp->SCLOSEIBTATONCE, :recordp->CONSOLIDATIONDELAY, :recordp->AUTOIBTSUBST, :recordp->SWNEWCALLBACK, :recordp->SRANGECALCBASE,
		:recordp->SDISCOUNTCALCBASE, :recordp->MSV3DELIVERYTIMEFRAME, :recordp->SENDMSV3DELIVERYTIME, :recordp->MSV3TOUROPTION, :recordp->USETOURMANAGER, :recordp->TOURWEEKDAY,
        :recordp->ORDERPERIODTOURASSIGNMENT, :recordp->MSV3ORDERPERIODCLOSURE, :recordp->MSV3CLOSURETIMEADJUSTMENT, :recordp->USEIBTCUSTFORDELIVERYTIME, :recordp->USENEWDISCOUNTCALC,
        :recordp->NLEVELIBT, :recordp->IBTQTYAVAILABILITYPERCENTAGE, :recordp->REVERSESUBSTITUTIONDAYS, :recordp->SSTOPCREMA, :recordp->TIMECANCELCREMAORDER, :recordp->SNODISPOCLOSED,
		:recordp->IBTNORMALTOURACTIVE, :recordp->SCLOSERESTDELIVERYATONCE, :recordp->SCLOSEDISPOATONCE, :recordp->SCOOL20, 
		:recordp->DISABLEGT24TOURSFORHOLIDAY, :recordp->SNEWF6, :recordp->SDISPOIMPORT, :recordp->DAYSHANDOVERTODELIVERY, :recordp->USELATESTIBTTOUR;
	

	switch( SQLCODE )
	{
		case 0:
			retval = cDBXR_NORMAL; 
			break;
		case 1:
			retval = cDBXR_ISDUPLICATE;
			break;
		case 100:
			retval = cDBXR_NOTFOUND;
			break;
		default:
			retval = cDBXR_IOERROR;
			break;
	}

	EXEC SQL CLOSE pxparaauftragbearbread_cur;
	EXEC SQL FREE pxparaauftragbearbread_stmt;

	return retval;
}

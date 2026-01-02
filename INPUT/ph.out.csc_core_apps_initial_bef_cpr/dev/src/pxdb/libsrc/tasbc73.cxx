#include "tasbccommon.h"
#include "pxdatetime.h"


int tasbc73( struct tKDAUFTRAG* record, int mode )
{
	EXEC SQL BEGIN DECLARE SECTION;
	struct C_KDAUFTRAG* recordp;
	long currentdate;
	EXEC SQL END DECLARE SECTION;

	currentdate = basardatetime_getCurrentDateYYYYMMDD();

    recordp = (struct C_KDAUFTRAG*) record;

    switch (mode)
    {
		case 1: // open cursor			// z.B. Aufruf z.B. durch aaorderclose!
			EXEC SQL DECLARE C1 CURSOR FOR
				select KDAUFTRAG_LISTE from kdauftrag 
				left join kdauftragdebtrel on kdauftrag.kdauftragnr=kdauftragdebtrel.kdauftragnr
				left join cscorderflags on kdauftrag.kdauftragnr=cscorderflags.cscorderno
				where kdauftrag.filialnr = :recordp->FILIALNR
				and kdauftrag.kdauftragstat like :recordp->KDAUFTRAGSTAT
				and ( (kdauftrag.zugrund like :recordp->ZUGRUND) or (kdauftrag.zugrund like '1000%' and kdauftragdebtrel.isreleased=1) )
				and kdauftrag.datumauslieferung <= :currentdate
				and kdauftrag.sendestatus = :recordp->SENDESTATUS
				and cscorderflags.waitforibtpicking = 0;
			EXEC SQL OPEN C1;
			switch( SQLCODE )
			{
				case 0:
					return 0;
				case 100:
					return cDBXR_NOTFOUND;
				default:
					return cDBXR_IOERROR;
			}					

		case 2: // fetch row
			EXEC SQL FETCH C1 into KDAUFTRAG_ZEIGER(recordp);
			switch( SQLCODE )
			{
				case 0:
					return 0;
				case 100:
					return cDBXR_ENDOFDATA;
				default:
					return cDBXR_IOERROR;
			}

		default: // close cursor
			EXEC SQL CLOSE C1;
			return 0;
    }
}

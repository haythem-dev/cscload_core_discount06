#ifndef __STRUCTS_H_
#define __STRUCTS_H_ __STRUCTS_H_

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PROJECT KD2ORDER
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef ESQL_C
	EXEC SQL BEGIN DECLARE SECTION;
#endif

struct S_Counter
{
	unsigned long ulIns;
	unsigned long ulUpd;
	unsigned long ulSel;
    unsigned long ulDel;
    unsigned long ulSerialized;
	
	#ifndef ESQL_C
	S_Counter()
	{
		init();
	};
	void init()
	{
		ulIns        = 0; 
		ulUpd        = 0;
		ulSel        = 0;
        ulDel        = 0;
        ulSerialized = 0;
	};
	#endif
};

#ifdef ESQL_C
	EXEC SQL END DECLARE SECTION;
#endif

#endif /* __STRUCTS_H_ */


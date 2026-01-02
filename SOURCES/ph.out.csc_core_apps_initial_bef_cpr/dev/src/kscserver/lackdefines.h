#ifndef _LACKDEFINES_H
#define _LACKDEFINES_H

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct LACKREASONS
	{
		long lLackReason;
		char cLackCode[1];
		char cLackText[81];
	} stLACKREASONS;

	char *GetLackCodebyReason( long reason, char *Out );

#ifdef __cplusplus
}
#endif

#endif

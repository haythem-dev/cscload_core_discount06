
#ifndef PNAMCODE_INCLUDED
#define PNAMCODE_INCLUDED

/* --- Win32-Code aus IFACode --------------------------------------------------- */

int GetPnamWIN32Code( int IFACode );

void ConvertToWIN32Code( unsigned char *str );

void ConvertUmlaute ( unsigned char *strOrig, char * strConv );

void Upper (unsigned char *s);

#endif /* PNAMCODE_INCLUDED */


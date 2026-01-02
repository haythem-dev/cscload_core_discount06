#ifndef TPULCONVERT_H_INCLUDED
#define TPULCONVERT_H_INCLUDED

/*** DECLARATION **************************************************************/

 void DoubleToString (double source, int vorkomma, int nachkomma);
 void LongToString (long source);
 long CutCentury (long source);
 int Trim (char *s);
 void Upper (char *s);
 void DiscardNotNumerics (char *s);
 int GetUmlaut (int Sign, char *Conv);
 void ConvertUmlaute (unsigned char *strOrig, char *strConv);
 void ConvertDate (long datum, char *s);

 char m_String[30];

#endif /*  TPULCONVERT_H_INCLUDED  */

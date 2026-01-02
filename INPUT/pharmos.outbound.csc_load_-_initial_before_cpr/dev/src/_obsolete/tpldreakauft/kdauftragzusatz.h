#ifndef __PP_KDAUFTRAGZUSATZ_H_
#define __PP_KDAUFTRAGZUSATZ_H_

/******************************************************************************/
/* e:\prj\df\unix\tpldauftr\kdauftragzusatz ***********************************/
/******************************************************************************/

/* Length-Define of KDAUFTRAGZUSATZ *******************************************/

  #define L_KDAUFTRAGZUSATZ_KDAUFTRAGNR 11
  #define L_KDAUFTRAGZUSATZ_KOMMIVARIANTE 6
  #define L_KDAUFTRAGZUSATZ_SKDTOURTEXT 1
  #define L_KDAUFTRAGZUSATZ_SKDVBDRUCKSCANNER 1
  #define L_KDAUFTRAGZUSATZ_SKDHAUSRABATT 1
  #define L_KDAUFTRAGZUSATZ_SKDWERBEFACH 1
  #define L_KDAUFTRAGZUSATZ_SKDZENTRALVERBUND 1
  #define L_KDAUFTRAGZUSATZ_HAUSRABATTPROZ 7
  #define N_KDAUFTRAGZUSATZ_HAUSRABATTPROZ 2
  #define L_KDAUFTRAGZUSATZ_VERBUNDTOUR 6
  #define L_KDAUFTRAGZUSATZ_VERTRIEBSFILIALE 2
  #define L_KDAUFTRAGZUSATZ_BETRIEBSFILIALE 2
  #define L_KDAUFTRAGZUSATZ_ANZAHLRECHSEITEN 11
  #define L_KDAUFTRAGZUSATZ_LAGERAUFNRRECH 11

/* Length/Count-Define of KDAUFTRAGZUSATZ *************************************/

  #define LS_KDAUFTRAGZUSATZ_KDAUFTRAGNR 10 + 1
  #define LS_KDAUFTRAGZUSATZ_KOMMIVARIANTE 5 + 1
  #define LS_KDAUFTRAGZUSATZ_SKDTOURTEXT 1 + 1
  #define LS_KDAUFTRAGZUSATZ_SKDVBDRUCKSCANNER 1 + 1
  #define LS_KDAUFTRAGZUSATZ_SKDHAUSRABATT 1 + 1
  #define LS_KDAUFTRAGZUSATZ_SKDWERBEFACH 1 + 1
  #define LS_KDAUFTRAGZUSATZ_SKDZENTRALVERBUND 1 + 1
  #define LS_KDAUFTRAGZUSATZ_HAUSRABATTPROZ 7 + 2
  #define LS_KDAUFTRAGZUSATZ_VERBUNDTOUR 6 + 1
  #define LS_KDAUFTRAGZUSATZ_VERTRIEBSFILIALE 2 + 1
  #define LS_KDAUFTRAGZUSATZ_BETRIEBSFILIALE 2 + 1
  #define LS_KDAUFTRAGZUSATZ_ANZAHLRECHSEITEN 10 + 1
  #define LS_KDAUFTRAGZUSATZ_LAGERAUFNRRECH 10 + 1

  #define KDAUFTRAGZUSATZKDAUFTRAGNR 0
  #define KDAUFTRAGZUSATZKOMMIVARIANTE 1
  #define KDAUFTRAGZUSATZSKDTOURTEXT 2
  #define KDAUFTRAGZUSATZSKDVBDRUCKSCANNER 3
  #define KDAUFTRAGZUSATZSKDHAUSRABATT 4
  #define KDAUFTRAGZUSATZSKDWERBEFACH 5
  #define KDAUFTRAGZUSATZSKDZENTRALVERBUND 6
  #define KDAUFTRAGZUSATZHAUSRABATTPROZ 7
  #define KDAUFTRAGZUSATZVERBUNDTOUR 8
  #define KDAUFTRAGZUSATZVERTRIEBSFILIALE 9
  #define KDAUFTRAGZUSATZBETRIEBSFILIALE 10
  #define KDAUFTRAGZUSATZANZAHLRECHSEITEN 11
  #define KDAUFTRAGZUSATZLAGERAUFNRRECH 12

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define KDAUFTRAGZUSATZ_H
 #define KDAUFTRAGZUSATZ_ANZ ( sizeof(KDAUFTRAGZUSATZ_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KDAUFTRAGZUSATZ ***********************************************/

 #define KDAUFTRAGZUSATZ_LISTE \
         KDAUFTRAGZUSATZ.KDAUFTRAGNR,\
         KDAUFTRAGZUSATZ.KOMMIVARIANTE,\
         KDAUFTRAGZUSATZ.SKDTOURTEXT,\
         KDAUFTRAGZUSATZ.SKDVBDRUCKSCANNER,\
         KDAUFTRAGZUSATZ.SKDHAUSRABATT,\
         KDAUFTRAGZUSATZ.SKDWERBEFACH,\
         KDAUFTRAGZUSATZ.SKDZENTRALVERBUND,\
         KDAUFTRAGZUSATZ.HAUSRABATTPROZ,\
         KDAUFTRAGZUSATZ.VERBUNDTOUR,\
         KDAUFTRAGZUSATZ.VERTRIEBSFILIALE,\
         KDAUFTRAGZUSATZ.BETRIEBSFILIALE,\
         KDAUFTRAGZUSATZ.ANZAHLRECHSEITEN,\
         KDAUFTRAGZUSATZ.LAGERAUFNRRECH

 #define KDAUFTRAGZUSATZ_LISTE_390 \
         KDAUFTRAGNR,\
         KOMMIVARIANTE,\
         SKDTOURTEXT,\
         SKDVBDRUCKSCANNER,\
         SKDHAUSRABATT,\
         SKDWERBEFACH,\
         SKDZENTRALVERBUND,\
         HAUSRABATTPROZ,\
         VERBUNDTOUR,\
         VERTRIEBSFILIALE,\
         BETRIEBSFILIALE,\
         ANZAHLRECHSEITEN,\
         LAGERAUFNRRECH

 #define KDAUFTRAGZUSATZ_PLISTE \
         "KDAUFTRAGZUSATZ.KDAUFTRAGNR,"\
         "KDAUFTRAGZUSATZ.KOMMIVARIANTE,"\
         "KDAUFTRAGZUSATZ.SKDTOURTEXT,"\
         "KDAUFTRAGZUSATZ.SKDVBDRUCKSCANNER,"\
         "KDAUFTRAGZUSATZ.SKDHAUSRABATT,"\
         "KDAUFTRAGZUSATZ.SKDWERBEFACH,"\
         "KDAUFTRAGZUSATZ.SKDZENTRALVERBUND,"\
         "KDAUFTRAGZUSATZ.HAUSRABATTPROZ,"\
         "KDAUFTRAGZUSATZ.VERBUNDTOUR,"\
         "KDAUFTRAGZUSATZ.VERTRIEBSFILIALE,"\
         "KDAUFTRAGZUSATZ.BETRIEBSFILIALE,"\
         "KDAUFTRAGZUSATZ.ANZAHLRECHSEITEN,"\
         "KDAUFTRAGZUSATZ.LAGERAUFNRRECH"

 #define KDAUFTRAGZUSATZ_PELISTE \
         "KDAUFTRAGNR,"\
         "KOMMIVARIANTE,"\
         "SKDTOURTEXT,"\
         "SKDVBDRUCKSCANNER,"\
         "SKDHAUSRABATT,"\
         "SKDWERBEFACH,"\
         "SKDZENTRALVERBUND,"\
         "HAUSRABATTPROZ,"\
         "VERBUNDTOUR,"\
         "VERTRIEBSFILIALE,"\
         "BETRIEBSFILIALE,"\
         "ANZAHLRECHSEITEN,"\
         "LAGERAUFNRRECH"

 #define KDAUFTRAGZUSATZ_UPDLISTE \
         "KDAUFTRAGNR=?,"\
         "KOMMIVARIANTE=?,"\
         "SKDTOURTEXT=?,"\
         "SKDVBDRUCKSCANNER=?,"\
         "SKDHAUSRABATT=?,"\
         "SKDWERBEFACH=?,"\
         "SKDZENTRALVERBUND=?,"\
         "HAUSRABATTPROZ=?,"\
         "VERBUNDTOUR=?,"\
         "VERTRIEBSFILIALE=?,"\
         "BETRIEBSFILIALE=?,"\
         "ANZAHLRECHSEITEN=?,"\
         "LAGERAUFNRRECH=?"

/* SqlMacros-Define of KDAUFTRAGZUSATZ ****************************************/

 #define KDAUFTRAGZUSATZ_ZEIGER(x) \
         :x->KDAUFTRAGNR,\
         :x->KOMMIVARIANTE,\
         :x->SKDTOURTEXT,\
         :x->SKDVBDRUCKSCANNER,\
         :x->SKDHAUSRABATT,\
         :x->SKDWERBEFACH,\
         :x->SKDZENTRALVERBUND,\
         :x->HAUSRABATTPROZ,\
         :x->VERBUNDTOUR,\
         :x->VERTRIEBSFILIALE,\
         :x->BETRIEBSFILIALE,\
         :x->ANZAHLRECHSEITEN,\
         :x->LAGERAUFNRRECH

 #define KDAUFTRAGZUSATZ_ZEIGERSEL(x) \
         :x->KDAUFTRAGNR,\
         :x->KOMMIVARIANTE,\
         :x->SKDTOURTEXT,\
         :x->SKDVBDRUCKSCANNER,\
         :x->SKDHAUSRABATT,\
         :x->SKDWERBEFACH,\
         :x->SKDZENTRALVERBUND,\
         :x->HAUSRABATTPROZ,\
         :x->VERBUNDTOUR,\
         :x->VERTRIEBSFILIALE,\
         :x->BETRIEBSFILIALE,\
         :x->ANZAHLRECHSEITEN,\
         :x->LAGERAUFNRRECH

 #define KDAUFTRAGZUSATZ_UPDATE(x) \
         KDAUFTRAGZUSATZ.KDAUFTRAGNR=:x->KDAUFTRAGNR,\
         KDAUFTRAGZUSATZ.KOMMIVARIANTE=:x->KOMMIVARIANTE,\
         KDAUFTRAGZUSATZ.SKDTOURTEXT=:x->SKDTOURTEXT,\
         KDAUFTRAGZUSATZ.SKDVBDRUCKSCANNER=:x->SKDVBDRUCKSCANNER,\
         KDAUFTRAGZUSATZ.SKDHAUSRABATT=:x->SKDHAUSRABATT,\
         KDAUFTRAGZUSATZ.SKDWERBEFACH=:x->SKDWERBEFACH,\
         KDAUFTRAGZUSATZ.SKDZENTRALVERBUND=:x->SKDZENTRALVERBUND,\
         KDAUFTRAGZUSATZ.HAUSRABATTPROZ=:x->HAUSRABATTPROZ,\
         KDAUFTRAGZUSATZ.VERBUNDTOUR=:x->VERBUNDTOUR,\
         KDAUFTRAGZUSATZ.VERTRIEBSFILIALE=:x->VERTRIEBSFILIALE,\
         KDAUFTRAGZUSATZ.BETRIEBSFILIALE=:x->BETRIEBSFILIALE,\
         KDAUFTRAGZUSATZ.ANZAHLRECHSEITEN=:x->ANZAHLRECHSEITEN,\
         KDAUFTRAGZUSATZ.LAGERAUFNRRECH=:x->LAGERAUFNRRECH

/* SqlMacros390-Define of KDAUFTRAGZUSATZ *************************************/

 #define KDAUFTRAGZUSATZ_ZEIGER_390 \
         :KDAUFTRAGNR,\
         :KOMMIVARIANTE,\
         :SKDTOURTEXT,\
         :SKDVBDRUCKSCANNER,\
         :SKDHAUSRABATT,\
         :SKDWERBEFACH,\
         :SKDZENTRALVERBUND,\
         :HAUSRABATTPROZ,\
         :VERBUNDTOUR,\
         :VERTRIEBSFILIALE,\
         :BETRIEBSFILIALE,\
         :ANZAHLRECHSEITEN,\
         :LAGERAUFNRRECH

 #define KDAUFTRAGZUSATZ_UPDATE_390 \
         KDAUFTRAGNR=:KDAUFTRAGNR,\
         KOMMIVARIANTE=:KOMMIVARIANTE,\
         SKDTOURTEXT=:SKDTOURTEXT,\
         SKDVBDRUCKSCANNER=:SKDVBDRUCKSCANNER,\
         SKDHAUSRABATT=:SKDHAUSRABATT,\
         SKDWERBEFACH=:SKDWERBEFACH,\
         SKDZENTRALVERBUND=:SKDZENTRALVERBUND,\
         HAUSRABATTPROZ=:HAUSRABATTPROZ,\
         VERBUNDTOUR=:VERBUNDTOUR,\
         VERTRIEBSFILIALE=:VERTRIEBSFILIALE,\
         BETRIEBSFILIALE=:BETRIEBSFILIALE,\
         ANZAHLRECHSEITEN=:ANZAHLRECHSEITEN,\
         LAGERAUFNRRECH=:LAGERAUFNRRECH

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of KDAUFTRAGZUSATZ ****************************************/

 #ifndef TRANSCLASS
 typedef struct N_KDAUFTRAGZUSATZ {
         long KDAUFTRAGNR;
         short KOMMIVARIANTE;
         char SKDTOURTEXT[2];
         char SKDVBDRUCKSCANNER[2];
         char SKDHAUSRABATT[2];
         char SKDWERBEFACH[2];
         char SKDZENTRALVERBUND[2];
         double HAUSRABATTPROZ;
         char VERBUNDTOUR[7];
         char VERTRIEBSFILIALE[3];
         char BETRIEBSFILIALE[3];
         long ANZAHLRECHSEITEN;
         long LAGERAUFNRRECH;
        } kdauftragzusatzS;
 #else /*TRANSCLASS*/
 typedef struct N_KDAUFTRAGZUSATZ {
         long KDAUFTRAGNR;
         short KOMMIVARIANTE;
         char SKDTOURTEXT[2];
         char SKDVBDRUCKSCANNER[2];
         char SKDHAUSRABATT[2];
         char SKDWERBEFACH[2];
         char SKDZENTRALVERBUND[2];
         double HAUSRABATTPROZ;
         char VERBUNDTOUR[7];
         char VERTRIEBSFILIALE[3];
         char BETRIEBSFILIALE[3];
         long ANZAHLRECHSEITEN;
         long LAGERAUFNRRECH;

			bool operator==(const N_KDAUFTRAGZUSATZ& right) const {
			return(
				KDAUFTRAGNR == right.KDAUFTRAGNR &&
				KOMMIVARIANTE == right.KOMMIVARIANTE &&
				!strcmp(SKDTOURTEXT, right.SKDTOURTEXT) &&
				!strcmp(SKDVBDRUCKSCANNER, right.SKDVBDRUCKSCANNER) &&
				!strcmp(SKDHAUSRABATT, right.SKDHAUSRABATT) &&
				!strcmp(SKDWERBEFACH, right.SKDWERBEFACH) &&
				!strcmp(SKDZENTRALVERBUND, right.SKDZENTRALVERBUND) &&
				HAUSRABATTPROZ == right.HAUSRABATTPROZ &&
				!strcmp(VERBUNDTOUR, right.VERBUNDTOUR) &&
				!strcmp(VERTRIEBSFILIALE, right.VERTRIEBSFILIALE) &&
				!strcmp(BETRIEBSFILIALE, right.BETRIEBSFILIALE) &&
				ANZAHLRECHSEITEN == right.ANZAHLRECHSEITEN &&
				LAGERAUFNRRECH == right.LAGERAUFNRRECH
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				KDAUFTRAGNR = 0;
				KOMMIVARIANTE = 0;
				strcpy(SKDTOURTEXT, " " );
				strcpy(SKDVBDRUCKSCANNER, " " );
				strcpy(SKDHAUSRABATT, " " );
				strcpy(SKDWERBEFACH, " " );
				strcpy(SKDZENTRALVERBUND, " " );
				HAUSRABATTPROZ = 0;
				strcpy(VERBUNDTOUR, " " );
				strcpy(VERTRIEBSFILIALE, " " );
				strcpy(BETRIEBSFILIALE, " " );
				ANZAHLRECHSEITEN = 0;
				LAGERAUFNRRECH = 0;
#endif
			}
         } kdauftragzusatzS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KDAUFTRAGZUSATZ ***********************************/

 struct S_KDAUFTRAGZUSATZ {
         char KDAUFTRAGNR[11];
         char KOMMIVARIANTE[7];
         char SKDTOURTEXT[1 + 1];
         char SKDVBDRUCKSCANNER[1 + 1];
         char SKDHAUSRABATT[1 + 1];
         char SKDWERBEFACH[1 + 1];
         char SKDZENTRALVERBUND[1 + 1];
         char HAUSRABATTPROZ[7 + 2];
         char VERBUNDTOUR[6 + 1];
         char VERTRIEBSFILIALE[2 + 1];
         char BETRIEBSFILIALE[2 + 1];
         char ANZAHLRECHSEITEN[11];
         char LAGERAUFNRRECH[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KDAUFTRAGZUSATZ ******************/

 struct O_KDAUFTRAGZUSATZ {
         char KDAUFTRAGNR[11];
         char KOMMIVARIANTE[7];
         char SKDTOURTEXT[1];
         char SKDVBDRUCKSCANNER[1];
         char SKDHAUSRABATT[1];
         char SKDWERBEFACH[1];
         char SKDZENTRALVERBUND[1];
         char HAUSRABATTPROZ[7];
         char VERBUNDTOUR[6];
         char VERTRIEBSFILIALE[2];
         char BETRIEBSFILIALE[2];
         char ANZAHLRECHSEITEN[11];
         char LAGERAUFNRRECH[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of KDAUFTRAGZUSATZ ******************************/

 struct C_KDAUFTRAGZUSATZ {
         long KDAUFTRAGNR;
         short KOMMIVARIANTE;
         char SKDTOURTEXT;
         char SKDVBDRUCKSCANNER;
         char SKDHAUSRABATT;
         char SKDWERBEFACH;
         char SKDZENTRALVERBUND;
         double HAUSRABATTPROZ;
         char VERBUNDTOUR[7];
         char VERTRIEBSFILIALE[3];
         char BETRIEBSFILIALE[3];
         long ANZAHLRECHSEITEN;
         long LAGERAUFNRRECH;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of KDAUFTRAGZUSATZ ****************************/

 struct I_KDAUFTRAGZUSATZ {
         short KDAUFTRAGNR;
         short KOMMIVARIANTE;
         short SKDTOURTEXT;
         short SKDVBDRUCKSCANNER;
         short SKDHAUSRABATT;
         short SKDWERBEFACH;
         short SKDZENTRALVERBUND;
         short HAUSRABATTPROZ;
         short VERBUNDTOUR;
         short VERTRIEBSFILIALE;
         short BETRIEBSFILIALE;
         short ANZAHLRECHSEITEN;
         short LAGERAUFNRRECH;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KDAUFTRAGZUSATZ *************************************/

#if defined (BUF_DESC)
 static struct buf_desc KDAUFTRAGZUSATZ_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_D, 7, 2 },
   { TYP_C, 6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KDAUFTRAGZUSATZ_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_D, 7, 2 },
   { TYP_C, 6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 2, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of KDAUFTRAGZUSATZ *******************************/

 #define KDAUFTRAGZUSATZ_S390 \
         long KDAUFTRAGNR; \
         short KOMMIVARIANTE; \
         char SKDTOURTEXT; \
         char SKDVBDRUCKSCANNER; \
         char SKDHAUSRABATT; \
         char SKDWERBEFACH; \
         char SKDZENTRALVERBUND; \
         double HAUSRABATTPROZ; \
         char VERBUNDTOUR[7]; \
         char VERTRIEBSFILIALE[3]; \
         char BETRIEBSFILIALE[3]; \
         long ANZAHLRECHSEITEN; \
         long LAGERAUFNRRECH; \



/* Copy-Function Struct to single Data KDAUFTRAGZUSATZ ************************/

 #define KDAUFTRAGZUSATZ_S390_COPY_TO_SINGLE(_x_) \
         KDAUFTRAGNR=_x_->KDAUFTRAGNR;\
         KOMMIVARIANTE=_x_->KOMMIVARIANTE;\
         SKDTOURTEXT=_x_->SKDTOURTEXT;\
         SKDVBDRUCKSCANNER=_x_->SKDVBDRUCKSCANNER;\
         SKDHAUSRABATT=_x_->SKDHAUSRABATT;\
         SKDWERBEFACH=_x_->SKDWERBEFACH;\
         SKDZENTRALVERBUND=_x_->SKDZENTRALVERBUND;\
         HAUSRABATTPROZ=_x_->HAUSRABATTPROZ;\
          strcpy(VERBUNDTOUR,_x_->VERBUNDTOUR);\
          strcpy(VERTRIEBSFILIALE,_x_->VERTRIEBSFILIALE);\
          strcpy(BETRIEBSFILIALE,_x_->BETRIEBSFILIALE);\
         ANZAHLRECHSEITEN=_x_->ANZAHLRECHSEITEN;\
         LAGERAUFNRRECH=_x_->LAGERAUFNRRECH;\

 #define KDAUFTRAGZUSATZ_S390_COPY_TO_STRUCT(_x_) \
          _x_->KDAUFTRAGNR=KDAUFTRAGNR;\
          _x_->KOMMIVARIANTE=KOMMIVARIANTE;\
          _x_->SKDTOURTEXT=SKDTOURTEXT;\
          _x_->SKDVBDRUCKSCANNER=SKDVBDRUCKSCANNER;\
          _x_->SKDHAUSRABATT=SKDHAUSRABATT;\
          _x_->SKDWERBEFACH=SKDWERBEFACH;\
          _x_->SKDZENTRALVERBUND=SKDZENTRALVERBUND;\
          _x_->HAUSRABATTPROZ=HAUSRABATTPROZ;\
          strcpy(_x_->VERBUNDTOUR,VERBUNDTOUR);\
          strcpy(_x_->VERTRIEBSFILIALE,VERTRIEBSFILIALE);\
          strcpy(_x_->BETRIEBSFILIALE,BETRIEBSFILIALE);\
          _x_->ANZAHLRECHSEITEN=ANZAHLRECHSEITEN;\
          _x_->LAGERAUFNRRECH=LAGERAUFNRRECH;\



/* FunctionNumber-Define of kdauftragzusatz ***********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kdauftragzusatz *******************************/


#endif

/* C++ Class ******************************************************************/

#ifdef TRANSCLASS
#include<vector>
using namespace std;

#ifndef __VIRTUAL_DADE_CLASS__
#define __VIRTUAL_DADE_CLASS__

class ppDadeVirtual
{
	public:
		virtual const int SelList(int FetchRel = 1,int pos=0) = 0;
		virtual const int SelListHist(int FetchRel = 1,int pos=0) = 0;
		virtual const int SelListFuture(int FetchRel = 1,int pos=0) = 0;
		virtual const int Load(int pos=0) = 0;
 		virtual const int Delete(int pos=0) = 0;
		virtual const int Save(int pos=0) = 0;
};
#endif

class CKDAUFTRAGZUSATZ : public ppDadeVirtual
{
	//data members
	public:
		kdauftragzusatzS s;
		int rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<kdauftragzusatzS> *pl; // pointer to class list

	//functions
	public:

		const int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		const bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		const bool 		SetList(const unsigned int i) {	if (GetSize() <= i)	return false; vector<kdauftragzusatzS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		const bool 		InsList() { if ( !pl ) pl = new vector<kdauftragzusatzS>; Strip(s); kdauftragzusatzS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		const bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<kdauftragzusatzS>::iterator itPtr = pl->begin() + i; if ( itPtr ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<kdauftragzusatzS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<kdauftragzusatzS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		const long		GetKdauftragnr() const	{ return s.KDAUFTRAGNR; }
		const short		GetKommivariante() const	{ return s.KOMMIVARIANTE; }
		const char		GetSkdtourtext() const	{ return s.SKDTOURTEXT[0]; }
		const char		GetSkdvbdruckscanner() const	{ return s.SKDVBDRUCKSCANNER[0]; }
		const char		GetSkdhausrabatt() const	{ return s.SKDHAUSRABATT[0]; }
		const char		GetSkdwerbefach() const	{ return s.SKDWERBEFACH[0]; }
		const char		GetSkdzentralverbund() const	{ return s.SKDZENTRALVERBUND[0]; }
		const double		GetHausrabattproz() const	{ return s.HAUSRABATTPROZ; }
		const char*	GetVerbundtour(ppString& t) const 	{ t = s.VERBUNDTOUR; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetVertriebsfiliale(ppString& t) const 	{ t = s.VERTRIEBSFILIALE; t.erasespace(ppString::END); return t.c_str(); }
		const char*	GetBetriebsfiliale(ppString& t) const 	{ t = s.BETRIEBSFILIALE; t.erasespace(ppString::END); return t.c_str(); }
		const long		GetAnzahlrechseiten() const	{ return s.ANZAHLRECHSEITEN; }
		const long		GetLageraufnrrech() const	{ return s.LAGERAUFNRRECH; }
		const kdauftragzusatzS& GetStruct() const { return s; }
		void 		SetKdauftragnr(long t) { s.KDAUFTRAGNR = t; }
		void 		SetKommivariante(short t) { s.KOMMIVARIANTE = t; }
		void 		SetSkdtourtext(char t) { s.SKDTOURTEXT[0] = t; s.SKDTOURTEXT[1] = '\0';}
		void 		SetSkdvbdruckscanner(char t) { s.SKDVBDRUCKSCANNER[0] = t; s.SKDVBDRUCKSCANNER[1] = '\0';}
		void 		SetSkdhausrabatt(char t) { s.SKDHAUSRABATT[0] = t; s.SKDHAUSRABATT[1] = '\0';}
		void 		SetSkdwerbefach(char t) { s.SKDWERBEFACH[0] = t; s.SKDWERBEFACH[1] = '\0';}
		void 		SetSkdzentralverbund(char t) { s.SKDZENTRALVERBUND[0] = t; s.SKDZENTRALVERBUND[1] = '\0';}
		void 		SetHausrabattproz(double t) { s.HAUSRABATTPROZ = t; }
		void 		SetVerbundtour(const ppString& t) { ppGStrCopy(s.VERBUNDTOUR,t.c_str() ,L_KDAUFTRAGZUSATZ_VERBUNDTOUR); }
		void 		SetVertriebsfiliale(const ppString& t) { ppGStrCopy(s.VERTRIEBSFILIALE,t.c_str() ,L_KDAUFTRAGZUSATZ_VERTRIEBSFILIALE); }
		void 		SetBetriebsfiliale(const ppString& t) { ppGStrCopy(s.BETRIEBSFILIALE,t.c_str() ,L_KDAUFTRAGZUSATZ_BETRIEBSFILIALE); }
		void 		SetAnzahlrechseiten(long t) { s.ANZAHLRECHSEITEN = t; }
		void 		SetLageraufnrrech(long t) { s.LAGERAUFNRRECH = t; }
		void 		SetStruct(const kdauftragzusatzS& t) { s = t; }

	//virtual functions
	public:

		const int	Load(int pos=0) { return 1; }
		const int	Save(int pos=0) { return 1; }
		const int	Delete(int pos=0) { return 1; }
		const int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		const int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		const int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CKDAUFTRAGZUSATZ()  //constructor
		{
			::buf_default((void *)&s,KDAUFTRAGZUSATZ_BES,KDAUFTRAGZUSATZ_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		~CKDAUFTRAGZUSATZ()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, KDAUFTRAGZUSATZ_BES, KDAUFTRAGZUSATZ_ANZ );
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			FehlerBehandlung( -1, "False function number!" );
			return -1;
		}

	private:

		void Strip(N_KDAUFTRAGZUSATZ& d)
		{
#ifdef WIN32
			ppGStripLast(d.VERBUNDTOUR);
			ppGStripLast(d.VERTRIEBSFILIALE);
			ppGStripLast(d.BETRIEBSFILIALE);
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc=::ServerNr(pos, FncNr, (void *)&s,KDAUFTRAGZUSATZ_BES,KDAUFTRAGZUSATZ_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of KDAUFTRAGZUSATZ **************************************/

 #define KDAUFTRAGZUSATZ_CREATE(x) exec sql create table x (\
         KDAUFTRAGNR integer default 0 not null,\
         KOMMIVARIANTE smallint default 0 not null,\
         SKDTOURTEXT char(1) default " " not null,\
         SKDVBDRUCKSCANNER char(1) default " " not null,\
         SKDHAUSRABATT char(1) default " " not null,\
         SKDWERBEFACH char(1) default " " not null,\
         SKDZENTRALVERBUND char(1) default " " not null,\
         HAUSRABATTPROZ decimal(7,2) default 0 not null,\
         VERBUNDTOUR char(6) default " " not null,\
         VERTRIEBSFILIALE char(2) default " " not null,\
         BETRIEBSFILIALE char(2) default " " not null,\
         ANZAHLRECHSEITEN integer default 0 not null,\
         LAGERAUFNRRECH integer default 0 not null) in ksc extent size 498 lock mode row;



/* CreateIndexStatement of KDAUFTRAGZUSATZ ************************************/

 #define KDAUFTRAGZUSATZ_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_kdauftragzusat_1 on _X_(\
              kdauftragnr ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KDAUFTRAGZUSATZ ************************************/

 #define KDAUFTRAGZUSATZ_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_kdauftragzusat_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

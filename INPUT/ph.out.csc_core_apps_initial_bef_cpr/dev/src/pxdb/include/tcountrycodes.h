#ifndef __PP_COUNTRYCODES_H_
#define __PP_COUNTRYCODES_H_

/******************************************************************************/
/* v:\CountryCodes ************************************************************/
/******************************************************************************/

/* Length-Define of COUNTRYCODES **********************************************/

  #define L_COUNTRYCODES_BRANCHNO 6
  #define L_COUNTRYCODES_INFOCODE 2
  #define L_COUNTRYCODES_ARTICLEACTIV 1
  #define L_COUNTRYCODES_AUXDELIVERY 1
  #define L_COUNTRYCODES_SERACODE 20
  #define L_COUNTRYCODES_PRINTCODE 30
  #define L_COUNTRYCODES_XMLCODE 5
  #define L_COUNTRYCODES_XMLTEXT 100

/* Length/Count-Define of COUNTRYCODES ****************************************/

  #define LS_COUNTRYCODES_BRANCHNO 5 + 1
  #define LS_COUNTRYCODES_INFOCODE 2 + 1
  #define LS_COUNTRYCODES_ARTICLEACTIV 1 + 1
  #define LS_COUNTRYCODES_AUXDELIVERY 1 + 1
  #define LS_COUNTRYCODES_SERACODE 20 + 1
  #define LS_COUNTRYCODES_PRINTCODE 30 + 1
  #define LS_COUNTRYCODES_XMLCODE 5 + 1
  #define LS_COUNTRYCODES_XMLTEXT 100 + 1

  #define COUNTRYCODESBRANCHNO 0
  #define COUNTRYCODESINFOCODE 1
  #define COUNTRYCODESARTICLEACTIV 2
  #define COUNTRYCODESAUXDELIVERY 3
  #define COUNTRYCODESSERACODE 4
  #define COUNTRYCODESPRINTCODE 5
  #define COUNTRYCODESXMLCODE 6
  #define COUNTRYCODESXMLTEXT 7

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define COUNTRYCODES_H
 #define COUNTRYCODES_ANZ ( sizeof(COUNTRYCODES_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of COUNTRYCODES **************************************************/

 #define COUNTRYCODES_LISTE \
         COUNTRYCODES.BRANCHNO,\
         COUNTRYCODES.INFOCODE,\
         COUNTRYCODES.ARTICLEACTIV,\
         COUNTRYCODES.AUXDELIVERY,\
         COUNTRYCODES.SERACODE,\
         COUNTRYCODES.PRINTCODE,\
         COUNTRYCODES.XMLCODE,\
         COUNTRYCODES.XMLTEXT

 #define COUNTRYCODES_LISTE_390 \
         BRANCHNO,\
         INFOCODE,\
         ARTICLEACTIV,\
         AUXDELIVERY,\
         SERACODE,\
         PRINTCODE,\
         XMLCODE,\
         XMLTEXT

 #define COUNTRYCODES_PLISTE \
         "COUNTRYCODES.BRANCHNO,"\
         "COUNTRYCODES.INFOCODE,"\
         "COUNTRYCODES.ARTICLEACTIV,"\
         "COUNTRYCODES.AUXDELIVERY,"\
         "COUNTRYCODES.SERACODE,"\
         "COUNTRYCODES.PRINTCODE,"\
         "COUNTRYCODES.XMLCODE,"\
         "COUNTRYCODES.XMLTEXT"

 #define COUNTRYCODES_PELISTE \
         "BRANCHNO,"\
         "INFOCODE,"\
         "ARTICLEACTIV,"\
         "AUXDELIVERY,"\
         "SERACODE,"\
         "PRINTCODE,"\
         "XMLCODE,"\
         "XMLTEXT"

 #define COUNTRYCODES_UPDLISTE \
         "BRANCHNO=?,"\
         "INFOCODE=?,"\
         "ARTICLEACTIV=?,"\
         "AUXDELIVERY=?,"\
         "SERACODE=?,"\
         "PRINTCODE=?,"\
         "XMLCODE=?,"\
         "XMLTEXT=?"

/* SqlMacros-Define of COUNTRYCODES *******************************************/

 #define COUNTRYCODES_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->INFOCODE,\
         :x->ARTICLEACTIV,\
         :x->AUXDELIVERY,\
         :x->SERACODE,\
         :x->PRINTCODE,\
         :x->XMLCODE,\
         :x->XMLTEXT

 #define COUNTRYCODES_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->INFOCODE,\
         :x->ARTICLEACTIV,\
         :x->AUXDELIVERY,\
         :x->SERACODE,\
         :x->PRINTCODE,\
         :x->XMLCODE,\
         :x->XMLTEXT

 #define COUNTRYCODES_UPDATE(x) \
         COUNTRYCODES.BRANCHNO=:x->BRANCHNO,\
         COUNTRYCODES.INFOCODE=:x->INFOCODE,\
         COUNTRYCODES.ARTICLEACTIV=:x->ARTICLEACTIV,\
         COUNTRYCODES.AUXDELIVERY=:x->AUXDELIVERY,\
         COUNTRYCODES.SERACODE=:x->SERACODE,\
         COUNTRYCODES.PRINTCODE=:x->PRINTCODE,\
         COUNTRYCODES.XMLCODE=:x->XMLCODE,\
         COUNTRYCODES.XMLTEXT=:x->XMLTEXT

/* SqlMacros390-Define of COUNTRYCODES ****************************************/

 #define COUNTRYCODES_ZEIGER_390 \
         :BRANCHNO,\
         :INFOCODE,\
         :ARTICLEACTIV,\
         :AUXDELIVERY,\
         :SERACODE,\
         :PRINTCODE,\
         :XMLCODE,\
         :XMLTEXT

 #define COUNTRYCODES_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         INFOCODE=:INFOCODE,\
         ARTICLEACTIV=:ARTICLEACTIV,\
         AUXDELIVERY=:AUXDELIVERY,\
         SERACODE=:SERACODE,\
         PRINTCODE=:PRINTCODE,\
         XMLCODE=:XMLCODE,\
         XMLTEXT=:XMLTEXT

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of COUNTRYCODES *******************************************/

 #ifndef TRANSCLASS
 typedef struct N_COUNTRYCODES {
         short BRANCHNO;
         char INFOCODE[3];
         char ARTICLEACTIV[2];
         char AUXDELIVERY[2];
         char SERACODE[21];
         char PRINTCODE[31];
         char XMLCODE[6];
         char XMLTEXT[101];
        } countrycodesS;
 #else /*TRANSCLASS*/
 typedef struct N_COUNTRYCODES {
         short BRANCHNO;
         char INFOCODE[3];
         char ARTICLEACTIV[2];
         char AUXDELIVERY[2];
         char SERACODE[21];
         char PRINTCODE[31];
         char XMLCODE[6];
         char XMLTEXT[101];

                        bool operator==(const N_COUNTRYCODES& right) const {
                        return(
                                BRANCHNO == right.BRANCHNO &&
                                !strcmp(INFOCODE, right.INFOCODE) &&
                                !strcmp(ARTICLEACTIV, right.ARTICLEACTIV) &&
                                !strcmp(AUXDELIVERY, right.AUXDELIVERY) &&
                                !strcmp(SERACODE, right.SERACODE) &&
                                !strcmp(PRINTCODE, right.PRINTCODE) &&
                                !strcmp(XMLCODE, right.XMLCODE) &&
                                !strcmp(XMLTEXT, right.XMLTEXT)
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                BRANCHNO = 0;
                                strcpy(INFOCODE, " " );
                                strcpy(ARTICLEACTIV, " " );
                                strcpy(AUXDELIVERY, " " );
                                strcpy(SERACODE, " " );
                                strcpy(PRINTCODE, " " );
                                strcpy(XMLCODE, " " );
                                strcpy(XMLTEXT, " " );
#endif
                        }
         } countrycodesS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of COUNTRYCODES **************************************/

 struct S_COUNTRYCODES {
         char BRANCHNO[7];
         char INFOCODE[2 + 1];
         char ARTICLEACTIV[1 + 1];
         char AUXDELIVERY[1 + 1];
         char SERACODE[20 + 1];
         char PRINTCODE[30 + 1];
         char XMLCODE[5 + 1];
         char XMLTEXT[100 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of COUNTRYCODES *********************/

 struct O_COUNTRYCODES {
         char BRANCHNO[7];
         char INFOCODE[2];
         char ARTICLEACTIV[1];
         char AUXDELIVERY[1];
         char SERACODE[20];
         char PRINTCODE[30];
         char XMLCODE[5];
         char XMLTEXT[100];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of COUNTRYCODES ********************************/

 struct C_COUNTRYCODES {
         short BRANCHNO;
         char INFOCODE[3];
         char ARTICLEACTIV;
         char AUXDELIVERY;
         char SERACODE[21];
         char PRINTCODE[31];
         char XMLCODE[6];
         char XMLTEXT[101];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of COUNTRYCODES ******************************/

 struct I_COUNTRYCODES {
         short BRANCHNO;
         short INFOCODE;
         short ARTICLEACTIV;
         short AUXDELIVERY;
         short SERACODE;
         short PRINTCODE;
         short XMLCODE;
         short XMLTEXT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of COUNTRYCODES ****************************************/

#if defined (BUF_DESC)
 static struct buf_desc COUNTRYCODES_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 5, 0 },
   { TYP_C, 100, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc COUNTRYCODES_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 30, 0 },
   { TYP_C, 5, 0 },
   { TYP_C, 100, 0 },
 };
#endif

/* description for datatypes of COUNTRYCODES **********************************/

 #define COUNTRYCODES_S390 \
         short BRANCHNO; \
         char INFOCODE[3]; \
         char ARTICLEACTIV; \
         char AUXDELIVERY; \
         char SERACODE[21]; \
         char PRINTCODE[31]; \
         char XMLCODE[6]; \
         char XMLTEXT[101]; \



/* Copy-Function Struct to single Data COUNTRYCODES ***************************/

 #define COUNTRYCODES_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
          strcpy(INFOCODE,_x_->INFOCODE);\
         ARTICLEACTIV=_x_->ARTICLEACTIV;\
         AUXDELIVERY=_x_->AUXDELIVERY;\
          strcpy(SERACODE,_x_->SERACODE);\
          strcpy(PRINTCODE,_x_->PRINTCODE);\
          strcpy(XMLCODE,_x_->XMLCODE);\
          strcpy(XMLTEXT,_x_->XMLTEXT);\

 #define COUNTRYCODES_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          strcpy(_x_->INFOCODE,INFOCODE);\
          _x_->ARTICLEACTIV=ARTICLEACTIV;\
          _x_->AUXDELIVERY=AUXDELIVERY;\
          strcpy(_x_->SERACODE,SERACODE);\
          strcpy(_x_->PRINTCODE,PRINTCODE);\
          strcpy(_x_->XMLCODE,XMLCODE);\
          strcpy(_x_->XMLTEXT,XMLTEXT);\



/* FunctionNumber-Define of CountryCodes **************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of CountryCodes **********************************/


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
                virtual    ~ppDadeVirtual() {};
                virtual int SelList      (int FetchRel = 1, int pos = 0) = 0;
                virtual int SelListHist  (int FetchRel = 1, int pos = 0) = 0;
                virtual int SelListFuture(int FetchRel = 1, int pos = 0) = 0;
                virtual int Load         (int pos = 0                  ) = 0;
                virtual int Delete       (int pos = 0                  ) = 0;
                virtual int Save         (int pos = 0                  ) = 0;
};
#endif

class CCOUNTRYCODES : public ppDadeVirtual
{
        //data members
        public:
                countrycodesS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<countrycodesS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<countrycodesS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<countrycodesS>; Strip(s); countrycodesS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<countrycodesS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<countrycodesS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<countrycodesS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetBranchno() const     { return s.BRANCHNO; }
                const char*     GetInfocode(ppString& t) const  { t = s.INFOCODE; t.erasespace(ppString::END); return t.c_str(); }
                char            GetArticleactiv() const { return s.ARTICLEACTIV[0]; }
                char            GetAuxdelivery() const  { return s.AUXDELIVERY[0]; }
                const char*     GetSeracode(ppString& t) const  { t = s.SERACODE; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetPrintcode(ppString& t) const         { t = s.PRINTCODE; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetXmlcode(ppString& t) const   { t = s.XMLCODE; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetXmltext(ppString& t) const   { t = s.XMLTEXT; t.erasespace(ppString::END); return t.c_str(); }
                const countrycodesS& GetStruct() const { return s; }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetInfocode(const ppString& t) { ppGStrCopy(s.INFOCODE,t.c_str() ,L_COUNTRYCODES_INFOCODE); }
                void            SetArticleactiv(char t) { s.ARTICLEACTIV[0] = t; s.ARTICLEACTIV[1] = '\0';}
                void            SetAuxdelivery(char t) { s.AUXDELIVERY[0] = t; s.AUXDELIVERY[1] = '\0';}
                void            SetSeracode(const ppString& t) { ppGStrCopy(s.SERACODE,t.c_str() ,L_COUNTRYCODES_SERACODE); }
                void            SetPrintcode(const ppString& t) { ppGStrCopy(s.PRINTCODE,t.c_str() ,L_COUNTRYCODES_PRINTCODE); }
                void            SetXmlcode(const ppString& t) { ppGStrCopy(s.XMLCODE,t.c_str() ,L_COUNTRYCODES_XMLCODE); }
                void            SetXmltext(const ppString& t) { ppGStrCopy(s.XMLTEXT,t.c_str() ,L_COUNTRYCODES_XMLTEXT); }
                void            SetStruct(const countrycodesS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CCOUNTRYCODES()  //constructor
                {
                        ::buf_default((void *)&s, COUNTRYCODES_BES, COUNTRYCODES_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CCOUNTRYCODES()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, COUNTRYCODES_BES, COUNTRYCODES_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, COUNTRYCODES_BES, COUNTRYCODES_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, COUNTRYCODES_BES, COUNTRYCODES_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_COUNTRYCODES& d)
                {
#ifdef WIN32
                        ppGStripLast(d.INFOCODE);
                        ppGStripLast(d.SERACODE);
                        ppGStripLast(d.PRINTCODE);
                        ppGStripLast(d.XMLCODE);
                        ppGStripLast(d.XMLTEXT);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, COUNTRYCODES_BES, COUNTRYCODES_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of COUNTRYCODES *****************************************/

 #define COUNTRYCODES_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         INFOCODE char(2) default " " not null,\
         ARTICLEACTIV char(1) default " " not null,\
         AUXDELIVERY char(1) default " " not null,\
         SERACODE char(20) default " " not null,\
         PRINTCODE char(30) default " " not null,\
         XMLCODE char(5) default " " not null,\
         XMLTEXT char(100) default " " not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of COUNTRYCODES ***************************************/

 #define COUNTRYCODES_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_countrycode_1 on _X_(\
              BranchNo,\
              InfoCode ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of COUNTRYCODES ***************************************/

 #define COUNTRYCODES_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_countrycode_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

#ifndef __PP_KUNDEKONDI_H_
#define __PP_KUNDEKONDI_H_

/******************************************************************************/
/* v:\nordat\kundekondi *******************************************************/
/******************************************************************************/

/* Length-Define of KUNDEKONDI ************************************************/

  #define L_KUNDEKONDI_IDFNR 11
  #define L_KUNDEKONDI_BUENDELRUNDUNGPROZ 3
  #define N_KUNDEKONDI_BUENDELRUNDUNGPROZ 1
  #define L_KUNDEKONDI_MENGENATRABASIS 11
  #define L_KUNDEKONDI_MENGENATRA 11
  #define L_KUNDEKONDI_SKDNATRARABATT04 1
  #define L_KUNDEKONDI_VERTRIEBSZENTRUMNR 6
  #define L_KUNDEKONDI_KUNDENNR 11
  #define L_KUNDEKONDI_TAGAUTOVALUTA 6
  #define L_KUNDEKONDI_VALUTATAGEMAX 6

/* Length/Count-Define of KUNDEKONDI ******************************************/

  #define LS_KUNDEKONDI_IDFNR 10 + 1
  #define LS_KUNDEKONDI_BUENDELRUNDUNGPROZ 3 + 2
  #define LS_KUNDEKONDI_MENGENATRABASIS 10 + 1
  #define LS_KUNDEKONDI_MENGENATRA 10 + 1
  #define LS_KUNDEKONDI_SKDNATRARABATT04 1 + 1
  #define LS_KUNDEKONDI_VERTRIEBSZENTRUMNR 5 + 1
  #define LS_KUNDEKONDI_KUNDENNR 10 + 1
  #define LS_KUNDEKONDI_TAGAUTOVALUTA 5 + 1
  #define LS_KUNDEKONDI_VALUTATAGEMAX 5 + 1

  #define KUNDEKONDIIDFNR 0
  #define KUNDEKONDIBUENDELRUNDUNGPROZ 1
  #define KUNDEKONDIMENGENATRABASIS 2
  #define KUNDEKONDIMENGENATRA 3
  #define KUNDEKONDISKDNATRARABATT04 4
  #define KUNDEKONDIVERTRIEBSZENTRUMNR 5
  #define KUNDEKONDIKUNDENNR 6
  #define KUNDEKONDITAGAUTOVALUTA 7
  #define KUNDEKONDIVALUTATAGEMAX 8

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define KUNDEKONDI_H
 #define KUNDEKONDI_ANZ ( sizeof(KUNDEKONDI_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of KUNDEKONDI ****************************************************/

 #define KUNDEKONDI_LISTE \
         KUNDEKONDI.IDFNR,\
         KUNDEKONDI.BUENDELRUNDUNGPROZ,\
         KUNDEKONDI.MENGENATRABASIS,\
         KUNDEKONDI.MENGENATRA,\
         KUNDEKONDI.SKDNATRARABATT04,\
         KUNDEKONDI.VERTRIEBSZENTRUMNR,\
         KUNDEKONDI.KUNDENNR,\
         KUNDEKONDI.TAGAUTOVALUTA,\
         KUNDEKONDI.VALUTATAGEMAX

 #define KUNDEKONDI_LISTE_390 \
         IDFNR,\
         BUENDELRUNDUNGPROZ,\
         MENGENATRABASIS,\
         MENGENATRA,\
         SKDNATRARABATT04,\
         VERTRIEBSZENTRUMNR,\
         KUNDENNR,\
         TAGAUTOVALUTA,\
         VALUTATAGEMAX

 #define KUNDEKONDI_PLISTE \
         "KUNDEKONDI.IDFNR,"\
         "KUNDEKONDI.BUENDELRUNDUNGPROZ,"\
         "KUNDEKONDI.MENGENATRABASIS,"\
         "KUNDEKONDI.MENGENATRA,"\
         "KUNDEKONDI.SKDNATRARABATT04,"\
         "KUNDEKONDI.VERTRIEBSZENTRUMNR,"\
         "KUNDEKONDI.KUNDENNR,"\
         "KUNDEKONDI.TAGAUTOVALUTA,"\
         "KUNDEKONDI.VALUTATAGEMAX"

 #define KUNDEKONDI_PELISTE \
         "IDFNR,"\
         "BUENDELRUNDUNGPROZ,"\
         "MENGENATRABASIS,"\
         "MENGENATRA,"\
         "SKDNATRARABATT04,"\
         "VERTRIEBSZENTRUMNR,"\
         "KUNDENNR,"\
         "TAGAUTOVALUTA,"\
         "VALUTATAGEMAX"

 #define KUNDEKONDI_UPDLISTE \
         "IDFNR=?,"\
         "BUENDELRUNDUNGPROZ=?,"\
         "MENGENATRABASIS=?,"\
         "MENGENATRA=?,"\
         "SKDNATRARABATT04=?,"\
         "VERTRIEBSZENTRUMNR=?,"\
         "KUNDENNR=?,"\
         "TAGAUTOVALUTA=?,"\
         "VALUTATAGEMAX=?"

/* SqlMacros-Define of KUNDEKONDI *********************************************/

 #define KUNDEKONDI_ZEIGER(x) \
         :x->IDFNR,\
         :x->BUENDELRUNDUNGPROZ,\
         :x->MENGENATRABASIS,\
         :x->MENGENATRA,\
         :x->SKDNATRARABATT04,\
         :x->VERTRIEBSZENTRUMNR,\
         :x->KUNDENNR,\
         :x->TAGAUTOVALUTA,\
         :x->VALUTATAGEMAX

 #define KUNDEKONDI_ZEIGERSEL(x) \
         :x->IDFNR,\
         :x->BUENDELRUNDUNGPROZ,\
         :x->MENGENATRABASIS,\
         :x->MENGENATRA,\
         :x->SKDNATRARABATT04,\
         :x->VERTRIEBSZENTRUMNR,\
         :x->KUNDENNR,\
         :x->TAGAUTOVALUTA,\
         :x->VALUTATAGEMAX

 #define KUNDEKONDI_UPDATE(x) \
         KUNDEKONDI.IDFNR=:x->IDFNR,\
         KUNDEKONDI.BUENDELRUNDUNGPROZ=:x->BUENDELRUNDUNGPROZ,\
         KUNDEKONDI.MENGENATRABASIS=:x->MENGENATRABASIS,\
         KUNDEKONDI.MENGENATRA=:x->MENGENATRA,\
         KUNDEKONDI.SKDNATRARABATT04=:x->SKDNATRARABATT04,\
         KUNDEKONDI.VERTRIEBSZENTRUMNR=:x->VERTRIEBSZENTRUMNR,\
         KUNDEKONDI.KUNDENNR=:x->KUNDENNR,\
         KUNDEKONDI.TAGAUTOVALUTA=:x->TAGAUTOVALUTA,\
         KUNDEKONDI.VALUTATAGEMAX=:x->VALUTATAGEMAX

/* SqlMacros390-Define of KUNDEKONDI ******************************************/

 #define KUNDEKONDI_ZEIGER_390 \
         :IDFNR,\
         :BUENDELRUNDUNGPROZ,\
         :MENGENATRABASIS,\
         :MENGENATRA,\
         :SKDNATRARABATT04,\
         :VERTRIEBSZENTRUMNR,\
         :KUNDENNR,\
         :TAGAUTOVALUTA,\
         :VALUTATAGEMAX

 #define KUNDEKONDI_UPDATE_390 \
         IDFNR=:IDFNR,\
         BUENDELRUNDUNGPROZ=:BUENDELRUNDUNGPROZ,\
         MENGENATRABASIS=:MENGENATRABASIS,\
         MENGENATRA=:MENGENATRA,\
         SKDNATRARABATT04=:SKDNATRARABATT04,\
         VERTRIEBSZENTRUMNR=:VERTRIEBSZENTRUMNR,\
         KUNDENNR=:KUNDENNR,\
         TAGAUTOVALUTA=:TAGAUTOVALUTA,\
         VALUTATAGEMAX=:VALUTATAGEMAX

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of KUNDEKONDI *********************************************/

 #ifndef TRANSCLASS
 typedef struct N_KUNDEKONDI {
         long IDFNR;
         double BUENDELRUNDUNGPROZ;
         long MENGENATRABASIS;
         long MENGENATRA;
         char SKDNATRARABATT04[2];
         short VERTRIEBSZENTRUMNR;
         long KUNDENNR;
         short TAGAUTOVALUTA;
         short VALUTATAGEMAX;
        } kundekondiS;
 #else /*TRANSCLASS*/
 typedef struct N_KUNDEKONDI {
         long IDFNR;
         double BUENDELRUNDUNGPROZ;
         long MENGENATRABASIS;
         long MENGENATRA;
         char SKDNATRARABATT04[2];
         short VERTRIEBSZENTRUMNR;
         long KUNDENNR;
         short TAGAUTOVALUTA;
         short VALUTATAGEMAX;

                        bool operator==(const N_KUNDEKONDI& right) const {
                        return(
                                IDFNR == right.IDFNR &&
                                BUENDELRUNDUNGPROZ == right.BUENDELRUNDUNGPROZ &&
                                MENGENATRABASIS == right.MENGENATRABASIS &&
                                MENGENATRA == right.MENGENATRA &&
                                !strcmp(SKDNATRARABATT04, right.SKDNATRARABATT04) &&
                                VERTRIEBSZENTRUMNR == right.VERTRIEBSZENTRUMNR &&
                                KUNDENNR == right.KUNDENNR &&
                                TAGAUTOVALUTA == right.TAGAUTOVALUTA &&
                                VALUTATAGEMAX == right.VALUTATAGEMAX
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                IDFNR = 0;
                                BUENDELRUNDUNGPROZ = 0;
                                MENGENATRABASIS = 0;
                                MENGENATRA = 0;
                                strcpy(SKDNATRARABATT04, " " );
                                VERTRIEBSZENTRUMNR = 0;
                                KUNDENNR = 0;
                                TAGAUTOVALUTA = 0;
                                VALUTATAGEMAX = 0;
#endif
                        }
         } kundekondiS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of KUNDEKONDI ****************************************/

 struct S_KUNDEKONDI {
         char IDFNR[11];
         char BUENDELRUNDUNGPROZ[3 + 2];
         char MENGENATRABASIS[11];
         char MENGENATRA[11];
         char SKDNATRARABATT04[1 + 1];
         char VERTRIEBSZENTRUMNR[7];
         char KUNDENNR[11];
         char TAGAUTOVALUTA[7];
         char VALUTATAGEMAX[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of KUNDEKONDI ***********************/

 struct O_KUNDEKONDI {
         char IDFNR[11];
         char BUENDELRUNDUNGPROZ[3];
         char MENGENATRABASIS[11];
         char MENGENATRA[11];
         char SKDNATRARABATT04[1];
         char VERTRIEBSZENTRUMNR[7];
         char KUNDENNR[11];
         char TAGAUTOVALUTA[7];
         char VALUTATAGEMAX[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of KUNDEKONDI ***********************************/

 struct C_KUNDEKONDI {
         long IDFNR;
         double BUENDELRUNDUNGPROZ;
         long MENGENATRABASIS;
         long MENGENATRA;
         char SKDNATRARABATT04;
         short VERTRIEBSZENTRUMNR;
         long KUNDENNR;
         short TAGAUTOVALUTA;
         short VALUTATAGEMAX;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of KUNDEKONDI *********************************/

 struct I_KUNDEKONDI {
         short IDFNR;
         short BUENDELRUNDUNGPROZ;
         short MENGENATRABASIS;
         short MENGENATRA;
         short SKDNATRARABATT04;
         short VERTRIEBSZENTRUMNR;
         short KUNDENNR;
         short TAGAUTOVALUTA;
         short VALUTATAGEMAX;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of KUNDEKONDI ******************************************/

#if defined (BUF_DESC)
 static struct buf_desc KUNDEKONDI_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_D, 3, 1 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc KUNDEKONDI_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_D, 3, 1 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of KUNDEKONDI ************************************/

 #define KUNDEKONDI_S390 \
         long IDFNR; \
         double BUENDELRUNDUNGPROZ; \
         long MENGENATRABASIS; \
         long MENGENATRA; \
         char SKDNATRARABATT04; \
         short VERTRIEBSZENTRUMNR; \
         long KUNDENNR; \
         short TAGAUTOVALUTA; \
         short VALUTATAGEMAX; \



/* Copy-Function Struct to single Data KUNDEKONDI *****************************/

 #define KUNDEKONDI_S390_COPY_TO_SINGLE(_x_) \
         IDFNR=_x_->IDFNR;\
         BUENDELRUNDUNGPROZ=_x_->BUENDELRUNDUNGPROZ;\
         MENGENATRABASIS=_x_->MENGENATRABASIS;\
         MENGENATRA=_x_->MENGENATRA;\
         SKDNATRARABATT04=_x_->SKDNATRARABATT04;\
         VERTRIEBSZENTRUMNR=_x_->VERTRIEBSZENTRUMNR;\
         KUNDENNR=_x_->KUNDENNR;\
         TAGAUTOVALUTA=_x_->TAGAUTOVALUTA;\
         VALUTATAGEMAX=_x_->VALUTATAGEMAX;\

 #define KUNDEKONDI_S390_COPY_TO_STRUCT(_x_) \
          _x_->IDFNR=IDFNR;\
          _x_->BUENDELRUNDUNGPROZ=BUENDELRUNDUNGPROZ;\
          _x_->MENGENATRABASIS=MENGENATRABASIS;\
          _x_->MENGENATRA=MENGENATRA;\
          _x_->SKDNATRARABATT04=SKDNATRARABATT04;\
          _x_->VERTRIEBSZENTRUMNR=VERTRIEBSZENTRUMNR;\
          _x_->KUNDENNR=KUNDENNR;\
          _x_->TAGAUTOVALUTA=TAGAUTOVALUTA;\
          _x_->VALUTATAGEMAX=VALUTATAGEMAX;\



/* FunctionNumber-Define of kundekondi ****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of kundekondi ************************************/


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
                virtual int SelList(int FetchRel = 1,int pos=0) = 0;
                virtual int SelListHist(int FetchRel = 1,int pos=0) = 0;
                virtual int SelListFuture(int FetchRel = 1,int pos=0) = 0;
                virtual int Load(int pos=0) = 0;
                virtual int Delete(int pos=0) = 0;
                virtual int Save(int pos=0) = 0;
};
#endif

class CKUNDEKONDI : public ppDadeVirtual
{
        //data members
        public:
                kundekondiS s;
                int rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<kundekondiS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<kundekondiS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<kundekondiS>; Strip(s); kundekondiS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<kundekondiS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<kundekondiS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<kundekondiS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetIdfnr() const        { return s.IDFNR; }
                double          GetBuendelrundungproz() const   { return s.BUENDELRUNDUNGPROZ; }
                long            GetMengenatrabasis() const      { return s.MENGENATRABASIS; }
                long            GetMengenatra() const   { return s.MENGENATRA; }
                char            GetSkdnatrarabatt04() const     { return s.SKDNATRARABATT04[0]; }
                short           GetVertriebszentrumnr() const   { return s.VERTRIEBSZENTRUMNR; }
                long            GetKundennr() const     { return s.KUNDENNR; }
                short           GetTagautovaluta() const        { return s.TAGAUTOVALUTA; }
                short           GetValutatagemax() const        { return s.VALUTATAGEMAX; }
                const kundekondiS& GetStruct() const { return s; }
                void            SetIdfnr(long t) { s.IDFNR = t; }
                void            SetBuendelrundungproz(double t) { s.BUENDELRUNDUNGPROZ = t; }
                void            SetMengenatrabasis(long t) { s.MENGENATRABASIS = t; }
                void            SetMengenatra(long t) { s.MENGENATRA = t; }
                void            SetSkdnatrarabatt04(char t) { s.SKDNATRARABATT04[0] = t; s.SKDNATRARABATT04[1] = '\0';}
                void            SetVertriebszentrumnr(short t) { s.VERTRIEBSZENTRUMNR = t; }
                void            SetKundennr(long t) { s.KUNDENNR = t; }
                void            SetTagautovaluta(short t) { s.TAGAUTOVALUTA = t; }
                void            SetValutatagemax(short t) { s.VALUTATAGEMAX = t; }
                void            SetStruct(const kundekondiS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CKUNDEKONDI()  //constructor
                {
                        ::buf_default((void *)&s,KUNDEKONDI_BES,KUNDEKONDI_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CKUNDEKONDI()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, KUNDEKONDI_BES, KUNDEKONDI_ANZ );
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc=::ServerNr(pos, fkt_nr, (void *)&s,KUNDEKONDI_BES,KUNDEKONDI_ANZ, error_msg);
                        #else
                        rc=::Server(fkt_nr, (void *)&s,KUNDEKONDI_BES,KUNDEKONDI_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_KUNDEKONDI& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc=::ServerNr(pos, FncNr, (void *)&s,KUNDEKONDI_BES,KUNDEKONDI_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of KUNDEKONDI *******************************************/

 #define KUNDEKONDI_CREATE(x) exec sql create table x (\
         IDFNR integer default 0 not null,\
         BUENDELRUNDUNGPROZ decimal(3,1) default 0 not null,\
         MENGENATRABASIS integer default 0 not null,\
         MENGENATRA integer default 0 not null,\
         SKDNATRARABATT04 char(1) default " " not null,\
         VERTRIEBSZENTRUMNR smallint default 0 not null,\
         KUNDENNR integer default 0 not null,\
         TAGAUTOVALUTA smallint default 0 not null,\
         VALUTATAGEMAX smallint default 0 not null) in KscCustomer extent size 392 next size 40 lock mode row;



/* CreateIndexStatement of KUNDEKONDI *****************************************/

 #define KUNDEKONDI_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_kundekondi_2 on _X_(\
              VertriebszentrumNr,\
              KundenNr ) in KscCustomerIdx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index kundekondix on _X_(\
              idfnr ) in KscCustomerIdx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of KUNDEKONDI *****************************************/

 #define KUNDEKONDI_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_kundekondi_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index kundekondix;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

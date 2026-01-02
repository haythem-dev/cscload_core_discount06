#ifndef __PP_PARAMETER_H_
#define __PP_PARAMETER_H_

/******************************************************************************/
/* u:\nordat\Parameter ********************************************************/
/******************************************************************************/

/* Length-Define of PARAMETER *************************************************/

  #define L_PARAMETER_FILIALNR 6
  #define L_PARAMETER_PROGRAMMNAME 15
  #define L_PARAMETER_ZWECK 20
  #define L_PARAMETER_PARAMETERNAME 20
  #define L_PARAMETER_AUSPRAEGUNG 254
  #define L_PARAMETER_WERT 11

/* Length/Count-Define of PARAMETER *******************************************/

  #define LS_PARAMETER_FILIALNR 5 + 1
  #define LS_PARAMETER_PROGRAMMNAME 15 + 1
  #define LS_PARAMETER_ZWECK 20 + 1
  #define LS_PARAMETER_PARAMETERNAME 20 + 1
  #define LS_PARAMETER_AUSPRAEGUNG 254 + 1
  #define LS_PARAMETER_WERT 10 + 1

  #define PARAMETERFILIALNR 0
  #define PARAMETERPROGRAMMNAME 1
  #define PARAMETERZWECK 2
  #define PARAMETERPARAMETERNAME 3
  #define PARAMETERAUSPRAEGUNG 4
  #define PARAMETERWERT 5

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define PARAMETER_H
 #define PARAMETER_ANZ ( sizeof(PARAMETER_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of PARAMETER *****************************************************/

 #define PARAMETER_LISTE \
         PARAMETER.FILIALNR,\
         PARAMETER.PROGRAMMNAME,\
         PARAMETER.ZWECK,\
         PARAMETER.PARAMETERNAME,\
         PARAMETER.AUSPRAEGUNG,\
         PARAMETER.WERT

 #define PARAMETER_LISTE_390 \
         FILIALNR,\
         PROGRAMMNAME,\
         ZWECK,\
         PARAMETERNAME,\
         AUSPRAEGUNG,\
         WERT

 #define PARAMETER_PLISTE \
         "PARAMETER.FILIALNR,"\
         "PARAMETER.PROGRAMMNAME,"\
         "PARAMETER.ZWECK,"\
         "PARAMETER.PARAMETERNAME,"\
         "PARAMETER.AUSPRAEGUNG,"\
         "PARAMETER.WERT"

 #define PARAMETER_PELISTE \
         "FILIALNR,"\
         "PROGRAMMNAME,"\
         "ZWECK,"\
         "PARAMETERNAME,"\
         "AUSPRAEGUNG,"\
         "WERT"

 #define PARAMETER_UPDLISTE \
         "FILIALNR=?,"\
         "PROGRAMMNAME=?,"\
         "ZWECK=?,"\
         "PARAMETERNAME=?,"\
         "AUSPRAEGUNG=?,"\
         "WERT=?"

/* SqlMacros-Define of PARAMETER **********************************************/

 #define PARAMETER_ZEIGER(x) \
         :x->FILIALNR,\
         :x->PROGRAMMNAME,\
         :x->ZWECK,\
         :x->PARAMETERNAME,\
         :x->AUSPRAEGUNG,\
         :x->WERT

 #define PARAMETER_ZEIGERSEL(x) \
         :x->FILIALNR,\
         :x->PROGRAMMNAME,\
         :x->ZWECK,\
         :x->PARAMETERNAME,\
         :x->AUSPRAEGUNG,\
         :x->WERT

 #define PARAMETER_UPDATE(x) \
         PARAMETER.FILIALNR=:x->FILIALNR,\
         PARAMETER.PROGRAMMNAME=:x->PROGRAMMNAME,\
         PARAMETER.ZWECK=:x->ZWECK,\
         PARAMETER.PARAMETERNAME=:x->PARAMETERNAME,\
         PARAMETER.AUSPRAEGUNG=:x->AUSPRAEGUNG,\
         PARAMETER.WERT=:x->WERT

/* SqlMacros390-Define of PARAMETER *******************************************/

 #define PARAMETER_ZEIGER_390 \
         :FILIALNR,\
         :PROGRAMMNAME,\
         :ZWECK,\
         :PARAMETERNAME,\
         :AUSPRAEGUNG,\
         :WERT

 #define PARAMETER_UPDATE_390 \
         FILIALNR=:FILIALNR,\
         PROGRAMMNAME=:PROGRAMMNAME,\
         ZWECK=:ZWECK,\
         PARAMETERNAME=:PARAMETERNAME,\
         AUSPRAEGUNG=:AUSPRAEGUNG,\
         WERT=:WERT

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of PARAMETER **********************************************/

 #ifndef TRANSCLASS
 typedef struct N_PARAMETER {
         short FILIALNR;
         char PROGRAMMNAME[16];
         char ZWECK[21];
         char PARAMETERNAME[21];
         char AUSPRAEGUNG[255];
         long WERT;
        } parameterS;
 #else /*TRANSCLASS*/
 typedef struct N_PARAMETER {
         short FILIALNR;
         char PROGRAMMNAME[16];
         char ZWECK[21];
         char PARAMETERNAME[21];
         char AUSPRAEGUNG[255];
         long WERT;

                        bool operator==(const N_PARAMETER& right) const {
                        return(
                                FILIALNR == right.FILIALNR &&
                                !strcmp(PROGRAMMNAME, right.PROGRAMMNAME) &&
                                !strcmp(ZWECK, right.ZWECK) &&
                                !strcmp(PARAMETERNAME, right.PARAMETERNAME) &&
                                !strcmp(AUSPRAEGUNG, right.AUSPRAEGUNG) &&
                                WERT == right.WERT
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                FILIALNR = 0;
                                strcpy(PROGRAMMNAME, " " );
                                strcpy(ZWECK, " " );
                                strcpy(PARAMETERNAME, " " );
                                strcpy(AUSPRAEGUNG, " " );
                                WERT = 0;
#endif
                        }
         } parameterS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of PARAMETER *****************************************/

 struct S_PARAMETER {
         char FILIALNR[7];
         char PROGRAMMNAME[15 + 1];
         char ZWECK[20 + 1];
         char PARAMETERNAME[20 + 1];
         char AUSPRAEGUNG[254 + 1];
         char WERT[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of PARAMETER ************************/

 struct O_PARAMETER {
         char FILIALNR[7];
         char PROGRAMMNAME[15];
         char ZWECK[20];
         char PARAMETERNAME[20];
         char AUSPRAEGUNG[254];
         char WERT[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of PARAMETER ************************************/

 struct C_PARAMETER {
         short FILIALNR;
         char PROGRAMMNAME[16];
         char ZWECK[21];
         char PARAMETERNAME[21];
         char AUSPRAEGUNG[255];
         long WERT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of PARAMETER **********************************/

 struct I_PARAMETER {
         short FILIALNR;
         short PROGRAMMNAME;
         short ZWECK;
         short PARAMETERNAME;
         short AUSPRAEGUNG;
         short WERT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of PARAMETER *******************************************/

#if defined (BUF_DESC)
 static struct buf_desc PARAMETER_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 254, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc PARAMETER_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_C, 15, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 20, 0 },
   { TYP_C, 254, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of PARAMETER *************************************/

 #define PARAMETER_S390 \
         short FILIALNR; \
         char PROGRAMMNAME[16]; \
         char ZWECK[21]; \
         char PARAMETERNAME[21]; \
         char AUSPRAEGUNG[255]; \
         long WERT; \



/* Copy-Function Struct to single Data PARAMETER ******************************/

 #define PARAMETER_S390_COPY_TO_SINGLE(_x_) \
         FILIALNR=_x_->FILIALNR;\
          strcpy(PROGRAMMNAME,_x_->PROGRAMMNAME);\
          strcpy(ZWECK,_x_->ZWECK);\
          strcpy(PARAMETERNAME,_x_->PARAMETERNAME);\
          strcpy(AUSPRAEGUNG,_x_->AUSPRAEGUNG);\
         WERT=_x_->WERT;\

 #define PARAMETER_S390_COPY_TO_STRUCT(_x_) \
          _x_->FILIALNR=FILIALNR;\
          strcpy(_x_->PROGRAMMNAME,PROGRAMMNAME);\
          strcpy(_x_->ZWECK,ZWECK);\
          strcpy(_x_->PARAMETERNAME,PARAMETERNAME);\
          strcpy(_x_->AUSPRAEGUNG,AUSPRAEGUNG);\
          _x_->WERT=WERT;\



/* FunctionNumber-Define of Parameter *****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of Parameter *************************************/


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

class CPARAMETER : public ppDadeVirtual
{
        //data members
        public:
                parameterS s;
                int rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<parameterS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<parameterS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<parameterS>; Strip(s); parameterS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<parameterS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<parameterS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<parameterS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetFilialnr() const     { return s.FILIALNR; }
                const char*     GetProgrammname(ppString& t) const      { t = s.PROGRAMMNAME; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetZweck(ppString& t) const     { t = s.ZWECK; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetParametername(ppString& t) const     { t = s.PARAMETERNAME; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetAuspraegung(ppString& t) const       { t = s.AUSPRAEGUNG; t.erasespace(ppString::END); return t.c_str(); }
                long            GetWert() const { return s.WERT; }
                const parameterS& GetStruct() const { return s; }
                void            SetFilialnr(short t) { s.FILIALNR = t; }
                void            SetProgrammname(const ppString& t) { ppGStrCopy(s.PROGRAMMNAME,t.c_str() ,L_PARAMETER_PROGRAMMNAME); }
                void            SetZweck(const ppString& t) { ppGStrCopy(s.ZWECK,t.c_str() ,L_PARAMETER_ZWECK); }
                void            SetParametername(const ppString& t) { ppGStrCopy(s.PARAMETERNAME,t.c_str() ,L_PARAMETER_PARAMETERNAME); }
                void            SetAuspraegung(const ppString& t) { ppGStrCopy(s.AUSPRAEGUNG,t.c_str() ,L_PARAMETER_AUSPRAEGUNG); }
                void            SetWert(long t) { s.WERT = t; }
                void            SetStruct(const parameterS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CPARAMETER()  //constructor
                {
                        ::buf_default((void *)&s,PARAMETER_BES,PARAMETER_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CPARAMETER()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, PARAMETER_BES, PARAMETER_ANZ );
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc=::ServerNr(pos, fkt_nr, (void *)&s,PARAMETER_BES,PARAMETER_ANZ, error_msg);
                        #else
                        rc=::Server(fkt_nr, (void *)&s,PARAMETER_BES,PARAMETER_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_PARAMETER& d)
                {
#ifdef WIN32
                        ppGStripLast(d.PROGRAMMNAME);
                        ppGStripLast(d.ZWECK);
                        ppGStripLast(d.PARAMETERNAME);
                        ppGStripLast(d.AUSPRAEGUNG);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc=::ServerNr(pos, FncNr, (void *)&s,PARAMETER_BES,PARAMETER_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of PARAMETER ********************************************/

 #define PARAMETER_CREATE(x) exec sql create table x (\
         FILIALNR smallint default 0 not null,\
         PROGRAMMNAME char(15) default " " not null,\
         ZWECK char(20) default " " not null,\
         PARAMETERNAME char(20) default " " not null,\
         AUSPRAEGUNG varchar(254,0) default " " not null,\
         WERT integer default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of PARAMETER ******************************************/

 #define PARAMETER_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create   index i_parameter_1 on _X_(\
              filialnr,\
              ProgrammName ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of PARAMETER ******************************************/

 #define PARAMETER_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_parameter_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

#ifndef __PP_FEIERTAG_H_
#define __PP_FEIERTAG_H_

/******************************************************************************/
/* v:\nordat\feiertage ********************************************************/
/******************************************************************************/

/* Length-Define of FEIERTAG *************************************************/

  #define L_FEIERTAG_FILIALNR 6
  #define L_FEIERTAG_MODUS 6
  #define L_FEIERTAG_TAG 6
  #define L_FEIERTAG_VON_JAHR 6
  #define L_FEIERTAG_BIS_JAHR 6

/* Length/Count-Define of FEIERTAG *******************************************/

  #define LS_FEIERTAG_FILIALNR 5 + 1
  #define LS_FEIERTAG_MODUS 5 + 1
  #define LS_FEIERTAG_TAG 5 + 1
  #define LS_FEIERTAG_VON_JAHR 5 + 1
  #define LS_FEIERTAG_BIS_JAHR 5 + 1

  #define FEIERTAGFILIALNR 0
  #define FEIERTAGMODUS 1
  #define FEIERTAGTAG 2
  #define FEIERTAGVON_JAHR 3
  #define FEIERTAGBIS_JAHR 4

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define FEIERTAG_H
 #define FEIERTAG_ANZ ( sizeof(FEIERTAG_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of FEIERTAG *****************************************************/

 #define FEIERTAG_LISTE \
         FEIERTAG.FILIALNR,\
         FEIERTAG.MODUS,\
         FEIERTAG.TAG,\
         FEIERTAG.VON_JAHR,\
         FEIERTAG.BIS_JAHR

 #define FEIERTAG_LISTE_390 \
         FILIALNR,\
         MODUS,\
         TAG,\
         VON_JAHR,\
         BIS_JAHR

 #define FEIERTAG_PLISTE \
         "FEIERTAG.FILIALNR,"\
         "FEIERTAG.MODUS,"\
         "FEIERTAG.TAG,"\
         "FEIERTAG.VON_JAHR,"\
         "FEIERTAG.BIS_JAHR"

 #define FEIERTAG_PELISTE \
         "FILIALNR,"\
         "MODUS,"\
         "TAG,"\
         "VON_JAHR,"\
         "BIS_JAHR"

 #define FEIERTAG_UPDLISTE \
         "FILIALNR=?,"\
         "MODUS=?,"\
         "TAG=?,"\
         "VON_JAHR=?,"\
         "BIS_JAHR=?"

/* SqlMacros-Define of FEIERTAG **********************************************/

 #define FEIERTAG_ZEIGER(x) \
         :x->FILIALNR,\
         :x->MODUS,\
         :x->TAG,\
         :x->VON_JAHR,\
         :x->BIS_JAHR

 #define FEIERTAG_ZEIGERSEL(x) \
         :x->FILIALNR,\
         :x->MODUS,\
         :x->TAG,\
         :x->VON_JAHR,\
         :x->BIS_JAHR

 #define FEIERTAG_UPDATE(x) \
         FEIERTAG.FILIALNR=:x->FILIALNR,\
         FEIERTAG.MODUS=:x->MODUS,\
         FEIERTAG.TAG=:x->TAG,\
         FEIERTAG.VON_JAHR=:x->VON_JAHR,\
         FEIERTAG.BIS_JAHR=:x->BIS_JAHR

/* SqlMacros390-Define of FEIERTAG *******************************************/

 #define FEIERTAG_ZEIGER_390 \
         :FILIALNR,\
         :MODUS,\
         :TAG,\
         :VON_JAHR,\
         :BIS_JAHR

 #define FEIERTAG_UPDATE_390 \
         FILIALNR=:FILIALNR,\
         MODUS=:MODUS,\
         TAG=:TAG,\
         VON_JAHR=:VON_JAHR,\
         BIS_JAHR=:BIS_JAHR

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of FEIERTAG **********************************************/

 #ifndef TRANSCLASS
 typedef struct N_FEIERTAG {
         short FILIALNR;
         short MODUS;
         short TAG;
         short VON_JAHR;
         short BIS_JAHR;
        } feiertageS;
 #else /*TRANSCLASS*/
 typedef struct N_FEIERTAG {
         short FILIALNR;
         short MODUS;
         short TAG;
         short VON_JAHR;
         short BIS_JAHR;

                        bool operator==(const N_FEIERTAG& right) const {
                        return(
                                FILIALNR == right.FILIALNR &&
                                MODUS == right.MODUS &&
                                TAG == right.TAG &&
                                VON_JAHR == right.VON_JAHR &&
                                BIS_JAHR == right.BIS_JAHR
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                FILIALNR = 0;
                                MODUS = 0;
                                TAG = 0;
                                VON_JAHR = 0;
                                BIS_JAHR = 0;
#endif
                        }
         } feiertageS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of FEIERTAG *****************************************/

 struct S_FEIERTAG {
         char FILIALNR[7];
         char MODUS[7];
         char TAG[7];
         char VON_JAHR[7];
         char BIS_JAHR[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of FEIERTAG ************************/

 struct O_FEIERTAG {
         char FILIALNR[7];
         char MODUS[7];
         char TAG[7];
         char VON_JAHR[7];
         char BIS_JAHR[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of FEIERTAG ************************************/

 struct C_FEIERTAG {
         short FILIALNR;
         short MODUS;
         short TAG;
         short VON_JAHR;
         short BIS_JAHR;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of FEIERTAG **********************************/

 struct I_FEIERTAG {
         short FILIALNR;
         short MODUS;
         short TAG;
         short VON_JAHR;
         short BIS_JAHR;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of FEIERTAG *******************************************/

#if defined (BUF_DESC)
 static struct buf_desc FEIERTAG_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc FEIERTAG_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of FEIERTAG *************************************/

 #define FEIERTAG_S390 \
         short FILIALNR; \
         short MODUS; \
         short TAG; \
         short VON_JAHR; \
         short BIS_JAHR; \



/* Copy-Function Struct to single Data FEIERTAG ******************************/

 #define FEIERTAG_S390_COPY_TO_SINGLE(_x_) \
         FILIALNR=_x_->FILIALNR;\
         MODUS=_x_->MODUS;\
         TAG=_x_->TAG;\
         VON_JAHR=_x_->VON_JAHR;\
         BIS_JAHR=_x_->BIS_JAHR;\

 #define FEIERTAG_S390_COPY_TO_STRUCT(_x_) \
          _x_->FILIALNR=FILIALNR;\
          _x_->MODUS=MODUS;\
          _x_->TAG=TAG;\
          _x_->VON_JAHR=VON_JAHR;\
          _x_->BIS_JAHR=BIS_JAHR;\



/* FunctionNumber-Define of feiertage *****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of feiertage *************************************/


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

class CFEIERTAG : public ppDadeVirtual
{
        //data members
        public:
                feiertageS s;
                int rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<feiertageS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<feiertageS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<feiertageS>; Strip(s); feiertageS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<feiertageS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<feiertageS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<feiertageS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetFilialnr() const     { return s.FILIALNR; }
                short           GetModus() const        { return s.MODUS; }
                short           GetTag() const  { return s.TAG; }
                short           GetVon_jahr() const     { return s.VON_JAHR; }
                short           GetBis_jahr() const     { return s.BIS_JAHR; }
                const feiertageS& GetStruct() const { return s; }
                void            SetFilialnr(short t) { s.FILIALNR = t; }
                void            SetModus(short t) { s.MODUS = t; }
                void            SetTag(short t) { s.TAG = t; }
                void            SetVon_jahr(short t) { s.VON_JAHR = t; }
                void            SetBis_jahr(short t) { s.BIS_JAHR = t; }
                void            SetStruct(const feiertageS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CFEIERTAG()  //constructor
                {
                        ::buf_default((void *)&s,FEIERTAG_BES,FEIERTAG_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CFEIERTAG()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, FEIERTAG_BES, FEIERTAG_ANZ );
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc=::ServerNr(pos, fkt_nr, (void *)&s,FEIERTAG_BES,FEIERTAG_ANZ, error_msg);
                        #else
                        rc=::Server(fkt_nr, (void *)&s,FEIERTAG_BES,FEIERTAG_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_FEIERTAG& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc=::ServerNr(pos, FncNr, (void *)&s,FEIERTAG_BES,FEIERTAG_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of FEIERTAG ********************************************/

 #define FEIERTAG_CREATE(x) exec sql create table x (\
         FILIALNR smallint default 0 not null,\
         MODUS smallint default 0 not null,\
         TAG smallint default 0 not null,\
         VON_JAHR smallint default 0 not null,\
         BIS_JAHR smallint default 0 not null) extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of FEIERTAG ******************************************/

 #define FEIERTAG_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_feiertag_1 on _X_(\
              filialnr,\
              modus,\
              tag );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of FEIERTAG ******************************************/

 #define FEIERTAG_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_feiertag_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

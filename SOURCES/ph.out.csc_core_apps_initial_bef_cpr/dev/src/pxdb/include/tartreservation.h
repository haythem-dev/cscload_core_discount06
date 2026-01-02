#ifndef __PP_ARTICLERESERVATION_H_
#define __PP_ARTICLERESERVATION_H_

/******************************************************************************/
/* v:\nordat\ArticleReservation ***********************************************/
/******************************************************************************/

/* Length-Define of ARTICLERESERVATION ****************************************/

  #define L_ARTICLERESERVATION_BRANCHNO 6
  #define L_ARTICLERESERVATION_PHARMACYGROUPID 3
  #define L_ARTICLERESERVATION_ARTICLENO 11
  #define L_ARTICLERESERVATION_RESERVTYPE 6
  #define L_ARTICLERESERVATION_MAXQTY 11
  #define L_ARTICLERESERVATION_RESERVEDQTY 11
  #define L_ARTICLERESERVATION_RESERVEPCT 6

/* Length/Count-Define of ARTICLERESERVATION **********************************/

  #define LS_ARTICLERESERVATION_BRANCHNO 5 + 1
  #define LS_ARTICLERESERVATION_PHARMACYGROUPID 3 + 1
  #define LS_ARTICLERESERVATION_ARTICLENO 10 + 1
  #define LS_ARTICLERESERVATION_RESERVTYPE 5 + 1
  #define LS_ARTICLERESERVATION_MAXQTY 10 + 1
  #define LS_ARTICLERESERVATION_RESERVEDQTY 10 + 1
  #define LS_ARTICLERESERVATION_RESERVEPCT 5 + 1

  #define ARTICLERESERVATIONBRANCHNO 0
  #define ARTICLERESERVATIONPHARMACYGROUPID 1
  #define ARTICLERESERVATIONARTICLENO 2
  #define ARTICLERESERVATIONRESERVTYPE 3
  #define ARTICLERESERVATIONMAXQTY 4
  #define ARTICLERESERVATIONRESERVEDQTY 5
  #define ARTICLERESERVATIONRESERVEPCT 6

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ARTICLERESERVATION_H
 #define ARTICLERESERVATION_ANZ ( sizeof(ARTICLERESERVATION_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTICLERESERVATION ********************************************/

 #define ARTICLERESERVATION_LISTE \
         ARTICLERESERVATION.BRANCHNO,\
         ARTICLERESERVATION.PHARMACYGROUPID,\
         ARTICLERESERVATION.ARTICLENO,\
         ARTICLERESERVATION.RESERVTYPE,\
         ARTICLERESERVATION.MAXQTY,\
         ARTICLERESERVATION.RESERVEDQTY,\
         ARTICLERESERVATION.RESERVEPCT

 #define ARTICLERESERVATION_LISTE_390 \
         BRANCHNO,\
         PHARMACYGROUPID,\
         ARTICLENO,\
         RESERVTYPE,\
         MAXQTY,\
         RESERVEDQTY,\
         RESERVEPCT

 #define ARTICLERESERVATION_PLISTE \
         "ARTICLERESERVATION.BRANCHNO,"\
         "ARTICLERESERVATION.PHARMACYGROUPID,"\
         "ARTICLERESERVATION.ARTICLENO,"\
         "ARTICLERESERVATION.RESERVTYPE,"\
         "ARTICLERESERVATION.MAXQTY,"\
         "ARTICLERESERVATION.RESERVEDQTY,"\
         "ARTICLERESERVATION.RESERVEPCT"

 #define ARTICLERESERVATION_PELISTE \
         "BRANCHNO,"\
         "PHARMACYGROUPID,"\
         "ARTICLENO,"\
         "RESERVTYPE,"\
         "MAXQTY,"\
         "RESERVEDQTY,"\
         "RESERVEPCT"

 #define ARTICLERESERVATION_UPDLISTE \
         "BRANCHNO=?,"\
         "PHARMACYGROUPID=?,"\
         "ARTICLENO=?,"\
         "RESERVTYPE=?,"\
         "MAXQTY=?,"\
         "RESERVEDQTY=?,"\
         "RESERVEPCT=?"

/* SqlMacros-Define of ARTICLERESERVATION *************************************/

 #define ARTICLERESERVATION_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->PHARMACYGROUPID,\
         :x->ARTICLENO,\
         :x->RESERVTYPE,\
         :x->MAXQTY,\
         :x->RESERVEDQTY,\
         :x->RESERVEPCT

 #define ARTICLERESERVATION_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->PHARMACYGROUPID,\
         :x->ARTICLENO,\
         :x->RESERVTYPE,\
         :x->MAXQTY,\
         :x->RESERVEDQTY,\
         :x->RESERVEPCT

 #define ARTICLERESERVATION_UPDATE(x) \
         ARTICLERESERVATION.BRANCHNO=:x->BRANCHNO,\
         ARTICLERESERVATION.PHARMACYGROUPID=:x->PHARMACYGROUPID,\
         ARTICLERESERVATION.ARTICLENO=:x->ARTICLENO,\
         ARTICLERESERVATION.RESERVTYPE=:x->RESERVTYPE,\
         ARTICLERESERVATION.MAXQTY=:x->MAXQTY,\
         ARTICLERESERVATION.RESERVEDQTY=:x->RESERVEDQTY,\
         ARTICLERESERVATION.RESERVEPCT=:x->RESERVEPCT

/* SqlMacros390-Define of ARTICLERESERVATION **********************************/

 #define ARTICLERESERVATION_ZEIGER_390 \
         :BRANCHNO,\
         :PHARMACYGROUPID,\
         :ARTICLENO,\
         :RESERVTYPE,\
         :MAXQTY,\
         :RESERVEDQTY,\
         :RESERVEPCT

 #define ARTICLERESERVATION_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         PHARMACYGROUPID=:PHARMACYGROUPID,\
         ARTICLENO=:ARTICLENO,\
         RESERVTYPE=:RESERVTYPE,\
         MAXQTY=:MAXQTY,\
         RESERVEDQTY=:RESERVEDQTY,\
         RESERVEPCT=:RESERVEPCT

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ARTICLERESERVATION *************************************/

 #ifndef TRANSCLASS
 typedef struct N_ARTICLERESERVATION {
         short BRANCHNO;
         char PHARMACYGROUPID[4];
         long ARTICLENO;
         short RESERVTYPE;
         long MAXQTY;
         long RESERVEDQTY;
         short RESERVEPCT;
         long FETCH_REL;
        } articlereservationS;
 #else /*TRANSCLASS*/
 typedef struct N_ARTICLERESERVATION {
         short BRANCHNO;
         char PHARMACYGROUPID[4];
         long ARTICLENO;
         short RESERVTYPE;
         long MAXQTY;
         long RESERVEDQTY;
         short RESERVEPCT;
         long FETCH_REL;
                        bool operator==(const N_ARTICLERESERVATION& right) const {
                        return(
                                BRANCHNO == right.BRANCHNO &&
                                !strcmp(PHARMACYGROUPID, right.PHARMACYGROUPID) &&
                                ARTICLENO == right.ARTICLENO &&
                                RESERVTYPE == right.RESERVTYPE &&
                                MAXQTY == right.MAXQTY &&
                                RESERVEDQTY == right.RESERVEDQTY &&
                                RESERVEPCT == right.RESERVEPCT
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                BRANCHNO = 0;
                                strcpy(PHARMACYGROUPID, " " );
                                ARTICLENO = 0;
                                RESERVTYPE = 0;
                                MAXQTY = 0;
                                RESERVEDQTY = 0;
                                RESERVEPCT = 0;
#endif
                        }
         } articlereservationS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTICLERESERVATION ********************************/

 struct S_ARTICLERESERVATION {
         char BRANCHNO[7];
         char PHARMACYGROUPID[3 + 1];
         char ARTICLENO[11];
         char RESERVTYPE[7];
         char MAXQTY[11];
         char RESERVEDQTY[11];
         char RESERVEPCT[7];
         char FETCH_REL[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTICLERESERVATION ***************/

 struct O_ARTICLERESERVATION {
         char BRANCHNO[7];
         char PHARMACYGROUPID[3];
         char ARTICLENO[11];
         char RESERVTYPE[7];
         char MAXQTY[11];
         char RESERVEDQTY[11];
         char RESERVEPCT[7];
         char FETCH_REL[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTICLERESERVATION **************************/

 struct C_ARTICLERESERVATION {
         short BRANCHNO;
         char PHARMACYGROUPID[4];
         long ARTICLENO;
         short RESERVTYPE;
         long MAXQTY;
         long RESERVEDQTY;
         short RESERVEPCT;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTICLERESERVATION ************************/

 struct I_ARTICLERESERVATION {
         short BRANCHNO;
         short PHARMACYGROUPID;
         short ARTICLENO;
         short RESERVTYPE;
         short MAXQTY;
         short RESERVEDQTY;
         short RESERVEPCT;
         short FETCH_REL;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTICLERESERVATION **********************************/

#if defined (BUF_DESC)
 static struct buf_desc ARTICLERESERVATION_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTICLERESERVATION_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of ARTICLERESERVATION ****************************/

 #define ARTICLERESERVATION_S390 \
         short BRANCHNO; \
         char PHARMACYGROUPID[4]; \
         long ARTICLENO; \
         short RESERVTYPE; \
         long MAXQTY; \
         long RESERVEDQTY; \
         short RESERVEPCT; \
         long FETCH_REL;



/* Copy-Function Struct to single Data ARTICLERESERVATION *********************/

 #define ARTICLERESERVATION_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
          strcpy(PHARMACYGROUPID,_x_->PHARMACYGROUPID);\
         ARTICLENO=_x_->ARTICLENO;\
         RESERVTYPE=_x_->RESERVTYPE;\
         MAXQTY=_x_->MAXQTY;\
         RESERVEDQTY=_x_->RESERVEDQTY;\
         RESERVEPCT=_x_->RESERVEPCT;\
          FETCH_REL=_x_->FETCH_REL;\

 #define ARTICLERESERVATION_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          strcpy(_x_->PHARMACYGROUPID,PHARMACYGROUPID);\
          _x_->ARTICLENO=ARTICLENO;\
          _x_->RESERVTYPE=RESERVTYPE;\
          _x_->MAXQTY=MAXQTY;\
          _x_->RESERVEDQTY=RESERVEDQTY;\
          _x_->RESERVEPCT=RESERVEPCT;\
          _x_->FETCH_REL=FETCH_REL;\



/* FunctionNumber-Define of ArticleReservation ********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ArticleReservation ****************************/


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

class CARTICLERESERVATION : public ppDadeVirtual
{
        //data members
        public:
                articlereservationS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<articlereservationS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<articlereservationS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<articlereservationS>; Strip(s); articlereservationS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<articlereservationS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<articlereservationS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<articlereservationS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetBranchno() const     { return s.BRANCHNO; }
                const char*     GetPharmacygroupid(ppString& t) const   { t = s.PHARMACYGROUPID; t.erasespace(ppString::END); return t.c_str(); }
                long            GetArticleno() const    { return s.ARTICLENO; }
                short           GetReservtype() const   { return s.RESERVTYPE; }
                long            GetMaxqty() const       { return s.MAXQTY; }
                long            GetReservedqty() const  { return s.RESERVEDQTY; }
                short           GetReservepct() const   { return s.RESERVEPCT; }
                const articlereservationS& GetStruct() const { return s; }
                long            GetFetch_rel() const { return s.FETCH_REL; }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetPharmacygroupid(const ppString& t) { ppGStrCopy(s.PHARMACYGROUPID,t.c_str() ,L_ARTICLERESERVATION_PHARMACYGROUPID); }
                void            SetArticleno(long t) { s.ARTICLENO = t; }
                void            SetReservtype(short t) { s.RESERVTYPE = t; }
                void            SetMaxqty(long t) { s.MAXQTY = t; }
                void            SetReservedqty(long t) { s.RESERVEDQTY = t; }
                void            SetReservepct(short t) { s.RESERVEPCT = t; }
                void            SetStruct(const articlereservationS& t) { s = t; }
                void            SetFetch_rel(const long t) { s.FETCH_REL = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CARTICLERESERVATION()  //constructor
                {
                        ::buf_default((void *)&s, ARTICLERESERVATION_BES, ARTICLERESERVATION_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CARTICLERESERVATION()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                        CloseCursor();
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, ARTICLERESERVATION_BES, ARTICLERESERVATION_ANZ);
                }

                int CloseCursor(int pos = 0)  //close db cursor
                {
                        if( !bOpenCursor ) return 0;
                        s.FETCH_REL = 0;
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNumber, (void *)&s,ARTICLERESERVATION_BES,ARTICLERESERVATION_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
                        #endif
                        bOpenCursor  = false;
                        bEndOfSelect = false;
                        FncNumber    = 0;
                        CursorPos    = 0;
                        AnzPos       = 0;
                        if(pl)
                        {
                                delete pl;
                                pl = NULL;
                        }
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ARTICLERESERVATION_BES, ARTICLERESERVATION_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, ARTICLERESERVATION_BES, ARTICLERESERVATION_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_ARTICLERESERVATION& d)
                {
#ifdef WIN32
                        ppGStripLast(d.PHARMACYGROUPID);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, ARTICLERESERVATION_BES, ARTICLERESERVATION_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

                int CursorServerCall(int FncNr,int FetchRel = 1, int pos=0)
                {
                        if              ( FetchRel == 0 ) return CloseCursor(pos);
                        else if ( FetchRel == 1 ) return GetNext(pos,FncNr);
                        else if ( FetchRel <  0 ) return ChangeCursor(FetchRel);
                        else
                        {
                                FehlerBehandlung( -1, "False cursor position!" );
                                return -1;
                        }
                }

                int GetNext(int pos, int FncNr)
                {
                        CARTICLERESERVATION c;
                        if( bOpenCursor && FncNumber != FncNr ) CloseCursor(pos);
                        if( bOpenCursor ) s.FETCH_REL = 1;
                        else
                        {
                                s.FETCH_REL = 2;
                                bOpenCursor = true;
                                FncNumber   = FncNr;
                                AnzPos      = 0;
                                if ( pl ) delete pl;
                                pl = new vector<articlereservationS>;
                        }
                        if( CursorPos == AnzPos && bEndOfSelect ) { rc = 1; return 1; }
                        else if( CursorPos < AnzPos )
                        {
                                s = pl->at(CursorPos);
                                CursorPos++;
                                return 0;
                        }
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNumber, (void *)&s, ARTICLERESERVATION_BES, ARTICLERESERVATION_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNumber, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc == 0)
                        {
                                Strip(s);
                                c.s = s;
                                pl->insert(pl->end(),c.s);
                                bEndOfSelect = false;
                                CursorPos++;
                                AnzPos++;
                        }
                        else if (rc == 1) bEndOfSelect = true;
                        else if (rc < 0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

                int ChangeCursor(int FetchRel) // FetchRel is a negative value
                {
                        CursorPos = CursorPos + FetchRel < 0 ? 0 : CursorPos + FetchRel - 1;
                        if ( CursorPos >= AnzPos )
                        {
                                FehlerBehandlung( -1, "False cursor position!" );
                                return -1;
                        }
                        s = pl->at(CursorPos);
                        CursorPos++;
                        rc = 0;
                        return 0;
                }

};

#endif

/* CreateSqlStatement of ARTICLERESERVATION ***********************************/

 #define ARTICLERESERVATION_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         PHARMACYGROUPID char(3) default " " not null,\
         ARTICLENO integer default 0 not null,\
         RESERVTYPE smallint default 0 not null,\
         MAXQTY integer default 0 not null,\
         RESERVEDQTY integer default 0 not null,\
         RESERVEPCT smallint default 0 not null) in ksc extent size 156 next size 16 lock mode row;



/* CreateIndexStatement of ARTICLERESERVATION *********************************/

 #define ARTICLERESERVATION_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_ArtReserve_1 on _X_(\
              BranchNo,\
              ArticleNo,\
              PharmacyGroupId,\
              ReservType ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index i_ArtReserve_2 on _X_(\
              BranchNo,\
              ArticleNo,\
              PharmacyGroupId ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ARTICLERESERVATION *********************************/

 #define ARTICLERESERVATION_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_ArtReserve_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_ArtReserve_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

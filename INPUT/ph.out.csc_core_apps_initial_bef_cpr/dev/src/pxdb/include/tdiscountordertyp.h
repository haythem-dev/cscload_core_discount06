#ifndef __PP_DISCOUNTORDERTYP_H_
#define __PP_DISCOUNTORDERTYP_H_

/******************************************************************************/
/* u:\nordat\DiscountOrderTyp *************************************************/
/******************************************************************************/

/* Length-Define of DISCOUNTORDERTYP ******************************************/

  #define L_DISCOUNTORDERTYP_DISCOUNTTYPE 6
  #define L_DISCOUNTORDERTYP_KDAUFTRAGART 2

/* Length/Count-Define of DISCOUNTORDERTYP ************************************/

  #define LS_DISCOUNTORDERTYP_DISCOUNTTYPE 5 + 1
  #define LS_DISCOUNTORDERTYP_KDAUFTRAGART 2 + 1

  #define DISCOUNTORDERTYPDISCOUNTTYPE 0
  #define DISCOUNTORDERTYPKDAUFTRAGART 1

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define DISCOUNTORDERTYP_H
 #define DISCOUNTORDERTYP_ANZ ( sizeof(DISCOUNTORDERTYP_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of DISCOUNTORDERTYP **********************************************/

 #define DISCOUNTORDERTYP_LISTE \
         DISCOUNTORDERTYP.DISCOUNTTYPE,\
         DISCOUNTORDERTYP.KDAUFTRAGART

 #define DISCOUNTORDERTYP_LISTE_390 \
         DISCOUNTTYPE,\
         KDAUFTRAGART

 #define DISCOUNTORDERTYP_PLISTE \
         "DISCOUNTORDERTYP.DISCOUNTTYPE,"\
         "DISCOUNTORDERTYP.KDAUFTRAGART"

 #define DISCOUNTORDERTYP_PELISTE \
         "DISCOUNTTYPE,"\
         "KDAUFTRAGART"

 #define DISCOUNTORDERTYP_UPDLISTE \
         "DISCOUNTTYPE=?,"\
         "KDAUFTRAGART=?"

/* SqlMacros-Define of DISCOUNTORDERTYP ***************************************/

 #define DISCOUNTORDERTYP_ZEIGER(x) \
         :x->DISCOUNTTYPE,\
         :x->KDAUFTRAGART

 #define DISCOUNTORDERTYP_ZEIGERSEL(x) \
         :x->DISCOUNTTYPE,\
         :x->KDAUFTRAGART

 #define DISCOUNTORDERTYP_UPDATE(x) \
         DISCOUNTORDERTYP.DISCOUNTTYPE=:x->DISCOUNTTYPE,\
         DISCOUNTORDERTYP.KDAUFTRAGART=:x->KDAUFTRAGART

/* SqlMacros390-Define of DISCOUNTORDERTYP ************************************/

 #define DISCOUNTORDERTYP_ZEIGER_390 \
         :DISCOUNTTYPE,\
         :KDAUFTRAGART

 #define DISCOUNTORDERTYP_UPDATE_390 \
         DISCOUNTTYPE=:DISCOUNTTYPE,\
         KDAUFTRAGART=:KDAUFTRAGART

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of DISCOUNTORDERTYP ***************************************/

 #ifndef TRANSCLASS
 typedef struct N_DISCOUNTORDERTYP {
         short DISCOUNTTYPE;
         char KDAUFTRAGART[3];
        } discountordertypS;
 #else /*TRANSCLASS*/
 typedef struct N_DISCOUNTORDERTYP {
         short DISCOUNTTYPE;
         char KDAUFTRAGART[3];

                        bool operator==(const N_DISCOUNTORDERTYP& right) const {
                        return(
                                DISCOUNTTYPE == right.DISCOUNTTYPE &&
                                !strcmp(KDAUFTRAGART, right.KDAUFTRAGART)
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                DISCOUNTTYPE = 0;
                                strcpy(KDAUFTRAGART, " " );
#endif
                        }
         } discountordertypS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of DISCOUNTORDERTYP **********************************/

 struct S_DISCOUNTORDERTYP {
         char DISCOUNTTYPE[7];
         char KDAUFTRAGART[2 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of DISCOUNTORDERTYP *****************/

 struct O_DISCOUNTORDERTYP {
         char DISCOUNTTYPE[7];
         char KDAUFTRAGART[2];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of DISCOUNTORDERTYP ****************************/

 struct C_DISCOUNTORDERTYP {
         short DISCOUNTTYPE;
         char KDAUFTRAGART[3];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of DISCOUNTORDERTYP **************************/

 struct I_DISCOUNTORDERTYP {
         short DISCOUNTTYPE;
         short KDAUFTRAGART;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of DISCOUNTORDERTYP ************************************/

#if defined (BUF_DESC)
 static struct buf_desc DISCOUNTORDERTYP_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DISCOUNTORDERTYP_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_C, 2, 0 },
 };
#endif

/* description for datatypes of DISCOUNTORDERTYP ******************************/

 #define DISCOUNTORDERTYP_S390 \
         short DISCOUNTTYPE; \
         char KDAUFTRAGART[3]; \



/* Copy-Function Struct to single Data DISCOUNTORDERTYP ***********************/

 #define DISCOUNTORDERTYP_S390_COPY_TO_SINGLE(_x_) \
         DISCOUNTTYPE=_x_->DISCOUNTTYPE;\
          strcpy(KDAUFTRAGART,_x_->KDAUFTRAGART);\

 #define DISCOUNTORDERTYP_S390_COPY_TO_STRUCT(_x_) \
          _x_->DISCOUNTTYPE=DISCOUNTTYPE;\
          strcpy(_x_->KDAUFTRAGART,KDAUFTRAGART);\



/* FunctionNumber-Define of DiscountOrderTyp **********************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of DiscountOrderTyp ******************************/


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

class CDISCOUNTORDERTYP : public ppDadeVirtual
{
        //data members
        public:
                discountordertypS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<discountordertypS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<discountordertypS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<discountordertypS>; Strip(s); discountordertypS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<discountordertypS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<discountordertypS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<discountordertypS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetDiscounttype() const { return s.DISCOUNTTYPE; }
                const char*     GetKdauftragart(ppString& t) const      { t = s.KDAUFTRAGART; t.erasespace(ppString::END); return t.c_str(); }
                const discountordertypS& GetStruct() const { return s; }
                void            SetDiscounttype(short t) { s.DISCOUNTTYPE = t; }
                void            SetKdauftragart(const ppString& t) { ppGStrCopy(s.KDAUFTRAGART,t.c_str() ,L_DISCOUNTORDERTYP_KDAUFTRAGART); }
                void            SetStruct(const discountordertypS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CDISCOUNTORDERTYP()  //constructor
                {
                        ::buf_default((void *)&s, DISCOUNTORDERTYP_BES, DISCOUNTORDERTYP_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CDISCOUNTORDERTYP()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, DISCOUNTORDERTYP_BES, DISCOUNTORDERTYP_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, DISCOUNTORDERTYP_BES, DISCOUNTORDERTYP_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, DISCOUNTORDERTYP_BES, DISCOUNTORDERTYP_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_DISCOUNTORDERTYP& d)
                {
#ifdef WIN32
                        ppGStripLast(d.KDAUFTRAGART);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, DISCOUNTORDERTYP_BES, DISCOUNTORDERTYP_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of DISCOUNTORDERTYP *************************************/

 #define DISCOUNTORDERTYP_CREATE(x) exec sql create table x (\
         DISCOUNTTYPE smallint default 0 not null,\
         KDAUFTRAGART char(2) default " " not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of DISCOUNTORDERTYP ***********************************/

 #define DISCOUNTORDERTYP_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of DISCOUNTORDERTYP ***********************************/

 #define DISCOUNTORDERTYP_DELETE_INDEX(_X_)\
              _X_ = 0;\

#endif

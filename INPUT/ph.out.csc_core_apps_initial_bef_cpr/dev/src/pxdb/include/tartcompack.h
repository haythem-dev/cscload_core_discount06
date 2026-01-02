#ifndef __PP_ARTCOMPACK_H_
#define __PP_ARTCOMPACK_H_

/******************************************************************************/
/* u:\ArtComPack **************************************************************/
/******************************************************************************/

/* Length-Define of ARTCOMPACK ************************************************/

  #define L_ARTCOMPACK_ARTICLE_NO_PACK 11
  #define L_ARTCOMPACK_ARTICLE_NO_ELEMENT 11
  #define L_ARTCOMPACK_QUANTITY 11

/* Length/Count-Define of ARTCOMPACK ******************************************/

  #define LS_ARTCOMPACK_ARTICLE_NO_PACK 10 + 1
  #define LS_ARTCOMPACK_ARTICLE_NO_ELEMENT 10 + 1
  #define LS_ARTCOMPACK_QUANTITY 10 + 1

  #define ARTCOMPACKARTICLE_NO_PACK 0
  #define ARTCOMPACKARTICLE_NO_ELEMENT 1
  #define ARTCOMPACKQUANTITY 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ARTCOMPACK_H
 #define ARTCOMPACK_ANZ ( sizeof(ARTCOMPACK_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTCOMPACK ****************************************************/

 #define ARTCOMPACK_LISTE \
         ARTCOMPACK.ARTICLE_NO_PACK,\
         ARTCOMPACK.ARTICLE_NO_ELEMENT,\
         ARTCOMPACK.QUANTITY

 #define ARTCOMPACK_LISTE_390 \
         ARTICLE_NO_PACK,\
         ARTICLE_NO_ELEMENT,\
         QUANTITY

 #define ARTCOMPACK_PLISTE \
         "ARTCOMPACK.ARTICLE_NO_PACK,"\
         "ARTCOMPACK.ARTICLE_NO_ELEMENT,"\
         "ARTCOMPACK.QUANTITY"

 #define ARTCOMPACK_PELISTE \
         "ARTICLE_NO_PACK,"\
         "ARTICLE_NO_ELEMENT,"\
         "QUANTITY"

 #define ARTCOMPACK_UPDLISTE \
         "ARTICLE_NO_PACK=?,"\
         "ARTICLE_NO_ELEMENT=?,"\
         "QUANTITY=?"

/* SqlMacros-Define of ARTCOMPACK *********************************************/

 #define ARTCOMPACK_ZEIGER(x) \
         :x->ARTICLE_NO_PACK,\
         :x->ARTICLE_NO_ELEMENT,\
         :x->QUANTITY

 #define ARTCOMPACK_ZEIGERSEL(x) \
         :x->ARTICLE_NO_PACK,\
         :x->ARTICLE_NO_ELEMENT,\
         :x->QUANTITY

 #define ARTCOMPACK_UPDATE(x) \
         ARTCOMPACK.ARTICLE_NO_PACK=:x->ARTICLE_NO_PACK,\
         ARTCOMPACK.ARTICLE_NO_ELEMENT=:x->ARTICLE_NO_ELEMENT,\
         ARTCOMPACK.QUANTITY=:x->QUANTITY

/* SqlMacros390-Define of ARTCOMPACK ******************************************/

 #define ARTCOMPACK_ZEIGER_390 \
         :ARTICLE_NO_PACK,\
         :ARTICLE_NO_ELEMENT,\
         :QUANTITY

 #define ARTCOMPACK_UPDATE_390 \
         ARTICLE_NO_PACK=:ARTICLE_NO_PACK,\
         ARTICLE_NO_ELEMENT=:ARTICLE_NO_ELEMENT,\
         QUANTITY=:QUANTITY

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ARTCOMPACK *********************************************/

 #ifndef TRANSCLASS
 typedef struct N_ARTCOMPACK {
         long ARTICLE_NO_PACK;
         long ARTICLE_NO_ELEMENT;
         long QUANTITY;
         long FETCH_REL;
        } artcompackS;
 #else /*TRANSCLASS*/
 typedef struct N_ARTCOMPACK {
         long ARTICLE_NO_PACK;
         long ARTICLE_NO_ELEMENT;
         long QUANTITY;
         long FETCH_REL;
                        bool operator==(const N_ARTCOMPACK& right) const {
                        return(
                                ARTICLE_NO_PACK == right.ARTICLE_NO_PACK &&
                                ARTICLE_NO_ELEMENT == right.ARTICLE_NO_ELEMENT &&
                                QUANTITY == right.QUANTITY
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                ARTICLE_NO_PACK = 0;
                                ARTICLE_NO_ELEMENT = 0;
                                QUANTITY = 0;
#endif
                        }
         } artcompackS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTCOMPACK ****************************************/

 struct S_ARTCOMPACK {
         char ARTICLE_NO_PACK[11];
         char ARTICLE_NO_ELEMENT[11];
         char QUANTITY[11];
         char FETCH_REL[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTCOMPACK ***********************/

 struct O_ARTCOMPACK {
         char ARTICLE_NO_PACK[11];
         char ARTICLE_NO_ELEMENT[11];
         char QUANTITY[11];
         char FETCH_REL[11];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of ARTCOMPACK **********************************/

 struct C_ARTCOMPACK {
         long ARTICLE_NO_PACK;
         long ARTICLE_NO_ELEMENT;
         long QUANTITY;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of ARTCOMPACK ********************************/

 struct I_ARTCOMPACK {
         short ARTICLE_NO_PACK;
         short ARTICLE_NO_ELEMENT;
         short QUANTITY;
         short FETCH_REL;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTCOMPACK ******************************************/

#if defined (BUF_DESC)
 static struct buf_desc ARTCOMPACK_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTCOMPACK_BES [] =
 {
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
 };
#endif

/* description for datatypes of ARTCOMPACK ************************************/

 #define ARTCOMPACK_S390 \
         long ARTICLE_NO_PACK; \
         long ARTICLE_NO_ELEMENT; \
         long QUANTITY; \
         long FETCH_REL;



/* Copy-Function Struct to single Data ARTCOMPACK *****************************/

 #define ARTCOMPACK_S390_COPY_TO_SINGLE(_x_) \
         ARTICLE_NO_PACK=_x_->ARTICLE_NO_PACK;\
         ARTICLE_NO_ELEMENT=_x_->ARTICLE_NO_ELEMENT;\
         QUANTITY=_x_->QUANTITY;\
          FETCH_REL=_x_->FETCH_REL;\

 #define ARTCOMPACK_S390_COPY_TO_STRUCT(_x_) \
          _x_->ARTICLE_NO_PACK=ARTICLE_NO_PACK;\
          _x_->ARTICLE_NO_ELEMENT=ARTICLE_NO_ELEMENT;\
          _x_->QUANTITY=QUANTITY;\
          _x_->FETCH_REL=FETCH_REL;\



/* FunctionNumber-Define of ArtComPack ****************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of ArtComPack ************************************/


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

class CARTCOMPACK : public ppDadeVirtual
{
        //data members
        public:
                artcompackS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<artcompackS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<artcompackS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<artcompackS>; Strip(s); artcompackS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<artcompackS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<artcompackS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<artcompackS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                long            GetArticle_no_pack() const      { return s.ARTICLE_NO_PACK; }
                long            GetArticle_no_element() const   { return s.ARTICLE_NO_ELEMENT; }
                long            GetQuantity() const     { return s.QUANTITY; }
                const artcompackS& GetStruct() const { return s; }
                long            GetFetch_rel() const { return s.FETCH_REL; }
                void            SetArticle_no_pack(long t) { s.ARTICLE_NO_PACK = t; }
                void            SetArticle_no_element(long t) { s.ARTICLE_NO_ELEMENT = t; }
                void            SetQuantity(long t) { s.QUANTITY = t; }
                void            SetStruct(const artcompackS& t) { s = t; }
                void            SetFetch_rel(const long t) { s.FETCH_REL = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CARTCOMPACK()  //constructor
                {
                        ::buf_default((void *)&s, ARTCOMPACK_BES, ARTCOMPACK_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CARTCOMPACK()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                        CloseCursor();
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, ARTCOMPACK_BES, ARTCOMPACK_ANZ);
                }

                int CloseCursor(int pos = 0)  //close db cursor
                {
                        if( !bOpenCursor ) return 0;
                        s.FETCH_REL = 0;
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNumber, (void *)&s,ARTCOMPACK_BES,ARTCOMPACK_ANZ, error_msg);
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
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, ARTCOMPACK_BES, ARTCOMPACK_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, ARTCOMPACK_BES, ARTCOMPACK_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_ARTCOMPACK& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, ARTCOMPACK_BES, ARTCOMPACK_ANZ, error_msg);
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
                        CARTCOMPACK c;
                        if( bOpenCursor && FncNumber != FncNr ) CloseCursor(pos);
                        if( bOpenCursor ) s.FETCH_REL = 1;
                        else
                        {
                                s.FETCH_REL = 2;
                                bOpenCursor = true;
                                FncNumber   = FncNr;
                                AnzPos      = 0;
                                if ( pl ) delete pl;
                                pl = new vector<artcompackS>;
                        }
                        if( CursorPos == AnzPos && bEndOfSelect ) { rc = 1; return 1; }
                        else if( CursorPos < AnzPos )
                        {
                                s = pl->at(CursorPos);
                                CursorPos++;
                                return 0;
                        }
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNumber, (void *)&s, ARTCOMPACK_BES, ARTCOMPACK_ANZ, error_msg);
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

/* CreateSqlStatement of ARTCOMPACK *******************************************/

 #define ARTCOMPACK_CREATE(x) exec sql create table x (\
         ARTICLE_NO_PACK integer default 0 not null,\
         ARTICLE_NO_ELEMENT integer default 0 not null,\
         QUANTITY integer default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of ARTCOMPACK *****************************************/

 #define ARTCOMPACK_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_artcompack_1 on _X_(\
              article_no_pack,\
              article_no_element ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of ARTCOMPACK *****************************************/

 #define ARTCOMPACK_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_artcompack_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

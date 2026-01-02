#ifndef __PP_ARTICLETEXT_H_
#define __PP_ARTICLETEXT_H_

/******************************************************************************/
/* v:\nordat\articletext ******************************************************/
/******************************************************************************/

/* Length-Define of ARTICLETEXT ***********************************************/

  #define L_ARTICLETEXT_BRANCHNO 6
  #define L_ARTICLETEXT_TEXTKEY 6
  #define L_ARTICLETEXT_TEXT 240
  #define L_ARTICLETEXT_DISPLAYONSCREEN 1

/* Length/Count-Define of ARTICLETEXT *****************************************/

  #define LS_ARTICLETEXT_BRANCHNO 5 + 1
  #define LS_ARTICLETEXT_TEXTKEY 5 + 1
  #define LS_ARTICLETEXT_TEXT 240 + 1
  #define LS_ARTICLETEXT_DISPLAYONSCREEN 1 + 1

  #define ARTICLETEXTBRANCHNO 0
  #define ARTICLETEXTTEXTKEY 1
  #define ARTICLETEXTTEXT 2
  #define ARTICLETEXTDISPLAYONSCREEN 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define ARTICLETEXT_H
 #define ARTICLETEXT_ANZ ( sizeof(ARTICLETEXT_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of ARTICLETEXT ***************************************************/

 #define ARTICLETEXT_LISTE \
         ARTICLETEXT.BRANCHNO,\
         ARTICLETEXT.TEXTKEY,\
         ARTICLETEXT.TEXT,\
         ARTICLETEXT.DISPLAYONSCREEN

 #define ARTICLETEXT_LISTE_390 \
         BRANCHNO,\
         TEXTKEY,\
         TEXT,\
         DISPLAYONSCREEN

 #define ARTICLETEXT_PLISTE \
         "ARTICLETEXT.BRANCHNO,"\
         "ARTICLETEXT.TEXTKEY,"\
         "ARTICLETEXT.TEXT,"\
         "ARTICLETEXT.DISPLAYONSCREEN"

 #define ARTICLETEXT_PELISTE \
         "BRANCHNO,"\
         "TEXTKEY,"\
         "TEXT,"\
         "DISPLAYONSCREEN"

 #define ARTICLETEXT_UPDLISTE \
         "BRANCHNO=?,"\
         "TEXTKEY=?,"\
         "TEXT=?,"\
         "DISPLAYONSCREEN=?"

/* SqlMacros-Define of ARTICLETEXT ********************************************/

 #define ARTICLETEXT_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->TEXTKEY,\
         :x->TEXT,\
         :x->DISPLAYONSCREEN

 #define ARTICLETEXT_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->TEXTKEY,\
         :x->TEXT,\
         :x->DISPLAYONSCREEN

 #define ARTICLETEXT_UPDATE(x) \
         ARTICLETEXT.BRANCHNO=:x->BRANCHNO,\
         ARTICLETEXT.TEXTKEY=:x->TEXTKEY,\
         ARTICLETEXT.TEXT=:x->TEXT,\
         ARTICLETEXT.DISPLAYONSCREEN=:x->DISPLAYONSCREEN

/* SqlMacros390-Define of ARTICLETEXT *****************************************/

 #define ARTICLETEXT_ZEIGER_390 \
         :BRANCHNO,\
         :TEXTKEY,\
         :TEXT,\
         :DISPLAYONSCREEN

 #define ARTICLETEXT_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         TEXTKEY=:TEXTKEY,\
         TEXT=:TEXT,\
         DISPLAYONSCREEN=:DISPLAYONSCREEN

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of ARTICLETEXT ********************************************/

 #ifndef TRANSCLASS
 typedef struct N_ARTICLETEXT {
         short BRANCHNO;
         short TEXTKEY;
         char TEXT[241];
         char DISPLAYONSCREEN[2];
        } articletextS;
 #else /*TRANSCLASS*/
 typedef struct N_ARTICLETEXT {
         short BRANCHNO;
         short TEXTKEY;
         char TEXT[241];
         char DISPLAYONSCREEN[2];

                        bool operator==(const N_ARTICLETEXT& right) const {
                        return(
                                BRANCHNO == right.BRANCHNO &&
                                TEXTKEY == right.TEXTKEY &&
                                !strcmp(TEXT, right.TEXT) &&
                                !strcmp(DISPLAYONSCREEN, right.DISPLAYONSCREEN)
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                BRANCHNO = 0;
                                TEXTKEY = 0;
                                strcpy(TEXT, " " );
                                strcpy(DISPLAYONSCREEN, " " );
#endif
                        }
         } articletextS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of ARTICLETEXT ***************************************/

 struct S_ARTICLETEXT {
         char BRANCHNO[7];
         char TEXTKEY[7];
         char TEXT[240 + 1];
         char DISPLAYONSCREEN[1 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of ARTICLETEXT **********************/

 struct O_ARTICLETEXT {
         char BRANCHNO[7];
         char TEXTKEY[7];
         char TEXT[240];
         char DISPLAYONSCREEN[1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Strucur with real chartype of ARTICLETEXT **********************************/

 struct C_ARTICLETEXT {
         short BRANCHNO;
         short TEXTKEY;
         char TEXT[241];
         char DISPLAYONSCREEN;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Strucur (buf_desc) of ARTICLETEXT ********************************/

 struct I_ARTICLETEXT {
         short BRANCHNO;
         short TEXTKEY;
         short TEXT;
         short DISPLAYONSCREEN;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of ARTICLETEXT *****************************************/

#if defined (BUF_DESC)
 static struct buf_desc ARTICLETEXT_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 240, 0 },
   { TYP_C, 1, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc ARTICLETEXT_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_C, 240, 0 },
   { TYP_C, 1, 0 },
 };
#endif

/* description for datatypes of ARTICLETEXT ***********************************/

 #define ARTICLETEXT_S390 \
         short BRANCHNO; \
         short TEXTKEY; \
         char TEXT[241]; \
         char DISPLAYONSCREEN; \



/* Copy-Function Struct to single Data ARTICLETEXT ****************************/

 #define ARTICLETEXT_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         TEXTKEY=_x_->TEXTKEY;\
          strcpy(TEXT,_x_->TEXT);\
         DISPLAYONSCREEN=_x_->DISPLAYONSCREEN;\

 #define ARTICLETEXT_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->TEXTKEY=TEXTKEY;\
          strcpy(_x_->TEXT,TEXT);\
          _x_->DISPLAYONSCREEN=DISPLAYONSCREEN;\



/* FunctionNumber-Define of articletext ***************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of articletext ***********************************/


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

class CARTICLETEXT : public ppDadeVirtual
{
        //data members
        public:
                articletextS s;
                int rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<articletextS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<articletextS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<articletextS>; Strip(s); articletextS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<articletextS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<articletextS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<articletextS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetBranchno() const     { return s.BRANCHNO; }
                short           GetTextkey() const      { return s.TEXTKEY; }
                const char*     GetText(ppString& t) const      { t = s.TEXT; t.erasespace(ppString::END); return t.c_str(); }
                char            GetDisplayonscreen() const      { return s.DISPLAYONSCREEN[0]; }
                const articletextS& GetStruct() const { return s; }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetTextkey(short t) { s.TEXTKEY = t; }
                void            SetText(const ppString& t) { ppGStrCopy(s.TEXT,t.c_str() ,L_ARTICLETEXT_TEXT); }
                void            SetDisplayonscreen(char t) { s.DISPLAYONSCREEN[0] = t; s.DISPLAYONSCREEN[1] = '\0';}
                void            SetStruct(const articletextS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CARTICLETEXT()  //constructor
                {
                        ::buf_default((void *)&s,ARTICLETEXT_BES,ARTICLETEXT_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CARTICLETEXT()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, ARTICLETEXT_BES, ARTICLETEXT_ANZ );
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc=::ServerNr(pos, fkt_nr, (void *)&s,ARTICLETEXT_BES,ARTICLETEXT_ANZ, error_msg);
                        #else
                        rc=::Server(fkt_nr, (void *)&s,ARTICLETEXT_BES,ARTICLETEXT_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_ARTICLETEXT& d)
                {
#ifdef WIN32
                        ppGStripLast(d.TEXT);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc=::ServerNr(pos, FncNr, (void *)&s,ARTICLETEXT_BES,ARTICLETEXT_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of ARTICLETEXT ******************************************/

 #define ARTICLETEXT_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         TEXTKEY smallint default 0 not null,\
         TEXT varchar(240,0) default " " not null,\
         DISPLAYONSCREEN char(1) default " " not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of ARTICLETEXT ****************************************/

 #define ARTICLETEXT_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
/* DeleteIndexStatement of ARTICLETEXT ****************************************/

 #define ARTICLETEXT_DELETE_INDEX(_X_)\
              _X_ = 0;\

#endif

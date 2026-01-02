#ifndef __PP_DEALERVOLUME_H_
#define __PP_DEALERVOLUME_H_

/******************************************************************************/
/* u:\DealerVolume ************************************************************/
/******************************************************************************/

/* Length-Define of DEALERVOLUME **********************************************/

  #define L_DEALERVOLUME_BRANCHNO 6
  #define L_DEALERVOLUME_UID 11
  #define L_DEALERVOLUME_INVOICENO 11
  #define L_DEALERVOLUME_ORDERNOVSE 11
  #define L_DEALERVOLUME_ORDERNOKSC 11
  #define L_DEALERVOLUME_DATEINVOICE 11
  #define L_DEALERVOLUME_TIMEINVOICE 11
  #define L_DEALERVOLUME_INVOICEVOLUME 11
  #define N_DEALERVOLUME_INVOICEVOLUME 2
  #define L_DEALERVOLUME_VOLUME1 11
  #define N_DEALERVOLUME_VOLUME1 2
  #define L_DEALERVOLUME_VOLUME2 11
  #define N_DEALERVOLUME_VOLUME2 2
  #define L_DEALERVOLUME_VOLUME3 11
  #define N_DEALERVOLUME_VOLUME3 2
  #define L_DEALERVOLUME_VOLUME4 11
  #define N_DEALERVOLUME_VOLUME4 2
  #define L_DEALERVOLUME_CUSTOMERNO 11
  #define L_DEALERVOLUME_VOLUMESTATE 1

/* Length/Count-Define of DEALERVOLUME ****************************************/

  #define LS_DEALERVOLUME_BRANCHNO 5 + 1
  #define LS_DEALERVOLUME_UID 10 + 1
  #define LS_DEALERVOLUME_INVOICENO 10 + 1
  #define LS_DEALERVOLUME_ORDERNOVSE 10 + 1
  #define LS_DEALERVOLUME_ORDERNOKSC 10 + 1
  #define LS_DEALERVOLUME_DATEINVOICE 10 + 1
  #define LS_DEALERVOLUME_TIMEINVOICE 10 + 1
  #define LS_DEALERVOLUME_INVOICEVOLUME 11 + 2
  #define LS_DEALERVOLUME_VOLUME1 11 + 2
  #define LS_DEALERVOLUME_VOLUME2 11 + 2
  #define LS_DEALERVOLUME_VOLUME3 11 + 2
  #define LS_DEALERVOLUME_VOLUME4 11 + 2
  #define LS_DEALERVOLUME_CUSTOMERNO 10 + 1
  #define LS_DEALERVOLUME_VOLUMESTATE 1 + 1

  #define DEALERVOLUMEBRANCHNO 0
  #define DEALERVOLUMEUID 1
  #define DEALERVOLUMEINVOICENO 2
  #define DEALERVOLUMEORDERNOVSE 3
  #define DEALERVOLUMEORDERNOKSC 4
  #define DEALERVOLUMEDATEINVOICE 5
  #define DEALERVOLUMETIMEINVOICE 6
  #define DEALERVOLUMEINVOICEVOLUME 7
  #define DEALERVOLUMEVOLUME1 8
  #define DEALERVOLUMEVOLUME2 9
  #define DEALERVOLUMEVOLUME3 10
  #define DEALERVOLUMEVOLUME4 11
  #define DEALERVOLUMECUSTOMERNO 12
  #define DEALERVOLUMEVOLUMESTATE 13

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define DEALERVOLUME_H
 #define DEALERVOLUME_ANZ ( sizeof(DEALERVOLUME_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of DEALERVOLUME **************************************************/

 #define DEALERVOLUME_LISTE \
         DEALERVOLUME.BRANCHNO,\
         DEALERVOLUME.UID,\
         DEALERVOLUME.INVOICENO,\
         DEALERVOLUME.ORDERNOVSE,\
         DEALERVOLUME.ORDERNOKSC,\
         DEALERVOLUME.DATEINVOICE,\
         DEALERVOLUME.TIMEINVOICE,\
         DEALERVOLUME.INVOICEVOLUME,\
         DEALERVOLUME.VOLUME1,\
         DEALERVOLUME.VOLUME2,\
         DEALERVOLUME.VOLUME3,\
         DEALERVOLUME.VOLUME4,\
         DEALERVOLUME.CUSTOMERNO,\
         DEALERVOLUME.VOLUMESTATE

 #define DEALERVOLUME_LISTE_390 \
         BRANCHNO,\
         UID,\
         INVOICENO,\
         ORDERNOVSE,\
         ORDERNOKSC,\
         DATEINVOICE,\
         TIMEINVOICE,\
         INVOICEVOLUME,\
         VOLUME1,\
         VOLUME2,\
         VOLUME3,\
         VOLUME4,\
         CUSTOMERNO,\
         VOLUMESTATE

 #define DEALERVOLUME_PLISTE \
         "DEALERVOLUME.BRANCHNO,"\
         "DEALERVOLUME.UID,"\
         "DEALERVOLUME.INVOICENO,"\
         "DEALERVOLUME.ORDERNOVSE,"\
         "DEALERVOLUME.ORDERNOKSC,"\
         "DEALERVOLUME.DATEINVOICE,"\
         "DEALERVOLUME.TIMEINVOICE,"\
         "DEALERVOLUME.INVOICEVOLUME,"\
         "DEALERVOLUME.VOLUME1,"\
         "DEALERVOLUME.VOLUME2,"\
         "DEALERVOLUME.VOLUME3,"\
         "DEALERVOLUME.VOLUME4,"\
         "DEALERVOLUME.CUSTOMERNO,"\
         "DEALERVOLUME.VOLUMESTATE"

 #define DEALERVOLUME_PELISTE \
         "BRANCHNO,"\
         "UID,"\
         "INVOICENO,"\
         "ORDERNOVSE,"\
         "ORDERNOKSC,"\
         "DATEINVOICE,"\
         "TIMEINVOICE,"\
         "INVOICEVOLUME,"\
         "VOLUME1,"\
         "VOLUME2,"\
         "VOLUME3,"\
         "VOLUME4,"\
         "CUSTOMERNO,"\
         "VOLUMESTATE"

 #define DEALERVOLUME_UPDLISTE \
         "BRANCHNO=?,"\
         "UID=?,"\
         "INVOICENO=?,"\
         "ORDERNOVSE=?,"\
         "ORDERNOKSC=?,"\
         "DATEINVOICE=?,"\
         "TIMEINVOICE=?,"\
         "INVOICEVOLUME=?,"\
         "VOLUME1=?,"\
         "VOLUME2=?,"\
         "VOLUME3=?,"\
         "VOLUME4=?,"\
         "CUSTOMERNO=?,"\
         "VOLUMESTATE=?"

/* SqlMacros-Define of DEALERVOLUME *******************************************/

 #define DEALERVOLUME_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->UID,\
         :x->INVOICENO,\
         :x->ORDERNOVSE,\
         :x->ORDERNOKSC,\
         :x->DATEINVOICE,\
         :x->TIMEINVOICE,\
         :x->INVOICEVOLUME,\
         :x->VOLUME1,\
         :x->VOLUME2,\
         :x->VOLUME3,\
         :x->VOLUME4,\
         :x->CUSTOMERNO,\
         :x->VOLUMESTATE

 #define DEALERVOLUME_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->UID,\
         :x->INVOICENO,\
         :x->ORDERNOVSE,\
         :x->ORDERNOKSC,\
         :x->DATEINVOICE,\
         :x->TIMEINVOICE,\
         :x->INVOICEVOLUME,\
         :x->VOLUME1,\
         :x->VOLUME2,\
         :x->VOLUME3,\
         :x->VOLUME4,\
         :x->CUSTOMERNO,\
         :x->VOLUMESTATE

 #define DEALERVOLUME_UPDATE(x) \
         DEALERVOLUME.BRANCHNO=:x->BRANCHNO,\
         DEALERVOLUME.UID=:x->UID,\
         DEALERVOLUME.INVOICENO=:x->INVOICENO,\
         DEALERVOLUME.ORDERNOVSE=:x->ORDERNOVSE,\
         DEALERVOLUME.ORDERNOKSC=:x->ORDERNOKSC,\
         DEALERVOLUME.DATEINVOICE=:x->DATEINVOICE,\
         DEALERVOLUME.TIMEINVOICE=:x->TIMEINVOICE,\
         DEALERVOLUME.INVOICEVOLUME=:x->INVOICEVOLUME,\
         DEALERVOLUME.VOLUME1=:x->VOLUME1,\
         DEALERVOLUME.VOLUME2=:x->VOLUME2,\
         DEALERVOLUME.VOLUME3=:x->VOLUME3,\
         DEALERVOLUME.VOLUME4=:x->VOLUME4,\
         DEALERVOLUME.CUSTOMERNO=:x->CUSTOMERNO,\
         DEALERVOLUME.VOLUMESTATE=:x->VOLUMESTATE

/* SqlMacros390-Define of DEALERVOLUME ****************************************/

 #define DEALERVOLUME_ZEIGER_390 \
         :BRANCHNO,\
         :UID,\
         :INVOICENO,\
         :ORDERNOVSE,\
         :ORDERNOKSC,\
         :DATEINVOICE,\
         :TIMEINVOICE,\
         :INVOICEVOLUME,\
         :VOLUME1,\
         :VOLUME2,\
         :VOLUME3,\
         :VOLUME4,\
         :CUSTOMERNO,\
         :VOLUMESTATE

 #define DEALERVOLUME_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         UID=:UID,\
         INVOICENO=:INVOICENO,\
         ORDERNOVSE=:ORDERNOVSE,\
         ORDERNOKSC=:ORDERNOKSC,\
         DATEINVOICE=:DATEINVOICE,\
         TIMEINVOICE=:TIMEINVOICE,\
         INVOICEVOLUME=:INVOICEVOLUME,\
         VOLUME1=:VOLUME1,\
         VOLUME2=:VOLUME2,\
         VOLUME3=:VOLUME3,\
         VOLUME4=:VOLUME4,\
         CUSTOMERNO=:CUSTOMERNO,\
         VOLUMESTATE=:VOLUMESTATE

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of DEALERVOLUME *******************************************/

 #ifndef TRANSCLASS
 typedef struct N_DEALERVOLUME {
         short BRANCHNO;
         long UID;
         long INVOICENO;
         long ORDERNOVSE;
         long ORDERNOKSC;
         long DATEINVOICE;
         long TIMEINVOICE;
         double INVOICEVOLUME;
         double VOLUME1;
         double VOLUME2;
         double VOLUME3;
         double VOLUME4;
         long CUSTOMERNO;
         char VOLUMESTATE[2];
        } dealervolumeS;
 #else /*TRANSCLASS*/
 typedef struct N_DEALERVOLUME {
         short BRANCHNO;
         long UID;
         long INVOICENO;
         long ORDERNOVSE;
         long ORDERNOKSC;
         long DATEINVOICE;
         long TIMEINVOICE;
         double INVOICEVOLUME;
         double VOLUME1;
         double VOLUME2;
         double VOLUME3;
         double VOLUME4;
         long CUSTOMERNO;
         char VOLUMESTATE[2];

                        bool operator==(const N_DEALERVOLUME& right) const {
                        return(
                                BRANCHNO == right.BRANCHNO &&
                                UID == right.UID &&
                                INVOICENO == right.INVOICENO &&
                                ORDERNOVSE == right.ORDERNOVSE &&
                                ORDERNOKSC == right.ORDERNOKSC &&
                                DATEINVOICE == right.DATEINVOICE &&
                                TIMEINVOICE == right.TIMEINVOICE &&
                                INVOICEVOLUME == right.INVOICEVOLUME &&
                                VOLUME1 == right.VOLUME1 &&
                                VOLUME2 == right.VOLUME2 &&
                                VOLUME3 == right.VOLUME3 &&
                                VOLUME4 == right.VOLUME4 &&
                                CUSTOMERNO == right.CUSTOMERNO &&
                                !strcmp(VOLUMESTATE, right.VOLUMESTATE)
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                BRANCHNO = 0;
                                UID = 0;
                                INVOICENO = 0;
                                ORDERNOVSE = 0;
                                ORDERNOKSC = 0;
                                DATEINVOICE = 0;
                                TIMEINVOICE = 0;
                                INVOICEVOLUME = 0;
                                VOLUME1 = 0;
                                VOLUME2 = 0;
                                VOLUME3 = 0;
                                VOLUME4 = 0;
                                CUSTOMERNO = 0;
                                strcpy(VOLUMESTATE, " " );
#endif
                        }
         } dealervolumeS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of DEALERVOLUME **************************************/

 struct S_DEALERVOLUME {
         char BRANCHNO[7];
         char UID[11];
         char INVOICENO[11];
         char ORDERNOVSE[11];
         char ORDERNOKSC[11];
         char DATEINVOICE[11];
         char TIMEINVOICE[11];
         char INVOICEVOLUME[11 + 2];
         char VOLUME1[11 + 2];
         char VOLUME2[11 + 2];
         char VOLUME3[11 + 2];
         char VOLUME4[11 + 2];
         char CUSTOMERNO[11];
         char VOLUMESTATE[1 + 1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of DEALERVOLUME *********************/

 struct O_DEALERVOLUME {
         char BRANCHNO[7];
         char UID[11];
         char INVOICENO[11];
         char ORDERNOVSE[11];
         char ORDERNOKSC[11];
         char DATEINVOICE[11];
         char TIMEINVOICE[11];
         char INVOICEVOLUME[11];
         char VOLUME1[11];
         char VOLUME2[11];
         char VOLUME3[11];
         char VOLUME4[11];
         char CUSTOMERNO[11];
         char VOLUMESTATE[1];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of DEALERVOLUME ********************************/

 struct C_DEALERVOLUME {
         short BRANCHNO;
         long UID;
         long INVOICENO;
         long ORDERNOVSE;
         long ORDERNOKSC;
         long DATEINVOICE;
         long TIMEINVOICE;
         double INVOICEVOLUME;
         double VOLUME1;
         double VOLUME2;
         double VOLUME3;
         double VOLUME4;
         long CUSTOMERNO;
         char VOLUMESTATE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of DEALERVOLUME ******************************/

 struct I_DEALERVOLUME {
         short BRANCHNO;
         short UID;
         short INVOICENO;
         short ORDERNOVSE;
         short ORDERNOKSC;
         short DATEINVOICE;
         short TIMEINVOICE;
         short INVOICEVOLUME;
         short VOLUME1;
         short VOLUME2;
         short VOLUME3;
         short VOLUME4;
         short CUSTOMERNO;
         short VOLUMESTATE;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of DEALERVOLUME ****************************************/

#if defined (BUF_DESC)
 static struct buf_desc DEALERVOLUME_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEALERVOLUME_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_D, 11, 2 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
 };
#endif

/* description for datatypes of DEALERVOLUME **********************************/

 #define DEALERVOLUME_S390 \
         short BRANCHNO; \
         long UID; \
         long INVOICENO; \
         long ORDERNOVSE; \
         long ORDERNOKSC; \
         long DATEINVOICE; \
         long TIMEINVOICE; \
         double INVOICEVOLUME; \
         double VOLUME1; \
         double VOLUME2; \
         double VOLUME3; \
         double VOLUME4; \
         long CUSTOMERNO; \
         char VOLUMESTATE; \



/* Copy-Function Struct to single Data DEALERVOLUME ***************************/

 #define DEALERVOLUME_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         UID=_x_->UID;\
         INVOICENO=_x_->INVOICENO;\
         ORDERNOVSE=_x_->ORDERNOVSE;\
         ORDERNOKSC=_x_->ORDERNOKSC;\
         DATEINVOICE=_x_->DATEINVOICE;\
         TIMEINVOICE=_x_->TIMEINVOICE;\
         INVOICEVOLUME=_x_->INVOICEVOLUME;\
         VOLUME1=_x_->VOLUME1;\
         VOLUME2=_x_->VOLUME2;\
         VOLUME3=_x_->VOLUME3;\
         VOLUME4=_x_->VOLUME4;\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         VOLUMESTATE=_x_->VOLUMESTATE;\

 #define DEALERVOLUME_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->UID=UID;\
          _x_->INVOICENO=INVOICENO;\
          _x_->ORDERNOVSE=ORDERNOVSE;\
          _x_->ORDERNOKSC=ORDERNOKSC;\
          _x_->DATEINVOICE=DATEINVOICE;\
          _x_->TIMEINVOICE=TIMEINVOICE;\
          _x_->INVOICEVOLUME=INVOICEVOLUME;\
          _x_->VOLUME1=VOLUME1;\
          _x_->VOLUME2=VOLUME2;\
          _x_->VOLUME3=VOLUME3;\
          _x_->VOLUME4=VOLUME4;\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->VOLUMESTATE=VOLUMESTATE;\



/* FunctionNumber-Define of DealerVolume **************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of DealerVolume **********************************/


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

class CDEALERVOLUME : public ppDadeVirtual
{
        //data members
        public:
                dealervolumeS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<dealervolumeS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<dealervolumeS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<dealervolumeS>; Strip(s); dealervolumeS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<dealervolumeS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<dealervolumeS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<dealervolumeS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetBranchno() const     { return s.BRANCHNO; }
                long            GetUid() const  { return s.UID; }
                long            GetInvoiceno() const    { return s.INVOICENO; }
                long            GetOrdernovse() const   { return s.ORDERNOVSE; }
                long            GetOrdernoksc() const   { return s.ORDERNOKSC; }
                long            GetDateinvoice() const  { return s.DATEINVOICE; }
                long            GetTimeinvoice() const  { return s.TIMEINVOICE; }
                double          GetInvoicevolume() const        { return s.INVOICEVOLUME; }
                double          GetVolume1() const      { return s.VOLUME1; }
                double          GetVolume2() const      { return s.VOLUME2; }
                double          GetVolume3() const      { return s.VOLUME3; }
                double          GetVolume4() const      { return s.VOLUME4; }
                long            GetCustomerno() const   { return s.CUSTOMERNO; }
                char            GetVolumestate() const  { return s.VOLUMESTATE[0]; }
                const dealervolumeS& GetStruct() const { return s; }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetUid(long t) { s.UID = t; }
                void            SetInvoiceno(long t) { s.INVOICENO = t; }
                void            SetOrdernovse(long t) { s.ORDERNOVSE = t; }
                void            SetOrdernoksc(long t) { s.ORDERNOKSC = t; }
                void            SetDateinvoice(long t) { s.DATEINVOICE = t; }
                void            SetTimeinvoice(long t) { s.TIMEINVOICE = t; }
                void            SetInvoicevolume(double t) { s.INVOICEVOLUME = t; }
                void            SetVolume1(double t) { s.VOLUME1 = t; }
                void            SetVolume2(double t) { s.VOLUME2 = t; }
                void            SetVolume3(double t) { s.VOLUME3 = t; }
                void            SetVolume4(double t) { s.VOLUME4 = t; }
                void            SetCustomerno(long t) { s.CUSTOMERNO = t; }
                void            SetVolumestate(char t) { s.VOLUMESTATE[0] = t; s.VOLUMESTATE[1] = '\0';}
                void            SetStruct(const dealervolumeS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CDEALERVOLUME()  //constructor
                {
                        ::buf_default((void *)&s, DEALERVOLUME_BES, DEALERVOLUME_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CDEALERVOLUME()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, DEALERVOLUME_BES, DEALERVOLUME_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, DEALERVOLUME_BES, DEALERVOLUME_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, DEALERVOLUME_BES, DEALERVOLUME_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_DEALERVOLUME& d)
                {
#ifdef WIN32
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, DEALERVOLUME_BES, DEALERVOLUME_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of DEALERVOLUME *****************************************/

 #define DEALERVOLUME_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         UID integer default 0 not null,\
         INVOICENO integer default 0 not null,\
         ORDERNOVSE integer default 0 not null,\
         ORDERNOKSC integer default 0 not null,\
         DATEINVOICE integer default 0 not null,\
         TIMEINVOICE integer default 0 not null,\
         INVOICEVOLUME decimal(11,2) default 0 not null,\
         VOLUME1 decimal(11,2) default 0 not null,\
         VOLUME2 decimal(11,2) default 0 not null,\
         VOLUME3 decimal(11,2) default 0 not null,\
         VOLUME4 decimal(11,2) default 0 not null,\
         CUSTOMERNO integer default 0 not null,\
         VOLUMESTATE char(1) default " " not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of DEALERVOLUME ***************************************/

 #define DEALERVOLUME_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_dealervolume_1 on _X_(\
              BranchNo,\
              uid,\
              DateInvoice,\
              InvoiceNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index i_dealervolume_2 on _X_(\
              BranchNo,\
              CustomerNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of DEALERVOLUME ***************************************/

 #define DEALERVOLUME_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_dealervolume_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_dealervolume_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

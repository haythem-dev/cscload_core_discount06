#ifndef __PP_GENERALCALCAVP_H_
#define __PP_GENERALCALCAVP_H_

/******************************************************************************/
/* c:\temp3\GeneralCalcAVP ****************************************************/
/******************************************************************************/

/* Length-Define of GENERALCALCAVP ********************************************/

  #define L_GENERALCALCAVP_PRICE_GROUP 6
  #define L_GENERALCALCAVP_PERCENTPRESCRIPT 5
  #define N_GENERALCALCAVP_PERCENTPRESCRIPT 2
  #define L_GENERALCALCAVP_PERCENTNOPERSCRIPT 5
  #define N_GENERALCALCAVP_PERCENTNOPERSCRIPT 2
  #define L_GENERALCALCAVP_PREIS_TYP 6

/* Length/Count-Define of GENERALCALCAVP **************************************/

  #define LS_GENERALCALCAVP_PRICE_GROUP 5 + 1
  #define LS_GENERALCALCAVP_PERCENTPRESCRIPT 5 + 2
  #define LS_GENERALCALCAVP_PERCENTNOPERSCRIPT 5 + 2
  #define LS_GENERALCALCAVP_PREIS_TYP 5 + 1

  #define GENERALCALCAVPPRICE_GROUP 0
  #define GENERALCALCAVPPERCENTPRESCRIPT 1
  #define GENERALCALCAVPPERCENTNOPERSCRIPT 2
  #define GENERALCALCAVPPREIS_TYP 3

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define GENERALCALCAVP_H
 #define GENERALCALCAVP_ANZ ( sizeof(GENERALCALCAVP_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of GENERALCALCAVP ************************************************/

 #define GENERALCALCAVP_LISTE \
         GENERALCALCAVP.PRICE_GROUP,\
         GENERALCALCAVP.PERCENTPRESCRIPT,\
         GENERALCALCAVP.PERCENTNOPERSCRIPT,\
         GENERALCALCAVP.PREIS_TYP

 #define GENERALCALCAVP_LISTE_390 \
         PRICE_GROUP,\
         PERCENTPRESCRIPT,\
         PERCENTNOPERSCRIPT,\
		 PREIS_TYP

 #define GENERALCALCAVP_PLISTE \
         "GENERALCALCAVP.PRICE_GROUP,"\
         "GENERALCALCAVP.PERCENTPRESCRIPT,"\
         "GENERALCALCAVP.PERCENTNOPERSCRIPT,"\
         "GENERALCALCAVP.PREIS_TYP"

 #define GENERALCALCAVP_PELISTE \
         "PRICE_GROUP,"\
         "PERCENTPRESCRIPT,"\
         "PERCENTNOPERSCRIPT,"\
         "PREIS_TYP"

 #define GENERALCALCAVP_UPDLISTE \
         "PRICE_GROUP=?,"\
         "PERCENTPRESCRIPT=?,"\
         "PERCENTNOPERSCRIPT=?,"\
         "PREIS_TYP=?"

/* SqlMacros-Define of GENERALCALCAVP *****************************************/

 #define GENERALCALCAVP_ZEIGER(x) \
         :x->PRICE_GROUP,\
         :x->PERCENTPRESCRIPT,\
         :x->PERCENTNOPERSCRIPT,\
         :x->PREIS_TYP

 #define GENERALCALCAVP_ZEIGERSEL(x) \
         :x->PRICE_GROUP,\
         :x->PERCENTPRESCRIPT,\
         :x->PERCENTNOPERSCRIPT,\
         :x->PREIS_TYP

 #define GENERALCALCAVP_UPDATE(x) \
         GENERALCALCAVP.PRICE_GROUP=:x->PRICE_GROUP,\
         GENERALCALCAVP.PERCENTPRESCRIPT=:x->PERCENTPRESCRIPT,\
         GENERALCALCAVP.PERCENTNOPERSCRIPT=:x->PERCENTNOPERSCRIPT,\
         GENERALCALCAVP.PREIS_TYP=:x->PREIS_TYP

/* SqlMacros390-Define of GENERALCALCAVP **************************************/

 #define GENERALCALCAVP_ZEIGER_390 \
         :PRICE_GROUP,\
         :PERCENTPRESCRIPT,\
         :PERCENTNOPERSCRIPT,\
         :PREIS_TYP

 #define GENERALCALCAVP_UPDATE_390 \
         PRICE_GROUP=:PRICE_GROUP,\
         PERCENTPRESCRIPT=:PERCENTPRESCRIPT,\
         PERCENTNOPERSCRIPT=:PERCENTNOPERSCRIPT,\
         PREIS_TYP=:PREIS_TYP

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of GENERALCALCAVP *****************************************/

 #ifndef TRANSCLASS
 typedef struct N_GENERALCALCAVP {
         short PRICE_GROUP;
         double PERCENTPRESCRIPT;
         double PERCENTNOPERSCRIPT;
         short PREIS_TYP;
        } generalcalcavpS;
 #else /*TRANSCLASS*/
 typedef struct N_GENERALCALCAVP {
         short PRICE_GROUP;
         double PERCENTPRESCRIPT;
         double PERCENTNOPERSCRIPT;
         short PREIS_TYP;

			bool operator==(const N_GENERALCALCAVP& right) const {
			return(
				PRICE_GROUP == right.PRICE_GROUP &&
				PERCENTPRESCRIPT == right.PERCENTPRESCRIPT &&
				PERCENTNOPERSCRIPT == right.PERCENTNOPERSCRIPT &&
				PREIS_TYP == right.PREIS_TYP
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				PRICE_GROUP = 0;
				PERCENTPRESCRIPT = 0;
				PERCENTNOPERSCRIPT = 0;
				PREIS_TYP = 0;
#endif
			}
         } generalcalcavpS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of GENERALCALCAVP ************************************/

 struct S_GENERALCALCAVP {
         char PRICE_GROUP[7];
         char PERCENTPRESCRIPT[5 + 2];
         char PERCENTNOPERSCRIPT[5 + 2];
         char PREIS_TYP[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of GENERALCALCAVP *******************/

 struct O_GENERALCALCAVP {
         char PRICE_GROUP[7];
         char PERCENTPRESCRIPT[5];
         char PERCENTNOPERSCRIPT[5];
         char PREIS_TYP[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of GENERALCALCAVP ******************************/

 struct C_GENERALCALCAVP {
         short PRICE_GROUP;
         double PERCENTPRESCRIPT;
         double PERCENTNOPERSCRIPT;
         short PREIS_TYP;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of GENERALCALCAVP ****************************/

 struct I_GENERALCALCAVP {
         short PRICE_GROUP;
         short PERCENTPRESCRIPT;
         short PERCENTNOPERSCRIPT;
         short PREIS_TYP;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of GENERALCALCAVP **************************************/

#if defined (BUF_DESC)
 static struct buf_desc GENERALCALCAVP_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc GENERALCALCAVP_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of GENERALCALCAVP ********************************/

 #define GENERALCALCAVP_S390 \
         short PRICE_GROUP; \
         double PERCENTPRESCRIPT; \
         double PERCENTNOPERSCRIPT; \
         short PREIS_TYP; \



/* Copy-Function Struct to single Data GENERALCALCAVP *************************/

 #define GENERALCALCAVP_S390_COPY_TO_SINGLE(_x_) \
         PRICE_GROUP=_x_->PRICE_GROUP;\
         PERCENTPRESCRIPT=_x_->PERCENTPRESCRIPT;\
         PERCENTNOPERSCRIPT=_x_->PERCENTNOPERSCRIPT;\
         PREIS_TYP=_x_->PREIS_TYP;\

 #define GENERALCALCAVP_S390_COPY_TO_STRUCT(_x_) \
          _x_->PRICE_GROUP=PRICE_GROUP;\
          _x_->PERCENTPRESCRIPT=PERCENTPRESCRIPT;\
          _x_->PERCENTNOPERSCRIPT=PERCENTNOPERSCRIPT;\
          _x_->PREIS_TYP=PREIS_TYP;\



/* FunctionNumber-Define of GeneralCalcAVP ************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of GeneralCalcAVP ********************************/


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

class CGENERALCALCAVP : public ppDadeVirtual
{
	//data members
	public:
		generalcalcavpS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<generalcalcavpS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<generalcalcavpS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<generalcalcavpS>; Strip(s); generalcalcavpS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<generalcalcavpS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<generalcalcavpS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<generalcalcavpS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		short		GetPrice_group() const	{ return s.PRICE_GROUP; }
		double		GetPercentprescript() const	{ return s.PERCENTPRESCRIPT; }
		double		GetPercentnoperscript() const	{ return s.PERCENTNOPERSCRIPT; }
		short		GetPreis_typ() const	{ return s.PREIS_TYP; }
		const generalcalcavpS& GetStruct() const { return s; }
		void 		SetPrice_group(short t) { s.PRICE_GROUP = t; }
		void 		SetPercentprescript(double t) { s.PERCENTPRESCRIPT = t; }
		void 		SetPercentnoperscript(double t) { s.PERCENTNOPERSCRIPT = t; }
		void 		SetPreis_typ(short t) { s.PREIS_TYP = t; }
		void 		SetStruct(const generalcalcavpS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CGENERALCALCAVP()  //constructor
		{
			::buf_default((void *)&s, GENERALCALCAVP_BES, GENERALCALCAVP_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CGENERALCALCAVP()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, GENERALCALCAVP_BES, GENERALCALCAVP_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, GENERALCALCAVP_BES, GENERALCALCAVP_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, GENERALCALCAVP_BES, GENERALCALCAVP_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_GENERALCALCAVP& d)
		{
#ifdef WIN32
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, GENERALCALCAVP_BES, GENERALCALCAVP_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of GENERALCALCAVP ***************************************/

 #define GENERALCALCAVP_CREATE(x) exec sql create table x (\
         PRICE_GROUP smallint default 0 not null,\
         PERCENTPRESCRIPT decimal(5,2) default 0 not null,\
         PERCENTNOPERSCRIPT decimal(5,2) default 0 not null,\
         PREIS_TYP smallint default 0 not null) in ksc extent size 8 next size 8 lock mode row;



/* CreateIndexStatement of GENERALCALCAVP *************************************/

 #define GENERALCALCAVP_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create unique index i_GeneralCalcAVP_1 on _X_(\
              price_group,\
              preis_typ ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of GENERALCALCAVP *************************************/

 #define GENERALCALCAVP_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_GeneralCalcAVP_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

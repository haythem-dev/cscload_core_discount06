#ifndef __PP_REBATEPRICE_H_
#define __PP_REBATEPRICE_H_

/******************************************************************************/
/* d:\prj\AA\UNIX\AAPSERV\RebatePrice *****************************************/
/******************************************************************************/

/* Length-Define of REBATEPRICE ***********************************************/

  #define L_REBATEPRICE_DISCOUNTVALUEPCT 5
  #define N_REBATEPRICE_DISCOUNTVALUEPCT 2
  #define L_REBATEPRICE_PREISEKAPO 9
  #define N_REBATEPRICE_PREISEKAPO 2
  #define L_REBATEPRICE_PREISFAKTUR 9
  #define N_REBATEPRICE_PREISFAKTUR 2

/* Length/Count-Define of REBATEPRICE *****************************************/

  #define LS_REBATEPRICE_DISCOUNTVALUEPCT 5 + 2
  #define LS_REBATEPRICE_PREISEKAPO 9 + 2
  #define LS_REBATEPRICE_PREISFAKTUR 9 + 2

  #define REBATEPRICEDISCOUNTVALUEPCT 0
  #define REBATEPRICEPREISEKAPO 1
  #define REBATEPRICEPREISFAKTUR 2

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define REBATEPRICE_H
 #define REBATEPRICE_ANZ (int) ( sizeof(REBATEPRICE_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of REBATEPRICE ***************************************************/

 #define REBATEPRICE_LISTE \
         DISCOUNT.DISCOUNTVALUEPCT,\
         KDAUFTRAGPOS.PREISEKAPO,\
         KDAUFTRAGPOS.PREISFAKTUR

 #define REBATEPRICE_LISTE_390 \
         DISCOUNTVALUEPCT,\
         PREISEKAPO,\
         PREISFAKTUR

 #define REBATEPRICE_PLISTE \
         "DISCOUNT.DISCOUNTVALUEPCT,"\
         "KDAUFTRAGPOS.PREISEKAPO,"\
         "KDAUFTRAGPOS.PREISFAKTUR"

 #define REBATEPRICE_PELISTE \
         "DISCOUNTVALUEPCT,"\
         "PREISEKAPO,"\
         "PREISFAKTUR"

 #define REBATEPRICE_UPDLISTE \
         "DISCOUNTVALUEPCT=?,"\
         "PREISEKAPO=?,"\
         "PREISFAKTUR=?"

/* SqlMacros-Define of REBATEPRICE ********************************************/

 #define REBATEPRICE_ZEIGER(x) \
         :x->DISCOUNTVALUEPCT,\
         :x->PREISEKAPO,\
         :x->PREISFAKTUR

 #define REBATEPRICE_ZEIGERSEL(x) \
         :x->DISCOUNTVALUEPCT,\
         :x->PREISEKAPO,\
         :x->PREISFAKTUR

 #define REBATEPRICE_UPDATE(x) \
         DISCOUNT.DISCOUNTVALUEPCT=:x->DISCOUNTVALUEPCT,\
         KDAUFTRAGPOS.PREISEKAPO=:x->PREISEKAPO,\
         KDAUFTRAGPOS.PREISFAKTUR=:x->PREISFAKTUR

/* SqlMacros390-Define of REBATEPRICE *****************************************/

 #define REBATEPRICE_ZEIGER_390 \
         :DISCOUNTVALUEPCT,\
         :PREISEKAPO,\
         :PREISFAKTUR

 #define REBATEPRICE_UPDATE_390 \
         DISCOUNTVALUEPCT=:DISCOUNTVALUEPCT,\
         PREISEKAPO=:PREISEKAPO,\
         PREISFAKTUR=:PREISFAKTUR

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of REBATEPRICE ********************************************/

 #ifndef TRANSCLASS
 typedef struct N_REBATEPRICE {
         double DISCOUNTVALUEPCT;
         double PREISEKAPO;
         double PREISFAKTUR;
        } rebatepriceS;
 #else /*TRANSCLASS*/
 typedef struct N_REBATEPRICE {
         double DISCOUNTVALUEPCT;
         double PREISEKAPO;
         double PREISFAKTUR;

			bool operator==(const N_REBATEPRICE& right) const {
			return(
				DISCOUNTVALUEPCT == right.DISCOUNTVALUEPCT &&
				PREISEKAPO == right.PREISEKAPO &&
				PREISFAKTUR == right.PREISFAKTUR
				);
			}
			void clear() {
#ifdef WIN32
			memset((char*)this,0,sizeof(*this));
#else
				DISCOUNTVALUEPCT = 0;
				PREISEKAPO = 0;
				PREISFAKTUR = 0;
#endif
			}
         } rebatepriceS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of REBATEPRICE ***************************************/

 struct S_REBATEPRICE {
         char DISCOUNTVALUEPCT[5 + 2];
         char PREISEKAPO[9 + 2];
         char PREISFAKTUR[9 + 2];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of REBATEPRICE **********************/

 struct O_REBATEPRICE {
         char DISCOUNTVALUEPCT[5];
         char PREISEKAPO[9];
         char PREISFAKTUR[9];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of REBATEPRICE *********************************/

 struct C_REBATEPRICE {
         double DISCOUNTVALUEPCT;
         double PREISEKAPO;
         double PREISFAKTUR;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of REBATEPRICE *******************************/

 struct I_REBATEPRICE {
         short DISCOUNTVALUEPCT;
         short PREISEKAPO;
         short PREISFAKTUR;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of REBATEPRICE *****************************************/

#if defined (BUF_DESC)
 static struct buf_desc REBATEPRICE_BES [] =
 {
   { TYP_D, 5, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc REBATEPRICE_BES [] =
 {
   { TYP_D, 5, 2 },
   { TYP_D, 9, 2 },
   { TYP_D, 9, 2 },
 };
#endif

/* description for datatypes of REBATEPRICE ***********************************/

 #define REBATEPRICE_S390 \
         double DISCOUNTVALUEPCT; \
         double PREISEKAPO; \
         double PREISFAKTUR; \



/* Copy-Function Struct to single Data REBATEPRICE ****************************/

 #define REBATEPRICE_S390_COPY_TO_SINGLE(_x_) \
         DISCOUNTVALUEPCT=_x_->DISCOUNTVALUEPCT;\
         PREISEKAPO=_x_->PREISEKAPO;\
         PREISFAKTUR=_x_->PREISFAKTUR;\

 #define REBATEPRICE_S390_COPY_TO_STRUCT(_x_) \
          _x_->DISCOUNTVALUEPCT=DISCOUNTVALUEPCT;\
          _x_->PREISEKAPO=PREISEKAPO;\
          _x_->PREISFAKTUR=PREISFAKTUR;\



/* FunctionNumber-Define of RebatePrice ***************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of RebatePrice ***********************************/


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

class CREBATEPRICE : public ppDadeVirtual
{
	//data members
	public:
		rebatepriceS s;
		int  rc;
		char error_msg[81];
	private:
		bool bOpenCursor;
		bool bEndOfSelect;
		int  FncNumber;
		int  CursorPos;
		int  AnzPos;
		vector<rebatepriceS> *pl; // pointer to class list

	//functions
	public:

		unsigned int	GetSize() const { return pl ? pl->size() : 0; }
		void 		ClearStruct() { s.clear(); }
		bool 		SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
		bool 		SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<rebatepriceS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
		bool 		InsList() { if ( !pl ) pl = new vector<rebatepriceS>; Strip(s); rebatepriceS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
		bool 		DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<rebatepriceS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
		vector<rebatepriceS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
		vector<rebatepriceS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
		double		GetDiscountvaluepct() const	{ return s.DISCOUNTVALUEPCT; }
		double		GetPreisekapo() const	{ return s.PREISEKAPO; }
		double		GetPreisfaktur() const	{ return s.PREISFAKTUR; }
		const rebatepriceS& GetStruct() const { return s; }
		void 		SetDiscountvaluepct(double t) { s.DISCOUNTVALUEPCT = t; }
		void 		SetPreisekapo(double t) { s.PREISEKAPO = t; }
		void 		SetPreisfaktur(double t) { s.PREISFAKTUR = t; }
		void 		SetStruct(const rebatepriceS& t) { s = t; }

	//virtual functions
	public:

		int	Load(int pos=0) { return 1; }
		int	Save(int pos=0) { return 1; }
		int	Delete(int pos=0) { return 1; }
		int	SelList(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListHist(int FetchRel = 1,int pos=0) { return 1; }
		int	SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
		CREBATEPRICE()  //constructor
		{
			::buf_default((void *)&s, REBATEPRICE_BES, REBATEPRICE_ANZ);
			bOpenCursor		= false;
			bEndOfSelect	= false;
			FncNumber		= 0;
			CursorPos		= 0;
			AnzPos			= 0;
			rc  			= 0;
			pl = NULL;
			s.clear();
		}

		virtual ~CREBATEPRICE()  //destructor
		{
			if(pl) {
				delete pl;
				pl = NULL;
			}
		}

		void buf_default()  //buffer init
		{
			::buf_default((void *)&s, REBATEPRICE_BES, REBATEPRICE_ANZ);
		}

		int Server(int fkt_nr,int pos=0) // socket server call
		{
			#ifdef WIN32
			rc = ::ServerNr(pos, fkt_nr, (void *)&s, REBATEPRICE_BES, REBATEPRICE_ANZ, error_msg);
			#else
			rc = ::Server(fkt_nr, (void *)&s, REBATEPRICE_BES, REBATEPRICE_ANZ, error_msg);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

	private:

		void Strip(N_REBATEPRICE& d)
		{
#ifdef WIN32
#endif
		}


		int UniqueServerCall(int FncNr,int pos=0)
		{
			#ifndef __DADE_LOAD__
			rc = ::ServerNr(pos, FncNr, (void *)&s, REBATEPRICE_BES, REBATEPRICE_ANZ, error_msg);
			#else
			rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
			#endif
			if (rc<0) FehlerBehandlung( rc, error_msg );
			return rc;
		}

};

#endif

/* CreateSqlStatement of REBATEPRICE ******************************************/

 #define REBATEPRICE_CREATE(x) exec sql create table x (\
         DISCOUNTVALUEPCT decimal(5,2) default 0 not null,\
         PREISEKAPO decimal(9,2) default 0 not null,\
         PREISFAKTUR decimal(9,2) default 0 not null) extent size 80 next size 8 lock mode row;



/* CreateIndexStatement of REBATEPRICE ****************************************/

 #define REBATEPRICE_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create   index i_discount_1 on _X_(\
              BranchNo,\
              ArticleNo,\
              DiscountType,\
              PharmacyGroupId );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index i_discount_2 on _X_(\
              BranchNo,\
              DiscountGrpNo,\
              PharmacyGroupId );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index i_discount_3 on _X_(\
              BranchNo,\
              ArticleNo,\
              CustomerNo );\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of REBATEPRICE ****************************************/

 #define REBATEPRICE_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_discount_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_discount_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_discount_3;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

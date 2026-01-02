#ifndef PXDISCOUNTDEF_INC
#define PXDISCOUNTDEF_INC

/*----------------------------------------------------------------------------*/
/*  Discount Type enumeration.                                                */
/*----------------------------------------------------------------------------*/
enum  tDiscountType
{
   DiscType_Default,                 // default type        = 0
   DiscType_Shortrabatt,             // shortrabatt         = 1
   DiscType_Team,                    // aktionservice       = 2
   DiscType_Diabetes,                // diabetes            = 3
   DiscType_Generika,                // generikarabatt      = 4
   DiscType_Partenariat,             // partenariat         = 5
   DiscType_Overdrive,               // overdrive           = 6
   DiscType_PhoenixMagic,            // phoenix magic       = 7
   DiscType_Promotion,               // promotion rebate    = 8(BG)
   DiscType_Tender,                  // Tender conditions   = 9(BG)
   DiscType_ShortLine = 11,          // Short Liner Rebate  = 11(FR)
   DiscType_Last,
   DiscType_CashDiscount             // cashdiscount(barrabatt) = 7
};

//enum  tDiscountKey
//{
//   DiscUndefined,
//   DiscSupplier,                     // Discount from supplier
//   DiscWholeSale,                    // Discount from wholesale
//   DiscBase
//};

enum tDiscountCategory
{
	DiscCategory_Common = 0,
	DiscCategory_PharmacyGroup = 1,
	DiscCategory_Customer = 2,
	DiscCategory_Manual = 3
};

/*----------------------------------------------------------------------------*/
/*  Discount Specification enumeration.                                       */
/*----------------------------------------------------------------------------*/
enum  tDiscountSpec
{
   DiscSpec_Default,                 // default spec                       = 0
   DiscSpec_LogisticAddition,        // LogisticAddition                   = 1
   DiscSpec_WholeSale,               // Wholesale( HR)                     = 2
   DiscSpec_Retail,                  // Retail( HR)                        = 3
   DiscSpec_PosMonthly,              // Month Rabatt per Position( AU)     = 4
   DiscSpec_MonthlyBuy,              // Month Rabatt on Monthly buy( AU)   = 5
   DiscSpec_QuaterlyBuy,             // Month Rabatt on Quarterly buy( AU) = 6
   DiscSpec_WholeSale_Ind,           // Wholesale Industrie(WI)( HR)       = 7
   DiscSpec_VoluntarySale,           // VoluntarySale( BG Freiverkauf)     = 8
   DiscSpec_HealthFund,              // HealthFund( BG Krankenkasse)       = 9
   DiscSpec_Occasions,               // Occasions (SR)                     = 10
   DiscSpec_Wholesale_Surcharge,	 // Wholesale Surcharge (??)		   = 11
   DiscSpec_DataTransfer,			 // LogisticsAddtion Special Case (CH) = 12
   // for internal use
   DiscSpec_SpecialPrice = 50,       // Special Price (SP) ( HR)           = 50
   DiscSpec_Last
};

/*----------------------------------------------------------------------------*/
/*  Discount BestBuy enumeration.                                             */
/*----------------------------------------------------------------------------*/
enum  tBestBuy
{
   BestBuy_NatraDefault          = 1,   // NatraDefault                    = 1
   BestBuy_NatraTeam,                   // NatraTeam                       = 2
   BestBuy_NatraDiabetes,               // NatraDiabetes                   = 3
   BestBuy_FixedPriceDefault,           // FixedPrice Default              = 4
   BestBuy_FixedPriceTeam,              // FixedPrice Team                 = 5
   BestBuy_FixedPriceDiabetes,          // FixedPrice Diabetes             = 6
   BestBuy_ValuePctCash,                // ValuePercentage Cash            = 7
   BestBuy_ValuePctShort,               // ValuePercentage Short           = 8
   BestBuy_ValuePctGenerika,            // ValuePercentage Generika        = 9
   BestBuy_ValuePctPartenariat,         // ValuePercentage Partenariat     = 10
   BestBuy_ValuePctWholeSale,           // ValuePercentage WholeSale       = 11
   BestBuy_ValuePctRetail,              // ValuePercentage Retail          = 12
   BestBuy_ValuePctTena,                // ValuePercentage Retail          = 13
   BestBuy_LogisticAddition,            // LogisticAddition                = 14
   BestBuy_FixedPricePharmGroup,        // FixedPricePharmGroup            = 15
   BestBuy_ValuePctPharmgroupExcluded,  // ValuePctPharmgroupExcluded      = 16
   BestBuy_ValuePctPhoenixMagic,        // ValuePercentage Phoenix Magic   = 17
   BestBuy_ValuePctOverdrive,           // ValuePercentage Overdrive       = 18
   BestBuy_ValuePctWholeSaleInd,        // ValuePercentage WholeSale Ind.  = 19
   BestBuy_SpecialPrice,                // special price (HR)              = 20
   BestBuy_GrossProfitPct,              // Grossprofitpct special pct(BG)  = 21
   BestBuy_ValuePctShortLine,           // ValuePercentage ShortLine       = 22
   BestBuy_FixedDiscountValue,          // fixed discount value		       = 23
   BestBuy_ValuePctOMG,					// ValuePercentage OMG in CH       = 24
   BestBuy_LogisticDataTransfer,		// LogisticsAdd.(Herst+Cust) in CH = 25
   BestBuy_ValuePctCashAssorted,		// ValuePercentage Assorted (CH)   = 26
   BestBuy_Last
};
/*----------------------------------------------------------------------------*/
/*  Discount Type contained within discountlist                               */
/*----------------------------------------------------------------------------*/
enum  tDiscountList
{
   NatraDefault          = 1,   // NatraDefault                    = 1
   NatraTeam,                   // NatraTeam                       = 2
   NatraDiabetes,               // NatraDiabetes                   = 3
   FixedPriceDefault,           // FixedPrice Default              = 4
   FixedPriceTeam,              // FixedPrice Team                 = 5
   FixedPriceDiabetes,          // FixedPrice Diabetes             = 6
   ValuePctCash,                // ValuePercentage Cash            = 7
   ValuePctShort,               // ValuePercentage Short           = 8
   ValuePctGenerika,            // ValuePercentage Generika        = 9
   ValuePctPartenariat,         // ValuePercentage Partenariat     = 10
   ValuePctWholeSale,           // ValuePercentage WholeSale       = 11
   ValuePctRetail,              // ValuePercentage Retail          = 12
   ValuePctTena,                // ValuePercentage Retail          = 13
   LogisticAddition,            // LogisticAdditio                 = 14
   FixedPricePharmGroup,        // FixedPricePharmGroup            = 15
   ValuePctPharmgroupExcluded,  // ValuePctPharmgroupExcluded      = 16
   ValuePctPhoenixMagic,        // ValuePercentage Phoenix Magic   = 17
   ValuePctOverdrive,           // ValuePercentage Overdrive       = 18
   ValuePctWholeSaleInd,        // ValuePercentage WholeSale Ind.  = 19
   SpecialPriceHR,              // special price (HR)              = 20
   ValueGrossProfitPct,         // Grossprofitpct special pct(BG)  = 21
   ValuePctShortLine,           // ValuePercentage Short Line      = 22
   FixedDiscountValue,          // FixedDiscountValue Short Line   = 23
   ValuePctOMG,                 // ValuePercentage OMG             = 24
   LogisticDataTransfer,		// LogisticsAdd.(Herst+Cust)       = 25
   ValuePctCashAssorted,		// ValuePercentage Assorted        = 26
   DiscountList_Last
};

#define cMaxKindOffRebate  50
#define cMaxCasCadeNo      10

#endif

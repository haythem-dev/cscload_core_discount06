#ifndef TPULCONVERT_H_INCLUDED
#define TPULCONVERT_H_INCLUDED

/*** DECLARATION **************************************************************/

 void ConvertManufacturerArticle( dezapO *d, dezapherstelSTR *a, struct AUFB des[] );
 void ConvertArticle( dezapO *d, dezapzartikelSTR *a, const dezapcsafetydatasheetSTR *s, struct AUFB des[], parameter *p );
 void ConvertPrice( dezapO *d, dezapzartpreisSTR *p, struct AUFB des[], parameter *par );
 /* bool ConvertEan( dezapeanO *d, dezapeanSTR *p, struct AUFB des[] ); */

 bool ConvertDksoa( dezapdksoaO *d, dezapcbaselistarticlesSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDkean( dezapeanO *d, dezapeanSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDkaff( dezapdkaffO *d, dezapcarticlelangSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDkegr( dezapdkegrO *d, dezapcpharmgrpSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDkste( dezapdksteO *d, dezapcartcompackSTR *p, dezapccpvalidityperiodSTR *v, struct AUFB des[], rterror rc );
 bool ConvertDkwgr( dezapdkwgrO *d, dezapzdkwgrSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDkiwg( dezapdkiwgO *d, dezapzdkiwgSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDktgr( dezapdktgrO *d, dezapzdktgrSTR *p, struct AUFB des[], rterror rc );
/* bool ConvertDkbgr( dezapdkbgrO *d, dezapzdkbgrSTR *p, struct AUFB des[], rterror rc ); */
/* bool ConvertDkwir( dezapdkwirO *d, dezapzdkwirSTR *p, struct AUFB des[], rterror rc ); */
 bool ConvertDkatx( dezapdkatxO *d, dezapcarticletextSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDkcrr( dezapdkcrrO *d, dezapzchargenrueckrufSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDkaco( dezapdkacoO *d, dezapcarticlecodesSTR *p, struct AUFB des[], rterror rc );
/* void ConvertDkgal( dezapdkgalO *d, dezapcgaloartSTR *p, struct AUFB des[], rterror rc );
   void ConvertDkgah( dezapdkgahO *d, dezapcgalocomSTR *p, struct AUFB des[], rterror rc ); */
 bool ConvertDklid( dezapdklidO *d, dezapherstel_dispoSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDkrgr( dezapdkrgrO *d, dezapzrabgrpSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDkzab( dezapdkzabO *d, dezapzzahlbedSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDkrab( dezapdkrabO *d, dezapcdiscountSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDkral( dezapdkralO *d, dezapcdisclistSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDkser( dezapdkserO *d, dezapcservicesSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDkrpg( dezapdkrpgO *d, dezapcdiscgrpSTR *o, dezapcdiscgrpmemSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDkazb( dezapdkazbO *d, dezapzartikelSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDepau( dezapdepauO *d, dezapzartikelSTR *p, struct AUFB des[], rterror rc );
/* void ConvertDkgfg( dezapdkgfgO *d, dezapzartikelSTR *p, struct AUFB des[], rterror rc ); */
 void ConvertDrram( dezapdrramO *d, dezapcdiscmodelSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDkmrs( dezapdkmrsO *d, dezapcmonthdiscsortSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDkghz( dezapdkghzO *d, dezapchighpaymtargetfeeSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDkkgr( dezapdkkgrO *d, dezapccustomergroupSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDkmvs( dezapdkmvsO *d, dezapcmonthvirtsortSTR *p, struct AUFB des[], rterror rc );
/* bool ConvertDkllv( dezapdkllvO *d, dezapccustservicesSTR *p, struct AUFB des[], rterror rc ); */
 bool ConvertDklkr( dezapdklkrO *d, dezapcstoragecriteriaSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDklkz( dezapdklkzO *d, dezapcintrastatcountrySTR *p, struct AUFB des[], rterror rc );
 bool ConvertDkfok( dezapdkfokO *d, dezapcformtypesSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDkrbf( dezapdkrbfO *d, dezapcdiscformSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDksps( dezapdkspsO *d, dezapcshipperSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDkaua( dezapdkauaO *d, dezapcordertypeSTR *p, struct AUFB des[], rterror rc );
 bool ConvertDkpro( dezapdkproO *d, dezapcpromotionsSTR *p, struct AUFB des[], rterror rc );
 void ConvertDkain( dezapdkainO *d, dezapcregistersSTR *p, struct AUFB des[], rterror rc );
/* void ConvertCgalonam( dezapdkgalO *d, dezapcgalonamSTR *p, struct AUFB des[] ); */
 void ConvertSecondary( dezapO *d, dezapzartsekbezSTR *s, struct AUFB des[] );
 void ConvertDeposit( dezapO *d, dezapcdeposittypesSTR *s, struct AUFB des[] );
 void ConvertGoodsgroup( dezapO *d, dezapzartwgSTR *g, struct AUFB des[], parameter *p );
 void ConvertCodes( dezapO *d, dezapcarticlecodesSTR *g, struct AUFB des[], parameter *p );
 void ConvertFixedAmount( dezapO *d, dezapzartfeb2STR *a, struct AUFB des[] );
 void ConvertArticleExt( dezapO *d, dezapcarticleextSTR *a );
 void ConvertZautidemsperre( dezapO *d, dezapzautidemsperreSTR *a, struct AUFB des[] );
 void ConvertArtve( dezapO *d, dezapartveSTR *a, struct AUFB des[], parameter *p );
 void ConvertAustria( dezapO *d, dezapzartaustriaSTR *a, struct AUFB des[] );
 void ConvertCroatia( dezapO *d, dezapzartcroatiaSTR *a, struct AUFB des[] );
 void ConvertCroatiaSpecial( dezapO *d, dezapzartcroatiaSTR *a, dezapzartpreisSTR *p, struct AUFB des[] );
 void ConvertBulgaria( dezapO *d, dezapzartbulgariaSTR *a, dezapzartpreisSTR *p, struct AUFB des[] );
 void ConvertSerbia( dezapO *d, dezapzartserbiaSTR *a, struct AUFB des[] );
 void ConvertManufacturer( dezapdklifO *d, dezapherstelSTR *a, struct AUFB des[], parameter *p );
 void ConvertSalesCondition( dezapdklifO *d, dezaphsalescondSTR *a, struct AUFB des[], parameter *p, int i );
 void ConvertSwitzerland( dezapO *d, dezapzartswitzerlandSTR *a, struct AUFB des[] );
 void ConvertFrance( dezapO *d, dezapzartfranceSTR *a, struct AUFB des[], parameter *p );
 void ConvertDkris( dezapdkrisO *d, dezapzartverkSTR *p, struct AUFB des[], rterror rc );
 void ConvertBatchInfo( dezapO *d, dezapzartikelSTR *a, dezapzartswitzerlandSTR *s, struct AUFB des[], parameter *p );

 void InitCustGrpFlagArray ();
 void FillCustGrpFlagArray( short scustomergrpflag, short sindex_skkgr );

 void InitOrderTypeFlagArray ();
 void FillOrderTypeFlagArray( short sordertypeflag, short sindex_sdkaua );

/*  void DoubleToString (double source, int vorkomma, int nachkomma); */
 void DoubleToString (double source, int laenge_gesamt, int nachkomma);
 void LongToString (long source);
 void LongToStringWithLength (long source, int length);
 void LongToStringDateCheck(long source, long checkdate);
 long CutCentury (long source);
 int Trim (char *s);
 void Upper (char *s);
 void DiscardNotNumerics (char *s);
 int GetUmlaut (int Sign, char *Conv);
 void ConvertUmlaute (unsigned char *strOrig, char *strConv);
 int AvoidOverflow (char *s, int length);
 void Runden (double *wert, int stellen);

 /*maybe move to it's own c/h file pair*/
 bool IsCountry(const char* countryCode, const char* const countryCodeToCompair);
 
 char m_String[30];
 short dkkgr_flags[ANZ_DKKGR_TABELEMENTE];
 short dkaua_flags[ANZ_DKAUA_TABELEMENTE];

#endif /*  TPULCONVERT_H_INCLUDED  */

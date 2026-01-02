 #ifndef TPULDB_H_INCLUDED
 #define TPULDB_H_INCLUDED

 rterror startBrowse( const long lDateCurrent, const long lDateUntil, const long lDateDelete, const char *spDatabase, const char *spKuerzel, const short sPrewhole );
/*  rterror endBrowse( void  ); */
 rterror endBrowse( const bool bCloseAll  );  /* hajo */

 rterror startBrowseZchargenrueckruf( const long lartikel_nr );
 rterror endBrowseZchargenrueckruf( void  ); 

 rterror startBrowseCarticlecodes( const long lartikel_nr );
 rterror endBrowseCarticlecodes( void  ); 

 rterror startBrowseCdiscount_Pzn( const long lartikel_nr, const long ldate );
 rterror endBrowseCdiscount_Pzn( void  ); 

 rterror startBrowseCdiscount_Rpg( const long lrabgrp_nr );
 rterror endBrowseCdiscount_Rpg( void  ); 

 rterror startBrowseCdiscount_Hnr( const long lrabgrp_nr );
 rterror endBrowseCdiscount_Hnr( void  ); 

 rterror startBrowseCdiscount_Agn( const long lrabgrp_nr );
 rterror endBrowseCdiscount_Agn( void  ); 

 rterror startBrowseCartcompack( const long lartikel_nr );
 rterror endBrowseCartcompack( void  ); 

 rterror startBrowseZartverk( const long lartikel_nr );
 rterror endBrowseZartverk( void  ); 

 rterror startBrowseCdiscgrpmem( const long discountgrpno );
 rterror endBrowseCdiscgrpmem( void  ); 

 rterror startBrowseCcustomergroupflags( const short sKundengruppe );
 rterror endBrowseCcustomergroupflags( void  ); 

 rterror startBrowseCordertypeflags( const char *sAuftragsart );
 rterror endBrowseCordertypeflags( void  ); 

 rterror startBrowseCbaselistarticles( const long lartikel_nr );
 rterror endBrowseCbaselistarticles( void  ); 

 rterror GetNextArticle( dezapzartikelSTR *article );
 rterror GetPriceOfArticle( dezapzartpreisSTR *price );
 rterror GetSecondaryOfArticle( dezapzartsekbezSTR *secundary );
 rterror GetDepositValueOfArticle( dezapcdeposittypesSTR *secundary );
 rterror GetManufacturerOfArticle( dezapherstelSTR *manufacturer );
 rterror GetManufacturer_Dispo( dezapherstel_dispoSTR *manufacturer_dispo );
 rterror GetEan( dezapeanSTR *ean );
 rterror InitGoodsgroupOfArticle( dezapzartwgSTR *goodsgroup );
 rterror GetGoodsgroupOfArticle( dezapzartwgSTR *goodsgroup );
 rterror InitCodes( dezapcarticlecodesSTR *articlecodes );
 rterror GetCodes( dezapcarticlecodesSTR *articlecodes );
 rterror InitHSalesCondition( dezaphsalescondSTR *hsalescond );
 rterror GetHSalesCondition( dezaphsalescondSTR *hsalescond );
 rterror DeleteNextArticle( void );
 rterror DeleteNextGroup( void );
 rterror DeleteNextPZN( void );
 rterror GetFixedAmountOfArticle( dezapzartfeb2STR *fixedamount );
 rterror GetCsafetydatasheet( dezapcsafetydatasheetSTR *safetydatasheet );
 rterror GetCarticleext( dezapcarticleextSTR *articleext );
 rterror GetZautidemsperre( dezapzautidemsperreSTR *zautidemsperre );
 /* rterror GetCgibatchentry( dezapcgibatchentrySTR *cgibatchentry ); */
 rterror GetArtve( dezapartveSTR *artve );
 rterror GetZartikel( dezapzartikelSTR *zartikel );
 rterror GetAustrianFields( dezapzartaustriaSTR *austria );
 rterror GetCroatianFields( dezapzartcroatiaSTR *croatia );
 rterror GetBulgarianFields( dezapzartbulgariaSTR *bulgaria );
 rterror GetSerbianFields( dezapzartserbiaSTR *serbia );
 rterror GetNextGroup( dezapzgrppflegeSTR *zgrppflege );
 rterror GetNextPZN( dezapzpznpflegeSTR *zpznpflege );
 rterror GetZdkwgr( dezapzdkwgrSTR *zdkwgr );
 rterror GetZdkiwg( dezapzdkiwgSTR *zdkiwg );
 rterror GetZdktgr( dezapzdktgrSTR *zdktgr );
/* rterror GetZdkbgr( dezapzdkbgrSTR *zdkbgr ); */
 rterror GetZrabgrp( dezapzrabgrpSTR *zrabgrp );
 rterror GetZzahlbed( dezapzzahlbedSTR *zzahlbed );
 rterror GetCdiscmodel( dezapcdiscmodelSTR *cdiscmodel );
 rterror GetCmonthdiscsort( dezapcmonthdiscsortSTR *cmonthdiscsort );
 rterror GetChighpaymtargetfee( dezapchighpaymtargetfeeSTR *chighpaymtargetfee );
 rterror GetCcustomergroup( dezapccustomergroupSTR *ccustomergroup );
 rterror GetCordertype( dezapcordertypeSTR *cordertype );
 rterror GetCmonthvirtsort( dezapcmonthvirtsortSTR *cmonthvirtsort );
/* rterror GetCcustservices( dezapccustservicesSTR *ccustservices ); */
 rterror GetCstoragecriteria( dezapcstoragecriteriaSTR *cstoragecriteria );
 rterror GetCintrastatcountry( dezapcintrastatcountrySTR *cintrastatcountry );
 rterror GetCformtypes( dezapcformtypesSTR *cformtypes );
 rterror GetCdiscform( dezapcdiscformSTR *cdiscform );
 rterror GetCshipper( dezapcshipperSTR *cshipper );
 rterror GetCpromotions( dezapcpromotionsSTR *cpromotions );
 rterror GetCregisters( dezapcregistersSTR *cregisters );
 rterror GetCdisclist( dezapcdisclistSTR *cdisclist );
 rterror GetCservices( dezapcservicesSTR *cservices );
/* rterror GetZdkwir( dezapzdkwirSTR *zdkwir ); */
 rterror GetCarticletext( dezapcarticletextSTR *carticletext );
 rterror GetNextZchargenrueckruf( dezapzchargenrueckrufSTR *zchargenrueckruf );
 rterror GetNextCarticlecodes( dezapcarticlecodesSTR *carticlecodes );
 rterror GetNextCdiscount_Pzn( dezapcdiscountSTR *cdiscount );
 rterror GetNextCdiscount_Rpg( dezapcdiscountSTR *cdiscount );
 rterror GetNextCdiscount_Hnr( dezapcdiscountSTR *cdiscount );
 rterror GetNextCdiscount_Agn( dezapcdiscountSTR *cdiscount );
 rterror GetSwissFields( dezapzartswitzerlandSTR *switzerland );
 rterror GetCarticlelang( dezapcarticlelangSTR *carticlelang );
 rterror GetCcpvalidityperiod( dezapccpvalidityperiodSTR *ccpvalidityperiod );
 rterror GetCdiscgrp( dezapcdiscgrpSTR *cdiscgrp );
 rterror GetNextCartcompack( dezapcartcompackSTR *cartcompack );
/* rterror GetCgalocom( dezapcgalocomSTR *cgalocom );
   rterror GetCgaloart( dezapcgaloartSTR *cgaloart );
   rterror InitCgalonam( dezapcgalonamSTR *cgalonam );
   rterror GetCgalonam( dezapcgalonamSTR *cgalonam ); */
 rterror GetFrenchFields( dezapzartfranceSTR *france );
 rterror GetNextZartverk( dezapzartverkSTR *zartverk );
 rterror GetCpharmgrp( dezapcpharmgrpSTR *cpharmgrp );
 rterror GetNextCdiscgrpmem( dezapcdiscgrpmemSTR *cdiscgrpmem );
 rterror GetNextCcustomergrpflags( dezapccustomergrpflagSTR *ccustomergrpflag );
 rterror GetNextCordertypeflags( dezapcordertypeflagSTR *cordertypeflag );
 rterror GetNextCbaselistarticles( dezapcbaselistarticlesSTR *cbaselistarticles );
 
 #endif  /*  TPULDB_H_INCLUDED  */

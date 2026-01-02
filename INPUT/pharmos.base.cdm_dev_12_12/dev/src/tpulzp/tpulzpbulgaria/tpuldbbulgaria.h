 #ifndef TPULDB_H_INCLUDED
 #define TPULDB_H_INCLUDED

 rterror startBrowse( const long lDateCurrent, const long lDateUntil, const long lDateDelete, const char *spDatabase );
 rterror endBrowse( const bool bCloseAll  ); 

 rterror startBrowseZartpreis( const long lartikel_nr );
 rterror endBrowseZartpreis( void  ); 

 rterror GetNextArticle( dezapzartikelSTR *article );
 rterror GetSecondaryOfArticle( dezapzartsekbezSTR *secondary );
 rterror GetVeOfArticle( dezapartveSTR *artve );
 rterror GetEanOfArticle( dezapeanSTR *ean );
 rterror InitGoodsgroupOfArticle( dezapzartwgSTR *goodsgroup );
 rterror GetGoodsgroupOfArticle( dezapzartwgSTR *goodsgroup );
 rterror GetBulgarianFields( dezapzartbulgariaSTR *france );
 rterror GetSecondNameOfArticle( dezapcarticlelangSTR *secondname );
 rterror GetNextZartpreis( dezapzartpreisSTR *zartpreis );
 rterror GetSubstanceName( dezapzdkwirSTR *zdkwir );
 rterror GetINN( dezapcregistersSTR *cregisters, dezapartveSTR *artve );
 
 #endif  /*  TPULDB_H_INCLUDED  */

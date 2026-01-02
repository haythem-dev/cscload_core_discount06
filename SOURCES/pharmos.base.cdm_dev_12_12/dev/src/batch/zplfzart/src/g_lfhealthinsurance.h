#ifndef G_LFHEALTHINSURANCE_INCLUDED
#define G_LFHEALTHINSURANCE_INCLUDED

long Load_HealthInsurance_Daten( char *db, char *ili_direc, char *errmld );

int  upd_code_del;

int  Fd_CHealthInsurance;
int  Fd_CHealthInsuranceArticles;
int  Fd_CHealthInsuranceGroups;

enum EAbdaFileArt
{
	IZG_APO = 0,
	IKZ_APO,
	PZG_APO
};

#endif

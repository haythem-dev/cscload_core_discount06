/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_DKRIS_RISFIL               2
 #define L_DKRIS_RISKUBZ              12
 #define L_DKRIS_RISPZN1              7
 #define L_DKRIS_RISPZN2              7
 #define L_DKRIS_RISFIL2              2
 #define L_DKRIS_RISPZN01             7
 #define L_DKRIS_RISKZMAN01           1
 #define L_DKRIS_RISTABHNR01          5
 #define L_DKRIS_RISSORKZ01           1
 #define L_DKRIS_RISVKART01           1
 #define L_DKRIS_RISFILLER01          15
 #define L_DKRIS_RISPZN02             7
 #define L_DKRIS_RISKZMAN02           1
 #define L_DKRIS_RISTABHNR02          5
 #define L_DKRIS_RISSORKZ02           1
 #define L_DKRIS_RISVKART02           1
 #define L_DKRIS_RISFILLER02          15
 #define L_DKRIS_RISPZN03             7
 #define L_DKRIS_RISKZMAN03           1
 #define L_DKRIS_RISTABHNR03          5
 #define L_DKRIS_RISSORKZ03           1
 #define L_DKRIS_RISVKART03           1
 #define L_DKRIS_RISFILLER03          15
 #define L_DKRIS_RISPZN04             7
 #define L_DKRIS_RISKZMAN04           1
 #define L_DKRIS_RISTABHNR04          5
 #define L_DKRIS_RISSORKZ04           1
 #define L_DKRIS_RISVKART04           1
 #define L_DKRIS_RISFILLER04          15
 #define L_DKRIS_RISPZN05             7
 #define L_DKRIS_RISKZMAN05           1
 #define L_DKRIS_RISTABHNR05          5
 #define L_DKRIS_RISSORKZ05           1
 #define L_DKRIS_RISVKART05           1
 #define L_DKRIS_RISFILLER05          15
 #define L_DKRIS_RISPZN06             7
 #define L_DKRIS_RISKZMAN06           1
 #define L_DKRIS_RISTABHNR06          5
 #define L_DKRIS_RISSORKZ06           1
 #define L_DKRIS_RISVKART06           1
 #define L_DKRIS_RISFILLER06          15
 #define L_DKRIS_RISPZN07             7
 #define L_DKRIS_RISKZMAN07           1
 #define L_DKRIS_RISTABHNR07          5
 #define L_DKRIS_RISSORKZ07           1
 #define L_DKRIS_RISVKART07           1
 #define L_DKRIS_RISFILLER07          15
 #define L_DKRIS_RISPZN08             7
 #define L_DKRIS_RISKZMAN08           1
 #define L_DKRIS_RISTABHNR08          5
 #define L_DKRIS_RISSORKZ08           1
 #define L_DKRIS_RISVKART08           1
 #define L_DKRIS_RISFILLER08          15
 #define L_DKRIS_RISPZN09             7
 #define L_DKRIS_RISKZMAN09           1
 #define L_DKRIS_RISTABHNR09          5
 #define L_DKRIS_RISSORKZ09           1
 #define L_DKRIS_RISVKART09           1
 #define L_DKRIS_RISFILLER09          15
 #define L_DKRIS_RISPZN10             7
 #define L_DKRIS_RISKZMAN10           1
 #define L_DKRIS_RISTABHNR10          5
 #define L_DKRIS_RISSORKZ10           1
 #define L_DKRIS_RISVKART10           1
 #define L_DKRIS_RISFILLER10          15
 #define L_DKRIS_RISPZN11             7
 #define L_DKRIS_RISKZMAN11           1
 #define L_DKRIS_RISTABHNR11          5
 #define L_DKRIS_RISSORKZ11           1
 #define L_DKRIS_RISVKART11           1
 #define L_DKRIS_RISFILLER11          15
 #define L_DKRIS_RISPZN12             7
 #define L_DKRIS_RISKZMAN12           1
 #define L_DKRIS_RISTABHNR12          5
 #define L_DKRIS_RISSORKZ12           1
 #define L_DKRIS_RISVKART12           1
 #define L_DKRIS_RISFILLER12          15
 #define L_DKRIS_RISKZHV              1
 #define L_DKRIS_RISLOE               1
 #define L_DKRIS_RISFILLER2           18


 #define L_DKRIS_PKEY 0

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DKRIS_ANZ ( sizeof(DKRIS_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DKRIS sizeof(struct DKRIS)


 #define DKRIS_H

 #define DKRIS_LISTE \
 			DKRIS.RISFIL, \
 			DKRIS.RISKUBZ, \
 			DKRIS.RISPZN1, \
 			DKRIS.RISPZN2, \
 			DKRIS.RISFIL2, \
 			DKRIS.RISPZN01, \
			DKRIS.RISKZMAN01, \
			DKRIS.RISTABHNR01, \
			DKRIS.RISSORKZ01, \
			DKRIS.RISVKART01, \
			DKRIS.RISFILLER01, \
 			DKRIS.RISPZN02, \
			DKRIS.RISKZMAN02, \
			DKRIS.RISTABHNR02, \
			DKRIS.RISSORKZ02, \
			DKRIS.RISVKART02, \
			DKRIS.RISFILLER02, \
 			DKRIS.RISPZN03, \
			DKRIS.RISKZMAN03, \
			DKRIS.RISTABHNR03, \
			DKRIS.RISSORKZ03, \
			DKRIS.RISVKART03, \
			DKRIS.RISFILLER03, \
 			DKRIS.RISPZN04, \
			DKRIS.RISKZMAN04, \
			DKRIS.RISTABHNR04, \
			DKRIS.RISSORKZ04, \
			DKRIS.RISVKART04, \
			DKRIS.RISFILLER04, \
 			DKRIS.RISPZN05, \
			DKRIS.RISKZMAN05, \
			DKRIS.RISTABHNR05, \
			DKRIS.RISSORKZ05, \
			DKRIS.RISVKART05, \
			DKRIS.RISFILLER05, \
 			DKRIS.RISPZN06, \
			DKRIS.RISKZMAN06, \
			DKRIS.RISTABHNR06, \
			DKRIS.RISSORKZ06, \
			DKRIS.RISVKART06, \
			DKRIS.RISFILLER06, \
 			DKRIS.RISPZN07, \
			DKRIS.RISKZMAN07, \
			DKRIS.RISTABHNR07, \
			DKRIS.RISSORKZ07, \
			DKRIS.RISVKART07, \
			DKRIS.RISFILLER07, \
 			DKRIS.RISPZN08, \
			DKRIS.RISKZMAN08, \
			DKRIS.RISTABHNR08, \
			DKRIS.RISSORKZ08, \
			DKRIS.RISVKART08, \
			DKRIS.RISFILLER08, \
 			DKRIS.RISPZN09, \
			DKRIS.RISKZMAN09, \
			DKRIS.RISTABHNR09, \
			DKRIS.RISSORKZ09, \
			DKRIS.RISVKART09, \
			DKRIS.RISFILLER09, \
 			DKRIS.RISPZN10, \
			DKRIS.RISKZMAN10, \
			DKRIS.RISTABHNR10, \
			DKRIS.RISSORKZ10, \
			DKRIS.RISVKART10, \
			DKRIS.RISFILLER10, \
 			DKRIS.RISPZN11, \
			DKRIS.RISKZMAN11, \
			DKRIS.RISTABHNR11, \
			DKRIS.RISSORKZ11, \
			DKRIS.RISVKART11, \
			DKRIS.RISFILLER11, \
 			DKRIS.RISPZN12, \
			DKRIS.RISKZMAN12, \
			DKRIS.RISTABHNR12, \
			DKRIS.RISSORKZ12, \
			DKRIS.RISVKART12, \
			DKRIS.RISFILLER12, \
 			DKRIS.RISKZHV, \
 			DKRIS.RISLOE, \
 			DKRIS.RISFILLER2
 #define DKRIS_PLISTE \
 			"DKRIS.RISFIL," \
 			"DKRIS.RISKUBZ," \
 			"DKRIS.RISPZN1," \
 			"DKRIS.RISPZN2," \
 			"DKRIS.RISFIL2," \
 			"DKRIS.RISPZN01," \
			"DKRIS.RISKZMAN01," \
			"DKRIS.RISTABHNR01," \
			"DKRIS.RISSORKZ01," \
			"DKRIS.RISVKART01," \
			"DKRIS.RISFILLER01," \
 			"DKRIS.RISPZN02," \
			"DKRIS.RISKZMAN02," \
			"DKRIS.RISTABHNR02," \
			"DKRIS.RISSORKZ02," \
			"DKRIS.RISVKART02," \
			"DKRIS.RISFILLER02," \
 			"DKRIS.RISPZN03," \
			"DKRIS.RISKZMAN03," \
			"DKRIS.RISTABHNR03," \
			"DKRIS.RISSORKZ03," \
			"DKRIS.RISVKART03," \
			"DKRIS.RISFILLER03," \
 			"DKRIS.RISPZN04," \
			"DKRIS.RISKZMAN04," \
			"DKRIS.RISTABHNR04," \
			"DKRIS.RISSORKZ04," \
			"DKRIS.RISVKART04," \
			"DKRIS.RISFILLER04," \
 			"DKRIS.RISPZN05," \
			"DKRIS.RISKZMAN05," \
			"DKRIS.RISTABHNR05," \
			"DKRIS.RISSORKZ05," \
			"DKRIS.RISVKART05," \
			"DKRIS.RISFILLER05," \
 			"DKRIS.RISPZN06," \
			"DKRIS.RISKZMAN06," \
			"DKRIS.RISTABHNR06," \
			"DKRIS.RISSORKZ06," \
			"DKRIS.RISVKART06," \
			"DKRIS.RISFILLER06," \
 			"DKRIS.RISPZN07," \
			"DKRIS.RISKZMAN07," \
			"DKRIS.RISTABHNR07," \
			"DKRIS.RISSORKZ07," \
			"DKRIS.RISVKART07," \
			"DKRIS.RISFILLER07," \
 			"DKRIS.RISPZN08," \
			"DKRIS.RISKZMAN08," \
			"DKRIS.RISTABHNR08," \
			"DKRIS.RISSORKZ08," \
			"DKRIS.RISVKART08," \
			"DKRIS.RISFILLER08," \
 			"DKRIS.RISPZN09," \
			"DKRIS.RISKZMAN09," \
			"DKRIS.RISTABHNR09," \
			"DKRIS.RISSORKZ09," \
			"DKRIS.RISVKART09," \
			"DKRIS.RISFILLER09," \
 			"DKRIS.RISPZN10," \
			"DKRIS.RISKZMAN10," \
			"DKRIS.RISTABHNR10," \
			"DKRIS.RISSORKZ10," \
			"DKRIS.RISVKART10," \
			"DKRIS.RISFILLER10," \
 			"DKRIS.RISPZN11," \
			"DKRIS.RISKZMAN11," \
			"DKRIS.RISTABHNR11," \
			"DKRIS.RISSORKZ11," \
			"DKRIS.RISVKART11," \
			"DKRIS.RISFILLER11," \
 			"DKRIS.RISPZN12," \
			"DKRIS.RISKZMAN12," \
			"DKRIS.RISTABHNR12," \
			"DKRIS.RISSORKZ12," \
			"DKRIS.RISVKART12," \
			"DKRIS.RISFILLER12," \
 			"DKRIS.RISKZHV," \
 			"DKRIS.RISLOE," \
 			"DKRIS.RISFILLER2 " 

 #define DKRIS_PELISTE \
 			"RISFIL," \
 			"RISKUBZ," \
 			"RISPZN1," \
 			"RISPZN2," \
 			"RISFIL2," \
 			"RISPZN01," \
			"RISKZMAN01," \
			"RISTABHNR01," \
			"RISSORKZ01," \
			"RISVKART01," \
			"RISFILLER01," \
 			"RISPZN02," \
			"RISKZMAN02," \
			"RISTABHNR02," \
			"RISSORKZ02," \
			"RISVKART02," \
			"RISFILLER02," \
 			"RISPZN03," \
			"RISKZMAN03," \
			"RISTABHNR03," \
			"RISSORKZ03," \
			"RISVKART03," \
			"RISFILLER03," \
 			"RISPZN04," \
			"RISKZMAN04," \
			"RISTABHNR04," \
			"RISSORKZ04," \
			"RISVKART04," \
			"RISFILLER04," \
 			"RISPZN05," \
			"RISKZMAN05," \
			"RISTABHNR05," \
			"RISSORKZ05," \
			"RISVKART05," \
			"RISFILLER05," \
 			"RISPZN06," \
			"RISKZMAN06," \
			"RISTABHNR06," \
			"RISSORKZ06," \
			"RISVKART06," \
			"RISFILLER06," \
 			"RISPZN07," \
			"RISKZMAN07," \
			"RISTABHNR07," \
			"RISSORKZ07," \
			"RISVKART07," \
			"RISFILLER07," \
 			"RISPZN08," \
			"RISKZMAN08," \
			"RISTABHNR08," \
			"RISSORKZ08," \
			"RISVKART08," \
			"RISFILLER08," \
 			"RISPZN09," \
			"RISKZMAN09," \
			"RISTABHNR09," \
			"RISSORKZ09," \
			"RISVKART09," \
			"RISFILLER09," \
 			"RISPZN10," \
			"RISKZMAN10," \
			"RISTABHNR10," \
			"RISSORKZ10," \
			"RISVKART10," \
			"RISFILLER10," \
 			"RISPZN11," \
			"RISKZMAN11," \
			"RISTABHNR11," \
			"RISSORKZ11," \
			"RISVKART11," \
			"RISFILLER11," \
 			"RISPZN12," \
			"RISKZMAN12," \
			"RISTABHNR12," \
			"RISSORKZ12," \
			"RISVKART12," \
			"RISFILLER12," \
 			"RISKZHV," \
 			"RISLOE," \
 			"RISFILLER2 " 

 #define DKRIS_UPDLISTE \
 			"RISFIL=?," \
 			"RISKUBZ=?," \
 			"RISPZN1=?," \
 			"RISPZN2=?," \
 			"RISFIL2=?," \
 			"RISPZN01=?," \
			"RISKZMAN01=?," \
			"RISTABHNR01=?," \
			"RISSORKZ01=?," \
			"RISVKART01=?," \
			"RISFILLER01=?," \
 			"RISPZN02=?," \
			"RISKZMAN02=?," \
			"RISTABHNR02=?," \
			"RISSORKZ02=?," \
			"RISVKART02=?," \
			"RISFILLER02=?," \
 			"RISPZN03=?," \
			"RISKZMAN03=?," \
			"RISTABHNR03=?," \
			"RISSORKZ03=?," \
			"RISVKART03=?," \
			"RISFILLER03=?," \
 			"RISPZN04=?," \
			"RISKZMAN04=?," \
			"RISTABHNR04=?," \
			"RISSORKZ04=?," \
			"RISVKART04=?," \
			"RISFILLER04=?," \
 			"RISPZN05=?," \
			"RISKZMAN05=?," \
			"RISTABHNR05=?," \
			"RISSORKZ05=?," \
			"RISVKART05=?," \
			"RISFILLER05=?," \
 			"RISPZN06=?," \
			"RISKZMAN06=?," \
			"RISTABHNR06=?," \
			"RISSORKZ06=?," \
			"RISVKART06=?," \
			"RISFILLER06=?," \
 			"RISPZN07=?," \
			"RISKZMAN07=?," \
			"RISTABHNR07=?," \
			"RISSORKZ07=?," \
			"RISVKART07=?," \
			"RISFILLER07=?," \
 			"RISPZN08=?," \
			"RISKZMAN08=?," \
			"RISTABHNR08=?," \
			"RISSORKZ08=?," \
			"RISVKART08=?," \
			"RISFILLER08=?," \
 			"RISPZN09=?," \
			"RISKZMAN09=?," \
			"RISTABHNR09=?," \
			"RISSORKZ09=?," \
			"RISVKART09=?," \
			"RISFILLER09=?," \
 			"RISPZN10=?," \
			"RISKZMAN10=?," \
			"RISTABHNR10=?," \
			"RISSORKZ10=?," \
			"RISVKART10=?," \
			"RISFILLER10=?," \
 			"RISPZN11=?," \
			"RISKZMAN11=?," \
			"RISTABHNR11=?," \
			"RISSORKZ11=?," \
			"RISVKART11=?," \
			"RISFILLER11=?," \
 			"RISPZN12=?," \
			"RISKZMAN12=?," \
			"RISTABHNR12=?," \
			"RISSORKZ12=?," \
			"RISVKART12=?," \
			"RISFILLER12=?," \
 			"RISKZHV=?," \
 			"RISLOE=?," \
 			"RISFILLER2=? " 

 #define DKRISRISFIL                        0
 #define DKRISRISKUBZ                       1
 #define DKRISRISPZN1                       2
 #define DKRISRISPZN2                       3
 #define DKRISRISFIL2                       4
 #define DKRISRISPZN01                      5
 #define DKRISRISKZMAN01                    6
 #define DKRISRISTABHNR01                   7
 #define DKRISRISSORKZ01                    8
 #define DKRISRISVKART01                    9
 #define DKRISRISFILLER01                   10
 #define DKRISRISPZN02                      11
 #define DKRISRISKZMAN02                    12
 #define DKRISRISTABHNR02                   13
 #define DKRISRISSORKZ02                    14
 #define DKRISRISVKART02                    15
 #define DKRISRISFILLER02                   16
 #define DKRISRISPZN03                      17
 #define DKRISRISKZMAN03                    18
 #define DKRISRISTABHNR03                   19
 #define DKRISRISSORKZ03                    20
 #define DKRISRISVKART03                    21
 #define DKRISRISFILLER03                   22
 #define DKRISRISPZN04                      23
 #define DKRISRISKZMAN04                    24
 #define DKRISRISTABHNR04                   25
 #define DKRISRISSORKZ04                    26
 #define DKRISRISVKART04                    27
 #define DKRISRISFILLER04                   28
 #define DKRISRISPZN05                      29
 #define DKRISRISKZMAN05                    30
 #define DKRISRISTABHNR05                   31
 #define DKRISRISSORKZ05                    32
 #define DKRISRISVKART05                    33
 #define DKRISRISFILLER05                   34
 #define DKRISRISPZN06                      35
 #define DKRISRISKZMAN06                    36
 #define DKRISRISTABHNR06                   37
 #define DKRISRISSORKZ06                    38
 #define DKRISRISVKART06                    39
 #define DKRISRISFILLER06                   40
 #define DKRISRISPZN07                      41
 #define DKRISRISKZMAN07                    42
 #define DKRISRISTABHNR07                   43
 #define DKRISRISSORKZ07                    44
 #define DKRISRISVKART07                    45
 #define DKRISRISFILLER07                   46
 #define DKRISRISPZN08                      47
 #define DKRISRISKZMAN08                    48
 #define DKRISRISTABHNR08                   49
 #define DKRISRISSORKZ08                    50
 #define DKRISRISVKART08                    51
 #define DKRISRISFILLER08                   52
 #define DKRISRISPZN09                      53
 #define DKRISRISKZMAN09                    54
 #define DKRISRISTABHNR09                   55
 #define DKRISRISSORKZ09                    56
 #define DKRISRISVKART09                    57
 #define DKRISRISFILLER09                   58
 #define DKRISRISPZN10                      59
 #define DKRISRISKZMAN10                    60
 #define DKRISRISTABHNR10                   61
 #define DKRISRISSORKZ10                    62
 #define DKRISRISVKART10                    63
 #define DKRISRISFILLER10                   64
 #define DKRISRISPZN11                      65
 #define DKRISRISKZMAN11                    66
 #define DKRISRISTABHNR11                   67
 #define DKRISRISSORKZ11                    68
 #define DKRISRISVKART11                    69
 #define DKRISRISFILLER11                   70
 #define DKRISRISPZN12                      71
 #define DKRISRISKZMAN12                    72
 #define DKRISRISTABHNR12                   73
 #define DKRISRISSORKZ12                    74
 #define DKRISRISVKART12                    75
 #define DKRISRISFILLER12                   76
 #define DKRISRISKZHV                       77
 #define DKRISRISLOE                        78
 #define DKRISRISFILLER2                    79

 #define DKRIS_ZEIGER(xxx) \
 			:xxx->RISFIL,\
 			:xxx->RISKUBZ,\
 			:xxx->RISPZN1,\
 			:xxx->RISPZN2,\
 			:xxx->RISFIL2,\
 			:xxx->RISPZN01,\
 			:xxx->RISKZMAN01,\
 			:xxx->RISTABHNR01,\
 			:xxx->RISSORKZ01,\
 			:xxx->RISVKART01,\
 			:xxx->RISFILLER01,\
 			:xxx->RISPZN02,\
 			:xxx->RISKZMAN02,\
 			:xxx->RISTABHNR02,\
 			:xxx->RISSORKZ02,\
 			:xxx->RISVKART02,\
 			:xxx->RISFILLER02,\
 			:xxx->RISPZN03,\
 			:xxx->RISKZMAN03,\
 			:xxx->RISTABHNR03,\
 			:xxx->RISSORKZ03,\
 			:xxx->RISVKART03,\
 			:xxx->RISFILLER03,\
 			:xxx->RISPZN04,\
 			:xxx->RISKZMAN04,\
 			:xxx->RISTABHNR04,\
 			:xxx->RISSORKZ04,\
 			:xxx->RISVKART04,\
 			:xxx->RISFILLER04,\
 			:xxx->RISPZN05,\
 			:xxx->RISKZMAN05,\
 			:xxx->RISTABHNR05,\
 			:xxx->RISSORKZ05,\
 			:xxx->RISVKART05,\
 			:xxx->RISFILLER05,\
 			:xxx->RISPZN06,\
 			:xxx->RISKZMAN06,\
 			:xxx->RISTABHNR06,\
 			:xxx->RISSORKZ06,\
 			:xxx->RISVKART06,\
 			:xxx->RISFILLER06,\
 			:xxx->RISPZN07,\
 			:xxx->RISKZMAN07,\
 			:xxx->RISTABHNR07,\
 			:xxx->RISSORKZ07,\
 			:xxx->RISVKART07,\
 			:xxx->RISFILLER07,\
 			:xxx->RISPZN08,\
 			:xxx->RISKZMAN08,\
 			:xxx->RISTABHNR08,\
 			:xxx->RISSORKZ08,\
 			:xxx->RISVKART08,\
 			:xxx->RISFILLER08,\
 			:xxx->RISPZN09,\
 			:xxx->RISKZMAN09,\
 			:xxx->RISTABHNR09,\
 			:xxx->RISSORKZ09,\
 			:xxx->RISVKART09,\
 			:xxx->RISFILLER09,\
 			:xxx->RISPZN10,\
 			:xxx->RISKZMAN10,\
 			:xxx->RISTABHNR10,\
 			:xxx->RISSORKZ10,\
 			:xxx->RISVKART10,\
 			:xxx->RISFILLER10,\
 			:xxx->RISPZN11,\
 			:xxx->RISKZMAN11,\
 			:xxx->RISTABHNR11,\
 			:xxx->RISSORKZ11,\
 			:xxx->RISVKART11,\
 			:xxx->RISFILLER11,\
 			:xxx->RISPZN12,\
 			:xxx->RISKZMAN12,\
 			:xxx->RISTABHNR12,\
 			:xxx->RISSORKZ12,\
 			:xxx->RISVKART12,\
 			:xxx->RISFILLER12,\
 			:xxx->RISKZHV,\
 			:xxx->RISLOE,\
 			:xxx->RISFILLER2

 #define DKRIS_UPDATE(xxx) \
 			RISFIL = :xxx->RISFIL,\
 			RISKUBZ = :xxx->RISKUBZ,\
 			RISPZN1 = :xxx->RISPZN1,\
 			RISPZN2 = :xxx->RISPZN2,\
 			RISFIL2 = :xxx->RISFIL2,\
 			RISPZN01 = :xxx->RISPZN01,\
 			RISKZMAN01 = :xxx->RISKZMAN01,\
 			RISTABHNR01 = :xxx->RISTABHNR01,\
 			RISSORKZ01 = :xxx->RISSORKZ01,\
 			RISVKART01 = :xxx->RISVKART01,\
 			RISFILLER01 = :xxx->RISFILLER01,\
 			RISPZN02 = :xxx->RISPZN02,\
 			RISKZMAN02 = :xxx->RISKZMAN02,\
 			RISTABHNR02 = :xxx->RISTABHNR02,\
 			RISSORKZ02 = :xxx->RISSORKZ02,\
 			RISVKART02 = :xxx->RISVKART02,\
 			RISFILLER02 = :xxx->RISFILLER02,\
 			RISPZN03 = :xxx->RISPZN03,\
 			RISKZMAN03 = :xxx->RISKZMAN03,\
 			RISTABHNR03 = :xxx->RISTABHNR03,\
 			RISSORKZ03 = :xxx->RISSORKZ03,\
 			RISVKART03 = :xxx->RISVKART03,\
 			RISFILLER03 = :xxx->RISFILLER03,\
 			RISPZN04 = :xxx->RISPZN04,\
 			RISKZMAN04 = :xxx->RISKZMAN04,\
 			RISTABHNR04 = :xxx->RISTABHNR04,\
 			RISSORKZ04 = :xxx->RISSORKZ04,\
 			RISVKART04 = :xxx->RISVKART04,\
 			RISFILLER04 = :xxx->RISFILLER04,\
 			RISPZN05 = :xxx->RISPZN05,\
 			RISKZMAN05 = :xxx->RISKZMAN05,\
 			RISTABHNR05 = :xxx->RISTABHNR05,\
 			RISSORKZ05 = :xxx->RISSORKZ05,\
 			RISVKART05 = :xxx->RISVKART05,\
 			RISFILLER05 = :xxx->RISFILLER05,\
 			RISPZN06 = :xxx->RISPZN06,\
 			RISKZMAN06 = :xxx->RISKZMAN06,\
 			RISTABHNR06 = :xxx->RISTABHNR06,\
 			RISSORKZ06 = :xxx->RISSORKZ06,\
 			RISVKART06 = :xxx->RISVKART06,\
 			RISFILLER06 = :xxx->RISFILLER06,\
 			RISPZN07 = :xxx->RISPZN07,\
 			RISKZMAN07 = :xxx->RISKZMAN07,\
 			RISTABHNR07 = :xxx->RISTABHNR07,\
 			RISSORKZ07 = :xxx->RISSORKZ07,\
 			RISVKART07 = :xxx->RISVKART07,\
 			RISFILLER07 = :xxx->RISFILLER07,\
 			RISPZN08 = :xxx->RISPZN08,\
 			RISKZMAN08 = :xxx->RISKZMAN08,\
 			RISTABHNR08 = :xxx->RISTABHNR08,\
 			RISSORKZ08 = :xxx->RISSORKZ08,\
 			RISVKART08 = :xxx->RISVKART08,\
 			RISFILLER08 = :xxx->RISFILLER08,\
 			RISPZN09 = :xxx->RISPZN09,\
 			RISKZMAN09 = :xxx->RISKZMAN09,\
 			RISTABHNR09 = :xxx->RISTABHNR09,\
 			RISSORKZ09 = :xxx->RISSORKZ09,\
 			RISVKART09 = :xxx->RISVKART09,\
 			RISFILLER09 = :xxx->RISFILLER09,\
 			RISPZN10 = :xxx->RISPZN10,\
 			RISKZMAN10 = :xxx->RISKZMAN10,\
 			RISTABHNR10 = :xxx->RISTABHNR10,\
 			RISSORKZ10 = :xxx->RISSORKZ10,\
 			RISVKART10 = :xxx->RISVKART10,\
 			RISFILLER10 = :xxx->RISFILLER10,\
 			RISPZN11 = :xxx->RISPZN11,\
 			RISKZMAN11 = :xxx->RISKZMAN11,\
 			RISTABHNR11 = :xxx->RISTABHNR11,\
 			RISSORKZ11 = :xxx->RISSORKZ11,\
 			RISVKART11 = :xxx->RISVKART11,\
 			RISFILLER11 = :xxx->RISFILLER11,\
 			RISPZN12 = :xxx->RISPZN12,\
 			RISKZMAN12 = :xxx->RISKZMAN12,\
 			RISTABHNR12 = :xxx->RISTABHNR12,\
 			RISSORKZ12 = :xxx->RISSORKZ12,\
 			RISVKART12 = :xxx->RISVKART12,\
 			RISFILLER12 = :xxx->RISFILLER12,\
 			RISKZHV = :xxx->RISKZHV,\
 			RISLOE = :xxx->RISLOE,\
 			RISFILLER2 = :xxx->RISFILLER2

 #define LS_DKRIS_RISFIL               3
 #define LS_DKRIS_RISKUBZ              13
 #define LS_DKRIS_RISPZN1              8
 #define LS_DKRIS_RISPZN2              8
 #define LS_DKRIS_RISFIL2              3
 #define LS_DKRIS_RISPZN01             8
 #define LS_DKRIS_RISKZMAN01           2
 #define LS_DKRIS_RISTABHNR01          6
 #define LS_DKRIS_RISSORKZ01           2
 #define LS_DKRIS_RISVKART01           2
 #define LS_DKRIS_RISFILLER01          16
 #define LS_DKRIS_RISPZN02             8
 #define LS_DKRIS_RISKZMAN02           2
 #define LS_DKRIS_RISTABHNR02          6
 #define LS_DKRIS_RISSORKZ02           2
 #define LS_DKRIS_RISVKART02           2
 #define LS_DKRIS_RISFILLER02          16
 #define LS_DKRIS_RISPZN03             8
 #define LS_DKRIS_RISKZMAN03           2
 #define LS_DKRIS_RISTABHNR03          6
 #define LS_DKRIS_RISSORKZ03           2
 #define LS_DKRIS_RISVKART03           2
 #define LS_DKRIS_RISFILLER03          16
 #define LS_DKRIS_RISPZN04             8
 #define LS_DKRIS_RISKZMAN04           2
 #define LS_DKRIS_RISTABHNR04          6
 #define LS_DKRIS_RISSORKZ04           2
 #define LS_DKRIS_RISVKART04           2
 #define LS_DKRIS_RISFILLER04          16
 #define LS_DKRIS_RISPZN05             8
 #define LS_DKRIS_RISKZMAN05           2
 #define LS_DKRIS_RISTABHNR05          6
 #define LS_DKRIS_RISSORKZ05           2
 #define LS_DKRIS_RISVKART05           2
 #define LS_DKRIS_RISFILLER05          16
 #define LS_DKRIS_RISPZN06             8
 #define LS_DKRIS_RISKZMAN06           2
 #define LS_DKRIS_RISTABHNR06          6
 #define LS_DKRIS_RISSORKZ06           2
 #define LS_DKRIS_RISVKART06           2
 #define LS_DKRIS_RISFILLER06          16
 #define LS_DKRIS_RISPZN07             8
 #define LS_DKRIS_RISKZMAN07           2
 #define LS_DKRIS_RISTABHNR07          6
 #define LS_DKRIS_RISSORKZ07           2
 #define LS_DKRIS_RISVKART07           2
 #define LS_DKRIS_RISFILLER07          16
 #define LS_DKRIS_RISPZN08             8
 #define LS_DKRIS_RISKZMAN08           2
 #define LS_DKRIS_RISTABHNR08          6
 #define LS_DKRIS_RISSORKZ08           2
 #define LS_DKRIS_RISVKART08           2
 #define LS_DKRIS_RISFILLER08          16
 #define LS_DKRIS_RISPZN09             8
 #define LS_DKRIS_RISKZMAN09           2
 #define LS_DKRIS_RISTABHNR09          6
 #define LS_DKRIS_RISSORKZ09           2
 #define LS_DKRIS_RISVKART09           2
 #define LS_DKRIS_RISFILLER09          16
 #define LS_DKRIS_RISPZN10             8
 #define LS_DKRIS_RISKZMAN10           2
 #define LS_DKRIS_RISTABHNR10          6
 #define LS_DKRIS_RISSORKZ10           2
 #define LS_DKRIS_RISVKART10           2
 #define LS_DKRIS_RISFILLER10          16
 #define LS_DKRIS_RISPZN11             8
 #define LS_DKRIS_RISKZMAN11           2
 #define LS_DKRIS_RISTABHNR11          6
 #define LS_DKRIS_RISSORKZ11           2
 #define LS_DKRIS_RISVKART11           2
 #define LS_DKRIS_RISFILLER11          16
 #define LS_DKRIS_RISPZN12             8
 #define LS_DKRIS_RISKZMAN12           2
 #define LS_DKRIS_RISTABHNR12          6
 #define LS_DKRIS_RISSORKZ12           2
 #define LS_DKRIS_RISVKART12           2
 #define LS_DKRIS_RISFILLER12          16
 #define LS_DKRIS_RISKZHV              2
 #define LS_DKRIS_RISLOE               2
 #define LS_DKRIS_RISFILLER2           19

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct DKRIS {
		 char    RISFIL[2 + 1];
		 char    RISKUBZ[12 + 1];
		 char    RISPZN1[7 + 1];
		 char    RISPZN2[7 + 1];
		 char    RISFIL2[2 + 1];
		 char    RISPZN01[7 + 1];
		 char    RISKZMAN01[1 + 1];
		 char    RISTABHNR01[5 + 1];
		 char    RISSORKZ01[1 + 1];
		 char    RISVKART01[1 + 1];
		 char    RISFILLER01[15 + 1];
		 char    RISPZN02[7 + 1];
		 char    RISKZMAN02[1 + 1];
		 char    RISTABHNR02[5 + 1];
		 char    RISSORKZ02[1 + 1];
		 char    RISVKART02[1 + 1];
		 char    RISFILLER02[15 + 1];
		 char    RISPZN03[7 + 1];
		 char    RISKZMAN03[1 + 1];
		 char    RISTABHNR03[5 + 1];
		 char    RISSORKZ03[1 + 1];
		 char    RISVKART03[1 + 1];
		 char    RISFILLER03[15 + 1];
		 char    RISPZN04[7 + 1];
		 char    RISKZMAN04[1 + 1];
		 char    RISTABHNR04[5 + 1];
		 char    RISSORKZ04[1 + 1];
		 char    RISVKART04[1 + 1];
		 char    RISFILLER04[15 + 1];
		 char    RISPZN05[7 + 1];
		 char    RISKZMAN05[1 + 1];
		 char    RISTABHNR05[5 + 1];
		 char    RISSORKZ05[1 + 1];
		 char    RISVKART05[1 + 1];
		 char    RISFILLER05[15 + 1];
		 char    RISPZN06[7 + 1];
		 char    RISKZMAN06[1 + 1];
		 char    RISTABHNR06[5 + 1];
		 char    RISSORKZ06[1 + 1];
		 char    RISVKART06[1 + 1];
		 char    RISFILLER06[15 + 1];
		 char    RISPZN07[7 + 1];
		 char    RISKZMAN07[1 + 1];
		 char    RISTABHNR07[5 + 1];
		 char    RISSORKZ07[1 + 1];
		 char    RISVKART07[1 + 1];
		 char    RISFILLER07[15 + 1];
		 char    RISPZN08[7 + 1];
		 char    RISKZMAN08[1 + 1];
		 char    RISTABHNR08[5 + 1];
		 char    RISSORKZ08[1 + 1];
		 char    RISVKART08[1 + 1];
		 char    RISFILLER08[15 + 1];
		 char    RISPZN09[7 + 1];
		 char    RISKZMAN09[1 + 1];
		 char    RISTABHNR09[5 + 1];
		 char    RISSORKZ09[1 + 1];
		 char    RISVKART09[1 + 1];
		 char    RISFILLER09[15 + 1];
		 char    RISPZN10[7 + 1];
		 char    RISKZMAN10[1 + 1];
		 char    RISTABHNR10[5 + 1];
		 char    RISSORKZ10[1 + 1];
		 char    RISVKART10[1 + 1];
		 char    RISFILLER10[15 + 1];
		 char    RISPZN11[7 + 1];
		 char    RISKZMAN11[1 + 1];
		 char    RISTABHNR11[5 + 1];
		 char    RISSORKZ11[1 + 1];
		 char    RISVKART11[1 + 1];
		 char    RISFILLER11[15 + 1];
		 char    RISPZN12[7 + 1];
		 char    RISKZMAN12[1 + 1];
		 char    RISTABHNR12[5 + 1];
		 char    RISSORKZ12[1 + 1];
		 char    RISVKART12[1 + 1];
		 char    RISFILLER12[15 + 1];
		 char    RISKZHV[1 + 1];
		 char    RISLOE[1 + 1];
		 char    RISFILLER2[18 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct C_DKRIS {
		 char    RISFIL[2 + 1];
		 char    RISKUBZ[12 + 1];
		 char    RISPZN1[7 + 1];
		 char    RISPZN2[7 + 1];
		 char    RISFIL2[2 + 1];
		 char    RISPZN01[7 + 1];
		 char    RISKZMAN01[1 + 1];
		 char    RISTABHNR01[5 + 1];
		 char    RISSORKZ01[1 + 1];
		 char    RISVKART01[1 + 1];
		 char    RISFILLER01[15 + 1];
		 char    RISPZN02[7 + 1];
		 char    RISKZMAN02[1 + 1];
		 char    RISTABHNR02[5 + 1];
		 char    RISSORKZ02[1 + 1];
		 char    RISVKART02[1 + 1];
		 char    RISFILLER02[15 + 1];
		 char    RISPZN03[7 + 1];
		 char    RISKZMAN03[1 + 1];
		 char    RISTABHNR03[5 + 1];
		 char    RISSORKZ03[1 + 1];
		 char    RISVKART03[1 + 1];
		 char    RISFILLER03[15 + 1];
		 char    RISPZN04[7 + 1];
		 char    RISKZMAN04[1 + 1];
		 char    RISTABHNR04[5 + 1];
		 char    RISSORKZ04[1 + 1];
		 char    RISVKART04[1 + 1];
		 char    RISFILLER04[15 + 1];
		 char    RISPZN05[7 + 1];
		 char    RISKZMAN05[1 + 1];
		 char    RISTABHNR05[5 + 1];
		 char    RISSORKZ05[1 + 1];
		 char    RISVKART05[1 + 1];
		 char    RISFILLER05[15 + 1];
		 char    RISPZN06[7 + 1];
		 char    RISKZMAN06[1 + 1];
		 char    RISTABHNR06[5 + 1];
		 char    RISSORKZ06[1 + 1];
		 char    RISVKART06[1 + 1];
		 char    RISFILLER06[15 + 1];
		 char    RISPZN07[7 + 1];
		 char    RISKZMAN07[1 + 1];
		 char    RISTABHNR07[5 + 1];
		 char    RISSORKZ07[1 + 1];
		 char    RISVKART07[1 + 1];
		 char    RISFILLER07[15 + 1];
		 char    RISPZN08[7 + 1];
		 char    RISKZMAN08[1 + 1];
		 char    RISTABHNR08[5 + 1];
		 char    RISSORKZ08[1 + 1];
		 char    RISVKART08[1 + 1];
		 char    RISFILLER08[15 + 1];
		 char    RISPZN09[7 + 1];
		 char    RISKZMAN09[1 + 1];
		 char    RISTABHNR09[5 + 1];
		 char    RISSORKZ09[1 + 1];
		 char    RISVKART09[1 + 1];
		 char    RISFILLER09[15 + 1];
		 char    RISPZN10[7 + 1];
		 char    RISKZMAN10[1 + 1];
		 char    RISTABHNR10[5 + 1];
		 char    RISSORKZ10[1 + 1];
		 char    RISVKART10[1 + 1];
		 char    RISFILLER10[15 + 1];
		 char    RISPZN11[7 + 1];
		 char    RISKZMAN11[1 + 1];
		 char    RISTABHNR11[5 + 1];
		 char    RISSORKZ11[1 + 1];
		 char    RISVKART11[1 + 1];
		 char    RISFILLER11[15 + 1];
		 char    RISPZN12[7 + 1];
		 char    RISKZMAN12[1 + 1];
		 char    RISTABHNR12[5 + 1];
		 char    RISSORKZ12[1 + 1];
		 char    RISVKART12[1 + 1];
		 char    RISFILLER12[15 + 1];
		 char    RISKZHV;
		 char    RISLOE;
		 char    RISFILLER2[18 + 1];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct I_DKRIS {
		 short  RISFIL;
		 short  RISKUBZ;
		 short  RISPZN1;
		 short  RISPZN2;
		 short  RISFIL2;
		 short  RISPZN01;
		 short  RISKZMAN01;
		 short  RISTABHNR01;
		 short  RISSORKZ01;
		 short  RISVKART01;
		 short  RISFILLER01;
		 short  RISPZN02;
		 short  RISKZMAN02;
		 short  RISTABHNR02;
		 short  RISSORKZ02;
		 short  RISVKART02;
		 short  RISFILLER02;
		 short  RISPZN03;
		 short  RISKZMAN03;
		 short  RISTABHNR03;
		 short  RISSORKZ03;
		 short  RISVKART03;
		 short  RISFILLER03;
		 short  RISPZN04;
		 short  RISKZMAN04;
		 short  RISTABHNR04;
		 short  RISSORKZ04;
		 short  RISVKART04;
		 short  RISFILLER04;
		 short  RISPZN05;
		 short  RISKZMAN05;
		 short  RISTABHNR05;
		 short  RISSORKZ05;
		 short  RISVKART05;
		 short  RISFILLER05;
		 short  RISPZN06;
		 short  RISKZMAN06;
		 short  RISTABHNR06;
		 short  RISSORKZ06;
		 short  RISVKART06;
		 short  RISFILLER06;
		 short  RISPZN07;
		 short  RISKZMAN07;
		 short  RISTABHNR07;
		 short  RISSORKZ07;
		 short  RISVKART07;
		 short  RISFILLER07;
		 short  RISPZN08;
		 short  RISKZMAN08;
		 short  RISTABHNR08;
		 short  RISSORKZ08;
		 short  RISVKART08;
		 short  RISFILLER08;
		 short  RISPZN09;
		 short  RISKZMAN09;
		 short  RISTABHNR09;
		 short  RISSORKZ09;
		 short  RISVKART09;
		 short  RISFILLER09;
		 short  RISPZN10;
		 short  RISKZMAN10;
		 short  RISTABHNR10;
		 short  RISSORKZ10;
		 short  RISVKART10;
		 short  RISFILLER10;
		 short  RISPZN11;
		 short  RISKZMAN11;
		 short  RISTABHNR11;
		 short  RISSORKZ11;
		 short  RISVKART11;
		 short  RISFILLER11;
		 short  RISPZN12;
		 short  RISKZMAN12;
		 short  RISTABHNR12;
		 short  RISSORKZ12;
		 short  RISVKART12;
		 short  RISFILLER12;
		 short  RISKZHV;
		 short  RISLOE;
		 short  RISFILLER2;
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct S_DKRIS {
		 char    RISFIL[2 + 1];
		 char    RISKUBZ[12 + 1];
		 char    RISPZN1[7 + 1];
		 char    RISPZN2[7 + 1];
		 char    RISFIL2[2 + 1];
		 char    RISPZN01[7 + 1];
		 char    RISKZMAN01[1 + 1];
		 char    RISTABHNR01[5 + 1];
		 char    RISSORKZ01[1 + 1];
		 char    RISVKART01[1 + 1];
		 char    RISFILLER01[15 + 1];
		 char    RISPZN02[7 + 1];
		 char    RISKZMAN02[1 + 1];
		 char    RISTABHNR02[5 + 1];
		 char    RISSORKZ02[1 + 1];
		 char    RISVKART02[1 + 1];
		 char    RISFILLER02[15 + 1];
		 char    RISPZN03[7 + 1];
		 char    RISKZMAN03[1 + 1];
		 char    RISTABHNR03[5 + 1];
		 char    RISSORKZ03[1 + 1];
		 char    RISVKART03[1 + 1];
		 char    RISFILLER03[15 + 1];
		 char    RISPZN04[7 + 1];
		 char    RISKZMAN04[1 + 1];
		 char    RISTABHNR04[5 + 1];
		 char    RISSORKZ04[1 + 1];
		 char    RISVKART04[1 + 1];
		 char    RISFILLER04[15 + 1];
		 char    RISPZN05[7 + 1];
		 char    RISKZMAN05[1 + 1];
		 char    RISTABHNR05[5 + 1];
		 char    RISSORKZ05[1 + 1];
		 char    RISVKART05[1 + 1];
		 char    RISFILLER05[15 + 1];
		 char    RISPZN06[7 + 1];
		 char    RISKZMAN06[1 + 1];
		 char    RISTABHNR06[5 + 1];
		 char    RISSORKZ06[1 + 1];
		 char    RISVKART06[1 + 1];
		 char    RISFILLER06[15 + 1];
		 char    RISPZN07[7 + 1];
		 char    RISKZMAN07[1 + 1];
		 char    RISTABHNR07[5 + 1];
		 char    RISSORKZ07[1 + 1];
		 char    RISVKART07[1 + 1];
		 char    RISFILLER07[15 + 1];
		 char    RISPZN08[7 + 1];
		 char    RISKZMAN08[1 + 1];
		 char    RISTABHNR08[5 + 1];
		 char    RISSORKZ08[1 + 1];
		 char    RISVKART08[1 + 1];
		 char    RISFILLER08[15 + 1];
		 char    RISPZN09[7 + 1];
		 char    RISKZMAN09[1 + 1];
		 char    RISTABHNR09[5 + 1];
		 char    RISSORKZ09[1 + 1];
		 char    RISVKART09[1 + 1];
		 char    RISFILLER09[15 + 1];
		 char    RISPZN10[7 + 1];
		 char    RISKZMAN10[1 + 1];
		 char    RISTABHNR10[5 + 1];
		 char    RISSORKZ10[1 + 1];
		 char    RISVKART10[1 + 1];
		 char    RISFILLER10[15 + 1];
		 char    RISPZN11[7 + 1];
		 char    RISKZMAN11[1 + 1];
		 char    RISTABHNR11[5 + 1];
		 char    RISSORKZ11[1 + 1];
		 char    RISVKART11[1 + 1];
		 char    RISFILLER11[15 + 1];
		 char    RISPZN12[7 + 1];
		 char    RISKZMAN12[1 + 1];
		 char    RISTABHNR12[5 + 1];
		 char    RISSORKZ12[1 + 1];
		 char    RISVKART12[1 + 1];
		 char    RISFILLER12[15 + 1];
		 char    RISKZHV[1 + 1];
		 char    RISLOE[1 + 1];
		 char    RISFILLER2[18 + 1];
       };

 struct O_DKRIS {
		 char    RISFIL[2];
		 char    RISKUBZ[12];
		 char    RISPZN1[7];
		 char    RISPZN2[7];
		 char    RISFIL2[2];
		 char    RISPZN01[7];
		 char    RISKZMAN01[1];
		 char    RISTABHNR01[5];
		 char    RISSORKZ01[1];
		 char    RISVKART01[1];
		 char    RISFILLER01[15];
		 char    RISPZN02[7];
		 char    RISKZMAN02[1];
		 char    RISTABHNR02[5];
		 char    RISSORKZ02[1];
		 char    RISVKART02[1];
		 char    RISFILLER02[15];
		 char    RISPZN03[7];
		 char    RISKZMAN03[1];
		 char    RISTABHNR03[5];
		 char    RISSORKZ03[1];
		 char    RISVKART03[1];
		 char    RISFILLER03[15];
		 char    RISPZN04[7];
		 char    RISKZMAN04[1];
		 char    RISTABHNR04[5];
		 char    RISSORKZ04[1];
		 char    RISVKART04[1];
		 char    RISFILLER04[15];
		 char    RISPZN05[7];
		 char    RISKZMAN05[1];
		 char    RISTABHNR05[5];
		 char    RISSORKZ05[1];
		 char    RISVKART05[1];
		 char    RISFILLER05[15];
		 char    RISPZN06[7];
		 char    RISKZMAN06[1];
		 char    RISTABHNR06[5];
		 char    RISSORKZ06[1];
		 char    RISVKART06[1];
		 char    RISFILLER06[15];
		 char    RISPZN07[7];
		 char    RISKZMAN07[1];
		 char    RISTABHNR07[5];
		 char    RISSORKZ07[1];
		 char    RISVKART07[1];
		 char    RISFILLER07[15];
		 char    RISPZN08[7];
		 char    RISKZMAN08[1];
		 char    RISTABHNR08[5];
		 char    RISSORKZ08[1];
		 char    RISVKART08[1];
		 char    RISFILLER08[15];
		 char    RISPZN09[7];
		 char    RISKZMAN09[1];
		 char    RISTABHNR09[5];
		 char    RISSORKZ09[1];
		 char    RISVKART09[1];
		 char    RISFILLER09[15];
		 char    RISPZN10[7];
		 char    RISKZMAN10[1];
		 char    RISTABHNR10[5];
		 char    RISSORKZ10[1];
		 char    RISVKART10[1];
		 char    RISFILLER10[15];
		 char    RISPZN11[7];
		 char    RISKZMAN11[1];
		 char    RISTABHNR11[5];
		 char    RISSORKZ11[1];
		 char    RISVKART11[1];
		 char    RISFILLER11[15];
		 char    RISPZN12[7];
		 char    RISKZMAN12[1];
		 char    RISTABHNR12[5];
		 char    RISSORKZ12[1];
		 char    RISVKART12[1];
		 char    RISFILLER12[15];
		 char    RISKZHV[1];
		 char    RISLOE[1];
		 char    RISFILLER2[18];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DKRIS_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   12 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,   21 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   18 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DKRIS_BES [] =
 {
	 { TYP_C,    2 ,   0 },
	 { TYP_C,   12 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,    2 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,   21 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,   21 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,   21 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,   21 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,   21 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,   21 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,   21 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,   21 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,   21 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,   21 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,   21 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_C,   21 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,   18 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDKRIS
 {
  public:

  DKRIS s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DKRIS_BES, DKRIS_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DKRIS_BES, DKRIS_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DKRIS_BES, DKRIS_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDKRIS()
  {
   ::buf_default((void *)&s, DKRIS_BES, DKRIS_ANZ);
  }
 };
#endif

#define DKRIS_CREATE(xxx)  EXEC SQL CREATE TABLE xxx (\
		 RISFIL             CHAR(2)         default " " NOT NULL,\
		 RISKUBZ            CHAR(12)        default " " NOT NULL,\
		 RISPZN1            CHAR(7)         default " " NOT NULL,\
		 RISPZN2            CHAR(7)         default " " NOT NULL,\
		 RISFIL2            CHAR(2)         default " " NOT NULL,\
		 RISPZN01           CHAR(7)         default " " NOT NULL,\
		 RISKZMAN01         CHAR(1)         default " " NOT NULL,\
		 RISTABHNR01        CHAR(5)         default " " NOT NULL,\
		 RISSORKZ01         CHAR(1)         default " " NOT NULL,\
		 RISVKART01         CHAR(1)         default " " NOT NULL,\
		 RISFILLER01        CHAR(15)        default " " NOT NULL,\
		 RISPZN02           CHAR(7)         default " " NOT NULL,\
		 RISKZMAN02         CHAR(1)         default " " NOT NULL,\
		 RISTABHNR02        CHAR(5)         default " " NOT NULL,\
		 RISSORKZ02         CHAR(1)         default " " NOT NULL,\
		 RISVKART02         CHAR(1)         default " " NOT NULL,\
		 RISFILLER02        CHAR(15)        default " " NOT NULL,\
		 RISPZN03           CHAR(7)         default " " NOT NULL,\
		 RISKZMAN03         CHAR(1)         default " " NOT NULL,\
		 RISTABHNR03        CHAR(5)         default " " NOT NULL,\
		 RISSORKZ03         CHAR(1)         default " " NOT NULL,\
		 RISVKART03         CHAR(1)         default " " NOT NULL,\
		 RISFILLER03        CHAR(15)        default " " NOT NULL,\
		 RISPZN04           CHAR(7)         default " " NOT NULL,\
		 RISKZMAN04         CHAR(1)         default " " NOT NULL,\
		 RISTABHNR04        CHAR(5)         default " " NOT NULL,\
		 RISSORKZ04         CHAR(1)         default " " NOT NULL,\
		 RISVKART04         CHAR(1)         default " " NOT NULL,\
		 RISFILLER04        CHAR(15)        default " " NOT NULL,\
		 RISPZN05           CHAR(7)         default " " NOT NULL,\
		 RISKZMAN05         CHAR(1)         default " " NOT NULL,\
		 RISTABHNR05        CHAR(5)         default " " NOT NULL,\
		 RISSORKZ05         CHAR(1)         default " " NOT NULL,\
		 RISVKART05         CHAR(1)         default " " NOT NULL,\
		 RISFILLER05        CHAR(15)        default " " NOT NULL,\
		 RISPZN06           CHAR(7)         default " " NOT NULL,\
		 RISKZMAN06         CHAR(1)         default " " NOT NULL,\
		 RISTABHNR06        CHAR(5)         default " " NOT NULL,\
		 RISSORKZ06         CHAR(1)         default " " NOT NULL,\
		 RISVKART06         CHAR(1)         default " " NOT NULL,\
		 RISFILLER06        CHAR(15)        default " " NOT NULL,\
		 RISPZN07           CHAR(7)         default " " NOT NULL,\
		 RISKZMAN07         CHAR(1)         default " " NOT NULL,\
		 RISTABHNR07        CHAR(5)         default " " NOT NULL,\
		 RISSORKZ07         CHAR(1)         default " " NOT NULL,\
		 RISVKART07         CHAR(1)         default " " NOT NULL,\
		 RISFILLER07        CHAR(15)        default " " NOT NULL,\
		 RISPZN08           CHAR(7)         default " " NOT NULL,\
		 RISKZMAN08         CHAR(1)         default " " NOT NULL,\
		 RISTABHNR08        CHAR(5)         default " " NOT NULL,\
		 RISSORKZ08         CHAR(1)         default " " NOT NULL,\
		 RISVKART08         CHAR(1)         default " " NOT NULL,\
		 RISFILLER08        CHAR(15)        default " " NOT NULL,\
		 RISPZN09           CHAR(7)         default " " NOT NULL,\
		 RISKZMAN09         CHAR(1)         default " " NOT NULL,\
		 RISTABHNR09        CHAR(5)         default " " NOT NULL,\
		 RISSORKZ09         CHAR(1)         default " " NOT NULL,\
		 RISVKART09         CHAR(1)         default " " NOT NULL,\
		 RISFILLER09        CHAR(15)        default " " NOT NULL,\
		 RISPZN10           CHAR(7)         default " " NOT NULL,\
		 RISKZMAN10         CHAR(1)         default " " NOT NULL,\
		 RISTABHNR10        CHAR(5)         default " " NOT NULL,\
		 RISSORKZ10         CHAR(1)         default " " NOT NULL,\
		 RISVKART10         CHAR(1)         default " " NOT NULL,\
		 RISFILLER10        CHAR(15)        default " " NOT NULL,\
		 RISPZN11           CHAR(7)         default " " NOT NULL,\
		 RISKZMAN11         CHAR(1)         default " " NOT NULL,\
		 RISTABHNR11        CHAR(5)         default " " NOT NULL,\
		 RISSORKZ11         CHAR(1)         default " " NOT NULL,\
		 RISVKART11         CHAR(1)         default " " NOT NULL,\
		 RISFILLER11        CHAR(15)        default " " NOT NULL,\
		 RISPZN12           CHAR(7)         default " " NOT NULL,\
		 RISKZMAN12         CHAR(1)         default " " NOT NULL,\
		 RISTABHNR12        CHAR(5)         default " " NOT NULL,\
		 RISSORKZ12         CHAR(1)         default " " NOT NULL,\
		 RISVKART12         CHAR(1)         default " " NOT NULL,\
		 RISFILLER12        CHAR(15)        default " " NOT NULL,\
		 RISKZHV            CHAR(1)         default " " NOT NULL,\
		 RISLOE             CHAR(1)         default " " NOT NULL,\
		 RISFILLER2         CHAR(18)        default " " NOT NULL  ) EXTENT SIZE 9 LOCK MODE ROW;

#define DKRIS_CREATE_INDEX(yyy,xxx) \

#define DKRIS_DELETE_INDEX(xxx) \


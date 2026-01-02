/******************************************************************************/
/* INCLUDE DATEI FUER CLIENT/SERVER-PIPE ANWENDUNG                            */
/******************************************************************************/


 #define L_DEZAPEAN_ZAPSA09              2
 #define L_DEZAPEAN_ZAP09EAN1            13
 #define L_DEZAPEAN_ZAP09PZN1            7
 #define L_DEZAPEAN_ZAP09LOEKZ1          1
 #define L_DEZAPEAN_ZAP09EAN2            13
 #define L_DEZAPEAN_ZAP09PZN2            7
 #define L_DEZAPEAN_ZAP09LOEKZ2          1
 #define L_DEZAPEAN_ZAP09EAN3            13
 #define L_DEZAPEAN_ZAP09PZN3            7
 #define L_DEZAPEAN_ZAP09LOEKZ3          1
 #define L_DEZAPEAN_ZAP09EAN4            13
 #define L_DEZAPEAN_ZAP09PZN4            7
 #define L_DEZAPEAN_ZAP09LOEKZ4          1
 #define L_DEZAPEAN_ZAP09EAN5            13
 #define L_DEZAPEAN_ZAP09PZN5            7
 #define L_DEZAPEAN_ZAP09LOEKZ5          1
 #define L_DEZAPEAN_ZAP09EAN6            13
 #define L_DEZAPEAN_ZAP09PZN6            7
 #define L_DEZAPEAN_ZAP09LOEKZ6          1
 #define L_DEZAPEAN_ZAP09EAN7            13
 #define L_DEZAPEAN_ZAP09PZN7            7
 #define L_DEZAPEAN_ZAP09LOEKZ7          1
 #define L_DEZAPEAN_ZAP09EAN8            13
 #define L_DEZAPEAN_ZAP09PZN8            7
 #define L_DEZAPEAN_ZAP09LOEKZ8          1
 #define L_DEZAPEAN_ZAP09EAN9            13
 #define L_DEZAPEAN_ZAP09PZN9            7
 #define L_DEZAPEAN_ZAP09LOEKZ9          1
 #define L_DEZAPEAN_ZAP09EAN10           13
 #define L_DEZAPEAN_ZAP09PZN10           7
 #define L_DEZAPEAN_ZAP09LOEKZ10         1
 #define L_DEZAPEAN_ZAP09EAN11           13
 #define L_DEZAPEAN_ZAP09PZN11           7
 #define L_DEZAPEAN_ZAP09LOEKZ11         1
 #define L_DEZAPEAN_ZAP09EAN12           13
 #define L_DEZAPEAN_ZAP09PZN12           7
 #define L_DEZAPEAN_ZAP09LOEKZ12         1
 #define L_DEZAPEAN_ZAP09EAN13           13
 #define L_DEZAPEAN_ZAP09PZN13           7
 #define L_DEZAPEAN_ZAP09LOEKZ13         1
 #define L_DEZAPEAN_ZAP09EAN14           13
 #define L_DEZAPEAN_ZAP09PZN14           7
 #define L_DEZAPEAN_ZAP09LOEKZ14         1
 #define L_DEZAPEAN_ZAP09FILLER          84

#if defined (BUF_DESC) || defined (C_BUF_DESC)

 #define DEZAPEAN_ANZ ( sizeof(DEZAPEAN_BES) / sizeof(struct buf_desc) )
#endif
 #define G_DEZAPEAN sizeof(struct DEZAPEAN)

 #define DEZAPEAN_H

 #define DEZAPEANZAPSA09                       0
 #define DEZAPEANZAP09EAN1                     1
 #define DEZAPEANZAP09PZN1                     2
 #define DEZAPEANZAP09LOEKZ1                   3
 #define DEZAPEANZAP09EAN2                     4
 #define DEZAPEANZAP09PZN2                     5
 #define DEZAPEANZAP09LOEKZ2                   6
 #define DEZAPEANZAP09EAN3                     7
 #define DEZAPEANZAP09PZN3                     8
 #define DEZAPEANZAP09LOEKZ3                   9
 #define DEZAPEANZAP09EAN4                     10
 #define DEZAPEANZAP09PZN4                     11
 #define DEZAPEANZAP09LOEKZ4                   12
 #define DEZAPEANZAP09EAN5                     13
 #define DEZAPEANZAP09PZN5                     14
 #define DEZAPEANZAP09LOEKZ5                   15
 #define DEZAPEANZAP09EAN6                     16
 #define DEZAPEANZAP09PZN6                     17
 #define DEZAPEANZAP09LOEKZ6                   18
 #define DEZAPEANZAP09EAN7                     19
 #define DEZAPEANZAP09PZN7                     20
 #define DEZAPEANZAP09LOEKZ7                   21
 #define DEZAPEANZAP09EAN8                     22
 #define DEZAPEANZAP09PZN8                     23
 #define DEZAPEANZAP09LOEKZ8                   24
 #define DEZAPEANZAP09EAN9                     25
 #define DEZAPEANZAP09PZN9                     26
 #define DEZAPEANZAP09LOEKZ9                   27
 #define DEZAPEANZAP09EAN10                    28
 #define DEZAPEANZAP09PZN10                    29
 #define DEZAPEANZAP09LOEKZ10                  30
 #define DEZAPEANZAP09EAN11                    31
 #define DEZAPEANZAP09PZN11                    32
 #define DEZAPEANZAP09LOEKZ11                  33
 #define DEZAPEANZAP09EAN12                    34
 #define DEZAPEANZAP09PZN12                    35
 #define DEZAPEANZAP09LOEKZ12                  36
 #define DEZAPEANZAP09EAN13                    37
 #define DEZAPEANZAP09PZN13                    38
 #define DEZAPEANZAP09LOEKZ13                  39
 #define DEZAPEANZAP09EAN14                    40
 #define DEZAPEANZAP09PZN14                    41
 #define DEZAPEANZAP09LOEKZ14                  42
 #define DEZAPEANZAP09FILLER                   43

#ifdef ESQL_C
EXEC SQL BEGIN DECLARE SECTION;
#endif

 struct O_DEZAPEAN {
		 char    ZAPSA09[2];
		 char    ZAP09EAN1[13];
		 char    ZAP09PZN1[7];
		 char    ZAP09LOEKZ1[1];
		 char    ZAP09EAN2[13];
		 char    ZAP09PZN2[7];
		 char    ZAP09LOEKZ2[1];
		 char    ZAP09EAN3[13];
		 char    ZAP09PZN3[7];
		 char    ZAP09LOEKZ3[1];
		 char    ZAP09EAN4[13];
		 char    ZAP09PZN4[7];
		 char    ZAP09LOEKZ4[1];
		 char    ZAP09EAN5[13];
		 char    ZAP09PZN5[7];
		 char    ZAP09LOEKZ5[1];
		 char    ZAP09EAN6[13];
		 char    ZAP09PZN6[7];
		 char    ZAP09LOEKZ6[1];
		 char    ZAP09EAN7[13];
		 char    ZAP09PZN7[7];
		 char    ZAP09LOEKZ7[1];
		 char    ZAP09EAN8[13];
		 char    ZAP09PZN8[7];
		 char    ZAP09LOEKZ8[1];
		 char    ZAP09EAN9[13];
		 char    ZAP09PZN9[7];
		 char    ZAP09LOEKZ9[1];
		 char    ZAP09EAN10[13];
		 char    ZAP09PZN10[7];
		 char    ZAP09LOEKZ10[1];
		 char    ZAP09EAN11[13];
		 char    ZAP09PZN11[7];
		 char    ZAP09LOEKZ11[1];
		 char    ZAP09EAN12[13];
		 char    ZAP09PZN12[7];
		 char    ZAP09LOEKZ12[1];
		 char    ZAP09EAN13[13];
		 char    ZAP09PZN13[7];
		 char    ZAP09LOEKZ13[1];
		 char    ZAP09EAN14[13];
		 char    ZAP09PZN14[7];
		 char    ZAP09LOEKZ14[1];
		 char    ZAP09FILLER[84];
       };

#ifdef ESQL_C
EXEC SQL END DECLARE SECTION;
#endif


#if defined (BUF_DESC)
 static struct buf_desc DEZAPEAN_BES [] =
 {
	 { TYP_C ,    2 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   13 ,   0 },
	 { TYP_C ,    7 ,   0 },
	 { TYP_C ,    1 ,   0 },
	 { TYP_C ,   84 ,   0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DEZAPEAN_BES [] =
 {
	 { TYP_C,    2 ,   0 },
	 { TYP_C,   13 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,   13 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,   13 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,   13 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,   13 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,   13 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,   13 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,   13 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,   13 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,   13 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,   13 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,   13 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,   13 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,   13 ,   0 },
	 { TYP_C,    7 ,   0 },
	 { TYP_F,    1 ,   0 },
	 { TYP_C,   84 ,   0 },
 };
#endif

#ifdef TRANSCLASS

 class CDEZAPEAN
 {
  public:

  DEZAPEAN s;
  char error_msg[81];
  int rc;

  void buf_default()
  {
   ::buf_default((void *) &s, DEZAPEAN_BES, DEZAPEAN_ANZ);
  }
  void Server(int fkt_nr, int pos=0)
  {
#ifdef WIN32
   rc=::ServerNr(pos,fkt_nr,(void *)&s,DEZAPEAN_BES, DEZAPEAN_ANZ, error_msg);
   #else
   rc=::Server(fkt_nr,(void *)&s,DEZAPEAN_BES, DEZAPEAN_ANZ, error_msg);
#endif
   if (rc<0) FehlerBehandlung( rc, error_msg );
  }
  CDEZAPEAN()
  {
   ::buf_default((void *)&s, DEZAPEAN_BES, DEZAPEAN_ANZ);
  }
 };
#endif


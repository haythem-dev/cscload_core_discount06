#ifndef __PP_DISCOUNT_H_
#define __PP_DISCOUNT_H_

/******************************************************************************/
/* u:\Discount ****************************************************************/
/******************************************************************************/

/* Length-Define of DISCOUNT **************************************************/

  #define L_DISCOUNT_BRANCHNO 6
  #define L_DISCOUNT_ARTICLENO 11
  #define L_DISCOUNT_DISCOUNTGRPNO 11
  #define L_DISCOUNT_PHARMACYGROUPID 3
  #define L_DISCOUNT_CUSTOMERNO 11
  #define L_DISCOUNT_GRPDISCOUNTTYP 6
  #define L_DISCOUNT_DATEFROM 11
  #define L_DISCOUNT_DATETO 11
  #define L_DISCOUNT_BASEQTY 11
  #define L_DISCOUNT_DISCOUNTSPEC 6
  #define L_DISCOUNT_DISCOUNTTYPE 6
  #define L_DISCOUNT_DISCOUNTQTY 6
  #define L_DISCOUNT_DISCOUNTVALUEPCT 5
  #define N_DISCOUNT_DISCOUNTVALUEPCT 2
  #define L_DISCOUNT_DISCOUNTQTYPCT 5
  #define N_DISCOUNT_DISCOUNTQTYPCT 2
  #define L_DISCOUNT_SURCHARGEPCT 5
  #define N_DISCOUNT_SURCHARGEPCT 2
  #define L_DISCOUNT_PHARMGRPEXCLUDED 3
  #define L_DISCOUNT_FIXEDPRICE 9
  #define N_DISCOUNT_FIXEDPRICE 2
  #define L_DISCOUNT_REFUNDPCT 5
  #define N_DISCOUNT_REFUNDPCT 2
  #define L_DISCOUNT_INTERNALDISCOUNT 1
  #define L_DISCOUNT_DISCOUNTARTICLE 11
  #define L_DISCOUNT_PHARMGRPEXCL_2 3
  #define L_DISCOUNT_PHARMGRPEXCL_3 3
  #define L_DISCOUNT_BASE_VALUE 10
  #define N_DISCOUNT_BASE_VALUE 2
  #define L_DISCOUNT_BASE_MULT_STD_QTY 11
  #define L_DISCOUNT_NO_MULTIPLE_QTY 1
  #define L_DISCOUNT_FIXEDDISCOUNTVALUE 9
  #define N_DISCOUNT_FIXEDDISCOUNTVALUE 2
  #define L_DISCOUNT_MANUFACTURERNO 11
  #define L_DISCOUNT_ARTCATEGORYNO 11
  #define L_DISCOUNT_PAYMENTTARGETNO 6
  #define L_DISCOUNT_GROSSPROFITPCT 5
  #define N_DISCOUNT_GROSSPROFITPCT 2
  #define L_DISCOUNT_ADDONDISCOUNTOK 1
  #define L_DISCOUNT_PAYMENTTERMTYPE 1
  #define L_DISCOUNT_TARGETQTY 11
  #define L_DISCOUNT_EXCEEDANCEPCT 5
  #define N_DISCOUNT_EXCEEDANCEPCT 2
  #define L_DISCOUNT_REFUNDTYPE 6
  #define L_DISCOUNT_ARTICLE_NO_PACK 11
  #define L_DISCOUNT_REFUNDVALUE 9
  #define N_DISCOUNT_REFUNDVALUE 2
  #define L_DISCOUNT_PROMOTION_NO 6
  #define L_DISCOUNT_MAXQTY 11
  #define L_DISCOUNT_TURNOVERCALCIMPACT 1
  #define L_DISCOUNT_ADDONDISCOUNT 1
  #define L_DISCOUNT_MONTHLYDISCOUNT 1
  #define L_DISCOUNT_DISCOUNTCALCFROM 6
  #define L_DISCOUNT_DISCOUNTAPPLYTO 6

/* Length/Count-Define of DISCOUNT ********************************************/

  #define LS_DISCOUNT_BRANCHNO 5 + 1
  #define LS_DISCOUNT_ARTICLENO 10 + 1
  #define LS_DISCOUNT_DISCOUNTGRPNO 10 + 1
  #define LS_DISCOUNT_PHARMACYGROUPID 3 + 1
  #define LS_DISCOUNT_CUSTOMERNO 10 + 1
  #define LS_DISCOUNT_GRPDISCOUNTTYP 5 + 1
  #define LS_DISCOUNT_DATEFROM 10 + 1
  #define LS_DISCOUNT_DATETO 10 + 1
  #define LS_DISCOUNT_BASEQTY 10 + 1
  #define LS_DISCOUNT_DISCOUNTSPEC 5 + 1
  #define LS_DISCOUNT_DISCOUNTTYPE 5 + 1
  #define LS_DISCOUNT_DISCOUNTQTY 5 + 1
  #define LS_DISCOUNT_DISCOUNTVALUEPCT 5 + 2
  #define LS_DISCOUNT_DISCOUNTQTYPCT 5 + 2
  #define LS_DISCOUNT_SURCHARGEPCT 5 + 2
  #define LS_DISCOUNT_PHARMGRPEXCLUDED 3 + 1
  #define LS_DISCOUNT_FIXEDPRICE 9 + 2
  #define LS_DISCOUNT_REFUNDPCT 5 + 2
  #define LS_DISCOUNT_INTERNALDISCOUNT 1 + 1
  #define LS_DISCOUNT_DISCOUNTARTICLE 10 + 1
  #define LS_DISCOUNT_PHARMGRPEXCL_2 3 + 1
  #define LS_DISCOUNT_PHARMGRPEXCL_3 3 + 1
  #define LS_DISCOUNT_BASE_VALUE 10 + 2
  #define LS_DISCOUNT_BASE_MULT_STD_QTY 10 + 1
  #define LS_DISCOUNT_NO_MULTIPLE_QTY 1 + 1
  #define LS_DISCOUNT_FIXEDDISCOUNTVALUE 9 + 2
  #define LS_DISCOUNT_MANUFACTURERNO 10 + 1
  #define LS_DISCOUNT_ARTCATEGORYNO 10 + 1
  #define LS_DISCOUNT_PAYMENTTARGETNO 5 + 1
  #define LS_DISCOUNT_GROSSPROFITPCT 5 + 2
  #define LS_DISCOUNT_ADDONDISCOUNTOK 1 + 1
  #define LS_DISCOUNT_PAYMENTTERMTYPE 1 + 1
  #define LS_DISCOUNT_TARGETQTY 10 + 1
  #define LS_DISCOUNT_EXCEEDANCEPCT 5 + 2
  #define LS_DISCOUNT_REFUNDTYPE 5 + 1
  #define LS_DISCOUNT_ARTICLE_NO_PACK 10 + 1
  #define LS_DISCOUNT_REFUNDVALUE 9 + 2
  #define LS_DISCOUNT_PROMOTION_NO 5 + 1
  #define LS_DISCOUNT_MAXQTY 10 + 1
  #define LS_DISCOUNT_TURNOVERCALCIMPACT 1 + 1
  #define LS_DISCOUNT_ADDONDISCOUNT 1 + 1
  #define LS_DISCOUNT_MONTHLYDISCOUNT 1 + 1
  #define LS_DISCOUNT_DISCOUNTCALCFROM 5 + 1
  #define LS_DISCOUNT_DISCOUNTAPPLYTO 5 + 1

  #define DISCOUNTBRANCHNO 0
  #define DISCOUNTARTICLENO 1
  #define DISCOUNTDISCOUNTGRPNO 2
  #define DISCOUNTPHARMACYGROUPID 3
  #define DISCOUNTCUSTOMERNO 4
  #define DISCOUNTGRPDISCOUNTTYP 5
  #define DISCOUNTDATEFROM 6
  #define DISCOUNTDATETO 7
  #define DISCOUNTBASEQTY 8
  #define DISCOUNTDISCOUNTSPEC 9
  #define DISCOUNTDISCOUNTTYPE 10
  #define DISCOUNTDISCOUNTQTY 11
  #define DISCOUNTDISCOUNTVALUEPCT 12
  #define DISCOUNTDISCOUNTQTYPCT 13
  #define DISCOUNTSURCHARGEPCT 14
  #define DISCOUNTPHARMGRPEXCLUDED 15
  #define DISCOUNTFIXEDPRICE 16
  #define DISCOUNTREFUNDPCT 17
  #define DISCOUNTINTERNALDISCOUNT 18
  #define DISCOUNTDISCOUNTARTICLE 19
  #define DISCOUNTPHARMGRPEXCL_2 20
  #define DISCOUNTPHARMGRPEXCL_3 21
  #define DISCOUNTBASE_VALUE 22
  #define DISCOUNTBASE_MULT_STD_QTY 23
  #define DISCOUNTNO_MULTIPLE_QTY 24
  #define DISCOUNTFIXEDDISCOUNTVALUE 25
  #define DISCOUNTMANUFACTURERNO 26
  #define DISCOUNTARTCATEGORYNO 27
  #define DISCOUNTPAYMENTTARGETNO 28
  #define DISCOUNTGROSSPROFITPCT 29
  #define DISCOUNTADDONDISCOUNTOK 30
  #define DISCOUNTPAYMENTTERMTYPE 31
  #define DISCOUNTTARGETQTY 32
  #define DISCOUNTEXCEEDANCEPCT 33
  #define DISCOUNTREFUNDTYPE 34
  #define DISCOUNTARTICLE_NO_PACK 35
  #define DISCOUNTREFUNDVALUE 36
  #define DISCOUNTPROMOTION_NO 37
  #define DISCOUNTMAXQTY 38
  #define DISCOUNTTURNOVERCALCIMPACT 39
  #define DISCOUNTADDONDISCOUNT 40
  #define DISCOUNTMONTHLYDISCOUNT 41
  #define DISCOUNTDISCOUNTCALCFROM 42
  #define DISCOUNTDISCOUNTAPPLYTO 43

/* define of Buf_Desc *********************************************************/

#if defined (BUF_DESC) || defined (C_BUF_DESC)
 #define DISCOUNT_H
 #define DISCOUNT_ANZ ( sizeof(DISCOUNT_BES) / sizeof(struct buf_desc) )
#endif

/* SqlDefine of DISCOUNT ******************************************************/

 #define DISCOUNT_LISTE \
         DISCOUNT.BRANCHNO,\
         DISCOUNT.ARTICLENO,\
         DISCOUNT.DISCOUNTGRPNO,\
         DISCOUNT.PHARMACYGROUPID,\
         DISCOUNT.CUSTOMERNO,\
         DISCOUNT.GRPDISCOUNTTYP,\
         DISCOUNT.DATEFROM,\
         DISCOUNT.DATETO,\
         DISCOUNT.BASEQTY,\
         DISCOUNT.DISCOUNTSPEC,\
         DISCOUNT.DISCOUNTTYPE,\
         DISCOUNT.DISCOUNTQTY,\
         DISCOUNT.DISCOUNTVALUEPCT,\
         DISCOUNT.DISCOUNTQTYPCT,\
         DISCOUNT.SURCHARGEPCT,\
         DISCOUNT.PHARMGRPEXCLUDED,\
         DISCOUNT.FIXEDPRICE,\
         DISCOUNT.REFUNDPCT,\
         DISCOUNT.INTERNALDISCOUNT,\
         DISCOUNT.DISCOUNTARTICLE,\
         DISCOUNT.PHARMGRPEXCL_2,\
         DISCOUNT.PHARMGRPEXCL_3,\
         DISCOUNT.BASE_VALUE,\
         DISCOUNT.BASE_MULT_STD_QTY,\
         DISCOUNT.NO_MULTIPLE_QTY,\
         DISCOUNT.FIXEDDISCOUNTVALUE,\
         DISCOUNT.MANUFACTURERNO,\
         DISCOUNT.ARTCATEGORYNO,\
         DISCOUNT.PAYMENTTARGETNO,\
         DISCOUNT.GROSSPROFITPCT,\
         DISCOUNT.ADDONDISCOUNTOK,\
         DISCOUNT.PAYMENTTERMTYPE,\
         DISCOUNT.TARGETQTY,\
         DISCOUNT.EXCEEDANCEPCT,\
         DISCOUNT.REFUNDTYPE,\
         DISCOUNT.ARTICLE_NO_PACK,\
         DISCOUNT.REFUNDVALUE,\
         DISCOUNT.PROMOTION_NO,\
         DISCOUNT.MAXQTY,\
         DISCOUNT.TURNOVERCALCIMPACT,\
         DISCOUNT.ADDONDISCOUNT,\
         DISCOUNT.MONTHLYDISCOUNT,\
         DISCOUNT.DISCOUNTCALCFROM,\
         DISCOUNT.DISCOUNTAPPLYTO

         
 #define DISCOUNT_LISTE_390 \
         BRANCHNO,\
         ARTICLENO,\
         DISCOUNTGRPNO,\
         PHARMACYGROUPID,\
         CUSTOMERNO,\
         GRPDISCOUNTTYP,\
         DATEFROM,\
         DATETO,\
         BASEQTY,\
         DISCOUNTSPEC,\
         DISCOUNTTYPE,\
         DISCOUNTQTY,\
         DISCOUNTVALUEPCT,\
         DISCOUNTQTYPCT,\
         SURCHARGEPCT,\
         PHARMGRPEXCLUDED,\
         FIXEDPRICE,\
         REFUNDPCT,\
         INTERNALDISCOUNT,\
         DISCOUNTARTICLE,\
         PHARMGRPEXCL_2,\
         PHARMGRPEXCL_3,\
         BASE_VALUE,\
         BASE_MULT_STD_QTY,\
         NO_MULTIPLE_QTY,\
         FIXEDDISCOUNTVALUE,\
         MANUFACTURERNO,\
         ARTCATEGORYNO,\
         PAYMENTTARGETNO,\
         GROSSPROFITPCT,\
         ADDONDISCOUNTOK,\
         PAYMENTTERMTYPE,\
         TARGETQTY,\
         EXCEEDANCEPCT,\
         REFUNDTYPE,\
         ARTICLE_NO_PACK,\
         REFUNDVALUE,\
         PROMOTION_NO,\
         MAXQTY,\
         TURNOVERCALCIMPACT,\
         ADDONDISCOUNT,\
         MONTHLYDISCOUNT,\
         DISCOUNTCALCFROM,\
         DISCOUNTAPPLYTO

 #define DISCOUNT_PLISTE \
         "DISCOUNT.BRANCHNO,"\
         "DISCOUNT.ARTICLENO,"\
         "DISCOUNT.DISCOUNTGRPNO,"\
         "DISCOUNT.PHARMACYGROUPID,"\
         "DISCOUNT.CUSTOMERNO,"\
         "DISCOUNT.GRPDISCOUNTTYP,"\
         "DISCOUNT.DATEFROM,"\
         "DISCOUNT.DATETO,"\
         "DISCOUNT.BASEQTY,"\
         "DISCOUNT.DISCOUNTSPEC,"\
         "DISCOUNT.DISCOUNTTYPE,"\
         "DISCOUNT.DISCOUNTQTY,"\
         "DISCOUNT.DISCOUNTVALUEPCT,"\
         "DISCOUNT.DISCOUNTQTYPCT,"\
         "DISCOUNT.SURCHARGEPCT,"\
         "DISCOUNT.PHARMGRPEXCLUDED,"\
         "DISCOUNT.FIXEDPRICE,"\
         "DISCOUNT.REFUNDPCT,"\
         "DISCOUNT.INTERNALDISCOUNT,"\
         "DISCOUNT.DISCOUNTARTICLE,"\
         "DISCOUNT.PHARMGRPEXCL_2,"\
         "DISCOUNT.PHARMGRPEXCL_3,"\
         "DISCOUNT.BASE_VALUE,"\
         "DISCOUNT.BASE_MULT_STD_QTY,"\
         "DISCOUNT.NO_MULTIPLE_QTY,"\
         "DISCOUNT.FIXEDDISCOUNTVALUE,"\
         "DISCOUNT.MANUFACTURERNO,"\
         "DISCOUNT.ARTCATEGORYNO,"\
         "DISCOUNT.PAYMENTTARGETNO,"\
         "DISCOUNT.GROSSPROFITPCT,"\
         "DISCOUNT.ADDONDISCOUNTOK,"\
         "DISCOUNT.PAYMENTTERMTYPE,"\
         "DISCOUNT.TARGETQTY,"\
         "DISCOUNT.EXCEEDANCEPCT,"\
         "DISCOUNT.REFUNDTYPE,"\
         "DISCOUNT.ARTICLE_NO_PACK,"\
         "DISCOUNT.REFUNDVALUE,"\
         "DISCOUNT.PROMOTION_NO,"\
         "DISCOUNT.MAXQTY,"\
         "DISCOUNT.TURNOVERCALCIMPACT,"\
         "DISCOUNT.ADDONDISCOUNT,"\
         "DISCOUNT.MONTHLYDISCOUNT,"\
         "DISCOUNT.DISCOUNTCALCFROM,"\
         "DISCOUNTDISCOUNTAPPLYTO"

 #define DISCOUNT_PELISTE \
         "BRANCHNO,"\
         "ARTICLENO,"\
         "DISCOUNTGRPNO,"\
         "PHARMACYGROUPID,"\
         "CUSTOMERNO,"\
         "GRPDISCOUNTTYP,"\
         "DATEFROM,"\
         "DATETO,"\
         "BASEQTY,"\
         "DISCOUNTSPEC,"\
         "DISCOUNTTYPE,"\
         "DISCOUNTQTY,"\
         "DISCOUNTVALUEPCT,"\
         "DISCOUNTQTYPCT,"\
         "SURCHARGEPCT,"\
         "PHARMGRPEXCLUDED,"\
         "FIXEDPRICE,"\
         "REFUNDPCT,"\
         "INTERNALDISCOUNT,"\
         "DISCOUNTARTICLE,"\
         "PHARMGRPEXCL_2,"\
         "PHARMGRPEXCL_3,"\
         "BASE_VALUE,"\
         "BASE_MULT_STD_QTY,"\
         "NO_MULTIPLE_QTY,"\
         "FIXEDDISCOUNTVALUE,"\
         "MANUFACTURERNO,"\
         "ARTCATEGORYNO,"\
         "PAYMENTTARGETNO,"\
         "GROSSPROFITPCT,"\
         "ADDONDISCOUNTOK,"\
         "PAYMENTTERMTYPE,"\
         "TARGETQTY,"\
         "EXCEEDANCEPCT,"\
         "REFUNDTYPE,"\
         "ARTICLE_NO_PACK,"\
         "REFUNDVALUE,"\
         "PROMOTION_NO,"\
         "MAXQTY,"\
         "TURNOVERCALCIMPACT,"\
         "ADDONDISCOUNT,"\
         "MONTHLYDISCOUNT,"\
         "DISCOUNTCALCFROM,"\
         "DISCOUNTAPPLYTO"

 #define DISCOUNT_UPDLISTE \
         "BRANCHNO=?,"\
         "ARTICLENO=?,"\
         "DISCOUNTGRPNO=?,"\
         "PHARMACYGROUPID=?,"\
         "CUSTOMERNO=?,"\
         "GRPDISCOUNTTYP=?,"\
         "DATEFROM=?,"\
         "DATETO=?,"\
         "BASEQTY=?,"\
         "DISCOUNTSPEC=?,"\
         "DISCOUNTTYPE=?,"\
         "DISCOUNTQTY=?,"\
         "DISCOUNTVALUEPCT=?,"\
         "DISCOUNTQTYPCT=?,"\
         "SURCHARGEPCT=?,"\
         "PHARMGRPEXCLUDED=?,"\
         "FIXEDPRICE=?,"\
         "REFUNDPCT=?,"\
         "INTERNALDISCOUNT=?,"\
         "DISCOUNTARTICLE=?,"\
         "PHARMGRPEXCL_2=?,"\
         "PHARMGRPEXCL_3=?,"\
         "BASE_VALUE=?,"\
         "BASE_MULT_STD_QTY=?,"\
         "NO_MULTIPLE_QTY=?,"\
         "FIXEDDISCOUNTVALUE=?,"\
         "MANUFACTURERNO=?,"\
         "ARTCATEGORYNO=?,"\
         "PAYMENTTARGETNO=?,"\
         "GROSSPROFITPCT=?,"\
         "ADDONDISCOUNTOK=?,"\
         "PAYMENTTERMTYPE=?,"\
         "TARGETQTY=?,"\
         "EXCEEDANCEPCT=?,"\
         "REFUNDTYPE=?,"\
         "ARTICLE_NO_PACK=?,"\
         "REFUNDVALUE=?,"\
         "PROMOTION_NO=?,"\
         "MAXQTY=?,"\
         "TURNOVERCALCIMPACT=?,"\
         "ADDONDISCOUNT=?,"\
         "MONTHLYDISCOUNT=?,"\
         "DISCOUNTCALCFROM=?,"\
         "DISCOUNTAPPLYTO=?"

/* SqlMacros-Define of DISCOUNT ***********************************************/

 #define DISCOUNT_ZEIGER(x) \
         :x->BRANCHNO,\
         :x->ARTICLENO,\
         :x->DISCOUNTGRPNO,\
         :x->PHARMACYGROUPID,\
         :x->CUSTOMERNO,\
         :x->GRPDISCOUNTTYP,\
         :x->DATEFROM,\
         :x->DATETO,\
         :x->BASEQTY,\
         :x->DISCOUNTSPEC,\
         :x->DISCOUNTTYPE,\
         :x->DISCOUNTQTY,\
         :x->DISCOUNTVALUEPCT,\
         :x->DISCOUNTQTYPCT,\
         :x->SURCHARGEPCT,\
         :x->PHARMGRPEXCLUDED,\
         :x->FIXEDPRICE,\
         :x->REFUNDPCT,\
         :x->INTERNALDISCOUNT,\
         :x->DISCOUNTARTICLE,\
         :x->PHARMGRPEXCL_2,\
         :x->PHARMGRPEXCL_3,\
         :x->BASE_VALUE,\
         :x->BASE_MULT_STD_QTY,\
         :x->NO_MULTIPLE_QTY,\
         :x->FIXEDDISCOUNTVALUE,\
         :x->MANUFACTURERNO,\
         :x->ARTCATEGORYNO,\
         :x->PAYMENTTARGETNO,\
         :x->GROSSPROFITPCT,\
         :x->ADDONDISCOUNTOK,\
         :x->PAYMENTTERMTYPE,\
         :x->TARGETQTY,\
         :x->EXCEEDANCEPCT,\
         :x->REFUNDTYPE,\
         :x->ARTICLE_NO_PACK,\
         :x->REFUNDVALUE,\
         :x->PROMOTION_NO,\
         :x->MAXQTY,\
         :x->TURNOVERCALCIMPACT,\
         :x->ADDONDISCOUNT,\
         :x->MONTHLYDISCOUNT,\
         :x->DISCOUNTCALCFROM,\
         :x->DISCOUNTAPPLYTO

 #define DISCOUNT_ZEIGERSEL(x) \
         :x->BRANCHNO,\
         :x->ARTICLENO,\
         :x->DISCOUNTGRPNO,\
         :x->PHARMACYGROUPID,\
         :x->CUSTOMERNO,\
         :x->GRPDISCOUNTTYP,\
         :x->DATEFROM,\
         :x->DATETO,\
         :x->BASEQTY,\
         :x->DISCOUNTSPEC,\
         :x->DISCOUNTTYPE,\
         :x->DISCOUNTQTY,\
         :x->DISCOUNTVALUEPCT,\
         :x->DISCOUNTQTYPCT,\
         :x->SURCHARGEPCT,\
         :x->PHARMGRPEXCLUDED,\
         :x->FIXEDPRICE,\
         :x->REFUNDPCT,\
         :x->INTERNALDISCOUNT,\
         :x->DISCOUNTARTICLE,\
         :x->PHARMGRPEXCL_2,\
         :x->PHARMGRPEXCL_3,\
         :x->BASE_VALUE,\
         :x->BASE_MULT_STD_QTY,\
         :x->NO_MULTIPLE_QTY,\
         :x->FIXEDDISCOUNTVALUE,\
         :x->MANUFACTURERNO,\
         :x->ARTCATEGORYNO,\
         :x->PAYMENTTARGETNO,\
         :x->GROSSPROFITPCT,\
         :x->ADDONDISCOUNTOK,\
         :x->PAYMENTTERMTYPE,\
         :x->TARGETQTY,\
         :x->EXCEEDANCEPCT,\
         :x->REFUNDTYPE,\
         :x->ARTICLE_NO_PACK,\
         :x->REFUNDVALUE,\
         :x->PROMOTION_NO,\
         :x->MAXQTY,\
         :x->TURNOVERCALCIMPACT,\
         :x->ADDONDISCOUNT,\
         :x->MONTHLYDISCOUNT,\
         :x->DISCOUNTCALCFROM,\
         :x->DISCOUNTAPPLYTO

 #define DISCOUNT_UPDATE(x) \
         DISCOUNT.BRANCHNO=:x->BRANCHNO,\
         DISCOUNT.ARTICLENO=:x->ARTICLENO,\
         DISCOUNT.DISCOUNTGRPNO=:x->DISCOUNTGRPNO,\
         DISCOUNT.PHARMACYGROUPID=:x->PHARMACYGROUPID,\
         DISCOUNT.CUSTOMERNO=:x->CUSTOMERNO,\
         DISCOUNT.GRPDISCOUNTTYP=:x->GRPDISCOUNTTYP,\
         DISCOUNT.DATEFROM=:x->DATEFROM,\
         DISCOUNT.DATETO=:x->DATETO,\
         DISCOUNT.BASEQTY=:x->BASEQTY,\
         DISCOUNT.DISCOUNTSPEC=:x->DISCOUNTSPEC,\
         DISCOUNT.DISCOUNTTYPE=:x->DISCOUNTTYPE,\
         DISCOUNT.DISCOUNTQTY=:x->DISCOUNTQTY,\
         DISCOUNT.DISCOUNTVALUEPCT=:x->DISCOUNTVALUEPCT,\
         DISCOUNT.DISCOUNTQTYPCT=:x->DISCOUNTQTYPCT,\
         DISCOUNT.SURCHARGEPCT=:x->SURCHARGEPCT,\
         DISCOUNT.PHARMGRPEXCLUDED=:x->PHARMGRPEXCLUDED,\
         DISCOUNT.FIXEDPRICE=:x->FIXEDPRICE,\
         DISCOUNT.REFUNDPCT=:x->REFUNDPCT,\
         DISCOUNT.INTERNALDISCOUNT=:x->INTERNALDISCOUNT,\
         DISCOUNT.DISCOUNTARTICLE=:x->DISCOUNTARTICLE,\
         DISCOUNT.PHARMGRPEXCL_2=:x->PHARMGRPEXCL_2,\
         DISCOUNT.PHARMGRPEXCL_3=:x->PHARMGRPEXCL_3,\
         DISCOUNT.BASE_VALUE=:x->BASE_VALUE,\
         DISCOUNT.BASE_MULT_STD_QTY=:x->BASE_MULT_STD_QTY,\
         DISCOUNT.NO_MULTIPLE_QTY=:x->NO_MULTIPLE_QTY,\
         DISCOUNT.FIXEDDISCOUNTVALUE=:x->FIXEDDISCOUNTVALUE,\
         DISCOUNT.MANUFACTURERNO=:x->MANUFACTURERNO,\
         DISCOUNT.ARTCATEGORYNO=:x->ARTCATEGORYNO,\
         DISCOUNT.PAYMENTTARGETNO=:x->PAYMENTTARGETNO,\
         DISCOUNT.GROSSPROFITPCT=:x->GROSSPROFITPCT,\
         DISCOUNT.ADDONDISCOUNTOK=:x->ADDONDISCOUNTOK,\
         DISCOUNT.PAYMENTTERMTYPE=:x->PAYMENTTERMTYPE,\
         DISCOUNT.TARGETQTY=:x->TARGETQTY,\
         DISCOUNT.EXCEEDANCEPCT=:x->EXCEEDANCEPCT,\
         DISCOUNT.REFUNDTYPE=:x->REFUNDTYPE,\
         DISCOUNT.ARTICLE_NO_PACK=:x->ARTICLE_NO_PACK,\
         DISCOUNT.REFUNDVALUE=:x->REFUNDVALUE,\
         DISCOUNT.PROMOTION_NO=:x->PROMOTION_NO,\
         DISCOUNT.MAXQTY=:x->MAXQTY,\
         DISCOUNT.TURNOVERCALCIMPACT=:x->TURNOVERCALCIMPACT,\
         DISCOUNT.ADDONDISCOUNT=:x->ADDONDISCOUNT,\
         DISCOUNT.MONTHLYDISCOUNT=:x->MONTHLYDISCOUNT,\
         DISCOUNT.DISCOUNTCALCFROM=:x->DISCOUNTCALCFROM,\
         DISCOUNT.DISCOUNTAPPLYTO=:x->DISCOUNTAPPLYTO

/* SqlMacros390-Define of DISCOUNT ********************************************/

 #define DISCOUNT_ZEIGER_390 \
         :BRANCHNO,\
         :ARTICLENO,\
         :DISCOUNTGRPNO,\
         :PHARMACYGROUPID,\
         :CUSTOMERNO,\
         :GRPDISCOUNTTYP,\
         :DATEFROM,\
         :DATETO,\
         :BASEQTY,\
         :DISCOUNTSPEC,\
         :DISCOUNTTYPE,\
         :DISCOUNTQTY,\
         :DISCOUNTVALUEPCT,\
         :DISCOUNTQTYPCT,\
         :SURCHARGEPCT,\
         :PHARMGRPEXCLUDED,\
         :FIXEDPRICE,\
         :REFUNDPCT,\
         :INTERNALDISCOUNT,\
         :DISCOUNTARTICLE,\
         :PHARMGRPEXCL_2,\
         :PHARMGRPEXCL_3,\
         :BASE_VALUE,\
         :BASE_MULT_STD_QTY,\
         :NO_MULTIPLE_QTY,\
         :FIXEDDISCOUNTVALUE,\
         :MANUFACTURERNO,\
         :ARTCATEGORYNO,\
         :PAYMENTTARGETNO,\
         :GROSSPROFITPCT,\
         :ADDONDISCOUNTOK,\
         :PAYMENTTERMTYPE,\
         :TARGETQTY,\
         :EXCEEDANCEPCT,\
         :REFUNDTYPE,\
         :ARTICLE_NO_PACK,\
         :REFUNDVALUE,\
         :PROMOTION_NO,\
         :MAXQTY,\
         :TURNOVERCALCIMPACT,\
         :ADDONDISCOUNT,\
         :MONTHLYDISCOUNT,\
         :DISCOUNTCALCFROM,\
         :DISCOUNTAPPLYTO

 #define DISCOUNT_UPDATE_390 \
         BRANCHNO=:BRANCHNO,\
         ARTICLENO=:ARTICLENO,\
         DISCOUNTGRPNO=:DISCOUNTGRPNO,\
         PHARMACYGROUPID=:PHARMACYGROUPID,\
         CUSTOMERNO=:CUSTOMERNO,\
         GRPDISCOUNTTYP=:GRPDISCOUNTTYP,\
         DATEFROM=:DATEFROM,\
         DATETO=:DATETO,\
         BASEQTY=:BASEQTY,\
         DISCOUNTSPEC=:DISCOUNTSPEC,\
         DISCOUNTTYPE=:DISCOUNTTYPE,\
         DISCOUNTQTY=:DISCOUNTQTY,\
         DISCOUNTVALUEPCT=:DISCOUNTVALUEPCT,\
         DISCOUNTQTYPCT=:DISCOUNTQTYPCT,\
         SURCHARGEPCT=:SURCHARGEPCT,\
         PHARMGRPEXCLUDED=:PHARMGRPEXCLUDED,\
         FIXEDPRICE=:FIXEDPRICE,\
         REFUNDPCT=:REFUNDPCT,\
         INTERNALDISCOUNT=:INTERNALDISCOUNT,\
         DISCOUNTARTICLE=:DISCOUNTARTICLE,\
         PHARMGRPEXCL_2=:PHARMGRPEXCL_2,\
         PHARMGRPEXCL_3=:PHARMGRPEXCL_3,\
         BASE_VALUE=:BASE_VALUE,\
         BASE_MULT_STD_QTY=:BASE_MULT_STD_QTY,\
         NO_MULTIPLE_QTY=:NO_MULTIPLE_QTY,\
         FIXEDDISCOUNTVALUE=:FIXEDDISCOUNTVALUE,\
         MANUFACTURERNO=:MANUFACTURERNO,\
         ARTCATEGORYNO=:ARTCATEGORYNO,\
         PAYMENTTARGETNO=:PAYMENTTARGETNO,\
         GROSSPROFITPCT=:GROSSPROFITPCT,\
         ADDONDISCOUNTOK=:ADDONDISCOUNTOK,\
         PAYMENTTERMTYPE=:PAYMENTTERMTYPE,\
         TARGETQTY=:TARGETQTY,\
         EXCEEDANCEPCT=:EXCEEDANCEPCT,\
         REFUNDTYPE=:REFUNDTYPE,\
         ARTICLE_NO_PACK=:ARTICLE_NO_PACK,\
         REFUNDVALUE=:REFUNDVALUE,\
         PROMOTION_NO=:PROMOTION_NO,\
         MAXQTY=:MAXQTY,\
         TURNOVERCALCIMPACT=:TURNOVERCALCIMPACT,\
         ADDONDISCOUNT=:ADDONDISCOUNT,\
         MONTHLYDISCOUNT=:MONTHLYDISCOUNT,\
         DISCOUNTCALCFROM=:DISCOUNTCALCFROM,\
         DISCOUNTAPPLYTO=:DISCOUNTAPPLYTO

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* original Strucur of DISCOUNT ***********************************************/

 #ifndef TRANSCLASS
 typedef struct N_DISCOUNT {
         short BRANCHNO;
         long ARTICLENO;
         long DISCOUNTGRPNO;
         char PHARMACYGROUPID[4];
         long CUSTOMERNO;
         short GRPDISCOUNTTYP;
         long DATEFROM;
         long DATETO;
         long BASEQTY;
         short DISCOUNTSPEC;
         short DISCOUNTTYPE;
         short DISCOUNTQTY;
         double DISCOUNTVALUEPCT;
         double DISCOUNTQTYPCT;
         double SURCHARGEPCT;
         char PHARMGRPEXCLUDED[4];
         double FIXEDPRICE;
         double REFUNDPCT;
         char INTERNALDISCOUNT[2];
         long DISCOUNTARTICLE;
         char PHARMGRPEXCL_2[4];
         char PHARMGRPEXCL_3[4];
         double BASE_VALUE;
         long BASE_MULT_STD_QTY;
         char NO_MULTIPLE_QTY[2];
         double FIXEDDISCOUNTVALUE;
         long MANUFACTURERNO;
         long ARTCATEGORYNO;
         short PAYMENTTARGETNO;
         double GROSSPROFITPCT;
         char ADDONDISCOUNTOK[2];
         char PAYMENTTERMTYPE[2];
         long TARGETQTY;
         double EXCEEDANCEPCT;
         short REFUNDTYPE;
         long ARTICLE_NO_PACK;
         double REFUNDVALUE;
         short PROMOTION_NO;
         long MAXQTY;
         char TURNOVERCALCIMPACT[2];
         char ADDONDISCOUNT[2];
         char MONTHLYDISCOUNT[2];
         short DISCOUNTCALCFROM;
         short DISCOUNTAPPLYTO;
        } discountS;
 #else /*TRANSCLASS*/
 typedef struct N_DISCOUNT {
         short BRANCHNO;
         long ARTICLENO;
         long DISCOUNTGRPNO;
         char PHARMACYGROUPID[4];
         long CUSTOMERNO;
         short GRPDISCOUNTTYP;
         long DATEFROM;
         long DATETO;
         long BASEQTY;
         short DISCOUNTSPEC;
         short DISCOUNTTYPE;
         short DISCOUNTQTY;
         double DISCOUNTVALUEPCT;
         double DISCOUNTQTYPCT;
         double SURCHARGEPCT;
         char PHARMGRPEXCLUDED[4];
         double FIXEDPRICE;
         double REFUNDPCT;
         char INTERNALDISCOUNT[2];
         long DISCOUNTARTICLE;
         char PHARMGRPEXCL_2[4];
         char PHARMGRPEXCL_3[4];
         double BASE_VALUE;
         long BASE_MULT_STD_QTY;
         char NO_MULTIPLE_QTY[2];
         double FIXEDDISCOUNTVALUE;
         long MANUFACTURERNO;
         long ARTCATEGORYNO;
         short PAYMENTTARGETNO;
         double GROSSPROFITPCT;
         char ADDONDISCOUNTOK[2];
         char PAYMENTTERMTYPE[2];
         long TARGETQTY;
         double EXCEEDANCEPCT;
         short REFUNDTYPE;
         long ARTICLE_NO_PACK;
         double REFUNDVALUE;
         short PROMOTION_NO;
         long MAXQTY;
         char TURNOVERCALCIMPACT[2];
         char ADDONDISCOUNT[2];
         char MONTHLYDISCOUNT[2];
         short DISCOUNTCALCFROM;
         short DISCOUNTAPPLYTO;

                        bool operator==(const N_DISCOUNT& right) const {
                        return(
                                BRANCHNO == right.BRANCHNO &&
                                ARTICLENO == right.ARTICLENO &&
                                DISCOUNTGRPNO == right.DISCOUNTGRPNO &&
                                !strcmp(PHARMACYGROUPID, right.PHARMACYGROUPID) &&
                                CUSTOMERNO == right.CUSTOMERNO &&
                                GRPDISCOUNTTYP == right.GRPDISCOUNTTYP &&
                                DATEFROM == right.DATEFROM &&
                                DATETO == right.DATETO &&
                                BASEQTY == right.BASEQTY &&
                                DISCOUNTSPEC == right.DISCOUNTSPEC &&
                                DISCOUNTTYPE == right.DISCOUNTTYPE &&
                                DISCOUNTQTY == right.DISCOUNTQTY &&
                                DISCOUNTVALUEPCT == right.DISCOUNTVALUEPCT &&
                                DISCOUNTQTYPCT == right.DISCOUNTQTYPCT &&
                                SURCHARGEPCT == right.SURCHARGEPCT &&
                                !strcmp(PHARMGRPEXCLUDED, right.PHARMGRPEXCLUDED) &&
                                FIXEDPRICE == right.FIXEDPRICE &&
                                REFUNDPCT == right.REFUNDPCT &&
                                !strcmp(INTERNALDISCOUNT, right.INTERNALDISCOUNT) &&
                                DISCOUNTARTICLE == right.DISCOUNTARTICLE &&
                                !strcmp(PHARMGRPEXCL_2, right.PHARMGRPEXCL_2) &&
                                !strcmp(PHARMGRPEXCL_3, right.PHARMGRPEXCL_3) &&
                                BASE_VALUE == right.BASE_VALUE &&
                                BASE_MULT_STD_QTY == right.BASE_MULT_STD_QTY &&
                                !strcmp(NO_MULTIPLE_QTY, right.NO_MULTIPLE_QTY) &&
                                FIXEDDISCOUNTVALUE == right.FIXEDDISCOUNTVALUE &&
                                MANUFACTURERNO == right.MANUFACTURERNO &&
                                ARTCATEGORYNO == right.ARTCATEGORYNO &&
                                PAYMENTTARGETNO == right.PAYMENTTARGETNO &&
                                GROSSPROFITPCT == right.GROSSPROFITPCT &&
                                !strcmp(ADDONDISCOUNTOK, right.ADDONDISCOUNTOK) &&
                                !strcmp(PAYMENTTERMTYPE, right.PAYMENTTERMTYPE) &&
                                TARGETQTY == right.TARGETQTY &&
                                EXCEEDANCEPCT == right.EXCEEDANCEPCT &&
                                REFUNDTYPE == right.REFUNDTYPE &&
                                ARTICLE_NO_PACK == right.ARTICLE_NO_PACK &&
                                REFUNDVALUE == right.REFUNDVALUE &&
                                PROMOTION_NO == right.PROMOTION_NO &&
                                MAXQTY == right.MAXQTY &&
                                !strcmp(TURNOVERCALCIMPACT, right.TURNOVERCALCIMPACT) &&
                                !strcmp(ADDONDISCOUNT, right.ADDONDISCOUNT) &&
                                !strcmp(MONTHLYDISCOUNT, right.MONTHLYDISCOUNT) &&
                                DISCOUNTCALCFROM == right.DISCOUNTCALCFROM &&
                                DISCOUNTAPPLYTO == right.DISCOUNTAPPLYTO
                                );
                        }
                        void clear() {
#ifdef WIN32
                        memset((char*)this,0,sizeof(*this));
#else
                                BRANCHNO = 0;
                                ARTICLENO = 0;
                                DISCOUNTGRPNO = 0;
                                strcpy(PHARMACYGROUPID, " " );
                                CUSTOMERNO = 0;
                                GRPDISCOUNTTYP = 0;
                                DATEFROM = 0;
                                DATETO = 0;
                                BASEQTY = 0;
                                DISCOUNTSPEC = 0;
                                DISCOUNTTYPE = 0;
                                DISCOUNTQTY = 0;
                                DISCOUNTVALUEPCT = 0;
                                DISCOUNTQTYPCT = 0;
                                SURCHARGEPCT = 0;
                                strcpy(PHARMGRPEXCLUDED, " " );
                                FIXEDPRICE = 0;
                                REFUNDPCT = 0;
                                strcpy(INTERNALDISCOUNT, " " );
                                DISCOUNTARTICLE = 0;
                                strcpy(PHARMGRPEXCL_2, " " );
                                strcpy(PHARMGRPEXCL_3, " " );
                                BASE_VALUE = 0;
                                BASE_MULT_STD_QTY = 0;
                                strcpy(NO_MULTIPLE_QTY, " " );
                                FIXEDDISCOUNTVALUE = 0;
                                MANUFACTURERNO = 0;
                                ARTCATEGORYNO = 0;
                                PAYMENTTARGETNO = 0;
                                GROSSPROFITPCT = 0;
                                strcpy(ADDONDISCOUNTOK, " " );
                                strcpy(PAYMENTTERMTYPE, " " );
                                TARGETQTY = 0;
                                EXCEEDANCEPCT = 0;
                                REFUNDTYPE = 0;
                                ARTICLE_NO_PACK = 0;
                                REFUNDVALUE = 0;
                                PROMOTION_NO = 0;
                                MAXQTY = 0;
                                strcpy(TURNOVERCALCIMPACT, " " );
                                strcpy(ADDONDISCOUNT, " " );
                                strcpy(MONTHLYDISCOUNT, " " );
                                DISCOUNTCALCFROM = 0;
                                DISCOUNTAPPLYTO = 1;
#endif
                        }
         } discountS;
         #endif /*TRANSCLASS*/


#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer Structur of DISCOUNT ******************************************/

 struct S_DISCOUNT {
         char BRANCHNO[7];
         char ARTICLENO[11];
         char DISCOUNTGRPNO[11];
         char PHARMACYGROUPID[3 + 1];
         char CUSTOMERNO[11];
         char GRPDISCOUNTTYP[7];
         char DATEFROM[11];
         char DATETO[11];
         char BASEQTY[11];
         char DISCOUNTSPEC[7];
         char DISCOUNTTYPE[7];
         char DISCOUNTQTY[7];
         char DISCOUNTVALUEPCT[5 + 2];
         char DISCOUNTQTYPCT[5 + 2];
         char SURCHARGEPCT[5 + 2];
         char PHARMGRPEXCLUDED[3 + 1];
         char FIXEDPRICE[9 + 2];
         char REFUNDPCT[5 + 2];
         char INTERNALDISCOUNT[1 + 1];
         char DISCOUNTARTICLE[11];
         char PHARMGRPEXCL_2[3 + 1];
         char PHARMGRPEXCL_3[3 + 1];
         char BASE_VALUE[10 + 2];
         char BASE_MULT_STD_QTY[11];
         char NO_MULTIPLE_QTY[1 + 1];
         char FIXEDDISCOUNTVALUE[9 + 2];
         char MANUFACTURERNO[11];
         char ARTCATEGORYNO[11];
         char PAYMENTTARGETNO[7];
         char GROSSPROFITPCT[5 + 2];
         char ADDONDISCOUNTOK[1 + 1];
         char PAYMENTTERMTYPE[1 + 1];
         char TARGETQTY[11];
         char EXCEEDANCEPCT[5 + 2];
         char REFUNDTYPE[7];
         char ARTICLE_NO_PACK[11];
         char REFUNDVALUE[9 + 2];
         char PROMOTION_NO[7];
         char MAXQTY[11];
         char TURNOVERCALCIMPACT[1 + 1];
         char ADDONDISCOUNT[1 + 1];
         char MONTHLYDISCOUNT[1 + 1];
         char DISCOUNTCALCFROM[7];
         char DISCOUNTAPPLYTO[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Stringbuffer (without strend) Structur of DISCOUNT *************************/

 struct O_DISCOUNT {
         char BRANCHNO[7];
         char ARTICLENO[11];
         char DISCOUNTGRPNO[11];
         char PHARMACYGROUPID[3];
         char CUSTOMERNO[11];
         char GRPDISCOUNTTYP[7];
         char DATEFROM[11];
         char DATETO[11];
         char BASEQTY[11];
         char DISCOUNTSPEC[7];
         char DISCOUNTTYPE[7];
         char DISCOUNTQTY[7];
         char DISCOUNTVALUEPCT[5];
         char DISCOUNTQTYPCT[5];
         char SURCHARGEPCT[5];
         char PHARMGRPEXCLUDED[3];
         char FIXEDPRICE[9];
         char REFUNDPCT[5];
         char INTERNALDISCOUNT[1];
         char DISCOUNTARTICLE[11];
         char PHARMGRPEXCL_2[3];
         char PHARMGRPEXCL_3[3];
         char BASE_VALUE[10];
         char BASE_MULT_STD_QTY[11];
         char NO_MULTIPLE_QTY[1];
         char FIXEDDISCOUNTVALUE[9];
         char MANUFACTURERNO[11];
         char ARTCATEGORYNO[11];
         char PAYMENTTARGETNO[7];
         char GROSSPROFITPCT[5];
         char ADDONDISCOUNTOK[1];
         char PAYMENTTERMTYPE[1];
         char TARGETQTY[11];
         char EXCEEDANCEPCT[5];
         char REFUNDTYPE[7];
         char ARTICLE_NO_PACK[11];
         char REFUNDVALUE[9];
         char PROMOTION_NO[7];
         char MAXQTY[11];
         char TURNOVERCALCIMPACT[1];
         char ADDONDISCOUNT[1];
         char MONTHLYDISCOUNT[1];
         char DISCOUNTCALCFROM[7];
         char DISCOUNTAPPLYTO[7];
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Structur with real chartype of DISCOUNT ************************************/

 struct C_DISCOUNT {
         short BRANCHNO;
         long ARTICLENO;
         long DISCOUNTGRPNO;
         char PHARMACYGROUPID[4];
         long CUSTOMERNO;
         short GRPDISCOUNTTYP;
         long DATEFROM;
         long DATETO;
         long BASEQTY;
         short DISCOUNTSPEC;
         short DISCOUNTTYPE;
         short DISCOUNTQTY;
         double DISCOUNTVALUEPCT;
         double DISCOUNTQTYPCT;
         double SURCHARGEPCT;
         char PHARMGRPEXCLUDED[4];
         double FIXEDPRICE;
         double REFUNDPCT;
         char INTERNALDISCOUNT;
         long DISCOUNTARTICLE;
         char PHARMGRPEXCL_2[4];
         char PHARMGRPEXCL_3[4];
         double BASE_VALUE;
         long BASE_MULT_STD_QTY;
         char NO_MULTIPLE_QTY;
         double FIXEDDISCOUNTVALUE;
         long MANUFACTURERNO;
         long ARTCATEGORYNO;
         short PAYMENTTARGETNO;
         double GROSSPROFITPCT;
         char ADDONDISCOUNTOK;
         char PAYMENTTERMTYPE;
         long TARGETQTY;
         double EXCEEDANCEPCT;
         short REFUNDTYPE;
         long ARTICLE_NO_PACK;
         double REFUNDVALUE;
         short PROMOTION_NO;
         long MAXQTY;
         char TURNOVERCALCIMPACT;
         char ADDONDISCOUNT;
         char MONTHLYDISCOUNT;
         short DISCOUNTCALCFROM;
         short DISCOUNTAPPLYTO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

#ifdef ESQL_C
 EXEC SQL BEGIN DECLARE SECTION;
#endif

/* Sizetype  Structur (buf_desc) of DISCOUNT **********************************/

 struct I_DISCOUNT {
         short BRANCHNO;
         short ARTICLENO;
         short DISCOUNTGRPNO;
         short PHARMACYGROUPID;
         short CUSTOMERNO;
         short GRPDISCOUNTTYP;
         short DATEFROM;
         short DATETO;
         short BASEQTY;
         short DISCOUNTSPEC;
         short DISCOUNTTYPE;
         short DISCOUNTQTY;
         short DISCOUNTVALUEPCT;
         short DISCOUNTQTYPCT;
         short SURCHARGEPCT;
         short PHARMGRPEXCLUDED;
         short FIXEDPRICE;
         short REFUNDPCT;
         short INTERNALDISCOUNT;
         short DISCOUNTARTICLE;
         short PHARMGRPEXCL_2;
         short PHARMGRPEXCL_3;
         short BASE_VALUE;
         short BASE_MULT_STD_QTY;
         short NO_MULTIPLE_QTY;
         short FIXEDDISCOUNTVALUE;
         short MANUFACTURERNO;
         short ARTCATEGORYNO;
         short PAYMENTTARGETNO;
         short GROSSPROFITPCT;
         short ADDONDISCOUNTOK;
         short PAYMENTTERMTYPE;
         short TARGETQTY;
         short EXCEEDANCEPCT;
         short REFUNDTYPE;
         short ARTICLE_NO_PACK;
         short REFUNDVALUE;
         short PROMOTION_NO;
         short MAXQTY;
         short TURNOVERCALCIMPACT;
         short ADDONDISCOUNT;
         short MONTHLYDISCOUNT;
         short DISCOUNTCALCFROM;
         short DISCOUNTAPPLYTO;
         };

#ifdef ESQL_C
 EXEC SQL END DECLARE SECTION;
#endif

/* structures of Buf_Desc *****************************************************/

/* Structur (buf_desc) of DISCOUNT ********************************************/

#if defined (BUF_DESC)
 static struct buf_desc DISCOUNT_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_C, 3, 0 },
   { TYP_D, 9, 2 },
   { TYP_D, 5, 2 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 3, 0 },
   { TYP_D, 10, 2 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
 };
#elif defined (C_BUF_DESC)
 static struct buf_desc DISCOUNT_BES [] =
 {
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_D, 5, 2 },
   { TYP_C, 3, 0 },
   { TYP_D, 9, 2 },
   { TYP_D, 5, 2 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 3, 0 },
   { TYP_C, 3, 0 },
   { TYP_D, 10, 2 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_D, 9, 2 },
   { TYP_L , 11, 0 },
   { TYP_L , 11, 0 },
   { TYP_S ,  6, 0 },
   { TYP_D, 5, 2 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 5, 2 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_D, 9, 2 },
   { TYP_S ,  6, 0 },
   { TYP_L , 11, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_C, 1, 0 },
   { TYP_S ,  6, 0 },
   { TYP_S ,  6, 0 },
 };
#endif

/* description for datatypes of DISCOUNT **************************************/

 #define DISCOUNT_S390 \
         short BRANCHNO; \
         long ARTICLENO; \
         long DISCOUNTGRPNO; \
         char PHARMACYGROUPID[4]; \
         long CUSTOMERNO; \
         short GRPDISCOUNTTYP; \
         long DATEFROM; \
         long DATETO; \
         long BASEQTY; \
         short DISCOUNTSPEC; \
         short DISCOUNTTYPE; \
         short DISCOUNTQTY; \
         double DISCOUNTVALUEPCT; \
         double DISCOUNTQTYPCT; \
         double SURCHARGEPCT; \
         char PHARMGRPEXCLUDED[4]; \
         double FIXEDPRICE; \
         double REFUNDPCT; \
         char INTERNALDISCOUNT; \
         long DISCOUNTARTICLE; \
         char PHARMGRPEXCL_2[4]; \
         char PHARMGRPEXCL_3[4]; \
         double BASE_VALUE; \
         long BASE_MULT_STD_QTY; \
         char NO_MULTIPLE_QTY; \
         double FIXEDDISCOUNTVALUE; \
         long MANUFACTURERNO; \
         long ARTCATEGORYNO; \
         short PAYMENTTARGETNO; \
         double GROSSPROFITPCT; \
         char ADDONDISCOUNTOK; \
         char PAYMENTTERMTYPE; \
         long TARGETQTY; \
         double EXCEEDANCEPCT; \
         short REFUNDTYPE; \
         long ARTICLE_NO_PACK; \
         double REFUNDVALUE; \
         short PROMOTION_NO; \
         long MAXQTY; \
         char TURNOVERCALCIMPACT; \
         char ADDONDISCOUNT; \
         char MONTHLYDISCOUNT; \
         short DISCOUNTCALCFROM; \
         short DISCOUNTAPPLYTO; \



/* Copy-Function Struct to single Data DISCOUNT *******************************/

 #define DISCOUNT_S390_COPY_TO_SINGLE(_x_) \
         BRANCHNO=_x_->BRANCHNO;\
         ARTICLENO=_x_->ARTICLENO;\
         DISCOUNTGRPNO=_x_->DISCOUNTGRPNO;\
          strcpy(PHARMACYGROUPID,_x_->PHARMACYGROUPID);\
         CUSTOMERNO=_x_->CUSTOMERNO;\
         GRPDISCOUNTTYP=_x_->GRPDISCOUNTTYP;\
         DATEFROM=_x_->DATEFROM;\
         DATETO=_x_->DATETO;\
         BASEQTY=_x_->BASEQTY;\
         DISCOUNTSPEC=_x_->DISCOUNTSPEC;\
         DISCOUNTTYPE=_x_->DISCOUNTTYPE;\
         DISCOUNTQTY=_x_->DISCOUNTQTY;\
         DISCOUNTVALUEPCT=_x_->DISCOUNTVALUEPCT;\
         DISCOUNTQTYPCT=_x_->DISCOUNTQTYPCT;\
         SURCHARGEPCT=_x_->SURCHARGEPCT;\
          strcpy(PHARMGRPEXCLUDED,_x_->PHARMGRPEXCLUDED);\
         FIXEDPRICE=_x_->FIXEDPRICE;\
         REFUNDPCT=_x_->REFUNDPCT;\
         INTERNALDISCOUNT=_x_->INTERNALDISCOUNT;\
         DISCOUNTARTICLE=_x_->DISCOUNTARTICLE;\
          strcpy(PHARMGRPEXCL_2,_x_->PHARMGRPEXCL_2);\
          strcpy(PHARMGRPEXCL_3,_x_->PHARMGRPEXCL_3);\
         BASE_VALUE=_x_->BASE_VALUE;\
         BASE_MULT_STD_QTY=_x_->BASE_MULT_STD_QTY;\
         NO_MULTIPLE_QTY=_x_->NO_MULTIPLE_QTY;\
         FIXEDDISCOUNTVALUE=_x_->FIXEDDISCOUNTVALUE;\
         MANUFACTURERNO=_x_->MANUFACTURERNO;\
         ARTCATEGORYNO=_x_->ARTCATEGORYNO;\
         PAYMENTTARGETNO=_x_->PAYMENTTARGETNO;\
         GROSSPROFITPCT=_x_->GROSSPROFITPCT;\
         ADDONDISCOUNTOK=_x_->ADDONDISCOUNTOK;\
         PAYMENTTERMTYPE=_x_->PAYMENTTERMTYPE;\
         TARGETQTY=_x_->TARGETQTY;\
         EXCEEDANCEPCT=_x_->EXCEEDANCEPCT;\
         REFUNDTYPE=_x_->REFUNDTYPE;\
         ARTICLE_NO_PACK=_x_->ARTICLE_NO_PACK;\
         REFUNDVALUE=_x_->REFUNDVALUE;\
         PROMOTION_NO=_x_->PROMOTION_NO;\
         MAXQTY=_x_->MAXQTY;\
         TURNOVERCALCIMPACT=_x_->TURNOVERCALCIMPACT;\
         ADDONDISCOUNT=_x_->ADDONDISCOUNT;\
         MONTHLYDISCOUNT=_x_->MONTHLYDISCOUNT;\
         DISCOUNTCALCFROM=_x_->DISCOUNTCALCFROM;\
         DISCOUNTAPPLYTO=_x_->DISCOUNTAPPLYTO;\

 #define DISCOUNT_S390_COPY_TO_STRUCT(_x_) \
          _x_->BRANCHNO=BRANCHNO;\
          _x_->ARTICLENO=ARTICLENO;\
          _x_->DISCOUNTGRPNO=DISCOUNTGRPNO;\
          strcpy(_x_->PHARMACYGROUPID,PHARMACYGROUPID);\
          _x_->CUSTOMERNO=CUSTOMERNO;\
          _x_->GRPDISCOUNTTYP=GRPDISCOUNTTYP;\
          _x_->DATEFROM=DATEFROM;\
          _x_->DATETO=DATETO;\
          _x_->BASEQTY=BASEQTY;\
          _x_->DISCOUNTSPEC=DISCOUNTSPEC;\
          _x_->DISCOUNTTYPE=DISCOUNTTYPE;\
          _x_->DISCOUNTQTY=DISCOUNTQTY;\
          _x_->DISCOUNTVALUEPCT=DISCOUNTVALUEPCT;\
          _x_->DISCOUNTQTYPCT=DISCOUNTQTYPCT;\
          _x_->SURCHARGEPCT=SURCHARGEPCT;\
          strcpy(_x_->PHARMGRPEXCLUDED,PHARMGRPEXCLUDED);\
          _x_->FIXEDPRICE=FIXEDPRICE;\
          _x_->REFUNDPCT=REFUNDPCT;\
          _x_->INTERNALDISCOUNT=INTERNALDISCOUNT;\
          _x_->DISCOUNTARTICLE=DISCOUNTARTICLE;\
          strcpy(_x_->PHARMGRPEXCL_2,PHARMGRPEXCL_2);\
          strcpy(_x_->PHARMGRPEXCL_3,PHARMGRPEXCL_3);\
          _x_->BASE_VALUE=BASE_VALUE;\
          _x_->BASE_MULT_STD_QTY=BASE_MULT_STD_QTY;\
          _x_->NO_MULTIPLE_QTY=NO_MULTIPLE_QTY;\
          _x_->FIXEDDISCOUNTVALUE=FIXEDDISCOUNTVALUE;\
          _x_->MANUFACTURERNO=MANUFACTURERNO;\
          _x_->ARTCATEGORYNO=ARTCATEGORYNO;\
          _x_->PAYMENTTARGETNO=PAYMENTTARGETNO;\
          _x_->GROSSPROFITPCT=GROSSPROFITPCT;\
          _x_->ADDONDISCOUNTOK=ADDONDISCOUNTOK;\
          _x_->PAYMENTTERMTYPE=PAYMENTTERMTYPE;\
          _x_->TARGETQTY=TARGETQTY;\
          _x_->EXCEEDANCEPCT=EXCEEDANCEPCT;\
          _x_->REFUNDTYPE=REFUNDTYPE;\
          _x_->ARTICLE_NO_PACK=ARTICLE_NO_PACK;\
          _x_->REFUNDVALUE=REFUNDVALUE;\
          _x_->PROMOTION_NO=PROMOTION_NO;\
          _x_->MAXQTY=MAXQTY;\
          _x_->TURNOVERCALCIMPACT=TURNOVERCALCIMPACT;\
          _x_->ADDONDISCOUNT=ADDONDISCOUNT;\
          _x_->MONTHLYDISCOUNT=MONTHLYDISCOUNT;\
          _x_->DISCOUNTCALCFROM=DISCOUNTCALCFROM;\
          _x_->DISCOUNTAPPLYTO=DISCOUNTAPPLYTO;\



/* FunctionNumber-Define of Discount ******************************************/


#ifdef PRZ_OLD_FUNCTION
/* Old-FunctionNumber-Define of Discount **************************************/


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

class CDISCOUNT : public ppDadeVirtual
{
        //data members
        public:
                discountS s;
                int  rc;
                char error_msg[81];
        private:
                bool bOpenCursor;
                bool bEndOfSelect;
                int  FncNumber;
                int  CursorPos;
                int  AnzPos;
                vector<discountS> *pl; // pointer to class list

        //functions
        public:

                unsigned int    GetSize() const { return pl ? pl->size() : 0; }
                void            ClearStruct() { s.clear(); }
                bool            SetData(const unsigned int i) { if (GetSize() <= i) return false; s = pl->at(i); return true;}
                bool            SetList(const unsigned int i) { if (GetSize() <= i) return false; vector<discountS>::iterator itPtr = pl->begin() + i; *itPtr = s; return true; }
                bool            InsList() { if ( !pl ) pl = new vector<discountS>; Strip(s); discountS c = s; pl->insert(pl->end(),c); AnzPos++; return true; }
                bool            DelList(const unsigned int i) { if (GetSize() <= i) return false; vector<discountS>::iterator itPtr = pl->begin() + i; if ( itPtr < pl->end() ) pl->erase(itPtr); if ( --AnzPos < 0 ) AnzPos = 0; return true; }
                vector<discountS>::iterator begin(){ if (pl) return pl->begin(); else return NULL; };
                vector<discountS>::iterator end(){ if (pl) return pl->end(); else return NULL; };
                short           GetBranchno() const     { return s.BRANCHNO; }
                long            GetArticleno() const    { return s.ARTICLENO; }
                long            GetDiscountgrpno() const        { return s.DISCOUNTGRPNO; }
                const char*     GetPharmacygroupid(ppString& t) const   { t = s.PHARMACYGROUPID; t.erasespace(ppString::END); return t.c_str(); }
                long            GetCustomerno() const   { return s.CUSTOMERNO; }
                short           GetGrpdiscounttyp() const       { return s.GRPDISCOUNTTYP; }
                long            GetDatefrom() const     { return s.DATEFROM; }
                long            GetDateto() const       { return s.DATETO; }
                long            GetBaseqty() const      { return s.BASEQTY; }
                short           GetDiscountspec() const { return s.DISCOUNTSPEC; }
                short           GetDiscounttype() const { return s.DISCOUNTTYPE; }
                short           GetDiscountqty() const  { return s.DISCOUNTQTY; }
                double          GetDiscountvaluepct() const     { return s.DISCOUNTVALUEPCT; }
                double          GetDiscountqtypct() const       { return s.DISCOUNTQTYPCT; }
                double          GetSurchargepct() const { return s.SURCHARGEPCT; }
                const char*     GetPharmgrpexcluded(ppString& t) const  { t = s.PHARMGRPEXCLUDED; t.erasespace(ppString::END); return t.c_str(); }
                double          GetFixedprice() const   { return s.FIXEDPRICE; }
                double          GetRefundpct() const    { return s.REFUNDPCT; }
                char            GetInternaldiscount() const     { return s.INTERNALDISCOUNT[0]; }
                long            GetDiscountarticle() const      { return s.DISCOUNTARTICLE; }
                const char*     GetPharmgrpexcl_2(ppString& t) const    { t = s.PHARMGRPEXCL_2; t.erasespace(ppString::END); return t.c_str(); }
                const char*     GetPharmgrpexcl_3(ppString& t) const    { t = s.PHARMGRPEXCL_3; t.erasespace(ppString::END); return t.c_str(); }
                double          GetBase_value() const   { return s.BASE_VALUE; }
                long            GetBase_mult_std_qty() const    { return s.BASE_MULT_STD_QTY; }
                char            GetNo_multiple_qty() const      { return s.NO_MULTIPLE_QTY[0]; }
                double          GetFixeddiscountvalue() const   { return s.FIXEDDISCOUNTVALUE; }
                long            GetManufacturerno() const       { return s.MANUFACTURERNO; }
                long            GetArtcategoryno() const        { return s.ARTCATEGORYNO; }
                short           GetPaymenttargetno() const      { return s.PAYMENTTARGETNO; }
                double          GetGrossprofitpct() const       { return s.GROSSPROFITPCT; }
                char            GetAddondiscountok() const      { return s.ADDONDISCOUNTOK[0]; }
                char            GetPaymenttermtype() const      { return s.PAYMENTTERMTYPE[0]; }
                long            GetTargetqty() const    { return s.TARGETQTY; }
                double          GetExceedancepct() const        { return s.EXCEEDANCEPCT; }
                short           GetRefundtype() const   { return s.REFUNDTYPE; }
                long            GetArticle_no_pack() const      { return s.ARTICLE_NO_PACK; }
                double          GetRefundvalue() const  { return s.REFUNDVALUE; }
                short           GetPromotion_no() const { return s.PROMOTION_NO; }
                long            GetMaxqty() const       { return s.MAXQTY; }
                char            GetTurnovercalcimpact() const   { return s.TURNOVERCALCIMPACT[0]; }
                char            GetAddondiscount() const        { return s.ADDONDISCOUNT[0]; }
                char            GetMonthlydiscount() const      { return s.MONTHLYDISCOUNT[0]; }
                short           GetDiscountCalcFrom() const     { return s.DISCOUNTCALCFROM; }
                short           GetDiscountApplyTo() const      { return s.DISCOUNTAPPLYTO; }
                const discountS& GetStruct() const { return s; }
                void            SetBranchno(short t) { s.BRANCHNO = t; }
                void            SetArticleno(long t) { s.ARTICLENO = t; }
                void            SetDiscountgrpno(long t) { s.DISCOUNTGRPNO = t; }
                void            SetPharmacygroupid(const ppString& t) { ppGStrCopy(s.PHARMACYGROUPID,t.c_str() ,L_DISCOUNT_PHARMACYGROUPID); }
                void            SetCustomerno(long t) { s.CUSTOMERNO = t; }
                void            SetGrpdiscounttyp(short t) { s.GRPDISCOUNTTYP = t; }
                void            SetDatefrom(long t) { s.DATEFROM = t; }
                void            SetDateto(long t) { s.DATETO = t; }
                void            SetBaseqty(long t) { s.BASEQTY = t; }
                void            SetDiscountspec(short t) { s.DISCOUNTSPEC = t; }
                void            SetDiscounttype(short t) { s.DISCOUNTTYPE = t; }
                void            SetDiscountqty(short t) { s.DISCOUNTQTY = t; }
                void            SetDiscountvaluepct(double t) { s.DISCOUNTVALUEPCT = t; }
                void            SetDiscountqtypct(double t) { s.DISCOUNTQTYPCT = t; }
                void            SetSurchargepct(double t) { s.SURCHARGEPCT = t; }
                void            SetPharmgrpexcluded(const ppString& t) { ppGStrCopy(s.PHARMGRPEXCLUDED,t.c_str() ,L_DISCOUNT_PHARMGRPEXCLUDED); }
                void            SetFixedprice(double t) { s.FIXEDPRICE = t; }
                void            SetRefundpct(double t) { s.REFUNDPCT = t; }
                void            SetInternaldiscount(char t) { s.INTERNALDISCOUNT[0] = t; s.INTERNALDISCOUNT[1] = '\0';}
                void            SetDiscountarticle(long t) { s.DISCOUNTARTICLE = t; }
                void            SetPharmgrpexcl_2(const ppString& t) { ppGStrCopy(s.PHARMGRPEXCL_2,t.c_str() ,L_DISCOUNT_PHARMGRPEXCL_2); }
                void            SetPharmgrpexcl_3(const ppString& t) { ppGStrCopy(s.PHARMGRPEXCL_3,t.c_str() ,L_DISCOUNT_PHARMGRPEXCL_3); }
                void            SetBase_value(double t) { s.BASE_VALUE = t; }
                void            SetBase_mult_std_qty(long t) { s.BASE_MULT_STD_QTY = t; }
                void            SetNo_multiple_qty(char t) { s.NO_MULTIPLE_QTY[0] = t; s.NO_MULTIPLE_QTY[1] = '\0';}
                void            SetFixeddiscountvalue(double t) { s.FIXEDDISCOUNTVALUE = t; }
                void            SetManufacturerno(long t) { s.MANUFACTURERNO = t; }
                void            SetArtcategoryno(long t) { s.ARTCATEGORYNO = t; }
                void            SetPaymenttargetno(short t) { s.PAYMENTTARGETNO = t; }
                void            SetGrossprofitpct(double t) { s.GROSSPROFITPCT = t; }
                void            SetAddondiscountok(char t) { s.ADDONDISCOUNTOK[0] = t; s.ADDONDISCOUNTOK[1] = '\0';}
                void            SetPaymenttermtype(char t) { s.PAYMENTTERMTYPE[0] = t; s.PAYMENTTERMTYPE[1] = '\0';}
                void            SetTargetqty(long t) { s.TARGETQTY = t; }
                void            SetExceedancepct(double t) { s.EXCEEDANCEPCT = t; }
                void            SetRefundtype(short t) { s.REFUNDTYPE = t; }
                void            SetArticle_no_pack(long t) { s.ARTICLE_NO_PACK = t; }
                void            SetRefundvalue(double t) { s.REFUNDVALUE = t; }
                void            SetPromotion_no(short t) { s.PROMOTION_NO = t; }
                void            SetMaxqty(long t) { s.MAXQTY = t; }
                void            SetTurnovercalcimpact(char t) { s.TURNOVERCALCIMPACT[0] = t; s.TURNOVERCALCIMPACT[1] = '\0';}
                void            SetAddondiscount(char t) { s.ADDONDISCOUNT[0] = t; s.ADDONDISCOUNT[1] = '\0';}
                void            SetMonthlydiscount(char t) { s.MONTHLYDISCOUNT[0] = t; s.MONTHLYDISCOUNT[1] = '\0';}
                void            SetStruct(const discountS& t) { s = t; }

        //virtual functions
        public:

                int     Load(int pos=0) { return 1; }
                int     Save(int pos=0) { return 1; }
                int     Delete(int pos=0) { return 1; }
                int     SelList(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListHist(int FetchRel = 1,int pos=0) { return 1; }
                int     SelListFuture(int FetchRel = 1,int pos=0) { return 1; }
                CDISCOUNT()  //constructor
                {
                        ::buf_default((void *)&s, DISCOUNT_BES, DISCOUNT_ANZ);
                        bOpenCursor             = false;
                        bEndOfSelect    = false;
                        FncNumber               = 0;
                        CursorPos               = 0;
                        AnzPos                  = 0;
                        rc                      = 0;
                        pl = NULL;
                        s.clear();
                }

                virtual ~CDISCOUNT()  //destructor
                {
                        if(pl) {
                                delete pl;
                                pl = NULL;
                        }
                }

                void buf_default()  //buffer init
                {
                        ::buf_default((void *)&s, DISCOUNT_BES, DISCOUNT_ANZ);
                }

                int Server(int fkt_nr,int pos=0) // socket server call
                {
                        #ifdef WIN32
                        rc = ::ServerNr(pos, fkt_nr, (void *)&s, DISCOUNT_BES, DISCOUNT_ANZ, error_msg);
                        #else
                        rc = ::Server(fkt_nr, (void *)&s, DISCOUNT_BES, DISCOUNT_ANZ, error_msg);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

        private:

                void Strip(N_DISCOUNT& d)
                {
#ifdef WIN32
                        ppGStripLast(d.PHARMACYGROUPID);
                        ppGStripLast(d.PHARMGRPEXCLUDED);
                        ppGStripLast(d.PHARMGRPEXCL_2);
                        ppGStripLast(d.PHARMGRPEXCL_3);
#endif
                }


                int UniqueServerCall(int FncNr,int pos=0)
                {
                        #ifndef __DADE_LOAD__
                        rc = ::ServerNr(pos, FncNr, (void *)&s, DISCOUNT_BES, DISCOUNT_ANZ, error_msg);
                        #else
                        rc = DistributorFunSelect(FncNr, (void *)&s, error_msg, &rc);
                        #endif
                        if (rc<0) FehlerBehandlung( rc, error_msg );
                        return rc;
                }

};

#endif

/* CreateSqlStatement of DISCOUNT *********************************************/

 #define DISCOUNT_CREATE(x) exec sql create table x (\
         BRANCHNO smallint default 0 not null,\
         ARTICLENO integer default 0 not null,\
         DISCOUNTGRPNO integer default 0 not null,\
         PHARMACYGROUPID char(3) default " " not null,\
         CUSTOMERNO integer default 0 not null,\
         GRPDISCOUNTTYP smallint default 0 not null,\
         DATEFROM integer default 0 not null,\
         DATETO integer default 0 not null,\
         BASEQTY integer default 0 not null,\
         DISCOUNTSPEC smallint default 0 not null,\
         DISCOUNTTYPE smallint default 0 not null,\
         DISCOUNTQTY smallint default 0 not null,\
         DISCOUNTVALUEPCT decimal(5,2) default 0 not null,\
         DISCOUNTQTYPCT decimal(5,2) default 0 not null,\
         SURCHARGEPCT decimal(5,2) default 0 not null,\
         PHARMGRPEXCLUDED char(3) default " " not null,\
         FIXEDPRICE decimal(9,2) default 0 not null,\
         REFUNDPCT decimal(5,2) default 0 not null,\
         INTERNALDISCOUNT char(1) default " " not null,\
         DISCOUNTARTICLE integer default 0 not null,\
         PHARMGRPEXCL_2 char(3) default " " not null,\
         PHARMGRPEXCL_3 char(3) default " " not null,\
         BASE_VALUE decimal(10,2) default 0 not null,\
         BASE_MULT_STD_QTY integer default 0 not null,\
         NO_MULTIPLE_QTY char(1) default " " not null,\
         FIXEDDISCOUNTVALUE decimal(9,2) default 0 not null,\
         MANUFACTURERNO integer default 0 not null,\
         ARTCATEGORYNO integer default 0 not null,\
         PAYMENTTARGETNO smallint default 0 not null,\
         GROSSPROFITPCT decimal(5,2) default 0 not null,\
         ADDONDISCOUNTOK char(1) default " " not null,\
         PAYMENTTERMTYPE char(1) default " " not null,\
         TARGETQTY integer default 0 not null,\
         EXCEEDANCEPCT decimal(5,2) default 0 not null,\
         REFUNDTYPE smallint default 0 not null,\
         ARTICLE_NO_PACK integer default 0 not null,\
         REFUNDVALUE decimal(9,2) default 0 not null,\
         PROMOTION_NO smallint default 0 not null,\
         MAXQTY integer default 0 not null,\
         TURNOVERCALCIMPACT char(1) default " " not null,\
         ADDONDISCOUNT char(1) default " " not null,\
         MONTHLYDISCOUNT char(1) default " " not null,\
         DISCOUNTCALCFROM smallint default 0 not null,\
         DISCOUNTAPPLYTO smallint default 1 not null) in ksc extent size 80 next size 8 lock mode row;



/* CreateIndexStatement of DISCOUNT *******************************************/

 #define DISCOUNT_CREATE_INDEX(_X_,_Y_)\
              _Y_ = 0;\
         exec sql create   index i_discount_1 on _X_(\
              BranchNo,\
              ArticleNo,\
              DiscountType,\
              PharmacyGroupId ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index i_discount_2 on _X_(\
              BranchNo,\
              DiscountGrpNo,\
              PharmacyGroupId ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index i_discount_3 on _X_(\
              BranchNo,\
              ArticleNo,\
              CustomerNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index i_discount_4 on _X_(\
              BranchNo,\
              CustomerNo,\
              PharmacyGroupId,\
              ArticleNo,\
              manufacturerno,\
              DiscountGrpNo ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\
         exec sql create   index i_discount_5 on _X_(\
              BranchNo,\
              manufacturerno ) in kscidx;\
         if ( sqlca.sqlcode != 0 ) _Y_ = sqlca.sqlcode;\


/* DeleteIndexStatement of DISCOUNT *******************************************/

 #define DISCOUNT_DELETE_INDEX(_X_)\
              _X_ = 0;\
         exec sql drop index i_discount_1;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_discount_2;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_discount_3;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_discount_4;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\
         exec sql drop index i_discount_5;\
         if ( sqlca.sqlcode != 0 ) _X_ = sqlca.sqlcode;\



#endif

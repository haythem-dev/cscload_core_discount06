#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"

using namespace std;

void testSubSequentDelivery()
{
	short branchno = 44;
	long articleno = 53520;
	
	SessionUtil session(branchno);
	pxOrderTransmit* xmit = session.get();
	int retval = DistributeIncomingGoods( xmit->Session(), branchno, articleno );
	cout << "retval: " << retval << endl;
}

/*
INSERT INTO pharmostransactions (branchno,creationdatetime,vseoffset,processingstate,processedtimestamp,transferredtimestamp,datasetsequenceno,recordtype,customerno,bookingtype,userid,invoiceno,invoicetimestamp,customerorderno,cscorderno,turnover,paymentdate,paymenttype,pricetype,chainno,remainingdiscaccvalue,invoicevalue,discaccoperationno,priority,vouchertype,articleno,batch,expirydate,quantity,debitvalue,limitvalue,supplierno,purchaseorderno,costprice,storagelocation,storagearea,stationno,expirydatechangeflag,storagelocationchangeflag,costpricechangeflag,pharmacypurchasepricechangeflag,pharmacysellpricechangeflag,pharmacypurchaseprice,pharmacysellprice,ibtbranchno,codeblocage,quantitynatra,orderpositionno,dailyclosing,origin) VALUES (51,{ts '2014-11-10 07:29:51'},77440,'C',{ts '2014-11-10 07:29:56'},{ts '2014-11-10 07:30:01'},478,'WE','       ',1,0,'          ',{ts '9999-12-31 23:59:59'},0,'       ',0.000,{d '9999-12-31'},' ',' ',0,0.000,0.000,0,0,'  ',6583988,'                        ',{d '9999-12-31'},2,0.000,0.000,6245,'0087363',0.000,'        ',' ','  ',0,0,0,0,0,0.000,0.000,0,'  ',0,0,141108,0);
INSERT INTO nachlieferpos (kdauftragnr,posnr,datum,postyp,idfnr,artikel_nr,menge,filialnr1,filialnr2,filialnr3,status,ursprungauftragnr,ursprungposnr,kundennr,vertriebszentrumnr,erfasst,kdauftragart,posart,preisekaponetto,batchauftragnr,batchposnr,mengenatra,bemerkungen,preisekapo,preisvkapo,preisagp,datumvaluta,koart,buchart,code_type,article_code,discountvaluepct) VALUES (31387,1,20150223,3,3363973,53520,1,0,0,0,0,0,0,3363973,44,0,'HZ','P ',0.00,0,0,0,'BR20;0',1.55,2.99,0.00,0,'0','3',16,'10203595                 ',0.00);
*/

/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXGOODSDELIVERY.H
Generic goods delivery order entry definitions.

REVISION HISTORY

18 April 2005 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXGOODSDELDEFS_INC
   #define PXGOODSDELDEFS_INC

/*----------------------------------------------------------------------------*/
/*  Global server function prototypes for Goods Delivery Service              */
/*----------------------------------------------------------------------------*/

int  DistributeIncomingGoods(pxSession* session, short VZ, long articleno);
int  DistributeIncomingGoods_Old(pxSession* session, short VZ, long articleno);
int  DistributeIncomingGoods_New(pxSession* session, short VZ, long articleno);
int  WorkUpSpecialDeliveryPos(pxSession* session, short VZ, long articleno);
int  WorkUpSpecialCCDeliveryPos(pxSession* session, short VZ, long articleno);

#endif

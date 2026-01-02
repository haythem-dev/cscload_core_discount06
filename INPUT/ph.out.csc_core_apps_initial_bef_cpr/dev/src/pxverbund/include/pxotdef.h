/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXOTDEF.H
Internal Order Type Definitions.
*/

#ifndef PXOTDEF_INC
   #define PXOTDEF_INC

/*----------------------------------------------------------------------------*/
/*  Enumerate sales order categories.                                         */
/*----------------------------------------------------------------------------*/
enum tOrderTypeCode
{
    /* DCT Standard categories:                                               */
    NoOrderType             =  000    , /*     Keine Auftragsart              */
    Normal                  =  100    , /* NO  Normalauftrag                  */
    SBL                     =  200    , /* SB  whatever this is               */
    Batch                   =  300    , /* ST  Stapelauftrag                  */
    Service                 =  400    , /* SV  Service-Auftrag                */
    Test                    =  Service, /* TE  Test-Auftrag                   */
    StockPurchase           =  500    , /* VR  Vorratskauf                    */
    Tens                    =  600    , /* ZE  Zehner-Auftrag                 */
    TimeOrdered             =  700    , /* ZT  Zeitauftrag                    */
    Query                   =  800    , /* AN  Anfrage/Auskunft               */
    Special                 =  900    , /* SO  Sonderauftrag                  */

    /* Other standard categories:                                             */
    ScheduleOrder           = 2100    , /*  DI  Dispo-Faktur                  */
    OverStockBalance        = 2200    , /*  FU  Uebervorratsausgleich         */
    AdditionalDelivery      = 2300    , /*  NL  Kostenlose Nachlieferung      */
    Opiate                  = 2400    , /*  OP  Opiate-Lieferung              */
    NoDiscounts             = 2500    , /*  OR  Auftrag ohne Rabatt           */
    Transfer                = 2600    , /*  UW  Ueberweisungsauftrag          */
    BuyBack                 = 2700    , /*  RK  Rueckkauf                     */
    ScheduleQuantity        = 2800    , /*  MD  Mengen Dispo                  */
    OmgSwiss                = 2900    , /*  OM                                */
    IndustrieDispo          = 3000    , /*  ID                                */
    DispoTransfer           = 3100    , /*  DT                                */
    UnoTransfer             = 3200    , /*  UN                                */

    /* Some new categories for the french application                         */
    ShortBusiness           = 4000    , /*  SH  Short Business                */
    GenerikaOne             = 4001    , /*  G1  Generika                      */
    GenerikaTwo             = 4002    , /*  G2  Generika                      */
    GenerikaThree           = 4003    , /*  G3  Generika                      */
    PrismaOrder             = 4004    , /*  LO  Prisma                        */
    Generika                = 4005    , /*  GE  Generika                      */
    PhoenixMagic            = 4006    , /*  PM  Phoenix Magic                 */
    PriceFree               = 4007    , /*  RL  Price Free                    */
    OnlyInvoice             = 4008    , /*  NF  Only Invoice                  */
    Automate0               = 4009    , /*  A0  Automat 0                     */
    Automate1               = 4010    , /*  A1  Automat 1                     */
    Automate2               = 4011    , /*  A2  Automat 2                     */
    Automate3               = 4012    , /*  A3  Automat 3                     */
    Automate4               = 4013    , /*  A4  Automat 4                     */
    Automate5               = 4014    , /*  A5  Automat 5                     */
    Automate6               = 4015    , /*  A6  Automat 6                     */
    Automate7               = 4016    , /*  A7  Automat 7                     */
    Automate8               = 4017    , /*  A8  Automat 8                     */
    Automate9               = 4018    , /*  A9  Automat 9                     */
    ShortLineBusiness       = 4019    , /*  SL  Short Line Business           */
    ChronicIllness          = 4020    , /*  CC  Chronic Illness               */

    /* Some new categories for the Swiss  application                         */
    OverDrive               = 5000    , /*  OV  Overdrive                     */
    Express                 = 5001    , /*  EX  Express                       */

    /* Some new categories for the Serbian  application                       */
    QuarantineOrder         = 6000    , /*  QA  Quarantine                    */

    /* Some new categories for the Croatian  application                      */
    ProformaOrder           = 7000    , /*  PO  Proforma                      */

    /* Implementation defined                                                 */
    Special1                =  901    , /*  S1  Sonderauftrag 1               */
    Special2                =  902    , /*  S2  Sonderauftrag 2               */
    Special3                =  903    , /*  S3  Sonderauftrag 3               */
    Special4                =  904    , /*  S4  Sonderauftrag 4               */
    Special5                =  905    , /*  S5  Sonderauftrag 5               */
    Special6                =  906    , /*  S6  Sonderauftrag 6               */
    Special7                =  907    , /*  S7  Sonderauftrag 7               */
    Special8                =  908    , /*  S8  Sonderauftrag 8               */
    Special9                =  909    , /*  S9  Sonderauftrag 9               */
    SpecialLast             =  999    , /*  last supported special            */

    Active3000              = 8000    , /*  AK  Aktivkurs 3000                */
    Active4000              = 8001    , /*  AC  Aktivkurs 4000                */
    BountyOrder             = 8002    , /*  SP  Spenden Auftrag(PWSAT)        */
    DestructionOrder        = 8003    , /*  VE  Vernichtung Auftrag(PWSAT)    */
    PrivateProductRange     = 8004    , /*  PR  Privatsortiment Auftragsart(DE)*/
    CollectiveOrder         = 8005    , /*  CV  CollectiveOrder Auftragsart(FR)*/

    DiscountAccount         = 9000    , /*  RO  Rebate Order(BG)              */
    TenderOrder             = 9001    , /*  TO  Tender Order(BG)              */
    TenderInvoice           = 9002    , /*  TI  Tender Invoice Order(BG)      */
    CashOrder               = 9003    , /*  CO  Cash Order (BG)               */
    ManualPromotion         = 9004    , /*  MP  Manual Promotion / Stotinken (BG) */
    RetailSalesOrder        = 9005    , /*  EH  Retailsale(BG)                */
    ChargeRecallOrder       = 9006    , /*  BC  ChargeRecall(BG)              */
    FreeConditionOrder      = 9007    , /*  FC  FreeConditionOrder(BG)        */
    HighLimit               = 9999
};

#endif

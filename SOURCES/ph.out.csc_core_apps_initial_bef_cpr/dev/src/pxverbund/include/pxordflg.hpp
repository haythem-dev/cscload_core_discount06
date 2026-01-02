/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

PXORDFLG.HPP
Customer Order flag processing.
This file is intended to be included within the order class definition.

REVISION HISTORY

28 Aug 1995 V1.00 REV 00 written by Wolfgang Hoppe.
*/

#ifndef PXORDFLG_INC
   #define PXORDFLG_INC


/*----------------------------------------------------------------------------*/
/*  Order state queries.                                                      */
/*----------------------------------------------------------------------------*/
public:
    bool        IsEntryInProgress       () {return State_.TestBit(Order::EntryInProgress     ); }
    bool        IsUpdateInProgress      () {return State_.TestBit(Order::UpdateInProgress    ); }
    bool        IsEntryDeferred         () {return State_.TestBit(Order::EntryDeferred       ); }
    bool        IsEntryClosed           () {return State_.TestBit(Order::EntryClosed         ); }
    bool        IsShipmentInProgress    () {return State_.TestBit(Order::ShipmentInProgress  ); }
    bool        IsShipmentClosed        () {return State_.TestBit(Order::ShipmentClosed      ); }
    bool        IsInvoiceable           () {return State_.TestBit(Order::Invoiceable         ); }
    bool        IsInvoiced              () {return State_.TestBit(Order::Invoiced            ); }
    bool        IsCancelled             () {return State_.TestBit(Order::Cancelled           ); }
    bool        IsProtected             () {return State_.TestBit(Order::Protected           ); }
    bool        IsCustomerService       () {return State_.TestBit(Order::CustomerService     ); }
    bool        IsProblemClearance      () {return State_.TestBit(Order::ProblemClearance    ); }
    bool        IsCallBack              () {return State_.TestBit(Order::CallBack            ); }
    bool        IsDCParallel            () {return State_.TestBit(Order::DCParallel          ); }
    bool        IsConsolidation         () {return State_.TestBit(Order::Consolidation       ); }

    bool        IsOrderViewing          () { return (!(State_.TestBit(Order::EntryInProgress) ||
                                                        State_.TestBit(Order::UpdateInProgress)));}
    bool        IsOpen                  () {return (ItemList_ != NULL);}
    bool        IsChangeable();
    bool        IsOrderConsolidation();
    bool        IsOrderConsolidationMSV3();

/*----------------------------------------------------------------------------*/
/*  Order RCEntryDeffered  queries.                                           */
/*----------------------------------------------------------------------------*/
public:
    bool        IsKreditLimitErreicht   () {return RCEntryDeffered_.TestBit(Order::CreditLimitOnTop  );}
    bool        IsDefferedForInternet   () {return RCEntryDeffered_.TestBit(Order::InternetOrderEntry);}
    bool        IsDefferedForBackRouting() {return RCEntryDeffered_.TestBit(Order::BackRouting);}
    bool        IsDDNotClose            () {return RCEntryDeffered_.TestBit(Order::DDNotClose);}
    bool        IsSeparateArtGroup      () {return RCEntryDeffered_.TestBit(Order::SeparateArtGroup);}
    bool        IsDoNotAppend           () {return RCEntryDeffered_.TestBit(Order::DoNotAppend);}
    bool        IsOverDriveCondition    () {return RCEntryDeffered_.TestBit(Order::OverDriveCondition);}
    bool        IsRebateArtSelection    () {return RCEntryDeffered_.TestBit(Order::RebateArtSelection);}
    bool        IsNoRebateQty           () {return RCEntryDeffered_.TestBit(Order::NoRebateQty);       }
    bool        IsNoCics                () {return RCEntryDeffered_.TestBit(Order::NoCics);            }
    bool        IsNullDocument          () {return RCEntryDeffered_.TestBit(Order::NullDocument);      }
    bool        IsHighValuePosition     () {return RCEntryDeffered_.TestBit(Order::HighValuePosition); }
    bool        IsManufacturerInventory () {return RCEntryDeffered_.TestBit(Order::ManufacturerInventory); }
    bool        IsKonsigPartnerInventory() {return RCEntryDeffered_.TestBit(Order::KonsigPartnerInventory); }


/*----------------------------------------------------------------------------*/
/*  Setting/Clearing order state flags.                                       */
/*----------------------------------------------------------------------------*/
protected:
    void        SetEntryInProgress      () {State_.SetBit(Order::EntryInProgress      ); }
    void        SetUpdateInProgress     () {State_.SetBit(Order::UpdateInProgress     ); }
    void        SetEntryDeferred        () {State_.SetBit(Order::EntryDeferred        ); }
    void        SetEntryClosed          () {State_.SetBit(Order::EntryClosed          ); }
    void        SetShipmentInProgress   () {State_.SetBit(Order::ShipmentInProgress   ); }
    void        SetShipmentClosed       () {State_.SetBit(Order::ShipmentClosed       ); }
    void        SetInvoiceable          () {State_.SetBit(Order::Invoiceable          ); }
    void        SetInvoiced             () {State_.SetBit(Order::Invoiced             ); }
    void        SetCancelled            () {State_.SetBit(Order::Cancelled            ); }
    void        SetProtected            () {State_.SetBit(Order::Protected            ); }
    void        SetDCParallel           () {State_.SetBit(Order::DCParallel           ); }
    void        SetConsolidation        () {State_.SetBit(Order::Consolidation        ); }
public:
    void        SetCustomerService      () {State_.SetBit(Order::CustomerService      ); }
    void        SetProblemClearance     () {State_.SetBit(Order::ProblemClearance     ); }
    void        SetCallBack             () {State_.SetBit(Order::CallBack             ); }

protected:
    void        ClearEntryInProgress    () {State_.ClearBit(Order::EntryInProgress    ); }
    void        ClearUpdateInProgress   () {State_.ClearBit(Order::UpdateInProgress   ); }
    void        ClearEntryDeferred      () {State_.ClearBit(Order::EntryDeferred      ); }
    void        ClearEntryClosed        () {State_.ClearBit(Order::EntryClosed        ); }
    void        ClearShipmentInProgress () {State_.ClearBit(Order::ShipmentInProgress ); }
    void        ClearShipmentClosed     () {State_.ClearBit(Order::ShipmentClosed     ); }
    void        ClearInvoiceable        () {State_.ClearBit(Order::Invoiceable        ); }
    void        ClearInvoiced           () {State_.ClearBit(Order::Invoiced           ); }
    void        ClearCancelled          () {State_.ClearBit(Order::Cancelled          ); }
    void        ClearProtected          () {State_.ClearBit(Order::Protected          ); }
    void        ClearDCParallel         () {State_.ClearBit(Order::DCParallel         ); }
    void        ClearConsolidation      () {State_.ClearBit(Order::Consolidation      ); }
public:
    void        ClearCustomerService    () {State_.ClearBit(Order::CustomerService    ); }
    void        ClearProblemClearance   () {State_.ClearBit(Order::ProblemClearance   ); }
    void        ClearCallBack           () {State_.ClearBit(Order::CallBack           ); }

/*----------------------------------------------------------------------------*/
/*  Setting/Clearing Order RCEntryDeffered flags                              */
/*----------------------------------------------------------------------------*/
protected:
    void        SetKreditLimitErreicht   () {RCEntryDeffered_.SetBit(Order::CreditLimitOnTop  );}
    void        SetDefferedForBackRouting() {RCEntryDeffered_.SetBit(Order::BackRouting       );}
public:
    void        SetDefferedForInternet   () {RCEntryDeffered_.SetBit(Order::InternetOrderEntry);}
    void        SetDDNotClose            () {RCEntryDeffered_.SetBit(Order::DDNotClose);}
    void        SetSeparateArtGroup      () {RCEntryDeffered_.SetBit(Order::SeparateArtGroup  );}
    void        SetDoNotAppend           () {RCEntryDeffered_.SetBit(Order::DoNotAppend       );}
    void        SetOverDriveCondition    () {RCEntryDeffered_.SetBit(Order::OverDriveCondition);}
    void        SetRebateArtSelection    () {RCEntryDeffered_.SetBit(Order::RebateArtSelection);}
    void        SetNoRebateQty           () {RCEntryDeffered_.SetBit(Order::NoRebateQty);       }
    void        SetNoCics                () {RCEntryDeffered_.SetBit(Order::NoCics);            }
    void        SetNullDocument          () {RCEntryDeffered_.SetBit(Order::NullDocument);      }
    void        SetHighValuePosition     () {RCEntryDeffered_.SetBit(Order::HighValuePosition); }
    void        SetManufacturerInventory () {RCEntryDeffered_.SetBit(Order::ManufacturerInventory); }
    void        SetKonsigPartnerInventory() {RCEntryDeffered_.SetBit(Order::KonsigPartnerInventory); }

public:
    void        ClearKreditLimitErreicht    () {RCEntryDeffered_.ClearBit(Order::CreditLimitOnTop  );}
    void        ClearDefferedForInternet    () {RCEntryDeffered_.ClearBit(Order::InternetOrderEntry);}
    void        ClearDefferedForBackRouting () {RCEntryDeffered_.ClearBit(Order::BackRouting       );}
    void        ClearDDNotClose             () {RCEntryDeffered_.ClearBit(Order::DDNotClose        );}
    void        ClearSeparateArtGroup       () {RCEntryDeffered_.ClearBit(Order::SeparateArtGroup  );}
    void        ClearDoNotAppend            () {RCEntryDeffered_.ClearBit(Order::DoNotAppend       );}
    void        ClearOverDriveCondition     () {RCEntryDeffered_.ClearBit(Order::OverDriveCondition);}
    void        ClearRebateArtSelection     () {RCEntryDeffered_.ClearBit(Order::RebateArtSelection);}
    void        ClearNoRebateQty            () {RCEntryDeffered_.ClearBit(Order::NoRebateQty);       }
    void        ClearNoCics                 () {RCEntryDeffered_.ClearBit(Order::NoCics);            }
    void        ClearNullDocument           () {RCEntryDeffered_.ClearBit(Order::NullDocument);      }
    void        ClearHighValuePosition      () {RCEntryDeffered_.ClearBit(Order::HighValuePosition); }
    void        ClearManufacturerInventory  () {RCEntryDeffered_.ClearBit(Order::ManufacturerInventory); }
    void        ClearKonsigPartnerInventory () {RCEntryDeffered_.ClearBit(Order::KonsigPartnerInventory); }


/*----------------------------------------------------------------------------*/
/*  Misc. order flags.                                                        */
/*----------------------------------------------------------------------------*/
// define a name for the flag array:
#define FLAGS     ETAuftragSchalter_
#define FL_TEST   ETAuftragSchalter_.TestBit
#define FL_ON     ETAuftragSchalter_.SetBit
#define FL_OFF    ETAuftragSchalter_.ClearBit

    bool     IsRouteCheck            () {return FL_TEST(bRouteCheck         );}
    void    SetRouteCheck            () {       FL_ON  (bRouteCheck         );}
    void  ClearRouteCheck            () {       FL_OFF (bRouteCheck         );}

    bool     IsQuantityLimitCheck    () {return FL_TEST(bQuantityLimitCheck );}
    void    SetQuantityLimitCheck    () {       FL_ON  (bQuantityLimitCheck );}
    void  ClearQuantityLimitCheck    () {       FL_OFF (bQuantityLimitCheck );}

    bool     IsAuxPositions          () {return FL_TEST(bAuxPositions       );}
    void    SetAuxPositions          () {       FL_ON  (bAuxPositions       );}
    void  ClearAuxPositions          () {       FL_OFF (bAuxPositions       );}

    bool     IsCorruptLimitCheck     () {return FL_TEST(bCorruptLimitCheck  );}
    void    SetCorruptLimitCheck     () {       FL_ON  (bCorruptLimitCheck  );}
    void  ClearCorruptLimitCheck     () {       FL_OFF (bCorruptLimitCheck  );}

    bool     IsImmediatePrint        () {return FL_TEST(bImmediatePrint     );}
    void    SetImmediatePrint        () {       FL_ON  (bImmediatePrint     );}
    void  ClearImmediatePrint        () {       FL_OFF (bImmediatePrint     );}

    bool     IsSendOrderDouble       () {return FL_TEST(uDoppelteBestellung );}
    void    SetSendOrderDouble       () {       FL_ON  (uDoppelteBestellung );}
    void  ClearSendOrderDouble       () {       FL_OFF (uDoppelteBestellung );}

    bool     IsNotUpdateValdate      () {return FL_TEST(uKeinUpdateValutadatum );}
    void    SetNotUpdateValdate      () {       FL_ON  (uKeinUpdateValutadatum );}
    void  ClearNotUpdateValdate      () {       FL_OFF (uKeinUpdateValutadatum );}

    bool     IsSeparatedOrder        () {return FL_TEST(uAuftragGetrennt    );}
    void    SetSeparatedOrder        () {       FL_ON  (uAuftragGetrennt    );}
    void  ClearSeparatedOrder        () {       FL_OFF (uAuftragGetrennt    );}

    bool     IsBulgariaListFive      () {return FL_TEST(uBulgariaListFive   );}
    void    SetBulgariaListFive      () {       FL_ON  (uBulgariaListFive   );}
    void  ClearBulgariaListFive      () {       FL_OFF (uBulgariaListFive   );}

    bool    IsDoNotConnectDKRAK      () {return FL_TEST(bDoNotConnectDKRAK  );}
    void    SetDoNotConnectDKRAK     () {       FL_ON  (bDoNotConnectDKRAK  );}
    void  ClearDoNotConnectDKRAK     () {       FL_OFF (bDoNotConnectDKRAK  );}

    bool    IsEncloserSplitt         () {return FL_TEST(bEncloserSplitt     );}
    void    SetEncloserSplitt        () {       FL_ON  (bEncloserSplitt     );}
    void  ClearEncloserSplitt        () {       FL_OFF (bEncloserSplitt     );}

    bool    IsNoRebateAccount        () {return FL_TEST(bNoRebateAccount    );}
    void    SetNoRebateAccount       () {       FL_ON  (bNoRebateAccount    );}
    void  ClearNoRebateAccount       () {       FL_OFF (bNoRebateAccount    );}

    bool    IsSepDefectOrder         () {return FL_TEST(bSepDefectOrder     );}
    void    SetSepDefectOrder        () {       FL_ON  (bSepDefectOrder     );}
    void  ClearSepDefectOrder        () {       FL_OFF (bSepDefectOrder     );}

    bool    IsTurnOverOrigin         () {return FL_TEST(uTurnOverOrigin     );}
    void    SetTurnOverOrigin        () {       FL_ON  (uTurnOverOrigin     );}
    void  ClearTurnOverOrigin        () {       FL_OFF (uTurnOverOrigin     );}
/*----------------------------------------------------------------------------*/
/*  UNIPHARM/PHARMOS compatibilty.                                            */
/*----------------------------------------------------------------------------*/
public:

    bool     IsErfassungZurueckGestellt () {return FLAGS.TestBit(uErfassungZurueckGestellt   );}
    bool     IsErfassungAbgeschlossen   () {return FLAGS.TestBit(uErfassungAbgeschlossen     );}
    bool     IsKommiBegonnen            () {return FLAGS.TestBit(uKommiBegonnen              );}
    bool     IsKommiBeendet             () {return FLAGS.TestBit(uKommiBeendet               );}
    bool     IsFakturierbar             () {return FLAGS.TestBit(uFakturierbar               );}
    bool     IsFakturiert               () {return FLAGS.TestBit(uFakturiert                 );}
    bool     IsStorniert                () {return FLAGS.TestBit(uStorniert                  );}
    bool     IsNichtAenderbar           () {return FLAGS.TestBit(uNichtAenderbar             );}

    //bool     IsTourPruefen              () {return FLAGS.TestBit(uTourPruefen                );}
    //bool     IsKeinAckAufDS99           () {return FLAGS.TestBit(uKeinAckAufDS99             );}

    //bool     IsAuftragInQ1              () {return FLAGS.TestBit(uAuftragInQ1                );}
    //bool     IsAuftragInQ2              () {return FLAGS.TestBit(uAuftragInQ2                );}
    //bool     IsAuftragInQ3              () {return FLAGS.TestBit(uAuftragInQ3                );}
    //bool     IsAuftragInQ4              () {return FLAGS.TestBit(uAuftragInQ4                );}
    //bool     IsAuftragInQ8              () {return FLAGS.TestBit(uAuftragInQ8                );}
    bool     IsVerzoegerAusgeliefert    () {return FLAGS.TestBit(uVerzoegerAusgeliefert      );}
    bool     IsAuftragVomXML            () {return FLAGS.TestBit(uAuftragVomXML              );}
    //bool     IsAlterIDFAmedis           () {return FLAGS.TestBit(uAlterIDFAmedis             );}

    //bool     IsAuftragVonUMK            () {return FLAGS.TestBit(uAuftragVonUMK              );}
    //bool     IsUMKOnline                () {return FLAGS.TestBit(uUMKOnline                  );}
    //bool     IsUMKSeriell               () {return FLAGS.TestBit(uUMKSeriell                 );}
    //bool     IsZurueckstellenDAFUE      () {return FLAGS.TestBit(uZurueckstellenDAFUE        );}
    //bool     IsDefektLimitCheck         () {return FLAGS.TestBit(uDefektLimitCheck           );}
    //bool     IsDafueReinRuf             () {return FLAGS.TestBit(uDafueReinRuf               );}
    //bool     IsDafueAbbruch99           () {return FLAGS.TestBit(uDafueAbbruch99             );}
    //bool     IsDoppelteBestellung       () {return FLAGS.TestBit(uDoppelteBestellung         );}

    //bool     IsDAFUEAbbruch             () {return FLAGS.TestBit(uDAFUEAbbruch               );}
    //bool     IsKuehlBoxBuchen           () {return FLAGS.TestBit(uKuehlBoxBuchen             );}
    bool     IsKuehlBoxDisabled         () {return FLAGS.TestBit(uKuehlBoxDisabled           );}
    bool     IsBTMErwerbScheinBuchen    () {return FLAGS.TestBit(uBTMErwerbScheinBuchen      );}
    //bool     IsKeinLagerAuftrag         () {return FLAGS.TestBit(uKeinLagerAuftrag           );}
    //bool     IsAuftragInLagerEbene1     () {return FLAGS.TestBit(uAuftragInLagerEbene1       );}
    //bool     IsAuftragInLagerEbene2     () {return FLAGS.TestBit(uAuftragInLagerEbene2       );}
    //bool     IsAuftragInLagerEbene3     () {return FLAGS.TestBit(uAuftragInLagerEbene3       );}

    //bool     IsAuftragInLagerEbene4     () {return FLAGS.TestBit(uAuftragInLagerEbene4       );}
    //bool     IsAuftragInLagerEbene5     () {return FLAGS.TestBit(uAuftragInLagerEbene5       );}
    bool     IsAuftragSHWithC           () {return FLAGS.TestBit(uAuftragSHWithC             );}
    bool     IsAuftragSHWithS           () {return FLAGS.TestBit(uAuftragSHWithS             );}

    //bool     IsEintragQ4Notwendig       () {return FLAGS.TestBit(uEintragQ4Notwendig         );}
    //bool     IsVerbundPosition          () {return FLAGS.TestBit(uVerbundPosition            );}
    //bool     IsAutomatPositionVorhanden () {return FLAGS.TestBit(uAutomatPositionVorhanden   );}
    bool     IsMitWerbung               () {return FLAGS.TestBit(uMitWerbung                 );}
    bool     IsMitNachlieferung         () {return FLAGS.TestBit(uMitNachlieferung           );}
    //bool     IsMitNachAuslieferung      () {return FLAGS.TestBit(uMitNachAuslieferung        );}
    //bool     IsRechnungSofortDruck      () {return FLAGS.TestBit(uRechnungSofortDruck        );}
    bool     IsMitGefahrenGut           () {return FLAGS.TestBit(uMitGefahrenGut             );}

    bool     IsMitZytostatika           () {return FLAGS.TestBit(uMitZytostatika             );}
    //bool     IsQ2InStockLevel1          () {return FLAGS.TestBit(uQ2InStockLevel1            );}
    //bool     IsQ2InStockLevel2          () {return FLAGS.TestBit(uQ2InStockLevel2            );}
    //bool     IsQ2InStockLevel3          () {return FLAGS.TestBit(uQ2InStockLevel3            );}
    //bool     IsQ2InStockLevel4          () {return FLAGS.TestBit(uQ2InStockLevel4            );}
    //bool     IsQ2InStockLevel5          () {return FLAGS.TestBit(uQ2InStockLevel5            );}
    //bool     IsRabateArtikelSelection   () {return FLAGS.TestBit(uRabateArtikelSelection     );}

    bool     IsStammhausNewSuivra       () {return FLAGS.TestBit(uStammhausNewSuivra         );}
    bool     IsVerbundhausNewSuivra     () {return FLAGS.TestBit(uVerbundhausNewSuivra       );}

    void     SetVerzoegerAusgeliefert   () {FLAGS.SetBit(uVerzoegerAusgeliefert              );}
    void     SetAuftragVomXML           () {FLAGS.SetBit(uAuftragVomXML                      );}

    void    SetStammhausNewSuivra          () {FLAGS.SetBit(uStammhausNewSuivra         );}
    void    SetVerbundhausNewSuivra        () {FLAGS.SetBit(uVerbundhausNewSuivra       );}
protected:
    void  ClearErfassungZurueckGestellt    () {FLAGS.ClearBit(uErfassungZurueckGestellt   );}
    void  ClearErfassungAbgeschlossen      () {FLAGS.ClearBit(uErfassungAbgeschlossen     );}
    void  ClearKommiBegonnen               () {FLAGS.ClearBit(uKommiBegonnen              );}
    void  ClearKommiBeendet                () {FLAGS.ClearBit(uKommiBeendet               );}
    void  ClearFakturierbar                () {FLAGS.ClearBit(uFakturierbar               );}
    void  ClearFakturiert                  () {FLAGS.ClearBit(uFakturiert                 );}
    void  ClearStorniert                   () {FLAGS.ClearBit(uStorniert                  );}
    void  ClearNichtAenderbar              () {FLAGS.ClearBit(uNichtAenderbar             );}

    //void  ClearTourPruefen                 () {FLAGS.ClearBit(uTourPruefen                );}
    //void  ClearKeinAckAufDS99              () {FLAGS.ClearBit(uKeinAckAufDS99             );}

    //void  ClearAuftragInQ1                 () {FLAGS.ClearBit(uAuftragInQ1                );}
    //void  ClearAuftragInQ2                 () {FLAGS.ClearBit(uAuftragInQ2                );}
    //void  ClearAuftragInQ3                 () {FLAGS.ClearBit(uAuftragInQ3                );}
    //void  ClearAuftragInQ4                 () {FLAGS.ClearBit(uAuftragInQ4                );}
    //void  ClearAuftragInQ8                 () {FLAGS.ClearBit(uAuftragInQ8                );}
    void  ClearVerzoegerAusgeliefert       () {FLAGS.ClearBit(uVerzoegerAusgeliefert      );}
    void  ClearAuftragVomXML               () {FLAGS.ClearBit(uAuftragVomXML              );}
    //void  ClearAlterIDFAmedis              () {FLAGS.ClearBit(uAlterIDFAmedis             );}

    //void  ClearAuftragVonUMK               () {FLAGS.ClearBit(uAuftragVonUMK              );}
    //void  ClearUMKOnline                   () {FLAGS.ClearBit(uUMKOnline                  );}
    //void  ClearUMKSeriell                  () {FLAGS.ClearBit(uUMKSeriell                 );}
    //void  ClearZurueckstellenDAFUE         () {FLAGS.ClearBit(uZurueckstellenDAFUE        );}
    //void  ClearDefektLimitCheck            () {FLAGS.ClearBit(uDefektLimitCheck           );}
    //void  ClearDafueReinRuf                () {FLAGS.ClearBit(uDafueReinRuf               );}
    //void  ClearDafueAbbruch99              () {FLAGS.ClearBit(uDafueAbbruch99             );}
    //void  ClearDoppelteBestellung          () {FLAGS.ClearBit(uDoppelteBestellung         );}

    //void  ClearDAFUEAbbruch                () {FLAGS.ClearBit(uDAFUEAbbruch               );}
    //void  ClearKuehlBoxBuchen              () {FLAGS.ClearBit(uKuehlBoxBuchen             );}
    void  ClearKuehlBoxDisabled            () {FLAGS.ClearBit(uKuehlBoxDisabled           );}
    void  ClearBTMErwerbScheinBuchen       () {FLAGS.ClearBit(uBTMErwerbScheinBuchen      );}
    //void  ClearKeinLagerAuftrag            () {FLAGS.ClearBit(uKeinLagerAuftrag           );}
    //void  ClearAuftragInLagerEbene1        () {FLAGS.ClearBit(uAuftragInLagerEbene1       );}
    //void  ClearAuftragInLagerEbene2        () {FLAGS.ClearBit(uAuftragInLagerEbene2       );}
    //void  ClearAuftragInLagerEbene3        () {FLAGS.ClearBit(uAuftragInLagerEbene3       );}

    //void  ClearAuftragInLagerEbene4        () {FLAGS.ClearBit(uAuftragInLagerEbene4       );}
    //void  ClearAuftragInLagerEbene5        () {FLAGS.ClearBit(uAuftragInLagerEbene5       );}
    void  ClearAuftragSHWithC              () {FLAGS.ClearBit(uAuftragSHWithC             );}
    void  ClearAuftragSHWithS              () {FLAGS.ClearBit(uAuftragSHWithS             );}

    //void  ClearEintragQ4Notwendig          () {FLAGS.ClearBit(uEintragQ4Notwendig         );}
    //void  ClearVerbundPosition             () {FLAGS.ClearBit(uVerbundPosition            );}
    //void  ClearAutomatPositionVorhanden    () {FLAGS.ClearBit(uAutomatPositionVorhanden   );}
    void  ClearMitWerbung                  () {FLAGS.ClearBit(uMitWerbung                 );}
    void  ClearMitNachlieferung            () {FLAGS.ClearBit(uMitNachlieferung           );}
    //void  ClearMitNachAuslieferung         () {FLAGS.ClearBit(uMitNachAuslieferung        );}
    //void  ClearRechnungSofortDruck         () {FLAGS.ClearBit(uRechnungSofortDruck        );}
    void  ClearMitGefahrenGut              () {FLAGS.ClearBit(uMitGefahrenGut             );}

    void  ClearMitZytostatika              () {FLAGS.ClearBit(uMitZytostatika             );}
    //void  ClearQ2InStockLevel1             () {FLAGS.ClearBit(uQ2InStockLevel1            );}
    //void  ClearQ2InStockLevel2             () {FLAGS.ClearBit(uQ2InStockLevel2            );}
    //void  ClearQ2InStockLevel3             () {FLAGS.ClearBit(uQ2InStockLevel3            );}
    //void  ClearQ2InStockLevel4             () {FLAGS.ClearBit(uQ2InStockLevel4            );}
    //void  ClearQ2InStockLevel5             () {FLAGS.ClearBit(uQ2InStockLevel5            );}
    //void  ClearRabateArtikelSelection      () {FLAGS.ClearBit(uRabateArtikelSelection     );}

    void  ClearStammhausNewSuivra          () {FLAGS.ClearBit(uStammhausNewSuivra         );}
    void  ClearVerbundhausNewSuivra        () {FLAGS.ClearBit(uVerbundhausNewSuivra       );}

    void    SetErfassungZurueckGestellt    () {FLAGS.SetBit(uErfassungZurueckGestellt   );}
    void    SetErfassungAbgeschlossen      () {FLAGS.SetBit(uErfassungAbgeschlossen     );}
    void    SetKommiBegonnen               () {FLAGS.SetBit(uKommiBegonnen              );}
    void    SetKommiBeendet                () {FLAGS.SetBit(uKommiBeendet               );}
    void    SetFakturierbar                () {FLAGS.SetBit(uFakturierbar               );}
    void    SetFakturiert                  () {FLAGS.SetBit(uFakturiert                 );}
    void    SetStorniert                   () {FLAGS.SetBit(uStorniert                  );}
    void    SetNichtAenderbar              () {FLAGS.SetBit(uNichtAenderbar             );}

    //void    SetTourPruefen                 () {FLAGS.SetBit(uTourPruefen                );}
    //void    SetKeinAckAufDS99              () {FLAGS.SetBit(uKeinAckAufDS99             );}

    //void    SetAuftragInQ1                 () {FLAGS.SetBit(uAuftragInQ1                );}
    //void    SetAuftragInQ2                 () {FLAGS.SetBit(uAuftragInQ2                );}
    //void    SetAuftragInQ3                 () {FLAGS.SetBit(uAuftragInQ3                );}
    //void    SetAuftragInQ4                 () {FLAGS.SetBit(uAuftragInQ4                );}
    //void    SetAuftragInQ8                 () {FLAGS.SetBit(uAuftragInQ8                );}
    //void    SetAlterIDFAmedis              () {FLAGS.SetBit(uAlterIDFAmedis             );}

    //void    SetAuftragVonUMK               () {FLAGS.SetBit(uAuftragVonUMK              );}
    //void    SetUMKOnline                   () {FLAGS.SetBit(uUMKOnline                  );}
    //void    SetUMKSeriell                  () {FLAGS.SetBit(uUMKSeriell                 );}
    //void    SetZurueckstellenDAFUE         () {FLAGS.SetBit(uZurueckstellenDAFUE        );}
    //void    SetDefektLimitCheck            () {FLAGS.SetBit(uDefektLimitCheck           );}
    //void    SetDafueReinRuf                () {FLAGS.SetBit(uDafueReinRuf               );}
    //void    SetDafueAbbruch99              () {FLAGS.SetBit(uDafueAbbruch99             );}
    //void    SetDoppelteBestellung          () {FLAGS.SetBit(uDoppelteBestellung         );}

    //void    SetDAFUEAbbruch                () {FLAGS.SetBit(uDAFUEAbbruch               );}
    //void    SetKuehlBoxBuchen              () {FLAGS.SetBit(uKuehlBoxBuchen             );}
    void    SetKuehlBoxDisabled            () {FLAGS.SetBit(uKuehlBoxDisabled           );}
    void    SetBTMErwerbScheinBuchen       () {FLAGS.SetBit(uBTMErwerbScheinBuchen      );}
    //void    SetKeinLagerAuftrag            () {FLAGS.SetBit(uKeinLagerAuftrag           );}
    //void    SetAuftragInLagerEbene1        () {FLAGS.SetBit(uAuftragInLagerEbene1       );}
    //void    SetAuftragInLagerEbene2        () {FLAGS.SetBit(uAuftragInLagerEbene2       );}
    //void    SetAuftragInLagerEbene3        () {FLAGS.SetBit(uAuftragInLagerEbene3       );}

    //void    SetAuftragInLagerEbene4        () {FLAGS.SetBit(uAuftragInLagerEbene4       );}
    //void    SetAuftragInLagerEbene5        () {FLAGS.SetBit(uAuftragInLagerEbene5       );}
    void    SetAuftragSHWithC              () {FLAGS.SetBit(uAuftragSHWithC             );}
    void    SetAuftragSHWithS              () {FLAGS.SetBit(uAuftragSHWithS             );}

    //void    SetEintragQ4Notwendig          () {FLAGS.SetBit(uEintragQ4Notwendig         );}
    //void    SetVerbundPosition             () {FLAGS.SetBit(uVerbundPosition            );}
    //void    SetAutomatPositionVorhanden    () {FLAGS.SetBit(uAutomatPositionVorhanden   );}
    void    SetMitWerbung                  () {FLAGS.SetBit(uMitWerbung                 );}
    void    SetMitNachlieferung            () {FLAGS.SetBit(uMitNachlieferung           );}
    //void    SetMitNachAuslieferung         () {FLAGS.SetBit(uMitNachAuslieferung        );}
    //void    SetRechnungSofortDruck         () {FLAGS.SetBit(uRechnungSofortDruck        );}
    void    SetMitGefahrenGut              () {FLAGS.SetBit(uMitGefahrenGut             );}

    void    SetMitZytostatika              () {FLAGS.SetBit(uMitZytostatika             );}
    //void    SetQ2InStockLevel1             () {FLAGS.SetBit(uQ2InStockLevel1            );}
    //void    SetQ2InStockLevel2             () {FLAGS.SetBit(uQ2InStockLevel2            );}
    //void    SetQ2InStockLevel3             () {FLAGS.SetBit(uQ2InStockLevel3            );}
    //void    SetQ2InStockLevel4             () {FLAGS.SetBit(uQ2InStockLevel4            );}
    //void    SetQ2InStockLevel5             () {FLAGS.SetBit(uQ2InStockLevel5            );}
    //void    SetRabateArtikelSelection      () {FLAGS.SetBit(uRabateArtikelSelection     );}


#undef  FLAGS
#undef  FL_TEST
#undef  FL_ON
#undef  FL_OFF
#endif

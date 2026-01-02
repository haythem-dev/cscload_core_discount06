#include "stdafx.h"
#include "MAufDef.h"
#include "AeDoc.h"


CMAufDef::CMAufDef(CAeDoc* pDoc)
    : m_pDoc(pDoc)
{
    m_bNeuSetzen = false;
    m_bBemerkungEing = false;
    m_lAnzDef = 0L;
    m_lDatumDelayedDelivery = 0L;
    m_lDatumValuta = 0L;
    m_lIVC = 0L;
    m_lTenderNo = 0L;
    m_dBalance = 0.0;
    m_dBalance2 = 0.0;
    m_sServType = 0;
    m_bMitRab = false;
    m_bCashOrder= false;
}


// in
void CMAufDef::SetNeuSetzen(bool bNeuSetzen)
{
    m_bNeuSetzen = bNeuSetzen;
}

void CMAufDef::SetBemerkungEing(bool bBemerkungEing)
{
    m_bBemerkungEing = bBemerkungEing;
}

void CMAufDef::SetBatchschreiben(long lBatchschreiben)
{
    m_lBatchschreiben = lBatchschreiben;
}

void CMAufDef::SetKndNr(long kndNr)
{
    m_KndNr = kndNr;
}

void CMAufDef::SetIdfNr(long idfNr)
{
    m_IdfNr = idfNr;
}

void CMAufDef::SetVzNr(short vzNr)
{
    m_VzNr = vzNr;
}

void CMAufDef::SetMitRab(bool bMitRab)
{
    m_bMitRab = bMitRab;
}

void CMAufDef::SetShowCashOrder(bool bShowCashOrder)
{
    m_bShowCashOrder = bShowCashOrder;
}

CAeDoc* CMAufDef::GetDoc()
{
    return m_pDoc;
}

const bool& CMAufDef::GetNeuSetzen()
{
    return m_bNeuSetzen;
}

const bool& CMAufDef::GetBemerkungEing()
{
    return m_bBemerkungEing;
}

const long& CMAufDef::GetBatchschreiben()
{
    return m_lBatchschreiben;
}

const long& CMAufDef::GetKndNr()
{
    return m_KndNr;
}

const long& CMAufDef::GetIdfNr()
{
    return m_IdfNr;
}

const short& CMAufDef::GetVzNr()
{
    return m_VzNr;
}

const bool& CMAufDef::GetMitRab()
{
    return m_bMitRab;
}

const bool& CMAufDef::GetShowCashOrder()
{
    return m_bShowCashOrder;
}


// in/out
void CMAufDef::SetGebucht(bool bGebucht)
{
    m_bGebucht = bGebucht;
}

void CMAufDef::SetCashOrder(bool bCashOrder)
{
    m_bCashOrder = bCashOrder;
}

void CMAufDef::SetDatumDelayedDelivery(long lDatumDelayedDelivery)
{
    m_lDatumDelayedDelivery = lDatumDelayedDelivery;
}

void CMAufDef::SetValuta(long lValuta)
{
    m_lValuta = lValuta;
}

void CMAufDef::SetDatumValuta(long lDatumValuta)
{
    m_lDatumValuta = lDatumValuta;
}

void CMAufDef::SetABemerkung(CString aBemerkung)
{
    m_ABemerkung = aBemerkung;
}

void CMAufDef::SetTour(CString tour)
{
    m_Tour = tour;
}

void CMAufDef::SetDeliveryDate(long lDeliveryDate)
{
    m_lDeliveryDate = lDeliveryDate;
}

void CMAufDef::SetTenderNo(long lTenderNo)
{
    m_lTenderNo = lTenderNo;
}

void CMAufDef::SetServType(short sServType)
{
    m_sServType = sServType;
}

void CMAufDef::SetZuGrund(CString cZuGrund)
{
    m_cZuGrund = cZuGrund;
}

void CMAufDef::SetIVC(long lIVC)
{
    m_lIVC = lIVC;
}

void CMAufDef::SetNoRabattKonto(bool bNoRabattKonto)
{
    m_bNoRabattKonto = bNoRabattKonto;
}

void CMAufDef::SetAArt(CString AArt)
{
    m_AArt = AArt;
}

void CMAufDef::SetSubType(CString SubType)
{
    m_SubType = SubType;
}

void CMAufDef::SetBuchArt(CString BuchArt)
{
    m_BuchArt = BuchArt;
}

void CMAufDef::SetKommArt(CString KommArt)
{
    m_KommArt = KommArt;
}

const bool& CMAufDef::GetGebucht()
{
    return m_bGebucht;
}

const bool& CMAufDef::GetCashOrder()
{
    return m_bCashOrder;
}

const long& CMAufDef::GetDatumDelayedDelivery()
{
    return m_lDatumDelayedDelivery;
}

const long& CMAufDef::GetValuta()
{
    return m_lValuta;
}

const long& CMAufDef::GetDatumValuta()
{
    return m_lDatumValuta;
}

const CString& CMAufDef::GetABemerkung()
{
    return m_ABemerkung;
}

const CString& CMAufDef::GetTour()
{
    return m_Tour;
}

const long& CMAufDef::GetDeliveryDate()
{
    return m_lDeliveryDate;
}

const long& CMAufDef::GetTenderNo()
{
    return m_lTenderNo;
}

const short& CMAufDef::GetServType()
{
    return m_sServType;
}

const CString& CMAufDef::GetZuGrund()
{
    return m_cZuGrund;
}

const long& CMAufDef::GetIVC()
{
    return m_lIVC;
}

const bool& CMAufDef::GetNoRabattKonto()
{
    return m_bNoRabattKonto;
}

const CString& CMAufDef::GetAArt()
{
    return m_AArt;
}

const CString& CMAufDef::GetSubType()
{
    return m_SubType;
}

const CString& CMAufDef::GetBuchArt()
{
    return m_BuchArt;
}

const CString& CMAufDef::GetKommArt()
{
    return m_KommArt;
}


// out
void CMAufDef::SetBalance(double dBalance)
{
    m_dBalance = dBalance;
}

void CMAufDef::SetBalance2(double dBalance2)
{
    m_dBalance2 = dBalance2;
}

void CMAufDef::SetAnzDef(long lAnzDef)
{
    m_lAnzDef = lAnzDef;
}

const double& CMAufDef::GetBalance()
{
    return m_dBalance;
}

const double& CMAufDef::GetBalance2()
{
    return m_dBalance2;
}

const long& CMAufDef::GetAnzDef()
{
    return m_lAnzDef;
}

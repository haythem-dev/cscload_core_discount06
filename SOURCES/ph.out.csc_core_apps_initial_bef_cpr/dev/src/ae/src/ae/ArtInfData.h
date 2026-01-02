#pragma once

#include <articleomg.h>
#include <artikel.h>
#include <customer.h>

struct SArtInfData
{
    long m_ArtikelNr;
    short m_FilialNr;
    long m_lKndNr;

    CString m_CArtName;
    CString m_CArtNr;
    CString m_CArtEinh;
    CString m_CHerst;
    CString m_CArtDarr;
    CString m_CWarenGr;
    CString m_CTherapGr;
    CString m_CNachfArt;
    CString m_CLagArt;

    CString m_CRabatt;
    CString m_CInnField;

};

struct SArtInfPackageData
{
    CString m_CContGr;
    CString m_CBreite;
    CString m_CGewicht;
    CString m_CHoehe;
    CString m_CLaenge;
    CString m_CLaufZeit;
    CString m_CNormPack;
    CString m_CVke;
};

struct SArtInfIbtData
{
    char m_CVerbundartikel;
    CStringArray m_ibttypename;
    CString m_assortmenttypename;
};

struct SArtInfDiscountData
{
    vector<discountanzS> m_lDisc;
    vector<paytermS> m_lPay;
    vector<articleomgS> m_lOmg;
    BOOL m_bOMGCst;                 //Kunde hat für diesen Artikel OMG-Rabatt
    BOOL m_bOMG;                    //Artikel hat OMG-Rabatt

    SArtInfDiscountData()
    {
        m_bOMGCst = false;
        m_bOMG = false;
    }
};

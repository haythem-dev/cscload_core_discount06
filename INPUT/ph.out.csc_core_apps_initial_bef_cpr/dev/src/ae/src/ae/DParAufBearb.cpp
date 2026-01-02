// DParAufBearb.cpp : implementation file
//

#include "stdafx.h"
#include <math.h>
#include <artsel.h>
#include "DParAufBearb.h"


#define MAXIMUM_DEFWERT         1000000
#define MAXIMUM_POS_AUF         999
#define MAXIMUM_RESERVE_QTY     200
#define MAXIMUM_MINBESTELL      9999
#define MINIMUM_WERT            1000
#define MAXIMUM_SPAETER         360
#define MINIMUM_SPAETER         -999
#define MINIMUM_VB_POS          1
#define MAXIMUM_VB_POS          999
#define MAXIMUM_DURCHLAUF       120
#define MAXIMUM_TIMETOCLOSE     60
#define MAXIMUM_REQUEST         999
#define MAXIMUM_DPODAYS         5
#define MAXIMUM_DELAYEDDAYS     15
#define MAXIMUM_REVERSE         99

/////////////////////////////////////////////////////////////////////////////
// CDParAufBearb dialog


CDParAufBearb::CDParAufBearb(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDParAufBearb::IDD, pParent)
    , m_bJa18(FALSE)
    , m_bNein18(FALSE)
    , m_bJa19(FALSE)
    , m_bNein19(FALSE)
    , m_bJa20(FALSE)
    , m_bNein20(FALSE)
    , m_lMaxPosAuf(0)
    , m_lPosZu(0)
    , m_lMaxEil(0)
    , m_CNorouting(_T(""))
    , m_bJa21(FALSE)
    , m_bJa22(FALSE)
    , m_bNein21(FALSE)
    , m_bNein22(FALSE)
    , m_bJa23(FALSE)
    , m_bNein23(FALSE)
    , m_sPlusBTM(0)
    , m_lNoNatra(0)
    , m_CMinBestell(_T(""))
    , m_CPZNGeb(_T(""))
    , m_CMaxDauer(_T(""))
    , m_CMaxQty(_T(""))
    , m_CPriceRange(_T(""))
    , m_bJa24(FALSE)
    , m_bNein24(FALSE)
    , m_bJa25(FALSE)
    , m_bNein25(FALSE)
    , m_bJa26(FALSE)
    , m_bNein26(FALSE)
    , m_CTourCheck(_T(""))
    , m_CPZNFranko(_T(""))
    , m_CPZNFracht(_T(""))
    , m_CAufClose(_T(""))
    , m_CPosClose(_T(""))
    , m_bJa27(FALSE)
    , m_bNein27(FALSE)
    , m_bJa28(FALSE)
    , m_bNein28(FALSE)
    , m_bJa29(FALSE)
    , m_bNein29(FALSE)
    , m_sklclose(FALSE)
    , m_lBeifueger(0)
    , m_bJa30(FALSE)
    , m_bNein30(FALSE)
    , m_bJa31(FALSE)
    , m_bNein31(FALSE)
    , m_bJa32(FALSE)
    , m_bNein32(FALSE)
    , m_sTimeToClose(0)
    , m_sRequest(0)
    , m_sReverse(0)
    , m_sCremacancel(0)
    , m_sDPODays(0)
    , m_sDelayedDays(0)
    , m_bJa33(FALSE)
    , m_bNein33(FALSE)
    , m_bJa34(FALSE)
    , m_bNein34(FALSE)
    , m_bJa35(FALSE)
    , m_bNein35(FALSE)
    , m_bJa36(FALSE)
    , m_bNein36(FALSE)
    , m_bJa37(FALSE)
    , m_bNein37(FALSE)
    , m_bJa38(FALSE)
    , m_bNein38(FALSE)
    , m_bJa39(FALSE)
    , m_bNein39(FALSE)
    , m_bJa40(FALSE)
    , m_bNein40(FALSE)
    , m_bJa41(FALSE)
    , m_bNein41(FALSE)
    , m_bJa42(FALSE)
    , m_bNein42(FALSE)
{
    m_CAa = _T("");
    m_lAnzPos = 0;
    m_CBa = _T("");
    m_CDopKo = _T("");
    m_lEilZeit = 0;
    m_CKa = _T("");
    m_lMaxPos = 0;
    m_lNZeit = 0;
    m_lPZNBTM = 0;
    m_lPZNGr = 0;
    m_lPZNKl = 0;
    m_lPZNWf1 = 0;
    m_lPZNWf2 = 0;
    m_lSpaeter = 0;
    m_CWTag = _T("");
    m_lZHH = 0;
    m_lZMM = 0;
    m_bJa1 = FALSE;
    m_bJa2 = FALSE;
    m_bJa3 = FALSE;
    m_bJa4 = FALSE;
    m_bJa5 = FALSE;
    m_bJa6 = FALSE;
    m_bJa7 = FALSE;
    m_bNein1 = FALSE;
    m_bNein7 = FALSE;
    m_bNein6 = FALSE;
    m_bNein5 = FALSE;
    m_bNein4 = FALSE;
    m_bNein3 = FALSE;
    m_bNein2 = FALSE;
    m_lKZeit = 0;
    m_iFiliale = 0;
    m_lSepZeit = 0;
    m_iWTyp = 0;
    m_bJa8 = FALSE;
    m_bNein8 = FALSE;
    m_lTourKippZeit = 0;
    m_bJa9 = FALSE;
    m_bNein9 = FALSE;
    m_bJa10 = FALSE;
    m_bNein10 = FALSE;
    m_LDefwertkeinabschluss = 0;
    m_bJa11 = FALSE;
    m_bNein11 = FALSE;
    m_bJa12 = FALSE;
    m_bJa13 = FALSE;
    m_bNein12 = FALSE;
    m_bNein13 = FALSE;
    m_bJa14 = FALSE;
    m_bJa15 = FALSE;
    m_bNein14 = FALSE;
    m_bNein15 = FALSE;
    m_bJa16 = FALSE;
    m_bNein16 = FALSE;
    m_lZeitNoBTM = 0;
    m_lVbPos = 0;
    m_lPZNZyto = 0;
    m_bNein17 = FALSE;
    m_bJa17 = FALSE;
    m_sWake1 = 0;
    m_sWake2 = 0;
    m_dMaxSurcharge = 0.00;
}


void CDParAufBearb::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CHECK_JA17, m_CBJa17);
    DDX_Control(pDX, IDC_CHECK_NEIN17, m_CBNein17);
    DDX_Control(pDX, IDC_EDIT_PZNZYTO, m_EditPZNZyto);
    DDX_Control(pDX, IDC_EDIT_VBPOS, m_EditVbPos);
    DDX_Control(pDX, IDC_EDIT_ZEITNOBTM, m_EditZeitNoBTM);
    DDX_Control(pDX, IDC_CHECK_NEIN16, m_CBNein16);
    DDX_Control(pDX, IDC_CHECK_JA16, m_CBJa16);
    DDX_Control(pDX, IDC_CHECK_JA15, m_CBJa15);
    DDX_Control(pDX, IDC_CHECK_NEIN15, m_CBNein15);
    DDX_Control(pDX, IDC_CHECK_NEIN14, m_CBNein14);
    DDX_Control(pDX, IDC_CHECK_JA14, m_CBJa14);
    DDX_Control(pDX, IDC_CHECK_NEIN13, m_CBNein13);
    DDX_Control(pDX, IDC_CHECK_NEIN12, m_CBNein12);
    DDX_Control(pDX, IDC_CHECK_JA13, m_CBJa13);
    DDX_Control(pDX, IDC_CHECK_JA12, m_CBJa12);
    DDX_Control(pDX, IDC_CHECK_NEIN11, m_CBNein11);
    DDX_Control(pDX, IDC_CHECK_JA11, m_CBJa11);
    DDX_Control(pDX, IDC_EDIT_DEFWERTKEINABSCHLUSS, m_EditDefwertkeinabschluss);
    DDX_Control(pDX, IDC_CHECK_NEIN10, m_CBNein10);
    DDX_Control(pDX, IDC_CHECK_JA10, m_CBJa10);
    DDX_Control(pDX, IDC_CHECK_NEIN9, m_CBNein9);
    DDX_Control(pDX, IDC_CHECK_JA9, m_CBJa9);
    DDX_Control(pDX, IDC_CHECK_NEIN8, m_CBNein8);
    DDX_Control(pDX, IDC_CHECK_JA8, m_CBJa8);
    DDX_Control(pDX, IDC_EDIT_TOURKIPPZEIT, m_EditTourKippZeit);
    DDX_Control(pDX, IDC_EDIT_FILIALE, m_EditFiliale);
    DDX_Control(pDX, IDC_CHECK_NEIN3, m_CBNein3);
    DDX_Control(pDX, IDC_CHECK_NEIN7, m_CBNein7);
    DDX_Control(pDX, IDC_CHECK_NEIN6, m_CBNein6);
    DDX_Control(pDX, IDC_CHECK_NEIN5, m_CBNein5);
    DDX_Control(pDX, IDC_CHECK_NEIN4, m_CBNein4);
    DDX_Control(pDX, IDC_CHECK_NEIN2, m_CBNein2);
    DDX_Control(pDX, IDC_CHECK_NEIN1, m_CBNein1);
    DDX_Control(pDX, IDC_CHECK_JA7, m_CBJa7);
    DDX_Control(pDX, IDC_CHECK_JA6, m_CBJa6);
    DDX_Control(pDX, IDC_CHECK_JA5, m_CBJa5);
    DDX_Control(pDX, IDC_CHECK_JA4, m_CBJa4);
    DDX_Control(pDX, IDC_CHECK_JA3, m_CBJa3);
    DDX_Control(pDX, IDC_CHECK_JA2, m_CBJa2);
    DDX_Control(pDX, IDC_CHECK_JA1, m_CBJa1);
    DDX_Control(pDX, IDC_EDIT_ZMM, m_EditZMM);
    DDX_Control(pDX, IDC_EDIT_ZHH, m_EditZHH);
    DDX_Control(pDX, IDC_EDIT_WTYP, m_EditWTyp);
    DDX_Control(pDX, IDC_EDIT_WTAG, m_EditWTag);
    DDX_Control(pDX, IDC_EDIT_SPAETER, m_EditSpaeter);
    DDX_Control(pDX, IDC_EDIT_SEPZEIT, m_EditSepZeit);
    DDX_Control(pDX, IDC_EDIT_PZNWF2, m_EditPZNWf2);
    DDX_Control(pDX, IDC_EDIT_PZNWF1, m_EditPZNWf1);
    DDX_Control(pDX, IDC_EDIT_PZNKL, m_EditPZNKl);
    DDX_Control(pDX, IDC_EDIT_PZNGR, m_EditPZNGr);
    DDX_Control(pDX, IDC_EDIT_PZNBTM, m_EditPZNBTM);
    DDX_Control(pDX, IDC_EDIT_NZEIT, m_EditNZeit);
    DDX_Control(pDX, IDC_EDIT_MAXPOS, m_EditMaxPos);
    DDX_Control(pDX, IDC_EDIT_KZEIT, m_EditKZeit);
    DDX_Control(pDX, IDC_EDIT_KA, m_EditKa);
    DDX_Control(pDX, IDC_EDIT_EILZEIT, m_EditEilZeit);
    DDX_Control(pDX, IDC_EDIT_DOPKO, m_EditDopKo);
    DDX_Control(pDX, IDC_EDIT_BA, m_EditBa);
    DDX_Control(pDX, IDC_EDIT_ANZPOS, m_EditAnzPos);
    DDX_Control(pDX, IDC_EDIT_AA, m_EditAa);
    DDX_Text(pDX, IDC_EDIT_AA, m_CAa);
    DDX_Text(pDX, IDC_EDIT_ANZPOS, m_lAnzPos);
    DDX_Text(pDX, IDC_EDIT_BA, m_CBa);
    DDX_Text(pDX, IDC_EDIT_DOPKO, m_CDopKo);
    DDX_Text(pDX, IDC_EDIT_EILZEIT, m_lEilZeit);
    DDX_Text(pDX, IDC_EDIT_KA, m_CKa);
    DDX_Text(pDX, IDC_EDIT_MAXPOS, m_lMaxPos);
    DDX_Text(pDX, IDC_EDIT_NZEIT, m_lNZeit);
    DDX_Text(pDX, IDC_EDIT_PZNBTM, m_lPZNBTM);
    DDX_Text(pDX, IDC_EDIT_PZNGR, m_lPZNGr);
    DDX_Text(pDX, IDC_EDIT_PZNKL, m_lPZNKl);
    DDX_Text(pDX, IDC_EDIT_PZNWF1, m_lPZNWf1);
    DDX_Text(pDX, IDC_EDIT_PZNWF2, m_lPZNWf2);
    DDX_Text(pDX, IDC_EDIT_SPAETER, m_lSpaeter);
    DDX_Text(pDX, IDC_EDIT_WTAG, m_CWTag);
    DDX_Text(pDX, IDC_EDIT_ZHH, m_lZHH);
    DDX_Text(pDX, IDC_EDIT_ZMM, m_lZMM);
    DDX_Check(pDX, IDC_CHECK_JA1, m_bJa1);
    DDX_Check(pDX, IDC_CHECK_JA2, m_bJa2);
    DDX_Check(pDX, IDC_CHECK_JA3, m_bJa3);
    DDX_Check(pDX, IDC_CHECK_JA4, m_bJa4);
    DDX_Check(pDX, IDC_CHECK_JA5, m_bJa5);
    DDX_Check(pDX, IDC_CHECK_JA6, m_bJa6);
    DDX_Check(pDX, IDC_CHECK_JA7, m_bJa7);
    DDX_Check(pDX, IDC_CHECK_NEIN1, m_bNein1);
    DDX_Check(pDX, IDC_CHECK_NEIN7, m_bNein7);
    DDX_Check(pDX, IDC_CHECK_NEIN6, m_bNein6);
    DDX_Check(pDX, IDC_CHECK_NEIN5, m_bNein5);
    DDX_Check(pDX, IDC_CHECK_NEIN4, m_bNein4);
    DDX_Check(pDX, IDC_CHECK_NEIN3, m_bNein3);
    DDX_Check(pDX, IDC_CHECK_NEIN2, m_bNein2);
    DDX_Text(pDX, IDC_EDIT_KZEIT, m_lKZeit);
    DDX_Text(pDX, IDC_EDIT_FILIALE, m_iFiliale);
    DDX_Text(pDX, IDC_EDIT_SEPZEIT, m_lSepZeit);
    DDX_Text(pDX, IDC_EDIT_WTYP, m_iWTyp);
    DDX_Check(pDX, IDC_CHECK_JA8, m_bJa8);
    DDX_Check(pDX, IDC_CHECK_NEIN8, m_bNein8);
    DDX_Text(pDX, IDC_EDIT_TOURKIPPZEIT, m_lTourKippZeit);
    DDX_Check(pDX, IDC_CHECK_JA9, m_bJa9);
    DDX_Check(pDX, IDC_CHECK_NEIN9, m_bNein9);
    DDX_Check(pDX, IDC_CHECK_JA10, m_bJa10);
    DDX_Check(pDX, IDC_CHECK_NEIN10, m_bNein10);
    DDX_Text(pDX, IDC_EDIT_DEFWERTKEINABSCHLUSS, m_LDefwertkeinabschluss);
    DDX_Check(pDX, IDC_CHECK_JA11, m_bJa11);
    DDX_Check(pDX, IDC_CHECK_NEIN11, m_bNein11);
    DDX_Check(pDX, IDC_CHECK_JA12, m_bJa12);
    DDX_Check(pDX, IDC_CHECK_JA13, m_bJa13);
    DDX_Check(pDX, IDC_CHECK_NEIN12, m_bNein12);
    DDX_Check(pDX, IDC_CHECK_NEIN13, m_bNein13);
    DDX_Check(pDX, IDC_CHECK_JA14, m_bJa14);
    DDX_Check(pDX, IDC_CHECK_JA15, m_bJa15);
    DDX_Check(pDX, IDC_CHECK_NEIN14, m_bNein14);
    DDX_Check(pDX, IDC_CHECK_NEIN15, m_bNein15);
    DDX_Check(pDX, IDC_CHECK_JA16, m_bJa16);
    DDX_Check(pDX, IDC_CHECK_NEIN16, m_bNein16);
    DDX_Text(pDX, IDC_EDIT_ZEITNOBTM, m_lZeitNoBTM);
    DDX_Text(pDX, IDC_EDIT_VBPOS, m_lVbPos);
    DDX_Text(pDX, IDC_EDIT_PZNZYTO, m_lPZNZyto);
    DDX_Check(pDX, IDC_CHECK_NEIN17, m_bNein17);
    DDX_Check(pDX, IDC_CHECK_JA17, m_bJa17);
    DDX_Check(pDX, IDC_CHECK_JA18, m_bJa18);
    DDX_Control(pDX, IDC_CHECK_JA18, m_CBJa18);
    DDX_Control(pDX, IDC_CHECK_NEIN18, m_CBNein18);
    DDX_Check(pDX, IDC_CHECK_NEIN18, m_bNein18);
    DDX_Control(pDX, IDC_CHECK_JA19, m_CBJa19);
    DDX_Check(pDX, IDC_CHECK_JA19, m_bJa19);
    DDX_Control(pDX, IDC_CHECK_NEIN19, m_CBNein19);
    DDX_Check(pDX, IDC_CHECK_NEIN19, m_bNein19);
    DDX_Control(pDX, IDC_CHECK_JA20, m_CBJa20);
    DDX_Check(pDX, IDC_CHECK_JA20, m_bJa20);
    DDX_Control(pDX, IDC_CHECK_NEIN20, m_CBNein20);
    DDX_Check(pDX, IDC_CHECK_NEIN20, m_bNein20);
    DDX_Control(pDX, IDC_EDIT_MAXPOSAUF, m_edit_MaxPosAuf);
    DDX_Text(pDX, IDC_EDIT_MAXPOSAUF, m_lMaxPosAuf);
    DDX_Control(pDX, IDC_EDIT_POS_ZU, m_edit_PosZu);
    DDX_Text(pDX, IDC_EDIT_POS_ZU, m_lPosZu);
    DDX_Control(pDX, IDC_EDIT_MAX_EIL, m_edit_MaxEil);
    DDX_Text(pDX, IDC_EDIT_MAX_EIL, m_lMaxEil);
    DDX_Control(pDX, IDC_EDIT_NOROUTING, m_EditNorouting);
    DDX_Text(pDX, IDC_EDIT_NOROUTING, m_CNorouting);
    DDX_Control(pDX, IDC_CHECK_JA21, m_CBJa21);
    DDX_Check(pDX, IDC_CHECK_JA21, m_bJa21);
    DDX_Control(pDX, IDC_CHECK_JA22, m_CBJa22);
    DDX_Check(pDX, IDC_CHECK_JA22, m_bJa22);
    DDX_Control(pDX, IDC_CHECK_NEIN21, m_CBNein21);
    DDX_Check(pDX, IDC_CHECK_NEIN21, m_bNein21);
    DDX_Control(pDX, IDC_CHECK_NEIN22, m_CBNein22);
    DDX_Check(pDX, IDC_CHECK_NEIN22, m_bNein22);
    DDX_Control(pDX, IDC_CHECK_JA23, m_CB_Ja23);
    DDX_Check(pDX, IDC_CHECK_JA23, m_bJa23);
    DDX_Control(pDX, IDC_CHECK_NEIN23, m_CB_Nein23);
    DDX_Check(pDX, IDC_CHECK_NEIN23, m_bNein23);
    DDX_Control(pDX, IDC_EDIT_PLUS_BTM, m_EditPlusBTM);
    DDX_Text(pDX, IDC_EDIT_PLUS_BTM, m_sPlusBTM);
    DDX_Control(pDX, IDC_EDIT_NO_NATRA, m_EditNoNatra);
    DDX_Text(pDX, IDC_EDIT_NO_NATRA, m_lNoNatra);
    DDX_Control(pDX, IDC_EDIT_MIN_BESTELL, m_EditMinBestell);
    DDX_Text(pDX, IDC_EDIT_MIN_BESTELL, m_CMinBestell);
    DDX_Control(pDX, IDC_EDIT_PZN_GEB, m_EditPZNGeb);
    DDX_Text(pDX, IDC_EDIT_PZN_GEB, m_CPZNGeb);
    DDX_Control(pDX, IDC_EDIT_MAX_DAUER, m_EditMaxDauer);
    DDX_Text(pDX, IDC_EDIT_MAX_DAUER, m_CMaxDauer);
    DDX_Control(pDX, IDC_EDIT_MAX_QTY, m_EditMaxQty);
    DDX_Text(pDX, IDC_EDIT_MAX_QTY, m_CMaxQty);
    DDX_Control(pDX, IDC_EDIT_PRICE_RANGE, m_EditPriceRange);
    DDX_Text(pDX, IDC_EDIT_PRICE_RANGE, m_CPriceRange);
    DDX_Control(pDX, IDC_CHECK_JA24, m_CBJa24);
    DDX_Check(pDX, IDC_CHECK_JA24, m_bJa24);
    DDX_Control(pDX, IDC_CHECK_NEIN24, m_CBNein24);
    DDX_Check(pDX, IDC_CHECK_NEIN24, m_bNein24);
    DDX_Control(pDX, IDC_CHECK_JA25, m_CBJa25);
    DDX_Check(pDX, IDC_CHECK_JA25, m_bJa25);
    DDX_Control(pDX, IDC_CHECK_NEIN25, m_CBNein25);
    DDX_Check(pDX, IDC_CHECK_NEIN25, m_bNein25);
    DDX_Control(pDX, IDC_CHECK_JA26, m_CBJa26);
    DDX_Check(pDX, IDC_CHECK_JA26, m_bJa26);
    DDX_Control(pDX, IDC_CHECK_NEIN26, m_CBNein26);
    DDX_Check(pDX, IDC_CHECK_NEIN26, m_bNein26);
    DDX_Control(pDX, IDC_EDIT_TOUR_CHECK, m_EditTourCheck);
    DDX_Text(pDX, IDC_EDIT_TOUR_CHECK, m_CTourCheck);
    DDX_Control(pDX, IDC_EDIT_PZN_FRANKO, m_EditPZNFranko);
    DDX_Text(pDX, IDC_EDIT_PZN_FRANKO, m_CPZNFranko);
    DDX_Control(pDX, IDC_EDIT_PZN_FRACHT, m_EditPZNFracht);
    DDX_Text(pDX, IDC_EDIT_PZN_FRACHT, m_CPZNFracht);
    DDX_Control(pDX, IDC_EDIT_AUF_CLOSE, m_EditAufClose);
    DDX_Text(pDX, IDC_EDIT_AUF_CLOSE, m_CAufClose);
    DDX_Control(pDX, IDC_EDIT_POS_CLOSE, m_EditPosClose);
    DDX_Text(pDX, IDC_EDIT_POS_CLOSE, m_CPosClose);
    DDX_Control(pDX, IDC_CHECK_JA27, m_CBJa27);
    DDX_Check(pDX, IDC_CHECK_JA27, m_bJa27);
    DDX_Control(pDX, IDC_CHECK_NEIN27, m_CBNein27);
    DDX_Check(pDX, IDC_CHECK_NEIN27, m_bNein27);
    DDX_Control(pDX, IDC_CHECK_JA28, m_CBJa28);
    DDX_Check(pDX, IDC_CHECK_JA28, m_bJa28);
    DDX_Control(pDX, IDC_CHECK_NEIN28, m_CBNein28);
    DDX_Check(pDX, IDC_CHECK_NEIN28, m_bNein28);
    DDX_Control(pDX, IDC_CHECK_JA29, m_CBJa29);
    DDX_Check(pDX, IDC_CHECK_JA29, m_bJa29);
    DDX_Control(pDX, IDC_CHECK_NEIN29, m_CBNein29);
    DDX_Check(pDX, IDC_CHECK_NEIN29, m_bNein29);
    DDX_Control(pDX, IDC_EDIT_WAKE1, m_EditWake1);
    DDX_Control(pDX, IDC_EDIT_WAKE2, m_EditWake2);
    DDX_Text(pDX, IDC_EDIT_WAKE1, m_sWake1);
    DDX_Text(pDX, IDC_EDIT_WAKE2, m_sWake2);
    DDX_Control(pDX, IDC_EDIT_MAX_SURCHARGE, m_EditMaxSurcharge);
    DDX_Text(pDX, IDC_EDIT_MAX_SURCHARGE, m_dMaxSurcharge);
    DDX_Control(pDX, IDC_EDIT_BEIFUEGER, m_editBeifueger);
    DDX_Text(pDX, IDC_EDIT_BEIFUEGER, m_lBeifueger);
    DDX_Control(pDX, IDC_CHECK_JA30, m_CBJa30);
    DDX_Check(pDX, IDC_CHECK_JA30, m_bJa30);
    DDX_Control(pDX, IDC_CHECK_NEIN30, m_CBNein30);
    DDX_Check(pDX, IDC_CHECK_NEIN30, m_bNein30);
    DDX_Control(pDX, IDC_CHECK_JA31, m_CBJa31);
    DDX_Check(pDX, IDC_CHECK_JA31, m_bJa31);
    DDX_Control(pDX, IDC_CHECK_NEIN31, m_CBNein31);
    DDX_Check(pDX, IDC_CHECK_NEIN31, m_bNein31);
    DDX_Check(pDX, IDC_CHECK_JA32, m_bJa32);
    DDX_Check(pDX, IDC_CHECK_NEIN32, m_bNein32);
    DDX_Control(pDX, IDC_CHECK_JA32, m_CBJa32);
    DDX_Control(pDX, IDC_CHECK_NEIN32, m_CBNein32);
    DDX_Control(pDX, IDC_EDIT_TIMETOCLOSE, m_editTimeToClose);
    DDX_Text(pDX, IDC_EDIT_TIMETOCLOSE, m_sTimeToClose);
    DDX_Control(pDX, IDC_EDIT_REQUEST, m_editRequest);
    DDX_Text(pDX, IDC_EDIT_REQUEST, m_sRequest);
    DDX_Control(pDX, IDC_EDIT_DPODAYS, m_editDPODays);
    DDX_Text(pDX, IDC_EDIT_DPODAYS, m_sDPODays);
    DDX_Control(pDX, IDC_EDIT_DELAYEDDAYS, m_editDelayedDays);
    DDX_Text(pDX, IDC_EDIT_DELAYEDDAYS, m_sDelayedDays);
    DDX_Control(pDX, IDC_CHECK_JA33, m_CB_Ja33);
    DDX_Check(pDX, IDC_CHECK_JA33, m_bJa33);
    DDX_Control(pDX, IDC_CHECK_NEIN33, m_CBNein33);
    DDX_Check(pDX, IDC_CHECK_NEIN33, m_bNein33);
    DDX_Control(pDX, IDC_CHECK_JA34, m_CB_Ja34);
    DDX_Check(pDX, IDC_CHECK_JA34, m_bJa34);
    DDX_Control(pDX, IDC_CHECK_NEIN34, m_CBNein34);
    DDX_Check(pDX, IDC_CHECK_NEIN34, m_bNein34);
    DDX_Control(pDX, IDC_CHECK_JA35, m_CB_Ja35);
    DDX_Check(pDX, IDC_CHECK_JA35, m_bJa35);
    DDX_Control(pDX, IDC_CHECK_NEIN35, m_CBNein35);
    DDX_Check(pDX, IDC_CHECK_NEIN35, m_bNein35);
    DDX_Control(pDX, IDC_CHECK_JA36, m_CB_Ja36);
    DDX_Check(pDX, IDC_CHECK_JA36, m_bJa36);
    DDX_Control(pDX, IDC_CHECK_NEIN36, m_CBNein36);
    DDX_Check(pDX, IDC_CHECK_NEIN36, m_bNein36);
    DDX_Control(pDX, IDC_CHECK_JA37, m_CB_Ja37);
    DDX_Check(pDX, IDC_CHECK_JA37, m_bJa37);
    DDX_Control(pDX, IDC_CHECK_NEIN37, m_CBNein37);
    DDX_Check(pDX, IDC_CHECK_NEIN37, m_bNein37);
    DDX_Control(pDX, IDC_CHECK_JA38, m_CB_Ja38);
    DDX_Check(pDX, IDC_CHECK_JA38, m_bJa38);
    DDX_Control(pDX, IDC_CHECK_NEIN38, m_CBNein38);
    DDX_Check(pDX, IDC_CHECK_NEIN38, m_bNein38);
    DDX_Control(pDX, IDC_CHECK_JA39, m_CB_Ja39);
    DDX_Check(pDX, IDC_CHECK_JA39, m_bJa39);
    DDX_Control(pDX, IDC_CHECK_NEIN39, m_CBNein39);
    DDX_Check(pDX, IDC_CHECK_NEIN39, m_bNein39);
    DDX_Control(pDX, IDC_CHECK_JA40, m_CB_Ja40);
    DDX_Check(pDX, IDC_CHECK_JA40, m_bJa40);
    DDX_Control(pDX, IDC_CHECK_NEIN40, m_CBNein40);
    DDX_Check(pDX, IDC_CHECK_NEIN40, m_bNein40);
    DDX_Control(pDX, IDC_CHECK_JA41, m_CB_Ja41);
    DDX_Check(pDX, IDC_CHECK_JA41, m_bJa41);
    DDX_Control(pDX, IDC_CHECK_NEIN41, m_CBNein41);
    DDX_Check(pDX, IDC_CHECK_NEIN41, m_bNein41);
    DDX_Control(pDX, IDC_CHECK_JA42, m_CB_Ja42);
    DDX_Check(pDX, IDC_CHECK_JA42, m_bJa42);
    DDX_Control(pDX, IDC_CHECK_NEIN42, m_CBNein42);
    DDX_Check(pDX, IDC_CHECK_NEIN42, m_bNein42);
    DDX_Control(pDX, IDC_EDIT_REVERSE, m_editReverse);
    DDX_Text(pDX, IDC_EDIT_REVERSE, m_sReverse);
    DDX_Control(pDX, IDC_EDIT_CANCELCREMA, m_editCremacancel);
    DDX_Text(pDX, IDC_EDIT_CANCELCREMA, m_sCremacancel);
}


BEGIN_MESSAGE_MAP(CDParAufBearb, CDialogMultiLang)
    ON_BN_CLICKED(IDC_CHECK_JA1, OnCheckJa1)
    ON_BN_CLICKED(IDC_CHECK_JA2, OnCheckJa2)
    ON_BN_CLICKED(IDC_CHECK_JA3, OnCheckJa3)
    ON_BN_CLICKED(IDC_CHECK_JA4, OnCheckJa4)
    ON_BN_CLICKED(IDC_CHECK_JA5, OnCheckJa5)
    ON_BN_CLICKED(IDC_CHECK_JA6, OnCheckJa6)
    ON_BN_CLICKED(IDC_CHECK_JA7, OnCheckJa7)
    ON_BN_CLICKED(IDC_CHECK_NEIN1, OnCheckNein1)
    ON_BN_CLICKED(IDC_CHECK_NEIN2, OnCheckNein2)
    ON_BN_CLICKED(IDC_CHECK_NEIN3, OnCheckNein3)
    ON_BN_CLICKED(IDC_CHECK_NEIN4, OnCheckNein4)
    ON_BN_CLICKED(IDC_CHECK_NEIN5, OnCheckNein5)
    ON_BN_CLICKED(IDC_CHECK_NEIN6, OnCheckNein6)
    ON_BN_CLICKED(IDC_CHECK_NEIN7, OnCheckNein7)
    ON_EN_CHANGE(IDC_EDIT_AA, OnChangeEditAa)
    ON_EN_CHANGE(IDC_EDIT_ANZPOS, OnChangeEditAnzpos)
    ON_EN_CHANGE(IDC_EDIT_BA, OnChangeEditBa)
    ON_EN_CHANGE(IDC_EDIT_DOPKO, OnChangeEditDopko)
    ON_EN_CHANGE(IDC_EDIT_EILZEIT, OnChangeEditEilzeit)
    ON_EN_CHANGE(IDC_EDIT_KA, OnChangeEditKa)
    ON_EN_CHANGE(IDC_EDIT_KZEIT, OnChangeEditKzeit)
    ON_EN_CHANGE(IDC_EDIT_MAXPOS, OnChangeEditMaxpos)
    ON_EN_CHANGE(IDC_EDIT_NZEIT, OnChangeEditNzeit)
    ON_EN_CHANGE(IDC_EDIT_PZNBTM, OnChangeEditPznbtm)
    ON_EN_CHANGE(IDC_EDIT_PZNGR, OnChangeEditPzngr)
    ON_EN_CHANGE(IDC_EDIT_PZNKL, OnChangeEditPznkl)
    ON_EN_CHANGE(IDC_EDIT_PZNWF1, OnChangeEditPznwf1)
    ON_EN_CHANGE(IDC_EDIT_PZNWF2, OnChangeEditPznwf2)
    ON_EN_CHANGE(IDC_EDIT_SPAETER, OnChangeEditSpaeter)
    ON_EN_CHANGE(IDC_EDIT_WTAG, OnChangeEditWtag)
    ON_EN_CHANGE(IDC_EDIT_ZHH, OnChangeEditZhh)
    ON_EN_CHANGE(IDC_EDIT_ZMM, OnChangeEditZmm)
    ON_EN_CHANGE(IDC_EDIT_WTYP, OnChangeEditWtyp)
    ON_EN_CHANGE(IDC_EDIT_SEPZEIT, OnChangeEditSepzeit)
    ON_BN_CLICKED(IDC_CHECK_NEIN8, OnCheckNein8)
    ON_BN_CLICKED(IDC_CHECK_JA8, OnCheckJa8)
    ON_EN_CHANGE(IDC_EDIT_TOURKIPPZEIT, OnChangeEditTourkippzeit)
    ON_BN_CLICKED(IDC_CHECK_JA10, OnCheckJa10)
    ON_BN_CLICKED(IDC_CHECK_JA9, OnCheckJa9)
    ON_BN_CLICKED(IDC_CHECK_NEIN10, OnCheckNein10)
    ON_BN_CLICKED(IDC_CHECK_NEIN9, OnCheckNein9)
    ON_EN_CHANGE(IDC_EDIT_DEFWERTKEINABSCHLUSS, OnChangeEditDefwertkeinabschluss)
    ON_BN_CLICKED(IDC_CHECK_JA11, OnCheckJa11)
    ON_BN_CLICKED(IDC_CHECK_NEIN11, OnCheckNein11)
    ON_BN_CLICKED(IDC_CHECK_JA12, OnCheckJa12)
    ON_BN_CLICKED(IDC_CHECK_JA13, OnCheckJa13)
    ON_BN_CLICKED(IDC_CHECK_NEIN12, OnCheckNein12)
    ON_BN_CLICKED(IDC_CHECK_NEIN13, OnCheckNein13)
    ON_BN_CLICKED(IDC_CHECK_JA14, OnCheckJa14)
    ON_BN_CLICKED(IDC_CHECK_JA15, OnCheckJa15)
    ON_BN_CLICKED(IDC_CHECK_NEIN14, OnCheckNein14)
    ON_BN_CLICKED(IDC_CHECK_NEIN15, OnCheckNein15)
    ON_BN_CLICKED(IDC_CHECK_JA16, OnCheckJa16)
    ON_BN_CLICKED(IDC_CHECK_NEIN16, OnCheckNein16)
    ON_EN_CHANGE(IDC_EDIT_ZEITNOBTM, OnChangeEditZeitnobtm)
    ON_EN_CHANGE(IDC_EDIT_VBPOS, OnChangeEditVbpos)
    ON_EN_CHANGE(IDC_EDIT_PZNZYTO, OnChangeEditPznzyto)
    ON_BN_CLICKED(IDC_CHECK_JA17, OnCheckJa17)
    ON_BN_CLICKED(IDC_CHECK_NEIN17, OnCheckNein17)
    ON_BN_CLICKED(IDC_CHECK_JA18, OnBnClickedCheckJa18)
    ON_BN_CLICKED(IDC_CHECK_NEIN18, OnBnClickedCheckNein18)
    ON_BN_CLICKED(IDC_CHECK_JA19, OnBnClickedCheckJa19)
    ON_BN_CLICKED(IDC_CHECK_NEIN19, OnBnClickedCheckNein19)
    ON_BN_CLICKED(IDC_CHECK_JA20, OnBnClickedCheckJa20)
    ON_BN_CLICKED(IDC_CHECK_NEIN20, OnBnClickedCheckNein20)
    ON_EN_CHANGE(IDC_EDIT_MAXPOSAUF, OnEnChangeEditMaxposauf)
    ON_EN_CHANGE(IDC_EDIT_POS_ZU, OnEnChangeEditPosZu)
    ON_EN_CHANGE(IDC_EDIT_MAX_EIL, OnEnChangeEditMaxEil)
    ON_EN_CHANGE(IDC_EDIT_NOROUTING, OnEnChangeEditNorouting)
    ON_BN_CLICKED(IDC_CHECK_JA21, OnBnClickedCheckJa21)
    ON_BN_CLICKED(IDC_CHECK_NEIN21, OnBnClickedCheckNein21)
    ON_BN_CLICKED(IDC_CHECK_JA22, OnBnClickedCheckJa22)
    ON_BN_CLICKED(IDC_CHECK_NEIN22, OnBnClickedCheckNein22)
    ON_BN_CLICKED(IDC_CHECK_JA23, OnBnClickedCheckJa23)
    ON_BN_CLICKED(IDC_CHECK_NEIN23, OnBnClickedCheckNein23)
    ON_EN_CHANGE(IDC_EDIT_PLUS_BTM, OnEnChangeEditPlusBtm)
    ON_EN_CHANGE(IDC_EDIT_MIN_BESTELL, OnEnChangeEditMinBestell)
    ON_EN_CHANGE(IDC_EDIT_PZN_GEB, OnEnChangeEditPznGeb)
    ON_EN_CHANGE(IDC_EDIT_MAX_DAUER, OnEnChangeEditMaxDauer)
    ON_EN_CHANGE(IDC_EDIT_MAX_QTY, OnEnChangeEditMaxQty)
    ON_EN_CHANGE(IDC_EDIT_PRICE_RANGE, OnEnChangeEditPriceRange)
    ON_BN_CLICKED(IDC_CHECK_JA24, OnBnClickedCheckJa24)
    ON_BN_CLICKED(IDC_CHECK_NEIN24, OnBnClickedCheckNein24)
    ON_BN_CLICKED(IDC_CHECK_JA25, OnBnClickedCheckJa25)
    ON_BN_CLICKED(IDC_CHECK_NEIN25, OnBnClickedCheckNein25)
    ON_BN_CLICKED(IDC_CHECK_JA26, OnBnClickedCheckJa26)
    ON_BN_CLICKED(IDC_CHECK_NEIN26, OnBnClickedCheckNein26)
    ON_EN_CHANGE(IDC_EDIT_TOUR_CHECK, OnEnChangeEditTourCheck)
    ON_EN_CHANGE(IDC_EDIT_PZN_FRANKO, OnEnChangeEditPznFranko)
    ON_EN_CHANGE(IDC_EDIT_PZN_FRACHT, OnEnChangeEditPznFracht)
    ON_EN_CHANGE(IDC_EDIT_AUF_CLOSE, OnEnChangeEditAufClose)
    ON_EN_CHANGE(IDC_EDIT_POS_CLOSE, OnEnChangeEditPosClose)
    ON_BN_CLICKED(IDC_CHECK_JA27, OnBnClickedCheckJa27)
    ON_BN_CLICKED(IDC_CHECK_NEIN27, OnBnClickedCheckNein27)
    ON_BN_CLICKED(IDC_CHECK_JA28, OnBnClickedCheckJa28)
    ON_BN_CLICKED(IDC_CHECK_NEIN28, OnBnClickedCheckNein28)
    ON_BN_CLICKED(IDC_CHECK_JA29, OnBnClickedCheckJa29)
    ON_BN_CLICKED(IDC_CHECK_NEIN29, OnBnClickedCheckNein29)
    ON_EN_CHANGE(IDC_EDIT_WAKE1, OnEnChangeEditWake1)
    ON_EN_CHANGE(IDC_EDIT_WAKE2, OnEnChangeEditWake2)
    ON_BN_CLICKED(IDC_CHECK_JA30, OnBnClickedCheckJa30)
    ON_BN_CLICKED(IDC_CHECK_NEIN30, OnBnClickedCheckNein30)
    ON_EN_CHANGE(IDC_EDIT_BEIFUEGER, OnEnChangeEditBeifueger)
    ON_BN_CLICKED(IDC_CHECK_JA31, OnBnClickedCheckJa31)
    ON_BN_CLICKED(IDC_CHECK_NEIN31, OnBnClickedCheckNein31)
    ON_BN_CLICKED(IDC_CHECK_JA32, OnBnClickedCheckJa32)
    ON_BN_CLICKED(IDC_CHECK_NEIN32, OnBnClickedCheckNein32)
    ON_EN_CHANGE(IDC_EDIT_TIMETOCLOSE, OnEnChangeEditTimetoclose)
    ON_EN_CHANGE(IDC_EDIT_REQUEST, OnEnChangeEditRequest)
    ON_EN_CHANGE(IDC_EDIT_DPODAYS, OnEnChangeEditDpodays)
    ON_EN_CHANGE(IDC_EDIT_DELAYEDDAYS, OnEnChangeEditDelayeddays)
    ON_BN_CLICKED(IDC_CHECK_JA33, OnBnClickedCheckJa33)
    ON_BN_CLICKED(IDC_CHECK_NEIN33, OnBnClickedCheckNein33)
    ON_BN_CLICKED(IDC_CHECK_JA34, OnBnClickedCheckJa34)
    ON_BN_CLICKED(IDC_CHECK_NEIN34, OnBnClickedCheckNein34)
    ON_BN_CLICKED(IDC_CHECK_JA35, OnBnClickedCheckJa35)
    ON_BN_CLICKED(IDC_CHECK_NEIN35, OnBnClickedCheckNein35)
    ON_BN_CLICKED(IDC_CHECK_JA36, OnBnClickedCheckJa36)
    ON_BN_CLICKED(IDC_CHECK_NEIN36, OnBnClickedCheckNein36)
    ON_BN_CLICKED(IDC_CHECK_JA37, OnBnClickedCheckJa37)
    ON_BN_CLICKED(IDC_CHECK_NEIN37, OnBnClickedCheckNein37)
    ON_BN_CLICKED(IDC_CHECK_JA38, OnBnClickedCheckJa38)
    ON_BN_CLICKED(IDC_CHECK_NEIN38, OnBnClickedCheckNein38)
    ON_BN_CLICKED(IDC_CHECK_JA39, OnBnClickedCheckJa39)
    ON_BN_CLICKED(IDC_CHECK_NEIN39, OnBnClickedCheckNein39)
    ON_BN_CLICKED(IDC_CHECK_JA40, OnBnClickedCheckJa40)
    ON_BN_CLICKED(IDC_CHECK_NEIN40, OnBnClickedCheckNein40)
    ON_BN_CLICKED(IDC_CHECK_JA41, OnBnClickedCheckJa41)
    ON_BN_CLICKED(IDC_CHECK_NEIN41, OnBnClickedCheckNein41)
    ON_BN_CLICKED(IDC_CHECK_JA42, OnBnClickedCheckJa42)
    ON_BN_CLICKED(IDC_CHECK_NEIN42, OnBnClickedCheckNein42)
    ON_EN_CHANGE(IDC_EDIT_REVERSE, OnEnChangeEditReverse)
    ON_EN_CHANGE(IDC_EDIT_CANCELCREMA, OnEnChangeEditCremacancel)
    ON_WM_CTLCOLOR()
    END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDParAufBearb message handlers

BOOL CDParAufBearb::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    GetDlgItem(IDC_CHECK_JA4)->EnableWindow(FALSE);
    GetDlgItem(IDC_CHECK_NEIN4)->EnableWindow(FALSE);
    if (GetAeUser().IsEnableWerbeFach())
    {
        GetDlgItem(IDC_CHECK_JA4)->EnableWindow(TRUE);
        GetDlgItem(IDC_CHECK_NEIN4)->EnableWindow(TRUE);
    }

    if (AeGetApp()->IsCH() || AeGetApp()->IsAT())
    {
        GetDlgItem(IDC_EDIT_BEIFUEGER)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_BEIFUEGER)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_BEIFUEGER)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_BEIFUEGER)->ShowWindow(SW_SHOW);
    }
    if (AeGetApp()->IsFR() || AeGetApp()->IsPF())
    {
        GetDlgItem(IDC_EDIT_DELAYEDDAYS)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_DELAYEDDAYS)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_DELAYEDDAYS)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_DELAYEDDAYS)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_REVERSE)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_REVERSE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_REVERSE)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_REVERSE)->ShowWindow(SW_SHOW);
    }
    if (AeGetApp()->IsMK())
    {
        if (!GetAeUser().IsChangeDPODays())
        {
            GetDlgItem(IDC_EDIT_DPODAYS)->EnableWindow(FALSE);
        }
        else
        {
            GetDlgItem(IDC_EDIT_DPODAYS)->EnableWindow(TRUE);
        }
        GetDlgItem(IDC_EDIT_DPODAYS)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_DPODAYS)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_DPODAYS)->ShowWindow(SW_SHOW);
    }
    m_paraufbearb.s.FILIALNR = m_FilialNr;
    BeginWaitCursor();
    m_paraufbearb.Server(AafilSelaufbearb);
    AllgEntfSpaces(m_paraufbearb.s.KDAUFTRAGART);
    AllgEntfSpaces(m_paraufbearb.s.BUCHART);
    AllgEntfSpaces(m_paraufbearb.s.KOART);
    AllgEntfSpaces(m_paraufbearb.s.SSAMMELKOMMI);
    AllgEntfSpaces(m_paraufbearb.s.SVORFAKTURA);
    AllgEntfSpaces(m_paraufbearb.s.SBTMSCHEIN);
    AllgEntfSpaces(m_paraufbearb.s.SWERBUNG);
    AllgEntfSpaces(m_paraufbearb.s.TOURWOCHENTAG);
    AllgEntfSpaces(m_paraufbearb.s.BAHNHOFDOPPELKONTR);
    AllgEntfSpaces(m_paraufbearb.s.SERWEITERTETOURANZ);
    AllgEntfSpaces(m_paraufbearb.s.SAUFTRAGZUSAMMEN);
    AllgEntfSpaces(m_paraufbearb.s.SSEPWANNENEILBOTE);
    m_iFiliale = m_paraufbearb.s.FILIALNR;
    m_LDefwertkeinabschluss = m_paraufbearb.s.DEFWERTKEINABSCHL;
    m_CAa = m_paraufbearb.s.KDAUFTRAGART;
    m_CBa = m_paraufbearb.s.BUCHART;
    m_CKa = m_paraufbearb.s.KOART;
    m_lNZeit = m_paraufbearb.s.DURCHLAUFNORMAL;
    m_lEilZeit = m_paraufbearb.s.DURCHLAUFEILBOTE;
    m_lKZeit = m_paraufbearb.s.KARENZTOURSCHEIN;
    m_lPZNKl = m_paraufbearb.s.PZNKUEHLBOX1;
    m_lPZNGr = m_paraufbearb.s.PZNKUEHLBOX2;
    m_lPZNBTM = m_paraufbearb.s.PZNBTMSCHEIN;
    m_lPZNWf1 = m_paraufbearb.s.PZNWERBEFACH;
    m_lPZNWf2 = m_paraufbearb.s.PZNWERBEFACH2;
    m_lPZNKl_old = m_paraufbearb.s.PZNKUEHLBOX1;
    m_lPZNGr_old = m_paraufbearb.s.PZNKUEHLBOX2;
    m_lPZNBTM_old = m_paraufbearb.s.PZNBTMSCHEIN;
    m_lPZNWf1_old = m_paraufbearb.s.PZNWERBEFACH;
    m_lPZNWf2_old = m_paraufbearb.s.PZNWERBEFACH2;
    m_lAnzPos = m_paraufbearb.s.ANZARTALPHAWSORT;
    m_lMaxPos = m_paraufbearb.s.MAXPOSMENGE;
    m_CWTag = m_paraufbearb.s.TOURWOCHENTAG;
    m_lSpaeter = m_paraufbearb.s.TOURVERSPAETUNG;
    m_CDopKo = m_paraufbearb.s.BAHNHOFDOPPELKONTR;
    m_lZMM = m_paraufbearb.s.AUFTRAGZUSAMMENMMM;
    m_lZHH = m_paraufbearb.s.AUFTRAGZUSAMMENHHH;
    m_iWTyp = m_paraufbearb.s.SEPWANNENTYP;
    m_lSepZeit = m_paraufbearb.s.SEPWANNENRESTZEIT;
    m_lTourKippZeit = m_paraufbearb.s.TOURENKIPPZEIT;
    m_lZeitNoBTM = m_paraufbearb.s.TIME_NO_BTM;
    m_lVbPos = m_paraufbearb.s.MAXPOSVERBUND;
    m_lPZNZyto = m_paraufbearb.s.PZNZYTOSTATIKA;
    m_lPZNZyto_old = m_paraufbearb.s.PZNZYTOSTATIKA;
    m_lMaxPosAuf = m_paraufbearb.s.MAXPOSAUFTRAG;
    m_lPosZu = m_paraufbearb.s.ANZPOSZU;
    m_lMaxEil = m_paraufbearb.s.MAXPOSEIL;
    m_CNorouting.Format("%d", m_paraufbearb.s.NOROUTINGMM);
    m_sPlusBTM = (short)m_paraufbearb.s.PLUSZEITBTM;
    m_lNoNatra = m_paraufbearb.s.ETARTNONATRA;
    m_CPZNGeb.Format("%d", m_paraufbearb.s.PZNADDONCHARGE);
    m_lPZNGeb_old = m_paraufbearb.s.PZNADDONCHARGE;
    m_CMinBestell.Format("%d", m_paraufbearb.s.MINDESTBESTELLWERT);
    m_CMaxDauer.Format("%d", m_paraufbearb.s.RESERVEPERIOD);
    m_CMaxQty.Format("%d", m_paraufbearb.s.RESERVEMAXQTY);
    m_CPriceRange.Format("%2.2f", m_paraufbearb.s.RANGEPRICEPCT);
    AllgCStrCharToChar(m_CPriceRange, '.', ',');
    m_CTourCheck.Format("%d", m_paraufbearb.s.TOURCHECKTIME);
    m_CPZNFranko.Format("%d", m_paraufbearb.s.PZNFRANKO);
    m_lPZNFranko_old = m_paraufbearb.s.PZNFRANKO;
    m_CPZNFracht.Format("%d", m_paraufbearb.s.PZNFREIGHTAGE);
    m_lPZNFracht_old = m_paraufbearb.s.PZNFREIGHTAGE;
    m_CAufClose.Format("%d", m_paraufbearb.s.ANZAUFCLOSE);
    m_CPosClose.Format("%d", m_paraufbearb.s.ANZPOSCLOSE);
    m_sWake1 = m_paraufbearb.s.WAKETIME1;
    m_sWake2 = m_paraufbearb.s.WAKETIME2;
    m_dMaxSurcharge = m_paraufbearb.s.MAXSURCHARGE;
    m_lBeifueger = m_paraufbearb.s.ENCLOSERTILTTIME;
    m_sTimeToClose = m_paraufbearb.s.CHECKTIMETOCLOSE;
    m_sRequest = m_paraufbearb.s.MAXQTYREQUEST;
    m_sDPODays = m_paraufbearb.s.MAXDPODAYS;
    m_sDelayedDays = m_paraufbearb.s.DELAYEDDAYS;
    m_sReverse = m_paraufbearb.s.REVERSESUBSTITUTIONDAYS;
    m_sCremacancel = m_paraufbearb.s.TIMECANCELCREMAORDER;

    if (m_paraufbearb.s.SSAMMELKOMMI[0] != '1') m_bNein1 = TRUE;
    else m_bJa1 = TRUE;
    if (m_paraufbearb.s.SVORFAKTURA[0] != '1') m_bNein2 = TRUE;
    else m_bJa2 = TRUE;
    if (m_paraufbearb.s.SBTMSCHEIN[0] != '1') m_bNein3 = TRUE;
    else m_bJa3 = TRUE;
    if (m_paraufbearb.s.SWERBUNG[0] != '1') m_bNein4 = TRUE;
    else m_bJa4 = TRUE;
    if (m_paraufbearb.s.SERWEITERTETOURANZ[0] != '1') m_bNein5 = TRUE;
    else m_bJa5 = TRUE;
    if (m_paraufbearb.s.SAUFTRAGZUSAMMEN[0] != '1') m_bNein6 = TRUE;
    else m_bJa6 = TRUE;
    if (m_paraufbearb.s.SSEPWANNENEILBOTE[0] != '1') m_bNein7 = TRUE;
    else m_bJa7 = TRUE;
    if (m_paraufbearb.s.SKDAUFTRAGSPLIT[0] != '1') m_bNein8 = TRUE;
    else m_bJa8 = TRUE;
    if (m_paraufbearb.s.AUTOMNACHLIEF[0] != '1') m_bNein9 = TRUE;
    else m_bJa9 = TRUE;
    if (m_paraufbearb.s.DAFUEENTSDIORNL[0] != '1') m_bNein10 = TRUE;
    else m_bJa10 = TRUE;
    if (m_paraufbearb.s.SKUEHLU8GRAD[0] != '1') m_bNein11 = TRUE;
    else m_bJa11 = TRUE;
    if (m_paraufbearb.s.SRRSA02[0] != '1') m_bNein12 = TRUE;
    else m_bJa12 = TRUE;
    if (m_paraufbearb.s.STRENNBEI10NER[0] != '1') m_bNein13 = TRUE;
    else m_bJa13 = TRUE;
    if (m_paraufbearb.s.STEXT99NAK[0] != '1') m_bNein14 = TRUE;
    else m_bJa14 = TRUE;
    if (m_paraufbearb.s.SBEARB06[0] != '1') m_bNein15 = TRUE;
    else m_bJa15 = TRUE;
    if (m_paraufbearb.s.BTM_EXTRA[0] != '1') m_bNein16 = TRUE;
    else m_bJa16 = TRUE;
    if (m_paraufbearb.s.DEFEKTDISPO[0] != '1') m_bNein17 = TRUE;
    else m_bJa17 = TRUE;
    if (m_paraufbearb.s.SVORAUSBEZG[0] != '1') m_bNein18 = TRUE;
    else m_bJa18 = TRUE;
    if (m_paraufbearb.s.SBTMKOMMI[0] != '1') m_bNein19 = TRUE;
    else m_bJa19 = TRUE;
    if (m_paraufbearb.s.SNOTOAK[0] != '1') m_bNein20 = TRUE;
    else m_bJa20 = TRUE;
    if (m_paraufbearb.s.SNEWDISCOUNT[0] != '1') m_bNein21 = TRUE;
    else m_bJa21 = TRUE;
    if (m_paraufbearb.s.SVERUNDEN[0] != '1') m_bNein22 = TRUE;
    else m_bJa22 = TRUE;
    if (m_paraufbearb.s.SBATCHTEILMENGE[0] != '1') m_bNein23 = TRUE;
    else m_bJa23 = TRUE;
    if (m_paraufbearb.s.SNARCTRANS[0] != '1') m_bNein24 = TRUE;
    else m_bJa24 = TRUE;
    if (m_paraufbearb.s.SPOSSPLIT[0] != '1') m_bNein25 = TRUE;
    else m_bJa25 = TRUE;
    if (m_paraufbearb.s.SDAYNIGHT[0] != '1') m_bNein26 = TRUE;
    else m_bJa26 = TRUE;
    if (m_paraufbearb.s.SNOCHANGEVAL[0] != '1') m_bNein27 = TRUE;
    else m_bJa27 = TRUE;
    if (m_paraufbearb.s.SKUMPOS[0] != '1') m_bNein28 = TRUE;
    else m_bJa28 = TRUE;
    if (m_paraufbearb.s.SANZPRINTCODE[0] != '1') m_bNein29 = TRUE;
    else m_bJa29 = TRUE;
    if (m_paraufbearb.s.SDEFORDERDF[0] != '1') m_bNein30 = TRUE;
    else m_bJa30 = TRUE;
    if (m_paraufbearb.s.SIBTCSTORG[0] != '1') m_bNein31 = TRUE;
    else m_bJa31 = TRUE;
    if (m_paraufbearb.s.SCREMA[0] != '1') m_bNein32 = TRUE;
    else m_bJa32 = TRUE;
    if (m_paraufbearb.s.SDAYNIGHTMERGE != 1) m_bNein33 = TRUE;
    else m_bJa33 = TRUE;
    if (m_paraufbearb.s.SCLOSEIBTATONCE != 1) m_bNein34 = TRUE;
    else m_bJa34 = TRUE;
    if (m_paraufbearb.s.SWNEWCALLBACK != 1) m_bNein35 = TRUE;
    else m_bJa35 = TRUE;
    if (m_paraufbearb.s.SSTOPCREMA != 1) m_bNein36 = TRUE;
    else m_bJa36 = TRUE;
    if (m_paraufbearb.s.SCOOL20 != 1) m_bNein37 = TRUE;
    else m_bJa37 = TRUE;
    if (m_paraufbearb.s.SNODISPOCLOSED != 1) m_bNein38 = TRUE;
    else m_bJa38 = TRUE;
    if (m_paraufbearb.s.IBTNORMALTOURACTIVE != 1) m_bNein39 = TRUE;
    else m_bJa39 = TRUE;
    if (m_paraufbearb.s.SCLOSERESTDELIVERYATONCE != 1) m_bNein40 = TRUE;
    else m_bJa40 = TRUE;
    if (m_paraufbearb.s.SCLOSEDISPOATONCE != 1) m_bNein41 = TRUE;
    else m_bJa41 = TRUE;
    if (m_paraufbearb.s.USELATESTIBTTOUR != 1) m_bNein42 = TRUE;
    else m_bJa42 = TRUE;
    // nicht im update, aber merken
    if (m_paraufbearb.s.SKLCLOSE[0] != '1') m_sklclose = FALSE;
    else m_sklclose = TRUE;
    if (m_paraufbearb.s.SCREMA[0] == '1')
    {
        GetDlgItem(IDC_EDIT_CANCELCREMA)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_CANCELCREMA)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_CANCELCREMA)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_CANCELCREMA)->ShowWindow(SW_SHOW);
    }
    bool bFound = false;
    if (m_paraufbearb.s.USETOURMANAGER == 1)
    {
        GetDlgItem(IDC_STATIC_TOURMANAGER)->SetWindowText(CResString::ex().getStrTblText(AETXT_TOURMANAGER_AKTIV));
        GetDlgItem(IDC_STATIC_TOURMANAGER)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_TOURMANAGER)->ShowWindow(SW_SHOW);
        tour = RGB(0, 0, 200);
        bFound = true;
    }
    else if (m_paraufbearb.s.USETOURMANAGER == 2)
    {
        GetDlgItem(IDC_STATIC_TOURMANAGER)->SetWindowText(CResString::ex().getStrTblText(AETXT_AKTIV_AUSSCHLUSS));
        GetDlgItem(IDC_STATIC_TOURMANAGER)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_TOURMANAGER)->ShowWindow(SW_SHOW);
        tour = RGB(0, 150, 0);
        bFound = true;
    }
    if (m_paraufbearb.s.NLEVELIBT == 1)
    {
        GetDlgItem(IDC_STATIC_NLEVEL)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_NLEVEL)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_NLEVEL)->SetWindowText(CResString::ex().getStrTblText(AETXT_NLEVEL_AKTIV));
        bFound = true;
    }
    if (m_paraufbearb.s.ORDERPERIODTOURASSIGNMENT == 1)
    {
        GetDlgItem(IDC_STATIC_FIX)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_FIX)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_FIX)->SetWindowText(CResString::ex().getStrTblText(AETXT_MSV3_FIX));
        bFound = true;
    }
    if (m_paraufbearb.s.MSV3ORDERPERIODCLOSURE == 1)
    {
        CString str;
        GetDlgItem(IDC_STATIC_ABSCHLUSS)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_ABSCHLUSS)->ShowWindow(SW_SHOW);
        str.Format(CResString::ex().getStrTblText(AETXT_MSV3_ABSCHLUSS), m_paraufbearb.s.MSV3CLOSURETIMEADJUSTMENT);
        GetDlgItem(IDC_STATIC_ABSCHLUSS)->SetWindowText(str);
        bFound = true;
    }
    if (bFound)
    {
        GetDlgItem(IDC_STATIC_HINWEIS)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_HINWEIS)->ShowWindow(SW_SHOW);
    }
    EndWaitCursor();
    UpdateData(FALSE);
    if (!GetAeUser().UpdParAufBearb())
    {
        GetDlgItem(IDC_CHECK_JA1)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA10)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA11)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA12)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA13)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA14)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA15)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA16)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA17)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA18)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA19)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA2)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA20)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA21)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA22)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA23)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA24)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA25)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA26)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA27)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA28)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA29)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA3)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA30)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA31)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA32)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA33)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA34)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA35)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA36)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA37)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA38)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA39)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA40)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA41)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA5)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA6)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA7)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA8)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_JA9)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN1)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN10)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN11)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN12)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN13)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN14)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN15)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN16)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN17)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN18)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN19)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN2)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN20)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN21)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN22)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN23)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN24)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN25)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN26)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN27)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN28)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN29)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN3)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN30)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN31)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN32)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN33)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN34)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN35)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN36)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN37)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN38)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN39)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN40)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN41)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN5)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN6)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN7)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN8)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_NEIN9)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_AA)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_ANZPOS)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_AUF_CLOSE)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_BA)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_BEIFUEGER)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_CANCELCREMA)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_DEFWERTKEINABSCHLUSS)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_DELAYEDDAYS)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_DOPKO)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_DPODAYS)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_EILZEIT)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_FILIALE)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_KA)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_KZEIT)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_MAX_DAUER)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_MAX_EIL)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_MAX_QTY)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_MAX_SURCHARGE)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_MAXPOS)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_MAXPOSAUF)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_MIN_BESTELL)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_NO_NATRA)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_NOROUTING)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_NZEIT)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_PLUS_BTM)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_POS_CLOSE)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_POS_ZU)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_PRICE_RANGE)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_PZN_FRACHT)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_PZN_FRANKO)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_PZN_GEB)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_PZNBTM)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_PZNGR)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_PZNKL)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_PZNWF1)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_PZNWF2)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_PZNZYTO)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_REQUEST)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_REVERSE)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_SEPZEIT)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_SPAETER)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_TIMETOCLOSE)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_TOUR_CHECK)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_TOURKIPPZEIT)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_VBPOS)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_WAKE1)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_WAKE2)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_WTAG)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_WTYP)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_ZEITNOBTM)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_ZHH)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_ZMM)->EnableWindow(FALSE);
    }
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDParAufBearb::OnOK()
{
    CARTINF art;
    CString CStr;
    UpdateData();
    m_paraufbearb.s.FILIALNR = static_cast<short>(m_iFiliale);
    AllgStrCopy(m_paraufbearb.s.KDAUFTRAGART, m_CAa, L_PARAUFBEARB_KDAUFTRAGART);
    AllgStrCopy(m_paraufbearb.s.BUCHART, m_CBa, L_PARAUFBEARB_BUCHART);
    AllgStrCopy(m_paraufbearb.s.KOART, m_CKa, L_PARAUFBEARB_KOART);
    if (m_lPZNKl_old != m_lPZNKl && m_lPZNKl != MAXIMUM_ART_NR)
    {
        art.s.ARTIKEL_NR = m_lPZNKl;
        art.s.IMPORTARTICLE = 0;    //Importartikel machen hier keinen Sinn
        art.s.FILIALNR = AeGetApp()->VzNr();
        art.Server(AatartInf_art_nr);
        if (art.rc != SRV_OK)
        {
            MsgBoxOK(IDP_PZN_UNBEKANNT);
            return;
        }
        CStr.Format(CResString::ex().getStrTblText(IDP_SOLL_UPDATE), art.s.ARTIKEL_NAME);
        if (MsgBoxYesNo(CStr) != IDYES)
            return;
    }
    if (m_lPZNZyto_old != m_lPZNZyto && m_lPZNZyto != MAXIMUM_ART_NR)
    {
        art.s.ARTIKEL_NR = m_lPZNZyto;
        art.s.FILIALNR = AeGetApp()->VzNr();
        art.s.IMPORTARTICLE = 0;    //Importartikel machen hier keinen Sinn
        art.Server(AatartInf_art_nr);
        if (art.rc != SRV_OK)
        {
            MsgBoxOK(IDP_PZN_UNBEKANNT);
            return;
        }
        CStr.Format(CResString::ex().getStrTblText(IDP_SOLL_UPDATE), art.s.ARTIKEL_NAME);
        if (MsgBoxYesNo(CStr) != IDYES)
            return;
    }
    if (m_lPZNGr_old != m_lPZNGr && m_lPZNGr != MAXIMUM_ART_NR)
    {
        art.s.ARTIKEL_NR = m_lPZNGr;
        art.s.FILIALNR = AeGetApp()->VzNr();
        art.s.IMPORTARTICLE = 0;    //Importartikel machen hier keinen Sinn
        art.Server(AatartInf_art_nr);
        if (art.rc != SRV_OK)
        {
            MsgBoxOK(IDP_PZN_UNBEKANNT);
            return;
        }
        CStr.Format(CResString::ex().getStrTblText(IDP_SOLL_UPDATE), art.s.ARTIKEL_NAME);
        if (MsgBoxYesNo(CStr) != IDYES)
            return;
    }
    if (m_lPZNBTM_old != m_lPZNBTM && m_lPZNBTM != MAXIMUM_ART_NR)
    {
        art.s.ARTIKEL_NR = m_lPZNBTM;
        art.s.FILIALNR = AeGetApp()->VzNr();
        art.s.IMPORTARTICLE = 0;    //Importartikel machen hier keinen Sinn
        art.Server(AatartInf_art_nr);
        if (art.rc != SRV_OK)
        {
            MsgBoxOK(IDP_PZN_UNBEKANNT);
            return;
        }
        CStr.Format(CResString::ex().getStrTblText(IDP_SOLL_UPDATE), art.s.ARTIKEL_NAME);
        if (MsgBoxYesNo(CStr) != IDYES)
            return;
    }
    if (m_lPZNWf1_old != m_lPZNWf1 && m_lPZNWf1 != MAXIMUM_ART_NR)
    {
        art.s.ARTIKEL_NR = m_lPZNWf1;
        art.s.FILIALNR = AeGetApp()->VzNr();
        art.s.IMPORTARTICLE = 0;    //Importartikel machen hier keinen Sinn
        art.Server(AatartInf_art_nr);
        if (art.rc != SRV_OK)
        {
            MsgBoxOK(IDP_PZN_UNBEKANNT);
            return;
        }
        CStr.Format(CResString::ex().getStrTblText(IDP_SOLL_UPDATE), art.s.ARTIKEL_NAME);
        if (MsgBoxYesNo(CStr) != IDYES)
            return;
    }
    if (m_lPZNWf2_old != m_lPZNWf2 && m_lPZNWf2 != MAXIMUM_ART_NR)
    {
        art.s.ARTIKEL_NR = m_lPZNWf2;
        art.s.FILIALNR = AeGetApp()->VzNr();
        art.s.IMPORTARTICLE = 0;    //Importartikel machen hier keinen Sinn
        art.Server(AatartInf_art_nr);
        if (art.rc != SRV_OK)
        {
            MsgBoxOK(IDP_PZN_UNBEKANNT);
            return;
        }
        CStr.Format(CResString::ex().getStrTblText(IDP_SOLL_UPDATE), art.s.ARTIKEL_NAME);
        if (MsgBoxYesNo(CStr) != IDYES)
            return;
    }
    if (m_lPZNGeb_old != atol(m_CPZNGeb) && atol(m_CPZNGeb) != MAXIMUM_ART_NR)
    {
        art.s.ARTIKEL_NR = atol(m_CPZNGeb);
        art.s.FILIALNR = AeGetApp()->VzNr();
        art.s.IMPORTARTICLE = 0;    //Importartikel machen hier keinen Sinn
        art.Server(AatartInf_art_nr);
        if (art.rc != SRV_OK)
        {
            MsgBoxOK(IDP_PZN_UNBEKANNT);
            return;
        }
        CStr.Format(CResString::ex().getStrTblText(IDP_SOLL_UPDATE), art.s.ARTIKEL_NAME);
        if (MsgBoxYesNo(CStr) != IDYES)
            return;
    }
    if (m_lPZNFranko_old != atol(m_CPZNFranko) && atol(m_CPZNFranko) != MAXIMUM_ART_NR)
    {
        art.s.ARTIKEL_NR = atol(m_CPZNFranko);
        art.s.FILIALNR = AeGetApp()->VzNr();
        art.s.IMPORTARTICLE = 0;    //Importartikel machen hier keinen Sinn
        art.Server(AatartInf_art_nr);
        if (art.rc != SRV_OK)
        {
            MsgBoxOK(IDP_PZN_UNBEKANNT);
            return;
        }
        CStr.Format(CResString::ex().getStrTblText(IDP_SOLL_UPDATE), art.s.ARTIKEL_NAME);
        if (MsgBoxYesNo(CStr) != IDYES)
            return;
    }
    if (m_lPZNFracht_old != atol(m_CPZNFracht) && atol(m_CPZNFracht) != MAXIMUM_ART_NR)
    {
        art.s.ARTIKEL_NR = atol(m_CPZNFracht);
        art.s.FILIALNR = AeGetApp()->VzNr();
        art.s.IMPORTARTICLE = 0;    //Importartikel machen hier keinen Sinn
        art.Server(AatartInf_art_nr);
        if (art.rc != SRV_OK)
        {
            MsgBoxOK(IDP_PZN_UNBEKANNT);
            return;
        }
        CStr.Format(CResString::ex().getStrTblText(IDP_SOLL_UPDATE), art.s.ARTIKEL_NAME);
        if (MsgBoxYesNo(CStr) != IDYES)
            return;
    }
    if (m_LDefwertkeinabschluss < MINIMUM_WERT && m_LDefwertkeinabschluss != 0)
    {
        CStr.Format(CResString::ex().getStrTblText(AETXT_MIN_WERT), MINIMUM_WERT);
        MsgBoxOK(CStr);
        return;
    }
    m_paraufbearb.s.DEFWERTKEINABSCHL = m_LDefwertkeinabschluss;
    m_paraufbearb.s.DURCHLAUFNORMAL = m_lNZeit;
    m_paraufbearb.s.DURCHLAUFEILBOTE = m_lEilZeit;
    m_paraufbearb.s.KARENZTOURSCHEIN = m_lKZeit;
    m_paraufbearb.s.PZNKUEHLBOX1 = m_lPZNKl;
    m_paraufbearb.s.PZNKUEHLBOX2 = m_lPZNGr;
    m_paraufbearb.s.PZNBTMSCHEIN = m_lPZNBTM;
    m_paraufbearb.s.PZNWERBEFACH = m_lPZNWf1;
    m_paraufbearb.s.PZNWERBEFACH2 = m_lPZNWf2;
    m_paraufbearb.s.ANZARTALPHAWSORT = m_lAnzPos;
    m_paraufbearb.s.MAXPOSMENGE = m_lMaxPos;
    m_paraufbearb.s.MAXPOSVERBUND = m_lVbPos;
    AllgStrCopy(m_paraufbearb.s.TOURWOCHENTAG, m_CWTag, L_PARAUFBEARB_TOURWOCHENTAG);
    m_paraufbearb.s.TOURVERSPAETUNG = m_lSpaeter;
    AllgStrCopy(m_paraufbearb.s.BAHNHOFDOPPELKONTR, m_CDopKo, L_PARAUFBEARB_BAHNHOFDOPPELKONTR);
    m_paraufbearb.s.AUFTRAGZUSAMMENMMM = m_lZMM;
    m_paraufbearb.s.AUFTRAGZUSAMMENHHH = m_lZHH;
    m_paraufbearb.s.SEPWANNENTYP = static_cast<short>(m_iWTyp);
    m_paraufbearb.s.SEPWANNENRESTZEIT = m_lSepZeit;
    m_paraufbearb.s.TOURENKIPPZEIT = m_lTourKippZeit;
    m_paraufbearb.s.TIME_NO_BTM = m_lZeitNoBTM;
    m_paraufbearb.s.PZNZYTOSTATIKA = m_lPZNZyto;
    m_paraufbearb.s.MAXPOSAUFTRAG = m_lMaxPosAuf;
    m_paraufbearb.s.ANZPOSZU = m_lPosZu;
    m_paraufbearb.s.MAXPOSEIL = m_lMaxEil;
    m_paraufbearb.s.NOROUTINGMM = static_cast<short>(atoi(m_CNorouting));
    m_paraufbearb.s.PLUSZEITBTM = m_sPlusBTM;
    m_paraufbearb.s.ETARTNONATRA = m_lNoNatra;
    m_paraufbearb.s.MINDESTBESTELLWERT = atol(m_CMinBestell);
    m_paraufbearb.s.PZNADDONCHARGE = atol(m_CPZNGeb);
    m_paraufbearb.s.RESERVEPERIOD = static_cast<short>(atoi(m_CMaxDauer));
    m_paraufbearb.s.RESERVEMAXQTY = static_cast<short>(atoi(m_CMaxQty));
    m_paraufbearb.s.PZNFRANKO = atol(m_CPZNFranko);
    m_paraufbearb.s.PZNFREIGHTAGE = atol(m_CPZNFracht);
    AllgCStrCharToChar(m_CPriceRange, ',', '.');
    m_paraufbearb.s.RANGEPRICEPCT = atof(m_CPriceRange);
    m_paraufbearb.s.TOURCHECKTIME = static_cast<short>(atoi(m_CTourCheck));
    m_paraufbearb.s.ANZAUFCLOSE = static_cast<short>(atoi(m_CAufClose));
    m_paraufbearb.s.ANZPOSCLOSE = static_cast<short>(atoi(m_CPosClose));
    m_paraufbearb.s.WAKETIME1 = m_sWake1;
    m_paraufbearb.s.WAKETIME2 = m_sWake2;
    m_paraufbearb.s.MAXSURCHARGE = m_dMaxSurcharge;
    m_paraufbearb.s.ENCLOSERTILTTIME = m_lBeifueger;
    m_paraufbearb.s.CHECKTIMETOCLOSE = m_sTimeToClose;
    m_paraufbearb.s.MAXQTYREQUEST = m_sRequest;
    m_paraufbearb.s.MAXDPODAYS = m_sDPODays;
    m_paraufbearb.s.DELAYEDDAYS = m_sDelayedDays;
    m_paraufbearb.s.REVERSESUBSTITUTIONDAYS = m_sReverse;
    m_paraufbearb.s.TIMECANCELCREMAORDER = m_sCremacancel;
    if (m_bNein1 == TRUE) m_paraufbearb.s.SSAMMELKOMMI[0] = '0';
    else m_paraufbearb.s.SSAMMELKOMMI[0] = '1';
    if (m_bNein2 == TRUE) m_paraufbearb.s.SVORFAKTURA[0] = '0';
    else m_paraufbearb.s.SVORFAKTURA[0] = '1';
    if (m_bNein3 == TRUE) m_paraufbearb.s.SBTMSCHEIN[0] = '0';
    else m_paraufbearb.s.SBTMSCHEIN[0] = '1';
    if (m_bNein4 == TRUE) m_paraufbearb.s.SWERBUNG[0] = '0';
    else m_paraufbearb.s.SWERBUNG[0] = '1';
    if (m_bNein5 == TRUE) m_paraufbearb.s.SERWEITERTETOURANZ[0] = '0';
    else m_paraufbearb.s.SERWEITERTETOURANZ[0] = '1';
    if (m_bNein6 == TRUE) m_paraufbearb.s.SAUFTRAGZUSAMMEN[0] = '0';
    else m_paraufbearb.s.SAUFTRAGZUSAMMEN[0] = '1';
    if (m_bNein7 == TRUE) m_paraufbearb.s.SSEPWANNENEILBOTE[0] = '0';
    else m_paraufbearb.s.SSEPWANNENEILBOTE[0] = '1';
    if (m_bNein8 == TRUE) m_paraufbearb.s.SKDAUFTRAGSPLIT[0] = '0';
    else m_paraufbearb.s.SKDAUFTRAGSPLIT[0] = '1';
    if (m_bNein9 == TRUE) m_paraufbearb.s.AUTOMNACHLIEF[0] = '0';
    else m_paraufbearb.s.AUTOMNACHLIEF[0] = '1';
    if (m_bNein10 == TRUE) m_paraufbearb.s.DAFUEENTSDIORNL[0] = '0';
    else m_paraufbearb.s.DAFUEENTSDIORNL[0] = '1';
    if (m_bNein11 == TRUE) m_paraufbearb.s.SKUEHLU8GRAD[0] = '0';
    else m_paraufbearb.s.SKUEHLU8GRAD[0] = '1';
    if (m_bNein12 == TRUE) m_paraufbearb.s.SRRSA02[0] = '0';
    else m_paraufbearb.s.SRRSA02[0] = '1';
    if (m_bNein13 == TRUE) m_paraufbearb.s.STRENNBEI10NER[0] = '0';
    else m_paraufbearb.s.STRENNBEI10NER[0] = '1';
    if (m_bNein14 == TRUE) m_paraufbearb.s.STEXT99NAK[0] = '0';
    else m_paraufbearb.s.STEXT99NAK[0] = '1';
    if (m_bNein15 == TRUE) m_paraufbearb.s.SBEARB06[0] = '0';
    else m_paraufbearb.s.SBEARB06[0] = '1';
    if (m_bNein16 == TRUE) m_paraufbearb.s.BTM_EXTRA[0] = '0';
    else m_paraufbearb.s.BTM_EXTRA[0] = '1';
    if (m_bNein17 == TRUE) m_paraufbearb.s.DEFEKTDISPO[0] = '0';
    else m_paraufbearb.s.DEFEKTDISPO[0] = '1';
    if (m_bNein18 == TRUE) m_paraufbearb.s.SVORAUSBEZG[0] = '0';
    else m_paraufbearb.s.SVORAUSBEZG[0] = '1';
    if (m_bNein19 == TRUE) m_paraufbearb.s.SBTMKOMMI[0] = '0';
    else m_paraufbearb.s.SBTMKOMMI[0] = '1';
    if (m_bNein20 == TRUE) m_paraufbearb.s.SNOTOAK[0] = '0';
    else m_paraufbearb.s.SNOTOAK[0] = '1';
    if (m_bNein21 == TRUE) m_paraufbearb.s.SNEWDISCOUNT[0] = '0';
    else m_paraufbearb.s.SNEWDISCOUNT[0] = '1';
    if (m_bNein22 == TRUE) m_paraufbearb.s.SVERUNDEN[0] = '0';
    else m_paraufbearb.s.SVERUNDEN[0] = '1';
    if (m_bNein23 == TRUE) m_paraufbearb.s.SBATCHTEILMENGE[0] = '0';
    else m_paraufbearb.s.SBATCHTEILMENGE[0] = '1';
    if (m_bNein24 == TRUE) m_paraufbearb.s.SNARCTRANS[0] = '0';
    else m_paraufbearb.s.SNARCTRANS[0] = '1';
    if (m_bNein25 == TRUE) m_paraufbearb.s.SPOSSPLIT[0] = '0';
    else m_paraufbearb.s.SPOSSPLIT[0] = '1';
    if (m_bNein26 == TRUE) m_paraufbearb.s.SDAYNIGHT[0] = '0';
    else m_paraufbearb.s.SDAYNIGHT[0] = '1';
    if (m_bNein27 == TRUE) m_paraufbearb.s.SNOCHANGEVAL[0] = '0';
    else m_paraufbearb.s.SNOCHANGEVAL[0] = '1';
    if (m_bNein28 == TRUE) m_paraufbearb.s.SKUMPOS[0] = '0';
    else m_paraufbearb.s.SKUMPOS[0] = '1';
    if (m_bNein29 == TRUE) m_paraufbearb.s.SANZPRINTCODE[0] = '0';
    else m_paraufbearb.s.SANZPRINTCODE[0] = '1';
    if (m_bNein30 == TRUE) m_paraufbearb.s.SDEFORDERDF[0] = '0';
    else m_paraufbearb.s.SDEFORDERDF[0] = '1';
    if (m_bNein31 == TRUE) m_paraufbearb.s.SIBTCSTORG[0] = '0';
    else m_paraufbearb.s.SIBTCSTORG[0] = '1';
    if (m_bNein32 == TRUE) m_paraufbearb.s.SCREMA[0] = '0';
    else m_paraufbearb.s.SCREMA[0] = '1';
    if (m_bNein33 == TRUE) m_paraufbearb.s.SDAYNIGHTMERGE = 0;
    else m_paraufbearb.s.SDAYNIGHTMERGE = 1;
    if (m_bNein34 == TRUE) m_paraufbearb.s.SCLOSEIBTATONCE = 0;
    else m_paraufbearb.s.SCLOSEIBTATONCE = 1;
    if (m_bNein35 == TRUE) m_paraufbearb.s.SWNEWCALLBACK = 0;
    else m_paraufbearb.s.SWNEWCALLBACK = 1;
    if (m_bNein36 == TRUE) m_paraufbearb.s.SSTOPCREMA = 0;
    else m_paraufbearb.s.SSTOPCREMA = 1;
    if (m_bNein37 == TRUE) m_paraufbearb.s.SCOOL20 = 0;
    else m_paraufbearb.s.SCOOL20 = 1;
    if (m_bNein38 == TRUE) m_paraufbearb.s.SNODISPOCLOSED = 0;
    else m_paraufbearb.s.SNODISPOCLOSED = 1;
    if (m_bNein39 == TRUE) m_paraufbearb.s.SCLOSERESTDELIVERYATONCE = 0;
    else m_paraufbearb.s.SCLOSERESTDELIVERYATONCE = 1;
    if (m_bNein40 == TRUE) m_paraufbearb.s.SCLOSERESTDELIVERYATONCE = 0;
    else m_paraufbearb.s.SCLOSERESTDELIVERYATONCE = 1;
    if (m_bNein41 == TRUE) m_paraufbearb.s.SCLOSEDISPOATONCE = 0;
    else m_paraufbearb.s.SCLOSEDISPOATONCE = 1;
    if (m_bNein42 == TRUE) m_paraufbearb.s.USELATESTIBTTOUR = 0;
    else m_paraufbearb.s.USELATESTIBTTOUR = 1;
    // nicht im update, aber merken
    if (m_sklclose == FALSE) m_paraufbearb.s.SKLCLOSE[0] = '0';
    else m_paraufbearb.s.SKLCLOSE[0] = '1';
    BeginWaitCursor();
    m_paraufbearb.Server(AafilUpdaufbearb);

    EndWaitCursor();
    if (m_paraufbearb.rc < SRV_OK)
        return;
    CDialogMultiLang::OnOK();
}

void CDParAufBearb::OnCheckJa1()
{
    if (m_CBJa1.GetCheck()) m_CBNein1.SetCheck(0);
    else m_CBNein1.SetCheck(1);
}

void CDParAufBearb::OnCheckJa2()
{
    if (m_CBJa2.GetCheck()) m_CBNein2.SetCheck(0);
    else m_CBNein2.SetCheck(1);
}

void CDParAufBearb::OnCheckJa3()
{
    if (m_CBJa3.GetCheck()) m_CBNein3.SetCheck(0);
    else m_CBNein3.SetCheck(1);
}

void CDParAufBearb::OnCheckJa4()
{
    if (m_CBJa4.GetCheck()) m_CBNein4.SetCheck(0);
    else m_CBNein4.SetCheck(1);
}

void CDParAufBearb::OnCheckJa5()
{
    if (m_CBJa5.GetCheck()) m_CBNein5.SetCheck(0);
    else m_CBNein5.SetCheck(1);
}

void CDParAufBearb::OnCheckJa6()
{
    if (m_CBJa6.GetCheck()) m_CBNein6.SetCheck(0);
    else m_CBNein6.SetCheck(1);
}

void CDParAufBearb::OnCheckJa7()
{
    if (m_CBJa7.GetCheck()) m_CBNein7.SetCheck(0);
    else m_CBNein7.SetCheck(1);
}

void CDParAufBearb::OnCheckJa8()
{
    if (m_CBJa8.GetCheck()) m_CBNein8.SetCheck(0);
    else m_CBNein8.SetCheck(1);
}

void CDParAufBearb::OnCheckJa9()
{
    if (m_CBJa9.GetCheck()) m_CBNein9.SetCheck(0);
    else m_CBNein9.SetCheck(1);
}

void CDParAufBearb::OnCheckJa10()
{
    if (m_CBJa10.GetCheck()) m_CBNein10.SetCheck(0);
    else m_CBNein10.SetCheck(1);
}
void CDParAufBearb::OnCheckJa11()
{
    if (m_CBJa11.GetCheck()) m_CBNein11.SetCheck(0);
    else m_CBNein11.SetCheck(1);
}

void CDParAufBearb::OnCheckJa12()
{
    if (m_CBJa12.GetCheck()) m_CBNein12.SetCheck(0);
    else m_CBNein12.SetCheck(1);
}

void CDParAufBearb::OnCheckJa13()
{
    if (m_CBJa13.GetCheck()) m_CBNein13.SetCheck(0);
    else m_CBNein13.SetCheck(1);
}

void CDParAufBearb::OnCheckJa14()
{
    if (m_CBJa14.GetCheck()) m_CBNein14.SetCheck(0);
    else m_CBNein14.SetCheck(1);
}

void CDParAufBearb::OnCheckJa15()
{
    if (m_CBJa15.GetCheck()) m_CBNein15.SetCheck(0);
    else m_CBNein15.SetCheck(1);
}

void CDParAufBearb::OnCheckJa16()
{
    if (m_CBJa16.GetCheck()) m_CBNein16.SetCheck(0);
    else m_CBNein16.SetCheck(1);
}

void CDParAufBearb::OnCheckJa17()
{
    if (m_CBJa17.GetCheck()) m_CBNein17.SetCheck(0);
    else m_CBNein17.SetCheck(1);
}

void CDParAufBearb::OnCheckNein1()
{
    if (m_CBNein1.GetCheck()) m_CBJa1.SetCheck(0);
    else m_CBJa1.SetCheck(1);
}

void CDParAufBearb::OnCheckNein2()
{
    if (m_CBNein2.GetCheck()) m_CBJa2.SetCheck(0);
    else m_CBJa2.SetCheck(1);
}

void CDParAufBearb::OnCheckNein3()
{
    if (m_CBNein3.GetCheck()) m_CBJa3.SetCheck(0);
    else m_CBJa3.SetCheck(1);
}

void CDParAufBearb::OnCheckNein4()
{
    if (m_CBNein4.GetCheck()) m_CBJa4.SetCheck(0);
    else m_CBJa4.SetCheck(1);
}

void CDParAufBearb::OnCheckNein5()
{
    if (m_CBNein5.GetCheck()) m_CBJa5.SetCheck(0);
    else m_CBJa5.SetCheck(1);
}

void CDParAufBearb::OnCheckNein6()
{
    if (m_CBNein6.GetCheck()) m_CBJa6.SetCheck(0);
    else m_CBJa6.SetCheck(1);
}

void CDParAufBearb::OnCheckNein7()
{
    if (m_CBNein7.GetCheck()) m_CBJa7.SetCheck(0);
    else m_CBJa7.SetCheck(1);
}

void CDParAufBearb::OnCheckNein8()
{
    if (m_CBNein8.GetCheck()) m_CBJa8.SetCheck(0);
    else m_CBJa8.SetCheck(1);
}

void CDParAufBearb::OnCheckNein9()
{
    if (m_CBNein9.GetCheck()) m_CBJa9.SetCheck(0);
    else m_CBJa9.SetCheck(1);
}

void CDParAufBearb::OnCheckNein10()
{
    if (m_CBNein10.GetCheck()) m_CBJa10.SetCheck(0);
    else m_CBJa10.SetCheck(1);
}

void CDParAufBearb::OnCheckNein11()
{
    if (m_CBNein11.GetCheck()) m_CBJa11.SetCheck(0);
    else m_CBJa11.SetCheck(1);
}

void CDParAufBearb::OnCheckNein12()
{
    if (m_CBNein12.GetCheck()) m_CBJa12.SetCheck(0);
    else m_CBJa12.SetCheck(1);
}

void CDParAufBearb::OnCheckNein13()
{
    if (m_CBNein13.GetCheck()) m_CBJa13.SetCheck(0);
    else m_CBJa13.SetCheck(1);
}

void CDParAufBearb::OnCheckNein14()
{
    if (m_CBNein14.GetCheck()) m_CBJa14.SetCheck(0);
    else m_CBJa14.SetCheck(1);
}

void CDParAufBearb::OnCheckNein15()
{
    if (m_CBNein15.GetCheck()) m_CBJa15.SetCheck(0);
    else m_CBJa15.SetCheck(1);
}

void CDParAufBearb::OnCheckNein16()
{
    if (m_CBNein16.GetCheck()) m_CBJa16.SetCheck(0);
    else m_CBJa16.SetCheck(1);
}

void CDParAufBearb::OnCheckNein17()
{
    if (m_CBNein17.GetCheck()) m_CBJa17.SetCheck(0);
    else m_CBJa17.SetCheck(1);
}

void CDParAufBearb::OnChangeEditAa()
{
    AllgLaengeKontr(&m_EditAa, L_PARAUFBEARB_KDAUFTRAGART,AeGetApp()->Modus());
}

void CDParAufBearb::OnChangeEditAnzpos()
{
    AllgWertKontr(&m_EditAnzPos, MAXIMUM_ANZ_POS);
}

void CDParAufBearb::OnChangeEditBa()
{
    AllgLaengeKontr(&m_EditBa, L_PARAUFBEARB_BUCHART,AeGetApp()->Modus());
}

void CDParAufBearb::OnChangeEditDopko()
{
    AllgLaengeKontr(&m_EditDopKo, L_PARAUFBEARB_BAHNHOFDOPPELKONTR,AeGetApp()->Modus());
}

void CDParAufBearb::OnChangeEditEilzeit()
{
    AllgWertKontr(&m_EditEilZeit, MAXIMUM_MIN);
}

void CDParAufBearb::OnChangeEditKa()
{
    AllgLaengeKontr(&m_EditKa, L_PARAUFBEARB_TOURWOCHENTAG,AeGetApp()->Modus());
}

void CDParAufBearb::OnChangeEditKzeit()
{
    AllgWertKontr(&m_EditKZeit, MAXIMUM_MIN);
}

void CDParAufBearb::OnChangeEditMaxpos()
{
    AllgWertKontr(&m_EditMaxPos, MAXIMUM_ANZ_POS);
}

void CDParAufBearb::OnChangeEditNzeit()
{
    AllgWertKontr(&m_EditNZeit, MAXIMUM_DURCHLAUF);
}

void CDParAufBearb::OnChangeEditPznbtm()
{
    AllgWertKontr(&m_EditPZNBTM, MAXIMUM_IDF);
}

void CDParAufBearb::OnChangeEditPzngr()
{
    AllgWertKontr(&m_EditPZNGr, MAXIMUM_IDF);
}

void CDParAufBearb::OnChangeEditPznkl()
{
    AllgWertKontr(&m_EditPZNKl, MAXIMUM_IDF);
}

void CDParAufBearb::OnChangeEditPznwf1()
{
    AllgWertKontr(&m_EditPZNWf1, MAXIMUM_IDF);
}

void CDParAufBearb::OnChangeEditPznwf2()
{
    AllgWertKontr(&m_EditPZNWf2, MAXIMUM_IDF);
}

void CDParAufBearb::OnChangeEditSpaeter()
{
    char buf[22];
    m_EditSpaeter.GetWindowText(buf,20);
    if (buf[0] == '-' && buf[1] == '\0')
        return;
    AllgWertKontr(&m_EditSpaeter, MINIMUM_SPAETER, MAXIMUM_SPAETER);
}

void CDParAufBearb::OnChangeEditWtag()
{
    AllgLaengeKontr(&m_EditWTag, L_PARAUFBEARB_TOURWOCHENTAG,AeGetApp()->Modus());
}

void CDParAufBearb::OnChangeEditZhh()
{
    AllgWertKontr(&m_EditZHH, MAXIMUM_END_ZEIT);
}

void CDParAufBearb::OnChangeEditZmm()
{
    AllgWertKontr(&m_EditZMM, MAXIMUM_ZUSAMMENZEIT);
}

void CDParAufBearb::OnChangeEditWtyp()
{
    AllgWertKontr(&m_EditWTyp, MAXIMUM_KOMMIARTTYP);
}

void CDParAufBearb::OnChangeEditSepzeit()
{
    AllgWertKontr(&m_EditSepZeit, MAXIMUM_MIN);
}

void CDParAufBearb::OnChangeEditTourkippzeit()
{
    AllgWertKontr(&m_EditTourKippZeit, MAXIMUM_END_ZEIT);
}

void CDParAufBearb::OnChangeEditDefwertkeinabschluss()
{
    AllgWertKontr(&m_EditDefwertkeinabschluss, MAXIMUM_DEFWERT);
}

void CDParAufBearb::OnChangeEditZeitnobtm()
{
    AllgWertKontr(&m_EditZeitNoBTM, MAXIMUM_END_ZEIT);
}

void CDParAufBearb::OnChangeEditVbpos()
{
    AllgWertKontr(&m_EditVbPos, MINIMUM_VB_POS, MAXIMUM_VB_POS);
}

void CDParAufBearb::OnChangeEditPznzyto()
{
    AllgWertKontr(&m_EditPZNZyto, MAXIMUM_IDF);
}

void CDParAufBearb::OnBnClickedCheckJa18()
{
    if (m_CBJa18.GetCheck()) m_CBNein18.SetCheck(0);
    else m_CBNein18.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein18()
{
    if (m_CBNein18.GetCheck()) m_CBJa18.SetCheck(0);
    else m_CBJa18.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckJa19()
{
    if (m_CBJa19.GetCheck()) m_CBNein19.SetCheck(0);
    else m_CBNein19.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein19()
{
    if (m_CBNein19.GetCheck()) m_CBJa19.SetCheck(0);
    else m_CBJa19.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckJa20()
{
    if (m_CBJa20.GetCheck()) m_CBNein20.SetCheck(0);
    else m_CBNein20.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein20()
{
    if (m_CBNein20.GetCheck()) m_CBJa20.SetCheck(0);
    else m_CBJa20.SetCheck(1);
}

void CDParAufBearb::OnEnChangeEditMaxposauf()
{
    AllgWertKontr(&m_edit_MaxPosAuf, MAXIMUM_POS_AUF);
}

void CDParAufBearb::OnEnChangeEditPosZu()
{
    AllgWertKontr(&m_edit_PosZu, MAXIMUM_POS_AUF);
}

void CDParAufBearb::OnEnChangeEditMaxEil()
{
    AllgWertKontr(&m_edit_MaxEil, MAXIMUM_POS_AUF);
}

void CDParAufBearb::OnEnChangeEditNorouting()
{
    AllgWertKontr(&m_EditNorouting, MAXIMUM_MIN);
}

void CDParAufBearb::OnBnClickedCheckJa21()
{
    if (m_CBJa21.GetCheck()) m_CBNein21.SetCheck(0);
    else m_CBNein21.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein21()
{
    if (m_CBNein21.GetCheck()) m_CBJa21.SetCheck(0);
    else m_CBJa21.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckJa22()
{
    if (m_CBJa22.GetCheck()) m_CBNein22.SetCheck(0);
    else m_CBNein22.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein22()
{
    if (m_CBNein22.GetCheck()) m_CBJa22.SetCheck(0);
    else m_CBJa22.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckJa23()
{
    if (m_CB_Ja23.GetCheck()) m_CB_Nein23.SetCheck(0);
    else m_CB_Nein23.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein23()
{
    if (m_CB_Nein23.GetCheck()) m_CB_Ja23.SetCheck(0);
    else m_CB_Ja23.SetCheck(1);
}

void CDParAufBearb::OnEnChangeEditPlusBtm()
{
    AllgWertKontr(&m_EditPlusBTM, MAXIMUM_MIN);
}

void CDParAufBearb::OnEnChangeEditMinBestell()
{
    AllgWertKontr(&m_EditMinBestell, MAXIMUM_MINBESTELL);
}

void CDParAufBearb::OnEnChangeEditPznGeb()
{
    AllgWertKontr(&m_EditPZNGeb, MAXIMUM_IDF);
}

void CDParAufBearb::OnEnChangeEditMaxDauer()
{
    AllgWertKontr(&m_EditMaxDauer, MAXIMUM_MIN);
}

void CDParAufBearb::OnEnChangeEditMaxQty()
{
    AllgWertKontr(&m_EditMaxQty, MAXIMUM_RESERVE_QTY);
}

void CDParAufBearb::OnEnChangeEditPriceRange()
{
    AllgWedDezimalKontr(&m_EditPriceRange, 4,2);
}

void CDParAufBearb::OnBnClickedCheckJa24()
{
    if (m_CBJa24.GetCheck()) m_CBNein24.SetCheck(0);
    else m_CBNein24.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein24()
{
    if (m_CBNein24.GetCheck()) m_CBJa24.SetCheck(0);
    else m_CBJa24.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckJa25()
{
    if (m_CBJa25.GetCheck()) m_CBNein25.SetCheck(0);
    else m_CBNein25.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein25()
{
    if (m_CBNein25.GetCheck()) m_CBJa25.SetCheck(0);
    else m_CBJa25.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckJa26()
{
    if (m_CBJa26.GetCheck()) m_CBNein26.SetCheck(0);
    else m_CBNein26.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein26()
{
    if (m_CBNein26.GetCheck()) m_CBJa26.SetCheck(0);
    else m_CBJa26.SetCheck(1);
}

void CDParAufBearb::OnEnChangeEditTourCheck()
{
    AllgWertKontr(&m_EditTourCheck, MAXIMUM_MIN);
}

void CDParAufBearb::OnEnChangeEditPznFranko()
{
    AllgWertKontr(&m_EditPZNFranko, MAXIMUM_IDF);
}

void CDParAufBearb::OnEnChangeEditPznFracht()
{
    AllgWertKontr(&m_EditPZNFracht, MAXIMUM_IDF);
}

void CDParAufBearb::OnEnChangeEditAufClose()
{
    AllgWertKontr(&m_EditAufClose, MAXIMUM_POS_AUF);
}

void CDParAufBearb::OnEnChangeEditPosClose()
{
    AllgWertKontr(&m_EditPosClose, MAXIMUM_ANZ_POS);
}

void CDParAufBearb::OnBnClickedCheckJa27()
{
    if (m_CBJa27.GetCheck()) m_CBNein27.SetCheck(0);
    else m_CBNein27.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein27()
{
    if (m_CBNein27.GetCheck()) m_CBJa27.SetCheck(0);
    else m_CBJa27.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckJa28()
{
    if (m_CBJa28.GetCheck()) m_CBNein28.SetCheck(0);
    else m_CBNein28.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein28()
{
    if (m_CBNein28.GetCheck()) m_CBJa28.SetCheck(0);
    else m_CBJa28.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckJa29()
{
    if (m_CBJa29.GetCheck()) m_CBNein29.SetCheck(0);
    else m_CBNein29.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein29()
{
    if (m_CBNein29.GetCheck()) m_CBJa29.SetCheck(0);
    else m_CBJa29.SetCheck(1);
}

void CDParAufBearb::OnEnChangeEditWake1()
{
    AllgWertKontr(&m_EditWake1, MAXIMUM_MIN);
}

void CDParAufBearb::OnEnChangeEditWake2()
{
    AllgWertKontr(&m_EditWake2, MAXIMUM_MIN);
}

void CDParAufBearb::OnBnClickedCheckJa30()
{
    if (m_CBJa30.GetCheck()) m_CBNein30.SetCheck(0);
    else m_CBNein30.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein30()
{
    if (m_CBNein30.GetCheck()) m_CBJa30.SetCheck(0);
    else m_CBJa30.SetCheck(1);
}

void CDParAufBearb::OnEnChangeEditBeifueger()
{
    AllgWertKontr(&m_editBeifueger, MAXIMUM_DURCHLAUF);
}

void CDParAufBearb::OnBnClickedCheckJa31()
{
    if (m_CBJa31.GetCheck()) m_CBNein31.SetCheck(0);
    else m_CBNein31.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein31()
{
    if (m_CBNein31.GetCheck()) m_CBJa31.SetCheck(0);
    else m_CBJa31.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckJa32()
{
    if (m_CBJa32.GetCheck()) m_CBNein32.SetCheck(0);
    else m_CBNein32.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein32()
{
    if (m_CBNein32.GetCheck()) m_CBJa32.SetCheck(0);
    else m_CBJa32.SetCheck(1);
}

void CDParAufBearb::OnEnChangeEditTimetoclose()
{
    AllgWertKontr(&m_editTimeToClose, MAXIMUM_TIMETOCLOSE);
}

void CDParAufBearb::OnEnChangeEditRequest()
{
    AllgWertKontr(&m_editRequest, MAXIMUM_REQUEST);
}

void CDParAufBearb::OnEnChangeEditDpodays()
{
    AllgWertKontr(&m_editDPODays, MAXIMUM_DPODAYS);
}

void CDParAufBearb::OnEnChangeEditDelayeddays()
{
    AllgWertKontr(&m_editDelayedDays, MAXIMUM_DELAYEDDAYS);
}

void CDParAufBearb::OnEnChangeEditReverse()
{
    AllgWertKontr(&m_editReverse, MAXIMUM_REVERSE);
}

void CDParAufBearb::OnEnChangeEditCremacancel()
{
    AllgWertKontr(&m_editCremacancel, MAXIMUM_HOUR);
}

void CDParAufBearb::OnBnClickedCheckJa33()
{
    if (m_CB_Ja33.GetCheck()) m_CBNein33.SetCheck(0);
    else m_CBNein33.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein33()
{
    if (m_CBNein33.GetCheck()) m_CB_Ja33.SetCheck(0);
    else m_CB_Ja33.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckJa34()
{
    if (m_CB_Ja34.GetCheck()) m_CBNein34.SetCheck(0);
    else m_CBNein34.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein34()
{
    if (m_CBNein34.GetCheck()) m_CB_Ja34.SetCheck(0);
    else m_CB_Ja34.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckJa35()
{
    if (m_CB_Ja35.GetCheck()) m_CBNein35.SetCheck(0);
    else m_CBNein35.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein35()
{
    if (m_CBNein35.GetCheck()) m_CB_Ja35.SetCheck(0);
    else m_CB_Ja35.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckJa36()
{
    if (m_CB_Ja36.GetCheck()) m_CBNein36.SetCheck(0);
    else m_CBNein36.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein36()
{
    if (m_CBNein36.GetCheck()) m_CB_Ja36.SetCheck(0);
    else m_CB_Ja36.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckJa37()
{
    if (m_CB_Ja37.GetCheck()) m_CBNein37.SetCheck(0);
    else m_CBNein37.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein37()
{
    if (m_CBNein37.GetCheck()) m_CB_Ja37.SetCheck(0);
    else m_CB_Ja37.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckJa38()
{
    if (m_CB_Ja38.GetCheck()) m_CBNein38.SetCheck(0);
    else m_CBNein38.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein38()
{
    if (m_CBNein38.GetCheck()) m_CB_Ja38.SetCheck(0);
    else m_CB_Ja38.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckJa39()
{
    if (m_CB_Ja39.GetCheck()) m_CBNein39.SetCheck(0);
    else m_CBNein39.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein39()
{
    if (m_CBNein39.GetCheck()) m_CB_Ja39.SetCheck(0);
    else m_CB_Ja39.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckJa40()
{
    if (m_CB_Ja40.GetCheck()) m_CBNein40.SetCheck(0);
    else m_CBNein40.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein40()
{
    if (m_CBNein40.GetCheck()) m_CB_Ja40.SetCheck(0);
    else m_CB_Ja40.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckJa41()
{
    if (m_CB_Ja41.GetCheck()) m_CBNein41.SetCheck(0);
    else m_CBNein41.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein41()
{
    if (m_CBNein41.GetCheck()) m_CB_Ja41.SetCheck(0);
    else m_CB_Ja41.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckJa42()
{
    if (m_CB_Ja42.GetCheck()) m_CBNein42.SetCheck(0);
    else m_CBNein42.SetCheck(1);
}

void CDParAufBearb::OnBnClickedCheckNein42()
{
    if (m_CBNein42.GetCheck()) m_CB_Ja42.SetCheck(0);
    else m_CB_Ja42.SetCheck(1);
}

HBRUSH CDParAufBearb::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);
    if (pWnd->GetDlgCtrlID() == IDC_STATIC_TOURMANAGER)
        pDC->SetTextColor(tour);
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_NLEVEL)
        pDC->SetTextColor(RGB(0,0,200));
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_FIX)
        pDC->SetTextColor(RGB(0,0,200));
    else if (pWnd->GetDlgCtrlID() == IDC_STATIC_ABSCHLUSS)
        pDC->SetTextColor(RGB(0,0,200));

    return hbr;
}

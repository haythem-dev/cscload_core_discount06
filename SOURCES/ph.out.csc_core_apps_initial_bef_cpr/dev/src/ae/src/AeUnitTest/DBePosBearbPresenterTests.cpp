#include "stdafx.h"
#include "CppUnitTest.h"

#include "DBePosBearbPresenterTests.h"
#include <DBePosBearbPresenter.h>
#include <DBePosBearbData.h>
#include "DBePosBearbModelMock.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AeUnitTest
{
    TEST_CLASS(DBePosBearbPresenterTests)
    {
    private:
        CDBePosBearbData _data;
        CDBePosBearbModelMock _model;
        CDBePosBearbPresenter _presenter;

    public:
        DBePosBearbPresenterTests() : _presenter(_data, _model)
        {
            _data.m_bIgnoreNoWafo = true;
        }

        // AUSSERHANDEL
        TEST_METHOD(InitDialog_ETARTSCHALTER1_3__NL_false_DI_false)
        {
            _model.m_Article.ETARTSCHALTER1 = 0x3000;

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);
        }

        // BTM
        TEST_METHOD(InitDialog_ETARTKLASSE1_6__NL_false_DI_false)
        {
            _model.m_Article.ETARTKLASSE1 = 0x0200;

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);
        }

        // AUSLAUF
        TEST_METHOD(InitDialog_ETARTSCHALTER1_4__NL_false_DI_true)
        {
            _model.m_Article.ETARTSCHALTER1 = 0x0800;

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsTrue(_data.m_bEnableBtnDispo);
        }

        // EKS
        TEST_METHOD(InitDialog_ETARTSCHALTER5_0__NL_false_DI_true)
        {
            _model.m_Article.ETARTSCHALTER5 = 0x8000;

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsTrue(_data.m_bEnableBtnDispo);
        }

        // AArt == "SV"
        TEST_METHOD(InitDialog_AArt_SV__NL_false_DI_false)
        {
            _data.m_strAArt = "SV";

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);
        }

        // Not IsNachlieferung
        TEST_METHOD(InitDialog_not_NL__NL_false_DI_true)
        {
            _model.m_bNachlieferung = false;

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsTrue(_data.m_bEnableBtnDispo);
        }

        // else
        TEST_METHOD(InitDialog_Else__NL_false_DI_true)
        {
            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsTrue(_data.m_bEnableBtnDispo);
        }

        // KndNLTyp == 4 && WAFOTYP == 3 && AArt == "SV"
        TEST_METHOD(InitDialog_KndNLTyp_4_WAFOTYP_3_AArt_SV__NL_true_DI_false)
        {
            _model.m_cKndNLTyp = '4';
            _model.m_Article.WAFOTYP[0] = '3';
            _data.m_strAArt = "SV";

            _presenter.InitDialog();

            Assert::IsTrue(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);
        }

        // KndNLTyp == 4 && WAFOTYP == 3 && else
        TEST_METHOD(InitDialog_KndNLTyp_4_WAFOTYP_3_Else__NL_true_DI_true)
        {
            _model.m_cKndNLTyp = '4';
            _model.m_Article.WAFOTYP[0] = '3';

            _presenter.InitDialog();

            Assert::IsTrue(_data.m_bEnableBtnNachlieferung);
            Assert::IsTrue(_data.m_bEnableBtnDispo);
        }

        // ETARTSCHALTER2,15 && AArt == "SV"
        TEST_METHOD(InitDialog_ETARTSCHALTER2_15_AArt_SV__NL_true_DI_false)
        {
            _model.m_Article.ETARTSCHALTER2 = 0x0001;
            _data.m_strAArt = "SV";

            _presenter.InitDialog();

            Assert::IsTrue(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);
        }

        // ETARTSCHALTER2,15 && else
        TEST_METHOD(InitDialog_ETARTSCHALTER2_15_Else__NL_true_DI_true)
        {
            _model.m_Article.ETARTSCHALTER2 = 0x0001;

            _presenter.InitDialog();

            Assert::IsTrue(_data.m_bEnableBtnNachlieferung);
            Assert::IsTrue(_data.m_bEnableBtnDispo);
        }

        // KndMussKopfBem && ETARTSCHALTER2,15 && AArt == "SV"
        TEST_METHOD(InitDialog_KndMussKopfBem_ETARTSCHALTER2_15_AArt_SV__NL_false_DI_false)
        {
            _model.m_Article.ETARTSCHALTER2 = 0x0001;
            _data.m_bKndMussKopfBem = true;
            _data.m_strAArt = "SV";

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);
        }

        // KndMussKopfBem && ETARTSCHALTER2,15 && else
        TEST_METHOD(InitDialog_KndMussKopfBem_ETARTSCHALTER2_15_Else__NL_false_DI_true)
        {
            _model.m_Article.ETARTSCHALTER2 = 0x0001;
            _data.m_bKndMussKopfBem = true;

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsTrue(_data.m_bEnableBtnDispo);
        }

        // IMPORTARTICLE && ETARTSCHALTER2,15 && AArt == "SV"
        TEST_METHOD(InitDialog_IMPORTARTICLE_ETARTSCHALTER2_15_AArt_SV__NL_false_DI_false)
        {
            _model.m_Article.IMPORTARTICLE = 1;
            _model.m_Article.ETARTSCHALTER2 = 0x0001;
            _data.m_strAArt = "SV";

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);
        }

        // IMPORTARTICLE && ETARTSCHALTER2,15 && else
        TEST_METHOD(InitDialog_IMPORTARTICLE_ETARTSCHALTER2_15_Else__NL_false_DI_false)
        {
            _model.m_Article.IMPORTARTICLE = 1;
            _model.m_Article.ETARTSCHALTER2 = 0x0001;

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);
        }

        // IMPORTARTICLE && DeGetter && AArt == "SV"
        TEST_METHOD(InitDialog_IMPORTARTICLE_DeGetter_AArt_SV__NL_false_DI_false)
        {
            _model.m_Article.IMPORTARTICLE = 1;
            _model.m_bDEGetter = true;
            _data.m_strAArt = "SV";

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);
        }

        // IMPORTARTICLE && DeGetter && else
        TEST_METHOD(InitDialog_IMPORTARTICLE_DeGetter_Else__NL_false_DI_false)
        {
            _model.m_Article.IMPORTARTICLE = 1;
            _model.m_bDEGetter = true;

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);
        }

        // IMPORTARTICLE && DeGetter && ImportArticle found && AArt == "SV"
        TEST_METHOD(InitDialog_IMPORTARTICLE_DeGetter_ImportArticleFound_AArt_SV__NL_false_DI_true)
        {
            _model.m_Article.IMPORTARTICLE = 1;
            _model.m_bDEGetter = true;
            _model.m_bImportArticle = true;
            _data.m_strAArt = "SV";

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsTrue(_data.m_bEnableBtnDispo);
        }

        // IMPORTARTICLE && DeGetter && ImportArticle found && else
        TEST_METHOD(InitDialog_IMPORTARTICLE_DeGetter_ImportArticleFound_Else__NL_false_DI_true)
        {
            _model.m_Article.IMPORTARTICLE = 1;
            _model.m_bImportArticle = true;
            _model.m_bDEGetter = true;

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsTrue(_data.m_bEnableBtnDispo);
        }

        // DE && ARTIKELAKTIV == '0' && ETARTSCHALTER2,15 && AArt == "SV"
        TEST_METHOD(InitDialog_DE_not_ARTIKELAKTIV_ETARTSCHALTER2_15_AArt_SV__NL_false_DI_false)
        {
            _model.m_bDE = true;
            _model.m_Article.ARTIKELAKTIV[0] = '0';
            _model.m_Article.ETARTSCHALTER2 = 0x0001;
            _data.m_strAArt = "SV";

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);
        }

        // DE && ARTIKELAKTIV == '0' && ETARTSCHALTER2,15 && else
        TEST_METHOD(InitDialog_DE_not_ARTIKELAKTIV_ETARTSCHALTER2_15_Else__NL_false_DI_false)
        {
            _model.m_bDE = true;
            _model.m_Article.ARTIKELAKTIV[0] = '0';
            _model.m_Article.ETARTSCHALTER2 = 0x0001;

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);
        }

        // DE && ARTIKEL_GESPERRT == '1' && ETARTSCHALTER2,15 && AArt == "SV"
        TEST_METHOD(InitDialog_DE_ARTIKELGESPERRT_ETARTSCHALTER2_15_AArt_SV__NL_false_DI_false)
        {
            _model.m_bDE = true;
            _model.m_Article.ARTIKEL_GESPERRT[0] = '1';
            _model.m_Article.ETARTSCHALTER2 = 0x0001;
            _data.m_strAArt = "SV";

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);
        }

        // DE && ARTIKEL_GESPERRT == '1' && ETARTSCHALTER2,15 && else
        TEST_METHOD(InitDialog_DE_ARTIKELGESPERRT_ETARTSCHALTER2_15_Else__NL_false_DI_false)
        {
            _model.m_bDE = true;
            _model.m_Article.ARTIKEL_GESPERRT[0] = '1';
            _model.m_Article.ETARTSCHALTER2 = 0x0001;

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);
        }

        // DE && WAFOTYP == 3 && ETARTSCHALTER2,15 && else
        TEST_METHOD(InitDialog_DE_WAFOTYP_3_Else__NL_false_DI_false)
        {
            _model.m_bDE = true;
            _model.m_Article.WAFOTYP[0] = '3';
            _data.m_bIgnoreNoWafo = false;
            _model.m_Article.ETARTSCHALTER2 = 0x0001;

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);
        }

        // DE && article.ABDACODE == "GUEG1" && AUSLAUF
        TEST_METHOD(InitDialog_DE_ABDACODE_GUEG1_ETARTSCHALTER1_4__NL_false_DI_false)
        {
            _model.m_bDE = true;
            strcpy_s(_model.m_Article.ABDACODE, "GUEG1");
            _model.m_Article.ETARTSCHALTER1 = 0x0800;

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);

            Assert::AreEqual("GUEG1 ", _data.m_strAH);
        }

        // DE && article.ABDACODE == "GUEG1" && EKS
        TEST_METHOD(InitDialog_DE_ABDACODE_GUEG1_ETARTSCHALTER5_0__NL_false_DI_false)
        {
            _model.m_bDE = true;
            strcpy_s(_model.m_Article.ABDACODE, "GUEG1");
            _model.m_Article.ETARTSCHALTER5 = 0x8000;

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);

            Assert::AreEqual("GUEG1 ", _data.m_strAH);
        }

        // DE && article.ABDACODE == "GUEG1" && Not IsNachlieferung
        TEST_METHOD(InitDialog_DE_ABDACODE_GUEG1_not_NL__NL_false_DI_false)
        {
            _model.m_bDE = true;
            strcpy_s(_model.m_Article.ABDACODE, "GUEG1");
            _model.m_bNachlieferung = false;

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);

            Assert::AreEqual("GUEG1 ", _data.m_strAH);
        }

        // DE && article.ABDACODE == "GUEG1" && else
        TEST_METHOD(InitDialog_DE_ABDACODE_GUEG1_Else__NL_false_DI_false)
        {
            _model.m_bDE = true;
            strcpy_s(_model.m_Article.ABDACODE, "GUEG1");

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);

            Assert::AreEqual("GUEG1 ", _data.m_strAH);
        }

        // DE && article.ABDACODE == "GUEG2" && AUSLAUF
        TEST_METHOD(InitDialog_DE_ABDACODE_GUEG2_ETARTSCHALTER1_4__NL_false_DI_false)
        {
            _model.m_bDE = true;
            strcpy_s(_model.m_Article.ABDACODE, "GUEG2");
            _model.m_Article.ETARTSCHALTER1 = 0x0800;

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);

            Assert::AreEqual("GUEG2 ", _data.m_strAH);
        }

        // DE && article.ABDACODE == "GUEG2" && EKS
        TEST_METHOD(InitDialog_DE_ABDACODE_GUEG2_ETARTSCHALTER5_0__NL_false_DI_false)
        {
            _model.m_bDE = true;
            strcpy_s(_model.m_Article.ABDACODE, "GUEG2");
            _model.m_Article.ETARTSCHALTER5 = 0x8000;

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);

            Assert::AreEqual("GUEG2 ", _data.m_strAH);
        }

        // DE && article.ABDACODE == "GUEG2" && Not IsNachlieferung
        TEST_METHOD(InitDialog_DE_ABDACODE_GUEG2_not_NL__NL_false_DI_false)
        {
            _model.m_bDE = true;
            strcpy_s(_model.m_Article.ABDACODE, "GUEG2");
            _model.m_bNachlieferung = false;

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);

            Assert::AreEqual("GUEG2 ", _data.m_strAH);
        }

        // DE && ETARTSCHALTER2,15 && else
        TEST_METHOD(InitDialog_DE_ABDACODE_GUEG2_Else__NL_false_DI_false)
        {
            _model.m_bDE = true;
            strcpy_s(_model.m_Article.ABDACODE, "GUEG2");

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);

            Assert::AreEqual("GUEG2 ", _data.m_strAH);
        }

        // DE && ETARTSCHALTER2,15 && AUSLAUF
        TEST_METHOD(InitDialog_DE_ETARTSCHALTER2_15_ETARTSCHALTER1_4__NL_false_DI_false)
        {
            _model.m_bDE = true;
            _model.m_Article.ETARTSCHALTER2 = 0x0001;
            _model.m_Article.ETARTSCHALTER1 = 0x0800;

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);
        }

        // DE && ETARTSCHALTER2,15 && EKS
        TEST_METHOD(InitDialog_DE_ETARTSCHALTER2_15_ETARTSCHALTER5_0__NL_false_DI_false)
        {
            _model.m_bDE = true;
            _model.m_Article.ETARTSCHALTER2 = 0x0001;
            _model.m_Article.ETARTSCHALTER5 = 0x8000;

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);
        }

        // DE && ETARTSCHALTER2,15 && Not IsNachlieferung
        TEST_METHOD(InitDialog_DE_ETARTSCHALTER2_15_GUEG1_not_NL__NL_false_DI_false)
        {
            _model.m_bDE = true;
            _model.m_Article.ETARTSCHALTER2 = 0x0001;
            _model.m_bNachlieferung = false;

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);
        }

        // DE && ETARTSCHALTER2,15 && else
        TEST_METHOD(InitDialog_DE_ETARTSCHALTER2_15_Else__NL_true_DI_false)
        {
            _model.m_bDE = true;
            _model.m_Article.ETARTSCHALTER2 = 0x0001;

            _presenter.InitDialog();

            Assert::IsTrue(_data.m_bEnableBtnNachlieferung);
            Assert::IsFalse(_data.m_bEnableBtnDispo);
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////
        // Check boundary conditions "KndNLTyp" && "WAFOTYP"
        //////////////////////////////////////////////////////////////////////////////////////////////////

        // KndNLTyp == 2 && WAFOTYP == 1 && AArt == "SV"
        TEST_METHOD(InitDialog_CheckBoundaries_KndNLTyp_2_WAFOTYP_1_AArt_SV__NL_true)
        {
            _model.m_cKndNLTyp = '2';
            _model.m_Article.WAFOTYP[0] = '1';
            _data.m_strAArt = "SV";

            _presenter.InitDialog();

            Assert::IsTrue(_data.m_bEnableBtnNachlieferung);
        }

        // KndNLTyp == 6 && WAFOTYP == 1 && AArt == "SV"
        TEST_METHOD(InitDialog_CheckBoundaries_KndNLTyp_6_WAFOTYP_1_AArt_SV__NL_true)
        {
            _model.m_cKndNLTyp = '6';
            _model.m_Article.WAFOTYP[0] = '1';
            _data.m_strAArt = "SV";

            _presenter.InitDialog();

            Assert::IsTrue(_data.m_bEnableBtnNachlieferung);
        }

        // KndNLTyp == 1 && WAFOTYP == 1 && AArt == "SV"
        TEST_METHOD(InitDialog_CheckBoundaries_KndNLTyp_1_WAFOTYP_1_AArt_SV__NL_false)
        {
            _model.m_cKndNLTyp = '1';
            _model.m_Article.WAFOTYP[0] = '1';
            _data.m_strAArt = "SV";

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
        }

        // KndNLTyp == 7 && WAFOTYP == 1 && AArt == "SV"
        TEST_METHOD(InitDialog_CheckBoundaries_KndNLTyp_7_WAFOTYP_1_AArt_SV__NL_false)
        {
            _model.m_cKndNLTyp = '7';
            _model.m_Article.WAFOTYP[0] = '1';
            _data.m_strAArt = "SV";

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
        }

        // KndNLTyp == 3 && WAFOTYP == 0 && AArt == "SV"
        TEST_METHOD(InitDialog_CheckBoundaries_KndNLTyp_3_WAFOTYP_0_AArt_SV__NL_false)
        {
            _model.m_cKndNLTyp = '3';
            _model.m_Article.WAFOTYP[0] = '0';
            _data.m_strAArt = "SV";

            _presenter.InitDialog();

            Assert::IsFalse(_data.m_bEnableBtnNachlieferung);
        }
    };
}

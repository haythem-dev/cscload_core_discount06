#ifndef GUARD_LIBCSC_RETURNS_RETURN_POSITION_CHECK_UC_H
#define GUARD_LIBCSC_RETURNS_RETURN_POSITION_CHECK_UC_H

#include <boost/shared_ptr.hpp>
#include <returns/returnrulebook/ireturnrulebookrepositoryptr.h>
#include <returns/returnrulebook/returnrulebookptr.h>
#include <returns/returnperiod/ireturnperiodrepositoryptr.h>
#include <returns/returnperiod/returnperiodarticletypeenum.h>
#include <returns/returnannouncement/returnannouncementptr.h>
#include <returns/returnannouncement/returnannouncementpos/returnannouncementposptr.h>
#include <document/deliveryadvice/deliveryadvicerepositoryptr.h>
#include <document/deliveryadvice/deliveryadviceptr.h>
#include <workingdayscalendar/iworkingdayscalendarrepositoryptr.h>
#include <libbasarcmnutil_bstring.h>
#include <libbasarcmnutil_decimal.h>
#include "pxsess.hpp"
#include "pxartbaseptr.h"


namespace libcsc {
namespace returns {

class ReturnPositionCheckUC
{
public:
	ReturnPositionCheckUC();
	virtual ~ReturnPositionCheckUC();

	void injectReturnRuleBookRepository(IReturnRuleBookRepositoryPtr rulebook);
	void injectReturnPeriodRepository(IReturnPeriodRepositoryPtr repo);
	void injectDeliveryAdviceRepository(document::DeliveryAdviceRepositoryPtr repo);
	void injectWorkingdaysCalendarRepository(workingdayscalendar::IWorkingdaysCalendarRepositoryPtr repo);
	void injectHighPriceLimit(const basar::Decimal& limit);
	void injectSession(pxSession* sess);

	void setReturnAnnouncement(ReturnAnnouncementPtr returnAnnouncement);
	ReturnAnnouncementPtr getReturnAnnouncement() const;

	void checkPosition(ReturnAnnouncementPosPtr pos);

private:
	bool matchesRule(ReturnAnnouncementPosPtr pos, ReturnRuleBookPtr rule, pxArtBasePtr article) const;

	bool C01_InvoiceUnknown		(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const; //1	Rechnungsnr.Unbekannt	Rechnung in Rechnungshistorie nicht gefunden
	bool C02_InvoiceCancelled	(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const; //2	Rechnung storniert	Rechnung ist storniert
	bool C03_ArticleNotInInvoice(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const; //3	Artikel nicht auf Rechnung	Artikelcode ist nicht Teil der Rechnung

	bool C23_BatchNotInInvoice		(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const;
	bool C24_ExpiryDateNotInInvoice	(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const;

	bool C04_QuantityExceeded	(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const; //4	Menge erschoepft	Komplette Menge bereits retourniert oder abgelehnt
	bool C05_OutOfTrade			(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const; //5	Außer Handel	Artikel ist Außer Handel
	bool C06_BlockedForReturns	(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const; //6	Retouren - Sperre	Artikel ist für Retouren gesperrt
	bool C07_BlockedBySales		(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const; //7	Vertriebs - Sperre	Artikel ist fuer den Vertrieb gesperrt
	bool C08_ManufacturerRecall	(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const; //8	Hersteller - Rueckruf	Artikel mit Hersteller - Rueckruf
	bool C09_BatchRecall		(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const; //9	Chargen - Rueckruf	Artikel mit Chargenrueckruf fuer alle Chargen
	bool C10_DeadlineGUG		(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const;	//10	Rueckgabefrist GÜG	Rueckgabefrist fuer meldepflichtige Artikel(GÜG) ueberschritten
	bool C11_DeadlineNarc		(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const;	//11	Rueckgabefrist BTM	Reuckgabefrist fuer BTM - Artikel ueberschritten
	bool C12_DeadlineColdchain	(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const;	//12	Rueckgabefrist KK	Rueckgabefrist fuer KK - Artikel ueberschritten
	bool C13_DeadlineCold08		(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const;	//13	Rueckgabefrist K8	Rueckgabefrist fuer K8 - Artikel ueberschritten
	bool C14_DeadlineCold20		(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const;	//14	Rueckgabefrist K20	Rueckgabefrist fuer K20 - Artikel ueberschritten
	bool C15_DeadlineReturns	(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const;	//15	Rueckgabefrist Retouren	Allgemeine Rueckgabefrist ueberschritten
	bool C16_GUGArticle			(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const; //16	GÜG - Artikel	Artikel ist meldepflichtig(GÜG)
	bool C17_NarcArticle		(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const; //17	BTM - Artikel	Artikel ist BTM
	bool C18_ColdchainArticle	(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const; //18	KK - Artikel	Artikel ist Kuehlartikel(KK)
	bool C19_Cold08Article		(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const; //19	K8 - Artikel	Artikel ist Kuehlartikel(K8)
	bool C20_Cold20Article		(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const; //20	K20 - Artikel	Artikel ist Kuehlartikel(K20)
	bool C21_HighPriceArticle	(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const; //21	Hochpreis	Artikel ist Hochpreisartikel
	bool C22_CallbackOrderType	(const ReturnAnnouncementPosPtr pos, const pxArtBasePtr article) const; //22	Rücksprache Auftragsart	Rechnung zu Auftragsart mit Ruecksprache

	bool returnPeriodExceeded	(const ReturnAnnouncementPosPtr pos, const ReturnPeriodArticleTypeEnum& type) const;

	basar::Int16 determineWorkingDaysSinceDelivery(const basar::Int16& branchNo, const basar::Date& deliveryAdviceDate) const;

	document::DeliveryAdvicePtr findDeliveryAdvice(ReturnAnnouncementPosPtr pos) const;
	void insertPosition(const basar::VarString& accCheckResult, ReturnAnnouncementPosPtr pos);

	basar::Decimal											m_HighPriceLimit;
	IReturnRuleBookRepositoryPtr							m_ReturnRuleBookRepository;
	IReturnPeriodRepositoryPtr								m_ReturnPeriodRepository;
	ReturnAnnouncementPtr									m_ReturnAnnouncement;
	document::DeliveryAdviceRepositoryPtr					m_DeliveryAdviceRepository;
	workingdayscalendar::IWorkingdaysCalendarRepositoryPtr	m_WorkingdaysCalendarRepository;
	mutable document::DeliveryAdvicePtr						m_DeliveryAdvice;
	mutable basar::Int16									m_WorkingDaysSinceDelivery;
	pxSession*												m_Session;

};

typedef boost::shared_ptr<libcsc::returns::ReturnPositionCheckUC> ReturnPositionCheckUCPtr;

} // end namespace returns
} // end namespace libcsc

#endif // GUARD_LIBCSC_RETURNS_RETURN_POSITION_CHECK_UC_H

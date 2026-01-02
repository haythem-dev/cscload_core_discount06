#ifndef TOURASSIGNMENTUTIL_HPP
#define TOURASSIGNMENTUTIL_HPP

#include "tourinfo.hpp"

class pxArtBase;
class pxOrder;
class pxOrderItem;
class TourManager;

/*############################################################################################################################*/
/*                                       C L A S S                                                                            */
/*############################################################################################################################*/
class TourAssignmentUtil
{
    public:

        TourAssignmentUtil(	pxOrder* order );

        virtual						~TourAssignmentUtil();

		TourInfo					getNormalDeliveryTour(const nString& tourid, const short weekday = -1);

        int							assignTour();

        int							assignItemTour( pxOrderItem* item );

		bool						isDayNightMergeDeliveryFaster(pxOrderItem* item, short routingBranchNo);

        bool						changeToUrgentPickingIfNecessary();

        bool						isArticleDeliverable( pxArtBase* article );
		bool						isArticleDeliverableByArticleNo( const long articleno );

		bool						isArticleDeliverableForIBT(short ibtbranchno, pxArtBase* article);

        bool						isTourValid( const nString& tourid );
		bool						isTourValidForDate( const nString& tourid );

        bool						isTourValidForOrderClosure( const nString& tourid );

        const TourInfo&				getLastTourInfo();

        char						getPickingTypeForTour( const nString& tourid );

        TourInfo					getTourInformation( const long& orderno, const long& lineno, bool ibt = false );

        int							removeTourAssignments();

		void						removeIBTTourAssignment(pxOrderItem* item);

        int							resetItemTourAssignments( pxOrderItem* item );

        void						saveItemTourInformationFromOrder( const long& lineno );

        bool						specialTourPossible( pxArtBase* article );

        void						injectArticle( pxArtBase* article );
        void						injectDesiredTourId( const nString& tourid );
        void						injectIBTBranchNo( const short ibtbranchno );
        void						injectIBTTypeArticle( const short& ibttypearticle, const short& nlevelibttype = 0 );
        void						injectWeekday( const short weekday );
        void						injectOrderPosNo( const long& orderposno );
		void						injectNoCheckForTransitionTimesAndPickingDurations( const bool b = true );

        void						resetInjections();

        TourManager*				getTourManager();	// TODO need it public???

    private:

		bool						isArticleNarcoticOnly();
		bool						isArticleCoolChainOnly();
		bool						isArticleCoolBelow8Only();
		bool						isArticleCoolBelow20Only();

        TourManager*				getTourManager4CustomerRouting();

        void						setErrorMessage( const int errorno );

        bool						hasCustomerRouting();
        //int							assingCustomerRoutingTour( pxOrderItem* item );

		TourInfo					determineItemTour( pxOrderItem* item, bool avoidCustRouting = false );
		TourInfo					determineCustomerRoutingTour();

        pxOrder*					m_Order;

        TourManager*				m_TourManager;
        TourManager*				m_TourManager4CustomerRouting;

        TourInfo					m_LastTourInfo;

		TourInfo					m_TourInfoBTM;
		TourInfo					m_TourInfoKK;
		TourInfo					m_TourInfoK8;
		TourInfo					m_TourInfoK20;

        nString						m_ArgDesiredTourId;
        short						m_ArgWeekday;
        short						m_ArgIBTBranchNo;
        short						m_ArgIBTTypeArticle;
        pxArtBase*					m_ArgArticle;
        long						m_ArgOrderPosNo;
		short						m_ArgNLevelIBTType;
		bool						m_ArgNoCheckForTransitionTimesAndPickingDurations;
};

#endif // TOURASSIGNMENTUTIL_HPP

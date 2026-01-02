#include "shipmenttrackingordertopackagemapmakerbase.h"
#include "shipmenttrackingcurrentwhslinecontext.h"
#include "shipmenttracking/shipmenttrackingrequestprocessingcontext.h"
#include "shipmenttrackingpackageinformationsqlmapper.h"
#include "shipmenttrackingtotepositiontolinebuildermapper.h"

#include <boost/make_shared.hpp>
#include <util/loggingutils.h>
#include <string>       // std::string


namespace libcsc {
namespace shipmenttracking {

ShipmentTrackingOrderToPackageMapMakerBase::ShipmentTrackingOrderToPackageMapMakerBase(ShipmentTrackingRequestProcessingContextPtr context) :
    m_Context(context)
{
}


ShipmentTrackingOrderToPackageMapMakerBase::~ShipmentTrackingOrderToPackageMapMakerBase()
{
}

//----------------------------------------------------------------------------------
// Extract and Update Next Line Detail
//----------------------------------------------------------------------------------
void ShipmentTrackingOrderToPackageMapMakerBase::extractAndUpdateNextLineDetail(
    ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext
)
{
    METHODNAME_DEF(ShipmentTrackingOrderToPackageMapMakerBase, extractAndUpdateNextLineDetail);

    if (currentWhsLineContext.get() == NULL)
    {
        throw basar::Exception(basar::ExceptInfo(fun, "currentWhsLineContext is Null!", __FILE__, __LINE__), "");
    }

    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << currentWhsLineContext);

    if (m_Context->Filter.DetailsDesired)
    {
        // check if the WHS line was already attached to the whsPackageInfoBuilder, or if there is sibling of the current DKTSV line, splitted already to some previous tote:

        // 1st: try to get WHS line from current WHS tote if possible:
        if (currentWhsLineContext->getWhsPackageInfoBuilder().get() != NULL)
        {
            currentWhsLineContext->setLineDetailBuilder(
                currentWhsLineContext->getWhsPackageInfoBuilder()->getToteLineDetailBuilderForTotePosNr(
                    currentWhsLineContext->getTotePosNr()
                )
            );
        }

        // ------------
        // try to get registered lineDetaBuilder from another tote for a case, this CscOrderPos is splitted to more than one tote:
        if (currentWhsLineContext->getLineDetailBuilder().get() == NULL)
        {
            tryToGetAndRegisterToteSplittedLineDataBuilder(currentWhsLineContext);
        }
    }


    if (!m_Context->Filter.DetailsDesired && 
        currentWhsLineContext->getWhsPackageInfoBuilder().get() != NULL
        )
    {
        // just process the next inctruction line in: whsPackageInfoBuilder->mapFromWarehouseData(currentWhsLineContext);
        currentWhsLineContext->setIsFirstTotePositionLine(true); // == always try to update data
    }

    
    if (currentWhsLineContext->getLineDetailBuilder().get() != NULL)
    {
        // Let the ShipmentTrackingRepositoryBuilder process it, its redirections, etc.
        currentWhsLineContext->setIsFirstTotePositionLine(
            currentWhsLineContext->getWhsPackageInfoBuilder()->isFirstTotePositionNrOrHasNoLinesYet(currentWhsLineContext->getTotePosNr())
        );
    }
    else
    {
        // Extract new Line from Outbound PackageInfo and attach it to current WHS Tote.
        // Create the WHS Tote from the found Outbound PackageInfo as a template, it the WHS Tote doesn't exist yet

        ShipmentTrackingPackageInformationSQLMapperPtr outboundPackageInfoBuilderTemplate = getOutboundPackageInfoBuilderTemplate(currentWhsLineContext);
        if (outboundPackageInfoBuilderTemplate.get() == NULL)
        {
            // Don't throw, error is already reported. Just continue:
            return;
        }

        // ----------------------------------------
        // Create new Warehouse Tote == PackageInfo based on the outbound collected "template" tote if needed:
        if (currentWhsLineContext->getWhsPackageInfoBuilder().get() == NULL)
        {
            // Clone New Tote From Outbound Template
            // Create a shallow copy, but do also a shallow copy of the contained IbtInfo and DO NOT TAKE Lines in this step
            currentWhsLineContext->setWhsPackageInfoBuilder(
                outboundPackageInfoBuilderTemplate->createCloneWithTighlyConnectedDataButWithoutLinesAndRemoveFromTourIfEmpty()
            );
            
            //NOTE: ONLY FIRST LOCAL LINE must cause Tour Redirection update in ShipmentTrackingRepositoryBuilder! The IBT Lines does not influence the Redirection processed in ShipmentTrackingRepositoryBuilder.
            currentWhsLineContext->setIsFirstTotePositionLine(true);

            registerNewWhsPackageInfoBuilder(currentWhsLineContext);
        }

        // -------------------
        // Get machtching line based on articleNr and "steal 1 articleNr position" from the template if handling details:
        if (m_Context->Filter.DetailsDesired)
        {
            
            extractOneOutboundArticleLineAndRemoveFromTourIfEmpty(
                outboundPackageInfoBuilderTemplate,
                currentWhsLineContext
            );

            if (currentWhsLineContext->getLineDetailBuilder().get() != NULL)
            {
                currentWhsLineContext->getWhsPackageInfoBuilder()->addNewWarehouseLineDetailBuilder(currentWhsLineContext);

                // register the mapped WHS line:
                ShipmentTrackingTotePositionToLineBuilderMapperPtr totePosNoToLineBuilderMapper = m_Context->getOrCreateTotePositionToLineBuilderMapperForCscOrderNo(currentWhsLineContext->getCscOrderNo());
                totePosNoToLineBuilderMapper->addTotePositionLineBuildersPackageInfo(currentWhsLineContext->getTotePosNr(), currentWhsLineContext->getWhsPackageInfoBuilder());
            }
        }
    }

    // update it from the resultSet
    // integrate the line into the new map: m_WarehouseLineDetailMap
    currentWhsLineContext->getWhsPackageInfoBuilder()->mapFromWarehouseData(currentWhsLineContext);
}

//----------------------------------------------------------------------------------
// Try to get a registered lineDetaBuilder from another tote for a case, current CscOrderPos is splitted to more than one tote
//----------------------------------------------------------------------------------
void ShipmentTrackingOrderToPackageMapMakerBase::tryToGetAndRegisterToteSplittedLineDataBuilder(
    ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext
)
{
    METHODNAME_DEF(ShipmentTrackingOrderToPackageMapMakerBase, tryToGetAndRegisterToteSplittedLineDataBuilder);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    ShipmentTrackingTotePositionToLineBuilderMapperPtr totePosNoToLineBuilderMapper = m_Context->getTotePositionToLineBuilderMapperForCscOrderNo(currentWhsLineContext->getCscOrderNo());
    if (totePosNoToLineBuilderMapper.get() == NULL)
    {
        return; // no totePosNoToLineBuilderMapper available for the CscOderNo so --> quit here!
    }

    ShipmentTrackingPackageInformationSQLMapperPtr whsLineDetailsPackageInfoBuilder =
        totePosNoToLineBuilderMapper->getPackageInfoBuilderForTotePosition(
            currentWhsLineContext->getTotePosNr()
        );

    if (whsLineDetailsPackageInfoBuilder.get() == NULL)
    {
        return; // no whsLineDetailsPackageInfoBuilder available for the TotePosNo so --> quit here!
    }

    currentWhsLineContext->setLineDetailBuilder(
        whsLineDetailsPackageInfoBuilder->getToteLineDetailBuilderForTotePosNr(
            currentWhsLineContext->getTotePosNr()
        )
    );

    if (currentWhsLineContext->getLineDetailBuilder().get() == NULL)
    {
        // Don't throw, report and just continue:
        LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Unexpected! found whsLineDetailsPackageInfoBuilder: " << whsLineDetailsPackageInfoBuilder->getPackageInformation()->getWarehouseMapKey() << " for current WHS DB row's TotePosNr: " << currentWhsLineContext << ", BUT NO LineDetailBuilder!");
        return;
    }

    // double check:
    if (currentWhsLineContext->getLineDetailBuilder()->getLineDetail()->getArticleNr() != currentWhsLineContext->getArticleNr() ||
        currentWhsLineContext->getLineDetailBuilder()->getLineDetail()->getExpectedDeliveryQuantity() != currentWhsLineContext->getWhsOriginalQuantity()
        )
    {
        // Don't throw, report and just continue:
        LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Unexpected! Wrong splitted LineDetailBuilder found in totePosNoToLineBuilderMapper for current WHS DB row: " << currentWhsLineContext << ", AND: " << currentWhsLineContext->getLineDetailBuilder()->getLineDetail());

        // reset:
        currentWhsLineContext->setLineDetailBuilder(ShipmentTrackingLineDetailSQLMapperPtr());
    }
    else
    {
        if (currentWhsLineContext->getWhsPackageInfoBuilder().get() == NULL)
        {
            // create a clone of the owner tote of the splitted line, as if it was an Outbound Template PackageInfo:
            // Create a shallow copy, but do also a shallow copy of the contained IbtInfo and DO NOT TAKE Lines!
            
            // The called method links to the same Tour as the original:
            currentWhsLineContext->setWhsPackageInfoBuilder(whsLineDetailsPackageInfoBuilder->createCloneWithTighlyConnectedDataButWithoutLinesAndIbt());

            // clone IBT info:
            currentWhsLineContext->getWhsPackageInfoBuilder()->addIbtCloneFromOutboundData(*whsLineDetailsPackageInfoBuilder.get());
        }

        // Register the found shared lineDetailBuilder with current tote:
        currentWhsLineContext->getWhsPackageInfoBuilder()->resuseToteSplittedWarehouseLineDetailBuilder(currentWhsLineContext);
    }
}


} // end namespace shipmenttracking
} // end namespace libcsc


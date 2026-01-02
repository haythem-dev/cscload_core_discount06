#include "shipmenttrackinglinedetailsqlmapper.h"
#include "shipmenttrackingpackageinformationsqlmapper.h"
#include "shipmenttrackingbatchtototelinemapper.h"
#include "shipmenttrackingcurrentwhslinecontext.h"

#include <util/loggingutils.h>
#include <boost/make_shared.hpp>

namespace libcsc {
namespace shipmenttracking {


ShipmentTrackingLineDetailSQLMapper::ShipmentTrackingLineDetailSQLMapper(ShipmentTrackingLineDetailPtr lineDetail) :
    ShipmentTrackingLineDetailMapperBase(lineDetail)
{
}


ShipmentTrackingLineDetailSQLMapper::~ShipmentTrackingLineDetailSQLMapper()
{
}

//----------------------------------------------------------------------------------
// Mapping Data from Outbound Database
//----------------------------------------------------------------------------------
void ShipmentTrackingLineDetailSQLMapper::mapFromOutboundDataAndAddLineDetail(const basar::db::sql::ResultsetRef resultSet, ShipmentTrackingPackageInformationSQLMapper& ownerPackageInfoBuilder, bool isNarcotic)
{
    if (getLineDetail().get() == NULL)
    {
        throw basar::Exception(basar::ExceptInfo("ShipmentTrackingLineDetailSQLMapper::mapFromOutboundData()", "m_LineDetail is Null!", __FILE__, __LINE__), "");
    }

    if (resultSet.isNull())
    {
        throw basar::Exception(basar::ExceptInfo("ShipmentTrackingLineDetailSQLMapper::mapFromOutboundData()", "resultSet is Null!", __FILE__, __LINE__), "");
    }

    setOrderPosNo               (resultSet.getInt32("posnr"));                  // <- (a)kdauftragpos.posnr
    setIbtOrderPosNo            (resultSet.getInt32("ibtorderposno"));          // <- ibtresponse.ibtorderposno
    setExpectedDeliveryQuantity (resultSet.getInt32("expecteddeliveryquantity")); // <- NVL(ibtresponse.ibtconfirmedqty, (a)kdauftragpos.mengegeliefert) ~= (a)kdauftragpos.mengebestaetigt + (a)kdauftragpos.mengenatra /or/ dktsv.tsv_kop_omenge

    setArticleNr                (resultSet.getInt32("artikel_nr"));             // <- (a)kdauftragpos.artikel_nr (== dktsv.tsv_kop_pzn) -> used for JOINing DKTSV lines
    setArticleCode              (resultSet.getString("article_code"));          // <- articlecodes.article_code -> based on: (a)kdauftragpos.artikel_nr /  dktsv.tsv_kop_pzn -> articlecodes.article_code  (where c.articleno = t.tsv_kop_pzn AND c.preferred_flag = 1)
    setArticleName              (resultSet.getString("artikel_name"));          // <- artikelzentral.artikel_name / dktsv.tsv_kop_abez
    setIsNarcotic               (isNarcotic);                                   // <- bitand(artikelzentral.etartklasse1, 512) = 512 / dktsv.tsv_vsw_btm 'J'/'N'

    // Add new line to the result structure:
    m_OutboundPackageLineColectionIterator = addCurrentLineDetailToOwnerPackage(ownerPackageInfoBuilder);
}

ShipmentTrackingLineDetailCollection::iterator ShipmentTrackingLineDetailSQLMapper::addCurrentLineDetailToOwnerPackage(ShipmentTrackingPackageInformationSQLMapper& ownerPackageInfoBuilder)
{
    ShipmentTrackingLineDetailCollection::iterator packageLineCollectionIter = ownerPackageInfoBuilder.addLineDetail(getLineDetail());
    setOwnerPackageInfo(ownerPackageInfoBuilder.getPackageInformation());

    return packageLineCollectionIter;
}

//----------------------------------------------------------------------------------
// Warehouse Data Mapping Helpers
//----------------------------------------------------------------------------------
void ShipmentTrackingLineDetailSQLMapper::removeLineDetailFromOutboundCollection(ShipmentTrackingPackageInformationSQLMapper& ownerPackageInfoBuilder)
{
    // Remove line from the Outbound result structure -> just to be moved (added) to the Warehouse result structure:
    m_OutboundPackageLineColectionIterator = ownerPackageInfoBuilder.removeLineDetailFromList(m_OutboundPackageLineColectionIterator);
    setOwnerPackageInfo(ShipmentTrackingPackageInformationPtr());
}

void ShipmentTrackingLineDetailSQLMapper::addExtractedOutboundLineToWarehouseTote(ShipmentTrackingPackageInformationSQLMapper& ownerPackageInfoBuilder)
{
    addCurrentLineDetailToOwnerPackage(ownerPackageInfoBuilder);
}

void ShipmentTrackingLineDetailSQLMapper::createNewLineDetailCloneFromOutboundDataAndAttachToPackageInfo(ShipmentTrackingPackageInformationSQLMapper& ownerPackageInfoBuilder)
{
    METHODNAME_DEF(ShipmentTrackingLineDetailSQLMapper, createNewLineDetailCloneFromOutboundDataAndAttachToPackageInfo);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    // create a copy and switch to it
    ShipmentTrackingLineDetailPtr previousLineDetail = getLineDetail();

    ShipmentTrackingLineDetailPtr lineDetail = boost::make_shared<ShipmentTrackingLineDetail>(previousLineDetail->getWhsToteMapKeyToOrderPositionSplitSiblingLines());
    switchToOtherLineBatch(lineDetail);

    fillCloneFromOutboundData(*previousLineDetail.get());

    addCurrentLineDetailToOwnerPackage(ownerPackageInfoBuilder);
}

void ShipmentTrackingLineDetailSQLMapper::fillCloneFromOutboundData(const ShipmentTrackingLineDetail& originalLineDetail)
{
    setOrderPosNo               (originalLineDetail.getOrderPosNo());
    setIbtOrderPosNo            (originalLineDetail.getIbtOrderPosNo());
    setExpectedDeliveryQuantity (originalLineDetail.getExpectedDeliveryQuantity());
    setArticleNr                (originalLineDetail.getArticleNr());
    setArticleCode              (originalLineDetail.getArticleCode());
    setArticleName              (originalLineDetail.getArticleName());
    setIsNarcotic               (originalLineDetail.getIsNarcotic());
}

//----------------------------------------------------------------------------------
// Mapping Data from Warehouse Database
//----------------------------------------------------------------------------------
void ShipmentTrackingLineDetailSQLMapper::mapFromWarehouseData(ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext, ShipmentTrackingPackageInformationSQLMapper& ownerPackageInfoBuilder)
{
    METHODNAME_DEF(ShipmentTrackingLineDetailSQLMapper, mapFromWarehouseData);
    BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun);

    if (getLineDetail().get() == NULL)
    {
        throw basar::Exception(basar::ExceptInfo(fun, "m_LineDetail is Null!", __FILE__, __LINE__), "");
    }

    if (currentWhsLineContext.get() == NULL)
    {
        throw basar::Exception(basar::ExceptInfo(fun, "currentWhsLineContext is Null!", __FILE__, __LINE__), "");
    }


    // implementing Batch Splitting and integrating:

    basar::VarString batch = currentWhsLineContext->getResultSet().getString("tsv_kop_charge");             // <- dktsv.tsv_kop_charge  -  Chargen-Nummer


    ShipmentTrackingBatchToToteLineMapperStrMap::iterator previousBatchToToteLineMapperIter = m_WhsBatchToBatchToToteLineMapperMap.find(batch);
    ShipmentTrackingBatchToToteLineMapperPtr batchToToteLineMapper;
    if (previousBatchToToteLineMapperIter != m_WhsBatchToBatchToToteLineMapperMap.end())
    {
        batchToToteLineMapper = previousBatchToToteLineMapperIter->second;
    }

    std::string ownersWhsMapKey = ownerPackageInfoBuilder.getPackageInformation()->getWarehouseMapKey();
    bool hasWhsData = getLineDetail()->hasWarehouseData();

    if (hasWhsData)
    {
        if (getLineDetail()->getBatch() == batch &&
            getLineDetail()->getWarehouseToteMapKey() == ownersWhsMapKey
            )
        {
            // same batch and WhsMapKey is already set -> just let update it below....
        }
        else
        {
            ShipmentTrackingLineDetailPtr lineDetailToSwitchTo;
            if (batchToToteLineMapper.get() != NULL)
            {
                lineDetailToSwitchTo = batchToToteLineMapper->getLineDetailForWhsMapKey(ownersWhsMapKey);
            }

            if (lineDetailToSwitchTo.get() != NULL)
            {
                // switch to the line and just let update it below....
                switchToOtherLineBatch(lineDetailToSwitchTo);
            }
            else
            {
                // create a copy and switch to it
                hasWhsData = false;

                createNewLineDetailCloneFromOutboundDataAndAttachToPackageInfo(ownerPackageInfoBuilder);
            }
        }
    }


    // do update or fill now:
    ShipmentTrackingLineDetailPtr currentLineDetailCache = getLineDetail();

    basar::Int32 confirmedDeliveryQty = currentWhsLineContext->getResultSet().getInt32("tsv_kop_meng");     // <- dktsv.tsv_kop_meng    -> NOTE: this could be different to Quantity (mengebestaetigt) if changed during picking!
    if (hasWhsData)
    {
        // Update:
        confirmedDeliveryQty += currentLineDetailCache->getConfirmedDeliveryQuantity();
        setConfirmedDeliveryQuantity(confirmedDeliveryQty);                     // <- dktsv.tsv_kop_meng    -> NOTE: this could be different to Quantity (mengebestaetigt) if changed during picking!
    }
    else
    {
        // filling new line from WHS DB data:
        setTotePosNo                (currentWhsLineContext->getTotePosNr());    // <- dktsv.tsv_pos
        setConfirmedDeliveryQuantity(confirmedDeliveryQty);                     // <- dktsv.tsv_kop_meng    -> NOTE: this could be different to Quantity (mengebestaetigt) if changed during picking!
        setBatch                    (batch);                                    // <- dktsv.tsv_kop_charge  -  Chargen-Nummer

        setHasWarehouseData         (true);

        // ----------------
        // store it in map: m_WhsBatchToBatchToToteLineMapperMap
        if (batchToToteLineMapper.get() == NULL)
        {
            // Create new batchToToteLineMapper:
            batchToToteLineMapper = boost::make_shared<ShipmentTrackingBatchToToteLineMapper>();
            m_WhsBatchToBatchToToteLineMapperMap[batch] = batchToToteLineMapper;
        }

        batchToToteLineMapper->addLineDetailForWhsMapKey(ownersWhsMapKey, currentLineDetailCache);

        // -----------------------
        // store it in shared map: m_LineDetail->m_WhsToteMapKeyToOrderPositionSplitSiblingLines
        ShipmentTrackingLineDetailWeakStrToClollectionMapPtr whsToteMapKeyToOrderPositionSplitSiblingLines = currentLineDetailCache->getWhsToteMapKeyToOrderPositionSplitSiblingLines();

        ShipmentTrackingLineDetailWeakCollectionPtr lineDetailWeakCollection;
        ShipmentTrackingLineDetailWeakStrToClollectionMap::iterator lineDetailWeakCollectionIter = whsToteMapKeyToOrderPositionSplitSiblingLines->find(ownersWhsMapKey);
        if (lineDetailWeakCollectionIter != whsToteMapKeyToOrderPositionSplitSiblingLines->end())
        {
            lineDetailWeakCollection = lineDetailWeakCollectionIter->second;
        }
        else
        {
            lineDetailWeakCollection = boost::make_shared<ShipmentTrackingLineDetailWeakCollection>();
            (*whsToteMapKeyToOrderPositionSplitSiblingLines)[ownersWhsMapKey] = lineDetailWeakCollection;
        }

        lineDetailWeakCollection->push_back(currentLineDetailCache);
    }
}


} // end namespace shipmenttracking
} // end namespace libcsc

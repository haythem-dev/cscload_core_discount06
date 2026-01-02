#include "msv3orderlabelprocessor.h"
#include "pxcstot.hpp"
#include "pxxmit.hpp"
#include "pxcstbas.hpp"
#include "pxmsv3order.hpp"
#include <pxrecord.h>

MSV3OrderLabelProcessor::MSV3OrderLabelProcessor() :
	m_MaxNumberOfOrderLabels(0),
	m_DefaultOrderLabel(),
	m_UsedOrderLabels(),
	m_UsageOfCustomOrderLabelsAllowed(false)
{
}

MSV3OrderLabelProcessor::~MSV3OrderLabelProcessor()
{
}

void MSV3OrderLabelProcessor::init(pxOrderTransmit* xmit, const basar::VarString& ordertype, const long orderperiodid)
{
	m_MaxNumberOfOrderLabels = 0;
	m_DefaultOrderLabel = "";
	m_UsedOrderLabels.clear();
	m_UsageOfCustomOrderLabelsAllowed = false;

	pxCustBase* customer = xmit->Customer();

	pxCustOrderType* customerOrderType = new pxCustOrderType(xmit);
	if (0 == customerOrderType->getCustomerOrderType(customer->FilialNr(), customer->IDFNr(), ordertype.c_str()))
	{
		m_DefaultOrderLabel = customerOrderType->OrderIdentificatio()();
		m_DefaultOrderLabel.trim(basar::VarString::FIRST_END);
		m_MaxNumberOfOrderLabels = customerOrderType->OrderLabelCount();
		m_UsageOfCustomOrderLabelsAllowed = customerOrderType->isUsageOfCustomOrderLabelsAllowed();

		pxMSV3OrderList* msv3orderlist = new pxMSV3OrderList(xmit);
		msv3orderlist->SelectMSV3OrderLabel(customer->FilialNr(), customer->IDFNr(), customerOrderType->KdAuftragArt(), orderperiodid);

		// check if orderlabel has already been used and count used custom order labels
		if (msv3orderlist->Entries() > 0)
		{
			pxMSV3Order* msv3order = NULL;
			pxMSV3OrderListIter iter = pxMSV3OrderListIter(*msv3orderlist);
			while( (msv3order = (pxMSV3Order*) ++iter) != NULL )
			{
				basar::VarString usedLabel = msv3order->OrderLabel()();
				usedLabel.trim(basar::VarString::FIRST_END);
				m_UsedOrderLabels.insert(usedLabel);
			}
		}
	}
}

const basar::VarString MSV3OrderLabelProcessor::processLabel(const basar::VarString& label)
{
	// default order label always allowed
	if (label == m_DefaultOrderLabel)
	{
		return label;
	}
	
	// use default orderlabel if custom orderlabels are not allowed
	if (false == m_UsageOfCustomOrderLabelsAllowed)
	{
		return m_DefaultOrderLabel;
	}

	// if orderlabel has already been used -> OK, use custom orderlabel	
	if (m_UsedOrderLabels.find(label) != m_UsedOrderLabels.end())
	{
		return label;
	}
	
	// if orderlabel has not been used -> check if max allowed custom orderlabels is reached
	if (m_UsedOrderLabels.size() < m_MaxNumberOfOrderLabels)
	{
		m_UsedOrderLabels.insert(label);
		return label;
	}

	// otherwise return default label
	return m_DefaultOrderLabel;
}

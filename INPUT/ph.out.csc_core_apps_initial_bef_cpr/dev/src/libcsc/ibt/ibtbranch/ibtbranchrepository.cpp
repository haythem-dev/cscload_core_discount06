#include "ibtbranchrepository.h"
#include <persistence/iaccessor.h>
#include <logger/loggerpool.h>
#include <libbasarcmnutil_exceptions.h>
#include "ibtbranchsettingsqlmapper.h"
#include "ibtbranchsetting.h"
#include "iibtbranchsettingcollection.h"
#include "ibtbranchsettingcollection.h"
#include "ibtbranchsettingcollectionptr.h"
#include <boost/make_shared.hpp>

namespace libcsc {
namespace ibt {

IbtBranchRepository::IbtBranchRepository()
{
}

IbtBranchRepository::~IbtBranchRepository()
{
	m_BranchSettingAccessor.reset();
}

void IbtBranchRepository::injectBranchSettingAccessor( persistence::IAccessorPtr accessor )
{
	m_BranchSettingAccessor = accessor;
}


IIbtBranchSettingPtr IbtBranchRepository::findIbtBranchSetting(const basar::Int16& branchNo, const basar::Int16& ibtBranchNo)
{
	IbtBranchSettingPtr ibtBranchSetting;

	try
	{
		basar::db::sql::ResultsetRef resultset = m_BranchSettingAccessor->select(IbtBranchSettingSqlMapper::getSingleSelectSQL(branchNo, ibtBranchNo));
		if( resultset.next() )
		{
			ibtBranchSetting = boost::make_shared<IbtBranchSetting>();
			IbtBranchSettingSqlMapper mapper(ibtBranchSetting, resultset );
			mapper.map();
		}
	}
	catch( const basar::Exception & e )
	{
		BLOG_ERROR(LoggerPool::getLoggerSession(), e.what());
		throw;
	}
	return ibtBranchSetting;
}

IIbtBranchSettingCollectionPtr IbtBranchRepository::findIbtBranchSettings(const basar::Int16& branchNo)
{
	IbtBranchSettingCollectionPtr coll = boost::make_shared<IbtBranchSettingCollection>();

	try
	{
		basar::db::sql::ResultsetRef resultset = m_BranchSettingAccessor->select(IbtBranchSettingSqlMapper::getBranchSelectSQL(branchNo));
		while (resultset.next())
		{
			IbtBranchSettingPtr ibtBranchSetting = boost::make_shared<IbtBranchSetting>();
			IbtBranchSettingSqlMapper mapper(ibtBranchSetting, resultset);
			mapper.map();
			coll->push_back(ibtBranchSetting);
		}
	}
	catch (const basar::Exception & e)
	{
		BLOG_ERROR(LoggerPool::getLoggerSession(), e.what());
		throw;
	}
	return coll;
}


} // end namespace ibt
} // end namespace libcsc

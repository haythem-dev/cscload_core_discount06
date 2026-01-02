#include "ordertypeflagtypemapperbase.h"
#include "ordertypeflagtype.h"
#include <logger/loggerpool.h>

namespace libcsc
{
	namespace cscordertype
	{
		OrderTypeFlagTypeMapperBase::OrderTypeFlagTypeMapperBase(OrderTypeFlagTypePtr orderTypeFlagType)
			: m_OrderTypeFlagType(orderTypeFlagType)
		{
		}

		OrderTypeFlagTypeMapperBase::~OrderTypeFlagTypeMapperBase()
		{
		}

		void OrderTypeFlagTypeMapperBase::map()
		{
			doMap();
		}

		void OrderTypeFlagTypeMapperBase::setOrderType(const basar::VarString& orderType)
		{
			m_OrderTypeFlagType->m_OrderType = orderType;
			m_OrderTypeFlagType->m_OrderType.setClean();
		}

		void OrderTypeFlagTypeMapperBase::setName(const basar::VarString& name)
		{
			m_OrderTypeFlagType->m_Name = name;
			m_OrderTypeFlagType->m_Name.setClean();
		}

		void OrderTypeFlagTypeMapperBase::setOrderTypeFlag(const basar::Int16 orderTypeFlag)
		{
			m_OrderTypeFlagType->m_OrderTypeFlag = orderTypeFlag;
			m_OrderTypeFlagType->m_OrderTypeFlag.setClean();
		}

		void OrderTypeFlagTypeMapperBase::setOrderTypeFlagType(const basar::Int16 orderTypeFlagType)
		{
			m_OrderTypeFlagType->m_OrderTypeFlagType = static_cast<OrderTypeFlagTypeEnum>(orderTypeFlagType);
			//m_OrderTypeFlagType->m_OrderTypeFlagType.setClean();
		}

		void OrderTypeFlagTypeMapperBase::setDescription(const basar::VarString& description)
		{
			m_OrderTypeFlagType->m_Description = description;
			m_OrderTypeFlagType->m_Description.setClean();
		}

		void OrderTypeFlagTypeMapperBase::setIndexDKAUA(const basar::Int16 indexDKAUA)
		{
			m_OrderTypeFlagType->m_IndexDKAUA = indexDKAUA;
			m_OrderTypeFlagType->m_IndexDKAUA.setClean();
		}

	} // end namespace cscordertype
} // end namespace libcsc

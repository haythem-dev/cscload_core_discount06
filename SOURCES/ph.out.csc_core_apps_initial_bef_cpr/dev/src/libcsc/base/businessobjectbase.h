#ifndef GUARD_LIBCSC_BASE_BUSINESSOBJECTBASE_H
#define GUARD_LIBCSC_BASE_BUSINESSOBJECTBASE_H

#include <datatypes/propertycollection.h>

namespace libcsc {
namespace base {

class BusinessObjectBase
{
public:
	BusinessObjectBase() {}
	virtual ~BusinessObjectBase() {}

	virtual bool containsUnset() const { return m_PropertyCollection.containsUnset(); }
	virtual bool containsClean() const { return m_PropertyCollection.containsClean(); }
	virtual bool containsDirty() const { return m_PropertyCollection.containsDirty(); }

	virtual bool isUnset() const { return m_PropertyCollection.isUnset(); }
	virtual bool isClean() const { return m_PropertyCollection.isClean(); }
	virtual bool isDirty() const { return m_PropertyCollection.isDirty(); }

protected:
	PropertyCollection m_PropertyCollection;
};

} // end namespace base
} // end namespace libcsc

#endif // GUARD_LIBCSC_BASE_BUSINESSOBJECTBASE_H

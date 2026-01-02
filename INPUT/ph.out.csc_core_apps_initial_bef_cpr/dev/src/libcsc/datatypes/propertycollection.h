#ifndef GUARD_LIBCSC_PROPERTY_COLLECTION_H
#define GUARD_LIBCSC_PROPERTY_COLLECTION_H

#include <datatypes/propertystate.h>
#include <set>

namespace libcsc
{
class PropertyCollection
{
public:
	PropertyCollection();
	~PropertyCollection();

	bool operator==( const PropertyCollection & rhs ) const;

	void add( PropertyState & prop );
	void clear();

	bool containsUnset() const;
	bool containsClean() const;
	bool containsDirty() const;

	bool isUnset() const;
	bool isClean() const;
	bool isDirty() const;

	void setUnset();
	void setClean();
	//void setDirty(); is this really needed???

private:
	bool containsState( const PropertyStateEnum state ) const;
	bool containsOnlyState( const PropertyStateEnum state ) const;
	void setState( const PropertyStateEnum state );

	typedef std::set<PropertyState *> InnerCollection;
	InnerCollection		m_Collection;
};

} // end namespace libcsc

#endif // GUARD_LIBCSC_PROPERTY_STATE_COLLECTION_H

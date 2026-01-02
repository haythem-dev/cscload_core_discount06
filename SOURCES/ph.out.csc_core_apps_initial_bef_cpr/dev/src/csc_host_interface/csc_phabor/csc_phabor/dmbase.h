#ifndef GUARD_DOMMOD_DMBASE_H
#define GUARD_DOMMOD_DMBASE_H

//-----------------------------------------------------------------------------------------------------------------------------------//
// include section
//-----------------------------------------------------------------------------------------------------------------------------------//
#include <componentinitializeexception.h>

//-----------------------------------------------------------------------------------------------------------------------------------//
// class declaration section
//-----------------------------------------------------------------------------------------------------------------------------------//
namespace domMod
{

template <class T, class Derived>
class DMBase
{
public:
	DMBase() : m_initialized( false )
	{
	}

	virtual ~DMBase()
	{
		if( m_initialized )
		{
			basar::VarString msg( Derived::getClassName() );
			msg.append( ": shutdown() not called!" );
			throw ::util::ComponentInitializeException( basar::ExceptInfo( msg, "DM init()/shutdown()", __FILE__, __LINE__ ) );
		}
	}

	void init( const T params )
	{
		if( m_initialized )
		{
			basar::VarString msg( Derived::getClassName() );
			msg.append( ": init() multiple times called!" );
			throw ::util::ComponentInitializeException( basar::ExceptInfo( msg, "DM init()/shutdown()", __FILE__, __LINE__ ) );
		}

		doInit( params );
		m_initialized = true;
	}

	void shutdown()
	{
		if( !m_initialized )
		{
			basar::VarString msg( Derived::getClassName() );
			msg.append( ": init() not called or shutdown() multiple times called!" );
			throw ::util::ComponentInitializeException( basar::ExceptInfo( msg, "DM init()/shutdown()", __FILE__, __LINE__ ) );
		}

		doShutdown();
		m_initialized = false;
	}

	inline bool isInitialized() const 
    {
        return m_initialized;
    }

protected:
	virtual void doInit( const T params ) = 0;
	virtual void doShutdown() = 0;

private:
	bool			m_initialized;
};

} // end namespace domMod

#endif // GUARD_DOMMOD_DMBASE_H

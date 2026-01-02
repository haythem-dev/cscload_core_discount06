//----------------------------------------------------------------------------
/*! \file UnittestTableEntry.h
*  \brief Helper for creation of table entries only required to run unit tests.
*  \author	Stefan Suffa
*  \date 05.03.2008
*/
//----------------------------------------------------------------------------

#ifndef GUARD_LIBTESTUTILS_UNITTEST_TABLEENTRY_H
#define GUARD_LIBTESTUTILS_UNITTEST_TABLEENTRY_H

namespace basar
{
	namespace db
	{
		namespace sql
		{
			class ConnectionRef;
		}
	}
}


namespace ivc
{
	namespace test
	{
		namespace ivcdm
		{
			namespace utils
			{
				class UnittestTableEntry
				{
				public:
					/*!
					\brief Default constructor.
					*/
					UnittestTableEntry();

					/*!
					\brief Destructor.
					*/
					virtual ~UnittestTableEntry();

					/*!
					\brief Create an entry for branch number 90 in rfiliale.

					Deletes all entries from rfiliale (if a transaction is running) and
					inserts a single entry for the unittest branch 90.
					*/
					static void prepareRfiliale(basar::db::sql::ConnectionRef connection //!< Reference to the sql connection instance to be used.
						);
				protected:
				private:
					/*!
					\brief Copy constructor.
					*/
					UnittestTableEntry(const UnittestTableEntry& unittestTableEntry);

					/*!
					\brief Assignment operator.
					*/
					UnittestTableEntry operator& (const UnittestTableEntry& unittestTableEntry);
				};
			}
		}
	}
}

#endif

#ifndef GUARD_LIBCSC_STOCKBOOKING_LONGTERMLACK_MAPPER_BASE_H
#define GUARD_LIBCSC_STOCKBOOKING_LONGTERMLACK_MAPPER_BASE_H

#include <libbasar_definitions.h>

namespace libcsc
{
namespace stockbooking
{
    class LongTermLackMapperBase
    {
        public:
            LongTermLackMapperBase( const basar::Int32 articleNo );
	        void map();

        protected:
	        virtual ~LongTermLackMapperBase();
	        virtual void doMap() = 0;
        
        private:
            LongTermLackMapperBase(const LongTermLackMapperBase&);
            LongTermLackMapperBase& operator=(const LongTermLackMapperBase&);

            //////////////////////////////////////////
            // member variables
            //////////////////////////////////////////
            const basar::Int32 m_ArticleNo;
    };

}
}

#endif

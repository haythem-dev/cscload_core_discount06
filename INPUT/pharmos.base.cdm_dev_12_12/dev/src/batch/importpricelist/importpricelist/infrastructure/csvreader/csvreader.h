//--------------------------------------------------------------------------------------------------//
/*! \brief
 *  \author     Michael Helmich
 *  \date       27.08.2021
 *  \version    00.00.00.01
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_IMPORTPRICELIST_INFRASTRUCTURE_CSVREADER_CSVREADER_H
#define GUARD_IMPORTPRICELIST_INFRASTRUCTURE_CSVREADER_CSVREADER_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <fstream>
#include <list>
#include <string>

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace importpricelist
{
    namespace infrastructure
    {
        namespace csvReader
        {
            class CsvReader
            {
                public:
					CsvReader();
					~CsvReader();

					void openFile(const std::string& fileName);
					void closeFile();

					void readNextRecord(std::list<std::string>& valueList);

					bool good() const;
					bool eof() const;

                private:
					std::string m_fileName;
					std::ifstream m_inputStream;
            };
        }
    }
}

#endif

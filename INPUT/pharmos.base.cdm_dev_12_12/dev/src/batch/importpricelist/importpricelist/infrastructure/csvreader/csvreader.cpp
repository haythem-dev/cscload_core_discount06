//--------------------------------------------------------------------------------------------------//
/*! \brief
 *  \author     Michael Helmich
 *  \date       27.08.2021
 *  \version    00.00.00.01
 */
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/tokenizer.hpp>

#include "csvreader.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace importpricelist
{
    namespace infrastructure
    {
        namespace csvReader
        {
            CsvReader::CsvReader()
            {
            }

			CsvReader::~CsvReader()
			{
			}

			void CsvReader::openFile(const std::string& fileName)
			{
				m_fileName = fileName;
				m_inputStream.open(fileName.c_str());
			}

			void CsvReader::closeFile()
			{
				m_inputStream.close();
			}

			void CsvReader::readNextRecord(std::list<std::string>& valueList)
			{
				std::string line;
				boost::escaped_list_separator<char> sep('\\', ';');

				valueList.clear();

				if (std::getline(m_inputStream, line)) 
				{
					boost::tokenizer<boost::escaped_list_separator<char> > tok(line, sep);
					for (boost::tokenizer<boost::escaped_list_separator<char> >::iterator beg = tok.begin(); beg != tok.end(); ++beg) 
					{
						valueList.push_back(*beg);
					}
				}
			}

			bool CsvReader::good() const
			{
				return m_inputStream.good();
			}

			bool CsvReader::eof() const
			{
				return m_inputStream.eof();
			}
		} // end namespace csvReader
    } // end namespace infrastructure
} // end namespace ibtrelevantcalculator

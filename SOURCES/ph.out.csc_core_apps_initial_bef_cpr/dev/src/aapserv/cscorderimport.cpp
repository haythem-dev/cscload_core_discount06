#include "cscorderimport.h"
#include "ppgeneric.h"
#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxcstbas.hpp"
#include "pxorder.hpp"
#include "pxtxtdoc.hpp"
#include "pxartdsp.hpp"
#include <pxbase/pxconstants.hpp>
#include "texte.h"
#include "artsel.h"
#include "aasrv.h"
#include <stdio.h>
#include <initializer_list>

#include <parameter/componentmanager/parametercomponentmanager.h>
#include <parameter/csvorderimport/icsvorderimportrepository.h>
#include <parameter/csvorderimport/cscorderimportcsvformats.h>
#include <parameter/csvorderimport/icscorderimportfields.h>
#include <parameter/csvorderimport/icscorderimportcsvcolumns.h>

#define FIELDNAME_BRANCHNO "branchno"
#define FIELDNAME_CUSTOMERNO "customerno"
#define FIELDNAME_ORDERTYPE "ordertype"
#define FIELDNAME_PICKINGTYPE "pickingtype"
#define FIELDNAME_BOOKINGTYPE "bookingtype"
#define FIELDNAME_ORDERREMARK "orderremark"
#define FIELDNAME_ARTICLECODE "articlecode"
#define FIELDNAME_ORDERQTY "orderqty"
#define FIELDNAME_POSREMARK "posremark"
#define FIELDNAME_PHARMACYPURCHASEPRICE "pharmacypurchaseprice"
#define FIELDNAME_GROSSPURCHASEPRICE "grosspurchaseprice"
#define FIELDNAME_PORTO "porto"
#define FIELDNAME_ARTICLEDESCRIPTION "articledescription"
#define FIELDNAME_DISCOUTPRECENTAGE "discountpercentage"
#define FIELDNAME_VATLEVEL "vatlevel"
#define FIELDNAME_HEADREMARK "headremark"
#define FIELDNAME_DATEVALUTA "datevaluta"
#define FIELDNAME_DATEDELAYEDDELIVERY "datedelayeddelivery"
#define FIELDNAME_ORDERLABEL "orderlabel"
#define FIELDNAME_RESTDELIVARY "restdelivery"
#define FIELDNAME_SERVICETYPE "servicetype"
#define FIELDNAME_SERVICE "service"

const std::string empty_str;


extern "C" {
#include"allg.h"
    /* PROTOTYPES */
    int AatartSel_NoByCode(struct ARTAESEL *d, char *error_msg);
    bool AatartSel_service_type_exists(const char* service_type, char* error_msg);
    bool AatartSel_service_number_exists_and_valid(const char* service_no, const char* service_type, char* result, char* error_msg);
    bool AatartSel_taxlevel_exists(const short taxlevel, char* error_msg);
}

// constants
const int CSV_MAX_COLUMN_SIZE = 8192;

// utils functions
void TrimStr(char* str, int lenStr = -1);
void splitStr(std::vector<std::string>& result, std::string& s, char delim);
void toUpperStr(std::string& str);
std::string ExtractDirectory(const std::string& path);
void CsvRowToLine(std::vector<std::string>& csvRow, std::string& outLine, char csvDelimiter);

// CSCOrderImport ///////////////////////////////////////////////////////////////////

CSCOrderImport::CSCOrderImport(pxSession &ps) : curMessagesMap( &OrdImpMessagesMapDE )
{
    psession = &ps;
    m_bWriteLog = true;
    m_bOrderOpen = false;
    m_bSwitchOrder = false;
    ordercount = 0;
    orderposcount = 0;
    orderposread = 0;
    totalposcount = 0;
    m_count = 0;
    csvDelimiter = ';';
    strcpy(reportCsvFileName, "");
}

CSCOrderImport::~CSCOrderImport()
{
}

int CSCOrderImport::GenerateOrders(const std::string& input, const std::string& output, const std::string& orgfile, const std::string& reportfile, int FormatID, const std::string& FormatName, const std::string& language)
{
    m_input = input;
    m_orgfile = orgfile;
    m_output = output;
    m_FormatID = FormatID;

    // default langage "DE"
    curMessagesMap = &OrdImpMessagesMapDE;
    // switch language if supported
    if (language != "DE")
    {
        curMessagesMap = &OrdImpMessagesMapEN;
    }

    if (OpenLogFile() != 0)
    {
        m_bWriteLog = false;
        return OrdImpRCReportFileFailed;
    }

    if (OpenFile() != 0)
    {
        CloseLogFile();
        return OrdImpRCInputFileFailed;
    }

    m_fieldtypes = psession->getParameterComponentManager()->getCSVOrderImportRepository()->findCSCOrderImportCSVFields();
    if (!GetFormat())
    {
        m_output.format(GetMessage(CMSG_ORDIMPORT_GETFORMAT_FAILURE).c_str(), m_FormatID, FormatName.c_str());
        WriteLogFile();
        CloseLogFile();
        CloseFile();
        return OrdImpRCFormatNotFound;
    }
    else
    {
        m_output.format(GetMessage(CMSG_ORDIMPORT_USED_FORMAT).c_str(), m_FormatID, FormatName.c_str());
        WriteLogFile();
    }
    strcpy(reportCsvFileName, reportfile.c_str());
    TrimStr(reportCsvFileName, -1);

    if (FetchOrders() > 0)
    {
        CloseFile();
        CloseLogFile();
        // export all orders/positions
        ExportOrders(false);
        return OrdImpRCCreateOrdersError;
    }
    CloseFile();

    if (!CreateOrders())
    {
        CloseLogFile();
        return OrdImpRCCreateOrdersError;
    }

    CloseLogFile();

    if (!m_bWriteLog) return OrdImpRCReportFileFailed;

    return OrdImpRCSuccess;
}

bool CSCOrderImport::ExportOrders(bool onlyFaulty)
{
    std::vector<std::string> curRow;
    std::string csvLine;
    size_t statusIdx = formatMaxPosition;
    bool firstLine = true;
    // generate report filename if empty
    if (strlen(reportCsvFileName) == 0)
    {
        sprintf(reportCsvFileName, "%sorderimport-%08i-%06i.csv", ExtractDirectory(m_input).c_str(), ppGGetDate(), ppGGetTime());
    }

    std::ofstream outputcsvfile;
    
    outputcsvfile.open(reportCsvFileName, std::ios_base::out);
    if (!outputcsvfile.is_open())
    {
        return false;
    }

    // export saved header
    if (headRows.size() > 0)
    {
        bool statusRemarkAdded = false;
        for (size_t i = 0; i < headRows.size(); i++)
        {
            // not an empty header row, so maybe the columns names row, so we can add status/remarks columns names
            if (!statusRemarkAdded && headRows[i].size() > 0)
            {
                statusRemarkAdded = true;
                headRows[i].resize(formatMaxPosition + 3);
                headRows[i][formatMaxPosition] = GetMessage(CMSG_ORDIMPORT_STATUS);
                headRows[i][formatMaxPosition+1] = GetMessage(CMSG_ORDIMPORT_REMARKS);
                headRows[i][formatMaxPosition+2] = GetMessage(CMSG_ORDIMPORT_ORDER_NR);
            }
            CsvRowToLine(headRows[i], csvLine, csvDelimiter);
            if (!firstLine)
            {
                outputcsvfile << std::endl;
            }
            outputcsvfile << csvLine;
            firstLine = false;
        }
    }
    
    // export orders/positions
    for (size_t j = 0; j < m_listOrders.size(); j++)
    {
        if (m_listOrders[j].listPositions.size() > 0)
        {
            for (size_t i = 0; i < m_listOrders[j].listPositions.size(); i++)
            {
                GetRow(j, i, curRow);
                if (!onlyFaulty || curRow[statusIdx] != "Ok")
                {
                    CsvRowToLine(curRow, csvLine, csvDelimiter);
                    if (!firstLine)
                    {
                        outputcsvfile << std::endl;
                    }
                    outputcsvfile << csvLine;
                    firstLine = false;
                }
            }
        }
        else
        {
            GetRow(j, 0, curRow);
            if (!onlyFaulty || curRow[statusIdx] != "Ok")
            {
                CsvRowToLine(curRow, csvLine, csvDelimiter);
                if (!firstLine)
                {
                    outputcsvfile << std::endl;
                }
                outputcsvfile << csvLine;
                firstLine = false;
            }
        }
    }

    outputcsvfile.close();
    return true;
}


bool CSCOrderImport::CsvGetNextRow(std::vector<std::string>& curRow, bool& emptyRow)
{
    char currField[CSV_MAX_COLUMN_SIZE] = "";
    bool newLine = false;
    bool OverSize = false;

    emptyRow = true;
    curRow.clear();
    if (isEOF)
        return false;
    while (CsvGetNextColumn(currField, CSV_MAX_COLUMN_SIZE-1, &newLine, &OverSize))
    {
        curRow.push_back(currField);
        if (emptyRow && currField[0] != 0)
        {
            emptyRow = false;
        }
        if (newLine)
        {
            break;
        }
    }

    return true;
}

const std::string& CSCOrderImport::GetMessage(OrdImpMessagesEnum messageID)
{
    std::map< OrdImpMessagesEnum, std::string >::iterator it;

    if ((it = curMessagesMap->find(messageID)) != curMessagesMap->end())
    {
        return it->second;
    }
    // try default german map if ID not found
    if ((it = OrdImpMessagesMapDE.find(messageID)) != OrdImpMessagesMapDE.end())
    {
        return it->second;
    }
    // else return empty
    return empty_str;
}


int CSCOrderImport::OpenFile()
{
    inputfile.open(m_input.c_str(), std::ios_base::in);
    if(inputfile.fail())
    {
        m_output = strerror(errno);
        WriteLogFile();
        return 1;
    }
    m_output = GetMessage(CMSG_ORDIMPORT_PROCESSING) + m_orgfile + "\n";
    WriteLogFile();
    isEOF = false;
    lastCharIsDelimiter = false;
    lastAvailableByte = false;
    lineCount = 0;
    currByte = 0;

    return 0;
}

bool CSCOrderImport::CsvGetNextColumn(char* currField, size_t maxOutSize, bool* newRow, bool* overLength)
{
    int fieldIter = 0;
    int inside_complex_field = 0;
    int currFieldCharIter = 0;
    int seriesOfQuotesLength = 0;
    int lastCharIsQuote = 0;
    int isEndOfFile = 0;
    int lastLenField = 0;
    bool overLengthMode = false;

    if (newRow != NULL) 
        *newRow = false;
    if (overLength != NULL)
        *overLength = false;

    for (;;) {
        char currChar = CsvGetNextByte();
        if (isEOF) {
            // reached end of file or last row contains less than expected columns
            if (!lastCharIsDelimiter && currFieldCharIter == 0 && fieldIter == 0)
            {
                return false;
            }
            //currChar = '\n';
            isEndOfFile = 1;
        }

        if (!isEndOfFile) {
            if (currChar == '\r')
            {
                continue;
            }
            if (currChar == '\"' && inside_complex_field == 0)
            {
                inside_complex_field = 1;
                lastCharIsQuote = 1;
                continue;
            }
            lastCharIsDelimiter = ((currChar == csvDelimiter) && inside_complex_field == 0);

            if (currChar == '\"' && inside_complex_field == 1 && lastCharIsQuote == 0 && currFieldCharIter == 0)
            {
                inside_complex_field = 0;
                currFieldCharIter++;
                lastCharIsQuote = 1;
                continue;
            }
            if (currFieldCharIter == 0 && !lastCharIsQuote)
            {
                if (currChar == '\"')
                {
                    inside_complex_field = 1;
                    lastCharIsQuote = 1;
                    continue;
                }
            }
            else if (currChar == '\"')
            {
                seriesOfQuotesLength++;
                inside_complex_field = (seriesOfQuotesLength % 2 == 0);
                if (inside_complex_field)
                {
                    currFieldCharIter--;
                }
            }
            else
            {
                seriesOfQuotesLength = 0;
            }
        }
        if (isEndOfFile || ((currChar == csvDelimiter || currChar == '\n') && !inside_complex_field))
        {
            if (lastCharIsQuote && currFieldCharIter > 0)
            {
                lastLenField = (currFieldCharIter - 1);
            }
            else
{
                lastLenField = currFieldCharIter;
            }
            lastCharIsQuote = 0;
            currField[lastLenField] = '\0';
            TrimStr(currField, lastLenField);

            if (currChar == '\n' || isEndOfFile)
            {
               lineCount++;
               if (newRow != NULL)
               {
                   *newRow = true;
               }
            }
            return true;
        }
        else 
        {
            if (!overLengthMode)
            {
                currField[currFieldCharIter] = currChar;
                currFieldCharIter++;
                // column buffer full ?
                if (currFieldCharIter > maxOutSize - 1) 
                {
                    if (overLength != NULL)
                    {
                        *overLength = true;
                        overLengthMode = true;
                        currField[currFieldCharIter] = 0; // we get only max size
                    }
                }
            }
        }
        lastCharIsQuote = (currChar == '\"') ? 1 : 0;
    }
}

char CSCOrderImport::CsvGetNextByte()
{
    char gByte = 0;
    if (inputfile.is_open() && !isEOF)
    {
        inputfile.get(gByte);
        isEOF = inputfile.eof();
        lastAvailableByte = isEOF;
        return gByte;
    }
    return 0;
}

int CSCOrderImport::FetchOrders()
{
    char error_msg[256];
    short iStart = m_format->getDataStartingLine();
    bool bcheckcustomer = false;
    short sbranch = 0;
    long customer = 0;
    int rc = 0;
    bool first = true;
    bool emptyRow = false;
    int countOrders = 0;
    int countBadOrders = 0;
    int countPositions = 0;
    int countLines = 0;
    int countRows = 0;
    int countBadRows = 0;

    while (CsvGetNextRow(curCSVRow, emptyRow)) 
    {
        bool rowOK = true;

        // still not reached data line ? store header lines
        if (countLines+1 < iStart)
        {
            countLines++;
            headRows.push_back(curCSVRow);
            continue;
        }
        // after reaching the data rows, ignore any empty row
        if (emptyRow)
    {
            continue;
        }
        InitFelder();
        countLines++;
        countRows++;
        // error reading row ?
        if ((rc = FillStruct()) != 0)
        {
            t_order faultyOrder;
            // set with values that he was able to parse
            faultyOrder.set(m_Felder); 
            faultyOrder.lineNo = countLines;
            faultyOrder.validationStatus = "Errors";

            if (rc == 1)
            {
                m_output += GetMessage(CMSG_ORDIMPORT_INVALID_FORMAT) + m_format->getCSVFormatName();
            }
            faultyOrder.validationRemarks = m_output;
            countBadRows++;
            countOrders++;
            countBadOrders++;
            countPositions = 0;
            m_listOrders.push_back(faultyOrder);

            // reset to new order
            first = true;
            // continue parsing next row if only invalid format, else continue to try parse current positon
            if (rc == 1)
            {
                continue;
            }
            rowOK = false;
        }

        // implement order staging validation
        //////////////////////////////////////////
        
        if (rowOK)
            {
            // create a new memory t_order if required
            if (CheckGrouping() || first)   //Nur um sicher zu sein, dass beim ersten mal ein Auftrag eroeffnet wird
            {
                CopyFelder();
                t_order newOrder;
                // set with values that he was able to parse
                countOrders++;
                countPositions = 0; // reset positions counter
                newOrder.set(m_Felder);
                newOrder.validationStatus = "Ok";
                newOrder.lineNo = countLines;

                // 1 - check and validate ordertype and servicetype
                if (m_Felder.ordertype.Field.empty() && false == m_Felder.servicetype.Field.empty())
                {
                    m_Felder.ordertype.Field = m_Felder.servicetype.Field;
                    m_Felder.ordertype.IsGrouping = m_Felder.servicetype.IsGrouping;

                    if (AatartSel_service_type_exists(m_Felder.servicetype.Field.c_str(), error_msg) == false)
                    {
                        first = true;
                        newOrder.validationStatus = "Errors";
                        m_output.format(GetMessage(CMSG_ORDIMPORT_UNKNOWN_SERVICE_TYPE).c_str(), m_Felder.servicetype.Field.c_str());
                        newOrder.validationRemarks += m_output + "\n";
                        // insert the faulty 
                        if (rowOK)
                        {
                            countBadRows++;
                            countBadOrders++;
                            m_listOrders.push_back(newOrder);
                            rowOK = false;
                        }
            }
        }
                // 2 - Check if the pair (branchno, customerno) is valid
                pxCustBase customer(psession, m_Felder.branchno.Field, m_Felder.customerno.Field);
                if (!customer.IsGoodState())
        {
                    first = true;
                    newOrder.validationStatus = "Errors";
                    newOrder.validationRemarks += std::string(customer.ErrorMsg()) + "\n";
                    // insert the faulty 
                    if (rowOK)
                    {
                        countBadRows++;
                        countBadOrders++;
                        rowOK = false;
                        m_listOrders.push_back(newOrder);
        }

                }

                // 3 - Check if order.branchno isn't equal to session branchno for BG only
                if (psession->Country() == pxSession::COUNTRY_BULGARIA && psession->UsersFilialNr() != m_Felder.branchno.Field)
        {
                    first = true;
                    m_output.format(GetMessage(CMSG_ORDIMPORT_CREATE_ORD_OUTOF_SESSION_BRANCH).c_str(), m_Felder.branchno.Field, psession->UsersFilialNr());
                    newOrder.validationStatus = "Errors";
                    newOrder.validationRemarks += m_output + "\n";
                    if (rowOK)
            {
                        countBadRows++;
                        countBadOrders++;
                        rowOK = false;
                        m_listOrders.push_back(newOrder);
                    }
            }

                // insert the new valid order
                if (rowOK)
            {
                    m_listOrders.push_back(newOrder);
                    first = false;
                }
            }
        }
        
        // implement all staging validation of position (any new row always mean a new position)
        ////////////////////////////////////////////////////////////////////////////////////////

        t_postion newPosition;
        newPosition.set(m_Felder);
        newPosition.lineNo = countLines;
        newPosition.validationStatus = "Ok";

        // 1 - at least one of fields (servicetype, articlecode or articledescription) should be filled
        if (m_Felder.servicetype.Field.empty() && m_Felder.articlecode.Field.empty() && m_Felder.articledescription.Field.empty())
            {
            newPosition.validationStatus = "Errors";
            newPosition.validationRemarks = GetMessage(CMSG_ORDIMPORT_MISSING_ARTCODE_OR_ARTDESC) + "\n";
            if (rowOK)
            {
                countBadRows++;
                rowOK = false;
            }
        }

        // 2 - validate articleCode
        struct ARTAESEL   artikel;
        sprintf(artikel.ARTICLE_CODE, "%s", m_Felder.articlecode.Field.c_str());
        if (strcmp(artikel.ARTICLE_CODE, "0") == 0)
        {
            artikel.ARTIKEL_NR = 0;
            newPosition.articleNo = 0;
        }
        else if (m_Felder.articlecode.Field.empty() && !m_Felder.articledescription.Field.empty())
        {
            // instead of article code (PCN) an article description has been provided
            // leave the validation of that article to the create order during import
            artikel.ARTIKEL_NR = 0;
            newPosition.articleNo = 0;
        }
        else if (AatartSel_NoByCode(&artikel, error_msg) == 1)
        {
            m_output.format(GetMessage(CMSG_ORDIMPORT_ARTCODE_NOTFOUND).c_str(), m_Felder.articlecode.Field.c_str());
            newPosition.validationStatus = "Errors";
            if (rowOK)
            {
                countBadRows++;
                rowOK = false;
            }
            newPosition.validationRemarks += m_output + "\n";
        }
        newPosition.articleNo = artikel.ARTIKEL_NR;

        // insert the new position faulty or not
        m_listOrders[countOrders - 1].listPositions.push_back(newPosition);
    }

    // log status of orders fetching
    if (countBadRows == 0)
    {
        m_output.format(GetMessage(CMSG_ORDIMPORT_SUCCESS_FETCH_ORDERS).c_str(), countOrders, countRows);
            }
            else
            {
        m_output.format(GetMessage(CMSG_ORDIMPORT_FAIL_FETCH_ORDERS).c_str(), countOrders - countBadOrders, countBadOrders, countBadRows);
    }
    WriteLogFile();

    return countBadRows;
}

bool CSCOrderImport::CreateOrders()
{
    int rc = 0;
    int countFailure = 0;
    char csvFileName[256] = "";
    size_t statusIdx = formatMaxPosition;

    for (size_t j = 0; j < m_listOrders.size(); j++)
    {
        // reset all fields values
        InitFelder();
        // get fields required for order creation
        m_listOrders[j].get(m_Felder);
        m_output = "";
        rc = 0;
        if (m_listOrders[j].validationStatus != "Ok")
        {
            countFailure++;
        }
        // if order has no position or if open Order fail, export to csv this order with all it's position(s)
        else if (m_listOrders[j].listPositions.size() == 0 || (rc = OpenOrder()) != 0)
        {
            m_listOrders[j].validationStatus = "Errors";
            // rc not zero mean that we tried OpenOrder call with failure, so take error message
            if (rc != 0)
            {
                m_listOrders[j].validationRemarks += m_output + "\n";
            }
            else
            {
                m_output = GetMessage(CMSG_ORDIMPORT_EMPTY_ORD_CANCELED) + "\n";
                m_listOrders[j].validationRemarks = m_output;
        }
            WriteLogFile();
            m_listOrders[j].closingRemarks += GetMessage(CMSG_ORDIMPORT_ORD_OPEN_FAILED) + "\n";

            countFailure++;

        }
        else // else create order positions if no staging validation errors
        {
            // store mesage of successfull order opening
            m_listOrders[j].validationRemarks = m_output;
            // store Order Nr
            m_listOrders[j].OrderNr = order->KdAuftragNr();
            // create postions
            orderposread = m_listOrders[j].listPositions.size();
            for (size_t i = 0; i < m_listOrders[j].listPositions.size(); i++)
            {
                if (m_listOrders[j].listPositions[i].validationStatus == "Ok")
                {
                    rc = 0;
                    // fill required fields for position creation
                    m_listOrders[j].listPositions[i].get(m_Felder);
        if (!m_Felder.servicetype.Field.empty())
        {
                        rc = WritePos(true);
        }
        else if (!m_Felder.articlecode.Field.empty())
        {
                        rc = WritePos();
        }
        else if (!m_Felder.articledescription.Field.empty())
        {
                        rc = WriteTextPos();
        }
                    // rc != 0 => error happened during position creation
                    if (rc != 0)
        {
                        countFailure++;
                        m_listOrders[j].listPositions[i].validationStatus = "Errors";
                    }
                    // adds any possible remark in position creation
                    if (m_output.length() > 0)
                    {
                        m_listOrders[j].listPositions[i].validationRemarks += m_output + "\n";
        }
    }
                else
    {
                    countFailure++;
                }
            }
        CloseOrder();
            m_listOrders[j].closingRemarks = m_output;
        }
    }
    // generate csv with only faulty orders/positons or empty file
    ExportOrders(false); // currently generate report csv with all orders
    if (countFailure)
    {
        return false;
    }

    return true;
}

int CSCOrderImport::CloseFile()
{
    inputfile.close();
    return 0;
}

int CSCOrderImport::OpenLogFile()
{
    outputfile.open(m_output.c_str(), std::ios_base::out);
    if (!outputfile.is_open())
    {
        return 1;
    }
    return 0;
}

int CSCOrderImport::WriteLogFile()
{
    if(!m_bWriteLog) return 0;
    //char ausgabe[100];
    //sprintf(ausgabe, "%s\n", m_output.c_str());
    //outputfile.write(ausgabe,strlen(ausgabe));
    outputfile << m_output << std::endl;
    return 0;
}

int CSCOrderImport::CloseLogFile()
{
    if (m_bWriteLog)
    {
        outputfile.close();
    }
    return 0;
}

int CSCOrderImport::OpenOrder()
{
    std::string AArt;
    char error_msg[200];

    psession->resetOrderEntryParam();

    if (m_Felder.ordertype.Field.empty() && false == m_Felder.servicetype.Field.empty())
    {
        m_Felder.ordertype.Field = m_Felder.servicetype.Field;
        m_Felder.ordertype.IsGrouping = m_Felder.servicetype.IsGrouping;

        if (AatartSel_service_type_exists(m_Felder.servicetype.Field.c_str(), error_msg) == false)
        {
            m_output.format(GetMessage(CMSG_ORDIMPORT_UNKNOWN_SERVICE_TYPE).c_str(), m_Felder.servicetype.Field.c_str());
            WriteLogFile();
            return -1;
        }
    }

    pxCustBase customer(psession, m_Felder.branchno.Field, m_Felder.customerno.Field);
    if (!customer.IsGoodState())
    {
        m_output = customer.ErrorMsg();
        WriteLogFile();
        return -1;
    }

    order = new pxOrder(psession, customer);
    if (order == NULL)
    {
        m_output = GetMessage(CMSG_ORDIMPORT_ORD_OPEN_FAILED);
        WriteLogFile();
        return -2;
    }
    if (!order->IsGoodState())
    {
        m_output = order->ErrorMsg();
        WriteLogFile();
        if (order->IsFatalErrorState() || order->IsAbendState())
        {
            return -1;
        }
        else
        {
            if (order->IsChangeable())
            {
                m_output.format(GetMessage(CMSG_ORDIMPORT_ORD_OPENED).c_str(), order->KdAuftragNr(), m_Felder.branchno.Field, m_Felder.customerno.Field);
                WriteLogFile();
                m_output = order->ErrorMsg();
                WriteLogFile();
            }
            else
                return -2;
        }
    }
    else
    {
        m_output.format(GetMessage(CMSG_ORDIMPORT_ORD_OPENED).c_str(), order->KdAuftragNr(), m_Felder.branchno.Field, m_Felder.customerno.Field);
        WriteLogFile();
    }
    if (!m_Felder.ordertype.Field.empty() || !m_Felder.pickingtype.Field.empty() || !m_Felder.bookingtype.Field.empty())
    {
        char OT[1];
        char BT[1];
        if (m_Felder.ordertype.Field.empty()) AArt = order->KdAuftragArt();
        else AArt = m_Felder.ordertype.Field.c_str();
        if (m_Felder.pickingtype.Field.empty()) OT[0] = '0';
        else OT[0] = m_Felder.pickingtype.Field.at(0);
        if (m_Felder.bookingtype.Field.empty()) BT[0] = '0';
        else BT[0] = m_Felder.bookingtype.Field.at(0);
        order->OrderType(AArt.c_str(), OT[0], BT[0]);
        if (!(order->IsGoodState()))
        {
            m_output = order->ErrorMsg();
            WriteLogFile();
        }
        order->RouteAssign();
    }
    char cAArt[3];
    char Tour[7];
    AllgStrCopy(cAArt, order->KdAuftragArt(), 2);
    AllgStrCopy(Tour, order->TourId(), 6);
    if (!m_Felder.orderlabel.Field.empty())    //Auftragskennung für den Auftrag setzen
    {
        nString label = m_Felder.orderlabel.Field.c_str();
        order->SetOrderLabel(label);
        m_output.format(GetMessage(CMSG_ORDIMPORT_ORD_TYPE_COMM_LABEL ).c_str(), cAArt, order->KoArt(), order->BuchArt(), Tour, label() );
    }
    else
    {
        m_output.format(GetMessage(CMSG_ORDIMPORT_ORD_TYPE_COMM ).c_str(), cAArt, order->KoArt(), order->BuchArt(), Tour);
    }


    long actdate = AllgGetDate();
    if (m_Felder.datevaluta.Field >= actdate)    //Valutadatum setzen
    {
        nDate valuta(m_Felder.datevaluta.Field);
        order->ValDate(valuta);
        valuta = order->DatumValuta();
        if (valuta != pxConstants::NullDate)
        {
            order->SetDatumValutaBatch(valuta);
            basar::VarString tmp;
            tmp.format(GetMessage(CMSG_ORDIMPORT_DATE_VALUE ).c_str(), valuta.GetDay(), valuta.GetMonth(), valuta.GetYear());
            m_output.append(tmp);
        }
    }

    if (!m_Felder.servicetype.Field.empty() && m_Felder.datedelayeddelivery.Field == 0)
    {
        m_Felder.datedelayeddelivery.Field = actdate;
    }

    if (m_Felder.datedelayeddelivery.Field >= actdate)    //Datum Auslieferung setzen
    {
        nDate dd(m_Felder.datedelayeddelivery.Field);
        order->RouteAssignDayType(dd);
//      order->SetDatumAuslieferung(m_Felder.datedelayeddelivery.Field);
        order->SetDeliveryDatePreset();
        basar::VarString tmp;
        tmp.format(GetMessage(CMSG_ORDIMPORT_DATE_EXTRAD).c_str(), order->DatumAuslieferung().GetDay(), order->DatumAuslieferung().GetMonth(), order->DatumAuslieferung().GetYear());
        m_output.append(tmp);
    }
    WriteLogFile();
    if (!m_Felder.orderremark.Field.empty())    //Bemerkung für die Auftrag setzen
    {
        nString nStr = m_Felder.orderremark.Field.c_str();
        order->Bemerkungen(nStr);
    }
    if (!m_Felder.headremark.Field.empty())    //Kopfzeile für die Auftrag setzen
    {
        pxTextDoc *doc = order->HeadText();
        doc->NewLine(m_Felder.headremark.Field.c_str());
    }

    orderposcount = 0;
    orderposread = 0;
    ordercount++;
    m_bOrderOpen = true;
    return 0;
}

int CSCOrderImport::CloseOrder()
{
    order->ClearError();
    m_output = "";
    if (m_format->getPostponeOrder())
    {
        order->SetProblemClearance();   //Nur wenn Schalter gesetzt
    }
    if (orderposcount == 0)
    {
        order->CancelOrder(pxDVC_UNDEFINED);
        m_output = GetMessage(CMSG_ORDIMPORT_EMPTY_ORD_CANCELED);
    }
    else
    {
        if (m_format->getPostponeOrder())
        {
            order->Close();
        }
        else
        {
            if (order->IsOrderConsolidation())
            {
                order->Close();
            }
            else
            {
                order->Close(Order::EntryClosed);
            }
        }
        if (orderposread > orderposcount)
        {
            m_output.format(GetMessage(CMSG_ORDIMPORT_ORD_OK_VALID_INVALID ).c_str(), orderposcount, orderposread - orderposcount);
        }
        else
        {
            m_output.format(GetMessage(CMSG_ORDIMPORT_ORD_OK_VALID).c_str(), orderposcount);
        }
    }
    WriteLogFile();
    m_bOrderOpen = false;
    return 0;
}

int CSCOrderImport::WritePos(bool isService)
{
    pxOrderItem* orderitem = NULL;
    char error_msg[200];
    char fehler[200] = { 0 };
    char description[255];
    struct ARTAESEL   artikel;
    bool bNL = false;
    if (m_Felder.restdelivery.Field != 0) bNL = true;
    sprintf(artikel.ARTICLE_CODE, "%s", m_Felder.articlecode.Field.c_str());
    if (strcmp(artikel.ARTICLE_CODE, "0") == 0)
    {
        artikel.ARTIKEL_NR = 0;
    }
    else if (AatartSel_NoByCode(&artikel, error_msg) == 1)
    {
        m_output.format(GetMessage(CMSG_ORDIMPORT_ARTCODE_NOTFOUND).c_str(), m_Felder.articlecode.Field.c_str());
        WriteLogFile();
        return 1;
    }

    if (isService)
    {
        if (AatartSel_service_type_exists(m_Felder.servicetype.Field.c_str(), error_msg) == false)
        {
            m_output.format(GetMessage(CMSG_ORDIMPORT_SERVICETYPE_NOTFOUND).c_str(), m_Felder.servicetype.Field.c_str());
            WriteLogFile();
            return 1;
        }

        if (AatartSel_service_number_exists_and_valid(m_Felder.service.Field.c_str(), m_Felder.servicetype.Field.c_str(), description, error_msg) == false)
        {
            m_output.format(GetMessage(CMSG_ORDIMPORT_SERVICE_NOTFOUND).c_str(), m_Felder.service.Field.c_str(), m_Felder.servicetype.Field.c_str());
            WriteLogFile();
            return 1;
        }

        if (m_Felder.vatlevel.Field != 0 && m_Felder.vatlevel.Field != 1)
        {
            /* Auch wenn di.MWSTSchluessel ein ENUM ist mit den Werten 0 und 1 sind Werte aus
               der taxrates Tabelle ebenfalls gültig. Denn es gibt mehr als nur die beiden Enums
               Bei der Tax Berechnung wird der Wert aus taxrates auch korrekt eingesetzt.
               Die Werte 0 und 1 werden nicht gegenüber der DB geprüft nur Werte außerhalb des
               Enum-Wertebereichs. Hier muss der taxlevel in der Tabelle existieren. */

            if (AatartSel_taxlevel_exists(m_Felder.vatlevel.Field, error_msg) == false)
            {
                m_output.format(GetMessage(CMSG_ORDIMPORT_VAT_RATE_MUST).c_str(), m_Felder.servicetype.Field.c_str());
                WriteLogFile();
                return 1;
            }
        }

        tDISPOITEM dispoItem;
        dispoItem.Bezeichnung = nString(description);
        dispoItem.MengeBestellt = m_Felder.orderqty.Field;
        dispoItem.PreisEKGrosso = m_Felder.aep.Field;
        dispoItem.PreisEKApo = m_Felder.aep.Field;
        dispoItem.NetPrice = m_Felder.aep.Field;
        dispoItem.Rabattfaehig = false;
        dispoItem.MWSTSchluessel = static_cast<pxMWSTSchluessel>(m_Felder.vatlevel.Field);
        dispoItem.Service_No = std::atoi(m_Felder.service.Field.c_str());

        orderitem = order->NewOrderItem_15(dispoItem);
    }
    else
    {
    if (m_Felder.aep.Field > 0.0)
    {
        orderitem = order->NewOrderItem_13(artikel.ARTIKEL_NR, m_Felder.orderqty.Field, "", "", false, bNL, false, true, static_cast<PriceTypeEnum>(0), m_Felder.aep.Field, 0.0, 0.0, 0);
    }
    else
    {
        orderitem = order->NewOrderItem_12(artikel.ARTIKEL_NR, m_Felder.orderqty.Field, "", "", false, bNL, false, true, static_cast<PriceTypeEnum>(0));
    }
    }

    if (!(order->IsGoodState()))
    {
        AllgStrCopy(fehler, order->ErrorMsg(), MAX_ERROR_MSG_AE);
        m_output.format(GetMessage(CMSG_ORDIMPORT_ARTCODE_QUANTITY_FAILED).c_str(), m_Felder.orderqty.Field, m_Felder.articlecode.Field.c_str(), fehler);
        WriteLogFile();
        return 1;
    }
    if (orderitem == NULL)
    {
        m_output = psession->ErrorMsg();
        WriteLogFile();
        return 1;
    }
    if (orderitem->GetError(fehler) > 0)
    {
        fehler[strlen(fehler) - 1] = '\0';  // \n enfernen, da writelog \n ergänzt wird
    }
    if (!m_Felder.posremark.Field.empty())    //Bemerkung für die Position setzen
    {
        nString nStr = m_Felder.posremark.Field.c_str();
        orderitem->Bemerkungen(nStr);
    }
    m_output.format(GetMessage(CMSG_ORDIMPORT_ARTCODE_CONFIRMED_ORD_QUANTITY).c_str(), orderitem->MengeBestellt(), orderitem->MengeBestaetigt(), m_Felder.articlecode.Field.c_str(), fehler);
    WriteLogFile();

    orderposcount++;
    totalposcount++;
    return 0;
}

int CSCOrderImport::WriteTextPos()
{
//  pxOrderItem *item;
    tDISPOITEM  di;
    di.Bezeichnung = m_Felder.articledescription.Field.c_str();
    di.Einheit.Clear();
    di.Darreichform.Clear();
    di.Bemerkungen = m_Felder.posremark.Field.c_str();
    di.PreisEKApo = m_Felder.aep.Field;
    if(m_Felder.gep.Field == 0)
    {
        di.PreisEKGrosso = m_Felder.aep.Field;
    }
    else
    {
        di.PreisEKGrosso = m_Felder.gep.Field;
    }
    di.MengeBestellt = m_Felder.orderqty.Field;
    di.RabattFestDM = 0;
    di.RabattFest = 0;
    di.MWSTSchluessel = static_cast<pxMWSTSchluessel>(m_Felder.vatlevel.Field);
    di.TaxPflichtig = false;
    di.Rabattfaehig = false;
    di.WarenGruppeEigen = "99999";
    di.UrsprungAuftragnr = 0;
    di.UrsprungPosnr = 0;
    di.GebuehrBearb = 0.0;
    di.NetPrice = 0.0;
    di.Service_No = 0;
    di.KzPriso = ' ';

//  item = order->NewOrderItem_15(di, pxOrderItem::BookingTypeDefault);
    order->NewOrderItem_15(di, pxOrderItem::BookingTypeDefault);
    if (!(order->IsGoodState()))
    {
        m_output = order->ErrorMsg();
        WriteLogFile();
        return 1;
    }
    orderposcount++;
    totalposcount++;
    return 0;
}

bool CSCOrderImport::GetFormat()
{
    int position = 0;

    psession->getParameterComponentManager()->getCSVOrderImportRepository()->reset();
    m_format = psession->getParameterComponentManager()->getCSVOrderImportRepository()->findCSCOrderImportCSVFormatsById(m_FormatID);
    if (m_format.get() == NULL) return false;
    // fill fieldID to columnName map
    for (size_t i = 0; i < m_fieldtypes->size(); i++)
    {
        libcsc::parameter::ICSCOrderImportFieldsPtr type = m_fieldtypes->at(i);
        type.get();
        mapFieldIDToName.insert(std::pair<int, std::string>(type->getFieldNameId(), type->getImportFieldName()));
    }
    // get max position value for this format
    formatMaxPosition = 0;
    for (int index = 0; index < (int)m_format->getCSCOrderImportCSVColums()->size(); index++)
    {
        position = m_format->getCSCOrderImportCSVColums()->at(index)->getColumnNo();
        if (position > formatMaxPosition)
        {
            formatMaxPosition = position;
        }
    }

    return true;
}

int CSCOrderImport::FillStruct()
{
    int position;
    int fieldid;
    short grouping;
    int anzfields;
    std::vector<std::string> datelist;
    std::map<int, std::string>::iterator it;
    std::string validationErrMsg = "";
    std::string multilangMessage = "";
    std::string fieldErrMsg = "";
    bool validationErr = false;

    basar::VarString importfieldname;
    anzfields = curCSVRow.size();
    for(int index = 0;index < (int)m_format->getCSCOrderImportCSVColums()->size();index++)
    {
        position = m_format->getCSCOrderImportCSVColums()->at(index)->getColumnNo();
        if (position > anzfields)
        {
            m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_FIELD).c_str(), position, anzfields);
            WriteLogFile();
            return OrdImpRCWrongFormat;
        }
        fieldid = m_format->getCSCOrderImportCSVColums()->at(index)->getFieldNameId();
        grouping = m_format->getCSCOrderImportCSVColums()->at(index)->getGrouping();
        importfieldname.clear();
        if ((it = mapFieldIDToName.find(fieldid)) != mapFieldIDToName.end())
            {
            importfieldname = it->second;
        }
        if (importfieldname.empty())
        {
            m_output = GetMessage(CMSG_ORDIMPORT_UNKNOW_FIELD_TYPE_FORMAT);
            WriteLogFile();
            return 1;
        }
        if (importfieldname == FIELDNAME_BRANCHNO)
        {
            m_Felder.branchno.strField = curCSVRow[position - 1];
            m_Felder.branchno.Field = (short)atoi(curCSVRow[position - 1].c_str());
            m_Felder.branchno.IsGrouping = grouping;
        }
        else if (importfieldname == FIELDNAME_CUSTOMERNO)
        {
            m_Felder.customerno.strField = curCSVRow[position - 1];
            m_Felder.customerno.Field = atoi(curCSVRow[position - 1].c_str());
            m_Felder.customerno.IsGrouping = grouping;
        }
        else if (importfieldname == FIELDNAME_ORDERTYPE)
        {
            m_Felder.ordertype.strField = curCSVRow[position - 1];
            toUpperStr(curCSVRow[position - 1]);
            m_Felder.ordertype.Field = curCSVRow[position - 1];
            m_Felder.ordertype.IsGrouping = grouping;
        }
        else if (importfieldname == FIELDNAME_PICKINGTYPE)
        {
            m_Felder.pickingtype.strField = curCSVRow[position - 1];
            m_Felder.pickingtype.Field = curCSVRow[position - 1];
            m_Felder.pickingtype.IsGrouping = grouping;
        }
        else if (importfieldname == FIELDNAME_BOOKINGTYPE)
        {
            m_Felder.bookingtype.strField = curCSVRow[position - 1];
            m_Felder.bookingtype.Field = curCSVRow[position - 1];
            m_Felder.bookingtype.IsGrouping = grouping;
        }
        else if (importfieldname == FIELDNAME_ORDERREMARK)
        {
            m_Felder.orderremark.strField = curCSVRow[position - 1];
            toUpperStr(curCSVRow[position - 1]);
            m_Felder.orderremark.Field = curCSVRow[position - 1];
            m_Felder.orderremark.IsGrouping = grouping;
        }
        else if (importfieldname == FIELDNAME_ARTICLECODE)
        {
            m_Felder.articlecode.strField = curCSVRow[position - 1];
            m_Felder.articlecode.Field = curCSVRow[position - 1];
            m_Felder.articlecode.IsGrouping = grouping;
        }
        else if (importfieldname == FIELDNAME_ORDERQTY)
        {
            m_Felder.orderqty.strField = curCSVRow[position - 1];
            m_Felder.orderqty.Field = atoi(curCSVRow[position - 1].c_str());
            m_Felder.orderqty.IsGrouping = grouping;
        }
        else if (importfieldname == FIELDNAME_POSREMARK)
        {
            m_Felder.posremark.strField = curCSVRow[position - 1];
            toUpperStr(curCSVRow[position - 1]);
            m_Felder.posremark.Field = curCSVRow[position - 1];
            m_Felder.posremark.IsGrouping = grouping;
        }
        else if (importfieldname == FIELDNAME_PHARMACYPURCHASEPRICE)
        {
            m_Felder.aep.strField = curCSVRow[position - 1];
            std::replace(curCSVRow[position - 1].begin(), curCSVRow[position - 1].end(), ',', '.');
            m_Felder.aep.Field = atof(curCSVRow[position - 1].c_str());
            m_Felder.aep.IsGrouping = grouping;
        }
        else if (importfieldname == FIELDNAME_GROSSPURCHASEPRICE)
        {
            m_Felder.gep.strField = curCSVRow[position - 1];
            std::replace(curCSVRow[position - 1].begin(), curCSVRow[position - 1].end(), ',', '.');
            m_Felder.gep.Field = atof(curCSVRow[position - 1].c_str());
            m_Felder.gep.IsGrouping = grouping;
        }
        else if (importfieldname == FIELDNAME_PORTO)
        {
            m_Felder.porto.strField = curCSVRow[position - 1];
            std::replace(curCSVRow[position - 1].begin(), curCSVRow[position - 1].end(), ',', '.');
            m_Felder.porto.Field = atof(curCSVRow[position - 1].c_str());
            m_Felder.porto.IsGrouping = grouping;
        }
        else if (importfieldname == FIELDNAME_ARTICLEDESCRIPTION)
        {
            m_Felder.articledescription.strField = curCSVRow[position - 1];
            toUpperStr(curCSVRow[position - 1]);
            m_Felder.articledescription.Field = curCSVRow[position - 1];
            m_Felder.articledescription.IsGrouping = grouping;
        }
        else if (importfieldname == FIELDNAME_DISCOUTPRECENTAGE)
        {
            m_Felder.dicountpercentage.strField = curCSVRow[position - 1];
            std::replace(curCSVRow[position - 1].begin(), curCSVRow[position - 1].end(), ',', '.');
            m_Felder.dicountpercentage.Field = atof(curCSVRow[position - 1].c_str());
            m_Felder.dicountpercentage.IsGrouping = grouping;
        }
        else if (importfieldname == FIELDNAME_VATLEVEL)
        {
            m_Felder.vatlevel.strField = curCSVRow[position - 1];
            m_Felder.vatlevel.Field = (short)atoi(curCSVRow[position - 1].c_str());
            m_Felder.vatlevel.IsGrouping = grouping;
        }
        else if (importfieldname == FIELDNAME_HEADREMARK)
        {
            m_Felder.headremark.strField = curCSVRow[position - 1];
            toUpperStr(curCSVRow[position - 1]);
            m_Felder.headremark.Field = curCSVRow[position - 1];
            m_Felder.headremark.IsGrouping = grouping;
        }
        else if (importfieldname == FIELDNAME_DATEVALUTA)
        {
            m_Felder.datevaluta.strField = curCSVRow[position - 1];
            splitStr(datelist, curCSVRow[position - 1], '.');
            if (datelist.size() == 3)
            {
                m_Felder.datevaluta.Field = atoi(datelist[0].c_str()) + (atoi(datelist[1].c_str()) * 100) + (atoi(datelist[2].c_str()) * 10000);
            }
            m_Felder.datevaluta.IsGrouping = grouping;
        }
        else if (importfieldname == FIELDNAME_DATEDELAYEDDELIVERY)
        {
            m_Felder.datedelayeddelivery.strField = curCSVRow[position - 1];
            splitStr(datelist, curCSVRow[position - 1], '.');
            if (datelist.size() == 3)
            {
                m_Felder.datedelayeddelivery.Field = atoi(datelist[0].c_str()) + (atoi(datelist[1].c_str()) * 100) + (atoi(datelist[2].c_str()) * 10000);
            }
            m_Felder.datedelayeddelivery.IsGrouping = grouping;
        }
        else if (importfieldname == FIELDNAME_ORDERLABEL)
        {
            m_Felder.orderlabel.strField = curCSVRow[position - 1];
            toUpperStr(curCSVRow[position - 1]);
            m_Felder.orderlabel.Field = curCSVRow[position - 1];
            m_Felder.orderlabel.IsGrouping = grouping;
        }
        else if (importfieldname == FIELDNAME_RESTDELIVARY)
        {
            m_Felder.restdelivery.strField = curCSVRow[position - 1];
            m_Felder.restdelivery.Field = (short)atoi(curCSVRow[position - 1].c_str());
            m_Felder.restdelivery.IsGrouping = grouping;
        }
        else if (importfieldname == FIELDNAME_SERVICETYPE)
        {
            m_Felder.servicetype.strField = curCSVRow[position - 1];
            m_Felder.servicetype.Field = curCSVRow[position - 1];
            m_Felder.servicetype.IsGrouping = grouping;
            m_Felder.articlecode.Field = "0";
            m_Felder.articlecode.IsGrouping = false;
        }
        else if (importfieldname == FIELDNAME_SERVICE)
        {
            m_Felder.service.strField = curCSVRow[position - 1];
            m_Felder.service.Field = curCSVRow[position - 1];
            m_Felder.service.IsGrouping = grouping;
        }
        else
        {
            m_output = GetMessage(CMSG_ORDIMPORT_UNKNOW_FIELD_TYPE);
            WriteLogFile();
            return 1;
        }
    }
    orderposread++;

    // mandatory fields checking
    for (size_t i = 0; i < m_fieldtypes->size(); i++)
    {
        libcsc::parameter::ICSCOrderImportFieldsPtr type = m_fieldtypes->at(i);
        type.get();
            importfieldname = type->getImportFieldName();

        // fields branchnon, customerno and orderQty are always mandatory what ever the current format settings
            if (importfieldname == FIELDNAME_BRANCHNO)
            {
                if (m_Felder.branchno.Field == 0)
                {
                m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD).c_str(), importfieldname.c_str());
                    WriteLogFile();
                validationErr = true;
                validationErrMsg += m_output + '\n';
                }
            }
            else if (importfieldname == FIELDNAME_CUSTOMERNO)
            {
                if (m_Felder.customerno.Field == 0)
                {
                m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD).c_str(), importfieldname.c_str());
                    WriteLogFile();
                validationErr = true;
                validationErrMsg += m_output + '\n';
                }
            }
        else if (importfieldname == FIELDNAME_ARTICLECODE)
            {
            if (m_Felder.articlecode.Field.empty() && type->getImportMandatory() == 1)
                {
                m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD).c_str(), importfieldname.c_str());
                    WriteLogFile();
                validationErr = true;
                validationErrMsg += m_output + '\n';
                }
            }
        else if (importfieldname == FIELDNAME_ORDERQTY)
            {
            if (m_Felder.orderqty.Field == 0)
                {
                m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD).c_str(), importfieldname.c_str());
                    WriteLogFile();
                validationErr = true;
                validationErrMsg += m_output + '\n';
                }
            }
        else if (importfieldname == FIELDNAME_ORDERTYPE)
            {
            if (m_Felder.ordertype.Field.empty() && type->getImportMandatory() == 1)
                {
                m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD).c_str(), importfieldname.c_str());
                    WriteLogFile();
                validationErr = true;
                validationErrMsg += m_output + '\n';
                }
            }
        else if (importfieldname == FIELDNAME_PICKINGTYPE)
            {
            if (m_Felder.pickingtype.Field.empty() && type->getImportMandatory() == 1)
                {
                m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD).c_str(), importfieldname.c_str());
                    WriteLogFile();
                validationErr = true;
                validationErrMsg += m_output + '\n';
                }
            }
        else if (importfieldname == FIELDNAME_BOOKINGTYPE)
            {
            if (m_Felder.bookingtype.Field.empty() && type->getImportMandatory() == 1)
                {
                m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD).c_str(), importfieldname.c_str());
                    WriteLogFile();
                validationErr = true;
                validationErrMsg += m_output + '\n';
                }
            }
        else if (importfieldname == FIELDNAME_ORDERREMARK)
            {
            if (m_Felder.orderremark.Field.empty() && type->getImportMandatory() == 1)
                {
                m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD).c_str(), importfieldname.c_str());
                    WriteLogFile();
                validationErr = true;
                validationErrMsg += m_output + '\n';
                }
            }
            else if (importfieldname == FIELDNAME_POSREMARK)
            {
            if (m_Felder.posremark.Field.empty() && type->getImportMandatory() == 1)
                {
                m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD).c_str(), importfieldname.c_str());
                    WriteLogFile();
                validationErr = true;
                validationErrMsg += m_output + '\n';
                }
            }
            else if (importfieldname == FIELDNAME_PHARMACYPURCHASEPRICE)
            {
            if (m_Felder.aep.Field == 0 && type->getImportMandatory() == 1)
                {
                m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD).c_str(), importfieldname.c_str());
                    WriteLogFile();
                validationErr = true;
                validationErrMsg += m_output + '\n';
                }
            }
            else if (importfieldname == FIELDNAME_GROSSPURCHASEPRICE)
            {
            if (m_Felder.gep.Field == 0 && type->getImportMandatory() == 1)
                {
                m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD).c_str(), importfieldname.c_str());
                    WriteLogFile();
                validationErr = true;
                validationErrMsg += m_output + '\n';
                }
            }
            else if (importfieldname == FIELDNAME_PORTO)
            {
            if (m_Felder.porto.Field == 0 && type->getImportMandatory() == 1)
                {
                m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD).c_str(), importfieldname.c_str());
                    WriteLogFile();
                validationErr = true;
                validationErrMsg += m_output + '\n';
                }
            }
            else if (importfieldname == FIELDNAME_ARTICLEDESCRIPTION)
            {
            if (m_Felder.articledescription.Field.empty() && type->getImportMandatory() == 1)
                {
                m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD).c_str(), importfieldname.c_str());
                    WriteLogFile();
                validationErr = true;
                validationErrMsg += m_output + '\n';
                }
            }
            else if (importfieldname == FIELDNAME_DISCOUTPRECENTAGE)
            {
            if (m_Felder.dicountpercentage.Field == 0 && type->getImportMandatory() == 1)
                {
                m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD).c_str(), importfieldname.c_str());
                    WriteLogFile();
                validationErr = true;
                validationErrMsg += m_output + '\n';
                }
            }
            else if (importfieldname == FIELDNAME_VATLEVEL)
            {
            if (m_Felder.vatlevel.Field == 0 && type->getImportMandatory() == 1)
                {
                m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD).c_str(), importfieldname.c_str());
                    WriteLogFile();
                validationErr = true;
                validationErrMsg += m_output + '\n';
                }
            }
            else if (importfieldname == FIELDNAME_HEADREMARK)
            {
            if (m_Felder.headremark.Field.empty() && type->getImportMandatory() == 1)
                {
                m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD).c_str(), importfieldname.c_str());
                    WriteLogFile();
                validationErr = true;
                validationErrMsg += m_output + '\n';
                }
            }
            else if (importfieldname == FIELDNAME_DATEVALUTA)
            {
            if (m_Felder.datevaluta.Field == 0 && type->getImportMandatory() == 1)
                {
                m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD).c_str(), importfieldname.c_str());
                    WriteLogFile();
                validationErr = true;
                validationErrMsg += m_output + '\n';
                }
            }
            else if (importfieldname == FIELDNAME_DATEDELAYEDDELIVERY)
            {
            if (m_Felder.datedelayeddelivery.Field == 0 && type->getImportMandatory() == 1)
                {
                m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD).c_str(), importfieldname.c_str());
                    WriteLogFile();
                validationErr = true;
                validationErrMsg += m_output + '\n';
                }
            }
            else if (importfieldname == FIELDNAME_ORDERLABEL)
            {
            if (m_Felder.orderlabel.Field.empty() && type->getImportMandatory() == 1)
                {
                m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD).c_str(), importfieldname.c_str());
                    WriteLogFile();
                validationErr = true;
                validationErrMsg += m_output + '\n';
                }
            }
            else if (importfieldname == FIELDNAME_RESTDELIVARY)
            {
            if (m_Felder.restdelivery.Field == 0 && type->getImportMandatory() == 1)
                {
                m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD).c_str(), importfieldname.c_str());
                    WriteLogFile();
                validationErr = true;
                validationErrMsg += m_output + '\n';
                }
            }
			else if (importfieldname == FIELDNAME_SERVICETYPE)
			{
            if (m_Felder.servicetype.Field.empty() && type->getImportMandatory() == 1)
			    {
                m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD).c_str(), importfieldname.c_str());
				    WriteLogFile();
                validationErr = true;
                validationErrMsg += m_output + '\n';
			    }
			}
			else if (importfieldname == FIELDNAME_SERVICE)
			{
            if (m_Felder.service.Field.empty() && type->getImportMandatory() == 1)
			    {
                m_output.format(GetMessage(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD).c_str(), importfieldname.c_str());
				    WriteLogFile();
                validationErr = true;
                validationErrMsg += m_output + '\n';
			    }
			}
            else
            {
            m_output.format(GetMessage(CMSG_ORDIMPORT_UNKNOW_FIELD_TYPE_LINE).c_str(), m_count);
                WriteLogFile();
            validationErr = true;
            validationErrMsg += m_output + '\n';
        }
    }

    // format fields validation
    for (int index = 0; index < (int)m_format->getCSCOrderImportCSVColums()->size(); index++)
    {
        position = m_format->getCSCOrderImportCSVColums()->at(index)->getColumnNo();
        fieldid = m_format->getCSCOrderImportCSVColums()->at(index)->getFieldNameId();
        importfieldname.clear();
        if ((it = mapFieldIDToName.find(fieldid)) != mapFieldIDToName.end())
        {
            importfieldname = it->second;
        }

        if (importfieldname.empty())
        {
            continue;
        }
        if (importfieldname == FIELDNAME_BRANCHNO)
        {
            if (!m_Felder.branchno.strField.empty() && !IsInteger32(m_Felder.branchno.strField.c_str(), fieldErrMsg))
            {
                validationErr = true;
                m_output.format(GetMessage(CMSG_ORDIMPORT_FAILED_TO_VALIDATE_FIELD).c_str(), importfieldname.c_str(), fieldErrMsg.c_str());
                validationErrMsg += m_output + "\n";
            }
        }
        else if (importfieldname == FIELDNAME_CUSTOMERNO)
        {
            if (!m_Felder.customerno.strField.empty() && !IsInteger32(m_Felder.customerno.strField.c_str(), fieldErrMsg))
            {
                validationErr = true;
                m_output.format(GetMessage(CMSG_ORDIMPORT_FAILED_TO_VALIDATE_FIELD).c_str(), importfieldname.c_str(), fieldErrMsg.c_str());
                validationErrMsg += m_output + "\n";
            }
        }
        else if (importfieldname == FIELDNAME_ARTICLECODE)
        {
            if (!m_Felder.articlecode.strField.empty() && !IsNumericString(m_Felder.articlecode.strField.c_str(), fieldErrMsg))
            {
                validationErr = true;
                m_output.format(GetMessage(CMSG_ORDIMPORT_FAILED_TO_VALIDATE_FIELD).c_str(), importfieldname.c_str(), fieldErrMsg.c_str());
                validationErrMsg += m_output + "\n";
            }
        }
        else if (importfieldname == FIELDNAME_ORDERQTY)
        {
            if (!m_Felder.orderqty.strField.empty() && !IsInteger32(m_Felder.orderqty.strField.c_str(), fieldErrMsg))
            {
                validationErr = true;
                m_output.format(GetMessage(CMSG_ORDIMPORT_FAILED_TO_VALIDATE_FIELD).c_str(), importfieldname.c_str(), fieldErrMsg.c_str());
                validationErrMsg += m_output + "\n";
            }
        }
        else if (importfieldname == FIELDNAME_ORDERTYPE)
        {
        }
        else if (importfieldname == FIELDNAME_PICKINGTYPE)
        {
        }
        else if (importfieldname == FIELDNAME_BOOKINGTYPE)
        {
        }
        else if (importfieldname == FIELDNAME_ORDERREMARK)
        {
        }
        else if (importfieldname == FIELDNAME_POSREMARK)
        {
        }
        else if (importfieldname == FIELDNAME_PHARMACYPURCHASEPRICE)
        {
            if (!m_Felder.aep.strField.empty() && !IsDouble(m_Felder.aep.strField.c_str(), fieldErrMsg))
            {
                validationErr = true;
                m_output.format(GetMessage(CMSG_ORDIMPORT_FAILED_TO_VALIDATE_FIELD).c_str(), importfieldname.c_str(), fieldErrMsg.c_str());
                validationErrMsg += m_output + "\n";
            }
        }
        else if (importfieldname == FIELDNAME_GROSSPURCHASEPRICE)
        {
            if (!m_Felder.gep.strField.empty() && !IsDouble(m_Felder.gep.strField.c_str(), fieldErrMsg))
            {
                validationErr = true;
                m_output.format(GetMessage(CMSG_ORDIMPORT_FAILED_TO_VALIDATE_FIELD).c_str(), importfieldname.c_str(), fieldErrMsg.c_str());
                validationErrMsg += m_output + "\n";
            }
        }
        else if (importfieldname == FIELDNAME_PORTO)
        {
            if (!m_Felder.porto.strField.empty() && !IsDouble(m_Felder.porto.strField.c_str(), fieldErrMsg))
            {
                validationErr = true;
                m_output.format(GetMessage(CMSG_ORDIMPORT_FAILED_TO_VALIDATE_FIELD).c_str(), importfieldname.c_str(), fieldErrMsg.c_str());
                validationErrMsg += m_output + "\n";
            }
        }
        else if (importfieldname == FIELDNAME_ARTICLEDESCRIPTION)
        {
        }
        else if (importfieldname == FIELDNAME_DISCOUTPRECENTAGE)
        {
            if (!m_Felder.dicountpercentage.strField.empty() && !IsDouble(m_Felder.dicountpercentage.strField.c_str(), fieldErrMsg))
            {
                validationErr = true;
                m_output.format(GetMessage(CMSG_ORDIMPORT_FAILED_TO_VALIDATE_FIELD).c_str(), importfieldname.c_str(), fieldErrMsg.c_str());
                validationErrMsg += m_output + "\n";
            }
        }
        else if (importfieldname == FIELDNAME_VATLEVEL)
        {
            if (!m_Felder.vatlevel.strField.empty() && !IsInteger32(m_Felder.vatlevel.strField.c_str(), fieldErrMsg))
            {
                validationErr = true;
                m_output.format(GetMessage(CMSG_ORDIMPORT_FAILED_TO_VALIDATE_FIELD).c_str(), importfieldname.c_str(), fieldErrMsg.c_str());
                validationErrMsg += m_output + "\n";
            }
        }
        else if (importfieldname == FIELDNAME_HEADREMARK)
        {
        }
        else if (importfieldname == FIELDNAME_DATEVALUTA)
        {
            if (!m_Felder.datevaluta.strField.empty() && m_Felder.datevaluta.strField != "0" && !IsDate(m_Felder.datevaluta.strField.c_str(), fieldErrMsg))
            {
                validationErr = true;
                m_output.format(GetMessage(CMSG_ORDIMPORT_FAILED_TO_VALIDATE_FIELD).c_str(), importfieldname.c_str(), fieldErrMsg.c_str());
                validationErrMsg += m_output + "\n";
            }
        }
        else if (importfieldname == FIELDNAME_DATEDELAYEDDELIVERY)
        {
            // field type validation
            if (!m_Felder.datedelayeddelivery.strField.empty() && m_Felder.datedelayeddelivery.strField != "0" && !IsDate(m_Felder.datedelayeddelivery.strField.c_str(), fieldErrMsg))
            {
                validationErr = true;
                m_output.format(GetMessage(CMSG_ORDIMPORT_FAILED_TO_VALIDATE_FIELD).c_str(), importfieldname.c_str(), fieldErrMsg.c_str());
                validationErrMsg += m_output + "\n";
            }
        }
        else if (importfieldname == FIELDNAME_ORDERLABEL)
        {
        }
        else if (importfieldname == FIELDNAME_RESTDELIVARY)
        {
            // field type validation
            if (!m_Felder.restdelivery.strField.empty() && !IsInteger32(m_Felder.restdelivery.strField.c_str(), fieldErrMsg))
            {
                validationErr = true;
                m_output.format(GetMessage(CMSG_ORDIMPORT_FAILED_TO_VALIDATE_FIELD).c_str(), importfieldname.c_str(), fieldErrMsg.c_str());
                validationErrMsg += m_output + "\n";
            }
        }
        else if (importfieldname == FIELDNAME_SERVICETYPE)
        {
        }
        else if (importfieldname == FIELDNAME_SERVICE)
        {
        }

    }

    if (validationErr)
    {
        m_output = validationErrMsg;
        return 2;
    }
    return 0;
}

bool CSCOrderImport::GetRow(int orderIdx, int posIdx, std::vector<std::string>& outRow)
{
    int position;
    int fieldid;
    short grouping;
    int anzfields;
    std::vector<std::string> datelist;
    std::map<int, std::string>::iterator it;
    t_felder cur_Felder;
    std::string validationStatus = "Ok";
    std::string validationRemarks = "";
    char strOrderNr[64] = "";

    outRow.clear();

    // invalid indexes
    if (m_listOrders.size() <= orderIdx || (m_listOrders[orderIdx].listPositions.size() <= posIdx && m_listOrders[orderIdx].listPositions.size() > 0))
    {
        return false;
    }
    // + status and remarks colummns
    outRow.resize(formatMaxPosition + 3); 
    basar::VarString importfieldname;

    // get fields values and merge status/remarks of order/position
    m_listOrders[orderIdx].get(cur_Felder);
    if (m_listOrders[orderIdx].validationStatus != "Ok")
    {
        validationStatus = "Errors";
        // validation remarks are the messages detected while opening the order, useful only to add to remarks for the first postion in order
    }
    if (posIdx == 0 && m_listOrders[orderIdx].validationRemarks.length() > 0)
    {
        validationRemarks = m_listOrders[orderIdx].validationRemarks + '\n';
    }
    if (m_listOrders[orderIdx].listPositions.size() > posIdx)
    {
        m_listOrders[orderIdx].listPositions[posIdx].get(cur_Felder);
        if (m_listOrders[orderIdx].listPositions[posIdx].validationStatus != "Ok")
        {
            validationStatus = "Errors";
        }
        if (m_listOrders[orderIdx].listPositions[posIdx].validationRemarks.length() > 0)
        {
            validationRemarks += m_listOrders[orderIdx].listPositions[posIdx].validationRemarks + '\n';
        }
    }
    // if this is the last position in order merge order closing remarks
    if (posIdx == m_listOrders[orderIdx].listPositions.size()-1)
    {
        validationRemarks += m_listOrders[orderIdx].closingRemarks;
    }

    // store additional columns status/Remarks/OrderNr
    outRow[formatMaxPosition] = validationStatus;
    outRow[formatMaxPosition+1] = validationRemarks;
    sprintf(strOrderNr, "%ld", m_listOrders[orderIdx].OrderNr);
    outRow[formatMaxPosition + 2] = strOrderNr;

    // put required fields according to current format
    anzfields = formatMaxPosition;
    for (int index = 0; index < (int)m_format->getCSCOrderImportCSVColums()->size(); index++)
    {
        position = m_format->getCSCOrderImportCSVColums()->at(index)->getColumnNo();
        if (position > anzfields)
        {
            outRow.clear();
            return false;
         }
        fieldid = m_format->getCSCOrderImportCSVColums()->at(index)->getFieldNameId();
        grouping = m_format->getCSCOrderImportCSVColums()->at(index)->getGrouping();
        importfieldname.clear();
        if ((it = mapFieldIDToName.find(fieldid)) != mapFieldIDToName.end())
        {
            importfieldname = it->second;
        }

        if (importfieldname.empty())
        {
            outRow.clear();
            return false;
        }
        if (importfieldname == FIELDNAME_BRANCHNO)
        {
            outRow[position - 1] = cur_Felder.branchno.strField;
        }
        else if (importfieldname == FIELDNAME_CUSTOMERNO)
        {
            outRow[position - 1] = cur_Felder.customerno.strField;
        }
        else if (importfieldname == FIELDNAME_ORDERTYPE)
        {
            outRow[position - 1] = cur_Felder.ordertype.strField;
         }
        else if (importfieldname == FIELDNAME_PICKINGTYPE)
        {
            outRow[position - 1] = cur_Felder.pickingtype.strField;
         }
        else if (importfieldname == FIELDNAME_BOOKINGTYPE)
        {
            outRow[position - 1] = cur_Felder.bookingtype.strField;
        }
        else if (importfieldname == FIELDNAME_ORDERREMARK)
        {
            outRow[position - 1] = cur_Felder.orderremark.strField;
         }
        else if (importfieldname == FIELDNAME_ARTICLECODE)
        {
            outRow[position - 1] = cur_Felder.articlecode.strField;
         }
        else if (importfieldname == FIELDNAME_ORDERQTY)
        {
            outRow[position - 1] = cur_Felder.orderqty.strField;
        }
        else if (importfieldname == FIELDNAME_POSREMARK)
        {
            outRow[position - 1] = cur_Felder.posremark.strField;
        }
        else if (importfieldname == FIELDNAME_PHARMACYPURCHASEPRICE)
        {
            outRow[position - 1] = cur_Felder.aep.strField;
        }
        else if (importfieldname == FIELDNAME_GROSSPURCHASEPRICE)
        {
            outRow[position - 1] = cur_Felder.gep.strField;
         }
        else if (importfieldname == FIELDNAME_PORTO)
        {
            outRow[position - 1] = cur_Felder.porto.strField;
        }
        else if (importfieldname == FIELDNAME_ARTICLEDESCRIPTION)
        {
            outRow[position - 1] = cur_Felder.articledescription.strField;
         }
        else if (importfieldname == FIELDNAME_DISCOUTPRECENTAGE)
        {
            outRow[position - 1] = cur_Felder.dicountpercentage.strField;
         }
        else if (importfieldname == FIELDNAME_VATLEVEL)
        {
            outRow[position - 1] = cur_Felder.vatlevel.strField;
        }
        else if (importfieldname == FIELDNAME_HEADREMARK)
        {
            outRow[position - 1] = cur_Felder.headremark.strField;
        }
        else if (importfieldname == FIELDNAME_DATEVALUTA)
        {
            outRow[position - 1] = cur_Felder.datevaluta.strField;
        }
        else if (importfieldname == FIELDNAME_DATEDELAYEDDELIVERY)
        {
            outRow[position - 1] = cur_Felder.datedelayeddelivery.strField;
        }
        else if (importfieldname == FIELDNAME_ORDERLABEL)
        {
            outRow[position - 1] = cur_Felder.orderlabel.strField;
        }
        else if (importfieldname == FIELDNAME_RESTDELIVARY)
        {
            outRow[position - 1] = cur_Felder.restdelivery.strField;
        }
        else if (importfieldname == FIELDNAME_SERVICETYPE)
        {
            outRow[position - 1] = cur_Felder.servicetype.strField;
        }
        else if (importfieldname == FIELDNAME_SERVICE)
        {
            outRow[position - 1] = cur_Felder.service.strField;
        }
        else
        {
            outRow.clear();
            return false;
        }
    }
    return true;
}

void CSCOrderImport::InitFelder()
{
    m_Felder.branchno.Field = 0;
    m_Felder.branchno.strField.clear();
    m_Felder.branchno.IsGrouping = 0;
    m_Felder.customerno.Field = 0;
    m_Felder.customerno.strField.clear();
    m_Felder.customerno.IsGrouping = 0;
    m_Felder.ordertype.Field.clear();
    m_Felder.ordertype.strField.clear();
    m_Felder.ordertype.IsGrouping = 0;
    m_Felder.pickingtype.Field.clear();
    m_Felder.pickingtype.strField.clear();
    m_Felder.pickingtype.IsGrouping = 0;
    m_Felder.bookingtype.Field.clear();
    m_Felder.bookingtype.strField.clear();
    m_Felder.bookingtype.IsGrouping = 0;
    m_Felder.orderremark.Field.clear();
    m_Felder.orderremark.strField.clear();
    m_Felder.orderremark.IsGrouping = 0;
    m_Felder.articlecode.Field.clear();
    m_Felder.articlecode.strField.clear();
    m_Felder.articlecode.IsGrouping = 0;
    m_Felder.orderqty.Field = 0;
    m_Felder.orderqty.strField.clear();
    m_Felder.orderqty.IsGrouping = 0;
    m_Felder.posremark.Field.clear();
    m_Felder.posremark.strField.clear();
    m_Felder.posremark.IsGrouping = 0;
    m_Felder.aep.Field = 0;
    m_Felder.aep.strField.clear();
    m_Felder.aep.IsGrouping = 0;
    m_Felder.gep.Field = 0;
    m_Felder.gep.strField.clear();
    m_Felder.gep.IsGrouping = 0;
    m_Felder.porto.Field = 0;
    m_Felder.porto.strField.clear();
    m_Felder.porto.IsGrouping = 0;
    m_Felder.articledescription.Field.clear();
    m_Felder.articledescription.strField.clear();
    m_Felder.articledescription.IsGrouping = 0;
    m_Felder.dicountpercentage.Field = 0;
    m_Felder.dicountpercentage.strField.clear();
    m_Felder.dicountpercentage.IsGrouping = 0;
    m_Felder.vatlevel.Field = 0;
    m_Felder.vatlevel.strField.clear();
    m_Felder.vatlevel.IsGrouping = 0;
    m_Felder.headremark.Field.clear();
    m_Felder.headremark.strField.clear();
    m_Felder.headremark.IsGrouping = 0;
    m_Felder.datevaluta.Field = 0;
    m_Felder.datevaluta.strField.clear();
    m_Felder.datevaluta.IsGrouping = 0;
    m_Felder.datedelayeddelivery.Field = 0;
    m_Felder.datedelayeddelivery.strField.clear();
    m_Felder.datedelayeddelivery.IsGrouping = 0;
    m_Felder.orderlabel.Field.clear();
    m_Felder.orderlabel.strField.clear();
    m_Felder.orderlabel.IsGrouping = 0;
    m_Felder.restdelivery.Field = 0;
    m_Felder.restdelivery.strField.clear();
    m_Felder.restdelivery.IsGrouping = 0;
    m_Felder.servicetype.Field.clear();
    m_Felder.servicetype.strField.clear();
    m_Felder.servicetype.IsGrouping = 0;
    m_Felder.service.Field.clear();
    m_Felder.service.strField.clear();
    m_Felder.service.IsGrouping = 0;
    return;
}

void CSCOrderImport::CopyFelder()
{
    m_Felder_old = m_Felder;
}

bool CSCOrderImport::CheckGrouping()
{
    if((m_Felder_old.branchno.Field != m_Felder.branchno.Field) && (m_Felder.branchno.IsGrouping == 1) )
    {
        return true;
    }
    if ((m_Felder_old.customerno.Field != m_Felder.customerno.Field) && (m_Felder.customerno.IsGrouping == 1))
    {
        return true;
    }
    if ((m_Felder_old.ordertype.Field != m_Felder.ordertype.Field) && (m_Felder.ordertype.IsGrouping == 1))
    {
        return true;
    }
    if ((m_Felder_old.pickingtype.Field != m_Felder.pickingtype.Field) && (m_Felder.pickingtype.IsGrouping == 1))
    {
        return true;
    }
    if ((m_Felder_old.bookingtype.Field != m_Felder.bookingtype.Field) && (m_Felder.bookingtype.IsGrouping == 1))
    {
        return true;
    }
    if ((m_Felder_old.orderremark.Field != m_Felder.orderremark.Field) && (m_Felder.orderremark.IsGrouping == 1))
    {
        return true;
    }
    if ((m_Felder_old.articlecode.Field != m_Felder.articlecode.Field) && (m_Felder.articlecode.IsGrouping == 1))
    {
        return true;
    }
    if ((m_Felder_old.orderqty.Field != m_Felder.orderqty.Field) && (m_Felder.orderqty.IsGrouping == 1))
    {
        return true;
    }
    if ((m_Felder_old.posremark.Field != m_Felder.posremark.Field) && (m_Felder.posremark.IsGrouping == 1))
    {
        return true;
    }
    if ((m_Felder_old.aep.Field != m_Felder.aep.Field) && (m_Felder.aep.IsGrouping == 1))
    {
        return true;
    }
    if ((m_Felder_old.gep.Field != m_Felder.gep.Field) && (m_Felder.gep.IsGrouping == 1))
    {
        return true;
    }
    if ((m_Felder_old.porto.Field != m_Felder.porto.Field) && (m_Felder.porto.IsGrouping == 1))
    {
        return true;
    }
    if ((m_Felder_old.articledescription.Field != m_Felder.articledescription.Field) && (m_Felder.articledescription.IsGrouping == 1))
    {
        return true;
    }
    if ((m_Felder_old.articledescription.Field != m_Felder.articledescription.Field) && (m_Felder.articledescription.IsGrouping == 1))
    {
        return true;
    }
    if ((m_Felder_old.headremark.Field != m_Felder.headremark.Field) && (m_Felder.headremark.IsGrouping == 1))
    {
        return true;
    }
    if ((m_Felder_old.vatlevel.Field != m_Felder.vatlevel.Field) && (m_Felder.vatlevel.IsGrouping == 1))
    {
        return true;
    }
    if ((m_Felder_old.datevaluta.Field != m_Felder.datevaluta.Field) && (m_Felder.datevaluta.IsGrouping == 1))
    {
        return true;
    }
    if ((m_Felder_old.datedelayeddelivery.Field != m_Felder.datedelayeddelivery.Field) && (m_Felder.datedelayeddelivery.IsGrouping == 1))
    {
        return true;
    }
    if ((m_Felder_old.orderlabel.Field != m_Felder.orderlabel.Field) && (m_Felder.orderlabel.IsGrouping == 1))
    {
        return true;
    }
    if ((m_Felder_old.restdelivery.Field != m_Felder.restdelivery.Field) && (m_Felder.restdelivery.IsGrouping == 1))
    {
        return true;
    }
    if ((m_Felder_old.servicetype.Field != m_Felder.servicetype.Field) && (m_Felder.servicetype.IsGrouping == 1))
    {
        return true;
    }
    if ((m_Felder_old.service.Field != m_Felder.service.Field) && (m_Felder.service.IsGrouping == 1))
    {
        return true;
    }
    return false;
}

// typed validations functions
bool CSCOrderImport::IsInteger32(const char* input, std::string& errMsg)
{
    char errmsg[1024];
    int64_t v = 0;
    int cpos = 0;
    int neg = 0;
    int i = 0;
    int c = 0;
    int lenInput = (int)strlen(input);

    errMsg = "";
    // prepare generic error message 
    sprintf(errmsg, GetMessage(CMSG_ORDIMPORT_FAILURE_VALIDATE_INT).c_str(), input);

    if (input[0] == '-') {
        neg = 1;
        cpos++;
    }
    else if (input[0] == '+') {
        cpos++;
    }

    if (!isdigit((int)(input[cpos]))) 
    {
        errMsg = errmsg;
        return false;
    }
    // jump any left zeros
    while (input[cpos] == '0') {
        cpos++;
    }
    // convert left numbers to integer
    for (i = 0; cpos < lenInput; i++) 
    {
        c = input[cpos] - '0';
        if ((i > 10) || (c < 0 || c > 9)) 
        {
            errMsg = errmsg;
            return false;
        }
        v = v * 10 + c;
        cpos++;
    }

    if (v - neg > 2147483647) 
    {
        errMsg = errmsg;
        return false;
    }

    return true;
}

// dd.mm.yyyy format
bool CSCOrderImport::IsDate(const char* input, std::string& errMsg)
{
#define MAX_VALID_YR 9999
#define MIN_VALID_YR 1900

    std::string gErrMsg;
    char inCopy[CSV_MAX_COLUMN_SIZE] = "";
    char errmsg[1024] = "";
    char syear[8] = "";
    char smonth[4] = "";
    char sday[4] = "";
    int valYear = 0;
    int valMonth = 0;
    int valDay = 0;

    strncpy(inCopy, input, CSV_MAX_COLUMN_SIZE-1);
    TrimStr(inCopy);
    errMsg = "";
    // prepare generic error message 
    sprintf(errmsg, GetMessage(CMSG_ORDIMPORT_FAILURE_VALIDATE_DATE).c_str(), input);

    // check format
    // check length
    if (strlen(inCopy) != 10)
        return false;
    // separator are here ?
    if (inCopy[2] != '.' || inCopy[5] != '.')
    {
        errMsg = errmsg;
        return false;
    }

    memcpy(sday, &inCopy[0], 2);
    sday[2] = 0;
    memcpy(smonth, &inCopy[3], 2);
    smonth[2] = 0;
    memcpy(syear, &inCopy[6], 4);
    syear[4] = 0;

    // check if all of year, month day are integer
    if (!IsInteger32(sday, gErrMsg) || !IsInteger32(smonth, gErrMsg) || !IsInteger32(syear, gErrMsg))
    {
        errMsg = errmsg;
        return false;
    }

    valYear = atoi(syear);
    valMonth = atoi(smonth);
    valDay = atoi(sday);

    // If year, month and day are not in given range
    if ((valYear > MAX_VALID_YR || valYear < MIN_VALID_YR) || (valMonth < 1 || valMonth > 12) || (valDay < 1 || valDay > 31)) {
        errMsg = errmsg;
        return false;
    }

    // validate valDay according to the month/year
    switch (valMonth) {
    case 2:
        // Handle February month with leap year
        if (((((valYear % 4 == 0) && (valYear % 100 != 0)) || (valYear % 400 == 0))) && (valDay > 28)) {
            errMsg = errmsg;
            return false;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        // Handle Months of April, June, Sept and Nov must have number of days less than or equal to 30.
        if (valDay > 30) {
            errMsg = errmsg;
            return false;
        }
        break;
    }

    return true;
}

// nnnn,nnn format
bool CSCOrderImport::IsDouble(const char* input, std::string& errMsg)
{
    char inCopy[CSV_MAX_COLUMN_SIZE];
    char errmsg[1024];
    char* endptr = NULL;
    double val;
    int pos = 0;
    bool replaced = false;

    strncpy(inCopy, input, CSV_MAX_COLUMN_SIZE-1);
    errMsg = "";
    // prepare generic error message 
    sprintf(errmsg, GetMessage(CMSG_ORDIMPORT_FAILURE_VALIDATE_DOUBLE).c_str(), input);
    // replace any ',' by '.' should be only one
    while (inCopy[pos] != 0)
    {
        if (inCopy[pos] == ',')
        {
            if (!replaced)
            {
                inCopy[pos] = '.';
                replaced = true;
            }
            else
            {   // duplicated ',' char
                errMsg = errmsg;
                return false;
            }
        }
        pos++;
    }


    errno = 0;    /* reset errno to zero */
    val = strtod(inCopy, &endptr);

    // multiple values or out of range or out of float range ? error
    if ((*endptr != '\0') || (endptr == inCopy))
    {
        errMsg = errmsg;
        return false;
    }

    return true;
}

// should contain only numeric char after trimming
bool CSCOrderImport::IsNumericString(const char* input, std::string& errMsg)
{
    char errmsg[1024];
    char inCopy[CSV_MAX_COLUMN_SIZE];

    strncpy(inCopy, input, CSV_MAX_COLUMN_SIZE - 1);
    TrimStr(inCopy);
    errMsg = "";
    // prepare generic error message 
    sprintf(errmsg, GetMessage(CMSG_ORDIMPORT_FAILURE_VALIDATE_NUMSTRING).c_str(), input);
    // verify all chars are digits
    for (int i = 0; inCopy[i] != 0; i++) 
    {
        if (!isdigit((int)(inCopy[i]))) 
        {
            errMsg = errmsg;
            return false;
        }
    }

    return true;
}


// utils functions
void TrimStr(char* str, int lenStr) {
    size_t lenstr = (lenStr >= 0) ? (size_t)lenStr : strlen(str);
    char* tmpStr = NULL;
    char* ptrCpy = NULL;

    if (lenstr == 0)
        return;

    tmpStr = (char*)malloc(sizeof(char) * (lenstr + 1));
    ptrCpy = str;

    // jump starting white spaces
    while (lenstr > 0 && isspace(*ptrCpy)) {
        ptrCpy++;
        lenstr--;
    }
    // count endian white spaces
    while (lenstr > 0 && isspace(ptrCpy[lenstr - 1])) {
        lenstr--;
    }
    // copy result
    strncpy(tmpStr, ptrCpy, lenstr);
    tmpStr[lenstr] = 0;
    strcpy(str, tmpStr);
    free(tmpStr);
}

void splitStr(std::vector<std::string> &result, std::string& s, char delim) 
{
    std::stringstream ss(s);
    std::string item;

    result.clear();
    while (getline(ss, item, delim)) 
    {
        result.push_back(item);
    }
}

void toUpperStr(std::string& str)
{
    for (size_t i = 0; i < str.length(); i++)
    {
        str[i] = (char)std::toupper(str.c_str()[i]);
    }
}

std::string ExtractDirectory(const std::string& path)
{
    std::string dir = path.substr(0, path.find_last_of('/') + 1);
    if (dir.length() == 0)
    {
        return "./";
    }
    return dir;
}

void CsvRowToLine(std::vector<std::string> &csvRow, std::string &outLine, char csvDelimiter)
{
    char curChar = 0;

    outLine.clear();
    for (size_t j = 0; j < csvRow.size(); j++)
    {
        outLine += '"'; // starting quote
        for (size_t i = 0; i < csvRow[j].length(); i++)
        {
            curChar = csvRow[j].c_str()[i];
            outLine += curChar;
            // handle case of quote inside the column, by inserting double quotes
            if (curChar == '"') {
                outLine += curChar;
            }

        }
        outLine += '"'; // endian quote
        // insert delimiter if it's not the last column
        if (j < csvRow.size() - 1)
        {
            outLine += csvDelimiter;
        }
    }
}

// messages MAP

std::pair<OrdImpMessagesEnum, std::string> mapMessageDE_data[] =
{
    std::make_pair(CMSG_ORDIMPORT_PROCESSING,                         "Verarbeitung "),
    std::make_pair(CMSG_ORDIMPORT_EMPTY_LINE,                         "leere Zeile!"),
    std::make_pair(CMSG_ORDIMPORT_INVALID_FORMAT,                     "Falsches Format: "),
    std::make_pair(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD,            "Nicht alle Pflichtfelder gefüllt '%s'"),
    std::make_pair(CMSG_ORDIMPORT_UNKNOWN_SERVICE_TYPE,               "Service vom Typ %s nicht vorhanden"),
    std::make_pair(CMSG_ORDIMPORT_MISSING_ARTCODE_OR_ARTDESC,         "Weder PZN noch Artikelbezeichnung gefüllt\n"),
    std::make_pair(CMSG_ORDIMPORT_ARTCODE_NOTFOUND,                   "Artikel mit der Nummer %s nicht vorhanden"),
    std::make_pair(CMSG_ORDIMPORT_ORD_OPEN_FAILED,                    "Auftrag konnte nicht geoeffnet werden!"),
    std::make_pair(CMSG_ORDIMPORT_ORD_OPENED,                         "Auftrag %ld eröffnet für Filiale %d, IDF %d"),
    std::make_pair(CMSG_ORDIMPORT_ORD_TYPE_COMM_LABEL,                "Auftragsart %s, Kommiart %c, Buchungsart %c, Tour %s, Kennung %s"),
    std::make_pair(CMSG_ORDIMPORT_ORD_TYPE_COMM,                      "Auftragsart %s, Kommiart %c, Buchungsart %c, Tour %s"),
    std::make_pair(CMSG_ORDIMPORT_DATE_VALUE,                         " Valuta %ld.%ld.%ld"),
    std::make_pair(CMSG_ORDIMPORT_DATE_EXTRAD,                        " Auslieferung %ld.%ld.%ld"),
    std::make_pair(CMSG_ORDIMPORT_EMPTY_ORD_CANCELED,                 "Auftrag ohne gültigen Positionen storniert\n"),
    std::make_pair(CMSG_ORDIMPORT_ORD_CANCELED_VALID_INVALID,         "Auftrag storniert mit %d gültigen Positionen und %d ungültigen Positionen\n"),
    std::make_pair(CMSG_ORDIMPORT_ORD_CANCELED_VALID,                 "Auftrag storniert mit %d Positionen\n"),
    std::make_pair(CMSG_ORDIMPORT_ORD_OK_VALID_INVALID,               "Auftrag mit %d Positionen und %d ungültigen Positionen\n"),
    std::make_pair(CMSG_ORDIMPORT_ORD_OK_VALID,                       "Auftrag mit %d Positionen\n"),
    std::make_pair(CMSG_ORDIMPORT_SERVICETYPE_NOTFOUND,               "Service mit der Nummer %s nicht vorhanden"),
    std::make_pair(CMSG_ORDIMPORT_SERVICE_NOTFOUND,                   "Service vom Typ %s nicht vorhanden"),
    std::make_pair(CMSG_ORDIMPORT_VAT_RATE_MUST,                      "MwSt Satz muss 0 = FULLTAX oder 1 = HALFTAX oder in taxrates Tabelle enthalten sein"),
    std::make_pair(CMSG_ORDIMPORT_ARTCODE_QUANTITY_FAILED,            "   Artikelanzahl %d für PZN nicht gebucht   %s"),
    std::make_pair(CMSG_ORDIMPORT_ARTCODE_CONFIRMED_ORD_QUANTITY,     "   Artikelanzahl %ld gebucht, ursprünglich bestellt %ld für PZN %s   %s"),
    std::make_pair(CMSG_ORDIMPORT_MISSING_FIELD,                      "Format definiert %d Spalten - Datei enthält jedoch nur %d Spalten"),
    std::make_pair(CMSG_ORDIMPORT_UNKNOW_FIELD_TYPE_FORMAT,           "Unbekannter Feldtyp im Format"),
    std::make_pair(CMSG_ORDIMPORT_UNKNOW_FIELD_TYPE,                  "Unbekannter Feldtyp"),
    std::make_pair(CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD_LINE,       "Pflichtfeld %s in Zeile %d nicht versorgt"),
    std::make_pair(CMSG_ORDIMPORT_UNKNOW_FIELD_TYPE_LINE,             "Unbekannter Feldtyp in Zeile %d"),
    std::make_pair(CMSG_ORDIMPORT_ORD_CREATED_POSTIONS,               "%d Aufträge mit insgesamt %d Positionen erstellt"),
    std::make_pair(CMSG_ORDIMPORT_CREATE_ORD_OUTOF_SESSION_BRANCH,    "Auftrag für Filiale %d, passt nicht zur Anmeldung des Benutzers in Filiale %d"),
    std::make_pair(CMSG_ORDIMPORT_SUCCESS_FETCH_ORDERS,               "%i Aufträge erfolgreich aus %i Zeilen erstellt"),
    std::make_pair(CMSG_ORDIMPORT_FAIL_FETCH_ORDERS,			       "Auftragsdatei enthält Fehler: %i gültige Aufträge, %i ungültige Aufträge, %i Fehler in Datenzeilen"),
    std::make_pair(CMSG_ORDIMPORT_STATUS,                             "Status"),
    std::make_pair(CMSG_ORDIMPORT_REMARKS,                            "Bemerkungen"),
    std::make_pair(CMSG_ORDIMPORT_ORDER_NR,                           "Auftrag Nr"),
    std::make_pair(CMSG_ORDIMPORT_GETFORMAT_FAILURE,                  "Fehler beim Abrufen von Format - ID = %i - %s"),
    std::make_pair(CMSG_ORDIMPORT_FAILURE_VALIDATE_INT,               "Fehler beim Validieren des Integer-Felds! Aktueller Wert '%s'"),
    std::make_pair(CMSG_ORDIMPORT_FAILURE_VALIDATE_DOUBLE,            "Fehler beim Validieren des double-Felds! format [nnnn,nn] aktueller Wert'%s'"),
    std::make_pair(CMSG_ORDIMPORT_FAILURE_VALIDATE_DATE,	           "Datumsfeld konnte nicht validiert werden! format [dd.mm.yyyy] aktueller Wert '%s'"),
    std::make_pair(CMSG_ORDIMPORT_FAILURE_VALIDATE_NUMSTRING,         "Fehler beim Validieren der numerischen Zeichenfolge: Feld! Aktueller Wert '%s'"),
    std::make_pair(CMSG_ORDIMPORT_USED_FORMAT,                        "Lese Datei über Format: %ld - %s"),
    std::make_pair(CMSG_ORDIMPORT_OPEN_FILE_ERROR,                    "Fehler beim öffnen der Datei: %s (Datei nicht gefunden oder Berechtigungen fehlen)"),
    std::make_pair(CMSG_ORDIMPORT_CREATE_ORDERS_FAILED,               "Fehler beim Anlegen neuer Aufträge - Details siehe Reportdatei: %s"),
    std::make_pair(CMSG_ORDIMPORT_IMPORT_FORMAT_FAILED,               "Datei '%s'konnte mit Format %ld - '%s' nicht importiert werden - Details können dem Report '%s' entnommen werden."),
    std::make_pair(CMSG_ORDIMPORT_FAILED_TO_VALIDATE_FIELD,           "Fehler bei der Validierung von Feld [%s]: %s")
};

std::map< OrdImpMessagesEnum, std::string > OrdImpMessagesMapDE(mapMessageDE_data,  mapMessageDE_data + sizeof mapMessageDE_data / sizeof mapMessageDE_data[0]);

std::pair<OrdImpMessagesEnum, std::string> mapMessageEN_data[] =
{
    std::make_pair( CMSG_ORDIMPORT_PROCESSING,                         "Processing  "),
    std::make_pair( CMSG_ORDIMPORT_EMPTY_LINE,                         "empty line!"),
    std::make_pair( CMSG_ORDIMPORT_INVALID_FORMAT,                     "Invalid Format: "),
    std::make_pair( CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD,            "Missing mandatory field '%s'"),
    std::make_pair( CMSG_ORDIMPORT_UNKNOWN_SERVICE_TYPE,               "Service type '%s' does not exist"),
    std::make_pair( CMSG_ORDIMPORT_MISSING_ARTCODE_OR_ARTDESC,         "At least one of articlecode or articledescription should be filled"),
    std::make_pair( CMSG_ORDIMPORT_ARTCODE_NOTFOUND,                   "ArticleCode %s not found"),
    std::make_pair( CMSG_ORDIMPORT_ORD_OPEN_FAILED,                    "Order could not be opened!"),
    std::make_pair( CMSG_ORDIMPORT_ORD_OPENED,                         "Order %ld opened for branch %d, CustomerNo %d"),
    std::make_pair( CMSG_ORDIMPORT_ORD_TYPE_COMM_LABEL,                "OrderType %s, commission %c, Booking type %c, Tour %s, Label %s"),
    std::make_pair( CMSG_ORDIMPORT_ORD_TYPE_COMM,                      "OrderType %s, commission %c, Booking type %c, Tour %s"),
    std::make_pair( CMSG_ORDIMPORT_DATE_VALUE,                         " ValueDate %ld.%ld.%ld"),
    std::make_pair( CMSG_ORDIMPORT_DATE_EXTRAD,                        " ShipingDate %ld.%ld.%ld"),
    std::make_pair( CMSG_ORDIMPORT_EMPTY_ORD_CANCELED,                 "Order cancelled because there are no valid items\n"),
    std::make_pair( CMSG_ORDIMPORT_ORD_CANCELED_VALID_INVALID,         "Order cancelled with %d positions and %d invalid positions\n"),
    std::make_pair( CMSG_ORDIMPORT_ORD_CANCELED_VALID,                 "Order Cancelled with %d Positions\n"),
    std::make_pair( CMSG_ORDIMPORT_ORD_OK_VALID_INVALID,               "Order with %d positions and %d invalid positions\n"),
    std::make_pair( CMSG_ORDIMPORT_ORD_OK_VALID,                       "Order with %d positions\n"),
    std::make_pair( CMSG_ORDIMPORT_SERVICETYPE_NOTFOUND,               "Service Type %s not found"),
    std::make_pair( CMSG_ORDIMPORT_SERVICE_NOTFOUND,                   "Service %s does not exist or is not assigned to Service Type %s"),
    std::make_pair( CMSG_ORDIMPORT_VAT_RATE_MUST,                      "VAT rate must be 0 = FULLTAX or 1 = HALFTAX or included in taxrates table"),
    std::make_pair( CMSG_ORDIMPORT_ARTCODE_QUANTITY_FAILED,            "   quantity %d for ArticleCode %s failed  %s"),
    std::make_pair( CMSG_ORDIMPORT_ARTCODE_CONFIRMED_ORD_QUANTITY,     "   Position ordered quantity %ld confirmed quantity %ld ArticleCode %s  %s"),
    std::make_pair( CMSG_ORDIMPORT_MISSING_FIELD,                      "Format reference column %d but input file contains only %d columns"),
    std::make_pair( CMSG_ORDIMPORT_UNKNOW_FIELD_TYPE_FORMAT,           "Unknown Field Type in Format"),
    std::make_pair( CMSG_ORDIMPORT_UNKNOW_FIELD_TYPE,                  "Unknown field type"),
    std::make_pair( CMSG_ORDIMPORT_MISSING_MANDATORY_FIELD_LINE,       "Mandatory field %s not supplied in line %d"),
    std::make_pair( CMSG_ORDIMPORT_UNKNOW_FIELD_TYPE_LINE,             "Unknown Field Type in line %d" ),
    std::make_pair( CMSG_ORDIMPORT_ORD_CREATED_POSTIONS,               "%d Orders created with %d total Positions" ),
    std::make_pair( CMSG_ORDIMPORT_CREATE_ORD_OUTOF_SESSION_BRANCH,    "Trying to create order in branch %d, outside user session branch %d"),
    std::make_pair( CMSG_ORDIMPORT_SUCCESS_FETCH_ORDERS,               "Successfully fetched %i orders for a total of %i rows"),
    std::make_pair( CMSG_ORDIMPORT_FAIL_FETCH_ORDERS,			       "Failed Fetching Orders: %i valid orders, %i invalid orders, %i bad rows detected"),
    std::make_pair( CMSG_ORDIMPORT_STATUS,                             "Status"),
    std::make_pair( CMSG_ORDIMPORT_REMARKS,                            "Remarks"),
    std::make_pair( CMSG_ORDIMPORT_ORDER_NR,                           "Order Nr"),
    std::make_pair( CMSG_ORDIMPORT_GETFORMAT_FAILURE,                  "Failed to select Format ID = %i - %s"),
    std::make_pair( CMSG_ORDIMPORT_FAILURE_VALIDATE_INT,               "Failed to validate Integer Field! current value '%s'"),
    std::make_pair( CMSG_ORDIMPORT_FAILURE_VALIDATE_DOUBLE,            "Failed to validate double Field! format [nnnn,nn] current value '%s'"),
    std::make_pair( CMSG_ORDIMPORT_FAILURE_VALIDATE_DATE,	           "Failed to validate date Field! format [dd.mm.yyyy] current value '%s'"),
    std::make_pair( CMSG_ORDIMPORT_FAILURE_VALIDATE_NUMSTRING,         "Failed to validate numeric string Field! current value '%s'"),
    std::make_pair( CMSG_ORDIMPORT_USED_FORMAT,                        "Processing file using Format: %ld - %s"),
    std::make_pair( CMSG_ORDIMPORT_OPEN_FILE_ERROR,                    "Can't open file %s (Possible file not found or missing permissions)"),
    std::make_pair( CMSG_ORDIMPORT_CREATE_ORDERS_FAILED,               "Fatal error on creation of new orders, see details in report file: %s"),
    std::make_pair( CMSG_ORDIMPORT_IMPORT_FORMAT_FAILED,               "Can't import File '%s', using Format %ld - '%s' - see details in report file '%s'"),
    std::make_pair( CMSG_ORDIMPORT_FAILED_TO_VALIDATE_FIELD,           "Failed to validate Field [%s]: %s")
};

std::map< OrdImpMessagesEnum, std::string > OrdImpMessagesMapEN(mapMessageEN_data, mapMessageEN_data + sizeof mapMessageEN_data / sizeof mapMessageEN_data[0]);
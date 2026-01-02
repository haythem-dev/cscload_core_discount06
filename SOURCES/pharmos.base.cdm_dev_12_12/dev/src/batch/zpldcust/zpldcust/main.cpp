//-------------------------------------------------------------------------------------------------//
/*! \file   main.cpp
 *  \brief  application (main) functions for zpldcust load customer
 *  \author Frank Naumann
 *  \date   25.03.2010
 */
//-------------------------------------------------------------------------------------------------//

#include "commonheader.h"
#include "loadcustomerappl.h"
#include "zpldcust_definitions.h"
#include "loggerpool.h"
#include "version.h"


#include "../../../cdm_version.h"

//-------------------------------------------------------------------------------------------------//

/*! \brief prints the version of the program to stdout.
 */
void version()
{
  printf("\n === zpldcust --> Version: =============================================\n");
  printf("\n   CDM: <%s> - %-10s: <%02d.%02d.%02d.%02d>\n",
    CDM_VERSION, 
    APPLICATION_NAME,
	VERSION_MAJORNO, VERSION_MINORNO, VERSION_EXTENSION, VERSION_BUILDNO);
  printf("   %-10s: <%s>\n", "SSUK", PRODUCT_NUMBER);
  printf("\n ========================================================================\n");
}

//-------------------------------------------------------------------------------------------------//

/*! \brief prints the usage of the program to stdout.
 */
void usage()
{
  printf("\n === zpldcust.bin --> Usage: ========================================\n");
  printf("PARAMETER: -branchno <branchno> [-mode <mode>]\n");
  printf("  MODE: \"full\" Load ALL articles from VSAM.DKKUL to ccustomermaindata\n");
  printf("  MODE: \"last\" Load only changes since last work day  from VSAM.DKKUL to ccustomermaindata\n");
  printf("  If no mode is specified, \"last\" is the default\n");
  printf("\n ========================================================================\n");
}

//-------------------------------------------------------------------------------------------------//

/*! \brief main entry point of zpldcust.
 *  \param argc argument count.
 *  \param argv argument array.
 */
int main(int argc, char *argv[])
{
  EventReturnStruct ret;

  if (argc == 2 && strcmp(argv[1], zpldcust::PARAM_VERSION) == 0) 
  {
    version();
    ::exit(0);
  }

  // read branchno + mode, given via calling- parameter
  if (argc != 3 && argc != 5)
  {
    usage();
    ::exit(0);
  }

  try
  {
    Int16                           branchNo = 0;
    VarString                       mode = zpldcust::MODE_LAST;
    I18nString                      searchStr;
    AccessorPropertyTable_YIterator yit;

    if (strcmp(argv[1], zpldcust::PARAM_BRANCHNO) == 0)
      branchNo = static_cast<basar::Int16>(atoi(argv[2]));
    if (argc == 5)
      if (strcmp(argv[3], zpldcust::PARAM_MODE) == 0)
        mode = argv[4];

    if ( branchNo <= 0)
    {
      printf("branch must be set and be greater than 0!\n");
      zpldcust::LoadCustomerAppl::clear();
      basar::login::Manager::clear();
      basar::db::aspect::Manager::clear();
      return 0;
    }

    searchStr.format("%s=%d;%s=%s",
      lit::zpldcust::BRANCHNO.getName().c_str(), branchNo,
      lit::zpldcust::MODE.getName().c_str(), mode.c_str());

    yit = basar::db::aspect::Manager::getInstance().createAccessorYIterator(searchStr);
    ret = zpldcust::LoadCustomerAppl::getInstance().run(NullEventSource::getInstance(), yit);

    if (ret.ret != basar::appl::HANDLER_OK)
    {
      printf(ret.message.c_str());
      printf("\n");
	  
	  if (ret.ret == basar::appl::HANDLER_INFO) // to avoid returning HANDLER_INFO (!= 0) to start_process
		  ret.ret = basar::appl::HANDLER_OK;
    }
  }
  catch (const basar::db::sql::DbException & except)
  {
    printf("\n === basar db exception caught ===========================================================\n\n");
    printf("%s\n", except.what().c_str());
    BLOG_ERROR(zpldcust::LoggerPool::zpldcust, except.what().c_str());
    return basar::appl::HANDLER_ERROR;
  }
  catch (const basar::Exception & except)
  {
    printf("\n === basar exception caught ===========================================================\n\n");
    printf("%s\n", except.what().c_str());
    BLOG_ERROR(zpldcust::LoggerPool::zpldcust, except.what().c_str());
    return basar::appl::HANDLER_ERROR;
  }
  catch (const std::exception & except)
  {
    printf("\n === std exception caught ===========================================================\n");
    printf("%s\n", except.what());
    BLOG_ERROR(zpldcust::LoggerPool::zpldcust, "=== std exception caught ===");
    return basar::appl::HANDLER_ERROR;
  }
  catch (...)
  {
    printf("\n === unknown exception caught ===========================================================\n");	
    BLOG_ERROR(zpldcust::LoggerPool::zpldcust, "=== unknown exception caught ===");
    return basar::appl::HANDLER_ERROR;
  }

  zpldcust::LoadCustomerAppl::clear();
  basar::login::Manager::clear();
  basar::db::aspect::Manager::clear();

#ifdef WIN32
#ifndef NDEBUG
  getchar();
#endif // NDEBUG
#endif // WIN32
  return ret.ret;
}

//-------------------------------------------------------------------------------------------------//

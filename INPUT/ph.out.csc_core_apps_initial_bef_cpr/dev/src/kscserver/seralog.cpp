#include <stdlib.h>
#include <string>
#include "string.hpp"
#include "time.hpp"
#include "seralog.hpp"
#ifdef unix
extern "C" {
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
extern int mkdir(const char*, mode_t);
}
#else
#include <io.h>
#include <direct.h>
#define F_OK 00
#define W_OK 02
#endif

// ---------------------------------------------------------------------
// Create directory and path name.
// ---------------------------------------------------------------------
nSeraLog :: nSeraLog() :
    environmentpath_(getenv("SERALOG"))

{
    timestamp_.SetNow();
    Init();
}

// ---------------------------------------------------------------------
// Clear the list.
// ---------------------------------------------------------------------
nSeraLog :: ~nSeraLog()
{
    strcoll_.clear();
}

// ---------------------------------------------------------------------
// Construct part of the subdirectory name. (ddmmyyyy)
// ---------------------------------------------------------------------
const nString nSeraLog :: Subname()
{
    nString day, month, year;

    // Get current day
    year = timestamp_.GetYear();
    month = timestamp_.GetMonth();
    day = timestamp_.GetDay();

    // Format the strings.
    day.Trim(2, nString::cLEADING, '0');
    month.Trim(2, nString::cLEADING, '0');
    year.Trim(4, nString::cLEADING, '0');

    return day + month + year;
}

// ---------------------------------------------------------------------
// Create the name of the path.
// If neccessary create the directory.
// Finally check, if we have permission to write into it.
// ---------------------------------------------------------------------
void nSeraLog :: CreateDir
(
 const nString& subdir
)
{
    // Get contents of environment variable.
    path_ = environmentpath_;

    // Test, if we have permission to write.
#ifdef WIN32
    if (_access(path_, W_OK) == -1)
#else
    if (access(path_, W_OK) == -1)
#endif
        path_ = ".";

    path_ += "/";

    nString fullpath;

    // Construct full path name
    fullpath = path_ + "ORD" + subdir;

    // Does the directory exist.
#ifdef WIN32
    if (_access(fullpath, F_OK) == -1)
#else
    if (access(fullpath, F_OK) == -1)
#endif
    {
        // We try to create it.
#ifdef unix
        mkdir(fullpath, S_IRWXU | S_IRWXG | S_IRWXO);
#else
        _mkdir(fullpath);
#endif
    }

    // Finally test, if we have permission to write.
#ifdef WIN32
    if (_access(fullpath, W_OK) == 0)
#else
    if (access(fullpath, W_OK) == 0)
#endif
        path_ = fullpath + "/";

}

// ---------------------------------------------------------------------
// Set to initalized values.
// ---------------------------------------------------------------------
void nSeraLog :: Init()
{
    idfnr_.clear();
    strcoll_.clear();
    MustWrite         = false;
    WriteMessageList  = false;
    SeraFile_Open     = false;
}

// ---------------------------------------------------------------------
// Dafue starts, so set to current time.
// ---------------------------------------------------------------------
void nSeraLog :: Start()
{
    timestamp_.SetNow();
}

// ---------------------------------------------------------------------
// We Open the file, if we have a idfnr (after SA01).
//  - we built the full path file name
//  - we open the file and hold this state
// ---------------------------------------------------------------------
void nSeraLog :: Open()
{
    // Have we a valid order ?
    if (!idfnr_.empty() &&  !SeraFile_Open )
    {

        // Get current date.
        nString subdir;
        subdir = Subname();

        // Must we create a new directory ?
        // (Contains path_ the environment variable and current date ?)
        if (path_.FindSubString(subdir) > path_.Length() ||
            path_.FindSubString(environmentpath_) > path_.Length())
        {
            CreateDir(subdir);
        }

        // Construct full file name.
        nString fullname_ = path_ + "O"
            + idfnr_.c_str()
            + termid_.c_str()
            + timestamp_.AsString("%H%M%S");

        // Open it.
        serafile_.open(fullname_);
        if (serafile_.good())
          SeraFile_Open = true;
        else
        {
          serafile_.close();
          Init();
        }
    }
}

// ---------------------------------------------------------------------
// Write one dafue message.
// If this is the last message, we write the file.
// ---------------------------------------------------------------------
void nSeraLog :: Write
(
 const nString& line
)
{
    WriteFile( line );
}

// ---------------------------------------------------------------------
// Dafue end of data, Dafue has to send now data
// ---------------------------------------------------------------------
void nSeraLog :: WriteList()
{
    WriteMessageList = true;
}
// ---------------------------------------------------------------------
// Dafue disconnects, the order closes.
// ---------------------------------------------------------------------
void nSeraLog :: End()
{
    MustWrite = true;
}

// ---------------------------------------------------------------------
// Dafue disconnects, the order closes.
// ---------------------------------------------------------------------
void nSeraLog :: CloseSeralog()
{
    if ( MustWrite )
    {
       serafile_.close();
       strcoll_.clear();
       Init();
    }
}

// ---------------------------------------------------------------------
// if the file is open and writesofar = true we
// write the list to the file, Clear the list
// otherwise
// we write the current message to the file
// ---------------------------------------------------------------------
void nSeraLog :: WriteFile
(
 const nString& line
)
{
    if ( !SeraFile_Open )
       strcoll_.push_back(line());

    if ( SeraFile_Open )
    {
       if ( WriteMessageList )
       {
          std::list<std::string>::iterator it = strcoll_.begin();
          while (it != strcoll_.end())
          {
              serafile_ << (*it) << std::endl;
              ++it;
          }
          strcoll_.clear();
          WriteMessageList = false;
       }
       serafile_ << line() << std::endl;
    }

    if ( MustWrite )
    {
       serafile_.close();
       Init();
    }
}

// ---------------------------------------------------------------------
// Sets the idfnr and trim it to seven chars.
// ---------------------------------------------------------------------
void nSeraLog :: SetIDFNr
(
 const std::string& idfnr
)
{
    idfnr_ = idfnr;
}

// ---------------------------------------------------------------------
// Sets the terminalid (It is 4 chars).
// ---------------------------------------------------------------------
void nSeraLog :: SetTerminalID
(
 const std::string& termid
)
{
    termid_ = termid;
}

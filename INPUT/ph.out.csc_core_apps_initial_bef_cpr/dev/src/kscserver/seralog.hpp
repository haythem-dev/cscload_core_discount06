/*
 ******************** C/C++ Application Program Services **********************

                 (c) Copyright 1995/96 by NORDAT NetWork GmbH
                              All rights reserved

seralog.hpp
This class writes the transmissions into files.

DESCRIPTION

    This class tries to realize the seralog. It writes the transmission for
    the orders in separate files.

    The file name is :

        - contents of environment variable SERALOG  (existing directory)
        - plus "ORD" + ddmmyyyy + "/"               (subdirectory)
        - plus "O" + idfnr + terminalid + timestamp (filename)

    The directory SERALOG exists and we create the subdirectory if we can do
    it. In the subdirectory we create the files which contain the transmission
    messages (each line contains one message).

*/

#ifndef NSERALOG_INC
#define NSERALOG_INC

#include <list>
#include <fstream>
#include <time.hpp>


class nSeraLog
{
public:
    nSeraLog();
    virtual ~nSeraLog();

    // Sets the idfnr with 7 digits.
    void SetIDFNr(const std::string& idfnr);

    // Sets the terminalid.
    void SetTerminalID(const std::string& termid);

    // Write dafue message.
    void Write(const nString&);

    // Dafue starts / ends.
    void Start();
    void End();
    void WriteList();
    void Open();
    void CloseSeralog();

private:
    nString environmentpath_;   // Name of environment variable SERALOG
    nString path_;              // Path to directory
    std::string idfnr_;         // Current idfnr
    std::string termid_;        // Current terminalid
    nTime   timestamp_;         // Time of dafue start
    std::ofstream serafile_;    // filepointer
    std::list<std::string> strcoll_;    // Dafue messages
    bool    MustWrite;          // Dafue ends
    bool    WriteMessageList;   // Write collected list to file
    bool    SeraFile_Open;      // seralog file open state

    // Initialize the private datas.
    void Init();

    // Write the messages into the file.
    void WriteFile(const nString&);

    // Create the subdirectory
    void CreateDir(const nString&);

    // Create part of subdirectory name.
    const nString Subname();

};

#endif

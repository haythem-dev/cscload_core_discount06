/*
 ******************** C/C++ Application Program Services **********************

                 (c) Copyright 1995 by NORDAT NetWork GmbH
                              All rights reserved

Implementation of class nSectionHdl.

REVISION HISTORY

 2 Oct 1995 V1.00 REV 00 written by Carsten Krabiell.

*/
/*  $History: NSECFILE.CPP $ */
/*  */
/* *****************  Version 7  ***************** */
/* User: Ck           Date: 18.07.96   Time: 14:05 */
/* Updated in $/cxxtools/src */
/* Final release. */
/* *********************************************** */
#include "nsecfile.hpp"
#include <stdio.h>
#include "nntypes.h"

// Interface to get nString from nString streamio.
class nStr
{
    nString temp;

public:

    nString& ReadToDelimiter(std::istream& strm, const nString& delim)
    {
        temp.ReadToDelimiter(strm, delim);
        return temp;
    }
};

// Copy the 'filename' and open the stream.
nSectionHdl::nSectionHdl(const nString& filename) :
    sectionfilename(filename)
{
    // Open the stream (not create it).
    sectionfile = new std::ifstream;
    sectionfile->open((char*)sectionfilename, std::ios_base::in);

    // Clear previous error flags of the file.
    sectionfile->clear();
    sectionfile->seekg(std::ios_base::beg);

    // Is it open ?
    sectionfilefound = sectionfile->good();
}

// Attach the file.
nSectionHdl::nSectionHdl(std::ifstream* infile)
{
    sectionfilename.Clear();

    // Set the stream.
    sectionfile = infile;

    // Clear previous error flags of the file.
    sectionfile->clear();
    sectionfile->seekg(std::ios_base::beg);

    // Is it open ?
    sectionfilefound = sectionfile->good();
}


// Close the file. The nStrings are automatically destroyed.
nSectionHdl::~nSectionHdl()
{
    // Close file if nSectionHdl has opened it.
    if (!sectionfilename.IsEmpty())
    {
        if (sectionfilefound)
            sectionfile->close();

        delete sectionfile;
    }
}

// Overread rest of line (include EOL).
void nSectionHdl::IgnoreRestOfLine(void)
{
    while (   sectionfile->good() && !sectionfile->eof()
           && (static_cast<char>(sectionfile->get()) != '\n') )
    ;
}

// Try to find the first section name in section file
bool nSectionHdl::GotoBeginOfFile()
{
    if (sectionfilefound && !sectionfile->bad() && !sectionfile->fail())
    {
        // Go to beginning of file.
        sectionfile->clear();
        sectionfile->seekg(std::ios_base::beg);

        return true;
    }
    else
        return false;
}

// Try to find the name of the next loadable section in section file
bool nSectionHdl::GetNextSection(nString& sectionname)
{
    if (sectionfilefound && !sectionfile->bad() && !sectionfile->fail())
    {
        bool found = false;
        sectionname.Clear();

        while (sectionfile->good() && !found)
        {
            // Read to beginning of a section.
            while (sectionfile->good() && !sectionfile->eof() && (sectionfile->get() != cSECTIONBEGIN))
            ;

            if (!sectionfile->eof() && sectionfile->good())
            {
                // Read the current sectionname and compress it.
                nString name, restofline;
                name.ReadToDelimiter(*sectionfile, (nString)cSECTIONEND);
                restofline.ReadToDelimiter(*sectionfile, (nString) cNEWLINE);
                if ((restofline.Length() >= 2) && (restofline[0U] == cSECTIONEND) && (restofline[1U] == cMARKLOADABLE))
                {
                    name.Compress(' ');
                    sectionname = name;
                    found = true;
                }
            }
        }

        if (sectionfile->bad() || sectionfile->fail())
            return sectionfilefound = false;
        else
            return found;
    }
    else  // Stream is corrupt !
        return sectionfilefound = false;
}


// Try to find the section beginning with 'sectionname'.
bool nSectionHdl::ExistSection(const nString& sectionname)
{
    // Copy sectionname and trim it.
    nString copysectionname = sectionname;
    copysectionname.Compress(' ');

    if (sectionfilefound && !sectionfile->bad() && !sectionfile->fail())
    {
        bool found = false;

        // Go to beginning of file.
        sectionfile->clear();
        sectionfile->seekg(std::ios_base::beg);

        //while (!sectionfile->eof() && !sectionfile->bad() && !sectionfile->fail() && !found)
        while (sectionfile->good() && !found)
        {
            // Read to beginning of a section.
            while (sectionfile->good() && !sectionfile->eof() && (sectionfile->get() != cSECTIONBEGIN))
            ;

            if (!sectionfile->eof() && sectionfile->good())
            {
                nStr cursecname;     // current sectionname

                // Read the current sectionname.
                if (copysectionname == cursecname.ReadToDelimiter(*sectionfile, (nString)cSECTIONEND).Compress(' '))
                {
                    found = true;
                }

                IgnoreRestOfLine();
            }
        }

        if (sectionfile->bad() || sectionfile->fail())
            return sectionfilefound = false;
        else
            return found;
    }
    else  // Stream is corrupt !
        return sectionfilefound = false;
}

// Reads the next section text
const nString& nSectionHdl::GetSectionTxt()
{
    // Initiate the sectiontxt.
    sectiontxt.Clear();

    if (sectionfilefound)
    {
        bool ready = false;

        while (!ready)
        {
            // Overread comments standing after the sectionname
            while (sectionfile->good() && sectionfile->peek() == cCOMMENT)
                IgnoreRestOfLine();

            // Ready with reading ?
            if (sectionfile->eof() || sectionfile->peek() == cSECTIONBEGIN)
            {
                ready = true;

                // Return empty string, if stream is corrupt.
                if (sectionfile->bad() || sectionfile->fail())
                    sectiontxt.Clear();
            }
            else
            {
                // Read the text until cSECTIONBEGIN or cCOMMENT.
                nStr tempsectxt;
                sectiontxt += tempsectxt.ReadToDelimiter(*sectionfile, (nString)cSECTIONBEGIN + (nString)cCOMMENT);
            }
        }
    }

    return sectiontxt;
}

// Try to find the section and read the text.
const nString& nSectionHdl::GetSectionTxt(const nString& sectionname)
{
    // Init. the sectiontxt.
    sectiontxt.Clear();

    if (sectionfilefound && ExistSection(sectionname))
    {
        bool ready = false;

        while (!ready)
        {
            // Overread comments standing after the sectionname
            while (sectionfile->good() && sectionfile->peek() == cCOMMENT)
                IgnoreRestOfLine();

            // Ready with reading ?
            if (sectionfile->eof() || sectionfile->peek() == cSECTIONBEGIN)
            {
                ready = true;

                // Return empty string, if stream is corrupt.
                if (sectionfile->bad() || sectionfile->fail())
                    sectiontxt.Clear();
            }
            else
            {
                // Read the text until cSECTIONBEGIN or cCOMMENT.
                nStr tempsectxt;
                sectiontxt += tempsectxt.ReadToDelimiter(*sectionfile, (nString)cSECTIONBEGIN + (nString)cCOMMENT);
            }
        }
    }

    return sectiontxt;
}

// Return the entire sectiontext.
const nString& nSectionHdl::PrintSectionTxt(const nString* sectionname, ...)
{
    va_list vptr;
    va_start(vptr, sectionname);

    PrintSectionTxt(sectionname, vptr);

    va_end(vptr);

    return sectiontxt;
}

// Return the entire sectiontext.
const nString& nSectionHdl::PrintSectionTxt(const nString* sectionname, va_list vptr)
{
    const size_t cMAXSTRINGLENGTH = 16*1024;
    sectiontxt.Clear();

    if (sectionfilefound)
    {
        // Find the section.
        sectiontxt = GetSectionTxt(*sectionname);

        // Expect 'sectiontxt' arguments ?
        if (!sectiontxt.IsEmpty() && (sectiontxt.FindChar('%') < sectiontxt.Length()))
        {
            // Allocate buffer.
            char* alltxt = new char[((sectiontxt.Length() / cMAXSTRINGLENGTH) + 1) * cMAXSTRINGLENGTH];

            vsprintf(alltxt, (char*)sectiontxt, vptr);

            sectiontxt = alltxt;

            // Deallocate buffer.
            delete[] alltxt;
        }
    }

    return sectiontxt;
}

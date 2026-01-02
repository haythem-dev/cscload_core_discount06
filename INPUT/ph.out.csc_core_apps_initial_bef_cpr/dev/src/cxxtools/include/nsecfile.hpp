/*
 ******************** C/C++ Application Program Services **********************

                 (c) Copyright 1995 by NORDAT NetWork GmbH
                              All rights reserved

NSECFILE.HPP
nSectionHdl : handles sections inside a file.

REVISION HISTORY

18. August 1995 V1.00 REV 00 written by Carsten Krabiell.

*/
/*  $History: NSECFILE.HPP $ */
/*  */
/* *****************  Version 7  ***************** */
/* User: Ck           Date: 18.07.96   Time: 14:12 */
/* Updated in $/cxxtools/inc */
/* Final release. */
/* *********************************************** */

/*@CS --------------------------------------------------------------------------
NAME
   nSectionHdl - handles sections inside a file.

SYNOPSIS
   include <nsecfile.hpp>
   nSectionHdl secstrm1("c:/user/msg/messages.ini");     Unix-style
   nSectionHdl secstrm2("c:\\\\user\\\\msg\\\\messages.ini");  Dos-style

   ifstream instrm("c:/user/msg/messages.ini");
   nSectionHdl secstrm3(&instrm);

DESCRIPTION

   This class reads a given file containing sections.

   A section consists of :
      - the sectionname enclosed by cSECTIONBEGIN ('[') and cSECTIONEND (']'),
      - lines of text containing the informations,
      - comments beginning with cCOMMENT (';').

   The sectionname consist of an array of characters. The Rest of this line is
   read over.
   The informations and the comments can stand in any order. If cCOMMENT is
   read, the rest of the line is ignored.

   A flag is set if the file containing the sections is found or not.
   ExistSectionFile gives you the success of finding. If the file couldn't
   be opened or is corrupted all the functions gives you empty strings, etc.

@DE*/

#ifndef SECTIONHDL_INC
#define SECTIONHDL_INC
#ifndef NSTRING_INC
    #include "string.hpp"
#endif
#ifndef STDARGH_INC
    #define STDARGH_INC
    #include <stdio.h>
    #include <stdarg.h>
#endif

/*@CS
GLOBAL CONSTANTS.

*/
const char cSECTIONBEGIN = '[';
const char cSECTIONEND   = ']';
const char cCOMMENT      = ';';
const char cMARKLOADABLE = '*';

//@DE



class nSectionHdl {

private:
   bool sectionfilefound;   // Flag, if file is open.
   nString sectiontxt;       // Contains the current -.

protected:
   nString sectionfilename;
   std::ifstream* sectionfile;

   void IgnoreRestOfLine(void);
   // Reads to the beginning of next line.

public:

/*@DS
PUBLIC MEMBER FUNCTIONS.
*/

   nSectionHdl(const nString& filename);
   nSectionHdl(std::ifstream* infile);
   ~nSectionHdl();

   bool ExistSectionFile() const
/*@DE*/{return sectionfilefound;}
/*@DS*/
   // Returns the success of opening the sectionfile.

   bool ExistSection(const nString& sectionname);
   // Tries to find the 'sectionname' inside the sectionfile.

   bool GotoBeginOfFile();
   // Tries to find the first sectionname inside the section file.

   bool GetNextSection(nString& sectionname);
   // Tries to find the next sectionname inside the section file.

   const nString& GetSectionTxt();
   // Delivers the next section text entry inside the section file.

   const nString& GetSectionTxt(const nString& sectionname);
   // Tries to find the section and reads the text towards the next section
   // (or EOF). All characters are read except from cCOMMENT to EOL.

   const nString& PrintSectionTxt(const nString* sectionname, ...);
   const nString& PrintSectionTxt(const nString* sectionname, va_list vptr);
   // Returns the entire setiontxt. If the sectiontxt contains a format
   // then the arguments are inserted into the txt.

//@DE

};

#endif

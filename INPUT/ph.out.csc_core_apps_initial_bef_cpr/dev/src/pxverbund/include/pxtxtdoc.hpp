/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1996 by NORDAT Network GmbH
                              All rights reserved

PXTXTDOC.HPP
Generic text document classes.

REVISION HISTORY

21 Feb 1996 V1.00 REV 00 written by Peter Hoernich.
*/

#ifndef PXTXTDOC_INC
#define PXTXTDOC_INC

#include "pxbase/pxrecord.hpp"

/*----------------------------------------------------------------------------*/
/*  Text document types.                                                      */
/*----------------------------------------------------------------------------*/
enum pxTextDocType
{
    pxDOC_ORDERHEAD = 1,
    pxDOC_ORDERTAIL
};

/*----------------------------------------------------------------------------*/
/*  A text line within the document.                                          */
/*----------------------------------------------------------------------------*/
class pxTextLine : public pxDBRecord
{
public:

    virtual           ~pxTextLine()  {;}
                      pxTextLine(pxSession *session, const nString& text);
//  Construct a new line for a text document.

                      pxTextLine(pxTextLine& src);
//  Copy constructor.

    pxTextLine&       operator= (const pxTextLine& src);
//  Copy contents of 'src' into self.

    void              Text(const nString& text)
//  Update text in this line.
                      {Text_ = text; SetDirty();}

    const nString&    Text() const
//  Returns a reference to the text string contained in self.
                      {return Text_;}

protected:
                      pxTextLine(pxSession *session,const nString& t,const int n);
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
    void              Init(const nString& t, const int n = cDEFAULT);
    virtual  int     Insert(const void *record);

    int               Number_;          // This line's number
    nString           Text_;

private:
    friend class pxTextDoc;
};

class pxTextDoc : public nDBRecordSet, public nDListCollect
{

public:
    virtual           ~pxTextDoc();
                      pxTextDoc(pxSession *session, const pxTextDocType type, const nString& n);
//  Construct a text document of type 't', with name 'n'.

    int               Get();
//  Reads the entire document from the data base. Note that the the type 't'
//  and the name 'n' passed at construction time are used as read keys.

    int               Put();
//  Write document into the database. Note that empty lines are not
//  written. If all lines are empty, the entire document is deleted from the
//  data base.

    void              Clear()
//  Removes and deletes all text lines from the document.
                      {nDBRecordSet::Clear();}

    pxTextLine*       NewLine(const nString& text);
//  Append a new line with Text 'text' to the end of the document.

    pxTextLine*       Remove(pxTextLine* lp);
//  Remove text line 'lp' points at from the document. Returns NULL if the text
//  line could not be found in the document.

    bool              IsDirty() const;
//  Returns true if the document has been updated anyway, otherwise false.

protected:
    pxSession*        Session()
                      {return (pxSession*) DataBase();}
    virtual nCollectable*
                      AddToList(const void *record, const int row);
    void              ToRecord(void *) const;
    void              ToRecord(void *, pxTextLine*) const;
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

             int      LinesRead_;       // no of lines read from the data base
             pxTextDocType DocType_;         // This document's type
             nString  DocName_;         // and name

private:
    friend class pxTextDocIter;
};

class pxTextDocIter : public nDListCollectIter
{

public:
                      pxTextDocIter(pxTextDoc& list)
                         : nDListCollectIter(list) {;}
    virtual           ~pxTextDocIter() {;}

};

#endif

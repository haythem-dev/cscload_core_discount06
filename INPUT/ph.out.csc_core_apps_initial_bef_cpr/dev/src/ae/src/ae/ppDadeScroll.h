#pragma once

//(c)---------- Customer ClassModel ------------------------------------------//
/*
   Source: ppDadeScroll.h
   Author: A.Schmidt-Rehschuh
   made  : 03.02.2000
                            >No changes in this text may be made<
   declaration:
   In order to be able to use this template-class, the function names
   defined in the Dade must be identical.
*/

template<class E> class ppDadeScroll
{
public:
    enum t_listtyp
    {
        list_current = 0,
        list_history = 1,
        list_future  = 2
    };

public:
    void SetCountPerPage(const int nCountPerPage);          //how many rows are viewing in the listbox
    int GetCountPerPage() const;

protected: /*public: //list selection from data, page-scrolling  */
    ppDadeScroll();                                         //initialize members
    bool StartBrowse();                                     //start to fill list
    bool SetNextPage(const t_listtyp eList = list_current); //start to fill the next page
    bool SetPreviousPage();                                 //set to previous page
    bool GetNext(const bool bNormalFetch = true, const t_listtyp eList = list_current);     //get data from list
    bool SetElement(const unsigned nPos);                   //get an element from list and set to classmembers
    bool SetList(const unsigned nPos = -1);                 //set changed data into server-list (dade)
    bool DelList(const unsigned nPos = -1);                 //insert new data into server-list (dade)
    bool InsList();                                         //delete data from server-list (dade)
    const int GetSize() const;                              //gets number of items

protected:
    bool EndBrowse();                                       //close cursor and initalize members
    E* GetSrv() { return m_srv; }                           //return a pointer to active object
    E* GetSrvUP() { return m_srvUP; }                       //return a pointer to saved object
    const E* GetSrv() const { return m_srv; }               //return a const pointer to dadeobject

protected: //page-scrolling-members
    E*   m_srv;                                             //pointer to class which is given from template
    E*   m_srvUP;                                           //pointer to class which is given from template
    bool m_bFirstItem;                                      //first call to server
    bool m_bCursorOpen;                                     //call is active
    int  m_nCountPerPage;                                   //number per page
    int  m_nCurrentPage;                                    //number of current page
    int  m_nNumberLastPage;                                 //number of last page
    int  m_nCounter;                                        //pagecounter
    unsigned m_nPos;                                        //position, which is set by set element
};

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

template<class E> inline ppDadeScroll<E>::ppDadeScroll()
{
    m_srv   = new E;
    m_srvUP = new E;
    m_bFirstItem = true;
    m_bCursorOpen = false;
    m_nCountPerPage = 0;
    m_nCurrentPage = 0;
    m_nNumberLastPage = 0;
    m_nCounter = 0;
    m_nPos = 0;
}

//----------------------------------------------------------------------------//
//--- methodes to fill a listbox (overloaded from template ppDadeScroll) -----//
//----------------------------------------------------------------------------//

//--- SetCountPerPage --------------------------------------------------------//

template<class E> inline void ppDadeScroll<E>::SetCountPerPage(const int nCountPerPage)
{
    m_nNumberLastPage = m_nCountPerPage = nCountPerPage;
}

//--- GetCountPerPage --------------------------------------------------------//

template<class E> inline int ppDadeScroll<E>::GetCountPerPage() const
{
    return m_nCountPerPage;
}

//--- GetSize --------------------------------------------------------//

template<class E> inline const int ppDadeScroll<E>::GetSize() const
{
    return m_srv->GetSize();
}

//--- StartBrowse ------------------------------------------------------------//

template<class E> inline bool ppDadeScroll<E>::StartBrowse()
{
    return EndBrowse();
}

//--- SetPreviousPage --------------------------------------------------------//

template<class E> inline bool ppDadeScroll<E>::SetPreviousPage()
{
    if (m_nCurrentPage <= 1)
        return false;
    m_srv->SetFetch_rel(-(m_nCountPerPage + m_nNumberLastPage - 1));
    m_nNumberLastPage = m_nCountPerPage;
    --m_nCurrentPage;
    m_nCounter = 0;
    return true;
}

//--- SetNextPage ------------------------------------------------------------//

template<class E> inline bool ppDadeScroll<E>::SetNextPage(const t_listtyp eList /* list_current */)
{
    if (m_nNumberLastPage != m_nCountPerPage)
        return false;
    else if (m_bFirstItem)
    {
        int iReturn = -1;
        switch (eList)
        {
        case list_current:
            iReturn = m_srv->SelList(0);
            break;
        case list_history:
            iReturn = m_srv->SelListHist(0);
            break;
        case list_future:
            iReturn = m_srv->SelListFuture(0);
            break;
        default:
            break;
        }

        if (iReturn != IS_OK)
            return false;
        m_bFirstItem = false;
        m_bCursorOpen = true;
    }

    m_srv->SetFetch_rel(1);
    ++m_nCurrentPage;
    m_nCounter = 0;
    return true;
}

//--- GetNext ----------------------------------------------------------------//

template<class E> inline bool ppDadeScroll<E>::GetNext(const bool bNormalFetch /* = true */,
                                                       const t_listtyp eList /* list_current */ )
{
    if (m_nCounter < m_nCountPerPage)
    {
        int iReturn = -1;
        switch (eList)
        {
        case list_current:
            iReturn = m_srv->SelList(m_srv->GetFetch_rel());
            break;
        case list_history:
            iReturn = m_srv->SelListHist(m_srv->GetFetch_rel());
            break;
        case list_future:
            iReturn = m_srv->SelListFuture(m_srv->GetFetch_rel());
            break;
        default:
            break;
        }

        if (iReturn == IS_OK)
        {
            m_srv->SetFetch_rel(1);
            ++m_nCounter;
            return true;
        }
        else if (iReturn == IS_NOTFOUND)
        {
            m_srv->rc = IS_NOTFOUND; //not set at virtual method
        }
    }

    if (bNormalFetch && (m_srv->rc == IS_NOTFOUND && m_bFirstItem))
    {
        EndBrowse();
    }
    else if (m_srv->rc == IS_NOTFOUND)
    {
        m_nNumberLastPage = m_nCounter;
    }
    else if (m_srv->rc < IS_OK)
    {
        EndBrowse();
    }

    return false;
}

//--- EndBrowse --------------------------------------------------------------//

template<class E> inline bool ppDadeScroll<E>::EndBrowse()
{
    if (!m_bCursorOpen)
        return true;
    m_bCursorOpen = false;
    m_bFirstItem = true;
    m_nNumberLastPage = m_nCountPerPage;
    m_nCurrentPage = 0;
    m_srv->CloseCursor();
    return m_srv->rc == IS_OK ? true : false;
}

//----------------------------------------------------------------------------//
//--- set element of the controlled sequence at position to class member -----//
//----------------------------------------------------------------------------//

template<class E> inline bool ppDadeScroll<E>::SetElement(const unsigned nPos)
{
    m_nPos = nPos;
    if (m_srv->SetData(nPos + ((m_nCurrentPage - 1) * m_nCountPerPage)))
    {
        m_srvUP->SetStruct(m_srv->GetStruct());
        return true;
    }
    return false;
}

//--- SetList (put changed data into the vector list from struct -------------//

template<class E> inline bool ppDadeScroll<E>::SetList(const unsigned nPos)
{
    if (m_srv->GetSize() == 0)
        return true;
    return m_srv->SetList(nPos == -1 ? m_nPos : nPos);
}

//--- InsList (put new data into the vector list from struct -----------------//

template<class E> inline bool ppDadeScroll<E>::InsList()
{
    return m_srv->InsList();
}

//--- DelList (delete data from the vector list ------------------------------//

template<class E> inline bool ppDadeScroll<E>::DelList(const unsigned nPos)
{
    if (m_srv->GetSize() == 0)
        return true;
    return m_srv->DelList(nPos == -1 ? m_nPos : nPos);
}

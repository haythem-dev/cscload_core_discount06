//-------------------------------------------------------------//
// include section
//-------------------------------------------------------------//
#include "stdafx.h"
#include <collectivorders.h>
#include "CustomerGroups.h"
#include <utility>

//-------------------------------------------------------------//
// using section
//-------------------------------------------------------------//
using std::string;
using std::pair;

//-------------------------------------------------------------//
// static section
//-------------------------------------------------------------//
CustomerGroups* CustomerGroups::exemplar = NULL;

//-------------------------------------------------------------//
// static creation method
//-------------------------------------------------------------//
CustomerGroups* CustomerGroups::Ex()
{
    if (exemplar == NULL)
    {
        exemplar = new CustomerGroups;
    }
    return exemplar;
}

//-------------------------------------------------------------//
// c'tor
//-------------------------------------------------------------//
CustomerGroups::CustomerGroups()
    : m_pGrp(0), m_GroupName4Save(""), strError("")
{
    m_MembersPerGroup.clear();
}

//-------------------------------------------------------------//
// d'tor
//-------------------------------------------------------------//
CustomerGroups::~CustomerGroups()
{
    delete m_pGrp;
}

//-------------------------------------------------------------//
// begin()
//-------------------------------------------------------------//
CustomerGroups::T_GROUPS::iterator CustomerGroups::begin()
{
    load();
    return m_pGrp->beginList();
}

//-------------------------------------------------------------//
// end()
//-------------------------------------------------------------//
CustomerGroups::T_GROUPS::iterator CustomerGroups::end()
{
    load();
    return m_pGrp->endList();
}

//-------------------------------------------------------------//
// load
//-------------------------------------------------------------//
bool CustomerGroups::load(bool newLoad)
{
    if (0 == m_pGrp)
    {
        m_pGrp = new CCOLLORDERGRP;
        m_pGrp->SetBranchno(AeGetApp()->VzNr());
        while (m_pGrp->SelList() == SRV_OK)
        {
        }
    }
    else if (newLoad)
    {
        // clearing groups
        m_pGrp->CloseCursor();
        m_MembersPerGroup.clear();
        m_GroupName4Save = "";
        m_custNos.clear();
        m_pGrp->SetBranchno(AeGetApp()->VzNr());
        while (m_pGrp->SelList() == SRV_OK)
        {
        }
    }
    return true;
}

//-------------------------------------------------------------//
// getMembers( int grpID )
//-------------------------------------------------------------//
CustomerGroups::T_MEMBERS& CustomerGroups::getMembers(int grpID)
{
    T_GROUPS_2_MEMBERS::iterator it = m_MembersPerGroup.find(grpID);
    static T_MEMBERS notfound;
    if (m_MembersPerGroup.end() == it)
    {
        // load of members
        CCOLLORDERGRPMEM members;
        members.SetBranchno(AeGetApp()->VzNr());
        members.SetCollordergrpid(grpID);
        vector<collordergrpmemS> vCollordergrpmem;
        while (members.SelList() == SRV_OK)
        {
            vCollordergrpmem.push_back(members.GetStruct());
        }
        if (!vCollordergrpmem.empty())
        {
            pair<T_GROUPS_2_MEMBERS::iterator, bool> p = m_MembersPerGroup.insert(T_GROUPS_2_MEMBERS::value_type(grpID, vCollordergrpmem));
            it = p.first;
        }
        else
            return notfound;
    }
    return it->second;
}

//-------------------------------------------------------------//
// getMembers( const ppString& )
//-------------------------------------------------------------//
CustomerGroups::T_MEMBERS& CustomerGroups::getMembers(const ppString& grpName)
{
    const long grpID = findOutGrpID(grpName);
    return getMembers(grpID);
}

//-------------------------------------------------------------//
// setGroupName( ppString& ppName )
//-------------------------------------------------------------//
void CustomerGroups::setGroupName(ppString& ppName)
{
    m_GroupName4Save = ppName;
}

//-------------------------------------------------------------//
// setMembers( vector<int>& custNos )
//-------------------------------------------------------------//
void CustomerGroups::setMembers(T_MEMBERS_ID& custNos)
{
    m_custNos = custNos;
}

//-------------------------------------------------------------//
// findOutGrpID( const ppString& grpName )
//-------------------------------------------------------------//
long CustomerGroups::findOutGrpID(const ppString& grpName)
{
    long grpID = -1;
    T_GROUPS::iterator it = m_pGrp->beginList();
    for (; it != m_pGrp->endList(); ++it)
    {
        ppString str = it->COLLORDERGRPNAME;
        if (grpName == str)
        {
            grpID = it->COLLORDERGRPID;
            break;
        }
    }
    return grpID;
}

//-------------------------------------------------------------//
// erase()
//-------------------------------------------------------------//
bool CustomerGroups::erase()
{
    if (m_GroupName4Save.empty())
    {
        strError = CResString::ex().getStrTblText(AETXT_NO_GROUP_TO_DELETE);
        return true;
    }

    long grpID = findOutGrpID(m_GroupName4Save);
    T_GROUPS_2_MEMBERS::iterator it = m_MembersPerGroup.find(grpID);

    if (m_MembersPerGroup.end() == it)
    {
        CString str = CResString::ex().getStrTblText(AETXT_NO_GROUP_FOUND_WITH_ID);
        str.Format(str, grpID);
        strError = str;
        return false;
    }

    m_Member.SetBranchno(AeGetApp()->VzNr());
    m_Member.SetCollordergrpid(grpID);
    if (!deleteOldMembers(it->second))
    {
        return false;
    }

    m_pGrp->SetBranchno(AeGetApp()->VzNr());
    m_pGrp->SetCollordergrpid(grpID);
    if (0 != m_pGrp->Delete())
    {
        CString str = CResString::ex().getStrTblText(AETXT_ERROR_WITH_DELETEING_GROUP_WITH_ID);
        str.Format(str, grpID);
        strError = str;
        return false;
    }

    // new load after manipulation
    load( true );

    return true;
}

//-------------------------------------------------------------//
// save()
//-------------------------------------------------------------//
bool CustomerGroups::save()
{
    if (m_GroupName4Save.empty())
    {
        strError = CResString::ex().getStrTblText(AETXT_NO_GROUPNAME_GIVEN_TO_SAVE);
        return true;
    }

    const long grpID = findOutGrpID(m_GroupName4Save);

    if (-1 < grpID)
    {
        // UPDATE
        T_GROUPS_2_MEMBERS::iterator it = m_MembersPerGroup.find(grpID);
        {
            if (false == isSame(getMembers(grpID), m_custNos))
            {
                m_Member.SetBranchno(AeGetApp()->VzNr());
                m_Member.SetCollordergrpid(grpID);
                if (m_MembersPerGroup.end() != it)
                {
                    if (!deleteOldMembers(it->second))
                    {
                        return false;
                    }
                }
                if (!insertNewMembers())
                {
                    return false;
                }
            }
        }
    }
    else
    {
        // 1. check if new members are existing at all
        if (m_custNos.empty())
        {
            strError = CResString::ex().getStrTblText(AETXT_NO_CUSTOMERS_TO_INSERT);
            return false;
        }
        // 2. insert for the new customer group
        m_pGrp->SetBranchno(AeGetApp()->VzNr());
        m_pGrp->SetCollordergrpname(m_GroupName4Save);
        if (0 != m_pGrp->Insert())
        {
            strError = CResString::ex().getStrTblText(AETXT_ERROR_WITH_INSERTING_NEW_GROUP);
            strError += m_Member.error_msg;
            return false;
        }
        // 3: insert all new members
        m_Member.SetBranchno(AeGetApp()->VzNr());
        m_Member.SetCollordergrpid(m_pGrp->GetCollordergrpid());
        if (!insertNewMembers())
        {
            return false;
        }
    }

    m_GroupName4Save = "";
    m_custNos.clear();

    // new load after manipulation
    load( true );

    return true;
}

//-------------------------------------------------------------//
// deleteOldMembers()
//-------------------------------------------------------------//
bool CustomerGroups::deleteOldMembers(T_MEMBERS& members)
{
    // delete all existing members
    T_MEMBERS::iterator memExisting = members.begin();
    for (; memExisting != members.end(); ++memExisting)
    {
        m_Member.SetCustomerno(memExisting->CUSTOMERNO);
        if (0 != m_Member.Delete())
        {
            strError = CResString::ex().getStrTblText(AETXT_ERROR_WITH_DELETING_CUSTOMERS);
            strError += m_Member.error_msg;
            return false;
        }
    }

    return true;
}

//-------------------------------------------------------------//
// insertNewMembers()
//-------------------------------------------------------------//
bool CustomerGroups::insertNewMembers()
{
    // insert all new members
    T_MEMBERS_ID::iterator newMembers = m_custNos.begin();
    for (; newMembers != m_custNos.end(); ++newMembers)
    {
        m_Member.SetCustomerno(*newMembers);
        if (0 != m_Member.Insert())
        {
            strError = CResString::ex().getStrTblText(AETXT_ERROR_WITH_INSERTING_NEW_CUSTOMERS);
            strError += ppString("; ") + m_Member.error_msg;
            return false;
        }
    }

    return true;
}

//-------------------------------------------------------------//
// isSame( T_MEMBERS& oldMembers, T_MEMBERS_ID& newMembers )
//-------------------------------------------------------------//
bool CustomerGroups::isSame(T_MEMBERS& oldMembers, T_MEMBERS_ID& newMembers)
{
    bool found = false;
    if (oldMembers.size() == newMembers.size())
    {
        // the number of the new members and the existing members are the same
        // now it has to be checked if the members are the same
        T_MEMBERS_ID::iterator itNewMem = newMembers.begin();
        T_MEMBERS::iterator itOldMem;
        for (; itNewMem != newMembers.end(); ++itNewMem)
        {
            found = false;
            itOldMem = oldMembers.begin();
            for (; itOldMem != oldMembers.end(); ++itOldMem)
            {
                if ((*itNewMem) == itOldMem->CUSTOMERNO)
                {
                    found = true;
                    break;
                }
            }
        } // for NewMembers
    }

    return found;
}
//-------------------------------------------------------------//
// include guard
//-------------------------------------------------------------//
#pragma once

//-------------------------------------------------------------//
// forward declaration
//-------------------------------------------------------------//
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <map>
#include <sstream>

//-------------------------------------------------------------//
// using section
//-------------------------------------------------------------//
using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::ostringstream;
using std::map;

//-------------------------------------------------------------//
// forward declaration
//-------------------------------------------------------------//
class CCOLLORDERGRP;

//-------------------------------------------------------------//
// class declaration
//-------------------------------------------------------------//
class CustomerGroups
{
    // class methods
public:
    static CustomerGroups* Ex();

private:
    static CustomerGroups* exemplar;

    // object methods
public:
    typedef vector<collordergrpS>       T_GROUPS;
    typedef vector<collordergrpmemS>    T_MEMBERS;
    typedef vector<long>                T_MEMBERS_ID;

    CustomerGroups();
    ~CustomerGroups();
    T_GROUPS::iterator              begin();
    T_GROUPS::iterator              end();
    bool                            load(bool newLoad = false);
    T_MEMBERS& getMembers(int grpID);
    T_MEMBERS& getMembers(const ppString&);
    void                            setGroupName(ppString& ppName);
    void                            setMembers(T_MEMBERS_ID& custNos);
    bool                            save();
    bool                            erase();
    bool                            isSame(T_MEMBERS& oldMembers, T_MEMBERS_ID& newMembers);
    long                            findOutGrpID(const ppString&);

public:
    // members
    ppString                        strError;

private:
    // typedefs
    typedef map<int, T_MEMBERS>     T_GROUPS_2_MEMBERS;

    // methods
    bool                            deleteOldMembers(T_MEMBERS& members);
    bool                            insertNewMembers();

    // members
    CCOLLORDERGRPMEM                m_Member;
    CCOLLORDERGRP* m_pGrp;
    T_GROUPS_2_MEMBERS              m_MembersPerGroup;
    ppString                        m_GroupName4Save;
    T_MEMBERS_ID                    m_custNos;
};

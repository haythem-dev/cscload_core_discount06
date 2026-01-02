// RwProfile.h: Schnittstelle für die Klasse CRwProfile.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RWPROFILE_H__F0234EA6_530E_4BE4_B75E_27230C3D63E1__INCLUDED_)
#define AFX_RWPROFILE_H__F0234EA6_530E_4BE4_B75E_27230C3D63E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRwProfile  
{
public:
	CRwProfile();
	virtual ~CRwProfile();

	void ReadServerNames( CStringArray &ServerNames );
	void WriteServerNames( CStringArray &ServerNames );

	void ReadDbaseNames( CString cServerName, CStringArray &DbaseNames ) ;
	void WriteDbaseNames( CString cServerName, CStringArray &DbaseNames );

	void ReadLastServerDbNames( CString &cServerName, CString &cDbaseName );
	void WriteLastServerDbNames( CString cServerName, CString cDbaseName );

	void ReadLastUserName( CString &cUserName );
	void WriteLastUserName( CString cUserName );

	void ReadLastLanguage( CString &cLanguage );
	void WriteLastLanguage( CString cLanguage );

private:
	void writeRegistryValue	( CString value,	CString registryValueID	);
	const CString readRegistryValue	( CString registryValueID );

	CString m_REGISTRY_KEY_ZDP;
	CString m_RegValueName_LastLanguage;
	CString m_RegValueName_LastUsername;
	CString m_RegValueName_LastServer;
	CString m_RegValueName_LastDatabase;
	CString m_RegValueName_AllServers;
	CString m_RegValueName_AllDatabases;

	CString m_Delimiter;
};

#endif // !defined(AFX_RWPROFILE_H__F0234EA6_530E_4BE4_B75E_27230C3D63E1__INCLUDED_)

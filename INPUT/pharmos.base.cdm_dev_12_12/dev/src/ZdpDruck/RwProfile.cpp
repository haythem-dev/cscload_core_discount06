// RwProfile.cpp: Implementierung der Klasse CRwProfile.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RwProfile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CRwProfile::CRwProfile()
{
	m_REGISTRY_KEY_ZDP			= "Software\\ZDP";			// registry key for application ZDP (HKEY_CURRENT_USER)		
	m_RegValueName_LastLanguage = "Last_Language";
	m_RegValueName_LastUsername = "Last_Username";
	m_RegValueName_LastServer	= "Last_Server";
	m_RegValueName_LastDatabase = "Last_Database";
	m_RegValueName_AllServers	= "All_Servers";
	m_RegValueName_AllDatabases = "All_Databases_";

	m_Delimiter = ";";
}

CRwProfile::~CRwProfile()
{

}

void CRwProfile::ReadServerNames( CStringArray &ServerNames )
{
	int i;
	int anz = 0;
	CString ServerName;
	CString cEntry;

	cEntry = readRegistryValue(m_RegValueName_AllServers);
	i = cEntry.Find(m_Delimiter);

	while (i > 0)
	{
		ServerName = cEntry.Mid(0, i);
		cEntry = cEntry.Mid(i + 1);
		i = cEntry.Find(m_Delimiter);
		
		if ( ! ServerName.IsEmpty() )
		{
			ServerNames.SetSize( anz + 1 );
			ServerNames[anz++] = ServerName;
		}
	}
}

void CRwProfile::WriteServerNames(  CStringArray &ServerNames  )
{
	int i;
	int anz;
	CString cEntry;

	anz = static_cast<int>(ServerNames.GetSize());
	for ( i = 0; i < anz; i++ )
	{
		cEntry += ServerNames[i] + m_Delimiter;
	}
	
	writeRegistryValue(cEntry, m_RegValueName_AllServers);	
}

void CRwProfile::ReadDbaseNames( CString cServerName, CStringArray &DbaseNames ) 
{
	int i;
	int anz = 0;
	CString DbaseName;
	CString cEntry;
	CString cKey;

	cKey = m_RegValueName_AllDatabases;
	cKey += cServerName;

	cEntry = readRegistryValue(cKey);
	i = cEntry.Find(m_Delimiter);

	while (i > 0)
	{
		DbaseName = cEntry.Mid(0, i);
		cEntry = cEntry.Mid(i + 1);
		i = cEntry.Find(m_Delimiter);
		
		if ( ! DbaseName.IsEmpty() )
		{
			DbaseNames.SetSize( anz + 1 );
			DbaseNames[anz++] = DbaseName;
		}
	}
}

void CRwProfile::WriteDbaseNames( CString cServerName, CStringArray &DbaseNames ) 
{
	int i;
	int anz;
	CString cEntry;
	CString cKey;

	cKey = m_RegValueName_AllDatabases;
	cKey += cServerName;

	anz = static_cast<int>(DbaseNames.GetSize());
	for ( i = 0; i < anz; i++ )
	{
		cEntry += DbaseNames[i] + m_Delimiter;
	}
	
	writeRegistryValue(cEntry, cKey);	
}

void CRwProfile::ReadLastServerDbNames( CString &cServerName, CString &cDbaseName )
{
 	cServerName = readRegistryValue(m_RegValueName_LastServer);
	cDbaseName  = readRegistryValue(m_RegValueName_LastDatabase);
}

void CRwProfile::WriteLastServerDbNames( CString cServerName, CString cDbaseName )
{
	writeRegistryValue(cServerName, m_RegValueName_LastServer);
	writeRegistryValue(cDbaseName, m_RegValueName_LastDatabase);
}

void CRwProfile::ReadLastUserName( CString &cUserName )
{
 	cUserName = readRegistryValue(m_RegValueName_LastUsername);
}

void CRwProfile::WriteLastUserName( CString cUserName )
{
	writeRegistryValue(cUserName, m_RegValueName_LastUsername);
}

void CRwProfile::ReadLastLanguage( CString &cLanguage )
{
	cLanguage = readRegistryValue(m_RegValueName_LastLanguage);
}

void CRwProfile::WriteLastLanguage( CString cLanguage )
{
	writeRegistryValue(cLanguage, m_RegValueName_LastLanguage);
}

//----------------------------------------------------------------------------
void CRwProfile::writeRegistryValue	 (	CString value,	CString registryValueID	)
{
	long		lnResult; 
	HKEY		hKey	= NULL; 
	
	lnResult = RegOpenKeyEx( HKEY_CURRENT_USER, m_REGISTRY_KEY_ZDP, 0, KEY_WRITE, &hKey ); 
	
	if( !hKey || lnResult != ERROR_SUCCESS )
	{
		lnResult = RegCreateKeyEx(HKEY_CURRENT_USER, m_REGISTRY_KEY_ZDP, 0, "", 0, 
									KEY_WRITE, NULL, &hKey, NULL); 
	}

	if( !hKey || lnResult != ERROR_SUCCESS )
	{
		RegCloseKey(hKey);
		return;
	}
		
	TCHAR szValue[100]; 
	DWORD dwSize = sizeof(szValue)*sizeof(TCHAR); 
		
	strcpy(szValue, value);
	dwSize = sizeof(szValue)*sizeof(TCHAR); 
	
	lnResult = RegSetValueEx(hKey, registryValueID, 0, REG_SZ, (LPBYTE) szValue, dwSize);
	RegCloseKey(hKey);
	
	return;
}

//----------------------------------------------------------------------------
const CString	CRwProfile::readRegistryValue	 (	CString registryValueID )
{
	long		lnResult; 
	HKEY		hKey	= NULL; 
	CString		value = "";

	lnResult = RegOpenKeyEx( HKEY_CURRENT_USER, m_REGISTRY_KEY_ZDP, 0, KEY_READ, &hKey ); 
	
	if( !hKey || lnResult != ERROR_SUCCESS )
	{ 
		RegCloseKey(hKey);
		return value;	
	}

	DWORD dwType; 
	TCHAR szValue[100]; 
	DWORD dwSize = sizeof(szValue)*sizeof(TCHAR); 

	lnResult = RegQueryValueEx(hKey, registryValueID, NULL, &dwType, (LPBYTE) szValue, &dwSize); 
		
	if ( (lnResult == ERROR_SUCCESS) && (dwType == REG_SZ) )
		value	= szValue;

	RegCloseKey(hKey);

	return value; 
}
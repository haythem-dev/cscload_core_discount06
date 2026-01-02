/******************************************************************************/
/**                                                                           */
/**   Author : R. Raab PRZ GmbH	    										  */
/**   Date   : 21.01.2015                                                     */
/**                                                                           */
/******************************************************************************/
#include "stdafx.h"

#include "ArtFreeTextDoc.h"

#include "Ekzdp.h"

#include <libscsvoodoo/libscsvoodoo.h>

#include <eklibs/wdbups/wpp_prot.h>
#include <eklibs/wdbups/wpp_bufd.h>
#include "FeldBreite.h"

/*----------------------------------------------------------------------------*/
CArtFreeTextDoc::CArtFreeTextDoc()
{
}

/*----------------------------------------------------------------------------*/
CArtFreeTextDoc::~CArtFreeTextDoc()
{
}

/*----------------------------------------------------------------------------*/
struct CARTFREETEXT* CArtFreeTextDoc::GetBuffer()
{
	return &m_Buf;
}

/*----------------------------------------------------------------------------*/
void CArtFreeTextDoc::SetPrimekeyCondition_ArtFreeText ( )
{
	sprintf( m_PrimekeyCond, "ARTICLENO=%ld and TEXTTYPENO=%d and DATEFROM=%ld and DATETO = %ld and LINE_NUMBER=%d", 
		m_Buf.ARTICLENO, m_Buf.TEXTTYPENO, m_Buf.DATEFROM, m_Buf.DATETO, m_Buf.LINE_NUMBER);
}

/*----------------------------------------------------------------------------*/
int CArtFreeTextDoc::GetBufferDesc_ArtFreeText( CString &cErrmld )
{
	char *tabelle = "cartfreetext";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");

	if ( m_Fd_ArtFreeText >= 0 )
		return 0;

	lStatus = ::OpenBufferDesc( &m_Fd_ArtFreeText, tabelle,
                                NULL, NULL, V_PROTO_VERTEIL, errmld ); 

	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_ArtFreeText = -1;
		return -1;
	}
	return 0;
}

/*----------------------------------------------------------------------------*/
/* int CArtFreeTextDoc::GetBufferDesc_Zpznpflege( CString &cErrmld )
{
	char *tabelle = "zpznpflege";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");

	if ( m_Fd_Zpznpflege >= 0 ) 
		return 0;

	lStatus = ::OpenBufferDesc( &m_Fd_Zpznpflege, tabelle,
                                NULL, NULL, V_OHNE, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Zpznpflege = -1;
		return -1;
	}
	return 0;
} */

/*----------------------------------------------------------------------------*/
long CArtFreeTextDoc::StoreRecord_ArtFreeText( CString &cErrmld )
{
	long lStatus = 0;
	char errmld[200];

	m_NumberOfLinesNew = DismantleTextIntoLines (m_Buf.FREETEXT);

	if (m_NumberOfLinesNew == -1)
	{
		cErrmld.Format("%s", "mehr als 5 Zeilen nicht zulaessig");
		return -1;
	}
		
	for (short i = 0; i < m_NumberOfLinesNew; i++)
	{
		m_Buf.LINE_NUMBER = i + 1;
		strcpy (m_Buf.FREETEXT, m_Textline[i]);

		struct CARTFREETEXT BufTemp = m_Buf;

		ReadRecord( cErrmld );

		m_Buf = BufTemp;

		if ( m_lStatus_ArtFreeText == 100 )
		{
			lStatus = ::FdDelayInsertRecord( m_Fd_ArtFreeText, &m_Buf, 
											 m_PrimekeyCond, errmld);

			if ( lStatus != 0 ) 
				cErrmld = errmld; 
			else 
				cErrmld = _T("");
		}
		else if ( m_lStatus_ArtFreeText == 0 )
		{
			lStatus = ::FdDelayUpdateRecord( m_Fd_ArtFreeText, &m_Buf, &m_BufOld, 
											 m_PrimekeyCond, errmld);

			if ( lStatus != 0 ) 
				cErrmld = errmld; 
			else 
				cErrmld = _T("");
		}
		else
		{
			lStatus = m_lStatus_ArtFreeText;
		}

		if (lStatus != 0)
			break;
	}

	// gelöschte Zeilen auch physikalisch löschen
	if (m_NumberOfLinesOld > m_NumberOfLinesNew)
	{
		for (short i = m_NumberOfLinesNew; i < m_NumberOfLinesOld; i++)
		{
			lStatus = DeleteOneRecord_ArtFreeText (i + 1, cErrmld);

			if ( lStatus != 0 ) 
				break;
		}
	}

	return lStatus;
}

/*----------------------------------------------------------------------------*/
long CArtFreeTextDoc::DeleteRecord_ArtFreeText( CString &cErrmld )
{
	long lStatus = 0;

	for (short i = 0; i < m_NumberOfLinesOld; i++)
	{
		lStatus = DeleteOneRecord_ArtFreeText (i + 1, cErrmld);

		if ( lStatus != 0 ) 
			break;
	}

	return lStatus;
}

/*----------------------------------------------------------------------------*/
long CArtFreeTextDoc::DeleteOneRecord_ArtFreeText( short i, CString &cErrmld )
{
	long lStatus = 0;
	char errmld[200];

	m_Buf.LINE_NUMBER = i;

	ReadRecord( cErrmld );

	if ( m_lStatus_ArtFreeText == 0 )
	{
		lStatus = ::FdDelayDeleteRecord( m_Fd_ArtFreeText, &m_Buf, 
											m_PrimekeyCond, errmld );
	
		if ( lStatus != 0 )
			cErrmld = errmld; 
		else 
			cErrmld = _T("");
	}

	return lStatus;
}

/*----------------------------------------------------------------------------*/
void CArtFreeTextDoc::InitPflegeDesc( char* Anwender )
{
	m_Anwender = Anwender;
	
	m_Fd_ArtFreeText  = -1;

	m_NumberOfLinesOld = 0;

//	m_Fd_Zpznpflege = -1;

//	m_tagesdatum = 0;
}

/*----------------------------------------------------------------------------*/
void CArtFreeTextDoc::FreeBufferDesc( )
{
	if ( m_Fd_ArtFreeText >= 0 )
		CloseOneBufferDesc( m_Fd_ArtFreeText );
	m_Fd_ArtFreeText = -1;

/*	if ( m_Fd_Zpznpflege >= 0 )
		CloseOneBufferDesc( m_Fd_Zpznpflege );
	m_Fd_Zpznpflege = -1; */
}

/*----------------------------------------------------------------------------*/
void CArtFreeTextDoc::StoreBuffer()
{
//	hier dummy
}

/*----------------------------------------------------------------------------*/
void CArtFreeTextDoc::RestoreBuffer()
{
//	hier dummy
}

/*----------------------------------------------------------------------------*/
int CArtFreeTextDoc::GetBufferDesc( CString &cErrmld )
{
   	if ( GetBufferDesc_ArtFreeText( cErrmld ) != 0 ) 
	   return -1;

/*    	if ( GetBufferDesc_Zpznpflege( cErrmld ) != 0 ) 
		return -1; */
	
   return 0;
}

/*----------------------------------------------------------------------------*/
int CArtFreeTextDoc::InitRecord  ( CString& cErrmld )
{
	if (cErrmld.GetLength()) {}
	return 0;
}

/*----------------------------------------------------------------------------*/
long CArtFreeTextDoc::ReadRecord( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	if ( GetBufferDesc( cErrmld ) != 0 )  
		return -1;

	SetPrimekeyCondition_ArtFreeText ( );

    lStatus = ::FdReadRecord( m_Fd_ArtFreeText, m_PrimekeyCond, 
								&m_Buf, errmld );
		
	if ( !( lStatus == 0 || lStatus == 100 ) )
	{                                
		cErrmld = errmld;
	}

	m_lStatus_ArtFreeText = lStatus;

	m_BufOld = m_Buf;

	return lStatus;
}

/*----------------------------------------------------------------------------*/
long CArtFreeTextDoc::StoreRecord( CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 )  
		return -1;

	if ( StoreRecord_ArtFreeText( cErrmld ) != 0 ) 
		return -1;
 
	char errmld[200];
	if ( FdTransact( errmld ) != 0 ) 
	{
		cErrmld = errmld;
		return -1;
	}
/*	else
		// Ausgabe zpznpflege für Verteilung mittels tpulzentpfl 
		return StoreRecord_Zpznpflege( m_tagesdatum, cErrmld ); */
	
	return 0;
}

/*----------------------------------------------------------------------------*/
long CArtFreeTextDoc::DeleteRecord( CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 ) 
		return -1;

    if ( DeleteRecord_ArtFreeText( cErrmld ) != 0 ) 
		return -1;
    
	char errmld[200];
	if ( FdTransact( errmld ) != 0 ) 
	{
		cErrmld = errmld;
		return -1;
	}
/*	else
		// Ausgabe zpznpflege für Verteilung mittels tpulzentpfl 
		return StoreRecord_Zpznpflege( m_tagesdatum, cErrmld ) ; */

	return 0;
}

/*----------------------------------------------------------------------------*/
/* void CArtFreeTextDoc::SetTagesdatum( long datum )
{
	m_tagesdatum = datum;
} */

/*----------------------------------------------------------------------------*/
/* long CArtFreeTextDoc::StoreRecord_Zpznpflege( long datum, CString &cErrmld )
{
	long lStatus;

	char PrimekeyCond_Zpznpflege[100];
	char errmld[200];

	m_ZpznpflegeBuf.ARTIKEL_NR = m_Buf.ARTICLENO;
	m_ZpznpflegeBuf.DATUM		= datum;

	sprintf( PrimekeyCond_Zpznpflege, "ARTIKEL_NR=%ld and DATUM=%ld and DEZAP_SA = '28'",
									m_ZpznpflegeBuf.ARTIKEL_NR, m_ZpznpflegeBuf.DATUM );

    lStatus = ::FdReadRecord( m_Fd_Zpznpflege, PrimekeyCond_Zpznpflege,
				  			  &m_ZpznpflegeBuf, errmld );

	if ( lStatus == 100 )
	{
		m_ZpznpflegeBuf.ARTIKEL_NR = m_Buf.ARTICLENO;
		m_ZpznpflegeBuf.DATUM		= datum;
		strcpy (m_ZpznpflegeBuf.DEZAP_SA, "28");

		lStatus = ::FdInsertRecord( m_Fd_Zpznpflege, &m_ZpznpflegeBuf, 
										 PrimekeyCond_Zpznpflege, errmld );
	}

	if ( lStatus != 0 ) 
		cErrmld = errmld;
	else 
		cErrmld = _T("");

	return lStatus;
} */

short CArtFreeTextDoc::DismantleTextIntoLines (char *Text)
{
	if (Text) {}
	char *c1;
	int i1;
	short s1 = 0;

	c1 = strchr(m_Buf.FREETEXT, 0x0d0a);

	while (c1 != NULL)
	{
		// -1, weil außerhalb des Loops nochmal ein Element gefüllt wird
		if (s1 >= MAX_NUMBER_OF_LINES - 1)
			return -1;

 		i1 = static_cast<int>(c1 - m_Buf.FREETEXT - 1);

		if (i1 > 0) 
		{
			strncpy (m_Textline[s1], m_Buf.FREETEXT, i1);
			m_Textline[s1][i1]= '\0';
			s1++;
		}

		strcpy (m_Buf.FREETEXT, c1 + 1);

		c1 = strchr(m_Buf.FREETEXT, 0x0d0a);
	}

	strcpy (m_Textline[s1], m_Buf.FREETEXT);
	return s1 + 1;
}

short CArtFreeTextDoc::GetAllTextLines ( )
{
	CString sql, cErrmld, cs, csGesamt;
	long s;
	int iMax;

	sql.Format( "select max(line_number) from cartfreetext where ARTICLENO=%ld and TEXTTYPENO=%d and DATEFROM=%ld and DATETO = %ld", 
				m_Buf.ARTICLENO, m_Buf.TEXTTYPENO, m_Buf.DATEFROM, m_Buf.DATETO);

	s = SqlRead(sql, &iMax, NULL);

	if (s != 0)
	{
		cErrmld = CResString::ex().getStrTblText(IDS_STRING38);
		cErrmld += DynErrmld();
		MsgBoxOK( cErrmld );
		return -1;
	}

	m_NumberOfLinesOld = static_cast<short>(iMax);

	memset(m_Buf.FREETEXT, ' ', L_CARTFREETEXT_FREETEXT);
	
	for (short i = 0; i < m_NumberOfLinesOld; i++)
	{
		m_Buf.LINE_NUMBER = i + 1;

		s = ReadRecord( cErrmld );

		if (s == 0)
		{
			cs.Format("%s", m_Buf.FREETEXT);
			cs.Trim();

			if (i == 0)
				csGesamt = cs; 
			else
				csGesamt.Format("%s\r\n%s", csGesamt, cs);
		}
	}

	strcpy (m_Buf.FREETEXT, csGesamt);
		
	return static_cast<short>(iMax);
}



// ServerDatum.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include "ServerDatum.h"

#include <hdatum/PhoDate.h>
#include <hdatum/PhoZeit.h>

#ifdef ALTE_VERSION

#include "ZdpDruck.h"
#include <eklibs/wunxlocs/UnixSys.h>

long Today( )
{
	if ( ((CEk1*) AfxGetApp())->IsSyncronized() )
	{
		return PhoToday();
	}
	else
	{
		return PhoTodayFromServer( 0 );
	}
}

long ActualTime( )
{
	if ( ((CEk1App*) AfxGetApp())->IsSyncronized() )
	{
		return GetPhoTime();
	}
	else
	{
		long zeit;
		PhoTodayClockFromServer( &zeit, 0 );
		return zeit;
	}
}

long ActualDateTime( long *zeit )
{
	if ( ((CEk1App*) AfxGetApp())->IsSyncronized() )
	{
		*zeit = GetPhoTime();
		return PhoToday();
	}
	else
	{
		return PhoTodayClockFromServer( zeit, 0 );
	}
}

#else

#include <libscsvoodoo/libscsvoodoo.h>

long Today( )
{
	long datum;
	long zeit;
	if ( UnxDateTime( &datum, &zeit ) == 0 )
		return datum;
	else
		return PhoToday();
}


long ActualTime( )
{
	long datum;
	long zeit;
	if ( UnxDateTime( &datum, &zeit ) == 0 )
		return zeit;
	else
		return GetPhoTime();
}

long ActualDateTime( long *zeit )
{
	long datum;
	if ( UnxDateTime( &datum, zeit ) == 0 )
		return datum;
	else
	{
		*zeit = GetPhoTime();
		return PhoToday();
	}
}


#endif
#!/usr/bin/perl
use warnings;
use strict;

package DateMinusDays;

use Time::localtime;
use Time::Local;

sub is_positive_int {
    return ( $_[0] eq int( $_[0] ) && $_[0] > 0 );
}

my ($days) = @ARGV;
if( ! is_positive_int($days) )
{
	printf( "ARG not a positive integer!\n" );
	exit -1;
}

my $tm = localtime;
my $TIME = timelocal($tm->sec, $tm->min, $tm->hour, $tm->mday, $tm->mon+1, $tm->year+1900);

$TIME = $TIME - $days * 24 * 60 * 60;
$tm = localtime($TIME);

printf( "%04d%02d%02d\n", $tm->year+1900, $tm->mon, $tm->mday );
exit 0;

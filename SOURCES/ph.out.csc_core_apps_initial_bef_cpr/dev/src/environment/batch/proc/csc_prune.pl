#!/usr/bin/perl

#-------------------------------------------------------
#Author: Marco Köppendörfer
#Creation Date: 14.11.2012
#Version:
#           1.08 - added new phadex specific tables to prune
#                - removed old phatra table pair
#        	1.07 - added new phatra specific tables to prune
#        	1.06 - added phabor specific tables to prune
#			1.05 - fixed regex pattern errously matching e.g. -branchno 57 as -branchno 5
#			1.04 - checking if specific application(s) are not active before pruning 
#			1.03 - added branchno to logfile
#			1.02 - branch specific
#-------------------------------------------------------

#-------------------------------------------------------
#	perl directives
#-------------------------------------------------------
use strict;
use warnings;
#-------------------------------------------------------

#-------------------------------------------------------
#	package name
#-------------------------------------------------------
package csc_phatra_prune;
#-------------------------------------------------------

#-------------------------------------------------------
#	usage of other packages
#-------------------------------------------------------
use File::Basename;
use POSIX qw/strftime/;
use Data::Dumper;
#-------------------------------------------------------

#-------------------------------------------------------
#	read me :)
#-------------------------------------------------------
#	script for pruning pharmostransaction table
#	make sure no one inserts data during archiveing - maybe we should lock? would mean we have to do everything in one dbaccess session
#
#	should work for all archive tables which
#	a) need to be copied whole
#	b) contains all fields of source table
#	c) has an additional first column of type date 
#
#-------------------------------------------------------

#-------------------------------------------------------
#	usage
#-------------------------------------------------------
#	edit constans below
#	
#	Paramns
#		<databaseName>: Name of database to archive, e.g. zpos1de
#		<branchno>: Number of branch to archive, e.g. 5 (no leading zeros)
#
#	Call
#		csc_prune.pl zpos1de 57
#-------------------------------------------------------

#-------------------------------------------------------
#	return values
#-------------------------------------------------------
#	0:	ok
#	>0:	not ok
#		19: running application is preventing pruning
#		22: essential parameters are missing
#		33: same name of table and archive table found
#		99: severe error: no databases found (automatic mode) or system call failed
#-------------------------------------------------------


#-------------------------------------------------------
#	constants (edit this for own version)
#-------------------------------------------------------
#number of days to keep archived data
use constant ARCHIVE_DAYS => 14;

#use '<tablename of table to archive>' =>  '<tablename of archive table>'
#separate pairs with comma
#example:
#my %tablePairs = (
#	'pharmostransaction' => 'apharmostransaction',
#	'pharmostransaction2' => 'apharmostransaction2'
#);
#
my %tablePairs = (
	'phadextransaction' => 'aphadextransaction',
	'pharmostransactions' => 'apharmostransactions',
	'pharmosbatchorderhead' => 'apharmosbatchorderhead',
	'pharmosbatchorderpos' => 'apharmosbatchorderpos'
);

#array of application names to check before pruning
#use sperate strings with comma
my @applicationNames = ('csc_phatra.bin','csc_phabor.bin','csc_phadex.bin'); 

#set MODE to 'UNLOAD' use unloading
#note: 'UNLOAD' not finished yet
use constant MODE => 'ARCHIVE_TABLE';
#------------------------------------------------------- 


#-------------------------------------------------------
#module wide variables, for convenience
#-------------------------------------------------------
#key=database name, value=database collation
my %databaseCollations;
my $log_fh;
my $branchno = -1;
#-------------------------------------------------------

#
sub logMessage($)
{
	my $logMessage = shift;

	my $timeStamp = strftime('%Y.%m.%d %H:%M:%S: ',localtime); 
	
	for (*STDOUT, $log_fh)
	{
		print $_ $timeStamp; 
		print $_ $logMessage;
	}
}

sub prepareEnvironment()
{
	my $path_to_dbaccess = qx/which dbaccess/;
	
	my $informixdir = dirname(dirname($path_to_dbaccess));
	
	logMessage("setting informixdir to " . $informixdir . "\n");
	
	$ENV{INFORMIXDIR} = $informixdir;
}


sub getDatabaseNames()
{
	#old perl is old, there are now more elegant ways of doing this, but this works at least...
	my $command = 'echo "SELECT dbs_dbsname, dbs_collate FROM   sysmaster:Sysdbslocale WHERE  LOWER(dbs_dbsname) NOT LIKE \'sys%\';" | dbaccess sysmaster';
	
	open(FILE, "$command 2>/dev/null |");

	my $last_dbs_name = "";

	while(<FILE>)
	{
		#ignore blank lines
		next unless $_ !~ /^\n$/;
		
		#remove newlines
		s/\n//;
		
		#parse statement output
		if ($_ =~ /dbs_dbsname/)
		{
			$_ =~ /dbs_dbsname\s+(.*)/;
			$last_dbs_name = $1;
			logMessage("found database name $last_dbs_name\n");
			$databaseCollations{$last_dbs_name} = 'void'; 
		}
		
		if ($_ =~ /dbs_collate/)
		{
			$_ =~ /dbs_collate\s+(.*)/;
			my $db_collation = $1;
			logMessage("found database name $last_dbs_name has collation $db_collation\n");
			$databaseCollations{$last_dbs_name} = $db_collation; 
		}
		
	}
	
	close FILE;
	
	#get return value of open(FILE, "$command 2>/dev/null |"), that is the return value of dbaccess - tricky, eh? 
	my $return = $?;
	
	print "return of system call: " . $return . "\n";
	
	return $return; 
	
}

sub pruneTableInDatabase($$)
{
	#issue command to truncate table
	
	my ($databaseName, $tablename)  = @_;
		
	my $command = 'echo "delete from '. $tablename .' where branchno = '. $branchno .';" | dbaccess ' . $databaseName . " 1>/dev/null 2>\&1";
	
	#todo: check return value
	system($command);	
	logMessage(sprintf "command: %s\n", $command);
	logMessage(sprintf "got return code: %d\n", $? >> 8);
	
	#todo: also check rowCount tablename == 0
#	if (getRowsFromTableInDatabase($databaseName, $tablename) != 0)
#	{
#		logMessage(print "table " . $tablename . " in " . $databaseName . " does not contain 0 rows after truncate\n");
#	}
	
}

sub archiveTableFromDatabase($$$)
{
	my ($databaseName, $tablename, $archive_tablename) = @_;
	
	logMessage("using mode: ". MODE . "\n");
	
	if (MODE eq 'ARCHIVE_TABLE')
	{
		my $archive_table_exists = tableExistsInDatabase($databaseName, $archive_tablename);
	
		if (!$archive_table_exists)
		{
			logMessage(print "database " . $databaseName . " does not contain " . $archive_tablename ." - skipping archive step\n");
			return;
		}
		
		logMessage("deleting datasets older than " . ARCHIVE_DAYS . " day(s) from " . $databaseName . ":" . $archive_tablename . "\n");
		
		my $command = 'echo "delete from '. $archive_tablename . ' where archivedate < today - '. ARCHIVE_DAYS . ' and branchno = '. $branchno .';" | dbaccess ' .$databaseName . " 1>/dev/null 2>\&1"; 
		
		#todo: check return value
		system($command);		
		logMessage(sprintf "command: %s\n", $command);
		logMessage(sprintf "got return code: %d\n", $? >> 8);

		#todo: get number of rows of table, check if archivetable's row count increases by number of rows -  after deletion
		
		my $rowcount_table = getRowsFromTableInDatabase($databaseName, $tablename);

		my $rowcount_archive = getRowsFromTableInDatabase($databaseName, $archive_tablename);
		
		logMessage("deletion of too old data of $archive_tablename finished. Archiving new data...\n");
		
		$command = 'echo "insert into '. $archive_tablename . ' select today,* from '. $tablename .' where branchno = '. $branchno .';" | dbaccess ' .$databaseName  . " 1>/dev/null 2>\&1"; ;
		
		# reihenfolge der spalten passt bei der phadextransaction nicht!!!
		#if ($tablename eq 'phadextransaction')
		#{
		#	$command = 'echo "insert into '. $archive_tablename . ' select today, branchno, recordno, creationdatetime, data, recordtype, transferdatetime, processdatetime, processedflag from '. $tablename .' where branchno = '. $branchno .';" | dbaccess ' .$databaseName  . " 1>/dev/null 2>\&1"; ;		
		#}
		
		#todo: check return value also :)
		system($command);
		logMessage(sprintf "command: %s\n", $command);
		logMessage(sprintf "got return code: %d\n", $? >> 8);
		
		logMessage("archiving of new data of table $tablename finsihed\n");
		
		my $rowcount_archive_new = getRowsFromTableInDatabase($databaseName, $archive_tablename);
		
		if ($rowcount_archive_new != $rowcount_table + $rowcount_archive)
		{
			logMessage("rowcount ($tablename/$archive_tablename) don't match, something is not right...\n");
		}
		
	}
	elsif (MODE eq 'UNLOAD')
	{
		
		print "warning, not finished!\n";
		
		#unload table entries to temp file, zip temp file
		my $unload_filename = "getUnloadFilename";
		
		my $command = "echo UNLOAD to ". $unload_filename . " DELIMTIER '|' select * from ". $tablename ."; | dbaccess " .$databaseName;
		
		#todo: check return value
		system($command);
		logMessage(sprintf "got return code: %d\n", $? >> 8);
		
		$command = "gtar -czf " . $unload_filename . ".tgz " . $unload_filename;
		
		#todo: check return value also :)
		system($command);
		logMessage(sprintf "got return code: %d\n", $? >> 8);
	}	
	else
	{
		logMessage('warning: MODE unknown, skipping archive step');
	}
	
}

sub getRowsFromTableInDatabase($$)
{
	my ($databaseName, $tablename) = @_;
	
	#better way?
	my $command = 'echo "select count(*) as rowcount from '. $tablename . ' where branchno = '. $branchno .';" | dbaccess ' . $databaseName;
	
	open(FILE, "$command 2>/dev/null |");
	
	while(<FILE>)
	{
		#ignore blank lines
		next unless $_ !~ /^\n$/;
		
		#remove newlines
		s/\n//;
		
		#kinda dirty
		if ($_ =~ /\d+/)
		{
			$_ =~ /(\d+)/;
			
			return $1;
		}
				
	} 
	
}

sub tableExistsInDatabase($$)
{
	my ($database, $tablename) = @_;
	
	my $command = 'echo "select tabname from systables where tabname = \'' . $tablename . '\';" | dbaccess ' . $database;
	
	my $found = 0;
	
	#get only STDERR
	open(FILE, "$command 2>\&1 1>/dev/null |");
	
	while(<FILE>)
	{
		#ignore blank lines
		next unless $_ !~ /^\n$/;
				
		#kinda dirty
		if ($_ =~ /1 row\(s\) retrieved\./)
		{
			$found = 1;
			
			#exit loop - last leads to broken pipe, need to read all from pipe
		}
				
	} 
	
	close FILE;
	
	return $found;
	
}


sub workingTitleSubName($)
{
	my $database = shift;
	
	logMessage("checking database ". $database . "\n");

	while((my $tablename, my $archive_tablename) = each %tablePairs)
	{
	
		if (tableExistsInDatabase($database, $tablename))
		{		
			archiveTableFromDatabase($database, $tablename, $archive_tablename);
			
			pruneTableInDatabase($database, $tablename);
		}
		else
		{
			logMessage("database " . $database . " does not contain table " . $tablename . "\n");
		}
	}
}

sub getPSCommand()
{
	my @uname_values = POSIX::uname();
	my $sysname = $uname_values[0];
	
	logMessage("running on $sysname\n");
		
	if ($sysname =~ m/sun/i)
	{
		return "/usr/ucb/ps -awwwx ";
	}
	elsif ($sysname =~ m/aix/i)
	{
		return "ps awwwx ";
	}
	else
	{
		logMessage("found unknown operating system: $sysname, can't run, exiting...\n");
		exit 19;
	}
}

sub pruningPreventingApplicationRunning()
{
	my $psCommand = getPSCommand(); 
	
	logMessage("got ps command: $psCommand\n");
	
	my $retVal = 0;
		
	foreach (@applicationNames)
	{
		my $appName = $_;
		
		my $pattern = "$appName.*-branchno\\s+$branchno\\s";
		
		logMessage("using pattern: $pattern\n");
		
		open (PS, "$psCommand |") or die("can't ps");
		while (<PS>)
		{
		    if ($_ =~ m/$pattern/i)
    		    {
				logMessage("found running application $appName for branchno $branchno, can't prune, exiting...\n");
				$retVal = 1;
				
				#exit loop - last leads to broken pipe, need to read all from pipe
    		    }
		}
	}
	
	return $retVal;
}

sub trim($)
{
	my $string = shift;
	$string =~ s/^\s+//;
	$string =~ s/\s+$//;
	return $string;
}

sub usage()
{
	print "usage: $0 <database name> <branch no>";
}

sub getCollationToDatabase($)
{
	my $databaseName = shift;
	
	if ($databaseName =~ /zpos3bg/ || $databaseName =~ /obg21/)
	{
		return "bg_BG.915";
	}
	
	return "en_US.819";
}

sub isBranchNoValid()
{
	if ($branchno != -1)
	{
		if ($branchno =~ /\d+/ )
		{
			return 1;	
		}
	}
	
	return 0;
}

#-------------------------------------------------------
#main programm
#-------------------------------------------------------

if ($#ARGV != 1)
{
	usage;
	exit 2;
}

#get branchno - needed for logging
$branchno = $ARGV[1];

my $logfile_name;

if (!$ENV{LOG_PATH})
{
    $logfile_name = "./csc_prune.$branchno.log";
}
else
{
    $logfile_name = "$ENV{LOG_PATH}/csc_prune.$branchno.log";
}

open $log_fh, ">>$logfile_name" or print "can't open logfile $logfile_name: $!\n";

logMessage("$0 started\n");

if (!isBranchNoValid())
{
	logMessage("invalid branchno $branchno entered\nexiting\n");
	exit 22;	
}

if (pruningPreventingApplicationRunning())
{
	logMessage("found application preventing pruning, can't run\nexiting\n");
	exit 19;
}

#get databasename
$databaseCollations{$ARGV[0]} = getCollationToDatabase($ARGV[0]);

logMessage("using database $ARGV[0] for branchno $branchno, preparing environment\n");

prepareEnvironment();

logMessage("environment prepared\n");

#get all database names of database server
#if (getDatabaseNames() != 0)
#{
#	logMessage("getDatabaseNames failed\n");
#}

#sanity check, make sure tablename != archive_tablename
while((my $tablename, my $archive_tablename) = each %tablePairs)
{
	my $found = 0;
	
	if ($tablename eq $archive_tablename)
	{
		logMessage("name of table " . $tablename . " matches name of it's archive table  " . $archive_tablename ."\n");
		$found += 1;
	}
	
	if ($found > 0)
	{
		logMessage("can't run, found " . $found . " table pairs with same name\n");
		exit 33;
	}
	
}

if (!keys %databaseCollations)
{
	logMessage("database hash is empty, could not read sysmaster:Sysdbslocale apparently... exiting...\n");
	exit 99;
}
else
{
	while((my $database, my $collation) = each %databaseCollations)
	{
		if (trim($collation) eq "en_US.819")
		{
			#do stuff with env to make it work
			delete $ENV{CLIENT_LOCALE} if defined;
			delete $ENV{DB_LOCALE} if defined;
			delete $ENV{DBDATE} if defined;
			
			$ENV{DBMONEY} = ',' unless (defined $ENV{DBMONEY} && $ENV{DBMONEY} eq ',');
			
			workingTitleSubName($database);
			
		}
		elsif(trim($collation) eq "bg_BG.915")
		{
			#do stuff with env to make it work
			$ENV{CLIENT_LOCALE} = 'bg_bg.8859-5';
			$ENV{DB_LOCALE} = 'bg_bg.8859-5';
			$ENV{DBMONEY} = '.';
			$ENV{DBDATE} = 'MDY4/';		
			
			workingTitleSubName($database);
			
		}
		else
		{
			logMessage("unknown collation $collation for database $database");
		}
		
	}
}

close $log_fh;

exit 0;

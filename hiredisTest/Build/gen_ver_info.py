#!/bin/env python

import os, sys
import string

def get_svn_info() :

	svn_version="0"
	
	os.putenv( "LC_ALL", "C" )
        info = os.popen( "svn info .." ).read()
        for line in string.split( info, "\n" ) :
                if string.find( line, "Last Changed Rev:" ) == 0 :
                        svn_version = str(int(line[18:]))

	return svn_version;

# <0> get file_name
if len( sys.argv ) >= 2 :
	ver_file=sys.argv[1]
else :
	print "Usage: python gen_ver_info file_name"
	sys.exit( -1 );

# <1> get svn and date information
svn_version = get_svn_info()
build_date = os.popen( "date" ).readline().strip('\n')

# <2> generate version.h
fp = open( ver_file, 'w' )
print	>>fp,"#define PROGNAME        \"HSMTS\" " 
print	>>fp,"#define VERSION         \"3.0\" " 
print   >>fp,"#define SVNVERSION      \"" + svn_version + "\" "
print	>>fp,"#define BUILD           \"" + build_date + "\" "
fp.close()

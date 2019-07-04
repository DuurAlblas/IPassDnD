#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
#
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := supp.cpp reader.cpp rc522.cpp

# header files in this project
HEADERS := supp.hpp reader.hpp rc522.hpp

# other places to look for files for this project
SEARCH  :=

# set RELATIVE to the next higher directory
# and defer to the appropriate Makefile.* there
RELATIVE := ../../v1oopc-examples
include $(RELATIVE)/Makefile.due
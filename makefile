#
#  makefile
#
#  Copyright (C) 2012  MT
#
#  This  program is free software: you can redistribute it and/or modify it
#  under  the terms of the GNU General Public License as published  by  the
#  Free  Software Foundation, either version 3 of the License, or (at  your
#  option) any later version.
#
#  This  program  is distributed in the hope that it will  be  useful,  but
#  WITHOUT   ANY   WARRANTY;   without even   the   implied   warranty   of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
#  Public License for more details.
#
#  You  should have received a copy of the GNU General Public License along
#  with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#  Note - Shell commands must start with a tab character at the beginning
#  of each line NOT spaces..!
#
#  09 Apr 12   0.1   - Initial version derived from gtk-sample-menu - MT
#  17 Aug 13   0.2   - Added  make  clean  and make verify  to  delete  any 
#                      object  files and automatically compare  the  output
#                      against that expected - MT
#  18 Aug 13         - Now re-compiles sources before verifying output - MT
#
PROGRAM = gcc-pwdgen
SOURCE	= $(PROGRAM).c
OBJECT	= $(SOURCE:.c=.o)
OUTPUT	= gcc-pwdgen.t
FLAGS	= 
LIBS	= 
CC	= gcc
DIFF	= diff
#
$(PROGRAM): $(OBJECT) 
#	@echo '*** Linking $(OBJECT)'
	@$(CC) $(FLAGS) $(OBJECT) -o $(PROGRAM) $(LIBS)
#
$(OBJECT): $(SOURCE)
#	@echo '*** Compiling $(SOURCE)'
	@$(CC) $(FLAGS) -c $(SOURCE)
#
all: clean $(PROGRAM)
#
clean:
#	Tidy up by simply deleting ALL object files this will force all the
#	sources to be recompiled.
#	@echo '*** Deleting object files'
	@rm -f $(OBJECT)
#
verify: clean
#	Rebuilds source and checks output
#	@echo '*** Compiling $(SOURCE)'
	@$(CC) $(FLAGS) -c $(SOURCE)
#	@echo '*** Linking $(OBJECT)'
	@$(CC) $(OBJECT) -o $(PROGRAM) $(LIBS)
#	@echo '*** Cleaning up object files'
	@rm -f $(OBJECT)
#	@echo '*** Verifying $(PROGRAM) output against $(OUTPUT)'
	@./$(PROGRAM) |$(DIFF) -E -B -y --suppress-common-lines - ./$(OUTPUT) ; if [ $$? -eq 0 ] ; then echo "Result:  PASSED" ; fi


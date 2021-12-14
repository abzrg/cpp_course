#
# =============================================================================
#
# Philipp Schubert
#
#    Copyright (C) 2017
#    Software Engineering Group
#    Heinz Nixdorf Institut
#    University of Paderborn
#    philipp.schubert@upb.de
#
# =============================================================================
#

###############################################################################
# Compiler Settings                                                           #
###############################################################################

# Set-up the compiler to use
CXX = clang++

# Set-up the basic compiler flags
CXX_FLAGS = -std=c++14 # set-up the C++ standard to use
CXX_FLAGS += -pedantic # be pedantic about it
CXX_FLAGS += -Wall # enable compiler warnings
CXX_FLAGS += -Wextra # enable some more warnings
CXX_FLAGS += -MMD # header file detection stuff
CXX_FLAGS += -MP # header file detection stuff
CXX_FLAGS += -stdlib=libstdc++ # libstdc++ for GCC, libc++ for Clang
# CXX_FLAGS += -Ofast # use all compiler optimizations that are possible
# CXX_FLAGS += -march=native # compile the code for this very architecture
# CXX_FLAGS += -Wno-unknown-warning-option # ignore unknown warnings (as
										   # '-Wno-maybe-uninitialized'
										   # resulting from internal bugs)
# CXX_FLAGS += -Qunused-arguments # ignore unused compiler arguments
CXX_FLAGS += -pipe # do not use temporary files, use pipes instead
CXX_FLAGS += -O0 # Disable Optimizations
CXX_FLAGS += -ggdb3 # Produce debugging information for use by GDB
					# (Level 3 includes extra information, such as all the macro
					# definitions present in the program)


###############################################################################
# Function Definitions                                                        #
###############################################################################

# Define useful make functions (recwildcard: recursive wildcard)
recwildcard=$(wildcard $1$2)\
			$(foreach d,$(wildcard $1*),$(call recwildcard,$d/,$2))

#################
# function call #
#################
# - syntax
#
# $(FUNCTION ARGUMENTS)
# or
# ${FUNCTION ARGUMENTS}
#
#  - Function: is a function name
#  - ARGUMENTS: arguments of the function
#    - separated from the function name by one or more spaces or tabs,
#    - and if there is more than one argument, then they are separated by
#    commas

#################
# call function #
#################
# - 'call' function can be used to create new parameterized functions
# - You can write a complex expression as the value of a variable, then use
# call to expand it with different values
# - syntax
#
#   $(call variable,param,param,...)
#
# - When make expands this function,
#   - it assigns each param to temporary variables $(1), $(2), etc.
#   - The variable $(0) will contain variable.
# - NOTE: The 'variable' is the name of a variable, not a reference to that
# variable
#   - You can, however, use a variable reference in the name if you want the
#   name not to be a constant
# - NOTE: If 'variable' is the name of a built-in function, the built-in
# function is always invoked (even if a make variable by that name also
# exists).
# - EXAMPLE: This macro simply reverses its arguments
#
#   reverse = $(2) $(1)
#   foo = $(call reverse,a,b) # $(1) = a, $(2) = b, foo = b a

####################
# foreach function #
####################
# - syntax
#
#   $(foreach var,list,text)
#
# - The first two arguments, 'var' and 'list', are expanded before anything
# else is done
#   - Note that the last argument, 'text', is not expanded at the same time
# -  Then for each word of the expanded value of list, the variable named by
# the expanded value of var is set to that word, and text is expanded.
# Presumably text contains references to that variable, so its expansion will
# be different each time.
# - The result is that text is expanded as many times as there are
# whitespace-separated words in list. The multiple expansions of text are
# concatenated, with spaces between them, to make the result of foreach.
# - EXAMPLE: following sets the variable 'files'.to the list of all files in
# the directories in the list 'dirs'.
#
#    dirs := a b c d
#    files := $(foreach dir,$(dirs),$(wildcard $(dir)/*))
#
# Here text is '$(wildcard $(dir)/*)'. The first repetition finds the value 'a'
# for dir, so it produces the same result as '$(wildcard a/*)'. the second
# repetition produces the result of '$(wildcard b/*)'. and the third, that of
# '$(wildcard c/*)'.

#####################
# wildcard function #
#####################
# - wildcard expansion does not normally take place when a variable is set, or
# inside the arguments of a function.
# - To address that, we use 'wildcard' function:
#   - $(wildcard PATTERN...)
# - This string, used anywhere in a makefile, is replaced by a space-separated
# list of names of existing files that match one of the given file name
# patterns.  If no existing file name matches a pattern, then that pattern is
# omitted from the output of the 'wildcard' function


###############################################################################
# Specify Some File and Directory Paths                                       #
###############################################################################

# Name of the executable
EXE = hash

# Basic project directories
BIN = bin/
OBJDIR = obj/
DOC = doc/
SRC = src/
# All the directories that starts with src and all the directory within them
ALL_SRC = $(sort $(dir $(call recwildcard,$(SRC)**/*/)))

################
# dir function #
################
# (https://www.gnu.org/software/make/manual/html_node/File-Name-Functions.html)
# - syntax
#
#   $(dir names...)
#
# - Extracts the directory-part of each file name in 'names'. The
# directory-part of the file name is everything up through (and including) the
# last slash in it. If the file name contains no slash, the directory part is
# the string './'. For example,
#
#   $(dir src/foo.c hacks)
#
# produces the result 'src/ ./'.

#################
# sort function #
#################
# (https://www.gnu.org/software/make/manual/html_node/Text-Functions.html)
# - syntax
#
#   $(sort list)
#
# - Sorts the words of 'list' in lexical order, removing duplicate words. The
# output is a list of words separated by single spaces. Thus,
#
#   $(sort foo bar lose)
#
# returns the value 'bar foo lose'.
# - Incidentally, since sort removes duplicate words, you can use it for this
# purpose even if you don'. care about the sort order.

# Set the virtual (search) path
VPATH = $(SRC):$(ALL_SRC)

#########
# VPATH #
#########
# - If a file that is listed as a target or prerequisite does not exist in the
# current directory, make searches the directories listed in VPATH for a file
# with that name.
# - In the VPATH variable, directory names are separated by colons or blanks.
# - The order in which directories are listed is the order followed by make in
# its search.

# Determine all object files that we need in order to produce an executable
# - Find all the .cpp file under src (recursively)
# - substitute their suffix (.cpp -> .o)
# - remove filepath till the last / (only basename.o)
# - prefix all the file names with our directory designated for storing object
#   file
OBJ = $(addprefix\
	  $(OBJDIR),$(notdir $(patsubst %.cpp,%.o,$(call recwildcard,src/,*.cpp))))

##########################
# patsubstitute function #
##########################
# (https://www.gnu.org/software/make/manual/html_node/Text-Functions.html)
# - syntax
#
#    $(patsubst pattern,replacement,text)
#
# - Finds whitespace-separated words in 'text' that match 'pattern' and
# replaces them with 'replacement'
#   - Here 'pattern' may contain a '%' which acts as a wildcard, matching any
#   number of any characters within a word.
#   - If replacement also contains a '%', the '%' is replaced by the text that
#   matched the '%' in pattern.
#     - Only the first '%' in the pattern and replacement is treated this way;
#     any subsequent '%' is unchanged.

###################
# notdir function #
###################
# (https://www.gnu.org/software/make/manual/html_node/File-Name-Functions.html)
#  - syntax
#
#    $(notdir names...)
#
# - Extracts all but the directory-part of each file name in 'names'. If the
#   file name contains no slash, it is left unchanged. Otherwise, everything
#   through the last slash is removed from it.
#
#    $(notdir src/foo.c hacks)
#
#   produces the result 'foo.c hacks'.

######################
# addprefix function #
######################
# (https://www.gnu.org/software/make/manual/html_node/File-Name-Functions.html)
# - syntax
#
#    $(addprefix prefix,names…)
#
# - The argument 'names' is regarded as a series of names, separated by
#   whitespace; 'prefix' is used as a unit. The value of 'prefix' is prepended
#   to the front of each individual name and the resulting larger names are
#   concatenated with single spaces between them. For example,
#
#    $(addprefix src/,foo bar)
#
#   produces the result 'src/foo src/bar'.

# To determine source (.cpp) and header (.hh) dependencies
DEP = $(OBJ:.o=.d)
	#  - The above syntax is a substitution reference,
	#  - It has the form '$(var:a=b)' (or '${var:a=b}') and its meaning is to
	#  take the value of the variable 'var', replace every 'a' at the end of a
	#  word with 'b' in that value, and substitute the resulting string

# Important scripts and binaries to use
AUTOFORMAT_SCRIPT := misc/format_src_code.py


###############################################################################
# Targets and Rules                                                           #
###############################################################################

.PHONY: all

################
# PHONY target #
################
# A PHONY target is one that is not really the name of a file; rather it is just
# a name for a recipe to be executed when you make an explicit request. There
# are two reasons to use a phony target: to avoid a conflict with a file of the
# same name, and to improve performance.
# (https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html)

all: $(OBJDIR) $(BIN) $(BIN)$(EXE)

# To resolve header dependencies
-include $(DEP)

#####################
# include directive #
#####################
# The include directive tells make to suspend reading the current makefile and
# read one or more other makefiles before continuing. The directive is a line in
# the makefile that looks like this:
#
# include filenames...
#
# - 'filenames' can contain shell file name patterns. If 'filenames' is empty,
#   nothing is included and no error is printed.
#
# - If the file names contain any variable or function references, they are
#   expanded.
#
# - One use of this is when you want to generate prerequisites from source files
#   automatically; the prerequisites can be put in a file that is included by
#   the main makefile. This practice is generally cleaner than that of somehow
#   appending the prerequisites to the end of the main makefile as has been
#   traditionally done with other versions of make.
#
# - If the specified name does not start with a slash, and the file is not found
#   in the current directory, several other directories are searched.
#   - First, any directories you have specified with the '-I' or '--include-dir'
#   option are searched.
#
#   - Then the following directories (if they exist) are searched, in this
#   order:
#     - prefix/include (normally /usr/local/include 1)
#     - /usr/gnu/include
#     - /usr/local/include
#     - /usr/include
#
# - If an included makefile cannot be found in any of these directories, a
#   warning message is generated, but it is not an immediately fatal error;
#   processing of the makefile containing the include continues. Once it has
#   finished reading makefiles, make will try to remake any that are out of date
#   or don't exist. Only after it has tried to find a way to remake a makefile
#   and failed, will make diagnose the missing makefile as a fatal error.
#
# - If you want make to simply ignore a makefile which does not exist or cannot
#   be remade, with no error message, use the -include directive instead of
#   include, like this:
#
#    -include filenames...
#
#   This acts like include in every way except that there is no error (not even
#   a warning) if any of the filenames (or any prerequisites of any of the
#   filenames) do not exist or cannot be remade.
#
# - For compatibility with some other make implementations, sinclude is another
#   name for -include.

# Create object directory
$(OBJDIR):
	mkdir $@

# $@ == name of the target

# Create binary directory
$(BIN):
	mkdir $@

# Link all object code (against additional libraries) to produce the machine
# code
$(BIN)$(EXE): $(OBJ)
	$(CXX) $(CXX_FLAGS) $^ $(MATH_LIBS) -o $@
	@echo "done ;-)"

#   ^
# @ before echo command causes it to not appear in the stdout

# Compile source code to object code
$(OBJDIR)%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

.PHONY: doc
# Create the code documentation
doc:
	@echo "Building the documentation of the source code ..."
	cd $(SRC); \
		doxygen doxy_config.conf

.PHONY: open_doc
open_doc:
	$$BROWSER $(DOC)/html/index.html

.PHONY: format
# Format the source code of this project
format:
	@echo "Formatting the projects source code using clang-format ..."
	python3 $(AUTOFORMAT_SCRIPT)

.PHONY: clean
# Clean all auto-generated stuff
clean:
	$(RM) -rf $(BIN)
	$(RM) -rf $(OBJDIR)
	$(RM) -rf $(DOC)

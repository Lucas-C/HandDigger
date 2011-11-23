# Debbug level : 0 for a "release" version
DEBUG		:= 1

EXEC		:= digger

# Basename and content of an archive
ARCHIVE		:= $(EXEC)
CONTENU		:= $(SRC_REP) Makefile *.cpp
BCKUP_REP	:= ../

######################################################

ifeq (1,$(DEBUG))
DBGFLAGS	:= -g3 -D_DEBUG -Wall -Wextra -pedantic-errors -Wfloat-equal -Wconversion -Wshadow -Weffc++
else
DBGFLAGS	:= -O1 -DNDEBUG -Wall -Wextra -pedantic
endif

LIB_DYN		:= -lGLU -lGL -lglut

CXX			:= g++
CXXFLAGS	:= $(DBGFLAGS)
LDFLAGS		:= $(CXXFLAGS) $(LIB_DYN)


all: $(EXEC)

$(EXEC): digger.cpp
	@$(CXX) $(LDFLAGS) $< -o $@


.PHONY: clean val prof todo accents archive backup help

clean:
	@$(RM) $(EXEC)
	
# valgrind --leak-check=full --gen-suppressions=all ./main 2>&1 | egrep "^[{}]|^   [^ \t]" > sfml.supr
# --suppressions=sfml.supp
val: $(TESTS)
	@: $(foreach prog,$(TESTS), && echo $(prog) && valgrind --leak-check=full --track-origins=yes ./$(prog) && echo)

#FROM: http://goog-perftools.sourceforge.net/doc/cpu_profiler.html
#Perl script FROM: http://google-perftools.googlecode.com/svn/trunk/src/pprof
prof: $(EXEC)
	@CPUPROFILE=$(EXEC).profile ./$(EXEC)
	@./pprof --gv $(EXEC) $(EXEC).profile

todo:
	@echo "#### TODO:"
	@grep --color=auto -rin --exclude="*.svn*" TODO $(SRC_REP)*

accents:
	@echo "#### ACCENTS:"
	@grep --color=auto -rin --exclude="*.svn*" -e "é" -e "è" -e "à" -e "ç" -e "ê" -e "ù" -e "ô" $(SRC_REP)* $(SCRIPTS_REP)*

archive: clean
	@$(RM) $(ARCHIVE).tgz
	@mkdir $(ARCHIVE)
	@cp -rt $(ARCHIVE) $(CONTENU)
	@$(RM) -r `find $(ARCHIVE) -name .svn`
	@tar -czf $(ARCHIVE).tgz $(ARCHIVE)
	@$(RM) -r $(ARCHIVE)	

backup: archive
	@mv $(ARCHIVE).tgz $(BCKUP_REP)`date +%y-%m-%d`_$(ARCHIVE).tgz

help:
	@echo "### Makefile targets"
	@echo " -all- \t\t : generate all the tests"
	@echo " help"
	@echo " clean"
	@echo " val \t\t : call valgrind on the tests"
	@echo " prof \t\t : analyse the gmon.out"
	@echo " todo \t\t : list the 'TODO'"
	@echo " accents \t : list the accents in the source files"
	@echo " archive \t : create an archive named '$(ARCHIVE).tgz' of the content generated for the project"
	@echo " backup \t : create an archive and move it to a backup folder ('$(BCKUP_REP)')"

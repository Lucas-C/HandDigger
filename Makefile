# Debbug level : 0 for a "release" version
DEBUG		:= 1

EXEC		:= digger
TEST_FREENECT	:= cppview

SRC_DIR		:= ./
OBJ_DIR		:= ./
INC_DIR		:= include/
FREENECT_DIR:= freenect_cpp/
FREENECT_SRCS_DIR	:= /opt/libfreenect/

# Basename and content of an archive
ARCHIVE		:= HandDigger
CONTENU		:= $(SRC_DIR) Makefile *.cpp
BCKUP_DIR	:= ../

######################################################

SRCS		:= $(wildcard $(SRC_DIR)*.cpp)
HDRS		:= $(wildcard $(SRC_DIR)*.hpp) $(wildcard $(SRC_DIR)*.tpp)
OBJS		:= $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRCS))

ifeq (1,$(DEBUG))
DBGFLAGS	:= -g3 -D_DEBUG -Wall -Wextra -pedantic-errors -Wfloat-equal -Wconversion -Wshadow -Weffc++
else
DBGFLAGS	:= -O1 -DNDEBUG -Wall -Wextra -pedantic
endif

LIB_GLUT	:= -lGLU -lGL -lglut
INC_FREENECT:= -isystem $(INC_DIR)
LIB_FREENECT:= -L $(FREENECT_DIR)lib/ -lfreenect -lusb-1.0

CXX			:= g++ -std=c++0x
CXXFLAGS	:= $(DBGFLAGS)
LDFLAGS		:= $(CXXFLAGS) $(LIB_GLUT)


all: $(EXEC)

$(OBJS): $(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(SRC_DIR)%.h
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC): digger.cc
	@$(CXX) $(LDFLAGS) $< -o $@

$(TEST_FREENECT): cppview.cc $(OBJS)
	@$(CXX) $(LDFLAGS) $(INC_FREENECT) $(LIB_FREENECT) $^ -o $@

.PHONY: clean val prof todo accents archive backup help

dep:
	@cd $(FREENECT_DIR) && cmake $(FREENECT_SRCS_DIR)

go: $(EXEC)
	@./$(EXEC)

clean:
	@$(RM) *.o $(EXEC) $(TEST_FREENECT)
	
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
	@grep --color=auto -rin --exclude="*.svn*" TODO $(SRC_DIR)*

accents:
	@echo "#### ACCENTS:"
	@grep --color=auto -rin --exclude="*.svn*" -e "é" -e "è" -e "à" -e "ç" -e "ê" -e "ù" -e "ô" $(SRC_DIR)* $(SCRIPTS_DIR)*

archive: clean
	@$(RM) $(ARCHIVE).tgz
	@mkdir $(ARCHIVE)
	@cp -rt $(ARCHIVE) $(CONTENU)
	@$(RM) -r `find $(ARCHIVE) -name .svn`
	@tar -czf $(ARCHIVE).tgz $(ARCHIVE)
	@$(RM) -r $(ARCHIVE)	

backup: archive
	@mv $(ARCHIVE).tgz $(BCKUP_DIR)`date +%y-%m-%d`_$(ARCHIVE).tgz

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
	@echo " backup \t : create an archive and move it to a backup folder ('$(BCKUP_DIR)')"

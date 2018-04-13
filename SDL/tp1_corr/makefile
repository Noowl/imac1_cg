CC       =  gcc
CFLAGS   = -Wall -O2 -g
LIB      = -lSDL -lGLU -lGL -lm  
INCLUDES = 

RM       = rm -f
BIN      = Exercice3 Exercice4 Exercice5 Exercice6
DIRNAME  = $(shell basename $$PWD)
BACKUP   = $(shell date +`basename $$PWD`-%m.%d.%H.%M.tgz)
STDNAME  = $(DIRNAME).tgz

all : $(BIN)

% : %.c
	@echo "edition de liens $< + lib*.so -> $@"
	@$(CC) $(CFLAGS) $< $(LIB) -o $@
	@echo "------------------------"

clean :	
	@echo "**************************"
	@echo "CLEAN"
	@echo "**************************"
	$(RM) *~ $(OBJ) $(BIN) 

tar : clean 
	@echo "**************************"
	@echo "TAR"
	@echo "**************************"
	cd .. && tar cvfz $(BACKUP) $(DIRNAME)


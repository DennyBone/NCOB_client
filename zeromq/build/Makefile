PROJECT_NAME = ncob_client

CC = gcc
OBJCOPY = objcopy
SIZE = size

SOURCEDIR = ../src
ODIR=obj

#INCLUDE = -I"../common/applications/user_application/user_board/config" -I"../src/config"
IDIR =../include
INCLUDE=-I$(IDIR)

SRCS = $(shell find $(SOURCEDIR) -name '*.c') #read in all source files
EXCLUDES := $(shell cat ./excluded_sources.txt) #read in list of source files to exclude
SRC := $(filter-out $(EXCLUDES), $(SRCS)) #remove exlcuded source files

SRC_DIRS = $(dir $(SRC))
OBJS = $(SRC:.c=.o)
OBJECTSs = $(notdir $(OBJS))
OBJECTS = $(patsubst %,$(ODIR)/%,$(OBJECTSs))

vpath %.c $(SRC_DIRS)

CFLAGS = -g3 -O1 -ffunction-sections -fdata-sections
WFLAGS = -Wall -Wpadded
LFLAGS = -Wl,-Map=ncob_client.map,--cref -Wl,--gc-sections -Wl,--print-gc-sections
LIBS   = -lczmq
#-lzmq

#.PHONY: all
#	all: $(PROJECT_NAME)
.PHONY: clean

#%.o: %.c
#	$(CC) -c -o $@ -I. $(INCLUDE) $(DEFS) $(UNDEFS) $(CFLAGS) $(WFLAGS) $^
$(ODIR)/%.o: %.c
	$(CC) -c -o $@ $(INCLUDE) $(CFLAGS) $(WFLAGS) $^

$(PROJECT_NAME).elf: $(OBJECTS)
	$(CC) $(CFLAGS) $(LFLAGS) $^ $(LIBS) -o $@
	$(SIZE) $@
#	$(OBJCOPY) -O binary $(PROJECT_NAME).elf $(PROJECT_NAME)
#	$(OBJCOPY) -O ihex $(PROJECT_NAME).elf   $(PROJECT_NAME).hex
#ncob_client: $(OBJECTS)
#	$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS) $(LIBS)

#clean:
#	rm -f *.o $(PROJECT_NAME).elf $(PROJECT_NAME).hex $(PROJECT_NAME).bin $(PROJECT_NAME).map
clean:
	rm -f $(ODIR)/*.o $(PROJECT_NAME) $(PROJECT_NAME).map $(PROJECT_NAME).elf 
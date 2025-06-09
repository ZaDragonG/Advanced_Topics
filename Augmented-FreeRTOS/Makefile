######## Build options ########

verbose = 0

######## Build setup ########

CC              = gcc
SRCROOT         = $(CURDIR)
ODIR            = obj

# Source VPATHS
VPATH           += $(SRCROOT)/Source
VPATH	        += $(SRCROOT)/Source/portable/MemMang
VPATH	        += $(SRCROOT)/Source/portable/GCC/POSIX
VPATH           += $(SRCROOT)/Demo/Common
VPATH			+= $(SRCROOT)/Project/FileIO
VPATH			+= $(SRCROOT)/Project
VPATH           += . # <-- Add current dir for benchmark.c

# FreeRTOS Core
C_FILES			+= croutine.c
C_FILES			+= event_groups.c
C_FILES			+= list.c
C_FILES			+= queue.c
C_FILES			+= tasks.c
C_FILES			+= timers.c

# Portable implementation
C_FILES			+= heap_3.c
C_FILES			+= port.c

# Project-specific files
C_FILES			+= main.c
C_FILES			+= benchmark.c

# Includes
INCLUDES        += -I$(SRCROOT)/Source/include
INCLUDES        += -I$(SRCROOT)/Source/portable/GCC/POSIX/
INCLUDES        += -I$(SRCROOT)/Project
INCLUDES        += -I/usr/include/x86_64-linux-gnu/
INCLUDES        += -I. # <-- Include current directory for benchmark.h

# Object files
OBJS = $(patsubst %.c,%.o,$(C_FILES))
_OBJS = $(patsubst %,$(ODIR)/%,$(OBJS))

######## C Flags ########

CWARNS += -W -Wall -Wextra -Wformat -Wmissing-braces -Wno-cast-align
CWARNS += -Wparentheses -Wshadow -Wno-sign-compare -Wswitch
CWARNS += -Wuninitialized -Wunknown-pragmas -Wunused-function
CWARNS += -Wunused-label -Wunused-parameter -Wunused-value
CWARNS += -Wunused-variable -Wmissing-prototypes

CFLAGS += -m32 -DDEBUG=1
CFLAGS += -g -UUSE_STDIO -D__GCC_POSIX__=1
ifneq ($(shell uname), Darwin)
CFLAGS += -pthread
endif
CFLAGS += -DMAX_NUMBER_OF_TASKS=300
CFLAGS += $(INCLUDES) $(CWARNS) -O2

######## Build Targets ########

.PHONY : all
all: FreeRTOS-Sim

$(ODIR)/%.o: %.c
	@mkdir -p $(dir $@)
ifeq ($(verbose),1)
	@echo ">> Compiling $<"
	$(CC) $(CFLAGS) -c -o $@ $<
else
	@echo ">> Compiling $(notdir $<)"
	@$(CC) $(CFLAGS) -c -o $@ $<
endif

FreeRTOS-Sim: $(_OBJS)
	@echo ">> Linking $@..."
ifeq ($(verbose),1)
	$(CC) $(CFLAGS) $^ -o $@
else
	@$(CC) $(CFLAGS) $^ -o $@
endif
	@echo "-------------------------"
	@echo "BUILD COMPLETE: $@"
	@echo "-------------------------"

.PHONY : clean
clean:
	@-rm -rf $(ODIR) FreeRTOS-Sim
	@echo "--------------"
	@echo "CLEAN COMPLETE"
	@echo "--------------"

.PHONY: valgrind
valgrind: FreeRTOS-Sim
	valgrind.bin --tool=memcheck --leak-check=full --show-reachable=yes --track-fds=yes ./FreeRTOS-Sim

PROJDIR 		:= $(realpath $(CURDIR))
SOURCEDIR 		:= $(PROJDIR)/src
SOURCES			:= $(wildcard $(SOURCEDIR)/*.c)
INCLUDEDIR		:= $(PROJDIR)/include	
HEADERS			:= $(wildcard $(INCLUDEDIR)/*.h)
OBJS			:= $(subst $(SOURCEDIR), $(PROJDIR), $(SOURCES:.c=.o))

TARGET 			= mlcc

CC 				= gcc
CFLAGS 			= -g -Wall -I$(INCLUDEDIR)

define generate_rules
$(PROJDIR)/%.o: $(1)/%.c
	@echo Building $$@
	$(CC) -c $(CFLAGS) -o $$@ $$<
endef

all: $(TARGET)
	echo Linking $@

$(TARGET): $(OBJS) $(HEADERS)
	$(CC) -o $(PROJDIR)/../$(TARGET) $(OBJS)

$(foreach src, $(SOURCEDIR), $(eval $(call generate_rules, $(src))))

# mlcc.o: mlcc.c
#	$(CC) $(CFLAGS) -c -o mlcc.o mlcc.c

clean:
	rm -f *.o $(PROJDIR)/../mlcc

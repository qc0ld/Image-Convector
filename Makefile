AS = /usr/bin/nasm
LD = /usr/bin/ld

CCFLAGS = -g -c -O3
ASFLAGS = -g -f elf64
LDFLAGS = -static -z noexecstack -lm

LIBPATH = -L /lib/gcc/x86_64-unknown-linux-gnu/12.2.0 -L /lib
OBJPATH = /usr/lib

LIBS = -lgcc -lgcc_eh -lc -lm

PREOBJ = $(OBJPATH)/crt1.o $(OBJPATH)/crti.o
POSTOBJ = $(OBJPATH)/crtn.o

SRCS = lab.c func.c funcasm.s
HEAD = func.h
OBJS = lab.o func.o funcasm.o

EXE = lab

all: $(SRCS) $(EXE)

clean:
	rm -rf $(EXE) $(OBJS)

$(OBJS): $(HEAD)

$(EXE): $(OBJS)
	$(LD) $(LDFLAGS) $(LIBPATH) $(PREOBJ) $(OBJS) $(POSTOBJ) -\( $(LIBS) -\) -o $@

.c.o:
	$(CC) $(CCFLAGS) $< -o $@

.s.o:
	$(AS) $(ASFLAGS) $< -o $@


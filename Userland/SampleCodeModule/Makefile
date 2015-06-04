include ../Makefile.inc

MODULE=sampleCodeModule.bin
SOURCES=$(wildcard *.c)
SOURCES_ASM=$(wildcard *.asm)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)

all: $(MODULE)

$(MODULE): $(OBJECTS_ASM) $(SOURCES)
	$(GCC) $(GCCFLAGS) -T sampleCodeModule.ld $(SOURCES) -o ../$(MODULE)


%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o

.PHONY: all clean

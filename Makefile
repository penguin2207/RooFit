TARGET = libSusyRooFit.so
PDFSOURCES = $(wildcard src/*.cc)
PDFHEADERS = $(patsubst src/%.cc,include/%.h,$(PDFSOURCES))
PDFOBJECTS = $(patsubst src/%.cc,build/%.o,$(PDFSOURCES))

CFLAGS = -c -O3 -Wall -fPIC $(shell root-config --cflags)
LFLAGS = -shared -Wl

EXTRAINC = -I. -I$(subst lib/libRooFit.so,include,$(CMSSW_RELEASE_BASE)/external/$(SCRAM_ARCH)/lib/$(shell readlink $(CMSSW_RELEASE_BASE)/external/$(SCRAM_ARCH)/lib/libRooFit.so))
LIBS = $(shell root-config --libs)

all: $(TARGET)

clean:
	rm -f $(TARGET) build/* > /dev/null 2>&1

$(TARGET): $(PDFOBJECTS) build/pdfDict.o
	g++ $(LFLAGS) -o $(TARGET) $(LIBS) $^

build/pdfDict.o: build/pdfDict.cc | build
	g++ $(CFLAGS) $(EXTRAINC) -o $@ $< $(LIBS)

build/%.o: src/%.cc include/%.h | build
	g++ $(CFLAGS) $(EXTRAINC) -o $@ $< $(LIBS)

build:
	@mkdir -p $@

build/pdfDict.cc: $(PDFHEADERS) include/LinkDef.h
	rootcint -f $@ -c $(EXTRAINC) $^

TARGET = libSusyRooFit.so
PDFSOURCES = $(wildcard src/*Shape.cc)
PDFHEADERS = $(patsubst src/%.cc,include/%.h,$(PDFSOURCES))
ALLSOURCES = $(PDFSOURCES) src/pdfDict.cc
ALLOBJECTS = $(patsubst src/%.cc,%.o,$(ALLSOURCES))

CFLAGS = -c -O3 -Wall -fPIC $(shell root-config --cflags)
LFLAGS = -shared -Wl

EXTRAINC = -I. -I$(subst lib/libRooFit.so,include,$(CMSSW_RELEASE_BASE)/external/$(SCRAM_ARCH)/lib/$(shell readlink $(CMSSW_RELEASE_BASE)/external/$(SCRAM_ARCH)/lib/libRooFit.so))
LIBS = $(shell root-config --libs)

all: $(TARGET)

clean:
	rm -f $(TARGET) *.o src/pdfDict.* > /dev/null 2>&1

$(TARGET): $(ALLOBJECTS)
	g++ $(LFLAGS) -o $(TARGET) $(LIBS) $^

pdfDict.o: src/pdfDict.cc
	g++ $(CFLAGS) $(EXTRAINC) -o $@ $< $(LIBS)

%.o: src/%.cc include/%.h
	g++ $(CFLAGS) $(EXTRAINC) -o $@ $< $(LIBS)

src/pdfDict.cc: $(PDFHEADERS) src/LinkDef.h
	rootcint -f $@ -c $(EXTRAINC) $^

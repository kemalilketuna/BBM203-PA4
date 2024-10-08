CC = g++
# -Wno-c++11-extensions is to suppress the warning "extended initializer lists only available with -std=c++11 or -std=gnu++11"
CFLAGS = -std=c++11 -g -Wno-c++11-extensions
LDFLAGS =

SOURCES = main.cpp Sector.cpp SpaceSectorBST.cpp SpaceSectorLLRBT.cpp KD_Tree.cpp kNN.cpp
HEADERS = Sector.h SpaceSectorBST.h SpaceSectorLLRBT.h KD_Tree.h KDT_Node.h kNN.h kNN_DAT_Parser.h kNN_Data.h
HEADER_GCH = $(wildcard *.gch)
MISSION_RESCUE = mission_rescue

all: $(MISSION_RESCUE)

$(MISSION_RESCUE): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) $(LDFLAGS) -o $@

clean:
	rm -f $(MISSION_RESCUE) $(HEADER_GCH)

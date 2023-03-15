INC := lib/
CXXFLAGS_BASE := -std=c++20 -Wall -Wpedantic -Wextra -I$(INC)
CXXFLAGS_SDL := `pkg-config --cflags sdl2`
LDLIBS_SDL := `pkg-config --libs sdl2`
CXXFLAGS := $(CXXFLAGS_BASE) $(CXXFLAGS_SDL)
LDLIBS := $(LDLIBS_SDL)

SRC := src/main.cpp
EXE := build/$(basename $(notdir $(SRC)))
HEADER_LIST := build/$(basename $(notdir $(SRC))).d

default-target: $(EXE)

$(EXE): $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS)

test: build/tests
.PHONY: build/tests
build/tests: src/tests.cpp
	$(CXX) $(CXXFLAGS_BASE) $^ -o $@
	build/tests

build/ctags-dlist: ctags-dlist.cpp
	$(CXX) $(CXXFLAGS_BASE) $^ -o $@

.PHONY: $(HEADER_LIST)
$(HEADER_LIST): $(SRC)
	$(CXX) $(CXXFLAGS) -M $^ -MF $@

.PHONY: tags
tags: $(HEADER_LIST) build/ctags-dlist
	build/ctags-dlist $(HEADER_LIST)
	ctags --c-kinds=+p+x -L headers.txt
	ctags --c-kinds=+p+x+l -a $(SRC)

what:
	echo $(EXE)


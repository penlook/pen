#
# Pengo Project
#
# Copyright (c) 2015 Penlook Development Team
#
# --------------------------------------------------------------------
#
# This program is free software: you can redistribute it and/or
# modify it under the terms of the GNU Affero General Public License
# as published by the Free Software Foundation, either version 3
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public
# License along with this program.
# If not, see <http://www.gnu.org/licenses/>.
#
# --------------------------------------------------------------------
#
# Authors:
#     Loi Nguyen       <loint@penlook.com>

LIB     = pen
TEST	= pentest
GCC     = gcc
G++		= g++
GCCVER  = c11  
G++VER 	= c++14
FGCC    = -std=$(GCCVER) -O3 -fPIC
FG++    = -std=$(G++VER) -O3 -fPIC
DEBUG   = -std=$(G++VER) -pipe -g0 -fno-inline -Wall -fPIC
EXECUTE = /usr/bin/$(LIB)
LIBSYS  = /usr/lib
TESTF	= -std=$(G++VER) -g -pthread -L/usr/lib/gtest/lib -I/usr/lib/gtest/include -I/usr/lib/pen -lpen
INCLUDE = inc
SOURCED = src
TESTD   = obj/
OBJECTD = obj/
HEADERS = $(shell find /usr/lib/pen -name *.h)
SOURCES = $(shell find src -name '*.c*' -o -name '*.s')
TESTS   = $(shell find test -name *.cpp)
SOURCE  = $(patsubst %.cpp, %.o, $(SOURCES))
SOURCE  := $(patsubst %.c, %.o, $(SOURCE))
SOURCE  := $(patsubst %.s, %.o, $(SOURCE))
HEADER  = $(patsubst %.h, %.h.gch, $(HEADERS))
OBJECTS = $(addprefix $(OBJECTD), $(SOURCE))
OHEADER = $(addprefix $(OHEADERD), $(HEADER))
BINARY  = $(OBJECTD)/$(SOURCED)/$(LIB)
OBJECTT = $(addprefix $(TESTD)/, $(patsubst %.cpp, %.o, $(TESTS)))
G++FLAG = $(FG++)
GCCFLAG = $(FGCC)
GGOFLAG = $(FGGO)

all: $(LIB)
$(LIB): $(OBJECTS)
	ar cr bin/lib$(LIB).a $(OBJECTS)

$(OBJECTD)%.o: %.cpp
	$(G++) -c -static -ffunction-sections -fdata-sections -Wl,-dead_strip,-gc-sections $(G++FLAG) -I$(INCLUDE) $< -o $@

$(OBJECTD)%.o: %.c
	$(GCC) -c -static -ffunction-sections -fdata-sections -Wl,-dead_strip,-gc-sections $(GCCFLAG) -I$(INCLUDE) $< -o $@

$(OBJECTD)%.o: %.s
	$(GCC) -c $(GCCFLAG) -I$(INCLUDE) $< -o $@

$(OHEADERD)%.h.gch: %.h
	$(G++) -c $(G++FLAG) -I$(INCLUDE) -I/usr/lib/gtest/include $< -o $@

$(OBJECTS): objectmk

objectmk:
	mkdir -p bin
	for file in $(OBJECTS) ; do if [ ! -e $$file ]; then mkdir -p $$file && rm -rf $$file; fi done

debug:
	mkdir -p /usr/lib/pen
	cp -ru $(INCLUDE)/* /usr/lib/pen
	cp -f bin/lib$(LIB).a $(LIBSYS)/
	ldconfig

install:
	mkdir -p /usr/lib/pen
	cp -ru $(INCLUDE)/* /usr/lib/pen
	cp -f bin/lib$(LIB).a $(LIBSYS)/

$(OBJECTT): testmk
testmk:
	mkdir -p bin
	for file in $(OBJECTT) ; do if [ ! -e $$file ]; then mkdir -p $$file && rm -rf $$file; fi done

$(TESTD)/%.o: %.cpp
	$(G++) -c $(TESTF) -I$(INCLUDE) $< -o $@

test: $(TEST)
$(TEST): $(OBJECTT)
	$(G++) $(TESTF) $(OBJECTT) -o bin/$(TEST) -lpen -lpthread -lgtest -lgtest_main
	./bin/$(TEST)

clean:
	rm -rf $(OBJECTD)
	rm -rf $(LIBSYS)/$(LIB)
	rm -rf $(LIBSYS)/lib$(LIB).so

remove:
	rm -rf $(EXECUTE)

.PHONY: all clean debug test
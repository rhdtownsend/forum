# File     : Makefile
# Purpose  : makefile for build subdir

# Default rule in case make is invoked in current dir

all:
	make -C ..

# Targets

LIB_TARGETS = libforum

INC_FILES = forum_m.mod forum.inc

ifeq ($(TESTS),yes)
  BIN_TARGETS += test_order test_arg_parser test_hdf5io
endif

# Source file lists & related variables
#
# xxx_SRCS = source files required to compile xxx
# xxx_USES = source files providing modules USE'd by xxx
# xxx_LIBS = library files required to link xxx

test_order_SRCS = test_order.fypp test_order_m.fypp
test_order_USES = $(libforum_SRCS)
test_order_LIBS = libforum

test_arg_parser_SRCS = test_arg_parser.fypp
test_arg_parser_USES = $(libforum_SRCS)
test_arg_parser_LIBS = libforum

test_hdf5io_SRCS = test_hdf5io.fypp
test_hdf5io_USES = $(libforum_SRCS)
test_hdf5io_LIBS = libforum

libforum_SRCS = arg_parser_m.fypp cinter_m.fypp const_m.fypp forum_m.fypp \
   hdf5io_m.fypp kinds_m.fypp memory_m.fypp order_m.fypp string_m.fypp \
   system_m.fypp version_m.fypp

# Build flags

PKGS = hdf5_fortran

FFLAGS := `pkgconf --cflags $(PKGS)`
LDFLAGS := `pkgconf --libs $(PKGS)`

# Include standard rules

include Make.inc

# Target for linting

linter :
	fortitude check --file-extensions=f90

.PHONY: all linter

# Source-file specific flags

hdf5io_m.f90: FFLAGS += -Wno-c-binding-type

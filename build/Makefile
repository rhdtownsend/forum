# File     : Makefile
# Purpose  : makefile for build subdir

# Targets

LIB_TARGETS = libforum

INC_FILES = forum_m.mod forum.inc

ifeq ($(TESTS),yes)
  BIN_TARGETS += test_order
endif

# Source file lists & related variables
#
# xxx_SRCS = source files required to compile xxx
# xxx_USES = source files providing modules USE'd by xxx
# xxx_LIBS = library files required to link xxx

test_order_SRCS = test_order.fypp test_order_m.fypp
test_order_USES = $(libforum_SRCS)
test_order_LIBS = libforum

libforum_SRCS = arg_parser_m.fypp cinter_m.fypp const_m.fypp forum_m.fypp \
   hdf5io_m.fypp kinds_m.fypp memory_m.fypp order_m.fypp string_m.fypp \
   system_m.fypp version_m.fypp

# Build flags

LDFLAGS = `lapack_link` `hdf5_link` `lapack95_link`

# Include standard rules

include Make.inc

# Target for linting

linter :
	fortitude check \
            --ignore M011 \
            --ignore S001 \
            --ignore E001 \
            --ignore T042 \
            --file-extensions=f90

.PHONY: linter

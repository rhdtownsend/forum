# File     : Makefile
# Purpose  : makefile for build subdir

# Enable debugging (with a performance penalty)
DEBUG ?= no

# Enable OpenMP parallelization
OMP ?= yes

# Enable FPE checks
FPE ?= yes

############ DO NOT EDIT BELOW THIS LINE ############
### (unless you think you know what you're doing) ###
#####################################################

# Targets

BIN_TARGETS = test_order
LIB_TARGETS = libforum

INC_FILES = forum_m.mod forum.inc

# Source file lists & related variables
#
# xxx_SRCS = source files required to compile xxx
# xxx_USES = source files providing modules USE'd by xxx
# xxx_LIBS = library files required to link xxx

test_order_SRCS = test_order.fypp test_order_m.fypp
test_order_USES = $(libforum_SRCS)
test_order_LIBS = libforum

libforum_SRCS = cinter_m.fypp const_m.fypp forum_m.fypp hdf5io_m.fypp \
   kinds_m.fypp memory_m.fypp order_m.fypp string_m.fypp system_m.fypp

# Directories

SRC_DIRS = ../src/lib ../src/test ../src/include

# Additional rules

include Make.inc

# File     : Makefile
# Purpose  : makefile for build subdir

# Default settings

# Build test programs
TESTS ?= yes

# Enable debugging (with a performance penalty)
DEBUG ?= no

# Enable OpenMP parallelization
OMP ?= yes

# Enable FPE checks
FPE ?= yes

# Targets

ifeq (${TESTS},yes)
  EXEC_TARGETS := ${EXEC_TARGETS} test_order
endif

# Object lists & related variables
#
# libxxx_OBJS = object files required to compile libxxx
# lbbxxx_DEPS = dependency that must be added to .libxxx.d file  
#
# prog_OBJS = object files required to compile prog
# prog_LIBS = library files required to link prog
# prog_DEPS = dependencies that must be added to .prog.d file

test_order_OBJS = test_order.o test_order_m.o kinds_m.o order_m.o
test_order_LIBS = 
test_order_DEPS = 

# Search subdirs

SUBDIRS = ../src:../test

# Include other makefiles

include Make.inc

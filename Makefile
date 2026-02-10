# File     : Makefile
# Purpose  : top-level makefile

# Build test programs
TESTS ?= no

# Enable debugging (with a performance penalty)
DEBUG ?= no

# Build & link against shared libraries
SHARED ?= yes

# Enable OpenMP parallelization
OMP ?= yes

# Enable FPE checks
FPE ?= yes

# Enable correctly rounded math functions
CRMATH ?= yes

# Enable portable math (for bit-for-bit reproducibility; setting to
# yes may incur a small performance hit)
PORTABLE ?= yes

# Re-export symbols from top-level modules (for compliers, like Intel
# Fortran, that otherwise would need to access lower-level modules)
RE_EXPORT_MOD_SYMS ?= no

############ DO NOT EDIT BELOW THIS LINE ############
### (unless you think you know what you're doing) ###
#####################################################

# Export options

export TESTS
export DEBUG
export SHARED
export OMP
export FPE
export CRMATH
export PORTABLE
export RE_EXPORT_MOD_SYMS

# General make settings

SH = /bin/bash
MAKEFLAGS += --no-print-directory

# Paths

export BIN_DIR ?= $(CURDIR)/bin
export LIB_DIR ?= $(CURDIR)/lib
export INC_DIR ?= $(CURDIR)/include

SRC_DIR = $(CURDIR)/src
export SRC_DIRS = $(addprefix $(SRC_DIR)/,lib test include)

# Rules

install : build | $(BIN_DIR) $(LIB_DIR) $(INC_DIR)
	@$(MAKE) -C build $@

build :
	@$(MAKE) -C build $@

clean :
	@$(MAKE) -C build clean
	@rm -rf $(BIN_DIR) $(LIB_DIR) $(INC_DIR)

.PHONY: install build clean

$(BIN_DIR) $(LIB_DIR) $(INC_DIR) :
	@mkdir -p $@

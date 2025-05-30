# File     : Makefile
# Purpose  : top-level makefile

# Build test programs
TESTS ?= yes

# Enable debugging (with a performance penalty)
DEBUG ?= no

# Build & link against shared libraries
SHARED ?= yes

# Enable OpenMP parallelization
OMP ?= yes

# Enable FPE checks
FPE ?= yes

# Re-export symbols from top-level modules (for compliers, like Intel
# Fortran, that otherwise would need to access lower-level modules)
RE_EXPORT_MOD_SYMS ?= no

############ DO NOT EDIT BELOW THIS LINE ############
### (unless you think you know what you're doing) ###
#####################################################

# General make settings

export

SH = /bin/bash
MAKEFLAGS += --no-print-directory

# Paths

BIN_DIR ?= $(CURDIR)/bin
LIB_DIR ?= $(CURDIR)/lib
INC_DIR ?= $(CURDIR)/include

SRC_DIR = $(CURDIR)/src

SRC_DIRS = $(addprefix $(SRC_DIR)/,lib test include)

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

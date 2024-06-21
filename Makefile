# File     : Makefile
# Purpose  : top-level makefile

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

SRC_DIR = $(CURDIR)/src
SRC_DIRS = $(addprefix $(SRC_DIR)/,lib test include)

BIN_DIR ?= $(CURDIR)/bin
LIB_DIR ?= $(CURDIR)/lib
INC_DIR ?= $(CURDIR)/include

# Rules

all :
	@$(MAKE) -C build

install : all | $(BIN_DIR) $(LIB_DIR) $(INC_DIR)
	@$(MAKE) -C build install

clean :
	@$(MAKE) -C build clean
	@rm -rf $(BIN_DIR) $(LIB_DIR) $(INC_DIR)

.PHONY: all install clean

$(BIN_DIR) $(LIB_DIR) $(INC_DIR) :
	@mkdir -p $@

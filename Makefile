# File     : Makefile
# Purpose  : top-level makefile

# Variables

export BIN_DIR = ${CURDIR}/bin
export LIB_DIR = ${CURDIR}/lib
export INC_DIR = ${CURDIR}/include

# Rules

all : | $(BIN_DIR) $(LIB_DIR) $(INC_DIR)
	@${MAKE} --no-print-directory -C build
	@${MAKE} --no-print-directory -C build install

test :
	@${MAKE} --no-print-directory -C test $@

clean almostclean :
	@${MAKE} -w -C build $@
	rm -f ${BIN_DIR}/* ${LIB_DIR}/* ${INC_DIR}/*

.PHONY: all test clean almostclean

${BIN_DIR} ${LIB_DIR} ${INC_DIR} :
	@mkdir -p $@

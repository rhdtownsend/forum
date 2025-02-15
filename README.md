# Overview

ForUM (Fortran Utility Modules) is a small set of modules, bundled into a library, for various common utility tasks in modern Fortran.

# Contents

The main ForUM module is defined in the source file src/lib/forum_m.fypp. This pulls in the following subsidiary modules, 
also defined in the src/lib subdirectory:

* cinter_m.fypp -- C interoperability
* const_m.fypp -- mathematical and physical constants
* hdf5io_m.fypp -- high-level HDF5 input/output
* forum_m.fypp -- wrapper that provides single-use access to all other modules
* kinds_m.fypp -- numerical kind definitions
* memory_m.fypp -- memory reallocation
* order_m.fypp -- sorting and indexing
* string_m.fypp -- string manipulation
* system_m.fypp -- accessing command-line arguments and environment variables
* version_m.fypp -- defines the version number of ForUM

# Building ForUM

To build ForUM, you need to install the [MESA SDK](http://user.astro.wisc.edu/~townsend/static.php?ref=mesasdk). Then, run the following commands in the top-level directory:

    make

This will place libraries in the lib/ subdirectory, and module/include files in the include/ subdirectory.

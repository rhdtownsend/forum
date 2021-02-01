#! Include : common
#! Purpose : common macros
#!
#! Copyright 2021 Rich Townsend
#!
#! This file is part of the ForUM (Fortran Utility Modules)
#! package. ForUM is free software: you can redistribute it and/or
#! modify it under the terms of the GNU General Public License as
#! published by the Free Software Foundation, version 3.
#!
#! ForUM is distributed in the hope that it will be useful, but WITHOUT
#! ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
#! or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
#! License for more details.
#!
#! You should have received a copy of the GNU General Public License
#! along with this program.  If not, see <http://www.gnu.org/licenses/>.

#!!! Type and suffix definitions

#:set INT_KINDS = ['i4', 'i8']
#:set INT_TYPES = [f'integer({kind})' for kind in INT_KINDS]
#:set INT_SUFFIXES = INT_KINDS

#:set REAL_KINDS = ['r4', 'r8']
#:set REAL_TYPES = [f'real({kind})' for kind in REAL_KINDS]
#:set REAL_SUFFIXES = REAL_KINDS

#:set COMPLEX_KINDS = REAL_KINDS
#:set COMPLEX_TYPES = [f'complex({kind})' for kind in REAL_KINDS]
#:set COMPLEX_SUFFIXES = [kind.replace('r', 'c') for kind in REAL_KINDS]

#:set CHAR_TYPES = ['character(*)']
#:set CHAR_SUFFIXES = ['s']

#:set LOGICAL_TYPES = ['logical']
#:set LOGICAL_SUFFIXES = ['l']

#:set NUM_TYPES = INT_TYPES + REAL_TYPES + COMPLEX_TYPES
#:set NUM_SUFFIXES = INT_SUFFIXES + REAL_SUFFIXES + COMPLEX_SUFFIXES

#:set MATH_TYPES = NUM_TYPES + LOGICAL_TYPES
#:set MATH_SUFFIXES = NUM_SUFFIXES + LOGICAL_SUFFIXES

#:set ORDERED_TYPES = INT_TYPES + REAL_TYPES + CHAR_TYPES
#:set ORDERED_SUFFIXES = INT_SUFFIXES + REAL_SUFFIXES + CHAR_SUFFIXES

#:set ALL_TYPES = MATH_TYPES + CHAR_TYPES
#:set ALL_SUFFIXES = MATH_SUFFIXES + CHAR_SUFFIXES

#:set RANK_MAX = 7

#!!! Macro definitions

#!!
#! Abort execution
#!!

#:def ABORT(message=None)
   write(UNIT=ERROR_UNIT, FMT=*) 'ABORT at line ${_LINE_}$ of ${_FILE_}$'
   #:if message
      write(UNIT=ERROR_UNIT, FMT=*) '${message}$'
   #:endif
   error stop
#:enddef

#!!
#! Assert that cond is satisfied
#!!

#:def ASSERT(cond, message=None)
   if (.NOT. (${cond}$)) then
      $:ABORT(message)
  end if
#:enddef

#!!
#! Same as ASSERT, but only if DEBUG is set
#!!

#:def ASSERT_DEBUG(cond, message)
   #:if defined('DEBUG')
      $:ASSERT(cond, message)
   #:endif
#:enddef

#!!
#! Create a deferred shape array specification list
#!!

#:def SPEC_LIST(rank)
   #:if rank > 0
      $:'(' + ','.join(':'*rank) + ')'
   #:endif
#:enddef

#!!
#! Create an index list, with indices v
#!!

#:def INDEX_LIST(rank, v)
   #:if rank > 0
      #:set a = []
      #:for i in range(1, rank+1)
         #:set a = a + [f'{v}({i})']
      #:endfor
      $:'(' + ','.join(a) + ')'
   #:endif
#:enddef

#!!
#! Create a shape list, with lower bound l and upper bound u
#!!

#:def SHAPE_LIST(rank, l, u)
   #:if rank > 0
      #:set a = []   
      #:for i in range(1, rank+1)
         #:set b = []
         #:for v in (l, u)
            #:set b = b + [f'{v}({i})']
         #:endfor
         #:set a = a + [':'.join(b)]
      #:endfor
      $:'(' + ','.join(a) + ')'
   #:endif
#:enddef

#!!
#! Create a slice list, with lower bound l, upper bound u and stride s
#!!

#:def SLICE_LIST(rank, l=None, u=None, s=None)
   #:if rank > 0
      #:set a = []   
      #:for i in range(1, rank+1)
         #:set b = []
         #:for v in (l, u)
            #:if v
               #:set b = b + [f'{v}({i})']
            #:else
               #:set b = b + ['']
            #:endif
         #:endfor
	 #:if s
	   #:set b = b + [f'{s}({i})']
	 #:endif
         #:set a = a + [':'.join(b)]
      #:endfor
      $:'(' + ','.join(a) + ')'
   #:endif
#:enddef

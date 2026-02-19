#! Include : forum
#! Purpose : common macros used throughout ForUM
#!
#! Copyright 2021-2026 Rich Townsend
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

#:set INT_KINDS = ['IS', 'ID']
#:set INT_TYPES = [f'integer({kind})' for kind in INT_KINDS]
#:set INT_SUFFIXES = ['is', 'id']

#:set REAL_KINDS = ['RS', 'RD']
#:set REAL_TYPES = [f'real({kind})' for kind in REAL_KINDS]
#:set REAL_SUFFIXES = ['rs', 'rd']

#:set COMPLEX_KINDS = REAL_KINDS
#:set COMPLEX_TYPES = [f'complex({kind})' for kind in REAL_KINDS]
#:set COMPLEX_SUFFIXES = [kind.replace('r', 'c') for kind in REAL_SUFFIXES]

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
#! Stop execution
#!!

#:def STOP(message=None)
   #:if message
      write(OUTPUT_UNIT, FMT=*) ${message}$
   #:endif
   stop
#:enddef

#!!
#! Abort execution
#!!

#:def ABORT(message=None)
   write(UNIT=ERROR_UNIT, FMT=*) 'ABORT at line ${_LINE_}$ of ${_FILE_}$'
   #:if message
      write(UNIT=ERROR_UNIT, FMT=*) ${message}$
   #:endif
   error stop
#:enddef

#!!
#! Assert that cond is satisfied
#!!

#:def ASSERT(cond, message=None)
   if (.NOT. (${cond}$)) then
      #:set cond_str = cond.replace("'", "''")
      #:if message
         @:ABORT('assertion ${cond_str}$ failed with message "'//${message}$//'"')
      #:else
         @:ABORT('assertion ${cond_str}$ failed')
      #:endif
   end if
#:enddef

#!!
#! Same as ASSERT, but only if DEBUG is set
#!!

#:def ASSERT_DEBUG(cond, message=None)
   #:if defined('DEBUG')
      @:ASSERT(${cond}$, ${message}$)
   #:endif
#:enddef

#!!
#! Used for bounds checking
#!!

#:def CHECK_BOUNDS(x, y)
   @:ASSERT_DEBUG(${x}$ == ${y}$, 'bounds mismatch')
#:enddef

#!!
#! Create a deferred shape array specification list
#!!

#:def ARRAY_SPEC(rank, str=':')
   #:if rank > 0
      $:'(' + ','.join([str.format(i) for i in range(1, rank+1)]) + ')'
   #:endif
#:enddef

#!!
#! Reallocate an array
#!!

#:def REALLOCATE(type, suffix, rank)

   #:if type == 'character(*)'
     #:set type_new = 'character(LEN(array))'
   #:else
     #:set type_new = type
   #:endif

   subroutine reallocate_${suffix}$_${rank}$_(array, shape, stat)

      ${type}$, allocatable, intent(inout) :: array${ARRAY_SPEC(rank)}$
      integer, intent(in)                  :: shape(:)
      integer, intent(out), optional       :: stat

      ${type_new}$, allocatable :: array_new${ARRAY_SPEC(rank)}$
      integer, allocatable      :: i_a(:)
      integer, allocatable      :: i_b(:)
      integer, allocatable      :: i_c(:)

      @:ASSERT_DEBUG(SIZE(shape) == ${rank}$, 'rank mismatch')

      ! Allocate the new array

      i_a = LBOUND(array)
      i_b = i_a + shape - 1

      if (PRESENT(stat)) then
         allocate(array_new${ARRAY_SPEC(rank, 'i_a({0:d}):i_b({0:d})')}$, STAT=stat)
         if (stat /= 0) return
      else
         allocate(array_new${ARRAY_SPEC(rank, 'i_a({0:d}):i_b({0:d})')}$)
      endif

      ! Copy the data from old to new

      i_c = MIN(i_b, UBOUND(array))

      array_new${ARRAY_SPEC(rank, 'i_a({0:d}):i_c({0:d})')}$ = array${ARRAY_SPEC(rank, 'i_a({0:d}):i_c({0:d})')}$

      ! Move the allocation

      call MOVE_ALLOC(array_new, array)

      ! Finish

      return

   end subroutine reallocate_${suffix}$_${rank}$_

#:enddef

#!!
#! Reallocate an array (without the stat argument)
#!!

#:def REALLOCATE_NOSTAT(type, suffix, rank)

   #:if type == 'character(*)'
     #:set type_new = 'character(LEN(array))'
   #:else
     #:set type_new = type
   #:endif

   subroutine reallocate_${suffix}$_${rank}$_(array, shape)

      ${type}$, allocatable, intent(inout) :: array${ARRAY_SPEC(rank)}$
      integer, intent(in)                  :: shape(:)

      ${type_new}$, allocatable :: array_new${ARRAY_SPEC(rank)}$
      integer, allocatable      :: i_a(:)
      integer, allocatable      :: i_b(:)
      integer, allocatable      :: i_c(:)

      @:ASSERT_DEBUG(SIZE(shape) == ${rank}$, 'rank mismatch')

      ! Allocate the new array

      i_a = LBOUND(array)
      i_b = i_a + shape - 1

      allocate(array_new${ARRAY_SPEC(rank, 'i_a({0:d}):i_b({0:d})')}$)

      ! Copy the data from old to new

      i_c = MIN(i_b, UBOUND(array))

      array_new${ARRAY_SPEC(rank, 'i_a({0:d}):i_c({0:d})')}$ = array${ARRAY_SPEC(rank, 'i_a({0:d}):i_c({0:d})')}$

      ! Move the allocation

      call MOVE_ALLOC(array_new, array)

      ! Finish

      return

   end subroutine reallocate_${suffix}$_${rank}$_

#:enddef

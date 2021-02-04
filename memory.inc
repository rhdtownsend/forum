#! Include : memory
#! Purpose : memory management macros
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

#:include 'forum.inc'

#!!
#! Reallocate an array
#!!

#:def REALLOCATE (type, suffix, rank)

   #:if type == 'character(*)'
     #:set type_new = 'character(LEN(array))'
   #:else
     #:set type_new = type
   #:endif

   subroutine reallocate_${suffix}$_${rank}$_(array, shape, stat)

      ${type}$, allocatable, intent(inout) :: array${SPEC_LIST(rank)}$
      integer, intent(in)                  :: shape(:)
      integer, intent(out), optional       :: stat
      
      ${type_new}$, allocatable :: array_new${SPEC_LIST(rank)}$
      integer, allocatable      :: i_a(:)
      integer, allocatable      :: i_b(:)
      integer, allocatable      :: i_c(:)

      @:ASSERT_DEBUG(SIZE(shape) == ${rank}$,Rank mismatch)

      ! Allocate the new array

      i_a = LBOUND(array)
      i_b = i_a + shape - 1

      if (PRESENT(stat)) then
         allocate(array_new${SHAPE_LIST(rank, 'i_a', 'i_b')}$, STAT=stat)
         if (stat /= 0) return
      else
         allocate(array_new${SHAPE_LIST(rank, 'i_a', 'i_b')}$)
      endif

      ! Copy the data from old to new

      i_c = MIN(i_b, UBOUND(array))

      array_new${SLICE_LIST(rank, 'i_a', 'i_c')}$ = array${SLICE_LIST(rank, 'i_a', 'i_c')}$

      ! Move the allocation

      call MOVE_ALLOC(array_new, array)

      ! Finish

      return

   end subroutine reallocate_${suffix}$_${rank}$_

#:enddef

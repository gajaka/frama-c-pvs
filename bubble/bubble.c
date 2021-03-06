#include "swap3.h"
/*@
   predicate bubble_sorted{Here}(int* a, integer start_i, integer end_i) =
      \forall integer k1;
	   start_i <= k1 && k1 < end_i ==> a[k1] <= a[k1 + 1];
*/

/*@ 
   inductive Permut_Is_Equiv{L1,L2}(int* a, integer index_from, integer index_to) 
      { 
	case Permut_Refl_Is_Equiv{L}:  
	   \forall int* a, integer index_from, index_to;
		Permut_Is_Equiv{L,L}(a, index_from, index_to);

	case Permut_Sym_Is_Equiv{L1,L2}:  
	   \forall int* a, integer index_from, index_to;  
		Permut_Is_Equiv{L1,L2}(a, index_from, index_to) ==> 
		Permut_Is_Equiv{L2,L1}(a, index_from, index_to); 

	case Permut_Trans_Is_Equiv{L1,L2,L3}:  
	   \forall int* a, integer index_from, index_to;  
		Permut_Is_Equiv{L1,L2}(a, index_from, index_to) && 
		Permut_Is_Equiv{L2,L3}(a, index_from, index_to) ==>  
		Permut_Is_Equiv{L1,L3}(a, index_from, index_to);

        case Bubble_Sorted_Implies_Equiv{L1,L2}:  
	   \forall int* a, integer index_from, index_to, i, j;  
		index_from <= i <= index_to && index_from <= j <= index_to &&
		  bubble_sorted{L2}(a, i, j) ==> Permut_Is_Equiv{L1,L2}(a, index_from, index_to);

        case Swapped_Implies_Equiv{L1,L2}:  
	   \forall int* a, integer index_from, index_to, i, j;  
		index_from <= i <= index_to && index_from <= j <= index_to &&
		  swapped{L1,L2}(a, i, j) ==> Permut_Is_Equiv{L1,L2}(a, index_from, index_to);       
      } 
  */

/*@ 
   requires 0 <= n;
   requires \valid(a + (0 .. n-1));
   assigns  a[0.. n-1];
   behavior bubble_sorted: 
      ensures bubble_sorted(a, 0, n-1);
   behavior permutation_is_equivalence: 
      ensures Permut_Is_Equiv{Old,Here}(a, 0, n-1);   
*/
void bubble(int *a, int n)
   {
       /* Bubble sort version that decreases the upper bound index.*/
      
      int i,k;

       k = n;
       /*@
         loop invariant k >= 0 && k <= n;
         loop invariant bubble_sorted(a, k , n - 1);
         loop invariant (k == n) || (\forall integer i1; (i1 > k) && (i1 < n ) ==> (a[k] <= a[i1]));
         loop invariant (\forall integer i2, i1; (i2 >= 0) && (i2 < k) && (i1 >= k) && (i1 < n ) ==> (a[i1] >= a[i2]));
         for permutation_is_equivalence:
			loop invariant Permut_Is_Equiv{Pre,Here}(a, 0, n-1);
         loop variant k - 1;
       */
       
       while ( k > 0)
       {
          i = 0;
          
          /*@
            loop invariant (i >= 0) && (i < k) && (i <= n);
            loop invariant (\forall integer j; (j >= 0) && (j < i) ==> a[j] <= a[i]);        
            loop invariant bubble_sorted(a, k , n - 1);
            loop invariant (\forall integer i1, i2; (i2 >= 0) && (i2 < k) && (i1 >= k) && (i1 <= n -1) ==> (a[i1] >= a[i2]));
            for permutation_is_equivalence:
				loop invariant Permut_Is_Equiv{Pre,Here}(a, 0, n - 1);
            loop variant k - i - 1;
          */        
          while (i <  k - 1)
          {  
              if (*(a + i) > *(a + i + 1)) 
               {
                	
                 //@ assert precondition_swap3_1: n >= 0; 
                 //@ assert precondition_swap3_2: i >= 0 && i <= n - 1; 
                 //@ assert precondition_swap3_3:( i + 1 >= 0 && i + 1 <= n - 1); 
                 //@ assert precondition_swap3_4: \valid (a +(0.. n-1));
                 
                 swap3(a, n, i, i + 1);

                 //@ for bubble_sorted: assert bubble_sorted(a, i, i+1);
                 //@ for permutation_is_equivalence: assert Permut_Is_Equiv{Pre,Here}(a, i, i + 1);           

               }

              i= i + 1;
          }

          //@ for bubble_sorted: assert bubble_sorted(a, i, k-1);
          //@ for permutation_is_equivalence: assert Permut_Is_Equiv{Pre,Here}(a, i, k - 1);

         k= k - 1;

         //@ for bubble_sorted: assert bubble_sorted(a, i, k);
         //@ for permutation_is_equivalence: assert Permut_Is_Equiv{Pre,Here}(a, i, k);

      }

   }

Project name: r
Authot: QIU Yuan
Email: yqiuac@connect.ust.hk
Date: 29/11/2014
Description:

This is a scheme-based interface supporting some basic matrix operations.
Safe checking has not been fully implemented. Please type in the correct data.
Only support numbers.

Following is the documentation for the procedures:
================================
(list-sum <alist>)
--Sum the list up, implemented for the convenience of other functions.
--Return type is number.
--Example:
> (list-sum '(1 4 7 3 0 5 -1 9 11))
  39
================================
(matrix <data> <nrow> <ncol>)
--Construct a matrix which has <nrow> rows and <ncol> columns with the <data> as a list of data by row order.
--There is no safe checking, so the data must be exactly of the same number as <nrow> * <ncol>.
--Return type is list.
--Example:(in later examples a is defined here)
> (define a (matrix '(1 4 7 3 0 5 -1 9 11) 3 3))
> a
((  1   4   7) (  3   0   5) ( -1   9  11))
> (matrix '(1 2 3 0 9 5) 3 2)
((  1   2) (  3   0) (  9   5))
================================
(mprint <mat>)
--Print the matrix in the usual form instead of in a single line.
--Return nil.
--Example:
> (mprint a)
(  1   4   7)
(  3   0   5)
( -1   9  11)
================================
(mtranspose <mat>)
--Find the transpose of a matrix.
--Return the transpose matrix.
--Example:
> (mtranspose a)
((  1   3  -1) (  4   0   9) (  7   5  11))
> (mprint (mtranspose a))
(  1   3  -1)
(  4   0   9)
(  7   5  11)
> (define b (mtranspose a))
================================
(mcount-row <mat>)
(mcount-col <mat>)
(mcount-elem <mat>)
--Count the number of rows/columns/elements in a matrix.
--Return type is number.
--Example:
> (mcount-row a)
  3
> (mcount-elem b)
  9
================================
(mref-row <mat> <m>)
(mref-col <mat> <n>)
(mref-elem <mat> <m> <n>)
--Give the refered value of a row/column/element.
--Return type is list for row/col, number for elem.
--On assumption that the top-left element has corrdinate (1,1).
--Example:
> (mref-row a 1)
(  1   4   7)
> (mref-col a 2)
(  4   0   9)
> (mref-elem b 3 3)
 11
================================
(mdrop-row <mat> <m>)
(mdrop-col <mat> <n>)
(mdrop-elem <mat> <m> <n>)
--Drop the given row and/or column.
--Return tyoe is list.
--Example:
> (mprint (mdrop-row a 1))
(  3   0   5)
( -1   9  11)
> (mprint (mdrop-col a 2))
(  1   7)
(  3   5)
( -1  11)
> (mprint (mdrop-elem b 3 3))
(  1   3)
(  4   0)
//////No change to data//////
> (mprint a)
(  1   4   7)
(  3   0   5)
( -1   9  11)
================================
(m= <mat1> <mat2>)
--Check whether two matrix are equal by element.
--Return 1 or 0.
--Example:
> (m= (mtranspose (mtranspose a)) a)
  1
================================
(mnegation <mat1> <mat2>)
--Change every number in the matrix to the negation.
--Return a matrix.
--Example:
> (mprint (mnegation a))
( -1  -4  -7)
( -3   0  -5)
(  1  -9 -11)
================================
(m+ <mat1> <mat2>)
(m- <mat1> <mat2>)
(m* <mat1> <mat2>)
--Do element-wise addition/subtraction/multiplication of two matrices.
--Return a matrix.
--No implementation of operation between matrix and numbers. For this purpose, create a matrix with all entrices the same number.
--Example:
> (mprint a)
(  1   4   7)
(  3   0   5)
( -1   9  11)
> (mprint b)
(  1   3  -1)
(  4   0   9)
(  7   5  11)
> (mprint (m+ a b))
(  2   7   6)
(  7   0  14)
(  6  14  22)
> (mprint (m- a b))
(  0   1   8)
( -1   0  -4)
( -8   4   0)
> (mprint (m* a b))
(  1  12  -7)
( 12   0  45)
( -7  45 121)
================================
(m/ <mat> <num>)
--Divide every member of the matrix with the number.
--Return a matrix.
--No type conversion if the data and divisor are both int but the result is not.
--Example
> (mprint (m/ a 2.0))
(  0.500000   2.000000   3.500000)
(  1.500000   0.000000   2.500000)
( -0.500000   4.500000   5.500000)
> (mprint (m/ a 2))
(  0   2   3)
(  1   0   2)
(  0   4   5)
================================
(mmult <mat1> <mat2>)
--Do matrix multiplication on two matrices.
--Return a m*p matrix if <mat1> is m*n and <mat2> is n*p.
--Example:
> (define c '((1 2) (3 4) (5 6)))
> (define d '((1 2 3) (4 5 6)))
> (mprint c)
(  1   2)
(  3   4)
(  5   6)
> (mprint d)
(  1   2   3)
(  4   5   6)
> (mprint (mmult c d))
(  9  12  15)
( 19  26  33)
( 29  40  51)
================================
(msymmetricp <mat>)
--Judging whether the matrix is symmetric.
--Return 1 or 0.
--Example:
> (msymmetricp (mmult a (mtranspose a)))
  1
================================
(list-to <x>)
--Helping function to generate a list frome 1 to x.
--No safe checking, make sure x is a positive integer.
--Return a list.
--Example:
> (list-to 10)
(  1   2   3   4   5   6   7   8   9  10)
================================
(mminor <mat> <i> <j>)
--Helping function to find the minor's value of the matrix with respect to the i-th row and the j-th column.
--Return type is number.
================================
(mdet <mat>)
--Find the determinant of the matrix.
--The matrix should be a square matrix.
--Return type is number.
--Example:
> (mdet a)
 -8
================================
(madj <mat>)
--Find the adjugate matrix.
--The matrix should be a square matrix.
--Return type is a matrix.
--Example:
> (mprint (madj a))
(-45  19  20)
(-38  18  16)
( 27 -13 -12)
> (mprint (mmult a (madj a)))
( -8   0   0)
(  0  -8   0)
(  0   0  -8)
================================
(minverse <mat>)
--Find the inverse matrix.
--The matrix should be a square matrix.
--Automatic change of type is applied so the inverse is double type.
--Return type is a matrix.
--Example:
> (mprint (minverse a))
(  5.625000  -2.375000  -2.500000)
(  4.750000  -2.250000  -2.000000)
( -3.375000   1.625000   1.500000)
> (define a-in (minverse a))
> (mprint (mmult a a-in))
(  1.000000   0.000000   0.000000)
(  0.000000   1.000000   0.000000)
(  0.000000   0.000000   1.000000)
> (mprint (mmult a-in a))
(  1.000000   0.000000   0.000000)
(  0.000000   1.000000   0.000000)
(  0.000000   0.000000   1.000000)
================================
A general example:
> (m= (m/ (madj a) (+ 0.0 (mdet a))) (minverse a))
  1
================================

Todo(After final probably):
Do more safe checking and throw different error message.
Try to allow giving some unsimplified formulas for symbols input.

================================

This is already extremely useful for some of my math courses compared to using Excel!
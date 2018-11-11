/*
 * CS:APP Data Lab
 *
 * Lam Nguyen - lnguye16@gustavus.edu
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function.
     The max operator count is checked by dlc. Note that '=' is not
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */
/*
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
    // 1010101
    int sample = 0x55;
    sample = sample | sample << 8;
    return sample|sample <<16;
}
/*
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
    int sum = x + y;
    int signX = x>>31;
    int signY = y>>31;
    int signSum = sum>>31;
    //check if x has different sign from sum and y has different sign from sum
    int notDifferent = !(signX^signSum) & !(signY^signSum);
    int notDifferent2 = !!(signX^signY); //x and y has either different or the same sign
    return notDifferent|notDifferent2;
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    int filter = !!x; //filter is 0 if x == 0, 1 if x != 0
    int filterAllOneOrAllZero = ((x<<31)>>31; //set all the bits in filter to either 1 or 0
    return ((y&filterAllOneOrAllZero) | (z&~filterAllOneOrAllZero)); //return either x or y
}
/*
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
    //get the sign of X
    int signOfX = x >> 31;
    // XOR to handle the addition when x is positive
    return (x^signOfX) + (1^!signOfX);
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
    //repeatedly split x in half and compare previous half with after half until x = 0 or 1
    int parity1 = x ^ (x>>16);
    int parity2 = parity1 ^ (parity1>>8);
    int parity3 = parity2 ^ (parity2>>4);
    int parity4 = parity3 ^ (parity3>>2);
    int parity5 = parity4 ^ (parity4>>1);
    // and with 1 to filter x to either all 1 or all 0;
    return parity5 & 1;
}
/*
 * fitsShort - return 1 if x can be represented as a
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
    // -32768 < X < 32767
    int msb = x >> 15;
    //handle both positive and negative numbers
    return !msb|!(~msb);
}
/*
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
    //arithmetic shift then logical shift
    return ((x>>31))<<31;
}
/*
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int oddBits(void) {
    //10101010
    int benchMark = 0xAA;
    benchMark = benchMark | benchMark << 8; //pad 8 zeros while preserving the value
    return benchMark | benchMark << 16;
}
/*
 * isGreater - if x > y  then return 1, else return 0
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
    //return 1 if x is greater than y
    //x is negative, y is positive
    // x - y <= 0 => x +(~y+1) <=0 => x + ~y < 0
    int sum = (x+~y);
    int signX = x>>31;
    int signY = y >> 31;
    //either x<y or x has same sign with y and the x+~y <0, negate the whole condition
    return !((signX & !signY)|(!(signX^signY)&sum>>31));
}
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    //create two masks for lower and upper bound
    int lower = 0x30;
    int upper = 0x39;
    //if x < 39 => 39 - x > 0 or 39 + (~x+1) > 0
    int isXsmallerThan39 = (upper+(~x+1))>>31;
    // if x > 30 => x - 30 > 0 or x + (~30+1) > 0
    int isXgreatherThan30 = (x + (~lower+1))>>31;
    return !(isXgreatherThan30|isXsmallerThan39);
}
/*
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int leastBitPos(int x) {
    return (x&(~x+1));
}
/*
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4
 */
int greatestBitPos(int x) {
    //turn x into the greatest 1 bit and all ones after that
    int mask = 1<<31;
    x |= x>>1;
    x |= x>>2;
    x |= x>>4;
    x |= x>>8;
    x |= x>>16;
    //get the Most significant bit
    return (x&((~x>>1)^mask));
}
/*
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
    unsigned mask = 0x7fffffff;
    unsigned lower = 0x7f800001;
    // get the true value
    unsigned val = uf&mask;
    // check if true value is positive, return argument otherwise return the true value
    if(val >= lower){
        return uf;
    }
    else{
        return val;
    }
}
/*
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
    unsigned signMask = 0x80000000;
    unsigned expMask = 0xFF;
    unsigned mantissaMask = 0x7FFFFF;
    unsigned sign = (uf) & signMask;
    unsigned exp = (uf >> 23) & expMask;
    unsigned mantissa = (uf) & mantissaMask;
    //NaN and infinity case
    if(exp == 0xFF){
        return 0x80000000u;
    }
    //take care of bias
    int expBias = exp - 127;
    //denormalized case
    if(expBias < 0)
        return 0;
    //overflow
    if(expBias > 30)
        return 0x80000000u;
    //OR with a mask to protect the sign bit
    mantissa = mantissa | 0x800000;
    if(expBias > 22)
        mantissa = mantissa << (expBias - 23);
    else
        mantissa = mantissa >> (23 - expBias);
    //if sign == 1, return the two's complement (flip the sign)
    if(sign)
        return ~mantissa+1;
    return mantissa;
}
/*
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
    //separate sign, exponent and fraction
    unsigned signMask = 0x80000000;
    unsigned expMask = 0xFF;
    unsigned mantissaMask = 0x7FFFFF;
    unsigned sign = (uf) & signMask;
    unsigned exp = (uf >> 23) & expMask;
    unsigned mantissa = (uf) & mantissaMask;
    // NaN case or infinity
    if(exp == 0xFF){
        return uf;
    }
    //normalized
    else if(exp > 1){
        exp--;
        //assemble the float representation
        return (sign|exp<<23|mantissa);
    }
    else{
        //denormalized
        if(exp == 1 ||exp == 0){
            //preserve the mantissa value
            mantissa |= 1<<23;
        }
        //if rightmost 2 bits is 11
        if((mantissa & 3) == 3){
            mantissa++;
        }
        mantissa >>= 1;
        return sign|mantissa;
    }
}

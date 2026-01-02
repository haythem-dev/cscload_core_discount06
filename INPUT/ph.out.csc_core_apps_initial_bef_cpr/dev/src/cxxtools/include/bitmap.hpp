/*
 ******************** C/C++ Application Program Services **********************

                 (c) Copyright 1995 by NORDAT NetWork GmbH
                              All rights reserved

BITMAP.H
A generic bit map class.

REVISION HISTORY

22 May 1995 V1.00 REV 00 written by Wolfgang Hoppe.

*/
/*  $History: BITMAP.HPP $ */
/*  */
/* *****************  Version 3  ***************** */
/* User: Ck           Date: 18.07.96   Time: 14:11 */
/* Updated in $/cxxtools/inc */
/* Final release. */
/* *********************************************** */

/*  Do not allow to include the file more than once                           */
#ifndef NBITMAP_INC
#define NBITMAP_INC

#include <stddef.h>

/*@DS --------------------------------------------------------------------------
NAME
    nBitMap - A generic bit map class.

SYNOPSIS
    include "bitmap.hpp"
    nBitMap  bitmap;
    nBitMap *bitmap = new nBitMap;

DESCRIPTION
    Class nBitMap is a bit vector whose length can be changed at run time. To
    address a bit, bits are numbered from 0 to n. Counting grows from left to
    right, similiar to an array.

@DE*/

//  Macro to isolate bit n:
#define mGETBIT(n) (*(((n)>>3) + (map_)) & ( 128 >> (7 & (n))))
class nBitMap
{

public:
/*@DS
PUBLIC CONSTRUCTORS
*/
                nBitMap();
// Default constructor. Does not allocate any memory to hold the bit map.
                nBitMap(size_t n);
// Construct a bit map to hold a number of n bits. The initial value of the
// entire map is FALSE.
                nBitMap(size_t n, unsigned char *src);
// Construct a bit map to hold a number of n bits. The bit map is then
// initialized from the contents of the byte array 'src'.

                nBitMap(const nBitMap& src);
// Copy constructor.

                ~nBitMap();
// Destructor. All allocated memory to hold the bit map is freed.

/*
PUBLIC MEMBER OPERATORS
*/
    nBitMap&    operator=(const nBitMap& src);
//  Assigns the bit map value of 'src' to self and returns a reference to it.

    nBitMap&    operator=(const unsigned char *src);
//  The entire bit map of self is set from the contents of the byte array 'src'.
//  The number of bits copied from 'src' depends on the current size setting of
//  of self. You may use Entries() to query the current bit quantity of self.

    void        operator() (size_t n, bool b)
//  Set bit n on or off, according the value of bool b.
//@DE
                {(b) ? SetBit(n) : ClearBit(n);}
/*@DS

PUBLIC MEMBER FUNCTIONS
*/
    size_t      ByteQ() const
//  Returns the number of bytes currently allocated to hold the bit map.
//@DE
                { return (bitq_+7) >> 3; };
//@DS

    void        Clear();
//  Clear entire bit vector.

    void        ClearBit(size_t n);
//  Clear bit n.

    size_t      Entries() const
//  Returns the number of bits in the bit map.
//@DE
                { return bitq_;}
//@DS

    void        Export(unsigned long  *array, size_t entries, size_t n = sizeof(unsigned long)) const;
    void        Export(unsigned int   *array, size_t entries, size_t n = sizeof(unsigned int)) const;
    void        Export(unsigned short *array, size_t entries, size_t n = sizeof(unsigned short)) const;
//  These overloaded functions copy the bit map contents to an array of one of
//  the unsigned integer types. 'entries' is the number of integers in the
//  array. 'n' is the number of bytes to be copied into the integer type and
//  defaults to the natural size of the integer type.
//  Oddly enough, some SQL data base vendors do not support unsigned integer
//  types (INFORMIX !!) and require the user not to use the most significant
//  bit in an integer type. Thus, when storing bit maps into integer types of
//  such a "data base", you have to omitt this bit or an entire byte.
//  This is where 'n' comes in handy.

    void        Export(unsigned char *array, size_t entries) const;
//  Export bit map to an array of bytes. This is a 1:1 copy of the raw bit map
//  data. If 'entries' is less than the number of bytes in the map, only
// 'entries' bytes are exported. If 'entries' is greater than the number of
//  bytes in the map, the remaining bytes in 'array' are left unchanged.

    void        Export(char *array, size_t entries) const;
//  Export bit map to an array of printable characters. Each bit set will set
//  the corresponding byte to '1', all other bytes are set to 0. If entries is
//  less than the number of bits in the map, only 'entries' characters are set.
//  If 'entries' is greater than the number of bits, the remaining characters
//  in the array are left unchanged.

    const unsigned char* GetBuffer() const
//  Returns a const pointer to the raw data itself. Should be used with care.
//@DE
                 { return map_;}
//@DS

    void        GetData(unsigned char* dest) const;
//  Copies the raw bit data into the byte array 'dest' points at.

    void Import(const unsigned long  *array, size_t entries, size_t n = sizeof(unsigned long));
    void Import(const unsigned int   *array, size_t entries, size_t n = sizeof(unsigned int));
    void Import(const unsigned short *array, size_t entries, size_t n = sizeof(unsigned short));
//  These overloaded functions load a bit map from an array of one of the
//  unsigned integer types. 'entries' is the number of integers in the array.
//  'n' is the number of bytes to be loaded from an integer type and defaults
//  to the natural size of the integer type. The bit map is resized to hold the
//  number of bits resulting from 'entries' * 'n' * bits-per-byte. See Export()
//  functions for a further description of 'n'.

    void        Import(const char *array, size_t entries);
//  Set the bit map from the contents of character array 'src'. Each character
//  in 'src' containing a printable '1' or \x01 will set the corresponding bit,
//  all other values will turn off the corresponding bit. 'entries' should
//  contain the number of bytes to be imported from 'array'. The bit map is
//  resized to hold the corresponding number of bits.

    void        Import(const unsigned char *array, size_t entries);
//  Set the bit map from the contents of the byte array 'src'. Each byte in
// 'src' is assumed to hold a bit pattern to be imported to self. 'entries'
//  should contain the number of bytes to be imported from 'array'. The bit map
//  is resized to hold the resulting bit quantity.

    void        Resize(size_t n);
//  Resizes the bit map to keep a quantity of 'n' bits. The old contents are
//  entirely preserved as long as 'n' is not less than the old number bits in
//  the map. If the map size is shrinked, bits are lost from right to left.
//  Resizing the bit map to 0 will delete its entire contents.

    void        SetBit(size_t n);
//  Set bit n.

    bool        TestBit(size_t n) const
//  Test bit n.
//@DE
                { return mGETBIT(n) != 0;}

private:
    void          MaskOut();
    unsigned char *map_;                  // ptr to bit map
    size_t        bitq_;                  // size of bit map in bits
};

#endif

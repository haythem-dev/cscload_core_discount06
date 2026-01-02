/*FIL
 ******************** C/C++ Application Program Services **********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

Routines to implement the generic bit map.

REVISION HISTORY

10 Jun 1995 V1.00 REV 00 written by Wolfgang Hoppe.

*/

#include "bitmap.hpp"
#include <algorithm>
#include <memory.h>

/*----------------------------------------------------------------------------*/
/*  Hex/Bitwise conversion from Integer types to byte array and vice-versa.   */
/*  Mainly used for bit manipulation routines, but defined globally to allow  */
/*  class-independent usage.                                                  */
/*----------------------------------------------------------------------------*/
#define mSTOREBYTES while (n>0) {bytep[--n] = (unsigned char) number;number >>= 8;}
#define mLOADBYTES(t) for (*number=0;n>0;n--,bytep++) {*number<<=8;*number+=(t)*bytep;}

inline void ToByte(unsigned char *bytep, unsigned long number, size_t n = sizeof(unsigned long))
//  Copy 'n' bytes of 'number' into byte array 'bytep' points at. Copying
//  starts from left to right.
{
    mSTOREBYTES;
}

inline void ToByte(unsigned char *bytep, unsigned short number, size_t n = sizeof(unsigned short))
{
    mSTOREBYTES;
}

inline void ToByte(unsigned char *bytep, unsigned int number, size_t n = sizeof(unsigned int))
{
    mSTOREBYTES;
}

inline void FromByte(unsigned long *number, unsigned char *bytep, size_t n = sizeof(unsigned long))
{
    mLOADBYTES(unsigned long);
}

inline void FromByte(unsigned int *number, unsigned char *bytep, size_t n = sizeof(unsigned int))
{
    mLOADBYTES(unsigned int);
}

inline void FromByte(unsigned short *number, unsigned char *bytep, size_t n = sizeof(unsigned short))
{
    mLOADBYTES(unsigned short);
}

#define mDOIMPORT                              \
    Resize(entries * n * 8);                   \
    unsigned char *bp = map_;                  \
    for (; entries > 0; array++, entries--)    \
    {                                          \
        ToByte(bp, *array, n);                 \
        bp += n;                               \
    }

#define mDOEXPORT                              \
    memset(array, 0, entries*n);               \
    unsigned char *bp = map_;                  \
    size_t bytesTotal = 0, bytesCopy = 0;      \
    for (; entries > 0; array++, entries--)    \
    {                                          \
        if (bytesTotal + n > ByteQ()) {        \
            bytesCopy = ByteQ() - bytesTotal;  \
        }                                      \
        else { bytesCopy = n; }                \
        bytesTotal += bytesCopy;               \
        FromByte(array, bp, bytesCopy);        \
        if (bytesCopy < n) break;              \
        bp += n;                               \
    }

/*----------------------------------------------------------------------------*/
/*  Default constructor.                                                      */
/*----------------------------------------------------------------------------*/
nBitMap :: nBitMap()
    : map_(NULL), bitq_(0)
{
}

/*----------------------------------------------------------------------------*/
/*  Constructor with a size of n bits passed.                                 */
/*----------------------------------------------------------------------------*/
nBitMap :: nBitMap
(
    size_t   n
)
    :map_(NULL), bitq_(n)

{
    if ( bitq_ )
    {
        size_t byteq = ByteQ();          // required byte quantity
        map_ = new unsigned char[byteq];
        memset(map_, 0, byteq);          // set all bits off
    }
}

/*----------------------------------------------------------------------------*/
/*  Construct a bit map and intialize it from the specfied byte array.        */
/*----------------------------------------------------------------------------*/
nBitMap :: nBitMap
(
    size_t        n,
    unsigned char *src
)
    :map_(NULL), bitq_(n)

{
    if ( bitq_ )
    {
        size_t byteq = ByteQ();          // required byte quantity
        map_ = new unsigned char[byteq];
        memcpy(map_, src, byteq);        // copy source bytes
    }
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
nBitMap :: nBitMap
(
    const nBitMap& src
)
    :map_(NULL), bitq_(src.bitq_)

{
    if ( bitq_ )
    {
        size_t byteq = ByteQ();          // required byte quantity
        map_ = new unsigned char[byteq];
        memcpy(map_, src.map_, byteq);   // copy bits
    }
}

/*----------------------------------------------------------------------------*/
/*  Overloaded assignment using operator =.                                   */
/*----------------------------------------------------------------------------*/
nBitMap&
nBitMap :: operator=(const unsigned char *src)
{
    if ( bitq_ )
        memcpy(map_, src, ByteQ());        // copy source bytes
    return *this;
}

nBitMap&
nBitMap :: operator=(const nBitMap& src)
{
    size_t byteq = ByteQ();             // byte quantity of self
    size_t srcbyteq = src.ByteQ();      // byte quantity of src

    if ( byteq != srcbyteq )            // then must allocate new buffer
    {
        if (map_)
            delete [/*ByteQ()*/] map_;
        map_ = new unsigned char[srcbyteq];
    }

    bitq_ = src.bitq_;
    memcpy(map_, src.map_, srcbyteq);   // copy bits
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Resize the bit map to keep a number of 'bitq' bits.                       */
/*----------------------------------------------------------------------------*/
void
nBitMap :: Resize(size_t bitq)
{
    size_t oldbyteq = ByteQ();          // old byte quantity of self
    bitq_           = bitq;
    size_t newbyteq = ByteQ();          // new byte quantity
    unsigned char *map = NULL;          // new bitmap buffer

    if ( !newbyteq )                    // then entire map must be released
    {
        if (map_)                        // ensure a buffer has been allocated
        {
            delete map_;                  // before deleting it
            map_ = NULL;
        }
        return;                          // bit map is empty, now we're done
    }

    if ( oldbyteq != newbyteq )         // then must allocate a new buffer
    {
        map = new unsigned char[newbyteq];
        memset(map, 0, newbyteq);
        if (map_)                        // then an old buffer was there
        {                                // copy its contents into the new one
            memcpy(map, map_, std::min(newbyteq, oldbyteq));
            delete map_;
        }
        map_ = map;
        MaskOut();                       // zero out remaining bits in last byte
    }

}

/*----------------------------------------------------------------------------*/
/*  Mask out none-significant bits in last byte.                              */
/*----------------------------------------------------------------------------*/
void
nBitMap :: MaskOut()
{
    size_t bitq = bitq_;
    if ( bitq &= 7 )                    // then bit quantity not modulo 8
    {
        unsigned char mask = (255 << (8-bitq));
        *(map_ + ByteQ() -1) &= mask;    // mask out none-significant bits
    }
}

/*----------------------------------------------------------------------------*/
/*  Load bit map from an array of printable characters. Each '1' in a byte    */
/*  will set the corresponding bit within the map.                            */
/*----------------------------------------------------------------------------*/
void
nBitMap :: Import(const char *src, size_t entries)
{

    Resize(entries);
    for (size_t i = 0; i < entries; i++)
    {
        (*this) (i, (src[i] == '1' || src[i] == 1));
    }

}

/*----------------------------------------------------------------------------*/
/*  Load bit map from an array of one of the integer types.                   */
/*----------------------------------------------------------------------------*/
void
nBitMap :: Import(const unsigned long *array, size_t entries, size_t n)
{
    mDOIMPORT;
}

void
nBitMap :: Import(const unsigned int *array, size_t entries, size_t n)
{
    mDOIMPORT;
}

void
nBitMap :: Import(const unsigned short *array, size_t entries, size_t n)
{
    mDOIMPORT;
}

/*----------------------------------------------------------------------------*/
/*  Export bit map to an array of one of the integer types.                   */
/*----------------------------------------------------------------------------*/
void
nBitMap :: Export(unsigned long *array, size_t entries, size_t n) const
{
    mDOEXPORT;
}

void
nBitMap :: Export(unsigned int *array, size_t entries, size_t n) const
{
    mDOEXPORT;
}

void
nBitMap :: Export(unsigned short *array, size_t entries, size_t n) const
{
    mDOEXPORT;
}

/*----------------------------------------------------------------------------*/
/*  Export bit map to an array of printable characters. Each bit set will set */
/*  will set the corresponding byte to '1', all other bytes are set to 0.     */
/*----------------------------------------------------------------------------*/
void
nBitMap :: Export(char *dest, size_t entries) const
{

    entries = std::min(bitq_, entries);
    for (size_t i = 0; i < entries; i++)
    {
        dest[i] = (TestBit(i)) ? '1' : '0';
    }
}

/*----------------------------------------------------------------------------*/
/*  Export the raw data.                                                      */
/*----------------------------------------------------------------------------*/
void
nBitMap :: GetData(unsigned char *dest) const
{
    memcpy (dest, map_, ByteQ());
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
nBitMap :: ~nBitMap()
{
    if ( map_ )
        delete [/*ByteQ()*/] map_;
}

void nBitMap::SetBit(size_t n)
{
    size_t bytepos = n >> 3;
    size_t bitpos = 7 & n;
    map_[bytepos] = static_cast<unsigned char>(map_[bytepos] | ( 128 >> bitpos ));
}

void nBitMap::ClearBit(size_t n)
{
    size_t bytepos = n >> 3;
    size_t bitpos = 7 & n;
    map_[bytepos] = static_cast<unsigned char>(map_[bytepos] & ~( 128 >> bitpos ));
}

#include <emmintrin.h> // SSE2
#include <smmintrin.h> // SSE4.1
#include <nmmintrin.h> //SSE4.2
#include <stdio.h>
#include <string.h>

#define MAX_STR 256

size_t strlen_sse42(const char *str)
{
    size_t len = 0;
    while (1)
    {
        // Resets the registers to zero
        __m128i zero = _mm_setzero_si128();
        __m128i chunk16 = _mm_setzero_si128();
        // Load 16 bytes from the string into the SSE register
        chunk16 = _mm_loadu_si128((const __m128i *)str);
        // Compare the loaded bytes with zero (null terminator)
        len += _mm_cmpistri(zero, chunk16, 0x08);
        // If the comparison result is true, it means we found a null terminator
        if (_mm_cmpistrc(zero, chunk16, 0x08))
        {
            return len;
        }
        // Move the pointer to the next 16 bytes
        str += 16;
    }
}

int hamming_dist(char str1[MAX_STR], char str2[MAX_STR])
{
// get the length of the two strings
    size_t len1 = strlen_sse42(str1);
    size_t len2 = strlen_sse42(str2);
    // determine the minimum and maximum lengths of the two strings
    size_t min_length = len1 < len2 ? len1 : len2;
    size_t max_length = len1 > len2 ? len1 : len2;
    //define the number of loops when the loop is 16 bytes
    size_t num_loop = min_length / 16;
    size_t count = 0;
    for (size_t i = 0; i < num_loop; i += 16)
    {
        // Load 16 bytes from each string into SSE registers
        __m128i xmm0 = _mm_setzero_si128();
        __m128i xmm1 = _mm_setzero_si128();
        xmm0 = _mm_loadu_si128((const __m128i *)&str1[i]);
        xmm1 = _mm_loadu_si128((const __m128i *)&str2[i]);
        // Compare the two strings and store the result in a mask
        // The 0x18 flag indicates that we want to compare the strings in a case-insensitive manner
        __m128i mask = _mm_cmpistrm(xmm0, xmm1, 0x18);
        // Count the number of differing bits in the mask
        // The mask is a 16-byte value where each byte represents the result of the comparison for each character
        // The _mm_movemask_epi8 function creates a bitmask from the mask, where each bit represents a comparison result
        // The __builtin_popcount function counts the number of set bits in the bitmask
        size_t bitmask = _mm_movemask_epi8(mask);
        count += __builtin_popcount(bitmask);
    }
    // Handle the remaining characters that are not a multiple of 16
    size_t remaining = min_length % 16;
    for (size_t i = 0; i < remaining; i++)
    {
        if (str1[i] != str2[i])
        {
            count++;
        }
    }
    size_t diff = max_length - min_length;
    return count + diff;
}

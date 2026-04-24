/**
 * string.c
 * Megan Lu
 * COSC050, 26S
 *
 * Description: string utilities to append, copy, and calculate
 * length of strings.
 * Implementation of functions strcat, strcpy, and strlen
 * defined by string.h library without using external functions.
 */

#include <stdio.h>
#include <stdlib.h>

/* ***************************
 * mystrcat
 * Catenate a string.
 *
 * Description:
 * 	This function catenates the string pointed to by src, after the string 
 * 	pointed to by dst (over‐writing its terminating null byte).
 * 	The programmer is responsible for  allocating  a  destination
 * 	buffer large enough, that is, strlen(dst) + strlen(src) + 1.
 *
 * Return value:
 * 	This function returns dst (pointer to the beginning of dst).
 *
 * Notes:
 * 	The strings src and dst may not overlap.
 * 	If  the  destination  buffer is not large enough, the behavior 
 * 	is undefined.
 */
char* mystrcat(char* restrict dst, const char* restrict src)
{
	// Store the start of dst for the return value
	char* start = dst;

	// Loop to the terminating null character of dst
	// starting with the first character of dst
	while (*dst != '\0') {
		dst++; // Move to the next character in dst string
	}
	
	// At the null terminating character of dst
	// Overwrite '\0' of dst with the first character of src
	// Continue adding all characters of src until end of src
	// (null terminating character is reached)
	while (*src != '\0') {
		// Set the value of dst to the character value of src
		*dst = *src;
		// Move to next character in both dst and src
		dst++;
		src++;
	}

	// Add null terminating character to end of the dst string
	*dst = '\0';

	// Return concatenated dst string 
	// (pointer to start of the dst string stored in start)
	return start;
}

/* ***************************
 * mystrcpy
 * Copy a string.
 *
 * Description:
 * 	This function copies the string pointed to by src, into a string at the 
 * 	buffer pointed to by dst. The programmer is responsible for allocating  
 * 	a destination buffer large enough, that is, strlen(src) + 1.
 *
 * Return value:
 *      This function returns dst (pointer to the beginning of dst).
 *
 * Notes:
 *      The strings src and dst may not overlap.
 *      If  the  destination  buffer is not large enough, the behavior 
 *      is undefined.
 */
char* mystrcpy(char* restrict dst, const char* restrict src)
{
	// Store the start of dst for the return value
        char* start = dst;
	
	// Loop through src until all characters added to dst
        // (null terminating character of src reached)
        while (*src != '\0') {
                // Set the value of dst to the character value of src
                *dst = *src;
                // Move to next character in both dst and src
                dst++;
                src++;
        }

        // Add null terminating character to end of the dst string
	*dst = '\0';

     	// Return string copied to dst 
        // (pointer to start of the dst string stored in start)
        return start;
}

/* ***************************
 * mystrlen
 * Calculate the length of a string.
 * 
 * Description:
 * 	This function calculates the length of the string pointed to by s,
 * 	excluding the terminating null byte ('\0').
 *
 * Return value:
 * 	This function returns the number of bytes in the string pointed to by s.
 *
 * Notes:
 * 	The input buffer must contain a terminating null byte.
 */
size_t mystrlen(const char *s)
{
	// Initialize the count (stored as an unsigned integer)
	size_t count = 0;

	// Loop through s until reaching the terminating null byte
	while (*s != '\0') {
		// Move to the next character in s
		s++;
		// Increment the count
		count++;
	}

	// At the null terminating character of s
	// (not included in the count, loop ended)
	// Return the count
	return count;
}

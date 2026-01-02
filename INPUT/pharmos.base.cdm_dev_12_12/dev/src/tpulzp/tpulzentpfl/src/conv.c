#include <stdlib.h>
#include <string.h>

#include "conv.h"

/* from libtpld */
#include <allgemein.h>
#include <struct.h>

void convert_format(char* destination, const char* source, struct AUFB* cobol_field_description, int field_length)
{

	/*check if string is longer than specified field length*/
	if (field_length < cobol_field_description->laenge + cobol_field_description->nachkomma)
	{
		field_length = cobol_field_description->laenge + cobol_field_description->nachkomma + 1; /*plus 1 for decimal delimiter*/
	}
	
	char* conv_helper = malloc( (sizeof(char) * field_length) + 1);
		
	conv_helper[field_length] = '\0';
	strncpy(conv_helper, source, field_length);

	/*Rbueding modifies conv_helper's buffer*/
	/*Note: cobol_field_description will also be written in case of negative value*/
	Rbuendig( conv_helper, cobol_field_description );

	/*copy the leftmost field_length bytes to destination*/
	memcpy( destination, conv_helper, cobol_field_description->laenge );
	free(conv_helper);
}

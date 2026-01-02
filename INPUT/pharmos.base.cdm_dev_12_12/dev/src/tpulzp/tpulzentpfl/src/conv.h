#ifndef GUARD_CONV
#define GUARD_CONV


struct AUFB;

/*Note: cobol_field_description will also be written in case of negative value*/
void convert_format(char* destination, const char* source, struct AUFB* cobol_field_description, int field_length);


#endif

#ifndef __PP_ARTICLEINFOSTRUCTCODE_H_
#define __PP_ARTICLEINFOSTRUCTCODE_H_

/******************************************************************************/
/* d:\prj\aa\UNIX\kscserver\client\articleinfostructcode **************************/
/******************************************************************************/

/* Length/Count-Define of ARTICLEINFOSTRUCT *******************************************/

#define LS_ARTICLEINFOSTRUCTCODE_ARTICLECODE 25 + 1
#define LS_ARTICLEINFOSTRUCTCODE_AVAILABLE 1 + 1

/* Structur with real chartype of ORDERDATA ***********************************/

typedef struct ARTSTRUCTCODE {
         char ARTICLECODE[25];
         char AVAILABLE;
         } stArticleCode;

typedef struct C_ARTSTRUCTINFOCODE {
         stArticleCode ArticlesCode[150];
         } stArticleInfoCode;

typedef struct CARTSTRUCTCODE {
         char ARTICLECODE[25];
         char AVAILABLE;
         } stCArticleCode;


#endif

#ifndef __PP_ARTICLEINFOSTRUCT_H_
#define __PP_ARTICLEINFOSTRUCT_H_

/******************************************************************************/
/* d:\prj\aa\UNIX\kscserver\client\articleinfostruct **************************/
/******************************************************************************/

/* Length/Count-Define of ARTICLEINFOSTRUCT *******************************************/

#define LS_ARTICLEINFOSTRUCT_ARTICLENO 7 + 1
#define LS_ARTICLEINFOSTRUCT_AVAILABLE 1 + 1

/* Structur with real chartype of ORDERDATA ***********************************/

typedef struct ARTSTRUCT {
         long ARTICLENO;
         char AVAILABLE;
         } stArticle;

typedef struct C_ARTSTRUCTINFO {
         stArticle Articles[250];
         } stArticleInfo;

typedef struct CARTSTRUCT {
         char ARTICLENO[7];
         char AVAILABLE;
         } stCArticle;


#endif

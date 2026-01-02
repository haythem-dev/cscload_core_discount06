#ifndef U_BSSG_H_DEFINED
#define U_BSSG_H_DEFINED

#ifdef __cplusplus
extern "C" {
#endif

int  TestBSSichG( char *wgr );

long SetBSSichG( long artikel_nr, char *wgr, char *errmld );

long OpenBSSichG( char *user, char *errmld );

void CloseBSSichG();

#ifdef __cplusplus
}
#endif

#endif /* U_BSSG_H_DEFINED */


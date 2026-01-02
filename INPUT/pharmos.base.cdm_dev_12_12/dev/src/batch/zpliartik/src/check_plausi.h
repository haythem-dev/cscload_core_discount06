/* ---------------------------------------------------------------------- *
 *                            CHECK_PLAUSI.H                                  *
 * ---------------------------------------------------------------------- */

#ifndef CHECK_PLAUSI_INCLUDED
#define CHECK_PLAUSI_INCLUDED


int CheckPruefziffer ( long pzn );
void SetNZwing ( struct CLIART *li, char *errmld);
void SetZwing ( struct CLIART *li, char *errmld );
void CalcKZs ( struct CLIART *li, char *errmld );

#endif

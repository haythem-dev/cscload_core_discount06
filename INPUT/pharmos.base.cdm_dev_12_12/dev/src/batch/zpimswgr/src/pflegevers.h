/* Pflege-Version */
 
#ifndef PFLEFEVERS_H_INCLUDE
#define PFLEGEVERS_H_INCLUDE

/* #define WP_ALTE_VERSION */

#ifdef WP_ALTE_VERSION
#include <wpx_dbas.h>
#include <wpx_prot.h>
#include <wpx_bufd.h>
#else
#include <wpp_dbas.h>
#include <wpp_prot.h>
#endif

#endif  /* PFLEGEVERS_H_INCLUDE */


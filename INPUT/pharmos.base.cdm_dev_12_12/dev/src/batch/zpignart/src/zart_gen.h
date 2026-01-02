
/* ---------------------------------------------------------------------- *
 *                        A R T _ G E N . H                               *
 * ---------------------------------------------------------------------- */

#ifndef ART_GEN_INCLUDED
#define ART_GEN_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

void InitArtveFields ( struct ARTVE *Buf);

void IfaSatzToArtikel( struct ZIFAART* IfaBuf, struct ZARTIKEL* Buf, int IsArtikelVorhanden,
                       int* ToStoreAbdaWg, int* ToStoreSwg1, int* ToStoreSwg2, int* ToStoreWg2);
void IfaSatzToPreis  ( struct ZIFAART *IfaBuf, struct ZARTPREIS *Buf,
                       int IsArtikelVorhanden );
void IfaSatzToArtPriceExt( struct ZIFAART *IfaBuf, struct CARTPRICEEXT *Buf );
void IfaSatzToEan    ( struct ZIFAART *IfaBuf, struct EAN *Buf,
                       int IsArtikelVorhanden );

int HasPreisAValue   ( struct ZIFAART *IfaBuf );
int HasArtPriceExtAValue   ( struct ZIFAART *IfaBuf );
int HasEanAValue     ( struct ZIFAART *IfaBuf );

int IsAnyNoValue     ( struct ZIFAART *IfaBuf );
int IsNoValue		 ( struct ZIFAART *IfaBuf, int pos );

int GetIsIfaLoeschung( struct ZIFAART *IfaBuf );
int GetIsIfaAH( struct ZIFAART *IfaBuf );

int TestEanNr( char *ean );

char Build_VERTRBIND_IFA( struct ZIFAART *IfaBuf );
char Build_KUEHLARTIKEL( struct ZIFAART *IfaBuf, int IsArtikelVorhanden, int *ToStoreSwg1 );
char Build_VERFALL( struct ZIFAART *IfaBuf );
void Build_EINHEIT( char *ArtEinheit, char *PgEinh, char *PgMeng );

#ifdef __cplusplus
}
#endif

#endif /* ART_GEN_INCLUDED */


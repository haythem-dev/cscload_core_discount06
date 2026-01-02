#ifndef __Q_CRYPT_H_
#define __Q_CRYPT_H_

#ifdef __cplusplus
extern "C" 
{
#endif

void pwd_crypt(const char *InOriginal, char *OutVerschluesselt, int Laenge);
void pwd_decrypt(char *OutOriginal, char *InVerschluesselt, int Laenge);

#ifdef __cplusplus
}
#endif

#endif

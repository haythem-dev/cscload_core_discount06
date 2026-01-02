#pragma once

// Minimal stub of x509v3.h just to satisfy Thrift build when using placeholder OpenSSL headers.
// This provides ONLY what TSSLSocket.cpp uses. It does NOT implement real X509 extension parsing.

#ifdef __cplusplus
extern "C" {
#endif

#ifdef X509_NAME
#undef X509_NAME
#endif

struct X509 {};
struct X509_NAME {};
struct X509_NAME_ENTRY {};

#define X509_V_OK 0

// NID for subjectAltName (already defined in ssl.h, guard in case)
#ifndef NID_subject_alt_name
#define NID_subject_alt_name 0
#endif

// Return type in real OpenSSL is void*; caller casts to STACK_OF(GENERAL_NAME)*.
static inline void* X509_get_ext_d2i(struct X509*, int /*nid*/, int* /*crit*/, int* /*idx*/) {
    return 0; // no extensions present
}

X509* SSL_get_peer_certificate(SSL*) { return NULL; }
const char* X509_verify_cert_error_string(int) { return ""; }
void X509_free(X509*) {}

X509_NAME* X509_get_subject_name(X509*) { return NULL; }
int X509_NAME_get_index_by_NID(X509_NAME*, int, int) { return -1; }
X509_NAME_ENTRY* X509_NAME_get_entry(void*, int) { return NULL; }
ASN1_STRING* X509_NAME_ENTRY_get_data(X509_NAME_ENTRY*) { return NULL; }

#ifdef __cplusplus
}
#endif

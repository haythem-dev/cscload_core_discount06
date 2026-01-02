#pragma once

#include <stdint.h> // for uint8_t
#ifdef _WIN32
#include <winsock2.h>
#endif

// If you want to emulate OpenSSL 1.1.0+ (where thread callbacks are ignored),
// uncomment the following line; Thrift will then not call CRYPTO_set_id_callback.
// #define OPENSSL_VERSION_NUMBER 0x10100000L

#ifndef OPENSSL_VERSION_NUMBER
// Emulate a pre-1.1.0 version so Thrift still installs callbacks
#define OPENSSL_VERSION_NUMBER 0x1000100fL
#endif

struct SSL {};
struct SSL_CTX {};
struct ASN1_STRING {};
struct BIO {};
struct GENERAL_NAME {
  struct {
    char* ia5;
  } d;
  int type;
};

// Forward declaration for dynamic locks
struct CRYPTO_dynlock_value;

#define CRYPTO_LOCK 0

// Initialization
void SSL_library_init() {}
void SSL_load_error_strings() {}
void ERR_load_crypto_strings() {}

int CRYPTO_num_locks() { return 1; }

// Thread / locking callbacks (corrected signatures)
void CRYPTO_set_id_callback(unsigned long (*id_function)(void)) {}
void CRYPTO_set_locking_callback(void (*locking_function)(int mode, int n, const char* file, int line)) {}

void CRYPTO_set_dynlock_create_callback(CRYPTO_dynlock_value* (*create_function)(const char* file, int line)) {}
void CRYPTO_set_dynlock_lock_callback(void (*lock_function)(int mode, CRYPTO_dynlock_value* lock,
                                                            const char* file, int line)) {}
void CRYPTO_set_dynlock_destroy_callback(void (*destroy_function)(CRYPTO_dynlock_value* lock,
                                                                  const char* file, int line)) {}

void ENGINE_cleanup() {}
void CONF_modules_unload(int) {}
void EVP_cleanup() {}
void CRYPTO_cleanup_all_ex_data() {}
void ERR_remove_state(int) {}
void ERR_free_strings() {}

// Context / methods
SSL_CTX* SSL_CTX_new(void*) { return NULL; }
void* SSLv23_method() { return NULL; }
void* SSLv3_method() { return NULL; }
void* TLSv1_method() { return NULL; }
void* TLSv1_1_method() { return NULL; }
void* TLSv1_2_method() { return NULL; }

#define SSL_MODE_AUTO_RETRY 0
#define SSL_OP_NO_SSLv2 0
#define SSL_OP_NO_SSLv3 0

void SSL_CTX_set_mode(SSL_CTX*, int) {}
void SSL_CTX_set_options(SSL_CTX*, int) {}
void SSL_CTX_free(SSL_CTX*) {}

SSL* SSL_new(SSL_CTX*) { return NULL; }

int SSL_pending(SSL*) { return 0; }
int SSL_get_shutdown(SSL*) { return 0; }
#define SSL_RECEIVED_SHUTDOWN 0
#define SSL_SENT_SHUTDOWN 0

int SSL_peek(SSL*, uint8_t*, int) { return 0; }
int SSL_get_error(SSL*, int) { return 0; }
int SSL_shutdown(SSL*) { return 0; }
void SSL_free(SSL*) {}

int SSL_read(SSL*, uint8_t*, int) { return 0; }
int SSL_write(SSL*, const uint8_t*, int) { return 0; }

#define SSL_ERROR_SYSCALL 0
#define SSL_ERROR_WANT_READ 1
#define SSL_ERROR_WANT_WRITE 2
#define SSL_ERROR_NONE 4
#define SSL_ERROR_ZERO_RETURN 5

int ERR_peek_error() { return 0; }
void ERR_clear_error() {}

BIO* SSL_get_wbio(SSL*) { return NULL; }
BIO* SSL_get_rbio(SSL*) { return NULL; }
int BIO_get_fd(BIO*, int*) { return 0; }
int BIO_flush(BIO*) { return 0; }

void SSL_set_fd(SSL*, int) {}
int SSL_accept(SSL*) { return 0; }
int SSL_connect(SSL*) { return 0; }

int SSL_get_verify_result(SSL*) { return 0; }

int SSL_get_verify_mode(SSL*) { return 0; }

#define NID_commonName 0

#define STACK_OF(type) struct stack_st_##type
#define NID_subject_alt_name 0

int sk_GENERAL_NAME_num(STACK_OF(GENERAL_NAME)*) { return 0; }
GENERAL_NAME* sk_GENERAL_NAME_value(STACK_OF(GENERAL_NAME)*, int) { return NULL; }
char* ASN1_STRING_data(char*) { return NULL; }
int ASN1_STRING_length(char*) { return 0; }
int ASN1_STRING_to_UTF8(unsigned char**, void*) { return 0; }
void OPENSSL_free(unsigned char*) {}

#define GEN_DNS 0
#define GEN_IPADD 1
#define GENERAL_NAME_free 0
void sk_GENERAL_NAME_pop_free(STACK_OF(GENERAL_NAME)*, int) {}

#define SSL_VERIFY_FAIL_IF_NO_PEER_CERT 0
#define SSL_VERIFY_PEER 0
#define SSL_VERIFY_CLIENT_ONCE 0
#define SSL_VERIFY_NONE 0
void SSL_CTX_set_verify(SSL_CTX*, int, void*) {}

#define SSL_FILETYPE_PEM 0
int SSL_CTX_use_PrivateKey_file(SSL_CTX*, const char*, int) { return 0; }
int SSL_CTX_load_verify_locations(SSL_CTX*, const char*, const char*) { return 0; }
int SSL_CTX_set_cipher_list(SSL_CTX*, const char*) { return 0; }
int SSL_CTX_use_certificate_chain_file(SSL_CTX*, const char*) { return 0; }

void RAND_poll() {}
void SSL_CTX_set_default_passwd_cb(SSL_CTX*, void*) {}
void SSL_CTX_set_default_passwd_cb_userdata(SSL_CTX*, void*) {}

int ERR_get_error() { return 0; }
const char* ERR_reason_error_string(int) { return ""; }
const char* ERR_error_string(int, char*) { return ""; }

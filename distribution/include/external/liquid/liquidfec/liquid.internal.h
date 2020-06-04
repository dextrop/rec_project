#ifndef LIQUID_INTERNAL_H

#define LIQUID_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif

#define LIBFEC_ENABLED

extern const unsigned char liquid_c_ones[256];

// Count the number of ones in an integer, inline insertion
#define liquid_count_ones_uint16(x) (           \
    liquid_c_ones[  (x)      & 0xff ] +         \
    liquid_c_ones[ ((x)>>8)  & 0xff ])

#define liquid_count_ones_uint24(x) (           \
    liquid_c_ones[  (x)      & 0xff ] +         \
    liquid_c_ones[ ((x)>> 8) & 0xff ] +         \
    liquid_c_ones[ ((x)>>16) & 0xff ])

#define liquid_count_ones_uint32(x) (           \
    liquid_c_ones[  (x)      & 0xff ] +         \
    liquid_c_ones[ ((x)>> 8) & 0xff ] +         \
    liquid_c_ones[ ((x)>>16) & 0xff ] +         \
    liquid_c_ones[ ((x)>>24) & 0xff ])


// number of ones in a byte, modulo 2
//  0   0000 0000   :   0
//  1   0000 0001   :   1
//  2   0000 0010   :   1
//  3   0000 0011   :   0
//  4   0000 0100   :   1
//  ...
//  126 0111 1110   :   0
//  127 0111 1111   :   1
//  128 1000 0000   :   1
//  129 1000 0001   :   0
//  ...
//  253 1111 1101   :   1
//  254 1111 1110   :   1
//  255 1111 1111   :   0
extern const unsigned char liquid_c_ones_mod2[256];

// Count the number of ones in an integer modulo 2, inline insertion
#define liquid_count_ones_mod2_uint16(x) ((         \
    liquid_c_ones_mod2[  (x)      & 0xff ] +        \
    liquid_c_ones_mod2[ ((x)>>8)  & 0xff ]) % 2)

#define liquid_count_ones_mod2_uint32(x) ((         \
    liquid_c_ones_mod2[  (x)       & 0xff ] +       \
    liquid_c_ones_mod2[ ((x)>> 8)  & 0xff ] +       \
    liquid_c_ones_mod2[ ((x)>>16)  & 0xff ] +       \
    liquid_c_ones_mod2[ ((x)>>24)  & 0xff ]) % 2)

// compute binary dot-products (inline pre-processor macros)
#define liquid_bdotprod_uint8(x,y)  liquid_c_ones_mod2[(x)&(y)]
#define liquid_bdotprod_uint16(x,y) liquid_count_ones_mod2_uint16((x)&(y))
#define liquid_bdotprod_uint32(x,y) liquid_count_ones_mod2_uint32((x)&(y))

// number of leading zeros in byte
extern unsigned int liquid_c_leading_zeros[256];

// byte reversal and manipulation
extern const unsigned char liquid_reverse_byte_gentab[256];

void liquid_pack_array(unsigned char * _src,
                       unsigned int _n,
                       unsigned int _k,
                       unsigned int _b,
                       unsigned char _sym_in);

// unpack symbols from binary array
//  _src        :   source array [size: _n x 1]
//  _n          :   input source array length
//  _k          :   bit index to write in _src
//  _b          :   number of bits in output symbol
//  _sym_out    :   output symbol
void liquid_unpack_array(unsigned char * _src,
                         unsigned int _n,
                         unsigned int _k,
                         unsigned int _b,
                         unsigned char * _sym_out);

#define LIQUID_SOFTBIT_0        (0)
#define LIQUID_SOFTBIT_1        (255)
#define LIQUID_SOFTBIT_ERASURE  (127)

// available CRC schemes
#define LIQUID_CRC_NUM_SCHEMES  7
typedef enum {
    LIQUID_CRC_UNKNOWN=0,   // unknown/unavailable CRC scheme
    LIQUID_CRC_NONE,        // no error-detection
    LIQUID_CRC_CHECKSUM,    // 8-bit checksum
    LIQUID_CRC_8,           // 8-bit CRC
    LIQUID_CRC_16,          // 16-bit CRC
    LIQUID_CRC_24,          // 24-bit CRC
    LIQUID_CRC_32           // 32-bit CRC
} crc_scheme;

// pretty names for crc schemes
extern const char * crc_scheme_str[LIQUID_CRC_NUM_SCHEMES][2];

// Print compact list of existing and available CRC schemes
void liquid_print_crc_schemes();

// returns crc_scheme based on input string
crc_scheme liquid_getopt_str2crc(const char * _str);

// get length of CRC (bytes)
unsigned int crc_get_length(crc_scheme _scheme);

// generate error-detection key
//  _scheme     :   error-detection scheme
//  _msg        :   input data message, [size: _n x 1]
//  _n          :   input data message size
unsigned int crc_generate_key(crc_scheme      _scheme,
                              unsigned char * _msg,
                              unsigned int    _n);

// generate error-detection key and append to end of message
//  _scheme     :   error-detection scheme (resulting in 'p' bytes)
//  _msg        :   input data message, [size: _n+p x 1]
//  _n          :   input data message size (excluding key at end)
void crc_append_key(crc_scheme      _scheme,
                    unsigned char * _msg,
                    unsigned int    _n);

// validate message using error-detection key
//  _scheme     :   error-detection scheme
//  _msg        :   input data message, [size: _n x 1]
//  _n          :   input data message size
//  _key        :   error-detection key
int crc_validate_message(crc_scheme      _scheme,
                         unsigned char * _msg,
                         unsigned int    _n,
                         unsigned int    _key);

// check message with key appended to end of array
//  _scheme     :   error-detection scheme (resulting in 'p' bytes)
//  _msg        :   input data message, [size: _n+p x 1]
//  _n          :   input data message size (excluding key at end)
int crc_check_key(crc_scheme      _scheme,
                  unsigned char * _msg,
                  unsigned int    _n);

// get size of key (bytes)
unsigned int crc_sizeof_key(crc_scheme _scheme);

// available FEC schemes
#define LIQUID_FEC_NUM_SCHEMES  28
typedef enum {
    LIQUID_FEC_UNKNOWN=0,       // unknown/unsupported scheme
    LIQUID_FEC_NONE,            // no error-correction
    LIQUID_FEC_REP3,            // simple repeat code, r1/3
    LIQUID_FEC_REP5,            // simple repeat code, r1/5
    LIQUID_FEC_HAMMING74,       // Hamming (7,4) block code, r1/2 (really 4/7)
    LIQUID_FEC_HAMMING84,       // Hamming (7,4) with extra parity bit, r1/2
    LIQUID_FEC_HAMMING128,      // Hamming (12,8) block code, r2/3
    
    LIQUID_FEC_GOLAY2412,       // Golay (24,12) block code, r1/2
    LIQUID_FEC_SECDED2216,      // SEC-DED (22,16) block code, r8/11
    LIQUID_FEC_SECDED3932,      // SEC-DED (39,32) block code
    LIQUID_FEC_SECDED7264,      // SEC-DED (72,64) block code, r8/9

    // codecs not defined internally (see http://www.ka9q.net/code/fec/)
    LIQUID_FEC_CONV_V27,        // r1/2, K=7, dfree=10
    LIQUID_FEC_CONV_V29,        // r1/2, K=9, dfree=12
    LIQUID_FEC_CONV_V39,        // r1/3, K=9, dfree=18
    LIQUID_FEC_CONV_V615,       // r1/6, K=15, dfree<=57 (Heller 1968)

    // punctured (perforated) codes
    LIQUID_FEC_CONV_V27P23,     // r2/3, K=7, dfree=6
    LIQUID_FEC_CONV_V27P34,     // r3/4, K=7, dfree=5
    LIQUID_FEC_CONV_V27P45,     // r4/5, K=7, dfree=4
    LIQUID_FEC_CONV_V27P56,     // r5/6, K=7, dfree=4
    LIQUID_FEC_CONV_V27P67,     // r6/7, K=7, dfree=3
    LIQUID_FEC_CONV_V27P78,     // r7/8, K=7, dfree=3

    LIQUID_FEC_CONV_V29P23,     // r2/3, K=9, dfree=7
    LIQUID_FEC_CONV_V29P34,     // r3/4, K=9, dfree=6
    LIQUID_FEC_CONV_V29P45,     // r4/5, K=9, dfree=5
    LIQUID_FEC_CONV_V29P56,     // r5/6, K=9, dfree=5
    LIQUID_FEC_CONV_V29P67,     // r6/7, K=9, dfree=4
    LIQUID_FEC_CONV_V29P78,     // r7/8, K=9, dfree=4

    // Reed-Solomon codes
    LIQUID_FEC_RS_M8            // m=8, n=255, k=223
} fec_scheme;

// pretty names for fec schemes
extern const char * fec_scheme_str[LIQUID_FEC_NUM_SCHEMES][2];

// Print compact list of existing and available FEC schemes
void liquid_print_fec_schemes();

// returns fec_scheme based on input string
fec_scheme liquid_getopt_str2fec(const char * _str);

// fec object (pointer to fec structure)
typedef struct fec_s * fec;

// return the encoded message length using a particular error-
// correction scheme (object-independent method)
//  _scheme     :   forward error-correction scheme
//  _msg_len    :   raw, uncoded message length
unsigned int fec_get_enc_msg_length(fec_scheme _scheme,
                                    unsigned int _msg_len);

// get the theoretical rate of a particular forward error-
// correction scheme (object-independent method)
float fec_get_rate(fec_scheme _scheme);

// create a fec object of a particular scheme
//  _scheme     :   error-correction scheme
//  _opts       :   (ignored)
fec fec_create(fec_scheme _scheme,
               void *_opts);

// recreate fec object
//  _q          :   old fec object
//  _scheme     :   new error-correction scheme
//  _opts       :   (ignored)
fec fec_recreate(fec _q,
                 fec_scheme _scheme,
                 void *_opts);

// destroy fec object
void fec_destroy(fec _q);

// print fec object internals
void fec_print(fec _q);

// encode a block of data using a fec scheme
//  _q              :   fec object
//  _dec_msg_len    :   decoded message length
//  _msg_dec        :   decoded message
//  _msg_enc        :   encoded message
void fec_encode(fec _q,
                unsigned int _dec_msg_len,
                unsigned char * _msg_dec,
                unsigned char * _msg_enc);

// decode a block of data using a fec scheme
//  _q              :   fec object
//  _dec_msg_len    :   decoded message length
//  _msg_enc        :   encoded message
//  _msg_dec        :   decoded message
void fec_decode(fec _q,
                unsigned int _dec_msg_len,
                unsigned char * _msg_enc,
                unsigned char * _msg_dec);

// decode a block of data using a fec scheme (soft decision)
//  _q              :   fec object
//  _dec_msg_len    :   decoded message length
//  _msg_enc        :   encoded message (soft bits)
//  _msg_dec        :   decoded message
void fec_decode_soft(fec _q,
                     unsigned int _dec_msg_len,
                     unsigned char * _msg_enc,
                     unsigned char * _msg_dec);


#define CRC8_POLY 0x07
#define CRC16_POLY 0x8005
#define CRC24_POLY 0x5D6DCB
#define CRC32_POLY 0x04C11DB7

unsigned int checksum_generate_key(unsigned char * _msg, unsigned int _msg_len);
unsigned int crc8_generate_key(unsigned char * _msg, unsigned int _msg_len);
unsigned int crc16_generate_key(unsigned char * _msg, unsigned int _msg_len);
unsigned int crc24_generate_key(unsigned char * _msg, unsigned int _msg_len);
unsigned int crc32_generate_key(unsigned char * _msg, unsigned int _msg_len);


// fec : basic object
struct fec_s {
    // common
    fec_scheme scheme;
    //unsigned int dec_msg_len;
    //unsigned int enc_msg_len;
    float rate;

    // lengths: convolutional, Reed-Solomon
    unsigned int num_dec_bytes;
    unsigned int num_enc_bytes;

    // convolutional : internal memory structure
    unsigned char * enc_bits;
    void * vp;      // decoder object
    int * poly;     // polynomial
    unsigned int R; // primitive rate, inverted (e.g. R=3 for 1/3)
    unsigned int K; // constraint length
    unsigned int P; // puncturing rate (e.g. p=3 for 3/4)
    int * puncturing_matrix;

    // viterbi decoder function pointers
    void*(*create_viterbi)(int);
    //void (*set_viterbi_polynomial)(int*);
    int  (*init_viterbi)(void*,int);
    int  (*update_viterbi_blk)(void*,unsigned char*,int);
    int  (*chainback_viterbi)(void*,unsigned char*,unsigned int,unsigned int);
    void (*delete_viterbi)(void*);

    // Reed-Solomon
    int symsize;    // symbol size (bits per symbol)
    int genpoly;    // generator polynomial
    int fcs;        //
    int prim;       //
    int nroots;     // number of roots in the polynomial
    //int ntrials;    //
    unsigned int rspad; // number of implicit padded symbols
    int nn;         // 2^symsize - 1
    int kk;         // nn - nroots
    void * rs;      // Reed-Solomon internal object

    // Reed-Solomon decoder
    unsigned int num_blocks;    // number of blocks: ceil(dec_msg_len / nn)
    unsigned int dec_block_len; // number of decoded bytes per block: 
    unsigned int enc_block_len; // number of encoded bytes per block: 
    unsigned int res_block_len; // residual bytes in last block
    unsigned int pad;           // padding for each block
    unsigned char * tblock;     // decoder input sequence [size: 1 x n]
    int * errlocs;              // error locations [size: 1 x n]
    int * derrlocs;             // decoded error locations [size: 1 x n]
    int erasures;               // number of erasures

    // encode function pointer
    void (*encode_func)(fec _q,
                        unsigned int _dec_msg_len,
                        unsigned char * _msg_dec,
                        unsigned char * _msg_enc);

    // decode function pointer
    void (*decode_func)(fec _q,
                        unsigned int _dec_msg_len,
                        unsigned char * _msg_enc,
                        unsigned char * _msg_dec);

    // decode function pointer (soft decision)
    void (*decode_soft_func)(fec _q,
                             unsigned int _dec_msg_len,
                             unsigned char * _msg_enc,
                             unsigned char * _msg_dec);
};

// simple type testing
int fec_scheme_is_convolutional(fec_scheme _scheme);
int fec_scheme_is_punctured(fec_scheme _scheme);
int fec_scheme_is_reedsolomon(fec_scheme _scheme);
int fec_scheme_is_hamming(fec_scheme _scheme);
int fec_scheme_is_repeat(fec_scheme _scheme);

// Pass
fec fec_pass_create(void *_opts);
void fec_pass_destroy(fec _q);
void fec_pass_print(fec _q);
void fec_pass_encode(fec _q,
                     unsigned int _dec_msg_len,
                     unsigned char * _msg_dec,
                     unsigned char * _msg_enc);
void fec_pass_decode(fec _q,
                     unsigned int _dec_msg_len,
                     unsigned char * _msg_enc,
                     unsigned char * _msg_dec);

// Repeat (3)
fec fec_rep3_create(void *_opts);
void fec_rep3_destroy(fec _q);
void fec_rep3_print(fec _q);
void fec_rep3_encode(fec _q,
                     unsigned int _dec_msg_len,
                     unsigned char * _msg_dec,
                     unsigned char * _msg_enc);
void fec_rep3_decode(fec _q,
                     unsigned int _dec_msg_len,
                     unsigned char * _msg_enc,
                     unsigned char * _msg_dec);
void fec_rep3_decode_soft(fec _q,
                          unsigned int _dec_msg_len,
                          unsigned char * _msg_enc,
                          unsigned char * _msg_dec);

// Repeat (5)
fec fec_rep5_create(void *_opts);
void fec_rep5_destroy(fec _q);
void fec_rep5_print(fec _q);
void fec_rep5_encode(fec _q,
                     unsigned int _dec_msg_len,
                     unsigned char * _msg_dec,
                     unsigned char * _msg_enc);
void fec_rep5_decode(fec _q,
                     unsigned int _dec_msg_len,
                     unsigned char * _msg_enc,
                     unsigned char * _msg_dec);
void fec_rep5_decode_soft(fec _q,
                          unsigned int _dec_msg_len,
                          unsigned char * _msg_enc,
                          unsigned char * _msg_dec);

// Hamming(7,4)
extern unsigned char hamming74_enc_gentab[16];
extern unsigned char hamming74_dec_gentab[128];
fec fec_hamming74_create(void *_opts);
void fec_hamming74_destroy(fec _q);
void fec_hamming74_print(fec _q);
void fec_hamming74_encode(fec _q,
                          unsigned int _dec_msg_len,
                          unsigned char * _msg_dec,
                          unsigned char * _msg_enc);
void fec_hamming74_decode(fec _q,
                          unsigned int _dec_msg_len,
                          unsigned char * _msg_enc,
                          unsigned char * _msg_dec);
void fec_hamming74_decode_soft(fec _q,
                               unsigned int _dec_msg_len,
                               unsigned char * _msg_enc,
                               unsigned char * _msg_dec);
// soft decoding of one symbol
unsigned char fecsoft_hamming74_decode(unsigned char * _soft_bits);

// Hamming(8,4)
extern unsigned char hamming84_enc_gentab[16];
extern unsigned char hamming84_dec_gentab[256];
fec fec_hamming84_create(void *_opts);
void fec_hamming84_destroy(fec _q);
void fec_hamming84_print(fec _q);
void fec_hamming84_encode(fec _q,
                          unsigned int _dec_msg_len,
                          unsigned char * _msg_dec,
                          unsigned char * _msg_enc);
void fec_hamming84_decode(fec _q,
                          unsigned int _dec_msg_len,
                          unsigned char * _msg_enc,
                          unsigned char * _msg_dec);
void fec_hamming84_decode_soft(fec _q,
                               unsigned int _dec_msg_len,
                               unsigned char * _msg_enc,
                               unsigned char * _msg_dec);
// soft decoding of one symbol
unsigned char fecsoft_hamming84_decode(unsigned char * _soft_bits);

// Hamming(12,8)

unsigned int fec_hamming128_encode_symbol(unsigned int _sym_dec);
unsigned int fec_hamming128_decode_symbol(unsigned int _sym_enc);
extern unsigned short int hamming128_enc_gentab[256];   // encoding table

fec fec_hamming128_create(void *_opts);
void fec_hamming128_destroy(fec _q);
void fec_hamming128_print(fec _q);
void fec_hamming128_encode(fec _q,
                           unsigned int _dec_msg_len,
                           unsigned char * _msg_dec,
                           unsigned char * _msg_enc);
void fec_hamming128_decode(fec _q,
                           unsigned int _dec_msg_len,
                           unsigned char * _msg_enc,
                           unsigned char * _msg_dec);
void fec_hamming128_decode_soft(fec _q,
                                unsigned int _dec_msg_len,
                                unsigned char * _msg_enc,
                                unsigned char * _msg_dec);
// soft decoding of one symbol
unsigned int fecsoft_hamming128_decode(unsigned char * _soft_bits);
extern unsigned char fecsoft_hamming128_n3[256][17];
unsigned int fecsoft_hamming128_decode_n3(unsigned char * _soft_bits);


// Hamming(15,11)
unsigned int fec_hamming1511_encode_symbol(unsigned int _sym_dec);
unsigned int fec_hamming1511_decode_symbol(unsigned int _sym_enc);

// Hamming(31,26)
unsigned int fec_hamming3126_encode_symbol(unsigned int _sym_dec);
unsigned int fec_hamming3126_decode_symbol(unsigned int _sym_enc);


// Golay(24,12)

unsigned int fec_golay2412_encode_symbol(unsigned int _sym_dec);
unsigned int fec_golay2412_decode_symbol(unsigned int _sym_enc);
extern unsigned int golay2412_P[12];
extern unsigned int golay2412_Gt[24];
extern unsigned int golay2412_H[12];

// multiply input vector with matrix
unsigned int golay2412_matrix_mul(unsigned int   _v,
                                  unsigned int * _A,
                                  unsigned int   _n);

// search for p[i] such that w(v+p[i]) <= 2, return -1 on fail
int golay2412_parity_search(unsigned int _v);

fec fec_golay2412_create(void *_opts);
void fec_golay2412_destroy(fec _q);
void fec_golay2412_print(fec _q);
void fec_golay2412_encode(fec _q,
                          unsigned int _dec_msg_len,
                          unsigned char * _msg_dec,
                          unsigned char * _msg_enc);
void fec_golay2412_decode(fec _q,
                          unsigned int _dec_msg_len,
                          unsigned char * _msg_enc,
                          unsigned char * _msg_dec);

// SEC-DED (22,16)

// compute parity on 16-bit input
unsigned char fec_secded2216_compute_parity(unsigned char * _m);

// compute syndrome on 22-bit input
unsigned char fec_secded2216_compute_syndrome(unsigned char * _v);

// encode symbol
//  _sym_dec    :   decoded symbol [size: 2 x 1]
//  _sym_enc    :   encoded symbol [size: 3 x 1], _sym_enc[0] has only 6 bits
void fec_secded2216_encode_symbol(unsigned char * _sym_dec,
                                  unsigned char * _sym_enc);

// decode symbol, returning 0/1/2 for zero/one/multiple errors detected
//  _sym_enc    :   encoded symbol [size: 3 x 1], _sym_enc[0] has only 6 bits
//  _sym_dec    :   decoded symbol [size: 2 x 1]
int  fec_secded2216_decode_symbol(unsigned char * _sym_enc,
                                  unsigned char * _sym_dec);

// estimate error vector, returning 0/1/2 for zero/one/multiple errors detected
//  _sym_enc    :   encoded symbol [size: 3 x 1], _sym_enc[0] has only 6 bits
//  _e_hat      :   estimated error vector [size: 3 x 1]
int  fec_secded2216_estimate_ehat(unsigned char * _sym_enc,
                                  unsigned char * _e_hat);

// parity matrix [6 x 16 bits], [6 x 2 bytes]
extern unsigned char secded2216_P[12];

// syndrome vectors of errors with weight exactly equal to 1
extern unsigned char secded2216_syndrome_w1[22];

fec fec_secded2216_create(void *_opts);
void fec_secded2216_destroy(fec _q);
void fec_secded2216_print(fec _q);
void fec_secded2216_encode(fec _q,
                           unsigned int _dec_msg_len,
                           unsigned char * _msg_dec,
                           unsigned char * _msg_enc);
void fec_secded2216_decode(fec _q,
                           unsigned int _dec_msg_len,
                           unsigned char * _msg_enc,
                           unsigned char * _msg_dec);

// SEC-DED (39,32)

// compute parity on 32-bit input
unsigned char fec_secded3932_compute_parity(unsigned char * _m);

// compute syndrome on 39-bit input
unsigned char fec_secded3932_compute_syndrome(unsigned char * _v);

// encode symbol
//  _sym_dec    :   decoded symbol [size: 4 x 1]
//  _sym_enc    :   encoded symbol [size: 5 x 1], _sym_enc[0] has only 7 bits
void fec_secded3932_encode_symbol(unsigned char * _sym_dec,
                                  unsigned char * _sym_enc);

// estimate error vector, returning 0/1/2 for zero/one/multiple errors detected
//  _sym_enc    :   encoded symbol [size: 5 x 1], _sym_enc[0] has only 7 bits
//  _e_hat      :   estimated error vector [size: 5 x 1]
int  fec_secded3932_estimate_ehat(unsigned char * _sym_enc,
                                  unsigned char * _e_hat);

// decode symbol, returning 0/1/2 for zero/one/multiple errors detected
//  _sym_enc    :   encoded symbol [size: 5 x 1], _sym_enc[0] has only 7 bits
//  _sym_dec    :   decoded symbol [size: 4 x 1]
int fec_secded3932_decode_symbol(unsigned char * _sym_enc,
                                 unsigned char * _sym_dec);

// parity matrix [7 x 32 bits], [7 x 4 bytes]
extern unsigned char secded3932_P[28];

// syndrome vectors of errors with weight exactly equal to 1
extern unsigned char secded3932_syndrome_w1[39];

fec fec_secded3932_create(void *_opts);
void fec_secded3932_destroy(fec _q);
void fec_secded3932_print(fec _q);
void fec_secded3932_encode(fec _q,
                           unsigned int _dec_msg_len,
                           unsigned char * _msg_dec,
                           unsigned char * _msg_enc);
void fec_secded3932_decode(fec _q,
                           unsigned int _dec_msg_len,
                           unsigned char * _msg_enc,
                           unsigned char * _msg_dec);

// SEC-DED (72,64)

// compute parity byte on 64-byte input
unsigned char fec_secded7264_compute_parity(unsigned char * _v);

// compute syndrome on 72-bit input
unsigned char fec_secded7264_compute_syndrome(unsigned char * _v);

// encode symbol
//  _sym_dec    :   input symbol [size: 8 x 1]
//  _sym_enc    :   input symbol [size: 9 x 1]
void fec_secded7264_encode_symbol(unsigned char * _sym_dec,
                                  unsigned char * _sym_enc);

// estimate error vector, returning 0/1/2 for zero/one/multiple errors detected
//  _sym_enc    :   encoded symbol [size: 9 x 1]
//  _e_hat      :   estimated error vector [size: 9 x 1]
int fec_secded7264_estimate_ehat(unsigned char * _sym_enc,
                                 unsigned char * _e_hat);

// decode symbol, returning 0/1/2 for zero/one/multiple errors detected
//  _sym_enc    :   input symbol [size: 8 x 1]
//  _sym_dec    :   input symbol [size: 9 x 1]
int fec_secded7264_decode_symbol(unsigned char * _sym_enc,
                                 unsigned char * _sym_dec);

extern unsigned char secded7264_P[64];
extern unsigned char secded7264_syndrome_w1[72];

fec fec_secded7264_create(void *_opts);
void fec_secded7264_destroy(fec _q);
void fec_secded7264_print(fec _q);
void fec_secded7264_encode(fec _q,
                           unsigned int _dec_msg_len,
                           unsigned char * _msg_dec,
                           unsigned char * _msg_enc);
void fec_secded7264_decode(fec _q,
                           unsigned int _dec_msg_len,
                           unsigned char * _msg_enc,
                           unsigned char * _msg_dec);


// Convolutional: r1/2 K=7
//                r1/2 K=9
//                r1/3 K=9
//                r1/6 K=15

// compute encoded message length for block codes
//  _dec_msg_len    :   decoded message length (bytes)
//  _m              :   input block size (bits)
//  _k              :   output block size (bits)
unsigned int fec_block_get_enc_msg_len(unsigned int _dec_msg_len,
                                       unsigned int _m,
                                       unsigned int _k);

// compute encoded message length for convolutional codes
//  _dec_msg_len    :   decoded message length
//  _K              :   constraint length
//  _p              :   puncturing rate, r = _p / (_p+1)
unsigned int fec_conv_get_enc_msg_len(unsigned int _dec_msg_len,
                                      unsigned int _K,
                                      unsigned int _p);

// convolutional code polynomials
extern int fec_conv27_poly[2];
extern int fec_conv29_poly[2];
extern int fec_conv39_poly[3];
extern int fec_conv615_poly[6];

// convolutional code puncturing matrices  [R x P]
extern int fec_conv27p23_matrix[4];     // [2 x 2]
extern int fec_conv27p34_matrix[6];     // [2 x 3]
extern int fec_conv27p45_matrix[8];     // [2 x 4]
extern int fec_conv27p56_matrix[10];    // [2 x 5]
extern int fec_conv27p67_matrix[12];    // [2 x 6]
extern int fec_conv27p78_matrix[14];    // [2 x 7]

extern int fec_conv29p23_matrix[4];     // [2 x 2]
extern int fec_conv29p34_matrix[6];     // [2 x 3]
extern int fec_conv29p45_matrix[8];     // [2 x 4]
extern int fec_conv29p56_matrix[10];    // [2 x 5]
extern int fec_conv29p67_matrix[12];    // [2 x 6]
extern int fec_conv29p78_matrix[14];    // [2 x 7]

fec fec_conv_create(fec_scheme _fs);
void fec_conv_destroy(fec _q);
void fec_conv_print(fec _q);
void fec_conv_encode(fec _q,
                     unsigned int _dec_msg_len,
                     unsigned char * _msg_dec,
                     unsigned char * _msg_enc);
void fec_conv_decode_hard(fec _q,
                          unsigned int _dec_msg_len,
                          unsigned char * _msg_enc,
                          unsigned char * _msg_dec);
void fec_conv_decode_soft(fec _q,
                          unsigned int _dec_msg_len,
                          unsigned char * _msg_enc,
                          unsigned char * _msg_dec);
void fec_conv_decode(fec _q,
                     unsigned char * _msg_dec);
void fec_conv_setlength(fec _q,
                        unsigned int _dec_msg_len);

// internal initialization methods (sets r, K, viterbi methods)
void fec_conv_init_v27(fec _q);
void fec_conv_init_v29(fec _q);
void fec_conv_init_v39(fec _q);
void fec_conv_init_v615(fec _q);

// punctured convolutional codes
fec fec_conv_punctured_create(fec_scheme _fs);
void fec_conv_punctured_destroy(fec _q);
void fec_conv_punctured_print(fec _q);
void fec_conv_punctured_encode(fec _q,
                               unsigned int _dec_msg_len,
                               unsigned char * _msg_dec,
                               unsigned char * _msg_enc);
void fec_conv_punctured_decode_hard(fec _q,
                                    unsigned int _dec_msg_len,
                                    unsigned char * _msg_enc,
                                    unsigned char * _msg_dec);
void fec_conv_punctured_decode_soft(fec _q,
                                    unsigned int _dec_msg_len,
                                    unsigned char * _msg_enc,
                                    unsigned char * _msg_dec);
void fec_conv_punctured_setlength(fec _q,
                                  unsigned int _dec_msg_len);

// internal initialization methods (sets r, K, viterbi methods,
// and puncturing matrix)
void fec_conv_init_v27p23(fec _q);
void fec_conv_init_v27p34(fec _q);
void fec_conv_init_v27p45(fec _q);
void fec_conv_init_v27p56(fec _q);
void fec_conv_init_v27p67(fec _q);
void fec_conv_init_v27p78(fec _q);

void fec_conv_init_v29p23(fec _q);
void fec_conv_init_v29p34(fec _q);
void fec_conv_init_v29p45(fec _q);
void fec_conv_init_v29p56(fec _q);
void fec_conv_init_v29p67(fec _q);
void fec_conv_init_v29p78(fec _q);

// Reed-Solomon

// compute encoded message length for Reed-Solomon codes
//  _dec_msg_len    :   decoded message length
//  _nroots         :   number of roots in polynomial
//  _nn             :   
//  _kk             :   
unsigned int fec_rs_get_enc_msg_len(unsigned int _dec_msg_len,
                                    unsigned int _nroots,
                                    unsigned int _nn,
                                    unsigned int _kk);


fec fec_rs_create(fec_scheme _fs);
void fec_rs_destroy(fec _q);
void fec_rs_init_p8(fec _q);
void fec_rs_setlength(fec _q,
                      unsigned int _dec_msg_len);
void fec_rs_encode(fec _q,
                   unsigned int _dec_msg_len,
                   unsigned char * _msg_dec,
                   unsigned char * _msg_enc);
void fec_rs_decode(fec _q,
                   unsigned int _dec_msg_len,
                   unsigned char * _msg_enc,
                   unsigned char * _msg_dec);

// phi(x) = -logf( tanhf( x/2 ) )
float sumproduct_phi(float _x);

// iterate over the sum-product algorithm:
// returns 1 if parity checks, 0 otherwise
//  _m          :   rows
//  _n          :   cols
//  _H          :   sparse binary parity check matrix [size: _m x _n]
//  _LLR        :   received signal (soft bits, LLR) [size: _n x 1]
//  _c_hat      :   estimated transmitted signal [size: _n x 1]
//  _max_steps  :   maximum number of steps before bailing
// int fec_sumproduct(unsigned int    _m,
//                    unsigned int    _n,
//                    smatrixb        _H,
//                    float *         _LLR,
//                    unsigned char * _c_hat,
//                    unsigned int    _max_steps);

// // sum-product algorithm, returns 1 if parity checks, 0 otherwise
// //  _m      :   rows
// //  _n      :   cols
// //  _H      :   sparse binary parity check matrix [size: _m x _n]
// //  _c_hat  :   estimated transmitted signal [size: _n x 1]
// //
// // internal state arrays
// //  _Lq     :   [size: _m x _n]
// //  _Lr     :   [size: _m x _n]
// //  _Lc     :   [size: _n x 1]
// //  _LQ     :   [size: _n x 1]
// //  _parity :   _H * _c_hat [size: _m x 1]
// int fec_sumproduct_step(unsigned int    _m,
//                         unsigned int    _n,
//                         smatrixb        _H,
//                         unsigned char * _c_hat,
//                         float *         _Lq,
//                         float *         _Lr,
//                         float *         _Lc,
//                         float *         _LQ,
//                         unsigned char * _parity);

// //
// // packetizer
// //

// // fec/interleaver plan
// struct fecintlv_plan {
//     unsigned int dec_msg_len;
//     unsigned int enc_msg_len;

//     // fec codec
//     fec_scheme fs;
//     fec f;

//     // interleaver
//     interleaver q;
// };

unsigned int liquid_count_ones(unsigned int _x);

// count the number of ones in an integer, modulo 2
unsigned int liquid_count_ones_mod2(unsigned int _x);

// count the binary dot-product between two integers
unsigned int liquid_bdotprod(unsigned int _x,
                             unsigned int _y);


// counts the number of different bits between two symbols
unsigned int count_bit_errors(unsigned int _s1,
                              unsigned int _s2);

// counts the number of different bits between two arrays of symbols
//  _msg0   :   original message [size: _n x 1]
//  _msg1   :   copy of original message [size: _n x 1]
//  _n      :   message size
unsigned int count_bit_errors_array(unsigned char * _msg0,
                                    unsigned char * _msg1,
                                    unsigned int _n);

// print string of bits to standard output
void liquid_print_bitstring(unsigned int _x,
                            unsigned int _n);

// slow implementation of byte reversal
unsigned char liquid_reverse_byte(unsigned char _x);

// reverse integer with 16 bits of data
unsigned int liquid_reverse_uint16(unsigned int _x);

// reverse integer with 24 bits of data
unsigned int liquid_reverse_uint24(unsigned int _x);

// reverse integer with 32 bits of data
unsigned int liquid_reverse_uint32(unsigned int _x);

void liquid_pack_array(unsigned char * _src,
                       unsigned int _n,
                       unsigned int _k,
                       unsigned int _b,
                       unsigned char _sym_in);

void liquid_unpack_array(unsigned char * _src,
                         unsigned int _n,
                         unsigned int _k,
                         unsigned int _b,
                         unsigned char * _sym_out);


void liquid_pack_bytes(unsigned char * _sym_in,
                       unsigned int _sym_in_len,
                       unsigned char * _sym_out,
                       unsigned int _sym_out_len,
                       unsigned int * _num_written);

void liquid_unpack_bytes(unsigned char * _sym_in,
                         unsigned int _sym_in_len,
                         unsigned char * _sym_out,
                         unsigned int _sym_out_len,
                         unsigned int * _num_written);

#ifdef __cplusplus
}
#endif

#endif

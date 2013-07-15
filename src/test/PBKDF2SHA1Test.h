/*
* Copyright (c) 2013 Rony Shapiro <ronys@users.sourceforge.net>.
* All rights reserved. Use of the code is allowed under the
* Artistic License 2.0 terms, as specified in the LICENSE file
* distributed with this code, or available from
* http://www.opensource.org/licenses/artistic-license-2.0.php
*/
// PBKDF2SHA1Test.h: Unit test for PBKDF implementation with HMAC-SHA1
// Test vectors from RFC6070

#include "test.h"
#include "core/pbkdf2.h"
#include "core/hmac.h"
#include "core/sha1.h"
#include <iostream>

class CPBKDF2_SHA1Test : public Test
{

public:
  CPBKDF2_SHA1Test()
  {
  }

  void run()
  {
    pbkdf2_sha1_test();
  }


  void pbkdf2_sha1_test(void)
  {
    const struct {
      unsigned char *P; unsigned long Plen;
      unsigned char *S; unsigned long Slen;
      int c;
      int dkLen;
      unsigned char DK[36];
    } tests[] = {
      {// Input:
        /* P = */ (unsigned char *)"password", 8,
        /* S = */ (unsigned char *)"salt", 4,
        /* c = */ 1,
        /* dkLen = */ 20,

     // Output:
        /* DK = */ {0x0c, 0x60, 0xc8, 0x0f, 0x96, 0x1f, 0x0e, 0x71,
                    0xf3, 0xa9, 0xb5, 0x24, 0xaf, 0x60, 0x12, 0x06,
                    0x2f, 0xe0, 0x37, 0xa6} /* (20 octets) */},
      {// Input:
        /* P = */ (unsigned char *)"password", 8,
        /* S = */ (unsigned char *)"salt", 4,
        /* c = */ 2,
        /* dkLen = */ 20,

     // Output:
        /* DK = */ {0xea, 0x6c, 0x01, 0x4d, 0xc7, 0x2d, 0x6f, 0x8c,
                    0xcd, 0x1e, 0xd9, 0x2a, 0xce, 0x1d, 0x41, 0xf0,
                    0xd8, 0xde, 0x89, 0x57} /* 20 octets) */},
      {// Input:
        /* P = */ (unsigned char *)"password", 8,
        /* S = */ (unsigned char *)"salt", 4,
        /* c = */ 4096,
        /* dkLen = */ 20,

     // Output:
        /* DK = */ {0x4b, 0x00, 0x79, 0x01, 0xb7, 0x65, 0x48, 0x9a,
                    0xbe, 0xad, 0x49, 0xd9, 0x26, 0xf7, 0x21, 0xd0,
                    0x65, 0xa4, 0x29, 0xc1} /* (20 octets) */},
      {// Input:
        /* P = */ (unsigned char *)"password", 8,
        /* S = */ (unsigned char *)"salt", 4,
        /* c = */ 16777216,
        /* dkLen = */ 20,

     // Output:
        /* DK = */ {0xee, 0xfe, 0x3d, 0x61, 0xcd, 0x4d, 0xa4, 0xe4,
                    0xe9, 0x94, 0x5b, 0x3d, 0x6b, 0xa2, 0x15, 0x8c,
                    0x26, 0x34, 0xe9, 0x84} /* (20 octets) */},
      {// Input:
        /* P = */ (unsigned char *)"passwordPASSWORDpassword", 24,
        /* S = */ (unsigned char *)"saltSALTsaltSALTsaltSALTsaltSALTsalt", 36,
        /* c = */ 4096,
        /* dkLen = */ 25,

     // Output:
        /* DK = */ {0x3d, 0x2e, 0xec, 0x4f, 0xe4, 0x1c, 0x84, 0x9b,
                    0x80, 0xc8, 0xd8, 0x36, 0x62, 0xc0, 0xe4, 0x4a,
                    0x8b, 0x29, 0x1a, 0x96, 0x4c, 0xf2, 0xf0, 0x70,
                    0x38} /* (25 octets) */},
      {// Input:
        /* P = */ (unsigned char *)"pass\0word", 9,
        /* S = */ (unsigned char *)"sa\0lt", 5,
        /* c = */ 4096,
        /* dkLen = */ 16,

     // Output:
        /* DK = */ {0x56, 0xfa, 0x6a, 0xa7, 0x55, 0x48, 0x09, 0x9d,
                    0xcc, 0x37, 0xd7, 0xf0, 0x34, 0x25, 0xe0, 0xc3} /* (16 octets) */},
    };

    size_t i;
    unsigned char tmp[32];
    unsigned long outLen;
    for (i = 0; i < (sizeof(tests) / sizeof(tests[0])); i++) {
      HMAC<SHA1, SHA1::HASHLEN, SHA1::BLOCKSIZE> hmac;
      outLen= tests[i].dkLen;
      pbkdf2(tests[i].P, tests[i].Plen,
             tests[i].S, tests[i].Slen,
             tests[i].c, &hmac, tmp, &outLen);
      _test(memcmp(tmp, tests[i].DK, outLen) == 0);
      if (memcmp(tmp, tests[i].DK, outLen)) {
        size_t j;
        std::cerr << std::endl << "expected: ";
        for (j = 0;  j < outLen; j++)
          std::cerr << std::hex << int(tests[i].DK[j]) << " ";
        std::cerr << std::endl << "actual:   ";
        for (j = 0;  j < outLen; j++)
          std::cerr << std::hex << int(tmp[j]) << " ";
        std::cerr << std::endl;
      }
    }
  }
};


// Custom iconv.h to work around macOS SDK type incompatibility
// This header provides compatible iconv declarations for cocos2d-x

#ifndef __ICONV_H__
#define __ICONV_H__

#include <cstddef>
#include <cstdint>

#ifdef __cplusplus
extern "C"
{
#endif

    // Define iconv_t as void* to match what cocos2d-x expects
    typedef void *iconv_t;

    // Function declarations
    iconv_t iconv_open(const char *tocode, const char *fromcode);
    int iconv_close(iconv_t cd);
    size_t iconv(iconv_t cd, char **inbuf, size_t *inleft,
                 char **outbuf, size_t *outleft);

#ifdef __cplusplus
}
#endif

#endif

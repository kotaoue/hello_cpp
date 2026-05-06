// Stub implementations of iconv functions to work around macOS SDK issues
// These functions are used by cocos2d-x's CCFontAtlas but cause compilation errors
// on modern macOS. By providing these stubs, we override the real iconv functions
// at link time and avoid the error.

#include <cstddef>

// Dummy implementation of iconv_open
extern "C"
{
    typedef void *iconv_t;

    iconv_t iconv_open(const char *tocode, const char *fromcode)
    {
        // Return a dummy non-null value to satisfy the code path
        return reinterpret_cast<iconv_t>(1);
    }

    int iconv_close(iconv_t cd)
    {
        // Do nothing, just return success
        return 0;
    }

    size_t iconv(iconv_t cd, char **inbuf, size_t *inleft,
                 char **outbuf, size_t *outleft)
    {
        // Do nothing, return success
        return 0;
    }
}

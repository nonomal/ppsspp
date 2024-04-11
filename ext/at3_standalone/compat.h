#pragma once

// Compat hacks

#if defined(__GNUC__)
#define DECLARE_ALIGNED(n,t,v)      t __attribute__ ((aligned (n))) v
#define DECLARE_ASM_CONST(n,t,v)    static const t av_used __attribute__ ((aligned (n))) v
#elif defined(_MSC_VER)
#define DECLARE_ALIGNED(n,t,v)      __declspec(align(n)) t v
#define DECLARE_ASM_CONST(n,t,v)    __declspec(align(n)) static const t v
#else
#define DECLARE_ALIGNED(n,t,v)      t v
#define DECLARE_ASM_CONST(n,t,v)    static const t v
#endif

#define LOCAL_ALIGNED(bits, type, name, subscript) type name subscript
#define av_restrict
#define av_alias
#define av_unused
#define av_assert0(cond)
#define av_assert1(cond)
#define av_assert2(cond)
#define av_printf_format(a,b)
#define avpriv_report_missing_feature(...)

#define AV_NOPTS_VALUE          ((int64_t)UINT64_C(0x8000000000000000))
#define AV_TIME_BASE            1000000
#define AV_TIME_BASE_Q          (AVRational){1, AV_TIME_BASE}

#define AVERROR(e) (-(e))   ///< Returns a negative error code from a POSIX error code, to return from library functions.
#define AVUNERROR(e) (-(e)) ///< Returns a POSIX error code from a library function error return value.

#define FFERRTAG(a, b, c, d) (-(int)MKTAG(a, b, c, d))

#define AVERROR_INVALIDDATA        FFERRTAG( 'I','N','D','A') ///< Invalid data found when processing input
#define AVERROR_PATCHWELCOME       FFERRTAG( 'P','A','W','E') ///< Not yet implemented in FFmpeg, patches welcome

#define FF_SANE_NB_CHANNELS 64U

#define AV_LOG_ERROR    16
#define AV_LOG_WARNING  24
#define AV_LOG_INFO     32
#define AV_LOG_VERBOSE  40
#define AV_LOG_DEBUG    48
#define AV_LOG_TRACE    56

void av_log(int level, const char *fmt, ...) av_printf_format(3, 4);

/**
 * Maximum size in bytes of extradata.
 * This value was chosen such that every bit of the buffer is
 * addressable by a 32-bit signed integer as used by get_bits.
 */
#define FF_MAX_EXTRADATA_SIZE ((1 << 28) - AV_INPUT_BUFFER_PADDING_SIZE)

 /**
  * Absolute value, Note, INT_MIN / INT64_MIN result in undefined behavior as they
  * are not representable as absolute values of their type. This is the same
  * as with *abs()
  * @see FFNABS()
  */
#define FFABS(a) ((a) >= 0 ? (a) : (-(a)))

#define FFMAX(a,b) ((a) > (b) ? (a) : (b))
#define FFMIN(a,b) ((a) > (b) ? (b) : (a))

#define FFSWAP(type,a,b) do{type SWAP_tmp= b; b= a; a= SWAP_tmp;}while(0)
#define FF_ARRAY_ELEMS(a) (sizeof(a) / sizeof((a)[0]))

#define MKTAG(a,b,c,d) ((a) | ((b) << 8) | ((c) << 16) | ((unsigned)(d) << 24))

#pragma warning(disable:4305)
#pragma warning(disable:4244)

int ff_fast_malloc(void *ptr, unsigned int *size, size_t min_size, int zero_realloc);

/**
 * Copy the string src to dst, but no more than size - 1 bytes, and
 * null-terminate dst.
 *
 * This function is the same as BSD strlcpy().
 *
 * @param dst destination buffer
 * @param src source string
 * @param size size of destination buffer
 * @return the length of src
 *
 * @warning since the return value is the length of src, src absolutely
 * _must_ be a properly 0-terminated string, otherwise this will read beyond
 * the end of the buffer and possibly crash.
 */
size_t av_strlcpy(char *dst, const char *src, size_t size);

/**
 * Locale-independent conversion of ASCII characters to uppercase.
 */
static inline int av_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c ^= 0x20;
	return c;
}

#define AV_BSWAP16C(x) (((x) << 8 & 0xff00)  | ((x) >> 8 & 0x00ff))
#define AV_BSWAP32C(x) (AV_BSWAP16C(x) << 16 | AV_BSWAP16C((x) >> 16))
#define av_be2ne32(x) AV_BSWAP32C((x))

#include <nh3api/core.hpp>

#ifndef IDA_TEST
#define IDA_TEST(FUNCTION_NAME, ...) [[gnu::used]] auto FUNCTION_NAME (__VA_ARGS__) noexcept
#endif

#ifndef IS_MUL_OK_TEST
#define IS_MUL_OK_TEST(U, N) IDA_TEST(is_mul_ok_test##N, U##int##N##_t x, U##int##N##_t y) { return is_mul_ok(x, y); }
#endif

IS_MUL_OK_TEST(,8)
IS_MUL_OK_TEST(u,8)
IS_MUL_OK_TEST(,16)
IS_MUL_OK_TEST(u,16)
IS_MUL_OK_TEST(,32)
IS_MUL_OK_TEST(u,32)
IS_MUL_OK_TEST(,64)
IS_MUL_OK_TEST(u,64)

#define SATURATED_MUL_TEST(U, N) IDA_TEST(saturated_mul_test##N, U##int##N##_t x, U##int##N##_t y) { return saturated_mul(x, y); }
SATURATED_MUL_TEST(,8)
SATURATED_MUL_TEST(u,8)
SATURATED_MUL_TEST(,16)
SATURATED_MUL_TEST(u,16)
SATURATED_MUL_TEST(,32)
SATURATED_MUL_TEST(u,32)
SATURATED_MUL_TEST(,64)
SATURATED_MUL_TEST(u,64)

#define ROR_ROL_TEST(N) IDA_TEST(rol_test##N, uint##N##_t x, uint##N##_t y) { return __ROL__(x, y); } \
                        IDA_TEST(ror_test##N, uint##N##_t x, uint##N##_t y) { return __ROR__(x, y); }

ROR_ROL_TEST(8)
ROR_ROL_TEST(16)
ROR_ROL_TEST(32)
ROR_ROL_TEST(64)

#define MKCSHL_MKCSHR_TEST(U, N) IDA_TEST(mkcshl_test##N, U##int##N##_t value, uint32_t count) { return __MKCSHL__(value, count); } \
                                 IDA_TEST(mkcshr_test##N, U##int##N##_t value, uint32_t count) { return __MKCSHR__(value, count); }

MKCSHL_MKCSHR_TEST(,8)
MKCSHL_MKCSHR_TEST(u,8)
MKCSHL_MKCSHR_TEST(,16)
MKCSHL_MKCSHR_TEST(u,16)
MKCSHL_MKCSHR_TEST(,32)
MKCSHL_MKCSHR_TEST(u,32)
MKCSHL_MKCSHR_TEST(,64)
MKCSHL_MKCSHR_TEST(u,64)

#define OVERFLOW_TEST(U, N) IDA_TEST(ofsub_test##N, U##int##N##_t x, U##int##N##_t y) { return __OFSUB__(x, y); } \ 
                            IDA_TEST(ofadd_test##N, U##int##N##_t x, U##int##N##_t y) { return __OFADD__(x, y); } \ 
                            IDA_TEST(cfsub_test##N, U##int##N##_t x, U##int##N##_t y) { return __CFSUB__(x, y); } \ 
                            IDA_TEST(cfadd_test##N, U##int##N##_t x, U##int##N##_t y) { return __CFADD__(x, y); } 

OVERFLOW_TEST(,8)
OVERFLOW_TEST(u,8)
OVERFLOW_TEST(,16)
OVERFLOW_TEST(u,16)
OVERFLOW_TEST(,32)
OVERFLOW_TEST(u,32)
OVERFLOW_TEST(,64)
OVERFLOW_TEST(u,64)
  

#ifndef MACROS_H
#define MACROS_H

#define BIT(n) (1 << (n))
#define BIT_SET(v, mask) (v |= (mask))
#define BIT_MASK(len) (BIT(len) - 1)

#define SHIFT_V_ZERO(v, start, end) (((v) >> (start)) & (BIT_MASK((end)-(start)+1)))
#define SHIFT_V_FIRST(v) ((v) - (((v) >> 1) & 0x55555555))
#define SHIFT_V_SECOND(v) (((v) & 0x33333333) + (((v) >> 2) & 0x33333333))
#define SHIFT_V_THIRD(v) (((((v) + ((v) >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24)

#define TEST_IF_ANY_SET(v, start, end) ((((v) >> (start)) & (BIT_MASK((end)-(start) + 1))) > 0) /* 0 = no bits set */
#define TEST_IF_ALL_SET(v, start, end) ((((v) >> (start)) & (BIT_MASK((end)-(start) + 1)) ^ BIT_MASK( (end)-(start)+1) ) == 0) /* 1 = all bits set */
#define COUNT_NUM_SET(v, start, end) (SHIFT_V_THIRD(SHIFT_V_SECOND(SHIFT_V_FIRST(SHIFT_V_ZERO(v, start, end)))))

#endif
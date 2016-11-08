#define BIT(n) (1 << (n))
#define IS_SET_ANY(v, mask) (v & (mask))
#define BIT_MASK(len) (BIT(len) - 1)

#define TEST_IF_ANY_SET(v, start, end) ( ((v) >> (start)) & (BIT_MASK((end)-(start) + 1)) ) /* 0 = no bits set */
#define TEST_IF_ALL_SET(v, start, end) ( (TEST_IF_ANY_SET(v, start, end) ^ BIT_MASK((end)-(start)+1)) ) /* 0 = all bits set */
#define COUNT_NUM_SET(v, start, end) ( )
#ifndef _POKER_H
#define _POKER_H

#include <stdio.h>

/* TASK 1: 
 * Define the Value and Suit enumerators
 */

enum Value {HEART, DIAMOND, SPADE, CLUB};
enum Suit {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};

struct card {
	enum Value val;
	enum Suit suit;
};

struct player {
	struct card cards[5]; /* 5 cards for each player */
	unsigned int card_count[13]; /* counters for each of the 13 cards */
	unsigned long vector; /* A bit vector that represents the hand. Bit vector represented by higher hand is larger than bit vector represented by lower hand. */
};

/* TASK 15:
 * Insert declarations for functions in poker.c here.
 */

void compare_hands(FILE *fp);
void eval_strength(struct player *p);
int is_straight_flush(struct player *p);
int is_straight(struct player *p);
int is_flush(struct player *p);
void count_cards(struct player *p);


#endif

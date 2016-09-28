#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "poker.h"

/* Global instances of the two players */
struct player P1, P2;

/* Parse card from a 2 char input */
struct card parse(const char *card)
{
	/* TASK 14: parse input and store in card data structure. */
	struct card c;

	switch (card[0])
	{
		case '2': c.val = TWO; break;
		case '3': c.val = THREE; break;
		case '4': c.val = FOUR; break;
		case '5': c.val = FIVE; break;
		case '6': c.val = SIX; break;
		case '7': c.val = SEVEN; break;
		case '8': c.val = EIGHT; break;
		case '9': c.val = NINE; break;
		case 'T': c.val = TEN; break;
		case 'J': c.val = JACK; break;
		case 'Q': c.val = QUEEN; break;
		case 'K': c.val = KING; break;
		case 'A': c.val = ACE; break;
		default: exit(1); break; /* Error in test cases */
	}
	switch (card[1])
	{
		case 'H': c.suit = HEART; break;
		case 'D': c.suit = DIAMOND; break;
		case 'S': c.suit = SPADE; break;
		case 'C': c.suit = CLUB; break;
		default: exit(1); break; /* Error in test cases */
	}
	return c;
}

/* Count the number of occurrences of each card 2 through Ace */
void count_cards(struct player *p)
{
	/* TASK 13:  
	 * Iterate through the cards and increment the counter for each card
	 */
	 int i = 0;

	 for (i = 0; i < 5; i++)
	 	p->card_count[(int)(p->cards[i].val)]++;	 
}

int is_flush(struct player *p)
{
	int retVal = 0;
	/* TASK 12:
	 * Hand is flush if suit of all the cards is the same
	 */
	if ((p->cards[0].suit == p->cards[1].suit) &&
	 	(p->cards[0].suit == p->cards[2].suit) &&
	 	(p->cards[0].suit == p->cards[3].suit) &&
	 	(p->cards[0].suit == p->cards[4].suit))
	{
		retVal = 1;
	}

	return retVal;
}

int is_straight(struct player *p)
{
	int retVal = 0, i = 0;
	/* NOTE: By this stage, the vector must be constructed.
	 * 
	 * The hand is a straight, if the cards are sequential.
	 * A2345 as well as TJQKA are both valid straights, and Ace 
	 * assumes the value of 1 or 13, but not both.
	 */

	/* TASK 11: Check for regular straights
 	 * Hint: If this is a straight, player's card_count for i, i+1, i+2, i+3 and i+4 should be 1. */
	
	 for (i = 0; i < 13; i++)
	 {
	 	/* Only looking at bits 0->13 (2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K, A)
	 	So lets use modular to "wrap" around when checking for a straight */
	 	if  (
	 		(p->vector & (1 << (i%13))) &&
	 		(p->vector & (1 << ((i+1)%13))) &&
	 		(p->vector & (1 << ((i+2)%13))) &&
	 		(p->vector & (1 << ((i+3)%13))) &&
	 		(p->vector & (1 << ((i+4)%13)))
	 	    )
	 	{
	 		retVal = 1; /*p->vector |= (1UL << 39); /* Straight = true*/
			break;
	 	}
	 }

	/* Check for A2345
	 * TASK 10: If the hand is A2345, reset the bit for highcard Ace in the player's vector to appropriately reflect that the value of A is not 13. 
	 * Hint: 1 << position will generate a bit mask for the position of Ace. Xoring it with the vector will reset the bit.
	 */

	 /* Is Straight && contains 2 && contains A */
	 if (retVal && p->vector & (1UL << 0) && p->vector & (1UL << 12) )
	 {
	 	p->vector ^= (1 << 12); /* Set Ace to zero as it's low here, not high */
	 }

	return retVal;
}

int is_straight_flush(struct player *p)
{
	/* TASK 9: Detect straight flush. A straight flush is nothing but a straight and a flush */
	return (is_straight(p) && is_flush(p));
}
		
/* This is the main function that converts the player's hand into weighted unsigned long number. 
It is a 55bit vector as shown below (2 is the LSB and StraightFlush is the MSB) */
/* 2, 3, 4, 5, 6, 7, 8, 9, T, J, Q, K, A, 22, 33, 44, 55, 66, 77, 88, 99, TT, JJ, QQ, KK, AA,
222, 333, 444, 555, 666, 777, 888, 999, TTT, JJJ, QQQ, KKK, AAA, Straight, Flush, 2222, 3333, 
4444, 5555, 6666, 7777, 8888, 9999, TTTT, JJJJ, QQQQ, KKKK, AAAA, StraightFlush */
/* The number of occurrences of each number in the hand is first calculated in count_cards. 
Then, depending on the numeber of occurrences, the corresponding bit in the bit-vector is set. 
In order to find the winner, a simple comparison of the bit vectors (i.e., unsigned long integers) will suffice! */
void eval_strength(struct player *p)
{
	unsigned int straight_or_flush_possible;
	unsigned int i;
	unsigned int has_pair;
	unsigned int has_three_of_kind;
	straight_or_flush_possible = 1;
	has_pair = 0;
	has_three_of_kind = 0;

	/*
	 * TASK 6: Invoke the function to count the occurrences of each card
	 */
	count_cards(p);

	/*
	 * TASK 7: Iterate through the card_count array, and set the appropriate bit in the bit vector.
	 * For example, if the hand is JH JS 3C AH 4H, set the 23rd bit to indicate a pair of jacks, and 2nd, 3rd and 13th bit to indicate 3, 4 and A respectively. */
	for (i = 0; i < 13; i++)
	{
		if (p->card_count[i] == 1)
		{	
			/* This will set the vector's bits for single card correctly (0->12) */
			p->vector |= (1UL << i);
		}
		else if (p->card_count[i] == 2)
		{
			/* This will set the vector's bits for pair correctly (13->25) */
			p->vector |= (1UL << (i+13));
			has_pair = 1;
			straight_or_flush_possible = 0;
		}
		else if (p->card_count[i] == 3)
		{
			/* This will set the vector's bits for three of a kind correctly (26->38) */
			p->vector |= (1UL << (i+26));
			has_three_of_kind = 1;
			straight_or_flush_possible = 0;
		}
		else if (p->card_count[i] == 4)
		{
			/* This will set the vector's bits for four of a kind correctly <s>(41->53)</s> (42-54) */
			p->vector |= (1UL << (i+42));
			straight_or_flush_possible = 0;
		}
	}
	

	/* TASK 8:
	 * Check if this is a straight, flush or a straight flush, and set the appropriate bit in the vector.
	 */

	 /* This will check for a straight */
	if (straight_or_flush_possible && is_straight(p))
		p->vector |= (1UL << 39);

	 /* This will check for a flush */
	 if (straight_or_flush_possible && is_flush(p))
	 {
	 	p->vector |= (1UL << 40);
	 }
	 
	 /* EXTRA: Full House needs its own bit vector, so we're doing 56 bits */
	 if (has_three_of_kind && has_pair)
	 {
	 	p->vector |= (1UL << 41); /* Full House = True */
	 }			 

	 if (is_straight_flush(p))
	 {
	 	/* Straight and Flush are both true */
	 	p->vector |= (1UL << 56);
	 }

}

/* Parse each hand in the input file, evaluate the strengths of hands and identify a winner by comparing the weighted vectors */
void compare_hands(FILE *fp)
{
	char p1[5][3];
	char p2[5][3];
	int i;
	FILE *fw = fopen("Output.txt", "w");

	while(fscanf(fp, "%s %s %s %s %s %s %s %s %s %s", 
		&p1[0][0], &p1[1][0], &p1[2][0], &p1[3][0], &p1[4][0], 
		&p2[0][0], &p2[1][0], &p2[2][0], &p2[3][0], &p2[4][0]) == 10){
		memset(&P1, 0, sizeof(struct player));
		memset(&P2, 0, sizeof(struct player));
		for(i = 0; i < 5; i++) {
			P1.cards[i] = parse(&p1[i][0]);
			P2.cards[i] = parse(&p2[i][0]);
		}
		
		/* TASK 4: Invoke eval_strength for each player */
		eval_strength(&P1);
		eval_strength(&P2);
		
		/* TASK 5: Report the winner (e.g., "Player 1 wins") depending on whoever has the higher vector */
		
		if (P1.vector > P2.vector)
		{
			fprintf(fw, "%s\n", "Player 1 wins");
		}
		else if (P1.vector < P2.vector)
		{
			fprintf(fw, "%s\n", "Player 2 wins");
		}
		else /* They are equal, which breaks the test case rule..... */
		{
			fprintf(fw, "%s\n", "IT'S A TIE!!!");
		}
	}
	
	fclose(fw);
	fclose(fp);
}

int main(int argc, char *argv[])
{
	FILE *fp;

	/* TASK 2: Validate command line arguments and try to open the file. Exit on failure. */

	fp = fopen(argv[1], "r");

	if (argc != 2 || !fp)
	{
		printf("Too many arguments OR unable to open file: %s\n", argv[1]);
		exit(1);
	}

	/* TASK 3: Invoke the compare hands function */
	compare_hands(fp);

	return 0;
}
	

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "rngs.h"


int main(int argc, char** argv) {
	printf("------ Random testing adventurer card --------\n");

	srand(time(NULL));

	printf("RANDOM TESTS\n");

	int numtests = 10000;
	int failed = 0;
	for (int i = 0; i < numtests; i++) {
		int numplayers = rand() % (MAX_PLAYERS - 1) + 2; 
		struct gameState g;
		int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
		
		initializeGame(numplayers, k, rand(), &g);

		int player = rand() % numplayers;
		g.whoseTurn = player;

		int bonus = rand() % 100;
		int choice1 = rand() % 100;
		int choice2 = rand() % 100;
		int choice3 = rand() % 100;
		int handPos = rand() % MAX_HAND;

		struct gameState orig;
		memcpy(&orig, &g, sizeof(struct gameState));

		cardEffect(adventurer, choice1, choice2, choice3, &g, handPos, &bonus);
		assert(g.handCount[player] == orig.handCount[player] + 2);


		int cardDrawn1 = g.hand[player][g.handCount[player] - 1];
		assert(cardDrawn1 == copper || cardDrawn1 == silver || cardDrawn1 == gold);


		int cardDrawn2 = g.hand[player][g.handCount[player] - 2];
		assert(cardDrawn2 == copper || cardDrawn2 == silver || cardDrawn2 == gold);

	}

	printf("%d of %d tests passed\n", numtests - failed, numtests );
}
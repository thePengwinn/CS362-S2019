#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int main(){
    int i, j, k;
    int numTests = 2000;
    srand(time(NULL));
    int failures = 0;
    int cardDrawFails = 0, actionFails = 0;

    struct gameState G;
    int cards[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
    int bonus = 0;
    int numPlayers;

    printf("------ Testing Village...\n");

    for(i = 0; i < numTests; i++){
        numPlayers = (rand() % 3) + 2;
	    memset(&G, 23, sizeof(struct gameState)); 
        initializeGame(numPlayers, cards, 1, &G);

        // give each player a random deck configuration
        for(j = 0; j < numPlayers; j++){
            G.deckCount[j] = floor(Random() * MAX_DECK);
            G.discardCount[j] = 0;
            G.handCount[j] = floor(Random() * MAX_HAND);

            // add random cards to deck
            for(k = 0; k < G.deckCount[j]; k++){
                G.deck[j][k] = rand() % 26 + 1;
            }
        }

        // pick a random player to play the card
        G.whoseTurn = rand() % numPlayers;
        int player = G.whoseTurn;
        G.hand[player][0] = village;

        int originalHand = G.handCount[player];
        int originalActions = G.numActions;

        cardEffect(village, 0, 0, 0, &G, 0, &bonus);

        int postHand = G.handCount[player];
        int postActions = G.numActions;

        if(originalHand != postHand){
            failures++;
            cardDrawFails++;
        }
        if(postActions != (originalActions + 2)){
            failures++;
            actionFails++;
        }
    }
    printf("Failures: %d\n", failures);
    printf("Incorrect cards drawn: %d\n", cardDrawFails);
    printf("Incorrect Addition of Actions: %d\n", actionFails);
    printf("------ End test Village ------\n\n");
    return 0;
}
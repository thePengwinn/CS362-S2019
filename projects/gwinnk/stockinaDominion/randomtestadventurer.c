#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int main(){
    int i, j;
    int numTests = 2000;
    int failures = 0;
    int TreasureNotDrawn = 0;
    srand(time(NULL));

    struct gameState G;
    int cards[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
    int player;                                                         // for player number
    int finalGold = 0, finalSilver = 0, finalCopper = 0;                // totals for coins drawn
    int bonus = 0;

    printf("------ Testing playAdventurer()...\n");

    for(i = 0; i < numTests; i++){
        // start a game
	    memset(&G, 23, sizeof(struct gameState)); 
        initializeGame(4, cards, 1, &G);

        // make counters for coins drawn
        int coppers = 0, postCoppers = 0, silvers = 0, postSilvers = 0, golds = 0, postGolds = 0;

        // make a player with random deck configuration
        player = floor(Random() * MAX_PLAYERS);

        // make sure we have a chance to need the discard pile to shuffle
        j = rand() % 4;
        if(j == 3){
            G.deckCount[player] = rand() % 4;
            G.discardCount[player] = rand() % 15;
            if(G.discardCount[player] < 6){
                G.discardCount[player] = 6;
            }
            for(j = 0; j < G.discardCount[player]; j++){
                if(j < 6){
                    G.discard[player][j] = rand() % 3 + 4;
                }
                else
                    G.discard[player][j] = rand() % 26;
            }
            for(j = 0; j < G.deckCount[player]; j++){
                G.deck[player][j] = rand() % 26;
            }
        }

        // otherwise make sure we have coin cards in the deck
        else{
            G.deckCount[player] = floor(Random() * MAX_DECK);
            if(G.deckCount[player] < 8){
                G.deckCount[player] = 8;
            }
            G.discardCount[player] = rand() % 3;
            for(j = 0; j < G.deckCount[player]; j++){
                if(j < 6){
                    G.deck[player][j] = rand() % 3 + 4;
                }
                else
                    G.deck[player][j] = rand() % 26;
            }
            for(j = 0; j < G.discardCount[player]; j++){
                G.discard[player][j] = rand() % 26;
            }
        }

        // randomize hand
        G.handCount[player] = floor(Random() * MAX_HAND);
        if(G.handCount[player] < 5){
            G.handCount[player] = 5;
        }
        for(j = 1; j < G.handCount[player]; j++){
            G.hand[player][j] = rand() % 26;
        }

        // use our randomized player
        G.whoseTurn = player;
        G.hand[player][0] = adventurer;

        // count treasure
        int PreTreasureCount = 0;
        for(j = 0; j < G.handCount[player]; j++){
            if(G.hand[player][j] == copper || G.hand[player][j] == silver || G.hand[player][j] == gold){
                PreTreasureCount++;
            }
            if(G.hand[player][j] == copper){
                coppers++;
            }
            if(G.hand[player][j] == silver){
                silvers++;
            }
            if(G.hand[player][j] == gold){
                golds++;
            }
        }

        // test the card function itself
        if(cardEffect(adventurer, 0, 0, 0, &G, 0, &bonus) != 0){
            failures++;
        }

        // count treasure after play
        int PostTreasureCount = 0;
        for(j = 0; j < G.handCount[player]; j++){
            if(G.hand[player][j] == copper || G.hand[player][j] == silver || G.hand[player][j] == gold){
                PostTreasureCount++;
            }
            if(G.hand[player][j] == copper){
                postCoppers++;
            }
            if(G.hand[player][j] == silver){
                postSilvers++;
            }
            if(G.hand[player][j] == gold){
                postGolds++;
            }
        }

        // check if 2 were drawn
        if((PreTreasureCount + 2) != (PostTreasureCount)){
            TreasureNotDrawn++;
            failures++;
        }

        // calculate which coins were drawn
        if(golds < postGolds){
            finalGold += (postGolds - golds);
        }
        if(silvers < postSilvers){
            finalSilver += (postSilvers - silvers);
        }
        if(coppers < postCoppers){
            finalCopper += (postCoppers - coppers);
        }
    }

    printf("Test ran %d times.\n", numTests);
    printf("Total failures: %d\n", failures);
    printf("Treasure not drawn correctly: %d\n", TreasureNotDrawn);
    printf("Totals drawn from cardEffet: %d gold, %d silver, %d copper\n", finalGold, finalSilver, finalCopper);
    printf("------ End test Adventurer ------\n\n");
    return 0;
}
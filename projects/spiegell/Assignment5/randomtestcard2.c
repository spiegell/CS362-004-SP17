/*
Village
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

int main()
{
	struct gameState G, testG;
	int kingdomCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
		
	srand(time(NULL));
	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, handPos = 0;
	int p_count = 0;
	int f_count = 0;
	int loopCounter = 0;
	int i = 0;

	int preHandCount = 0, postHandCount = 0;
	int preDeckCount = 0, postDeckCount = 0;
	int preBuyCount = 0, postBuyCount = 0;
	int preActionCount = 0, postActionCount = 0;
	int pre_ECount = 0, pre_DCount = 0, pre_PCount = 0, post_ECount = 0, post_DCount = 0, post_PCount = 0;
	int pre_CCount = 0, pre_SCount = 0, pre_GCount = 0, post_CCount = 0, post_SCount = 0, post_GCount = 0;
	
	

	
	printf(" ..... TESTING CARD: %s .....\n", TESTCARD);
	

	for(loopCounter = 0; loopCounter < 2000; loopCounter++)
	{
		for(i = 0; i < sizeof(struct gameState); i++)
		{
			((char*)&G)[i] = floor(Random() * 256);
		}
		int seed = rand() % 10000;
		int numPlayers = rand() % 3 + 2;
		initializeGame(numPlayers, kingdomCards, seed, &G);
		G.deckCount[numPlayers] = floor(Random() * MAX_DECK);
		G.discardCount[numPlayers] = floor(Random() * MAX_DECK);
		G.handCount[numPlayers] = floor(Random() * MAX_HAND);
		

		memcpy(&testG, &G, sizeof(struct gameState));
		cardEffect(village, choice1, choice2, choice3, &testG, handPos, &bonus);
		// tests
        
		printf("...random tests...\n");

		
		printf("Test 1: Deck Check\n");
		postDeckCount = testG.deckCount[numPlayers];
		preDeckCount = G.deckCount[numPlayers];
		if(postDeckCount == preDeckCount - 1)
		{
			printf("TEST 1.%d.%d: PASS\n", loopCounter, numPlayers);
			p_count++;
		}
		else
		{
			printf("Test 1.%d.%d: FAIL\n", loopCounter, numPlayers);
			f_count++;
		}
        
        printf("Test 2: Hand Check\n");
        postHandCount = testG.handCount[numPlayers];
        preHandCount = G.handCount[numPlayers];
        if(postHandCount == preHandCount + 1)
        {
            printf("TEST 2.%d.%d: PASS\n", loopCounter, numPlayers);
            p_count++;
        }
        else
        {
            printf("Test 2.%d.%d: FAIL\n", loopCounter, numPlayers);
            f_count++;
        }
		
		printf("Test 3: Action Check\n");
		postActionCount = testG.numActions;
		preActionCount = G.numActions;
		if(postActionCount == preActionCount + 2)
		{
			printf("TEST 3.%d.%d: PASS\n", loopCounter, numPlayers);
			p_count++;
		}
		else
		{
			printf("Test 3.%d.%d: FAIL\n", loopCounter, numPlayers);
			f_count++;
		}
		
			
		
	}
	printf("\n");
	printf(.....TESTING of %s COMPLETE.....\n", TESTCARD);
	printf("Tests passed: %d\nTests failed: %d\n", p_count, f_count);
	
	return 0;
}


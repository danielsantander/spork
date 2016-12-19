/**************************************************************************************************/
/*
* File: main.c
* Author: Daniel Santander 
* NetID:
* Date:
*
* Description: Spork program finds nearby and good restaurants/businesses.
*
*/
/**************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "sporkprofile.h"

/**************************************************************************************************/

#define MAX_SPORK_PROFILES 500

/**************************************************************************************************/

int main(int argc, char *argv[]) {

	SporkProfile sporkProfiles[MAX_SPORK_PROFILES];
	int numProfiles = 0;
	int maxSponsorIndex = -1;

	// Usage Check:
	if (argc != 7) 
	{
		printf("Spork program finds nearby and good restaurants/businesses.\n");
		printf("Usage: \n");
		printf("spork inputSporkFile resultsFile userLocX userLocY maxDistMiles minAvgRating\n");
		return EXIT_FAILURE;
	}

	// Read Spork profiles from input file and store the number of profiles created.
	numProfiles = ReadSporkDataFromFile(sporkProfiles, MAX_SPORK_PROFILES, argv[1]);
	if (numProfiles == -1) {
		printf("Could not read input file %s\n", argv[1]);
		return EXIT_FAILURE;
	}

	// FIXME: Convert command line arguments for user's x and y location, maximum distance, and
	// minimum rating to variables userLocX, userLocY, maxDist, and minRating.

	FindNearbyBusinesses(sporkProfiles, numProfiles, *argv[3], *argv[4], *argv[5]);
	FindGoodBusinesses(sporkProfiles, numProfiles, *argv[6]);
	maxSponsorIndex = GetIndexMaxSponsor(sporkProfiles, numProfiles);

	// Write nearby and good Spork profiles to the output file.
	if (WriteSporkResultsToFile(sporkProfiles, numProfiles, maxSponsorIndex, argv[2]) == -1) {
		printf("Could not write output file %s\n", argv[2]);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/**************************************************************************************************/

/**************************************************************************************************/

/*
* File: sporkprofile.c
* Author: Daniel Santander
* NetID:
* Date:
*
* Description: Function definitions for reading, processing, and writing Spork profiles.
*
*/

/**************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sporkprofile.h"

int ReadSporkDataFromFile(SporkProfile sporkProfiles[], int maxProfiles, char *fileName) 
{
	int i = 0;
	int scanResult = 0;
	char lineBuffer[1024];
	FILE* inputFile = NULL;
	inputFile = fopen(fileName, "r");


	if (fileName == NULL){
		printf("Error opening file %c\n", fileName);
		return -1;
	}

	/* WHILE LOOP for reading in file text */
	while (!feof(inputFile) && i < maxProfiles){

		//gets inputFile puts into a char buffer
		fgets(lineBuffer, 1024, inputFile);

		//finds scanResult number and parses the business info from the lineBuffer:
		scanResult = sscanf(lineBuffer, "%s %lf %lf %lf %d", sporkProfiles[i].businessName, &sporkProfiles[i].locX, &sporkProfiles[i].locY, &sporkProfiles[i].avgRating, &sporkProfiles[i].adLevel);

		//Initializing
		sporkProfiles[i].isNearby = false;
		sporkProfiles[i].isGood = false;
		sporkProfiles[i].distMiles = 0.0;

		i++;	// increment index
	}
	return i;	// return index
}

/**************************************************************************************************/

void FindNearbyBusinesses(SporkProfile sporkProfiles[], int numProfiles, double userLocX, double userLocY, double maxDist)
{
	int i = 0;
	double EuclideanDistance = 0.0;

	//iterates through sporkProfiles of profiles
	for (i = 0; i < numProfiles; i++){

		//Euclidean Distance formula to calculate distMiles value:
		sporkProfiles[i].distMiles = sqrt(((userLocX - sporkProfiles[i].locX)*(userLocX - sporkProfiles[i].locX)) + ((userLocY - sporkProfiles[i].locY)*(userLocY - sporkProfiles[i].locY)));

		//checks if the distance calculated is less than or equal to the user max distance (sets isNearby to TRUE/FALSE)
		if (sporkProfiles[i].distMiles <= maxDist){
			sporkProfiles[i].isNearby = true;
		}
		else{
			sporkProfiles[i].isNearby = false;
		}

	}
}

/**************************************************************************************************/

void FindGoodBusinesses(SporkProfile sporkProfiles[], int numProfiles, double minRating)
{
	int i = 0;
	for (i = 0; i < numProfiles; i++)
	{
		//checks if average rating is less than or equal to user min rating
		if (sporkProfiles[i].avgRating >= minRating){
			sporkProfiles[i].isGood = true;
		}
		else{
			sporkProfiles[i].isGood = false;
		}
	}
}

/**************************************************************************************************/

int GetIndexMaxSponsor(SporkProfile sporkProfiles[], int numProfiles) 
{
	int i = 0;
	int highestAdIndex = 0;
	bool hasFoundHighest = false;	// used to determine if there is a highest advertising level is found

	//Interate through the profiles:
	for (i = 0; i < numProfiles; i++)
	{
		//checks if the profile is good AND nearby
		if (sporkProfiles[i].isGood && sporkProfiles[i].isNearby)
		{
			//if the adLevel of the current business is higher than the currently highestAdLev, then replace.highestAdLev with the index of that profile
			if (sporkProfiles[i].adLevel > sporkProfiles[highestAdIndex].adLevel)
			{
				hasFoundHighest == true;	// a hihest ad level has been found
				highestAdIndex = i;			// set the new highest index
			}
		}
	}

	if (hasFoundHighest)
	{
		return highestAdIndex;	//return the index of the busniess found
	}
	return -1;					// else return -1
}

/**************************************************************************************************/

int WriteSporkResultsToFile(SporkProfile sporkProfiles[], int numProfiles, int maxSponsorIndex, char *fileName) {

	//if output file could not be opended, return -1:
	if (fileName == NULL)
	{
		printf("Output file count not be opened");
		return -1;
	}

	int i = 0;
	FILE* outFile = NULL;
	outFile = fopen(fileName, "w");

	//outputting maxSponsor first:
	if (maxSponsorIndex != -1){
		fprintf(outFile, "%s\t%.2lf\t%.2lf\n", sporkProfiles[maxSponsorIndex].businessName, sporkProfiles[maxSponsorIndex].avgRating, sporkProfiles[maxSponsorIndex].distMiles);

		//Print the rest of the profiles:
		for (i = 0; i < numProfiles; i++)
		{
			if (i != maxSponsorIndex)
			{
				fprintf(outFile, "%s\t%.2lf\t%.2lf\n", sporkProfiles[i].businessName, sporkProfiles[i].avgRating, sporkProfiles[i].distMiles);
			}
		}
	}

	//else if maxSponsor index IS -1, print everything in order:
	else
	{
		for (i = 0; i < numProfiles; i++)
		{
			//print the business info:
			fprintf(outFile, "%s\t%.2lf\t%.2lf\n", sporkProfiles[i].businessName, sporkProfiles[i].avgRating, sporkProfiles[i].distMiles);
		}
	}
	return 0;
}
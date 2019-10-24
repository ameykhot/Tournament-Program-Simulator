#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tournament.h"

//This fucntion scan given file and divide team into respective team structure
Player *draftPlayers(char *filename, int team, int num_players)
{
    //File pointer to access files
    FILE *filePointer;

    //This will open file in reading and writing mode
    filePointer = fopen(filename, "rb+");

    //This character array will store each line from file
    char lineBuffer[200];

    //Creating instance of player structure
    Player *playersArray;
    Player *teamWisePlayersArray;

    int indexForPlayerArray = 0;
    int indexForTeamWisePlayerArray = 0;
    int statusOfFile = 0;

    //Assign size to player structures
    playersArray = malloc(320 * sizeof(Player));
    teamWisePlayersArray = malloc(num_players * sizeof(Player));

    //This will continue untill it reaches end of line
    while (statusOfFile != EOF)
    {
        //fgets will scan file line by line
        if (fgets(lineBuffer, sizeof(lineBuffer), filePointer))
        {
            //as firstNameOfPlayer and lastNameOfPlayer are pointers  we need to allocate memory to them
            playersArray[indexForPlayerArray].firstNameOfPlayer = malloc(100);
            playersArray[indexForPlayerArray].lastNameOfPlayer = malloc(150);

            //use %[^,\n] to avoid commas from line
            statusOfFile = sscanf(
                lineBuffer, "%d, %[^,],%[^,], %d, %d,%d",
                &playersArray[indexForPlayerArray].teamNumber,
                playersArray[indexForPlayerArray].firstNameOfPlayer,
                playersArray[indexForPlayerArray].lastNameOfPlayer,
                &playersArray[indexForPlayerArray].jerseyNumber,
                &playersArray[indexForPlayerArray].playerOffensiveRating,
                &playersArray[indexForPlayerArray].playerDefensiveRating);

            //Check the team name to club players with same team
            if (playersArray[indexForPlayerArray].teamNumber == team)
            {
                //Stored each value of players in new player array
                teamWisePlayersArray[indexForTeamWisePlayerArray].teamNumber = playersArray[indexForPlayerArray].teamNumber;
                teamWisePlayersArray[indexForTeamWisePlayerArray].firstNameOfPlayer = playersArray[indexForPlayerArray].firstNameOfPlayer;
                teamWisePlayersArray[indexForTeamWisePlayerArray].lastNameOfPlayer = playersArray[indexForPlayerArray].lastNameOfPlayer;
                teamWisePlayersArray[indexForTeamWisePlayerArray].jerseyNumber = playersArray[indexForPlayerArray].jerseyNumber;
                teamWisePlayersArray[indexForTeamWisePlayerArray].playerOffensiveRating = playersArray[indexForPlayerArray].playerOffensiveRating;
                teamWisePlayersArray[indexForTeamWisePlayerArray].playerDefensiveRating = playersArray[indexForPlayerArray].playerDefensiveRating;
                //increment indexForTeamWisePlayerArray to point to next postion for new team
                indexForTeamWisePlayerArray++;
            }
            //increment indexForPlayerArray to point to next postion for new team
            indexForPlayerArray++;
        }
        else
        {
            //break is importent otherwise while loop will go into infinite loop
            break;
        }
    }
    //Close file after
    fclose(filePointer);
    return teamWisePlayersArray;
}

Team *initializeTeam(char *name, Player *players)
{
    //Created team instance also assign size of team
    Team *newTeamObject = malloc(sizeof(Team));

    //Assign team name and player array to team instance
    newTeamObject->teamName = name;
    newTeamObject->structureArrayOfPlayers = players;

    return newTeamObject;
}

//This function will calculate score for offense team
int calculateScore(int offenseratingOfTeam, int defenseRatingOfTeam)
{
    int teamScore = 0;

    //This loop created because each team has 10 players and each player should have chance to score goal or not
    for (int inderForEachPlayer = 0; inderForEachPlayer < 10; inderForEachPlayer++)
    {
        //rand() function used to generate random value from 0 to total offense value
        if (rand() % offenseratingOfTeam > rand() % defenseRatingOfTeam)
        {
            teamScore++;
        }
    }
    return teamScore;
}

//This function will calculate offense of the team
int calculateOffense(Team *team)
{
    int teamsTotalOffense = 0;
    for (int indexforPlayersOffenseRating = 0; indexforPlayersOffenseRating < NUM_PLAYERS; indexforPlayersOffenseRating++)
    {
        teamsTotalOffense = teamsTotalOffense + team->structureArrayOfPlayers[indexforPlayersOffenseRating].playerOffensiveRating;
    }
    team->structureArrayOfPlayers[0].playerOffensiveRating;

    return teamsTotalOffense;
}
//This function will calculate defense of the team
int calculateDefense(Team *team)
{
    int teamsTotalDefense = 0;
    for (int indexforPlayersDefenseRating = 0; indexforPlayersDefenseRating < NUM_PLAYERS; indexforPlayersDefenseRating++)
    {
        teamsTotalDefense = teamsTotalDefense + team->structureArrayOfPlayers[indexforPlayersDefenseRating].playerDefensiveRating;
    }

    return teamsTotalDefense;
}

//this function takes two teams and decide whose win depending upon team score
Team *game(Team *team1, Team *team2)
{

    int totalOffenseOfTeam1 = 0;
    int totalDefenseOfTeam1 = 0;
    int team1Score = 0;

    int totalOffenseOfTeam2 = 0;
    int totalDefenseOfTeam2 = 0;
    int team2Score = 0;

    //NULL check for teams
    if (team1 == NULL && team2 == NULL)
    {
        return NULL;
    }
    else
    {

        totalOffenseOfTeam1 = calculateOffense(team1);
        totalDefenseOfTeam1 = calculateDefense(team1);

        totalOffenseOfTeam2 = calculateOffense(team2);
        totalDefenseOfTeam2 = calculateDefense(team2);

        //it will calculate team 1 score
        team1Score = calculateScore(totalOffenseOfTeam1, totalDefenseOfTeam2);
        //it will calculate team 2 score
        team2Score = calculateScore(totalOffenseOfTeam2, totalDefenseOfTeam1);

        if (team1Score > team2Score)
        {
            return team1;
        }
        else
        {
            return team2;
        }
    }
}

Team *tournament(Team **league, int totalTeams)
{

    int i = 0, j = 0;

    Team **winnerTeams = malloc(sizeof(Team *) * totalTeams);

    int teams = totalTeams;

    //checks whether a total team is in multiple of two or not
    if (totalTeams == 0)
        return NULL;

    //true till x is not equal to 1
    while (totalTeams != 1)
    {
        //checks whether a number is divisible by 2
        if (totalTeams % 2 != 0)
            return NULL;
        totalTeams /= 2;
    }

    //if team size is 2 then final round begins from here
    if (teams == 2)
    {
        //final round begins here and return winning team
        return game(league[0], league[1]);
    }

    // this loop run until it has found winner
    for (i = 0, j = teams / 2; i < teams / 2, j < teams; i++, j++)
    {
        winnerTeams[i] = game(league[i], league[j]);
    }

    teams = teams / 2;
    //recursive call to get the final winner
    return tournament(winnerTeams, teams);
}

void deleteTeam(Team *team)
{
    free(team);
    team = NULL;
}

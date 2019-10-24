#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#ifndef TOURNAMENT
#define TOURNAMENT

#define NUM_TEAMS 32
#define NUM_PLAYERS 10

//Created structure for Players
typedef struct Player
{
    int teamNumber;
    char *firstNameOfPlayer;
    char *lastNameOfPlayer;
    int jerseyNumber;
    int playerOffensiveRating;
    int playerDefensiveRating;
} Player;

//Structure for Creating teams and array of players
typedef struct Team
{
    char *teamName;
    struct Player *structureArrayOfPlayers;
} Team;

int inLeague(Team *, Team **);
void deleteTeam(Team *);
Player *draftPlayers(char *filename, int team, int num_players);
Team *initializeTeam(char *name, Player *players);
int calculateScore(int offense, int defense);
int calculateOffense(Team *team);
int calculateDefense(Team *team);
Team *game(Team *team1, Team *team2);
Team *tournament(Team **league, int totalTeams);
#endif

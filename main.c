#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "tournament.h"

#define DEBUG 0
#define NUM_TEAMS 32
#define NUM_PLAYERS 10
#define NUM_SEASONS 25

int inleagueOfTeams(Team *, Team **);

int main()
{
    /*****  Change the team names to names of your choosing ******/
    char *teamNames[] = {
        "team1",
        "team2",
        "team3",
        "team4",
        "team5",
        "team6",
        "team7",
        "team8",
        "team9",
        "team10",
        "team11",
        "team12",
        "team13",
        "team14",
        "team15",
        "team16",
        "team17",
        "team18",
        "team19",
        "team20",
        "team21",
        "team22",
        "team23",
        "team24",
        "team25",
        "team25",
        "team27",
        "team28",
        "team29",
        "team30",
        "team31",
        "team32",
    };

#if !DEBUG
    fclose(stderr);
#endif
    printf("\t-----------------------------------\n");
    printf("\t-   Part1 : Creating Your League  -\n");
    printf("\t-----------------------------------\n");
    srand(time(NULL));

    printf("\n\t=========Test #1: Creating your Teams and Players===========\n\n");
    Team **leagueOfTeams = malloc(sizeof(Team *) * NUM_TEAMS);
    //create teams i.e. league of N teams.
    for (int counter = 0; counter < NUM_TEAMS; counter++)
    {
        Player *draftedPlayersArray = draftPlayers("players.dat", counter, NUM_PLAYERS);
        assert(draftedPlayersArray[0].teamNumber == counter % NUM_TEAMS);
        leagueOfTeams[counter] = initializeTeam(teamNames[counter], draftedPlayersArray);
        assert(sizeof((leagueOfTeams[counter]->structureArrayOfPlayers[rand() % NUM_PLAYERS])) == sizeof(Player));
        assert((leagueOfTeams[counter]->structureArrayOfPlayers[rand() % NUM_PLAYERS]).playerOffensiveRating > 0);
        assert((leagueOfTeams[counter]->structureArrayOfPlayers[rand() % NUM_PLAYERS]).playerDefensiveRating > 0);
        assert(sizeof(*(leagueOfTeams[counter])) == sizeof(Team));
    }
    printf("\n\t\t....Test Passed\n");

    printf("\t-----------------------------------\n");
    printf("\t-   Part2 : Exhibition Games      -\n");
    printf("\t-----------------------------------\n");

    printf("\n\t=========Test #2: Sanity check for the game===========\n\n");

    Team *winningTeam = game(NULL, NULL);
    assert(winningTeam == NULL);
    printf("\n\t\t....Test Passed\n");

    printf("\n\t=========Test #3: Playing a Game between two random teams===========\n\n");
    Team *team1 = leagueOfTeams[rand() % NUM_TEAMS];
    Team *team2 = leagueOfTeams[rand() % NUM_TEAMS];
    printf("Up next, an exhibition game between %s and %s\n", team1->teamName, team2->teamName);
    winningTeam = game(team1, team2);
    assert(winningTeam == team1 || winningTeam == team2);
    printf("The winning team is %s\n\n", winningTeam->teamName);
    printf("\n\t\t....Test Passed\n");

    printf("\n\t=========Test #4: Playing a Game between the same team===========\n\n");
    int team_num = rand() % NUM_TEAMS;
    printf("Up next, a a scrimmage for %s\n", leagueOfTeams[team_num]->teamName);
    winningTeam = game(leagueOfTeams[team_num], leagueOfTeams[team_num]);
    assert(winningTeam == leagueOfTeams[team_num]);
    printf("The winning team is %s\n\n", winningTeam->teamName);
    printf("\n\t\t....Test Passed\n");

    printf("\t-----------------------------------\n");
    printf("\t-   Part3 : Running a Tournament  -\n");
    printf("\t-----------------------------------\n");
    printf("\n\t=========Test #5: Ensure number of teams is a power of 2===========\n\n");
    winningTeam = tournament(leagueOfTeams, 20);
    assert(winningTeam == NULL);
    printf("\n\t\t....Test Passed\n");

    printf("\n\t=========Test #6: Should result in a single winningTeam===========\n\n");
    winningTeam = tournament(leagueOfTeams, NUM_TEAMS);
    assert(inleagueOfTeams(winningTeam, leagueOfTeams));
    printf("\n************************ Result *******************************\n\n");
    printf("The winning team is %s\n\n", winningTeam->teamName);
    printf("\n\t\t....Test Passed\n");

    printf("\n\t=========Test #7: Should result in a random winningTeam===========\n\n");
    Team *winningTeams[NUM_SEASONS];
    for (int counter = 0; counter < NUM_SEASONS; counter++)
    {
        winningTeams[counter] = tournament(leagueOfTeams, NUM_TEAMS);
        printf("winningTeam is %s\n", winningTeams[counter]->teamName);
        assert(inleagueOfTeams(winningTeams[counter], leagueOfTeams));
    }
    Team *randomness_test = winningTeams[0];
    int is_random = 0;
    for (int counter = 1; counter < NUM_SEASONS; counter++)
    {
        if (randomness_test != winningTeams[counter])
        {
            is_random = 1;
        }
    }
    assert(is_random);
    printf("\n\t\t....Test Passed\n");

    printf("\n\t=========Test #8: Delete team method should clean up memory for each team ===========\n\n");
    //free team array.
    for (int counter = 0; counter < NUM_TEAMS; counter++)
    {
        deleteTeam(leagueOfTeams[counter]);
    }
    free(leagueOfTeams);

    printf("\n\t=========All Tests Passed. Don't forget to check Valgrind!===========\n\n");

    return 0;
}

int inleagueOfTeams(Team *testTeamName, Team **leagueOfTeamsArrayOfTeam)
{
    int i = 0;
    for (; i < NUM_TEAMS; i++)
    {
        if (leagueOfTeamsArrayOfTeam[i] == testTeamName)
        {
            return 1;
        }
    }
    return 0;
}

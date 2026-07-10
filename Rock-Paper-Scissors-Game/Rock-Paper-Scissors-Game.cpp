#include <iostream>
#include <cstdlib>

using namespace std;

enum enGameChoice { Paper = 1, Ston = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName = "";
};

struct stGameResults
{
    short GameRounds = 0;
    short Player1WinTimes;
    short ComputerWinTimes;
    short DrawTimes;
    enWinner GameWinner;
    string WinnerName = "";
};

short RandomNumber(short From, short To)
{
    // Function to generate Random Number 

    int RandomNum = rand() % (To - From + 1) + From;

    return RandomNum;
}

enGameChoice ReadPlayer1Choice()
{
    short Choice;

    do
    {
        cout << "Your choice: [1]:Paoer, [2]:Ston, [3]:Scissors ? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);

    return (enGameChoice)Choice;
}

enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
    {
        return enWinner::Draw;
    }

    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Ston:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Ston)
        {
            return enWinner::Computer;
        }
        break;
    }

    //if you reach here thene Player1 is Winner
    return enWinner::Player1;
}

string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "Player1", "Computer", "No Winner" };
    return arrWinnerName[Winner - 1];
}

string ChoiceName(enGameChoice Choice)
{
    string arrGameChoice[3] = { "Paper", "Ston", "Scissors" };
    return arrGameChoice[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player1:
        system("color 2F"); // turn screen to Green
        break;
    case enWinner::Computer:
        system("color 4F"); // turn screen to Red
        cout << "\a";
        break;
    default:
        system("color 6F"); // turn screen to Yellow
        break;
    }
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
    cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player1 Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
    cout << "_________________________________________\n" << endl;

    SetWinnerScreenColor(RoundInfo.Winner);
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes)
        return enWinner::Player1;
    else if (ComputerWinTimes > Player1WinTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

stGameResults FillGameResults(short GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
    stGameResults GameResults;

    GameResults.GameRounds = GameRounds;
    GameResults.Player1WinTimes = Player1WinTimes;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}

stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins\n\n";

        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        //Increase Win/Draw Counters

        if (RoundInfo.Winner == enWinner::Player1)
            Player1WinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;


        /*if (RoundInfo.Winner > RoundInfo.Winner)
            Player1WinTimes++;
        else if (RoundInfo.Winner > RoundInfo.Winner)
            ComputerWinTimes++;
        else
            DrawTimes++;*/

        PrintRoundResult(RoundInfo);
    }

    return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

string Tabs(short NumberOfTabs)
{
    string t = "";
    for (short i = 1; i <= NumberOfTabs; i++)
    {
        t += "\t";
        //cout << t;
    }

    return t;
}

void ShowGameOverScreen()
{
    cout << Tabs(2) << " -----------------------------------------\n\n";
    cout << Tabs(2) << " +++ G A M E O V E R +++ \n";
    cout << Tabs(2) << " -----------------------------------------\n\n";
}

void ShowFinalGameResults(stGameResults GameResults)
{
    cout << Tabs(2) << " ---------------------- [ Game Results ] --------------------\n\n";

    cout << Tabs(2) << "Game Rounds : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player1 Win times : " << GameResults.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer Win times : " << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw times : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner : " << GameResults.WinnerName << endl;

    cout << Tabs(2) << "-----------------------------------------------------\n";

    //SetWinnerScreenColor(GameResults.GameWinner);
}

short ReadHowManyRound()
{
    short Number = 1;

    do
    {
        cout << "How Many Rounds 1 To 10? \n";
        cin >> Number;

    } while (Number < 1 || Number > 10);

    return Number;
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRound());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);

        cout << Tabs(2) << "Do you want to play again? Y/N?";
        cin >> PlayAgain;

    } while (PlayAgain == 'y' || PlayAgain == 'Y');

}

int main()
{
    // Seeds the random number generator in C++, Called only once.
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}

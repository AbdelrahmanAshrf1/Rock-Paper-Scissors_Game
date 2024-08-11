#include <iostream>
#include <cstdlib>

using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissor = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;

};

struct stGameResult
{
	short GameRounds = 0;
	short Player1WinTimes = 0;
	short Computer2WinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};

short RandomNumber(short From , short To)
{
	short RandomNumber = rand() % (To - From + 1) + From;
	return RandomNumber;
}

string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player1","Computer","No Winner" };
	return arrWinnerName[Winner - 1];
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.PlayerChoice)
	{
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissor)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Scissor:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
		{
			return enWinner::Computer;
		}
		break;
	}

	// if you reach here then Player1 is winner 
	return enWinner::Player1;
}

string ChoiceNmae(enGameChoice Choice)
{
	string arrGameChoice[3] = { "Stone","Paper","Scissor" };
	return arrGameChoice[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player1:
		system("color 2F");
		break;

	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;

	case enWinner::Draw:
		system("color 6F");
		break;
	}
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
	cout << "\n____________Round [ " << RoundInfo.RoundNumber << "]____________\n\n";
	cout << "Player1 Choice : " << ChoiceNmae(RoundInfo.PlayerChoice) << endl;
	cout << "Computer Choice: " << ChoiceNmae(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner   : [" << RoundInfo.WinnerName << "]" << endl;
	cout << "__________________________________\n";

	SetWinnerScreenColor(RoundInfo.Winner);
}

short ReadHowManyRounds()
{
	short GameRounds = 1;

	do
	{
		cout << "How many Rounds 1 to 10 ? \n";
		cin >> GameRounds;

	} while (GameRounds < 1 || GameRounds > 10);

	return GameRounds;
}

enGameChoice ReadPlayer1Choice()
{
	short Choice = 1;

	do
	{
		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissor ?";
		cin >> Choice;
	} while (Choice < 1 || Choice > 3);

	return (enGameChoice)Choice;
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice) RandomNumber(1, 3);
}

enWinner WhoWonTheGame(short Player1WinTimes, short Computer2WinTimes)
{
	if (Player1WinTimes > Computer2WinTimes)
		return enWinner::Player1;
	else if (Player1WinTimes < Computer2WinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;

}

stGameResult FillGameResults(short GameRounds, short Player1WinTimes, short Computer2WinTimes , short DrawTimes)
{
	stGameResult GameResult;

	GameResult.GameRounds = GameRounds;
	GameResult.Player1WinTimes = Player1WinTimes;
	GameResult.Computer2WinTimes = Computer2WinTimes;
	GameResult.DrawTimes = DrawTimes;
	GameResult.GameWinner = WhoWonTheGame(Player1WinTimes, Computer2WinTimes);
	GameResult.WinnerName = WinnerName(GameResult.GameWinner);

	return GameResult;
}

stGameResult PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short Player1WinTimes = 0, Computer2WinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins:\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		// Increase Win / Draw counters
		if (RoundInfo.Winner == enWinner::Player1)
			Player1WinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			Computer2WinTimes++;
		else
			DrawTimes++;

		PrintRoundResult(RoundInfo);
	}
	return FillGameResults(HowManyRounds, Player1WinTimes, Computer2WinTimes, DrawTimes);
}

string Tabs(short NumberOfTabs)
{
	string t = "";

	for (int i = 1; i < NumberOfTabs; i++)
	{
		t += "\t";
	}
	return t;
}

void ShowGameOverScreen()
{
	cout << Tabs(2) << "_________________________________________________________________\n\n";
	cout << Tabs(2) << "                  +++G a m e  O v e r+++\n";
	cout << Tabs(2) << "_________________________________________________________________\n\n";
}

void ShowFinalGameResults(stGameResult GameResults)
{
	cout << Tabs(2) << "___________________________[Game Results ]_______________________\n\n";
	cout << Tabs(2) << "Gmae Rounds             : " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Player1 Won Times       : " << GameResults.Player1WinTimes << endl;
	cout << Tabs(2) << "Computer Won Times      : " << GameResults.Computer2WinTimes << endl;
	cout << Tabs(2) << "Draw Times              : " << GameResults.DrawTimes<< endl;
	cout << Tabs(2) << "Final Winner            : " << GameResults.WinnerName << endl;
	cout << Tabs(2) << "_________________________________________________________________\n\n";
}

void RestScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		RestScreen();
		stGameResult GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);

		cout << endl << Tabs(3) << "Do you want to play again? Y/N ?";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}
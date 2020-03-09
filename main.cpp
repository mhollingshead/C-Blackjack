#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "blackjack.h"

using namespace std;

int main()
{
  cout << "\nWelcome to the Comp322 Blackjack game!\n";

  BlackJackGame game;

  // The main loop of the game
  bool playAgain = true;
  char answer = 'y';
  while (playAgain)
  {
    game.play();

    // Check whether the player would like to play another round
    cout << "Would you like another round? (y/n):";
    cin >> answer;
    playAgain = (answer == 'y' ? true : false);
  }

  cout <<"Gave over!\n\n";

  return 0;
}

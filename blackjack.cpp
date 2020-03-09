#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "blackjack.h"

using namespace std;

Card::Card(Rank r, Suit s) {
  this->rank = r;
  this->suit = s;
}

int Card::getValue() {
  //get the integer value of the rank and return it
  int value = rank;

  //make sure all of the face cards are equal to 10
  if (value > 10) {
    value = value - (value % 10);
  }

  return value;
}

void Card::displayCard() {
  //if the card is a face card, display the first letter of the rank
  if (rank == JACK) {
    std::cout << 'J';
  }
  else if (rank == QUEEN) {
    std::cout << 'Q';
  }
  else if (rank == KING) {
    std::cout << 'K';
  }
  //else if the card is a number, display that number
  else {
    int value = rank;
    std::cout << rank;
  }

  //display the first letter of the suit
  if (suit == CLUBS) {
    std::cout << 'C';
  }
  else if (suit == DIAMONDS) {
    std::cout << 'D';
  }
  else if (suit == HEARTS) {
    std::cout << 'H';
  }
  else {
    std::cout << 'S';
  }

  std::cout << ' ';
}

void Hand::add(Card c) {
  hand.push_back(c);
}

//clear the hand
void Hand::clear() {
  hand.clear();
}

//display all of the cards in the hand
void Hand::displayHand() {
  for (int i = 0; i < hand.size(); i++){
    hand.at(i).displayCard();
  }
}

//display all of the cards in the hand except for the first
void Hand::displayCasinoHand() {
  for (int i = 1; i < hand.size(); i++){
    hand.at(i).displayCard();
  }
}

int Hand::getHandValue() {
  int value = 0;
  bool hasAce = false;

  //add the card value at i to the total value of the hand
  for (int i = 0; i < hand.size(); i++){
    value += hand.at(i).getValue();

    //if the card at i is an ace, set hasAce to true
    if (hand.at(i).getValue() == 1) {
      hasAce = true;
    }
  }

  //if the hand has an ace, check to see if an 11 would bust over a 1
  if (hasAce) {
    if (value <= 11) {
      //if the hand wouldn't bust, the ace should be an 11
      value += 10;
    }
    //otherwise ace should stay a 1
  }
  return value;
}

//get the value that should be displayed next to the casino hand
int Hand::getCasinoHandValue() {
  int value = 0;
  bool hasAce = false;
  bool aceHigh = false;

  //same as regular get hand value
  for (int i = 0; i < hand.size(); i++){
    value += hand.at(i).getValue();

    if (hand.at(i).getValue() == 1) {
      hasAce = true;
    }
  }

  if (hasAce) {
    if (value <= 11) {
      value += 10;
      aceHigh = true;
    }
  }

  //subtract the first card
  if (aceHigh && hand.at(0).getValue() == 1) {
    value -= 11;
  }
  else {
    value -= hand.at(0).getValue();
  }

  return value;
}

Deck::Deck() {
  Populate();
}

void Deck::Populate() {
  //empty the deck if there are already cards in it
  deck.clear();

  //iterate through suits, then ranks and push the card to the deck
  for (int i = 0; i < 4; i++) {
    for (int j = 1; j <= 13; j++) {
      Card c = Card((Rank)j, (Suit)i);
      deck.push_back(c);
    }
  }
}

//shuffles the deck by performing a faro shuffle, then cutting the deck randomly
//a little pointless and unnecessarily long but I thought it would be fun to
//shuffle like a real deck of cards
void Deck::shuffle() {
  //do the shuffle 7 times
  for (int i = 0; i < 7; i++) {
    //cut the deck in half
    vector<Card> h1 = split(deck, 0, (deck.size()/2));
    vector<Card> h2 = split(deck, (deck.size()/2), 52);
    vector<Card> newDeck;

    //faro shuffle
    int j;
    for (j = 0; j < h1.size(); j++) {
      newDeck.push_back(h1.at(j));
      newDeck.push_back(h2.at(j));
    }

    //cut the deck in a random place between 4 and 48
    int randomCut = rand()%(48-4+1)+4;

    h1 = split(newDeck, 0, randomCut);
    h2 = split(newDeck, randomCut, 52);
    newDeck.clear();

    //put the bottom stack on top to complete the cut
    for (j = 0; j < h2.size(); j++) {
      newDeck.push_back(h2.at(j));
    }
    for (j = 0; j < h1.size(); j++) {
      newDeck.push_back(h1.at(j));
    }

    deck = newDeck;
  }
}

//pop a card from the deck and add it to the specified hand
void Deck::deal(Hand &h) {
  h.add(deck.back());
  deck.pop_back();
}

//helper method to split a vector into a subvector to cut the deck
vector<Card> Deck::split(vector<Card> d, int start, int end) {
  vector<Card> subVector;

  for (int i = start; i < end; i++) {
    subVector.push_back(d.at(i));
  }

  return subVector;
}

bool AbstractPlayer::isBusted(string name) {
  if (hand.getHandValue() > 21) {
    cout << name << " busts. ";
    return true;
  }
  else {
    return false;
  }
}

bool HumanPlayer::isDrawing() {
  char ans;

  //make sure the response is either 'y' or 'n'
  while (!(ans == 'y' || ans == 'n')) {
    std::cout << "Do you want to draw? (y/n):";
    std::cin >> ans;
    if (ans == 'y') {
      return true;
    }
    //if response not recognized, ask again
    if (!(ans == 'n')) {
      std::cout << "Response not recognized. ";
    }
  }
  return false;
}

void HumanPlayer::announce(string winner) {
  if (winner == "player") {
    std::cout << "Player wins.\n\n";
  }
  else if (winner == "casino") {
    std::cout << "Casino wins.\n\n";
  }
  else {
    std::cout << "Push: No one wins.\n\n";
  }
}

bool ComputerPlayer::isDrawing() {
  if (hand.getHandValue() <= 16) {
    return true;
  }
  else {
    return false;
  }
}

void ComputerPlayer::announce(string winner) {}

void BlackJackGame::play() {
  //seed rand() for Deck::shuffle() to get random values within the loop
  srand(time(NULL));

  //initialize players
  AbstractPlayer *player;
  player = new HumanPlayer();
  m_casino = new ComputerPlayer();

  //initialize game variables
  string winner;
  bool drawing;

  //fill and shuffle the deck
  m_deck = Deck();
  m_deck.shuffle();

  //deal two cards to each player
  m_deck.deal(player->hand); m_deck.deal(player->hand);
  m_deck.deal(m_casino->hand); m_deck.deal(m_casino->hand);

  //print both hands
  std::cout << "\nCasino: ";
  m_casino->hand.displayCasinoHand();
  std::cout << "[" << m_casino->hand.getCasinoHandValue() << "]\n";

  std::cout << "Player: ";
  player->hand.displayHand();
  std::cout << "[" << player->hand.getHandValue() << "]\n";

  //see if player wants to draw
  drawing = player->isDrawing();

  //if they do, continue drawing until they want to stop
  while (drawing) {
    //deal a card
    m_deck.deal(player->hand);

    //display the hand
    std::cout << "Player: ";
    player->hand.displayHand();
    std::cout << "[" << player->hand.getHandValue() << "]\n";

    //if player busts, announce winner and return
    if (player->isBusted("Player")) {
      winner = "casino";
      player->announce(winner);
      return;
    }

    //see if player wants to continue drawing
    drawing = player->isDrawing();
  }

  //display players final hand
  std::cout << "Player: ";
  player->hand.displayHand();
  std::cout << "[" << player->hand.getHandValue() << "]\n";

  //see if casino wants to draw
  drawing = m_casino->isDrawing();

  //if they do, continue drawing until they want to stop
  while (drawing) {

    //deal a card
    m_deck.deal(m_casino->hand);

    //display the casino's hand
    std::cout << "Casino: ";
    m_casino->hand.displayCasinoHand();
    std::cout << "[" << m_casino->hand.getCasinoHandValue() << "]\n";

    //if casino busts, announce winner and return
    if (m_casino->isBusted("Casino")) {
      winner = "player";
      player->announce(winner);
      return;
    }

    //see if casino wants to keep drawing
    drawing = m_casino->isDrawing();
  }

  //showdown
  std::cout << "Casino: ";
  m_casino->hand.displayHand();
  std::cout << "[" << m_casino->hand.getHandValue() << "]\n";

  //check who wins and announce the winner
  if (player->hand.getHandValue() > m_casino->hand.getHandValue()) {
    winner = "player";
    player->announce(winner);
    return;
  }
  else if (player->hand.getHandValue() < m_casino->hand.getHandValue()) {
    winner = "casino";
    player->announce(winner);
    return;
  }
  else {
    winner = "draw";
    player->announce(winner);
    return;
  }
}

enum Rank {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
enum Suit {CLUBS, DIAMONDS, HEARTS, SPADES};

class Card {
public:
  /**
   * Card object constructor
   *
   * @param Rank r rank of the card
   * @param Suit s suit of the card
   */
  Card(Rank r, Suit s);

  /**
   * Returns the numerical value of a card
   *
   * @return int value
   */
  int getValue();

  /**
   * Prints the card in the proper format
   */
  void displayCard();

protected:
  Rank rank;
  Suit suit;
};

class Hand {
public:
  /**
   * Adds a card to the hand
   *
   * @param Card c card to be added
   */
  void add(Card c);

  /**
   * Clears all of the cards in a hand
   */
  void clear();

  /**
   * Prints all of the cards in a hand
   */
  void displayHand();

  /**
   * Prints all of the cards in a hand except
   * for the first one
   */
  void displayCasinoHand();

  /**
   * Returns the full numerical value of a hand
   *
   * @return int value
   */
  int getHandValue();

  /**
   * Returns the numerical value of a hand except
   * for the first one
   *
   * @return int value
   */
  int getCasinoHandValue();

protected:
  std::vector<Card> hand;
};

class Deck {
public:

  /**
   * Deck object constructor
   * Initializes a populated deck
   */
  Deck();

  /**
   * Populates a deck with all 52 cards
   */
  void Populate();

  /**
   * Shuffles a deck using a custom shuffle method
   *
   * Performs a perfect faro shuffle, then cuts the
   * deck at a random location and repeats 7 times
   */
  void shuffle();

  /**
   * Deals the card at the top of the deck to a hand
   *
   * @param Hand &h reference to a Hand object
   */
  void deal(Hand &h);

  /**
   * Splits a vector into a subvector of the given range
   *
   * @param vector<Card> d the deck to be split
   * @param int start index the subvector should start at
   * @param int end index the subvecor should end at
   * @return vector<Card> subvector
   */
  std::vector<Card> split(std::vector<Card> d, int start, int end);

protected:
  std::vector<Card> deck;
};

class AbstractPlayer {
public:
  /**
   * Pure virtual method isDrawing()
   */
  virtual bool isDrawing() = 0;

  /**
   * Pure virtual method announce()
   */
  virtual void announce(std::string winner) = 0;

  /**
   * Returns whether or not a player has busted
   *
   * @param string name player name
   * @return bool isBusted
   */
  bool isBusted(std::string name);

  Hand hand;
};

class HumanPlayer: public AbstractPlayer {
public:
  /**
   * Asks a player whether or not they want to
   * draw another card
   *
   * @return bool isDrawing
   */
  bool isDrawing();

  /**
   * Announce the winner of the current round
   *
   * @param string winner
   */
  void announce(std::string winner);
};

class ComputerPlayer: public AbstractPlayer {
public:
  /**
   * Determines whether or not the computer should
   * draw a card. True if hand.getValue() <= 16
   *
   * @return bool isDrawing
   */
  bool isDrawing();

  /**
   * Empty announce function
   */
  void announce(std::string winner);
};

class BlackJackGame {
public:
  /**
   * Carries out blackjack game logic
   */
  void play();

private:
  Deck m_deck;
  AbstractPlayer *m_casino;
};



### Building a Five-Card Poker Game

## Introduction

I am going to build a working game of 5-card poker. The players in the game will be `Player` objects I build, that can respond to the rules of the game, and driven by the process defined in your `Game` object (described below). 

The `Game` object drives the process of game-play.  During each round (hand), your `Player` class will analyze the cards it has received, and choose whether to fold, stand pat, or bet. 

When the program runs, it creates a `Game` object and adds two `Player` objects. Then it initiates game-play (Game::run), which is respresented by a series of "Rounds". During each round, this basic process is exectuted:

1. Determine which players have enough chips to enter the round (balance>=ante) (If only 1 player can proceed, game is over)
2. Collect the ante from each viable player and store these chips in the "pot"
3. Deal 5 cards to each player in the round
4. Ask each player to place an initial bet (bet>min_bet)  (store these chips in the "pot")
5. Offer each player the chance to "drop" as many as 4 (unwanted) cards, and draw replacement cards
6. Ask each player to place a final bet  (place these chips in the "pot")
7. Determine the winning hand, and award that play all the chips in the "pot"

After a while, a winner will emerge. The game will announce the winner, and how much they won. Then, the game will show all the hands, like this:

```
Winner is Player2 balance $1980
Round 1-- 
Player1 [JC, QD, 5C, 7S, 8C]
Player2 [AH, 7D, 9D, 6S, KD] won 210
Round 2-- 
Player1 [AH, 3D, JH, 2S, 3C]
Player2 [4S, QH, 7D, 6C, 6H] won 212
(..etc...)
```

--- 

## Rules of Five-Card Poker Game

Two (or more) players join the game. Each game is made up of a sequence of rounds (or hands). Rounds continue until all but one player has withdrawn from the game (usually by running out of money/chips).  

> To learn more, check out [this article on wikipedia](https://en.wikipedia.org/wiki/Five-card_draw).

### 1. The Ante
At the start of each round, every player pays an "ante" -- a small fee to participate in the round. The proceeds from player anties are kept in a central "pot" by the game, and these funds get disbursed at the end of the round to the winner of the round.

### 2. Dealing the Cards
The game shuffles a full deck of 52 cards. Each player is dealt a "hand" of five cards - by the game.  In your code, a `Hand` object will hold the five `Cards` that each `Player` receives.  Players are free to examine their own cards, which are kept out of the view of other players. 

### 3. First Bet 

After receiving their starting "hand", each `Player` has two options:

1. The player can fold their hand, and relinquish the money it put in the pot, and await the start of the next round. 
2. The player can place a bet (min. bet < bet < balance)

If _any_ player places a bet at this point, then _every_ player must match that bet, or elect to fold. To make our game a little simpler, players are not permitted to raise any bet. A player can either match a bet, or fold. 

If more than one player remains after that first round of betting, there follows a round of "drawing" new cards. If only 1 player is left, they immediately win the pot, and the next round begins. 

> Note: The game engine should _not_ allow the "last" player in a round to fold, even if that `Player` elects to do so. The last player in a round automatically wins the pot.

### 4. Drawing Cards (discard/add)

Each `Player` still in the round is given the opportunity to discard from 0 to 4 cards. After discarding N cards, the game will ask the `Player` to draw new cards to fill out the hand (to a total of 5 cards) again.

### 5. Final Bet -- 

As before, each player is again given the option to fold, hold, or bet. As before, if any player choose to bet, then every player who wants to remain in the round must match that bet, or they may fold.

### 6. Winning the Round 
Cards for all players are now revealed (you will show the cards in the hand for each player in the terminal), and the game determines which player has the winning hand, and how much they won in the pot (also shown in the terminal -- see below). The winning player receives all the money from the pot for this round. The game then continues back at step one in the process with a new shuffled `Deck`. 


---

## Hands you can achieve in Five-Card Poker (best to worst)

### 1. Royal flush
A sequence of 5 highest cards (all in the same suit).  Example: `{A♦, K♦, Q♦, J♦, 10♦}` (shown in order for clarity)

### 2. Straight flush
Five cards in a sequence, all in the same suit.  Examples : `{8♥ 7♥ 6♥ 5♥ 4♥}`, or `{7♦ 8♦ 9♦ 10♦ J♦}`
If tie persists, use "high-card" analysis to break tie.

### 3. Four of a kind
All four cards of the same face value (suit doesn't matter). Example: `{K-K-K-K 3}`
If tie persists, use "high-card" analysis to break tie.

### 4. Full house
Three cards with the same face value.  `{T T T 9 9}`
To determine winner, apply rules found in "Three of a kind".

### 5. Flush
Any five cards with the same suit, but not in a sequence.  Example:  `{4♦ J♦ 8♦ 2♦ 9♦}`
If tie persists, use "high-card" analysis to break tie.

### 6. Straight
Five cards in a sequence, regardless of suit. Example: `{5 6 7 8 9}`
Ties awarded to player with highest-card in straight. 
If tie persists, use "high-card" analysis to break tie.

### 7. Three of a kind
Three cards of the same rank, regardless of suit.  `{Q-Q-Q 2 3}`
Ties awarded to player with highest matching card (three Queens beat three Jacks). 

### 8. Two pairs
Two pairs of two cards with same face value.  Example: `{K-K 7-7 2}`
Ties awarded to player with highest matching pair (two Queens beat two Jacks). 
If necessary, compare lowest-matching pair. If that fails, use "high-card" to break tie.

### 9. One Pair
Two cards of the same face value.  Example: `{A-A 5 2 8}`
Ties awarded to player with highest pair (two Queens beat two Jacks). 
If pairs are tied, use "high-card" analysis to determine winner.

### 10. High Card
When you can't make any of the hands above, your highest card is the only play. 
Player with highest ranking card in hand wins. If tied, compare next highest-card, (etc.)

--- 

## Deliverables 

### 1. Implement the Core Classes...



#### 1. The `Card` class

The `Card` class represents a given card (suit, face) in a deck. As usual, there are 4 suits, with 13 faces in each, for a total of 52 cards.  

It is essential that your `Card` class correctly represents each card from the deck, and, that it be able to "show" the card in the terminal. You can show them in a fancy way, just a simple strings, like "QD" or "Q♦" (queen diamonds). 



```
    
    //correctly functioning OCF methods are required, but not shown here... 

    bool  operator==(const Card &aCard) const;  //test if cards are equal
    bool  operator<=(const Card &aCard) const;  //test if cards are <=
  
    //Shows a card on terminal in short form...
    friend std::ostream& operator<<(std::ostream &anOutput, const Card &aCard); 

```

#### 2. The `Deck` class

The `Deck` class will initially hold 52 distinct (non-repeating) `Card` objects in an internal data structure. 

```cpp
    bool pop(Card &aCard); //remove card from top of deck (copy it to aCard); return TRUE if success
    bool push(const Card &aCard); //add card to bottom of deck; return TRUE if success
    bool isEmpty() const; //true if the deck contains 0 cards        
    void shuffle(); //fully randomize cards in deck;
```

It's essential that your `shuffle` method works well, and that after calling this method, the cards are in a well-shuffled, random order. Be careful to ensure that the cards in your `Deck` are in a new random order each time `shuffle` is called.

#### 3. The `Hand` class

A `Hand` will represent the 5 cards that each player will have during each round of the game. Generally speaking, your `Hand` class should have a data member that contains N `Card` objects (N is usually 5). 

```cpp
   Hand&       add(const Card& aCard); //append given card to your hand
   bool        discard(const Card &aCard); //remove this card from your hand; return TRUE if removed
    
   HandTypes   determineRank() const; //determine the type of hand you're holding (see HandTypes)
    
   bool        operator>(const Hand &aHand) const; //compare two hands; TRUE if this hand > aHand (e.g. two_pair>one_pair)
    
   size_t      count(); //count cards in hand
      
   void        show(std::ostream &anOutput) const; //show cards in hand in short form, e.g.:  [JC, QD, 5C, 7S, 8C]
    
```

It's essential that you implement `determineRank()` correctly. Given a `Hand` object that contains 5 cards, this method will analyze the collection of cards to determine the "best-match" logical hand the cards represent. See "Hands you can achieve" (above). Your game will rely on this method working in order to choose a winning `Hand` from reach round. 

It is also essential that you implement `bool Hand::operator>()` correctly. This method compares the rank of two `Hand` objects. If the ranks are different, the winner is the `Hand` with the highest ordinal value.  The the ranks are the same, then the winner is determine by analysis of the individual cards as outlined above (See "Hands you can achieve in Five-Card Poker").  

#### 4. The `Player` class

Your `Player` class will act like a virtual player, and respond to calls made by the `Game` object to iterate through rounds until a winner emerges (with all the money!). Your player will contain a `Hand` object, a name, and a balance.  

```cpp
  public:
    void          setBalance(float aValue); //called by game update balance
    float         getBalance() const; //retrieve current balance
    
    const Hand&   getHand() const;  
    void          setHand(const Hand &aHand);

    const std::string&  getName() const;
    
    bool          isFolding() const; //return TRUE if you want to quit this round
    float         placeBet(float aMinBet); //return bet value (>aMinBet) based on final rank of your expected hand
    size_t        discardUnwanted();  //drop any cards that aren't useful to achieve best hand
    
    void          drawCards(Deck &aDeck, size_t aMaxCount);  //take aMaxCount cards from given deck, add to your hand.
  protected:
    
    std::string name;
    float       balance;
    Hand        hand;
  };    
```

`Player:drawCards` and `Player::discardUnwanted` are automatically called during each round. In `drawCards` you will retrieve cards from the given `Deck` to complete your hand. This happens when the round first begins, and later if the players chooses to discard cards to improve their hand.  In the `DiscardUnwanted` method, you have a chance to analyze your hand, and estimate the most likely "best" hand you can achieve. Then, drop cards that aren't helpful to you, in hopes that when you draw new cards, you can get a winning hand.

#### 5. The `Round` class

The `Round` class is a "process" object that drives the game forward.  The `Round` class is managed for you by the `Game` class , the `Game::run` method.  The `Round` class defines the following methods:

```cpp
    Round& dealCards(Deck &aDeck);
    Round& drawCards(Deck &aDeck);
    size_t placeBets(float aMinBet);
    Round& payWinner(std::ostream &anOutput);
    
    bool willRun(Players &aPlayers);
    bool didRun(bool runStatus);
    bool run(float aMinBet, std::ostream &anOutput);
```

##### WillRun 

In this method, iterate the given list of players and ensure each has enough chips (balance) to pay the ante. For each player that can pay the ante, subtract the ante from their balance, and add the player to the list of players in the round (the `Round` class has its own list of players). The total chips from each ante paid is added to the internal "Round::pot" value.  

##### DidRun 

In this method,  we increment the cost of the ante for each subsequent round.  

##### Run 

This method drives each round through the various states: `dealing cards`, `placing_bets`, determining the winner and awarding the pot (`payWinner`). 

##### Deal Cards

In this method,  you have to make sure each player starts with an empty hand, and then draws the appropriate number of cards. 

##### Draw Cards

In this method,  you ask each player to `discardUnwanted` cards, then draw new replacement cards.  

##### Place Bets 

In this method,  we get each player to commit to folding, or to place a bet. First, ask the player whether they are folding (`isFolding`). If they are not, then request the level of the bet they want to make `placeBet(aMinBet)`. The player must respond with a bet >= aMinBit; otherwise they forfeit the game.  Reduce the player balance to cover the bet by calling `setBalance`, and increment the internal `Round.pot` value by a corresponding amount.  

When this method is done, return the number of players who successfully made a bet. The round ends if only 1 player can place a bet.

##### Pay Winner

In this method, you award the chips in the "pot" to the player with the best hand. If only a single player remains in this round, simply award the pot to the remaining player. If more than one player remains in the round, you must determine which player has the best hand.  You do that by getting the `Hand` for each player, and calling `determineRank`. Then you compare the rank from each hand to determine the winner. While `determineRank` can tell you what type of hand each player has, it can't always determine the winner by itself.  If each player has a hand with a different rank, the winner can be determined by the comparing the value associated with each rank. If Player1 has `two_pair` and Player2 has `one_pair`, the Player1 wins based on rank alone. However, if both players have hands of equal rank, then you must analyze individual cards to determine the winner.

For more informmation about how to determine a winner, review the section (above) called "Hands you can achieve in five-card poker".

Once a winner has been determined, award the pot to the winner by incrementing that player's balance by a value equal to the amount in the pot.








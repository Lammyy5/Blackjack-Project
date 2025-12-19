#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
#include <cctype>

using namespace std;

struct Card
{
    int value;
    string name;
};

vector<Card> createDeck()
{
    vector<Card> deck;
    const string ranks = "A23456789TJQK";
    const string suits[4] = {"♠", "♥", "♦", "♣"};

    for (char r : ranks)
    {
        int v;
        if (r == 'A')
            v = 11;
        else if (r == 'T' || r == 'J' || r == 'Q' || r == 'K')
            v = 10;
        else
            v = r - '0';

        for (int s = 0; s < 4; ++s)
        {
            string n;
            n += r;
            n += suits[s];
            deck.push_back({v, n});
        }
    }
    return deck;
}

int handValue(const vector<Card> &hand)
{
    int sum = 0, aces = 0;
    for (const Card &c : hand)
    {
        sum += c.value;
        if (c.value == 11)
            aces++;
    }
    while (sum > 21 && aces > 0)
    {
        sum -= 10;
        aces--;
    }
    return sum;
}

bool isBust(const vector<Card> &hand)
{
    return handValue(hand) > 21;
}

void printHand(const string &label, const vector<Card> &hand, bool hideFirst = false)
{
    cout << label << " hand: ";
    for (size_t i = 0; i < hand.size(); ++i)
    {
        if (i == 0 && hideFirst)
            cout << "[hidden] ";
        else
            cout << hand[i].name << " ";
    }
    if (!hideFirst)
        cout << "(total = " << handValue(hand) << ")";
    cout << "\n";
}

void playDealer(vector<Card> &dealer, vector<Card> &deck)
{
    while (handValue(dealer) < 17 && !deck.empty())
    {
        dealer.push_back(deck.back());
        deck.pop_back();
    }
}

double estimateWinProbStand(const vector<Card> &remainingDeck,
                            const vector<Card> &playerHand,
                            const vector<Card> &dealerHand,
                            int trials = 5000)
{
    static mt19937 rng(static_cast<unsigned int>(time(nullptr)));

    int wins = 0;

    for (int t = 0; t < trials; ++t)
    {
        vector<Card> deck = remainingDeck;
        vector<Card> dealer = dealerHand;
        vector<Card> player = playerHand;

        shuffle(deck.begin(), deck.end(), rng);

        playDealer(dealer, deck);

        int p = handValue(player);
        int d = handValue(dealer);

        if (d > 21)
            wins++;
        else if (p > d)
            wins++;
    }

    return static_cast<double>(wins) / trials;
}

void playerTurn(vector<Card> &player, vector<Card> &dealer, vector<Card> &deck)
{
    while (true)
    {
        cout << "\n";
        printHand("Player", player, false);
        printHand("Dealer", dealer, true);
        cout << "Dealer visible card: " << dealer[1].name << "\n";

        int total = handValue(player);
        if (total > 21)
        {
            cout << "\nYou BUSTED! (total = " << total << ")\n";
            return;
        }

        double winProbStand = estimateWinProbStand(deck, player, dealer, 5000);
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << "Estimated win probability if you STAND now: " << (winProbStand * 100.0) << "%\n";

        char choice;
        cout << "Enter H to HIT or S to STAND: ";
        cin >> choice;
        choice = toupper(choice);

        if (choice == 'S')
        {
            cout << "You chose to STAND.\n";
            return;
        }
        else if (choice == 'H')
        {
            if (deck.empty())
            {
                cout << "No more cards left in the deck.\n";
                return;
            }
            Card c = deck.back();
            deck.pop_back();
            player.push_back(c);
            cout << "You drew: " << c.name << "\n";
        }
        else
        {
            cout << "Invalid input. Please enter H or S.\n";
        }
    }
}

int main()
{
    mt19937 rng(static_cast<unsigned int>(time(nullptr)));
    char playAgain = 'Y';

    do
    {
        vector<Card> deck = createDeck();
        shuffle(deck.begin(), deck.end(), rng);

        vector<Card> player, dealer;
        player.push_back(deck.back());
        deck.pop_back();
        dealer.push_back(deck.back());
        deck.pop_back();
        player.push_back(deck.back());
        deck.pop_back();
        dealer.push_back(deck.back());
        deck.pop_back();

        cout << "\n=== BLACKJACK (Single Deck) ===\n";

        playerTurn(player, dealer, deck);

        if (isBust(player))
        {
            cout << "\nFinal Result: Dealer wins (player busted).\n";
        }
        else
        {
            cout << "\nDealer reveals hole card...\n";
            printHand("Dealer", dealer, false);

            playDealer(dealer, deck);

            cout << "\n--- Final Hands ---\n";
            printHand("Player", player, false);
            printHand("Dealer", dealer, false);

            int pTotal = handValue(player);
            int dTotal = handValue(dealer);

            cout << "\n--- Outcome ---\n";
            if (dTotal > 21)
            {
                cout << "Dealer BUSTED! Player wins.\n";
            }
            else if (pTotal > dTotal)
            {
                cout << "Player wins!\n";
            }
            else if (pTotal < dTotal)
            {
                cout << "Dealer wins.\n";
            }
            else
            {
                cout << "Push (tie).\n";
            }
        }

        cout << "\nPlay again? (Y/N): ";
        cin >> playAgain;
        playAgain = toupper(playAgain);

    } while (playAgain == 'Y');

    cout << "\nThanks for playing Blackjack!\n";
    return 0;
}

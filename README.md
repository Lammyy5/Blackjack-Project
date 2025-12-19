# Blackjack Simulation Using Discrete Mathematics

## General Description

This project is a C++ implementation of a single-deck Blackjack game created as part of a Discrete Mathematics course project. The program models Blackjack as a finite probabilistic system and applies discrete structures such as sets, conditional branching, and experimental probability.

The user plays an interactive Blackjack game by choosing to hit or stand until the hand is completed. During gameplay, the program estimates the player’s probability of winning for the current hand based on the remaining cards in the deck. The goal of the project is to demonstrate how discrete mathematics concepts can be applied to real-world decision-making problems using C++ programming.

---

## Programming Approach

- A standard 52-card deck is represented as a finite set using a vector data structure.
- Cards are randomly shuffled using a random number generator.
- Hand values are calculated with special handling for aces to support both soft and hard totals.
- The player’s turn is controlled through a loop that allows repeated hit or stand decisions.
- Dealer behavior follows standard Blackjack rules: hit on 16 or less, stand on 17 or more.
- Player win probability is estimated using Monte Carlo simulation based on the remaining deck.
- The program supports multiple rounds using a play-again loop.

---

## Authors

- **Lamar Reliford**

**Team Name:** C.W.A

---

## Date Published

December 2025

---

## How to Use the Program

### Requirements
- C++ compiler (C++11 or later)

### Compile
```bash
g++ main.cpp -o blackjack

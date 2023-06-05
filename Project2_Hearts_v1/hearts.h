/* 
 * File:   hearts.h
 * Author: Stephanie Peacock
 * Created on June 1, 2023, 6:41 PM
 */

#ifndef HEARTS_H
#define HEARTS_H

struct Card {
    int  card[52];  // Number of the card in the deck (1-52)
    int  fv[13];      // For setting the char face
    char face[13];    // Card's face value: 2-10, J, Q, K, A (high)
    int  sn;      // For setting string suit
    char suit[4];    // Card's suit
};

struct Player {
    int pNum;
    string name; 
    int hand[13];
};

// Input function prototypes
void shuffle(int [], const unsigned short, string[]);
void deal(Player &, Player &, Player &, Player &, int []);
void bSort(Player &, int [], const short);
void sSort(Player &, int [], const short);
void mSort(Player &, int [], const short);
void print(Player  , int [], const short);
void faceVal(string [], char [][13], string [], const short, const short);

#endif /* HEARTS_H */


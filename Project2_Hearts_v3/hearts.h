/* 
 * File:   hearts.h
 * Author: Stephanie Peacock
 * Created on June 4, 2023, 4:45 PM
 */

#ifndef HEARTS_H
#define HEARTS_H

struct Player {
    int order;
    string name; 
    int hand[13];
    int choice;
    string cards[13];
    bool match;
    int tScore;
    int score;
};




// Input function prototypes
void shuffle(vector<int>, const unsigned short, string[]);
void deal(Player &,Player &,Player &,Player &, vector<int>, string[]);
void bSort(Player &, int [], const short, string []);
void sSort(Player &, int [], const short, string []);
void mSort(Player &, int [], const short, string []);
void print(Player &, int [], string [], const short, int);
void deal(string [], char [][13], string [], const short, const short);
void set(Player &, int&, int[]);
void unset(Player &, int&, int[], string[]);
void npcUn(Player &, int &, int[], string[]);
void played(Player &, string, int, string[]);
int linSrch(vector<int>,const unsigned short,int&);
void playCard(Player&, Player&, Player&, Player&, int&, int&, int [], string, int, bool&); 
void trick( Player&, Player&, Player&, Player&,
            int, int, int, int,
            int&, int&, int&, int&,
            int&, int&, int&, int&,
            bool ,bool ,bool ,bool);
void count();

#endif /* HEARTS_H */


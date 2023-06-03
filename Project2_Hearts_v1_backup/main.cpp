/* 
 * File:   main.cpp
 * Author: Stephanie Peacock
 * Created on May 8, 2023, 9:30 PM
 * Purpose: Play a game of Hearts vs computer.
 */

//System Libraries
#include <iostream>  // Input / Output Library
#include <cstdlib>   // Random Function Library
#include <ctime>     // Time Library
#include <iomanip>   // Formatting Library
#include <fstream>   // File Library
using namespace std;

//User Libraries
//Global Constants - Math/Physics/Chemistry/Conversions Only
//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv) {
    //Set Random number seed
    srand(static_cast<unsigned int>(time(0)));
    
//Declare Variable Data Types and Constants
    // <editor-fold defaultstate="collapsed" desc="Variables">
    const unsigned short NCARDS = 26; // 2 Suits is 26 cards
    int card1, card2, card3, card4, card5, card6, card7, card8, card9, card10, card11, card12, card13, // Player 1's cards
        card14, card15, card16, card17, card18, card19, card20, card21, card22, card23, card24, card25, card26; // Player 2's cards
    // Face Values of cards - Aces High
    char face1 = '2', face2 = '3', face3 = '4', face4 = '5', face5 = '6', face6 = '7',
         face7 = '8', face8 = '9', face9 = 'T', face10 = 'J', face11 = 'Q', face12 = 'K',
         face13 = 'A';
    int face;
    string suit3 = "\u2660", // Spades
            suit4 = "\u2661"; // Hearts
    int suit;
    // For Scoring and counters
    int count  = 1, // Stops displaying available cards when all have been played
        choice,     // For selecting player card & scoring
        comPlay,    // Records what computer played
        trick  = 0, // Records result of current card trick
        pHand  = 0, // Player's hand value
        cHand  = 0, // Computer's hand value
        pScore = 0, // Records Player's accumulated game score
        cScore = 0, // Records computer's accumulated game score
        wins   = 0, // Records how many wins the player has
        total  = 0; // Records total games    
    float winLoss;  // Displays they % of games won vs losses
    
    // </editor-fold>

    // Open file & read current win / total 
    ifstream inWins("wins.txt");
    inWins >> wins >> total;
    // Close the file for at the end!
    inWins.close();
    
    // Make sure we don't divide by 0!
    if(total != 0 ) {
        // Previous games have been played - output the ratio
        winLoss = (wins/static_cast<float>(total)) * 100;    
        cout << "It looks like you have played before. You have won " << fixed << setprecision(2) << winLoss << "% of the games you have played." << endl;
    }
    else{
        // First time player - tell them about the game
        cout << "Let's play a game of Hearts! We will use two suits, (\u2660 and \u2661). " << endl
             << "You can go first. Here are your cards!" << endl;
    }
    
    
    
    
    do {    
        // <editor-fold defaultstate="collapsed" desc="Draw Cards">
        //************************************************/
        /*                                               */
        /*               Draw Player 1 Cards             */
        /*                                               */
        //************************************************/

        int drawp1 = 0;
        while (drawp1 < 13) {
            int card = rand() % NCARDS + 1; // generate a random number between 1 and 26
            bool unique = true;
            if (card == card1 || card == card2 || card == card3 || card == card4 || card == card5 ||
                    card == card6 || card == card7 || card == card8 || card == card9 || card == card10 ||
                    card == card11 || card == card12) {
                unique = false;
            }
            if (unique) {
                switch (drawp1) {
                    case 0: card1 = card; break;
                    case 1: card2 = card; break;
                    case 2: card3 = card; break;
                    case 3: card4 = card; break;
                    case 4: card5 = card; break;
                    case 5: card6 = card; break;
                    case 6: card7 = card; break;
                    case 7: card8 = card; break;
                    case 8: card9 = card; break;
                    case 9: card10 = card; break;
                    case 10: card11 = card; break;
                    case 11: card12 = card; break;
                    case 12: card13 = card; break;
                }
                drawp1++;
            }
        }

        //************************************************/
        /*                                               */
        /*               Draw Player 2 Cards             */
        /*                                               */
        //************************************************/

        int drawp2 = 0;
        while (drawp2 < 13) {
            int card = rand() % NCARDS + 1; // generate a random number between 1 and 26
            bool unique = true;
            if (card == card1 || card == card2 || card == card3 || card == card4 || card == card5 ||
                    card == card6 || card == card7 || card == card8 || card == card9 || card == card10 ||
                    card == card11 || card == card12 || card == card13 || card == card14 || card == card15 ||
                    card == card16 || card == card17 || card == card18 || card == card19 || card == card20 ||
                    card == card21 || card == card22 || card == card23 || card == card24 || card == card25) {
                unique = false;
            }
            if (unique) {
                switch (drawp2) {
                    case 0: card14 = card; break;
                    case 1: card15 = card; break;
                    case 2: card16 = card; break;
                    case 3: card17 = card; break;
                    case 4: card18 = card; break;
                    case 5: card19 = card; break;
                    case 6: card20 = card; break;
                    case 7: card21 = card; break;
                    case 8: card22 = card; break;
                    case 9: card23 = card; break;
                    case 10: card24 = card; break;
                    case 11: card25 = card; break;
                    case 12: card26 = card; break;
                }
                drawp2++;
            }
        }// </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Order Player 1 Cards">

        //************************************************/
        /*                                               */
        /*              Order Player 1 Cards             */
        /*                                               */
        //************************************************/ 
        // Set lowest value to card 1
        // <editor-fold defaultstate="collapsed" desc="Card 1 Order">
        card13 < card1 && card13 < card2 && card13 < card3 && card13 < card4 &&
        card13 < card5 && card13 < card6 && card13 < card7 && card13 < card8 &&
        card13 < card9 && card13 < card10 && card13 < card11 && card13 < card12 ? swap(card13, card1) :
        card12 < card1 && card12 < card2 && card12 < card3 && card12 < card4 &&
        card12 < card5 && card12 < card6 && card12 < card7 && card12 < card8 &&
        card12 < card9 && card12 < card10 && card12 < card11 && card12 < card13 ? swap(card12, card1) :
        card11 < card1 && card11 < card2 && card11 < card3 && card11 < card4 &&
        card11 < card5 && card11 < card6 && card11 < card7 && card11 < card8 &&
        card11 < card9 && card11 < card10 && card11 < card12 && card11 < card13 ? swap(card11, card1) :
        card10 < card1 && card10 < card2 && card10 < card3 && card10 < card4 &&
        card10 < card5 && card10 < card6 && card10 < card7 && card10 < card8 &&
        card10 < card9 && card10 < card11 && card10 < card12 && card10 < card13 ? swap(card10, card1) :
        card9 < card1 && card9 < card2 && card9 < card3 && card9 < card4 &&
        card9 < card5 && card9 < card6 && card9 < card7 && card9 < card8 &&
        card9 < card10 && card9 < card11 && card9 < card12 && card9 < card13 ? swap(card9, card1) :
        card8 < card1 && card8 < card2 && card8 < card3 && card8 < card4 &&
        card8 < card5 && card8 < card6 && card8 < card7 && card8 < card9 &&
        card8 < card10 && card8 < card11 && card8 < card12 && card8 < card13 ? swap(card8, card1) :
        card7 < card1 && card7 < card2 && card7 < card3 && card7 < card4 &&
        card7 < card5 && card7 < card6 && card7 < card8 && card7 < card9 &&
        card7 < card10 && card7 < card11 && card7 < card12 && card7 < card13 ? swap(card7, card1) :
        card6 < card1 && card6 < card2 && card6 < card3 && card6 < card4 &&
        card6 < card5 && card6 < card7 && card6 < card8 && card6 < card9 &&
        card6 < card10 && card6 < card11 && card6 < card12 && card6 < card13 ? swap(card6, card1) :
        card5 < card1 && card5 < card2 && card5 < card3 && card5 < card4 &&
        card5 < card6 && card5 < card7 && card5 < card8 && card5 < card9 &&
        card5 < card10 && card5 < card11 && card5 < card12 && card5 < card13 ? swap(card5, card1) :
        card4 < card1 && card4 < card2 && card4 < card3 && card4 < card5 &&
        card4 < card6 && card4 < card7 && card4 < card8 && card4 < card9 &&
        card4 < card10 && card4 < card11 && card4 < card12 && card4 < card13 ? swap(card4, card1) :
        card3 < card1 && card3 < card2 && card3 < card4 && card3 < card5 &&
        card3 < card6 && card3 < card7 && card3 < card8 && card3 < card9 &&
        card3 < card10 && card3 < card11 && card3 < card12 && card3 < card13 ? swap(card3, card1) :
        card2 < card1 && card2 < card3 && card2 < card4 && card2 < card5 &&
        card2 < card6 && card2 < card7 && card2 < card8 && card2 < card9 &&
        card2 < card10 && card2 < card11 && card2 < card12 && card2 < card13 ? swap(card2, card1) :
        // If 1 is lowest, do nothing    
        (void) 0; // </editor-fold>

        // Set lowest remaining value to card 2
        // <editor-fold defaultstate="collapsed" desc="Card 2 Order">
        card13 < card2 && card13 < card3 && card13 < card4 &&
        card13 < card5 && card13 < card6 && card13 < card7 && card13 < card8 &&
        card13 < card9 && card13 < card10 && card13 < card11 && card13 < card12 ? swap(card13, card2) :
        card12 < card2 && card12 < card3 && card12 < card4 &&
        card12 < card5 && card12 < card6 && card12 < card7 && card12 < card8 &&
        card12 < card9 && card12 < card10 && card12 < card11 && card12 < card13 ? swap(card12, card2) :
        card11 < card2 && card11 < card3 && card11 < card4 &&
        card11 < card5 && card11 < card6 && card11 < card7 && card11 < card8 &&
        card11 < card9 && card11 < card10 && card11 < card12 && card11 < card13 ? swap(card11, card2) :
        card10 < card2 && card10 < card3 && card10 < card4 &&
        card10 < card5 && card10 < card6 && card10 < card7 && card10 < card8 &&
        card10 < card9 && card10 < card11 && card10 < card12 && card10 < card13 ? swap(card10, card2) :
        card9 < card2 && card9 < card3 && card9 < card4 &&
        card9 < card5 && card9 < card6 && card9 < card7 && card9 < card8 &&
        card9 < card10 && card9 < card11 && card9 < card12 && card9 < card13 ? swap(card9, card2) :
        card8 < card2 && card8 < card3 && card8 < card4 &&
        card8 < card5 && card8 < card6 && card8 < card7 && card8 < card9 &&
        card8 < card10 && card8 < card11 && card8 < card12 && card8 < card13 ? swap(card8, card2) :
        card7 < card2 && card7 < card3 && card7 < card4 &&
        card7 < card5 && card7 < card6 && card7 < card8 && card7 < card9 &&
        card7 < card10 && card7 < card11 && card7 < card12 && card7 < card13 ? swap(card7, card2) :
        card6 < card2 && card6 < card3 && card6 < card4 &&
        card6 < card5 && card6 < card7 && card6 < card8 && card6 < card9 &&
        card6 < card10 && card6 < card11 && card6 < card12 && card6 < card13 ? swap(card6, card2) :
        card5 < card2 && card5 < card3 && card5 < card4 &&
        card5 < card6 && card5 < card7 && card5 < card8 && card5 < card9 &&
        card5 < card10 && card5 < card11 && card5 < card12 && card5 < card13 ? swap(card5, card2) :
        card4 < card2 && card4 < card3 && card4 < card5 &&
        card4 < card6 && card4 < card7 && card4 < card8 && card4 < card9 &&
        card4 < card10 && card4 < card11 && card4 < card12 && card4 < card13 ? swap(card4, card2) :
        card3 < card2 && card3 < card4 && card3 < card5 &&
        card3 < card6 && card3 < card7 && card3 < card8 && card3 < card9 &&
        card3 < card10 && card3 < card11 && card3 < card12 && card3 < card13 ? swap(card3, card2) :
        // If 2 is lowest, do nothing    
        (void) 0; // </editor-fold>

        // Set lowest remaining value to card 3
        // <editor-fold defaultstate="collapsed" desc="Card 3 Order">
        card13 < card3 && card13 < card4 &&
        card13 < card5 && card13 < card6 && card13 < card7 && card13 < card8 &&
        card13 < card9 && card13 < card10 && card13 < card11 && card13 < card12 ? swap(card13, card3) :
        card12 < card3 && card12 < card4 &&
        card12 < card5 && card12 < card6 && card12 < card7 && card12 < card8 &&
        card12 < card9 && card12 < card10 && card12 < card11 && card12 < card13 ? swap(card12, card3) :
        card11 < card3 && card11 < card4 &&
        card11 < card5 && card11 < card6 && card11 < card7 && card11 < card8 &&
        card11 < card9 && card11 < card10 && card11 < card12 && card11 < card13 ? swap(card11, card3) :
        card10 < card3 && card10 < card4 &&
        card10 < card5 && card10 < card6 && card10 < card7 && card10 < card8 &&
        card10 < card9 && card10 < card11 && card10 < card12 && card10 < card13 ? swap(card10, card3) :
        card9 < card3 && card9 < card4 &&
        card9 < card5 && card9 < card6 && card9 < card7 && card9 < card8 &&
        card9 < card10 && card9 < card11 && card9 < card12 && card9 < card13 ? swap(card9, card3) :
        card8 < card3 && card8 < card4 &&
        card8 < card5 && card8 < card6 && card8 < card7 && card8 < card9 &&
        card8 < card10 && card8 < card11 && card8 < card12 && card8 < card13 ? swap(card8, card3) :
        card7 < card3 && card7 < card4 &&
        card7 < card5 && card7 < card6 && card7 < card8 && card7 < card9 &&
        card7 < card10 && card7 < card11 && card7 < card12 && card7 < card13 ? swap(card7, card3) :
        card6 < card3 && card6 < card4 &&
        card6 < card5 && card6 < card7 && card6 < card8 && card6 < card9 &&
        card6 < card10 && card6 < card11 && card6 < card12 && card6 < card13 ? swap(card6, card3) :
        card5 < card3 && card5 < card4 &&
        card5 < card6 && card5 < card7 && card5 < card8 && card5 < card9 &&
        card5 < card10 && card5 < card11 && card5 < card12 && card5 < card13 ? swap(card5, card3) :
        card4 < card3 && card4 < card5 &&
        card4 < card6 && card4 < card7 && card4 < card8 && card4 < card9 &&
        card4 < card10 && card4 < card11 && card4 < card12 && card4 < card13 ? swap(card4, card3) :
        // If 3 is lowest, do nothing    
        (void) 0; // </editor-fold>

        // Set lowest remaining value to card 4
        // <editor-fold defaultstate="collapsed" desc="Card 4 Order">
        card13 < card4 &&
        card13 < card5 && card13 < card6 && card13 < card7 && card13 < card8 &&
        card13 < card9 && card13 < card10 && card13 < card11 && card13 < card12 ? swap(card13, card4) :
        card12 < card4 &&
        card12 < card5 && card12 < card6 && card12 < card7 && card12 < card8 &&
        card12 < card9 && card12 < card10 && card12 < card11 && card12 < card13 ? swap(card12, card4) :
        card11 < card4 &&
        card11 < card5 && card11 < card6 && card11 < card7 && card11 < card8 &&
        card11 < card9 && card11 < card10 && card11 < card12 && card11 < card13 ? swap(card11, card4) :
        card10 < card4 &&
        card10 < card5 && card10 < card6 && card10 < card7 && card10 < card8 &&
        card10 < card9 && card10 < card11 && card10 < card12 && card10 < card13 ? swap(card10, card4) :
        card9 < card4 &&
        card9 < card5 && card9 < card6 && card9 < card7 && card9 < card8 &&
        card9 < card10 && card9 < card11 && card9 < card12 && card9 < card13 ? swap(card9, card4) :
        card8 < card4 &&
        card8 < card5 && card8 < card6 && card8 < card7 && card8 < card9 &&
        card8 < card10 && card8 < card11 && card8 < card12 && card8 < card13 ? swap(card8, card4) :
        card7 < card4 &&
        card7 < card5 && card7 < card6 && card7 < card8 && card7 < card9 &&
        card7 < card10 && card7 < card11 && card7 < card12 && card7 < card13 ? swap(card7, card4) :
        card6 < card4 &&
        card6 < card5 && card6 < card7 && card6 < card8 && card6 < card9 &&
        card6 < card10 && card6 < card11 && card6 < card12 && card6 < card13 ? swap(card6, card4) :
        card5 < card4 &&
        card5 < card6 && card5 < card7 && card5 < card8 && card5 < card9 &&
        card5 < card10 && card5 < card11 && card5 < card12 && card5 < card13 ? swap(card5, card4) :
        // If 4 is lowest, do nothing    
        (void) 0; // </editor-fold>

        // Set lowest remaining value to card 5
        // <editor-fold defaultstate="collapsed" desc="Card 5 Order">
        card13 < card5 && card13 < card6 && card13 < card7 && card13 < card8 &&
        card13 < card9 && card13 < card10 && card13 < card11 && card13 < card12 ? swap(card13, card5) :
        card12 < card5 && card12 < card6 && card12 < card7 && card12 < card8 &&
        card12 < card9 && card12 < card10 && card12 < card11 && card12 < card13 ? swap(card12, card5) :
        card11 < card5 && card11 < card6 && card11 < card7 && card11 < card8 &&
        card11 < card9 && card11 < card10 && card11 < card12 && card11 < card13 ? swap(card11, card5) :
        card10 < card5 && card10 < card6 && card10 < card7 && card10 < card8 &&
        card10 < card9 && card10 < card11 && card10 < card12 && card10 < card13 ? swap(card10, card5) :
        card9 < card5 && card9 < card6 && card9 < card7 && card9 < card8 &&
        card9 < card10 && card9 < card11 && card9 < card12 && card9 < card13 ? swap(card9, card5) :
        card8 < card5 && card8 < card6 && card8 < card7 && card8 < card9 &&
        card8 < card10 && card8 < card11 && card8 < card12 && card8 < card13 ? swap(card8, card5) :
        card7 < card5 && card7 < card6 && card7 < card8 && card7 < card9 &&
        card7 < card10 && card7 < card11 && card7 < card12 && card7 < card13 ? swap(card7, card5) :
        card6 < card5 && card6 < card7 && card6 < card8 && card6 < card9 &&
        card6 < card10 && card6 < card11 && card6 < card12 && card6 < card13 ? swap(card6, card5) :
        // If 5 is lowest, do nothing    
        (void) 0; // </editor-fold>

        // Set lowest remaining value to card 6
        // <editor-fold defaultstate="collapsed" desc="Card 6 Order">
        card13 < card6 && card13 < card7 && card13 < card8 &&
        card13 < card9 && card13 < card10 && card13 < card11 && card13 < card12 ? swap(card13, card6) :
        card12 < card6 && card12 < card7 && card12 < card8 &&
        card12 < card9 && card12 < card10 && card12 < card11 && card12 < card13 ? swap(card12, card6) :
        card11 < card6 && card11 < card7 && card11 < card8 &&
        card11 < card9 && card11 < card10 && card11 < card12 && card11 < card13 ? swap(card11, card6) :
        card10 < card6 && card10 < card7 && card10 < card8 &&
        card10 < card9 && card10 < card11 && card10 < card12 && card10 < card13 ? swap(card10, card6) :
        card9 < card6 && card9 < card7 && card9 < card8 &&
        card9 < card10 && card9 < card11 && card9 < card12 && card9 < card13 ? swap(card9, card6) :
        card8 < card6 && card8 < card7 && card8 < card9 &&
        card8 < card10 && card8 < card11 && card8 < card12 && card8 < card13 ? swap(card8, card6) :
        card7 < card6 && card7 < card8 && card7 < card9 &&
        card7 < card10 && card7 < card11 && card7 < card12 && card7 < card13 ? swap(card7, card6) :
        // If 6 is lowest, do nothing    
        (void) 0; // </editor-fold>

        // Set lowest remaining value to card 7
        // <editor-fold defaultstate="collapsed" desc="Card 7 Order">
        card13 < card7 && card13 < card8 &&
        card13 < card9 && card13 < card10 && card13 < card11 && card13 < card12 ? swap(card13, card7) :
        card12 < card7 && card12 < card8 &&
        card12 < card9 && card12 < card10 && card12 < card11 && card12 < card13 ? swap(card12, card7) :
        card11 < card7 && card11 < card8 &&
        card11 < card9 && card11 < card10 && card11 < card12 && card11 < card13 ? swap(card11, card7) :
        card10 < card7 && card10 < card8 &&
        card10 < card9 && card10 < card11 && card10 < card12 && card10 < card13 ? swap(card10, card7) :
        card9 < card7 && card9 < card8 &&
        card9 < card10 && card9 < card11 && card9 < card12 && card9 < card13 ? swap(card9, card7) :
        card8 < card7 && card8 < card9 &&
        card8 < card10 && card8 < card11 && card8 < card12 && card8 < card13 ? swap(card8, card7) :
        // If 7 is lowest, do nothing    
        (void) 0; // </editor-fold>

        // Set lowest remaining value to card 8
        // <editor-fold defaultstate="collapsed" desc="Card 8 Order">
        card13 < card8 &&
        card13 < card9 && card13 < card10 && card13 < card11 && card13 < card12 ? swap(card13, card8) :
        card12 < card8 &&
        card12 < card9 && card12 < card10 && card12 < card11 && card12 < card13 ? swap(card12, card8) :
        card11 < card8 &&
        card11 < card9 && card11 < card10 && card11 < card12 && card11 < card13 ? swap(card11, card8) :
        card10 < card8 &&
        card10 < card9 && card10 < card11 && card10 < card12 && card10 < card13 ? swap(card10, card8) :
        card9 < card8 &&
        card9 < card10 && card9 < card11 && card9 < card12 && card9 < card13 ? swap(card9, card8) :
        // If 8 is lowest, do nothing    
        (void) 0; // </editor-fold>

        // Set lowest remaining value to card 9
        // <editor-fold defaultstate="collapsed" desc="Card 9 Order">
        card13 < card9 && card13 < card10 && card13 < card11 && card13 < card12 ? swap(card13, card9) :
        card12 < card9 && card12 < card10 && card12 < card11 && card12 < card13 ? swap(card12, card9) :
        card11 < card9 && card11 < card10 && card11 < card12 && card11 < card13 ? swap(card11, card9) :
        card10 < card9 && card10 < card11 && card10 < card12 && card10 < card13 ? swap(card10, card9) :
        // If 9 is lowest, do nothing    
        (void) 0; // </editor-fold>

        // Set lowest remaining value to card 10
        // <editor-fold defaultstate="collapsed" desc="Card 10 Order">
        card13 < card10 && card13 < card11 && card13 < card12 ? swap(card13, card10) :
        card12 < card10 && card12 < card11 && card12 < card13 ? swap(card12, card10) :
        card11 < card10 && card11 < card12 && card11 < card13 ? swap(card11, card10) :
        // If 10 is lowest, do nothing    
        (void) 0; // </editor-fold>

        // Set lowest remaining value to card 11
        // <editor-fold defaultstate="collapsed" desc="Card 11 Order">
        card13 < card11 && card13 < card12 ? swap(card13, card11) :
        card12 < card11 && card12 < card13 ? swap(card12, card11) :
        // If 11 is lowest, do nothing    
        (void) 0; // </editor-fold>

        // Set last 2 lowest remaining value to card 12 & 13
        // <editor-fold defaultstate="collapsed" desc="Card 12 & 13 Order">
        card13 < card12 ? swap(card13, card12) :
                // If 12 is lowest, do nothing    
                (void) 0; // </editor-fold>
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Order Player 2 Cards">
        //************************************************/
        //                                                /
        //              Order Player 2 Cards              /   
        //                                                /    
        //************************************************/ 
        // Set lowest value to card 14
        // <editor-fold defaultstate="collapsed" desc="Card 14 Order">
        card26 < card14 && card26 < card15 && card26 < card16 && card26 < card17 &&
        card26 < card18 && card26 < card19 && card26 < card20 && card26 < card21 &&
        card26 < card22 && card26 < card23 && card26 < card24 && card26 < card25 ? swap(card26, card14) :
        card25 < card14 && card25 < card15 && card25 < card16 && card25 < card17 &&
        card25 < card18 && card25 < card19 && card25 < card20 && card25 < card21 &&
        card25 < card22 && card25 < card23 && card25 < card24 && card25 < card26 ? swap(card25, card14) :
        card24 < card14 && card24 < card15 && card24 < card16 && card24 < card17 &&
        card24 < card18 && card24 < card19 && card24 < card20 && card24 < card21 &&
        card24 < card22 && card24 < card23 && card24 < card25 && card24 < card26 ? swap(card24, card14) :
        card23 < card14 && card23 < card15 && card23 < card16 && card23 < card17 &&
        card23 < card18 && card23 < card19 && card23 < card20 && card23 < card21 &&
        card23 < card22 && card23 < card24 && card23 < card25 && card23 < card26 ? swap(card23, card14) :
        card22 < card14 && card22 < card15 && card22 < card16 && card22 < card17 &&
        card22 < card18 && card22 < card19 && card22 < card20 && card22 < card21 &&
        card22 < card23 && card22 < card24 && card22 < card25 && card22 < card26 ? swap(card22, card14) :
        card21 < card14 && card21 < card15 && card21 < card16 && card21 < card17 &&
        card21 < card18 && card21 < card19 && card21 < card20 && card21 < card22 &&
        card21 < card23 && card21 < card24 && card21 < card25 && card21 < card26 ? swap(card21, card14) :
        card20 < card14 && card20 < card15 && card20 < card16 && card20 < card17 &&
        card20 < card18 && card20 < card19 && card20 < card21 && card20 < card22 &&
        card20 < card23 && card20 < card24 && card20 < card25 && card20 < card26 ? swap(card20, card14) :
        card19 < card14 && card19 < card15 && card19 < card16 && card19 < card17 &&
        card19 < card18 && card19 < card20 && card19 < card21 && card19 < card22 &&
        card19 < card23 && card19 < card24 && card19 < card25 && card19 < card26 ? swap(card19, card14) :
        card18 < card14 && card18 < card15 && card18 < card16 && card18 < card17 &&
        card18 < card19 && card18 < card20 && card18 < card21 && card18 < card22 &&
        card18 < card23 && card18 < card24 && card18 < card25 && card18 < card26 ? swap(card18, card14) :
        card17 < card14 && card17 < card15 && card17 < card16 && card17 < card18 &&
        card17 < card19 && card17 < card20 && card17 < card21 && card17 < card22 &&
        card17 < card23 && card17 < card24 && card17 < card25 && card17 < card26 ? swap(card17, card14) :
        card16 < card14 && card16 < card15 && card16 < card17 && card16 < card18 &&
        card16 < card19 && card16 < card20 && card16 < card21 && card16 < card22 &&
        card16 < card23 && card16 < card24 && card16 < card25 && card16 < card26 ? swap(card16, card14) :
        card15 < card14 && card15 < card16 && card15 < card17 && card15 < card18 &&
        card15 < card19 && card15 < card20 && card15 < card21 && card15 < card22 &&
        card15 < card23 && card15 < card24 && card15 < card25 && card15 < card26 ? swap(card2, card14) :
        // If 14 is lowest, do nothing    
        (void) 0; // </editor-fold>

        // Set lowest remaining value to card 15
        // <editor-fold defaultstate="collapsed" desc="Card 15 Order">
        card26 < card15 && card26 < card16 && card26 < card17 &&
        card26 < card18 && card26 < card19 && card26 < card20 && card26 < card21 &&
        card26 < card22 && card26 < card23 && card26 < card24 && card26 < card25 ? swap(card26, card15) :
        card25 < card15 && card25 < card16 && card25 < card17 &&
        card25 < card18 && card25 < card19 && card25 < card20 && card25 < card21 &&
        card25 < card22 && card25 < card23 && card25 < card24 && card25 < card26 ? swap(card25, card15) :
        card24 < card15 && card24 < card16 && card24 < card17 &&
        card24 < card18 && card24 < card19 && card24 < card20 && card24 < card21 &&
        card24 < card22 && card24 < card23 && card24 < card25 && card24 < card26 ? swap(card24, card15) :
        card23 < card15 && card23 < card16 && card23 < card17 &&
        card23 < card18 && card23 < card19 && card23 < card20 && card23 < card21 &&
        card23 < card22 && card23 < card24 && card23 < card25 && card23 < card26 ? swap(card23, card15) :
        card22 < card15 && card22 < card16 && card22 < card17 &&
        card22 < card18 && card22 < card19 && card22 < card20 && card22 < card21 &&
        card22 < card23 && card22 < card24 && card22 < card25 && card22 < card26 ? swap(card22, card15) :
        card21 < card15 && card21 < card16 && card21 < card17 &&
        card21 < card18 && card21 < card19 && card21 < card20 && card21 < card22 &&
        card21 < card23 && card21 < card24 && card21 < card25 && card21 < card26 ? swap(card21, card15) :
        card20 < card15 && card20 < card16 && card20 < card17 &&
        card20 < card18 && card20 < card19 && card20 < card21 && card20 < card22 &&
        card20 < card23 && card20 < card24 && card20 < card25 && card20 < card26 ? swap(card20, card15) :
        card19 < card15 && card19 < card16 && card19 < card17 &&
        card19 < card18 && card19 < card20 && card19 < card21 && card19 < card22 &&
        card19 < card23 && card19 < card24 && card19 < card25 && card19 < card26 ? swap(card19, card15) :
        card18 < card15 && card18 < card16 && card18 < card17 &&
        card18 < card19 && card18 < card20 && card18 < card21 && card18 < card22 &&
        card18 < card23 && card18 < card24 && card18 < card25 && card18 < card26 ? swap(card18, card15) :
        card17 < card15 && card17 < card16 && card17 < card18 &&
        card17 < card19 && card17 < card20 && card17 < card21 && card17 < card22 &&
        card17 < card23 && card17 < card24 && card17 < card25 && card17 < card26 ? swap(card17, card15) :
        card16 < card15 && card16 < card17 && card16 < card18 &&
        card16 < card19 && card16 < card20 && card16 < card21 && card16 < card22 &&
        card16 < card23 && card16 < card24 && card16 < card25 && card16 < card26 ? swap(card16, card15) :
        // If 15 is lowest, do nothing    
        (void) 0; // </editor-fold>

        // Set lowest remaining value to card 16
        // <editor-fold defaultstate="collapsed" desc="Card 16 Order">
        card26 < card16 && card26 < card17 &&
        card26 < card18 && card26 < card19 && card26 < card20 && card26 < card21 &&
        card26 < card22 && card26 < card23 && card26 < card24 && card26 < card25 ? swap(card26, card16) :
        card25 < card16 && card25 < card17 &&
        card25 < card18 && card25 < card19 && card25 < card20 && card25 < card21 &&
        card25 < card22 && card25 < card23 && card25 < card24 && card25 < card26 ? swap(card25, card16) :
        card24 < card16 && card24 < card17 &&
        card24 < card18 && card24 < card19 && card24 < card20 && card24 < card21 &&
        card24 < card22 && card24 < card23 && card24 < card25 && card24 < card26 ? swap(card24, card16) :
        card23 < card16 && card23 < card17 &&
        card23 < card18 && card23 < card19 && card23 < card20 && card23 < card21 &&
        card23 < card22 && card23 < card24 && card23 < card25 && card23 < card26 ? swap(card23, card16) :
        card22 < card16 && card22 < card17 &&
        card22 < card18 && card22 < card19 && card22 < card20 && card22 < card21 &&
        card22 < card23 && card22 < card24 && card22 < card25 && card22 < card26 ? swap(card22, card16) :
        card21 < card16 && card21 < card17 &&
        card21 < card18 && card21 < card19 && card21 < card20 && card21 < card22 &&
        card21 < card23 && card21 < card24 && card21 < card25 && card21 < card26 ? swap(card21, card16) :
        card20 < card16 && card20 < card17 &&
        card20 < card18 && card20 < card19 && card20 < card21 && card20 < card22 &&
        card20 < card23 && card20 < card24 && card20 < card25 && card20 < card26 ? swap(card20, card16) :
        card19 < card16 && card19 < card17 &&
        card19 < card18 && card19 < card20 && card19 < card21 && card19 < card22 &&
        card19 < card23 && card19 < card24 && card19 < card25 && card19 < card26 ? swap(card19, card16) :
        card18 < card16 && card18 < card17 &&
        card18 < card19 && card18 < card20 && card18 < card21 && card18 < card22 &&
        card18 < card23 && card18 < card24 && card18 < card25 && card18 < card26 ? swap(card18, card16) :
        card17 < card16 && card17 < card18 &&
        card17 < card19 && card17 < card20 && card17 < card21 && card17 < card22 &&
        card17 < card23 && card17 < card24 && card17 < card25 && card17 < card26 ? swap(card17, card16) :
        // If 16 is lowest, do nothing    
        (void) 0; // </editor-fold>

        // Set lowest remaining value to card 17
        // <editor-fold defaultstate="collapsed" desc="Card 17 Order">
        card26 < card17 &&
        card26 < card18 && card26 < card19 && card26 < card20 && card26 < card21 &&
        card26 < card22 && card26 < card23 && card26 < card24 && card26 < card25 ? swap(card26, card17) :
        card25 < card17 &&
        card25 < card18 && card25 < card19 && card25 < card20 && card25 < card21 &&
        card25 < card22 && card25 < card23 && card25 < card24 && card25 < card26 ? swap(card25, card17) :
        card24 < card17 &&
        card24 < card18 && card24 < card19 && card24 < card20 && card24 < card21 &&
        card24 < card22 && card24 < card23 && card24 < card25 && card24 < card26 ? swap(card24, card17) :
        card23 < card17 &&
        card23 < card18 && card23 < card19 && card23 < card20 && card23 < card21 &&
        card23 < card22 && card23 < card24 && card23 < card25 && card23 < card26 ? swap(card23, card17) :
        card22 < card17 &&
        card22 < card18 && card22 < card19 && card22 < card20 && card22 < card21 &&
        card22 < card23 && card22 < card24 && card22 < card25 && card22 < card26 ? swap(card22, card17) :
        card21 < card17 &&
        card21 < card18 && card21 < card19 && card21 < card20 && card21 < card22 &&
        card21 < card23 && card21 < card24 && card21 < card25 && card21 < card26 ? swap(card21, card17) :
        card20 < card17 &&
        card20 < card18 && card20 < card19 && card20 < card21 && card20 < card22 &&
        card20 < card23 && card20 < card24 && card20 < card25 && card20 < card26 ? swap(card20, card17) :
        card19 < card17 &&
        card19 < card18 && card19 < card20 && card19 < card21 && card19 < card22 &&
        card19 < card23 && card19 < card24 && card19 < card25 && card19 < card26 ? swap(card19, card17) :
        card18 < card17 &&
        card18 < card19 && card18 < card20 && card18 < card21 && card18 < card22 &&
        card18 < card23 && card18 < card24 && card18 < card25 && card18 < card26 ? swap(card18, card17) :
        // If 17 is lowest, do nothing    
        (void) 0; // </editor-fold>

        // Set lowest remaining value to card 18
        // <editor-fold defaultstate="collapsed" desc="Card 18 Order">
        card26 < card18 && card26 < card19 && card26 < card20 && card26 < card21 &&
        card26 < card22 && card26 < card23 && card26 < card24 && card26 < card25 ? swap(card26, card18) :
        card25 < card18 && card25 < card19 && card25 < card20 && card25 < card21 &&
        card25 < card22 && card25 < card23 && card25 < card24 && card25 < card26 ? swap(card25, card18) :
        card24 < card18 && card24 < card19 && card24 < card20 && card24 < card21 &&
        card24 < card22 && card24 < card23 && card24 < card25 && card24 < card26 ? swap(card24, card18) :
        card23 < card18 && card23 < card19 && card23 < card20 && card23 < card21 &&
        card23 < card22 && card23 < card24 && card23 < card25 && card23 < card26 ? swap(card23, card18) :
        card22 < card18 && card22 < card19 && card22 < card20 && card22 < card21 &&
        card22 < card23 && card22 < card24 && card22 < card25 && card22 < card26 ? swap(card22, card18) :
        card21 < card18 && card21 < card19 && card21 < card20 && card21 < card22 &&
        card21 < card23 && card21 < card24 && card21 < card25 && card21 < card26 ? swap(card21, card18) :
        card20 < card18 && card20 < card19 && card20 < card21 && card20 < card22 &&
        card20 < card23 && card20 < card24 && card20 < card25 && card20 < card26 ? swap(card20, card18) :
        card19 < card18 && card19 < card20 && card19 < card21 && card19 < card22 &&
        card19 < card23 && card19 < card24 && card19 < card25 && card19 < card26 ? swap(card19, card18) :
        // If 18 is lowest, do nothing    
        (void) 0; // </editor-fold>

        // Set lowest remaining value to card 19
        // <editor-fold defaultstate="collapsed" desc="Card 19 Order">
        card26 < card19 && card26 < card20 && card26 < card21 &&
        card26 < card22 && card26 < card23 && card26 < card24 && card26 < card25 ? swap(card26, card19) :
        card25 < card19 && card25 < card20 && card25 < card21 &&
        card25 < card22 && card25 < card23 && card25 < card24 && card25 < card26 ? swap(card25, card19) :
        card24 < card19 && card24 < card20 && card24 < card21 &&
        card24 < card22 && card24 < card23 && card24 < card25 && card24 < card26 ? swap(card24, card19) :
        card23 < card19 && card23 < card20 && card23 < card21 &&
        card23 < card22 && card23 < card24 && card23 < card25 && card23 < card26 ? swap(card23, card19) :
        card22 < card19 && card22 < card20 && card22 < card21 &&
        card22 < card23 && card22 < card24 && card22 < card25 && card22 < card26 ? swap(card22, card19) :
        card21 < card19 && card21 < card20 && card21 < card22 &&
        card21 < card23 && card21 < card24 && card21 < card25 && card21 < card26 ? swap(card21, card19) :
        card20 < card19 && card20 < card21 && card20 < card22 &&
        card20 < card23 && card20 < card24 && card20 < card25 && card20 < card26 ? swap(card20, card19) :
        // If 19 is lowest, do nothing    
        (void) 0; // </editor-fold>

        // Set lowest remaining value to card 20
        // <editor-fold defaultstate="collapsed" desc="Card 20 Order">
        card26 < card20 && card26 < card21 &&
        card26 < card22 && card26 < card23 && card26 < card24 && card26 < card25 ? swap(card26, card20) :
        card25 < card20 && card25 < card21 &&
        card25 < card22 && card25 < card23 && card25 < card24 && card25 < card26 ? swap(card25, card20) :
        card24 < card20 && card24 < card21 &&
        card24 < card22 && card24 < card23 && card24 < card25 && card24 < card26 ? swap(card24, card20) :
        card23 < card20 && card23 < card21 &&
        card23 < card22 && card23 < card24 && card23 < card25 && card23 < card26 ? swap(card23, card20) :
        card22 < card20 && card22 < card21 &&
        card22 < card23 && card22 < card24 && card22 < card25 && card22 < card26 ? swap(card22, card20) :
        card21 < card20 && card21 < card22 &&
        card21 < card23 && card21 < card24 && card21 < card25 && card21 < card26 ? swap(card21, card20) :
        // If 20 is lowest, do nothing    
        (void) 0; // </editor-fold>

        // Set lowest remaining value to card 21
        // <editor-fold defaultstate="collapsed" desc="Card 21 Order">
        card26 < card21 &&
        card26 < card22 && card26 < card23 && card26 < card24 && card26 < card25 ? swap(card26, card21) :
        card25 < card21 &&
        card25 < card22 && card25 < card23 && card25 < card24 && card25 < card26 ? swap(card25, card21) :
        card24 < card21 &&
        card24 < card22 && card24 < card23 && card24 < card25 && card24 < card26 ? swap(card24, card21) :
        card23 < card21 &&
        card23 < card22 && card23 < card24 && card23 < card25 && card23 < card26 ? swap(card23, card21) :
        card22 < card21 &&
        card22 < card23 && card22 < card24 && card22 < card25 && card22 < card26 ? swap(card22, card21) :
        // If 21 is lowest, do nothing    
        (void) 0; // </editor-fold>

        // Set lowest remaining value to card 22
        // <editor-fold defaultstate="collapsed" desc="Card 22 Order">
        card26 < card22 && card26 < card23 && card26 < card24 && card26 < card25 ? swap(card26, card22) :
        card25 < card22 && card25 < card23 && card25 < card24 && card25 < card26 ? swap(card25, card22) :
        card24 < card22 && card24 < card23 && card24 < card25 && card24 < card26 ? swap(card24, card22) :
        card23 < card22 && card23 < card24 && card23 < card25 && card23 < card26 ? swap(card23, card22) :
                // If 22 is lowest, do nothing    
                (void) 0; // </editor-fold>

        // Set lowest remaining value to card 23
        // <editor-fold defaultstate="collapsed" desc="Card 23 Order">
        card26 < card23 && card26 < card24 && card26 < card25 ? swap(card26, card23) :
        card25 < card23 && card25 < card24 && card25 < card26 ? swap(card25, card23) :
        card24 < card23 && card24 < card25 && card24 < card26 ? swap(card24, card23) :
                // If 23 is lowest, do nothing    
                (void) 0; // </editor-fold>

        // Set lowest remaining value to card 24
        // <editor-fold defaultstate="collapsed" desc="Card 24 Order">
        card26 < card24 && card26 < card25 ? swap(card26, card24) :
        card25 < card24 && card25 < card26 ? swap(card25, card24) :
                // If 24 is lowest, do nothing    
                (void) 0; // </editor-fold>

        // Set last 2 remaining values to card 25 & 26
        // <editor-fold defaultstate="collapsed" desc="Card 25 & 26 Order">
        card26 < card25 ? swap(card26, card25) :
                // If 25 is lowest, do nothing    
                (void) 0; // </editor-fold>
        // </editor-fold>

        // <editor-fold defaultstate="collapsed" desc="Assign Face Values (show)">

        //************************************************/
        //                                                /
        //              Player 1 Face Values              /   
        //                                                /    
        //************************************************/    
        // <editor-fold defaultstate="collapsed" desc="comment">
        // Player 1 card 1 conversion
        face = (card1 - 1) % 13;
        suit = (card1 - 1) / 13;
        string show1 = "";
        switch (face) {
            case 0: show1 += face1; break;
            case 1: show1 += face2; break;
            case 2: show1 += face3; break;
            case 3: show1 += face4; break;
            case 4: show1 += face5; break;
            case 5: show1 += face6; break;
            case 6: show1 += face7; break;
            case 7: show1 += face8; break;
            case 8: show1 += face9; break;
            case 9: show1 += face10; break;
            case 10: show1 += face11; break;
            case 11: show1 += face12; break;
            default: show1 += face13; break;
        }
        switch (suit) {
            case 0: show1 += suit3 + "\t"; break;
            default: show1 += suit4 + "\t"; break;
        }

        // Player 1 Card 2
        face = (card2 - 1) % 13;
        suit = (card2 - 1) / 13;
        string show2 = "";
        switch (face) {
            case 0: show2 += face1; break;
            case 1: show2 += face2; break;
            case 2: show2 += face3; break;
            case 3: show2 += face4; break;
            case 4: show2 += face5; break;
            case 5: show2 += face6; break;
            case 6: show2 += face7; break;
            case 7: show2 += face8; break;
            case 8: show2 += face9; break;
            case 9: show2 += face10; break;
            case 10: show2 += face11; break;
            case 11: show2 += face12; break;
            default: show2 += face13; break;
        }
        switch (suit) {
            case 0: show2 += suit3 + "\t"; break;
            default: show2 += suit4 + "\t"; break;
        }

        // Player 1 Card 3
        face = (card3 - 1) % 13;
        suit = (card3 - 1) / 13;
        string show3 = "";
        switch (face) {
            case 0: show3 += face1; break;
            case 1: show3 += face2; break;
            case 2: show3 += face3; break;
            case 3: show3 += face4; break;
            case 4: show3 += face5; break;
            case 5: show3 += face6; break;
            case 6: show3 += face7; break;
            case 7: show3 += face8; break;
            case 8: show3 += face9; break;
            case 9: show3 += face10; break;
            case 10: show3 += face11; break;
            case 11: show3 += face12; break;
            default: show3 += face13; break;
        }
        switch (suit) {
            case 0: show3 += suit3 + "\t"; break;
            default: show3 += suit4 + "\t"; break;
        }

        // Player 1 Card 4
        face = (card4 - 1) % 13;
        suit = (card4 - 1) / 13;
        string show4 = "";
        switch (face) {
            case 0: show4 += face1; break;
            case 1: show4 += face2; break;
            case 2: show4 += face3; break;
            case 3: show4 += face4; break;
            case 4: show4 += face5; break;
            case 5: show4 += face6; break;
            case 6: show4 += face7; break;
            case 7: show4 += face8; break;
            case 8: show4 += face9; break;
            case 9: show4 += face10; break;
            case 10: show4 += face11; break;
            case 11: show4 += face12; break;
            default: show4 += face13; break;
        }
        switch (suit) {
            case 0: show4 += suit3 + "\t"; break;
            default: show4 += suit4 + "\t"; break;
        }

        //Player 1 Card 5
        face = (card5 - 1) % 13;
        suit = (card5 - 1) / 13;
        string show5 = "";
        switch (face) {
            case 0: show5 += face1; break;
            case 1: show5 += face2; break;
            case 2: show5 += face3; break;
            case 3: show5 += face4; break;
            case 4: show5 += face5; break;
            case 5: show5 += face6; break;
            case 6: show5 += face7; break;
            case 7: show5 += face8; break;
            case 8: show5 += face9; break;
            case 9: show5 += face10; break;
            case 10: show5 += face11; break;
            case 11: show5 += face12; break;
            default: show5 += face13; break;
        }
        switch (suit) {
            case 0: show5 += suit3 + "\t"; break;
            default: show5 += suit4 + "\t"; break;
        }

        // Player 1 Card 6
        face = (card6 - 1) % 13;
        suit = (card6 - 1) / 13;
        string show6 = "";
        switch (face) {
            case 0: show6 += face1; break;
            case 1: show6 += face2; break;
            case 2: show6 += face3; break;
            case 3: show6 += face4; break;
            case 4: show6 += face5; break;
            case 5: show6 += face6; break;
            case 6: show6 += face7; break;
            case 7: show6 += face8; break;
            case 8: show6 += face9; break;
            case 9: show6 += face10; break;
            case 10: show6 += face11; break;
            case 11: show6 += face12; break;
            default: show6 += face13; break;
        }
        switch (suit) {
            case 0: show6 += suit3 + "\t"; break;
            default: show6 += suit4 + "\t"; break;
        }

        // Player 1 Card 7
        face = (card7 - 1) % 13;
        suit = (card7 - 1) / 13;
        string show7 = "";
        switch (face) {
            case 0: show7 += face1; break;
            case 1: show7 += face2; break;
            case 2: show7 += face3; break;
            case 3: show7 += face4; break;
            case 4: show7 += face5; break;
            case 5: show7 += face6; break;
            case 6: show7 += face7; break;
            case 7: show7 += face8; break;
            case 8: show7 += face9; break;
            case 9: show7 += face10; break;
            case 10: show7 += face11; break;
            case 11: show7 += face12; break;
            default: show7 += face13; break;
        }
        switch (suit) {
            case 0: show7 += suit3 + "\t"; break;
            default: show7 += suit4 + "\t"; break;
        }

        // Player 1 card 8
        face = (card8 - 1) % 13;
        suit = (card8 - 1) / 13;
        string show8 = "";
        switch (face) {
            case 0: show8 += face1; break;
            case 1: show8 += face2; break;
            case 2: show8 += face3; break;
            case 3: show8 += face4; break;
            case 4: show8 += face5; break;
            case 5: show8 += face6; break;
            case 6: show8 += face7; break;
            case 7: show8 += face8; break;
            case 8: show8 += face9; break;
            case 9: show8 += face10; break;
            case 10: show8 += face11; break;
            case 11: show8 += face12; break;
            default: show8 += face13; break;
        }
        switch (suit) {
            case 0: show8 += suit3 + "\t"; break;
            default: show8 += suit4 + "\t"; break;
        }

        // Player 1 Card 9
        face = (card9 - 1) % 13;
        suit = (card9 - 1) / 13;
        string show9 = "";
        switch (face) {
            case 0: show9 += face1; break;
            case 1: show9 += face2; break;
            case 2: show9 += face3; break;
            case 3: show9 += face4; break;
            case 4: show9 += face5; break;
            case 5: show9 += face6; break;
            case 6: show9 += face7; break;
            case 7: show9 += face8; break;
            case 8: show9 += face9; break;
            case 9: show9 += face10; break;
            case 10: show9 += face11; break;
            case 11: show9 += face12; break;
            default: show9 += face13; break;
        }
        switch (suit) {
            case 0: show9 += suit3 + "\t"; break;
            default: show9 += suit4 + "\t"; break;
        }

        // Player 1 Card 10
        face = (card10 - 1) % 13;
        suit = (card10 - 1) / 13;
        string show10 = "";
        switch (face) {
            case 0: show10 += face1; break;
            case 1: show10 += face2; break;
            case 2: show10 += face3; break;
            case 3: show10 += face4; break;
            case 4: show10 += face5; break;
            case 5: show10 += face6; break;
            case 6: show10 += face7; break;
            case 7: show10 += face8; break;
            case 8: show10 += face9; break;
            case 9: show10 += face10; break;
            case 10: show10 += face11; break;
            case 11: show10 += face12; break;
            default: show10 += face13; break;
        }
        switch (suit) {
            case 0: show10 += suit3 + "\t"; break;
            default: show10 += suit4 + "\t"; break;
        }

        // Player 1 Card 11
        face = (card11 - 1) % 13;
        suit = (card11 - 1) / 13;
        string show11 = "";
        switch (face) {
            case 0: show11 += face1; break;
            case 1: show11 += face2; break;
            case 2: show11 += face3; break;
            case 3: show11 += face4; break;
            case 4: show11 += face5; break;
            case 5: show11 += face6; break;
            case 6: show11 += face7; break;
            case 7: show11 += face8; break;
            case 8: show11 += face9; break;
            case 9: show11 += face10; break;
            case 10: show11 += face11; break;
            case 11: show11 += face12; break;
            default: show11 += face13; break;
        }
        switch (suit) {
            case 0: show11 += suit3 + "\t"; break;
            default: show11 += suit4 + "\t"; break;
        }

        // Player 1 card 12
        face = (card12 - 1) % 13;
        suit = (card12 - 1) / 13;
        string show12 = "";
        switch (face) {
            case 0: show12 += face1; break;
            case 1: show12 += face2; break;
            case 2: show12 += face3; break;
            case 3: show12 += face4; break;
            case 4: show12 += face5; break;
            case 5: show12 += face6; break;
            case 6: show12 += face7; break;
            case 7: show12 += face8; break;
            case 8: show12 += face9; break;
            case 9: show12 += face10; break;
            case 10: show12 += face11; break;
            case 11: show12 += face12; break;
            default: show12 += face13; break;
        }
        switch (suit) {
            case 0: show12 += suit3 + "\t"; break;
            default: show12 += suit4 + "\t"; break;
        }

        // Player 1 Card 13
        face = (card13 - 1) % 13;
        suit = (card13 - 1) / 13;
        string show13 = "";
        switch (face) {
            case 0: show13 += face1; break;
            case 1: show13 += face2; break;
            case 2: show13 += face3; break;
            case 3: show13 += face4; break;
            case 4: show13 += face5; break;
            case 5: show13 += face6; break;
            case 6: show13 += face7; break;
            case 7: show13 += face8; break;
            case 8: show13 += face9; break;
            case 9: show13 += face10; break;
            case 10: show13 += face11; break;
            case 11: show13 += face12; break;
            default: show13 += face13; break;
        }
        switch (suit) {
            case 0: show13 += suit3 + "\t"; break;
            default: show13 += suit4 + "\t"; break;
        } // </editor-fold>



        //************************************************/
        //                                                /
        //              Player 2 Face Values              /   
        //                                                /    
        //************************************************/    
        // <editor-fold defaultstate="collapsed" desc="Player 2 show values">        
        // Player 2 card 1 conversion
        face = (card14 - 1) % 13;
        suit = (card14 - 1) / 13;
        string show14 = "";

        switch (face) {
            case 0: show14 += face1; break;
            case 1: show14 += face2; break;
            case 2: show14 += face3; break;
            case 3: show14 += face4; break;
            case 4: show14 += face5; break;
            case 5: show14 += face6; break;
            case 6: show14 += face7; break;
            case 7: show14 += face8; break;
            case 8: show14 += face9; break;
            case 9: show14 += face10; break;
            case 10: show14 += face11; break;
            case 11: show14 += face12; break;
            default: show14 += face13; break;
        }
        switch (suit) {
            case 0: show14 += suit3 + "\t"; break;
            default: show14 += suit4 + "\t"; break;
        }

        // Player 2 Card 2
        face = (card15 - 1) % 13;
        suit = (card15 - 1) / 13;
        string show15 = "";

        switch (face) {
            case 0: show15 += face1; break;
            case 1: show15 += face2; break;
            case 2: show15 += face3; break;
            case 3: show15 += face4; break;
            case 4: show15 += face5; break;
            case 5: show15 += face6; break;
            case 6: show15 += face7; break;
            case 7: show15 += face8; break;
            case 8: show15 += face9; break;
            case 9: show15 += face10; break;
            case 10: show15 += face11; break;
            case 11: show15 += face12; break;
            default: show15 += face13; break;
        }
        switch (suit) {
            case 0: show15 += suit3 + "\t"; break;
            default: show15 += suit4 + "\t"; break;
        }

        // Player 2 Card 3
        face = (card16 - 1) % 13;
        suit = (card16 - 1) / 13;
        string show16 = "";

        switch (face) {
            case 0: show16 += face1; break;
            case 1: show16 += face2; break;
            case 2: show16 += face3; break;
            case 3: show16 += face4; break;
            case 4: show16 += face5; break;
            case 5: show16 += face6; break;
            case 6: show16 += face7; break;
            case 7: show16 += face8; break;
            case 8: show16 += face9; break;
            case 9: show16 += face10; break;
            case 10: show16 += face11; break;
            case 11: show16 += face12; break;
            default: show16 += face13; break;
        }
        switch (suit) {
            case 0: show16 += suit3 + "\t"; break;
            default: show16 += suit4 + "\t"; break;
        }

        // Player 2 Card 4
        face = (card17 - 1) % 13;
        suit = (card17 - 1) / 13;
        string show17 = "";

        switch (face) {
            case 0: show17 += face1; break;
            case 1: show17 += face2; break;
            case 2: show17 += face3; break;
            case 3: show17 += face4; break;
            case 4: show17 += face5; break;
            case 5: show17 += face6; break;
            case 6: show17 += face7; break;
            case 7: show17 += face8; break;
            case 8: show17 += face9; break;
            case 9: show17 += face10; break;
            case 10: show17 += face11; break;
            case 11: show17 += face12; break;
            default: show17 += face13; break;
        }
        switch (suit) {
            case 0: show17 += suit3 + "\t"; break;
            default: show17 += suit4 + "\t"; break;
        }

        //Player 2 Card 5
        face = (card18 - 1) % 13;
        suit = (card18 - 1) / 13;
        string show18 = "";

        switch (face) {
            case 0: show18 += face1; break;
            case 1: show18 += face2; break;
            case 2: show18 += face3; break;
            case 3: show18 += face4; break;
            case 4: show18 += face5; break;
            case 5: show18 += face6; break;
            case 6: show18 += face7; break;
            case 7: show18 += face8; break;
            case 8: show18 += face9; break;
            case 9: show18 += face10; break;
            case 10: show18 += face11; break;
            case 11: show18 += face12; break;
            default: show18 += face13; break;
        }
        switch (suit) {
            case 0: show18 += suit3 + "\t"; break;
            default: show18 += suit4 + "\t"; break;
        }

        // Player 2 Card 6
        face = (card19 - 1) % 13;
        suit = (card19 - 1) / 13;
        string show19 = "";

        switch (face) {
            case 0: show19 += face1; break;
            case 1: show19 += face2; break;
            case 2: show19 += face3; break;
            case 3: show19 += face4; break;
            case 4: show19 += face5; break;
            case 5: show19 += face6; break;
            case 6: show19 += face7; break;
            case 7: show19 += face8; break;
            case 8: show19 += face9; break;
            case 9: show19 += face10; break;
            case 10: show19 += face11; break;
            case 11: show19 += face12; break;
            default: show19 += face13; break;
        }
        switch (suit) {
            case 0: show19 += suit3 + "\t"; break;
            default: show19 += suit4 + "\t"; break;
        }

        // Player 2 Card 7
        face = (card20 - 1) % 13;
        suit = (card20 - 1) / 13;
        string show20 = "";

        switch (face) {
            case 0: show20 += face1; break;
            case 1: show20 += face2; break;
            case 2: show20 += face3; break;
            case 3: show20 += face4; break;
            case 4: show20 += face5; break;
            case 5: show20 += face6; break;
            case 6: show20 += face7; break;
            case 7: show20 += face8; break;
            case 8: show20 += face9; break;
            case 9: show20 += face10; break;
            case 10: show20 += face11; break;
            case 11: show20 += face12; break;
            default: show20 += face13; break;
        }
        switch (suit) {
            case 0: show20 += suit3 + "\t"; break;
            default: show20 += suit4 + "\t"; break;
        }

        // Player 2 card 8
        face = (card21 - 1) % 13;
        suit = (card21 - 1) / 13;
        string show21 = "";

        switch (face) {
            case 0: show21 += face1; break;
            case 1: show21 += face2; break;
            case 2: show21 += face3; break;
            case 3: show21 += face4; break;
            case 4: show21 += face5; break;
            case 5: show21 += face6; break;
            case 6: show21 += face7; break;
            case 7: show21 += face8; break;
            case 8: show21 += face9; break;
            case 9: show21 += face10; break;
            case 10: show21 += face11; break;
            case 11: show21 += face12; break;
            default: show21 += face13; break;
        }
        switch (suit) {
            case 0: show21 += suit3 + "\t"; break;
            default: show21 += suit4 + "\t"; break;
        }

        // Player 2 Card 9
        face = (card22 - 1) % 13;
        suit = (card22 - 1) / 13;
        string show22 = "";

        switch (face) {
            case 0: show22 += face1; break;
            case 1: show22 += face2; break;
            case 2: show22 += face3; break;
            case 3: show22 += face4; break;
            case 4: show22 += face5; break;
            case 5: show22 += face6; break;
            case 6: show22 += face7; break;
            case 7: show22 += face8; break;
            case 8: show22 += face9; break;
            case 9: show22 += face10; break;
            case 10: show22 += face11; break;
            case 11: show22 += face12; break;
            default: show22 += face13; break;
        }
        switch (suit) {
            case 0: show22 += suit3 + "\t"; break;
            default: show22 += suit4 + "\t"; break;
        }

        // Player 2 Card 10
        face = (card23 - 1) % 13;
        suit = (card23 - 1) / 13;
        string show23 = "";

        switch (face) {
            case 0: show23 += face1; break;
            case 1: show23 += face2; break;
            case 2: show23 += face3; break;
            case 3: show23 += face4; break;
            case 4: show23 += face5; break;
            case 5: show23 += face6; break;
            case 6: show23 += face7; break;
            case 7: show23 += face8; break;
            case 8: show23 += face9; break;
            case 9: show23 += face10; break;
            case 10: show23 += face11; break;
            case 11: show23 += face12; break;
            default: show23 += face13; break;
        }
        switch (suit) {
            case 0: show23 += suit3 + "\t"; break;
            default: show23 += suit4 + "\t"; break;
        }

        // Player 2 Card 11
        face = (card24 - 1) % 13;
        suit = (card24 - 1) / 13;
        string show24 = "";

        switch (face) {
            case 0: show24 += face1; break;
            case 1: show24 += face2; break;
            case 2: show24 += face3; break;
            case 3: show24 += face4; break;
            case 4: show24 += face5; break;
            case 5: show24 += face6; break;
            case 6: show24 += face7; break;
            case 7: show24 += face8; break;
            case 8: show24 += face9; break;
            case 9: show24 += face10; break;
            case 10: show24 += face11; break;
            case 11: show24 += face12; break;
            default: show24 += face13; break;
        }
        switch (suit) {
            case 0: show24 += suit3 + "\t"; break;
            default: show24 += suit4 + "\t"; break;
        }

        // Player 2 card 12
        face = (card25 - 1) % 13;
        suit = (card25 - 1) / 13;
        string show25 = "";

        switch (face) {
            case 0: show25 += face1; break;
            case 1: show25 += face2; break;
            case 2: show25 += face3; break;
            case 3: show25 += face4; break;
            case 4: show25 += face5; break;
            case 5: show25 += face6; break;
            case 6: show25 += face7; break;
            case 7: show25 += face8; break;
            case 8: show25 += face9; break;
            case 9: show25 += face10; break;
            case 10: show25 += face11; break;
            case 11: show25 += face12; break;
            default: show25 += face13; break;
        }
        switch (suit) {
            case 0: show25 += suit3 + "\t"; break;
            default: show25 += suit4 + "\t"; break;
        }

        // Player 2 Card 13
        face = (card26 - 1) % 13;
        suit = (card26 - 1) / 13;
        string show26 = "";

        switch (face) {
            case 0: show26 += face1; break;
            case 1: show26 += face2; break;
            case 2: show26 += face3; break;
            case 3: show26 += face4; break;
            case 4: show26 += face5; break;
            case 5: show26 += face6; break;
            case 6: show26 += face7; break;
            case 7: show26 += face8; break;
            case 8: show26 += face9; break;
            case 9: show26 += face10; break;
            case 10: show26 += face11; break;
            case 11: show26 += face12; break;
            default: show26 += face13; break;
        }
        switch (suit) {
            case 0: show26 += suit3 + "\t"; break;
            default: show26 += suit4 + "\t"; break;
        }
         // </editor-fold>   
        // </editor-fold>    

        // <editor-fold defaultstate="collapsed" desc="Output Original Cards">
        // output the generated cards
        cout << "Play Card #:\t" << "1" << "\t" << "2" << "\t" << "3" << "\t" << "4" << "\t" << "5"
             << "\t" << "6" << "\t" << "7" << "\t" << "8" << "\t" << "9" << "\t" << "10"
             << "\t" << "11" << "\t" << "12" << "\t" << "13" << endl
             << setw(14) << "\t" << show1 << show2 << show3 << show4 << show5 << show6 << show7 << show8
             << show9 << show10 << show11 << show12 << show13 << endl << endl;
            // Player 2 values go here for testing (see v4)    
                
        // Loop to play the Hand
        for (int i = 0; i < 13; i++)    {
            // <editor-fold defaultstate="collapsed" desc="Player Chooses Card">
            // Player plays a card - verifies player has selected card 1 - 13
            do {
                cout << "Choose a card in your hand you wish to play: ";
                cin >> choice;
            } while((choice  < 1  || choice > 13) || (choice == 1  && card1  == 0) || (choice == 2  && card2  == 0) || (choice == 3  && card3  == 0) || 
                    (choice == 4  && card4  == 0) || (choice == 5  && card5  == 0) || (choice == 6  && card6  == 0) || (choice == 7  && card7  == 0) ||
                    (choice == 8  && card8  == 0) || (choice == 9  && card9  == 0) || (choice == 10 && card10 == 0) || (choice == 11 && card11 == 0) ||
                    (choice == 12 && card12 == 0) || (choice == 13 && card13 == 0));

            cout << "You played: ";
            switch (choice) {
                case 1: cout << show1; break;
                case 2: cout << show2; break;
                case 3: cout << show3; break;
                case 4: cout << show4; break;
                case 5: cout << show5; break;
                case 6: cout << show6; break;
                case 7: cout << show7; break;
                case 8: cout << show8; break;
                case 9: cout << show9; break;
                case 10: cout << show11; break;
                case 11: cout << show11; break;
                case 12: cout << show12; break;
                case 13: cout << show13; break;
                case 14: cout << show14; break;
                case 15: cout << show15; break;
                case 16: cout << show16; break;
                case 17: cout << show17; break;
                case 18: cout << show18; break;
                case 19: cout << show19; break;
                case 20: cout << show20; break;
                case 21: cout << show21; break;
                case 22: cout << show22; break;
                case 23: cout << show23; break;
                case 24: cout << show24; break;
                case 25: cout << show25; break;
                default: cout << show26; break;
            }
            // </editor-fold>

            // Set choice to card value for scoring
            choice == 1  ? choice = card1  : choice == 2  ? choice = card2  : choice == 3  ? choice = card3  : 
            choice == 4  ? choice = card4  : choice == 5  ? choice = card5  : choice == 6  ? choice = card6  :  
            choice == 7  ? choice = card7  : choice == 8  ? choice = card8  : choice == 9  ? choice = card9  :
            choice == 10 ? choice = card10 : choice == 11 ? choice = card11 : choice == 12 ? choice = card12 : 
            choice = card13;    
            // <editor-fold defaultstate="collapsed" desc="Computer Plays a Card">

            //************************************************/
            //                                                /
            //            Computer Plays a card               /   
            //                                                /    
            //************************************************/ 
            //Player played spades    
            if (choice < 14) {
                // Spades available, so play the lowest card
                if (card14 < 14 || card15 < 14 || card16 < 14 || card17 < 14 ||
                    card18 < 14 || card19 < 14 || card20 < 14 || card21 < 14 ||
                    card22 < 14 || card23 < 14 || card24 < 14 || card25 < 14 || card26 < 14) {
                    // Select the lowest available spade
                    if     (card14 != 0 && card14 < 14) {
                            cout << "Computer plays: " << show14 << endl;
                            comPlay = card14;
                    }
                    else if(card15 != 0 && card15 < 14) {
                            cout << "Computer plays: " << show15 << endl;
                            comPlay = card15;
                    }
                    else if(card16 != 0 && card16 < 14) {
                            cout << "Computer plays: " << show16 << endl;
                            comPlay = card16;
                    } 
                    else if(card17 != 0 && card17 < 14) {
                            cout << "Computer plays: " << show17 << endl;
                            comPlay = card17;
                    }
                    else if(card18 != 0 && card18 < 14) {
                            cout << "Computer plays: " << show18 << endl;
                            comPlay = card18;
                    }            
                    else if(card19 != 0 && card19 < 14) {
                            cout << "Computer plays: " << show19 << endl;
                            comPlay = card19;
                    }
                    else if(card20 != 0 && card20 < 14) {
                            cout << "Computer plays: " << show20 << endl;
                            comPlay = card20;
                    }            
                    else if(card21 != 0 && card21 < 14) {
                            cout << "Computer plays: " << show21 << endl;
                            comPlay = card21;
                    }
                    else if(card22 != 0 && card22 < 14) {
                            cout << "Computer plays: " << show22 << endl;
                            comPlay = card22;
                    }            
                    else if(card23 != 0 && card23 < 14) {

                        cout << "Computer plays: " << show23 << endl;
                        comPlay = card23;
                    }
                    else if(card24 != 0 && card24 < 14) {
                            cout << "Computer plays: " << show24 << endl;
                            comPlay = card24;
                    }           
                    else if(card25 != 0 && card25 < 14) {
                            cout << "Computer plays: " << show25 << endl;
                            comPlay = card25;
                    }            
                    else   {
                            cout << "Computer plays: " << show26 << endl;
                            comPlay = card26;
                    }
                }            
                // No spades available, play the largest heart
                else {
                    // Select the largest heart
                    if      (card26 != 0) {
                        cout << "Computer plays: " << show26 << endl;
                        comPlay = card26;
                    }
                    else if (card25 != 0) {
                        cout << "Computer plays: " << show25 << endl;
                        comPlay = card25;
                    }
                    else if (card24 != 0) {
                        cout << "Computer plays: " << show24 << endl;
                        comPlay = card24;
                    }
                    else if (card23 != 0) {
                        cout << "Computer plays: " << show23 << endl;
                        comPlay = card23;
                    }
                    else if (card22 != 0) {
                        cout << "Computer plays: " << show22 << endl;
                        comPlay = card22;
                    }
                    else if (card21 != 0) {
                        cout << "Computer plays: " << show21 << endl;
                        comPlay = card21;
                    }
                    else if (card20 != 0) {
                        cout << "Computer plays: " << show20 << endl;
                        comPlay = card20;
                    }
                    else if (card19 != 0) {
                        cout << "Computer plays: " << show19 << endl;
                        comPlay = card19;
                    }
                    else if (card18 != 0) {
                        cout << "Computer plays: " << show18 << endl;
                        comPlay = card18;
                    }
                    else if (card17 != 0) {
                        cout << "Computer plays: " << show17 << endl;
                        comPlay = card17;
                    }
                    else if (card16 != 0) {
                        cout << "Computer plays: " << show16 << endl;
                        comPlay = card16;
                    }
                    else if (card15 != 0) {
                        cout << "Computer plays: " << show15 << endl;
                        comPlay = card15;
                    }
                    else                  {
                        cout << "Computer plays: " << show14 << endl;
                        comPlay = card14;
                    }
                }
            }        
            // Player played a heart
            else {
                // Hearts available - play lowest card
                if (card14 > 13 || card15 > 13 || card16 > 13 || card17 > 13 ||
                    card18 > 13 || card19 > 13 || card20 > 13 || card21 > 13 ||
                    card22 > 13 || card23 > 13 || card24 > 13 || card25 > 13 || card26 > 13) {
                    if     (card14 != 0 && card14 > 13) {
                            cout << "Computer plays: " << show14 << endl;
                            comPlay = card14;
                    }            
                    else if(card15 != 0 && card15 > 13) {
                            cout << "Computer plays: " << show15 << endl;
                            comPlay = card15;
                    }            
                    else if(card16 != 0 && card16 > 13) {
                            cout << "Computer plays: " << show16 << endl;
                            comPlay = card16;
                    }  
                    else if(card17 != 0 && card17 > 13) {
                            cout << "Computer plays: " << show17 << endl;
                            comPlay = card17;
                    }            
                    else if(card18 != 0 && card18 > 13) {
                            cout << "Computer plays: " << show18 << endl;
                            comPlay = card18;
                    }            
                    else if(card19 != 0 && card19 > 13) {
                            cout << "Computer plays: " << show19 << endl;
                            comPlay = card19;
                    }            
                    else if(card20 != 0 && card20 > 13) {
                            cout << "Computer plays: " << show20 << endl;
                            comPlay = card20;
                    }            
                    else if(card21 != 0 && card21 > 13) {
                            cout << "Computer plays: " << show21 << endl;
                            comPlay = card21;
                    }            
                    else if(card22 != 0 && card22 > 13) {
                            cout << "Computer plays: " << show22 << endl;
                            comPlay = card22;
                    }            
                    else if(card23 != 0 && card23 > 13) {
                            cout << "Computer plays: " << show23 << endl;
                            comPlay = card23;
                    }            
                    else if(card24 != 0 && card24 > 13) {
                            cout << "Computer plays: " << show24 << endl;
                            comPlay = card24;
                    }            
                    else if(card25 != 0 && card25 > 13) {
                            cout << "Computer plays: " << show25 << endl;
                            comPlay = card25;
                    }                    
                    else                                {
                            cout << "Computer plays: " << show26 << endl;
                            comPlay = card26;
                    }
                }
                // No Hearts, play largest card
                else {
                    // Select the largest heart
                    if      (card26 != 0) {
                        cout << "Computer plays: " << show26 << endl;
                        comPlay = card26;
                    }
                    else if (card25 != 0) {
                        cout << "Computer plays: " << show25 << endl;
                        comPlay = card25;
                    }
                    else if (card24 != 0) {
                        cout << "Computer plays: " << show24 << endl;
                        comPlay = card24;
                    }
                    else if (card23 != 0) {
                        cout << "Computer plays: " << show23 << endl;
                        comPlay = card23;
                    }
                    else if (card22 != 0) {
                        cout << "Computer plays: " << show22 << endl;
                        comPlay = card22;
                    }
                    else if (card21 != 0) {
                        cout << "Computer plays: " << show21 << endl;
                        comPlay = card21;
                    }
                    else if (card20 != 0) {
                        cout << "Computer plays: " << show20 << endl;
                        comPlay = card20;
                    }
                    else if (card19 != 0) {
                        cout << "Computer plays: " << show19 << endl;
                        comPlay = card19;
                    }
                    else if (card18 != 0) {
                        cout << "Computer plays: " << show18 << endl;
                        comPlay = card18;
                    }
                    else if (card17 != 0) {
                        cout << "Computer plays: " << show17 << endl;
                        comPlay = card17;
                    }
                    else if (card16 != 0) {
                        cout << "Computer plays: " << show16 << endl;
                        comPlay = card16;
                    }
                    else if (card15 != 0) {
                        cout << "Computer plays: " << show15 << endl;
                        comPlay = card15;
                    }
                    else                  {
                        cout << "Computer plays: " << show14 << endl;
                        comPlay = card14;
                    }
                }
            }
            // </editor-fold>

            // <editor-fold defaultstate="collapsed" desc="Score the Trick">

            //************************************************/
            //                                                /
            //                Trick is scored                 /   
            //                                                /    
            //************************************************/                 

            // Both Play Hearts
            if (choice > 13 && comPlay > 13) {
                cout << "Trick worth two points." << endl;
                // Player wins trick
                if (choice > comPlay) {
                    cout << "Player takes the trick." << endl;
                    pHand += 2;
                    cout << "Player hand is " << pHand << "\t" << "Computer hand is " << cHand << endl;
                }                    // Computer wins trick
                else {
                    cout << "Computer takes the trick." << endl;
                    cHand += 2;
                    cout << "Player hand is " << pHand << "\t" << "Computer hand is " << cHand << endl;
                }
            }                // Player Plays hearts - computer plays spades
            else if (choice > 13 && comPlay < 14) {
                // Player plays hearts, computer plays any spade but Queen
                if (choice > comPlay && comPlay != 11) {
                    cout << "Trick worth one point." << endl;
                    cout << "Player takes the trick." << endl;
                    pHand += 1;
                    cout << "Player hand is " << pHand << "\t" << "Computer hand is " << cHand << endl;
                }                    // Player plays hearts, computer plays Queen of Spades
                else if (choice > 13 && comPlay == 11) {
                    cout << "Trick worth fourteen points." << endl;
                    cout << "Player takes the trick." << endl;
                    pHand += 14;
                    cout << "Player hand is " << pHand << "\t" << "Computer hand is " << cHand << endl;
                }
            }                // Both play spades
            else if (choice < 13 && comPlay < 13) {
                // Player wins trick - no Queen of Spades played
                if (choice > comPlay && (choice != 11 && comPlay != 11)) {
                    cout << "Trick worth no points." << endl;
                    cout << "Player takes the trick." << endl;
                    pHand += 0;
                    cout << "Player hand is " << pHand << "\t" << "Computer hand is " << cHand << endl;
                }                    // Player wins trick - someone played Queen of spades
                else if (choice > comPlay && (choice == 11 || comPlay == 11)) {
                    cout << "Trick worth thirteen points." << endl;
                    cout << "Player takes the trick." << endl;
                    pHand += 13;
                    cout << "Player hand is " << pHand << "\t" << "Computer hand is " << cHand << endl;
                }                    // Computer wins trick - no Queen of Spades played
                else if (choice < comPlay && (choice != 11 && comPlay != 11)) {
                    cout << "Trick worth no points." << endl;
                    cout << "Computer takes the trick." << endl;
                    cHand += 0;
                    cout << "Player hand is " << pHand << "\t" << "Computer hand is " << cHand << endl;
                }                    // Computer wins trick - Queen of Spades Played
                else if (choice < comPlay && (choice == 11 || comPlay == 11)) {
                    cout << "Trick worth thirteen points." << endl;
                    cout << "Computer takes the trick." << endl;
                    cHand += 13;
                    cout << "Player hand is " << pHand << "\t" << "Computer hand is " << cHand << endl;
                }
            } // </editor-fold>

            // <editor-fold defaultstate="collapsed" desc="Output Remaining Cards">

        //************************************************/
        //                                                /
        //      Remove used cards & output remaining      /   
        //                                                /    
        //************************************************/  
        
        // Set choice back to the card number instead of card value & set used card to 0
        choice == card1  ? choice = 1  : choice == card2  ? choice = 2  : choice == card3  ? choice = 3  :     
        choice == card4  ? choice = 4  : choice == card5  ? choice = 5  : choice == card6  ? choice = 6  :     
        choice == card7  ? choice = 7  : choice == card8  ? choice = 8  : choice == card9  ? choice = 9  :
        choice == card10 ? choice = 10 : choice == card11 ? choice = 11 : choice == card12 ? choice = 12 :     
        choice = 13;     
        // set chosen card to 0
        if (choice == 1) { card1 = 0; show1 = ""; count++; }
        if (choice == 2) { card2 = 0; show2 = ""; count++; }
        if (choice == 3) { card3 = 0; show3 = ""; count++; }
        if (choice == 4) { card4 = 0; show4 = ""; count++; }
        if (choice == 5) { card5 = 0; show5 = ""; count++; }
        if (choice == 6) { card6 = 0; show6 = ""; count++; }
        if (choice == 7) { card7 = 0; show7 = ""; count++; }
        if (choice == 8) { card8 = 0; show8 = ""; count++; }
        if (choice == 9) { card9 = 0; show9 = ""; count++; }
        if (choice == 10) { card10 = 0; show10 = ""; count++; }
        if (choice == 11) { card11 = 0; show11 = ""; count++; }
        if (choice == 12) { card12 = 0; show12 = ""; count++; }
        if (choice == 13) { card13 = 0; show13 = ""; count++; }
        // set computer's card to 0 also so no replays
        if (comPlay == 14) { card14 = 0; }
        if (comPlay == 15) { card15 = 0; }
        if (comPlay == 16) { card16 = 0; }
        if (comPlay == 17) { card17 = 0; }
        if (comPlay == 18) { card18 = 0; }
        if (comPlay == 19) { card19 = 0; }
        if (comPlay == 20) { card20 = 0; }
        if (comPlay == 21) { card21 = 0; }
        if (comPlay == 22) { card22 = 0; }
        if (comPlay == 23) { card23 = 0; }
        if (comPlay == 24) { card24 = 0; }
        if (comPlay == 25) { card25 = 0; }
        if (comPlay == 26) { card26 = 0; }

        if (count < 14) {
            // output Player's remaining cards - if value is 0 an empty string is output
            cout << endl << endl << "Play Card #:\t";
            if (card1 == 0) { cout << ""; } else { cout << "1" << "\t"; }
            if (card2 == 0) { cout << ""; } else { cout << "2" << "\t"; }
            if (card3 == 0) { cout << ""; } else { cout << "3" << "\t"; }
            if (card4 == 0) { cout << ""; } else { cout << "4" << "\t"; }
            if (card5 == 0) { cout << ""; } else { cout << "5" << "\t"; }
            if (card6 == 0) { cout << ""; } else { cout << "6" << "\t"; }
            if (card7 == 0) { cout << ""; } else { cout << "7" << "\t"; }
            if (card8 == 0) { cout << ""; } else { cout << "8" << "\t"; }
            if (card9 == 0) { cout << ""; } else { cout << "9" << "\t"; }
            if (card10 == 0) { cout << ""; } else { cout << "10" << "\t"; }
            if (card11 == 0) { cout << ""; } else { cout << "11" << "\t"; }
            if (card12 == 0) { cout << ""; } else { cout << "12" << "\t"; }
            if (card13 == 0) { cout << ""; } else { cout << "13" << "\t"; }
            // now output the remaining face values
            cout << endl;
            cout << setw(14) << "\t" << show1 << show2 << show3 << show4 << show5 << show6 << show7
                    << show8 << show9 << show10 << show11 << show12 << show13 << endl << endl;

            // Player 2 show settings go here (see v4)

        } // </editor-fold>
        }    
        //************************************************/
        //                                                /
        //        Output current round score              /   
        //                                                /    
        //************************************************/               
        // Check for Shooting the Moon
        pHand == 26 ? pHand = 0, cHand = 26, cout << "You shot the moon! Computer takes all points." << endl << endl :
        cHand == 26 ? pHand = 26, cHand = 0, cout << "Computer shot the moon! You take all points."  << endl << endl :
        cout << endl << "What a fun hand!" << endl << endl;
        // get the round score
        pScore += pHand;
        cScore += cHand;
        // reset hands and count to 0
        pHand = 0;
        cHand = 0;
        count = 0;
        
        cout << "The current game score is:" << endl
             << "Player   : " << pScore << endl
             << "Computer : " << cScore << endl << endl;
    } while (pScore < 50 && cScore < 50);

         //************************************************/
         //                                                /
         //                   Output win                   /   
         //                  fout to file                  /    
         //************************************************/                 
    cout << endl;
    if (pScore < cScore) { wins++, cout << "You won the game!" << endl; }
    else {total++, cout << "You lost the game. Better luck next time!" << endl; }
    
    // Let them know how good they are
    winLoss = (wins/static_cast<float>(total)) * 100;
    
    cout << "You have won " << fixed << setprecision(2) << winLoss << "% of the games you have played." << endl;
    
    // Record win ratio to file
    ofstream outWins("wins.txt");
    outWins << wins << " " << total;
    outWins.close();
    
         
    return 0;
}
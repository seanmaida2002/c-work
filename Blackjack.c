#include <stdio.h>
#include <cs50.h> //provided by Harvard CS50 course
#include <stdlib.h>
#include <time.h>
#include <string.h>

bool deck[52];
char suits[4] = {'H', 'D', 'S', 'C'};
string values[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
string faceCards[3] = {"J", "Q", "K"};
string numberCards[10] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "A"};
int player1Value = 0; //the value of player 1 cards added up
int player2Value = 0; //the value of player 2 cards added up
int dealerValue = 0; //the value of the dealer's cards added up
int money1 = 100; //player 1 money
int money2 = 100; //player 2 money
int bet1; //player 1 bet
int bet2; //player 2 bet

//the following procedure was written by Rebecca Russell
void dealHand(int hand[]) { 
    int c;
    for (int i = 0; i < 2; i++)
    {
        do
        {
            c = rand()%52;
        }
        while (deck[c] == false);

        hand[i] = c;
        deck[c]=false;
    }

}

//deals one card
// the following procedure was written by Rebecca Russel
void printHand(int hand[]) { 
    for (int i = 0; i < 1; i++)
    {
        printf("%s %c\t", values[hand[i]%13], suits[hand[i]/13]);
    }
    printf("\n");
}

void printDealer(int hand[]) { //prints one card for the dealer
    for (int i = 0; i < 1; i++)
    {
        printf("Dealer: %s %c\t", values[hand[i]%13], suits[hand[i]/13]);
    }
}

void initialDeal(string player, int hand[]) { //deals the initial two cards
    printf("%s: ", player);

    for (int i = 0; i < 2; i++)
    {
        printf("%s %c\t", values[hand[i]%13], suits[hand[i]/13]);
    }
    printf("\n");
}

//sees if one of your cards is a face card (jack, queen, king)
int faceCard(string card) {
    int value = 0;
    string jack = "J";
    string queen = "Q";
    string king = "K";
    if(strcmp(jack, card) == 0) {
        value += 10;
    }
    else if(strcmp(queen, card) == 0) {
        value += 10;
    }
    else if(strcmp(king, card) == 0) {
        value += 10;
    }
    return value;
}

//sees what number card you have like if its a 2,3,5,etc and sets value equal to its corresponding value
int numberCard(string card) {
    int value = 0;
    string two = "2";
    string three = "3";
    string four = "4";
    string five = "5";
    string six = "6";
    string seven = "7";
    string eight = "8";
    string nine = "9";
    string ten = "10";
    string ace = "A";

    if(strcmp(two,card) == 0) {
        value += 2;
    }
    if(strcmp(three,card) ==0) {
        value += 3;
    }
    if(strcmp(four,card) == 0) {
        value += 4;
    }
    if(strcmp(five,card) == 0) {
        value += 5;
    }
    if(strcmp(six,card) == 0) {
        value += 6;
    }
    if(strcmp(seven,card) == 0) {
        value += 7;
    }
    if(strcmp(eight,card) == 0) {
        value += 8;
    }
    if(strcmp(nine,card) == 0) {
        value += 9;
    }
    if(strcmp(ten,card) == 0) {
        value += 10;
    }
    if(strcmp(ace,card) == 0) { //if you have an Ace, the value is 11
        value += 11;
    }
    return value;
}

int lose(int value, int money, int p) {
    if(value > 21) { //if you get more than 21, you lose then the program terminates
        printf("Sorry Player %i, you got more than 21. You lose.\n", p);
        printf("You got %i\n", value);
        printf("Money: $%i\n", money);
        return 0;
    }
    return 1;
    
}

void outcome(int playerValue, int dealer, int p, int money, int bet) {
    if(dealer > 21 && playerValue < 21) {
        printf("Player %i:\nYOU WIN!\n", p);
        printf("Dealer: %i\nPlayer %i: %i\n", dealerValue, p, playerValue);
        printf("Money = +%0.0f\n", bet * 1.5);
        printf("Money: $%0.0f\n", money + (bet * 1.5) + bet);
    }
    if(dealer <= 21 && dealer > playerValue) {
        printf("Player %i:\nSorry, you lose\n", p);
        printf("Dealer: %i\n", dealerValue);
        printf("Player %i: %i\n", p, playerValue);
        printf("Money: $%i\n", money);
    }
    if(playerValue > dealer) {
        printf("Player %i:\nYOU WIN!\n", p);
        printf("Dealer: %i\nPlayer %i: %i\n", dealerValue, p, playerValue);
        printf("Money = +%0.0f\n", bet * 1.5);
        printf("Money: $%0.0f\n", money + (bet * 1.5) + bet);
    }
    if(playerValue == dealer) {
        printf("Player %i:\nIts a tie\n", p);
        printf("Dealer: %i\nPlayer %i: %i\n", dealerValue, p, playerValue);
        printf("Money = +%0.0d\n", bet);
        printf("Money: $%0.0d\n", money + bet);
    }
    printf("\n");
}

int blackJack(int player[], int p, int money, int bet) {
    printf("Player %i:\n", p);
    int playerValue = 0;
    int l; 
    string stand = "stand";
    string hit = "hit";
    int hand[5];
    string card1;
    string card2;
    string card3;
    string card4;
    for(int i = 0; i < 2; i+=2) {
        card1 = values[player[i]%13];
        card2 = values[player[i+1]%13];
    }
    playerValue += faceCard(card1);
    playerValue += faceCard(card2);
    playerValue += numberCard(card1);
    playerValue += numberCard(card2);
    if(playerValue == 21) {
        printf("You got 21! YOU WON!\n");
        printf("Dealer: %i\nPlayer: %i\n", dealerValue, playerValue);
        printf("Money = +%0.0f\n", bet * 1.5);
        printf("Money: $%0.0f\n", money + (bet * 1.5) + bet);
        exit(0);
    }
    if (lose(playerValue, money, p) == 0) {
        return 0;
    }
    string answer = get_string("Do you want to hit or stand? ");;
    if(strcmp(answer, hit) == 0) {
        dealHand(hand);
        printHand(hand);
        for(int i = 0; i < 1; i++) {
            card3 = values[hand[i]%13];
        }
        playerValue += faceCard(card3);
        playerValue += numberCard(card3);
        if(lose(playerValue, money, p) == 0) {
            return 0;
        }
    }
    while(strcmp(answer, stand) != 0 || playerValue > 21) {
        answer = get_string("Do you want to hit or stand? ");
        if(strcmp(answer, hit) == 0) {
            dealHand(hand);
            printHand(hand);
            for(int i = 0; i < 1; i++) {
                card4 = values[hand[i]%13];
            }
            playerValue += faceCard(card4);
            playerValue += numberCard(card4);
        }
        if(lose(playerValue, money, p) == 0) {
            return 0;
        }
    }
    return playerValue; 
    printf("\n");
}

void dealer(int dealer[]) {
    string stand = "stand";
    string hit = "hit";
    int hand[5];
    string card1;
    string card2;
    string card3;
    string card4;
    for(int i = 0; i < 2; i+=2) {
        card1 = values[dealer[i]%13];
        card2 = values[dealer[i+1]%13];
    }
    dealerValue += faceCard(card1);
    dealerValue += faceCard(card2);
    dealerValue += numberCard(card1);
    dealerValue += numberCard(card2);
    while(dealerValue < 17) {
        dealHand(hand);
        printDealer(hand);
        printf("\n");
        for(int i = 0; i < 1; i++) {
                card4 = values[hand[i]%13];
            }
            dealerValue += faceCard(card4);
            dealerValue += numberCard(card4);
    }
}

int main(void) {
    int p1[5];
    int p2[5];
    int computer[5];
    srand(time(NULL));

    for (int i = 0; i < 52; i++) {
        deck[i] = true;
    }

    printf("Player 1: You have $%i to play with\n", money1);
    bet1 = get_int("How much do you want to bet? ");
    money1 -= bet1;
    printf("Player 1: Money: %i\n", money1);
    printf("Player 2: You have $%i to play with\n", money2);
    bet2 = get_int("How much do you want to bet? ");
    money2 -= bet2;
    printf("Player 2: Money: %i\n", money2);
    
    dealHand(p1);
    dealHand(p2);
    dealHand(computer);
    initialDeal("Dealer", computer);
    initialDeal("Player 1", p1);
    initialDeal("Player 2", p2);
    printf("\n");
    player1Value = blackJack(p1, 1, money1, bet1);
    player2Value = blackJack(p2, 2, money2, bet2);
    dealer(computer);
    printf("\n");
    outcome(player1Value, dealerValue, 1, money1, bet1);
    printf("\n");
    outcome(player2Value, dealerValue, 2, money2, bet2);
   
}

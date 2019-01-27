#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

//number of animation loops should n+1
//where n is number of animation files
//+1 because loop variable needs to start at 1
#define NUMBER_OF_ANIMATIONS 4
#define HAND_SIZE 5

#define COLOR1 "spades"
#define COLOR2 "hearts"
#define COLOR3 "diamonds"
#define COLOR4 "clubs"


typedef struct Cards {
    char *color;
    int rank;
} cards;

//using ascii art in files makes an shuffling animation
void shuffle_animation(void) {
    FILE *fp;
    int i;
    char ch;
    char file_ext[] = ".txt";
    char anim[] = "shuffle_animation";
    char file_name[100];

    for(i=1; i < NUMBER_OF_ANIMATIONS; i++) {
        sprintf(file_name, "%s%d%s", anim, i, file_ext);
        fp = fopen(file_name, "r");
        while((ch = fgetc(fp)) != EOF) {
            printf("%c", ch);
        }
        printf("\n");
        fclose(fp);
        sleep(1);
    }
    sprintf(file_name, "%s1%s", anim, file_ext);
    fp = fopen(file_name, "r");
    while((ch = fgetc(fp)) != EOF) {
        printf("%c", ch);
    }
    printf("\n");
    fclose(fp);
}

void deal_animation(void) {
    int i;
    for(i=0; i < 5; i++) {
        printf("+----+\t");
    }
    printf("\n");
    for(i=0; i < 5; i++) {
        printf("|    |\t");
    }
    printf("\n");
    for(i=0; i < 5; i++) {
        printf("|    |\t");
    }
    printf("\n");
    for(i=0; i < 5; i++) {
        printf("|    |\t");
    }
    printf("\n");
    for(i=0; i < 5; i++) {
        printf("|    |\t");
    }
    printf("\n");
    for(i=0; i < 5; i++) {
        printf("+----+\t");
    }
    printf("\n");
    sleep(1);
}

cards* deal_card(void) {
    //create array of pointers to card struct
    char * color_array[] = {COLOR1, COLOR2, COLOR3, COLOR4};
   

    cards * new_card;
    new_card = malloc(sizeof(cards));
    //make the card random rank and color
    new_card->rank = 1 + (rand() % 14);
    new_card->color = color_array[rand() % 4];

    return new_card;

}
//check to prevent duplicates in hand
int card_check(cards *card_array[], cards *new_card, int hand_size) {
    int i;
    for(i=0; i < hand_size; i++) {
        if(new_card->rank == card_array[i]->rank && new_card->color == card_array[i]->color) {
            return 0;
        }
    }
    return 1;
}

void show_cards(cards * card_array[]) {
    int i;
    for(i=0; i < HAND_SIZE; i++) {
        printf("+----+\t");
    }   
    printf("\n");

    for(i=0; i < HAND_SIZE; i++) {
        printf("| %c  |\t", card_array[i]->color[0]);
    }   
    printf("\n");

    for(i=0; i < HAND_SIZE; i++) {
        printf("|    |\t");
    }  
    printf("\n");

    for(i=0; i < HAND_SIZE; i++) {
        if(card_array[i]->rank >= 10) {
            printf("| %d |\t", card_array[i]->rank);
        }
        else {
            printf("|  %d |\t", card_array[i]->rank);
        }
    }    
    printf("\n");

    for(i=0; i < HAND_SIZE; i++) {
        printf("|    |\t");
    }    
    printf("\n");

    for(i=0; i < HAND_SIZE; i++) {
        printf("+----+\t");
    }
    printf("\n");
}

int main(void) {
    time_t t;
    srand((unsigned) time(&t));

    shuffle_animation();
    /*array of pointers to the cards struct
    each card gets random rank and color and 
    dupplicates are also checked for */
    cards* hand[HAND_SIZE];
    cards* new_card;
    deal_animation();

    int i;
    for(i=0; i < HAND_SIZE;) {
        new_card = deal_card();
        if(card_check(hand, new_card, i)) {
            hand[i] = new_card;
            i++;
        }
    }
    show_cards(hand);


}
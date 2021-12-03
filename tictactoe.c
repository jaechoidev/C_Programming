#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define TICTACTOE_DIM 3
#define ITEMS TICTACTOE_DIM * TICTACTOE_DIM
#define DIVIDE_STAR 40

void print_border_star(){
    for (int i = 0; i<DIVIDE_STAR; ++i){
        printf("*");
    }
    printf("\n");
}

void intro(){
    print_border_star();
    printf("Tic Tac Toe\n");
    printf("COMP 2131 - FALL 2021 \n");
    printf("You will be playing against the computer\n");
    print_border_star();

    char user_name[32];
    bool valid_user_name;
    valid_user_name = false;
    while (valid_user_name == false) {
        printf("What is your name? (less than 10 chars) \n\n");
        scanf("%[^\n]%*c", user_name);
        if (strlen(user_name) <= 10){
            valid_user_name = true;
        }else{
            printf("PLEASE write name LESS than 10 chars... \n\n");
            print_border_star();
        }
    }
    printf("\n\nHello %s ... Let's have fun !!! You = X | Computer = 0\n", user_name);
}

void show_board(char *pos){
    for (int i = 0; i<TICTACTOE_DIM*2; i++){
        for (int j = 0; j<TICTACTOE_DIM; j++){
            char pos_value = pos[(i/2)*TICTACTOE_DIM+j];
            if (i%2 == 1 && j==0){
                printf(" %c ",pos_value);
            }else if (i%2 == 1 && j>0){
                printf("| %c ",pos_value);
            }else if ((i%2 == 0 && j==0 && i>0)){
                printf("---");
            }else if ((i%2 == 0 && j>0 && i>0)){
                printf("|---");
            }
        }
        printf("\n");
    }
}

int get_user_input(){
    char coord[32];
    int user_pos;
    bool valid_input;
    valid_input = false;

    while(valid_input == false){
        printf("\nEnter X,Y coordinates for your move: ");
        scanf("%[^\n]%*c", coord);
        if ((strlen(coord) < 4)&&(coord[0] > 48 && coord[0] <= (TICTACTOE_DIM+48)) && (coord[1] == 44) && (coord[2] > 48 && coord[2] <= (TICTACTOE_DIM+48))) {
            user_pos = (coord[0] - 48 - 1) * TICTACTOE_DIM + (coord[2] - 48 - 1);
            valid_input = true;
        }else{
            printf("Please write coordinate as valid form. (ex: 1,2)");
        }
    }
    printf("\n\n");
    return user_pos;
}

int get_user_pos(int *pick_pos, int game_turns) {
    int user_pos;
    int tmp;
    bool valid_pos;
    int valid_idx;
    valid_pos = false;

    while(valid_pos != true){
        user_pos = get_user_input();
        for (int i = 0; i <=game_turns; i++){
            if (pick_pos[i] == user_pos){
                valid_pos = true;
                valid_idx = i;
                break;
            }
        }
        if (valid_pos == false){
            printf("The coordinate is occupied.");
        }
    }

    tmp = pick_pos[game_turns];
    pick_pos[game_turns] = pick_pos[valid_idx];
    pick_pos[valid_idx] = tmp;
    return pick_pos[game_turns];
}

int get_comp_pos(int *pick_pos, int game_turns){
    int comp_pos;
    int tmp;
    comp_pos = rand() % (game_turns+1);
    tmp = pick_pos[game_turns];
    pick_pos[game_turns] = pick_pos[comp_pos];
    pick_pos[comp_pos] = tmp;
    return pick_pos[game_turns];
}

char is_winner(char *pos){
    //rows
    char winner;
    for (int i = 0 ; i < TICTACTOE_DIM; i++){
        winner = pos[i * TICTACTOE_DIM];
        for (int c = 0; c < TICTACTOE_DIM-1; c++) {
            if (winner == pos[i * TICTACTOE_DIM + c + 1]){
                winner = pos[i * TICTACTOE_DIM + c + 1];
            }else{
                winner = 'N';
            }
        }
        if (winner == 'O' || winner == 'X'){
            return winner;
        }
    }

    //column
    for (int i = 0 ; i < TICTACTOE_DIM; i++){
        winner = pos[i];
        for (int r = 0; r < TICTACTOE_DIM-1; r++) {
            if (winner == pos[i + TICTACTOE_DIM * (r + 1)]){
                winner = pos[i + TICTACTOE_DIM * (r + 1)];
            }else{
                winner = 'N';
            }
        }
        if (winner == 'O' || winner == 'X'){
            return winner;
        }
    }

    //cross case 1
    winner = pos[TICTACTOE_DIM * 0 + 0];
    for (int i = 1; i < TICTACTOE_DIM; i++){
        if (winner == pos[i + TICTACTOE_DIM * i]){
            winner = pos[i + TICTACTOE_DIM * i];
        }else{
            winner = 'N';
        }

    }
    if (winner == 'O' || winner == 'X'){
        return winner;
    }

    //cross case 2
    winner = pos[TICTACTOE_DIM * 1 -1];
    for (int i = 1; i < TICTACTOE_DIM; i++){
        if (winner == pos[TICTACTOE_DIM * (i + 1) - 1 - i]){
            winner = pos[TICTACTOE_DIM * (i + 1) - 1 - i];
        }else{
            winner = 'N';
        }
    }
    if (winner == 'O' || winner == 'X'){
        return winner;
    }
    return 'N';
}

int main() {
    time_t t;
    srand((unsigned) time(&t));
    char pos[ITEMS];
    int pick_pos[ITEMS];
    int user_pos;
    int comp_pos;
    int game_turns;
    char winner = 'N';

    game_turns = ITEMS-1;

    for (int i = 0; i < ITEMS; ++i) {
        pick_pos[i] = i;
        pos[i] = ' ';
    }

    intro();

    while(game_turns >= 0){
        show_board((char *) pos);

        user_pos = get_user_pos((int *) pick_pos, game_turns);
        pos[user_pos] = 'X';
        game_turns -= 1;
        winner = is_winner((char *) pos);
        if (winner != 'N' || game_turns < 0) {
            break;
        }

        comp_pos = get_comp_pos((int *) pick_pos, game_turns);
        pos[comp_pos] = 'O';
        game_turns -= 1;
        winner = is_winner((char *) pos);
        if (winner != 'N' || game_turns < 0) {
            break;
        }
        printf("\n\n");
    }
    print_border_star();
    if (winner == 'X'){
        printf("YOU WON.\n");
    }else if (winner == 'O'){
        printf("COMPUTER WON.\n");
    }else{
        printf("DRAW.\n");
    }
    print_border_star();
    show_board((char *) pos);
    printf("\nGame Is Over.\n");
    return 0;
}


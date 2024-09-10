
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

int lines, colons, level, beef,total_beef, flag=1;
char end, dif;
char **table;
int **board,**flags;

void victory(void);
void defeat(void);
void game_name(void);
void print_controls(void);

void beef_flag(void)
{
    int i, j;
    char c;
    while (1)
    {
        printf("Please, enter lines , colons : (x,y) ..");  //remove dots later
        scanf("%d,%d", &i, &j);
        i--;
        j--;
        if (((i >= 0) && (i < lines)) && ((j >= 0) && (j < colons)) && ((board[i][j] == 0) || (board[i][j] == 2)))
        {
            if (table[i][j] == '@')
            {
                beef--;
            }
            if(board[i][j] == 2)
                board[i][j] = 0;
            else
                board[i][j] = 2;
            break;
        }
        else
        {
            while ((c = getchar()) != '\n');
        }
    }
}

void free1(void)
{
    int i;
    if (table != NULL)
    {
        for (i = 0; table[i] != NULL; i++)
        {
            free(table[i]);
        }
        free(table);
    }

    if (board != NULL)
    {
        for (i = 0; board[i] != NULL; i++)
        {
            free(board[i]);
        }
        free(board);
    }

    if (flags != NULL)
    {
        for (i = 0; flags[i] != NULL; i++)
        {
            free(flags[i]);
        }
        free(flags);
    }
}

void table_realloc(void)
{
    int i;
    lines++;
    colons++;
    level++;
    table = (char **)realloc(table, lines * sizeof(char *));
    if (table == NULL)
    {
        printf("ERROR: No memory.");
        free1();
        exit(1);
    }
    for (i = 0; i < lines; i++)
    {
        table[i] = (char *)realloc(table[i], colons * sizeof(char));
        if (table[i] == NULL)
        {
            printf("ERROR: No memory.");
            free1();
            exit(1);
        }
    }

    board = (int **)realloc(board, lines * sizeof(int *));
    if (board == NULL)
    {
        printf("ERROR: No memory.");
        free1();
        exit(1);
    }
    for (i = 0; i < lines; i++)
    {
        board[i] = (int *)realloc(board[i], colons * sizeof(int));
        if (board[i] == NULL)
        {
            printf("ERROR: No memory.");
            free1();
            exit(1);
        }
    }

    flags = (int **)realloc(flags, lines * sizeof(int *));
    if (flags == NULL)
    {
        printf("ERROR: No memory.");
        free1();
        exit(1);
    }
    for (i = 0; i < lines; i++)
    {
        flags[i] = (int *)realloc(flags[i], colons * sizeof(int));
        if (flags[i] == NULL)
        {
            printf("ERROR: No memory.");
            free1();
            exit(1);
        }
    }
}

void table_alloc(void)
{
    int i;
    level = 1;

    table = (char **)malloc(lines * sizeof(char *));
    if (table == NULL)
    {
        printf("ERROR: No memory.");
        free1();
        exit(1);
    }
    for (i = 0; i < lines; i++)
    {
        table[i] = (char *)malloc(colons * sizeof(char));
        if (table[i] == NULL)
        {
            printf("ERROR: No memory.");
            free1();
            exit(1);
        }
    }

    board = (int **)malloc(lines * sizeof(int *));
    if (board == NULL)
    {
        printf("ERROR: No memory.");
        free1();
        exit(1);
    }
    for (i = 0; i < lines; i++)
    {
        board[i] = (int *)malloc(colons * sizeof(int));
        if (board[i] == NULL)
        {
            printf("ERROR: No memory.");
            free1();
            exit(1);
        }
    }

    flags = (int **)malloc(lines * sizeof(int *));
    if (flags == NULL)
    {
        printf("ERROR: No memory.");
        free1();
        exit(1);
    }
    for (i = 0; i < lines; i++)
    {
        flags[i] = (int *)malloc(colons * sizeof(int));
        if (flags[i] == NULL)
        {
            printf("ERROR: No memory.");
            free1();
            exit(1);
        }
    }
}

void arr_init(void)
{
    int i, j;

    for (i = 0; i < lines; i++)
    {
        for (j = 0; j < colons; j++)
        {
            table[i][j] = '.';
        }
    }

    for (i = 0; i < lines; i++)
    {
        for (j = 0; j < colons; j++)
        {
            board[i][j] = 0; // hidden:0  revealed:1  star:2
        }
    }
}

void flags_init(int k){
    int i,j;
    for(i=0;i<lines;i++){
        for(j=0;j<colons;j++){
            flags[i][j] = k;         // closed=0 , open=1;
        }
    }
}

void buffalo(int buf_num, int i, int j)
{
    int x, y;

    while (buf_num)
    {
        
        x = rand() % lines;
        y = rand() % colons;
        
        if (( ! ((x == i) && (y == j)) ) && (table[x][y] != '@'))
        {
            table[x][y] = '@';
            buf_num--;
        }
    }
}

void help(void)
{
    int i, j;
    for (i = 0; i < lines; i++)
    {
        for (j = 0; j < colons; j++)
        {
            if (((table[i][j] == '.') ||(isdigit(table[i][j]))) && (board[i][j]==0))
            {
                printf("\n EMPTY CELL AT LINE: %d , COLON: %d\n", i+1, j+1);
                return;
            }
        }
    }
}

void bells(void)
{
    int i, j, c;
    for (i = 0; i < lines; i++)
    {
        for (j = 0; j < colons; j++)
        {
            if (table[i][j] == '@')
            {
                continue;
            }
            c = 0;
            if ((i + 1 < lines) && (table[i + 1][j] == '@'))
                c++;
            if ((j + 1 < colons) && (table[i][j + 1] == '@'))
                c++;
            if ((i - 1 >= 0) && (table[i - 1][j] == '@'))
                c++;
            if ((j - 1 >= 0) && (table[i][j - 1] == '@'))
                c++;
            if ((i + 1 < lines) && (j + 1 < colons) && (table[i + 1][j + 1] == '@'))
                c++;
            if ((i - 1 >= 0) && (j - 1 >= 0) && (table[i - 1][j - 1] == '@'))
                c++;
            if ((i + 1 < lines) && (j - 1 >= 0) && (table[i + 1][j - 1] == '@'))
                c++;
            if ((i - 1 >= 0) && (j + 1 < colons) && (table[i - 1][j + 1] == '@'))
                c++;
            if (c)
                table[i][j] = c + 48;
        }
    }
}

void fill_table(int i, int j)
{
    int num = lines * colons;
    if ((dif == 'e') || (dif == 'E'))
    {
        total_beef = beef = num / 8;
        buffalo(beef, i, j);
    }
    else if ((dif == 'n') || (dif == 'N'))
    {
        total_beef = beef = num / 7;
        buffalo(beef, i, j);
    }
    else if ((dif == 'h') || (dif == 'H'))
    {
        total_beef = beef = num / 6;
        buffalo(beef, i, j);
    }
    else if ((dif == 't') || (dif == 'T'))
    {
        total_beef = beef = num / 5;
        buffalo(beef, i, j);
    }
    bells();
}

void quit(void)
{
    if ((end == 'x') || (end == 'X'))
    {
        system("clear");
        free1();
        exit(0);
    }
}

int star_buf(void){
    int i,j,c=0;
    for(i=0;i<lines;i++){
        for(j=0;j<colons;j++){
            if((table[i][j]!='@') && (board[i][j]==2)){
                return 0;
            }else if (board[i][j]==2){
                c++;
            }
        }
    }
    //printf("\nstar_buf c: %d  ==  total_beef: %d \n",c,total_beef); //testing
    if(c==total_beef)
        return 1;
    else
        return 0;
}

int closed_buf(void){
    int i,j,c=0;
    for(i=0;i<lines;i++){
        for(j=0;j<colons;j++){
            if((table[i][j]!='@') && ((board[i][j]==0) || (board[i][j]==2))){
                return 0;
            }else if ((board[i][j]==0)||(board[i][j]==2)){
                c++;
            }
        }
    }
    //printf("\nclosed_buf c: %d  ==  total_beef: %d \n",c,total_beef);
    if(c==total_beef)
        return 1;
    else
        return 0;
}

int next_level(void)
{
    
    if(((star_buf()) || (closed_buf())) && (lines<10) && (colons<20)){
        //printf("\n sup bitch im heree uhouuu definetely sane \n");
        table_realloc();      
        arr_init();
        flags_init(1);
        return 1;
    }else if(((star_buf()) || (closed_buf())) && ((lines==10) && (colons==20))){  
        victory();
        sleep(2);
        end='x';
        quit();
    }
    return 0;
}

void print_table(void) //handles the visual aspect of the game
{
    int i, j;
    //system("clear");
    //printing difficulty
    if ((dif == 'e') || (dif == 'E'))
        printf("     ___________\n    |\t\t|\n    |\e[34m Easy Mode\e[0m |\n    |___________|");
    if ((dif == 'n') || (dif == 'N'))
        printf("     _____________\n    |\t\t  |\n    |\e[34m Normal Mode\e[0m |\n    |_____________|");
    if ((dif == 'h') || (dif == 'H'))
        printf("     ___________\n    |\t\t|\n    |\e[34m Hard Mode\e[0m |\n    |___________|");
    if ((dif == 't') || (dif == 'T'))
        printf("     ___________\n    |\t\t|\n    |\e[34m  Try Me   \e[0m |\n    |___________|");

    printf("\n     ____________________\n    |\t\t\t |\n    |\e[34m Beef counter: %4d\e[0m |\n    |____________________|\n\n\n", beef);

    // printing the actual board with line and colon numbers
    printf("    ");
    for (j = 0; j < colons; j++)
        printf("%3d", j + 1); //numbers on top of the board (colon numbers)
    printf("\n");
    printf("____"); //first part of the line underneath
    for (j = 0; j < colons; j++)
        printf("___"); //second part of the line underneath
    printf("\n");

    for (i = 0; i < lines; i++)
    {
        printf("   |\n");       //vertical line
        printf("%2d |", i + 1); //also vertical line
        for (j = 0; j < colons; j++)
        {
            if (board[i][j])
            {
                if (board[i][j] == 2)
                    printf("\033[33m  %c\033[0m", '*');
                else if (isdigit(table[i][j]))
                    printf("\033[31m  %c\033[0m", table[i][j]);
                else if (table[i][j] == '@')
                    printf("\033[32m  %c\033[0m", table[i][j]);
                else if (table[i][j] == '.')
                    printf("\033[36m  %c\033[0m", table[i][j]);
                //else
                  //  printf("  %c", table[i][j]);
            }
            else
            {
                printf("  %c", table[i][j] /*'#'*/); //DON'T FORGET TO CHANGE BACK
            }
        }
        printf("\n");
    }
    printf("\n    ________________________\t ____________________");
    printf("\n   |\t\t\t\t\b\b\b\b|\t|\t\t\t\b\b\b|");
    printf("\n   | Level: %8d        |   | Press (x) to exit. |", level);
    printf("\n   |________________________|\t|____________________|\n\n");
}

void exit_menu(void)
{
    while (1)
    {
        game_name();
        printf("\n\n\n\n\t\t\t     ___________________ \t ___________________");
        printf("\n\t\t\t    |\t\t\t|\t|\t\t\t\b\b\b\b|");
        printf("\n\t\t\t    | Press (F) to play |\t| Press (X) to exit |");
        printf("\n\t\t\t    |___________________|\t|___________________|\n");
        //while((*exit = getchar()) != '\n');
        end = getchar();
        system("clear");
        quit();
        if ((end == 'F') || (end == 'f'))
        {
            system("clear");
            break;
        }
    }
}

void dimensions(void)
{
    system("clear");
    //asking the player for the board dimensions
    while (1)
    {
        printf("\n\n\n ________________________________________________\n|\t\t\t\t\t\t |\n");
        printf("| Insert board dimensions between [5x10]U[10x20] |\n");
        printf("|________________________________________________|\n\n\n");
        printf("Vertical:");
        scanf("%d", &lines);
        printf("\n\nHorizontal:");
        scanf("%d", &colons);
        if (((lines >= 5) && (lines <= 10)) && ((colons >= 10) && (colons <= 20)))
        {
            system("clear");
            break;
        }
        else //informing the player of incorrect board size request
        {
            system("clear");
            printf("\n\n _________________________________________________\n");
            printf("| WARNING!\t\t\t\t\t  |\n|\t\t\t\t\t\t  |\n");
            printf("| Enter dimensions inside the indicated spectrum. |");
            printf("\n|_________________________________________________|\n\n");
        }
    }
}

void difficulty(void)
{
    //Player inserts the Difficulty
    while (1)
    {
        printf("\n\n _______________________\n");
        printf("|\t\t\t|\n");
        printf("|  Enter Difficulty:    |\n");
        printf("|\t\t\t|\n");
        printf("|  o Easy (E)           |\n");
        printf("|\t\t\t|\n");
        printf("|  o Normal (N)         |\n");
        printf("|\t\t\t|\n");
        printf("|  o Hard (H)           |\n");
        printf("|\t\t\t|\n");
        printf("|  o Try Me (T)         |\n");
        printf("|\t\t\t|\n");
        printf("|_______________________|\n");
        // while ((dif = getchar()) != '\n');
        dif = getchar();
        if (((dif == 'e') || (dif == 'E')) || ((dif == 'n') || (dif == 'N')) || ((dif == 'H') || (dif == 'h')) || ((dif == 't') || (dif == 'T')))
        {
            system("clear");
            break;
        }
        else
        {
            system("clear");
            printf("\n _______________________________________________________________________________________\n");
            printf("|\t\t\t\t\t\t\t\t\t\t\t|\n|\e[33m Incorrect input.\e[0m\t\t\t\t\t\t\t\t\t|\n");
            printf("| Insert the letter of the corresponding difficulty as indicated in the parenthesis (). |\n");
            printf("|_______________________________________________________________________________________|\n\n");
        }
    }
}

void menu(void)
{
    exit_menu();
    dimensions();
    difficulty();
}

void open_squares(int i, int j)
{
    if (((i < 0) || (i >= lines)) || ((j < 0) || (j >= colons)))
    {
        return;
    }
    if ((table[i][j] == '@') || (board[i][j] == 2) || (board[i][j] == 1))
    {
        return;
    }
    if (isdigit(table[i][j]))
    {
        board[i][j] = 1;
        return;
    }
    if(flags[i][j]==1)
        board[i][j] = 1;
    open_squares(i + 1, j);
    open_squares(i - 1, j);
    open_squares(i, j + 1);
    open_squares(i, j - 1);
    return;
}

int wisdom(int i, int j)
{
    int c=0;
    if (((i >= 0) && (i < lines)) && ((j >= 0) || (j < colons)))
    {
        if((board[i][j]==0) && (flags[i][j]==0)){
            if(table[i][j]=='.'){
                flags[i][j] = 1;
                c = 1;
                c+= wisdom(i,j+1);
                c+= wisdom(i+1,j);
                c+= wisdom(i,j-1);
                c+= wisdom(i-1,j);
            }
            else if(isdigit(table[i][j])){
                flags[i][j] = 1;
                c = 1;
            }
        }
    }
    return c;
}

void show(void)
{
    int i, j;
    char c;
    while (1)
    {
        printf("Please, enter lines , colons (x,y):  ");
        scanf("%d,%d", &i, &j);
        i--;
        j--;
        if (flag)
        {
            fill_table(i, j);
            flag = 0;
        }
        if (((i >= 0) && (i < lines)) && ((j >= 0) && (j < colons)) && ((board[i][j] == 0) || (board[i][j] == 2)))
        {
            if (isdigit(table[i][j]))
            {
                board[i][j] = 1;
            }
            else if (table[i][j] == '@')
            {
                board[i][j] = 1;
                print_table();
                sleep(2);
                defeat();
                sleep(2);
                end = 'x';
                quit();
            }
            else
            {
                open_squares(i, j);
            }
            break;
        }
        else
        {
            printf("Wrong Input: Try Again.\n");
            while ((c = getchar()) != '\n');
        }
    }
}

int main(void)
{
    int i, j, counter, max = 0, lin = 0, col = 0;

    srand(time(NULL));

    menu();
    quit();

    free1();
    table_alloc();
    arr_init();
    flags_init(1);
    //game loop
    while (1)
    {
        print_table(); 
        if(flag){
            show();
            end='E';
        }
        else{
            printf("Please, enter choise.\n");
            while ((end = getchar()) != '\n');
            end = getchar();
        }
        if ((end == 's') || (end == 'S'))
        {
            show();
        }
        else if ((end == 'b') || (end == 'B'))
        {
            beef_flag();
        }
        else if ((end == 'h') || (end == 'H'))
        {
            help();
        }
        else if ((end == 'w') || (end == 'W'))
        {
            max=0;
            flags_init(0);
            for (i = 0; i < lines; i++)
            {
                for (j = 0; j < colons; j++)
                {
                    counter = 0;
                    counter = wisdom(i, j);
                    if(counter == 1){
                        flags[i][j] = 0;
                    }                 
                    if (max < counter)
                    {
                        max = counter;
                        lin = i;
                        col = j;
                    }
                }
                
            }
            printf("\n BEST GROUP OF CELLS (%d) AT LINE: %d , COLON: %d\n",max, lin+1, col+1);
            flags_init(1);
        }
        else
        {
            quit();
        }
        if (next_level()){
            flag = 1;
        }
    }
    return 0;
}

void victory(void)
{
    system("clear");
    printf("\033[5;1;32m");
    printf("\n\n\n\n\n\n\n\n\n\t  (\\,~,/)\t\t\t\t\t\t\t\t\b(\\,~,/)"); //bow tie knot
    printf("\n\t  (/'~'\\)\t\t\t\t\t\t\t\t\b(/'~'\\)\033[0m");          //bow tie knot
    printf("\033[1;34m\n\t\t__        __  _     ____    _______    ___     _____   __     __");
    printf("\n\t\t\\ \\      / / | |   / __ \\  |__   __|  /   \\   |  _  \\  \\ \\   / /");
    printf("\n\t\t \\ \\    / /  | |  / /  \\_\\    | |    / / \\ \\  | (_)  )  \\ \\ / /");
    printf("\n\t\t  \\ \\  / /   | | ( (    __    | |   ( (   ) ) |  _  /    \\ v /");
    printf("\n\t\t   \\ \\/ /    | |  \\ \\__/ /    | |    \\ \\_/ /  | | \\ \\     | |");
    printf("\n\t\t    \\__/     |_|   \\____/     |_|     \\___/   |_|  \\_\\    |_|");
    printf("\033[0m\033[5;1;32m\n\n\t  (\\,~,/)\t\t\t\t\t\t\t\t\b(\\,~,/)"); //bow tie knot
    printf("\n\t  (/'~'\\)\t\t\t\t\t\t\t\t\b(/'~'\\)\n\n\033[0m");           //bow tie knot
    sleep(4);
    system("clear");
    printf("\033[1;32m");
    printf("\n\n\n\n\n\n\n\n\n\t  (\\,~,/)\t\t\t\t\t\t\t\t\b(\\,~,/)"); //bow tie knot
    printf("\n\t  (/'~'\\)\t\t\t\t\t\t\t\t\b(/'~'\\)");                 //bow tie knot
    printf("\033[1;34m\n\t\t__        __  _     ____    _______    ___     _____   __     __");
    printf("\n\t\t\\ \\      / / | |   / __ \\  |__   __|  /   \\   |  _  \\  \\ \\   / /");
    printf("\n\t\t \\ \\    / /  | |  / /  \\_\\    | |    / / \\ \\  | (_)  )  \\ \\ / /");
    printf("\n\t\t  \\ \\  / /   | | ( (    __    | |   ( (   ) ) |  _  /    \\ v /");
    printf("\n\t\t   \\ \\/ /    | |  \\ \\__/ /    | |    \\ \\_/ /  | | \\ \\     | |");
    printf("\n\t\t    \\__/     |_|   \\____/     |_|     \\___/   |_|  \\_\\    |_|");
    printf("\033[1;32m\n\n\t  (\\,~,/)\t\t\t\t\t\t\t\t\b(\\,~,/)"); //bow tie knot
    printf("\n\t  (/'~'\\)\t\t\t\t\t\t\t\t\b(/'~'\\)\n\n\033[0m");  //bow tie knot
}

void defeat(void)
{
    system("clear");
    printf("\033[5;1;32m\n\n\n\n\n\n\n\t__    __\t\t\t\t\t\t\t\t__    __");
    printf("\n\t\\ \\  / /\t\t\t\t\t\t\t\t\\ \\  / /");
    printf("\n\t \\ \\/ /\t\t\t\t\t\t\t\t\t \\ \\/ /");
    printf("\n\t / /\\ \\\t\t\t\t\t\t\t\t\t / /\\ \\");
    printf("\n\t/_/  \\_\\\t\t\t\t\t\t\t\t/_/  \\_\\\033[0m");
    printf("\033[1;31m\n\t\t\t\b_____     _____   _____   _____       _    _______");
    printf("\n\t\t\t\b\b|  __ \\   |  ___) |  ___) |  ___)     / \\  (__   __)");
    printf("\n\t\t\t\b\b| |  \\ \\  | |___  | |__   | |___     / _ \\    | |");
    printf("\n\t\t\t\b\b| |   ) ) |  ___) |  __)  |  ___)   / (_) \\   | |");
    printf("\n\t\t\t\b\b| |__/ /  | |___  | |     | |___   / .---. \\  | |");
    printf("\n\t\t\t\b\b|_____/   |_____) |_|     |_____) /_/     \\_\\ |_|");
    printf("\033[5;1;32m\n\t__    __\t\t\t\t\t\t\t\t__    __");
    printf("\n\t\\ \\  / /\t\t\t\t\t\t\t\t\\ \\  / /");
    printf("\n\t \\ \\/ /\t\t\t\t\t\t\t\t\t \\ \\/ /");
    printf("\n\t / /\\ \\\t\t\t\t\t\t\t\t\t / /\\ \\");
    printf("\n\t/_/  \\_\\\t\t\t\t\t\t\t\t/_/  \\_\\ \033[0m\n");
    sleep(4);
    system("clear");
    printf("\033[1;32m\n\n\n\n\n\n\n\t__    __\t\t\t\t\t\t\t\t__    __");
    printf("\n\t\\ \\  / /\t\t\t\t\t\t\t\t\\ \\  / /");
    printf("\n\t \\ \\/ /\t\t\t\t\t\t\t\t\t \\ \\/ /");
    printf("\n\t / /\\ \\\t\t\t\t\t\t\t\t\t / /\\ \\");
    printf("\n\t/_/  \\_\\\t\t\t\t\t\t\t\t/_/  \\_\\\033[0m");
    printf("\033[1;31m\n\t\t\t\b\b _____     _____   _____   _____       _    _______");
    printf("\n\t\t\t\b\b|  __ \\   |  ___) |  ___) |  ___)     / \\  (__   __)");
    printf("\n\t\t\t\b\b| |  \\ \\  | |___  | |__   | |___     / _ \\    | |");
    printf("\n\t\t\t\b\b| |   ) ) |  ___) |  __)  |  ___)   / (_) \\   | |");
    printf("\n\t\t\t\b\b| |__/ /  | |___  | |     | |___   / .---. \\  | |");
    printf("\n\t\t\t\b\b|_____/   |_____) |_|     |_____) /_/     \\_\\ |_|");
    printf("\033[1;32m\n\t__    __\t\t\t\t\t\t\t\t__    __");
    printf("\n\t\\ \\  / /\t\t\t\t\t\t\t\t\\ \\  / /");
    printf("\n\t \\ \\/ /\t\t\t\t\t\t\t\t\t \\ \\/ /");
    printf("\n\t / /\\ \\\t\t\t\t\t\t\t\t\t / /\\ \\");
    printf("\n\t/_/  \\_\\\t\t\t\t\t\t\t\t/_/  \\_\\\033[0m\n\n");
}

void game_name(void)
{
    system("clear");
    printf("\n\n\n\n _______________________________________________________________________________________________________");
    printf("\n )    _____    ______    ______    ______   __     __       ______       _          _         _         (");
    printf("\n(    |  __ \\  |  ____|  |  ____|  |  ____|  \\ \\   / /      |  ____|     / \\        | |       | |         )");
    printf("\n )   | |  | | | |       | |       | |        \\ \\ / /       | |         /   \\       | |       | |        (");
    printf("\n(    | |__| | | |___    | |___    | |___      \\ v /        | |___     / .-. \\      | |       | |         )");
    printf("\n )   |  __ <  |  ___|   |  ___|   |  ___|      | |         |  ___|   /  (_)  \\     | |       | |        (");
    printf("\n(    | |  | | | |       | |       | |          | |         | |      /  .---.  \\    | |       | |         )");
    printf("\n )   | |__| | | |____   | |____   | |          | |         | |     /  /     \\  \\   | |____   | |____    (");
    printf("\n(    |_____/  |______|  |______|  |_|          |_|         |_|    /__/       \\__\\  |______|  |______|    )");
    printf("\n )______________________________________________________________________________________________________(\n");
}

#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "queries.h"
#include "drivers_structure.h"
#include "rides_structure.h"
#include "users_structure.h"
#include "parsing.h"
#include <unistd.h>

// Function very simillar to the main in the file programa-principal, it receives as an input a path to de .csv files
// and creates the correspondent hash tables
int programa_main (char *file){

    // Creating the path for the driver's data file.
    char *file_d = malloc (250*sizeof(char));
    strcpy(file_d,file);
    strcat(file_d,"/drivers.csv");

    // Creating the path for the user's data file.
    char *file_u = malloc (250*sizeof(char));
    strcpy(file_u,file);
    strcat(file_u,"/users.csv");

    // Creating the path for the ride's data file.
    char *file_r = malloc (250*sizeof(char));
    strcpy(file_r,file);
    strcat(file_r,"/rides.csv");

    // If the input is invalid, a message of error pops on screen and the programs restarts
    if(count_lines(file_d,file_u,file_r)==1){
        printw("INVALID PATH FILE!");
        refresh();
        napms(1000);
        move(10,0);
        clrtoeol();
        refresh();
        return 1;
    };
    
    // Allocating memory for the hash tables
    allocate_drivers();
    allocate_users();
    allocate_rides();
    allocate_rides_drivers();
    allocate_rides_users();
    allocate_rides_drivers_city();
    allocate_rides_drivers_gender();
    allocate_rides_date();

    // These functions are responsible for parsing each line of the data files. Furthermore,
    // also inserts the read values ​​(organized in a struct) into the hash table, row by row.
    read_store(file_d,'d');
    read_store(file_u,'u');
    read_store(file_r,'r');

    // Sorting a couple of hash tables
    sortQ2();
    sortQ3();

    // Freeing the strings used to open the data files.
    free(file_d);
    free(file_u);
    free(file_r);

    return 0;
}


// Function resposible for displaying a page of the output
void display_page (FILE * File, int start, int end, int n_linhas, int isLarge){

    rewind(File); // Restarts the reading process of the file
    int i;
    char buffer[250];

    // This portion of code deletes the previous printed lines
    if(isLarge==0){
        for(i=10;i<25;i++){
            move(i,0);
            clrtoeol();
        }
    }
    i=0;

    // Function resposible for reading the File and printing the lines of the respective page
    while(fgets(buffer, 250, File) != NULL){
        if(n_linhas==1){ // If the output only has 1 line, then it doesn´t print a line tracker
            move(10,0);
            printw("%s",buffer);
            break;
        }
        if(i>=start && i<end){ // If the output has moer than 1 line then it prints the lines of a page given in the callee function
            move(i%15+10,0);
            printw("%d - %s",i+1,buffer);
        }
        i++;
    }
    refresh(); // Refreshes the screen
}


 // Function responsible for the mechanism of using pages and interacting with them
void move_pages(FILE *File, WINDOW *win, int n_linhas, int sum){

    int isLarge=0;
    move(9,0); // Output given in the 9th line, row 0
    printw("OUTPUTS:");

    if(n_linhas>15){ // Printing helpful information so the user can understand how to interact with the program
        move(30,14);
        printw("MENU (Q)");
    }
    else { // Printing helpful information so the user can understand how to interact with the program
        move(n_linhas+11,0);
        printw("MENU (Q)");
        isLarge=1;
    }

    refresh();
    rewind(File); // Restarts the reading process of the file
    int start=0;
    int end=15;
    int botao;
    int flag=0;
    int pag=1;
    move(10,0);
    while(1){

    // We only display the possibility of changing pages if the output has more than one page (more than 15 lines of output)
    if(n_linhas>15){ // Printing helpful information so the user can understand how to interact with the program
        move(26,5);
        clrtoeol();
        printw("(<-) BACK [%d/%d] NEXT (->)",pag,n_linhas/15+sum); // Displays the page we are on and the total ammount of pages
        move(28,7);
        printw("(F) FIRST | LAST (L)");
        refresh();
    }


        if(flag==0) display_page(File,start,end,n_linhas,isLarge); // Function that writes the outputs on the screen
        
        flag=0;
        botao=wgetch(win); 

        switch (botao) // Waits for user input
        {
        case KEY_RIGHT: // If the right arroy is pressed, then (and only if possible) prints the next page on the screen
            start+=15;
            end+=15;
            if(end-15>=n_linhas){
                 start-=15;
                 end-=15;
                 flag=1;
            }
            else pag++;
            break;

        case KEY_LEFT: // If the right arroy is pressed, then (and only if possible) prints the previous page on the screen
            start-=15;
            end-=15;
            if(start<0){
                start=0;
                end=15;
            }
            else pag--;
            break;

        case 'f': // If the right arroy is pressed, then (and only if possible) print the first page on the screen
            if(n_linhas>15){
                start=0;
                end=15;
                pag=1;
            }
            break;

        case 'l': // If the right arroy is pressed, then (and only if possible) print the last page on the screen
            if(n_linhas>15){
                while(end<n_linhas){
                    start+=15;
                    end+=15;
                }
                pag=n_linhas/15+sum;
            }
            break;

        case 'q': // If the right arroy is pressed, it deletes all the outputs on the screen so that the user can input new information
            for(int i=0;i<30;i++){
            move(i+9,0);
            clrtoeol();
            }
            refresh();
            move(10,0);
            return;       
        }
    }
}


 // Function responsible for the mechanism of using the menu buttons and interacting with them
int interact_program(int highlight, WINDOW *win, int querie_possible){

    int i;

    // If this happens it means that the user pressed the option EXIT which kills the program and frees all 
    // the information used
    if(highlight==2){
        endwin(); //  Closes the window
        free_hash_drivers();
        free_hash_users();
        free_hash_rides();
        free_hash_rides_drivers();
        free_hash_rides_users();
        free_hash_rides_date();
        exit(0); // Kill the program
    }

    // If this happens it means that the user pressed the option EXECUTE QUERIES which executes a query given
    // as input by the user
    if(highlight==1){

        // This happens if the user tries to insert a query without inserting the .csv file path which 
        // is not possibe. It displays an error on the screen reminding the user that it needs to be
        // given other information before using the button
        if(querie_possible==0){
            printw("YOU NEED TO INSERT DATA FILES FIRST!");
            refresh();
            napms(1000); // The program freezes for the duration of a second so that the error is given as a pop up 
            move(10,0);
            clrtoeol();
            refresh();
            
            return 0;
        }

        move(10,0);
        printw(">> INSERT QUERY: ");  // Printing helpful information so the user can understand how to interact with the program
        char *input_q = malloc(250);
        int ch_q;
        int n_linhas=0;
        char buffer[250];
        echo();
        curs_set(1); // Activates the cursor so the user can write information
        for (i = 0; i < 250 - 1 && (ch_q = getch()) != '\n'; i++) // It stores the written information on an array (input_q)
        input_q[i] = ch_q;
        input_q[i] = '\0';
        curs_set(0); // Removes the cursor
        noecho();
        move(10,0);
        clrtoeol(); // Deletes what was outputted on the line it's in
        refresh();
        
        
        if (read_exe_queries_interactive(input_q)==0){ // This means that the .csv path files exist and are valid

            chdir("Resultados/"); // Changes directories to where the output file is stored (Resultados)

            FILE* File;
            File = fopen("command_output_interativo.txt","r"); // Opens the file of the respective query

            if(fgetc(File)==EOF){ // If the file is empty then it's printed on the screen that exact infomation

                printw("QUERY HAS NO OUTPUT!");
                remove("command_output_interativo.txt"); // It deletes the file
                move(12,6);
                printw("MENU (Q)");  // Printing helpful information so the user can understand how to interact with the program
                refresh();

                while(wgetch(win)!='q'); // Waits until the user does the only possible interaction with the program which is press the key Q restarting the program
                for(int i=9;i<30;i++){
                    move(i,0);
                    clrtoeol();
                }
                move(10,0);
                refresh();
                return 0;
            }

            rewind(File); // Restarts the reading process of the file
            
            while(fgets(buffer, 250, File) != NULL){ // Counts the number of lines in the output files
                n_linhas++;
            }

            if(n_linhas%15!=0) move_pages(File,win,n_linhas,1); // Helpful for knowing the total ammount of pages in the file
            else move_pages(File,win,n_linhas,0);


            remove("command_output_interativo.txt"); // Deletes the file
            chdir("trabalho-pratico"); // Changes to the main directory
            }


    else{ // This means that the .csv path files doesn´t exist or it is not valid valid
        printw("INVALID QUERY!");
        refresh();
        napms(1000); // The program freezes for the duration of a second so that the error is given as a pop up 
        move(10,0);
        clrtoeol();
        refresh();
    }   
    }

    // If this happens it means that the user pressed the option INSERT DATA FILES which reads the path of
    // the .csv files and starts all the hash tables and sorting methods
    if(highlight==0){
        printw(">> INSERT PATH TO DATA FILES: "); // Printing helpful information so the user can understand how to interact with the program
        mvwprintw(win, 2, 23, "          ");
        wrefresh(win);
        char *input = malloc(250);
        int ch;
        echo(); // Shows input
        curs_set(1);
        for (i = 0; i < 250 - 1 && (ch = getch()) != '\n'; i++) // It stores the written information on an array (input)
        input[i] = ch;
        input[i] = '\0';
        noecho();
        curs_set(0);
        mvwprintw(win, 2, 23, "[...]"); // Printing helpful information so the user can understand how to interact with the program
        wrefresh(win); // Refreshes the window
        clrtoeol();
        refresh();

        if(programa_main(input)==1){ 
            mvwprintw(win, 2, 23, "     "); // Printing helpful information so the user can understand how to interact with the program
            wrefresh(win);
            return 1;
        }
        else{ 
        mvwprintw(win, 2, 23, "[LOADED]"); // Printing helpful information so the user can understand how to interact with the program
        wrefresh(win); // Refreshes the window
        }
    }
    return 0;
}


// Main function responsible for the whole interactive mode
void interactive (){ 

    initscr(); // Initializes the screen
    noecho();  // Doesn´t show output
    int height = 7;
    int width = 100;
    int start_y = 2;

    WINDOW *win = newwin(height, width, start_y, 0); // Size and proportion of the created window
    box(win, 0, 0); // It draws a box around the window
    refresh();
    move(10,0);
    wrefresh(win); // Refreshes the window
    keypad(win,true);  // It inables the use of arroy keys to interact with the program
    mvwprintw(win, 0, 5, "GRUPO-32"); // Name shown on top of the box created
    curs_set(0); // Removes the cursor
    raw(); // This function disbles the possibility to kill the program with shortcuts such as CTRL+Z

    const char *options[]={"INSERT DATA FILES","EXECUTE QUERIES","EXIT"}; // The names of the button on the menu screen
    int choice;
    int highlight = 0;
    int i;
    int querie_possible=0;

    while(1){
            for(i=0;i<3;i++){
                if(i==highlight) wattron(win, A_REVERSE); // It highlights the button the user is on
                mvwprintw(win, i+2, 5, options[i]); // Prints the button names
                wattroff(win, A_REVERSE); // Highlights off
            }
            choice=wgetch(win); // Waits for user input

            switch(choice){

                // If the user clicks on the up arrow key, the button the user is currently on changes to the one above.
                // If there is no button on top of the one the user is on, then it changes the button the the last one.
                case KEY_UP:
                    highlight--;
                    if(highlight== -1) highlight=2;
                    break;
                
                // If the user clicks on the down arrow key, the button the user is currently on changes to the one below.
                // If there is no button below the one the user is on, then it changes the button the the first one.
                case KEY_DOWN:
                    highlight++;
                    if(highlight== 3) highlight=0;
                    break;  

                default:
                    break;              


            }

            if(choice == 10){ // This happens when the user presses ENTER in a button, activating it
                if(highlight==0) querie_possible++; // Checks if the .csv path files have already been inserted
                if(interact_program(highlight,win,querie_possible)==1) querie_possible--; // If it is possible then the program develops
            }
    }
}
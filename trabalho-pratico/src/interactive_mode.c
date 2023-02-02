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


int programa_main (char *file){

     // Criação do path para o ficheiro drivers.csv.
    char *file_d = malloc (100*sizeof(char));
    strcpy(file_d,file);
    strcat(file_d,"/drivers.csv");
    // Criação do path para o ficheiro users.csv.
    char *file_u = malloc (100*sizeof(char));
    strcpy(file_u,file);
    strcat(file_u,"/users.csv");
    // Criação do path para o ficheiro rides.csv.
    char *file_r = malloc (100*sizeof(char));
    strcpy(file_r,file);
    strcat(file_r,"/rides.csv");

    if(count_lines(file_d,file_u,file_r)==1){
        printw("INVALID PATH FILE!");
        refresh();
        napms(1000);
        move(10,0);
        clrtoeol();
        refresh();
        return 1;
    };
    
    allocate_drivers();
    allocate_users();
    allocate_rides();
    allocate_rides_drivers();
    allocate_rides_users();
    allocate_rides_drivers_city();
    allocate_rides_drivers_gender();
    allocate_rides_date();

    // Estas funções são responsáveis pelo parsing de cada linha dos ficheiros .csv. Para além disso,
    // também inserem os valores lidos (organizados numa struct) para a hash table, linha a linha. 
    read_store(file_d,'d');
    read_store(file_u,'u');
    read_store(file_r,'r');

    sortQ2();
    sortQ3();

    return 0;
    //read_exe_queries(file_txt,1,NULL);


    // free(file_d);
    // free(file_u);
    // free(file_r);
    
    // free_hash_drivers();
    // free_hash_users();
    // free_hash_rides();
    // free_hash_rides_drivers();
    // free_hash_rides_users();
    // free_hash_rides_date();

}


void go_back (int linha_inicial, FILE* file){
    char buffer[250];
    int contador=1;
    int aux=0;

    while(fgets(buffer, 250, file)!=NULL){
        if(linha_inicial==contador){
            aux++;
            printw("%s",buffer);
            refresh();


            if(aux==15) return; 

        }



    }


}








int interact_program(int highlight, WINDOW *win, int querie_possible){
    int i;

    if(highlight==2){ // SE PRECIONAR EXIT sai
        endwin();
        exit(0);
    }


































    if(highlight==1){

        if(querie_possible==0){
            printw("YOU NEED TO INSERT .CSV FILES FIRST!");
            refresh();
            napms(1000);
            move(10,0);
            clrtoeol();
            refresh();
            
            return 0;
        }
        int flag=0;
        int linha_atraso=-1;
        int repeticoes=0;
        move(10,0);
        printw("-> Insert querie: ");
        char *input_q = malloc(50);
        int ch_q;
        echo();
        curs_set(1);
        for (i = 0; i < 50 - 1 && (ch_q = getch()) != '\n'; i++)
        input_q[i] = ch_q;
        input_q[i] = '\0';
        curs_set(0);
        noecho();
        clrtoeol();
        refresh();
        
        
        if (read_exe_queries_interativo(input_q)==0){

            int botao;
            char buffer[250];
            int cont=0;
            chdir("Resultados/");
            FILE* File;
            File = fopen("command_output_interativo.txt","r");

            if(fgetc(File)==EOF){
                printw("Query has no output!");
                refresh();
                napms(1000);
                move(10,0);
                remove("command_output_interativo.txt");
                clrtoeol();
                refresh();
                return 0;
            }

            rewind(File);
            



            while(fgets(buffer, 250, File)!=NULL){
            
                if(linha_atraso==cont+1){
                    
                        printw("%s",buffer);
                        refresh();
                        cont++;

                        repeticoes++;
                        
                        if(repeticoes == 15){
                            repeticoes=0;
                            linha_atraso=-2;
                        }

                    linha_atraso++;
                }

                if(cont%15==0 && cont !=0){

                    // move(30,20);
                    // printw("NEXT ->");
                    // refresh();
                    
                    botao=wgetch(win);
                
                    if(botao==KEY_RIGHT){
                        for(int i=0;i<16;i++){  
                            move(i+10,0);
                            clrtoeol();
                        }

                        refresh();
                        move(10,0);
                    }





                                    
                    if(botao==KEY_LEFT){
                            rewind(File);
                            for(int i=0;i<=15;i++){
                                move(i+10,0);
                                clrtoeol();
                            }  

                            refresh();
                            move(10,0);

                            linha_atraso=cont-30;
                            cont=0;
                            flag=1;

                    }
                }

                    


                    if(botao==KEY_BACKSPACE){
                        for(int i=0;i<16;i++){
                        move(i+10,0);
                        clrtoeol();
                        }
                        refresh();
                        remove("command_output_interativo.txt");
                        chdir("trabalho-pratico");
                        return 0;
                    }

                

                    if(flag==0){

                        printw("%s",buffer);
                        refresh();
                        cont++;
                    }
                    flag=0;

                }
            //}

            while(1){
                botao=wgetch(win);
                if(botao==KEY_BACKSPACE){
                    for(int i=0;i<16;i++){
                    move(i+10,0);
                    clrtoeol();
                    }
                    refresh();
                    break;
                }
            }
            remove("command_output_interativo.txt");
            chdir("trabalho-pratico");
            }
    else{
        printw("INVALID QUERY!");
        refresh();
        napms(1000);
        move(10,0);
        clrtoeol();
        refresh();
    }
        
    


    }






    if(highlight==0){
        printw("-> Insert path to files .csv: ");
        char *input = malloc(50);
        int ch;
        echo();
        curs_set(1);
        for (i = 0; i < 50 - 1 && (ch = getch()) != '\n'; i++)
        input[i] = ch;
        input[i] = '\0';
        noecho();
        curs_set(0);
        mvwprintw(win, 2, 16, "[...]");
        wclrtoeol(win);
        wrefresh(win);
        clrtoeol();
        refresh();
        if(programa_main(input)==1){ 
            mvwprintw(win, 2, 16, "     ");
            wrefresh(win);
            return 1;
        }
        else{ 
        mvwprintw(win, 2, 16, "[LOADED]");
        wrefresh(win);
        }
    }
    return 0;
}






void interactive (){

    initscr();

    noecho();
    int height = 7;
    int width = 40;
    int start_y = 2;

    int cols=getmaxx(stdscr);
    //getmaxx(stdscr, rows, cols); // get the size of the terminal
    // creating a window
    WINDOW *win = newwin(height, width, start_y, (cols-40)/2);
    box(win, 0, 0);
    refresh();
    move(10,0);
    wrefresh(win);
    keypad(win,true);  // Podemos usar as setas
    mvwprintw(win, 0, 12.5, "MODO INTERATIVO");
    curs_set(0);  // Remove o cursor
    //raw(); // Faz com que não seja permitido dar kill ao programa com atalhos

    const char *options[]={"FILES .CSV","QUERIES","EXIT"};
    int choice;
    int highlight = 0;
    int i;

    int querie_possible=0;

    while(1){
            for(i=0;i<3;i++){
                if(i==highlight) wattron(win, A_REVERSE); // Highlight da opção escolhida
                mvwprintw(win, i+2, 5, options[i]); // Mover no menu
                wattroff(win, A_REVERSE); // Highlight off
            }
            choice=wgetch(win); // espera por input

            switch(choice){
                
                case KEY_UP:
                    highlight--;
                    if(highlight== -1) highlight=2;
                    break;
                
                case KEY_DOWN:
                    highlight++;
                    if(highlight== 3) highlight=0;
                    break;  

                default:
                    break;              


            }
            if(choice == 10){
                if(highlight==0) querie_possible++;
                if(interact_program(highlight,win,querie_possible)==1) querie_possible--; // SE o user precionar ENTER pára o loop

            }
    }

}


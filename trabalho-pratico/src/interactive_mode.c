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

// Função muito parecida à main, recebe como input o path para os ficheiros .csv e cria as hash tables correspondentes
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

    if(count_lines(file_d,file_u,file_r)==1){ // Caso o input for inválido aparece uma mensagem de erro no terminal e o programa reinicia
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

    free(file_d);
    free(file_u);
    free(file_r);

    return 0;

}


// Esta função é responsável por interagir com os 3 botões do programa
int interact_program(int highlight, WINDOW *win, int querie_possible){

    int i;
    if(highlight==2){   // SE A OPÇÃO ESCOLHIDA FOR A DE SAIR
        endwin(); //  Fecha a janela e liberta a memória consumida pelas hash tables
        free_hash_drivers();
        free_hash_users();
        free_hash_rides();
        free_hash_rides_drivers();
        free_hash_rides_users();
        free_hash_rides_date();
        exit(0); // Termina o programa
    }


    if(highlight==1){   // SE A OPÇÃO ESCOLHIDA FOR INSERIR AS QUERIES

        if(querie_possible==0){ // Este caso acontece se o utilizador tentar inserir as queries antes dos ficheiros .csv
            printw("YOU NEED TO INSERT .CSV FILES FIRST!");
            refresh();
            napms(1000); // O programa dá freeze durante 1 segundo
            move(10,0);
            clrtoeol();
            refresh();
            
            return 0;
        }

        int pag=1;
        int flag=0;
        int linha_atraso=-1;
        int repeticoes=0;
        move(10,0);
        printw("-> Insert querie: ");
        char *input_q = malloc(50);
        int ch_q;
        echo();
        curs_set(1); // Ativa o cursor
        for (i = 0; i < 50 - 1 && (ch_q = getch()) != '\n'; i++) // Este for loop lê o input introduzido pelo user e guarda-p no array input_q
        input_q[i] = ch_q;
        input_q[i] = '\0';
        curs_set(0); // Remove o cursor
        noecho();
        move(10,0);
        clrtoeol(); // Apaga o que foi escrito na linha escolhida
        refresh();
        
        
        if (read_exe_queries_interativo(input_q)==0){ // Isto acontece quando o path para os ficheiros .csv existe e é válido

            int botao;
            char buffer[250];
            int cont=0;
            chdir("Resultados/"); // Muda para a diretoria onde se encontra o ficheiro de output das queries
            FILE* File;
            File = fopen("command_output_interativo.txt","r"); // Abre o ficheiro do output da querie correspondente

            if(fgetc(File)==EOF){ // Caso o ficheiro de resultados estiver vazio, escrevemos na consola que a querie não mostra output
                printw("Query has no output!");
                refresh(); // Refresca a tela
                napms(1000); // Espera 1 segundo até executar a próxima instrução
                move(10,0);
                remove("command_output_interativo.txt"); // Elimina o ficheiro e dá reset ao programa
                clrtoeol();
                refresh();
                return 0;
            }

            rewind(File); // Faz com que as funções de leitura no ficheiro .txt comece novamente para inserir tudo corretamente
            
            move(9,2); // Escreve na 9ª coluna e 2ª linha do terminal a mensagem de texto
            printw("Outputs:");
            move(10,0);

            while(fgets(buffer, 250, File)!=NULL){ // Este while executa enquanto a função de leitura tiver linhas do .txt para ler
            
                if(linha_atraso==cont){ // Este é o caso em que queremos mostrar os 15 outputs anterioes usando a seta para a esquerda
                        move((cont)%15+10,0);
                        printw("%s",buffer,cont);
                        refresh();
                        cont++;

                        repeticoes++;
                        
                        if(repeticoes == 15){ // Quando ele fizer este processo 15 vezes, para porque apenas imprimimos na tela 15 linhas de output em cada página
                            repeticoes=0;
                            linha_atraso=-2;
                            while(cont%15!=0 && cont!=0)cont++; // Alinha o contador para o if seguinte
                        }
                    linha_atraso++;
                }
                else {

                if(cont%15==0 && cont !=0){ // Se existirem mais de 15 linhas de output no ficheiro .txt, então será necessário criar páginas para facilitar a visualização dos outputs

                    move(26,5);
                    printw("(<-) PREVIOUS | NEXT (->)"); // Escreve esta mensagem na tela para judar o utilizador a perceber como interagir com o programa
                    move(27,5);
                    printw("    CLEAN (BACKSPACE)"); // Escreve esta mensagem na tela para judar o utilizador a perceber como interagir com o programa
                    refresh();
                    move(10,0);
                    
                    botao=wgetch(win); // Função que lê a tecla que o utilizador primiu
                
                    if(botao==KEY_RIGHT){ // Se a tecla for a seta para a direita, então será necessário avançar uma página para a frente
                        pag++;
                        for(int i=0;i<16;i++){  
                            move(i+10,0);
                            clrtoeol();
                        }

                        refresh();
                        move(10,0);
                        flag=0;
                    }

                    if(botao==KEY_LEFT && pag==1) flag=1;
                    else if(botao==KEY_LEFT && pag>1){ // Se a tecla for a seta para a esquerda, então será necessário avançar uma página para trás
                            rewind(File); // Recomeça a leitura do ficheiro
                            for(int i=0;i<16;i++){
                                move(i+10,0);
                                clrtoeol();
                            }  

                            refresh();
                            move(10,0);
                            pag--;

                            linha_atraso=cont-30;

                            cont=0;
                            flag=1;

                    }
                }

                    if(botao==KEY_BACKSPACE){ // Se a tecla for a seta para o backspace, então será necessário apagar todo o output escrito e preparar o programa para proximas iterações com o utilizador
                        for(int i=0;i<30;i++){ // Apaga todas as linas de output
                        move(i+9,0);
                        clrtoeol();
                        }
                        refresh();
                        remove("command_output_interativo.txt"); // Apaga o ficheiro
                        chdir("trabalho-pratico"); // Muda para a diretoria principal
                        return 0;
                    }

                

                    if(flag==0){ // Aqui são onde os outputs da query são mostrados ao utlizador

                        printw("%s",buffer);
                        refresh();
                        cont++;
                    }
                    
                }
                }

            while(1){ // Se a tecla for a seta para o backspace, então será necessário apagar todo o output escrito e preparar o programa para proximas iterações com o utilizador
                botao=wgetch(win); // Lê a tecla primita pelo utilizador
                if(botao==KEY_BACKSPACE){
                    for(int i=0;i<30;i++){ // Apaga todas as linas de output
                    move(i+9,0);
                    clrtoeol();
                    }
                    refresh();
                    break;
                }
            }
            remove("command_output_interativo.txt"); // Apaga o ficheiro
            chdir("trabalho-pratico"); // Muda para a diretoria principal
            }


    else{ // Isto acontece quando o path para os ficheiros .csv existe e é válido
        printw("INVALID QUERY!");
        refresh();
        napms(1000); // Espera 1 segundo e em seguida apaga o que acabou de escrever
        move(10,0);
        clrtoeol();
        refresh();
    }   
    }


    if(highlight==0){   // SE A OPÇÃO ESCOLHIDA FOR INSERIR OS FICHEIROS .CSV
        printw("-> Insert path to files .csv: ");
        char *input = malloc(50);
        int ch;
        echo();
        curs_set(1);
        for (i = 0; i < 50 - 1 && (ch = getch()) != '\n'; i++) // Função de leitura do input do utilizador e guardada no array input
        input[i] = ch;
        input[i] = '\0';
        noecho();
        curs_set(0);
        mvwprintw(win, 2, 16, "[...]"); // Mostra a mensagem ao utilizador indicando que o ficheiro está a ser validado e carregado
        wclrtoeol(win); // Atualiza a janela
        wrefresh(win);
        clrtoeol();
        refresh();
        if(programa_main(input)==1){ 
            mvwprintw(win, 2, 16, "     ");
            wrefresh(win);
            return 1;
        }
        else{ 
        mvwprintw(win, 2, 16, "[LOADED]"); // Mostra a mensagem ao utilizador indicando que o ficheiro foi carregado com sucesso
        wrefresh(win);
        }
    }
    return 0;
}



// Função principal chamada pela main responsável pelo modo iterativo
void interactive (){ 

    initscr();  // Inicia a tela

    noecho();  // Não mostra o input
    int height = 7;
    int width = 40;
    int start_y = 2;

    int cols=getmaxx(stdscr); // Esta função permite saber qual é o tamanho na horizontal do terminal para centrar a janela

    WINDOW *win = newwin(height, width, start_y, (cols-40)/2);  // Tamanho e proporções da janela
    box(win, 0, 0);
    refresh();
    move(10,0);
    wrefresh(win);
    keypad(win,true);  // Podemos usar as setas
    mvwprintw(win, 0, 12.5, "MODO INTERATIVO"); // Nome do bloco
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
                wattroff(win, A_REVERSE); // Highlight desligado
            }
            choice=wgetch(win); // Espera por input

            switch(choice){
                
                case KEY_UP:  // Se o user clickar na seta cima, o botão selecionado é trocado
                    highlight--;
                    if(highlight== -1) highlight=2;
                    break;
                
                case KEY_DOWN:  // Se o user clickar na seta baixo, o botão selecionado é trocado
                    highlight++;
                    if(highlight== 3) highlight=0;
                    break;  

                default:
                    break;              


            }
            if(choice == 10){ 
                if(highlight==0) querie_possible++;  // Verifica se já foi inserido o path para os ficheiros .csv
                if(interact_program(highlight,win,querie_possible)==1) querie_possible--; // Se o user precionar ENTER pára o loop

            }
    }

}

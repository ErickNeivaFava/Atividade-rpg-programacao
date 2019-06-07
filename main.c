#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>

int main()
{
    srand(time(NULL));

    int dano=0;
    char tipo[]="";
    int vidaInimigo[2];
    int vidaPlayer[2];
    int classeAtt[6];
    int andar[2];
    int quantInimigo[2];
    int danoInimigo[5];
    int bd=0;

    int dificuldade;

    void escolherClasse(){
        int classe;
        printf("Bem vindo ao RPG SIMULADOR\n\n");
        printf("Escolha uma classe:\n\n[1]Barbaro\nDano (10-35)\nChance critica (15%)\nPrecisao (80%)\nEsquiva/bloqueio (20%)\nVida (100)\n\n[2]Duelista\nDano (5-15)\nChance critica (40%)\nPrecisao (100%)\nEsquiva/bloqueio (30%)\nVida (90)\n\n[3]Elementalista\nDano (20-35)\nChance critica (5%)\nPrecisao (95%)\nEsquiva/bloqueio (10%)\nVida (80)\n");
        scanf("%d",&classe);
        printf("\n");
        if (classe == 1){
            //barbaro
            classeAtt[1]=10;//danoMin
            classeAtt[2]=35;//danoMax
            classeAtt[3]=20;//miss chance
            classeAtt[4]=15;//crit chance
            classeAtt[5]=50;//dodge block
            classeAtt[6]=100;//vida
        }else if (classe == 2){
            //duelista
            classeAtt[1]=5;
            classeAtt[2]=15;
            classeAtt[3]=0;
            classeAtt[4]=40;
            classeAtt[5]=60;
            classeAtt[6]=90;
        }else if (classe == 3){
            //elementalista
            classeAtt[1]=20;
            classeAtt[2]=35;
            classeAtt[3]=5;
            classeAtt[4]=5;
            classeAtt[5]=40;
            classeAtt[6]=80;
        }else{
            printf("Classe invalida\n");
            escolherClasse();
        }
            vidaPlayer[1]=classeAtt[6];
            vidaPlayer[2]=vidaPlayer[1];
    }

    void escolherDificuldade(){

        printf("Escolha uma dificuldade:\n[1]Facil\n[2]Medio\n[3]Dificil\n");
        scanf("%d",&dificuldade);

        if (dificuldade==1){
            andar[1] = 3;
            quantInimigo[1] = 1;
            vidaInimigo[1]=20;

            danoInimigo[1] = 3;
            danoInimigo[2] = 5;
            danoInimigo[3] = 66;
            danoInimigo[4] = 1;
        }else if (dificuldade==2){
            andar[1] = 3;
            quantInimigo[1] = 3;
            vidaInimigo[1]=30;

            danoInimigo[1] = 4;
            danoInimigo[2] = 6;
            danoInimigo[3] = 33;
            danoInimigo[4] = 2;
        }else if (dificuldade==3){
            andar[1] = 3;
            quantInimigo[1] = 5;
            vidaInimigo[1]=40;

            danoInimigo[1] = 5;
            danoInimigo[2] = 7;
            danoInimigo[3] = 16.5;
            danoInimigo[4] = 3;
        }else{
            printf("Dificuldade invalida");
            escolherDificuldade();
        }
    }

    void levarDano(int danoMin, int danoMax, int accuracy, int critChance){

        int accuracyL = rand() % 100;
        int critChanceL = rand() % 100;
        dano = danoMin + (rand() % (danoMax-danoMin));

        if(accuracyL<accuracy){
            //miss
            dano = dano*0;
            strcpy(tipo,"Errou o ataque");
        }else{
            //hit
            if(critChanceL<=critChance){
                //crit
                dano = danoMax*2;
                strcpy(tipo,"Acerto critico!");
            }else{
                //normal
                dano = dano*1;
                strcpy(tipo,"Ataque normal");
            }
        }
    }

    //a função levarDano recebe (dano minimo, dano maximo, chance de errar, chance critica)

    void bloquearEsquivar(int blockDodge){

        levarDano(classeAtt[1],classeAtt[2],classeAtt[3],classeAtt[4]);
        int bdL = rand() % 100;

        if(blockDodge>=bdL){
            dano = dano*1.5;
            strcat(tipo," | Bloqueio/esquiva com sucesso");
            bd=1;
            //printf("Dano bloqueado/esquivado %d\n",bdL);
        }else if (blockDodge<=bdL){
            dano= dano*0.75;
            strcat(tipo," | Falha ao bloquear/esquivar");
            bd=0;
            //printf("Falha ao bloquear/esquivar %d\n",bdL);
        }
    }

    void acao(){
        int ac;
        printf("\n[1]Atacar\n[2]Defender/esquivar\n");
        scanf("%d",&ac);
        printf("\n");

        if(ac==1){
            levarDano(classeAtt[1],classeAtt[2],classeAtt[3],classeAtt[4]);

        }else if(ac==2){
            bloquearEsquivar(classeAtt[5]);
        }else{
            printf("Acao invalida\n");
            acao();
        }

    }

    escolherClasse();
    escolherDificuldade();
    system("@cls||clear");


    void atacar(){
                    while(vidaInimigo[2]>0){
                    acao();
                    printf("Voce ataca o inimigo(%d) e causa %d de dano (HP: %d - %d [%s])\n",quantInimigo[2],dano,vidaInimigo[2],dano,tipo);
                    vidaInimigo[2] = vidaInimigo[2] - dano;
                    if (vidaInimigo[2]>0){
                        levarDano(danoInimigo[1],danoInimigo[2],danoInimigo[3],danoInimigo[4]);
                        danoInimigo[5] = dano;
                        if (bd==0){
                            printf("O inimigo(%d) te ataca e causa %d de dano (HP: %d - %d [%s])\n",quantInimigo[2],danoInimigo[5],vidaPlayer[2],danoInimigo[5],tipo);
                            danoInimigo[5] = danoInimigo[5]*1.25;
                        }else{
                            printf("O inimigo(%d) te ataca e voce bloqueia/esquiva %d de dano (HP: %d - %d [%s])\n",quantInimigo[2],danoInimigo[5],vidaPlayer[2],danoInimigo[5]*0,tipo);
                            danoInimigo[5] = danoInimigo[5]*0;
                            bd=0;
                        }

                        vidaPlayer[2] = vidaPlayer[2]- danoInimigo[5];
                        if(vidaPlayer[2]<=0){
                            printf("\nVoce morreu\n");
                            system("PAUSE");
                            //return 0;
                        }
                    }
                }

    }
    while(vidaPlayer[2]>0){
        for(andar[2]=0;andar[2]<=andar[1];andar[2]++){
        quantInimigo[2]=quantInimigo[1];
            while(quantInimigo[2]>0){
                vidaInimigo[2] = vidaInimigo[1]+rand() % 10;
                printf("Um inimigo com %d de HP apareceu\n",vidaInimigo[2]);
                    atacar();
                if(quantInimigo[2]>0){
                    quantInimigo[2] = quantInimigo[2]-1;
                    printf("\nInimigo morto\n");
                    Sleep(1000);
                if (quantInimigo[2]==0){
                    printf("\nFim do andar %d\n",andar[2]);
                    Sleep(2000);
                    system("@cls||clear");

                    vidaPlayer[2] = vidaPlayer[2]*1.2;
                    if (vidaPlayer[2]>vidaPlayer[1]){
                        vidaPlayer[2]=vidaPlayer[1];
                    }
                    printf("\nVoce acha uma pocao de cura\nSua vida atual e %d/%dHP\n\n",vidaPlayer[2],vidaPlayer[1]);
                    }

                }
            }
        }
        system("@cls||clear");
        if(vidaPlayer[2]>0){
            vidaInimigo[2] = 150+rand() % 50;
            printf("\nVoce encontra um yasuo 0/15 te chamando pro x1 (%dHP)\n",vidaInimigo[2]);
            danoInimigo[1] = 5;
            danoInimigo[2] = 10;
            danoInimigo[3] = 5;
            danoInimigo[4] = 0;
            atacar();
        }


        printf("\nFim de jogo\n");
        //Sleep(5000);
        system("PAUSE");
        return 0;
    }
}

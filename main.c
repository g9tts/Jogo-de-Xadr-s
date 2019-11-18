#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <SDL.h>

#define WIDTH 640
#define HEIGHT 480

SDL_Window * window;
SDL_Renderer * render;



char xadrez [8][8] = {
    { 'T','C','B','Q','K','B','C','T' },
    { 'P','P','P','P','P','P','P','P' },
    { ' ',' ',' ',' ',' ',' ',' ',' ' },
    { ' ',' ',' ',' ',' ',' ',' ',' ' },
    { ' ',' ',' ',' ',' ',' ',' ',' ' },
    { ' ',' ',' ',' ',' ',' ',' ',' ' },
    { 'p','p','p','p','p','p','p','p' },
    { 't','c','b','q','k','b','c','t' }
};

int init_graficos(){

	if (SDL_Init( SDL_INIT_EVERYTHING ) >= 0 ) {
            printf("\n Inicializou o SDL...");
        window = SDL_CreateWindow("X A D R E Z",
        50, 50, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

        if (window != NULL) {
            render = SDL_CreateRenderer(window, -1, 0);
            if (render != NULL) {
			}

    }
	}
}


int pintarTela(){
    int w = WIDTH / 8;
    int h = HEIGHT / 8;
    int lin, col;


    SDL_SetRenderDrawColor( render, 0, 0, 0, 255);
    SDL_RenderClear(render);

    for (lin = 0; lin < 8 ; lin++) {
        for(col=0; col < 8; col++) {
            if ((col + lin) % 2 == 0){
                SDL_SetRenderDrawColor( render, 0, 0, 0, 255);
            } else{
                SDL_SetRenderDrawColor( render, 255, 255, 0, 255);
            }
            int x = col * w;
            int y = lin * h;
            SDL_Rect r = {x, y, w, h};
            SDL_RenderFillRect(render, &r);
        }
    }

    SDL_RenderPresent(render);
}
int pintarTelaTexto() {

	system("cls");

	int lin, col, r;

	for (lin = 0; lin < 8 ; lin++) {
		for(r = 0; r < 3; r++) {
			for(col=0; col < 8; col++) {

				char peca = xadrez[lin][col];
				char letra = ( (lin + col) % 2 == 0) ? '\xB2': ' ';

				letra = (r == 1 && peca != ' ') ? peca : letra;       //Operador Ternario
				if ( (lin + col) % 2 == 0) {

					printf("\xB2\xB2\%c\xB2\xB2", letra);
				}
				else {
					printf ("  %c  ", letra);
				}

			}
			printf("\n");

		}
	}
}

int moverPeca ( int linOri, int colOri, int linDes, int colDes){
	int mover = 0;
	char peca;
	int dV = abs(linDes - linOri);
	int dH = abs(colDes - colOri);

		if ((linOri >=0 && linOri < 8 && colOri >=0 && colOri < 8) &&
			(linDes >=0 && linDes < 8 && colDes >=0 && colDes < 8)) {

			peca = xadrez[linOri][colOri];

			if ((peca == 'T' || peca == 't' ) && (dV == 0 || dH == 0) ) {
				mover = 1;
			}
			if ((peca == 'B' || peca == 'b' ) && (dV == dH) ) {
				mover = 1;
			}
			if ((peca == 'C' || peca == 'c' ) &&
			( (dV == 1 && dH == 2)  || (dV == 2 && dH == 1) )) {
				mover = 1;
			}
			if ((peca == 'Q' || peca == 'q' ) &&
			((dV == dH) || (dV == 0) || dH == 0 ) ) {
				mover = 1;
			}
			if ((peca == 'K' || peca == 'k' ) &&
			((dV >= 0 && dV <= 1) && (dV >= 0 && dH <= 1)) ) {
				mover = 1;
			}
			if ((peca == 'P') && ((linDes - linOri) == 1) && (dH == 0)) {
				mover = 1;
			}
			if ((peca == 'p') && ((linOri - linDes) == 1) && (dH == 0)) {
				mover = 1;
			}
			if (mover) {
				xadrez[linDes][colDes] = xadrez[linOri][colOri];
				xadrez [linOri][colOri] = ' ';
				return 1;	// Movimento realizado
			}
				else {
					return 9; // Peça nao pode ser movida deste jeito
				}
	}
	else {
		return 0;
	}
}

int main(int argc, char ** args){
    init_graficos();

	int linOri,linDes, colOri, colDes;
	while (1) {
        pintarTela();
		pintarTelaTexto();
		printf("informe a linha e coluna de origem: ");
		scanf("%d %d", &linOri,&colOri);
		printf("\ninforme a linha e coluna de destino: ");
		scanf("%d %d", &linDes,&colDes);

		int resultado = moverPeca(linOri, colOri, linDes, colDes);
			if(resultado != 1){
				switch(resultado){
					case 9:
						printf("\nERRO: Peca nao pode ser movida desse jeito");
						getch();
						break;
					case 0:
						printf("\nERRO: Coordenadas invalidas");
						getch();
						break;
					case 1:
						break;

				}
			printf("\nERRO: Coordenadas invalidas!");
			getch();
		}

	}
    getch();
	return 0;
}

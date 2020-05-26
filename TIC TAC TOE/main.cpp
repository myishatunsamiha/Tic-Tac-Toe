#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))
#define SIZE    3
#define LARGE_VALUE INFINITY


int start_window = 1;
int window_height = 600;
int window_width = 800;
int one_player = 0;
int two_player = 0;
int play_again = 0;


int count_down = 0;
int turn = 2;
int cunt = 0;
int index_i, index_j;
int game_over = 0, win_move = 0;
int result;

int txt_x_tictactoe = 400-75;
int txt_y_tictactoe = 300+80;



int txt_x_playerno = 400-60;
int txt_y_playerno = 300-10;


int position[SIZE][SIZE];

typedef struct MATRIX{
    int tmat[SIZE][SIZE];
}board;

board m;


typedef struct BEST{
    int row, col;
}best_move;


float max_algo(board new_board, int depth);
float min_algo(board new_board, int depth);



void drawAxes()
{

        int x_co = 400, y_co = 300;

		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( x_co+100,y_co,0);
			glVertex3f(x_co-100,y_co,0);

			glVertex3f(x_co,y_co-100,0);
			glVertex3f(x_co, y_co+100,0);

			//glVertex3f(0,0, z+100);
			//glVertex3f(0,0,z-100);
		}glEnd();

}





void keyboardListener(unsigned char key, int x,int y){
	switch(key){

        case 'A':
            start_window = 1;

            // re-initializing
            window_height = 600;
            window_width = 800;
            one_player = 0;
            two_player = 0;
            play_again = 0;


            count_down = 0;
            turn = 2;
            cunt = 0;
            index_i, index_j;
            game_over = 0, win_move = 0;


            for(int i = 0; i < SIZE; i++){
                for(int j = 0; j < SIZE; j++){
                    m.tmat[i][j] = 0;
                }
            }

            break;
     /*   case 'r':
            flag = 0;

            red = 1;
            green = 0;
            blue = 0;
            break;
        case 'g':
            flag = 0;

            red = 0;
            green = 1;
            blue = 0;
            break;
        case 'b':
            flag = 0;

            red = 0;
            green = 0;
            blue = 1;
            break;*/
		default:
		   // flag = 0;
			break;
	}
}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			break;
		case GLUT_KEY_UP:		// up arrow key
			break;

		case GLUT_KEY_RIGHT:


			break;
		case GLUT_KEY_LEFT:


			break;

		case GLUT_KEY_PAGE_UP:
			break;
		case GLUT_KEY_PAGE_DOWN:
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}

int check_result(board m, int mov){
    int row_match, col_match, d1_match, d2_match;

    d1_match = 0;
    d2_match = 0;
    for(int i = 0; i < SIZE; i++){
        row_match = 0;
        col_match = 0;
        for(int j = 0; j < SIZE; j++){
            if(m.tmat[i][j] == mov){
                row_match++;
            }

            if(m.tmat[j][i] == mov){
                col_match++;
            }

            if(i == j){
                if(m.tmat[i][j] == mov){
                    d1_match++;
                }
            }

            if(i+j == SIZE-1){
                if(m.tmat[i][j] == mov){
                    d2_match++;
                }
            }
        }

        if(row_match == 3 || col_match == 3 || d1_match == 3 || d2_match ==3){
            return 1;
        }
    }

    return 0;
}


int is_full(board m){
    for(int i =0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(m.tmat[i][j] == 0){
                return 0;
            }
        }
    }

    return 1;
}


float utility(int mov, int depth){
    if(mov == 1){
        return 1.0/depth;
    }else if(mov == 2){
        return -1.0;
    }else{
        return 0.0;
    }
}


float find_max(float a, float b){
    if(a >= b){
        return a;
    }else{
        return b;
    }
}

float find_min(float a, float b){
    if(a <= b){
        return a;
    }else{
        return b;
    }
}


float max_algo(board new_board, int depth){
    if(check_result(new_board, 1) == 1){
        return utility(1, depth);
    }else if(check_result(new_board, 2) == 1){
        return utility(2, depth);
    }else if(is_full(new_board) == 1){
        return utility(0, depth);
    }

    board newb;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            newb.tmat[i][j] = new_board.tmat[i][j];
        }
    }

    float uti_max = -LARGE_VALUE;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(newb.tmat[i][j] == 0){
                newb.tmat[i][j] = 1;
                uti_max = find_max(uti_max, min_algo(newb, depth+1));
                newb.tmat[i][j] = 0;
            }
        }
    }

    return uti_max * 1.00;
}

float min_algo(board new_board, int depth){
    if(check_result(new_board, 1) == 1){
        return utility(1, depth);
    }else if(check_result(new_board, 2) == 1){
        return utility(2, depth);
    }else if(is_full(new_board) == 1){
        return utility(0, depth);
    }

    board newb;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            newb.tmat[i][j] = new_board.tmat[i][j];
        }
    }

    float uti_min = +LARGE_VALUE;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(newb.tmat[i][j] == 0){
                newb.tmat[i][j] = 2;
                uti_min = find_min(uti_min, max_algo(newb, depth+1));
                newb.tmat[i][j] = 0;
            }
        }
    }

    return uti_min * 1.00;
}

best_move choose_pc_move(){
    board new_board;
    float max_utiltiy = -LARGE_VALUE;
    float u;
    int depth = 1;

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            new_board.tmat[i][j] = m.tmat[i][j];
        }
    }

    best_move bm;
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(new_board.tmat[i][j] == 0){
                new_board.tmat[i][j] = 1;
                u = min_algo(new_board, depth);
                if(u > max_utiltiy){
                    max_utiltiy = u;
                    bm.row = i;
                    bm.col = j;
                }
                new_board.tmat[i][j] = 0;
            }
        }
    }

    return bm;
}


void check_turn(){
    if(turn == 2){
        turn = 1;
    }else if(turn == 1){
        turn = 2;
    }
}


void pc_turn(){
        best_move bm;
        bm = choose_pc_move();
    //    for(int i = 0; i < SIZE; i++){
      //      for(int j = 0; j < SIZE; j++){
        //        if(i == bm.row && j == bm.col){
        m.tmat[bm.row][bm.col] = 1;
          //      }
          //  }
        //}

        result = check_result(m, 1);
        if(result == 1){
            win_move = 1;
            game_over = 1;
        }

        if(is_full(m) == 1){
            game_over = 1;
        }
}

void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP

               std::cout << x << " " << y << std::endl;     //openGL's coordinate system



               if(start_window == 1){
                    if((x >= 400-70 && x <= 400+70) && (y >= 259 && y <= 317)){
                        one_player = 1;
                    }else if((x >= 400-70 && x <= 400+70) && (y >= 343 && y <= 404)){
                        two_player = 1;
                    }
                    start_window = 0;
               }else{


                if(two_player == 1){

                    if((x >= 195 && x <= 302) && (y >= 74 && y <= 175)){

                            index_i = 0, index_j = 0;

                            if(m.tmat[index_i][index_j] == 0){

                                if(turn == 1){
                                    m.tmat[index_i][index_j] = 1;
                                }else if(turn == 2){
                                    m.tmat[index_i][index_j] = 2;
                                }
                                check_turn();
                                cunt++;
                            }

                        }else if((x >= 313 && x <= 486) && (y >= 74 && y <= 175)){
                            index_i = 0, index_j = 1;

                            if(m.tmat[index_i][index_j] == 0){

                                if(turn == 1){
                                    m.tmat[index_i][index_j] = 1;
                                }else if(turn == 2){
                                    m.tmat[index_i][index_j] = 2;
                                }
                                check_turn();
                                cunt++;
                            }

                        }else if((x >= 495 && x <= 605) && (y >= 74 && y <= 175)){
                            index_i = 0, index_j = 2;

                            if(m.tmat[index_i][index_j] == 0){

                                if(turn == 1){
                                    m.tmat[index_i][index_j] = 1;
                                }else if(turn == 2){
                                    m.tmat[index_i][index_j] = 2;
                                }
                                check_turn();
                                cunt++;
                            }
                        }else if((x >= 195 && x <= 302) && (y >= 186 && y <= 386)){
                            index_i = 1, index_j = 0;

                            if(m.tmat[index_i][index_j] == 0){

                                if(turn == 1){
                                    m.tmat[index_i][index_j] = 1;
                                }else if(turn == 2){
                                    m.tmat[index_i][index_j] = 2;
                                }
                                check_turn();
                                cunt++;
                            }
                        }else if((x >= 313 && x <= 486) && (y >= 186 && y <= 386)){
                            index_i = 1, index_j = 1;

                            if(m.tmat[index_i][index_j] == 0){

                                if(turn == 1){
                                    m.tmat[index_i][index_j] = 1;
                                }else if(turn == 2){
                                    m.tmat[index_i][index_j] = 2;
                                }
                                check_turn();
                                cunt++;
                            }
                        }else if((x >= 495 && x <= 605) && (y >= 186 && y <= 386)){
                            index_i = 1, index_j = 2;

                            if(m.tmat[index_i][index_j] == 0){

                                if(turn == 1){
                                    m.tmat[index_i][index_j] = 1;
                                }else if(turn == 2){
                                    m.tmat[index_i][index_j] = 2;
                                }
                                check_turn();
                                cunt++;
                            }
                        }else if((x >= 195 && x <= 302) && (y >= 400 && y <= 501)){
                            index_i = 2, index_j = 0;

                            if(m.tmat[index_i][index_j] == 0){

                                if(turn == 1){
                                    m.tmat[index_i][index_j] = 1;
                                }else if(turn == 2){
                                    m.tmat[index_i][index_j] = 2;
                                }
                                check_turn();
                                cunt++;
                            }
                        }else if((x >= 313 && x <= 486) && (y >= 400 && y <= 501)){
                            index_i = 2, index_j = 1;

                            if(m.tmat[index_i][index_j] == 0){

                                if(turn == 1){
                                    m.tmat[index_i][index_j] = 1;
                                }else if(turn == 2){
                                    m.tmat[index_i][index_j] = 2;
                                }
                                check_turn();
                                cunt++;
                            }
                        }else if((x >= 495 && x <= 605) && (y >= 400 && y <= 501)){
                            index_i = 2, index_j = 2;

                            if(m.tmat[index_i][index_j] == 0){

                                if(turn == 1){
                                    m.tmat[index_i][index_j] = 1;
                                }else if(turn == 2){
                                    m.tmat[index_i][index_j] = 2;
                                }
                                check_turn();
                                cunt++;
                            }
                        }


                        result = check_result(m, 1);
                        if(result == 1){
                            win_move = 1;
                            game_over = 1;
                        }else{
                            result = check_result(m, 2);
                            if(result == 1){
                                win_move = 2;
                                game_over = 1;
                            }
                        }

                        if(is_full(m) == 1){
                            game_over = 1;
                        }

                }else if(one_player == 1){

                    if((x >= 195 && x <= 302) && (y >= 74 && y <= 175)){

                            index_i = 0, index_j = 0;

                            if(m.tmat[index_i][index_j] == 0){

                                if(turn == 2){
                                    m.tmat[index_i][index_j] = 2;
                                }
                                check_turn();
                                cunt++;
                            }

                    }else if((x >= 313 && x <= 486) && (y >= 74 && y <= 175)){
                            index_i = 0, index_j = 1;

                            if(m.tmat[index_i][index_j] == 0){

                                if(turn == 2){
                                    m.tmat[index_i][index_j] = 2;
                                }/*else if(turn == 2){
                                    board[index_i][index_j] = 2;
                                }*/
                                check_turn();
                                cunt++;
                            }

                    }else if((x >= 495 && x <= 605) && (y >= 74 && y <= 175)){
                            index_i = 0, index_j = 2;

                            if(m.tmat[index_i][index_j] == 0){

                                if(turn == 2){
                                    m.tmat[index_i][index_j] = 2;
                                }/*else if(turn == 2){
                                    board[index_i][index_j] = 2;
                                }*/
                                check_turn();
                                cunt++;
                            }
                    }else if((x >= 195 && x <= 302) && (y >= 186 && y <= 386)){
                            index_i = 1, index_j = 0;

                            if(m.tmat[index_i][index_j] == 0){

                                if(turn == 2){
                                    m.tmat[index_i][index_j] = 2;
                                }/*else if(turn == 2){
                                    board[index_i][index_j] = 2;
                                }*/
                                check_turn();
                                cunt++;
                            }
                    }else if((x >= 313 && x <= 486) && (y >= 186 && y <= 386)){
                            index_i = 1, index_j = 1;

                            if(m.tmat[index_i][index_j] == 0){

                                if(turn == 2){
                                    m.tmat[index_i][index_j] = 2;
                                }/*else if(turn == 2){
                                    board[index_i][index_j] = 2;
                                }*/
                                check_turn();
                                cunt++;
                            }
                    }else if((x >= 495 && x <= 605) && (y >= 186 && y <= 386)){
                            index_i = 1, index_j = 2;

                            if(m.tmat[index_i][index_j] == 0){

                                if(turn == 2){
                                    m.tmat[index_i][index_j] = 2;
                                }/*else if(turn == 2){
                                    board[index_i][index_j] = 2;
                                }*/
                                check_turn();
                                cunt++;
                            }
                    }else if((x >= 195 && x <= 302) && (y >= 400 && y <= 501)){
                            index_i = 2, index_j = 0;

                            if(m.tmat[index_i][index_j] == 0){

                                if(turn == 2){
                                    m.tmat[index_i][index_j] = 2;
                                }/*else if(turn == 2){
                                    board[index_i][index_j] = 2;
                                }*/
                                check_turn();
                                cunt++;
                            }
                    }else if((x >= 313 && x <= 486) && (y >= 400 && y <= 501)){
                            index_i = 2, index_j = 1;

                            if(m.tmat[index_i][index_j] == 0){

                                if(turn == 2){
                                    m.tmat[index_i][index_j] = 2;
                                }/*else if(turn == 2){
                                    board[index_i][index_j] = 2;
                                }*/
                                check_turn();
                                cunt++;
                            }
                    }else if((x >= 495 && x <= 605) && (y >= 400 && y <= 501)){
                            index_i = 2, index_j = 2;

                            if(m.tmat[index_i][index_j] == 0){

                                if(turn == 2){
                                    m.tmat[index_i][index_j] = 2;
                                }/*else if(turn == 2){
                                    board[index_i][index_j] = 2;
                                }*/
                                check_turn();
                                cunt++;
                            }
                    }

                    result = check_result(m, 2);
                    if(result == 1){
                        win_move = 2;
                        game_over = 1;
                    }

                    if(is_full(m) == 1){
                        game_over = 1;
                    }

                    if(is_full(m) == 0 && turn == 1){   // board not full and pc's turn
                       pc_turn();
                      check_turn();
                    }



                    }

                }
			}
			break;

		case GLUT_RIGHT_BUTTON:
		    if(state == GLUT_DOWN){
                std::cout << x << " " << y << std::endl;     //openGL's coordinate system

		    }
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}

void rec1(int a, int b){
    glBegin(GL_QUADS);{     // according to actual coordinate system. bottom left(0,0)
        glVertex3d( a,  b, 0);
        glVertex3d( a, -b, 0);
        glVertex3d(-a, -b, 0);
        glVertex3d(-a, b, 0);
    }
    glEnd();
}


void rec2(int a, int b){
    glBegin(GL_QUADS);{     // according to actual coordinate system. bottom left(0,0)
        glVertex3d( a,  b, 0);
        glVertex3d( a, -b, 0);
        glVertex3d(-a, -b, 0);
        glVertex3d(-a, b, 0);
    }
    glEnd();
}

void blankspace(){

}

void cross(int a, int b){
    glBegin(GL_QUADS);{     // according to actual coordinate system. bottom left(0,0)
        glVertex3d( -a,  a, 0);
        glVertex3d( -b, a, 0);
        glVertex3d(a, -a, 0);
        glVertex3d(b, -a, 0);


        glVertex3d( a,  a, 0);
        glVertex3d( b, a, 0);
        glVertex3d(-a, -a, 0);
        glVertex3d(-b, -a, 0);
    }
    glEnd();
}

void nought(float radius_x, float radius_y){


	int i = 0;
	float angle = 0.0;

    glPushMatrix();{
		glBegin(GL_POLYGON);{
            glColor3f(0,0,0);
            for(i = 0; i < int(1000); i++){
                angle = 2 * 3.1416 * i / 1000;
                glVertex3f (cos(angle) * (radius_x-10.00), sin(angle) * (radius_y-10.00), 0);
            }

        }

        glEnd();
    }glPopMatrix();

    glPushMatrix();{
		glBegin(GL_POLYGON);{
            glColor3f(1,1,0);
            for(i = 0; i < int(1000); i++){
			angle = 2 * 3.1416 * i / 1000;
			glVertex3f (cos(angle) * radius_x, sin(angle) * radius_y, 0);
            }
        }
        glEnd();
    }glPopMatrix();
}

void background_color(){
    glColor3f(1, 1, 0);
    glBegin(GL_QUADS);{
        glVertex2d(0,0);
        glVertex2d(window_width, 0);
        glVertex2d(window_width, window_height);
        glVertex2d(0, window_height);
    }glEnd();
}

void button(int a, int b){


    glColor3d(0, 1, 0);

    glBegin(GL_QUADS);{     // shows the inner box
        glVertex2d(400+a, 300+b);
        glVertex2d(400+a, 300-b);
        glVertex2d(400-a, 300-b);
        glVertex2d(400-a, 300+b);
    }glEnd();

    a = a + 10; b = b + 10;
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);{     // shows the outer white box
        glVertex2d(400+a, 300+b);
        glVertex2d(400+a, 300-b);
        glVertex2d(400-a, 300-b);
        glVertex2d(400-a, 300+b);
    }glEnd();

}

void showTextSmall(char text[], float r, float g, float b, int x, int y, int z)
{
    glColor3f(r, g, b);
    glRasterPos3f( x , y , z);
    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}

void showTextLarge(char text[], float r, float g, float b, int x, int y, int z)
{
    glColor3f(r, g, b);
    glRasterPos3f( x , y , z);
    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
}


void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//gluLookAt(0,0,0,	0,0,-1,	0,1,0);
	//gluLookAt(0,0,0,	0,0,0,	1,0,0);



	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects
	//drawAxes();

	if(start_window == 1){

        showTextLarge("TIC TAC TOE", 0, 0, 1, txt_x_tictactoe, txt_y_tictactoe, 0);
        showTextLarge("One Player", 0, 0, 0, txt_x_playerno, txt_y_playerno, 0);
        button(70, 20);

        glPushMatrix();{
            glTranslated(0, -80, 0);
            showTextLarge("Two Players", 0, 0, 0, txt_x_playerno, txt_y_playerno, 0);
            button(70, 20);
        }glPopMatrix();

        play_again = 0;

        background_color();

	}else if(game_over == 1 && count_down >= 200){


        if(one_player == 1){
            showTextLarge("GAME OVER", 0, 0, 1, 400-75, 300+50, 0);
            if(win_move == 1){
                showTextLarge("PC wins", 0, 0, 0, 400-50, 300, 0);
            //button(70, 20);
            }else if(win_move == 2){
                showTextLarge("User wins", 0, 0, 0, 400-50, 300, 0);
            }else{
                showTextLarge("Draw", 0, 0, 0, 400-50, 300, 0);
            }





        }else if(two_player == 1){
            showTextLarge("GAME OVER", 0, 0, 1, 400-75, 300+50, 0);
            if(win_move == 1){
                showTextLarge("Player-2 wins", 0, 0, 0, 400-70, 300, 0);
            //button(70, 20);
            }else if(win_move == 2){
                showTextLarge("Player-1 wins", 0, 0, 0, 400-70, 300, 0);
            }else{
                showTextLarge("Draw", 0, 0, 0, 400-50, 300, 0);
            }
        }

        glPushMatrix();{
                glTranslated(0, -80, 0);
                showTextLarge("Press 'A' To Play Again", 1, 0, 0, 400-110, 300, 0);
        }glPopMatrix();



        background_color();

	}else{
	// create board





	if(one_player == 1 || two_player == 1){

        if(one_player == 1){
            showTextSmall("PC -> X", 0.8, 0.7, 0, 20, 540, 0);
            showTextSmall("USER -> O", 0.8, 0.7, 0, 20, 520, 0);
        }else if(two_player == 1){
            showTextSmall("Player-1 -> O", 0.8, 0.7, 0, 20, 540, 0);
            showTextSmall("Player-2 -> X", 0.8, 0.7, 0, 20, 520, 0);
        }

        // create board
        for(int i = -90; i <= 90 ; i += 180){
            glPushMatrix();{

                glTranslatef(i+400, 300, 0);
                glColor3d(0, 0, 1);
                rec1(5, 200);
            }glPopMatrix();
        }

        for(int i = -100; i <= 100 ; i += 200){
            glPushMatrix();{

                glTranslatef(400, i+300, 0);
                glColor3d(0, 1, 0);
                rec1(200, 5);
            }glPopMatrix();
        }


            int r, c;
            // board[0][0]
            glPushMatrix();{
                glTranslatef(400-150, 300+150, 0);
                glColor3d(0, 1, 0);

                r = 0; c = 0;
                if(m.tmat[r][c] == 0){
                    blankspace();
                }else if(m.tmat[r][c] == 1){
                    cross(30, 15);
                }else if(m.tmat[r][c] == 2){
                    nought(30.0, 30.0);
                }
            }glPopMatrix();


            // board[0][1]
            glPushMatrix();{
                glTranslatef(400, 300+150, 0);
                glColor3d(0, 1, 0);
                r = 0; c = 1;
                if(m.tmat[r][c] == 0){
                    blankspace();
                }else if(m.tmat[r][c] == 1){
                    cross(30, 15);
                }else if(m.tmat[r][c] == 2){
                    nought(30.0, 30.0);
                }
            }glPopMatrix();

            // board[0][2]
            glPushMatrix();{
                glTranslatef(400+150, 300+150, 0);
                glColor3d(0, 1, 0);
                r = 0; c = 2;
                if(m.tmat[r][c] == 0){
                    blankspace();
                }else if(m.tmat[r][c] == 1){
                    cross(30, 15);
                }else if(m.tmat[r][c] == 2){
                    nought(30.0, 30.0);
                }
            }glPopMatrix();




            // board[1][0]
            glPushMatrix();{
                glTranslatef(400-150, 300, 0);
                glColor3d(0, 1, 0);

                r = 1; c = 0;
                if(m.tmat[r][c] == 0){
                    blankspace();
                }else if(m.tmat[r][c] == 1){
                    cross(30, 15);
                }else if(m.tmat[r][c] == 2){
                    nought(30.0, 30.0);
                }
            }glPopMatrix();


            // board[1][1]
            glPushMatrix();{
                glTranslatef(400, 300, 0);
                glColor3d(0, 1, 0);

                r = 1; c = 1;
                if(m.tmat[r][c] == 0){
                    blankspace();
                }else if(m.tmat[r][c] == 1){
                    cross(30, 15);
                }else if(m.tmat[r][c] == 2){
                    nought(30.0, 30.0);
                }

            }glPopMatrix();


            // board[1][2]
            glPushMatrix();{
                glTranslatef(400+150, 300, 0);
                glColor3d(0, 1, 0);
                r = 1; c = 2;
                if(m.tmat[r][c] == 0){
                    blankspace();
                }else if(m.tmat[r][c] == 1){
                    cross(30, 15);
                }else if(m.tmat[r][c] == 2){
                    nought(30.0, 30.0);
                }
            }glPopMatrix();





            // board[2][0]
            glPushMatrix();{
                glTranslatef(400-150, 300-150, 0);
                glColor3d(0, 1, 0);
                r = 2; c = 0;
                if(m.tmat[r][c] == 0){
                    blankspace();
                }else if(m.tmat[r][c] == 1){
                    cross(30, 15);
                }else if(m.tmat[r][c] == 2){
                    nought(30.0, 30.0);
                }
            }glPopMatrix();


            // board[2][1]
            glPushMatrix();{
                glTranslatef(400, 300-150, 0);
                glColor3d(0, 1, 0);
                r = 2; c = 1;
                if(m.tmat[r][c] == 0){
                    blankspace();
                }else if(m.tmat[r][c] == 1){
                    cross(30, 15);
                }else if(m.tmat[r][c] == 2){
                    nought(30.0, 30.0);
                }
            }glPopMatrix();



            // board[2][2]
            glPushMatrix();{
                glTranslatef(400+150, 300-150, 0);
                glColor3d(0, 1, 0);
                r = 2; c = 2;
                if(m.tmat[r][c] == 0){
                    blankspace();
                }else if(m.tmat[r][c] == 1){
                    cross(30, 15);
                }else if(m.tmat[r][c] == 2){
                    nought(30.0, 30.0);
                }
            }glPopMatrix();


        }else{
            start_window = 1;
        }


	}


	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}



void animate(){
    if(game_over == 1){
        count_down++;
    }


	//codes for any changes in Models, Camera
	glutPostRedisplay();    // after pressing a button it is redisplaying the entire scenario again and again
}

void init(){
	//codes for initialization

	for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            m.tmat[i][j] = 0;
        }
	}

	/************************
	/ set-up projection here
	************************/



	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	gluOrtho2D(0, 800, 0, 600);
	//gluPerspective(100,	1,	800, 800);

}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color


    glutCreateWindow("GAME WINDOW");

	init();





	glEnable(GL_DEPTH_TEST);	//enable Depth Testing
	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

}

#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <time.h>   

#define SIZE 20

using namespace std;

char area[SIZE][SIZE];

class Maze{
	private:
		char area2[SIZE][SIZE];
		
	public:
		
		void mazeBorder(){
			for(int i = 0; i < SIZE; i++){
				for(int j = 0; j < SIZE; j++){
					if(i == 0 || j == 0 || i == SIZE-1 || j == SIZE-1){
						area2[i][j] = '#';
					 }
					else {
						area2[i][j] = ' ';						
					}
				}
			}
		}
		
		void wayToWin(){
			char area3[SIZE][SIZE] = {
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ','c','c',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
				{' ',' ','c','c',' ',' ',' ',' ',' ',' ',' ',' ','c','c','c',' ',' ',' ',' ',' '},
				{' ','c','c','c',' ',' ','c','c','c','c','c',' ','c',' ','c',' ',' ',' ',' ',' '},
				{' ',' ',' ','c','c',' ','c',' ',' ',' ','c',' ','c',' ','c','c','c',' ',' ',' '},
				{' ',' ',' ',' ','c',' ','c','c','c',' ','c','c','c',' ',' ',' ','c','c',' ',' '},
				{' ',' ',' ',' ','c',' ',' ',' ','c',' ',' ',' ',' ',' ',' ',' ',' ','c',' ',' '},
				{' ',' ',' ',' ','c',' ',' ',' ','c',' ',' ',' ',' ',' ',' ',' ',' ','c','c',' '},
				{' ',' ',' ','c','c','c','c','c','c',' ',' ',' ',' ',' ',' ',' ',' ',' ','c',' '},
				{' ',' ',' ','c',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','c',' '},
				{' ','c','c','c',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','c',' '},
				{' ','c',' ',' ',' ',' ',' ',' ','c','c','c',' ',' ',' ',' ','c','c','c','c',' '},
				{' ','c',' ',' ',' ',' ',' ',' ','c',' ','c',' ',' ',' ',' ','c',' ',' ',' ',' '},
				{' ','c','c',' ',' ',' ',' ',' ','c',' ','c','c','c','c','c','c','c','c',' ',' '},
				{' ',' ','c',' ','c','c','c',' ','c',' ',' ','c',' ',' ',' ',' ',' ','c','c',' '},
				{' ',' ','c','c','c',' ','c',' ','c',' ',' ','c',' ',' ',' ',' ',' ',' ','c',' '},
				{' ',' ',' ',' ',' ',' ','c',' ','c',' ',' ','c',' ',' ',' ',' ',' ',' ','c',' '},
				{' ',' ',' ',' ',' ',' ','c','c','c',' ',' ','c','c','c','c','c','c','c','c',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','c',' ','c',' ',' '},
				{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},};
				
			for(int i = 0; i<SIZE; i++){
				for(int j = 0; j<SIZE; j++){
					if(area3[i][j] == 'c'){
						area2[i][j] = area3[i][j];
					}
				}
			}	
		}
		
		void mazeWall(){
			srand(time(NULL));
			for(int i = 0; i <180; i++){
				int wall_x = rand() % SIZE-1;
				int wall_y = rand() % SIZE-1;
				if(area2[wall_y][wall_x] == ' '){
					area2[wall_y][wall_x] = '#';	
				}
				else {
					while(area2[wall_y][wall_x] != ' '){
						wall_x = rand() % SIZE-1;
						wall_y = rand() % SIZE-1;
					};
				}
			}
		}
		
		void mazeBomb(){
			srand(time(NULL));
			for(int i =0; i<90; i++){
				int bx = rand() % SIZE-1;
				int by = rand() % SIZE-1;
				if (area2[by][bx] == ' ') {
					area2[by][bx] = 'B';	
				}
				else {
					while(area2[by][bx] != ' '){
						bx = rand() % SIZE-1;
						by = rand() % SIZE-1;
					};
					area2[by][bx] = 'B';
				}
			}
		}
			
		void moreSetting(){
			area2[1][1] = '$';
			area2[18][18] = 'E';
		}
		
		void changePvToPublic(){
			for	(int i = 0; i < SIZE; i++){
				for(int j = 0; j < SIZE; j++){
					::area[i][j] = area2[i][j];
				}
			}	
		}
		
		void printMaze(){
			COORD pos = {0, 0};
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
			for(int i=0; i<SIZE; i++){
				for(int j=0; j<SIZE; j++){
					if (::area[i][j] == '#') cout<< (char)219<< (char)219<< (char)219;
					else if(::area[i][j] == 'B') cout <<" B ";
					else if(::area[i][j] == '$') cout <<" ! ";
					else if(::area[i][j] == 'E') cout <<"End";
					else cout<<"   ";
				}
				cout<<endl;
			}	
		}
};


class Player:public Maze{
	public:		
		COORD score;
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		int i = 1 , j = 1 , s = 0;
		int player_life = 2;
		bool bomb = true;
		
		void showConsoleCursor  (bool showFlag) {   
			HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);   
			CONSOLE_CURSOR_INFO     cursorInfo;   
			GetConsoleCursorInfo(out, &cursorInfo);   
			cursorInfo.bVisible = showFlag;   
			SetConsoleCursorInfo(out, &cursorInfo); 
		}
		
		void movePlayer(){
			char get_key;
			while (player_life != 0 && checkWin()){
				while(checkWin() && checkBomb()){
					get_key = _getch();
					
					while(get_key != 'w' && get_key != 'a' && get_key != 's' && get_key != 'd'){
						system("cls");
						printMaze();
						system("color 04");
						cout<<"\n ** Error ** \n\n You Can Move With ( w , a , s , d) "<<endl;
						get_key = _getch();
						system("color 0b");
						system("cls");
					};
					
					switch(get_key){
						case 'w':
							if(::area[i-1][j] != '#' ){
								::area[i][j] = ' ';
								i--;
								if(::area[i][j] == 'B'){
									player_life --;
									if(player_life == 0){
										bomb = false;	
									}
								}
								::area[i][j] = '$';	
								s++;						
							}
							break;
							
						case 'a':
							if(::area[i][j-1] != '#'){
								::area[i][j] = ' ';
								j--;
								if(::area[i][j] == 'B'){
									player_life --;
									if(player_life == 0){
										bomb = false;
									}
								}
								::area[i][j] = '$';	
								s++;						
							}
							break;
							
						case 's':
							if(::area[i+1][j] != '#'){
								::area[i][j] = ' ';
								i++;
								if(::area[i][j] == 'B'){
									player_life --;
									if(player_life == 0){
										bomb = false;
									}
								}
								::area[i][j] = '$';	
								s++;
							}
							break;
							
						case 'd':
							if(::area[i][j+1] != '#'){
								::area[i][j] = ' ';
								j++;
								if(::area[i][j] == 'B'){
									player_life --;
									if(player_life == 0){
										bomb = false;
									}
								}
								::area[i][j] = '$';	
								s++;						
							}
							break;
					}	
					printMaze();		
					scoreShow();
					playerLife();
				};					
			};
		}
		
		bool checkWin(){
			bool win = true;
			if(i == SIZE-2 && j == SIZE-2)
				win = false;
			return win;
		}
		
		bool checkBomb(){
			
			return bomb;
		}
	
		void scoreShow(){
			score = {65 , 10};
			SetConsoleCursorPosition(h,score);
			if(checkWin())
				cout<<"Move : "<<s;
			else
				cout<<"Your Score is : "<<s<<endl;
		}
		
		void playerLife(){
			COORD show_life;
			show_life={65, 3};
			SetConsoleCursorPosition(h,show_life);
			cout<<"Life: "<<player_life;
		}
		
		void finish(){
			COORD finish ;
			finish = {2 , 24};
			SetConsoleCursorPosition(h,finish);
			if(!checkWin()){
				cout<<"You Win , Good Job.  ";
			}
			else {
				cout<<" Game Over  ";
			}
		}
};	

int main(int argc, char** argv) {
	system("color 4f");
	cout<<"You Can Move Your Player With (W , A , S , D)\n"<<endl;
	cout<<"Notice : 1) B is Bomb :) \n\n\t 2) You Have 2 Lives in Game \n"<<endl;
	cout<<"* Press Enter To Start *"<<endl;
	cin.get();
	system("cls");
	
	system("color 0b");
	Maze a;
	a.mazeBorder();
	a.wayToWin();
	a.mazeWall();
	a.mazeBomb();
	a.moreSetting();
	a.changePvToPublic();
	a.printMaze();
	
	Player b;
	b.showConsoleCursor(false);
	b.movePlayer();
	b.finish();
	
	char z;
	do{
		cout<<"Do you want to Play again? (y / n)"<<endl;
		z = _getch();
		
		while(z!='y' && z!='n'){
			z = _getch();		
		};
		
	    if (z=='y') {
	    	system("cls");
	    	
	    	system("color 0b");	    	 	
			Maze a;
			a.mazeBorder();
			a.wayToWin();
			a.mazeWall();
			a.mazeBomb();
			a.moreSetting();
			a.changePvToPublic();
			a.printMaze();
			
			Player b;
			b.showConsoleCursor(false);
			b.movePlayer();
			b.finish();
		}
		else{
			cout<<"\n    Thanks For Playing ... \n\n** Press 'ENTER' to EXIT **"<<endl;
			cin.get();
		}	
	}while(z!='n');
	
	return 0;
}
	// ba tashakor az amoozeshaye khob va kameleton 

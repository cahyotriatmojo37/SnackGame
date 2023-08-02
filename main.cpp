#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <iomanip>
#include <ctype.h>

using namespace std;

struct node {
    int value;
    struct node *next;
};

struct node *head=NULL;
struct node *tail=NULL;
int xScore=61;
int yScore=1;

//LeaderBoard
char topP[20][4] = {"AAA","BBB","CCC","DDD","EEE","FFF","GGG","HHH","III","JJJ","KKK","LLL","MMM","NNN","OOO","PPP","QQQ","RRR","SSS","TTT"};
char dificulty[20][7] = {"Hard","Normal","Easy","Hard","Normal","Easy","Hard","Normal","Easy","Hard","Normal","Easy","Hard","Normal","Easy","Hard","Normal","Easy","Hard","Normal"};
int scoreP[20] = {5,4,3,5,4,3,5,2,1,5,3,2,5,4,3,4,5,3,2,5};

void bubblesort(int n, char name[][4], char dif[][7],int score []){
	int tempS;
	char tempN[500];
	char tempD[500];

	for(int i = 0; i < n ; i++){
		for(int j = 0 ; j < n - i - 1 ; j++){
			if(score[j] < score[j+1]){
				tempS=score[j];
				score[j]=score[j+1];
				score[j+1]=tempS;

				strcpy(tempN,name[j]);
            	strcpy(name[j],name[j+1]);
            	strcpy(name[j+1],tempN);

				strcpy(tempD,dif[j]);
            	strcpy(dif[j],dif[j+1]);
            	strcpy(dif[j+1],tempD);
			}
		}
	}
}


// movement function
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool isEmpty(){
    return head==NULL;
}

void insert(int data){
    if (isEmpty()){
        node *bantuan=new node();
        bantuan->value=data;
        bantuan->next=NULL;
        head=bantuan;
        tail=bantuan;
    } else {
        node *bantuan=new node();
        bantuan->value=data;
        bantuan->next=NULL;
        tail->next=bantuan;
        tail=bantuan;
    }
}

void display(){
    struct node *isi=head;
    xScore=69;
    while(isi!=NULL){
        gotoxy(xScore,yScore);cout<<isi->value;
        xScore--;
        isi=isi->next;
    }
}

// slow down anim
void slow()
{
    float a = 1;
    do
    {
        a = a + 0.04;
    } while (a < 1000000);
}

// arena
void arena()
{
    for (int i = 1; i < 69; i++)
    {
        for (int j = 1; j < 22; j++)
        {
            gotoxy(i, j);
            cout << " ";
        }
    }
}

// arena boundary
void bounds()
{
    gotoxy(0, 0);
    printf("%c", 218);
    gotoxy(0, 24);
    printf("%c", 192);
    gotoxy(21, 1);
    printf("ASDW : bergerak, ESC : keluar");
    for (int x = 1; x < 70; x++)
    {
        gotoxy(x, 0);
        printf("%c", 196);
        gotoxy(x, 2);
        printf("%c", 196);
        gotoxy(x, 24);
        printf("%c", 196);
    }
    gotoxy(70, 0);
    printf("%c", 191);
    gotoxy(70, 24);
    printf("%c", 217);
    for (int y = 1; y < 24; y++)
    {
        gotoxy(0, y);
        printf("%c", 179);
        gotoxy(70, y);
        printf("%c", 179);
    }
    gotoxy(0, 2);
    printf("%c", 195);
    gotoxy(70, 2);
    printf("%c", 180);
}

int acakX(){
    int x=rand();
    if(x<2)
        return (x%69)+2;
    else
        return (x%69);
}

int acakY(){
    int y=rand();
    if((y%23)<5)
        return (y%23)+5;
    else
        return (y%23);
}

void addPlayerLeaderboard(char name[], char difP[], int sc){
	int n = sizeof(scoreP) / sizeof(scoreP[0]);
	int min;

	min = scoreP[0];
	for(int i = 0 ; i < n ; i++){
		if(scoreP[i] < min){
			min = i;
		}
	}
    //strcpy = untuk mengcopy string
	strcpy(topP[min],name);
	strcpy(dificulty[min],difP);
	scoreP[min] = sc;


}

void game(int d, char nP[], char dP[])
{
    char key;

    //Size Array
    int n = sizeof(scoreP) / sizeof(scoreP[0]);

	//darah hero
	int health;

    // Posisi awal hero
    int xHero = 10;
    int yHero = 5;
    int xHeroPrev = xHero + 1;
    int yHeroPrev = yHero;

    // Hero Kena hit
    float invisible = 0.1;

	// Waktu pengurangan Skor
	int minSkor;

    // Batas Gerak
    int tAtas = 2;
    int tBawah = 24;
    int tKanan = 70;
    int tKiri = 0;

    // Posisi awa.l enemy
    float xEnemy = 50;
    float yEnemy = 22;
    float xEnemyPrev = xEnemy + 1;
    float yEnemyPrev = yEnemy;

    // langkah enemy & darah hero & detik
    float lEnemy;
    if(d == 1){
    	lEnemy = 0.25;
    	health = 5;
    	minSkor = 15;

	}
	else if(d == 2){
		lEnemy = 0.5;
		health = 3;
		minSkor = 10;
	}
	else if(d == 3){
		lEnemy = 0.75;
		health = 1;
		minSkor = 5;
	}

    int score=0;

    // int xScore=69;
    // int yScore=1;
    //fruit
    srand(time(0));
    int xFruit=acakX();
    int yFruit=acakY();

    arena();
    // clear area
    bounds();
    // create arena

	gotoxy(xScore,yScore);
	printf("Score: %d",score);

	//Penanda buah
	int fruitPin = 0;

//	do{
//		xFruit = acakX();
//		yFruit = acakY();
//	}while(xFruit <= 1 || xFruit >= 23 && yFruit <= 2 || yFruit >= 23 );
	xFruit = 40;
	yFruit = 10;

    gotoxy(xFruit,yFruit);cout<<"*";

    //dummy cek detik
    float cariDetik = 0;

    int a = 0;

    do
    {
        //mulai cek detik
        cariDetik+=0.05;
        gotoxy(3,4);printf(" Detik : %.0f  ",cariDetik);
        if ((int)cariDetik >= minSkor)
        {
        	if(score == 0){
        		cariDetik = 0;
				score = 0;
				gotoxy(xScore,yScore);
				printf("Score: %d",score);
			}
			else{
            cariDetik=0;
            score--;
            gotoxy(xScore,yScore);
			printf("Score: %d",score);
            }
        }

        // Menghilangkan jejak Hero dan Enemy
        gotoxy(xHeroPrev, yHeroPrev);
        printf(" ");

		// Membuat buah tidak hilang ketika musuh mengenai buah
        if((int)xEnemy == xFruit  && (int)yEnemy == yFruit){
    		fruitPin = 1;
    		gotoxy(xEnemyPrev, yEnemyPrev);
    		printf(" ");
		}
		else if(fruitPin == 1){
			fruitPin = 0;
			gotoxy(xEnemyPrev, yEnemyPrev);
			printf("*");
		}
		else{
			gotoxy(xEnemyPrev, yEnemyPrev);
    		printf(" ");
		}

        // Memunculkan Hero dan Enemy
        gotoxy(xHero, yHero);
        printf("H");
        gotoxy(xEnemy, yEnemy);
        printf("O");

        // Deteksi Tombol
        if (kbhit())
        {
            key = getch();
        }

        if (toupper(key) == 'W') // ke atas
        {
            xHeroPrev = xHero;
            yHeroPrev = yHero;
            yHero--;
            if (yHero <= tAtas)
                yHero = tAtas + 1;
        }
        if (toupper(key) == 'A') // ke kiri
        {
            xHeroPrev = xHero;
            yHeroPrev = yHero;
            xHero--;
            if (xHero <= tKiri)
                xHero = tKiri + 1;
        }
        if (toupper(key) == 'S') // ke bawah
        {
            xHeroPrev = xHero;
            yHeroPrev = yHero;
            yHero++;
            if (yHero >= tBawah)
                yHero = tBawah - 1;
        }
        if (toupper(key) == 'D') // ke kanan
        {
            xHeroPrev = xHero;
            yHeroPrev = yHero;
            xHero++;
            if (xHero >= tKanan){
            	xHero = tKanan - 1;
			}
        }

//      ALgoritma Kejar Hero
        if (xEnemy > xHero){ // enemy di kanan hero
            xEnemyPrev = xEnemy;
            xEnemy -= lEnemy;
		}
		else{ // enemy di kiri hero
            xEnemyPrev = xEnemy;
            xEnemy += lEnemy;
        }

        if (yEnemy <= yHero){ // enemy di atas hero
            yEnemyPrev = yEnemy;
            yEnemy += lEnemy;
        }
		else{ // enemy di bawah kero
            yEnemyPrev = yEnemy;
            yEnemy -= lEnemy;
        }

        // Deteksi Buah Dimakan Hero
        if((xHero==xFruit) && (yHero==yFruit))
        {
            score++;
            gotoxy(xScore,yScore);
			cout << "Score: " << score;

            if (score>=5)
            {
                gotoxy(10,10);
                break;
            }

            do{
				xFruit = acakX();
				yFruit = acakY();
			}while(xFruit <= 1 || xFruit >= 23 && yFruit <= 2 || yFruit >= 23 );

            gotoxy(xFruit,yFruit);cout<<"*";
            cariDetik=0;
        }

        if(((int)xEnemy==xHero) && ((int)yEnemy==yHero))
        {
        	if((int)invisible == 0){
				invisible = 1;
            	health -= 0.2;
        	}
        	else{
        		invisible -= 0.1;
			}
        }

        gotoxy(4,22);
        cout<<"Health: "<<health<<endl;

        slow();

    } while (key!= 27 && health > 0 || score == 5 );

    gotoxy(0, 26);
    if(health > 0){
    	cout<<"Selamat, anda memenangkan Game ini !";
    	addPlayerLeaderboard(nP,dP,score);
    	getchar();
    	system("cls");

	}
	else{
		cout<<"Anda kalah!";
		addPlayerLeaderboard(nP,dP,score);
		getchar();
		system("cls");

	}
}

void leaderBoard(){
	int n = sizeof(scoreP) / sizeof(scoreP[0]);
	int size;

	int slct;
	char nameL[20][4];
	char difL[20][7];
	int scoreL[20] = {0};
	int k = 0;

	int tempS;
	char tempN[500];
	char tempD[500];



	do{
		k = 0;
		system("cls");
		cout<<"Pilih dificulty leaderboard pemain yang ingin ditampilkan!"<<endl;
		cout<<"1.Easy"<<endl;
		cout<<"2.Normal"<<endl;
		cout<<"3.Hard"<<endl;
		cout<<"4.Kembali"<<endl;
		cout<<"Masukan Pilihan: ";
		cin>>slct;

		switch(slct){
			case 1:
				system("cls");
				for(int i = 0 ; i < n ; i++){
					if(strcmp(dificulty[i],"Easy" ) == 0){
						strcpy(nameL[k],topP[i]);
						strcpy(difL[k],dificulty[i]);
						scoreL[k] = scoreP[i];
						k++;

					}
				}
                //setw = fungsinya memberi spasi huruf
				bubblesort(k,nameL,difL,scoreL);
				cout<<"==========================================="<<endl;
				cout<<"|\t\t Leaderboard\t\t  |"<<endl;
				cout<<"==========================================="<<endl;
				cout<<"|" << setw(6) <<	"Name" << setw(3) << "|" << setw(15) <<	"Difficulty" << setw(6) << "|" << setw(8)	<< "Score" <<	setw(4) << "|" <<endl;
				cout<<"==========================================="<<endl;
				for(int i = 0 ; i < k ; i++){
					cout <<"|"<< setw(5) << nameL[i] << setw(4) <<"|"<< setw(12) << difL[i] << setw(9) <<"|"<< setw(6) << scoreL[i] << setw(6) << "|" <<endl;
				}
				cout<<"==========================================="<<endl;
				cout<<"Pencet tombol apa saja untuk lanjut....";
				getchar();	getchar();

				break;
			case 2:
				system("cls");
				for(int i = 0 ; i < n ; i++){
					if(strcmp(dificulty[i],"Normal" ) == 0){
						strcpy(nameL[k],topP[i]);
						strcpy(difL[k],dificulty[i]);
						scoreL[k] = scoreP[i];
						k++;
					}
				}

				bubblesort(k,nameL,difL,scoreL);
				cout<<"==========================================="<<endl;
				cout<<"|\t\t Leaderboard\t\t  |"<<endl;
				cout<<"==========================================="<<endl;
				cout<<"|" << setw(6) <<	"Name" << setw(3) << "|" << setw(15) <<	"Difficulty" << setw(6) << "|" << setw(8)	<< "Score" <<	setw(4) << "|" <<endl;
				cout<<"==========================================="<<endl;
				for(int i = 0 ; i < k ; i++){
					cout <<"|"<< setw(5) << nameL[i] << setw(4) <<"|"<< setw(12) << difL[i] << setw(9) <<"|"<< setw(6) << scoreL[i] << setw(6) << "|" <<endl;
				}
				cout<<"==========================================="<<endl;
				cout<<"Pencet tombol apa saja untuk lanjut....";
				getchar();	getchar();
				break;
			 case 3:
				system("cls");
				for(int i = 0 ; i < n ; i++){
					if(strcmp(dificulty[i],"Hard" ) == 0){
						strcpy(nameL[k],topP[i]);
						strcpy(difL[k],dificulty[i]);
						scoreL[k] = scoreP[i];
						k++;

					}
				}

				bubblesort(k,nameL,difL,scoreL);
				cout<<"==========================================="<<endl;
				cout<<"|\t\t Leaderboard\t\t  |"<<endl;
				cout<<"==========================================="<<endl;
				cout<<"|" << setw(6) <<	"Name" << setw(3) << "|" << setw(15) <<	"Difficulty" << setw(6) << "|" << setw(8)	<< "Score" <<	setw(4) << "|" <<endl;
				cout<<"==========================================="<<endl;
				for(int i = 0 ; i < k ; i++){
					cout <<"|"<< setw(5) << nameL[i] << setw(4) <<"|"<< setw(12) << difL[i] << setw(9) <<"|"<< setw(6) << scoreL[i] << setw(6) << "|" <<endl;
				}
				cout<<"==========================================="<<endl;
				cout<<"Pencet tombol apa saja untuk lanjut....";
				getchar();	getchar();
				break;
			case 4:
				break;
			default:
				cout<<"Pilih dengan benar!!!";
				getchar(); getchar();
		}
	}while(slct != 4);
	system("cls");

}

int main(){
	int select;
	int dif;

	char name[5];
	char difP[10];

	char s;

	int len;

	do{
		system("cls");
		cout<<"Selamat datang di game!"<<endl;
		cout<<"1.Play"<<endl;
		cout<<"2.Leaderboard"<<endl;
		cout<<"3.Exit"<<endl;
		cout<<"Masukan Pilihan: ";
		cin>>select;
		switch(select){
			case 1:
				system("cls");

				do{
					cout<<"Masukan nama: ";
					cin>>name;
					len = strlen(name);
					if(len !=3){
						cout<<"Nama harus mempunyai 3 karakter pas tidak boleh lebih atau kurang";
						getchar(); getchar();
						system("cls");
					}

				}while(len != 3);

				for(int i = 0 ; i < len ; i++){  //len = panjang kata
				  s = toupper(name[i]);
				  name[i] = s;
				}

				do{

					cout<<"Silahkan pilih tingkat kesusahan game!"<<endl;
					cout<<"1.Easy"<<endl;
					cout<<"2.Normal"<<endl;
					cout<<"3.Hard"<<endl;
					cout<<"Masukan Pilihan: ";
					cin>>dif;

                    //strcpy = untuk mengcopy string

					if(dif == 1){
						strcpy(difP,"Easy");
					}
					else if(dif == 2){
						strcpy(difP,"Normal");
					}
					else if(dif == 3){
						strcpy(difP,"Hard");
					}
					else{
						cout<<"Pilih dengan benar!!!";
						getchar(); getchar();
						system("cls");
					}
				}while(dif > 3 || dif <= 0 );

				system("cls");
				cout<<"Game akan dimulai tekan tombol apapun untuk memulai....";
				getchar(); getchar();
				game(dif,name,difP);
				break;
			case 2:
				leaderBoard();
				break;
			case 3:
				system("cls");
				break;
			default:
				cout<<"Pilih dengan benar!!!";
				getchar(); getchar();
				break;
		}
	}while(select != 3);
}

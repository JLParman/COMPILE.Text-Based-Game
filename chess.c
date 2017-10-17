#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>

//Mini Chess rules: PAWNS can only move and eat forward; no Horses;
//Sample Commands:
//move wp1 to 13
//move 12 to 13
//wp1 to 13
//12 to 13
//eat 13 with 12
//eat bp1 with 12
//eat 13 with wp1
//eat bp1 with wp1


//Chess pieces: index 0=King, 1=Queen, 2-3=Rook, 4-5=Bishop, 6-11=Pawn, if location is 0=piece is taken
//initialized values are locations on board
int Player1[12]={31,41,11,61,21,51,12,22,32,42,52,62}; //0,0,0,0,0,0};
int Player2[12]={36,46,16,66,26,56,15,25,35,45,55,65};
int Boardtiles[6][6]= {{11,12,13,14,15,16},{21,22,23,24,25,26},{31,32,33,34,35,36},{41,42,43,44,45,46},{51,52,53,54,55,56},{61,62,63,64,65,66}};
int gameover=0;

void main(){

printf("Welcome to Mini Chess\n\n");

drawboard(Boardtiles,Player1,Player2);
do{
	
if(gameover==0){
	player1turn(Boardtiles,Player1,Player2);
	gameover=checkGamestatus(Player1,Player2);
}

if(gameover==0){
	player2turn(Boardtiles,Player1,Player2);
	gameover=checkGamestatus(Player1,Player2);
}

}while(gameover==0);
getch();

}

drawboard(int Boardtiles[6][6], int Player1[], int Player2[]){
int x,y,pieceindex;

	system("cls");
	printf("   |  1  |  2  |  3  |  4  |  5  |  6  |\n");
		for(y=0;y<6;y++){
			printf(" %d |",y+1);
			for(x=0;x<6;x++){
				whatpiece(Boardtiles,Player1,Player2,x,y);
			}
			printf("\n");
		}			
}

int whatpiece(int Boardtiles[6][6], int Player1[], int Player2[], int x, int y, int flag){
int a; 				//index for location on board
int pieceindex=12; //12 is default "  " 
char piece[2]; 		//To print chess piece letter
flag=0;				//if flag is 0 = no match has been found; else if 1=piece found for player 1, flag=2 piece found for player 2
	
	//looks for the index of the piece to print on the current tile
		for(a=0;pieceindex!=a && a<12;a++){      
			if(Boardtiles[x][y]==Player1[a]){	//for player 1 pieces
				pieceindex=a;
				flag=1;
			}
		}
	if(flag==0){
		for(a=0;pieceindex!=a && a<12;a++){		//for player 2 pieces
			if(Boardtiles[x][y]==Player2[a])
				pieceindex=a;
				flag=2;
		}
	}	
				if (flag==1){
				
					switch(pieceindex){ //converts index to the equivalent piece for player 1
			
						case 0 : strcpy(piece, "WK ");
								break;
						case 1 : strcpy(piece, "WQ ");
								break;
						case 2 : strcpy(piece, "WR1");
								break;
						case 3 : strcpy(piece, "WR2");
								break;
						case 4 : strcpy(piece, "WB1");
								break;
						case 5 : strcpy(piece, "WB2");
								break;
						case 6 : strcpy(piece, "WP1");
								break;
						case 7 : strcpy(piece, "WP2");
								break;
						case 8 : strcpy(piece, "WP3");
								break;
						case 9 : strcpy(piece, "WP4");
								break;
						case 10 : strcpy(piece, "WP5");
								break;
						case 11 : strcpy(piece, "WP6");
								break;
						case 12 : strcpy(piece, "   ");
								break;
					}
				}
				else
				if (flag==2){
					
					switch(pieceindex){ //converts index to the equivalent piece for player 2
					
						case 0 : strcpy(piece, "BK ");
								break;
						case 1 : strcpy(piece, "BQ ");
								break;
						case 2 : strcpy(piece, "BR1");
								break;
						case 3 : strcpy(piece, "BR2");
								break;
						case 4 : strcpy(piece, "BB1");
								break;
						case 5 : strcpy(piece, "BB2");
								break;
						case 6 : strcpy(piece, "BP1");
								break;
						case 7 : strcpy(piece, "BP2");
								break;
						case 8 : strcpy(piece, "BP3");
								break;
						case 9 : strcpy(piece, "BP4");
								break;
						case 10 : strcpy(piece, "BP5");
								break;
						case 11 : strcpy(piece, "BP6");
								break;
						case 12 : strcpy(piece, "   ");
								break;
					}
				}
				printf(" %s |",piece);
}

player1turn(int BoardTiles[6][6], int Player1[], int Player2[]){
char piece[10],cp[10], command[10], cp2[10]; //piece is the 'K1' while cp is 'K' only
int Location,Destination; //location and destination of the piece
int valid=0;
int index;
int a = 0, b = 0;

do{
	printf("\nPlayer 1's Turn\n What's' your move? ");
	scanf("%[^\n]%*c",piece);
	
	char *token = strtok(piece, " ");

	int z = 0;
	char array[4][10];
	while(token){
		strcpy(array[z], token);
		strcpy(array[z], toUpperCase(array[z]));
		token = strtok(NULL, " ");
		z++;
	}
    
    int current;
    int loc, des;
    
    if(strcmp(array[0], "MOVE") == 0 && strcmp(array[2], "TO") == 0){ // MOVE <player1 piece or location of apiece> TO <destination>
		b = 1;
		if(isAPiece(array[1]) == 1){
			strcpy(cp, array[1]);
		}
		else if(isALocation(array[1]) == 1){
			int ctrb = 0, checker = 0, anum = atoi(array[1]);			
			while(ctrb < 12 && checker == 0){
				if(anum == Player1[ctrb]){
					checker = 1;
					if(ctrb == 0)strcpy(cp,"WK");
					else if(ctrb == 1)strcpy(cp,"WQ");
					else if(ctrb == 2)strcpy(cp,"WR1");
					else if(ctrb == 3)strcpy(cp,"WR2");
					else if(ctrb == 4)strcpy(cp,"WB1");
					else if(ctrb == 5)strcpy(cp,"WB2");
					else if(ctrb == 6)strcpy(cp,"WP1");
					else if(ctrb == 7)strcpy(cp,"WP2");
					else if(ctrb == 8)strcpy(cp,"WP3");
					else if(ctrb == 9)strcpy(cp,"WP4");
					else if(ctrb == 10)strcpy(cp,"WP5");
					else if(ctrb == 11)strcpy(cp,"WP6");
				}
				ctrb++;
			}
		}
		else{
			printf("Unidentified Action");
		}
		if(isALocation(array[3]) == 1){
			strcpy(cp2,array[3]);
			a = 1;
		}
		else{
			printf("Invalid Move");
		}
	}
	else if(strcmp(array[1], "TO") == 0){ // <player1 piece or location of p1's piece> TO <destination>
		b = 1;
		if(isAPiece(array[0]) == 1){
			strcpy(cp, array[0]);
		}
		else if(isALocation(array[0]) == 1){
			int ctrb = 0, checker = 0, anum = atoi(array[0]);			
			while(ctrb < 12 && checker == 0){
				if(anum == Player1[ctrb]){
					checker = 1;
					if(ctrb == 0)strcpy(cp,"WK");
					else if(ctrb == 1)strcpy(cp,"WQ");
					else if(ctrb == 2)strcpy(cp,"WR1");
					else if(ctrb == 3)strcpy(cp,"WR2");
					else if(ctrb == 4)strcpy(cp,"WB1");
					else if(ctrb == 5)strcpy(cp,"WB2");
					else if(ctrb == 6)strcpy(cp,"WP1");
					else if(ctrb == 7)strcpy(cp,"WP2");
					else if(ctrb == 8)strcpy(cp,"WP3");
					else if(ctrb == 9)strcpy(cp,"WP4");
					else if(ctrb == 10)strcpy(cp,"WP5");
					else if(ctrb == 11)strcpy(cp,"WP6");
				}
				ctrb++;
			}
		}
		else{
			printf("Unidentified Action");
		}
		if(isALocation(array[2]) == 1){
			strcpy(cp2,array[2]);
			a = 1;
		}
		else{
			printf("Invalid Move");
		}
	}
	else if(strcmp(array[0], "EAT") == 0 && strcmp(array[2], "WITH") == 0){ //EAT <player2 piece or a location of p2's piece> WITH <player 1 piece or a location of p1's piece>
		b = 1;
		if(isAPiece(array[3]) == 1){
			strcpy(cp, array[3]);
		}
		else if(isALocation(array[3]) == 1){
			int ctrb = 0, checker = 0, anum = atoi(array[3]);			
			while(ctrb < 12 && checker == 0){
				if(anum == Player1[ctrb]){
					checker = 1;
					if(ctrb == 0)strcpy(cp,"WK");
					else if(ctrb == 1)strcpy(cp,"WQ");
					else if(ctrb == 2)strcpy(cp,"WR1");
					else if(ctrb == 3)strcpy(cp,"WR2");
					else if(ctrb == 4)strcpy(cp,"WB1");
					else if(ctrb == 5)strcpy(cp,"WB2");
					else if(ctrb == 6)strcpy(cp,"WP1");
					else if(ctrb == 7)strcpy(cp,"WP2");
					else if(ctrb == 8)strcpy(cp,"WP3");
					else if(ctrb == 9)strcpy(cp,"WP4");
					else if(ctrb == 10)strcpy(cp,"WP5");
					else if(ctrb == 11)strcpy(cp,"WP6");
				}
				ctrb++;
			}
		}
		else{
			printf("Unidentified Action");
		}
		if(isALocation(array[1]) == 1){
			int ctrc = 0,anum1 = atoi(array[1]);
			while(ctrc < 12){
				if(Player2[ctrc] == anum1){
					strcpy(cp2,array[1]);
					a = 1;
				}
				ctrc++;
			}
		}
		else{
			char aString[10];
			if(strcmp(array[1],"BK") == 0){itoa(Player2[0],aString,10);strcpy(cp2,aString);a=1;}
			else if(strcmp(array[1],"BQ") == 0){itoa(Player2[1],aString,10);strcpy(cp2,aString);a=1;}
			else if(strcmp(array[1],"BR1") == 0){itoa(Player2[2],aString,10);strcpy(cp2,aString);a=1;}
			else if(strcmp(array[1],"BR2") == 0){itoa(Player2[3],aString,10);strcpy(cp2,aString);a=1;}
			else if(strcmp(array[1],"BB1") == 0){itoa(Player2[4],aString,10);strcpy(cp2,aString);a=1;}
			else if(strcmp(array[1],"BB2") == 0){itoa(Player2[5],aString,10);strcpy(cp2,aString);a=1;}
			else if(strcmp(array[1],"BP1") == 0){itoa(Player2[6],aString,10);strcpy(cp2,aString);a=1;}
			else if(strcmp(array[1],"BP2") == 0){itoa(Player2[7],aString,10);strcpy(cp2,aString);a=1;}
			else if(strcmp(array[1],"BP3") == 0){itoa(Player2[8],aString,10);strcpy(cp2,aString);a=1;}
			else if(strcmp(array[1],"BP4") == 0){itoa(Player2[9],aString,10);strcpy(cp2,aString);a=1;}
			else if(strcmp(array[1],"BP5") == 0){itoa(Player2[10],aString,10);strcpy(cp2,aString);a=1;}
			else if(strcmp(array[1],"BP6") == 0){itoa(Player2[11],aString,10);strcpy(cp2,aString);a=1;}
			else{
				printf("Invalid Move");
			}
		}
	}else{
		printf("Invalid Command\n");
	}
	
//    strcpy(cp, token);					//tokenizing inputs
//    token = strtok(NULL, " ");			//cp is the chesspiece to move
//    strcpy(command, token);				//command is moveto
//    token = strtok(NULL, " ");			//cp2 is the destination
//    strcpy(cp2, token);
    
//    a = isALocation(cp2);
//    b = isACommand(command);
//    toUpperCase(cp);
    
    //next lines of code are to determine what piece is moved and/or eaten.
    
    if(a == 1 && b == 1){
    	des = atoi(cp2);
    	if(strcmp(cp,"WK") == 0 ){
    		loc = Player1[0];
    		index=0;
    		valid=moveKing(Player1,des,loc,index);
    			if (valid==1){
    				checkEat(Player2,des);
				}
		}
		else if(strcmp(cp,"WQ") == 0){
    		loc = Player1[1];
    		index=1;
    		valid=moveQueen(Player1,des,loc,index);
				if (valid==1){
		    		checkEat(Player2,des);	
				}
		}
		else if(strcmp(cp,"WR1") == 0 ){
    		loc = Player1[2];
    		index=2;
  			valid=moveRook(Player1,des,loc,index);
  				if (valid==1){
		    		checkEat(Player2,des);	
				}
		}
		else if(strcmp(cp,"WR2") == 0){
    		loc = Player1[3];
    		index=3;
    		valid=moveRook(Player1,des,loc,index);
  				if (valid==1){
		    		checkEat(Player2,des);	
				}
		}
		else if(strcmp(cp,"WB1") == 0){
    		loc = Player1[4];
    		index=4;
	   		valid=moveBishop(Player1,des,loc,index);
  				if (valid==1){
		    		checkEat(Player2,des);	
				}
		}
		else if(strcmp(cp,"WB2") == 0){
    		loc = Player1[5];
    		index=5;
    		valid=moveBishop(Player1,des,loc,index);
  				if (valid==1){
		    		checkEat(Player2,des);	
				}
		}
    	else if(strcmp(cp,"WP1") == 0 ){
    		loc = Player1[6];
    		index=6;
    		valid=movePawn1(Player1,des,loc,index);
		    	if (valid==1){
		    		checkEat(Player2,des);	
				}
		}
		else if(strcmp(cp,"WP2") == 0){
    		loc = Player1[7];
    		index=7;
    		valid=movePawn1(Player1,des,loc,index);
		    	if (valid==1){
		    		checkEat(Player2,des);	
				}
		}
		else if(strcmp(cp,"WP3") == 0 ){
    		loc = Player1[8];
    		index=8;
    		valid=movePawn1(Player1,des,loc,index);
    			if (valid==1){
		    		checkEat(Player2,des);	
				}
		}
		else if(strcmp(cp,"WP4") == 0){
    		loc = Player1[9];
    		index=9;
    		valid=movePawn1(Player1,des,loc,index);
    			if (valid==1){
		    		checkEat(Player2,des);	
				}
		}
		else if(strcmp(cp,"WP5") == 0){
    		loc = Player1[10];
    		index=10;
    		valid=movePawn1(Player1,des,loc,index);
    			if (valid==1){
		    		checkEat(Player2,des);	
				}
		}
		else if(strcmp(cp,"WP6") == 0){
    		loc = Player1[11];
    		index=11;
    		valid=movePawn1(Player1,des,loc,index);
    			if (valid==1){
		    		checkEat(Player2,des);	
				}
		}
		else{
			valid=0;
			printf("\n\nMOVE INVALID");
		}
	//end of code for checking moved/eaten pieces.
		printf("\n\n");
		drawboard(Boardtiles,Player1,Player2); //draw new board layout
	}
	else
		valid=0;
	
}while(valid!=1 || b!=1);

}

//Basically same with player1turn function but for player 2.

player2turn(int BoardTiles[6][6], int Player1[], int Player2[]){
char input[10],cp[10], command[10], cp2[10]; //piece is the 'K1' while cp is 'K' only
int Location,Destination; //location and destination of the piece
int valid=0;
int index;
int a = 0, b = 0;

do{
	printf("\nPlayer 2's Turn\n What's' your move? ");
	scanf("%[^\n]%*c",input);
	
	char *token = strtok(input, " ");
	
	int z = 0;
	char array[4][10];
	while(token){
		strcpy(array[z], token);
		strcpy(array[z], toUpperCase(array[z]));
		token = strtok(NULL, " ");
		z++;
	}
    
    int current;
    int loc, des;
    
    if(strcmp(array[0], "MOVE") == 0 && strcmp(array[2], "TO") == 0){ // MOVE <player2 piece or location of P2'S piece> TO <destination>
		b = 1;
		if(isAPiece(array[1]) == 1){
			strcpy(cp, array[1]);
		}
		else if(isALocation(array[1]) == 1){
			int ctrb = 0, checker = 0, anum = atoi(array[1]);			
			while(ctrb < 12 && checker == 0){
				if(anum == Player2[ctrb]){
					checker = 1;
					if(ctrb == 0)strcpy(cp,"BK");
					else if(ctrb == 1)strcpy(cp,"BQ");
					else if(ctrb == 2)strcpy(cp,"BR1");
					else if(ctrb == 3)strcpy(cp,"BR2");
					else if(ctrb == 4)strcpy(cp,"BB1");
					else if(ctrb == 5)strcpy(cp,"BB2");
					else if(ctrb == 6)strcpy(cp,"BP1");
					else if(ctrb == 7)strcpy(cp,"BP2");
					else if(ctrb == 8)strcpy(cp,"BP3");
					else if(ctrb == 9)strcpy(cp,"BP4");
					else if(ctrb == 10)strcpy(cp,"BP5");
					else if(ctrb == 11)strcpy(cp,"BP6");
				}
				ctrb++;
			}
		}
		else{
			printf("Unidentified Action");
		}
		if(isALocation(array[3]) == 1){
			strcpy(cp2,array[3]);
			a = 1;
		}
		else{
			printf("Invalid Move");
		}
	}
	else if(strcmp(array[1], "TO") == 0){ // <player2 piece or location of p2's piece> TO <destination>
		b = 1;
		if(isAPiece(array[0]) == 1){
			strcpy(cp, array[0]);
		}
		else if(isALocation(array[0]) == 1){
			int ctrb = 0, checker = 0, anum = atoi(array[0]);			
			while(ctrb < 12 && checker == 0){
				if(anum == Player2[ctrb]){
					checker = 1;
					if(ctrb == 0)strcpy(cp,"BK");
					else if(ctrb == 1)strcpy(cp,"BQ");
					else if(ctrb == 2)strcpy(cp,"BR1");
					else if(ctrb == 3)strcpy(cp,"BR2");
					else if(ctrb == 4)strcpy(cp,"BB1");
					else if(ctrb == 5)strcpy(cp,"BB2");
					else if(ctrb == 6)strcpy(cp,"BP1");
					else if(ctrb == 7)strcpy(cp,"BP2");
					else if(ctrb == 8)strcpy(cp,"BP3");
					else if(ctrb == 9)strcpy(cp,"BP4");
					else if(ctrb == 10)strcpy(cp,"BP5");
					else if(ctrb == 11)strcpy(cp,"BP6");
				}
				ctrb++;
			}
		}
		else{
			printf("Unidentified Action");
		}
		if(isALocation(array[2]) == 1){
			strcpy(cp2,array[2]);
			a = 1;
		}
		else{
			printf("Invalid Move");
		}
	}
	else if(strcmp(array[0], "EAT") == 0 && strcmp(array[2], "WITH") == 0){ //EAT <player2 piece or a location of p2's piece> WITH <player 1 piece or a location of p1's piece>
		b = 1;
		if(isAPiece(array[3]) == 1){
			strcpy(cp, array[3]);
		}
		else if(isALocation(array[3]) == 1){
			int ctrb = 0, checker = 0, anum = atoi(array[3]);			
			while(ctrb < 12 && checker == 0){
				if(anum == Player2[ctrb]){
					checker = 1;
					if(ctrb == 0)strcpy(cp,"BK");
					else if(ctrb == 1)strcpy(cp,"BQ");
					else if(ctrb == 2)strcpy(cp,"BR1");
					else if(ctrb == 3)strcpy(cp,"BR2");
					else if(ctrb == 4)strcpy(cp,"BB1");
					else if(ctrb == 5)strcpy(cp,"BB2");
					else if(ctrb == 6)strcpy(cp,"BP1");
					else if(ctrb == 7)strcpy(cp,"BP2");
					else if(ctrb == 8)strcpy(cp,"BP3");
					else if(ctrb == 9)strcpy(cp,"BP4");
					else if(ctrb == 10)strcpy(cp,"BP5");
					else if(ctrb == 11)strcpy(cp,"BP6");
				}
				ctrb++;
			}
		}
		else{
			printf("Unidentified Action");
		}
		if(isALocation(array[1]) == 1){
			int ctrc = 0,anum1 = atoi(array[1]);
			while(ctrc < 12){
				if(Player2[ctrc] == anum1){
					strcpy(cp2,array[1]);
					a = 1;
				}
				ctrc++;
			}
		}
		else{
			char aString[10];
			if(strcmp(array[1],"WK") == 0){itoa(Player1[0],aString,10);strcpy(cp2,aString);a=1;}
			else if(strcmp(array[1],"WQ") == 0){itoa(Player1[1],aString,10);strcpy(cp2,aString);a=1;}
			else if(strcmp(array[1],"WR1") == 0){itoa(Player1[2],aString,10);strcpy(cp2,aString);a=1;}
			else if(strcmp(array[1],"WR2") == 0){itoa(Player1[3],aString,10);strcpy(cp2,aString);a=1;}
			else if(strcmp(array[1],"WB1") == 0){itoa(Player1[4],aString,10);strcpy(cp2,aString);a=1;}
			else if(strcmp(array[1],"WB2") == 0){itoa(Player1[5],aString,10);strcpy(cp2,aString);a=1;}
			else if(strcmp(array[1],"WP1") == 0){itoa(Player1[6],aString,10);strcpy(cp2,aString);a=1;}
			else if(strcmp(array[1],"WP2") == 0){itoa(Player1[7],aString,10);strcpy(cp2,aString);a=1;}
			else if(strcmp(array[1],"WP3") == 0){itoa(Player1[8],aString,10);strcpy(cp2,aString);a=1;}
			else if(strcmp(array[1],"WP4") == 0){itoa(Player1[9],aString,10);strcpy(cp2,aString);a=1;}
			else if(strcmp(array[1],"WP5") == 0){itoa(Player1[10],aString,10);strcpy(cp2,aString);a=1;}
			else if(strcmp(array[1],"WP6") == 0){itoa(Player1[11],aString,10);strcpy(cp2,aString);a=1;}
			else{
				printf("Invalid Move");
			}
		}
	}
	else{
		printf("Invalid Command\n");
	}
	
//    strcpy(cp, token);
//    token = strtok(NULL, " ");
//    strcpy(command, token);
//    token = strtok(NULL, " ");
//    strcpy(cp2, token);
//    
//    int current;
//    int loc, des;
//    
//    a = isALocation(cp2);
//    b = isACommand(command);
//    toUpperCase(cp);
    
    if(a == 1 && b == 1){
    	des = atoi(cp2);
    	if(strcmp(cp,"BK") == 0 ){
    		loc = Player2[0];
    		index=0;
    		valid=moveKing(Player2,des,loc,index);
				if (valid==1){
		    		checkEat(Player1,des);
		    	}
	 	}
		else if(strcmp(cp,"BQ") == 0){
    		loc = Player2[1];
    		index=1;
    		valid=moveQueen(Player2,des,loc,index);
    			if (valid==1){
		    		checkEat(Player1,des);
		    	}
		}
		else if(strcmp(cp,"BR1") == 0 ){
    		loc = Player2[2];
    		index=2;
   			valid=moveRook(Player2,des,loc,index);
   			if (valid==1){
		    		checkEat(Player1,des);	
				}
		}
		else if(strcmp(cp,"BR2") == 0){
    		loc = Player2[3];
    		index=3;
    		valid=moveRook(Player2,des,loc,index);
    		if (valid==1){
		    		checkEat(Player1,des);	
				}
		}
		else if(strcmp(cp,"BB1") == 0){
    		loc = Player2[4];
    		index=4;
	   		valid=moveBishop(Player2,des,loc,index);
	   		if (valid==1){
		    		checkEat(Player1,des);	
				}
		}
		else if(strcmp(cp,"BB2") == 0){
    		loc = Player2[5];
    		index=5;
    		valid=moveBishop(Player2,des,loc,index);
    		if (valid==1){
		    		checkEat(Player1,des);	
				}
		}
    	else if(strcmp(cp,"BP1") == 0 ){
    		loc = Player2[6];
    		index=6;
    		valid=movePawn2(Player2,des,loc,index);
    		if (valid==1){
		    		checkEat(Player1,des);	
				}
		}
		else if(strcmp(cp,"BP2") == 0){
    		loc = Player2[7];
    		index=7;
    		valid=movePawn2(Player2,des,loc,index);
    		if (valid==1){
		    		checkEat(Player1,des);	
				}
		}
		else if(strcmp(cp,"BP3") == 0 ){
    		loc = Player2[8];
    		index=8;
    		valid=movePawn2(Player2,des,loc,index);
    		if (valid==1){
		    		checkEat(Player1,des);	
				}
		}
		else if(strcmp(cp,"BP4") == 0){
    		loc = Player2[9];
    		index=9;
    		valid=movePawn2(Player2,des,loc,index);
    		if (valid==1){
		    		checkEat(Player1,des);	
				}
		}
		else if(strcmp(cp,"BP5") == 0){
    		loc = Player2[10];
    		index=10;
    		valid=movePawn2(Player2,des,loc,index);
    		if (valid==1){
		    		checkEat(Player1,des);	
				}
		}
		else if(strcmp(cp,"BP6") == 0){
		loc = Player2[11];
		index=11;
		valid=movePawn2(Player2,des,loc,index);
		if (valid==1){
	    		checkEat(Player1,des);	
			}
		}
		else{
			valid=0;
			printf("\n\nMOVE INVALID!");
		}
		printf("\n\n");
		drawboard(Boardtiles,Player1,Player2);
	}
	else
		valid=0;
		
}while(valid!=1 || b!=1);
	
}

//end code for player 2 turn..

//move pawn for player 1 since pawn directions go down..

int movePawn1(int Player1[], int Destination, int Location, int index){
int pieceindex=index;
int a; //index
int Valid=1; //Determines if move is valid or not
int canMove=0; //Determines if no other piece is in the Destination
int exist=1; //To check if the piece is still in the game
int Blocked=0; //means no piece is in the destination of the current piece moving

	     //checking if piece exists
		if(Location==0){
			exist=0;
		}
		
		for(a=0;Blocked==0 && a<6;a++){			//checking if any piece is blocking the way
			if(Destination==Player1[a])
				Blocked=1;
		}
		
		if(Destination==Location+1)	//to see if the move made by the piece is valid
			canMove=1;
			
		if(Location==Destination){
			canMove=0;
			Blocked=1;
		}
		
		if(canMove==1 && exist==1 && Blocked==0){	//if all conditions are met to make the move
			Valid=1;
			Player1[pieceindex]=Destination; //moves location of the piece being moved		
		}
		else 
			Valid=0;	
	
return Valid;
}

//end code

//move pawn for player 2 because pawns move up..

int movePawn2(int Player2[], int Destination, int Location, int index){
int pieceindex=index; //index of piece to be used
int a; //index
int Valid=1; //Determines if move is valid or not
int canMove=0; //Determines if no other piece is in the Destination
int exist=1; //To check if the piece is still in the game
int Blocked=0; //means no piece is in the destination of the current piece moving

		     //checking if piece exists
		if(Location==0){
			exist=0;
		}
	
		for(a=0;Blocked==0 && a<6;a++){			//checking if any piece is blocking the way
			if(Destination==Player2[a])
				Blocked=1;
		}
		
		if(Destination==Location-1)	//to see if the move made by the piece is valid
			canMove=1;
			
		if(Location==Destination){
			canMove=0;
			Blocked=1;
		}	
			
		if(canMove==1 && exist==1 && Blocked==0){	//if all conditions are met to make the move
			Valid=1;
			Player2[pieceindex]=Destination; //moves location of the piece being moved		
		}
		else 
			Valid=0;	
			
return Valid;	
}

//end code

//move rook code for player 1 and 2

moveRook(int Player[], int Destination, int Location, int index){
int pieceindex=index; //index of piece to be used
int a,b; //index
int flag=0; //if flag is 0, no piece exist in location. if flag is 1 , piece exists.
int Valid=0; //Determines if move is valid or not
int canMove=1; //Determines if no other piece is in the Destination
int exist=1; //To check if the piece is still in the game
int Blocked=0; //means no piece is in the destination of the current piece moving

		if(Location==0){
			exist=0;
		}
		
		if(Location<Destination){						//this if is to locate if rook is going down or right
			if(((Destination-Location)%10)!=0){				
				for(a=Location+1;a<=Destination;a++){		//for loop that checks each step of the way til destination
					for(b=0;b<12;b++){					//for loop that checks againts all friendly pieces if they are blocking the way
						if(a==Player[b]){
							Blocked=1;
							canMove=0;
						}
					}
				}
			}
			else{				
				for(a=Location+10;a<=Destination;a+=10){	//for loop that checks each step of the way til destination
					for(b=0;b<12;b++){						//for loop that checks againts all friendly pieces if they are blocking the way
						if(a==Player[b]){
							Blocked=1;
							canMove=0;
						}
					}
				}
			}
		}												//end location code
		else if(Location>Destination){						//this code is to locate if rook is going up or left
			if(((Location-Destination)%10)!=0){
				for(a=Location;a<=Destination;a-=1){	//for loop that checks each step of the way til destination
					for(b=0;b<12;b++){					//for loop that checks againts all friendly pieces if they are blocking the way
						if(a-1==Player[b]){
							Blocked=1;
							canMove=0;
						}
					}
				}
			}
			else{
				for(a=Location;a<=Destination;a-=10){	//for loop that checks each step of the way til destination
					for(b=0;b<12;b++){					//for loop that checks againts all friendly pieces if they are blocking the way
						if(a-10==Player[b]){
							Blocked=1;
							canMove=0;
						}
					}	
				}
			}
		}													//end code
		else if(Location==Destination){
			Blocked=1;
			canMove=0;
		}

		if(canMove==1 && exist==1 && Blocked==0){	//if all conditions are met to make the move
			Valid=1;
			Player[pieceindex]=Destination; //moves location of the piece being moved		
		}
		
return Valid;		
}

//end code

//move bishop code for player 1 and 2

moveBishop(int Player[], int Destination, int Location,int index){
int pieceindex=index; //index of piece to be used
int a,b; //index
int flag=0; //if flag is 0, no piece exist in location. if flag is 1 , piece exists.
int Valid=0; //Determines if move is valid or not
int canMove=1; //Determines if no other piece is in the Destination
int exist=1; //To check if the piece is still in the game
int Blocked=0; //means no piece is in the destination of the current piece moving

		if(Location==0){
			exist=0;
		}
		
		if(Location<Destination){
			if(((Destination-Location)%9)==0){
				for(a=Location+9;a<Destination;a+=9){
					for(b=0;b<12;b++){
						if(a==Player[b]){
							Blocked=1;
							canMove=0;
						}
					}
				}
			}
			else{
				for(a=Location+11;a<Destination;a+=11){
					for(b=0;b<12;b++){
						if(a==Player[b]){
							Blocked=1;
							canMove=0;
						}
					}			
				}
			}
		}
		else
		if(Location>Destination){
			if(((Location-Destination)%9)==0){
				for(a=Location-9;a<Destination;a-=9){
					for(b=0;b<12;b++){
						if(a==Player[b]){
							Blocked=1;
							canMove=0;
						}
					}
				}
			}
			else{
				for(a=Location-11;a<Destination;a-=11){
					for(b=0;b<12;b++){
						if(a==Player[b]){
							Blocked=1;
							canMove=0;
						}
					}
				}
			}
		}
		else if(Location==Destination){
			Blocked=1;
			canMove=0;
		}
		
		if(canMove==1 && exist==1 && Blocked==0){	//if all conditions are met to make the move
			Valid=1;
			Player[pieceindex]=Destination; //moves location of the piece being moved		
		}
		
		else {
			Valid=0;	
		}
return Valid;

	
}

//end code


moveKing(int Player[], int Destination, int Location,int index){
int pieceindex=index; //index of piece to be used
int a,b; //index
int flag=0; //if flag is 0, no piece exist in location. if flag is 1 , piece exists.
int Valid=1; //Determines if move is valid or not
int canMove=1; //Determines if no other piece is in the Destination
int exist=1; //To check if the piece is still in the game
int Blocked=0; //means no piece is in the destination of the current piece moving
		    
			 //checking if piece exists
			if(Location==0){
				exist=0;
			}
			
			for(a=0;a<12;a++){
				if(Location+1==Destination || Location-1==Destination || Location+10==Destination || Location-10==Destination || Location+9==Destination || Location-9==Destination || Location+11==Destination || Location-11==Destination){
					if(Player[a]==Destination){
						canMove=0;
						Blocked=1;
					}
				}
				else
						canMove=0;
				
			}
		if(Location==Destination){
			canMove=0;
			Blocked=1;
		}

		if(canMove==1 && exist==1 && Blocked==0){	//if all conditions are met to make the move
			Valid=1;
			Player[pieceindex]=Destination; //moves location of the piece being moved		
		}
		else 
			Valid=0;
return Valid;			

	
}


moveQueen(int Player[], int Destination, int Location, int index){
int pieceindex=index; //index of piece to be used
int a,b; //index
int flag=0; //if flag is 0, no piece exist in location. if flag is 1 , piece exists.
int Valid=1; //Determines if move is valid or not
int canMove=1; //Determines if no other piece is in the Destination
int exist=1; //To check if the piece is still in the game
int Blocked=0; //means no piece is in the destination of the current piece moving

		if(Location==0){
			exist=0;
		}
		
		if(Location<Destination){						//this if is to locate if rook is going down or right
			if(((Destination-Location)%11)==0){
				for(a=Location+11;a<Destination;a+=11){
					for(b=0;b<12;b++){
						if(a==Player[b]){
							Blocked=1;
							canMove=0;
						}
					}			
				}			
			}
			else if(((Destination-Location)%10)==0){				
				for(a=Location+10;a<=Destination;a+=10){	//for loop that checks each step of the way til destination
					for(b=0;b<12;b++){						//for loop that checks againts all friendly pieces if they are blocking the way
						if(a==Player[b]){
							Blocked=1;
							canMove=0;
						}
					}
				}
			}
			
			else if(((Destination-Location)%9)==0){
				for(a=Location+9;a<Destination;a+=9){
					for(b=0;b<12;b++){
						if(a==Player[b]){
							Blocked=1;
							canMove=0;
						}
					}
				}
			}
			else{
				for(a=Location+1;a<=Destination;a++){		//for loop that checks each step of the way til destination
					for(b=0;b<12;b++){					//for loop that checks againts all friendly pieces if they are blocking the way
						if(a==Player[b]){
							Blocked=1;
							canMove=0;
						}
					}
				}
			}
		}												//end location code
		else if(Location>Destination){						//this code is to locate if rook is going up or left
			if(((Location-Destination)%11)==0){
				for(a=Location-11;a<Destination;a-=11){
					for(b=0;b<12;b++){
						if(a==Player[b]){
							Blocked=1;
							canMove=0;
						}
					}
				}
			}
			else if(((Location-Destination)%10)==0){
				for(a=Location;a<=Destination;a-=10){	//for loop that checks each step of the way til destination
					for(b=0;b<12;b++){					//for loop that checks againts all friendly pieces if they are blocking the way
						if(a-10==Player[b]){
							Blocked=1;
							canMove=0;
						}
					}	
				}
			}
			else if(((Location-Destination)%9)==0){
				for(a=Location-9;a<Destination;a-=9){
					for(b=0;b<12;b++){
						if(a==Player[b]){
							Blocked=1;
							canMove=0;
						}
					}
				}
			}
			else{
				for(a=Location;a<=Destination;a-=1){	//for loop that checks each step of the way til destination
					for(b=0;b<12;b++){					//for loop that checks againts all friendly pieces if they are blocking the way
						if(a-1==Player[b]){
							Blocked=1;
							canMove=0;
						}
					}
				}
			}
		}
		else if(Location==Destination){
			Blocked=1;
			canMove=0;
		}
		
		if(canMove==1 && exist==1 && Blocked==0){	//if all conditions are met to make the move
			Valid=1;
			Player[pieceindex]=Destination; //moves location of the piece being moved		
		}
		
		else {
			Valid=0;	
		}
return Valid;													//end code
}


toUpperCase(char temp[]){
	int ctr1;
	for(ctr1 = 0 ; temp[ctr1] != NULL ; ctr1++) {
	  temp[ctr1] = toupper(temp[ctr1]);
   	}
	return temp;
}

//isACommand(char command[]){
////	strcpy(command, toUpperCase(command));
//	toUpperCase(command);
//	if(strcmp(command,"MOVETO") == 0){
//		return 1;
//	}else{
////		printf("INVALID COMMAND!\n");
//		return 0;
//	}	
//}

isALocation(char cp2[]){
	int i = 0;
	for(; cp2[i] != NULL ; i++){
		if(isdigit(cp2[i]) == 0){
//			printf("INVALID DESTINATION!\n");
			return 0;
		}
	}
	return 1;
}

isAPiece(char tempPiece[]){
	char *peices[24];
	peices[0] = "WK";
	peices[1] = "WQ";
	peices[2] = "WR1";
	peices[3] = "WR2";
	peices[4] = "WB1";
	peices[5] = "WB2";
	peices[6] = "WP1";
	peices[7] = "WP2";
	peices[8] = "WP3";
	peices[9] = "WP4";
	peices[10] = "WP5";
	peices[11] = "WP6";
	peices[12] = "BK";
	peices[13] = "BQ";
	peices[14] = "BR1";
	peices[15] = "BR2";
	peices[16] = "BB1";
	peices[17] = "BB2";
	peices[18] = "BP1";
	peices[19] = "BP2";
	peices[20] = "BP3";
	peices[21] = "BP4";
	peices[22] = "BP5";
	peices[23] = "BP6";
	
	int ctra = 0;
	while(ctra < 24){
		if(strcmp(tempPiece, peices[ctra++]) == 0){
			return 1;
		}
	}
	return 0;
}

checkEat(int Player[], int des){
	int a;
	int pieceeaten=0;
	
	for(a=0;a<12 && pieceeaten==0;a++){
		if(Player[a]==des){
			Player[a]=0;
			pieceeaten=1;
		}	
	}
}

int checkGamestatus(int Player1[],int Player2[]){
	int a=0;
	int status=0;
	
	if(Player1[a]==0){
		printf("\n\nPLAYER 2 WINS!");
		status=1;
	}
	if(Player2[a]==0){
		printf("\n\nPLAYER 1 WINS!");
		status=1;
	}
return status;
}
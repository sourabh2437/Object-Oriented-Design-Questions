#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<ctime>
using namespace std;

const int ROW = 10;
const int COL = 10;

int getShipValue(char type) { 
		if	    (type=='A') return 3;
	    else if (type=='B') return 4;
	    else if (type=='C') return 5;
	    else if (type=='D') return 6;
}

bool isInside(int x,int y){					//function to check whether the coordinates are in the board or not
	if(x>=0 && x<COL && y>=0 && y<ROW)
		return 1;
	else 
		return 0;
}

class Ship{
	int x,y,length;
	char direction,type;
	
	public:
		Ship(int x,int y, char h, int length,char type){
			this->x=x;
			this->y=y;
			this->direction=h;
			this->length=length;
			this->type=type;
		}
		
		int getShipX() { return this->x ; }
		int getShipY() { return this->y ; }
		int getShipLength() { return this->length ; }
		char getShipDirection() { return this->direction ; }
		char getShipType() { return this->type ; }	
};


class Player{
	string pName;
	int score, shipsLeft;
	char playerBoard[ROW][COL];
	
	public:
	
		Player(string name){
			this->pName=name;
			this->score=0;
			this->shipsLeft=4;
			for(int i=0;i<ROW;i++){
				for(int j=0;j<COL;j++){
					playerBoard[i][j] = '.';
				}
			}
		}
		int getScore(){ return this->score;	}
		int getRemainingShip(){ return this->shipsLeft;	}
		string getPlayerName(){ return this->pName;	}
		
		bool isSafe(int x,int y,int length,char d){					//to check if it is Safe to place a Ship there
			if(d=='V'){
				if(x>=0&&(x+length)<COL){
					for(int i=x;i<x+length;i++){
						if(playerBoard[i][y] != '.')
							return false;
					}
					return true;
				}

			}else{
				if(y>=0&&(y+length)<ROW){
					for(int i=y;i<y+length;i++){
						if(playerBoard[x][i]!='.')
							return false;
					}
					return true;
				}
			}
		}
		
		void addShip(Ship &s){										// to add ship in the board
			int x = s.getShipX();
			int y = s.getShipY();
			int length = s.getShipLength();
			char d =s.getShipDirection();
			char t =s.getShipType();
			if(isSafe(x,y,length,d))
			{
				if(d=='V'){
					for(int i=x;i<x+length;i++){
						playerBoard[i][y]=t;
					}
				}else{
					for(int i=y;i<y+length;i++){
						playerBoard[x][i]=t;
					}
				}				
			}else{
				cout<<"Can't place the ship there\n";
			}
		}
		
		void  fire(Player *opp){									//to fire a missile and check whether it is a miss/hit/completely destroyed
			int x = rand()%COL;
			int y = rand()%ROW;
			if(opp->playerBoard[x][y]=='.'){
				cout<<this->getPlayerName()<<" Miss!!\n";
				}
						
			else if((isInside(x+1,y)?(opp->playerBoard[x+1][y]=='.'):1)	&&
					(isInside(x-1,y)?(opp->playerBoard[x-1][y]=='.'):1) &&
					(isInside(x,y+1)?(opp->playerBoard[x][y+1]=='.'):1) &&
					(isInside(x,y-1)?(opp->playerBoard[x][y-1]=='.'):1) ){					
						char shipType = opp->playerBoard[x][y];
						int shipValue = getShipValue(shipType);
						this->score+=shipValue;
						opp->shipsLeft-=1;
						opp->playerBoard[x][y] = '.';
						cout<<this->getPlayerName()<<" Destroyed ship "<<shipType<<"\n";
					}
			else{
				opp->playerBoard[x][y]='.';
				cout<<this->getPlayerName()<< " Hit!!\n";
				}
		}
		
		void printBoard(){
			for(int i=0;i<ROW;i++){
				for(int j=0;j<COL;j++){
					cout<<playerBoard[i][j];
				}
				cout<<"\n";
			}
		}
};
class Board{
	vector<Player> playerArr;
	public:
		void addPlayers(Player &p){
			playerArr.push_back(p);
		}
		void gameSetup1(Player *p){
			Ship s01(0,0,'H',3,'A');
			Ship s02(3,1,'H',4,'B');
			Ship s03(2,5,'V',5,'C');
			Ship s04(3,8,'V',6,'D');
			p->addShip(s01);
			p->addShip(s03);
			p->addShip(s02);
			p->addShip(s04);
		}
		
		void gameSetup2(Player *p){
			Ship s11(0,0,'H',3,'A');
			Ship s12(3,1,'H',4,'B');
			Ship s13(2,5,'V',5,'C');
			Ship s14(3,9,'V',6,'D');
			p->addShip(s11);
			p->addShip(s13);
			p->addShip(s12);
			p->addShip(s14);
		}
		
		void startGame(Player *p1,Player *p2){
			gameSetup1(p1);
			gameSetup2(p2);
			int count=0;
			cout<<"Game Setup done\n";
			cout<<"Let the Battle Begin...!!!!\n";
				
			while(p1->getRemainingShip()&&p2->getRemainingShip()){
				p1->fire(p2);
				p2->fire(p1);
				count++;
			}
			if(p1->getScore()>p2->getScore()){
				cout<<p1->getPlayerName()<<" Won score "<<p1->getScore()<<" and ships destroyed "<<4-p2->getRemainingShip()<<" enemy ships\n";
			}else{
				cout<<p2->getPlayerName()<<" Won score "<<p2->getScore()<<" and ships destroyed "<<4-p1->getRemainingShip()<<" enemy ships\n";
			}
		}
		
};
int main(){
	srand (time(NULL));
	
	Player p1("Player 1");
	Player p2("Player 2");
	
	Board newGame;
	newGame.addPlayers(p1);
	newGame.addPlayers(p2);
	newGame.startGame(&p1,&p2);
	
	return 0;
}

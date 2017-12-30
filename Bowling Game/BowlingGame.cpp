#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
#include<vector>
#include<ctime>

using namespace std;

class Player{
	string pName;
	int score;
	public:
		Player(string name)
	{
		this->pName = name;
		this->score=0;
	}
	string getPlayerName (){
		return this->pName;
	}
	int getPlayerScore(){
		return this->score;
	}
	void updatePlayerScore(int hit){
		this->score+=hit;
	}
	int rollBall(){
		
			int randNum = rand()%10+1;
			return randNum;
		}

};

bool compare( Player  &a, Player  &b){
			int p1 = a.getPlayerScore();
			int p2 = b.getPlayerScore();
			return p1>p2;	
	    }
	    
class BowlingGame {
	int rounds;
	int pins;
	vector<Player> playerArr;
	
	public:
		BowlingGame(int rounds,int pins){
			this->rounds=rounds;
			this->pins=pins;
		}
		void addPlayer(Player &p){
			playerArr.push_back(p);
		}
		void display(){
			for(int i =0;i<playerArr.size();i++)
			 {
		 		playerArr[i].getPlayerName();
		 	 }
		}
		
		void printLeaderBoard(){
			int num_of_players = playerArr.size();
			sort(playerArr.begin(),playerArr.end(),compare);	
			for(int i=0;i<playerArr.size();i++){
				cout<<i+1<<" "<<playerArr[i].getPlayerName()<<" Score -> "<<playerArr[i].getPlayerScore()<<"\n";
			}
		}
		
		void startGame(){
			int i,j;
			for(i=0;i<this->rounds;i++){
				for(j=0;j<playerArr.size();j++){
					int hit = playerArr[j].rollBall();
					playerArr[j].updatePlayerScore(hit);
					cout<<playerArr[j].getPlayerName()<<" hit "<<hit<<" total score = "<<playerArr[j].getPlayerScore()<<"\n";
				}
			}
			printLeaderBoard();	
		}
	
};
int main(){
	srand (time(NULL));
	
	Player p1("Sourabh");
	Player p2("Shivani");
	Player p3("Piyush");

	BowlingGame Game(5,10);
	Game.addPlayer(p1);
	Game.addPlayer(p2);
	Game.addPlayer(p3);

	Game.startGame();
	return 0;
}

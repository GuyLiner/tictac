#include "boardfunctions.h"
int BoardGame::startGame(){
	Player players[2];	
	players[0].setPlayerMark("x");
	players[1].setPlayerMark("o");

	//main loop
	while(true){
		for(auto& player: players){
			printTable();
			promptPlayer(player);
			if(calculateVictory(player) == true){
				std::cout << "GAME OVER!";
				return 0;
			};
		}
	}
}

int BoardGame::findOrigin(int &rowsize){
	int origin;
	if((rowsize % 2) > 0 ){
		origin = (rowsize - 1) / 2;
	}	
	else{
		origin = rowsize / 2;
	}
	return origin;
}
;


//convert 2D array to grid
std::tuple<int,int,int> BoardGame::getXY(int X, int Y, int &origin){
	int pos[2] = {X,Y};
	for(auto& coord : pos){
		if(coord < origin){
			coord = std::abs(coord - origin);
			coord *= -1;
		}
		else if(coord > origin){
			coord = std::abs(origin - coord);
		}
		else{
			coord = 0;
		}
	}
	//invert the Y axis
	pos[1] *= -1;
	return std::make_tuple(pos[0],pos[1],0);
}

//use rotation matrix to calcuate degrees
std::array<int,2> BoardGame::rotMatrixMultiply(const int &degrees,int pos[]){
	static double radians = (degrees * M_PI) / 180;
	static double rot_matrix[2][2] = {{std::cos(radians),(std::sin(radians) * -1 )},{std::sin(radians), std::cos(radians)}};
	std::array<int,2> pos_arr;
	for(int i=0; i < sizeof(rot_matrix) / sizeof(rot_matrix[0]); i++){
		pos_arr[i] = (pos[0] * rot_matrix[i][0]) + ( pos[1] * rot_matrix[i][1]);
	}
	return pos_arr;

}

bool BoardGame::calculateSlope(int x, int y, int &board_x, int &board_y){
	int m,b;	
	//std::cout << "(" << x <<","<< y << ")" << "\n";	
	if(x != 0 && y != 0){	
		m = (y - (y * -1)) / (x - (x * -1)); 
		b = ((m * x) * -1) + y;	
		//std::cout << (board_y == (m*board_x)+b);
		return board_y == (m*board_x)+b; 
	}
	else if(y == 0){
		//std::cout << (x == board_x);
		return y == board_y;
	}
	else if(x == 0){
		//std::cout << (y == board_y);
		return x == board_x;

	}

}

bool BoardGame::calculateVictory(Player &player){
	int y_max = sizeof(game) / sizeof(game[0]);
	int x_max = sizeof(game[0])/ sizeof(std::string);
	int origin = findOrigin(y_max);
	bool victory;	

	std::tuple<int,int,int> zero_pos = getXY(0, 0, origin);
	int init_pos[2] = {std::get<0>(zero_pos), std::get<1>(zero_pos)};

	//variable to rotate around grid -135 degrees
	const static std::array<int,2> delta_pos = rotMatrixMultiply(-135,init_pos);
	
	//loop through board, then for each point create a straight line
	//and loop through the board again to see what points are in the line	
	//
	for(int y=0; y < y_max; y++){
		for(int x=0; x < x_max; x++){

			std::tuple<int,int,int> pos = getXY(x, y, origin);
			int real_x = std::get<0>(pos);
			int real_y = std::get<1>(pos);
			int real_pos[2] = {real_x, real_y};
			player.resetMarkCount();
			//std::cout << "reset";
			//if(real_pos[x] <= delta_pos[0] && real_pos[y] >= delta_pos[1]){
				for(int point_y=0; point_y < y_max; point_y++){
					for(int point_x=0; point_x < x_max; point_x++){
						std::tuple<int,int,int> point_pos = getXY(point_x, point_y, origin);

						if(calculateSlope(real_x,real_y, std::get<0>(point_pos), std::get<1>(point_pos)) && player.getMarkCount() < x_max){
							if(game[point_y][point_x] == player.getPlayerMark()){
								player.incrementMarkCount();
								//std::cout << "\n" << player.getMarkCount() << "("<< std::get<0>(point_pos) << "," << std::get<1>(point_pos) << ") " << player.getPlayerMark() << "\n";
								if(player.getMarkCount() == 3){
									victory = 1;
									return victory;
								}
							}
						}
					}

				}

			//}
		}
	}
	//std::cout << player.getMarkCount() << ": " << player.getPlayerMark();
	return victory;
}	
	
void BoardGame::markPosition(int &r, int &c, const std::string &mark){
	game[r-1][c-1] = mark;
}
void BoardGame::promptPlayer(Player &player){
	int pos_x, pos_y;
	std::cout << "Player "<< player.getPlayerMark() <<"\n";

	std::cout << "Choose your row: ";
	std::cin >> pos_x;
	std::cout << "Choose your column: ";
	std::cin >> pos_y;
	markPosition(pos_x, pos_y, player.getPlayerMark());
}

void BoardGame::printTable(){
	static const std::regex e ("\\ ");
	for(int i=0; i < sizeof(game) / sizeof(game[0]); i++){
		static const int size_arr = sizeof(game[i]) / sizeof(std::string);
		for(int j=0; j < size_arr; j++){
			std::string board_location ;
			if(j == 0){
				board_location = "| |";
			}
			else{
				board_location = " |";
			}

			if(game[i][j] == ""){
				std::cout << board_location;
			}
			else{
				std::cout << std::regex_replace(board_location, e, game[i][j]);
			}
			if(((j+1)) % (size_arr) == 0){
				std::cout << "\n";
				for (int i=0; i < size_arr; i++){
					std::cout << "--";
					if( i % size_arr == 0){
					std::cout << "-";
					}
				}
				std::cout << "\n";
			}
		}
	}
}

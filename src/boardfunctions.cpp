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
				printTable();
				std::cout << "GAME OVER!\n" << "Player " << player.getPlayerMark() << " wins!\n";
				return 0;
			};
		}
	}
}

int BoardGame::findOrigin(const int &rowsize){
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
std::tuple<int,int> BoardGame::getXY(int X, int Y, const int &origin){
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
	return std::make_tuple(pos[0],pos[1]);
}

//only does negative degrees
std::array<int,2> BoardGame::rotMatrixMultiply(const double &degrees,int pos[]){
	double radians = degrees * (M_PI / 180);
	Eigen::Rotation2D t(radians);
	Eigen::Vector2d xy(pos[0],pos[1]);
	std::array<int,2> pos_arr;

	xy = t.toRotationMatrix() * xy;

	//Double to int causes rounding errors	
	pos_arr[0] = (int)(xy[0] < 0 ? xy[0] - 0.5 : xy[0] + 0.5);
	pos_arr[1] = (int)(xy[1] < 0 ? xy[1] - 0.5 : xy[1] + 0.5);

	return pos_arr;

}

//Only determines if point is on line where m > 0 (slope has to exist)
bool BoardGame::calculateSlope(int x, int y, int &board_x, int &board_y){
	int m,b;
	if(x != 0 && y != 0){	
		m = (y - (y * -1)) / (x - (x * -1)); 
		b = ((m * x) * -1) + y;	
		return board_y == (m*board_x)+b; 
	}

	else if(y == 0){
		return y == board_y;
	}
	else if(x == 0){
		return x == board_x;

	}
	return false;
}

bool BoardGame::victoryOnSlope(Player &player, const int &origin){
	for(int y=0; y < y_max; y++){
		for(int x=0; x < x_max; x++){
			std::tuple<int,int> pos = getXY(x, y, origin);
			int real_x = std::get<0>(pos);
			int real_y = std::get<1>(pos);
			int real_pos[2] = {real_x, real_y};
			player.resetMarkCount();

			for(int point_y=0; point_y < y_max; point_y++){
				for(int point_x=0; point_x < x_max; point_x++){
					std::tuple<int,int> point_pos = getXY(point_x, point_y, origin);

					if(calculateSlope(real_x,real_y, std::get<0>(point_pos), std::get<1>(point_pos)) && player.getMarkCount() < x_max){
						if(game[point_y][point_x] == player.getPlayerMark()){
							player.incrementMarkCount();
							if(player.getMarkCount() == x_max){
								return true;
							}
						}
					}
				}

			}

		}
	}
	return false;
}

//The first point on the grid (which in this instance is (-1,1))
//needs to be rotated 90 degrees 4 times to determine the possible solutions
//the logic after this if statement does not cover.
bool BoardGame::victoryOnStraightLine(Player &player, const int &origin){
	int edge_coords[4][2];
	static std::tuple<int,int> zero_pos = getXY(0, 0, origin);
	int init_pos[2] = {std::get<0>(zero_pos), std::get<1>(zero_pos)};

	std::array<int,2> delta_pos;
	for(int i=0; i < 4; i++){
		delta_pos = rotMatrixMultiply(-90,init_pos);
		player.resetMarkCount();

		for(int y=0; y < y_max; y++){
			for(int x=0; x < x_max; x++){
				std::tuple<int,int> point_pos = getXY(x, y, origin);
				int cur_pos[2] = {std::get<0>(point_pos),std::get<1>(point_pos)};
				for(int j=0; j < 2; j++){
					if(delta_pos[j] == init_pos[j] && cur_pos[j] == init_pos[j] && game[y][x] == player.getPlayerMark()){
						player.incrementMarkCount();
					}
				}
				if(player.getMarkCount() == x_max){
					return true;
				}
			}	
		}
		init_pos[0] = delta_pos[0];
		init_pos[1] = delta_pos[1];
	}
	return false;
	
}

bool BoardGame::calculateVictory(Player &player){
	const int origin = findOrigin(y_max);

	static std::tuple<int,int> zero_pos = getXY(0, 0, origin);
	int init_pos[2] = {std::get<0>(zero_pos), std::get<1>(zero_pos)};

	//variable to rotate around grid -135 degrees
	const static std::array<int,2> delta_pos = rotMatrixMultiply(-135,init_pos);
	
	if(victoryOnStraightLine(player, origin) == true || victoryOnSlope(player, origin) == true){
		return true;
	}
	return false;
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

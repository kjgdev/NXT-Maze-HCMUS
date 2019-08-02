#include <iostream>

using namespace std;

#define SIZEMAP_X 30
#define SIZEMAP_Y 30

#define EAST 0
#define SOUTH 1
#define WEST 2
#define NORTH 3

#define LEFT 0
#define ABOVE 1
#define RIGHT 2
#define BACK 3

#define DESTINATION_X 31
#define DESTINATION_Y 31

#define LOCATION_START_X 10
#define LOCATION_START_Y 0

#define DISTANCE_BARRIER 15

/*
	- Lưu trạng thái tại 1 điểm ngã rẽ trong mê cung
*/
struct Turn {
	// 0:Close 1:Can go 2:Back 
	int east;
	int north;
	int south;
	int west;
};

/*
	- Tọa độ một điểm trong mê cung
*/
struct Point {
	int x;
	int y;
};


/*
- Sensor
*/
struct SensorR {
	int distanceSSLeft;
	int distanceSSAbove;
	int distanceSSRight;
};

Turn map[SIZEMAP_X][SIZEMAP_Y];
SensorR sensorR; // Khoảng cách của các sensor
/*
	- Hướng hiện tại của xe
	- 0:East 1:West 2:South 3:North
		   North
			 ^   
	  West <   > East 
			 v
		   South
*/
int direction;
Point location; // Tọa độ hiện tại của robot
Point destination;// Tọa độ đích

/*
- Khởi tạo dữ liệu
*/
void InitData() {
	Turn turn;
	turn.east = -1;
	turn.north = -1;
	turn.west = -1;
	turn.south = -1;
	for (int i = 0; i < SIZEMAP_Y; i++) {
		for (int j = 0; j < SIZEMAP_X; j++) {
			map[i][j] = turn;
		}
	}
}

/*
- Quét Sensor
- Lấy giá trị từ SensorUS
*/
void UpdateSensorUS() {
	sensorR.distanceSSLeft = 50;
	sensorR.distanceSSAbove = 50;
	sensorR.distanceSSRight = 50;
}

/*
- CHo robot đi thẳng
*/
void GoStraight() {
	// Test Console
	//
	cout << "Go Straight" << endl;
	//
}


/*
- Cho Robot rẽ phải
*/
void TurnRight() {
	// Test Console
	//
	cout << "Turn Right" << endl;
	//
}


/*
- Cho Robot rẽ trái
*/
void TurnLeft() {
	// Test Console
	//
	cout << "Turn Right" << endl;
	//
}


/*
- Cho robot quay 180 độ
*/
void TurnAround() {
	// Test Console
	//
	cout << "Turn Around" << endl;
	//
}


/*
- Chuyển hướng di chuyển
*/
void Navigation(int dir) {
	if (dir == LEFT) TurnLeft();
	else if (dir == RIGHT) TurnRight();
	else if (dir == BACK) TurnAround();
	else GoStraight();
}


/*
- Check đích đến
*/
bool CheckDestination() {
	if (location.x == destination.x && location.y == destination.y)
		return true;
	else return false;
}


/*
- Check turn
*/
bool checkTurn() {
	int count = 0;
	if (sensorR.distanceSSAbove < DISTANCE_BARRIER) count++;
	if (sensorR.distanceSSLeft < DISTANCE_BARRIER) count ++;
	if (sensorR.distanceSSRight < DISTANCE_BARRIER) count++;
	if (count > 1) return true;
	return false;
}


/*
- Trạng thái tại ngã rẽ
*/
void UpdateStatusTurn() {
	// Trạng thái tại ngã rẽ chưa được cập nhật
	Turn turn = map[location.y][location.x];
	if (turn.east == -1) {
		switch (direction) {
		case EAST: {
			if (sensorR.distanceSSAbove > DISTANCE_BARRIER) turn.east = 1;
			else turn.east = 0;
			if (sensorR.distanceSSLeft > DISTANCE_BARRIER) turn.north = 1;
			else turn.north = 0;
			if (sensorR.distanceSSRight > DISTANCE_BARRIER) turn.south = 1;
			else turn.south = 0;
			turn.west = 2;
			break;
		}
		case SOUTH: {
			if (sensorR.distanceSSAbove > DISTANCE_BARRIER) turn.south = 1;
			else turn.south = 0;
			if (sensorR.distanceSSLeft > DISTANCE_BARRIER) turn.east = 1;
			else turn.east = 0;
			if (sensorR.distanceSSRight > DISTANCE_BARRIER) turn.west = 1;
			else turn.west = 0;
			turn.north = 2;
			break;
		}
		case WEST: {
			if (sensorR.distanceSSAbove > DISTANCE_BARRIER) turn.west = 1;
			else turn.west = 0;
			if (sensorR.distanceSSLeft > DISTANCE_BARRIER) turn.south = 1;
			else turn.south = 0;
			if (sensorR.distanceSSRight > DISTANCE_BARRIER) turn.north = 1;
			else turn.north = 0;
			turn.east = 2;
			break;
		}
		case NORTH: {
			if (sensorR.distanceSSAbove > DISTANCE_BARRIER) turn.north = 1;
			else turn.north = 0;
			if (sensorR.distanceSSLeft > DISTANCE_BARRIER) turn.west = 1;
			else turn.west = 0;
			if (sensorR.distanceSSRight > DISTANCE_BARRIER) turn.east = 1;
			else turn.east = 0;
			turn.west = 2;
			break;
		}
		default: cout << "Error direction of robot"; break;
		}
	}
	else {
		switch (direction) {
		case EAST: {
			turn.east = 0;
			break;
		}
		case SOUTH: {
			turn.south = 0;
			break;
		}
		case WEST: {
			turn.west = 0;
			break;
		}
		case NORTH: {
			turn.north = 0;
			break;
		}
		default: cout << "Error direction of robot"; break;
		}
	}
	map[location.y][location.x] = turn;
}


/*
- Cập nhật lại tọa độ của robot
- Mỗi lần xe chạy 5cm se cập nhật tọa độ 1 lần
*/
void UpdateLocation() {
	switch (direction) {
		// direction = Eart
	case EAST: {
		location.x = location.x + 1;
		break;
	}
			   // direction = South 
	case SOUTH: {
		location.y = location.y - 1;
		break;
	}
				// direction = West
	case WEST: {
		location.x = location.x - 1;
		break;
	}
			   // direction = North
	case NORTH: {
		location.y = location.y + 1;
		break;
	}
	default: cout << "Error direction of robot";
	}
}


/*
- Tính vị trí ảo xe đi
- Input: Hướng cần tính tọa độ {0:Left 1:Above 2:Right}
- directionTemp: 0:Left 1:Above 2:Right
*/
Point PointTemporary(int directionTemp) {
	Point temp;
	switch (direction) {
	// direction = Eart
	case EAST: {
		if (directionTemp == 0) {
			temp.x = location.x;
			temp.y = location.y + 1;
		}
		else if (directionTemp == 1) {
			temp.x = location.x + 1;
			temp.y = location.y;
		}
		else if (directionTemp) {
			temp.x = location.x;
			temp.y = location.y - 1;
		}
		else cout << "Error directionTemp";
		break;
		}
	// direction = South 
	case SOUTH: {
		if (directionTemp == 0) {
			temp.x = location.x + 1;
			temp.y = location.y;
		}
		else if (directionTemp == 1) {
			temp.x = location.x;
			temp.y = location.y - 1;
		}
		else if (directionTemp) {
			temp.x = location.x - 1;
			temp.y = location.y;
		}
		else cout << "Error directionTemp";
		break;
	}
			// direction = West
	case WEST: {
		if (directionTemp == 0) {
			temp.x = location.x;
			temp.y = location.y - 1;
		}
		else if (directionTemp == 1) {
			temp.x = location.x - 1;
			temp.y = location.y;
		}
		else if (directionTemp) {
			temp.x = location.x;
			temp.y = location.y + 1;
		}
		else cout << "Error directionTemp";
		break;
	}
	// direction = North
	case NORTH: {
		if (directionTemp == 0) {
			temp.x = location.x - 1;
			temp.y = location.y;
		}
		else if (directionTemp == 1) {
			temp.x = location.x;
			temp.y = location.y + 1;
		}
		else if (directionTemp) {
			temp.x = location.x + 1;
			temp.y = location.y;
		}
		else cout << "Error directionTemp";
		break;
	}
	default: cout << "Error direction of robot";
	}
	return temp;
}


/*
- Tính khoảng cách
*/
float DistanceCaculation(Point point) {
	float result;
	result = sqrt(pow(abs((point.x - destination.x)), 2) + pow(abs((point.y - destination.y)), 2));
	return result;
}


/*
- So sánh khoảng cách
- Return {LEFT or RIGHT or ABOVE or BACK}
*/
int CompareDistance(float left, float right, float above, float back) {
	if (left < right && left < above && left < back) return LEFT;
	else if (right < left && right < above && right < back) return RIGHT;
	else if (above < right && above < left && above < back) return ABOVE;
	else if (back < right && back < left && back < above) return BACK;
	else if (left == right && left < above && left < back) return LEFT;
	else if (above == right && above < left && above < back) return ABOVE;
	else return BACK;
}

/*
- Tính hướng tối ưu cho robot
- Return {LEFT or RIGHT or ABOVE or BACK}
*/
int OptimalDirection() {
	float distanceLeft = 999;
	float distanceAbove = 999;
	float distanceRight = 999;
	float distanceBack = 998;

	Turn turn = map[location.y][location.x];
	switch (direction) {
	case EAST: {
		if(turn.north == 1) distanceLeft = DistanceCaculation(PointTemporary(0));
		if(turn.east == 1) distanceAbove = DistanceCaculation(PointTemporary(1));
		if(turn.south == 1) distanceRight = DistanceCaculation(PointTemporary(2));
		break;
	}
	case SOUTH: {
		if (turn.east == 1) distanceLeft = DistanceCaculation(PointTemporary(0));
		if (turn.south == 1) distanceAbove = DistanceCaculation(PointTemporary(1));
		if (turn.west == 1) distanceRight = DistanceCaculation(PointTemporary(2));
		break;
	}
	case WEST: {
		if (turn.south == 1) distanceLeft = DistanceCaculation(PointTemporary(0));
		if (turn.west == 1) distanceAbove = DistanceCaculation(PointTemporary(1));
		if (turn.north == 1) distanceRight = DistanceCaculation(PointTemporary(2));
		break;
	}
	case NORTH: {
		if (turn.west == 1) distanceLeft = DistanceCaculation(PointTemporary(0));
		if (turn.north == 1) distanceAbove = DistanceCaculation(PointTemporary(1));
		if (turn.east == 1) distanceRight = DistanceCaculation(PointTemporary(2));
		break;
	}
	default: cout << "Error direction of robot"; break;
	}
	return CompareDistance(distanceLeft,distanceRight,distanceAbove,distanceBack);
}


/*
- Thay đổi hướng xe
- Input: hướng xe thay đổi {0:Left 3:Back 2:Right}
*/
void ChangeDirection(int dirC) {
	switch (direction) {
		// direction = Eart
	case EAST: {
		if (dirC == LEFT) direction = NORTH;
		else if (dirC == BACK) direction = WEST;
		else if (dirC == RIGHT) direction = SOUTH;
		else cout << "Error Change Direction";
		break;
	}
			// direction = South 
	case SOUTH: {
		if (dirC == LEFT) direction = EAST;
		else if (dirC == BACK) direction = NORTH;
		else if (dirC == RIGHT) direction = WEST;
		else cout << "Error Change Direction";
		break;
	}
			// direction = West
	case WEST: {
		if (dirC == LEFT) direction = SOUTH;
		else if (dirC == BACK) direction = EAST;
		else if (dirC == RIGHT) direction = NORTH;
		else cout << "Error Change Direction";
		break;
	}
			// direction = North
	case NORTH: {
		if (dirC == LEFT) direction = WEST;
		else if (dirC == BACK) direction = SOUTH;
		else if (dirC == RIGHT) direction = EAST;
		else cout << "Error Change Direction";
		break;
	}
	default: cout << "Error direction of robot"; break;
	}
}


/*
- Xử lý di chuyen;
*/
void GO() {
	while (true) {
		// Kiểm tra xem tới đích hay chưa
		if (CheckDestination) return;
		// Kiểm tra ngã rẽ
		if (!checkTurn) {
			GoStraight();
			UpdateLocation();
		}
		else {
			UpdateStatusTurn();
			int optimalDirection = OptimalDirection();
			Navigation(optimalDirection);
			ChangeDirection(optimalDirection);
			GoStraight();
			UpdateLocation();
		}
	}
}

void main()
{
	GO();
	system("pause");
}
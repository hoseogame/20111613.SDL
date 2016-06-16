#pragma once

enum block_shape
{
	STICK_SHAPE,
	SQUARE_SHAPE,
	T_SHAPE,
	L_SHAPE,
	INVERTED_L_SHAPE,
	Z_SHAPE,
	S_SHAPE,
	SHAPE_COUNT,
	FIELD_WIDTH = 4,
	FIELD_HEIGHT = 4
};

enum block_angle
{
	UP,
	LEFT,
	RIGHT,
	DOWN,
	ANGLE_COUNT,
};

enum block_color
{
	WHITE,
	RED,
	YELLOW,
	GREEN,
	BLUE,
	VIOLET,
	COLOR_COUNT
};

enum block_behavior
{
	DOWN_MOVE,
	LEFT_MOVE,
	RIGHT_MOVE,
	ROTATE,
	BEHAVIOR_COUNT,
	ROTATION_COUNT = 1,
	MOVE_COUNT = 1
};

typedef struct Point
{
	int x;
	int y;
} Point;

class Block
{
public:
	Block(int _shape, int _angle, int _color, int _x, int _y) 
		: shape(_shape), angle(_angle), color(_color), x(_x), y(_y) {}
	~Block() {}

	//업데이트 함수로 이동
	void Update()
	{
		//y값 변경
	}

	void Move() { ++y; }
	void SetX(const int _x) { x = _x; }
	void SetY(const int _y) { y = _y; }
	void SetAngle(const int _angle) { angle = _angle; }
	int GetX() const { return x; }
	int GetY() const { return y; }
	int GetShape() const { return shape; }
	int GetAngle() const { return angle; }
	int GetColor() const { return color; }

private:
	int shape;
	int angle;
	int color;
	int x, y;
};

enum ground_size
{
	START_W = 0,
	WIDTH = 14,
	END_W = WIDTH - 1,
	START_H = 0,
	HEIGHT = 21,
	END_H = HEIGHT - 1,
	BLOCK_SIZE = 20,
	START_GROUND_X = BLOCK_SIZE * 2,
	START_GROUND_Y = BLOCK_SIZE,
	IMG_SIZE = 16,
	DESTRUCTION_FRAME_COUNT = 2
};

struct GroundBlock
{
	//위치 정보 추가할 것
	char existence;
	bool destruction;
	int frame;
	int color;
};
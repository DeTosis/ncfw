#pragma once 

struct IVec2 {
	int x = 0;
	int y = 0;
	
	IVec2 operator+(IVec2 other) {
		IVec2 res = *this;
		res.x += other.x;
		res.y += other.y;
		return res;
	}
	IVec2 operator-(IVec2 other) {
		IVec2 res = *this;
		res.x -= other.x;
		res.y -= other.y;
		return res;
	}
};

#pragma once

#include <list>
#include "CDisplayStatic.h"

typedef unsigned int uint;

class CDisplayStatic;

class DisplayController
{
public:
	DisplayController();
	~DisplayController();

	// CDisplayStatic 객체 설정 (필수)
	void setDisplayObject(CDisplayStatic* ctrl);

	// Display 영역의 크기(상대좌표) 지정
	void setCoordinateWidth(uint width);

	// 각종 그리기용 함수 (public APIs)
	void setBackgroundColor(COLORREF clr);
	void setBackgroundColor(uint r, uint g, uint b);
	void reset();

	void setThreatTrajectoryColor(COLORREF clr);
	void setThreatTrajectoryColor(uint r, uint g, uint b);
	void setMissileTrajectoryColor(COLORREF clr);
	void setMissileTrajectoryColor(uint r, uint g, uint b);

	void createThreatObject(const uint x, const uint y);
	void createMissileObject(const uint x, const uint y);
	void removeThreatObject();
	void removeMissileObject();
	void updateThreatPosition(const uint x, const uint y);
	void updateMissilePosition(const uint x, const uint y);

private:
	// 각종 그리기용 함수 (private)
	void render();

	void drawArrows();
	void drawBackground();
	void drawThreat();
	void drawMissile();

private:
	CDisplayStatic* dispObj;
	CDC* dc;
	CRect extent;
	COLORREF bgColor;
	COLORREF threatTrajectoryColor;
	COLORREF missileTrajectoryColor;

	// 좌표계의 x,y 크기
	uint coordinateWidth;
	uint coordinateHeight;

	uint arrowX;
	uint arrowY;

	struct Position {
		uint x;
		uint y;
	};

	std::list<Position> threatPositionList;
	std::list<Position> missilePositionList;

private:
	// Display 좌표 계산
	CPoint getRelativePosition(Position p);
};


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

	// CDisplayStatic ��ü ���� (�ʼ�)
	void setDisplayObject(CDisplayStatic* ctrl);

	// Display ������ ũ��(�����ǥ) ����
	void setCoordinateWidth(uint width);

	// ���� �׸���� �Լ� (public APIs)
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
	// ���� �׸���� �Լ� (private)
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

	// ��ǥ���� x,y ũ��
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
	// Display ��ǥ ���
	CPoint getRelativePosition(Position p);
};


#include "pch.h"
#include "DisplayController.h"

DisplayController::DisplayController()
{
	dispObj = nullptr;
	coordinateWidth = 1;
	coordinateHeight = 1;
	arrowX = 10;
	arrowY = 10;
}

DisplayController::~DisplayController()
{
	
}

void DisplayController::setDisplayObject(CDisplayStatic* dispObj)
{
	this->dispObj = dispObj;
	this->dc = dispObj->GetDC();
	this->bgColor = dc->GetBkColor();

	dispObj->GetClientRect(&extent);
	coordinateWidth = extent.Width();
	coordinateHeight = extent.Height();
}

void DisplayController::setCoordinateWidth(uint width)
{
	coordinateWidth = width;
	coordinateHeight = width * (double)(extent.Height() / (double)extent.Width());
}

void DisplayController::setBackgroundColor(COLORREF clr)
{
	bgColor = clr;
	render();
}

void DisplayController::setBackgroundColor(uint r, uint g, uint b)
{
	setBackgroundColor(RGB(r, g, b));
}

void DisplayController::setThreatTrajectoryColor(COLORREF clr)
{
	threatTrajectoryColor = clr;
	render();
}

void DisplayController::setThreatTrajectoryColor(uint r, uint g, uint b)
{
	setThreatTrajectoryColor(RGB(r, g, b));
}

void DisplayController::setMissileTrajectoryColor(COLORREF clr)
{
	missileTrajectoryColor = clr;
	render();
}

void DisplayController::setMissileTrajectoryColor(uint r, uint g, uint b)
{
	setMissileTrajectoryColor(RGB(r, g, b));
}

void DisplayController::reset()
{
	threatPositionList.clear();
	missilePositionList.clear();
	render();
}

void DisplayController::createThreatObject(const uint x, const uint y)
{
	if (threatPositionList.empty())
	{
		threatPositionList.push_back({ x, y });
	}
	render();
}

void DisplayController::createMissileObject(const uint x, const uint y)
{
	if (missilePositionList.empty())
	{
		missilePositionList.push_back({ x, y });
	}
	render();
}

void DisplayController::removeThreatObject()
{
	threatPositionList.clear();
	render();
}

void DisplayController::removeMissileObject()
{
	missilePositionList.clear();
	render();
}

void DisplayController::updateThreatPosition(const uint x, const uint y)
{
	Position p = { x, y };
	threatPositionList.push_back(p);
	render();
}

void DisplayController::updateMissilePosition(const uint x, const uint y)
{
	Position p = { x, y };
	missilePositionList.push_back(p);
	render();
}

void DisplayController::render()
{
	// background color
	drawBackground();

	// coordinate arrows
	drawArrows();

	// threat object & trajectory
	drawThreat();

	// missile object & trajectory
	drawMissile();

	// redraw
	dispObj->Invalidate(FALSE);
}

void DisplayController::drawArrows()
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	dc->SelectObject(&pen);

	// X axis
	dc->MoveTo(5, extent.Height() - arrowY);
	dc->LineTo(extent.Width() - 5, extent.Height() - arrowY);
	dc->LineTo(extent.Width() - 12, extent.Height() - arrowY - 6);
	dc->MoveTo(extent.Width() - 5, extent.Height() - arrowY);
	dc->LineTo(extent.Width() - 12, extent.Height() - arrowY + 6);

	// Y axis
	dc->MoveTo(arrowX, extent.Height() - 5);
	dc->LineTo(arrowX, 5);
	dc->LineTo(arrowX - 6, 5 + 12);
	dc->MoveTo(arrowX, 5);
	dc->LineTo(arrowX + 6, 5 + 12);
}

void DisplayController::drawBackground()
{
	CBrush br;
	br.CreateSolidBrush(bgColor);

	dc->FillRect(&this->extent, &br);
}

void DisplayController::drawThreat()
{
	if (!threatPositionList.empty())
	{
		auto p = getRelativePosition(*threatPositionList.begin());
		decltype(p) last = p;
		auto itr = threatPositionList.begin();
		itr++;

		CPen pen;
		pen.CreatePen(PS_SOLID, 3, threatTrajectoryColor);
		dc->SelectObject(&pen);
		dc->MoveTo(p.x, p.y);

		while (itr != threatPositionList.end())
		{
			auto p = getRelativePosition(*itr);
			dc->LineTo(p.x, p.y);
			last = p;
			itr++;
		}	

		CString t = _T("T");
		CRect r(last.x - 5, last.y - 8, last.x + 5, last.y + 7);
		dc->DrawText(t, &r, DT_CENTER | DT_VCENTER);		
	}
}

void DisplayController::drawMissile()
{
	if (!missilePositionList.empty())
	{
		auto p = getRelativePosition(*missilePositionList.begin());
		decltype(p) last = p;
		auto itr = missilePositionList.begin();
		itr++;

		CPen pen;
		pen.CreatePen(PS_DASHDOTDOT, 3, missileTrajectoryColor);
		dc->SelectObject(&pen);
		dc->MoveTo(p.x, p.y);

		while (itr != missilePositionList.end())
		{
			auto p = getRelativePosition(*itr);
			dc->LineTo(p.x, p.y);
			last = p;
			itr++;
		}

		CString t = _T("M");
		CRect r(last.x - 5, last.y - 8, last.x + 5, last.y + 7);
		dc->DrawText(t, &r, DT_CENTER | DT_VCENTER);		
	}
}

CPoint DisplayController::getRelativePosition(Position p)
{
	CPoint result;

	double wratio = (extent.Width() - arrowX) / (double)coordinateWidth;
	double hratio = (extent.Height() - arrowY) / (double)coordinateHeight;

	// 화면의 Y좌표는 top->bottom이나 객체의 좌표는 bottom->top이므로 이를 고려한다.
	result.x = p.x * wratio + arrowX;
	result.y = extent.Height() - arrowY - p.y * hratio;

	return result;
}
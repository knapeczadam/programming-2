// Knapecz, Adam - 1DAE11

#pragma once

enum class State
{
	green,
	orange,
	red,
	off
};

class TrafficLight
{
public:
	explicit TrafficLight();
	explicit TrafficLight(const Point2f& pos);
	void DoHitTest(const Point2f& point);
	void Update(float elapsedSec);
	void Draw() const;
	float GetWidth() const;
	void SetWidth(float width);
	float GetHeight() const;
	void SetHeight(float height);
	float GetRadius() const;
	void SetRadius(float radius);
	void SetPosition(const Point2f& newPosition);
	void SetState(State state);

private:
	State m_State;
	Point2f m_Position;
	float m_AccumulatedSec;

	float m_Width;
	float m_Height;
	float m_Radius;

};


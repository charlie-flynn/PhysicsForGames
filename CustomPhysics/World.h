#pragma once

class World
{
protected:
	// Elapsed time between last fixed tick
	float AccumulatedFixedTime;
public:
	// time between fixed tick
	float TargetFixedStep;

	World();

	void Init();
	void Tick();
	void TickFixed();
	void Draw();
	void Exit();

	bool ShouldClose() const;
	bool ShouldTickFixed() const;

protected:
	// Runs at the end of Init
	virtual void OnInit() {}
	// Runs at the end of Tick
	virtual void OnTick() {}
	// Run at end of TickFixed
	virtual void OnTickFixed() {}
	// Runs at the start of Draw
	virtual void OnDraw() const {}
	// Runs at the start of Exit
	virtual void OnExit() {}
};
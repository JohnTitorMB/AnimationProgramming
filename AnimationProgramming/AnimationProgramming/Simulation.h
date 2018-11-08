#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include "Engine.h"
#include "Skeleton.h"

class ENGINE_API ISimulation
{
public:
	virtual ~ISimulation() {}

	virtual void Init() = 0;
	virtual void Update(float frameTime) = 0;
};

class CSimulation : public ISimulation
{
private:
	Skeleton* m_skeleton;

	virtual void Init() override;
	virtual void Update(float frameTime) override;

	void DrawBase(); //Draw X, Y and Z axes
	
public:
	CSimulation();
	CSimulation(const CSimulation& simulation) = delete;
	~CSimulation();
	CSimulation& operator=(const CSimulation& simulation) = delete;
	CSimulation(CSimulation&& simulation) = delete;
};


#endif
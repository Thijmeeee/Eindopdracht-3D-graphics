#pragma onceq	

#include "Component.h"

class ArrowUpdateComponent : public Component
{

public:
	ArrowUpdateComponent() = default;
	~ArrowUpdateComponent() = default;

	virtual void update(float elapsedTime) override;
};
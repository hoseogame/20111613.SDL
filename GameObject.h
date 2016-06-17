#pragma once

class LoaderParams;

class GameObject
{
public:
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Clean() = 0;
	virtual void Load(const LoaderParams* params) = 0;

	virtual ~GameObject() {}

protected:
	GameObject() {}
};
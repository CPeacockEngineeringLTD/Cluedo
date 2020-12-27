#pragma once
class object{
protected:
	int randomPrecedenceStatus;
public:
	int getPrecedence() {
		return randomPrecedenceStatus;
	}
	virtual void chooseMurder() = 0;
	//virtual bool checkMurder(int a) = 0;
};


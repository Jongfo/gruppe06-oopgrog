#pragma once
#include "ListTool2B.h"
#include "ConstEnum.h"
#include "RobustIO.h"
#include "DivAvd.h"

extern RobustIO rIO;
class Idrett : TextElement
{
private:
	List * divisjoner;
	char* tabelltype;

public:
	Idrett(char* navn);
	void display();
	~Idrett();
};
#pragma once
#include "ListTool2B.h"
#include "ConstEnum.h"

class Idrett : TextElement
{
private:
	List * divisjoner;
	Tabelltype tabelltype;

public:
	Idrett(char* navn);
	~Idrett();
};
#include "Idrett.h"

Idrett::Idrett(char* navn) : TextElement(navn)
{

}

Idrett::~Idrett()
{
	delete divisjoner;
}
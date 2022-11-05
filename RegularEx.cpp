#include"RegularEx.h"
using  namespace std;

regex Regular::preSp()
{
	return regex("^[ \t]*");
}
regex Regular::postSp()
{
	return regex("[ \t]*$");
}
regex Regular::header()
{
	return regex("#[ \t]*include[ \t]*<stdio.h[ \t]*>");
}
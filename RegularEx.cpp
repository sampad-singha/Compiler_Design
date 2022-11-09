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
regex Regular::namingConversion()
{
	return regex("^[a-zA-Z_$][a-zA-Z_$0-9]*$");
}
regex Regular::mainFunc()
{
	return regex("^(int|void)[ \t]*main[ \t]*\([ \t]*\)({[ \t]*return[ \t]*0[ \t]*;[ \t]*})$");
}
regex Regular::fullCodereg()
{
	return regex("^({[ \t]*return[ \t]*0[ \t]*;[ \t]*})$");
}
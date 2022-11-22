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
	return regex("(int|void)[ \t]+main[ \t]*([ \t]*){[ \t]*(return)[ \t]+[0][ \t]*[;][ \t]*}");
	return regex("(int|void)[ \t]+main[ \t]*([ \t]*)[ \t]*{[ \t]*retur");

}
regex Regular::fullCodereg()
{
	return regex("^({[ \t]*return[ \t]*0[ \t]*;[ \t]*})$");
}
regex Regular::keyword()
{
	return regex("(auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while)");
}
regex Regular::identifier()
{
	return regex("^[a-zA-Z_$][a-zA-Z_$0-9]*$");
}
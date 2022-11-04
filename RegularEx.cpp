#include "RegularEx.h"
#include <regex>
using  namespace std;

class regular
{
public:
	regex preSpace();
	regex postSpace();

private:

};

regex regular::preSpace()
{
	regex preSp("^[ \t]*");
	return preSp;
}

regex regular::postSpace()
{
	regex postSp("[ \t]*$");
	return postSp;
}

#include <iostream>
#include"SyntaxAnalyzer.cpp"
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	SyntaxAnalzyer s;
	s.readGrammer();
    s.indexInit();
	s.VNfirstSetInit();
	s.VNfollowSetInit();
	s.getItem();
	///s.show();
    s.makeItemSet();
    s.makeTable();
    s.writefile2();
    s.analyzer();

}

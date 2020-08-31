#include <iostream>
#include<string>
#include<fstream>
#include"LexAnalyzer.cpp"
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
   LexAnalyzer lexanalyzer;
   lexanalyzer.readSourceFile();
   lexanalyzer.readGrammer();
   lexanalyzer.NFAtoDFA();
   lexanalyzer.analyze(); 
   lexanalyzer.saveResult();
}


#ifndef ClassCommun_h
#define ClassCommun_h
#include <cstdio>
#include <cstdlib>
#include <include/SDL/SDL.h>
#include <include/SDL/SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <ctime>
using namespace std;
char *convertRectToTabChar(SDL_Rect pos){
    stringstream x,y;
    x << pos.x;
    y << pos.y;
    string a="X="+x.str()+";Y="+y.str();
    return (char*)a.c_str();
}
char *convertIntToTabChar(int i){
    stringstream x;
    x << i;
    string a="indice:"+x.str();
    return (char*)a.c_str();
}
#endif // ClassCommun_h


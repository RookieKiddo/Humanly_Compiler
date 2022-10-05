#include <bits/stdc++.h>

using namespace std;

vector<string> l;

int check = 0; //to iterate indexes of string l
void match(string t);
void declarations();
void declaration();
void type();
void varlist();
void start();
void statement();
void tail();
void if_statement();
void else_statement();
void else_if_statement();
void while_statement();
void expression();
void assignment();
void comment();
void constant();
void input_output();
void parser();
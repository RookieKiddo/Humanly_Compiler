/* 
To Create This Lexical Analyzer Help Is Taken From The Following Link:
https://github.com/amirhakimnejad/Scanner-for-lexical-analyzer-in-cpp
This Code Is The Modified Version Of The Code Taken From The Link Above

Parser code is made entirely from scratch by the group memebers 
*/

#include <bits/stdc++.h>

using namespace std;

// Parser //
vector<string> l; // Look ahead //

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


// Lexical Analyzer // 
bool isNotLegal(const std::string &str);
bool isLiteral(const std::string &str);
bool isDigit(const std::string &str);
bool isDataType(const string &str);
bool iskeyWord(const string &str);
bool isPunctuators(const string &str);
bool isOperator(const string &str);
bool isIdentifier(const string &str);
bool isComment(const std::string &str);
void printRoleOfToken(const std::string &token);
void lexicalScanner(std::string &filename);

ofstream MyFile("tokens.txt");

int main()
{
    MyFile.flush();

    string fname = "SourceFile.hy";

    cout << "Lexical Analyzer in C++" << endl;
    cout << "--------------------------------" << endl;
    cout << "Team Members :-" << endl;
    cout << "1. Babar Siddiqi (cs182006)" << endl;
    cout << "2. Aaisha Motan (cs182009)" << endl;
    cout << "3. Aheed Uddin Basri (cs182010)" << endl;
    cout << "--------------------------------" << endl;

    lexicalScanner(fname);
    MyFile << " $ ";
    MyFile.close();

    cout << endl << " Parser Activated " << endl;

    parser();

    return 0;
}

bool isNotLegal(const std::string &str)
{
    return str == " " || str == "\n";
}

bool isDigit(const std::string &str)
{
    char ch;
    string buffer;

    for (int i = 0; i < str.size(); i++)
    {
        ch = str[i];

        if (!isdigit(ch))
        {
            return false;
        }
    }

    return true;
}

bool isLiteral(const std::string &str)
{
    return str[0] == '"' && str[str.size() - 1] == '"';
}

bool isDataType(const string &str)
{
    const vector<string> dataType{"DEC", "NUM", "WORD"};

    for (const auto &dataType : dataType)
    {
        if (dataType == str)
        {
            return true;
        }
    }

    return false;
}

bool iskeyWord(const string &str)
{
    const vector<string> keyWords{"IF", "ELSE", "BUTIF", "LISTEN", "SHOW", "REPEAT"};

    for (const auto &keyWords : keyWords)
    {
        if (keyWords == str)
        {
            return true;
        }
    }

    return false;
}

bool isOperator(const string &str)
{
    const vector<std::string> operators{"<", ">", "<=", ">=", "*", "+", "-", "/", "=", "<-", "AND", "OR", "~"};

    for (const auto &op : operators)
    {
        if (op == str)
        {
            return true;
        }
    }

    return false;
}

bool isPunctuators(const string &str)
{
    const vector<std::string> punctuators{"(", ")", "[", "]", "{", "}", ".", ";", ","};

    for (const auto &pc : punctuators)
    {
        if (pc == str)
        {
            return true;
        }
    }

    return false;
}

bool isIdentifier(const string &str)
{
    if (isdigit(str[0]))
    {
        return false;
    }
    if (str[0] == '_')
    {
        return false;
    }

    int counter = 0;

    if (isalpha(str[0]))
    {
        counter++;
    }

    while (counter < str.size())
    {
        if (!(isalnum(str[counter])))
        {
            if (str[counter] != '_')
            {
                return false;
            }
        }
        counter++;
    }
    return true;
}

bool isComment(const std::string &str)
{
    return str == "/#" || str == "//";
}

void printRoleOfToken(const std::string &token)
{

    if (isDataType(token))
    {
        //cout << "(DataType, " << token << ")";
        if (token == "NUM")
        {
            cout << " NUM ";
            MyFile << "NUM";
        }
        else if (token == "DEC")
        {
            cout << " DEC ";
            MyFile << " DEC ";
        }
        else if (token == "WORD")
        {
            cout << " WORD ";
            MyFile << " WORD ";
        }
    }
    else if (isOperator(token))
    {
        //cout << "(Operator, " << token << ")";
        if (token == "<-")
        {
            cout << " Assignment_Operator ";
            MyFile << " Assignment_Operator ";
        }
        else if (token == "<")
        {
            cout << " LessThan_Operator ";
            MyFile << " LessThan_Operator ";
        }
        else if (token == ">")
        {
            cout << " GreaterThan_Operator ";
            MyFile << " GreaterThan_Operator ";
        }
        else if (token == "<=")
        {
            cout << " LessThan_OR_Equals_Operator ";
            MyFile << " LessThan_OR_Equals_Operator ";
        }
        else if (token == ">=")
        {
            cout << " GreaterThan_OR_Equals_Operator ";
            MyFile << " GreaterThan_OR_Equals_Operatorrator ";
        }
        else if (token == "+")
        {
            cout << " Plus_Operator ";
            MyFile << " Plus_Operator ";
        }
        else if (token == "-")
        {
            cout << " Minus_Operator ";
            MyFile << " Minus_Operator ";
        }
        else if (token == "*")
        {
            cout << " Multiply_Operator ";
            MyFile << "Multiply_Operatorr ";
        }
        else if (token == "/")
        {
            cout << " Divide_Operator ";
            MyFile << " Divide_Operator ";
        }
        else if (token == "=")
        {
            cout << " Equals_Operator ";
            MyFile << " Equals_Operator ";
        }

        else if (token == "AND")
        {
            cout << "And_Operator ";
            MyFile << " And_Operator ";
        }
        else if (token == "OR")
        {
            cout << " Or_Operator ";
            MyFile << " Or_Operator ";
        }
        else if (token == "~")
        {
            cout << " Not_Operator ";
            MyFile << " Not_Operator ";
        }
    }

    else if (iskeyWord(token))
    {
        //cout << "(Reserved Keyword, " << token << ")";
        if (token == "IF")
        {
            cout << " IF ";
            MyFile << " IF ";
        }
        else if (token == "BUTIF")
        {
            cout << " BUTIF ";
            MyFile << " BUTIF ";
        }
        else if (token == "ELSE")
        {
            cout << " ELSE ";
            MyFile << "  ELSE ";
        }
        else if (token == "SHOW")
        {
            cout << " SHOW ";
            MyFile << " SHOW ";
        }
        else if (token == "LISTEN")
        {
            cout << " LISTEN ";
            MyFile << " LISTEN ";
        }
        else if (token == "REPEAT")
        {
            cout << " REPEAT ";
            MyFile << " REPEAT ";
        }
    }
    else if (isIdentifier(token))
    {
        cout << "(ID, " << token << ")";
        MyFile << " ID ";
    }
    else if (isDigit(token))
    {
        cout << "(INTEGER, " << token << ")";
        MyFile << " INTEGER ";
    }
    else if (isPunctuators(token))
    {
        //cout << "(Punctuator, " << token << ")";
        if (token == "(")
        {
            cout << "Open_Ronud_Bracket  ";
            MyFile << " Open_Ronud_Bracket  ";
        }
        else if (token == ")")
        {
            cout << " Close_Round_Bracket";
            MyFile << "Close_Round_Bracket ";
        }
        else if (token == "{")
        {
            cout << " Open_Curly_Bracket ";
            MyFile << " Open_Curly_Bracket ";
        }
        else if (token == "}")
        {
            cout << " Close_Curly_Bracket ";
            MyFile << " Close_Curly_Bracket ";
        }
        else if (token == "[")
        {
            cout << " Open_Square_Bracke ";
            MyFile << " Open_Square_Bracke ";
        }
        else if (token == "]")
        {
            cout << " Close_Square_Bracket ";
            MyFile << " Close_Square_Bracket ";
        }
        else if (token == ".")
        {
            cout << " FLOAT ";
            MyFile << " FLOAT ";
        }
        else if (token == ";")
        {
            cout << " Terminator ";
            MyFile << " Terminator ";
        }
        else if (token == ",")
        {
            cout << " Comma ";
            MyFile << "  Comma ";
        }
    }
    else if (isLiteral(token))
    {
        cout << "(LITERAL, " << token << ")";
        MyFile << " LITERAL ";
    }
    else if (isComment(token))
    {
        cout << "(IGNORE, " << token << ")";
        MyFile << " IGNORE ";
    }
    else
    {
        throw std::runtime_error("Invalid token: " + token);
    }
}

void lexicalScanner(std::string &filename)
{
    char ch;
    string data;
    string buffer;
    bool miltiCm = false;
    fstream file(filename, fstream::in);

    if (!file.is_open())
    {
        cout << "error while opening the file" << endl;
        exit(0);
    }
    else
    {
        cout << "File Opened Successfully" << endl
             << endl;
    }

    cout << "Tokens :- " << endl;
    cout << "--------------------------------" << endl;

    while (file >> noskipws >> ch)
    {
        if (miltiCm)
        {
            if (miltiCm && ch == '#')
            {
                file >> ch;
                if (ch == EOF)
                    break;

                if (ch == '/')
                    miltiCm = false;
            }
            continue;
        }

        if (ch == '/')
        {
            std::string comm(1, ch);
            file >> ch;
            if (ch == EOF)
            {
                printRoleOfToken(comm);
                break;
            }

            if (ch == '#')
            {
                miltiCm = true;
                comm += ch;
            }
            if (miltiCm)
            {
                printRoleOfToken(comm);
                continue;
            }
        }

        if (ch == '"')
        {
            file >> ch;
            buffer += '"';
            while (true)
            {
                if (ch != '"')
                {
                    file >> ch;
                    buffer += ch;
                    continue;
                }
                else
                {
                    if (!buffer.empty())
                    {
                        printRoleOfToken(buffer);
                        buffer = "";
                        file >> ch;
                        break;
                    }
                }
            }
        }

        if (isNotLegal(std::string(1, ch)))
        {
            if (!buffer.empty())
            {
                printRoleOfToken(buffer);
                buffer = "";
            }
            continue;
        }
        if (isPunctuators(string(1, ch)))
        {
            if (!buffer.empty())
            {
                printRoleOfToken(buffer);
                buffer = "";
            }
            if (isPunctuators(string(1, ch)))
            {
                printRoleOfToken(string(1, ch));
                continue;
            }
        }

        buffer += ch;
    }

    file.close();

    cout << endl
         << "\nFile Closed Successfully" << endl;
}


// Parser Part //
void parser()
{
    string temp;
    ifstream file("tokens.txt");

    while (file >> temp)
    {
        l.push_back(temp);
    }

    start();

    if (l[check] == "$")
    {
        cout << endl
             << "Parsing Successful" << endl;
    }
    else
    {
        cout << "Parsing Failed" << endl;
    }
    file.close();
}

void start()
{
    comment();
    declaration();
    statement();
    if (l[check] == "$")
    {
        return;
    }
    start();
}

void declaration()
{
    type();
    varlist();
    assignment();
    expression();
    if (l[check] == "Terminator")
    {
        cout << " , ";
        match("Terminator");
    }
}

void type()
{

    if (l[check] == "NUM")
    {
        cout << " NUM ";
        match("NUM");
    }
    else if (l[check] == "DEC")
    {
        cout << " DEC ";
        match("DEC");
    }
    else if (l[check] == "WORD")
    {
        cout << " WORD ";
        match("WORD");
    }
}

void varlist()
{
    if (l[check] == "ID")
    {
        cout << " ID ";
        match("ID");
        if (l[check] == "Comma")
        {
            match("Comma");
            cout << " , ";
            varlist();
        }
    }
}

void statement()
{
    if_statement();
    while_statement();
    expression();
    assignment();
    input_output();
    comment();
    return;
}

void if_statement()
{
    if (l[check] == "IF")
    {
        cout << " IF ";
        match("IF");
        if (l[check] == "Open_Ronud_Bracket")
        {
            cout << " ( ";
            match("Open_Ronud_Bracket");

            expression();

            if (l[check] == "Close_Round_Bracket")
            {
                cout << " ) ";
                match("Close_Round_Bracket");
                tail();
            }
            else
            {
                cout << "Wrong Statement 1 IF" << endl;
                exit(0);
            }
        }
        else
        {
            cout << "Wrong Statement IF" << endl;
            exit(0);
        }
    }
    else
    {
        else_if_statement();
        else_statement();
    }
}

void else_if_statement()
{
    if (l[check] == "BUTIF")
    {
        cout << " BUTIF ";
        match("BUTIF");

        if (l[check] == "Open_Ronud_Bracket")
        {
            cout << " ( ";
            match("Open_Ronud_Bracket");

            expression();

            if (l[check] == "Close_Round_Bracket")
            {
                cout << " ) ";
                match("Close_Round_Bracket");
                tail();
            }
            else
            {
                cout << "Wrong Statement 1 BUTIF" << endl;
                exit(0);
            }
        }
        else
        {
            cout << "Wrong Statement BUTIF" << endl;
            exit(0);
        }

        else_if_statement();
    }
    else
    {
        return;
    }
}

void else_statement()
{
    if (l[check] == "ELSE")
    {
        cout << " ELSE ";
        match("ELSE");
        tail();
    }
    else
    {
        return;
    }
}

void while_statement()
{
    if (l[check] == "REPEAT")
    {
        cout << " REPEAT ";
        match("REPEAT");
        if (l[check] == "Open_Ronud_Bracket")
        {
            cout << " ( ";
            match("Open_Ronud_Bracket");

            expression();

            if (l[check] == "Close_Round_Bracket")
            {
                cout << " ) ";
                match("Close_Round_Bracket");
                tail();
            }
            else
            {
                cout << "Wrong Statement 1 REPEAT" << endl;
                exit(0);
            }
        }
        else
        {
            cout << "Wrong Statement REPEAT" << endl;
            exit(0);
        }
    }
}

void expression()
{
    if (l[check] == "ID")
    {
        cout << " ID ";
        match("ID");

        if (l[check] == "LessThan_Operator")
        {
            cout << " < ";
            match("LessThan_Operator");
            expression();
            return;
        }
        else if (l[check] == "GreaterThan_Operator")
        {
            cout << " > ";
            match("GreaterThan_Operator");
            expression();
            return;
        }
        else if (l[check] == "Plus_Operator")
        {
            cout << " + ";
            match("Plus_Operator");
            expression();
            return;
        }
        else if (l[check] == "Multiply_Operator")
        {
            cout << " * ";
            match("Multiply_Operator");
            expression();
            return;
        }
        else if (l[check] == "Divide_Operator")
        {
            cout << " / ";
            match("Divide_Operator");
            expression();
            return;
        }
        else if (l[check] == "Or_Operator")
        {
            cout << " OR ";
            match("Or_Operator");
            expression();
            return;
        }
        else if (l[check] == "And_Operator")
        {
            cout << " AND ";
            match("And_Operator");
            expression();
            return;
        }
        else if (l[check] == "Equals_Operator")
        {
            cout << " = ";
            match("Equals_Operator");
            expression();
            return;
        }
        else if (l[check] == "GreaterThan_OR_Equals_Operator")
        {
            cout << " >= ";
            match("GreaterThan_OR_Equals_Operator");
            expression();
            return;
        }
        else if (l[check] == "LessThan_OR_Equals_Operator")
        {
            cout << " <= ";
            match("LessThan_OR_Equals_Operator");
            expression();
            return;
        }
        else if (l[check] == "GreaterThan_Operator")
        {
            cout << " < ";
            match("GreaterThan_Operator");
            expression();
            return;
        }
    }
    else
    {
        constant();
        return;
    }
}

void constant()
{
    if (l[check] == "INTEGER")
    {
        cout << " INTEGER ";
        match("INTEGER");
    }
    else if (l[check] == "FLOAT")
    {
        cout << " FLOAT ";
        match("FLOAT");
    }
    else if (l[check] == "LITERAL")
    {
        cout << " LITERAL ";
        match("LITERAL");
    }
}

void tail()
{
    if (l[check] == "Open_Curly_Bracket")
    {
        cout << " { ";
        match("Open_Curly_Bracket");
        statement();
        tail();
    }
    else if (l[check] == "Close_Curly_Bracket")
    {
        cout << " } ";
        match("Close_Curly_Bracket");
        tail();
    }
    else
    {
        return;
    }
}

void assignment()
{
    type();
    varlist();
    if (l[check] == "Assignment_Operator")
    {
        cout << " <- ";
        match("Assignment_Operator");
    }
    else
    {
        return;
    }
    expression();
    if (l[check] == "Terminator")
    {
        cout << " ; ";
        match("Terminator");
    }
}

void input_output()
{
    if (l[check] == "LISTEN")
    {
        cout << " LISTEN ";
        match("LISTEN");

        if (l[check] == "Open_Ronud_Bracket")
        {
            cout << " ( ";
            match("Open_Ronud_Bracket");

            if (l[check] == "ID")
            {
                cout << " ID ";
                match("ID");

                if (l[check] == "Close_Round_Bracket")
                {
                    cout << ")";
                    match("Close_Round_Bracket");
                    tail();
                }
                else
                {
                    cout << "Wrong Statement 1 INPUT" << endl;
                    exit(0);
                }

                if (l[check] == "Terminator")
                {
                    cout << " ; ";
                    match("Terminator");
                }
                else
                {
                    cout << "Wrong Statement 2 INPUT" << endl;
                    exit(0);
                }
            }
            else
            {
                cout << "Wrong Statement 3 INPUT" << endl;
                exit(0);
            }
        }
        else
        {
            cout << "Wrong Statement INPUT" << endl;
            exit(0);
        }
    }

    if (l[check] == "SHOW")
    {
        cout << " SHOW ";
        match("SHOW");

        if (l[check] == "Open_Ronud_Bracket")
        {
            cout << " ( ";
            match("Open_Ronud_Bracket");

            if (l[check] == "LITERAL")
            {
                cout << " LITERAL ";
                match("LITERAL");

                if (l[check] == "Close_Round_Bracket")
                {
                    cout << " ) ";
                    match("Close_Round_Bracket");
                    tail();
                }
                else
                {
                    cout << "Wrong Statement 1 OUTPUT" << endl;
                    exit(0);
                }
                if (l[check] == "Terminator")
                {
                    cout << " ; ";
                    match("Terminator");
                }
                else
                {
                    cout << "Wrong Statement 2 OUTPUT" << endl;
                    exit(0);
                }
            }
            else if (l[check] == "ID")
            {
                cout << " ID ";
                match("ID");

                if (l[check] == "Close_Round_Bracket")
                {
                    cout << " ) ";
                    match("Close_Round_Bracket");
                    tail();
                }
                else
                {
                    cout << "Wrong Statement 3 OUTPUT" << endl;
                    exit(0);
                }
                if (l[check] == "Terminator")
                {
                    cout << " ; ";
                    match("Terminator");
                }
                else
                {
                    cout << "Wrong Statement 4 INPUT" << endl;
                    exit(0);
                }
            }
            else
            {
                cout << "Wrong Statement 3 OUTPUT" << endl;
                exit(0);
            }
        }
        else
        {
            cout << "Wrong Statement  OUTPUT" << endl;
            exit(0);
        }
    }
}

void comment()
{
    if (l[check] == "IGNORE")
    {
        cout << " Comment Found ";
        match("IGNORE");
    }
    else
    {
        return;
    }
}

// Match function
void match(string t)
{
    if (l[check] == t)
    {
        check++;
    }
    else
        printf("Error");
}

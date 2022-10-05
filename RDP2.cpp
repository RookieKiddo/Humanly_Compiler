#include "RDP.h"

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

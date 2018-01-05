#include "scanner.h"
#include "parser.h"
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    string input, context = "";
    while (true)
    {
        do
        {
            if (context == "")
                cout << "?- ";
            else
                cout << "|   ";
            getline(cin, input);
            if (input != "")
                while (input[0] == ' ')
            input = input.substr(1, input.size() - 1);
            context += input;
        } while (input == "" || context.back() != '.');
        if (context == "halt.")
            break;
        
        try
        {
			Scanner s(context);
			Parser p(s);
            p.buildExpression();
			p.getExpressionTree()->evaluate() ;
			string result = p.getExpressionResult();
            cout << result << endl;
            //cout << parser->getResult() << endl;
        }
        catch (string &msg)
        {
            cout << msg << endl;
        }
        context = "";
    }
}
#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
//#include "procedure_functions.h"
using namespace std;

//functions used to determine input type-----------------------------------
bool isSeparator(char input);
bool isOperator(char input);
bool isUnderline(char input);
bool isDot(char input);
bool isKeyword(std::string input);
std::string operator_or_separator(char input);
bool isWhitespace(char input);
//2FSMs and helper functions
int FSM_col_determiner(char input);

int idFSM(int state, char input);
bool is_accepting_id(int state);

int intrealFSM(int state, char input);
bool is_accepting_intreal(int state);
//determine token type based on final state------------------------------------------
std::string ending_state_intreal(int state);
std::string ending_state_id(int state);


struct instruction_table
{
    string op;
    string oprnd;

    void new_instruction(string ope, string opre)
    {
        op = ope;
        oprnd = opre;
    }

    void print_ins(ofstream& outfile)
    {
        std::cout << op << "     " << oprnd << "\n";
        outfile << op << "     " << oprnd << "\n";
    
    }
};



class token_323 {
private:
    std::string token_323_;
    std::string lexeme_323_;


public:
    
    std::vector<instruction_table> all_instructions;
    std::vector<std::string> rule_holder;


    //constructor destructor
    token_323() {
        token_323_ = "none";
        lexeme_323_ = "none";
    }

    //~token323();

    //accessor and modifier functions------------------------------------------
    std::string token() { return token_323_; }
    std::string lexeme() { return lexeme_323_; }
    void token_update(std::string token) { token_323_ = token; }
    void lexeme_update(std::string lexeme) { lexeme_323_ = lexeme; }
    //void rule_holder_update(std::string rule) { }

    //function that helps print out rules
    void rule_print_helper()
    {//ofstream& outfile
        //token_print_helper();
        std::string tokenp;
        std::string lexemep;
        tokenp = token();
        lexemep = lexeme();
        std::cout << "Token: " << tokenp << "                   Lexeme: " << lexemep << "\n";
        //outfile << "Token: " << tokenp << "                   Lexeme: " << lexemep << "\n";
        
        
        int k = rule_holder.size() - 1;
        for (int i = k; i >= 0; i--)
        {
            std::cout << "   " << rule_holder[i] ;
            //outfile << "   " << rule_holder[i];
        }
    }


    //functions used to help print------------------------------------------
    void start_print_helper() {
        std::cout << "Program begins\n";
        std::cout << std::left << std::setw(15) << "token" << "lexeme" << "\n";
        //std::cout << "token" << "lexeme" << "\n";
        std::cout << "-------------------\n";
    }

    void token_print_helper() {
        //ofstream& outfile
        std::string tokenp;
        std::string lexemep;
        tokenp = token();
        lexemep = lexeme();
        std::cout <<"Token: " << tokenp << "                   Lexeme: " << lexemep << "\n";
        //outfile << std::left << std::setw(15) << tokenp << lexemep << "\n";
        //std::cout << lexemep << tokenp << "\n";
        //outfile << lexemep << tokenp << "\n";
    }
};


token_323 lexer_323(ifstream& input_file);



struct symbol_table_element
{
    //Identifier   MemoryLocation       Type
    string Identifier;
    int MemoryLocation;
    string Type;
    
    int get_ml(string id)
    {
        if (id == Identifier)
        {
            return MemoryLocation;
        }
        else 
        {
            //std::cout << "error, identifier not defined\n";
            return -1;
        }
    }



    void print_element(ofstream& outfile)
    {        
        std::cout << Identifier << "           " << MemoryLocation << "           " << Type << "\n";
        outfile << Identifier << "           " << MemoryLocation << "           " << Type << "\n";
    }
};




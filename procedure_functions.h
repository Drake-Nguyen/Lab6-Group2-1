#pragma once
#include "lexer.hpp"

bool identifierHelper(token_323 input_token);

// R28. <Primary> :: = <Identifier> | <Integer> | <Identifier>  (<IDs>) |
// (<Expression>) | <Real> | true | false
//---------------------------------------------------------------------------------------------------
bool procedurePrimary(vector<token_323> &all_tokens, int &loc);

// R27. <Factor> :: = -<Primary> | <Primary>
//---------------------------------------------------------------------------------------------------
bool procedureFactor(vector<token_323> &all_tokens, int &loc);

// R26.1 <Term'> :: = * <Factor> <Term>' | / <Factor> <Term>' | ϵ
//---------------------------------------------------------------------------------------------------
bool procedureTermq(vector<token_323> &all_tokens, int &loc);

// R26. <Term>    :: = <Factor> <Term>'
//---------------------------------------------------------------------------------------------------
bool procedureTerm(vector<token_323> &all_tokens, int &loc);

// R25. <Expression>  :: = <Term> <Expression'>
//---------------------------------------------------------------------------------------------------
bool procedureExpression(vector<token_323> &all_tokens, int &loc);

// R25.1 <Expression'>  :: = ϵ | +<Term> <Expression'>  | -<Term> <Expression'>
//---------------------------------------------------------------------------------------------------
bool procedureExpressionq(vector<token_323> &all_tokens, int &loc);

// R24. <Relop> :: = ==   |   !=    | > | <    |  <=   | = >
//---------------------------------------------------------------------------------------------------
bool procedureRelop(vector<token_323> &all_tokens, int &loc);

// R23. <Condition> :: = <Expression>  <Relop>   <Expression>
//---------------------------------------------------------------------------------------------------
bool procedureCondition(vector<token_323> &all_tokens, int &loc);

// R22. <While> :: = while (<Condition>) < Statement >
//---------------------------------------------------------------------------------------------------
bool procedureWhile(vector<token_323> &all_tokens, int &loc);

// R21. <Scan> :: = get(<IDs>);
//---------------------------------------------------------------------------------------------------
bool procedureScan(vector<token_323> &all_tokens, int &loc);

// R20. <Print> :: = put(<Expression>);
//---------------------------------------------------------------------------------------------------
bool procedurePrint(vector<token_323> &all_tokens, int &loc);

// R19. <Return> :: = return; | return <Expression>;
//---------------------------------------------------------------------------------------------------
bool procedureReturn(vector<token_323> &all_tokens, int &loc);

// R18. <If> :: = if (<Condition>) < Statement > fi | if (<Condition>) <
// Statement > else  <Statement>  fi
//---------------------------------------------------------------------------------------------------
bool procedureIf(vector<token_323> &all_tokens, int &loc);

// R17. <Assign> :: = <Identifier> = <Expression>;
//---------------------------------------------------------------------------------------------------
bool procedureAssign(vector<token_323> &all_tokens, int &loc);

// R16. <Compound> :: = { <Statement List> }
//---------------------------------------------------------------------------------------------------
bool procedureCompound(vector<token_323> &all_tokens, int &loc);

// R15. <Statement> :: = <Compound> | <Assign> | <If> | <Return> | <Print> |
// <Scan> | <While>
//---------------------------------------------------------------------------------------------------
bool procedureStatement(vector<token_323> &all_tokens, int &loc);

// R14. <Statement List> :: = <Statement> | <Statement> <Statement List>
//---------------------------------------------------------------------------------------------------
bool procedureStatementList(vector<token_323> &all_tokens, int &loc);

// R13. <IDs> :: = <Identifier> | <Identifier>, <IDs>
//---------------------------------------------------------------------------------------------------


bool procedureIDs(vector<token_323> &all_tokens, int &loc);



// R12. <Declaration> :: = <Qualifier > <IDs>
//---------------------------------------------------------------------------------------------------
bool procedureDeclaration(vector<token_323> &all_tokens, int &loc);

// R11. <Declaration List>  : = <Declaration>; | <Declaration>; <Declaration
// List>
//---------------------------------------------------------------------------------------------------
bool procedureDeclarationList(vector<token_323> &all_tokens, int &loc);

// R10. <Opt Declaration List> :: = <Declaration List> | <Empty>
//---------------------------------------------------------------------------------------------------
bool procedureOptDeclarationList(vector<token_323> &all_tokens, int &loc);

// R9. <Body>  :: = { < Statement List> }
//---------------------------------------------------------------------------------------------------
bool procedureBody(vector<token_323> &all_tokens, int &loc);

// R8. <Qualifier> :: = int | boolean | real
//---------------------------------------------------------------------------------------------------

bool procedureQualifier(vector<token_323> &all_tokens, int &loc);



// R7. <Parameter> :: = <IDs >  <Qualifier>
//---------------------------------------------------------------------------------------------------
bool procedureParameter(vector<token_323> &all_tokens, int &loc);

// R6. <Parameter List>  :: = <Parameter> | <Parameter>, <Parameter List>
//---------------------------------------------------------------------------------------------------


bool procedureParameterList(vector<token_323> &all_tokens, int &loc);


// R5. <Opt Parameter List> :: = <Parameter List> | <Empty>
//---------------------------------------------------------------------------------------------------
bool procedureOptParameterList(vector<token_323> &all_tokens, int &loc);

// R4. <Function> :: = function  <Identifier>  (  <Opt Parameter List>  )   <
// Opt Declaration List >   <Body>
bool procedureFunction(vector<token_323> &all_tokens, int &loc);

// R3. <Function Definitions>  :: = <Function> | <Function> <Function
// Definitions>
//---------------------------------------------------------------------------------------------------
bool procedureFunctionDefinitions(vector<token_323> &all_tokens, int &loc);

// R2. <Opt Function Definitions> :: = <Function Definitions> | <Empty>
//---------------------------------------------------------------------------------------------------
bool procedureOptFunctionDefinitions(vector<token_323> &all_tokens,
                                        int &loc);

// R1. <Rat20F>  :: = <Opt Function Definitions>   $$  <Opt Declaration List>
// <Statement List>  $$
//---------------------------------------------------------------------------------------------------
bool procedureRat20F(vector<token_323> &all_tokens, int &loc);

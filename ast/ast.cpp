/*!	
	\file    ast.cpp
	\brief   Code of funcitons of AST clas
	\author  
	\date    2018-12-13
	\version 1.0
*/

#include <iostream>
#include <stdlib.h>
#include <string>
#include <list>
#include <limits> 
// Para usar la funciones pow y std::abs
#include <cmath>

#include "ast.hpp"

#include "../table/table.hpp"

// warning
#include "../error/error.hpp"

// Macros for the screen
#include "../includes/macros.hpp"

// 
#include "../table/numericVariable.hpp"
#include "../table/logicalVariable.hpp"
#include "../table/stringVariable.hpp"

#include "../table/numericConstant.hpp"
#include "../table/logicalConstant.hpp"

#include "../table/builtinParameter0.hpp"
#include "../table/builtinParameter1.hpp"
#include "../table/builtinParameter2.hpp"

#include "../parser/interpreter.tab.h"



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

extern lp::Table table; //!< Reference to the Table of Symbols


extern lp::AST *root; //!< Reference to the object at the base of the AST


///////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::VariableNode::getType() 
{ 
	// Get the identifier in the table of symbols as Variable
	lp::Variable *var = (lp::Variable *) table.getSymbol(this->_id);

	// Return the type of the Variable
	return var->getType();
}


void lp::VariableNode::print() 
{
  std::cout << "VariableNode: " << this->_id << std::endl;
  std::cout << "Tipo: " << this->getType() << std::endl;
}


double lp::VariableNode::evaluateNumber() 
{ 
	double result = 0.0;

	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as NumericVariable
		lp::NumericVariable *var = (lp::NumericVariable *) table.getSymbol(this->_id);

		// Copy the value of the NumericVariable
		result = var->getValue();
	}
	else
	{
		warning("Error de ejecución en evaluateNumber(): la variable no es numérica", 
				   this->_id);
	}

	// Return the value of the NumericVariable
	return result;
}


bool lp::VariableNode::evaluateBool() 
{ 
	bool result = false;

	if (this->getType() == BOOL)
	{
		// Get the identifier in the table of symbols as LogicalVariable
		lp::LogicalVariable *var = (lp::LogicalVariable *) table.getSymbol(this->_id);

		// Copy the value of the LogicalVariable
		result = var->getValue();
	}
	else
	{
		warning("Error de ejecución en evaluateBool(): la variable no es booleana",
				   this->_id);
	}

	// Return the value of the LogicalVariable
	return result;
}

std::string lp::VariableNode::evaluateString(){
	std::string result = "";

	if (this->getType() == STRING)
	{
		// Get the identifier in the table of symbols as LogicalVariable
		lp::StringVariable *var = (lp::StringVariable *) table.getSymbol(this->_id);

		// Copy the value of the LogicalVariable
		result = var->getValue();
	}
	else
	{
		warning("Error de ejecución en evaluateString(): la variable no es una cadena",
				   this->_id);
	}

	// Return the value of the LogicalVariable
	return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ConstantNode::print() 
{
  std::cout << "ConstantNode: " << this->_id << std::endl;
  std::cout << "Tipo: " << this->getType() << std::endl;
}

int lp::ConstantNode::getType() 
{ 
	// Get the identifier in the table of symbols as Constant
	lp::Constant *var = (lp::Constant *) table.getSymbol(this->_id);

	// Return the type of the Constant
	return var->getType();
}


double lp::ConstantNode::evaluateNumber() 
{ 
	double result = 0.0;

	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as NumericConstant
		lp::NumericConstant *constant = (lp::NumericConstant *) table.getSymbol(this->_id);

		// Copy the value of the NumericConstant
		result = constant->getValue();
	}
	else
	{
		warning("Error de ejecución en evaluateNumber(): la constante no es numérica", this->_id);
	}

	// Return the value of the NumericVariable
	return result;
}

bool lp::ConstantNode::evaluateBool() 
{ 
	bool result = false;

	if (this->getType() == BOOL)
	{
		// Get the identifier in the table of symbols as LogicalConstant
		lp::LogicalConstant *constant = (lp::LogicalConstant *) table.getSymbol(this->_id);

		// Copy the value of the LogicalConstant
		result = constant->getValue();
	}
	else
	{
		warning("Error de ejecución en evaluateBool(): la constante no es booleana", this->_id);
	}

	// Return the value of the LogicalVariable
	return result;
}

std::string lp::ConstantNode::evaluateString(){
	std::string result = "";

	if (this->getType() == STRING)
	{
		// Get the identifier in the table of symbols as LogicalVariable
		lp::StringVariable *var = (lp::StringVariable *) table.getSymbol(this->_id);

		// Copy the value of the LogicalVariable
		result = var->getValue();
	}
	else
	{
		warning("Error de ejecución en evaluateString(): la variable no es una cadena", this->_id);
	}

	// Return the value of the LogicalVariable
	return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
 

int lp::NumberNode::getType()
{
	return NUMBER;
}


void lp::NumberNode::print()
{
  std::cout << "NumeroNode: " << this->_number << std::endl;
}

double lp::NumberNode::evaluateNumber() 
{ 
    return this->_number; 
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::StringNode::getType()
{
	return STRING;
}


void lp::StringNode::print()
{
  std::cout << "CadenaNode: " << this->_chain << std::endl;
}

std::string lp::StringNode::evaluateString() 
{ 
    return this->_chain; 
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
int lp::NumericUnaryOperatorNode::getType()
{
	int result;

	if(this->_exp->getType() == NUMBER)
	{
		result = NUMBER;
	}
	else
	{
		warning("Error de ejecución: Tipos incompatibles para ", "Numeric Unary Operator");
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::LogicalUnaryOperatorNode::getType()
{
	int result;

	if(this->_exp->getType() == BOOL)
	{
		result = BOOL;
	}
	else
	{
		warning("Error de ejecución: Tipos incompatibles para ", "Logical Unary Operator");
	}
	
	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::NumericOperatorNode::getType()
{
	int result = 0;
		
	if ( (this->_left->getType() == NUMBER) and (this->_right->getType() == NUMBER))
		result = NUMBER;
	else
		warning("Error de ejecución: Tipos incompatibles para ", "Numeric Operator");

	return	result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::StringOperatorNode::getType()
{
	int result = 0;
		
	if ( (this->_left->getType() == STRING) and (this->_right->getType() == STRING))
		result = STRING;
	else
		warning("Error de ejecución: Tipos incompatibles para ", "String Operator");

	return	result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


int lp::RelationalOperatorNode::getType()
{
	int result = 0;
		
	if (( (this->_left->getType() == NUMBER) and (this->_right->getType() == NUMBER)) or( (this->_left->getType() == STRING) and (this->_right->getType() == STRING)))
		result = BOOL;
	else
		warning("Error de ejecución: Tipos incompatibles para ", "Relational Operator");

	return	result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::LogicalOperatorNode:: getType()
{
	int result = 0;
		
	if ( (this->_left->getType() == BOOL) and (this->_right->getType() == BOOL))
	{
		// 
		result = BOOL;
	}
	else
		warning("Error de ejecución: Tipos incompatibles para ", "Logical Operator");

	return	result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::UnaryMinusNode::print() 
{
  std::cout << "DisminuciónUnariaNode: "  << std::endl;
  std::cout << "-";
  this->_exp->print();
}

double lp::UnaryMinusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the type of the expression
	if (this->getType() == NUMBER)
	{
		// Minus
		result = - this->_exp->evaluateNumber();
	}
	else
	{
		warning("Error de ejecución: Las expresiones no son numéricas para ", "UnaryMinus");
	}

  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::UnaryPlusNode::print() 
{
  std::cout << "AumentoUnarioNode: "  << std::endl;
  this->_exp->print();
}

double lp::UnaryPlusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the type of the expression
	if (this->getType() == NUMBER)
	{
		result = this->_exp->evaluateNumber();
	}
	else
	{
		warning("Error de ejecución: Las expresiones no son numéricas para ","UnaryPlus");
	}

  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PlusNode::print() 
{
  std::cout << "MásNode: "  << std::endl;
  this->_left->print();
  std::cout << " + ";
  this->_right->print();
}

double lp::PlusNode::evaluateNumber()
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = this->_left->evaluateNumber() + this->_right->evaluateNumber();
	}
	else
	{
		warning("Error de ejecución: Las expresiones no son numéricas para ", "Plus");
	}

  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::MinusNode::print() 
{
  std::cout << "MenosNode: "  << std::endl;
  this->_left->print();
  std::cout << " - ";
  this->_right->print();
}

double lp::MinusNode::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = this->_left->evaluateNumber() - this->_right->evaluateNumber();
	}
	else
	{
		warning("Error de ejecución: Las expresiones no son numéricas para ", "Minus");
	}

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::MultiplicationNode::print() 
{
	std::cout << "MultiplicaciónNode: "  << std::endl;
	this->_left->print();
	std::cout << " * ";
	this->_right->print();
}

double lp::MultiplicationNode::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = this->_left->evaluateNumber() * this->_right->evaluateNumber();
	}
	else
	{
		warning("Error de ejecución: Las expresiones no son numéricas para ","Multiplication");
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::DivisionNode::print()
{
  std::cout << "DivisionNode: " << std::endl;
  this->_left->print();
  std::cout << " / ";
  this->_right->print();
}

double lp::DivisionNode::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		double l_value, r_value;

		l_value = this->_left->evaluateNumber();
		r_value = this->_right->evaluateNumber();
	
		// The divisor is not zero
    	if(std::abs(r_value) > ERROR_BOUND)
		{
				result = l_value / r_value;
		}
		else
		{
			warning("Error de ejecución", "División entre cero");
		}
	}
	else
	{
		warning("Error de ejecución: Las expresiones no son numéricas para ", "Division");
	}

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::DivisionEnteraNode::print()
{
  std::cout << "DivisionEnteraNode: " << std::endl;
  this->_left->print();
  std::cout << " _div ";
  this->_right->print();
}

double lp::DivisionEnteraNode::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		double l_value, r_value;

		l_value = this->_left->evaluateNumber();
		r_value = this->_right->evaluateNumber();
	
		// The divisor is not zero
    	if(std::abs(r_value) > ERROR_BOUND)
		{
				result = l_value / r_value;
		}
		else
		{
			warning("Error de ejecución", "División entre cero");
		}
	}
	else
	{
		warning("Error de ejecución: Las expresiones no son numéricas para ", "Division");
	}
  result= (int) result;
  return  result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ModuloNode::print()
{
  std::cout << "ModuloNode: " << std::endl;
  this->_left->print();
  std::cout << " / ";
  this->_right->print();
}

double lp::ModuloNode::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		double l_value, r_value;

		l_value = this->_left->evaluateNumber();
		r_value = this->_right->evaluateNumber();
	
    	if(std::abs(r_value) > ERROR_BOUND)
				result = (int) l_value % (int) r_value;
		else
			warning("Error de ejecución", "División entre cero");
	}
	else
	{
		warning("Error de ejecución: Las expresiones no son numéricas para ", "Modulo");
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PowerNode::print() 
{
	std::cout << "ElevarNode: "  << std::endl;
	this->_left->print();
	std::cout << " ^ ";
	this->_right->print();
}

double lp::PowerNode::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		result = pow(this->_left->evaluateNumber(), this->_right->evaluateNumber());
	}
	else
	{
		warning("Error de ejecución: Las expresiones no son numéricas para ", "Power");
	}

  return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
int lp::BuiltinFunctionNode_0::getType()
{
	return	NUMBER;
}


void lp::BuiltinFunctionNode_0::print() 
{
	std::cout << "BuiltinFunctionNode_0: "  << std::endl;
	std::cout << this->_id;
	std::cout << " ( ) " ;
}

double lp::BuiltinFunctionNode_0::evaluateNumber() 
{
	// Get the identifier in the table of symbols as BuiltinParameter0
	lp::BuiltinParameter0 *f = (lp::BuiltinParameter0 *) table.getSymbol(this->_id);

	// Apply the function and copy the result
   	return f->getFunction()();
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::BuiltinFunctionNode_1::getType()
{
	int result = 0;
		
	if (this->_exp->getType() == NUMBER)
		result = NUMBER;
	else
		warning("Error de ejecución: tipos incompatibles para ", "BuiltinFunctionNode_1");

	return	result;
}

void lp::BuiltinFunctionNode_1::print() 
{
	std::cout << "BuiltinFunctionNode_1: "  << std::endl;
	std::cout << this->_id;
	std::cout << " ( " ;  
	this->_exp->print();
	std::cout << " ) " ;
}

double lp::BuiltinFunctionNode_1::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the type of the expression
	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as BuiltinParameter1
		lp::BuiltinParameter1 *f = (lp::BuiltinParameter1 *) table.getSymbol( this->_id);

		// Apply the function to the parameter and copy the result
		result = f->getFunction()(this->_exp->evaluateNumber());
	}
	else
	{
		warning("Error de ejecución: tipos incompatibles para ", this->_id);
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

int lp::BuiltinFunctionNode_2::getType()
{
	int result = 0;
		
	if (this->_exp1->getType() == this->_exp2->getType())
		result = this->_exp1->getType();
	else
		warning("Error de ejecución: tipos incompatibles para ", "BuiltinFunctionNode_2");

	return	result;
}


void lp::BuiltinFunctionNode_2::print() 
{
	std::cout << "BuiltinFunctionNode_2: "  << std::endl;
	std::cout << this->_id;
	std::cout << " ( " ;  
	this->_exp1->print();
	std::cout << " , " ;
	this->_exp2->print();
	std::cout << " ) " ;
}

double lp::BuiltinFunctionNode_2::evaluateNumber() 
{
	double result = 0.0;

	// Ckeck the types of the expressions
	if (this->getType() == NUMBER)
	{
		// Get the identifier in the table of symbols as BuiltinParameter2
		lp::BuiltinParameter2 *f = (lp::BuiltinParameter2 *) table.getSymbol(this->_id);

		// Apply the function to the parameters and copy the result
	  	result = f->getFunction()(this->_exp1->evaluateNumber(),this->_exp2->evaluateNumber());
	}
	else
	{
		warning("Error de ejecución: tipos incompatibles para ", this->_id);
	}

  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::GreaterThanNode::print()
{
  std::cout << "MayorQueNode: " << std::endl;
  this->_left->print();
  std::cout << " > ";
  this->_right->print();
}

bool lp::GreaterThanNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL && this->_left->getType() == NUMBER && this->_right->getType()== NUMBER )
	{
		double l_value, r_value;
		l_value = this->_left->evaluateNumber();
		r_value = this->_right->evaluateNumber();

		result = (l_value > r_value);
	}
	else if(this->getType() == BOOL and this->_left->getType() == STRING && this->_right->getType()== STRING )
	{
		std::string l_value, r_value;
		l_value = this->_left->evaluateString();
		r_value = this->_right->evaluateString();

		result = (l_value > r_value);	
	}
	else{
		warning("Error de ejecución: tipos incompatibles para ", "operador Mayor que");
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::GreaterOrEqualNode::print()
{
  std::cout << "MayorOIgualNode: " << std::endl;
  this->_left->print();
  std::cout << " >= ";
  this->_right->print();
}

bool lp::GreaterOrEqualNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL && this->_left->getType()==NUMBER && this->_right->getType()==NUMBER )
	{
		double l_value, r_value;
		l_value = this->_left->evaluateNumber();
		r_value = this->_right->evaluateNumber();

		result = (l_value >= r_value);
	}
	else if(this->getType() == BOOL && this->_left->getType()==STRING && this->_right->getType()==STRING )
	{
		std::string l_value, r_value;
		l_value = this->_left->evaluateString();
		r_value = this->_right->evaluateString();

		result = (l_value >= r_value);	
	}
	else{
		warning("Error de ejecución: tipos incompatibles para ", "Operador Mayor o igual que");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::LessThanNode::print()
{
  std::cout << "MenorQueNode: " << std::endl;
  this->_left->print();
  std::cout << " < ";
  this->_right->print();
}

bool lp::LessThanNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL && this->_left->getType()==NUMBER && this->_right->getType()==NUMBER )
	{
		double l_value, r_value;
		l_value = this->_left->evaluateNumber();
		r_value = this->_right->evaluateNumber();

		result = (l_value < r_value);
	}
	else if(this->getType() == BOOL && this->_left->getType()==STRING && this->_right->getType()==STRING )
	{
		std::string l_value, r_value;
		l_value = this->_left->evaluateString();
		r_value = this->_right->evaluateString();

		result = (l_value < r_value);	
	}
	else{
		warning("Error de ejecución: tipos incompatibles para ", "operador Menor que");
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::LessOrEqualNode::print()
{
  std::cout << "MenorOIgualNode: " << std::endl;
  this->_left->print();
  std::cout << " <= ";
  this->_right->print();
}

bool lp::LessOrEqualNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL && this->_left->getType()==NUMBER && this->_right->getType()==NUMBER )
	{
		double l_value, r_value;
		l_value = this->_left->evaluateNumber();
		r_value = this->_right->evaluateNumber();

		result = (l_value <= r_value);
	}
	else if(this->getType() == BOOL && this->_left->getType()==STRING && this->_right->getType()==STRING )
	{
		std::string l_value, r_value;
		l_value = this->_left->evaluateString();
		r_value = this->_right->evaluateString();

		result = (l_value <= r_value);	
	}
	else{
		warning("Error de ejecución: tipos incompatibles para ", "operador Menor o igual que");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::EqualNode::print()
{
  std::cout << "IgualNode: " << std::endl;
  this->_left->print();
  std::cout << " = ";
  this->_right->print();
}

bool lp::EqualNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL && this->_left->getType()==NUMBER && this->_right->getType()==NUMBER )
	{
		double l_value, r_value;
		l_value = this->_left->evaluateNumber();
		r_value = this->_right->evaluateNumber();

		// ERROR_BOUND to control the precision of real numbers
		result = std::abs( (l_value - r_value)) < ERROR_BOUND ;
	}
	else if(this->getType() == BOOL && this->_left->getType()==STRING && this->_right->getType()==STRING )
	{
		std::string l_string = this->_left->evaluateString();
		std::string r_string = this->_right->evaluateString();

		result = (l_string == r_string);	
	}
	else
	{
		warning("Error de ejecución: tipos incompatibles para ", "operador Igual");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::NotEqualNode::print()
{
  std::cout << "NoIgualNode: " << std::endl;
  this->_left->print();
  std::cout << " != ";
  this->_right->print();
}

bool lp::NotEqualNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL && this->_left->getType()==NUMBER && this->_right->getType()==NUMBER )
	{
		double l_value, r_value;
		l_value = this->_left->evaluateNumber();
		r_value = this->_right->evaluateNumber();

		// ERROR_BOUND to control the precision of real numbers
		result = std::abs( (l_value - r_value) ) >= ERROR_BOUND ;
	}
	else if(this->getType() == BOOL && this->_left->getType()==STRING && this->_right->getType()==STRING )
	{
		std::string l_value, r_value;
		l_value = this->_left->evaluateString();
		r_value = this->_right->evaluateString();

		result = (l_value != r_value);	
	}
	else
	{
		warning("Error de ejecución: tipos incompatibles para ", "operador No igual (distinto)");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AndNode::print()
{
  std::cout << "AndNode: " << std::endl;
  this->_left->print();
  std::cout << " and ";
  this->_right->print();
}

bool lp::AndNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		bool l_value, r_value;

		l_value = this->_left->evaluateBool();
		r_value = this->_right->evaluateBool();

		result = l_value && r_value;
	}
	else
	{
		warning("Error de ejecución: tipos incompatibles para ", "operador And");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::OrNode::print()
{
  std::cout << "OrNode: " << std::endl;
  this->_left->print();
  std::cout << " || ";
  this->_right->print();
}

bool lp::OrNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		bool l_value, r_value;

		l_value = this->_left->evaluateBool();
		r_value = this->_right->evaluateBool();

		result = l_value or r_value;
	}
	else
	{
		warning("Error de ejecución: tipos incompatibles para ", "operador Or");
	}

	return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::NotNode::print()
{
  std::cout << "NotNode: " << std::endl;
  std::cout << " ! ";
  this->_exp->print();
}

bool lp::NotNode::evaluateBool() 
{
	bool result = false;

	if (this->getType() == BOOL)
	{
		result = not this->_exp->evaluateBool();
	}
	else
	{
		warning("Error de ejecución: tipos incompatibles para ", "operador Not");
	}

	return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ConcatenacionNode::print() 
{
  std::cout << "ConcatenacionNode: "  << std::endl;
  this->_left->print();
  std::cout << " - ";
  this->_right->print();
}

std::string lp::ConcatenacionNode::evaluateString() 
{
	std::string result = "";

	// Ckeck the types of the expressions
	if (this->getType() == STRING)
	{
		result = this->_left->evaluateString() + this->_right->evaluateString();
	}
	else
	{
		warning("Error de ejecución: Tipos incompatibles para", "ConcatenacionNode");
	}

  return result;
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AssignmentStmt::print() 
{
  std::cout << "AsignaciónNode: "  << std::endl;
  std::cout << this->_id << " = ";
  this->_exp->print();
  std::cout << std::endl;
}

void lp::AssignmentStmt::evaluate() 
{
	lp::Variable *firstVar = (lp::Variable *) table.getSymbol(this->_id);

	// Check the expression
	if (this->_exp != NULL)
	{
		// Check the type of the expression of the asgn
		switch(this->_exp->getType())
		{
			case NUMBER:
			{
				double value;
				// evaluate the expression as NUMBER
			 	value = this->_exp->evaluateNumber();

				// Check the type of the first varible
				if (firstVar->getType() == NUMBER)
				{
				  	// Get the identifier in the table of symbols as NumericVariable
					lp::NumericVariable *v = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value to the identifier in the table of symbols
					v->setValue(value);
				}
				// The type of variable is not NUMBER
				else
				{
					// Delete the variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the variable in the table of symbols as NumericVariable 
					// with the type NUMBER and the value 
					lp::NumericVariable *v = new lp::NumericVariable(this->_id,
											VARIABLE,NUMBER,value);
					table.installSymbol(v);
				}
			}
			break;

			case BOOL:
			{
				bool value;
				// evaluate the expression as BOOL
			 	value = this->_exp->evaluateBool();

				if (firstVar->getType() == BOOL)
				{
				  	// Get the identifier in the table of symbols as LogicalVariable
					lp::LogicalVariable *v = (lp::LogicalVariable *) table.getSymbol(this->_id);

					// Assignment the value to the identifier in the table of symbols
					v->setValue(value);
				}
				// The type of variable is not BOOL
				else
				{
					// Delete the variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the variable in the table of symbols as NumericVariable 
					// with the type BOOL and the value 
					lp::LogicalVariable *v = new lp::LogicalVariable(this->_id,
											VARIABLE,BOOL,value);
					table.installSymbol(v);
				}
			}
			break;

			case STRING:
			{
				std::string value;
				// evaluate the expression as NUMBER
			 	value = this->_exp->evaluateString();

				// Check the type of the first varible
				if (firstVar->getType() == STRING)
				{
				  	// Get the identifier in the table of symbols as NumericVariable
					lp::StringVariable *v = (lp::StringVariable *) table.getSymbol(this->_id);

					// Assignment the value to the identifier in the table of symbols
					v->setValue(value);
				}
				// The type of variable is not NUMBER
				else
				{
					// Delete the variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the variable in the table of symbols as NumericVariable 
					// with the type NUMBER and the value 
					lp::StringVariable *v = new lp::StringVariable(this->_id,
											VARIABLE,STRING,value);
					table.installSymbol(v);
				}
			}
			break;
			default:
				warning("Error de ejecución: tipos incompatibles para ", "Asignación");
		}

	}

	//////////////////////////////////////////////
	// Allow multiple assigment -> a = b = c = 2;

	else // this->_asgn is not NULL
	{
		// IMPORTANT
		//  evaluate the assigment child
		this->_asgn->evaluate();


		/* Get the identifier of the previous asgn in the table of symbols as Variable */
		lp::Variable *secondVar = (lp::Variable *) table.getSymbol(this->_asgn->_id);

		// Get the type of the variable of the previous asgn
		switch(secondVar->getType())
		{
			case NUMBER:
			{
				/* Get the identifier of the previous asgn in the table of symbols as NumericVariable */
				lp::NumericVariable *secondVar = (lp::NumericVariable *) table.getSymbol(this->_asgn->_id);
				// Check the type of the first variable
				if (firstVar->getType() == NUMBER)
				{
				/* Get the identifier of the first variable in the table of symbols as NumericVariable */
				lp::NumericVariable *firstVar = (lp::NumericVariable *) table.getSymbol(this->_id);
				  	// Get the identifier o f the in the table of symbols as NumericVariable
//					lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(secondVar->getValue());

				}
				// The type of variable is not NUMBER
				else
				{
					// Delete the first variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the first variable in the table of symbols as NumericVariable 
					// with the type NUMBER and the value of the previous variable 
					lp::NumericVariable *firstVar = new lp::NumericVariable(this->_id,
											VARIABLE,NUMBER,secondVar->getValue());
					table.installSymbol(firstVar);
				}
			}
			break;

			case BOOL:
			{
				/* Get the identifier of the previous asgn in the table of symbols as LogicalVariable */
				lp::LogicalVariable *secondVar = (lp::LogicalVariable *) table.getSymbol(this->_asgn->_id);
				// Check the type of the first variable
				if (firstVar->getType() == BOOL)
				{
				/* Get the identifier of the first variable in the table of symbols as LogicalVariable */
				lp::LogicalVariable *firstVar = (lp::LogicalVariable *) table.getSymbol(this->_id);
				  	// Get the identifier o f the in the table of symbols as NumericVariable
//					lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(secondVar->getValue());

				}
				// The type of variable is not NUMBER
				else
				{
					// Delete the first variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the first variable in the table of symbols as NumericVariable 
					// with the type BOOL and the value of the previous variable 
					lp::LogicalVariable *firstVar = new lp::LogicalVariable(this->_id,
											VARIABLE,BOOL,secondVar->getValue());
					table.installSymbol(firstVar);
				}
			}
			break;

			case STRING:
			{
				/* Get the identifier of the previous asgn in the table of symbols as LogicalVariable */
				lp::StringVariable *secondVar = (lp::StringVariable *) table.getSymbol(this->_asgn->_id);
				// Check the type of the first variable
				if (firstVar->getType() == STRING)
				{
				/* Get the identifier of the first variable in the table of symbols as LogicalVariable */
				lp::StringVariable *firstVar = (lp::StringVariable *) table.getSymbol(this->_id);
				  	// Get the identifier o f the in the table of symbols as NumericVariable
//					lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);

					// Assignment the value of the second variable to the first variable
					firstVar->setValue(secondVar->getValue());

				}
				// The type of variable is not STRING
				else
				{
					// Delete the first variable from the table of symbols 
					table.eraseSymbol(this->_id);

					// Insert the first variable in the table of symbols as NumericVariable 
					// with the type STRING and the value of the previous variable 
					lp::StringVariable *firstVar = new lp::StringVariable(this->_id,
											VARIABLE,STRING,secondVar->getValue());
					table.installSymbol(firstVar);
				}
			}
			break;
			default:
				warning("Error de ejecución: tipos incompatibles para ", "Asignación");
		}
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PrintStmt::print() 
{
  	std::cout << "EscribirStmt: "  << std::endl;
  	std::cout << " escribir ";
  	this->_exp->print();
  	std::cout << std::endl;
}


void lp::PrintStmt::evaluate() 
{
	/*std::cout << BIYELLOW; 
	std::cout << "Escribir : ";
	std::cout << RESET; */

	switch(this->_exp->getType())
	{
		case NUMBER:
				std::cout << this->_exp->evaluateNumber() ;
				break;
		case BOOL:
			if (this->_exp->evaluateBool())
				std::cout << "verdadero" ;
			else
				std::cout << "falso" ;
		
			break;

		default:
			warning("Error de ejecución: tipos incompatibles para ", "escribir");
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::PrintChainStmt::print() 
{
  	std::cout << "EscribirStmt: "  << std::endl;
  	std::cout << " escribir ";
  	this->_exp->print();
  	std::cout << std::endl;
}


void lp::PrintChainStmt::evaluate() 
{
	/*std::cout << BIYELLOW; 
	std::cout << "Escribir : ";
	std::cout << RESET; */

	switch(this->_exp->getType())
	{
		case STRING:
				std::cout << this->_exp->evaluateString();
				break;
		default:
			warning("Error de ejecución: tipos incompatibles para ", "escribir_cadena");
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::BorrarPantallaStmt::print() 
{
  	std::cout << "BorrarPantallaStmt";
}



void lp::BorrarPantallaStmt::evaluate() 
{
  	std::cout << CLEAR_SCREEN;
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::EntradaStmt::print() 
{

  	std::cout<<"EntradaStmt";
}
void lp::EntradaStmt::evaluate() 
{
  	std::cin.ignore();
  	std::cin.ignore();
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::LugarStmt::print() 
{
	std::cout <<"LugarStmt( "  << this->_fila->evaluateNumber()<< ", "<<this->_columna->evaluateNumber()<<")"<<std::endl;
}

void lp::LugarStmt::evaluate() 
{

	// Ckeck the types of the expressions
	if (this->_fila->getType() == NUMBER && this->_columna->getType() == NUMBER)
	{
		PLACE((int)this->_fila->evaluateNumber(),(int)this->_columna->evaluateNumber());
	}
	else //If the type is not compatible
	{
		warning("Error de ejecución: las expresiones no son numéricas en", "#lugar");
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ReadStmt::print() 
{
  std::cout << "LeerStmt: "  << std::endl;
  std::cout << " leer (" << this->_id << ")";
  std::cout << std::endl;
}


void lp::ReadStmt::evaluate() 
{   
	double value;
	std::cin >> value;
	
	/* Get the identifier in the table of symbols as Variable */
	lp::Variable *var = (lp::Variable *) table.getSymbol(this->_id);

	// Check if the type of the variable is NUMBER
	if (var->getType() == NUMBER)
	{
		/* Get the identifier in the table of symbols as NumericVariable */
		lp::NumericVariable *n = (lp::NumericVariable *) table.getSymbol(this->_id);
						
		/* Assignment the read value to the identifier */
		n->setValue(value);
	}
	// The type of variable is not NUMBER
	else
	{
		// Delete $1 from the table of symbols as Variable
		table.eraseSymbol(this->_id);

			// Insert $1 in the table of symbols as NumericVariable 
		// with the type NUMBER and the read value 
		lp::NumericVariable *n = new lp::NumericVariable(this->_id, 
									  VARIABLE,NUMBER,value);

		table.installSymbol(n);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::ReadChainStmt::print() 
{
  std::cout << "LeerCadenaStmt: "  << std::endl;
  std::cout << " leer_cadena (" << this->_id << ")";
  std::cout << std::endl;
}


void lp::ReadChainStmt::evaluate() 
{   
	std::string value;
	std::cin >> value;

	/* Get the identifier in the table of symbols as Variable */
	lp::Variable *var = (lp::Variable *) table.getSymbol(this->_id);

	// Check if the type of the variable is STRING
	if (var->getType() == STRING)
	{
		/* Get the identifier in the table of symbols as StringVariable */
		lp::StringVariable *n = (lp::StringVariable *) table.getSymbol(this->_id);
						
		/* Assignment the read value to the identifier */
		n->setValue(value);
	}
	// The type of variable is not STRING
	else
	{
		// Delete $1 from the table of symbols as Variable
		table.eraseSymbol(this->_id);

			// Insert $1 in the table of symbols as NumericVariable 
		// with the type STRING and the read value 
		lp::StringVariable *n = new lp::StringVariable(this->_id, 
									  VARIABLE,STRING,value);

		table.installSymbol(n);
	}
 	std::cin.clear(); // reset failbit
  	  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////


void lp::EmptyStmt::print() 
{
  std::cout << "VacioStmt "  << std::endl;
}

void lp::EmptyStmt::evaluate() 
{
  // Empty
}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::IfStmt::print() 
{
  std::cout << "IfStmt: "  << std::endl;
  // Condition
  this->_cond->print();

  // Consequent
  this->_stmt1->print();

 // The alternative is printed if exists
  if (this->_stmt2 != NULL)
	  this->_stmt2->print();

  std::cout << std::endl;
}


void lp::IfStmt::evaluate() 
{
   // If the condition is true,
	if (this->_cond->evaluateBool() == true )
     // the consequent is run 
	  this->_stmt1->evaluate();

    // Otherwise, the alternative is run if exists
	else if (this->_stmt2 != NULL)
		  this->_stmt2->evaluate();
}




///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::WhileStmt::print() 
{
  std::cout << "WhileStmt: "  << std::endl;
  // Condition
  this->_cond->print();

  // Body of the while loop
  this->_stmt->print();

  std::cout << std::endl;
}


void lp::WhileStmt::evaluate() 
{
  // While the condition is true. the body is run 
  while (this->_cond->evaluateBool() == true)
  {	
	  this->_stmt->evaluate();
  }

}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
void lp::ForStmt::evaluatePaso(){
   	lp::VariableNode *v = new lp::VariableNode(this->_varId);

	if(_step->getType()==NUMBER)
	{
		PlusNode* sum=new lp::PlusNode(v,_step);
	   	lp::AssignmentStmt* asgm= new lp::AssignmentStmt(_varId,sum);
    	asgm->evaluate();
	  }
	 else{ warning("Error de ejecución: Tipos incompatibles en :", "para");}
		
}

bool lp::ForStmt::infinite(){
   	lp::VariableNode *v = new lp::VariableNode(this->_varId);	
	if(v->evaluateNumber()< this->_to->evaluateNumber() && this->_step->evaluateNumber()<0) 
	{
		return true;
	}
	if(v->evaluateNumber()>this->_to->evaluateNumber() && this->_step->evaluateNumber()>0) 
	{
		return true;
	}
	return false;
}

void lp::ForStmt::print() 
{
  	std::cout<< "ForStmt: "<< std::endl;
	std::cout<<std::endl;
}


void lp::ForStmt::evaluate() 
{
    if(this->_from->getType()==NUMBER)
	{
   	 	lp::AssignmentStmt* asgm= new lp::AssignmentStmt(_varId,_from);
    	asgm->evaluate();
    }
    else
	{
		warning("Error de ejecución: Los bucles para solo evaluan variables numericas en:", "para"); 
		return;
    }

   lp::VariableNode *var = new lp::VariableNode(this->_varId);

   if(this->_to->getType()==NUMBER && this->_step->getType()==NUMBER)
   {
	   
		if(!infinite())
		{
  	 		for(;var->evaluateNumber()!=this->_to->evaluateNumber();evaluatePaso())
	  	  		this->_stmt->evaluate();
 	    	this->_stmt->evaluate();
		}
		else 
		{
     		warning("Error de ejecución :Bucle infinito en:", "para");
     		return;
		}
	}
    
   else
   {		
     	warning("Error de ejecución: Las expresiones comparadas son de distinto tipo en:", "para");
     	return;
    }


  
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
void lp::CasesStmt::print()
{
	std::cout<<"CasesStmt"<<std::endl;
	std::list<CaseNode*>::iterator iterador;
	iterador = this->_cases->begin();
	for(;iterador != this->_cases->end();iterador++)
		(*iterador)->print();
}
void lp::CasesStmt::evaluate()
{
	std::list<CaseNode*>::iterator iterador;
	bool done = false;
	int type = this->_exp->getType();
	iterador = this->_cases->begin();
	for(;iterador != this->_cases->end() && !done ;iterador++)
	{
		if((*iterador)->getType() == type)
		{
			if(type == NUMBER)
			{

				if((*iterador)->getExpression()->evaluateNumber() == this->_exp->evaluateNumber())
				{
					(*iterador)->evaluate();
					done = true;
				}
			}
			else if(type == STRING)
			{
				if((*iterador)->getExpression()->evaluateString() == this->_exp->evaluateString())
				{
					(*iterador)->evaluate();
					done = true;
				}				
			}
			else if(type == BOOL)
			{
				if((*iterador)->getExpression()->evaluateBool() == this->_exp->evaluateBool())
				{
					(*iterador)->evaluate();
					done = true;
				}				
			}
			else
				warning("Error de ejecución: tipos incompatibles para ", "valor");
		}
		else
			warning("Error de ejecución : tipos incompatibles para", "valor");
	}
	if(this->_cdefault != NULL && !done)
		this->_cdefault->evaluate();

}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::CaseNode::print()
{
  std::cout << "CaseNode: "  << std::endl;
  this->_stmts->print();
}

lp::ExpNode* lp::CaseNode::getExpression()
{
	return this->_exp;
}
int lp::CaseNode::getType()
{
	return this->_exp->getType();
}
void lp::CaseNode::evaluate()
{
	this->_stmts->evaluate();
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::BlockStmt::print() 
{
  std::list<Statement *>::iterator stmtIter;

  std::cout << "BlockStmt: "  << std::endl;

  for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++) 
  {
     (*stmtIter)->print();
  }
}


void lp::BlockStmt::evaluate() 
{
  std::list<Statement *>::iterator stmtIter;

  for (stmtIter = this->_stmts->begin(); stmtIter != this->_stmts->end(); stmtIter++) 
  {
    (*stmtIter)->evaluate();
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::DoWhileStmt::print() 
{
  std::cout << "DoWhileStmt: "  << std::endl;

  // Body of the while loop
  this->_stmt->print();

  // Condition
  this->_cond->print();
  std::cout << std::endl;
}


void lp::DoWhileStmt::evaluate() 
{
  // the body is run while the condition is true
  do 
  {	
	  this->_stmt->evaluate();
  }while(this->_cond->evaluateBool() == false);

}


///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////






///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

void lp::AST::print() 
{
  std::list<Statement *>::iterator stmtIter;

  for (stmtIter = stmts->begin(); stmtIter != stmts->end(); stmtIter++) 
  {
     (*stmtIter)->print();
  }
}



void lp::AST::evaluate() 
{
  std::list<Statement *>::iterator stmtIter;

  for (stmtIter = stmts->begin(); stmtIter != stmts->end(); stmtIter++) 
  {
    (*stmtIter)->evaluate();
  }
}


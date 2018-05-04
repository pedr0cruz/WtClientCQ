//  MediatorGoF.cpp
//  Patron de Dise�o Mediator

#include "stdafx.h"

#include "MediatorGoF.h"

/////// Clase Mediador: act�a como mediador entre varios clientes para minimizar
/////// la cantidad de interacciones entre objetos. Dichos clientes, en vez de
/////// comunicarse directamente entre s�, se comunican solamente con el mediador.

/// Constructor
MediatorGoF::MediatorGoF()
{
}

/// Destructor
MediatorGoF::~MediatorGoF()
{
}

/// Registra un objeto cliente
void MediatorGoF::registerClient(ColleagueGoF* colleague_ptr)
{
    colleagues_vec_.push_back(colleague_ptr);
}

/// Constructor que recibe puntero a mediador
ColleagueGoF::ColleagueGoF(MediatorGoF* mediator) : mediator_(mediator)
{
}

/// Destructor
ColleagueGoF::~ColleagueGoF()
{
}


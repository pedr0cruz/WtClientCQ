//  MediatorGoF.h
//  Patron de Diseño Mediator

#ifndef MEDIATOR_H
#define MEDIATOR_H

#pragma once

#include <vector>
#include <memory>

class ColleagueGoF;

/// Clase Mediador: Hace de intermedio entre múltiples clientes que necesitan comunicarse entre ellos.
class MediatorGoF
{
public:
    /// Constructor
    MediatorGoF();

    /// Virtual destructor
	virtual ~MediatorGoF();

    /// Registra un objeto cliente
    void registerClient(ColleagueGoF* colleague_ptr);

protected:
    std::vector <ColleagueGoF*> colleagues_vec_;
};

class ColleagueGoF
{
public:
    /// Constructor que recibe puntero a mediador
    ColleagueGoF(MediatorGoF*);

    /// virtual Destructor
    virtual ~ColleagueGoF();
    
protected:
    MediatorGoF* mediator_;
};

#endif

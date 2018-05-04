//  ChainOfResponsibilityGoF.h
//  Patron de Dise�o Cadena de Responsabilidad

#ifndef CHAINOFRESPONSIBILITYGOF_H
#define CHAINOFRESPONSIBILITYGOF_H

#pragma once

/// Clase RequestGoF: Define la interfaz para encapsular una responsabilidad. 
/// Est� dise�ada para ser utilizada junto con HandlerGoF.
///
class RequestGoF
{
public:
    /// Constructor
    RequestGoF();
    /// Destructor
    virtual ~RequestGoF();
    /// Obtiene el tipo de solicitud asociada
    int GetKind()
    {
        return -1;
    }
protected:
};

/// Clase HandlerGoF: Define la interfaz para asumir una
/// responsabilidad 
///
class HandlerGoF
{
public:
    /// Constructor
    HandlerGoF(HandlerGoF* next);
    /// Funci�n virtual que ser� llamada desde las instancias de la clase HandlerGoF
    virtual bool handleRequest(RequestGoF* request  = nullptr)
    {
        if (! next_) {
            return false;
        }
        return next_->handleRequest(request);
    }
protected:
    HandlerGoF* next_;
};

#endif // #ifndef CHAINOFRESPONSIBILITYGOF_H

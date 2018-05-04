//  DecoratorGoF.h
//  Patron de Dise�o Decorator

#ifndef DECORATOR_H
#define DECORATOR_H

#pragma once

/// Clase Componente: Define la funcionalidad m�nima necesaria para usar la clase Decorador
///
class ComponentGoF
{
public:
    /// Funci�n virtual que ser� llamada desde las instancias de la clase Decorator
    virtual void operation() = 0;
};

/// Clase Decorador: Permite agregar responsabilidades a instances de clases de forma din�mica
///
class DecoratorGoF : public ComponentGoF
{
public:
    /// Constructor que recibe puntero a componente al que se le aplica el patr�n Decorator
    DecoratorGoF(ComponentGoF* component);

    /// Funci�n virtual que ser� reemplazada en las clases concretas derivadas de �sta.
    virtual void operation();

private:
	ComponentGoF* component_;
};

#endif // #ifndef DECORATOR_H

/*************************************************************************************
 *  Copyright (C) 2010 by Percy Camilo T. Aucahuasi <percy.camilo.ta@gmail.com>      *
 *                                                                                   *
 *  This program is free software; you can redistribute it and/or                    *
 *  modify it under the terms of the GNU General Public License                      *
 *  as published by the Free Software Foundation; either version 2                   *
 *  of the License, or (at your option) any later version.                           *
 *                                                                                   *
 *  This program is distributed in the hope that it will be useful,                  *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                    *
 *  GNU General Public License for more details.                                     *
 *                                                                                   *
 *  You should have received a copy of the GNU General Public License                *
 *  along with this program; if not, write to the Free Software                      *
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA   *
 *************************************************************************************/


#include "../solver.h"
#include "../solverfactory.h"

#include "analitza/value.h"
#include <analitza/vector.h>

namespace Keomath
{

class KEOMATH_EXPORT CylindricalSurface : public Solver3D
{
public:
    explicit CylindricalSurface(const Analitza::Expression &expression, Analitza::Variables *variables);
    CylindricalSurface(const CylindricalSurface &cylindricalSurface);
    virtual ~CylindricalSurface();

    static QStringList supportedBVars()
    {
        return QStringList() << "r" << "t";
    }
    static Analitza::ExpressionType expectedType()
    {

        return Analitza::ExpressionType(Analitza::ExpressionType::Lambda).addParameter(
                   Analitza::ExpressionType(Analitza::ExpressionType::Value)).addParameter(
                   Analitza::ExpressionType(Analitza::ExpressionType::Value)).addParameter(
                   Analitza::ExpressionType(Analitza::ExpressionType::Value));

    }
    static QStringList examples()
    {
        QStringList ret;


        return ret;
    }

    const Analitza::Expression & lambda() const;

    QStringList arguments() const
    {
        return supportedBVars();
    }
    Function::Axe axeType() const
    {
        return Function::Cartesian;
    }
    void solve(const RealInterval::List &spaceBounds);
    Solver * copy()
    {
        return new CylindricalSurface(*this);
    }

    QVector3D evalSurface(qreal u, qreal v);

    void loadParametricEvaluator();

protected:
    Analitza::Cn* m_u; 
    Analitza::Cn* m_v; 

    Analitza::Expression m_originalCartesianLambda;
};

CylindricalSurface::CylindricalSurface(const Analitza::Expression &expression, Analitza::Variables *variables)
    : Solver3D(expression, variables)
    , m_u(new Analitza::Cn)
    , m_v(new Analitza::Cn)
{

    loadParametricEvaluator();

    m_evaluator.setStack(m_runStack);

    if(m_evaluator.isCorrect())
    {






        m_evaluator.flushErrors();
    }
}

CylindricalSurface::CylindricalSurface(const CylindricalSurface &cylindricalSurface)
    : Solver3D(cylindricalSurface)
    , m_u(new Analitza::Cn)
    , m_v(new Analitza::Cn)
{
    loadParametricEvaluator();
}

CylindricalSurface::~CylindricalSurface()
{
    delete m_u;
    delete m_v;
}

const Analitza::Expression & CylindricalSurface::lambda() const
{
    return m_originalCartesianLambda;
}

void CylindricalSurface::solve(const RealInterval::List &spaceBounds)
{


}


QVector3D CylindricalSurface::evalSurface(qreal u, qreal v)
{
    m_u->setValue(u);
    m_v->setValue(v);

    Analitza::Expression res = m_evaluator.calculateLambda();

    Analitza::Object* vo = res.tree();
    Analitza::Vector* vec = dynamic_cast<Analitza::Vector*>(vo);



    if (vec)
    {
        Analitza::Cn* x = static_cast<Analitza::Cn*>(vec->at(0));
        Analitza::Cn* y = static_cast<Analitza::Cn*>(vec->at(1));
        Analitza::Cn* z = static_cast<Analitza::Cn*>(vec->at(2));






        return QVector3D(x->value()*u*cos(v), y->value()*u*sin(v), z->value()); 
    }

    return QVector3D();
}


void CylindricalSurface::loadParametricEvaluator()

{



    m_originalCartesianLambda = Analitza::Expression(m_evaluator.expression());

    Analitza::Expression oldExp = m_evaluator.expression();

    oldExp.renameArgument(0, "u"); 
    oldExp.renameArgument(1, "v"); 

    QString oldExpLit = oldExp.lambdaBody().toString();

    QString newExpLiteral = QString("(u,v)->vector{1,1," + oldExpLit + "}");

    m_evaluator.setExpression(Analitza::Expression(newExpLiteral, false));

    m_runStack.append(m_u);
    m_runStack.append(m_v);
    m_evaluator.setStack(m_runStack);

    
    
    

    
}

REGISTER_FUNCTION_3D(CylindricalSurface)


} 


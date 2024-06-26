/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2015 OpenFOAM Foundation
    Copyright (C) 2020 OpenCFD Ltd.
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "primitives/functions/Polynomial/polynomialFunction.H"
#include "db/runTimeSelection/construction/addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(polynomialFunction, 0);
}


// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

Foam::polynomialFunction Foam::polynomialFunction::cloneIntegral
(
    const polynomialFunction& poly,
    const scalar intConstant
)
{
    polynomialFunction newPoly(poly.size()+1);

    newPoly[0] = intConstant;
    forAll(poly, i)
    {
        newPoly[i+1] = poly[i]/(i + 1);
    }

    return newPoly;
}


Foam::polynomialFunction Foam::polynomialFunction::cloneIntegralMinus1
(
    const polynomialFunction& poly,
    const scalar intConstant
)
{
    polynomialFunction newPoly(poly.size()+1);

    if (poly[0] > VSMALL)
    {
        newPoly.logActive_ = true;
        newPoly.logCoeff_  = poly[0];
    }

    newPoly[0] = intConstant;
    for (label i=1; i < poly.size(); ++i)
    {
        newPoly[i] = poly[i]/i;
    }

    return newPoly;
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void Foam::polynomialFunction::checkSize() const
{
    if (this->empty())
    {
        FatalErrorInFunction
            << "polynomialFunction coefficients are invalid (empty)"
            << nl << exit(FatalError);
    }
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::polynomialFunction::polynomialFunction()
:
    scalarList(1, Zero),
    logActive_(false),
    logCoeff_(0)
{}


Foam::polynomialFunction::polynomialFunction(const label order)
:
    scalarList(order, Zero),
    logActive_(false),
    logCoeff_(0)
{
    checkSize();
}


Foam::polynomialFunction::polynomialFunction
(
    const std::initializer_list<scalar> coeffs
)
:
    scalarList(coeffs),
    logActive_(false),
    logCoeff_(0)
{
    checkSize();
}


Foam::polynomialFunction::polynomialFunction(const UList<scalar>& coeffs)
:
    scalarList(coeffs),
    logActive_(false),
    logCoeff_(0)
{
    checkSize();
}


Foam::polynomialFunction::polynomialFunction(Istream& is)
:
    scalarList(is),
    logActive_(false),
    logCoeff_(0)
{
    checkSize();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool Foam::polynomialFunction::logActive() const
{
    return logActive_;
}


Foam::scalar Foam::polynomialFunction::logCoeff() const
{
    return logCoeff_;
}


Foam::scalar Foam::polynomialFunction::value(const scalar x) const
{
    const scalarList& coeffs = *this;
    scalar val = coeffs[0];

    // Avoid costly pow() in calculation
    scalar powX = x;
    for (label i=1; i<coeffs.size(); ++i)
    {
        val += coeffs[i]*powX;
        powX *= x;
    }

    if (logActive_)
    {
        val += this->logCoeff_*log(x);
    }

    return val;
}


Foam::scalar Foam::polynomialFunction::integrate
(
    const scalar x1,
    const scalar x2
) const
{
    const scalarList& coeffs = *this;

    if (logActive_)
    {
        FatalErrorInFunction
            << "Cannot integrate polynomial with logarithmic coefficients"
            << nl << abort(FatalError);
    }

    // Avoid costly pow() in calculation
    scalar powX1 = x1;
    scalar powX2 = x2;

    scalar val = coeffs[0]*(powX2 - powX1);
    for (label i=1; i<coeffs.size(); ++i)
    {
        val += coeffs[i]/(i + 1)*(powX2 - powX1);
        powX1 *= x1;
        powX2 *= x2;
    }

    return val;
}


Foam::polynomialFunction
Foam::polynomialFunction::integral(const scalar intConstant) const
{
    return cloneIntegral(*this, intConstant);
}


Foam::polynomialFunction
Foam::polynomialFunction::integralMinus1(const scalar intConstant) const
{
    return cloneIntegralMinus1(*this, intConstant);
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

bool Foam::polynomialFunction::operator==(const polynomialFunction& rhs) const
{
    return
    (
        scalarList::operator==(static_cast<const scalarList&>(rhs))
     && logActive_ == rhs.logActive_
     && (!logActive_ || (logCoeff_ == rhs.logCoeff_))
    );
}


Foam::polynomialFunction&
Foam::polynomialFunction::operator+=(const polynomialFunction& poly)
{
    scalarList& coeffs = *this;

    if (coeffs.size() < poly.size())
    {
        coeffs.resize(poly.size(), Zero);
    }

    forAll(poly, i)
    {
        coeffs[i] += poly[i];
    }

    return *this;
}


Foam::polynomialFunction&
Foam::polynomialFunction::operator-=(const polynomialFunction& poly)
{
    scalarList& coeffs = *this;

    if (coeffs.size() < poly.size())
    {
        coeffs.resize(poly.size(), Zero);
    }

    forAll(poly, i)
    {
        coeffs[i] -= poly[i];
    }

    return *this;
}


Foam::polynomialFunction&
Foam::polynomialFunction::operator*=(const scalar s)
{
    scalarList& coeffs = *this;
    forAll(coeffs, i)
    {
        coeffs[i] *= s;
    }

    return *this;
}


Foam::polynomialFunction&
Foam::polynomialFunction::operator/=(const scalar s)
{
    scalarList& coeffs = *this;
    forAll(coeffs, i)
    {
        coeffs[i] /= s;
    }

    return *this;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

Foam::Istream& Foam::operator>>(Istream& is, polynomialFunction& poly)
{
    // Log handling may be unreliable
    poly.logActive_ = false;
    poly.logCoeff_ = 0;

    is >> static_cast<scalarList&>(poly);

    poly.checkSize();

    return is;
}


Foam::Ostream& Foam::operator<<(Ostream& os, const polynomialFunction& poly)
{
    // output like VectorSpace
    os  << token::BEGIN_LIST;

    forAll(poly, i)
    {
        if (i) os << token::SPACE;
        os  << poly[i];
    }
    os  << token::END_LIST;

    os.check(FUNCTION_NAME);

    return os;
}


// * * * * * * * * * * * * * * * Global Operators  * * * * * * * * * * * * * //

Foam::polynomialFunction
Foam::operator+
(
    const polynomialFunction& p1,
    const polynomialFunction& p2
)
{
    polynomialFunction poly(p1);
    return poly += p2;
}


Foam::polynomialFunction
Foam::operator-
(
    const polynomialFunction& p1,
    const polynomialFunction& p2
)
{
    polynomialFunction poly(p1);
    return poly -= p2;
}


Foam::polynomialFunction
Foam::operator*
(
    const scalar s,
    const polynomialFunction& p
)
{
    polynomialFunction poly(p);
    return poly *= s;
}


Foam::polynomialFunction
Foam::operator/
(
    const scalar s,
    const polynomialFunction& p
)
{
    polynomialFunction poly(p);
    return poly /= s;
}


Foam::polynomialFunction
Foam::operator*
(
    const polynomialFunction& p,
    const scalar s
)
{
    polynomialFunction poly(p);
    return poly *= s;
}


Foam::polynomialFunction
Foam::operator/
(
    const polynomialFunction& p,
    const scalar s
)
{
    polynomialFunction poly(p);
    return poly /= s;
}


// ************************************************************************* //

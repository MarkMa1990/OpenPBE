/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2013 OpenFOAM Foundation
     \\/     M anipulation  |
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

#include "binaryBreakup.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //
namespace Foam
{
namespace breakupKernels
{
defineTypeNameAndDebug(binaryBreakup, 0);
addToRunTimeSelectionTable
(
    breakupKernel,
    binaryBreakup,
    dictionary
);

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

binaryBreakup::binaryBreakup
(
    const dictionary& breakupDict,
    const phaseModel& dispersedPhase
)
:
    breakupKernel(breakupDict, dispersedPhase),
    c_("c", dimensionSet(0, -3, -1, 0, 0), breakupDict.lookup("c"))
{
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //
//
binaryBreakup::~binaryBreakup()
{}

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

dimensionedScalar binaryBreakup::S(const dimensionedScalar& xi) const
{
    return c_ * xi;
}

tmp<volScalarField> binaryBreakup::S(const volScalarField& xi) const
{
    return tmp<volScalarField>
        (
            new volScalarField
            (
                IOobject
                (
                    "bRate",
                    xi.mesh().time().timeName(),
                    xi.mesh(),
                    IOobject::NO_READ,
                    IOobject::NO_WRITE
                ),
                c_ * xi
            )
        );
}

} //End namespace breakupKernels
} //End namespace Foam
// ************************************************************************* //
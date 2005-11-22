/**
 *  @file Integrator.h
 *
 *  $Author$
 *  $Date$
 *  $Revision$
 *
 */

/**
 * @defgroup odeGroup ODE Integrators
 */

// Copyright 2001  California Institute of Technology


#ifndef CT_INTEGRATOR_H
#define CT_INTEGRATOR_H

#ifdef WIN32
#pragma warning(disable:4786)
#pragma warning(disable:4503)
#endif

#include "FuncEval.h"

#include "ct_defs.h"
#include "global.h"

#define DIAG  1
#define DENSE 2
#define NOJAC 4
#define JAC 8
#define GMRES 16


namespace Cantera {

    /**
     * Specifies the method used to integrate the system of equations.
     * Not all methods are supported by all integrators.
     */
    enum MethodType { 
        BDF_Method,          /**< Backward Differentiation */ 
        Adams_Method         /**< Adams                    */
    };

    /**
     * Specifies the method used for iteration.
     * Not all methods are supported by all integrators.
     */
    enum IterType { 
        Newton_Iter,         /**< Newton iteration         */ 
        Functional_Iter      /**< Functional iteration     */
    };


    /**
     *  Abstract base class for ODE system integrators.
     *  @ingroup odeGroup
     */
    class Integrator {

    public:

        virtual ~Integrator() {}

        /** Set or reset the number of equations. */ 
        //virtual void resize(int n)=0;

        /**
         * Set error tolerances. 
         * @param reltol scalar relative tolerance
         * @param number of equations
         * @param abstol array of N absolute tolerance values
         */ 
        virtual void setTolerances(doublereal reltol, int n, 
            doublereal* abstol) { warn("setTolerances"); }

        /**
         * Set error tolerances. 
         * @param reltol scalar relative tolerance
         * @param abstol scalar absolute tolerance
         */ 
        virtual void setTolerances(doublereal reltol, doublereal abstol)
            { warn("setTolerances"); }

        virtual void setSensitivityTolerances(doublereal reltol, doublereal abstol)
            {}//            { warn("setSensitivityTolerances"); }

        /**
         * Set problem type.
         */
        virtual void setProblemType(int probtype) { warn("setProblemType"); }

        /**
         * Initialize the integrator for a new problem. Call after
         * all options have been set.
         * @param t0   initial time
         * @param func RHS evaluator object for system of equations.
         */ 
        virtual void initialize(doublereal t0, FuncEval& func)
            { warn("initialize"); }

        virtual void reinitialize(doublereal t0, FuncEval& func)
            { warn("reinitialize"); }

        /**
         * Integrate the system of equations.
         * @param tout integrate to this time. Note that this is the
         * absolute time value, not a time interval.
         */
        virtual void integrate(doublereal tout)
            { warn("integrate"); }

        /**
         * Integrate the system of equations.
         * @param tout integrate to this time. Note that this is the
         * absolute time value, not a time interval.
         */
        virtual doublereal step(doublereal tout)
            { warn("step"); return 0.0; }

        /** The current value of the solution of equation k. */
	virtual doublereal& solution(int k)
            { warn("solution"); return m_dummy; }

        /** The current value of the solution of the system of equations. */
	virtual doublereal* solution()
            { warn("solution"); return 0; }

        /** The number of equations. */
	virtual int nEquations() const
            { warn("nEquations"); return 0; }

        /** The number of function evaluations. */
        virtual int nEvals() const 
            { warn("nEvals"); return 0; }

        /** Set the maximum integration order that will be used. **/
        virtual void setMaxOrder(int n)
            { warn("setMaxorder"); }

        /** Set the solution method */
        virtual void setMethod(MethodType t)
            { warn("setMethodType"); }

        /** Set the linear iterator. */
        virtual void setIterator(IterType t) 
            { warn("setInterator"); }

        /** Set the maximum step size */
        virtual void setMaxStepSize(double hmax)
            { warn("setMaxStepSize"); }

        /** Set the minimum step size */
        virtual void setMinStepSize(double hmin)
            { warn("setMinStepSize"); }

        virtual void setMaxSteps(int nmax) 
            { warn("setMaxStep"); }

        virtual int nSensParams() 
            { warn("nSensParams()"); return 0; }

        virtual double sensitivity(int k, int p) { 
            warn("sensitivity"); return 0.0;
        }
        
    private:

        doublereal m_dummy;
        void warn(string msg) const {
            writelog(">>>> Warning: method "+msg+" of base class "
                +"Integrator called. Nothing done.\n");
        }

    };

    // defined in ODE_integrators.cpp
    Integrator* newIntegrator(string itype);

}    // namespace

#endif 

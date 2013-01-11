// This file has been generated by Py++.

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
#include "boost/python/suite/indexing/vector_indexing_suite.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "BasicVector3D.h"
#include "Experiment.h"
#include "FormFactorCrystal.h"
#include "FormFactorCylinder.h"
#include "FormFactorDecoratorDebyeWaller.h"
#include "FormFactorFullSphere.h"
#include "FormFactorGauss.h"
#include "FormFactorLorentz.h"
#include "FormFactorPrism3.h"
#include "FormFactorPyramid.h"
#include "FormFactorSphereGaussianRadius.h"
#include "GISASExperiment.h"
#include "HomogeneousMaterial.h"
#include "ICloneable.h"
#include "IClusteredParticles.h"
#include "ICompositeSample.h"
#include "IDecoration.h"
#include "IFormFactor.h"
#include "IFormFactorBorn.h"
#include "IFormFactorDecorator.h"
#include "IInterferenceFunction.h"
#include "InterferenceFunctionNone.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "IMaterial.h"
#include "IParameterized.h"
#include "ISample.h"
#include "ISampleBuilder.h"
#include "ISelectionRule.h"
#include "ISingleton.h"
#include "Lattice.h"
#include "LatticeBasis.h"
#include "Layer.h"
#include "LayerDecorator.h"
#include "LayerRoughness.h"
#include "MaterialManager.h"
#include "MesoCrystal.h"
#include "MultiLayer.h"
#include "Particle.h"
#include "Crystal.h"
#include "ParticleDecoration.h"
#include "OpticalFresnel.h"
#include "ParameterPool.h"
#include "ParticleInfo.h"
#include "DiffuseParticleInfo.h"
#include "PythonOutputData.h"
#include "PythonPlusplusHelper.h"
#include "RealParameterWrapper.h"
#include "Transform3D.h"
#include "Units.h"
#include "Types.h"
#include "InterferenceFunction1DParaCrystal.pypp.h"

namespace bp = boost::python;

struct InterferenceFunction1DParaCrystal_wrapper : InterferenceFunction1DParaCrystal, bp::wrapper< InterferenceFunction1DParaCrystal > {

    InterferenceFunction1DParaCrystal_wrapper(double peak_distance, double width, double corr_length=0.0 )
    : InterferenceFunction1DParaCrystal( peak_distance, width, corr_length )
      , bp::wrapper< InterferenceFunction1DParaCrystal >(){
        // constructor
    
    }

    virtual ::InterferenceFunction1DParaCrystal * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->InterferenceFunction1DParaCrystal::clone(  );
        }
    }
    
    ::InterferenceFunction1DParaCrystal * default_clone(  ) const  {
        return InterferenceFunction1DParaCrystal::clone( );
    }

    virtual double evaluate( ::cvector_t const & q ) const  {
        if( bp::override func_evaluate = this->get_override( "evaluate" ) )
            return func_evaluate( boost::ref(q) );
        else{
            return this->InterferenceFunction1DParaCrystal::evaluate( boost::ref(q) );
        }
    }
    
    double default_evaluate( ::cvector_t const & q ) const  {
        return InterferenceFunction1DParaCrystal::evaluate( boost::ref(q) );
    }

    virtual bool areParametersChanged(  ) {
        if( bp::override func_areParametersChanged = this->get_override( "areParametersChanged" ) )
            return func_areParametersChanged(  );
        else{
            return this->IParameterized::areParametersChanged(  );
        }
    }
    
    bool default_areParametersChanged(  ) {
        return IParameterized::areParametersChanged( );
    }

    virtual ::ParameterPool * createParameterTree(  ) const  {
        if( bp::override func_createParameterTree = this->get_override( "createParameterTree" ) )
            return func_createParameterTree(  );
        else{
            return this->IParameterized::createParameterTree(  );
        }
    }
    
    ::ParameterPool * default_createParameterTree(  ) const  {
        return IParameterized::createParameterTree( );
    }

    virtual void printParameters(  ) const  {
        if( bp::override func_printParameters = this->get_override( "printParameters" ) )
            func_printParameters(  );
        else{
            this->IParameterized::printParameters(  );
        }
    }
    
    void default_printParameters(  ) const  {
        IParameterized::printParameters( );
    }

    virtual void print_structure(  ) {
        if( bp::override func_print_structure = this->get_override( "print_structure" ) )
            func_print_structure(  );
        else{
            this->ISample::print_structure(  );
        }
    }
    
    void default_print_structure(  ) {
        ISample::print_structure( );
    }

    virtual void setParametersAreChanged(  ) {
        if( bp::override func_setParametersAreChanged = this->get_override( "setParametersAreChanged" ) )
            func_setParametersAreChanged(  );
        else{
            this->IParameterized::setParametersAreChanged(  );
        }
    }
    
    void default_setParametersAreChanged(  ) {
        IParameterized::setParametersAreChanged( );
    }

};

void register_InterferenceFunction1DParaCrystal_class(){

    bp::class_< InterferenceFunction1DParaCrystal_wrapper, bp::bases< IInterferenceFunction >, boost::noncopyable >( "InterferenceFunction1DParaCrystal", bp::init< double, double, bp::optional< double > >(( bp::arg("peak_distance"), bp::arg("width"), bp::arg("corr_length")=0.0 )) )    
        .def( 
            "clone"
            , (::InterferenceFunction1DParaCrystal * ( ::InterferenceFunction1DParaCrystal::* )(  ) const)(&::InterferenceFunction1DParaCrystal::clone)
            , (::InterferenceFunction1DParaCrystal * ( InterferenceFunction1DParaCrystal_wrapper::* )(  ) const)(&InterferenceFunction1DParaCrystal_wrapper::default_clone)
            , bp::return_value_policy< bp::manage_new_object >() )    
        .def( 
            "evaluate"
            , (double ( ::InterferenceFunction1DParaCrystal::* )( ::cvector_t const & ) const)(&::InterferenceFunction1DParaCrystal::evaluate)
            , (double ( InterferenceFunction1DParaCrystal_wrapper::* )( ::cvector_t const & ) const)(&InterferenceFunction1DParaCrystal_wrapper::default_evaluate)
            , ( bp::arg("q") ) )    
        .def( 
            "areParametersChanged"
            , (bool ( ::IParameterized::* )(  ) )(&::IParameterized::areParametersChanged)
            , (bool ( InterferenceFunction1DParaCrystal_wrapper::* )(  ) )(&InterferenceFunction1DParaCrystal_wrapper::default_areParametersChanged) )    
        .def( 
            "createParameterTree"
            , (::ParameterPool * ( ::IParameterized::* )(  ) const)(&::IParameterized::createParameterTree)
            , (::ParameterPool * ( InterferenceFunction1DParaCrystal_wrapper::* )(  ) const)(&InterferenceFunction1DParaCrystal_wrapper::default_createParameterTree)
            , bp::return_value_policy< bp::manage_new_object >() )    
        .def( 
            "printParameters"
            , (void ( ::IParameterized::* )(  ) const)(&::IParameterized::printParameters)
            , (void ( InterferenceFunction1DParaCrystal_wrapper::* )(  ) const)(&InterferenceFunction1DParaCrystal_wrapper::default_printParameters) )    
        .def( 
            "print_structure"
            , (void ( ::ISample::* )(  ) )(&::ISample::print_structure)
            , (void ( InterferenceFunction1DParaCrystal_wrapper::* )(  ) )(&InterferenceFunction1DParaCrystal_wrapper::default_print_structure) )    
        .def( 
            "setParametersAreChanged"
            , (void ( ::IParameterized::* )(  ) )(&::IParameterized::setParametersAreChanged)
            , (void ( InterferenceFunction1DParaCrystal_wrapper::* )(  ) )(&InterferenceFunction1DParaCrystal_wrapper::default_setParametersAreChanged) );

}

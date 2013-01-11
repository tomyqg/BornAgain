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
#include "LatticeBasis.pypp.h"

namespace bp = boost::python;

struct LatticeBasis_wrapper : LatticeBasis, bp::wrapper< LatticeBasis > {

    LatticeBasis_wrapper( )
    : LatticeBasis( )
      , bp::wrapper< LatticeBasis >(){
        // null constructor
    
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

    virtual ::ICompositeSample * getCompositeSample(  ) {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ICompositeSample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample * default_getCompositeSample(  ) {
        return ICompositeSample::getCompositeSample( );
    }

    virtual ::ICompositeSample const * getCompositeSample(  ) const  {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ICompositeSample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample const * default_getCompositeSample(  ) const  {
        return ICompositeSample::getCompositeSample( );
    }

    virtual ::complex_t const getRefractiveIndex(  ) const  {
        if( bp::override func_getRefractiveIndex = this->get_override( "getRefractiveIndex" ) )
            return func_getRefractiveIndex(  );
        else{
            return this->Particle::getRefractiveIndex(  );
        }
    }
    
    ::complex_t const default_getRefractiveIndex(  ) const  {
        return Particle::getRefractiveIndex( );
    }

    virtual ::IFormFactor const * getSimpleFormFactor(  ) const  {
        if( bp::override func_getSimpleFormFactor = this->get_override( "getSimpleFormFactor" ) )
            return func_getSimpleFormFactor(  );
        else{
            return this->Particle::getSimpleFormFactor(  );
        }
    }
    
    ::IFormFactor const * default_getSimpleFormFactor(  ) const  {
        return Particle::getSimpleFormFactor( );
    }

    virtual bool hasDistributedFormFactor(  ) const  {
        if( bp::override func_hasDistributedFormFactor = this->get_override( "hasDistributedFormFactor" ) )
            return func_hasDistributedFormFactor(  );
        else{
            return this->Particle::hasDistributedFormFactor(  );
        }
    }
    
    bool default_hasDistributedFormFactor(  ) const  {
        return Particle::hasDistributedFormFactor( );
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

    virtual ::size_t size(  ) const  {
        if( bp::override func_size = this->get_override( "size" ) )
            return func_size(  );
        else{
            return this->ICompositeSample::size(  );
        }
    }
    
    ::size_t default_size(  ) const  {
        return ICompositeSample::size( );
    }

};

void register_LatticeBasis_class(){

    bp::class_< LatticeBasis_wrapper, bp::bases< Particle >, boost::noncopyable >( "LatticeBasis", bp::init< >() )    
        .def( 
            "addParticle"
            , (void ( ::LatticeBasis::* )( ::Particle const &,::std::vector< Geometry::BasicVector3D<double> > ) )( &::LatticeBasis::addParticle )
            , ( bp::arg("particle"), bp::arg("positions") ) )    
        .def( 
            "areParametersChanged"
            , (bool ( ::IParameterized::* )(  ) )(&::IParameterized::areParametersChanged)
            , (bool ( LatticeBasis_wrapper::* )(  ) )(&LatticeBasis_wrapper::default_areParametersChanged) )    
        .def( 
            "createParameterTree"
            , (::ParameterPool * ( ::IParameterized::* )(  ) const)(&::IParameterized::createParameterTree)
            , (::ParameterPool * ( LatticeBasis_wrapper::* )(  ) const)(&LatticeBasis_wrapper::default_createParameterTree)
            , bp::return_value_policy< bp::manage_new_object >() )    
        .def( 
            "getCompositeSample"
            , (::ICompositeSample * ( ::ICompositeSample::* )(  ) )(&::ICompositeSample::getCompositeSample)
            , (::ICompositeSample * ( LatticeBasis_wrapper::* )(  ) )(&LatticeBasis_wrapper::default_getCompositeSample)
            , bp::return_value_policy< bp::reference_existing_object >() )    
        .def( 
            "getCompositeSample"
            , (::ICompositeSample const * ( ::ICompositeSample::* )(  ) const)(&::ICompositeSample::getCompositeSample)
            , (::ICompositeSample const * ( LatticeBasis_wrapper::* )(  ) const)(&LatticeBasis_wrapper::default_getCompositeSample)
            , bp::return_value_policy< bp::reference_existing_object >() )    
        .def( 
            "getRefractiveIndex"
            , (::complex_t const ( ::Particle::* )(  ) const)(&::Particle::getRefractiveIndex)
            , (::complex_t const ( LatticeBasis_wrapper::* )(  ) const)(&LatticeBasis_wrapper::default_getRefractiveIndex) )    
        .def( 
            "getSimpleFormFactor"
            , (::IFormFactor const * ( ::Particle::* )(  ) const)(&::Particle::getSimpleFormFactor)
            , (::IFormFactor const * ( LatticeBasis_wrapper::* )(  ) const)(&LatticeBasis_wrapper::default_getSimpleFormFactor)
            , bp::return_value_policy< bp::reference_existing_object >() )    
        .def( 
            "hasDistributedFormFactor"
            , (bool ( ::Particle::* )(  ) const)(&::Particle::hasDistributedFormFactor)
            , (bool ( LatticeBasis_wrapper::* )(  ) const)(&LatticeBasis_wrapper::default_hasDistributedFormFactor) )    
        .def( 
            "printParameters"
            , (void ( ::IParameterized::* )(  ) const)(&::IParameterized::printParameters)
            , (void ( LatticeBasis_wrapper::* )(  ) const)(&LatticeBasis_wrapper::default_printParameters) )    
        .def( 
            "print_structure"
            , (void ( ::ISample::* )(  ) )(&::ISample::print_structure)
            , (void ( LatticeBasis_wrapper::* )(  ) )(&LatticeBasis_wrapper::default_print_structure) )    
        .def( 
            "setParametersAreChanged"
            , (void ( ::IParameterized::* )(  ) )(&::IParameterized::setParametersAreChanged)
            , (void ( LatticeBasis_wrapper::* )(  ) )(&LatticeBasis_wrapper::default_setParametersAreChanged) )    
        .def( 
            "size"
            , (::size_t ( ::ICompositeSample::* )(  ) const)(&::ICompositeSample::size)
            , (::size_t ( LatticeBasis_wrapper::* )(  ) const)(&LatticeBasis_wrapper::default_size) );

}

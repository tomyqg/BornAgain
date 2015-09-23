// This file has been generated by Py++.

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Automatically generated boost::python code for BornAgain Python bindings
//! @brief     Automatically generated boost::python code for BornAgain Python bindings
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Juelich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter)
GCC_DIAG_OFF(missing-field-initializers)
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter)
GCC_DIAG_ON(missing-field-initializers)
#include "PythonCoreList.h"
#include "IntensityData.pypp.h"

namespace bp = boost::python;

struct OutputData_less__double__greater__wrapper : OutputData< double >, bp::wrapper< OutputData< double > > {

    OutputData_less__double__greater__wrapper( )
    : OutputData<double>( )
      , bp::wrapper< OutputData< double > >(){
        // null constructor
    m_pyobj = 0;
    }

    PyObject* m_pyobj;

};

void register_IntensityData_class(){

    { //::OutputData< double >
        typedef bp::class_< OutputData_less__double__greater__wrapper, std::auto_ptr< OutputData_less__double__greater__wrapper >, boost::noncopyable > IntensityData_exposer_t;
        IntensityData_exposer_t IntensityData_exposer = IntensityData_exposer_t( "IntensityData", bp::init< >() );
        bp::scope IntensityData_scope( IntensityData_exposer );
        { //::OutputData< double >::addAxis
        
            typedef OutputData< double > exported_class_t;
            typedef void ( exported_class_t::*addAxis_function_type)( ::IAxis const & ) ;
            
            IntensityData_exposer.def( 
                "addAxis"
                , addAxis_function_type( &::OutputData< double >::addAxis )
                , ( bp::arg("new_axis") ) );
        
        }
        { //::OutputData< double >::addAxis
        
            typedef OutputData< double > exported_class_t;
            typedef void ( exported_class_t::*addAxis_function_type)( ::std::string const &,::std::size_t,double,double ) ;
            
            IntensityData_exposer.def( 
                "addAxis"
                , addAxis_function_type( &::OutputData< double >::addAxis )
                , ( bp::arg("name"), bp::arg("size"), bp::arg("start"), bp::arg("end") ) );
        
        }
        { //::OutputData< double >::clear
        
            typedef OutputData< double > exported_class_t;
            typedef void ( exported_class_t::*clear_function_type)(  ) ;
            
            IntensityData_exposer.def( 
                "clear"
                , clear_function_type( &::OutputData< double >::clear ) );
        
        }
        { //::OutputData< double >::clone
        
            typedef OutputData< double > exported_class_t;
            typedef ::OutputData< double > * ( exported_class_t::*clone_function_type)(  ) const;
            
            IntensityData_exposer.def( 
                "clone"
                , clone_function_type( &::OutputData< double >::clone )
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::OutputData< double >::copyFrom
        
            typedef OutputData< double > exported_class_t;
            typedef void ( exported_class_t::*copyFrom_function_type)( ::OutputData< double > const & ) ;
            
            IntensityData_exposer.def( 
                "copyFrom"
                , copyFrom_function_type( &::OutputData< double >::copyFrom )
                , ( bp::arg("other") ) );
        
        }
        { //::OutputData< double >::findGlobalIndex
        
            typedef OutputData< double > exported_class_t;
            typedef ::std::size_t ( exported_class_t::*findGlobalIndex_function_type)( ::std::vector< double > const & ) const;
            
            IntensityData_exposer.def( 
                "findGlobalIndex"
                , findGlobalIndex_function_type( &::OutputData< double >::findGlobalIndex )
                , ( bp::arg("coordinates") ) );
        
        }
        { //::OutputData< double >::getAllSizes
        
            typedef OutputData< double > exported_class_t;
            typedef ::std::vector< unsigned long > ( exported_class_t::*getAllSizes_function_type)(  ) const;
            
            IntensityData_exposer.def( 
                "getAllSizes"
                , getAllSizes_function_type( &::OutputData< double >::getAllSizes ) );
        
        }
        { //::OutputData< double >::getAllocatedSize
        
            typedef OutputData< double > exported_class_t;
            typedef ::std::size_t ( exported_class_t::*getAllocatedSize_function_type)(  ) const;
            
            IntensityData_exposer.def( 
                "getAllocatedSize"
                , getAllocatedSize_function_type( &::OutputData< double >::getAllocatedSize )
                , "Returns total size of data buffer (product of bin number in every dimension)." );
        
        }
        { //::OutputData< double >::getArray
        
            typedef OutputData< double > exported_class_t;
            typedef ::PyObject * ( exported_class_t::*getArray_function_type)(  ) const;
            
            IntensityData_exposer.def( 
                "getArray"
                , getArray_function_type( &::OutputData< double >::getArray )
                , "returns data as Python numpy array." );
        
        }
        { //::OutputData< double >::getAxesBinIndices
        
            typedef OutputData< double > exported_class_t;
            typedef ::std::vector< int > ( exported_class_t::*getAxesBinIndices_function_type)( ::std::size_t ) const;
            
            IntensityData_exposer.def( 
                "getAxesBinIndices"
                , getAxesBinIndices_function_type( &::OutputData< double >::getAxesBinIndices )
                , ( bp::arg("global_index") ) );
        
        }
        { //::OutputData< double >::getAxis
        
            typedef OutputData< double > exported_class_t;
            typedef ::IAxis const * ( exported_class_t::*getAxis_function_type)( ::std::size_t ) const;
            
            IntensityData_exposer.def( 
                "getAxis"
                , getAxis_function_type( &::OutputData< double >::getAxis )
                , ( bp::arg("serial_number") )
                , bp::return_internal_reference< >() );
        
        }
        { //::OutputData< double >::getAxis
        
            typedef OutputData< double > exported_class_t;
            typedef ::IAxis const * ( exported_class_t::*getAxis_function_type)( ::std::string const & ) const;
            
            IntensityData_exposer.def( 
                "getAxis"
                , getAxis_function_type( &::OutputData< double >::getAxis )
                , ( bp::arg("axis_name") )
                , bp::return_internal_reference< >() );
        
        }
        { //::OutputData< double >::getAxisBin
        
            typedef OutputData< double > exported_class_t;
            typedef ::Bin1D ( exported_class_t::*getAxisBin_function_type)( ::std::size_t,::std::string const & ) const;
            
            IntensityData_exposer.def( 
                "getAxisBin"
                , getAxisBin_function_type( &::OutputData< double >::getAxisBin )
                , ( bp::arg("global_index"), bp::arg("axis_name") ) );
        
        }
        { //::OutputData< double >::getAxisBinIndex
        
            typedef OutputData< double > exported_class_t;
            typedef int ( exported_class_t::*getAxisBinIndex_function_type)( ::std::size_t,::std::size_t ) const;
            
            IntensityData_exposer.def( 
                "getAxisBinIndex"
                , getAxisBinIndex_function_type( &::OutputData< double >::getAxisBinIndex )
                , ( bp::arg("global_index"), bp::arg("i_selected_axis") ) );
        
        }
        { //::OutputData< double >::getAxisBinIndex
        
            typedef OutputData< double > exported_class_t;
            typedef int ( exported_class_t::*getAxisBinIndex_function_type)( ::std::size_t,::std::string const & ) const;
            
            IntensityData_exposer.def( 
                "getAxisBinIndex"
                , getAxisBinIndex_function_type( &::OutputData< double >::getAxisBinIndex )
                , ( bp::arg("global_index"), bp::arg("axis_name") ) );
        
        }
        { //::OutputData< double >::getAxisSerialNumber
        
            typedef OutputData< double > exported_class_t;
            typedef ::std::size_t ( exported_class_t::*getAxisSerialNumber_function_type)( ::std::string const & ) const;
            
            IntensityData_exposer.def( 
                "getAxisSerialNumber"
                , getAxisSerialNumber_function_type( &::OutputData< double >::getAxisSerialNumber )
                , ( bp::arg("axis_name") ) );
        
        }
        { //::OutputData< double >::getAxisValue
        
            typedef OutputData< double > exported_class_t;
            typedef double ( exported_class_t::*getAxisValue_function_type)( ::std::size_t,::std::size_t ) const;
            
            IntensityData_exposer.def( 
                "getAxisValue"
                , getAxisValue_function_type( &::OutputData< double >::getAxisValue )
                , ( bp::arg("global_index"), bp::arg("i_selected_axis") ) );
        
        }
        { //::OutputData< double >::getAxisValue
        
            typedef OutputData< double > exported_class_t;
            typedef double ( exported_class_t::*getAxisValue_function_type)( ::std::size_t,::std::string const & ) const;
            
            IntensityData_exposer.def( 
                "getAxisValue"
                , getAxisValue_function_type( &::OutputData< double >::getAxisValue )
                , ( bp::arg("global_index"), bp::arg("axis_name") ) );
        
        }
        { //::OutputData< double >::getRank
        
            typedef OutputData< double > exported_class_t;
            typedef ::std::size_t ( exported_class_t::*getRank_function_type)(  ) const;
            
            IntensityData_exposer.def( 
                "getRank"
                , getRank_function_type( &::OutputData< double >::getRank )
                , "Returns number of dimensions." );
        
        }
        { //::OutputData< double >::getRawDataVector
        
            typedef OutputData< double > exported_class_t;
            typedef ::std::vector< double > ( exported_class_t::*getRawDataVector_function_type)(  ) const;
            
            IntensityData_exposer.def( 
                "getRawDataVector"
                , getRawDataVector_function_type( &::OutputData< double >::getRawDataVector ) );
        
        }
        { //::OutputData< double >::hasSameDimensions
        
            typedef OutputData< double > exported_class_t;
            typedef bool ( exported_class_t::*hasSameDimensions_function_type)( ::OutputData< double > const & ) const;
            
            IntensityData_exposer.def( 
                "hasSameDimensions"
                , hasSameDimensions_function_type( &::OutputData< double >::hasSameDimensions )
                , ( bp::arg("right") )
                , "Returns true if object have same dimensions." );
        
        }
        { //::OutputData< double >::hasSameShape
        
            typedef OutputData< double > exported_class_t;
            typedef bool ( exported_class_t::*hasSameShape_function_type)( ::OutputData< double > const & ) const;
            
            IntensityData_exposer.def( 
                "hasSameShape"
                , hasSameShape_function_type( &::OutputData< double >::hasSameShape )
                , ( bp::arg("right") )
                , "Returns true if object have same dimensions and shape of axis." );
        
        }
        IntensityData_exposer.def( bp::self *= bp::self );
        IntensityData_exposer.def( bp::self += bp::self );
        IntensityData_exposer.def( bp::self -= bp::self );
        IntensityData_exposer.def( bp::self /= bp::self );
        { //::OutputData< double >::operator[]
        
            typedef OutputData< double > exported_class_t;
            typedef double & ( exported_class_t::*__getitem___function_type)( ::std::size_t ) ;
            
            IntensityData_exposer.def( 
                "__getitem__"
                , __getitem___function_type( &::OutputData< double >::operator[] )
                , ( bp::arg("index") )
                , bp::return_value_policy< bp::copy_non_const_reference >()
                , "indexed accessor." );
        
        }
        { //::OutputData< double >::operator[]
        
            typedef OutputData< double > exported_class_t;
            typedef double const & ( exported_class_t::*__getitem___function_type)( ::std::size_t ) const;
            
            IntensityData_exposer.def( 
                "__getitem__"
                , __getitem___function_type( &::OutputData< double >::operator[] )
                , ( bp::arg("index") )
                , bp::return_value_policy< bp::copy_const_reference >()
                , "indexed accessor (const)." );
        
        }
        { //::OutputData< double >::removeAllMasks
        
            typedef OutputData< double > exported_class_t;
            typedef void ( exported_class_t::*removeAllMasks_function_type)(  ) ;
            
            IntensityData_exposer.def( 
                "removeAllMasks"
                , removeAllMasks_function_type( &::OutputData< double >::removeAllMasks ) );
        
        }
        { //::OutputData< double >::scaleAll
        
            typedef OutputData< double > exported_class_t;
            typedef void ( exported_class_t::*scaleAll_function_type)( double const & ) ;
            
            IntensityData_exposer.def( 
                "scaleAll"
                , scaleAll_function_type( &::OutputData< double >::scaleAll )
                , ( bp::arg("factor") ) );
        
        }
        { //::OutputData< double >::setAllTo
        
            typedef OutputData< double > exported_class_t;
            typedef void ( exported_class_t::*setAllTo_function_type)( double const & ) ;
            
            IntensityData_exposer.def( 
                "setAllTo"
                , setAllTo_function_type( &::OutputData< double >::setAllTo )
                , ( bp::arg("value") ) );
        
        }
        { //::OutputData< double >::setRawDataVector
        
            typedef OutputData< double > exported_class_t;
            typedef void ( exported_class_t::*setRawDataVector_function_type)( ::std::vector< double > const & ) ;
            
            IntensityData_exposer.def( 
                "setRawDataVector"
                , setRawDataVector_function_type( &::OutputData< double >::setRawDataVector )
                , ( bp::arg("data_vector") ) );
        
        }
        { //::OutputData< double >::toGlobalIndex
        
            typedef OutputData< double > exported_class_t;
            typedef ::std::size_t ( exported_class_t::*toGlobalIndex_function_type)( ::std::vector< int > const & ) const;
            
            IntensityData_exposer.def( 
                "toGlobalIndex"
                , toGlobalIndex_function_type( &::OutputData< double >::toGlobalIndex )
                , ( bp::arg("axes_indices") ) );
        
        }
        { //::OutputData< double >::totalSum
        
            typedef OutputData< double > exported_class_t;
            typedef double ( exported_class_t::*totalSum_function_type)(  ) const;
            
            IntensityData_exposer.def( 
                "totalSum"
                , totalSum_function_type( &::OutputData< double >::totalSum ) );
        
        }
        IntensityData_exposer.def("__setitem__", &pyplusplus_setitem<OutputData<double >,int,double> );
    }

}

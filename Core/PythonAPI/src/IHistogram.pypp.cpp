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
#include "IHistogram.pypp.h"

namespace bp = boost::python;

struct IHistogram_wrapper : IHistogram, bp::wrapper< IHistogram > {

    IHistogram_wrapper( )
    : IHistogram( )
      , bp::wrapper< IHistogram >(){
        // null constructor
    
    }

    IHistogram_wrapper(::IAxis const & axis_x )
    : IHistogram( boost::ref(axis_x) )
      , bp::wrapper< IHistogram >(){
        // constructor
    
    }

    IHistogram_wrapper(::IAxis const & axis_x, ::IAxis const & axis_y )
    : IHistogram( boost::ref(axis_x), boost::ref(axis_y) )
      , bp::wrapper< IHistogram >(){
        // constructor
    
    }

    virtual ::std::size_t getRank(  ) const  {
        if( bp::override func_getRank = this->get_override( "getRank" ) )
            return func_getRank(  );
        else{
            return this->IHistogram::getRank(  );
        }
    }
    
    ::std::size_t default_getRank(  ) const  {
        return IHistogram::getRank( );
    }

};

void register_IHistogram_class(){

    { //::IHistogram
        typedef bp::class_< IHistogram_wrapper, boost::noncopyable > IHistogram_exposer_t;
        IHistogram_exposer_t IHistogram_exposer = IHistogram_exposer_t( "IHistogram", "Base class for 1D and 2D histograms holding values of double typ.", bp::init< >() );
        bp::scope IHistogram_scope( IHistogram_exposer );
        bp::enum_< IHistogram::DataType>("DataType")
            .value("INTEGRAL", IHistogram::INTEGRAL)
            .value("AVERAGE", IHistogram::AVERAGE)
            .value("ERROR", IHistogram::ERROR)
            .value("NENTRIES", IHistogram::NENTRIES)
            .export_values()
            ;
        IHistogram_exposer.def( bp::init< IAxis const & >(( bp::arg("axis_x") )) );
        IHistogram_exposer.def( bp::init< IAxis const &, IAxis const & >(( bp::arg("axis_x"), bp::arg("axis_y") )) );
        { //::IHistogram::createHistogram
        
            typedef ::IHistogram * ( *createHistogram_function_type )( ::OutputData< double > const & );
            
            IHistogram_exposer.def( 
                "createHistogram"
                , createHistogram_function_type( &::IHistogram::createHistogram )
                , ( bp::arg("source") )
                , bp::return_value_policy< bp::manage_new_object >()
                , "Reset histogram content (axes remains)." );
        
        }
        { //::IHistogram::createOutputData
        
            typedef ::OutputData< double > * ( ::IHistogram::*createOutputData_function_type)( ::IHistogram::DataType ) const;
            
            IHistogram_exposer.def( 
                "createOutputData"
                , createOutputData_function_type( &::IHistogram::createOutputData )
                , ( bp::arg("dataType")=::IHistogram::INTEGRAL )
                , bp::return_value_policy< bp::manage_new_object >()
                , "creates new OutputData with histogram's shape and put there values corresponding to DataType." );
        
        }
        { //::IHistogram::findGlobalBin
        
            typedef int ( ::IHistogram::*findGlobalBin_function_type)( double,double ) const;
            
            IHistogram_exposer.def( 
                "findGlobalBin"
                , findGlobalBin_function_type( &::IHistogram::findGlobalBin )
                , ( bp::arg("x"), bp::arg("y") )
                , "Returns closest global bin index for given axes coordinates. For 1D @param x Value on x-axis @param y Value on y-axis @return Closest global bin index \n\n:Parameters:\n  - 'x' - Value on x-axis\n  - 'y' - Value on y-axis\n" );
        
        }
        { //::IHistogram::getArray
        
            typedef ::PyObject * ( ::IHistogram::*getArray_function_type)( ::IHistogram::DataType ) const;
            
            IHistogram_exposer.def( 
                "getArray"
                , getArray_function_type( &::IHistogram::getArray )
                , ( bp::arg("dataType")=::IHistogram::INTEGRAL )
                , "Returns numpy array with bin content (accumulated values)." );
        
        }
        { //::IHistogram::getBinAverage
        
            typedef double ( ::IHistogram::*getBinAverage_function_type)( int ) const;
            
            IHistogram_exposer.def( 
                "getBinAverage"
                , getBinAverage_function_type( &::IHistogram::getBinAverage )
                , ( bp::arg("bin") )
                , "Returns average value in the bin with given index. For 1D histograms bin index is related to x-axis. For 2D histograms bin index is global bin index. " );
        
        }
        { //::IHistogram::getBinAverage
        
            typedef double ( ::IHistogram::*getBinAverage_function_type)( int,int ) const;
            
            IHistogram_exposer.def( 
                "getBinAverage"
                , getBinAverage_function_type( &::IHistogram::getBinAverage )
                , ( bp::arg("binx"), bp::arg("biny") )
                , "Returns average value in the bin of 2D histogram with given axes indices." );
        
        }
        { //::IHistogram::getBinContent
        
            typedef double ( ::IHistogram::*getBinContent_function_type)( int ) const;
            
            IHistogram_exposer.def( 
                "getBinContent"
                , getBinContent_function_type( &::IHistogram::getBinContent )
                , ( bp::arg("bin") )
                , "Returns content (accumulated value) of the bin with given index. For 1D histograms bin index is related to x-axis. For 2D histograms bin index is global bin index. @param bin Bin index @return The value accumulated by the bin (integral) \n\n:Parameters:\n  - 'bin' - Bin index\n" );
        
        }
        { //::IHistogram::getBinContent
        
            typedef double ( ::IHistogram::*getBinContent_function_type)( int,int ) const;
            
            IHistogram_exposer.def( 
                "getBinContent"
                , getBinContent_function_type( &::IHistogram::getBinContent )
                , ( bp::arg("binx"), bp::arg("biny") )
                , "Returns content (accumulated value) of the bin of 2D histogram with given axes indices. @param binx X-axis bin index @param biny Y-axis bin index @return The value accumulated by the bin (integral) \n\n:Parameters:\n  - 'binx' - X-axis bin index\n  - 'biny' - Y-axis bin index\n" );
        
        }
        { //::IHistogram::getBinError
        
            typedef double ( ::IHistogram::*getBinError_function_type)( int ) const;
            
            IHistogram_exposer.def( 
                "getBinError"
                , getBinError_function_type( &::IHistogram::getBinError )
                , ( bp::arg("bin") )
                , "Returns error of the bin with given index. For 1D histograms bin index is related to x-axis. For 2D histograms bin index is global bin index. " );
        
        }
        { //::IHistogram::getBinError
        
            typedef double ( ::IHistogram::*getBinError_function_type)( int,int ) const;
            
            IHistogram_exposer.def( 
                "getBinError"
                , getBinError_function_type( &::IHistogram::getBinError )
                , ( bp::arg("binx"), bp::arg("biny") )
                , "Returns error of the bin of 2D histogram with given axes indices." );
        
        }
        { //::IHistogram::getBinNumberOfEntries
        
            typedef int ( ::IHistogram::*getBinNumberOfEntries_function_type)( int ) const;
            
            IHistogram_exposer.def( 
                "getBinNumberOfEntries"
                , getBinNumberOfEntries_function_type( &::IHistogram::getBinNumberOfEntries )
                , ( bp::arg("bin") )
                , "Returns number of entries in the bin with given index. For 1D histograms bin index is related to x-axis. For 2D histograms bin index is global bin index. " );
        
        }
        { //::IHistogram::getBinNumberOfEntries
        
            typedef int ( ::IHistogram::*getBinNumberOfEntries_function_type)( int,int ) const;
            
            IHistogram_exposer.def( 
                "getBinNumberOfEntries"
                , getBinNumberOfEntries_function_type( &::IHistogram::getBinNumberOfEntries )
                , ( bp::arg("binx"), bp::arg("biny") )
                , "Returns number of entries in the bin of 2D histogram with given axes indices." );
        
        }
        { //::IHistogram::getGlobalBin
        
            typedef int ( ::IHistogram::*getGlobalBin_function_type)( int,int ) const;
            
            IHistogram_exposer.def( 
                "getGlobalBin"
                , getGlobalBin_function_type( &::IHistogram::getGlobalBin )
                , ( bp::arg("binx"), bp::arg("biny")=(int)(0) )
                , "Returns global bin index for given axes indices. For 1D histogram the global bin index coinside with axis index. @param binx X-axis bin index @param biny Y-axis bin index @return The global bin index \n\n:Parameters:\n  - 'binx' - X-axis bin index\n  - 'biny' - Y-axis bin index\n" );
        
        }
        { //::IHistogram::getMaximum
        
            typedef double ( ::IHistogram::*getMaximum_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getMaximum"
                , getMaximum_function_type( &::IHistogram::getMaximum )
                , "Returns histogram maximum value (maximum of getBinContent() over all bins)." );
        
        }
        { //::IHistogram::getMaximumBinIndex
        
            typedef int ( ::IHistogram::*getMaximumBinIndex_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getMaximumBinIndex"
                , getMaximumBinIndex_function_type( &::IHistogram::getMaximumBinIndex )
                , "Returns histogram maximum bin global index." );
        
        }
        { //::IHistogram::getMinimum
        
            typedef double ( ::IHistogram::*getMinimum_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getMinimum"
                , getMinimum_function_type( &::IHistogram::getMinimum )
                , "Returns histogram minimum value (minimum of getBinContent() over all bins)." );
        
        }
        { //::IHistogram::getMinimumBinIndex
        
            typedef int ( ::IHistogram::*getMinimumBinIndex_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getMinimumBinIndex"
                , getMinimumBinIndex_function_type( &::IHistogram::getMinimumBinIndex )
                , "Returns histogram minimum bin global index." );
        
        }
        { //::IHistogram::getNbinsX
        
            typedef ::std::size_t ( ::IHistogram::*getNbinsX_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getNbinsX"
                , getNbinsX_function_type( &::IHistogram::getNbinsX )
                , "Returns number of bins on x-axis." );
        
        }
        { //::IHistogram::getNbinsY
        
            typedef ::std::size_t ( ::IHistogram::*getNbinsY_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getNbinsY"
                , getNbinsY_function_type( &::IHistogram::getNbinsY )
                , "Returns number of bins on y-axis." );
        
        }
        { //::IHistogram::getRank
        
            typedef ::std::size_t ( ::IHistogram::*getRank_function_type)(  ) const;
            typedef ::std::size_t ( IHistogram_wrapper::*default_getRank_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getRank"
                , getRank_function_type(&::IHistogram::getRank)
                , default_getRank_function_type(&IHistogram_wrapper::default_getRank) );
        
        }
        { //::IHistogram::getTotalNumberOfBins
        
            typedef ::std::size_t ( ::IHistogram::*getTotalNumberOfBins_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getTotalNumberOfBins"
                , getTotalNumberOfBins_function_type( &::IHistogram::getTotalNumberOfBins )
                , "Returns total number of histogram bins. For 2D histograms the result will be the product of bin numbers along X and Y axes. " );
        
        }
        { //::IHistogram::getXaxis
        
            typedef ::IAxis const * ( ::IHistogram::*getXaxis_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getXaxis"
                , getXaxis_function_type( &::IHistogram::getXaxis )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "returns x-axis." );
        
        }
        { //::IHistogram::getXaxisIndex
        
            typedef int ( ::IHistogram::*getXaxisIndex_function_type)( ::std::size_t ) const;
            
            IHistogram_exposer.def( 
                "getXaxisIndex"
                , getXaxisIndex_function_type( &::IHistogram::getXaxisIndex )
                , ( bp::arg("globalbin") )
                , "Returns x-axis bin index for given globalbin. For 1D histograms returned value conicide with globalbin value " );
        
        }
        { //::IHistogram::getXaxisValue
        
            typedef double ( ::IHistogram::*getXaxisValue_function_type)( ::std::size_t ) ;
            
            IHistogram_exposer.def( 
                "getXaxisValue"
                , getXaxisValue_function_type( &::IHistogram::getXaxisValue )
                , ( bp::arg("globalbin") )
                , "Returns the value on x-axis corresponding to the global bin index. @param binGlobalIndex The global bin index @return The center of axis's corresponding bin \n\n:Parameters:\n  - 'binGlobalIndex' - The global bin index\n" );
        
        }
        { //::IHistogram::getXmax
        
            typedef double ( ::IHistogram::*getXmax_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getXmax"
                , getXmax_function_type( &::IHistogram::getXmax )
                , "Returns x-axis max (upper edge of last bin)." );
        
        }
        { //::IHistogram::getXmin
        
            typedef double ( ::IHistogram::*getXmin_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getXmin"
                , getXmin_function_type( &::IHistogram::getXmin )
                , "Returns x-axis min (lower edge of first bin)." );
        
        }
        { //::IHistogram::getYaxis
        
            typedef ::IAxis const * ( ::IHistogram::*getYaxis_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getYaxis"
                , getYaxis_function_type( &::IHistogram::getYaxis )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "returns y-axis for 2D histograms." );
        
        }
        { //::IHistogram::getYaxisIndex
        
            typedef int ( ::IHistogram::*getYaxisIndex_function_type)( ::std::size_t ) const;
            
            IHistogram_exposer.def( 
                "getYaxisIndex"
                , getYaxisIndex_function_type( &::IHistogram::getYaxisIndex )
                , ( bp::arg("globalbin") )
                , "Returns x-axis bin index for given globalbin. For 1D histograms returned value conicide with globalbin value " );
        
        }
        { //::IHistogram::getYaxisValue
        
            typedef double ( ::IHistogram::*getYaxisValue_function_type)( ::std::size_t ) ;
            
            IHistogram_exposer.def( 
                "getYaxisValue"
                , getYaxisValue_function_type( &::IHistogram::getYaxisValue )
                , ( bp::arg("globalbin") )
                , "Returns the value on y-axis corresponding to the global bin index (for 2D histograms). @param globalbin The global bin index @return The center of axis's corresponding bin \n\n:Parameters:\n  - 'globalbin' - The global bin index\n" );
        
        }
        { //::IHistogram::getYmax
        
            typedef double ( ::IHistogram::*getYmax_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getYmax"
                , getYmax_function_type( &::IHistogram::getYmax )
                , "Returns y-axis max (upper edge of last bin) for 2D histograms." );
        
        }
        { //::IHistogram::getYmin
        
            typedef double ( ::IHistogram::*getYmin_function_type)(  ) const;
            
            IHistogram_exposer.def( 
                "getYmin"
                , getYmin_function_type( &::IHistogram::getYmin )
                , "Returns y-axis min (lower edge of first bin) for 2D histograms." );
        
        }
        { //::IHistogram::reset
        
            typedef void ( ::IHistogram::*reset_function_type)(  ) ;
            
            IHistogram_exposer.def( 
                "reset"
                , reset_function_type( &::IHistogram::reset )
                , "Reset histogram content (axes remains)." );
        
        }
        IHistogram_exposer.staticmethod( "createHistogram" );
    }

}

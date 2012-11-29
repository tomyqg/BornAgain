#ifndef IOUTPUTDATANORMALIZER_H
#define IOUTPUTDATANORMALIZER_H
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IOutputDataNormalizer.h
//! @brief  Definition of IOutputDataNormalizer class
//! @author Scientific Computing Group at FRM II
//! @date   26.11.2012

#include "IParameterized.h"
#include "OutputData.h"

/* ************************************************************************* */
// Normalize output data
/* ************************************************************************* */
class IOutputDataNormalizer : public IParameterized
{
public:
    virtual ~IOutputDataNormalizer() {}
    virtual IOutputDataNormalizer*clone() const=0;

    virtual OutputData<double> *createNormalizedData(const OutputData<double > &data) const=0;

};



class OutputDataNormalizerScaleAndShift : public IOutputDataNormalizer
{
public:
    OutputDataNormalizerScaleAndShift();
    OutputDataNormalizerScaleAndShift(double scale, double shift);
    OutputDataNormalizerScaleAndShift(const OutputDataNormalizerScaleAndShift &other);
    virtual ~OutputDataNormalizerScaleAndShift() {}

    virtual OutputData<double> *createNormalizedData(const OutputData<double > &data) const;

    virtual OutputDataNormalizerScaleAndShift *clone() const;

protected:
    //! initialize pool parameters, i.e. register some of class members for later access via parameter pool
    virtual void init_parameters();

private:
    // disable assignment operator
    OutputDataNormalizerScaleAndShift &operator=(const OutputDataNormalizerScaleAndShift &);

    double m_scale;
    double m_shift;
};



#endif // IOUTPUTDATANORMALIZER_H
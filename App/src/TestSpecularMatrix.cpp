// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      App/src/TestSpecularMatrix.cpp
//! @brief     Implements class TestSpecularMatrix.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "TestSpecularMatrix.h"

#include "SampleFactory.h"
#include "Units.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "DrawHelper.h"
#include "TH1F.h"
#include "TLegend.h"


TestSpecularMatrix::TestSpecularMatrix()
: mp_sample(0)
, mp_coeffs(0)
{
    std::cout << "TestSpecularMatrix::TestSpecularMatrix() -> Info." << std::endl;
}

void TestSpecularMatrix::execute()
{
    std::cout << "TestSpecularMatrix::execute() -> Info." << std::endl;

    // calculate amplitudes for several standard multi-layer samples
    test_standard_samples();
}

void TestSpecularMatrix::test_standard_samples()
{
    std::vector<std::string > snames;
    snames.push_back("MultilayerOffspecTestcase1a");

    // loop over standard samples defined in SampleFactory and StandardSamples
    for(size_t i_sample=0; i_sample<snames.size(); i_sample++){
        mp_sample = dynamic_cast<MultiLayer *>(SampleFactory::createSample(snames[i_sample]));

        mp_coeffs = new OutputData<SpecularMatrix::MultiLayerCoeff_t >;
        mp_coeffs->addAxis(std::string("alpha_i"), 2000, 0.0*Units::degree, 2.0*Units::degree);
        OutputData<SpecularMatrix::MultiLayerCoeff_t >::iterator it = mp_coeffs->begin();
        while (it != mp_coeffs->end()) {
            double alpha_i = mp_coeffs->getValueOfAxis("alpha_i", it.getIndex());
            kvector_t kvec;
            kvec.setLambdaAlphaPhi(1.54*Units::angstrom, -alpha_i, 0.0);

            SpecularMatrix::MultiLayerCoeff_t coeffs;
            SpecularMatrix matrixCalculator;
            matrixCalculator.execute(*mp_sample, kvec, coeffs);

            *it = coeffs;
            ++it;

        } // alpha_i

        draw_standard_samples();

        delete mp_sample;
        delete mp_coeffs;
    } // i_sample
}

void TestSpecularMatrix::draw_standard_samples()
{
    static int ncall = 0;

    size_t nlayers = mp_sample->getNumberOfLayers();

    // graphics for R,T coefficients in layers as a function of alpha_i
    size_t ncoeffs = 2;
    enum key_coeffs { kCoeffR, kCoeffT};
    const char *coeffs_title[]={" |R| "," |T| "};
    int coeffs_color[] = {kBlue, kRed};

    std::vector<std::vector<TGraph *> > gr_coeff; // [nlayers][ncoeffs]
    gr_coeff.resize(nlayers);
    for(size_t i_layer=0; i_layer<nlayers; i_layer++) {
        gr_coeff[i_layer].resize(ncoeffs,0);
        for(size_t i_coeff=0; i_coeff<ncoeffs; i_coeff++) {
            gr_coeff[i_layer][i_coeff] = new TGraph();
        }
    }
    TGraph *gr_absSum = new TGraph(); // |R_top|+|T_bottom|

    OutputData<SpecularMatrix::MultiLayerCoeff_t >::const_iterator it = mp_coeffs->begin();
    int i_point = 0;
    while (it != mp_coeffs->end()) {
        double alpha_i = mp_coeffs->getValueOfAxis("alpha_i", it.getIndex());
        const SpecularMatrix::MultiLayerCoeff_t coeffs = *it++;

        // Filling graphics for R,T as a function of alpha_i
        for(size_t i_layer=0; i_layer<nlayers; ++i_layer ) {
            gr_coeff[i_layer][kCoeffR]->SetPoint(i_point, Units::rad2deg(alpha_i), std::abs(coeffs[i_layer].R()) );
            gr_coeff[i_layer][kCoeffT]->SetPoint(i_point, Units::rad2deg(alpha_i), std::abs(coeffs[i_layer].T()) );
        }

        // Filling graphics for |R|+|T| as a function of alpha_i taking R from the top and T from the bottom layers
        int nlast = (int)nlayers - 1;
        double sum;
        if(coeffs[0].lambda.real()!=0.0) {
            sum = std::norm(coeffs[0].R()) + std::norm(coeffs[nlast].T())*coeffs[nlast].lambda.real()/coeffs[0].lambda.real();
        } else {
            sum = 1.0;
            std::cout << "Re(k_{z,0}) = 0 for alpha_i = " << alpha_i << std::endl;
            std::cout << " and Re(k_{z,N+1}) = " << coeffs[nlast].lambda.real() << std::endl;
        }
        gr_absSum->SetPoint(i_point++, Units::rad2deg(alpha_i), sum);
    }

    // create name of canvas different for each new call of this method
    std::ostringstream os;
    os << (ncall++) << std::endl;
    std::string cname = std::string("c1_test_Fresnel_sample")+os.str();
    TCanvas *c1 = new TCanvas(cname.c_str(),"Fresnel Coefficients in Multilayer",1024,768);
    DrawHelper::SetMagnifier(c1);

    // estimate subdivision of canvas (we need place for 'nlayers' and for one sample picture)
    int ndiv(2);
    if( nlayers+1 > 4 ) ndiv = int(sqrt(nlayers+1)+1);
    c1->Divide(ndiv,ndiv);

    for(size_t i_layer=0; i_layer<nlayers; i_layer++) {
        c1->cd((int)i_layer+1);
        gPad->SetLogy();

        // calculating histogram limits common for all graphs on given pad
        double xmin(0), ymin(0), xmax(0), ymax(0);
        for(size_t i_coeff=0; i_coeff<ncoeffs; i_coeff++){
            double x1(0), y1(0), x2(0), y2(0);
            gr_coeff[i_layer][kCoeffT]->ComputeRange(x1, y1, x2, y2);
            if(x1 < xmin ) xmin= x1;
            if(x2 > xmax ) xmax = x2;
            if(y1 < ymin ) ymin = y1;
            if(y2 > ymax ) ymax = y2;
        }
        TH1F h1ref("h1ref","h1ref",100, xmin, xmax);
        h1ref.SetMinimum(1e-6);
        h1ref.SetMaximum(10);
        h1ref.SetStats(0);
        h1ref.SetTitle("");
        h1ref.GetXaxis()->SetTitle("angle, deg");
        h1ref.GetYaxis()->SetTitle("|R|, |T|");
        h1ref.DrawCopy();

        TLegend *leg = new TLegend(0.725,0.7,0.89,0.88);
        leg->SetTextSize(0.04);
        leg->SetBorderSize(1);
        leg->SetFillStyle(0);
        std::ostringstream os;
        os << " layer #" << i_layer;
        leg->SetHeader(os.str().c_str());

        for(size_t i_coeff=0; i_coeff<ncoeffs; i_coeff++) {
            TGraph *gr = gr_coeff[i_layer][i_coeff];
            gr->SetLineColor( coeffs_color[i_coeff] );
            gr->SetMarkerColor( coeffs_color[i_coeff] );
            gr->SetMarkerStyle(21);
            gr->SetMarkerSize(0.2);
            gr->Draw("pl same");
            leg->AddEntry(gr, coeffs_title[i_coeff],"pl");
        }
        leg->Draw();
    }
    TGraph *gr = gr_absSum;
    gr->SetMarkerStyle(21);
    gr->SetMarkerSize(0.2);
    gr->SetLineColor(kMagenta);
    gr->SetMarkerColor(kMagenta);
    gr->Draw("pl same");
    TLegend *leg = new TLegend(0.625,0.6,0.89,0.69);
    leg->SetTextSize(0.04);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->AddEntry(gr, "|R_top|+|T_bottom|","pl");
    leg->Draw();

    // drawing sample geometry
    c1->cd((int)nlayers+1);
    DrawHelper::DrawMultilayer(mp_sample);
}
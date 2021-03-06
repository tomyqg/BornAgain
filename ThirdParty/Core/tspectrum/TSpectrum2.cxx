// @(#)root/spectrum:$Id$
// Author: Miroslav Morhac   17/01/2006

/** \class TSpectrum2
    \ingroup Spectrum
    \brief Advanced 2-dimensional spectra processing
    \author Miroslav Morhac

 This class contains advanced spectra processing functions.

  - One-dimensional background estimation functions
  - Two-dimensional background estimation functions
  - One-dimensional smoothing functions
  - Two-dimensional smoothing functions
  - One-dimensional deconvolution functions
  - Two-dimensional deconvolution functions
  - One-dimensional peak search functions
  - Two-dimensional peak search functions

 The algorithms in this class have been published in the following references:

 1.  M.Morhac et al.: Background elimination methods for multidimensional coincidence gamma-ray spectra. Nuclear Instruments and Methods in Physics Research A 401 (1997) 113-132.
 2.  M.Morhac et al.: Efficient one- and two-dimensional Gold deconvolution and its application to gamma-ray spectra decomposition. Nuclear Instruments and Methods in Physics Research A 401 (1997) 385-408.
 3.  M.Morhac et al.: Identification of peaks in multidimensional coincidence gamma-ray spectra. Nuclear Instruments and Methods in Research Physics A 443(2000), 108-125.

 These NIM papers are also available as doc or ps files from:

 - [SpectrumDec.ps.gz](ftp://root.cern.ch/root/SpectrumDec.ps.gz)
 - [SpectrumSrc.ps.gz](ftp://root.cern.ch/root/SpectrumSrc.ps.gz)
 - [SpectrumBck.ps.gz](ftp://root.cern.ch/root/SpectrumBck.ps.gz)

 See also the
 [online documentation](https://root.cern.ch/guides/tspectrum-manual) and
 [tutorials](https://root.cern.ch/doc/master/group__tutorial__spectrum.html).

 All the figures in this page were prepared using the DaqProVis
 system, Data Acquisition, Processing and Visualization system,
 developed at the Institute of Physics, Slovak Academy of Sciences, Bratislava,
 Slovakia.
*/

#include "TSpectrum2.h"
#include <cmath>
#include <stdexcept>
#include <algorithm>

#define PEAK_WINDOW 1024

using namespace tspectrum;

Int_t TSpectrum2::fgIterations    = 3;
Int_t TSpectrum2::fgAverageWindow = 3;


namespace {
const std::string s_nobackground = "nobackground";
const std::string s_nomarkov = "nomarkov";
const std::string s_log = "log";
}

////////////////////////////////////////////////////////////////////////////////
/// Constructor.

TSpectrum2::TSpectrum2()
{
   Int_t n = 100;
   fMaxPeaks   = n;
   fPosition   = new Double_t[static_cast<size_t>(n)];
   fPositionX  = new Double_t[static_cast<size_t>(n)];
   fPositionY  = new Double_t[static_cast<size_t>(n)];
   fResolution = 1;
//   fHistogram  = 0;
   fNPeaks     = 0;
}

////////////////////////////////////////////////////////////////////////////////
///  - maxpositions:  maximum number of peaks
///  - resolution:    *NOT USED* determines resolution of the neighbouring peaks
///                   default value is 1 correspond to 3 sigma distance
///                   between peaks. Higher values allow higher resolution
///                   (smaller distance between peaks.
///                   May be set later through SetResolution.

TSpectrum2::TSpectrum2(Int_t maxpositions, Double_t resolution)
{
   Int_t n = maxpositions;
   fMaxPeaks  = n;
   fPosition  = new Double_t[static_cast<size_t>(n)];
   fPositionX = new Double_t[static_cast<size_t>(n)];
   fPositionY = new Double_t[static_cast<size_t>(n)];
//   fHistogram = 0;
   fNPeaks    = 0;
   SetResolution(resolution);
}

////////////////////////////////////////////////////////////////////////////////
/// Destructor.

TSpectrum2::~TSpectrum2()
{
   delete [] fPosition;
   delete [] fPositionX;
   delete [] fPositionY;
//   delete    fHistogram;
}

////////////////////////////////////////////////////////////////////////////////
/// static function: Set average window of searched peaks
/// see TSpectrum2::SearchHighRes

void TSpectrum2::SetAverageWindow(Int_t w)
{
   fgAverageWindow = w;
}

////////////////////////////////////////////////////////////////////////////////
/// static function: Set max number of decon iterations in deconvolution operation
/// see TSpectrum2::SearchHighRes

void TSpectrum2::SetDeconIterations(Int_t n)
{
   fgIterations = n;
}

////////////////////////////////////////////////////////////////////////////////
///   This function calculates the background spectrum in the input histogram h.
///   The background is returned as a histogram.
///
///   Function parameters:
///   - h: input 2-d histogram
///   - numberIterations, (default value = 20)
///     Increasing numberIterations make the result smoother and lower.
///   - option: may contain one of the following options
///      - to set the direction parameter
///        "BackIncreasingWindow". By default the direction is BackDecreasingWindow
///      - filterOrder-order of clipping filter. Possible values:
///            - "BackOrder2" (default)
///            - "BackOrder4"
///            - "BackOrder6"
///            - "BackOrder8"
///      - "nosmoothing"- if selected, the background is not smoothed
///         By default the background is smoothed.
///      - smoothWindow-width of smoothing window. Possible values:
///            - "BackSmoothing3" (default)
///            - "BackSmoothing5"
///            - "BackSmoothing7"
///            - "BackSmoothing9"
///            - "BackSmoothing11"
///            - "BackSmoothing13"
///            - "BackSmoothing15"
///      - "Compton" if selected the estimation of Compton edge
///                  will be included.
///      - "same" : if this option is specified, the resulting background
///                 histogram is superimposed on the picture in the current pad.
///
///  NOTE that the background is only evaluated in the current range of h.
///  ie, if h has a bin range (set via h->GetXaxis()->SetRange(binmin,binmax),
///  the returned histogram will be created with the same number of bins
///  as the input histogram h, but only bins from binmin to binmax will be filled
///  with the estimated background.

//TH1 *TSpectrum2::Background(const TH1 * h, Int_t number_of_iterations,
//                                   Option_t * option)
//{
//   Error("Background","function not yet implemented: h=%s, iter=%d, option=%sn"
//        , h->GetName(), number_of_iterations, option);
//   return 0;
//}

////////////////////////////////////////////////////////////////////////////////
/// Print the array of positions.

//void TSpectrum2::Print(Option_t *) const
//{
//   printf("\nNumber of positions = %d\n",fNPeaks);
//   for (Int_t i=0;i<fNPeaks;i++) {
//      printf(" x[%d] = %g, y[%d] = %g\n",i,fPositionX[i],i,fPositionY[i]);
//   }
//}

////////////////////////////////////////////////////////////////////////////////
///   This function searches for peaks in source spectrum in hin
///   The number of found peaks and their positions are written into
///   the members fNpeaks and fPositionX.
///   The search is performed in the current histogram range.
///
///   Function parameters:
///  - hin:       pointer to the histogram of source spectrum
///  - sigma:   sigma of searched peaks, for details we refer to manual
///  - threshold: (default=0.05)  peaks with amplitude less than
///    threshold*highest_peak are discarded.  0<threshold<1
///
///   By default, the background is removed before deconvolution.
///   Specify the option "nobackground" to not remove the background.
///
///   By default the "Markov" chain algorithm is used.
///   Specify the option "noMarkov" to disable this algorithm
///   Note that by default the source spectrum is replaced by a new spectrum
///
///   By default a polymarker object is created and added to the list of
///   functions of the histogram. The histogram is drawn with the specified
///   option and the polymarker object drawn on top of the histogram.
///   The polymarker coordinates correspond to the npeaks peaks found in
///   the histogram.
///   A pointer to the polymarker object can be retrieved later via:
/// ~~~ {.cpp}
///    TList *functions = hin->GetListOfFunctions();
///    TPolyMarker *pm = (TPolyMarker*)functions->FindObject("TPolyMarker")
/// ~~~
///   Specify the option "goff" to disable the storage and drawing of the
///   polymarker.

Int_t TSpectrum2::Search(const vec2d& hist, Double_t sigma,
                             const std::string& option, Double_t threshold)
{
    std::string opt = option;
    std::transform(opt.begin(), opt.end(), opt.begin(), ::tolower);

    Bool_t background = kTRUE;
    size_t pos = opt.find(s_nobackground);
    if (pos != std::string::npos) {
        background = kFALSE;
        opt.erase(pos, s_nobackground.size());
    }

    Bool_t markov = kTRUE;
    pos = opt.find(s_nomarkov);
    if (pos != std::string::npos) {
        markov = kFALSE;
        opt.erase(pos, s_nomarkov.size());
    }

    Bool_t apply_log = kFALSE;
    pos = opt.find(s_log);
    if (pos != std::string::npos) {
        apply_log = kTRUE;
        opt.erase(pos, s_log.size());
    }

    if (!opt.empty())
        throw std::runtime_error("Cant's parse '" + option +"', remainder '" + opt+"'");

   Int_t sizex = static_cast<int>(hist.size());
   Int_t sizey = static_cast<int>(hist[0].size());
   Int_t i, j, npeaks;
   Double_t ** source = new Double_t*[static_cast<size_t>(sizex)];
   Double_t ** dest   = new Double_t*[static_cast<size_t>(sizex)];
   for (i = 0; i < sizex; i++) {
      source[i] = new Double_t[static_cast<size_t>(sizey)];
      dest[i]   = new Double_t[static_cast<size_t>(sizey)];
      for (j = 0; j < sizey; j++) {
          double value = hist[static_cast<size_t>(i)][static_cast<size_t>(j)];
          source[i][j] = apply_log ? std::log(value) : value;
      }
   }
   //npeaks = SearchHighRes(source, dest, sizex, sizey, sigma, 100*threshold, kTRUE, 3, kTRUE, 10);
   //the smoothing option is used for 1-d but not for 2-d histograms
   npeaks = SearchHighRes(source, dest, sizex, sizey, sigma, 100*threshold,  background, fgIterations, markov, fgAverageWindow);

   for (i = 0; i < sizex; i++) {
      delete [] source[i];
      delete [] dest[i];
   }
   delete [] source;
   delete [] dest;

   return npeaks;
}

////////////////////////////////////////////////////////////////////////////////
/// *NOT USED*
///  resolution: determines resolution of the neighboring peaks
///              default value is 1 correspond to 3 sigma distance
///              between peaks. Higher values allow higher resolution
///              (smaller distance between peaks.
///              May be set later through SetResolution.

void TSpectrum2::SetResolution(Double_t resolution)
{
   if (resolution > 1)
      fResolution = resolution;
   else
      fResolution = 1;
}

////////////////////////////////////////////////////////////////////////////////
///   This function calculates background spectrum from source spectrum.
///   The result is placed to the array pointed by spectrum pointer.
///
///   Function parameters:
///  - spectrum-pointer to the array of source spectrum
///  - ssizex-x length of spectrum
///  - ssizey-y length of spectrum
///  - numberIterationsX-maximal x width of clipping window
///  - numberIterationsY-maximal y width of clipping window
///                           for details we refer to manual
///  - direction- direction of change of clipping window
///               - possible values=kBackIncreasingWindow
///                                 kBackDecreasingWindow
///  - filterType-determines the algorithm of the filtering
///               - possible values=kBackSuccessiveFiltering
///                                 kBackOneStepFiltering
///
/// ### Background estimation
///
/// Goal: Separation of useful information (peaks) from useless information (background)
///
///  - method is based on Sensitive Nonlinear Iterative Peak (SNIP) clipping algorithm [1]
///
///  - there exist two algorithms for the estimation of new value in the channel \f$ i_1,i_2\f$
///
/// Algorithm based on Successive Comparisons:
///
/// It is an extension of one-dimensional SNIP algorithm to another dimension. For
/// details we refer to [2].
///
/// Algorithm based on One Step Filtering:
///
/// New value in the estimated channel is calculated as:
/// \f[ a = \nu_{p-1}(i_1,i_2)\f]
/// \f[
/// b = \frac{\nu_{p-1}(i_1-p,i_2-p) - 2\nu_{p-1}(i_1-p,i_2) + \nu_{p-1}(i_1-p,i_2+p) - 2\nu_{p-1}(i_1,i_2-p)}{4} +
/// \f]
/// \f[
/// \frac{-2\nu_{p-1}(i_1,i_2+p) + \nu_{p-1}(i_1+p,i_2-p) - 2\nu_{p-1}(i_1+p,i_2) + \nu_{p-1}(i_1+p,i_2+p)}{4}
/// \f]
/// \f[ \nu_{p-1}(i_1,i_2) = min(a,b)\f]
/// where p = 1, 2, ..., number_of_iterations.
///
/// #### References:
///
/// [1] C. G Ryan et al.: SNIP, a statistics-sensitive background treatment for the
/// quantitative analysis of PIXE spectra in geoscience applications. NIM, B34 (1988), 396-402.
///
/// [2] M. Morhac;, J. Kliman, V.
/// Matouoek, M. Veselsky, I. Turzo.:
/// Background elimination methods for multidimensional gamma-ray spectra. NIM,
/// A401 (1997) 113-132.
///
/// ### Example 1 - script Back_gamma64.c
///
/// \image html TSpectrum2_Background1.jpg Fig. 1 Original two-dimensional gamma-gamma-ray spectrum
/// \image html TSpectrum2_Background2.jpg Fig. 2 Background estimated from data from Fig. 1 using decreasing clipping window with widths 4, 4 and algorithm based on successive comparisons. The estimate includes not only continuously changing background but also one-dimensional ridges.
/// \image html TSpectrum2_Background3.jpg Fig. 3 Resulting peaks after subtraction of the estimated background (Fig. 2) from original two-dimensional gamma-gamma-ray spectrum (Fig. 1).
///
/// #### Script:
///
/// Example to illustrate the background estimator (class TSpectrum). To execute this example, do:
///
/// `root > .x Back_gamma64.C`
///
/// ~~~ {.cpp}
///   #include <TSpectrum>
///   void Back_gamma64() {
///      Int_t i, j;
///      Double_t nbinsx = 64;
///      Double_t nbinsy = 64;
///      Double_t xmin = 0;
///      Double_t xmax = (Double_t)nbinsx;
///      Double_t ymin = 0;
///      Double_t ymax = (Double_t)nbinsy;
///      Double_t ** source = new Double_t*[nbinsx];
///      for (i=0;i<nbinsx;i++)
///         source[i]=new Double_t[nbinsy];
///      TH2F *back = new TH2F("back","Background estimation",nbinsx,xmin,xmax,nbinsy,ymin,ymax);
///      TFile *f = new TFile("spectra2/TSpectrum2.root");
///      back=(TH2F*) f->Get("back1;1");
///      TCanvas *Background = new TCanvas("Background","Estimation of background with increasing window",10,10,1000,700);
///      TSpectrum *s = new TSpectrum();
///      for (i = 0; i < nbinsx; i++){
///         for (j = 0; j < nbinsy; j++){
///            source[i][j] = back->GetBinContent(i + 1,j + 1);
///         }
///      }
///      s->Background(source,nbinsx,nbinsy,4,4,kBackDecreasingWindow,kBackSuccessiveFiltering);
///      for (i = 0; i < nbinsx; i++){
///         for (j = 0; j < nbinsy; j++)
///            back->SetBinContent(i + 1,j + 1, source[i][j]);
///      }
///      back->Draw("SURF");
///   }
/// ~~~
///
/// ### Example 2- script Back_gamma256.c
///
/// \image html TSpectrum2_Background4.jpg Fig. 4 Original two-dimensional gamma-gamma-ray spectrum 256x256 channels
/// \image html TSpectrum2_Background5.jpg Fig. 5 Peaks after subtraction of the estimated background (increasing clipping window with widths 8, 8 and algorithm based on successive comparisons) from original two-dimensional gamma-gamma-ray spectrum (Fig. 4).
///
/// #### Script:
///
// Example to illustrate the background estimator (class TSpectrum).
/// To execute this example, do
///
/// `root > .x Back_gamma256.C`
///
/// ~~~ {.cpp}
///   #include <TSpectrum>
///   void Back_gamma256() {
///      Int_t i, j;
///      Double_t nbinsx = 64;
///      Double_t nbinsy = 64;
///      Double_t xmin = 0;
///      Double_t xmax = (Double_t)nbinsx;
///      Double_t ymin = 0;
///      Double_t ymax = (Double_t)nbinsy;
///      Double_t** source = new Double_t*[nbinsx];
///      for (i=0;i<nbinsx;i++)
///         source[i]=new Double_t[nbinsy];
///      TH2F *back = new TH2F("back","Background estimation",nbinsx,xmin,xmax,nbinsy,ymin,ymax);
///      TFile *f = new TFile("spectra2/TSpectrum2.root");
///      back=(TH2F*) f->Get("back2;1");
///      TCanvas *Background = new TCanvas("Background","Estimation of background with increasing window",10,10,1000,700);
///      TSpectrum *s = new TSpectrum();
///      for (i = 0; i < nbinsx; i++){
///         for (j = 0; j < nbinsy; j++){
///            source[i][j] = back->GetBinContent(i + 1,j + 1);
///         }
///      }
///      s->Background(source,nbinsx,nbinsy,8,8,kBackIncreasingWindow,kBackSuccessiveFiltering);
///      for (i = 0; i < nbinsx; i++){
///         for (j = 0; j < nbinsy; j++)
///            back->SetBinContent(i + 1,j + 1, source[i][j]);
///      }
///      back->Draw("SURF");
///   }
/// ~~~
///
/// Example 3- script Back_synt256.c
///
/// \image html TSpectrum2_Background6.jpg Fig. 6 Original two-dimensional synthetic spectrum 256x256 channels
/// \image html TSpectrum2_Background7.jpg Fig. 7 Peaks after subtraction of the estimated background (increasing clipping window with widths 8, 8 and algorithm based on successive comparisons) from original two-dimensional gamma-gamma-ray spectrum (Fig. 6). One can observe artefacts (ridges) around the peaks due to the employed algorithm.
/// \image html TSpectrum2_Background8.jpg Fig. 8 Peaks after subtraction of the estimated background (increasing clipping window with widths 8, 8 and algorithm based on one step filtering) from original two-dimensional gamma-gamma-ray spectrum (Fig. 6). The artefacts from the above given Fig. 7 disappeared.
///
/// #### Script:
///
/// Example to illustrate the background estimator (class TSpectrum).
/// To execute this example, do
///
/// `root > .x Back_synt256.C`
///
/// ~~~ {.cpp}
///   #include <TSpectrum>
///   void Back_synt256() {
///      Int_t i, j;
///      Double_t nbinsx = 64;
///      Double_t nbinsy = 64;
///      Double_t xmin = 0;
///      Double_t xmax = (Double_t)nbinsx;
///      Double_t ymin = 0;
///      Double_t ymax = (Double_t)nbinsy;
///      Double_t** source = new Double_t*[nbinsx];
///      for (i=0;i<nbinsx;i++)
///         source[i]=new Double_t[nbinsy];
///      TH2F *back = new TH2F("back","Background estimation",nbinsx,xmin,xmax,nbinsy,ymin,ymax);
///      TFile *f = new TFile("spectra2/TSpectrum2.root");
///      back=(TH2F*) f->Get("back3;1");
///      TCanvas *Background = new TCanvas("Background","Estimation of background with increasing window",10,10,1000,700);
///      TSpectrum *s = new TSpectrum();
///      for (i = 0; i < nbinsx; i++){
///         for (j = 0; j < nbinsy; j++){
///            source[i][j] = back->GetBinContent(i + 1,j + 1);
///         }
///      }
///      s->Background(source,nbinsx,nbinsy,8,8,
///                    kBackIncreasingWindow,kBackSuccessiveFiltering);//kBackOneStepFiltering
///      for (i = 0; i < nbinsx; i++){
///         for (j = 0; j < nbinsy; j++)
///            back->SetBinContent(i + 1,j + 1, source[i][j]);
///      }
///      back->Draw("SURF");
///   }
/// ~~~

const char *TSpectrum2::Background(Double_t **spectrum,
                       Int_t ssizex, Int_t ssizey,
                       Int_t numberIterationsX,
                       Int_t numberIterationsY,
                       Int_t direction,
                       Int_t filterType)
{
   Int_t i, x, y, sampling, r1, r2;
   Double_t a, b, p1, p2, p3, p4, s1, s2, s3, s4;
   if (ssizex <= 0 || ssizey <= 0)
      return "Wrong parameters";
   if (numberIterationsX < 1 || numberIterationsY < 1)
      return "Width of Clipping Window Must Be Positive";
   if (ssizex < 2 * numberIterationsX + 1
        || ssizey < 2 * numberIterationsY + 1)
      return ("Too Large Clipping Window");
   Double_t **working_space = new Double_t*[ssizex];
   for (i = 0; i < ssizex; i++)
      working_space[i] = new Double_t[ssizey];
   sampling =
       (Int_t) std::max(numberIterationsX, numberIterationsY);
   if (direction == kBackIncreasingWindow) {
      if (filterType == kBackSuccessiveFiltering) {
         for (i = 1; i <= sampling; i++) {
            r1 = (Int_t) std::min(i, numberIterationsX), r2 =
                (Int_t) std::min(i, numberIterationsY);
            for (y = r2; y < ssizey - r2; y++) {
               for (x = r1; x < ssizex - r1; x++) {
                  a = spectrum[x][y];
                  p1 = spectrum[x - r1][y - r2];
                  p2 = spectrum[x - r1][y + r2];
                  p3 = spectrum[x + r1][y - r2];
                  p4 = spectrum[x + r1][y + r2];
                  s1 = spectrum[x][y - r2];
                  s2 = spectrum[x - r1][y];
                  s3 = spectrum[x + r1][y];
                  s4 = spectrum[x][y + r2];
                  b = (p1 + p2) / 2.0;
                  if (b > s2)
                     s2 = b;
                  b = (p1 + p3) / 2.0;
                  if (b > s1)
                     s1 = b;
                  b = (p2 + p4) / 2.0;
                  if (b > s4)
                     s4 = b;
                  b = (p3 + p4) / 2.0;
                  if (b > s3)
                     s3 = b;
                  s1 = s1 - (p1 + p3) / 2.0;
                  s2 = s2 - (p1 + p2) / 2.0;
                  s3 = s3 - (p3 + p4) / 2.0;
                  s4 = s4 - (p2 + p4) / 2.0;
                  b = (s1 + s4) / 2.0 + (s2 + s3) / 2.0 + (p1 + p2 +
                                                            p3 +
                                                            p4) / 4.0;
                  if (b < a && b > 0)
                     a = b;
                  working_space[x][y] = a;
               }
            }
            for (y = r2; y < ssizey - r2; y++) {
               for (x = r1; x < ssizex - r1; x++) {
                  spectrum[x][y] = working_space[x][y];
               }
            }
         }
      }

      else if (filterType == kBackOneStepFiltering) {
         for (i = 1; i <= sampling; i++) {
            r1 = (Int_t) std::min(i, numberIterationsX), r2 =
                (Int_t) std::min(i, numberIterationsY);
            for (y = r2; y < ssizey - r2; y++) {
               for (x = r1; x < ssizex - r1; x++) {
                  a = spectrum[x][y];
                  b = -(spectrum[x - r1][y - r2] +
                         spectrum[x - r1][y + r2] + spectrum[x + r1][y -
                                                                     r2]
                         + spectrum[x + r1][y + r2]) / 4 +
                      (spectrum[x][y - r2] + spectrum[x - r1][y] +
                       spectrum[x + r1][y] + spectrum[x][y + r2]) / 2;
                  if (b < a && b > 0)
                     a = b;
                  working_space[x][y] = a;
               }
            }
            for (y = i; y < ssizey - i; y++) {
               for (x = i; x < ssizex - i; x++) {
                  spectrum[x][y] = working_space[x][y];
               }
            }
         }
      }
   }

   else if (direction == kBackDecreasingWindow) {
      if (filterType == kBackSuccessiveFiltering) {
         for (i = sampling; i >= 1; i--) {
            r1 = (Int_t) std::min(i, numberIterationsX), r2 =
                (Int_t) std::min(i, numberIterationsY);
            for (y = r2; y < ssizey - r2; y++) {
               for (x = r1; x < ssizex - r1; x++) {
                  a = spectrum[x][y];
                  p1 = spectrum[x - r1][y - r2];
                  p2 = spectrum[x - r1][y + r2];
                  p3 = spectrum[x + r1][y - r2];
                  p4 = spectrum[x + r1][y + r2];
                  s1 = spectrum[x][y - r2];
                  s2 = spectrum[x - r1][y];
                  s3 = spectrum[x + r1][y];
                  s4 = spectrum[x][y + r2];
                  b = (p1 + p2) / 2.0;
                  if (b > s2)
                     s2 = b;
                  b = (p1 + p3) / 2.0;
                  if (b > s1)
                     s1 = b;
                  b = (p2 + p4) / 2.0;
                  if (b > s4)
                     s4 = b;
                  b = (p3 + p4) / 2.0;
                  if (b > s3)
                     s3 = b;
                  s1 = s1 - (p1 + p3) / 2.0;
                  s2 = s2 - (p1 + p2) / 2.0;
                  s3 = s3 - (p3 + p4) / 2.0;
                  s4 = s4 - (p2 + p4) / 2.0;
                  b = (s1 + s4) / 2.0 + (s2 + s3) / 2.0 + (p1 + p2 +
                                                            p3 +
                                                            p4) / 4.0;
                  if (b < a && b > 0)
                     a = b;
                  working_space[x][y] = a;
               }
            }
            for (y = r2; y < ssizey - r2; y++) {
               for (x = r1; x < ssizex - r1; x++) {
                  spectrum[x][y] = working_space[x][y];
               }
            }
         }
      }

      else if (filterType == kBackOneStepFiltering) {
         for (i = sampling; i >= 1; i--) {
            r1 = (Int_t) std::min(i, numberIterationsX), r2 =
                (Int_t) std::min(i, numberIterationsY);
            for (y = r2; y < ssizey - r2; y++) {
               for (x = r1; x < ssizex - r1; x++) {
                  a = spectrum[x][y];
                  b = -(spectrum[x - r1][y - r2] +
                         spectrum[x - r1][y + r2] + spectrum[x + r1][y -
                                                                     r2]
                         + spectrum[x + r1][y + r2]) / 4 +
                      (spectrum[x][y - r2] + spectrum[x - r1][y] +
                       spectrum[x + r1][y] + spectrum[x][y + r2]) / 2;
                  if (b < a && b > 0)
                     a = b;
                  working_space[x][y] = a;
               }
            }
            for (y = i; y < ssizey - i; y++) {
               for (x = i; x < ssizex - i; x++) {
                  spectrum[x][y] = working_space[x][y];
               }
            }
         }
      }
   }
   for (i = 0; i < ssizex; i++)
      delete[]working_space[i];
   delete[]working_space;
   return 0;
}

////////////////////////////////////////////////////////////////////////////////
/// This function calculates smoothed spectrum from source spectrum
/// based on Markov chain method.
/// The result is placed in the array pointed by source pointer.
///
/// Function parameters:
///  - source-pointer to the array of source spectrum
///  - ssizex-x length of source
///  - ssizey-y length of source
///  - averWindow-width of averaging smoothing window
///
/// ### Smoothing
///
/// Goal: Suppression of statistical fluctuations the algorithm is based on discrete
/// Markov chain, which has very simple invariant distribution
/// \f[
/// U_2 = \frac{p_{1.2}}{p_{2,1}}U_1, U_3 = \frac{p_{2,3}}{p_{3,2}}U_2 U_1, ... , U_n = \frac{p_{n-1,n}}{p_{n,n-1}}U_{n-1} ... U_2 U_1
/// \f]
/// \f$U_1\f$ being defined from the normalization condition \f$ \sum_{i=1}^{n} U_i = 1\f$
/// n is the length of the smoothed spectrum and
/// \f[
/// p_{i,i\pm1} = A_i \sum_{k=1}^{m} exp\left[\frac{y(i\pm k)-y(i)}{y(i\pm k)+y(i)}\right]
/// \f]
/// is the probability of the change of the peak position from channel i to the channel i+1.
/// \f$A_i\f$ is the normalization constant so that\f$ p_{i,i-1}+p_{i,i+1}=1\f$ and m is a width
/// of smoothing window. We have extended this algorithm to two dimensions.
///
/// #### Reference:
///
/// [1] Z.K. Silagadze, A new algorithm for automatic photopeak searches. NIM A 376 (1996), 451.
///
/// ### Example 4 - script Smooth.c
///
/// \image html TSpectrum2_Smoothing1.jpg Fig. 9 Original noisy spectrum.
/// \image html TSpectrum2_Smoothing2.jpg Fig. 10 Smoothed spectrum m=3 Peaks can hardly be observed. Peaks become apparent.
/// \image html TSpectrum2_Smoothing3.jpg Fig. 11 Smoothed spectrum m=5
/// \image html TSpectrum2_Smoothing4.jpg Fig.12 Smoothed spectrum m=7
///
/// #### Script:
///
/// Example to illustrate the Markov smoothing (class TSpectrum).
/// To execute this example, do
///
/// `root > .x Smooth.C`
///
/// ~~~ {.cpp}
///   #include <TSpectrum>
///   void Smooth() {
///      Int_t i, j;
///      Double_t nbinsx = 256;
///      Double_t nbinsy = 256;
///      Double_t xmin = 0;
///      Double_t xmax = (Double_t)nbinsx;
///      Double_t ymin = 0;
///      Double_t ymax = (Double_t)nbinsy;
///      Double_t** source = new Double_t*[nbinsx];
///      for (i=0;i<nbinsx;i++)
///         source[i] = new Double_t[nbinsy];
///      TH2F *smooth = new TH2F("smooth","Background estimation",nbinsx,xmin,xmax,nbinsy,ymin,ymax);
///      TFile *f = new TFile("spectra2/TSpectrum2.root");
///      smooth=(TH2F*) f->Get("smooth1;1");
///      TCanvas *Smoothing = new TCanvas("Smoothing","Markov smoothing",10,10,1000,700);
///      TSpectrum *s = new TSpectrum();
///      for (i = 0; i < nbinsx; i++){
///         for (j = 0; j < nbinsy; j++){
///            source[i][j] = smooth->GetBinContent(i + 1,j + 1);
///         }
///      }
///      s->SmoothMarkov(source,nbinsx,nbinsx,3); //5,7
///      for (i = 0; i < nbinsx; i++){
///         for (j = 0; j < nbinsy; j++)
///            smooth->SetBinContent(i + 1,j + 1, source[i][j]);
///      }
///      smooth->Draw("SURF");
///   }
/// ~~~

const char* TSpectrum2::SmoothMarkov(Double_t **source, Int_t ssizex, Int_t ssizey, Int_t averWindow)
{

   Int_t xmin, xmax, ymin, ymax, i, j, l;
   Double_t a, b, maxch;
   Double_t nom, nip, nim, sp, sm, spx, spy, smx, smy, plocha = 0;
   if(averWindow <= 0)
      return "Averaging Window must be positive";
   Double_t **working_space = new Double_t*[ssizex];
   for(i = 0; i < ssizex; i++)
      working_space[i] = new Double_t[ssizey];
   xmin = 0;
   xmax = ssizex - 1;
   ymin = 0;
   ymax = ssizey - 1;
   for(i = 0, maxch = 0; i < ssizex; i++){
      for(j = 0; j < ssizey; j++){
         working_space[i][j] = 0;
         if(maxch < source[i][j])
            maxch = source[i][j];

         plocha += source[i][j];
      }
   }
   if(maxch == 0) {
      delete [] working_space;
      return 0;
   }

   nom = 0;
   working_space[xmin][ymin] = 1;
   for(i = xmin; i < xmax; i++){
      nip = source[i][ymin] / maxch;
      nim = source[i + 1][ymin] / maxch;
      sp = 0,sm = 0;
      for(l = 1; l <= averWindow; l++){
         if((i + l) > xmax)
            a = source[xmax][ymin] / maxch;

         else
            a = source[i + l][ymin] / maxch;
         b = a - nip;
         if(a + nip <= 0)
            a = 1;

         else
            a = std::sqrt(a + nip);
         b = b / a;
         b = std::exp(b);
         sp = sp + b;
         if(i - l + 1 < xmin)
            a = source[xmin][ymin] / maxch;

         else
            a = source[i - l + 1][ymin] / maxch;
         b = a - nim;
         if(a + nim <= 0)
            a = 1;

         else
            a = std::sqrt(a + nim);
         b = b / a;
         b = std::exp(b);
         sm = sm + b;
      }
      a = sp / sm;
      a = working_space[i + 1][ymin] = a * working_space[i][ymin];
      nom = nom + a;
   }
   for(i = ymin; i < ymax; i++){
      nip = source[xmin][i] / maxch;
      nim = source[xmin][i + 1] / maxch;
      sp = 0,sm = 0;
      for(l = 1; l <= averWindow; l++){
         if((i + l) > ymax)
            a = source[xmin][ymax] / maxch;

         else
            a = source[xmin][i + l] / maxch;
         b = a - nip;
         if(a + nip <= 0)
            a = 1;

         else
            a = std::sqrt(a + nip);
         b = b / a;
         b = std::exp(b);
         sp = sp + b;
         if(i - l + 1 < ymin)
            a = source[xmin][ymin] / maxch;

         else
            a = source[xmin][i - l + 1] / maxch;
         b = a - nim;
         if(a + nim <= 0)
            a = 1;

         else
            a = std::sqrt(a + nim);
         b = b / a;
         b = std::exp(b);
         sm = sm + b;
      }
      a = sp / sm;
      a = working_space[xmin][i + 1] = a * working_space[xmin][i];
      nom = nom + a;
   }
   for(i = xmin; i < xmax; i++){
      for(j = ymin; j < ymax; j++){
         nip = source[i][j + 1] / maxch;
         nim = source[i + 1][j + 1] / maxch;
         spx = 0,smx = 0;
         for(l = 1; l <= averWindow; l++){
            if(i + l > xmax)
               a = source[xmax][j] / maxch;

            else
               a = source[i + l][j] / maxch;
            b = a - nip;
            if(a + nip <= 0)
               a = 1;

            else
               a = std::sqrt(a + nip);
            b = b / a;
            b = std::exp(b);
            spx = spx + b;
            if(i - l + 1 < xmin)
               a = source[xmin][j] / maxch;

            else
               a = source[i - l + 1][j] / maxch;
            b = a - nim;
            if(a + nim <= 0)
               a = 1;

            else
               a = std::sqrt(a + nim);
            b = b / a;
            b = std::exp(b);
            smx = smx + b;
         }
         spy = 0,smy = 0;
         nip = source[i + 1][j] / maxch;
         nim = source[i + 1][j + 1] / maxch;
         for (l = 1; l <= averWindow; l++) {
            if (j + l > ymax) a = source[i][ymax]/maxch;
            else              a = source[i][j + l] / maxch;
            b = a - nip;
            if (a + nip <= 0) a = 1;
            else              a = std::sqrt(a + nip);
            b = b / a;
            b = std::exp(b);
            spy = spy + b;
            if (j - l + 1 < ymin) a = source[i][ymin] / maxch;
            else                  a = source[i][j - l + 1] / maxch;
            b = a - nim;
            if (a + nim <= 0) a = 1;
            else              a = std::sqrt(a + nim);
            b = b / a;
            b = std::exp(b);
            smy = smy + b;
         }
         a = (spx * working_space[i][j + 1] + spy * working_space[i + 1][j]) / (smx +smy);
         working_space[i + 1][j + 1] = a;
         nom = nom + a;
      }
   }
   for(i = xmin; i <= xmax; i++){
      for(j = ymin; j <= ymax; j++){
         working_space[i][j] = working_space[i][j] / nom;
      }
   }
   for(i = 0;i < ssizex; i++){
      for(j = 0; j < ssizey; j++){
         source[i][j] = plocha * working_space[i][j];
      }
   }
   for (i = 0; i < ssizex; i++)
      delete[]working_space[i];
   delete[]working_space;
   return 0;
}

////////////////////////////////////////////////////////////////////////////////
/// This function calculates deconvolution from source spectrum
/// according to response spectrum
/// The result is placed in the matrix pointed by source pointer.
///
/// Function parameters:
///  - source-pointer to the matrix of source spectrum
///  - resp-pointer to the matrix of response spectrum
///  - ssizex-x length of source and response spectra
///  - ssizey-y length of source and response spectra
///  - numberIterations, for details we refer to manual
///  - numberRepetitions, for details we refer to manual
///  - boost, boosting factor, for details we refer to manual
///
/// ### Deconvolution
///
/// Goal: Improvement of the resolution in spectra, decomposition of multiplets
///
/// Mathematical formulation of the 2-dimensional convolution system is
///
///\f[
/// y(i_1,i_2) = \sum_{k_1=0}^{N_1-1} \sum_{k_2=0}^{N_2-1} h(i_1-k_1,i_2-k_2)x(k_1,k_2)
///\f]
///\f[
/// i_1 = 0,1,2, ... ,N_1-1, i_2 = 0,1,2, ... ,N_2-1
///\f]
///
/// where h(i,j) is the impulse response function, x, y are input and output
/// matrices, respectively, \f$ N_1, N_2\f$ are the lengths of x and h matrices
///
///  - let us assume that we know the response and the output matrices (spectra) of the above given system.
///  - the deconvolution represents solution of the overdetermined system of linear equations, i.e., the
///    calculation of the matrix x.
///  - from numerical stability point of view the operation of deconvolution is
///    extremely critical (ill-posed problem) as well as time consuming operation.
///  - the Gold deconvolution algorithm proves to work very well even for 2-dimensional
///    systems. Generalisation of the algorithm for 2-dimensional systems was presented in [1], [2].
///  - for Gold deconvolution algorithm as well as for boosted deconvolution algorithm we refer also to TSpectrum
///
/// #### References:
///
/// [1] M. Morhac;, J. Kliman, V. Matouoek, M. Veselsky, I. Turzo.:
/// Efficient one- and two-dimensional Gold deconvolution and its application to
/// gamma-ray spectra decomposition. NIM, A401 (1997) 385-408.
///
/// [2] Morhac; M., Matouoek V., Kliman J., Efficient algorithm of multidimensional
/// deconvolution and its application to nuclear data processing, Digital Signal
/// Processing 13 (2003) 144.
///
/// ### Example 5 - script Decon.c
///
/// response function (usually peak) should be shifted to the beginning of the coordinate system (see Fig. 13)
///
/// \image html TSpectrum2_Deconvolution1.jpg Fig. 13 2-dimensional response spectrum
/// \image html TSpectrum2_Deconvolution2.jpg Fig. 14 2-dimensional gamma-gamma-ray input spectrum (before deconvolution)
/// \image html TSpectrum2_Deconvolution3.jpg Fig. 15 Spectrum from Fig. 14 after deconvolution (1000 iterations)
///
/// #### Script:
///
/// Example to illustrate the Gold deconvolution (class TSpectrum2).
/// To execute this example, do
///
/// `root > .x Decon.C`
///
/// ~~~ {.cpp}
///   #include <TSpectrum2>
///   void Decon() {
///      Int_t i, j;
///      Double_t nbinsx = 256;
///      Double_t nbinsy = 256;
///      Double_t xmin = 0;
///      Double_t xmax = (Double_t)nbinsx;
///      Double_t ymin = 0;
///      Double_t ymax = (Double_t)nbinsy;
///      Double_t** source = new Double_t*[nbinsx];
///      for (i=0;i<nbinsx;i++)
///         source[i]=new Double_t[nbinsy];
///      TH2F *decon = new TH2F("decon","Gold deconvolution",nbinsx,xmin,xmax,nbinsy,ymin,ymax);
///      TFile *f = new TFile("spectra2/TSpectrum2.root");
///      decon=(TH2F*) f->Get("decon1;1");
///      Double_t** response = new Double_t*[nbinsx];
///      for (i=0;i<nbinsx;i++)
///         response[i]=new Double_t[nbinsy];
///      TH2F *resp = new TH2F("resp","Response matrix",nbinsx,xmin,xmax,nbinsy,ymin,ymax);
///      resp=(TH2F*) f->Get("resp1;1");
///      TCanvas *Deconvol = new TCanvas("Deconvolution","Gold deconvolution",10,10,1000,700);
///      TSpectrum *s = new TSpectrum();
///      for (i = 0; i < nbinsx; i++){
///         for (j = 0; j < nbinsy; j++){
///            source[i][j] = decon->GetBinContent(i + 1,j + 1);
///         }
///      }
///      for (i = 0; i < nbinsx; i++){
///         for (j = 0; j < nbinsy; j++){
///            response[i][j] = resp->GetBinContent(i + 1,j + 1);
///         }
///      }
///      s->Deconvolution(source,response,nbinsx,nbinsy,1000,1,1);
///      for (i = 0; i < nbinsx; i++){
///         for (j = 0; j < nbinsy; j++)
///            decon->SetBinContent(i + 1,j + 1, source[i][j]);
///      }
///      decon->Draw("SURF");
///   }
/// ~~~
///
/// ### Example 6 - script Decon2.c
///
/// \image html TSpectrum2_Deconvolution4.jpg Fig. 16 Response spectrum
/// \image html TSpectrum2_Deconvolution5.jpg Fig. 17 Original synthetic input spectrum (before deconvolution). It is composed of 17 peaks. 5 peaks are overlapping in the outlined multiplet and two peaks in doublet.
/// \image html TSpectrum2_Deconvolution6.jpg Fig. 18 Spectrum from Fig. 17 after deconvolution (1000 iterations). Resolution is improved but the peaks in multiplet remained unresolved.
///
/// #### Script:
///
/// Example to illustrate the Gold deconvolution (class TSpectrum2).
/// To execute this example, do
///
/// `root > .x Decon2.C`
///
/// ~~~ {.cpp}
///   #include <TSpectrum2>
///   void Decon2() {
///      Int_t i, j;
///      Double_t nbinsx = 64;
///      Double_t nbinsy = 64;
///      Double_t xmin = 0;
///      Double_t xmax = (Double_t)nbinsx;
///      Double_t ymin = 0;
///      Double_t ymax = (Double_t)nbinsy;
///      Double_t** source = new Double_t*[nbinsx];
///      for (i=0;i<nbinsx;i++)
///         source[i]=new Double_t[nbinsy];
///      TH2F *decon = new TH2F("decon","Gold deconvolution",nbinsx,xmin,xmax,nbinsy,ymin,ymax);
///      TFile *f = new TFile("spectra2/TSpectrum2.root");
///      decon=(TH2F*) f->Get("decon2;1");
///      Double_t** response = new Double_t*[nbinsx];
///      for (i=0;i<nbinsx;i++)
///         response[i]=new Double_t[nbinsy];
///      TH2F *resp = new TH2F("resp","Response matrix",nbinsx,xmin,xmax,nbinsy,ymin,ymax);
///      resp=(TH2F*) f->Get("resp2;1");
///      TCanvas *Deconvol = new TCanvas("Deconvolution","Gold deconvolution",10,10,1000,700);
///      TSpectrum *s = new TSpectrum();
///      for (i = 0; i < nbinsx; i++){
///         for (j = 0; j < nbinsy; j++){
///            source[i][j] = decon->GetBinContent(i + 1,j + 1);
///         }
///      }
///      for (i = 0; i < nbinsx; i++){
///         for (j = 0; j < nbinsy; j++){
///            response[i][j] = resp->GetBinContent(i + 1,j + 1);
///         }
///      }
///      s->Deconvolution(source,response,nbinsx,nbinsy,1000,1,1);
///      for (i = 0; i < nbinsx; i++){
///         for (j = 0; j < nbinsy; j++)
///            decon->SetBinContent(i + 1,j + 1, source[i][j]);
///      }
///      decon->Draw("SURF");
///   }
/// ~~~
///
/// ### Example 7 - script Decon2HR.c
///
/// \image html TSpectrum2_Deconvolution7.jpg Fig. 19 Spectrum from Fig. 17 after boosted deconvolution (50 iterations repeated 20 times, boosting coefficient was 1.2). All the peaks in multiplet as well as in doublet are completely decomposed.
///
/// #### Script:
///
/// Example to illustrate boosted Gold deconvolution (class TSpectrum2).
/// To execute this example, do
///
/// `root > .x Decon2HR.C`
///
/// ~~~ {.cpp}
///   #include <TSpectrum2>
///   void Decon2HR() {
///      Int_t i, j;
///      Double_t nbinsx = 64;
///      Double_t nbinsy = 64;
///      Double_t xmin = 0;
///      Double_t xmax = (Double_t)nbinsx;
///      Double_t ymin = 0;
///      Double_t ymax = (Double_t)nbinsy;
///      Double_t** source = new Double_t*[nbinsx];
///      for (i=0;i<nbinsx;i++)
///         source[i]=new Double_t[nbinsy];
///      TH2F *decon = new TH2F("decon","Boosted Gold deconvolution",nbinsx,xmin,xmax,nbinsy,ymin,ymax);
///      TFile *f = new TFile("spectra2/TSpectrum2.root");
///      decon=(TH2F*) f->Get("decon2;1");
///      Double_t** response = new Double_t*[nbinsx];
///      for (i=0;i<nbinsx;i++)
///         response[i]=new Double_t[nbinsy];
///      TH2F *resp = new TH2F("resp","Response matrix",nbinsx,xmin,xmax,nbinsy,ymin,ymax);
///      resp=(TH2F*) f->Get("resp2;1");
///      TCanvas *Deconvol = new TCanvas("Deconvolution","Gold deconvolution",10,10,1000,700);
///      TSpectrum *s = new TSpectrum();
///      for (i = 0; i < nbinsx; i++){
///         for (j = 0; j < nbinsy; j++){
///            source[i][j] = decon->GetBinContent(i + 1,j + 1);
///         }
///      }
///      for (i = 0; i < nbinsx; i++){
///         for (j = 0; j < nbinsy; j++){
///            response[i][j] = resp->GetBinContent(i + 1,j + 1);
///         }
///      }
///      s->Deconvolution(source,response,nbinsx,nbinsy,1000,1,1);
///      for (i = 0; i < nbinsx; i++){
///         for (j = 0; j < nbinsy; j++)
///            dec   on->SetBinContent(i + 1,j + 1, source[i][j]);
///      }
///      decon->Draw("SURF");
///   }
/// ~~~

const char *TSpectrum2::Deconvolution(Double_t **source, Double_t **resp,
                                       Int_t ssizex, Int_t ssizey,
                                       Int_t numberIterations,
                                       Int_t numberRepetitions,
                                       Double_t boost)
{
   Int_t i, j, lhx, lhy, i1, i2, j1, j2, k1, k2, lindex, i1min, i1max,
       i2min, i2max, j1min, j1max, j2min, j2max, positx = 0, posity = 0, repet;
   Double_t lda, ldb, ldc, area, maximum = 0;
   if (ssizex <= 0 || ssizey <= 0)
      return "Wrong parameters";
   if (numberIterations <= 0)
      return "Number of iterations must be positive";
   if (numberRepetitions <= 0)
      return "Number of repetitions must be positive";
   Double_t **working_space = new Double_t *[ssizex];
   for (i = 0; i < ssizex; i++)
      working_space[i] = new Double_t[5 * ssizey];
   area = 0;
   lhx = -1, lhy = -1;
   for (i = 0; i < ssizex; i++) {
      for (j = 0; j < ssizey; j++) {
         lda = resp[i][j];
         if (lda != 0) {
            if ((i + 1) > lhx)
               lhx = i + 1;
            if ((j + 1) > lhy)
               lhy = j + 1;
         }
         working_space[i][j] = lda;
         area = area + lda;
         if (lda > maximum) {
            maximum = lda;
            positx = i, posity = j;
         }
      }
   }
   if (lhx == -1 || lhy == -1) {
      delete [] working_space;
      return ("Zero response data");
   }

//calculate ht*y and write into p
   for (i2 = 0; i2 < ssizey; i2++) {
      for (i1 = 0; i1 < ssizex; i1++) {
         ldc = 0;
         for (j2 = 0; j2 <= (lhy - 1); j2++) {
            for (j1 = 0; j1 <= (lhx - 1); j1++) {
               k2 = i2 + j2, k1 = i1 + j1;
               if (k2 >= 0 && k2 < ssizey && k1 >= 0 && k1 < ssizex) {
                  lda = working_space[j1][j2];
                  ldb = source[k1][k2];
                  ldc = ldc + lda * ldb;
               }
            }
         }
         working_space[i1][i2 + ssizey] = ldc;
      }
   }

//calculate matrix b=ht*h
   i1min = -(lhx - 1), i1max = lhx - 1;
   i2min = -(lhy - 1), i2max = lhy - 1;
   for (i2 = i2min; i2 <= i2max; i2++) {
      for (i1 = i1min; i1 <= i1max; i1++) {
         ldc = 0;
         j2min = -i2;
         if (j2min < 0)
            j2min = 0;
         j2max = lhy - 1 - i2;
         if (j2max > lhy - 1)
            j2max = lhy - 1;
         for (j2 = j2min; j2 <= j2max; j2++) {
            j1min = -i1;
            if (j1min < 0)
               j1min = 0;
            j1max = lhx - 1 - i1;
            if (j1max > lhx - 1)
               j1max = lhx - 1;
            for (j1 = j1min; j1 <= j1max; j1++) {
               lda = working_space[j1][j2];
               if (i1 + j1 < ssizex && i2 + j2 < ssizey)
                  ldb = working_space[i1 + j1][i2 + j2];
               else
                  ldb = 0;
               ldc = ldc + lda * ldb;
            }
         }
         working_space[i1 - i1min][i2 - i2min + 2 * ssizey ] = ldc;
      }
   }

//initialization in x1 matrix
   for (i2 = 0; i2 < ssizey; i2++) {
      for (i1 = 0; i1 < ssizex; i1++) {
         working_space[i1][i2 + 3 * ssizey] = 1;
         working_space[i1][i2 + 4 * ssizey] = 0;
      }
   }

   //START OF ITERATIONS
   for (repet = 0; repet < numberRepetitions; repet++) {
      if (repet != 0) {
         for (i = 0; i < ssizex; i++) {
            for (j = 0; j < ssizey; j++) {
               working_space[i][j + 3 * ssizey] =
                   std::pow(working_space[i][j + 3 * ssizey], boost);
            }
         }
      }
      for (lindex = 0; lindex < numberIterations; lindex++) {
         for (i2 = 0; i2 < ssizey; i2++) {
            for (i1 = 0; i1 < ssizex; i1++) {
               ldb = 0;
               j2min = i2;
               if (j2min > lhy - 1)
                  j2min = lhy - 1;
               j2min = -j2min;
               j2max = ssizey - i2 - 1;
               if (j2max > lhy - 1)
                  j2max = lhy - 1;
               j1min = i1;
               if (j1min > lhx - 1)
                  j1min = lhx - 1;
               j1min = -j1min;
               j1max = ssizex - i1 - 1;
               if (j1max > lhx - 1)
                  j1max = lhx - 1;
               for (j2 = j2min; j2 <= j2max; j2++) {
                  for (j1 = j1min; j1 <= j1max; j1++) {
                     ldc =  working_space[j1 - i1min][j2 - i2min + 2 * ssizey];
                     lda = working_space[i1 + j1][i2 + j2 + 3 * ssizey];
                     ldb = ldb + lda * ldc;
                  }
               }
               lda = working_space[i1][i2 + 3 * ssizey];
               ldc = working_space[i1][i2 + 1 * ssizey];
               if (ldc * lda != 0 && ldb != 0) {
                  lda = lda * ldc / ldb;
               }

               else
                  lda = 0;
               working_space[i1][i2 + 4 * ssizey] = lda;
            }
         }
         for (i2 = 0; i2 < ssizey; i2++) {
            for (i1 = 0; i1 < ssizex; i1++)
               working_space[i1][i2 + 3 * ssizey] =
                   working_space[i1][i2 + 4 * ssizey];
         }
      }
   }
   for (i = 0; i < ssizex; i++) {
      for (j = 0; j < ssizey; j++)
         source[(i + positx) % ssizex][(j + posity) % ssizey] =
             area * working_space[i][j + 3 * ssizey];
   }
   for (i = 0; i < ssizex; i++)
      delete[]working_space[i];
   delete[]working_space;
   return 0;
}

////////////////////////////////////////////////////////////////////////////////
/// This function searches for peaks in source spectrum
/// It is based on deconvolution method. First the background is
/// removed (if desired), then Markov spectrum is calculated
/// (if desired), then the response function is generated
/// according to given sigma and deconvolution is carried out.
///
/// Function parameters:
///  - source-pointer to the matrix of source spectrum
///  - dest-pointer to the matrix of resulting deconvolved spectrum
///  - ssizex-x length of source spectrum
///  - ssizey-y length of source spectrum
///  - sigma-sigma of searched peaks, for details we refer to manual
///  - threshold-threshold value in % for selected peaks, peaks with
///    amplitude less than threshold*highest_peak/100
///    are ignored, see manual
///  - backgroundRemove-logical variable, set if the removal of
///    background before deconvolution is desired
///  - deconIterations-number of iterations in deconvolution operation
///  - markov-logical variable, if it is true, first the source spectrum
///    is replaced by new spectrum calculated using Markov
///    chains method.
///  - averWindow-averaging window of searched peaks, for details
///    we refer to manual (applies only for Markov method)
///
/// ### Peaks searching
///
/// Goal: to identify automatically the peaks in spectrum with the presence of the
/// continuous background, one-fold coincidences (ridges) and statistical
/// fluctuations - noise.
///
/// The common problems connected with correct peak identification in two-dimensional coincidence spectra are
///
///  - non-sensitivity to noise, i.e., only statistically relevant peaks should be identified
///  - non-sensitivity of the algorithm to continuous background
///  - non-sensitivity to one-fold coincidences (coincidences peak - background in both dimensions) and their crossings
///  - ability to identify peaks close to the edges of the spectrum region. Usually peak finders fail to detect them
///  - resolution, decomposition of doublets and multiplets. The algorithm should be able to recognise close positioned peaks.
///  - ability to identify peaks with different sigma
///
/// #### References:
///
/// [1] M.A. Mariscotti: A method for identification of peaks in the presence of
/// background and its application to spectrum analysis. NIM 50 (1967), 309-320.
///
/// [2] M. Morhac;, J. Kliman, V. Matouoek, M. Veselsky, I. Turzo.:Identification
/// of peaks in multidimensional coincidence gamma-ray spectra. NIM, A443 (2000)
/// 108-125.
///
/// [3] Z.K. Silagadze, A new algorithm for automatic photopeak searches. NIM A 376
/// (1996), 451.
///
/// ### Examples of peak searching method
///
/// SearchHighRes function provides users with the possibility
/// to vary the input parameters and with the access to the output deconvolved data
/// in the destination spectrum. Based on the output data one can tune the
/// parameters.
///
/// ### Example 8 - script Src.c
///
/// \image html TSpectrum2_Searching1.jpg Fig. 20 Two-dimensional spectrum with found peaks denoted by markers (sigma=2, threshold=5%, 3 iterations steps in the deconvolution)
/// \image html TSpectrum2_Searching3.jpg Fig. 21 Spectrum from Fig. 20 after background elimination and deconvolution
///
/// #### Script:
///
/// Example to illustrate high resolution peak searching function (class TSpectrum).
/// To execute this example, do
///
/// `root > .x Src.C
///
/// ~~~ {.cpp}
///   #include <TSpectrum2>
///   void Src() {
///      Int_t i, j, nfound;
///      Double_t nbinsx = 64;
///      Double_t nbinsy = 64;
///      Double_t xmin = 0;
///      Double_t xmax = (Double_t)nbinsx;
///      Double_t ymin = 0;
///      Double_t ymax = (Double_t)nbinsy;
///      Double_t** source = new Double_t*[nbinsx];
///      for (i=0;i<nbinsx;i++)
///         source[i]=new Double_t[nbinsy];
///      Double_t** dest = new Double_t*[nbinsx];
///      for (i=0;i<nbinsx;i++)
///         dest[i]=new Double_t[nbinsy];
///      TH2F *search = new TH2F("search","High resolution peak searching",nbinsx,xmin,xmax,nbinsy,ymin,ymax);/
///      TFile *f = new TFile("spectra2/TSpectrum2.root");
///      search=(TH2F*) f->Get("search4;1");
///      TCanvas *Searching = new TCanvas("Searching","High resolution peak searching",10,10,1000,700);
///      TSpectrum2 *s = new TSpectrum2();
///      for (i = 0; i < nbinsx; i++){
///         for (j = 0; j < nbinsy; j++){
///            source[i][j] = search->GetBinContent(i + 1,j + 1);
///         }
///      }
///      nfound = s->SearchHighRes(source, dest, nbinsx, nbinsy, 2, 5, kTRUE, 3, kFALSE, 3);
///      printf("Found %d candidate peaks\n",nfound);
///      for(i=0;i<nfound;i++)
///         printf("posx= %d, posy= %d, value=%d\n",(Int_t)(fPositionX[i]+0.5), (Int_t)(fPositionY[i]+0.5),
///         (Int_t)source[(Int_t)(fPositionX[i]+0.5)][(Int_t)(fPositionY[i]+0.5)]);
///  }
/// ~~~
///
/// ### Example 9 - script Src2.c
///
/// \image html TSpectrum2_Searching4.jpg Fig. 22 Two-dimensional noisy spectrum with found peaks denoted by markers (sigma=2, threshold=10%, 10 iterations steps in the deconvolution). One can observe that the algorithm is insensitive to the crossings of one-dimensional ridges. It identifies only two-coincidence peaks.
/// \image html TSpectrum2_Searching5.jpg Fig. 23 Spectrum from Fig. 22 after background elimination and deconvolution
///
/// #### Script:
///
/// Example to illustrate high resolution peak searching function (class TSpectrum).
/// To execute this example, do
///
/// `root > .x Src2.C`
///
/// ~~~ {.cpp}
///   #include <TSpectrum2>
///   void Src2() {
///      Int_t i, j, nfound;
///      Double_t nbinsx = 256;
///      Double_t nbinsy = 256;
///      Double_t xmin = 0;
///      Double_t xmax = (Double_t)nbinsx;
///      Double_t ymin = 0;
///      Double_t ymax = (Double_t)nbinsy;
///      Double_t** source = new Double_t*[nbinsx];
///      for (i=0;i<nbinsx;i++)
///         source[i]=new Double_t[nbinsy];
///      Double_t** dest = new Double_t*[nbinsx];
///      for (i=0;i<nbinsx;i++)
///         dest[i]=new Double_t[nbinsy];
///      TH2F *search = new TH2F("search","High resolution peak searching",nbinsx,xmin,xmax,nbinsy,ymin,ymax);
///      TFile *f = new TFile("spectra2/TSpectrum2.root");
///      search=(TH2F*) f->Get("back3;1");
///      TCanvas *Searching = new TCanvas("Searching","High resolution peak searching",10,10,1000,700);
///      TSpectrum2 *s = new TSpectrum2();
///      for (i = 0; i < nbinsx; i++){
///         for (j = 0; j < nbinsy; j++){
///            source[i][j] = search->GetBinContent(i + 1,j + 1);
///         }
///      }
///      nfound = s->SearchHighRes(source, dest, nbinsx, nbinsy, 2, 10, kTRUE, 10, kFALSE, 3);
///      printf("Found %d candidate peaks\n",nfound);
///      for(i=0;i<nfound;i++)
///         printf("posx= %d, posy= %d, value=%d\n",(Int_t)(fPositionX[i]+0.5), (Int_t)(fPositionY[i]+0.5),
///         (Int_t)source[(Int_t)(fPositionX[i]+0.5)][(Int_t)(fPositionY[i]+0.5)]);
///   }
/// ~~~
///
/// ### Example 10 - script Src3.c
///
/// \image html TSpectrum2_Searching6.jpg Fig. 24 Two-dimensional spectrum with 15 found peaks denoted by markers. Some peaks are positioned close to each other. It is necessary to increase number of iterations in the deconvolution. In next 3 Figs. we shall study the influence of this parameter.
/// \image html TSpectrum2_Searching7.jpg Fig. 25 Spectrum from Fig. 24 after deconvolution (# of iterations = 3). Number of identified peaks = 13.
/// \image html TSpectrum2_Searching8.jpg Fig. 26 Spectrum from Fig. 24 after deconvolution (# of iterations = 10). Number of identified peaks = 13.
/// \image html TSpectrum2_Searching9.jpg Fig. 27 Spectrum from Fig. 24 after deconvolution (# of iterations = 100). Number of identified peaks = 15. Now the algorithm is able to decompose two doublets in the spectrum.
///
/// #### Script:
///
/// Example to illustrate high resolution peak searching function (class TSpectrum).
/// To execute this example, do
///
/// `root > .x Src3.C`
///
/// ~~~ {.cpp}
///   #include <TSpectrum2>
///   void Src3() {
///      Int_t i, j, nfound;
///      Double_t nbinsx = 64;
///      Double_t nbinsy = 64;
///      Double_t xmin = 0;
///      Double_t xmax = (Double_t)nbinsx;
///      Double_t ymin = 0;
///      Double_t ymax = (Double_t)nbinsy;
///      Double_t** source = new Double_t*[nbinsx];
///      for (i=0;i<nbinsx;i++)
///         source[i]=new Double_t[nbinsy];
///      Double_t** dest = new Double_t*[nbinsx];
///      for (i=0;i<nbinsx;i++)
///         dest[i]=new Double_t[nbinsy];
///      TH2F *search = new TH2F("search","High resolution peak searching",nbinsx,xmin,xmax,nbinsy,ymin,ymax);
///      TFile *f = new TFile("spectra2/TSpectrum2.root");
///      search=(TH2F*) f->Get("search1;1");
///      TCanvas *Searching = new TCanvas("Searching","High resolution peak searching",10,10,1000,700);
///      TSpectrum2 *s = new TSpectrum2();
///      for (i = 0; i < nbinsx; i++){
///         for (j = 0; j < nbinsy; j++){
///            source[i][j] = search->GetBinContent(i + 1,j + 1);
///         }
///      }
///      nfound = s->SearchHighRes(source, dest, nbinsx, nbinsy, 2, 2, kFALSE, 3, kFALSE, 1);//3, 10, 100
///      printf("Found %d candidate peaks\n",nfound);
///      for(i=0;i<nfound;i++)
///         printf("posx= %d, posy= %d, value=%d\n",(Int_t)(fPositionX[i]+0.5), (Int_t)(fPositionY[i]+0.5),
///         (Int_t)source[(Int_t)(fPositionX[i]+0.5)][(Int_t)(fPositionY[i]+0.5)]);
///  }
/// ~~~
///
/// ### Example 11 - script Src4.c
///
/// \image html TSpectrum2_Searching10.jpg Fig. 28 Two-dimensional spectrum with peaks with different sigma denoted by markers (sigma=3, threshold=5%, 10 iterations steps in the deconvolution, Markov smoothing with window=3)
/// \image html TSpectrum2_Searching12.jpg Fig. 29 Spectrum from Fig. 28 after smoothing and deconvolution.
///
/// #### Script:
///
/// Example to illustrate high resolution peak searching function (class TSpectrum).
/// To execute this example, do
///
/// `root > .x Src4.C`
///
/// ~~~ {.cpp}
///   #include <TSpectrum2>
///   void Src4() {
///   Int_t i, j, nfound;
///      Double_t nbinsx = 64;
///      Double_t nbinsy = 64;
///      Double_t xmin = 0;
///      Double_t xmax = (Double_t)nbinsx;
///      Double_t ymin = 0;
///      Double_t ymax = (Double_t)nbinsy;
///      Double_t** source = new Double_t*[nbinsx];
///      for (i=0;i<nbinsx;i++)
///         source[i]=new Double_t[nbinsy];
///      Double_t** dest = new Double_t*[nbinsx];
///      for (i=0;i<nbinsx;i++)
///         dest[i]=new Double_t[nbinsy];
///      TH2F *search = new TH2F("search","High resolution peak searching",nbinsx,xmin,xmax,nbinsy,ymin,ymax);
///      TFile *f = new TFile("spectra2/TSpectrum2.root");
///      search=(TH2F*) f->Get("search2;1");
///      TCanvas *Searching = new TCanvas("Searching","High resolution peak searching",10,10,1000,700);
///      TSpectrum2 *s = new TSpectrum2();
///      for (i = 0; i < nbinsx; i++){
///         for (j = 0; j < nbinsy; j++){
///            source[i][j] = search->GetBinContent(i + 1,j + 1);
///         }
///       }
///      nfound = s->SearchHighRes(source, dest, nbinsx, nbinsy, 3, 5, kFALSE, 10, kTRUE, 3);
///      printf("Found %d candidate peaks\n",nfound);
///      for(i=0;i<nfound;i++)
///         printf("posx= %d, posy= %d, value=%d\n",(Int_t)(fPositionX[i]+0.5), (Int_t)(fPositionY[i]+0.5),
///         (Int_t)source[(Int_t)(fPositionX[i]+0.5)][(Int_t)(fPositionY[i]+0.5)]);
///  }
/// ~~~
///
/// ### Example 12 - script Src5.c`
///
/// \image html TSpectrum2_Searching13.jpg Fig. 30 Two-dimensional spectrum with peaks positioned close to the edges denoted by markers (sigma=2, threshold=5%, 10 iterations steps in the deconvolution)
/// \image html TSpectrum2_Searching14.jpg Fig. 31 Spectrum from Fig. 30 after deconvolution.
///
/// #### Script:
///
/// Example to illustrate high resolution peak searching function (class TSpectrum).
/// To execute this example, do
///
/// `root > .x Src5.C`
///
/// ~~~ {.cpp}
///   #include <TSpectrum2>
///   void Src5() {
///      Int_t i, j, nfound;
///      Double_t nbinsx = 64;
///      Double_t nbinsy = 64;
///      Double_t xmin = 0;
///      Double_t xmax = (Double_t)nbinsx;
///      Double_t ymin = 0;
///      Double_t ymax = (Double_t)nbinsy;
///      Double_t** source = new Double_t*[nbinsx];
///      for (i=0;i<nbinsx;i++)
///         source[i]=new Double_t[nbinsy];
///      Double_t** dest = new Double_t*[nbinsx];
///      for (i=0;i<nbinsx;i++)
///         dest[i]=new Double_t[nbinsy];
///      TH2F *search = new TH2F("search","High resolution peak searching",nbinsx,xmin,xmax,nbinsy,ymin,ymax);
///      TFile *f = new TFile("spectra2/TSpectrum2.root");
///      search=(TH2F*) f->Get("search3;1");
///      TCanvas *Searching = new TCanvas("Searching","High resolution peak searching",10,10,1000,700);
///      TSpectrum2 *s = new TSpectrum2();
///      for (i = 0; i < nbinsx; i++){
///         for (j = 0; j < nbinsy; j++){
///            source[i][j] = search->GetBinContent(i + 1,j + 1);
///         }
///      }
///      nfound = s->SearchHighRes(source, dest, nbinsx, nbinsy, 2, 5, kFALSE, 10, kFALSE, 1);
///      printf("Found %d candidate peaks\n",nfound);
///      for(i=0;i<nfound;i++)
///         printf("posx= %d, posy= %d, value=%d\n",(Int_t)(fPositionX[i]+0.5), (Int_t)(fPositionY[i]+0.5),
///         (Int_t)source[(Int_t)(fPositionX[i]+0.5)][(Int_t)(fPositionY[i]+0.5)]);
///  }
/// ~~~

Int_t TSpectrum2::SearchHighRes(Double_t **source, Double_t **dest, Int_t ssizex, Int_t ssizey,
                                 Double_t sigma, Double_t threshold,
                                 Bool_t backgroundRemove,Int_t deconIterations,
                                 Bool_t markov, Int_t averWindow)

{
   Int_t number_of_iterations = (Int_t)(4 * sigma + 0.5);
   Int_t k, lindex, priz;
   Double_t lda, ldb, ldc, area, maximum;
   Int_t xmin, xmax, l, peak_index = 0, ssizex_ext = ssizex + 4 * number_of_iterations, ssizey_ext = ssizey + 4 * number_of_iterations, shift = 2 * number_of_iterations;
   Int_t ymin, ymax, i, j;
   Double_t a, b, ax, ay, maxch, plocha = 0;
   Double_t nom, nip, nim, sp, sm, spx, spy, smx, smy;
   Double_t p1, p2, p3, p4, s1, s2, s3, s4;
   Int_t x, y;
   Int_t lhx, lhy, i1, i2, j1, j2, k1, k2, i1min, i1max, i2min, i2max, j1min, j1max, j2min, j2max, positx, posity;
   if (sigma < 1) {
      throw std::runtime_error("SearchHighRes Invalid sigma, must be greater than or equal to 1");
   }

   if(threshold<=0||threshold>=100){
      throw std::runtime_error("SearchHighRes Invalid threshold, must be positive and less than 100");
   }

   j = (Int_t) (5.0 * sigma + 0.5);
   if (j >= PEAK_WINDOW / 2) {
      throw std::runtime_error("SearchHighRes Too large sigma");
   }

   if (markov == true) {
      if (averWindow <= 0) {
         throw std::runtime_error("SearchHighRes Averaging window must be positive");
      }
   }
   if(backgroundRemove == true){
      if(ssizex_ext < 2 * number_of_iterations + 1 || ssizey_ext < 2 * number_of_iterations + 1){
         throw std::runtime_error("SearchHighRes Too large clipping window");
      }
   }
   i = (Int_t)(4 * sigma + 0.5);
   i = 4 * i;
   Double_t **working_space = new Double_t *[ssizex + i];
   for (j = 0; j < ssizex + i; j++) {
      Double_t *wsk = working_space[j] = new Double_t[16 * (ssizey + i)];
      for (k=0;k<16 * (ssizey + i);k++) wsk[k] = 0;
   }
   for(j = 0; j < ssizey_ext; j++){
      for(i = 0; i < ssizex_ext; i++){
         if(i < shift){
            if(j < shift)
                  working_space[i][j + ssizey_ext] = source[0][0];

            else if(j >= ssizey + shift)
                  working_space[i][j + ssizey_ext] = source[0][ssizey - 1];

            else
                  working_space[i][j + ssizey_ext] = source[0][j - shift];
         }

         else if(i >= ssizex + shift){
            if(j < shift)
               working_space[i][j + ssizey_ext] = source[ssizex - 1][0];

            else if(j >= ssizey + shift)
               working_space[i][j + ssizey_ext] = source[ssizex - 1][ssizey - 1];

            else
               working_space[i][j + ssizey_ext] = source[ssizex - 1][j - shift];
         }

         else{
            if(j < shift)
               working_space[i][j + ssizey_ext] = source[i - shift][0];

            else if(j >= ssizey + shift)
               working_space[i][j + ssizey_ext] = source[i - shift][ssizey - 1];

            else
               working_space[i][j + ssizey_ext] = source[i - shift][j - shift];
         }
      }
   }
   if(backgroundRemove == true){
      for(i = 1; i <= number_of_iterations; i++){
         for(y = i; y < ssizey_ext - i; y++){
            for(x = i; x < ssizex_ext - i; x++){
               a = working_space[x][y + ssizey_ext];
               p1 = working_space[x - i][y + ssizey_ext - i];
               p2 = working_space[x - i][y + ssizey_ext + i];
               p3 = working_space[x + i][y + ssizey_ext - i];
               p4 = working_space[x + i][y + ssizey_ext + i];
               s1 = working_space[x][y + ssizey_ext - i];
               s2 = working_space[x - i][y + ssizey_ext];
               s3 = working_space[x + i][y + ssizey_ext];
               s4 = working_space[x][y + ssizey_ext + i];
               b = (p1 + p2) / 2.0;
               if(b > s2)
                  s2 = b;
               b = (p1 + p3) / 2.0;
               if(b > s1)
                  s1 = b;
               b = (p2 + p4) / 2.0;
               if(b > s4)
                  s4 = b;
               b = (p3 + p4) / 2.0;
               if(b > s3)
                  s3 = b;
               s1 = s1 - (p1 + p3) / 2.0;
               s2 = s2 - (p1 + p2) / 2.0;
               s3 = s3 - (p3 + p4) / 2.0;
               s4 = s4 - (p2 + p4) / 2.0;
               b = (s1 + s4) / 2.0 + (s2 + s3) / 2.0 + (p1 + p2 + p3 + p4) / 4.0;
               if(b < a)
                  a = b;
               working_space[x][y] = a;
            }
         }
         for(y = i;y < ssizey_ext - i; y++){
            for(x = i; x < ssizex_ext - i; x++){
               working_space[x][y + ssizey_ext] = working_space[x][y];
            }
         }
      }
      for(j = 0;j < ssizey_ext; j++){
         for(i = 0; i < ssizex_ext; i++){
            if(i < shift){
               if(j < shift)
                  working_space[i][j + ssizey_ext] = source[0][0] - working_space[i][j + ssizey_ext];

               else if(j >= ssizey + shift)
                  working_space[i][j + ssizey_ext] = source[0][ssizey - 1] - working_space[i][j + ssizey_ext];

               else
                  working_space[i][j + ssizey_ext] = source[0][j - shift] - working_space[i][j + ssizey_ext];
            }

            else if(i >= ssizex + shift){
               if(j < shift)
                  working_space[i][j + ssizey_ext] = source[ssizex - 1][0] - working_space[i][j + ssizey_ext];

               else if(j >= ssizey + shift)
                  working_space[i][j + ssizey_ext] = source[ssizex - 1][ssizey - 1] - working_space[i][j + ssizey_ext];

               else
                  working_space[i][j + ssizey_ext] = source[ssizex - 1][j - shift] - working_space[i][j + ssizey_ext];
            }

            else{
               if(j < shift)
                  working_space[i][j + ssizey_ext] = source[i - shift][0] - working_space[i][j + ssizey_ext];

               else if(j >= ssizey + shift)
                  working_space[i][j + ssizey_ext] = source[i - shift][ssizey - 1] - working_space[i][j + ssizey_ext];

               else
                  working_space[i][j + ssizey_ext] = source[i - shift][j - shift] - working_space[i][j + ssizey_ext];
            }
         }
      }
   }
   for(j = 0; j < ssizey_ext; j++){
      for(i = 0; i < ssizex_ext; i++){
         working_space[i][j + 15*ssizey_ext] = working_space[i][j + ssizey_ext];
      }
   }
   if(markov == true){
      for(i = 0;i < ssizex_ext; i++){
         for(j = 0; j < ssizey_ext; j++)
         working_space[i][j + 2 * ssizex_ext] = working_space[i][ssizey_ext + j];
      }
      xmin = 0;
      xmax = ssizex_ext - 1;
      ymin = 0;
      ymax = ssizey_ext - 1;
      for(i = 0, maxch = 0; i < ssizex_ext; i++){
         for(j = 0; j < ssizey_ext; j++){
            working_space[i][j] = 0;
            if(maxch < working_space[i][j + 2 * ssizey_ext])
               maxch = working_space[i][j + 2 * ssizey_ext];
            plocha += working_space[i][j + 2 * ssizey_ext];
         }
      }
      if(maxch == 0) {
         delete [] working_space;
         return 0;
      }

      nom=0;
      working_space[xmin][ymin] = 1;
      for(i = xmin; i < xmax; i++){
         nip = working_space[i][ymin + 2 * ssizey_ext] / maxch;
         nim = working_space[i + 1][ymin + 2 * ssizey_ext] / maxch;
         sp = 0,sm = 0;
         for(l = 1;l <= averWindow; l++){
            if((i + l) > xmax)
               a = working_space[xmax][ymin + 2 * ssizey_ext] / maxch;

            else
               a = working_space[i + l][ymin + 2 * ssizey_ext] / maxch;

            b = a - nip;
            if(a + nip <= 0)
               a = 1;

            else
               a=std::sqrt(a + nip);
            b = b / a;
            b = std::exp(b);
            sp = sp + b;
            if(i - l + 1 < xmin)
               a = working_space[xmin][ymin + 2 * ssizey_ext] / maxch;

            else
               a = working_space[i - l + 1][ymin + 2 * ssizey_ext] / maxch;
            b = a - nim;
            if(a + nim <= 0)
               a = 1;

            else
               a=std::sqrt(a + nim);
            b = b / a;
            b = std::exp(b);
            sm = sm + b;
         }
         a = sp / sm;
         a = working_space[i + 1][ymin] = a * working_space[i][ymin];
         nom = nom + a;
      }
      for(i = ymin; i < ymax; i++){
         nip = working_space[xmin][i + 2 * ssizey_ext] / maxch;
         nim = working_space[xmin][i + 1 + 2 * ssizey_ext] / maxch;
         sp = 0,sm = 0;
         for(l = 1; l <= averWindow; l++){
            if((i + l) > ymax)
               a = working_space[xmin][ymax + 2 * ssizey_ext] / maxch;

            else
               a = working_space[xmin][i + l + 2 * ssizey_ext] / maxch;
            b = a - nip;
            if(a + nip <= 0)
               a=1;

            else
               a=std::sqrt(a + nip);
            b = b / a;
            b = std::exp(b);
            sp = sp + b;
            if(i - l + 1 < ymin)
               a = working_space[xmin][ymin + 2 * ssizey_ext] / maxch;

            else
               a = working_space[xmin][i - l + 1 + 2 * ssizey_ext] / maxch;
            b = a - nim;
            if(a + nim <= 0)
               a = 1;

            else
               a=std::sqrt(a + nim);
            b = b / a;
            b = std::exp(b);
            sm = sm + b;
         }
         a = sp / sm;
         a = working_space[xmin][i + 1] = a * working_space[xmin][i];
         nom = nom + a;
      }
      for(i = xmin; i < xmax; i++){
         for(j = ymin; j < ymax; j++){
            nip = working_space[i][j + 1 + 2 * ssizey_ext] / maxch;
            nim = working_space[i + 1][j + 1 + 2 * ssizey_ext] / maxch;
            spx = 0,smx = 0;
            for(l = 1; l <= averWindow; l++){
               if(i + l > xmax)
                  a = working_space[xmax][j + 2 * ssizey_ext] / maxch;

               else
                  a = working_space[i + l][j + 2 * ssizey_ext] / maxch;
               b = a - nip;
               if(a + nip <= 0)
                  a = 1;

               else
                  a=std::sqrt(a + nip);
               b = b / a;
               b = std::exp(b);
               spx = spx + b;
               if(i - l + 1 < xmin)
                  a = working_space[xmin][j + 2 * ssizey_ext] / maxch;

               else
                  a = working_space[i - l + 1][j + 2 * ssizey_ext] / maxch;
               b = a - nim;
               if(a + nim <= 0)
                  a=1;

               else
                  a=std::sqrt(a + nim);
               b = b / a;
               b = std::exp(b);
               smx = smx + b;
            }
            spy = 0,smy = 0;
            nip = working_space[i + 1][j + 2 * ssizey_ext] / maxch;
            nim = working_space[i + 1][j + 1 + 2 * ssizey_ext] / maxch;
            for(l = 1; l <= averWindow; l++){
               if(j + l > ymax)
                  a = working_space[i][ymax + 2 * ssizey_ext] / maxch;

               else
                  a = working_space[i][j + l + 2 * ssizey_ext] / maxch;
               b = a - nip;
               if(a + nip <= 0)
                  a = 1;

               else
                  a=std::sqrt(a + nip);
               b = b / a;
               b = std::exp(b);
               spy = spy + b;
               if(j - l + 1 < ymin)
                  a = working_space[i][ymin + 2 * ssizey_ext] / maxch;

               else
                  a = working_space[i][j - l + 1 + 2 * ssizey_ext] / maxch;
               b=a-nim;
               if(a + nim <= 0)
                  a = 1;
               else
                  a=std::sqrt(a + nim);
               b = b / a;
               b = std::exp(b);
               smy = smy + b;
            }
            a = (spx * working_space[i][j + 1] + spy * working_space[i + 1][j]) / (smx + smy);
            working_space[i + 1][j + 1] = a;
            nom = nom + a;
         }
      }
      for(i = xmin; i <= xmax; i++){
         for(j = ymin; j <= ymax; j++){
            working_space[i][j] = working_space[i][j] / nom;
         }
      }
      for(i = 0; i < ssizex_ext; i++){
         for(j = 0; j < ssizey_ext; j++){
            working_space[i][j + ssizey_ext] = working_space[i][j] * plocha;
            working_space[i][2 * ssizey_ext + j] = working_space[i][ssizey_ext + j];
         }
      }
   }
   //deconvolution starts
   area = 0;
   lhx = -1,lhy = -1;
   positx = 0,posity = 0;
   maximum = 0;
   //generate response matrix
   for(i = 0; i < ssizex_ext; i++){
      for(j = 0; j < ssizey_ext; j++){
         lda = (Double_t)i - 3 * sigma;
         ldb = (Double_t)j - 3 * sigma;
         lda = (lda * lda + ldb * ldb) / (2 * sigma * sigma);
         k=(Int_t)(1000 * std::exp(-lda));
         lda = k;
         if(lda != 0){
            if((i + 1) > lhx)
               lhx = i + 1;

            if((j + 1) > lhy)
               lhy = j + 1;
         }
         working_space[i][j] = lda;
         area = area + lda;
         if(lda > maximum){
            maximum = lda;
            positx = i,posity = j;
         }
      }
   }
   //read source matrix
   for(i = 0;i < ssizex_ext; i++){
      for(j = 0;j < ssizey_ext; j++){
         working_space[i][j + 14 * ssizey_ext] = std::abs(working_space[i][j + ssizey_ext]);
      }
   }
   //calculate matrix b=ht*h
   i = lhx - 1;
   if(i > ssizex_ext)
      i = ssizex_ext;

   j = lhy - 1;
   if(j>ssizey_ext)
      j = ssizey_ext;

   i1min = -i,i1max = i;
   i2min = -j,i2max = j;
   for(i2 = i2min; i2 <= i2max; i2++){
      for(i1 = i1min; i1 <= i1max; i1++){
         ldc = 0;
         j2min = -i2;
         if(j2min < 0)
            j2min = 0;

         j2max = lhy - 1 - i2;
         if(j2max > lhy - 1)
            j2max = lhy - 1;

         for(j2 = j2min; j2 <= j2max; j2++){
            j1min = -i1;
            if(j1min < 0)
               j1min = 0;

            j1max = lhx - 1 - i1;
            if(j1max > lhx - 1)
               j1max = lhx - 1;

            for(j1 = j1min; j1 <= j1max; j1++){
               lda = working_space[j1][j2];
               ldb = working_space[i1 + j1][i2 + j2];
               ldc = ldc + lda * ldb;
            }
         }
         k = (i1 + ssizex_ext) / ssizex_ext;
         working_space[(i1 + ssizex_ext) % ssizex_ext][i2 + ssizey_ext + 10 * ssizey_ext + k * 2 * ssizey_ext] = ldc;
      }
   }
   //calculate at*y and write into p
   i = lhx - 1;
   if(i > ssizex_ext)
      i = ssizex_ext;

   j = lhy - 1;
   if(j > ssizey_ext)
      j = ssizey_ext;

   i2min = -j,i2max = ssizey_ext + j - 1;
   i1min = -i,i1max = ssizex_ext + i - 1;
   for(i2 = i2min; i2 <= i2max; i2++){
      for(i1=i1min;i1<=i1max;i1++){
         ldc=0;
         for(j2 = 0; j2 <= (lhy - 1); j2++){
            for(j1 = 0; j1 <= (lhx - 1); j1++){
               k2 = i2 + j2,k1 = i1 + j1;
               if(k2 >= 0 && k2 < ssizey_ext && k1 >= 0 && k1 < ssizex_ext){
                  lda = working_space[j1][j2];
                  ldb = working_space[k1][k2 + 14 * ssizey_ext];
                  ldc = ldc + lda * ldb;
               }
            }
         }
         k = (i1 + ssizex_ext) / ssizex_ext;
         working_space[(i1 + ssizex_ext) % ssizex_ext][i2 + ssizey_ext + ssizey_ext + k * 3 * ssizey_ext] = ldc;
      }
   }
   //move matrix p
   for(i2 = 0; i2 < ssizey_ext; i2++){
      for(i1 = 0; i1 < ssizex_ext; i1++){
         k = (i1 + ssizex_ext) / ssizex_ext;
         ldb = working_space[(i1 + ssizex_ext) % ssizex_ext][i2 + ssizey_ext + ssizey_ext + k * 3 * ssizey_ext];
         working_space[i1][i2 + 14 * ssizey_ext] = ldb;
      }
   }
   //initialization in x1 matrix
   for(i2 = 0; i2 < ssizey_ext; i2++){
      for(i1 = 0; i1 < ssizex_ext; i1++){
         working_space[i1][i2 + ssizey_ext] = 1;
         working_space[i1][i2 + 2 * ssizey_ext] = 0;
      }
   }
   //START OF ITERATIONS
   for(lindex = 0; lindex < deconIterations; lindex++){
      for(i2 = 0; i2 < ssizey_ext; i2++){
         for(i1 = 0; i1 < ssizex_ext; i1++){
            lda = working_space[i1][i2 + ssizey_ext];
            ldc = working_space[i1][i2 + 14 * ssizey_ext];
            if(lda > 0.000001 && ldc > 0.000001){
               ldb=0;
               j2min=i2;
               if(j2min > lhy - 1)
                  j2min = lhy - 1;

               j2min = -j2min;
               j2max = ssizey_ext - i2 - 1;
               if(j2max > lhy - 1)
                  j2max = lhy - 1;

               j1min = i1;
               if(j1min > lhx - 1)
                  j1min = lhx - 1;

               j1min = -j1min;
               j1max = ssizex_ext - i1 - 1;
               if(j1max > lhx - 1)
                  j1max = lhx - 1;

               for(j2 = j2min; j2 <= j2max; j2++){
                  for(j1 = j1min; j1 <= j1max; j1++){
                     k = (j1 + ssizex_ext) / ssizex_ext;
                     ldc = working_space[(j1 + ssizex_ext) % ssizex_ext][j2 + ssizey_ext + 10 * ssizey_ext + k * 2 * ssizey_ext];
                     lda = working_space[i1 + j1][i2 + j2 + ssizey_ext];
                     ldb = ldb + lda * ldc;
                  }
               }
               lda = working_space[i1][i2 + ssizey_ext];
               ldc = working_space[i1][i2 + 14 * ssizey_ext];
               if(ldc * lda != 0 && ldb != 0){
                  lda =lda * ldc / ldb;
               }

               else
                  lda=0;
               working_space[i1][i2 + 2 * ssizey_ext] = lda;
            }
         }
      }
      for(i2 = 0; i2 < ssizey_ext; i2++){
         for(i1 = 0; i1 < ssizex_ext; i1++)
            working_space[i1][i2 + ssizey_ext] = working_space[i1][i2 + 2 * ssizey_ext];
      }
   }
   //looking for maximum
   maximum=0;
   for(i = 0; i < ssizex_ext; i++){
      for(j = 0; j < ssizey_ext; j++){
         working_space[(i + positx) % ssizex_ext][(j + posity) % ssizey_ext] = area * working_space[i][j + ssizey_ext];
         if(maximum < working_space[(i + positx) % ssizex_ext][(j + posity) % ssizey_ext])
            maximum = working_space[(i + positx) % ssizex_ext][(j + posity) % ssizey_ext];

      }
   }
   //searching for peaks in deconvolved spectrum
   for(i = 1; i < ssizex_ext - 1; i++){
      for(j = 1; j < ssizey_ext - 1; j++){
         if(working_space[i][j] > working_space[i - 1][j] && working_space[i][j] > working_space[i - 1][j - 1] && working_space[i][j] > working_space[i][j - 1] && working_space[i][j] > working_space[i + 1][j - 1] && working_space[i][j] > working_space[i + 1][j] && working_space[i][j] > working_space[i + 1][j + 1] && working_space[i][j] > working_space[i][j + 1] && working_space[i][j] > working_space[i - 1][j + 1]){
            if(i >= shift && i < ssizex + shift && j >= shift && j < ssizey + shift){
               if(working_space[i][j] > threshold * maximum / 100.0){
                  if(peak_index < fMaxPeaks){
                     for(k = i - 1,a = 0,b = 0; k <= i + 1; k++){
                        a += (Double_t)(k - shift) * working_space[k][j];
                        b += working_space[k][j];
                     }
                     ax=a/b;
                     if(ax < 0)
                        ax = 0;

                     if(ax >= ssizex)
                        ax = ssizex - 1;

                     for(k = j - 1,a = 0,b = 0; k <= j + 1; k++){
                        a += (Double_t)(k - shift) * working_space[i][k];
                        b += working_space[i][k];
                     }
                     ay=a/b;
                     if(ay < 0)
                        ay = 0;

                     if(ay >= ssizey)
                        ay = ssizey - 1;

                     if(peak_index == 0){
                        fPositionX[0] = ax;
                        fPositionY[0] = ay;
                        peak_index = 1;
                     }

                     else{
                        for(k = 0, priz = 0; k < peak_index && priz == 0; k++){
                           if(working_space[shift+(Int_t)(ax+0.5)][15 * ssizey_ext + shift + (Int_t)(ay+0.5)] > working_space[shift+(Int_t)(fPositionX[k]+0.5)][15 * ssizey_ext + shift + (Int_t)(fPositionY[k]+0.5)])
                              priz = 1;
                        }
                        if(priz == 0){
                           if(k < fMaxPeaks){
                              fPositionX[k] = ax;
                              fPositionY[k] = ay;
                           }
                        }

                        else{
                           for(l = peak_index; l >= k; l--){
                              if(l < fMaxPeaks){
                                 fPositionX[l] = fPositionX[l - 1];
                                 fPositionY[l] = fPositionY[l - 1];
                              }
                           }
                           fPositionX[k - 1] = ax;
                           fPositionY[k - 1] = ay;
                        }
                        if(peak_index < fMaxPeaks)
                           peak_index += 1;
                     }
                  }
               }
            }
         }
      }
   }
   //writing back deconvolved spectrum
   for(i = 0; i < ssizex; i++){
      for(j = 0; j < ssizey; j++){
         dest[i][j] = working_space[i + shift][j + shift];
      }
   }
   i = (Int_t)(4 * sigma + 0.5);
   i = 4 * i;
   for (j = 0; j < ssizex + i; j++)
      delete[]working_space[j];
   delete[]working_space;
   fNPeaks = peak_index;
   return fNPeaks;
}

////////////////////////////////////////////////////////////////////////////////
/// static function (called by TH1), interface to TSpectrum2::Search

//Int_t TSpectrum2::StaticSearch(const TH1 *hist, Double_t sigma, Option_t *option, Double_t threshold)
//{
//   TSpectrum2 s;
//   return s.Search(hist,sigma,option,threshold);
//}

////////////////////////////////////////////////////////////////////////////////
/// static function (called by TH1), interface to TSpectrum2::Background

//TH1 *TSpectrum2::StaticBackground(const TH1 *hist,Int_t niter, Option_t *option)
//{
//   TSpectrum2 s;
//   return s.Background(hist,niter,option);
//}

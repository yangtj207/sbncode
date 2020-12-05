#pragma once 

#include "CAFAna/Core/Binning.h"
#include "CAFAna/Core/Cut.h"
#include "StandardRecord/Proxy/SRProxy.h"

#include "SBNAna/Vars/Binnings.h"
#include "SBNAna/Vars/NueVars.h"
#include "SBNAna/Vars/TruthVars.h"
#include "SBNAna/Vars/Vars.h"
#include "SBNAna/Cuts/Cuts.h"
#include "SBNAna/Cuts/NueCuts.h"
#include "SBNAna/Cuts/TruthCuts.h"

using namespace ana;

Color_t color_nue   = kBlue-7;
Color_t color_numu  = kGreen+1;
Color_t color_nc    = kMagenta;
Color_t color_other = kOrange+8;
Color_t color_cos   = kGray+2;
Style_t line_nue    = kSolid;
Style_t line_numu   = kSolid;
Style_t line_nc     = kDashed;
Style_t line_other  = kDotted;
Style_t line_cos    = kSolid;

// These are examples of useful structs to
// use when making a bunch of Spectra
struct PlotDef
{
  std::string suffix = "";
  std::string label = "";
  Binning bins = Binning::Simple(3,0,3);
  Var var = kCounting;
};

struct PlotDefSpill
{
  std::string suffix = "";
  std::string label = "";
  Binning bins = Binning::Simple(3,0,3);
  SpillMultiVar var = kCRTHitX;
};

const Binning kEnergyBinning    = Binning::Simple(40,0.,3000.); // to define
const Binning kDedxBinning      = Binning::Simple(20,0.,10); // to define
const Binning kGapBinning       = Binning::Simple(20,0.,10);
const Binning kDensityBinning 	= Binning::Simple(25,0.,10);
const Binning kOpenAngleBinning = Binning::Simple(20,0.,2);
const Binning kLengthBinning  	= Binning::Simple(40,0.,200);
const Binning kPEBinning        = Binning::Simple(60,0.,600);
const Binning kTimeBinning      = Binning::Simple(155,-1550.,1550.);
const Binning kFlashBinning     = Binning::Simple(40,-6.f,34.f);

// // In this example, we are making the following Spectra
std::vector<PlotDef> plots = 
  {{"count",      "Number of slices",        Binning::Simple(3,0,3), kCounting},
   {"bestdedx",   "Best plane dEdx (MeV)",   kDedxBinning,     kRecoShower_BestdEdx},  
   {"energy",     "Shower energy (MeV)",     kNueEnergyBinning, kRecoShower_Energy},
   {"length",     "Length (cm)",             kLengthBinning,    kRecoShower_Length},
   {"nuscore",    "Pandora #nu score",       kBDTBinning,       kSlcNuScore},
   {"flashscore", "Flash score",             kFlashBinning,     kSlcFlashScore}
   {"truthenergy","True #nu energy (GeV)",   kTruthLowEnergyBinning, kTruthEnergy},
 };

std::vector<PlotDefSpill> plots_spill =
  {{"crtx",   "CRT Hit Position X (cm)", kCRTXFDBinning, kCRTHitX},
  {"crty",    "CRT Hit Position Y (cm)", kCRTYFDBinning, kCRTHitY},
  {"crtz",    "CRT Hit Position Z (cm)", kCRTZFDBinning, kCRTHitZ},
  {"crttime", "CRT Hit Time (#mus)", kTimeBinning, kCRTHitTimeFD},
  {"crtpe",   "CRT PE", kPEBinning, kCRTHitPE}
};

// Selection Struc
struct SelDef
{
  std::string suffix = "";
  std::string label = "";
  Cut cut = kNoCut;
  int color = kBlack;
};

struct SelDefSpill
{
  std::string suffix = "";
  std::string label = "";
  SpillCut cut = kNoSpillCut;
  int color = kBlack;
};

const Cut kNuECC  = kIsNue && !kIsNC;
const Cut kNuMuCC = kIsNumu && !kIsNC;
const Cut kNC     = kIsNC;
const Cut kTotal  = kNoCut; // Get the total and substract everything else when plotting
const Cut kCosmic = !kHasNu;
const Cut kOtherNu = kHasNu && !(kNuECC || kNuMuCC || kNC);

// Step by step cuts
const Cut kContained = kFiducialVolumeFDCryo1;
const Cut kScoresCut = kSlcFlashMatchCut && kSlcNuScoreCut;
const Cut kFDRecoCut = kRecoShower && kNueNumShowersCut && kShowerdEdxCut && kShowerConvGapCut && kNueTrackLenCut && kShowerDensityCut && kShowerEnergyCut;
const Cut kFullFDCut = kContained && kScoresCut && kFDRecoCut;

std::vector<SelDef> types =
{
  {"nue",   "NuE CC",  kSlcIsRecoNu&&kNuECC,   color_nue},
  {"numu",  "NuMu CC", kSlcIsRecoNu&&kNuMuCC,  color_numu},
  {"nunc",  "NC",      kSlcIsRecoNu&&kNC,      color_nc},
  {"other", "Other",   kSlcIsRecoNu&&kOtherNu, color_other}
  {"total", "Total",   kSlcIsRecoNu&&kTotal,   color_other}
  {"cosmic", "Cosmic", kSlcIsRecoNu&&kCosmic,  color_cos}
};

std::vector<SelDef> sels ={
  {"nocut",     "No cut",             kNoCut,            kBlack},
  {"cont",      "Containment cut",    kContained,        kBlack},
  {"flash",     "Flash score cut",    kSlcFlashMatchCut, kBlack},
  {"pandnu",    "Neutrino score cut", kSlcNuScoreCut,    kBlack},  
  {"scores",    "Scores cut",         kScoresCut,        kBlack},
  {"fdrecocut", "Basic FD reco cut",  kFDRecoCut,        kBlack},
  {"cont_flash",  "Containment and flash score",    kContained && kSlcFlashMatchCut, kBlack},
  {"cont_pandnu", "Containment and neutrino score", kContained && kSlcNuScoreCut,    kBlack},
  {"cont_scores", "Containment and scores",         kContained && kScoresCut,        kBlack},
  {"everything",  "Full cut", kFullFDCut, kBlack}
  };

std::vector<SelDefSpill> sels_spill =
  {{"nocut_spill", "All Slices",         kNoSpillCut,   kBlack},
   {"crtveto_spill", "CRTVeto",          kCRTHitVetoFD, kBlue}
  };

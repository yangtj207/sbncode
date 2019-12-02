#ifndef _sbnanalysis_TrackReducer_data_hh_
#define _sbnanalysis_TrackReducer_data_hh_

#include "TVector3.h"

struct Track {
  std::vector<TVector3> trajectory; //!< The reconstructed trajectory [cm]
  std::vector<unsigned> track_daughters; //!< The list of "daughter" tracks to this one. Each entry is the index into the reco list of each daughter
  std::vector<unsigned> shower_daughters; //!< The list of "daughter" showers to this one. Each entry is the index into the reco list of each daughter
  int truth_match; //!< Match to true particle. -1 if no truth match exists. Otherwise, is the index into the truth list
};

struct Shower {
  TVector3 start; //!< Start location of shower [cm]
  TVector3 start_err; //!< Error in start location of shower [cm]
  TVector3 direction; //!< Initialial direction of shower (unit vector)
  TVector3 direction_err; //!< Error in initial direction of shower
  std::vector<unsigned> track_daughters; //!< The list of "daughter" tracks to this one. Each entry is the index into the reco list of each daughter
  std::vector<unsigned> shower_daughters; //!< The list of "daughter" showers to this one. Each entry is the index into the reco list of each daughter
  int truth_match; //!< Match to true particle. -1 if no truth match exists. Otherwise, is the index into the truth list
};

struct TrueParticle {
  int pid; //!< Particle ID
  float energy; //!< Initial energy of the particle [GeV]
  std::vector<TVector3> trajectory; //!< True trajectory of the particle [cm]
  std::vector<unsigned> daughters; //!< The list of true "daughter" particles to this one. Each entry is the index into the truth list of each daughter
  std::string process; //!< Process which created this particle
};

struct Tracks {
  std::vector<Shower> reco_showers;
  std::vector<Track> reco_tracks; // the list of reconstructed tracks
  std::vector<TrueParticle> truth; // the list of true particles
};


#endif

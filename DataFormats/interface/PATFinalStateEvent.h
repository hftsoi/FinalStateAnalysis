#ifndef PATFINALSTATEEVENT_MB433KP6
#define PATFINALSTATEEVENT_MB433KP6

/*
 *   A simple container for holding quantities that are defined across the whole
 *   event.
 *
 *   Author: Evan K. Friis, UW Madison
 *
 */

#include "FinalStateAnalysis/DataFormats/interface/PATFinalStateEventFwd.h"

#include "DataFormats/Common/interface/Ptr.h"
#include "DataFormats/Common/interface/PtrVector.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "DataFormats/METReco/interface/METFwd.h"
#include "DataFormats/METReco/interface/MET.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenFilterInfo.h"
#include "DataFormats/Provenance/interface/EventID.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/L1Trigger/interface/BXVector.h"
#include "DataFormats/L1Trigger/interface/Tau.h"

// For Rivet Tools
#include "SimDataFormats/HTXS/interface/HiggsTemplateCrossSections.h"

#include "TMatrixD.h"
#include <map>
#include <string>


class PATFinalStateEvent {
  public:

    PATFinalStateEvent();

    // minimal constructor used only for unit tests
    PATFinalStateEvent(
        const edm::Ptr<reco::Vertex>& pv,
        const edm::Ptr<pat::MET>& met
    );

    // This constructor should only be used in the initial production!
    // It automatically sets the version() to the current one.
    PATFinalStateEvent(
        double rho,
        const edm::Ptr<reco::Vertex>& pv,
        const std::vector<edm::Ptr<reco::Vertex>>& recoVertices,
        const edm::Ptr<pat::MET>& met,
        const TMatrixD& metCovariance,
        const std::vector<pat::MET> MVAMETs,
        const double metSig,
        const math::Error<2>::type metCov,
        const pat::TriggerEvent triggerEvent,
        const edm::RefProd<std::vector<pat::TriggerObjectStandAlone> >& triggerObjects,
        const edm::TriggerNames& names,
        const pat::PackedTriggerPrescales& triggerPrescale,
        const edm::TriggerResults& triggerResults,
        const BXVector<l1t::Tau>& l1extraIsoTaus, 
        const std::vector<PileupSummaryInfo>& puInfo,
        const lhef::HEPEUP& hepeup, // Les Houches info
        const reco::GenParticleRefProd& genParticles,
        const reco::GenJetRefProd& dressedParticles,
        const edm::RefProd<reco::METCollection>& rivetmetParticles,
        const std::vector<reco::GenJet> genHadronicTaus,
        const std::vector<reco::GenJet> genElectronicTaus,
        const std::vector<reco::GenJet> genMuonicTaus,
        const HTXS::HiggsClassification htxsRivetInfo,
        const edm::EventID& evtId,
        const GenEventInfoProduct& genEventInfoProd,
        const GenFilterInfo& genFilterInfo,
        bool isRealData,
        bool isEmbeddedSample,
        const edm::RefProd<pat::ElectronCollection>& electronRefProd,
        const edm::RefProd<pat::MuonCollection>& muonRefProd,
        const edm::RefProd<pat::TauCollection>& tauRefProd,
        const edm::RefProd<pat::JetCollection>& jetRefProd,
        const reco::PFCandidateRefProd& pfRefProd,
        const edm::RefProd<pat::PackedCandidateCollection>& packedPFRefProd,
        const reco::TrackRefProd& tracks,
        const reco::GsfTrackRefProd& gsfTracks,
	    const std::map<std::string, edm::Ptr<pat::MET> >& mets,
	    std::vector<float> lheweights,
            std::vector<float> geninfoweights,
            std::vector<float> prefiringweights,
        const int npNLO,
        const std::map<std::string, bool> filterFlagsMap
    );

    /// Get PV
    const edm::Ptr<reco::Vertex>& pv() const;
    /// Get all reconstructed vertices
    const std::vector<edm::Ptr<reco::Vertex>>& recoVertices() const;
    int numberVertices() const;
    /// Get PU information
    const std::vector<PileupSummaryInfo>& puInfo() const;
    /// Get the Les Houches event information
    const lhef::HEPEUP& lesHouches() const;
    /// Get the GenEventInfo product
    const GenEventInfoProduct& genEventInfo() const;

    /// Get weight for embedded samples
    const GenFilterInfo& generatorFilter() const;
    /// Get FastJet rho
    double rho() const;
    std::vector<float> lheweights() const;
    std::vector<float> geninfoweights() const;
    std::vector<float> prefiringweights() const;
    int npNLO() const;
    /// Get trigger information
    const pat::TriggerEvent& trig() const;
    const std::vector<pat::TriggerObjectStandAlone>& trigStandAlone() const;
    const edm::TriggerNames& names() const;
    const pat::PackedTriggerPrescales& trigPrescale() const;
    const edm::TriggerResults& trigResults() const;
    const BXVector<l1t::Tau>& l1extraIsoTaus() const;

    /*  These methods will be deprecated! */
    /// Get PFMET
    const edm::Ptr<pat::MET>& met() const;
    /// Get new MVAMET
    const std::vector<pat::MET> MVAMETs() const;
    // Get PF Met Significance
    const double metSig() const;
    // Get PF Met Covariance
    const double metCov(size_t i) const;
    /// Get MET covariance
    const TMatrixD& metCovariance() const;
    /// Get MET significance
    double metSignificance() const;

    // Get a given type of MET
    const edm::Ptr<pat::MET> met(const std::string& type) const;
    // Get 4-vector of the MET
    const reco::Candidate::LorentzVector met4vector(const std::string& type, const std::string& tag="", const int applyPhiCorr=0) const;
    // get met shift
    double metShift(const std::string& type,const std::string& var, const std::string& tag="") const;

    /// Get the event ID
    const edm::EventID& evtId() const;
    unsigned long long event() const { return evtId().event(); }
    // We also need a version that returns a double so the string parser used
    // to build the ntuples can deal with it. As long as the event number
    // never reaches 2^52, this should be fine.
    double eventDouble() const; 

    /// The following functions use the "SmartTrigger" functionality.
    /// They can be passed a comma separated list of paths:
    ///   hltResult("HLT_Mu15_v.*,HLT_Mu30_v.*")
    /// And the first path with the lowest prescale will be chosen.

    /// Get the result of the chosen path.  Returns -1 if it doesn't exist
    int hltResult(const std::string& pattern) const;

    /// Get the prescale of a given path.  Returns -1 if it doesn't exist
    int hltPrescale(const std::string& pattern) const;

    /// Get the group of a given path.  Returns -1 if it doesn't exist
    int hltGroup(const std::string& pattern) const;

    /// Determine if a candidate is matched to an HLT filter
    int matchedToFilter(const reco::Candidate& cand, const std::string& filter,
        double maxDeltaR = 0.3) const;

    /// Determine if a candidate is matched to an HLT path
    int matchedToPath(const reco::Candidate& cand, const std::string& pattern,
        double maxDeltaR = 0.3) const;

    //Finds a decay in MC
    const bool findDecay(const int pdgIdMother, const int pdgIdDaughter) const;

    const std::vector<float> findGenTau(const int pdgIdMother, const int pdgIdDaughter) const;
    const std::vector<float> findDressedLepton(const int pdgId) const;
    const std::vector<float> findRivetMet() const;
    const int findHTTfinalstate() const;

    // Get the gen mass for weighting
    float getGenMass() const;

    // Get the genHTT for weighting
    float genHTT() const;

    // Get the number of gen jets for weighting
    float numGenJets() const;

    /// Get a named event weight
    float weight(const std::string& name) const;
    void addWeight(const std::string& name, float weight);

    /// Get a named event flag
    int flag(const std::string& flag) const;
    void addFlag(const std::string& name, int flag);

    /// Is real data
    bool isRealData() const { return isRealData_; }
    bool isEmbeddedSample() const { return isEmbeddedSample_; }
    
    /// Access to object collections in the event
    const pat::ElectronCollection& electrons() const;
    const pat::MuonCollection& muons() const;
    const pat::JetCollection& jets() const;
    const pat::TauCollection& taus() const;
    //const pat::PhotonCollection& photons() const;

    /// Access to particle flow collections
    const reco::PFCandidateCollection& pflow() const;
    const pat::PackedCandidateCollection& packedPflow() const;

    //Access to GenParticleRefProd
    const reco::GenParticleRefProd genParticleRefProd() const {return genParticles_;} 
    const reco::GenJetRefProd dressedParticleRefProd() const {return dressedParticles_;}
    const edm::RefProd<reco::METCollection> rivetmetParticleRefProd() const {return rivetmetParticles_;}
    const std::vector<reco::GenJet> genHadronicTaus() const {return genHadronicTaus_;}
    const std::vector<reco::GenJet> genElectronicTaus() const {return genElectronicTaus_;}
    const std::vector<reco::GenJet> genMuonicTaus() const {return genMuonicTaus_;}

    // Access to HTXS Rivet info
    const HTXS::HiggsClassification getRivetInfo() const {return htxsRivetInfo_;}

    /// Get the version of the FinalState data formats API
    /// This allows you to detect which version of the software was used
    /// So that the methods can be update.
    /// The FSA_DATA_FORMAT_VERSION def at the top of the .cc file should be
    /// incremented after each change to the data format.
    char version() const { return fsaDataFormatVersion_; }
    float jetVariables(const reco::CandidatePtr jet, const std::string& myvar) const;


    // Method used when running MET filters and Bad Muon filters
    // in tagging mode, this allows one to retrieve the
    // associated flags
    const int getFilterFlags( std::string ) const;

  private:
    std::map<std::string, float> weights_;
    std::map<std::string, int> flags_;
    double rho_;
    pat::TriggerEvent triggerEvent_;
    edm::RefProd<std::vector<pat::TriggerObjectStandAlone> > triggerObjects_;
    edm::TriggerNames names_;
    pat::PackedTriggerPrescales triggerPrescale_;
    edm::TriggerResults triggerResults_;
    BXVector<l1t::Tau> l1extraIsoTaus_;
    edm::Ptr<reco::Vertex> pv_;
    std::vector<edm::Ptr<reco::Vertex>> recoVertices_;
    edm::Ptr<pat::MET> met_;
    TMatrixD metCovariance_;
    std::vector<pat::MET> MVAMETs_;
    double metSig_;
    math::Error<2>::type metCov_;
    std::vector<PileupSummaryInfo> puInfo_;
    lhef::HEPEUP lhe_;
    reco::GenParticleRefProd genParticles_;
    reco::GenJetRefProd dressedParticles_;
    edm::RefProd<reco::METCollection> rivetmetParticles_;
    std::vector<reco::GenJet> genHadronicTaus_;
    std::vector<reco::GenJet> genElectronicTaus_;
    std::vector<reco::GenJet> genMuonicTaus_;
    HTXS::HiggsClassification htxsRivetInfo_;
    edm::EventID evtID_;
    GenEventInfoProduct genEventInfoProduct_;
    GenFilterInfo generatorFilter_;
    bool isRealData_;
    bool isEmbeddedSample_;
    char fsaDataFormatVersion_;
    // Pointers to object collections in the event
    edm::RefProd<pat::ElectronCollection> electronRefProd_;
    edm::RefProd<pat::MuonCollection> muonRefProd_;
    edm::RefProd<pat::TauCollection> tauRefProd_;
    edm::RefProd<pat::JetCollection> jetRefProd_;
    //edm::RefProd<pat::PhotonCollection> phoRefProd_;
    reco::PFCandidateRefProd pfRefProd_;
    edm::RefProd<pat::PackedCandidateCollection> packedPFRefProd_;
    reco::TrackRefProd tracks_;
    reco::GsfTrackRefProd gsfTracks_;
    // List of different MET types
    std::map<std::string, edm::Ptr<pat::MET> > mets_;
    std::vector<float> lheweights_;
    std::vector<float> geninfoweights_;
    std::vector<float> prefiringweights_;
    int npNLO_;
    std::map<std::string, bool> filterFlagsMap_;

};

#endif /* end of include guard: PATFINALSTATEEVENT_MB433KP6 */

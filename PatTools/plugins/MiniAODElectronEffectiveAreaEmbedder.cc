//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//   MiniAODElectronEffectiveAreaEmbedder.cc                                //
//                                                                          //
//   Embeds electron effective areas using the EGamma POG recommendation.   //
//                                                                          //
//   Authors: Devin Taylor and Nate Woods, U. Wisconsin                     //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


// system includes
#include <memory>
#include <vector>
#include <iostream>

// CMS includes
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/Common/interface/View.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "RecoEgamma/EgammaTools/interface/EffectiveAreas.h"


class MiniAODElectronEffectiveAreaEmbedder : public edm::EDProducer
{
public:
  explicit MiniAODElectronEffectiveAreaEmbedder(const edm::ParameterSet&);
  ~MiniAODElectronEffectiveAreaEmbedder() {}

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  // Methods
  virtual void beginJob();
  virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup);
  virtual void endJob();

  float getEA(const edm::Ptr<pat::Electron>& elec, int year) const;

  // Data
  edm::EDGetTokenT<edm::View<pat::Electron> > electronCollectionToken_;
  const std::string label_; // label for the embedded userfloat
  const std::string year_; // year to choose the effective area
  const std::string filename_; //filename for effective area
  std::unique_ptr<std::vector<pat::Electron> > out; // Collection we'll output at the end
  EffectiveAreas effectiveAreas_;
};


// Constructors and destructors

MiniAODElectronEffectiveAreaEmbedder::MiniAODElectronEffectiveAreaEmbedder(const edm::ParameterSet& iConfig):
  electronCollectionToken_(consumes<edm::View<pat::Electron> >(iConfig.exists("src") ? 
                                                               iConfig.getParameter<edm::InputTag>("src") :
                                                               edm::InputTag("slimmedElectrons"))),
  label_(iConfig.exists("label") ?
	 iConfig.getParameter<std::string>("label") :
	 std::string("EffectiveArea")),
  year_(iConfig.getParameter<std::string>("year")),
  effectiveAreas_((iConfig.getParameter<edm::FileInPath>("configFile")).fullPath())
{
  produces<std::vector<pat::Electron> >();
}


void MiniAODElectronEffectiveAreaEmbedder::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  out = std::unique_ptr<std::vector<pat::Electron> >(new std::vector<pat::Electron>);

  edm::Handle<edm::View<pat::Electron> > electronsIn;

  iEvent.getByToken(electronCollectionToken_, electronsIn);

  for(edm::View<pat::Electron>::const_iterator ei = electronsIn->begin();
      ei != electronsIn->end(); ei++) // loop over electrons
    {
      const edm::Ptr<pat::Electron> eptr(electronsIn, ei - electronsIn->begin());

      out->push_back(*ei); // copy electron to save correctly in event

      float ea;
      ea = getEA(eptr,2016);
      if (year_=="2017")
	 ea = getEA(eptr,2017);
      if (year_=="2018")
         ea = getEA(eptr,2018);
	
      out->back().addUserFloat(label_, ea);
    }

  iEvent.put(std::move(out));
}

float MiniAODElectronEffectiveAreaEmbedder::getEA(const edm::Ptr<pat::Electron>& elec, int year) const
{
  //float abseta = fabs(elec->eta());
  //superCluster().eta
  float abseta = fabs(elec->superCluster()->eta());
  if (year==2017 or year==2018){
     if (abseta<1.000) return 0.1440;
     else if (abseta<1.479) return 0.1562;
     else if (abseta<2.000) return 0.1032;
     else if (abseta<2.200) return 0.0859;
     else if (abseta<2.300) return 0.1116;
     else if (abseta<2.400) return 0.1321;
     else return 0.1654;
  }

  else if (year==2016){
     if (abseta<1.000) return 0.1703;
     else if (abseta<1.479) return 0.1715;
     else if (abseta<2.000) return 0.1213;
     else if (abseta<2.200) return 0.1230;
     else if (abseta<2.300) return 0.1635;
     else if (abseta<2.400) return 0.1937;
     else return 0.2393;
  }

  else return 0.1440; //dummy value

}

void MiniAODElectronEffectiveAreaEmbedder::beginJob()
{}


void MiniAODElectronEffectiveAreaEmbedder::endJob()
{}


void
MiniAODElectronEffectiveAreaEmbedder::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(MiniAODElectronEffectiveAreaEmbedder);









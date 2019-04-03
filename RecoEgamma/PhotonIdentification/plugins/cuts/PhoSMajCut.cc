#include "PhysicsTools/SelectorUtils/interface/CutApplicatorWithEventContentBase.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "RecoEgamma/EgammaTools/interface/EffectiveAreas.h"


class PhoSMajCut : public CutApplicatorWithEventContentBase {
public:
  PhoSMajCut(const edm::ParameterSet& c);
  
  result_type operator()(const reco::PhotonPtr&) const final;

  void setConsumes(edm::ConsumesCollector&) final;
  void getEventContent(const edm::EventBase&) final;

  double value(const reco::CandidatePtr& cand) const final;

  CandidateType candidateType() const final { 
    return PHOTON; 
  }

private:
  // Cut values
  float _C1_EB;
  float _C1_EE;

  // Configuration
  float _barrelCutOff;
  // The isolations computed upstream
  edm::Handle<edm::ValueMap<float> > _sMajMap;


  constexpr static char sMaj_[] = "sMaj";

};

constexpr char PhoSMajCut::sMaj_[];


DEFINE_EDM_PLUGIN(CutApplicatorFactory,
		  PhoSMajCut,
		  "PhoSMajCut");

PhoSMajCut::PhoSMajCut(const edm::ParameterSet& c) :
  CutApplicatorWithEventContentBase(c),
  _C1_EB(c.getParameter<double>("C1_EB")),
  _C1_EE(c.getParameter<double>("C1_EE")),
  _barrelCutOff(c.getParameter<double>("barrelCutOff"))
{
  
  edm::InputTag maptag = c.getParameter<edm::InputTag>("sMajMap");
  contentTags_.emplace(sMaj_,maptag);

}

void PhoSMajCut::setConsumes(edm::ConsumesCollector& cc) {
  auto sMaj = 
    cc.consumes<edm::ValueMap<float> >(contentTags_[sMaj_]);
  contentTokens_.emplace(sMaj_,sMaj);

}

void PhoSMajCut::getEventContent(const edm::EventBase& ev) {  
  ev.getByLabel(contentTags_[sMaj_],_sMajMap);

}

CutApplicatorBase::result_type 
PhoSMajCut::
operator()(const reco::PhotonPtr& cand) const{  

  // in case we are by-value
  const std::string& inst_name = contentTags_.find(sMaj_)->second.instance();
  edm::Ptr<pat::Photon> pat(cand);
  float smajval = -1.0;
  if( _sMajMap.isValid() && _sMajMap->contains( cand.id() ) ) {
    smajval = (*_sMajMap)[cand];
  } else if ( _sMajMap.isValid() && _sMajMap->idSize() == 1 &&
              cand.id() == edm::ProductID() ) {
    // in case we have spoofed a ptr
    //note this must be a 1:1 valuemap (only one product input)
    smajval = _sMajMap->begin()[cand.key()];
  } else if ( _sMajMap.isValid() ){ // throw an exception
    smajval = (*_sMajMap)[cand];
  }

  // Figure out the cut value
  // The value is generally pt-dependent: C1 + pt * C2
  const double absEta = std::abs(cand->superCluster()->eta());
  const float sMajCutValue = 
    ( absEta < _barrelCutOff ? 
      _C1_EB 
      : 
      _C1_EE 
      );
  

  const float sMaj =  _sMajMap.isValid() ? smajval : pat->userFloat(inst_name);
  //  std::cout<<"inside cuts: "<<sMaj<< " cut value: "<<sMajCutValue<<std::endl;
  // Apply the cut and return the result
  // Scale by pT if the relative isolation is requested but avoid division by 0
  return sMaj < sMajCutValue;
}

double PhoSMajCut::
value(const reco::CandidatePtr& cand) const {
  reco::PhotonPtr pho(cand);

  // in case we are by-value
  const std::string& inst_name = contentTags_.find(sMaj_)->second.instance();
  edm::Ptr<pat::Photon> pat(cand);
  float smajval = -1.0;
  if( _sMajMap.isValid() && _sMajMap->contains( cand.id() ) ) {
    smajval = (*_sMajMap)[cand];
  } else if ( _sMajMap.isValid() && _sMajMap->idSize() == 1 &&
              cand.id() == edm::ProductID() ) {
    // in case we have spoofed a ptr
    //note this must be a 1:1 valuemap (only one product input)
    smajval = _sMajMap->begin()[cand.key()];
  } else if ( _sMajMap.isValid() ){ // throw an exception
    smajval = (*_sMajMap)[cand];
  }

  // Figure out the cut value
  // The value is generally pt-dependent: C1 + pt * C2
  //double absEta = std::abs(pho->superCluster()->eta());  
  
  float sMaj =_sMajMap.isValid() ? smajval : pat->userFloat(inst_name);

  // Divide by pT if the relative isolation is requested

  // Apply the cut and return the result
  return sMaj;
}

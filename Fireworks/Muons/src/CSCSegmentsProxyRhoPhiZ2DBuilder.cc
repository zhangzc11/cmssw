#include "Fireworks/Muons/interface/CSCSegmentsProxyRhoPhiZ2DBuilder.h"
#include "TEveTrack.h"
#include "TEveTrackPropagator.h"
#include "TEveManager.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/MuonDetId/interface/MuonSubdetId.h"
#include "TEveStraightLineSet.h"
#include "Fireworks/Core/interface/FWEventItem.h"
#include "RVersion.h"
#include "TEveGeoNode.h"
#include "Fireworks/Core/interface/TEveElementIter.h"
#include "TColor.h"
#include "TEvePolygonSetProjected.h"
#include "DataFormats/MuonDetId/interface/MuonSubdetId.h"
#include "Fireworks/Core/interface/DetIdToMatrix.h"
#include "DataFormats/MuonDetId/interface/DTChamberId.h"
#include "Fireworks/Core/interface/FWDisplayEvent.h"
#include "DataFormats/CSCRecHit/interface/CSCSegmentCollection.h"

CSCSegmentsProxyRhoPhiZ2DBuilder::CSCSegmentsProxyRhoPhiZ2DBuilder()
{
}

CSCSegmentsProxyRhoPhiZ2DBuilder::~CSCSegmentsProxyRhoPhiZ2DBuilder()
{
}

void CSCSegmentsProxyRhoPhiZ2DBuilder::buildRhoPhi(const FWEventItem* iItem, TEveElementList** product)
{
   build(iItem, product, true);
}

void CSCSegmentsProxyRhoPhiZ2DBuilder::buildRhoZ(const FWEventItem* iItem, TEveElementList** product)
{
   build(iItem, product, false);
}

void CSCSegmentsProxyRhoPhiZ2DBuilder::build(const FWEventItem* iItem, 
					    TEveElementList** product,
					    bool rhoPhiProjection)
{
   TEveElementList* tList = *product;

   if(0 == tList) {
      tList =  new TEveElementList(iItem->name().c_str(),"cscSegments",true);
      *product = tList;
      tList->SetMainColor(iItem->defaultDisplayProperties().color());
      gEve->AddElement(tList);
   } else {
      tList->DestroyElements();
   }
   
   const CSCSegmentCollection* segments = 0;
   iItem->get(segments);
   
   if(0 == segments ) {
      std::cout <<"failed to get CSC segments"<<std::endl;
      return;
   }
   unsigned int index = 0;
   for (  CSCSegmentCollection::id_iterator chamberId = segments->id_begin(); 
	 chamberId != segments->id_end(); ++chamberId, ++index )
     {
	const TGeoHMatrix* matrix = iItem->getGeom()->getMatrix( (*chamberId).rawId() );
	if ( ! matrix ) {
	   std::cout << "ERROR: failed get geometry of CSC chamber with det id: " <<
	     (*chamberId).rawId() << std::endl;
	   continue;
	}

	std::stringstream s;
	s << "chamber" << index;
	TEveStraightLineSet* segmentSet = new TEveStraightLineSet(s.str().c_str());
	TEvePointSet* pointSet = new TEvePointSet();
	segmentSet->SetLineWidth(3);
	segmentSet->SetMainColor(iItem->defaultDisplayProperties().color());
	pointSet->SetMainColor(iItem->defaultDisplayProperties().color());
        gEve->AddElement( segmentSet, tList );
        segmentSet->AddElement( pointSet );
	
	CSCSegmentCollection::range  range = segments->get(*chamberId);
	const double segmentLength = 15;
	for (CSCSegmentCollection::const_iterator segment = range.first;
	     segment!=range.second; ++segment)
	  {
	     Double_t localSegmentInnerPoint[3];
	     Double_t localSegmentOuterPoint[3];
	     Double_t globalSegmentInnerPoint[3];
	     Double_t globalSegmentOuterPoint[3];
	     
	     localSegmentOuterPoint[0] = segment->localPosition().x() + 
	       segmentLength* (fabs(segment->localDirection().z())>0.001 ? 
			       segment->localDirection().x()/segment->localDirection().z(): 0.001);
	     localSegmentOuterPoint[1] = segment->localPosition().y() + 
	       segmentLength* (fabs(segment->localDirection().z())>0.001 ? 
			       segment->localDirection().y()/segment->localDirection().z(): 0.001);
	     localSegmentOuterPoint[2] = segmentLength;
	     
	     localSegmentInnerPoint[0] = segment->localPosition().x() -
	       segmentLength* (fabs(segment->localDirection().z())>0.001 ? 
			       segment->localDirection().x()/segment->localDirection().z(): 0.001);
	     localSegmentInnerPoint[1] = segment->localPosition().y() - 
	       segmentLength* (fabs(segment->localDirection().z())>0.001 ? 
			       segment->localDirection().y()/segment->localDirection().z(): 0.001);
	     localSegmentInnerPoint[2] = -segmentLength;
	     
	     matrix->LocalToMaster( localSegmentInnerPoint, globalSegmentInnerPoint );
	     matrix->LocalToMaster( localSegmentOuterPoint, globalSegmentOuterPoint );
		
	     segmentSet->AddLine(globalSegmentInnerPoint[0], globalSegmentInnerPoint[1], globalSegmentInnerPoint[2],
				 globalSegmentOuterPoint[0], globalSegmentOuterPoint[1], globalSegmentOuterPoint[2] );
	  }
     }
}

REGISTER_FWRPZ2DDATAPROXYBUILDER(CSCSegmentsProxyRhoPhiZ2DBuilder,CSCSegmentCollection,"CSC-segments");

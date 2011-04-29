#pragma once
#include<yade/pkg/dem/Particle.hpp>
#include<yade/pkg/dem/ContactLoop.hpp>
#include<yade/core/MatchMaker.hpp>
#include<yade/pkg/dem/L6Geom.hpp>
// class MatchMaker;

class ElastMat: public Material{
	YADE_CLASS_BASE_DOC_ATTRS_CTOR(ElastMat,Material,"Elastic material with contact friction. See also :yref:`ElastMat`.",
		((Real,young,1e9,,"Young's modulus [Pa]"))
		((Real,poisson,.2,,"Poisson's ratio; this value should be only used in internal force computation, not for contacts."))
		, /*ctor*/ createIndex();
	);
	REGISTER_CLASS_INDEX(ElastMat,Material);
};
REGISTER_SERIALIZABLE(ElastMat);

class FrictMat: public ElastMat{
	YADE_CLASS_BASE_DOC_ATTRS_CTOR(FrictMat,ElastMat,"Elastic material with contact friction. See also :yref:`ElastMat`.",
		((Real,tanPhi,.5,,"Tangent of internal friction angle."))
		, /*ctor*/ createIndex();
	);
	REGISTER_CLASS_INDEX(FrictMat,ElastMat);
};
REGISTER_SERIALIZABLE(FrictMat);

class FrictPhys: public CPhys{
	YADE_CLASS_BASE_DOC_ATTRS_CTOR(FrictPhys,CPhys,"Physical parameters of contact with sliding",
		((Real,tanPhi,NaN,,"Tangent of friction angle"))
		((Real,kn,NaN,,"Normal stiffness"))
		((Real,kt,NaN,,"Tangent stiffness"))
		, /*ctor*/ createIndex();
	);
	REGISTER_CLASS_INDEX(FrictPhys,CPhys);
};
REGISTER_SERIALIZABLE(FrictPhys);

struct Cp2_FrictMat_FrictPhys: public CPhysFunctor{
	void go(const shared_ptr<Material>&, const shared_ptr<Material>&, const shared_ptr<Contact>&);
	FUNCTOR2D(FrictMat,FrictMat);
	YADE_CLASS_BASE_DOC_ATTRS(Cp2_FrictMat_FrictPhys,CPhysFunctor,"TODO",
		((shared_ptr<MatchMaker>,tanPhi,,,"Instance of :yref:`MatchMaker` determining how to compute contact friction angle. If ``None``, minimum value is used."))
		((Real,ktDivKn,.2,,"Ratio between tangent and normal stiffness on contact."))
	);
};
REGISTER_SERIALIZABLE(Cp2_FrictMat_FrictPhys);

class Law2_L6Geom_FrictPhys_IdealElPl: public LawFunctor{
	void go(const shared_ptr<CGeom>&, const shared_ptr<CPhys>&, const shared_ptr<Contact>&);
	FUNCTOR2D(L6Geom,FrictPhys);
	YADE_CLASS_BASE_DOC_ATTRS(Law2_L6Geom_FrictPhys_IdealElPl,LawFunctor,"Ideally elastic-plastic behavior.",
		((bool,noSlip,false,,"Disable plastic slipping"))
		((bool,noBreak,false,,"Disable removal of contacts when in tension."))
		((int,plastDissipIx,-1,(Attr::noSave|Attr::hidden),"Index of plastically dissipated energy"))
		((int,elastPotIx,-1,(Attr::hidden|Attr::noSave),"Index for elastic potential energy"))
	);
};
REGISTER_SERIALIZABLE(Law2_L6Geom_FrictPhys_IdealElPl);


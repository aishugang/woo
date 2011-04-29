
#pragma once
#include<yade/pkg/dem/Particle.hpp>
#include<yade/pkg/dem/ContactLoop.hpp>
#include<yade/pkg/dem/Sphere.hpp>

#ifdef YADE_OPENGL
	#include<yade/pkg/gl/Functors.hpp>
#endif

struct L6Geom: public CGeom{
	YADE_CLASS_BASE_DOC_ATTRS_CTOR(L6Geom,CGeom,"Geometry of particles in contact, defining relative velocities.",
		((Vector3r,vel,Vector3r::Zero(),,"Relative displacement rate in local coordinates, defined by :yref:`CGeom.node`"))
		((Vector3r,angVel,Vector3r::Zero(),,"Relative rotation rate in local coordinates"))
		((Real,uN,NaN,,"Normal displacement, distace of separation of particles (mathematically equal to integral of vel[0], but given here for numerically more stable results, as this component can be usually computed directly)."))
		((Vector2r,lengthHint,Vector2r::Zero(),,"Hint for Gp2 functor on how to distribute material stiffnesses."))
		((Matrix3r,trsf,Matrix3r::Identity(),,"Transformation (rotation) from global to local coordinates; only used internally, and is synchronized with :yref:`Node.ori` automatically. If the algorithm works with pure quaternions at some point (it is not stable now), can be removed safely."))
		, /*ctor*/ createIndex();
	);
	REGISTER_CLASS_INDEX(L6Geom,CGeom);
};
REGISTER_SERIALIZABLE(L6Geom);

struct Cg2_Sphere_Sphere_L6Geom: public CGeomFunctor{
		virtual bool go(const shared_ptr<Shape>& s1, const shared_ptr<Shape>& s2, const Vector3r& shift2, const bool& force, const shared_ptr<Contact>& C);
		// common code for {sphere,facet,wall}+sphere contacts
		void handleSpheresLikeContact(const shared_ptr<Contact>& C, const Vector3r& pos1, const Vector3r& vel1, const Vector3r& angVel1, const Vector3r& pos2, const Vector3r& vel2, const Vector3r& angVel2, const Vector3r& normal, const Vector3r& contPt, Real uN, Real r1, Real r2);

	enum { APPROX_NO_MID_TRSF=1, APPROX_NO_MID_NORMAL=2, APPROX_NO_RENORM_MID_NORMAL=4 };

	YADE_CLASS_BASE_DOC_ATTRS(Cg2_Sphere_Sphere_L6Geom,CGeomFunctor,"Incrementally compute :yref:`L6Geom` for contact of 2 spheres. Detailed documentation in py/_extraDocs.py",
		((bool,noRatch,true,,"FIXME: document what it really does."))
		((Real,distFactor,1,,"Create interaction if spheres are not futher than |distFactor|*(r1+r2). If negative, zero normal deformation will be set to be the initial value (otherwise, the geometrical distance is the 'zero' one)."))
		((int,trsfRenorm,100,,"How often to renormalize :yref:`trsf<L6Geom.trsf>`; if non-positive, never renormalized (simulation might be unstable)"))
		((int,approxMask,0,,"Selectively enable geometrical approximations (bitmask); add the values for approximations to be enabled.\n\n"
		"== ===============================================================\n"
		"1  use previous transformation to transform velocities (which are known at mid-steps), instead of mid-step transformation computed as quaternion slerp at t=0.5.\n"
		"2  do not take average (mid-step) normal when computing relative shear displacement, use previous value instead\n"
		"4  do not re-normalize average (mid-step) normal, if used.…\n"
		"== ===============================================================\n\n"
		"By default, the mask is zero, wherefore none of these approximations is used.\n"
		))
	);
	FUNCTOR2D(Sphere,Sphere);
	DEFINE_FUNCTOR_ORDER_2D(Sphere,Sphere);
	DECLARE_LOGGER;
};
REGISTER_SERIALIZABLE(Cg2_Sphere_Sphere_L6Geom);

#if 0
struct Ig2_Wall_Sphere_L3Geom: public Ig2_Sphere_Sphere_L3Geom{
	virtual bool go(const shared_ptr<Shape>& s1, const shared_ptr<Shape>& s2, const State& state1, const State& state2, const Vector3r& shift2, const bool& force, const shared_ptr<Interaction>& I);
	//virtual bool genericGo(bool is6Dof, const shared_ptr<Shape>& s1, const shared_ptr<Shape>& s2, const State& state1, const State& state2, const Vector3r& shift2, const bool& force, const shared_ptr<Interaction>& I);
	YADE_CLASS_BASE_DOC(Ig2_Wall_Sphere_L3Geom,Ig2_Sphere_Sphere_L3Geom,"Incrementally compute :yref:`L3Geom` for contact between :yref:`Wall` and :yref:`Sphere`. Uses attributes of :yref:`Ig2_Sphere_Sphere_L3Geom`.");
	FUNCTOR2D(Wall,Sphere);
	DEFINE_FUNCTOR_ORDER_2D(Wall,Sphere);
	DECLARE_LOGGER;
};
REGISTER_SERIALIZABLE(Ig2_Wall_Sphere_L3Geom);

#ifdef L3GEOM_SPHERESLIKE
struct Ig2_Facet_Sphere_L3Geom: public Ig2_Sphere_Sphere_L3Geom{
	// get point on segment A..B closest to P; algo: http://local.wasp.uwa.edu.au/~pbourke/geometry/pointline/
	static Vector3r getClosestSegmentPt(const Vector3r& P, const Vector3r& A, const Vector3r& B){ Vector3r BA=B-A; Real u=(P.dot(BA)-A.dot(BA))/(BA.squaredNorm()); return A+min(1.,max(0.,u))*BA; }
	virtual bool go(const shared_ptr<Shape>& s1, const shared_ptr<Shape>& s2, const State& state1, const State& state2, const Vector3r& shift2, const bool& force, const shared_ptr<Interaction>& I);
	YADE_CLASS_BASE_DOC(Ig2_Facet_Sphere_L3Geom,Ig2_Sphere_Sphere_L3Geom,"Incrementally compute :yref:`L3Geom` for contact between :yref:`Facet` and :yref:`Sphere`. Uses attributes of :yref:`Ig2_Sphere_Sphere_L3Geom`.");
	FUNCTOR2D(Facet,Sphere);
	DEFINE_FUNCTOR_ORDER_2D(Facet,Sphere);
	DECLARE_LOGGER;
};
REGISTER_SERIALIZABLE(Ig2_Facet_Sphere_L3Geom);
#endif

struct Ig2_Sphere_Sphere_L6Geom: public Ig2_Sphere_Sphere_L3Geom{
	virtual bool go(const shared_ptr<Shape>& s1, const shared_ptr<Shape>& s2, const State& state1, const State& state2, const Vector3r& shift2, const bool& force, const shared_ptr<Interaction>& I);
	YADE_CLASS_BASE_DOC(Ig2_Sphere_Sphere_L6Geom,Ig2_Sphere_Sphere_L3Geom,"Incrementally compute :yref:`L6Geom` for contact of 2 spheres.");
	FUNCTOR2D(Sphere,Sphere);
	DEFINE_FUNCTOR_ORDER_2D(Sphere,Sphere);
};
REGISTER_SERIALIZABLE(Ig2_Sphere_Sphere_L6Geom);


struct Law2_L3Geom_FrictPhys_ElPerfPl: public LawFunctor{
	virtual void go(shared_ptr<IGeom>&, shared_ptr<IPhys>&, Interaction*);
	FUNCTOR2D(L3Geom,FrictPhys);
	YADE_CLASS_BASE_DOC_ATTRS(Law2_L3Geom_FrictPhys_ElPerfPl,LawFunctor,"Basic law for testing :yref:`L3Geom`; it bears no cohesion (unless *noBreak* is ``True``), and plastic slip obeys the Mohr-Coulomb criterion (unless *noSlip* is ``True``).",
		((bool,noBreak,false,,"Do not break contacts when particles separate."))
		((bool,noSlip,false,,"No plastic slipping."))
		((int,plastDissipIx,-1,(Attr::noSave|Attr::hidden),"Index of plastically dissipated energy"))
		((int,elastPotentialIx,-1,(Attr::hidden|Attr::noSave),"Index for elastic potential energy (with O.trackEnergy)"))
	);
};
REGISTER_SERIALIZABLE(Law2_L3Geom_FrictPhys_ElPerfPl);

struct Law2_L6Geom_FrictPhys_Linear: public Law2_L3Geom_FrictPhys_ElPerfPl{
	virtual void go(shared_ptr<IGeom>&, shared_ptr<IPhys>&, Interaction*);
	FUNCTOR2D(L6Geom,FrictPhys);
	YADE_CLASS_BASE_DOC_ATTRS(Law2_L6Geom_FrictPhys_Linear,Law2_L3Geom_FrictPhys_ElPerfPl,"Basic law for testing :yref:`L6Geom` -- linear in both normal and shear sense, without slip or breakage.",
		((Real,charLen,1,,"Characteristic length with the meaning of the stiffness ratios bending/shear and torsion/normal."))
	);
};
REGISTER_SERIALIZABLE(Law2_L6Geom_FrictPhys_Linear);
#endif

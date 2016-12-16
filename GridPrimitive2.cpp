//**************************************************************************/
// Copyright (c) 1998-2007 Autodesk, Inc.
// All rights reserved.
// 
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information written by Autodesk, Inc., and are
// protected by Federal copyright law. They may not be disclosed to third
// parties or copied or duplicated in any form, in whole or in part, without
// the prior written consent of Autodesk, Inc.
//**************************************************************************/
// DESCRIPTION: Appwizard generated plugin
// AUTHOR: 
//***************************************************************************/

#include "GridPrimitive2.h"

#define GridPrimitive2_CLASS_ID	Class_ID(0x696927f7, 0x85e39692)

#define PBLOCK_REF	0

class GridPrimitive2 : public SimpleObject2
{
public:
	//Constructor/Destructor
	GridPrimitive2();
	virtual ~GridPrimitive2();

	// Member variable
  double objSize;

	// Parameter block handled by parent

	//Class vars
	static IObjParam *ip;			//Access to the interface

	// From BaseObject
	virtual CreateMouseCallBack* GetCreateMouseCallBack();

	// From Object
	virtual BOOL HasUVW();
	virtual void SetGenUVW(BOOL sw);
	virtual int IntersectRay(TimeValue t, Ray& ray, float& at, Point3& norm);

	// From Animatable
	virtual void BeginEditParams( IObjParam  *ip, ULONG flags,Animatable *prev);
	virtual void EndEditParams( IObjParam *ip, ULONG flags,Animatable *next);

	// From SimpleObject
	virtual void BuildMesh(TimeValue t);
	virtual void InvalidateUI();

	//From Animatable
	virtual Class_ID ClassID() {return GridPrimitive2_CLASS_ID;}
	virtual SClass_ID SuperClassID() { return GEOMOBJECT_CLASS_ID; }
	virtual void GetClassName(TSTR& s) {s = GetString(IDS_CLASS_NAME);}

	virtual RefTargetHandle Clone( RemapDir& remap );

	virtual int NumParamBlocks() { return 1; }					// return number of ParamBlocks in this instance
	virtual IParamBlock2* GetParamBlock(int /*i*/) { return pblock2; } // return i'th ParamBlock
	virtual IParamBlock2* GetParamBlockByID(BlockID id) { return (pblock2->ID() == id) ? pblock2 : NULL; } // return id'd ParamBlock

	void DeleteThis() { delete this; }
};



class GridPrimitive2ClassDesc : public ClassDesc2 
{
public:
	virtual int IsPublic() 							{ return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) 		{ return new GridPrimitive2(); }
	virtual const TCHAR *	ClassName() 			{ return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID SuperClassID() 				{ return GEOMOBJECT_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return GridPrimitive2_CLASS_ID; }
	virtual const TCHAR* Category() 				{ return GetString(IDS_CATEGORY); }

	virtual const TCHAR* InternalName() 			{ return _T("GridPrimitive2"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() 					{ return hInstance; }					// returns owning module handle
	

};


ClassDesc2* GetGridPrimitive2Desc() { 
	static GridPrimitive2ClassDesc GridPrimitive2Desc;
	return &GridPrimitive2Desc; 
}





enum { gridprimitive2_params };


//TODO: Add enums for various parameters
enum { 
	pb_size,
};




static ParamBlockDesc2 gridprimitive2_param_blk ( gridprimitive2_params, _T("params"),  0, GetGridPrimitive2Desc(), 
	P_AUTO_CONSTRUCT + P_AUTO_UI, PBLOCK_REF, 
	//rollout
	IDD_PANEL, IDS_PARAMS, 0, 0, NULL,
	// params
	pb_size, 			_T("size"), 		TYPE_FLOAT, 	P_ANIMATABLE, 	IDS_SPIN, 
		p_default, 		0.1f, 
		p_range, 		0.0f,1000.0f, 
		p_ui, 			TYPE_SPINNER,		EDITTYPE_FLOAT, IDC_EDIT,	IDC_SPIN, 0.01f, 
		p_end,
	p_end
	);


IObjParam *GridPrimitive2::ip			= NULL;

//--- GridPrimitive2 -------------------------------------------------------

GridPrimitive2::GridPrimitive2()
{
	GetGridPrimitive2Desc()->MakeAutoParamBlocks(this);
}

GridPrimitive2::~GridPrimitive2()
{
}

void GridPrimitive2::BeginEditParams(IObjParam* ip, ULONG flags, Animatable* prev)
{
	this->ip = ip;

	SimpleObject2::BeginEditParams(ip,flags,prev);
	GetGridPrimitive2Desc()->BeginEditParams(ip, this, flags, prev);
}

void GridPrimitive2::EndEditParams( IObjParam* ip, ULONG flags, Animatable* next )
{
	//TODO: Save plugin parameter values into class variables, if they are not hosted in ParamBlocks. 
	SimpleObject2::EndEditParams(ip,flags,next);
	GetGridPrimitive2Desc()->EndEditParams(ip, this, flags, next);

	this->ip = NULL;
}

//From Object
BOOL GridPrimitive2::HasUVW() 
{ 
	//TODO: Return whether the object has UVW coordinates or not
	return TRUE; 
}

void GridPrimitive2::SetGenUVW(BOOL sw) 
{
	if (sw==HasUVW()) 
		return;
	//TODO: Set the plugin's internal value to sw
}

//Class for interactive creation of the object using the mouse
class GridPrimitive2CreateCallBack : public CreateMouseCallBack {
	IPoint2 sp0;        //First point in screen coordinates
	GridPrimitive2* ob; //Pointer to the object 
	Point3 p0;          //First point in world coordinates
	Point3 p1;          //We added this point. Second point in world coordinates.
public:	
	int proc( ViewExp *vpt,int msg, int point, int flags, IPoint2 m, Matrix3& mat);
	void SetObj(GridPrimitive2 *obj) {ob = obj;}
};

int GridPrimitive2CreateCallBack::proc(ViewExp *vpt,int msg, int point, int /*flags*/, IPoint2 m, Matrix3& mat )
{
	if ( ! vpt || ! vpt->IsAlive() )
	{
		DbgAssert(!_T("Invalid viewport!"));
		return FALSE;
	}

	if (msg == MOUSE_POINT || msg == MOUSE_MOVE) {
		switch(point) {
		case 0: // only happens with MOUSE_POINT msg
			ob->suspendSnap = TRUE;
			sp0 = m;
			p0 = vpt->SnapPoint(m,m,NULL,SNAP_IN_PLANE);
			mat.SetTrans(p0);

			ob->pblock2->SetValue(pb_size, ob->ip->GetTime(), 0.0f);
			break;
		case 1:	{
      ob->suspendSnap = TRUE; 
      p1 = vpt->SnapPoint(m,m,NULL,SNAP_IN_PLANE);
      float speedFactor = 24.0f;

			float theSize = (Length(p1 - p0) / speedFactor);

			ob->pblock2->SetValue(pb_size, ob->ip->GetTime(), theSize);

			gridprimitive2_param_blk.InvalidateUI();
   //   ob->mesh.InvalidateGeomCache();
   //   ob->BuildMesh(t);
      if (msg == 1)
          return CREATE_STOP;
      break;
		}
  case 2:
      return CREATE_STOP;
		}
		ob->NotifyDependents(FOREVER, PART_ALL, REFMSG_CHANGE);
	} else {
		if (msg == MOUSE_ABORT) return CREATE_ABORT;
	}

	return TRUE;
}

static GridPrimitive2CreateCallBack GridPrimitive2CreateCB;

//From BaseObject
CreateMouseCallBack* GridPrimitive2::GetCreateMouseCallBack() 
{
	GridPrimitive2CreateCB.SetObj(this);
	return(&GridPrimitive2CreateCB);
}

//From SimpleObject
void GridPrimitive2::BuildMesh(TimeValue t)
{
	//TODO: Implement the code to build the mesh representation of the object
	//      using its parameter settings at the time passed. The plug-in should 
	//      use the data member mesh to store the built mesh.
	//      SimpleObject ivalid member should be updated. This can be done while
	//      retrieving values from pblock2.
	ivalid = FOREVER;

	float size, sizeLeft, sizeRight;
	pblock2->GetValue(pb_size, t, size, ivalid );

	mesh.setNumVerts(4);
  mesh.setNumFaces(3);
  mesh.setVert(0,size*Point3(0.0,0.0,0.0)); 
  mesh.setVert(1,size*Point3(10.0,0.0,0.0)); 
  mesh.setVert(2,size*Point3(0.0,10.0,0.0)); 
  mesh.setVert(3,size*Point3(0.0,0.0,10.0)); 

  mesh.faces[0].setVerts(0, 1, 2);
  mesh.faces[0].setEdgeVisFlags(1,1,0);
  mesh.faces[0].setSmGroup(2);
  mesh.faces[1].setVerts(3, 1, 0);
  mesh.faces[1].setEdgeVisFlags(1,1,0);
  mesh.faces[1].setSmGroup(2);
  mesh.faces[2].setVerts(0, 2, 3);
  mesh.faces[2].setEdgeVisFlags(1,1,0);
  mesh.faces[2].setSmGroup(4);

  mesh.InvalidateGeomCache();
}

void GridPrimitive2::InvalidateUI() 
{
	// Hey! Update the param blocks
	pblock2->GetDesc()->InvalidateUI();
}

// From Object
int GridPrimitive2::IntersectRay(TimeValue /*t*/, Ray& /*ray*/, float& /*at*/, Point3& /*norm*/)
{
	//TODO: Return TRUE after you implement this method
	return FALSE;
}

// From ReferenceTarget
RefTargetHandle GridPrimitive2::Clone(RemapDir& remap) 
{
	GridPrimitive2* newob = new GridPrimitive2();	
	//TODO: Make a copy all the data and also clone all the references
	newob->ReplaceReference(0,remap.CloneRef(pblock2));
	newob->ivalid.SetEmpty();
	BaseClone(this, newob, remap);
	return(newob);
}

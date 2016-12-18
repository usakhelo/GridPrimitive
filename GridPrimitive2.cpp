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
	GridPrimitive2();
	virtual ~GridPrimitive2();

	// Parameter block handled by parent

	//Class vars
	static IObjParam *ip;			//Access to the interface

	static int vPanels, hPanels, thickness;
	static Point3 grdPos;		
	static float grdWidth, grdHeight, grdLength;

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

enum { 
	pb_height, pb_width, pb_length, pb_hpanels, pb_vpanels, pb_thickness
};

static ParamBlockDesc2 gridprimitive2_param_blk ( gridprimitive2_params, _T("params"),  0, GetGridPrimitive2Desc(), 
	P_AUTO_CONSTRUCT + P_AUTO_UI, PBLOCK_REF, 
	//rollout
	IDD_PANEL, IDS_PARAMS, 0, 0, NULL,
	// params
	pb_height, 			_T("height"), 		TYPE_FLOAT, 	P_ANIMATABLE, 	IDS_SPIN, 
		p_default, 		0.0f, 
		p_range, 		0.0f, 10000.0f, 
		p_ui, 			TYPE_SPINNER,		EDITTYPE_UNIVERSE, IDC_H_EDIT,	IDC_H_SPIN, SPIN_AUTOSCALE, 
		p_end,
	pb_width, 			_T("width"), 		TYPE_FLOAT, 	P_ANIMATABLE, 	IDS_SPIN, 
		p_default, 		0.0f, 
		p_range, 		0.0f, 10000.0f, 
		p_ui, 			TYPE_SPINNER,		EDITTYPE_UNIVERSE, IDC_W_EDIT,	IDC_W_SPIN, SPIN_AUTOSCALE, 
		p_end,
	pb_length, 			_T("length"), 		TYPE_FLOAT, 	P_ANIMATABLE, 	IDS_SPIN, 
		p_default, 		0.0f, 
		p_range, 		0.0f, 10000.0f, 
		p_ui, 			TYPE_SPINNER,		EDITTYPE_UNIVERSE, IDC_L_EDIT,	IDC_L_SPIN, SPIN_AUTOSCALE, 
		p_end,
	pb_hpanels, 			_T("hpanels"), 		TYPE_INT, 	P_ANIMATABLE, 	IDS_SPIN, 
		p_default, 		1, 
		p_range, 		1, 100,
		p_ui, 			TYPE_SPINNER,		EDITTYPE_INT, IDC_HP_EDIT,	IDC_HP_SPIN, 1, 
		p_end,
	pb_vpanels, 			_T("vpanels"), 		TYPE_INT, 	P_ANIMATABLE, 	IDS_SPIN, 
		p_default, 		1, 
		p_range, 		1, 100,
		p_ui, 			TYPE_SPINNER,		EDITTYPE_INT, IDC_VP_EDIT,	IDC_VP_SPIN, 1, 
		p_end,
	pb_thickness, 			_T("thiñkness"), 		TYPE_INT, 	P_ANIMATABLE, 	IDS_SPIN, 
		p_default, 		1, 
		p_range, 		1, 100,
		p_ui, 			TYPE_SPINNER,		EDITTYPE_INT, IDC_TH_EDIT,	IDC_TH_SPIN, 1, 
		p_end,
	p_end
	);


IObjParam *GridPrimitive2::ip = NULL;
int GridPrimitive2::vPanels = 1;
int GridPrimitive2::hPanels = 1;
int GridPrimitive2::thickness = 1;
Point3 GridPrimitive2::grdPos = Point3(0,0,0);		
float GridPrimitive2::grdWidth = 0.0f; 
float GridPrimitive2::grdHeight = 0.0f;
float GridPrimitive2::grdLength = 0.0f;

//--- GridPrimitive2 -------------------------------------------------------

GridPrimitive2::GridPrimitive2()
{
	GetGridPrimitive2Desc()->MakeAutoParamBlocks(this);

	grdWidth = grdLength = grdHeight = 0.0f;

	pblock2->SetValue(pb_width, 0, grdWidth);
	pblock2->SetValue(pb_length, 0, grdLength);
	pblock2->SetValue(pb_height, 0, grdHeight);	
	pblock2->SetValue(pb_vpanels, 0, vPanels);
	pblock2->SetValue(pb_hpanels, 0, hPanels);
	pblock2->SetValue(pb_thickness, 0, thickness);
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

	ivalid = FOREVER;
	pblock2->GetValue(pb_vpanels, ip->GetTime(), vPanels, ivalid );
	pblock2->GetValue(pb_hpanels, ip->GetTime(), hPanels, ivalid );
	pblock2->GetValue(pb_thickness, ip->GetTime(), thickness, ivalid );

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
	IPoint2 sp0, sp1;   //points in screen coordinates
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

	if (msg == MOUSE_FREEMOVE)
	{
		vpt->SnapPreview(m,m,NULL, SNAP_IN_3D);
	}

	Point3 d;
	if (msg == MOUSE_POINT || msg == MOUSE_MOVE) {
		switch(point) {
			case 0: // only happens with MOUSE_POINT msg
				sp0 = m;
				
				ob->pblock2->SetValue(pb_width, ob->ip->GetTime(), 0.0f);
				ob->pblock2->SetValue(pb_length, ob->ip->GetTime(), 0.0f);
				ob->pblock2->SetValue(pb_height, ob->ip->GetTime(), 0.0f);
				ob->suspendSnap = TRUE;

				p0 = vpt->SnapPoint(m,m,NULL,SNAP_IN_PLANE);
				p1 = p0 + Point3(.01,.01,.01);
				mat.SetTrans(float(.5)*(p0+p1));

				break;
			case 1:	{
				//ob->suspendSnap = TRUE;
				sp1 = m;
				p1 = vpt->SnapPoint(m,m,NULL,SNAP_IN_PLANE);
				p1.z = p0.z + .01f;
				mat.SetTrans(float(.5)*(p0+p1));

				d = p1-p0;

				ob->pblock2->SetValue(pb_width, ob->ip->GetTime(), float(fabs(d.x)));
				ob->pblock2->SetValue(pb_length, ob->ip->GetTime(), float(fabs(d.y)));
				ob->pblock2->SetValue(pb_height, ob->ip->GetTime(), float(fabs(d.z)));

				gridprimitive2_param_blk.InvalidateUI();
      
				if (msg==MOUSE_POINT && (Length(sp1-sp0)<3 || Length(d)<0.1f)) {
					return CREATE_ABORT;
					}
				break;
			}
			case 2:
				#ifdef _OSNAP
					p1.z = p0.z + vpt->SnapLength(vpt->GetCPDisp(p0,Point3(0,0,1),sp1,m,TRUE));
				#else
					p1.z = p0.z + vpt->SnapLength(vpt->GetCPDisp(p1,Point3(0,0,1),sp1,m));
				#endif

				d = p1-p0;
				ob->pblock2->SetValue(pb_width, ob->ip->GetTime(), float(fabs(d.x)));
				ob->pblock2->SetValue(pb_length, ob->ip->GetTime(), float(fabs(d.y)));
				ob->pblock2->SetValue(pb_height, ob->ip->GetTime(), d.z);
				
				gridprimitive2_param_blk.InvalidateUI();

				if (msg==MOUSE_POINT) {
					ob->suspendSnap = FALSE;					
					return CREATE_STOP;
					}
				break;
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

	float width, height, length;
	Point3 va, vb, p;

	pblock2->GetValue(pb_width, t, width, ivalid );
	pblock2->GetValue(pb_height, t, height, ivalid );
	pblock2->GetValue(pb_length, t, length, ivalid );
	
	vb =  Point3(width, length, height)/2.0f;   
	va = -vb;
	va.z = 0.0f;
	vb.z = height;

	mesh.setNumVerts(4);
  mesh.setNumFaces(3);

	p.z = va.z;
	p.y = va.y;
	p.x = va.x;
  mesh.setVert(0, p);
	p.x = va.x + width;
  mesh.setVert(1, p);
	p.x = va.x;
	p.y = va.y + length;
  mesh.setVert(2, p);
	p.z = vb.z;
	p.y = va.y;
	p.x = va.x;
  mesh.setVert(3, p); 

  mesh.faces[0].setVerts(0, 1, 2);
  mesh.faces[0].setEdgeVisFlags(1,1,0);
  mesh.faces[0].setSmGroup(2);
  mesh.faces[1].setVerts(3, 1, 0);
  mesh.faces[1].setEdgeVisFlags(1,1,0);
  mesh.faces[1].setSmGroup(4);
  mesh.faces[2].setVerts(0, 2, 3);
  mesh.faces[2].setEdgeVisFlags(1,1,0);
  mesh.faces[2].setSmGroup(8);

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

///* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//
//Title : CMesh.h
//Author : Chad Vernon
//URL : http://www.c-unit.com
//
//Description : .X file wrappers
//
//Created :  08/13/2005
//Modified : 12/05/2005
//
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//#ifndef CMESH_H
//#define CMESH_H
//// Useful macros
//#define SAFE_RELEASE(x) if( x ) { (x)->Release(); (x) = NULL; }
//#define SAFE_DELETE(x) if( x ) { delete(x); (x) = NULL; }
//#define SAFE_DELETE_ARRAY(x) if( x ) { delete [] (x); (x) = NULL; }
//#define SHOWERROR(s,f,l) char buf[1024]; sprintf( buf, "File: %s\nLine: %d\n%s",f,l,s); MessageBox( 0, buf, "Error", 0 );
//#include "stdafx.h"
//#include "CWorldTransform.h"
//
//class CMesh
//{
//public:
//    CMesh();
//    ~CMesh() { Release(); }
//    BOOL Load( LPDIRECT3DDEVICE9 pDevice, char* file );
//    void Release();
//
//    LPD3DXMESH GetMesh() { return m_pMesh; }
//    DWORD GetNumMaterials() { return m_numMaterials; }
//    D3DMATERIAL9* GetMeshMaterial( int i ) { return &m_pMeshMaterials[i]; }
//    LPDIRECT3DTEXTURE9 GetMeshTexture( int i ) { return m_ppMeshTextures[i]; }
//
//private:
//    LPD3DXMESH m_pMesh;
//    DWORD m_numMaterials;
//    D3DMATERIAL9 *m_pMeshMaterials;
//    LPDIRECT3DTEXTURE9 *m_ppMeshTextures;
//};
//
//class CMeshInstance : public CWorldTransform
//{
//public:
//    CMeshInstance();
//    ~CMeshInstance() { Release(); }
//
//    void Release();
//    void SetMesh( CMesh* pMesh );
//    void Render( LPDIRECT3DDEVICE9 pevice );
//
//private:
//    CMesh* m_pMesh;
//};
//
//#endif
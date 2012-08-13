//------------------------------------------------------------------------------
// <copyright file="SkeletalViewer.h" company="Microsoft">
//     Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

// Declares of CSkeletalViewerApp class

#pragma once

#include "resource.h"
#include "NuiApi.h"
#include "DrawDevice.h"
//PeePeeSpeed - adding MData
#include "MData.h"
//End PPS

#define SZ_APPDLG_WINDOW_CLASS          _T("SkeletalViewerAppDlgWndClass")
#define WM_USER_UPDATE_FPS              WM_USER
#define WM_USER_UPDATE_COMBO            WM_USER+1
#define WM_USER_UPDATE_TRACKING_COMBO   WM_USER+2

class CSkeletalViewerApp
{
public:
    CSkeletalViewerApp();
    ~CSkeletalViewerApp();
    HRESULT                 Nui_Init( );
    HRESULT                 Nui_Init( OLECHAR * instanceName );
    void                    Nui_UnInit( );
    void                    Nui_GotDepthAlert( );
    void                    Nui_GotColorAlert( );
    void                    Nui_GotSkeletonAlert( );

    void                    Nui_Zero();
    void                    Nui_BlankSkeletonScreen( HWND hWnd, bool getDC );
    void                    Nui_DoDoubleBuffer(HWND hWnd,HDC hDC);
    void                    Nui_DrawSkeleton( NUI_SKELETON_DATA * pSkel, HWND hWnd, int WhichSkeletonColor );
    void                    Nui_DrawSkeletonId( NUI_SKELETON_DATA * pSkel, HWND hWnd, int WhichSkeletonColor );

    void                    Nui_DrawSkeletonSegment( NUI_SKELETON_DATA * pSkel, int numJoints, ... );
    void                    Nui_EnableSeatedTracking(bool seated);
    void                    Nui_SetApplicationTracking(bool applicationTracks);
    void                    Nui_SetTrackedSkeletons(int skel1, int skel2);

	// From PeePeeSpeed
	void					formatVectorsString( Vector4 * vArray[], int count );//this will need to be put into the MData Class
	void					attemptConnection();//attempts connection here.
	// end PPS

	// From James Bayliss
	// write and read to file for when no kinect is available
	int						lineCount;
	void					writeToFile(std::string);
	std::string				readFromFile(int);
	int						getTotalLine();

    RGBQUAD                 Nui_ShortToQuad_Depth( USHORT s );

    static LRESULT CALLBACK MessageRouter(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    LRESULT CALLBACK        WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    static void CALLBACK    Nui_StatusProcThunk(HRESULT hrStatus, const OLECHAR* instanceName, const OLECHAR* uniqueDeviceName, void* pUserData);
    void CALLBACK           Nui_StatusProc( HRESULT hrStatus, const OLECHAR* instanceName, const OLECHAR* uniqueDeviceName );

    HWND                    m_hWnd;
    HINSTANCE               m_hInstance;

    int MessageBoxResource(UINT nID, UINT nType);

private:
    void UpdateComboBox();
    void ClearComboBox();

    void UpdateTrackingComboBoxes();
    void UpdateTrackingFromComboBoxes();

    bool                    m_fUpdatingUi;
    TCHAR                   m_szAppTitle[256];    // Application title
    static DWORD WINAPI     Nui_ProcessThread(LPVOID pParam);
    DWORD WINAPI            Nui_ProcessThread();

    // Current kinect
    INuiSensor *            m_pNuiSensor;
    BSTR                    m_instanceId;

    // Draw devices
    //DrawDevice *            m_pDrawDepth; //removed all instances of m_pDrawDepth. Removed Window drawings of Depth
    DrawDevice *            m_pDrawColor;
    ID2D1Factory *          m_pD2DFactory;

    // thread handling
    HANDLE        m_hThNuiProcess;
    HANDLE        m_hEvNuiProcessStop;

    HANDLE        m_hNextDepthFrameEvent;
    HANDLE        m_hNextColorFrameEvent;
    HANDLE        m_hNextSkeletonEvent;
    HANDLE        m_pDepthStreamHandle;
    HANDLE        m_pVideoStreamHandle;
    HFONT         m_hFontFPS;
    HFONT         m_hFontSkeletonId;
    HPEN          m_Pen[NUI_SKELETON_COUNT];
    HDC           m_SkeletonDC;
    HBITMAP       m_SkeletonBMP;
    HGDIOBJ       m_SkeletonOldObj;
    int           m_PensTotal;
    POINT         m_Points[NUI_SKELETON_POSITION_COUNT];
    RGBQUAD       m_rgbWk[640*480];
    DWORD         m_LastSkeletonFoundTime;
    bool          m_bScreenBlanked;
    bool          m_bAppTracking;
    int           m_DepthFramesTotal;
    DWORD         m_LastDepthFPStime;
    int           m_LastDepthFramesTotal;
    DWORD         m_SkeletonIds[NUI_SKELETON_COUNT];
    DWORD         m_TrackedSkeletonIds[NUI_SKELETON_MAX_TRACKED_COUNT];
    ULONG_PTR     m_GdiplusToken;
};




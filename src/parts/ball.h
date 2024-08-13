#pragma once

#include "resource.h"
#include "renderer/Renderable.h"

class Ball;

// Helper class used for projecting sphere points, which is then used to compensate for projection stretch if anti-ball-stretch is enabled
class AntiStretchHelper
{
public:
   // The number of points matters: 12 points are not enough, 35 and more seems to give good results
   static constexpr int npts = 25;
   float m_stretchFitPoints[3 * npts];

   AntiStretchHelper()
   {
      const double a = 4.0 * M_PI / npts, d = sqrt(a);
      const int nTheta = (int)round(M_PI / d);
      const double dTheta = M_PI / nTheta, dPhi = a / dTheta;
      for (int pos = 0, j = 0; j < nTheta; j++)
      {
         const double theta = ((double)j + 0.5) * M_PI / (double)nTheta;
         const int nPhi = (int)round(2.0 * M_PI * sin(theta) / dPhi);
         for (int i = 0; i < nPhi; i++)
         {
            const double phi = (double)i * (2.0 * M_PI) / (double)nPhi;
            m_stretchFitPoints[pos++] = (float)(sin(theta) * cos(phi));
            m_stretchFitPoints[pos++] = (float)(sin(theta) * sin(phi));
            m_stretchFitPoints[pos++] = (float)cos(theta);
         }
         // npts = pos / 3;
      }
   }
};

class BallEx :
   public CComObjectRootEx<CComSingleThreadModel>,
   public CComCoClass<BallEx, &CLSID_Ball>,
   public IDispatchImpl<IBall, &IID_IBall, &LIBID_VPinballLib>,
   public IFireEvents,
   public IDebugCommands,
   public Renderable
{
public:
   BallEx();
   ~BallEx();

   DECLARE_REGISTRY_RESOURCEID(IDR_BALL)

   DECLARE_PROTECT_FINAL_CONSTRUCT()

   BEGIN_COM_MAP(BallEx)
      COM_INTERFACE_ENTRY(IBall)
      COM_INTERFACE_ENTRY(IDispatch)
   END_COM_MAP()

   virtual void RenderSetup(RenderDevice *device);
   virtual void UpdateAnimation(const float diff_time_msec);
   virtual void Render(const unsigned int renderMask);
   virtual void RenderRelease();

   bool m_antiStretch = false;

private:
   RenderDevice *m_rd = nullptr;
   static AntiStretchHelper m_ash;

   // IBall
public:
   STDMETHOD(get_Name)(/*[out, retval]*/ BSTR *pVal);
   STDMETHOD(put_Name)(/*[in]*/ BSTR newVal);
   STDMETHOD(get_FrontDecal)(/*[out, retval]*/ BSTR *pVal);
   STDMETHOD(put_FrontDecal)(/*[in]*/ BSTR newVal);
   STDMETHOD(get_DecalMode)(/*[out, retval]*/ VARIANT_BOOL *pVal);
   STDMETHOD(put_DecalMode)(/*[in]*/ VARIANT_BOOL newVal);
   STDMETHOD(get_Image)(/*[out, retval]*/ BSTR *pVal);
   STDMETHOD(put_Image)(/*[in]*/ BSTR newVal);
   STDMETHOD(get_Color)(/*[out, retval]*/ OLE_COLOR *pVal);
   STDMETHOD(put_Color)(/*[in]*/ OLE_COLOR newVal);
   STDMETHOD(get_VelZ)(/*[out, retval]*/ float *pVal);
   STDMETHOD(put_VelZ)(/*[in]*/ float newVal);
   STDMETHOD(get_Z)(/*[out, retval]*/ float *pVal);
   STDMETHOD(put_Z)(/*[in]*/ float newVal);
   STDMETHOD(get_VelY)(/*[out, retval]*/ float *pVal);
   STDMETHOD(put_VelY)(/*[in]*/ float newVal);
   STDMETHOD(get_VelX)(/*[out, retval]*/ float *pVal);
   STDMETHOD(put_VelX)(/*[in]*/ float newVal);
   STDMETHOD(get_AngVelZ)(/*[out, retval]*/ float *pVal);
   STDMETHOD(put_AngVelZ)(/*[out, retval]*/ float newVal) override { return S_OK; } // No-op to not break tables.
   STDMETHOD(get_AngVelY)(/*[out, retval]*/ float *pVal);
   STDMETHOD(put_AngVelY)(/*[out, retval]*/ float newVal) override { return S_OK; } // No-op to not break tables.
   STDMETHOD(get_AngVelX)(/*[out, retval]*/ float *pVal);
   STDMETHOD(put_AngVelX)(/*[out, retval]*/ float newVal) override { return S_OK; } // No-op to not break tables.
   STDMETHOD(get_AngMomZ)(/*[out, retval]*/ float *pVal);
   STDMETHOD(put_AngMomZ)(/*[in]*/ float newVal);
   STDMETHOD(get_AngMomY)(/*[out, retval]*/ float *pVal);
   STDMETHOD(put_AngMomY)(/*[in]*/ float newVal);
   STDMETHOD(get_AngMomX)(/*[out, retval]*/ float *pVal);
   STDMETHOD(put_AngMomX)(/*[in]*/ float newVal);
   STDMETHOD(get_Y)(/*[out, retval]*/ float *pVal);
   STDMETHOD(put_Y)(/*[in]*/ float newVal);
   STDMETHOD(get_X)(/*[out, retval]*/ float *pVal);
   STDMETHOD(put_X)(/*[in]*/ float newVal);
   STDMETHOD(get_Radius)(/*[out, retval]*/ float *pVal);
   STDMETHOD(put_Radius)(/*[in]*/ float newVal);
   STDMETHOD(get_Mass)(/*[out, retval]*/ float *pVal);
   STDMETHOD(put_Mass)(/*[in]*/ float newVal);
   STDMETHOD(get_UserValue)(/*[out, retval]*/ VARIANT *pVal);
   STDMETHOD(put_UserValue)(VARIANT *newVal);
   STDMETHOD(get_ID)(/*[out, retval]*/ int *pVal);
   STDMETHOD(put_ID)(/*[in]*/ int newVal);
   STDMETHOD(DestroyBall)(/*[out, retval]*/ int *pVal);
   STDMETHOD(get_BulbIntensityScale)(/*[out, retval]*/ float *pVal);
   STDMETHOD(put_BulbIntensityScale)(/*[in]*/ float newVal);
   STDMETHOD(get_ReflectionEnabled)(/*[out, retval]*/ VARIANT_BOOL *pVal);
   STDMETHOD(put_ReflectionEnabled)(/*[in]*/ VARIANT_BOOL newVal);
   STDMETHOD(get_PlayfieldReflectionScale)(/*[out, retval]*/ float *pVal);
   STDMETHOD(put_PlayfieldReflectionScale)(/*[in]*/ float newVal);
   STDMETHOD(get_ForceReflection)(/*[out, retval]*/ VARIANT_BOOL *pVal);
   STDMETHOD(put_ForceReflection)(/*[in]*/ VARIANT_BOOL newVal);
   STDMETHOD(get_Visible)(/*[out, retval]*/ VARIANT_BOOL *pVal);
   STDMETHOD(put_Visible)(/*[in]*/ VARIANT_BOOL newVal);

   void FireGroupEvent(const int dispid) final {}
   IDispatch *GetDispatch() final { return ((IDispatch *) this); }
   const IDispatch *GetDispatch() const final { return ((const IDispatch *) this); }
   IDebugCommands *GetDebugCommands() final { return (IDebugCommands *) this; }

   // IDebugCommands
   void GetDebugCommands(vector<int> &pvids, vector<int> &pvcommandid) final;
   void RunDebugCommand(int id) final;

   Ball *m_pball;

private:
   VARIANT m_uservalue;
};

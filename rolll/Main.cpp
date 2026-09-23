#include "LoopRoll.h"

#include <cstring>

HRESULT VDJ_API DllGetClassObject(
    const GUID &rclsid,
    const GUID &riid,
    void **ppObject)
{
    if (!ppObject)
        return E_POINTER;

    *ppObject = nullptr;

    if (std::memcmp(
            &rclsid,
            &CLSID_VdjPlugin8,
            sizeof(GUID)) == 0 &&
        std::memcmp(
            &riid,
            &IID_IVdjPluginBuffer8,
            sizeof(GUID)) == 0)
    {
        *ppObject = new LoopRollPlugin();
        return S_OK;
    }

    return CLASS_E_CLASSNOTAVAILABLE;
}

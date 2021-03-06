#include "stdafx_ao.h"
#include "ScreenManager.hpp"
#include "Function.hpp"
#include "ResourceManager.hpp"

START_NS_AO

ALIVE_VAR(1, 0x4FF7C8, ScreenManager*, pScreenManager_4FF7C8, nullptr);

EXPORT Camera* Camera::ctor_4446E0()
{
    field_0_array.ctor_4043E0(10);
    field_30_flags &= ~1u;
    field_C_ppBits = nullptr;
    return this;
}


EXPORT void Camera::dtor_444700()
{
    ResourceManager::FreeResource_455550(field_C_ppBits);

    for (int i = 0; i < field_0_array.Size(); i++)
    {
        BYTE** ppRes = field_0_array.ItemAt(i);
        if (!ppRes)
        {
            break;
        }

        ResourceManager::FreeResource_455550(ppRes);
        i = field_0_array.RemoveAt(i);
    }

    field_0_array.dtor_404440();
}


EXPORT void CC Camera::On_Loaded_4447A0(Camera* pThis)
{
    pThis->field_30_flags |= 1u;
    pThis->field_C_ppBits = ResourceManager::GetLoadedResource_4554F0(ResourceManager::Resource_Bits, pThis->field_10_resId, 1, 0);
}

EXPORT void ScreenManager::MoveImage_406C40()
{
    NOT_IMPLEMENTED();
}

EXPORT void ScreenManager::DecompressToVRam_407110(unsigned __int16** /*ppBits*/)
{
    NOT_IMPLEMENTED();
}

EXPORT void ScreenManager::InvalidateRect_406CC0(int /*x*/, int /*y*/, signed int /*width*/, signed int /*height*/)
{
    NOT_IMPLEMENTED();
}

ScreenManager* ScreenManager::ctor_406830(BYTE** ppBits, FP_Point* pCameraOffset)
{
    ctor_487E10(1);
    SetVTable(this, 0x4BA230);

    field_10_pCamPos = pCameraOffset;

    field_6_flags.Set(Options::eSurviveDeathReset_Bit9);
    field_6_flags.Set(Options::eUpdateDuringCamSwap_Bit10);

    Init_4068A0(ppBits);
    return this;
}

void ScreenManager::Init_4068A0(BYTE** /*ppBits*/)
{
    NOT_IMPLEMENTED();
}

BaseGameObject* ScreenManager::VDestructor(signed int flags)
{
    return vdtor_407290(flags);
}

void ScreenManager::UnsetDirtyBits_FG1_406EF0()
{
    NOT_IMPLEMENTED();
}

void ScreenManager::InvalidateRect_406E40(int /*x*/, int /*y*/, signed int /*width*/, signed int /*height*/, int /*idx*/)
{
    NOT_IMPLEMENTED();
}

EXPORT ScreenManager* ScreenManager::vdtor_407290(signed int /*flags*/)
{
    NOT_IMPLEMENTED();
    return this;
}

END_NS_AO

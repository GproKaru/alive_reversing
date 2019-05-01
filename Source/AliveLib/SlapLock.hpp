#pragma once

#include "FunctionFwd.hpp"
#include "BaseAliveGameObject.hpp"
#include "Path.hpp"


struct SlapLockWhirlWind_State
{
    Types field_0_type;
    __int16 field_2_switch_id;
};
ALIVE_ASSERT_SIZEOF_ALWAYS(SlapLockWhirlWind_State, 0x4);

class SlapLockWhirlWind : public BaseGameObject
{
public:
    EXPORT SlapLockWhirlWind* ctor_43D7E0(__int16 doorNumber, __int16 switchId, FP xpos, FP ypos, FP scale);
    virtual BaseGameObject* VDestructor(signed int flags) override;
    virtual void VUpdate() override;
    virtual int VGetSaveState(BYTE* pSaveBuffer) override;
    static EXPORT int CC CreateFromSaveState_43DC20(const BYTE* pBuffer);

private:
    EXPORT void dtor_43DA70();
    EXPORT SlapLockWhirlWind* vdtor_43DA40(signed int flags);
    EXPORT signed int vGetSaveState_43DC50(SlapLockWhirlWind_State* pSaveState);
    EXPORT void vUpdate_43DA90();

public:
    __int16 SwitchId() const;

private:
    FP field_20_xpos;
    FP field_24_ypos;
    FP field_28_scale;
    FP field_2C_door_x;
    FP field_30_door_y;
    FP field_34_door_scale;
    int field_38_orb_whirlwind_id;
    __int16 field_3C_state;
    __int16 field_3E_pad;
    int field_40_timer;
    __int16 field_44_switch_id;
    __int16 field_46_pad;
};
ALIVE_ASSERT_SIZEOF(SlapLockWhirlWind, 0x48);

struct Path_SlapLock : public Path_TLV
{
    __int16 field_10_scale;
    __int16 field_12_target_tomb_id1;
    __int16 field_14_target_tomb_id2;
    __int16 field_16_bPersistant;
    __int16 field_18_has_ghost;
    __int16 field_1A_has_powerup;
    __int16 field_1C_powerup_id;
    __int16 field_1E_option_id;
};
ALIVE_ASSERT_SIZEOF_ALWAYS(Path_SlapLock, 0x20);

class SlapLock : public BaseAliveGameObject
{
public:
    EXPORT SlapLock* ctor_43DC80(Path_SlapLock* pTlv, int tlvInfo);

    EXPORT void dtor_43DF00();

    virtual void VUpdate() override
    {
        // TODO
    }

    virtual BaseGameObject* VDestructor(signed int flags) override
    {
        return vdtor_43DED0(flags);
    }

    virtual void VScreenChanged() override
    {
        vScreenChanged_43E840();
    }

    virtual __int16 VTakeDamage_408730(BaseGameObject* /*pFrom*/) override
    {
        // TODO
        return 0;
    }

private:
    EXPORT SlapLock* vdtor_43DED0(signed int flags);

    EXPORT void vScreenChanged_43E840();

    EXPORT void GiveInvisiblity_43E880();

private:
    __int16 field_116;
    Path_SlapLock *field_118_pTlv;
    int field_11C_tlvInfo;
    __int16 field_120_state;
    __int16 field_122;
    int field_124_timer1;
    FP field_128_midX;
    FP field_12C_midY;
    __int16 field_130_has_ghost;
    __int16 field_132;
    int field_134_id;
    int field_138_possesion_flicker_id;
    int field_13C_timer2;
};
ALIVE_ASSERT_SIZEOF(SlapLock, 0x140);

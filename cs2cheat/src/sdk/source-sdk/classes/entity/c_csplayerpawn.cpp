#include "c_csplayerpawn.hpp"

#include "../../../interfaces/interfaces.hpp"
#include "../../../memory/memory.hpp"

bool C_CSPlayerPawn::IsEnemyWithTeam(int team) {
    static ConVar* mp_teammates_are_enemies =
        interfaces::pCvar->FindVarByName("mp_teammates_are_enemies");

    CCSPlayerController* pPlayerController =
        m_hController().Get<CCSPlayerController>();
    if (!pPlayerController) return true;

    if (pPlayerController->m_bIsLocalPlayerController()) return false;

    // We want  to make sure that Deathmatch still show different colors (just
    // for visualization while testing)
    // if (mp_teammates_are_enemies->GetValue<bool>()) return true;

    return m_iTeamNum() != team;
}

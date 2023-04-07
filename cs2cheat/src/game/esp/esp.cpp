#include "esp.hpp"

#include "../../sdk/interfaces/interfaces.hpp"

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include <filesystem>
#include <chrono>
#include <iostream>
#include <fstream>
#include "../../utils/utils.hpp"

namespace fs = std::filesystem;

// Keep track of every second
volatile std::time_t last = std::time(0);

void esp::Render() {
    if (!interfaces::pEngine->IsInGame()) return;

    CCSPlayerController* pLocalPlayerController =
        interfaces::pEntitySystem->GetLocalPlayerController();
    if (!pLocalPlayerController) return;

    // Create filename out of current time
    std::stringstream imgss("");
    imgss << "./dump/images/" << static_cast<long int>(last) << ".jpg";

    // Create stringstream which will contain YOLO-format coordinates for this
    // frame
    std::stringstream labelss, contentss;
    labelss << "./dump/labels/" << static_cast<long int>(last) << ".txt";

    ImDrawList* pBackgroundDrawList = ImGui::GetBackgroundDrawList();
    for (int i = 1; i <= MAX_PLAYERS; ++i) {
        CCSPlayerController* pPlayerController =
            interfaces::pEntitySystem->GetBaseEntity<CCSPlayerController>(i);
        if (!pPlayerController || !pPlayerController->IsPlayerController() ||
            !pPlayerController->m_bPawnIsAlive())
            continue;

        C_CSPlayerPawn* pPawn =
            pPlayerController->m_hPawn().Get<C_CSPlayerPawn>();
        if (!pPawn) continue;

        const bool isEnemy =
            pPawn->IsEnemyWithTeam(pLocalPlayerController->m_iTeamNum());
        if (bIgnoreTeammates && !isEnemy) continue;

        BBox_t bBox;
        if (!pPawn->GetBoundingBox(bBox)) continue;

        const ImVec2 min = {bBox.x, bBox.y};
        const ImVec2 max = {bBox.w, bBox.h};

        // If it has been one second since the last time we saved the image, save a new one
        if (std::difftime(std::time(0), last) >= 1) {
			last = std::time(0);

            contentss << (pLocalPlayerController->m_iTeamNum() == 0) ? "t " : "ct ";

            // Get window height and width from imgui
            ImVec2 winSize = ImGui::GetWindowSize();

            // Normalize the coordinate values to be between 0 and 1
            contentss << (min.x / winSize.x) << " " << (min.y / winSize.y) << " "
					  << ((max.x - min.x) / winSize.x) << " "
					  << ((max.y - min.y) / winSize.y) << std::endl;

            //utils::CaptureWindow((wchar_t*)imgss.str().c_str());
		}

        if (bBoxEsp) {
            pBackgroundDrawList->AddRect(
                min, max,
                isEnemy ? IM_COL32(255, 0, 0, 255) : IM_COL32(0, 255, 0, 255));
            pBackgroundDrawList->AddRect(min - ImVec2{1.f, 1.f},
                                         max + ImVec2{1.f, 1.f},
                                         IM_COL32(0, 0, 0, 255));
            pBackgroundDrawList->AddRect(min + ImVec2{1.f, 1.f},
                                         max - ImVec2{1.f, 1.f},
                                         IM_COL32(0, 0, 0, 255));
        }
        if (bNameEsp) {
            const char* szName = pPlayerController->m_sSanitizedPlayerName();
            if (szName && strlen(szName) > 0) {
                const ImVec2 textSize = ImGui::CalcTextSize(szName);
                const ImVec2 textPos =
                    ImFloor({(min.x + max.x - textSize.x) / 2.f,
                             min.y - textSize.y - 2.f});
                pBackgroundDrawList->AddText(textPos + ImVec2{1, 1},
                                             IM_COL32(0, 0, 0, 255), szName);
                pBackgroundDrawList->AddText(
                    textPos, IM_COL32(255, 255, 255, 255), szName);
            }
        }
        if (bHealthbar) {
            const int iClampedHp =
                std::min(pPlayerController->m_iPawnHealth(), 100u);

            const ImVec2 barMin = min - ImVec2{5, 0};
            const ImVec2 barMax = ImVec2{min.x - 2, max.y};

            const float green = iClampedHp * 2.f * 2.55f;
            const float greenClamped = (std::min)(255.f, green);
            const float red = (std::min)(255.f, 510 - green);

            const float height = ((barMax.y - barMin.y) * iClampedHp) / 100.f;

            pBackgroundDrawList->AddRectFilled(barMin - ImVec2{0, 1},
                                               barMax + ImVec2{0, 1},
                                               IM_COL32(0, 0, 0, 255));
            if (iClampedHp > 0) {
                pBackgroundDrawList->AddRectFilled(
                    ImVec2{barMin.x + 1, barMax.y - (std::max)(1.f, height)},
                    ImVec2{barMax.x - 1, barMax.y},
                    IM_COL32(red, greenClamped, 0, 255));
            }
        }
    }

    
    // Save label file
    std::ofstream file(labelss.str());
    file << contentss.str() << std::endl;
    file.close();
}

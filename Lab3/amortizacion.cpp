//ENUNCIADO: Tabla de amortizacion
//PARTICIPANTES: 1101331 Asier Ochoa ; Yeuris Terrero | 1099399 ; Carlos Garcia | 1101629 ; Miguel Angel | 1100685
//FECHA:29/05/22

#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

class TablaAmortizacion{
    public:
        float GetQuota(float p, float i, float m, float n);
};

int main(){
    int width = 800;
    InitWindow(width, 600, "Tabla de Amortizacion");
    rlImGuiSetup(true);
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        rlImGuiBegin();
        //ImGui::ShowDemoWindow();
        ImGui::SetNextWindowSize(ImVec2(800,600));
        ImGui::SetNextWindowPos(ImVec2(0,0));
        if (ImGui::Begin("Main", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar)){
            static int months;
            static float amount, tasa;
            ImGui::PushItemWidth(width/3 - 50);
            ImGui::InputInt("Meses", &months); ImGui::SameLine();
            ImGui::InputFloat("Monto",&amount); ImGui::SameLine();
            ImGui::InputFloat("Tasa", &tasa);
            ImGui::PopItemWidth();
            ImGui::Button("Generar Tabla", ImVec2(width/2, 40)); ImGui::SameLine();
            ImGui::Button("Borrar Tabla", ImVec2(width/2, 40));
            ImGui::Separator();
            ImGui::End();
        }
        rlImGuiEnd();
        EndDrawing();
    }
    return 0;
}
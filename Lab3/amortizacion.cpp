//ENUNCIADO: Tabla de amortizacion
//PARTICIPANTES: 1101331 Asier Ochoa ; Yeuris Terrero | 1099399 ; Carlos Garcia | 1101629 ; Miguel Angel | 1100685
//FECHA:29/05/22

#include <cmath>
#include <iostream>
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

class TablaAmortizacion{
    private:
        float* payments;
        int len = 0;
    public:
        void GenerateTable(int months, float monthly_rate, float amount);
        void DeleteTable();
        static float GetQuota(float p, float i, int n);
};

void TablaAmortizacion::GenerateTable(int months, float monthly_rate, float amount) {
    len = months;
    payments = new float[months];
    for (int i = 0; i < months; ++i) {
        payments[i] = GetQuota(amount, monthly_rate, months - i);
        std::cout << "Amount in month " << i << ": " << payments[i] << '\n';
        amount -= payments[i];
    }
}

void TablaAmortizacion::DeleteTable() {
    if (len > 0){
        delete[] payments;
        len = 0;
    }
}

float TablaAmortizacion::GetQuota(float p, float i, int n) {
    return p*((i*std::pow(1+i, n))/(std::pow(1+i,n)-1));
}

int main(){
    int width = 800;
    InitWindow(width, 600, "Tabla de Amortizacion");
    SetWindowPosition(200, 600);
    rlImGuiSetup(true);
    SetTargetFPS(60);
    TablaAmortizacion t;
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        rlImGuiBegin();
        //ImGui::ShowDemoWindow();
        ImGui::SetNextWindowSize(ImVec2(800,600));
        ImGui::SetNextWindowPos(ImVec2(0,0));
        if (ImGui::Begin("Main", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar)){
            static int months;
            static float amount, tasaAnual, tasaMensual;
            ImGui::PushItemWidth(width/3 - 80);
            ImGui::InputInt("Meses", &months); ImGui::SameLine();
            if (months < 1) months = 1;
            ImGui::InputFloat("Monto",&amount); ImGui::SameLine();
            ImGui::InputFloat("Tasa Anual", &tasaAnual);
            tasaMensual = tasaAnual/12;
            ImGui::PopItemWidth();
            static float xd;
            if (ImGui::Button("Generar Tabla", ImVec2(width/2, 40)))
                t.GenerateTable(months, tasaMensual, amount);
            ImGui::SameLine();
            ImGui::Button("Borrar Tabla", ImVec2(width/2, 40));
            ImGui::Separator();
            ImGui::End();
        }
        rlImGuiEnd();
        EndDrawing();
    }
    return 0;
}
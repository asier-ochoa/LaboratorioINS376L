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
        float* amountLeft;
        float avg = 0;
        int len = 0;
    public:
        void GenerateTable(int months, float monthly_rate, float amount);
        void DeleteTable();
        static float GetQuota(float p, float i, int n);
        void Draw();
};

void TablaAmortizacion::GenerateTable(int months, float monthly_rate, float amount) {
    if (len == 0) {
        len = months;
        payments = new float[months];
        amountLeft = new float[months];
        for (int i = 0; i < months; ++i) {
            payments[i] = GetQuota(amount, monthly_rate, months - i);
            avg += payments[i];
            amount -= payments[i];
            amountLeft[i] = (amount < 0 ? 0 : amount);
        }
        avg /= months;
    }
}

void TablaAmortizacion::DeleteTable() {
    if (len > 0){
        delete[] payments;
        delete[] amountLeft;
        len = 0;
        avg = 0;
    }
}

float TablaAmortizacion::GetQuota(float p, float i, int n) {
    return p*((i*std::pow(1+i, n))/(std::pow(1+i,n)-1));
}

void TablaAmortizacion::Draw() {
    if (len > 0){
        static ImGuiTableFlags f = ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV;
        ImGui::Indent(50);
        ImGui::BeginTable("Tabla de Amortizacion", 3, f, ImVec2(690, 450));
        ImGui::TableSetupScrollFreeze(0, 1);
        ImGui::TableSetupColumn("Mes");
        ImGui::TableSetupColumn("Pago Mensual");
        ImGui::TableSetupColumn("Pago Restante");
        ImGui::TableHeadersRow();
        for (int i = 0; i < len; ++i) {
            ImGui::TableNextColumn();
            ImGui::Text("%i", i + 1);
            ImGui::TableNextColumn();
            ImGui::Text("%.2f $", payments[i]);
            ImGui::TableNextColumn();
            ImGui::Text("%.2f $", amountLeft[i]);
            ImGui::TableNextRow();
        }
        ImGui::EndTable();
        ImGui::Text("Promedio de pagos mensuales: %.2f $", avg);
    }
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
//        ImGui::ShowDemoWindow();
        ImGui::SetNextWindowSize(ImVec2(800,600));
        ImGui::SetNextWindowPos(ImVec2(0,0));
        if (ImGui::Begin("Main", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar)){
            static int months;
            static float amount, tasaAnual, tasaMensual;
            ImGui::PushItemWidth(width/3 - 80);
            ImGui::InputInt("Meses", &months); ImGui::SameLine();
            if (months < 1) months = 1;
            ImGui::InputFloat("Monto",&amount, 0, 0, "%.2f $"); ImGui::SameLine();
            if (amount < 1) amount = 1;
            ImGui::SliderFloat("Tasa Anual", &tasaAnual, 0, 100, "%.0f %%");
            tasaMensual = (tasaAnual/100)/12;
            ImGui::PopItemWidth();
            static float xd;
            if (ImGui::Button("Generar Tabla", ImVec2(width/2, 40)))
                t.GenerateTable(months, tasaMensual, amount);
            ImGui::SameLine();
            if (ImGui::Button("Borrar Tabla", ImVec2(width/2, 40)))
                t.DeleteTable();
            ImGui::Separator();
            t.Draw();
            ImGui::End();
        }
        rlImGuiEnd();
        EndDrawing();
    }
    return 0;
}
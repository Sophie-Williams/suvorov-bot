// The MIT License (MIT)
//
// Copyright (c) 2017-2018 Alexander Kurbatov

#include "../Historican.h"
#include "Diagnosis.h"
#include "core/API.h"

Diagnosis::Diagnosis(const std::shared_ptr<Builder>& builder_):
    Plugin(), m_builder(builder_) {
}

void Diagnosis::OnStep() {
    auto builder = m_builder.lock();
    if (!builder)
        return;

    gAPI->debug().DrawText("Build order:");

    if (builder->GetConstructionOrders().empty()) {
        gAPI->debug().DrawText("Empty");
    } else {
        for (const auto& i : builder->GetConstructionOrders())
            gAPI->debug().DrawText(i.name);
    }

    gAPI->debug().SendDebug();
}

void Diagnosis::OnGameEnd() {
    gAPI->control().SaveReplay();
    gHistory.info() << "Replay saved" << std::endl;
}

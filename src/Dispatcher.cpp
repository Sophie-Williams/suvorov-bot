// The MIT License (MIT)
//
// Copyright (c) 2017-2018 Alexander Kurbatov

#include "Dispatcher.h"
#include "Historican.h"
#include "Hub.h"
#include "core/API.h"
#include "core/Helpers.h"
#include "core/Timer.h"
#include "plugins/ChatterBox.h"
#include "plugins/Diagnosis.h"
#include "plugins/ForceCommander.h"
#include "plugins/Governor.h"
#include "plugins/Miner.h"
#include "plugins/QuarterMaster.h"
#include "plugins/WarpSmith.h"

#include <sc2api/sc2_common.h>
#include <sc2api/sc2_unit.h>

Dispatcher::Dispatcher(const std::string& opponent_id_): m_builder(new Builder()) {
    gAPI.reset(new API::Interface(Actions(), Control(), Debug(), Observation(), Query()));

    m_plugins.emplace_back(new Governor(m_builder));
    m_plugins.emplace_back(new Miner(m_builder));
    m_plugins.emplace_back(new QuarterMaster(m_builder));
    m_plugins.emplace_back(new ForceCommander());
    m_plugins.emplace_back(new ChatterBox());

    if (!opponent_id_.empty()) {
        gHistory.info() << "Playing against an opponent with id "
            << opponent_id_ << std::endl;
    }

#ifdef DEBUG
    m_plugins.emplace_back(new Diagnosis(m_builder));
#endif
}

void Dispatcher::OnGameStart() {
    gHistory.info() << "New game started!" << std::endl;

    sc2::Race current_race = gAPI->observer().GetCurrentRace();
    gHub.reset(new Hub(current_race));

    if (current_race == sc2::Race::Protoss)
        m_plugins.emplace_back(new WarpSmith());

    for (const auto& i : m_plugins)
        i->OnGameStart();
}

void Dispatcher::OnGameEnd() {
    gHistory.info() << "Game over!" <<std::endl;

    for (const auto& i : m_plugins)
        i->OnGameEnd();
}

void Dispatcher::OnBuildingConstructionComplete(const sc2::Unit* building_) {
    gHistory.info() << sc2::UnitTypeToName(building_->unit_type) <<
        ": construction complete" << std::endl;
}

void Dispatcher::OnStep() {
    Timer clock;
    clock.Start();

    gHub->OnStep();

    for (const auto& i : m_plugins)
        i->OnStep();

    m_builder->OnStep();

    clock.Finish();
}

void Dispatcher::OnUnitCreated(const sc2::Unit* unit_) {
    // NOTE (alkurbatov): Could be just a worker exiting a refinery.
    if (unit_->alliance != sc2::Unit::Alliance::Self || IsGasWorker()(*unit_))
        return;

    gHistory.info() << sc2::UnitTypeToName(unit_->unit_type) <<
        " was created" << std::endl;

    gHub->OnUnitCreated(*unit_);
    m_builder->OnUnitCreated(*unit_);

    for (const auto& i : m_plugins)
        i->OnUnitCreated(unit_);
}

void Dispatcher::OnUnitIdle(const sc2::Unit* unit_) {
    gHub->OnUnitIdle(*unit_);

    for (const auto& i : m_plugins)
        i->OnUnitIdle(unit_);
}

void Dispatcher::OnUnitDestroyed(const sc2::Unit* unit_) {
    if (unit_->alliance != sc2::Unit::Alliance::Self)
        return;

    gHistory.info() << sc2::UnitTypeToName(unit_->unit_type) <<
        " was destroyed" << std::endl;

    gHub->OnUnitDestroyed(*unit_);

    for (const auto& i : m_plugins)
        i->OnUnitDestroyed(unit_);
}

void Dispatcher::OnError(const std::vector<sc2::ClientError>& client_errors,
        const std::vector<std::string>& protocol_errors) {
    for (const auto i : client_errors) {
        gHistory.error() << "Encountered client error: " <<
            static_cast<int>(i) << std::endl;
    }

    for (const auto& i : protocol_errors)
        gHistory.error() << "Encountered protocol error: " << i << std::endl;
}

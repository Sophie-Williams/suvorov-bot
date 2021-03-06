// The MIT License (MIT)
//
// Copyright (c) 2017-2018 Alexander Kurbatov

#include "Blueprint.h"
#include "Building.h"
#include "Creature.h"
#include "GateUnit.h"
#include "Mutation.h"
#include "Queen.h"
#include "Refinery.h"
#include "Research.h"
#include "TownHall.h"
#include "Unit.h"
#include "core/API.h"
#include "core/Errors.h"

Blueprint::~Blueprint() {
}

std::shared_ptr<Blueprint> Blueprint::Plot(sc2::ABILITY_ID ability_) {
    switch (ability_) {
        case sc2::ABILITY_ID::BUILD_REFINERY:
        case sc2::ABILITY_ID::BUILD_EXTRACTOR:
        case sc2::ABILITY_ID::BUILD_ASSIMILATOR:
            return std::shared_ptr<Blueprint>(new Refinery());

        case sc2::ABILITY_ID::MORPH_BROODLORD:
        case sc2::ABILITY_ID::MORPH_GREATERSPIRE:
        case sc2::ABILITY_ID::MORPH_HIVE:
        case sc2::ABILITY_ID::MORPH_LAIR:
        case sc2::ABILITY_ID::MORPH_LURKER:
        case sc2::ABILITY_ID::MORPH_ORBITALCOMMAND:
        case sc2::ABILITY_ID::MORPH_OVERSEER:
        case sc2::ABILITY_ID::MORPH_PLANETARYFORTRESS:
        case sc2::ABILITY_ID::MORPH_RAVAGER:
        case sc2::ABILITY_ID::TRAIN_BANELING:
            return std::shared_ptr<Blueprint>(new Mutation());

        case sc2::ABILITY_ID::TRAIN_ADEPT:
        case sc2::ABILITY_ID::TRAIN_DARKTEMPLAR:
        case sc2::ABILITY_ID::TRAIN_HIGHTEMPLAR:
        case sc2::ABILITY_ID::TRAIN_SENTRY:
        case sc2::ABILITY_ID::TRAIN_STALKER:
        case sc2::ABILITY_ID::TRAIN_ZEALOT:
            return std::shared_ptr<Blueprint>(new GateUnit());

        case sc2::ABILITY_ID::TRAINWARP_ADEPT:
        case sc2::ABILITY_ID::TRAINWARP_DARKTEMPLAR:
        case sc2::ABILITY_ID::TRAINWARP_HIGHTEMPLAR:
        case sc2::ABILITY_ID::TRAINWARP_SENTRY:
        case sc2::ABILITY_ID::TRAINWARP_STALKER:
        case sc2::ABILITY_ID::TRAINWARP_ZEALOT:
            // NOTE (alkurbatov): Instead please use
            // TRAIN_ADEPT, TRAIN_DARKTEMPLAR etc.
            throw InvalidBuildCommand(ability_);

        case sc2::ABILITY_ID::TRAIN_COLOSSUS:
        case sc2::ABILITY_ID::TRAIN_DISRUPTOR:
        case sc2::ABILITY_ID::TRAIN_IMMORTAL:
        case sc2::ABILITY_ID::TRAIN_OBSERVER:
        case sc2::ABILITY_ID::TRAIN_WARPPRISM:
            return std::shared_ptr<Blueprint>(
                new Unit(sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY));

        case sc2::ABILITY_ID::TRAIN_CARRIER:
        case sc2::ABILITY_ID::TRAIN_ORACLE:
        case sc2::ABILITY_ID::TRAIN_PHOENIX:
        case sc2::ABILITY_ID::TRAIN_TEMPEST:
        case sc2::ABILITY_ID::TRAIN_VOIDRAY:
            return std::shared_ptr<Blueprint>(
                new Unit(sc2::UNIT_TYPEID::PROTOSS_STARGATE));

        case sc2::ABILITY_ID::TRAIN_MOTHERSHIP:
            return std::shared_ptr<Blueprint>(
                new Unit(sc2::UNIT_TYPEID::PROTOSS_NEXUS));

        case sc2::ABILITY_ID::TRAIN_BANSHEE:
        case sc2::ABILITY_ID::TRAIN_BATTLECRUISER:
        case sc2::ABILITY_ID::TRAIN_LIBERATOR:
        case sc2::ABILITY_ID::TRAIN_MEDIVAC:
        case sc2::ABILITY_ID::TRAIN_VIKINGFIGHTER:
            return std::shared_ptr<Blueprint>(
                new Unit(sc2::UNIT_TYPEID::TERRAN_STARPORT));

        case sc2::ABILITY_ID::TRAIN_CYCLONE:
        case sc2::ABILITY_ID::TRAIN_HELLION:
        case sc2::ABILITY_ID::TRAIN_HELLBAT:
        case sc2::ABILITY_ID::TRAIN_SIEGETANK:
        case sc2::ABILITY_ID::TRAIN_THOR:
        case sc2::ABILITY_ID::TRAIN_WIDOWMINE:
            return std::shared_ptr<Blueprint>(
                new Unit(sc2::UNIT_TYPEID::TERRAN_FACTORY));

        case sc2::ABILITY_ID::TRAIN_GHOST:
        case sc2::ABILITY_ID::TRAIN_MARINE:
        case sc2::ABILITY_ID::TRAIN_MARAUDER:
        case sc2::ABILITY_ID::TRAIN_REAPER:
            return std::shared_ptr<Blueprint>(
                new Unit(sc2::UNIT_TYPEID::TERRAN_BARRACKS));

        case sc2::ABILITY_ID::TRAIN_QUEEN:
            return std::shared_ptr<Blueprint>(new Queen());

        case sc2::ABILITY_ID::TRAIN_PROBE:
        case sc2::ABILITY_ID::TRAIN_SCV:
            return std::shared_ptr<Blueprint>(
                new Unit(sc2::UNIT_TYPEID::INVALID));

        case sc2::ABILITY_ID::TRAIN_DRONE:
        case sc2::ABILITY_ID::TRAIN_CORRUPTOR:
        case sc2::ABILITY_ID::TRAIN_INFESTOR:
        case sc2::ABILITY_ID::TRAIN_HYDRALISK:
        case sc2::ABILITY_ID::TRAIN_MUTALISK:
        case sc2::ABILITY_ID::TRAIN_OVERLORD:
        case sc2::ABILITY_ID::TRAIN_ROACH:
        case sc2::ABILITY_ID::TRAIN_SWARMHOST:
        case sc2::ABILITY_ID::TRAIN_VIPER:
        case sc2::ABILITY_ID::TRAIN_ULTRALISK:
        case sc2::ABILITY_ID::TRAIN_ZERGLING:
            return std::shared_ptr<Blueprint>(new Creature());

        case sc2::ABILITY_ID::RESEARCH_WARPGATE:
            return std::shared_ptr<Blueprint>(
                new Research(sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE));

        case sc2::ABILITY_ID::RESEARCH_HISECAUTOTRACKING:
        case sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL1:
        case sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL2:
        case sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYARMORLEVEL3:
        case sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL1:
        case sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL2:
        case sc2::ABILITY_ID::RESEARCH_TERRANINFANTRYWEAPONSLEVEL3:
        case sc2::ABILITY_ID::RESEARCH_TERRANSTRUCTUREARMORUPGRADE:
            return std::shared_ptr<Blueprint>(
                new Research(sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY));

        case sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL1:
        case sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL2:
        case sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDARMORLEVEL3:
        case sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL1:
        case sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL2:
        case sc2::ABILITY_ID::RESEARCH_PROTOSSGROUNDWEAPONSLEVEL3:
        case sc2::ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL1:
        case sc2::ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL2:
        case sc2::ABILITY_ID::RESEARCH_PROTOSSSHIELDSLEVEL3:
            return std::shared_ptr<Blueprint>(
                new Research(sc2::UNIT_TYPEID::PROTOSS_FORGE));

        case sc2::ABILITY_ID::RESEARCH_ADEPTRESONATINGGLAIVES:
        case sc2::ABILITY_ID::RESEARCH_BLINK:
        case sc2::ABILITY_ID::RESEARCH_CHARGE:
            return std::shared_ptr<Blueprint>(
                new Unit(sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL));

        case sc2::ABILITY_ID::BUILD_COMMANDCENTER:
        case sc2::ABILITY_ID::BUILD_HATCHERY:
        case sc2::ABILITY_ID::BUILD_NEXUS:
            return std::shared_ptr<Blueprint>(new TownHall());

        case sc2::ABILITY_ID::RESEARCH_ZERGLINGADRENALGLANDS:
        case sc2::ABILITY_ID::RESEARCH_ZERGLINGMETABOLICBOOST:
            return std::shared_ptr<Blueprint>(
                new Unit(sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL));

        case sc2::ABILITY_ID::RESEARCH_ZERGGROUNDARMORLEVEL1:
        case sc2::ABILITY_ID::RESEARCH_ZERGGROUNDARMORLEVEL2:
        case sc2::ABILITY_ID::RESEARCH_ZERGGROUNDARMORLEVEL3:
        case sc2::ABILITY_ID::RESEARCH_ZERGMELEEWEAPONSLEVEL1:
        case sc2::ABILITY_ID::RESEARCH_ZERGMELEEWEAPONSLEVEL2:
        case sc2::ABILITY_ID::RESEARCH_ZERGMELEEWEAPONSLEVEL3:
        case sc2::ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONSLEVEL1:
        case sc2::ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONSLEVEL2:
        case sc2::ABILITY_ID::RESEARCH_ZERGMISSILEWEAPONSLEVEL3:
            return std::shared_ptr<Blueprint>(
                new Research(sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER));

        default:
            return std::shared_ptr<Blueprint>(new Building());
    }
}

// The MIT License (MIT)
//
// Copyright (c) 2017-2018 Alexander Kurbatov

#pragma once

#include "Plugin.h"

struct ChatterBox: Plugin {
    void OnGameStart() final;

    void OnStep() final;
};
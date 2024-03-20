# Open_Spaceward_Ho-
Open Implement of the Classic Spaceward Ho! Game - C++

NOTE: While this does not promise the exact mechanics of the original game, I've taken care to implement other entertaining features within the game, and intend to build on the original aesthetic.

The AI in this game will be machine learning trained on a CPU and will be relatively lightweight with difficulty in relation to input variables. If you wish to contact me about helping with completion of this project, I will provide a contact link in 1-3 weeks time of this commit.

The code is currently in development and serves at present only demonstration purposes. The code is relatively clean at the moment, and I intend the code to be clean by completion.

There will be updates- currently I'm only making a code dump which will clearly demonstrate the structure of the game, but not its final form. I've got about ~3500 lines of C++ and estimate needing another 4000 lines to complete this project, and cleaning up the existing code. Most of the extra lines will be handling exceptions likely.

This should work on all OS that can run C++.


File structure plan;

spaceward_ho/
├── CMakeLists.txt
├── src/
│   ├── CMakeLists.txt
│   ├── main.cpp
│   ├── game/
│   │   ├── CMakeLists.txt
│   │   ├── game.h
│   │   ├── game.cpp
│   │   ├── game_state.h
│   │   ├── game_state.cpp
│   │   ├── game_settings.h
│   │   └── game_settings.cpp
│   ├── entities/
│   │   ├── CMakeLists.txt
│   │   ├── planet.h
│   │   ├── planet.cpp
│   │   ├── ship.h
│   │   ├── ship.cpp
│   │   ├── player.h
│   │   ├── player.cpp
│   │   ├── technology.h
│   │   ├── technology.cpp
│   │   ├── projectile.h
│   │   └── projectile.cpp
│   ├── game_logic/
│   │   ├── CMakeLists.txt
│   │   ├── galaxy.h
│   │   ├── galaxy.cpp
│   │   ├── game_logic.h
│   │   ├── game_logic.cpp
│   │   ├── event_system.h
│   │   ├── event_system.cpp
│   │   ├── combat_system.h
│   │   ├── combat_system.cpp
│   │   ├── ai_system.h
│   │   └── ai_system.cpp
│   ├── rendering/
│   │   ├── CMakeLists.txt
│   │   ├── renderer.h
│   │   ├── renderer.cpp
│   │   ├── ui_renderer.h
│   │   ├── ui_renderer.cpp
│   │   ├── galaxy_view.h
│   │   ├── galaxy_view.cpp
│   │   ├── planet_view.h
│   │   ├── planet_view.cpp
│   │   ├── ship_designer.h
│   │   └── ship_designer.cpp
│   ├── input/
│   │   ├── CMakeLists.txt
│   │   ├── input_handler.h
│   │   └── input_handler.cpp
│   ├── ui/
│   │   ├── CMakeLists.txt
│   │   ├── ui_manager.h
│   │   ├── ui_manager.cpp
│   │   ├── ui_elements.h
│   │   ├── ui_elements.cpp
│   │   ├── screens/
│   │   │   ├── main_menu.h
│   │   │   ├── main_menu.cpp
│   │   │   ├── game_screen.h
│   │   │   ├── game_screen.cpp
│   │   │   ├── planet_screen.h
│   │   │   ├── planet_screen.cpp
│   │   │   ├── ship_design_screen.h
│   │   │   ├── ship_design_screen.cpp
│   │   │   ├── tech_screen.h
│   │   │   ├── tech_screen.cpp
│   │   │   ├── diplomacy_screen.h
│   │   │   └── diplomacy_screen.cpp
│   ├── networking/
│   │   ├── CMakeLists.txt
│   │   ├── network_manager.h
│   │   ├── network_manager.cpp
│   │   ├── network_messages.h
│   │   ├── network_messages.cpp
│   │   ├── server/
│   │   │   ├── server.h
│   │   │   └── server.cpp
│   │   └── client/
│   │       ├── client.h
│   │       └── client.cpp
│   ├── utility/
│   │   ├── CMakeLists.txt
│   │   ├── resource_manager.h
│   │   ├── resource_manager.cpp
│   │   ├── utility.h
│   │   └── utility.cpp
│   ├── data/
│   │   ├── CMakeLists.txt
│   │   ├── save_game.h
│   │   ├── save_game.cpp
│   │   ├── game_data.h
│   │   └── game_data.cpp
│   ├── config/
│   │   ├── CMakeLists.txt
│   │   ├── config_manager.h
│   │   ├── config_manager.cpp
│   │   ├── game_config.h
│   │   └── game_config.cpp
│   └── scripting/
│       ├── CMakeLists.txt
│       ├── scripting_engine.h
│       ├── scripting_engine.cpp
│       ├── script_api.h
│       └── script_api.cpp
├── assets/
│   ├── textures/
│   │   ├── planets/
│   │   ├── ships/
│   │   ├── ui/
│   │   └── backgrounds/
│   ├── fonts/
│   ├── sounds/
│   │   ├── effects/
│   │   └── music/
│   └── data/
│       ├── tech_tree.json
│       ├── ship_data.json
│       ├── planet_data.json
│       ├── event_data.json
│       └── localization/
├── docs/
│   ├── game_design.md
│   ├── api_reference.md
│   ├── scripting_guide.md
│   └── modding_guide.md
├── mods/
│   ├── example_mod/
│   └── mod_template/
└── tests/
├── CMakeLists.txt
├── game_tests.cpp
├── entity_tests.cpp
├── game_logic_tests.cpp
├── rendering_tests.cpp
├── input_tests.cpp
├── ui_tests.cpp
├── networking_tests.cpp
├── utility_tests.cpp
└── scripting_tests.cpp

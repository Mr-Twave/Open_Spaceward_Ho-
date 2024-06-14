# Open_Spaceward_Ho
Open Implement of the Classic Spaceward Ho! Game - C++

ORIGINAL GAME:
(https://www.deltatao.com/ho/pc.html)
FYI I'm a huge fan of these guys for creating this game. It's abandonware though, so I'm just going to make an open sourced better game.

IF YOU WISH TO HELP IN THE PRODUCTION OF THIS PROJECT, PLEASE MAKE AN ISSUE AND I WILL PROVIDE YOU WITH A CONTACT METHOD. (JUST SAY YOU WANT A CONTACT.)

NOTE: While Open Spaceward Ho does not promise the exact mechanics of the original game, I've taken care to implement other entertaining features within the game. I intend to build on the original aesthetic.

The AI in this game will be machine learning trained on a CPU and will be relatively lightweight with difficulty in relation to input variables. 

If you wish to contact me about helping with completion of this project, I do not mind you posting an issue if you wish to contact me. This project WILL be completed, but its completion a question of extra time resource. The author is currently very busy with important formatting projects, and this one has been set on the backburner. If you have read my code, you'll understand that I'm beyond proficient at creating simplistic code and am generally avoidant of individually complex functions. Formatting my code is something I'm improving on. You will see that in a future version of Open Spaceward Ho. I need to go over the mechanics of this game again before it can be produced in full; not all mechanics are outlined properly.

Once all of the mechanics are outlined properly, I will finish making this game.

The code is currently in development and serves at present only demonstration purposes. The code is relatively clean at the moment. I intend the code to be more clean by time of completion.

There will be updates- currently I'm only making a code dump which will clearly demonstrate the structure of the game, but not its final form. I've got about ~15000 lines of C++ and estimate needing another 2000 lines to complete this project, and cleaning up the existing code. Most of the extra lines will be handling exceptions likely.

This should work on all OS that can run C++.

The holdup currently is that most of the elementary game code is written, but it is somewhat disjunct.


File structure plan;
```
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
│   │   ├── game_settings.cpp
│   │   ├── game_simulation.h
│   │   ├── game_simulation.cpp
│   │   ├── game_calendar.h
│   │   └── game_calendar.cpp
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
│   │   ├── projectile.cpp
│   │   ├── resource.h
│   │   ├── resource.cpp
│   │   ├── fleet.h
│   │   └── fleet.cpp
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
│   │   ├── ai_system.cpp
│   │   ├── diplomacy_system.h
│   │   ├── diplomacy_system.cpp
│   │   ├── trade_system.h
│   │   ├── trade_system.cpp
│   │   ├── resource_system.h
│   │   ├── resource_system.cpp
│   │   ├── population_system.h
│   │   └── population_system.cpp
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
│   │   ├── ship_designer.cpp
│   │   ├── combat_view.h
│   │   ├── combat_view.cpp
│   │   ├── particle_system.h
│   │   ├── particle_system.cpp
│   │   ├── shader_manager.h
│   │   ├── shader_manager.cpp
│   │   ├── post_processing.h
│   │   └── post_processing.cpp
│   ├── input/
│   │   ├── CMakeLists.txt
│   │   ├── input_handler.h
│   │   ├── input_handler.cpp
│   │   ├── key_bindings.h
│   │   ├── key_bindings.cpp
│   │   ├── mouse_input.h
│   │   └── mouse_input.cpp
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
│   │   │   ├── diplomacy_screen.cpp
│   │   │   ├── trade_screen.h
│   │   │   ├── trade_screen.cpp
│   │   │   ├── resource_screen.h
│   │   │   ├── resource_screen.cpp
│   │   │   ├── fleet_screen.h
│   │   │   ├── fleet_screen.cpp
│   │   │   ├── combat_screen.h
│   │   │   ├── combat_screen.cpp
│   │   │   ├── settings_screen.h
│   │   │   └── settings_screen.cpp
│   │   ├── widgets/
│   │   │   ├── button.h
│   │   │   ├── button.cpp
│   │   │   ├── text_input.h
│   │   │   ├── text_input.cpp
│   │   │   ├── slider.h
│   │   │   ├── slider.cpp
│   │   │   ├── checkbox.h
│   │   │   ├── checkbox.cpp
│   │   │   ├── dropdown.h
│   │   │   ├── dropdown.cpp
│   │   │   ├── progress_bar.h
│   │   │   ├── progress_bar.cpp
│   │   │   ├── tooltip.h
│   │   │   └── tooltip.cpp
│   │   ├── gui_elements/
│   │   │   ├── minimap.h
│   │   │   ├── minimap.cpp
│   │   │   ├── resource_bar.h
│   │   │   ├── resource_bar.cpp
│   │   │   ├── tech_tree.h
│   │   │   ├── tech_tree.cpp
│   │   │   ├── ship_info.h
│   │   │   ├── ship_info.cpp
│   │   │   ├── planet_info.h
│   │   │   └── planet_info.cpp
│   │   └── animations/
│   │       ├── animation.h
│   │       ├── animation.cpp
│   │       ├── tweening.h
│   │       └── tweening.cpp
│   ├── ai/
│   │   ├── CMakeLists.txt
│   │   ├── ai_manager.h
│   │   ├── ai_manager.cpp
│   │   ├── decision_making/
│   │   │   ├── strategy_manager.h
│   │   │   ├── strategy_manager.cpp
│   │   │   ├── exploration_strategy.h
│   │   │   ├── exploration_strategy.cpp
│   │   │   ├── expansion_strategy.h
│   │   │   ├── expansion_strategy.cpp
│   │   │   ├── development_strategy.h
│   │   │   ├── development_strategy.cpp
│   │   │   ├── military_strategy.h
│   │   │   ├── military_strategy.cpp
│   │   │   ├── diplomacy_strategy.h
│   │   │   └── diplomacy_strategy.cpp
│   │   ├── ship_ai/
│   │   │   ├── ship_controller.h
│   │   │   ├── ship_controller.cpp
│   │   │   ├── fighter_ai.h
│   │   │   ├── fighter_ai.cpp
│   │   │   ├── scout_ai.h
│   │   │   ├── scout_ai.cpp
│   │   │   ├── colony_ship_ai.h
│   │   │   ├── colony_ship_ai.cpp
│   │   │   ├── frigate_ai.h
│   │   │   ├── frigate_ai.cpp
│   │   │   ├── capital_ship_ai.h
│   │   │   └── capital_ship_ai.cpp
│   │   ├── planet_ai/
│   │   │   ├── planet_manager.h
│   │   │   ├── planet_manager.cpp
│   │   │   ├── development_ai.h
│   │   │   ├── development_ai.cpp
│   │   │   ├── production_ai.h
│   │   │   ├── production_ai.cpp
│   │   │   ├── defense_ai.h
│   │   │   └── defense_ai.cpp
│   │   ├── diplomacy_ai/
│   │   │   ├── diplomacy_manager.h
│   │   │   ├── diplomacy_manager.cpp
│   │   │   ├── negotiation_ai.h
│   │   │   ├── negotiation_ai.cpp
│   │   │   ├── trade_ai.h
│   │   │   └── trade_ai.cpp
│   │   └── pathfinding/
│   │       ├── pathfinder.h
│   │       ├── pathfinder.cpp
│   │       ├── a_star.h
│   │       └── a_star.cpp
│   ├── networking/
│   │   ├── CMakeLists.txt
│   │   ├── network_manager.h
│   │   ├── network_manager.cpp
│   │   ├── network_messages.h
│   │   ├── network_messages.cpp
│   │   ├── server/
│   │   │   ├── server.h
│   │   │   ├── server.cpp
│   │   │   ├── game_server.h
│   │   │   ├── game_server.cpp
│   │   │   ├── lobby_server.h
│   │   │   └── lobby_server.cpp
│   │   └── client/
│   │       ├── client.h
│   │       ├── client.cpp
│   │       ├── game_client.h
│   │       └── game_client.cpp
│   ├── utility/
│   │   ├── CMakeLists.txt
│   │   ├── resource_manager.h
│   │   ├── resource_manager.cpp
│   │   ├── utility.h
│   │   ├── utility.cpp
│   │   ├── math_utils.h
│   │   ├── math_utils.cpp
│   │   ├── random.h
│   │   ├── random.cpp
│   │   ├── logging.h
│   │   ├── logging.cpp
│   │   ├── profiler.h
│   │   └── profiler.cpp
│   ├── data/
│   │   ├── CMakeLists.txt
│   │   ├── save_game.h
│   │   ├── save_game.cpp
│   │   ├── game_data.h
│   │   ├── game_data.cpp
│   │   ├── serialization.h
│   │   ├── serialization.cpp
│   │   ├── deserialization.h
│   │   └── deserialization.cpp
│   ├── config/
│   │   ├── CMakeLists.txt
│   │   ├── config_manager.h
│   │   ├── config_manager.cpp
│   │   ├── game_config.h
│   │   ├── game_config.cpp
│   │   ├── audio_config.h
│   │   ├── audio_config.cpp
│   │   ├── video_config.h
│   │   ├── video_config.cpp
│   │   ├── input_config.h
│   │   └── input_config.cpp
│   ├── scripting/
│   │   ├── CMakeLists.txt
│   │   ├── scripting_engine.h
│   │   ├── scripting_engine.cpp
│   │   ├── script_api.h
│   │   ├── script_api.cpp
│   │   ├── lua/
│   │   │   ├── lua_bindings.h
│   │   │   └── lua_bindings.cpp
│   │   └── python/
│   │       ├── python_bindings.h
│   │       └── python_bindings.cpp
│   ├── localization/
│   │   ├── CMakeLists.txt
│   │   ├── localization_manager.h
│   │   ├── localization_manager.cpp
│   │   ├── string_table.h
│   │   └── string_table.cpp
│   ├── sound/
│   │   ├── CMakeLists.txt
│   │   ├── audio_manager.h
│   │   ├── audio_manager.cpp
│   │   ├── sound_effect.h
│   │   ├── sound_effect.cpp
│   │   ├── music.h
│   │   └── music.cpp
│   └── physics/
│       ├── CMakeLists.txt
│       ├── physics_engine.h
│       ├── physics_engine.cpp
│       ├── collision_detection.h
│       ├── collision_detection.cpp
│       ├── rigid_body.h
│       └── rigid_body.cpp
├── assets/
│   ├── textures/
│   │   ├── planets/
│   │   ├── ships/
│   │   ├── ui/
│   │   ├── backgrounds/
│   │   ├── particles/
│   │   └── effects/
│   ├── fonts/
│   ├── sounds/
│   │   ├── effects/
│   │   ├── ambient/
│   │   ├── music/
│   │   └── voice/
│   ├── data/
│   │   ├── tech_tree.json
│   │   ├── ship_data.json
│   │   ├── planet_data.json
│   │   ├── event_data.json
│   │   ├── localization/
│   │   └── config/
│   └── shaders/
│       ├── vertex_shaders/
│       └── fragment_shaders/
├── docs/
│   ├── game_design.md
│   ├── gameplay_guide.md
│   ├── api_reference.md
│   ├── scripting_guide.md
│   ├── modding_guide.md
│   ├── networking_guide.md
│   └── ai_architecture.md
├── mods/
│   ├── example_mod/
│   └── mod_template/
├── tools/
│   ├── map_editor/
│   ├── ship_designer/
│   ├── particle_editor/
│   └── localization_tool/
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
├── scripting_tests.cpp
├── localization_tests.cpp
├── sound_tests.cpp
├── physics_tests.cpp
├── ai_tests/
│   ├── decision_making_tests.cpp
│   ├── ship_ai_tests.cpp
│   ├── planet_ai_tests.cpp
│   ├── diplomacy_ai_tests.cpp
│   └── pathfinding_tests.cpp
└── performance_tests/
├── game_simulation_tests.cpp
├── rendering_tests.cpp
├── networking_tests.cpp
└── ai_tests.cpp
```

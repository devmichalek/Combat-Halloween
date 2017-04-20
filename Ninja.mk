##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Ninja
ConfigurationName      :=Debug
WorkspacePath          :="/home/adr/Dokumenty/C++ workspace"
ProjectPath            :="/home/adr/Dokumenty/C++ workspace/Ninja"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Adrian Michalek
Date                   :=20/04/17
CodeLitePath           :=/home/adr/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="Ninja.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -lsfml-window -lsfml-system -lsfml-graphics -lsfml-network -lSDL2 -lSDL2_mixer
IncludePath            :=  $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -std=c++11 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/core.cpp$(ObjectSuffix) $(IntermediateDirectory)/timer.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/engine.cpp$(ObjectSuffix) $(IntermediateDirectory)/drawable_text.cpp$(ObjectSuffix) $(IntermediateDirectory)/drawable_sprite.cpp$(ObjectSuffix) $(IntermediateDirectory)/drawable_rect.cpp$(ObjectSuffix) $(IntermediateDirectory)/drawable_color.cpp$(ObjectSuffix) $(IntermediateDirectory)/sound_sound.cpp$(ObjectSuffix) $(IntermediateDirectory)/sound_music.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/sound_chunk.cpp$(ObjectSuffix) $(IntermediateDirectory)/file_file.cpp$(ObjectSuffix) $(IntermediateDirectory)/initialization_nick_setter.cpp$(ObjectSuffix) $(IntermediateDirectory)/initialization_nick_info.cpp$(ObjectSuffix) $(IntermediateDirectory)/initialization_loading.cpp$(ObjectSuffix) $(IntermediateDirectory)/initialization_initialization.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_menu.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_click.cpp$(ObjectSuffix) $(IntermediateDirectory)/level_level.cpp$(ObjectSuffix) $(IntermediateDirectory)/level_difficulty.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/level_cube.cpp$(ObjectSuffix) $(IntermediateDirectory)/level_choice.cpp$(ObjectSuffix) $(IntermediateDirectory)/level_character.cpp$(ObjectSuffix) $(IntermediateDirectory)/level_backtomenu.cpp$(ObjectSuffix) $(IntermediateDirectory)/panel_show_scores.cpp$(ObjectSuffix) $(IntermediateDirectory)/panel_replay_button.cpp$(ObjectSuffix) $(IntermediateDirectory)/panel_panel_menu.cpp$(ObjectSuffix) $(IntermediateDirectory)/panel_loading_world.cpp$(ObjectSuffix) $(IntermediateDirectory)/panel_backtomenu_panel.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_author_log_scroll.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/menu_author_log_member.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_author_log_list.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_author_log_author_info.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_author_log_author.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_development_headdeck.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_development_head.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_development_developdeck.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_development_develop.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_explanator_explanator.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_keyboard_keyboard.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/menu_keyboard_information.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_link_button_link_button.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_log_log.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_nick_nick.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_play_button_play_button.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_play_button_exit_log.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_reset_button_reset_button.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_sound_button_sound_button.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_title_title.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_volume_button_volume_button.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/platform_desert_desert_mechanics.cpp$(ObjectSuffix) 

Objects1=$(IntermediateDirectory)/platform_desert_desert.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_forest_forest_mechanics.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_forest_forest.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_winter_winter_mechanics.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_winter_winter.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_halloween_halloween_mechanics.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_halloween_halloween.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_future_future_mechanics.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_future_future.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/platform_ninja_kunai_kunai_effects.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_ninja_kunai_kunai_bit.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_ninja_kunai_kunai.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_ninja_kunai_damage.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_ninja_base_ninja_basic.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_ninja_base_ninja.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_ninja_base_activity.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_ninja_scope_scope.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_panel_heart_heart_bit.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_panel_heart_heart.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/platform_panel_money_money.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_panel_pause_pause.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_panel_scores_scores.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_panel_skill_skills.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_panel_skill_skill_effect.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_panel_skill_skill.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_panel_sound_pad_sound_pad.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_panel_time_box_time_box.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_background_day.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_background_background.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/platform_world_wall_wall.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_wall_pug.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_boulder_boulders.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_boulder_boulder.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_islands_islands.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_islands_hover.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_brick_rules.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_brick_brick.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_brick_block.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_score_dots_score_dots.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/platform_world_water_water.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_spikes_spikes.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_spikes_spike.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_saws_saws.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_saws_saw.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_exit_exit.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_greenery_plant.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_greenery_greenery.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_greenery_green.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_ladder_ladder.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/platform_enemy_actions_coins_coins.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_enemy_actions_coins_coin.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_enemy_actions_effect_effect.cpp$(ObjectSuffix) 

Objects2=$(IntermediateDirectory)/platform_enemy_actions_expletive_slab.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_enemy_actions_expletive_expletive.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_enemy_actions_hp_dots_hp_dots.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_enemy_actions_hp_dots_hp_dot.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_enemy_actions_show_showheal.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_enemy_actions_show_showdamage.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_enemy_foes_factory_factory.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/platform_enemy_foes_flying_fly_factory.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_enemy_foes_flying_fly.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_enemy_foes_golem_golem.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_enemy_foes_zombie_zombie.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_enemy_foes_robot_robot.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_enemy_foes_vampire_vampire.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_enemy_foes_skeleton_skeleton.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_enemy_foes_snakes_snakes_factory.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_enemy_foes_snakes_snakes.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_enemy_foes_mines_mine_factory.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/platform_enemy_foes_mines_mine.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_weather_rain_rain.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_weather_sun_sun.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_weather_snow_snow.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_world_weather_wind_wind.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_enemy_foes_checkActivity_cruncher_cruncher.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_enemy_foes_checkActivity_fireball_fireball.cpp$(ObjectSuffix) $(IntermediateDirectory)/platform_enemy_foes_checkActivity_lightning_lightning.cpp$(ObjectSuffix) 



Objects=$(Objects0) $(Objects1) $(Objects2) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	@echo $(Objects1) >> $(ObjectsFileList)
	@echo $(Objects2) >> $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/core.cpp$(ObjectSuffix): core.cpp $(IntermediateDirectory)/core.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/core.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/core.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/core.cpp$(DependSuffix): core.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/core.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/core.cpp$(DependSuffix) -MM core.cpp

$(IntermediateDirectory)/core.cpp$(PreprocessSuffix): core.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/core.cpp$(PreprocessSuffix) core.cpp

$(IntermediateDirectory)/timer.cpp$(ObjectSuffix): timer.cpp $(IntermediateDirectory)/timer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/timer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/timer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/timer.cpp$(DependSuffix): timer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/timer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/timer.cpp$(DependSuffix) -MM timer.cpp

$(IntermediateDirectory)/timer.cpp$(PreprocessSuffix): timer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/timer.cpp$(PreprocessSuffix) timer.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/engine.cpp$(ObjectSuffix): engine.cpp $(IntermediateDirectory)/engine.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/engine.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/engine.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/engine.cpp$(DependSuffix): engine.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/engine.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/engine.cpp$(DependSuffix) -MM engine.cpp

$(IntermediateDirectory)/engine.cpp$(PreprocessSuffix): engine.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/engine.cpp$(PreprocessSuffix) engine.cpp

$(IntermediateDirectory)/drawable_text.cpp$(ObjectSuffix): drawable/text.cpp $(IntermediateDirectory)/drawable_text.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/drawable/text.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/drawable_text.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/drawable_text.cpp$(DependSuffix): drawable/text.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/drawable_text.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/drawable_text.cpp$(DependSuffix) -MM drawable/text.cpp

$(IntermediateDirectory)/drawable_text.cpp$(PreprocessSuffix): drawable/text.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/drawable_text.cpp$(PreprocessSuffix) drawable/text.cpp

$(IntermediateDirectory)/drawable_sprite.cpp$(ObjectSuffix): drawable/sprite.cpp $(IntermediateDirectory)/drawable_sprite.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/drawable/sprite.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/drawable_sprite.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/drawable_sprite.cpp$(DependSuffix): drawable/sprite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/drawable_sprite.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/drawable_sprite.cpp$(DependSuffix) -MM drawable/sprite.cpp

$(IntermediateDirectory)/drawable_sprite.cpp$(PreprocessSuffix): drawable/sprite.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/drawable_sprite.cpp$(PreprocessSuffix) drawable/sprite.cpp

$(IntermediateDirectory)/drawable_rect.cpp$(ObjectSuffix): drawable/rect.cpp $(IntermediateDirectory)/drawable_rect.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/drawable/rect.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/drawable_rect.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/drawable_rect.cpp$(DependSuffix): drawable/rect.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/drawable_rect.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/drawable_rect.cpp$(DependSuffix) -MM drawable/rect.cpp

$(IntermediateDirectory)/drawable_rect.cpp$(PreprocessSuffix): drawable/rect.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/drawable_rect.cpp$(PreprocessSuffix) drawable/rect.cpp

$(IntermediateDirectory)/drawable_color.cpp$(ObjectSuffix): drawable/color.cpp $(IntermediateDirectory)/drawable_color.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/drawable/color.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/drawable_color.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/drawable_color.cpp$(DependSuffix): drawable/color.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/drawable_color.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/drawable_color.cpp$(DependSuffix) -MM drawable/color.cpp

$(IntermediateDirectory)/drawable_color.cpp$(PreprocessSuffix): drawable/color.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/drawable_color.cpp$(PreprocessSuffix) drawable/color.cpp

$(IntermediateDirectory)/sound_sound.cpp$(ObjectSuffix): sound/sound.cpp $(IntermediateDirectory)/sound_sound.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/sound/sound.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sound_sound.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sound_sound.cpp$(DependSuffix): sound/sound.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sound_sound.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/sound_sound.cpp$(DependSuffix) -MM sound/sound.cpp

$(IntermediateDirectory)/sound_sound.cpp$(PreprocessSuffix): sound/sound.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sound_sound.cpp$(PreprocessSuffix) sound/sound.cpp

$(IntermediateDirectory)/sound_music.cpp$(ObjectSuffix): sound/music.cpp $(IntermediateDirectory)/sound_music.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/sound/music.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sound_music.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sound_music.cpp$(DependSuffix): sound/music.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sound_music.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/sound_music.cpp$(DependSuffix) -MM sound/music.cpp

$(IntermediateDirectory)/sound_music.cpp$(PreprocessSuffix): sound/music.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sound_music.cpp$(PreprocessSuffix) sound/music.cpp

$(IntermediateDirectory)/sound_chunk.cpp$(ObjectSuffix): sound/chunk.cpp $(IntermediateDirectory)/sound_chunk.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/sound/chunk.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sound_chunk.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sound_chunk.cpp$(DependSuffix): sound/chunk.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sound_chunk.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/sound_chunk.cpp$(DependSuffix) -MM sound/chunk.cpp

$(IntermediateDirectory)/sound_chunk.cpp$(PreprocessSuffix): sound/chunk.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sound_chunk.cpp$(PreprocessSuffix) sound/chunk.cpp

$(IntermediateDirectory)/file_file.cpp$(ObjectSuffix): file/file.cpp $(IntermediateDirectory)/file_file.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/file/file.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/file_file.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/file_file.cpp$(DependSuffix): file/file.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/file_file.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/file_file.cpp$(DependSuffix) -MM file/file.cpp

$(IntermediateDirectory)/file_file.cpp$(PreprocessSuffix): file/file.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/file_file.cpp$(PreprocessSuffix) file/file.cpp

$(IntermediateDirectory)/initialization_nick_setter.cpp$(ObjectSuffix): initialization/nick_setter.cpp $(IntermediateDirectory)/initialization_nick_setter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/initialization/nick_setter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/initialization_nick_setter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/initialization_nick_setter.cpp$(DependSuffix): initialization/nick_setter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/initialization_nick_setter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/initialization_nick_setter.cpp$(DependSuffix) -MM initialization/nick_setter.cpp

$(IntermediateDirectory)/initialization_nick_setter.cpp$(PreprocessSuffix): initialization/nick_setter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/initialization_nick_setter.cpp$(PreprocessSuffix) initialization/nick_setter.cpp

$(IntermediateDirectory)/initialization_nick_info.cpp$(ObjectSuffix): initialization/nick_info.cpp $(IntermediateDirectory)/initialization_nick_info.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/initialization/nick_info.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/initialization_nick_info.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/initialization_nick_info.cpp$(DependSuffix): initialization/nick_info.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/initialization_nick_info.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/initialization_nick_info.cpp$(DependSuffix) -MM initialization/nick_info.cpp

$(IntermediateDirectory)/initialization_nick_info.cpp$(PreprocessSuffix): initialization/nick_info.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/initialization_nick_info.cpp$(PreprocessSuffix) initialization/nick_info.cpp

$(IntermediateDirectory)/initialization_loading.cpp$(ObjectSuffix): initialization/loading.cpp $(IntermediateDirectory)/initialization_loading.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/initialization/loading.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/initialization_loading.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/initialization_loading.cpp$(DependSuffix): initialization/loading.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/initialization_loading.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/initialization_loading.cpp$(DependSuffix) -MM initialization/loading.cpp

$(IntermediateDirectory)/initialization_loading.cpp$(PreprocessSuffix): initialization/loading.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/initialization_loading.cpp$(PreprocessSuffix) initialization/loading.cpp

$(IntermediateDirectory)/initialization_initialization.cpp$(ObjectSuffix): initialization/initialization.cpp $(IntermediateDirectory)/initialization_initialization.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/initialization/initialization.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/initialization_initialization.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/initialization_initialization.cpp$(DependSuffix): initialization/initialization.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/initialization_initialization.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/initialization_initialization.cpp$(DependSuffix) -MM initialization/initialization.cpp

$(IntermediateDirectory)/initialization_initialization.cpp$(PreprocessSuffix): initialization/initialization.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/initialization_initialization.cpp$(PreprocessSuffix) initialization/initialization.cpp

$(IntermediateDirectory)/menu_menu.cpp$(ObjectSuffix): menu/menu.cpp $(IntermediateDirectory)/menu_menu.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/menu.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_menu.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_menu.cpp$(DependSuffix): menu/menu.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_menu.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_menu.cpp$(DependSuffix) -MM menu/menu.cpp

$(IntermediateDirectory)/menu_menu.cpp$(PreprocessSuffix): menu/menu.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_menu.cpp$(PreprocessSuffix) menu/menu.cpp

$(IntermediateDirectory)/menu_click.cpp$(ObjectSuffix): menu/click.cpp $(IntermediateDirectory)/menu_click.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/click.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_click.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_click.cpp$(DependSuffix): menu/click.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_click.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_click.cpp$(DependSuffix) -MM menu/click.cpp

$(IntermediateDirectory)/menu_click.cpp$(PreprocessSuffix): menu/click.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_click.cpp$(PreprocessSuffix) menu/click.cpp

$(IntermediateDirectory)/level_level.cpp$(ObjectSuffix): level/level.cpp $(IntermediateDirectory)/level_level.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/level/level.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/level_level.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/level_level.cpp$(DependSuffix): level/level.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/level_level.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/level_level.cpp$(DependSuffix) -MM level/level.cpp

$(IntermediateDirectory)/level_level.cpp$(PreprocessSuffix): level/level.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/level_level.cpp$(PreprocessSuffix) level/level.cpp

$(IntermediateDirectory)/level_difficulty.cpp$(ObjectSuffix): level/difficulty.cpp $(IntermediateDirectory)/level_difficulty.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/level/difficulty.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/level_difficulty.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/level_difficulty.cpp$(DependSuffix): level/difficulty.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/level_difficulty.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/level_difficulty.cpp$(DependSuffix) -MM level/difficulty.cpp

$(IntermediateDirectory)/level_difficulty.cpp$(PreprocessSuffix): level/difficulty.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/level_difficulty.cpp$(PreprocessSuffix) level/difficulty.cpp

$(IntermediateDirectory)/level_cube.cpp$(ObjectSuffix): level/cube.cpp $(IntermediateDirectory)/level_cube.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/level/cube.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/level_cube.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/level_cube.cpp$(DependSuffix): level/cube.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/level_cube.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/level_cube.cpp$(DependSuffix) -MM level/cube.cpp

$(IntermediateDirectory)/level_cube.cpp$(PreprocessSuffix): level/cube.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/level_cube.cpp$(PreprocessSuffix) level/cube.cpp

$(IntermediateDirectory)/level_choice.cpp$(ObjectSuffix): level/choice.cpp $(IntermediateDirectory)/level_choice.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/level/choice.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/level_choice.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/level_choice.cpp$(DependSuffix): level/choice.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/level_choice.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/level_choice.cpp$(DependSuffix) -MM level/choice.cpp

$(IntermediateDirectory)/level_choice.cpp$(PreprocessSuffix): level/choice.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/level_choice.cpp$(PreprocessSuffix) level/choice.cpp

$(IntermediateDirectory)/level_character.cpp$(ObjectSuffix): level/character.cpp $(IntermediateDirectory)/level_character.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/level/character.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/level_character.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/level_character.cpp$(DependSuffix): level/character.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/level_character.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/level_character.cpp$(DependSuffix) -MM level/character.cpp

$(IntermediateDirectory)/level_character.cpp$(PreprocessSuffix): level/character.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/level_character.cpp$(PreprocessSuffix) level/character.cpp

$(IntermediateDirectory)/level_backtomenu.cpp$(ObjectSuffix): level/backtomenu.cpp $(IntermediateDirectory)/level_backtomenu.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/level/backtomenu.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/level_backtomenu.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/level_backtomenu.cpp$(DependSuffix): level/backtomenu.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/level_backtomenu.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/level_backtomenu.cpp$(DependSuffix) -MM level/backtomenu.cpp

$(IntermediateDirectory)/level_backtomenu.cpp$(PreprocessSuffix): level/backtomenu.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/level_backtomenu.cpp$(PreprocessSuffix) level/backtomenu.cpp

$(IntermediateDirectory)/panel_show_scores.cpp$(ObjectSuffix): panel/show_scores.cpp $(IntermediateDirectory)/panel_show_scores.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/panel/show_scores.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/panel_show_scores.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/panel_show_scores.cpp$(DependSuffix): panel/show_scores.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/panel_show_scores.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/panel_show_scores.cpp$(DependSuffix) -MM panel/show_scores.cpp

$(IntermediateDirectory)/panel_show_scores.cpp$(PreprocessSuffix): panel/show_scores.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/panel_show_scores.cpp$(PreprocessSuffix) panel/show_scores.cpp

$(IntermediateDirectory)/panel_replay_button.cpp$(ObjectSuffix): panel/replay_button.cpp $(IntermediateDirectory)/panel_replay_button.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/panel/replay_button.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/panel_replay_button.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/panel_replay_button.cpp$(DependSuffix): panel/replay_button.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/panel_replay_button.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/panel_replay_button.cpp$(DependSuffix) -MM panel/replay_button.cpp

$(IntermediateDirectory)/panel_replay_button.cpp$(PreprocessSuffix): panel/replay_button.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/panel_replay_button.cpp$(PreprocessSuffix) panel/replay_button.cpp

$(IntermediateDirectory)/panel_panel_menu.cpp$(ObjectSuffix): panel/panel_menu.cpp $(IntermediateDirectory)/panel_panel_menu.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/panel/panel_menu.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/panel_panel_menu.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/panel_panel_menu.cpp$(DependSuffix): panel/panel_menu.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/panel_panel_menu.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/panel_panel_menu.cpp$(DependSuffix) -MM panel/panel_menu.cpp

$(IntermediateDirectory)/panel_panel_menu.cpp$(PreprocessSuffix): panel/panel_menu.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/panel_panel_menu.cpp$(PreprocessSuffix) panel/panel_menu.cpp

$(IntermediateDirectory)/panel_loading_world.cpp$(ObjectSuffix): panel/loading_world.cpp $(IntermediateDirectory)/panel_loading_world.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/panel/loading_world.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/panel_loading_world.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/panel_loading_world.cpp$(DependSuffix): panel/loading_world.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/panel_loading_world.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/panel_loading_world.cpp$(DependSuffix) -MM panel/loading_world.cpp

$(IntermediateDirectory)/panel_loading_world.cpp$(PreprocessSuffix): panel/loading_world.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/panel_loading_world.cpp$(PreprocessSuffix) panel/loading_world.cpp

$(IntermediateDirectory)/panel_backtomenu_panel.cpp$(ObjectSuffix): panel/backtomenu_panel.cpp $(IntermediateDirectory)/panel_backtomenu_panel.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/panel/backtomenu_panel.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/panel_backtomenu_panel.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/panel_backtomenu_panel.cpp$(DependSuffix): panel/backtomenu_panel.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/panel_backtomenu_panel.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/panel_backtomenu_panel.cpp$(DependSuffix) -MM panel/backtomenu_panel.cpp

$(IntermediateDirectory)/panel_backtomenu_panel.cpp$(PreprocessSuffix): panel/backtomenu_panel.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/panel_backtomenu_panel.cpp$(PreprocessSuffix) panel/backtomenu_panel.cpp

$(IntermediateDirectory)/menu_author_log_scroll.cpp$(ObjectSuffix): menu/author_log/scroll.cpp $(IntermediateDirectory)/menu_author_log_scroll.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/author_log/scroll.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_author_log_scroll.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_author_log_scroll.cpp$(DependSuffix): menu/author_log/scroll.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_author_log_scroll.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_author_log_scroll.cpp$(DependSuffix) -MM menu/author_log/scroll.cpp

$(IntermediateDirectory)/menu_author_log_scroll.cpp$(PreprocessSuffix): menu/author_log/scroll.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_author_log_scroll.cpp$(PreprocessSuffix) menu/author_log/scroll.cpp

$(IntermediateDirectory)/menu_author_log_member.cpp$(ObjectSuffix): menu/author_log/member.cpp $(IntermediateDirectory)/menu_author_log_member.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/author_log/member.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_author_log_member.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_author_log_member.cpp$(DependSuffix): menu/author_log/member.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_author_log_member.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_author_log_member.cpp$(DependSuffix) -MM menu/author_log/member.cpp

$(IntermediateDirectory)/menu_author_log_member.cpp$(PreprocessSuffix): menu/author_log/member.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_author_log_member.cpp$(PreprocessSuffix) menu/author_log/member.cpp

$(IntermediateDirectory)/menu_author_log_list.cpp$(ObjectSuffix): menu/author_log/list.cpp $(IntermediateDirectory)/menu_author_log_list.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/author_log/list.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_author_log_list.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_author_log_list.cpp$(DependSuffix): menu/author_log/list.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_author_log_list.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_author_log_list.cpp$(DependSuffix) -MM menu/author_log/list.cpp

$(IntermediateDirectory)/menu_author_log_list.cpp$(PreprocessSuffix): menu/author_log/list.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_author_log_list.cpp$(PreprocessSuffix) menu/author_log/list.cpp

$(IntermediateDirectory)/menu_author_log_author_info.cpp$(ObjectSuffix): menu/author_log/author_info.cpp $(IntermediateDirectory)/menu_author_log_author_info.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/author_log/author_info.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_author_log_author_info.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_author_log_author_info.cpp$(DependSuffix): menu/author_log/author_info.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_author_log_author_info.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_author_log_author_info.cpp$(DependSuffix) -MM menu/author_log/author_info.cpp

$(IntermediateDirectory)/menu_author_log_author_info.cpp$(PreprocessSuffix): menu/author_log/author_info.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_author_log_author_info.cpp$(PreprocessSuffix) menu/author_log/author_info.cpp

$(IntermediateDirectory)/menu_author_log_author.cpp$(ObjectSuffix): menu/author_log/author.cpp $(IntermediateDirectory)/menu_author_log_author.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/author_log/author.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_author_log_author.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_author_log_author.cpp$(DependSuffix): menu/author_log/author.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_author_log_author.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_author_log_author.cpp$(DependSuffix) -MM menu/author_log/author.cpp

$(IntermediateDirectory)/menu_author_log_author.cpp$(PreprocessSuffix): menu/author_log/author.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_author_log_author.cpp$(PreprocessSuffix) menu/author_log/author.cpp

$(IntermediateDirectory)/menu_development_headdeck.cpp$(ObjectSuffix): menu/development/headdeck.cpp $(IntermediateDirectory)/menu_development_headdeck.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/development/headdeck.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_development_headdeck.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_development_headdeck.cpp$(DependSuffix): menu/development/headdeck.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_development_headdeck.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_development_headdeck.cpp$(DependSuffix) -MM menu/development/headdeck.cpp

$(IntermediateDirectory)/menu_development_headdeck.cpp$(PreprocessSuffix): menu/development/headdeck.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_development_headdeck.cpp$(PreprocessSuffix) menu/development/headdeck.cpp

$(IntermediateDirectory)/menu_development_head.cpp$(ObjectSuffix): menu/development/head.cpp $(IntermediateDirectory)/menu_development_head.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/development/head.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_development_head.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_development_head.cpp$(DependSuffix): menu/development/head.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_development_head.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_development_head.cpp$(DependSuffix) -MM menu/development/head.cpp

$(IntermediateDirectory)/menu_development_head.cpp$(PreprocessSuffix): menu/development/head.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_development_head.cpp$(PreprocessSuffix) menu/development/head.cpp

$(IntermediateDirectory)/menu_development_developdeck.cpp$(ObjectSuffix): menu/development/developdeck.cpp $(IntermediateDirectory)/menu_development_developdeck.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/development/developdeck.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_development_developdeck.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_development_developdeck.cpp$(DependSuffix): menu/development/developdeck.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_development_developdeck.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_development_developdeck.cpp$(DependSuffix) -MM menu/development/developdeck.cpp

$(IntermediateDirectory)/menu_development_developdeck.cpp$(PreprocessSuffix): menu/development/developdeck.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_development_developdeck.cpp$(PreprocessSuffix) menu/development/developdeck.cpp

$(IntermediateDirectory)/menu_development_develop.cpp$(ObjectSuffix): menu/development/develop.cpp $(IntermediateDirectory)/menu_development_develop.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/development/develop.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_development_develop.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_development_develop.cpp$(DependSuffix): menu/development/develop.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_development_develop.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_development_develop.cpp$(DependSuffix) -MM menu/development/develop.cpp

$(IntermediateDirectory)/menu_development_develop.cpp$(PreprocessSuffix): menu/development/develop.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_development_develop.cpp$(PreprocessSuffix) menu/development/develop.cpp

$(IntermediateDirectory)/menu_explanator_explanator.cpp$(ObjectSuffix): menu/explanator/explanator.cpp $(IntermediateDirectory)/menu_explanator_explanator.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/explanator/explanator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_explanator_explanator.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_explanator_explanator.cpp$(DependSuffix): menu/explanator/explanator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_explanator_explanator.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_explanator_explanator.cpp$(DependSuffix) -MM menu/explanator/explanator.cpp

$(IntermediateDirectory)/menu_explanator_explanator.cpp$(PreprocessSuffix): menu/explanator/explanator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_explanator_explanator.cpp$(PreprocessSuffix) menu/explanator/explanator.cpp

$(IntermediateDirectory)/menu_keyboard_keyboard.cpp$(ObjectSuffix): menu/keyboard/keyboard.cpp $(IntermediateDirectory)/menu_keyboard_keyboard.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/keyboard/keyboard.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_keyboard_keyboard.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_keyboard_keyboard.cpp$(DependSuffix): menu/keyboard/keyboard.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_keyboard_keyboard.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_keyboard_keyboard.cpp$(DependSuffix) -MM menu/keyboard/keyboard.cpp

$(IntermediateDirectory)/menu_keyboard_keyboard.cpp$(PreprocessSuffix): menu/keyboard/keyboard.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_keyboard_keyboard.cpp$(PreprocessSuffix) menu/keyboard/keyboard.cpp

$(IntermediateDirectory)/menu_keyboard_information.cpp$(ObjectSuffix): menu/keyboard/information.cpp $(IntermediateDirectory)/menu_keyboard_information.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/keyboard/information.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_keyboard_information.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_keyboard_information.cpp$(DependSuffix): menu/keyboard/information.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_keyboard_information.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_keyboard_information.cpp$(DependSuffix) -MM menu/keyboard/information.cpp

$(IntermediateDirectory)/menu_keyboard_information.cpp$(PreprocessSuffix): menu/keyboard/information.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_keyboard_information.cpp$(PreprocessSuffix) menu/keyboard/information.cpp

$(IntermediateDirectory)/menu_link_button_link_button.cpp$(ObjectSuffix): menu/link_button/link_button.cpp $(IntermediateDirectory)/menu_link_button_link_button.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/link_button/link_button.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_link_button_link_button.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_link_button_link_button.cpp$(DependSuffix): menu/link_button/link_button.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_link_button_link_button.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_link_button_link_button.cpp$(DependSuffix) -MM menu/link_button/link_button.cpp

$(IntermediateDirectory)/menu_link_button_link_button.cpp$(PreprocessSuffix): menu/link_button/link_button.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_link_button_link_button.cpp$(PreprocessSuffix) menu/link_button/link_button.cpp

$(IntermediateDirectory)/menu_log_log.cpp$(ObjectSuffix): menu/log/log.cpp $(IntermediateDirectory)/menu_log_log.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/log/log.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_log_log.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_log_log.cpp$(DependSuffix): menu/log/log.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_log_log.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_log_log.cpp$(DependSuffix) -MM menu/log/log.cpp

$(IntermediateDirectory)/menu_log_log.cpp$(PreprocessSuffix): menu/log/log.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_log_log.cpp$(PreprocessSuffix) menu/log/log.cpp

$(IntermediateDirectory)/menu_nick_nick.cpp$(ObjectSuffix): menu/nick/nick.cpp $(IntermediateDirectory)/menu_nick_nick.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/nick/nick.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_nick_nick.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_nick_nick.cpp$(DependSuffix): menu/nick/nick.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_nick_nick.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_nick_nick.cpp$(DependSuffix) -MM menu/nick/nick.cpp

$(IntermediateDirectory)/menu_nick_nick.cpp$(PreprocessSuffix): menu/nick/nick.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_nick_nick.cpp$(PreprocessSuffix) menu/nick/nick.cpp

$(IntermediateDirectory)/menu_play_button_play_button.cpp$(ObjectSuffix): menu/play_button/play_button.cpp $(IntermediateDirectory)/menu_play_button_play_button.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/play_button/play_button.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_play_button_play_button.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_play_button_play_button.cpp$(DependSuffix): menu/play_button/play_button.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_play_button_play_button.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_play_button_play_button.cpp$(DependSuffix) -MM menu/play_button/play_button.cpp

$(IntermediateDirectory)/menu_play_button_play_button.cpp$(PreprocessSuffix): menu/play_button/play_button.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_play_button_play_button.cpp$(PreprocessSuffix) menu/play_button/play_button.cpp

$(IntermediateDirectory)/menu_play_button_exit_log.cpp$(ObjectSuffix): menu/play_button/exit_log.cpp $(IntermediateDirectory)/menu_play_button_exit_log.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/play_button/exit_log.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_play_button_exit_log.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_play_button_exit_log.cpp$(DependSuffix): menu/play_button/exit_log.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_play_button_exit_log.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_play_button_exit_log.cpp$(DependSuffix) -MM menu/play_button/exit_log.cpp

$(IntermediateDirectory)/menu_play_button_exit_log.cpp$(PreprocessSuffix): menu/play_button/exit_log.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_play_button_exit_log.cpp$(PreprocessSuffix) menu/play_button/exit_log.cpp

$(IntermediateDirectory)/menu_reset_button_reset_button.cpp$(ObjectSuffix): menu/reset_button/reset_button.cpp $(IntermediateDirectory)/menu_reset_button_reset_button.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/reset_button/reset_button.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_reset_button_reset_button.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_reset_button_reset_button.cpp$(DependSuffix): menu/reset_button/reset_button.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_reset_button_reset_button.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_reset_button_reset_button.cpp$(DependSuffix) -MM menu/reset_button/reset_button.cpp

$(IntermediateDirectory)/menu_reset_button_reset_button.cpp$(PreprocessSuffix): menu/reset_button/reset_button.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_reset_button_reset_button.cpp$(PreprocessSuffix) menu/reset_button/reset_button.cpp

$(IntermediateDirectory)/menu_sound_button_sound_button.cpp$(ObjectSuffix): menu/sound_button/sound_button.cpp $(IntermediateDirectory)/menu_sound_button_sound_button.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/sound_button/sound_button.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_sound_button_sound_button.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_sound_button_sound_button.cpp$(DependSuffix): menu/sound_button/sound_button.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_sound_button_sound_button.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_sound_button_sound_button.cpp$(DependSuffix) -MM menu/sound_button/sound_button.cpp

$(IntermediateDirectory)/menu_sound_button_sound_button.cpp$(PreprocessSuffix): menu/sound_button/sound_button.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_sound_button_sound_button.cpp$(PreprocessSuffix) menu/sound_button/sound_button.cpp

$(IntermediateDirectory)/menu_title_title.cpp$(ObjectSuffix): menu/title/title.cpp $(IntermediateDirectory)/menu_title_title.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/title/title.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_title_title.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_title_title.cpp$(DependSuffix): menu/title/title.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_title_title.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_title_title.cpp$(DependSuffix) -MM menu/title/title.cpp

$(IntermediateDirectory)/menu_title_title.cpp$(PreprocessSuffix): menu/title/title.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_title_title.cpp$(PreprocessSuffix) menu/title/title.cpp

$(IntermediateDirectory)/menu_volume_button_volume_button.cpp$(ObjectSuffix): menu/volume_button/volume_button.cpp $(IntermediateDirectory)/menu_volume_button_volume_button.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/volume_button/volume_button.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_volume_button_volume_button.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_volume_button_volume_button.cpp$(DependSuffix): menu/volume_button/volume_button.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_volume_button_volume_button.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_volume_button_volume_button.cpp$(DependSuffix) -MM menu/volume_button/volume_button.cpp

$(IntermediateDirectory)/menu_volume_button_volume_button.cpp$(PreprocessSuffix): menu/volume_button/volume_button.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_volume_button_volume_button.cpp$(PreprocessSuffix) menu/volume_button/volume_button.cpp

$(IntermediateDirectory)/platform_desert_desert_mechanics.cpp$(ObjectSuffix): platform/desert/desert_mechanics.cpp $(IntermediateDirectory)/platform_desert_desert_mechanics.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/desert/desert_mechanics.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_desert_desert_mechanics.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_desert_desert_mechanics.cpp$(DependSuffix): platform/desert/desert_mechanics.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_desert_desert_mechanics.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_desert_desert_mechanics.cpp$(DependSuffix) -MM platform/desert/desert_mechanics.cpp

$(IntermediateDirectory)/platform_desert_desert_mechanics.cpp$(PreprocessSuffix): platform/desert/desert_mechanics.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_desert_desert_mechanics.cpp$(PreprocessSuffix) platform/desert/desert_mechanics.cpp

$(IntermediateDirectory)/platform_desert_desert.cpp$(ObjectSuffix): platform/desert/desert.cpp $(IntermediateDirectory)/platform_desert_desert.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/desert/desert.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_desert_desert.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_desert_desert.cpp$(DependSuffix): platform/desert/desert.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_desert_desert.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_desert_desert.cpp$(DependSuffix) -MM platform/desert/desert.cpp

$(IntermediateDirectory)/platform_desert_desert.cpp$(PreprocessSuffix): platform/desert/desert.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_desert_desert.cpp$(PreprocessSuffix) platform/desert/desert.cpp

$(IntermediateDirectory)/platform_forest_forest_mechanics.cpp$(ObjectSuffix): platform/forest/forest_mechanics.cpp $(IntermediateDirectory)/platform_forest_forest_mechanics.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/forest/forest_mechanics.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_forest_forest_mechanics.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_forest_forest_mechanics.cpp$(DependSuffix): platform/forest/forest_mechanics.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_forest_forest_mechanics.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_forest_forest_mechanics.cpp$(DependSuffix) -MM platform/forest/forest_mechanics.cpp

$(IntermediateDirectory)/platform_forest_forest_mechanics.cpp$(PreprocessSuffix): platform/forest/forest_mechanics.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_forest_forest_mechanics.cpp$(PreprocessSuffix) platform/forest/forest_mechanics.cpp

$(IntermediateDirectory)/platform_forest_forest.cpp$(ObjectSuffix): platform/forest/forest.cpp $(IntermediateDirectory)/platform_forest_forest.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/forest/forest.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_forest_forest.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_forest_forest.cpp$(DependSuffix): platform/forest/forest.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_forest_forest.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_forest_forest.cpp$(DependSuffix) -MM platform/forest/forest.cpp

$(IntermediateDirectory)/platform_forest_forest.cpp$(PreprocessSuffix): platform/forest/forest.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_forest_forest.cpp$(PreprocessSuffix) platform/forest/forest.cpp

$(IntermediateDirectory)/platform_winter_winter_mechanics.cpp$(ObjectSuffix): platform/winter/winter_mechanics.cpp $(IntermediateDirectory)/platform_winter_winter_mechanics.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/winter/winter_mechanics.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_winter_winter_mechanics.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_winter_winter_mechanics.cpp$(DependSuffix): platform/winter/winter_mechanics.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_winter_winter_mechanics.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_winter_winter_mechanics.cpp$(DependSuffix) -MM platform/winter/winter_mechanics.cpp

$(IntermediateDirectory)/platform_winter_winter_mechanics.cpp$(PreprocessSuffix): platform/winter/winter_mechanics.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_winter_winter_mechanics.cpp$(PreprocessSuffix) platform/winter/winter_mechanics.cpp

$(IntermediateDirectory)/platform_winter_winter.cpp$(ObjectSuffix): platform/winter/winter.cpp $(IntermediateDirectory)/platform_winter_winter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/winter/winter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_winter_winter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_winter_winter.cpp$(DependSuffix): platform/winter/winter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_winter_winter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_winter_winter.cpp$(DependSuffix) -MM platform/winter/winter.cpp

$(IntermediateDirectory)/platform_winter_winter.cpp$(PreprocessSuffix): platform/winter/winter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_winter_winter.cpp$(PreprocessSuffix) platform/winter/winter.cpp

$(IntermediateDirectory)/platform_halloween_halloween_mechanics.cpp$(ObjectSuffix): platform/halloween/halloween_mechanics.cpp $(IntermediateDirectory)/platform_halloween_halloween_mechanics.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/halloween/halloween_mechanics.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_halloween_halloween_mechanics.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_halloween_halloween_mechanics.cpp$(DependSuffix): platform/halloween/halloween_mechanics.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_halloween_halloween_mechanics.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_halloween_halloween_mechanics.cpp$(DependSuffix) -MM platform/halloween/halloween_mechanics.cpp

$(IntermediateDirectory)/platform_halloween_halloween_mechanics.cpp$(PreprocessSuffix): platform/halloween/halloween_mechanics.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_halloween_halloween_mechanics.cpp$(PreprocessSuffix) platform/halloween/halloween_mechanics.cpp

$(IntermediateDirectory)/platform_halloween_halloween.cpp$(ObjectSuffix): platform/halloween/halloween.cpp $(IntermediateDirectory)/platform_halloween_halloween.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/halloween/halloween.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_halloween_halloween.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_halloween_halloween.cpp$(DependSuffix): platform/halloween/halloween.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_halloween_halloween.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_halloween_halloween.cpp$(DependSuffix) -MM platform/halloween/halloween.cpp

$(IntermediateDirectory)/platform_halloween_halloween.cpp$(PreprocessSuffix): platform/halloween/halloween.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_halloween_halloween.cpp$(PreprocessSuffix) platform/halloween/halloween.cpp

$(IntermediateDirectory)/platform_future_future_mechanics.cpp$(ObjectSuffix): platform/future/future_mechanics.cpp $(IntermediateDirectory)/platform_future_future_mechanics.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/future/future_mechanics.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_future_future_mechanics.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_future_future_mechanics.cpp$(DependSuffix): platform/future/future_mechanics.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_future_future_mechanics.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_future_future_mechanics.cpp$(DependSuffix) -MM platform/future/future_mechanics.cpp

$(IntermediateDirectory)/platform_future_future_mechanics.cpp$(PreprocessSuffix): platform/future/future_mechanics.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_future_future_mechanics.cpp$(PreprocessSuffix) platform/future/future_mechanics.cpp

$(IntermediateDirectory)/platform_future_future.cpp$(ObjectSuffix): platform/future/future.cpp $(IntermediateDirectory)/platform_future_future.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/future/future.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_future_future.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_future_future.cpp$(DependSuffix): platform/future/future.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_future_future.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_future_future.cpp$(DependSuffix) -MM platform/future/future.cpp

$(IntermediateDirectory)/platform_future_future.cpp$(PreprocessSuffix): platform/future/future.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_future_future.cpp$(PreprocessSuffix) platform/future/future.cpp

$(IntermediateDirectory)/platform_ninja_kunai_kunai_effects.cpp$(ObjectSuffix): platform/ninja/kunai/kunai_effects.cpp $(IntermediateDirectory)/platform_ninja_kunai_kunai_effects.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/ninja/kunai/kunai_effects.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_ninja_kunai_kunai_effects.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_ninja_kunai_kunai_effects.cpp$(DependSuffix): platform/ninja/kunai/kunai_effects.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_ninja_kunai_kunai_effects.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_ninja_kunai_kunai_effects.cpp$(DependSuffix) -MM platform/ninja/kunai/kunai_effects.cpp

$(IntermediateDirectory)/platform_ninja_kunai_kunai_effects.cpp$(PreprocessSuffix): platform/ninja/kunai/kunai_effects.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_ninja_kunai_kunai_effects.cpp$(PreprocessSuffix) platform/ninja/kunai/kunai_effects.cpp

$(IntermediateDirectory)/platform_ninja_kunai_kunai_bit.cpp$(ObjectSuffix): platform/ninja/kunai/kunai_bit.cpp $(IntermediateDirectory)/platform_ninja_kunai_kunai_bit.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/ninja/kunai/kunai_bit.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_ninja_kunai_kunai_bit.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_ninja_kunai_kunai_bit.cpp$(DependSuffix): platform/ninja/kunai/kunai_bit.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_ninja_kunai_kunai_bit.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_ninja_kunai_kunai_bit.cpp$(DependSuffix) -MM platform/ninja/kunai/kunai_bit.cpp

$(IntermediateDirectory)/platform_ninja_kunai_kunai_bit.cpp$(PreprocessSuffix): platform/ninja/kunai/kunai_bit.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_ninja_kunai_kunai_bit.cpp$(PreprocessSuffix) platform/ninja/kunai/kunai_bit.cpp

$(IntermediateDirectory)/platform_ninja_kunai_kunai.cpp$(ObjectSuffix): platform/ninja/kunai/kunai.cpp $(IntermediateDirectory)/platform_ninja_kunai_kunai.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/ninja/kunai/kunai.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_ninja_kunai_kunai.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_ninja_kunai_kunai.cpp$(DependSuffix): platform/ninja/kunai/kunai.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_ninja_kunai_kunai.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_ninja_kunai_kunai.cpp$(DependSuffix) -MM platform/ninja/kunai/kunai.cpp

$(IntermediateDirectory)/platform_ninja_kunai_kunai.cpp$(PreprocessSuffix): platform/ninja/kunai/kunai.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_ninja_kunai_kunai.cpp$(PreprocessSuffix) platform/ninja/kunai/kunai.cpp

$(IntermediateDirectory)/platform_ninja_kunai_damage.cpp$(ObjectSuffix): platform/ninja/kunai/damage.cpp $(IntermediateDirectory)/platform_ninja_kunai_damage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/ninja/kunai/damage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_ninja_kunai_damage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_ninja_kunai_damage.cpp$(DependSuffix): platform/ninja/kunai/damage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_ninja_kunai_damage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_ninja_kunai_damage.cpp$(DependSuffix) -MM platform/ninja/kunai/damage.cpp

$(IntermediateDirectory)/platform_ninja_kunai_damage.cpp$(PreprocessSuffix): platform/ninja/kunai/damage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_ninja_kunai_damage.cpp$(PreprocessSuffix) platform/ninja/kunai/damage.cpp

$(IntermediateDirectory)/platform_ninja_base_ninja_basic.cpp$(ObjectSuffix): platform/ninja/base/ninja_basic.cpp $(IntermediateDirectory)/platform_ninja_base_ninja_basic.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/ninja/base/ninja_basic.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_ninja_base_ninja_basic.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_ninja_base_ninja_basic.cpp$(DependSuffix): platform/ninja/base/ninja_basic.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_ninja_base_ninja_basic.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_ninja_base_ninja_basic.cpp$(DependSuffix) -MM platform/ninja/base/ninja_basic.cpp

$(IntermediateDirectory)/platform_ninja_base_ninja_basic.cpp$(PreprocessSuffix): platform/ninja/base/ninja_basic.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_ninja_base_ninja_basic.cpp$(PreprocessSuffix) platform/ninja/base/ninja_basic.cpp

$(IntermediateDirectory)/platform_ninja_base_ninja.cpp$(ObjectSuffix): platform/ninja/base/ninja.cpp $(IntermediateDirectory)/platform_ninja_base_ninja.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/ninja/base/ninja.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_ninja_base_ninja.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_ninja_base_ninja.cpp$(DependSuffix): platform/ninja/base/ninja.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_ninja_base_ninja.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_ninja_base_ninja.cpp$(DependSuffix) -MM platform/ninja/base/ninja.cpp

$(IntermediateDirectory)/platform_ninja_base_ninja.cpp$(PreprocessSuffix): platform/ninja/base/ninja.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_ninja_base_ninja.cpp$(PreprocessSuffix) platform/ninja/base/ninja.cpp

$(IntermediateDirectory)/platform_ninja_base_activity.cpp$(ObjectSuffix): platform/ninja/base/activity.cpp $(IntermediateDirectory)/platform_ninja_base_activity.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/ninja/base/activity.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_ninja_base_activity.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_ninja_base_activity.cpp$(DependSuffix): platform/ninja/base/activity.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_ninja_base_activity.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_ninja_base_activity.cpp$(DependSuffix) -MM platform/ninja/base/activity.cpp

$(IntermediateDirectory)/platform_ninja_base_activity.cpp$(PreprocessSuffix): platform/ninja/base/activity.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_ninja_base_activity.cpp$(PreprocessSuffix) platform/ninja/base/activity.cpp

$(IntermediateDirectory)/platform_ninja_scope_scope.cpp$(ObjectSuffix): platform/ninja/scope/scope.cpp $(IntermediateDirectory)/platform_ninja_scope_scope.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/ninja/scope/scope.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_ninja_scope_scope.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_ninja_scope_scope.cpp$(DependSuffix): platform/ninja/scope/scope.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_ninja_scope_scope.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_ninja_scope_scope.cpp$(DependSuffix) -MM platform/ninja/scope/scope.cpp

$(IntermediateDirectory)/platform_ninja_scope_scope.cpp$(PreprocessSuffix): platform/ninja/scope/scope.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_ninja_scope_scope.cpp$(PreprocessSuffix) platform/ninja/scope/scope.cpp

$(IntermediateDirectory)/platform_panel_heart_heart_bit.cpp$(ObjectSuffix): platform/panel/heart/heart_bit.cpp $(IntermediateDirectory)/platform_panel_heart_heart_bit.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/panel/heart/heart_bit.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_panel_heart_heart_bit.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_panel_heart_heart_bit.cpp$(DependSuffix): platform/panel/heart/heart_bit.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_panel_heart_heart_bit.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_panel_heart_heart_bit.cpp$(DependSuffix) -MM platform/panel/heart/heart_bit.cpp

$(IntermediateDirectory)/platform_panel_heart_heart_bit.cpp$(PreprocessSuffix): platform/panel/heart/heart_bit.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_panel_heart_heart_bit.cpp$(PreprocessSuffix) platform/panel/heart/heart_bit.cpp

$(IntermediateDirectory)/platform_panel_heart_heart.cpp$(ObjectSuffix): platform/panel/heart/heart.cpp $(IntermediateDirectory)/platform_panel_heart_heart.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/panel/heart/heart.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_panel_heart_heart.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_panel_heart_heart.cpp$(DependSuffix): platform/panel/heart/heart.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_panel_heart_heart.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_panel_heart_heart.cpp$(DependSuffix) -MM platform/panel/heart/heart.cpp

$(IntermediateDirectory)/platform_panel_heart_heart.cpp$(PreprocessSuffix): platform/panel/heart/heart.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_panel_heart_heart.cpp$(PreprocessSuffix) platform/panel/heart/heart.cpp

$(IntermediateDirectory)/platform_panel_money_money.cpp$(ObjectSuffix): platform/panel/money/money.cpp $(IntermediateDirectory)/platform_panel_money_money.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/panel/money/money.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_panel_money_money.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_panel_money_money.cpp$(DependSuffix): platform/panel/money/money.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_panel_money_money.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_panel_money_money.cpp$(DependSuffix) -MM platform/panel/money/money.cpp

$(IntermediateDirectory)/platform_panel_money_money.cpp$(PreprocessSuffix): platform/panel/money/money.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_panel_money_money.cpp$(PreprocessSuffix) platform/panel/money/money.cpp

$(IntermediateDirectory)/platform_panel_pause_pause.cpp$(ObjectSuffix): platform/panel/pause/pause.cpp $(IntermediateDirectory)/platform_panel_pause_pause.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/panel/pause/pause.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_panel_pause_pause.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_panel_pause_pause.cpp$(DependSuffix): platform/panel/pause/pause.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_panel_pause_pause.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_panel_pause_pause.cpp$(DependSuffix) -MM platform/panel/pause/pause.cpp

$(IntermediateDirectory)/platform_panel_pause_pause.cpp$(PreprocessSuffix): platform/panel/pause/pause.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_panel_pause_pause.cpp$(PreprocessSuffix) platform/panel/pause/pause.cpp

$(IntermediateDirectory)/platform_panel_scores_scores.cpp$(ObjectSuffix): platform/panel/scores/scores.cpp $(IntermediateDirectory)/platform_panel_scores_scores.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/panel/scores/scores.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_panel_scores_scores.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_panel_scores_scores.cpp$(DependSuffix): platform/panel/scores/scores.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_panel_scores_scores.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_panel_scores_scores.cpp$(DependSuffix) -MM platform/panel/scores/scores.cpp

$(IntermediateDirectory)/platform_panel_scores_scores.cpp$(PreprocessSuffix): platform/panel/scores/scores.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_panel_scores_scores.cpp$(PreprocessSuffix) platform/panel/scores/scores.cpp

$(IntermediateDirectory)/platform_panel_skill_skills.cpp$(ObjectSuffix): platform/panel/skill/skills.cpp $(IntermediateDirectory)/platform_panel_skill_skills.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/panel/skill/skills.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_panel_skill_skills.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_panel_skill_skills.cpp$(DependSuffix): platform/panel/skill/skills.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_panel_skill_skills.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_panel_skill_skills.cpp$(DependSuffix) -MM platform/panel/skill/skills.cpp

$(IntermediateDirectory)/platform_panel_skill_skills.cpp$(PreprocessSuffix): platform/panel/skill/skills.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_panel_skill_skills.cpp$(PreprocessSuffix) platform/panel/skill/skills.cpp

$(IntermediateDirectory)/platform_panel_skill_skill_effect.cpp$(ObjectSuffix): platform/panel/skill/skill_effect.cpp $(IntermediateDirectory)/platform_panel_skill_skill_effect.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/panel/skill/skill_effect.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_panel_skill_skill_effect.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_panel_skill_skill_effect.cpp$(DependSuffix): platform/panel/skill/skill_effect.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_panel_skill_skill_effect.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_panel_skill_skill_effect.cpp$(DependSuffix) -MM platform/panel/skill/skill_effect.cpp

$(IntermediateDirectory)/platform_panel_skill_skill_effect.cpp$(PreprocessSuffix): platform/panel/skill/skill_effect.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_panel_skill_skill_effect.cpp$(PreprocessSuffix) platform/panel/skill/skill_effect.cpp

$(IntermediateDirectory)/platform_panel_skill_skill.cpp$(ObjectSuffix): platform/panel/skill/skill.cpp $(IntermediateDirectory)/platform_panel_skill_skill.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/panel/skill/skill.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_panel_skill_skill.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_panel_skill_skill.cpp$(DependSuffix): platform/panel/skill/skill.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_panel_skill_skill.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_panel_skill_skill.cpp$(DependSuffix) -MM platform/panel/skill/skill.cpp

$(IntermediateDirectory)/platform_panel_skill_skill.cpp$(PreprocessSuffix): platform/panel/skill/skill.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_panel_skill_skill.cpp$(PreprocessSuffix) platform/panel/skill/skill.cpp

$(IntermediateDirectory)/platform_panel_sound_pad_sound_pad.cpp$(ObjectSuffix): platform/panel/sound_pad/sound_pad.cpp $(IntermediateDirectory)/platform_panel_sound_pad_sound_pad.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/panel/sound_pad/sound_pad.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_panel_sound_pad_sound_pad.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_panel_sound_pad_sound_pad.cpp$(DependSuffix): platform/panel/sound_pad/sound_pad.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_panel_sound_pad_sound_pad.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_panel_sound_pad_sound_pad.cpp$(DependSuffix) -MM platform/panel/sound_pad/sound_pad.cpp

$(IntermediateDirectory)/platform_panel_sound_pad_sound_pad.cpp$(PreprocessSuffix): platform/panel/sound_pad/sound_pad.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_panel_sound_pad_sound_pad.cpp$(PreprocessSuffix) platform/panel/sound_pad/sound_pad.cpp

$(IntermediateDirectory)/platform_panel_time_box_time_box.cpp$(ObjectSuffix): platform/panel/time_box/time_box.cpp $(IntermediateDirectory)/platform_panel_time_box_time_box.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/panel/time_box/time_box.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_panel_time_box_time_box.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_panel_time_box_time_box.cpp$(DependSuffix): platform/panel/time_box/time_box.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_panel_time_box_time_box.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_panel_time_box_time_box.cpp$(DependSuffix) -MM platform/panel/time_box/time_box.cpp

$(IntermediateDirectory)/platform_panel_time_box_time_box.cpp$(PreprocessSuffix): platform/panel/time_box/time_box.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_panel_time_box_time_box.cpp$(PreprocessSuffix) platform/panel/time_box/time_box.cpp

$(IntermediateDirectory)/platform_world_background_day.cpp$(ObjectSuffix): platform/world/background/day.cpp $(IntermediateDirectory)/platform_world_background_day.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/background/day.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_background_day.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_background_day.cpp$(DependSuffix): platform/world/background/day.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_background_day.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_background_day.cpp$(DependSuffix) -MM platform/world/background/day.cpp

$(IntermediateDirectory)/platform_world_background_day.cpp$(PreprocessSuffix): platform/world/background/day.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_background_day.cpp$(PreprocessSuffix) platform/world/background/day.cpp

$(IntermediateDirectory)/platform_world_background_background.cpp$(ObjectSuffix): platform/world/background/background.cpp $(IntermediateDirectory)/platform_world_background_background.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/background/background.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_background_background.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_background_background.cpp$(DependSuffix): platform/world/background/background.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_background_background.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_background_background.cpp$(DependSuffix) -MM platform/world/background/background.cpp

$(IntermediateDirectory)/platform_world_background_background.cpp$(PreprocessSuffix): platform/world/background/background.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_background_background.cpp$(PreprocessSuffix) platform/world/background/background.cpp

$(IntermediateDirectory)/platform_world_wall_wall.cpp$(ObjectSuffix): platform/world/wall/wall.cpp $(IntermediateDirectory)/platform_world_wall_wall.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/wall/wall.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_wall_wall.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_wall_wall.cpp$(DependSuffix): platform/world/wall/wall.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_wall_wall.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_wall_wall.cpp$(DependSuffix) -MM platform/world/wall/wall.cpp

$(IntermediateDirectory)/platform_world_wall_wall.cpp$(PreprocessSuffix): platform/world/wall/wall.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_wall_wall.cpp$(PreprocessSuffix) platform/world/wall/wall.cpp

$(IntermediateDirectory)/platform_world_wall_pug.cpp$(ObjectSuffix): platform/world/wall/pug.cpp $(IntermediateDirectory)/platform_world_wall_pug.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/wall/pug.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_wall_pug.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_wall_pug.cpp$(DependSuffix): platform/world/wall/pug.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_wall_pug.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_wall_pug.cpp$(DependSuffix) -MM platform/world/wall/pug.cpp

$(IntermediateDirectory)/platform_world_wall_pug.cpp$(PreprocessSuffix): platform/world/wall/pug.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_wall_pug.cpp$(PreprocessSuffix) platform/world/wall/pug.cpp

$(IntermediateDirectory)/platform_world_boulder_boulders.cpp$(ObjectSuffix): platform/world/boulder/boulders.cpp $(IntermediateDirectory)/platform_world_boulder_boulders.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/boulder/boulders.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_boulder_boulders.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_boulder_boulders.cpp$(DependSuffix): platform/world/boulder/boulders.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_boulder_boulders.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_boulder_boulders.cpp$(DependSuffix) -MM platform/world/boulder/boulders.cpp

$(IntermediateDirectory)/platform_world_boulder_boulders.cpp$(PreprocessSuffix): platform/world/boulder/boulders.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_boulder_boulders.cpp$(PreprocessSuffix) platform/world/boulder/boulders.cpp

$(IntermediateDirectory)/platform_world_boulder_boulder.cpp$(ObjectSuffix): platform/world/boulder/boulder.cpp $(IntermediateDirectory)/platform_world_boulder_boulder.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/boulder/boulder.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_boulder_boulder.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_boulder_boulder.cpp$(DependSuffix): platform/world/boulder/boulder.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_boulder_boulder.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_boulder_boulder.cpp$(DependSuffix) -MM platform/world/boulder/boulder.cpp

$(IntermediateDirectory)/platform_world_boulder_boulder.cpp$(PreprocessSuffix): platform/world/boulder/boulder.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_boulder_boulder.cpp$(PreprocessSuffix) platform/world/boulder/boulder.cpp

$(IntermediateDirectory)/platform_world_islands_islands.cpp$(ObjectSuffix): platform/world/islands/islands.cpp $(IntermediateDirectory)/platform_world_islands_islands.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/islands/islands.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_islands_islands.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_islands_islands.cpp$(DependSuffix): platform/world/islands/islands.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_islands_islands.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_islands_islands.cpp$(DependSuffix) -MM platform/world/islands/islands.cpp

$(IntermediateDirectory)/platform_world_islands_islands.cpp$(PreprocessSuffix): platform/world/islands/islands.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_islands_islands.cpp$(PreprocessSuffix) platform/world/islands/islands.cpp

$(IntermediateDirectory)/platform_world_islands_hover.cpp$(ObjectSuffix): platform/world/islands/hover.cpp $(IntermediateDirectory)/platform_world_islands_hover.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/islands/hover.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_islands_hover.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_islands_hover.cpp$(DependSuffix): platform/world/islands/hover.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_islands_hover.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_islands_hover.cpp$(DependSuffix) -MM platform/world/islands/hover.cpp

$(IntermediateDirectory)/platform_world_islands_hover.cpp$(PreprocessSuffix): platform/world/islands/hover.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_islands_hover.cpp$(PreprocessSuffix) platform/world/islands/hover.cpp

$(IntermediateDirectory)/platform_world_brick_rules.cpp$(ObjectSuffix): platform/world/brick/rules.cpp $(IntermediateDirectory)/platform_world_brick_rules.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/brick/rules.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_brick_rules.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_brick_rules.cpp$(DependSuffix): platform/world/brick/rules.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_brick_rules.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_brick_rules.cpp$(DependSuffix) -MM platform/world/brick/rules.cpp

$(IntermediateDirectory)/platform_world_brick_rules.cpp$(PreprocessSuffix): platform/world/brick/rules.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_brick_rules.cpp$(PreprocessSuffix) platform/world/brick/rules.cpp

$(IntermediateDirectory)/platform_world_brick_brick.cpp$(ObjectSuffix): platform/world/brick/brick.cpp $(IntermediateDirectory)/platform_world_brick_brick.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/brick/brick.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_brick_brick.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_brick_brick.cpp$(DependSuffix): platform/world/brick/brick.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_brick_brick.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_brick_brick.cpp$(DependSuffix) -MM platform/world/brick/brick.cpp

$(IntermediateDirectory)/platform_world_brick_brick.cpp$(PreprocessSuffix): platform/world/brick/brick.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_brick_brick.cpp$(PreprocessSuffix) platform/world/brick/brick.cpp

$(IntermediateDirectory)/platform_world_brick_block.cpp$(ObjectSuffix): platform/world/brick/block.cpp $(IntermediateDirectory)/platform_world_brick_block.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/brick/block.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_brick_block.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_brick_block.cpp$(DependSuffix): platform/world/brick/block.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_brick_block.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_brick_block.cpp$(DependSuffix) -MM platform/world/brick/block.cpp

$(IntermediateDirectory)/platform_world_brick_block.cpp$(PreprocessSuffix): platform/world/brick/block.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_brick_block.cpp$(PreprocessSuffix) platform/world/brick/block.cpp

$(IntermediateDirectory)/platform_world_score_dots_score_dots.cpp$(ObjectSuffix): platform/world/score_dots/score_dots.cpp $(IntermediateDirectory)/platform_world_score_dots_score_dots.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/score_dots/score_dots.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_score_dots_score_dots.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_score_dots_score_dots.cpp$(DependSuffix): platform/world/score_dots/score_dots.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_score_dots_score_dots.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_score_dots_score_dots.cpp$(DependSuffix) -MM platform/world/score_dots/score_dots.cpp

$(IntermediateDirectory)/platform_world_score_dots_score_dots.cpp$(PreprocessSuffix): platform/world/score_dots/score_dots.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_score_dots_score_dots.cpp$(PreprocessSuffix) platform/world/score_dots/score_dots.cpp

$(IntermediateDirectory)/platform_world_water_water.cpp$(ObjectSuffix): platform/world/water/water.cpp $(IntermediateDirectory)/platform_world_water_water.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/water/water.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_water_water.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_water_water.cpp$(DependSuffix): platform/world/water/water.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_water_water.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_water_water.cpp$(DependSuffix) -MM platform/world/water/water.cpp

$(IntermediateDirectory)/platform_world_water_water.cpp$(PreprocessSuffix): platform/world/water/water.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_water_water.cpp$(PreprocessSuffix) platform/world/water/water.cpp

$(IntermediateDirectory)/platform_world_spikes_spikes.cpp$(ObjectSuffix): platform/world/spikes/spikes.cpp $(IntermediateDirectory)/platform_world_spikes_spikes.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/spikes/spikes.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_spikes_spikes.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_spikes_spikes.cpp$(DependSuffix): platform/world/spikes/spikes.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_spikes_spikes.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_spikes_spikes.cpp$(DependSuffix) -MM platform/world/spikes/spikes.cpp

$(IntermediateDirectory)/platform_world_spikes_spikes.cpp$(PreprocessSuffix): platform/world/spikes/spikes.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_spikes_spikes.cpp$(PreprocessSuffix) platform/world/spikes/spikes.cpp

$(IntermediateDirectory)/platform_world_spikes_spike.cpp$(ObjectSuffix): platform/world/spikes/spike.cpp $(IntermediateDirectory)/platform_world_spikes_spike.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/spikes/spike.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_spikes_spike.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_spikes_spike.cpp$(DependSuffix): platform/world/spikes/spike.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_spikes_spike.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_spikes_spike.cpp$(DependSuffix) -MM platform/world/spikes/spike.cpp

$(IntermediateDirectory)/platform_world_spikes_spike.cpp$(PreprocessSuffix): platform/world/spikes/spike.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_spikes_spike.cpp$(PreprocessSuffix) platform/world/spikes/spike.cpp

$(IntermediateDirectory)/platform_world_saws_saws.cpp$(ObjectSuffix): platform/world/saws/saws.cpp $(IntermediateDirectory)/platform_world_saws_saws.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/saws/saws.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_saws_saws.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_saws_saws.cpp$(DependSuffix): platform/world/saws/saws.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_saws_saws.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_saws_saws.cpp$(DependSuffix) -MM platform/world/saws/saws.cpp

$(IntermediateDirectory)/platform_world_saws_saws.cpp$(PreprocessSuffix): platform/world/saws/saws.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_saws_saws.cpp$(PreprocessSuffix) platform/world/saws/saws.cpp

$(IntermediateDirectory)/platform_world_saws_saw.cpp$(ObjectSuffix): platform/world/saws/saw.cpp $(IntermediateDirectory)/platform_world_saws_saw.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/saws/saw.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_saws_saw.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_saws_saw.cpp$(DependSuffix): platform/world/saws/saw.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_saws_saw.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_saws_saw.cpp$(DependSuffix) -MM platform/world/saws/saw.cpp

$(IntermediateDirectory)/platform_world_saws_saw.cpp$(PreprocessSuffix): platform/world/saws/saw.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_saws_saw.cpp$(PreprocessSuffix) platform/world/saws/saw.cpp

$(IntermediateDirectory)/platform_world_exit_exit.cpp$(ObjectSuffix): platform/world/exit/exit.cpp $(IntermediateDirectory)/platform_world_exit_exit.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/exit/exit.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_exit_exit.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_exit_exit.cpp$(DependSuffix): platform/world/exit/exit.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_exit_exit.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_exit_exit.cpp$(DependSuffix) -MM platform/world/exit/exit.cpp

$(IntermediateDirectory)/platform_world_exit_exit.cpp$(PreprocessSuffix): platform/world/exit/exit.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_exit_exit.cpp$(PreprocessSuffix) platform/world/exit/exit.cpp

$(IntermediateDirectory)/platform_world_greenery_plant.cpp$(ObjectSuffix): platform/world/greenery/plant.cpp $(IntermediateDirectory)/platform_world_greenery_plant.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/greenery/plant.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_greenery_plant.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_greenery_plant.cpp$(DependSuffix): platform/world/greenery/plant.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_greenery_plant.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_greenery_plant.cpp$(DependSuffix) -MM platform/world/greenery/plant.cpp

$(IntermediateDirectory)/platform_world_greenery_plant.cpp$(PreprocessSuffix): platform/world/greenery/plant.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_greenery_plant.cpp$(PreprocessSuffix) platform/world/greenery/plant.cpp

$(IntermediateDirectory)/platform_world_greenery_greenery.cpp$(ObjectSuffix): platform/world/greenery/greenery.cpp $(IntermediateDirectory)/platform_world_greenery_greenery.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/greenery/greenery.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_greenery_greenery.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_greenery_greenery.cpp$(DependSuffix): platform/world/greenery/greenery.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_greenery_greenery.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_greenery_greenery.cpp$(DependSuffix) -MM platform/world/greenery/greenery.cpp

$(IntermediateDirectory)/platform_world_greenery_greenery.cpp$(PreprocessSuffix): platform/world/greenery/greenery.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_greenery_greenery.cpp$(PreprocessSuffix) platform/world/greenery/greenery.cpp

$(IntermediateDirectory)/platform_world_greenery_green.cpp$(ObjectSuffix): platform/world/greenery/green.cpp $(IntermediateDirectory)/platform_world_greenery_green.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/greenery/green.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_greenery_green.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_greenery_green.cpp$(DependSuffix): platform/world/greenery/green.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_greenery_green.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_greenery_green.cpp$(DependSuffix) -MM platform/world/greenery/green.cpp

$(IntermediateDirectory)/platform_world_greenery_green.cpp$(PreprocessSuffix): platform/world/greenery/green.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_greenery_green.cpp$(PreprocessSuffix) platform/world/greenery/green.cpp

$(IntermediateDirectory)/platform_world_ladder_ladder.cpp$(ObjectSuffix): platform/world/ladder/ladder.cpp $(IntermediateDirectory)/platform_world_ladder_ladder.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/ladder/ladder.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_ladder_ladder.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_ladder_ladder.cpp$(DependSuffix): platform/world/ladder/ladder.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_ladder_ladder.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_ladder_ladder.cpp$(DependSuffix) -MM platform/world/ladder/ladder.cpp

$(IntermediateDirectory)/platform_world_ladder_ladder.cpp$(PreprocessSuffix): platform/world/ladder/ladder.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_ladder_ladder.cpp$(PreprocessSuffix) platform/world/ladder/ladder.cpp

$(IntermediateDirectory)/platform_enemy_actions_coins_coins.cpp$(ObjectSuffix): platform/enemy/actions/coins/coins.cpp $(IntermediateDirectory)/platform_enemy_actions_coins_coins.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/actions/coins/coins.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_actions_coins_coins.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_actions_coins_coins.cpp$(DependSuffix): platform/enemy/actions/coins/coins.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_actions_coins_coins.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_actions_coins_coins.cpp$(DependSuffix) -MM platform/enemy/actions/coins/coins.cpp

$(IntermediateDirectory)/platform_enemy_actions_coins_coins.cpp$(PreprocessSuffix): platform/enemy/actions/coins/coins.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_actions_coins_coins.cpp$(PreprocessSuffix) platform/enemy/actions/coins/coins.cpp

$(IntermediateDirectory)/platform_enemy_actions_coins_coin.cpp$(ObjectSuffix): platform/enemy/actions/coins/coin.cpp $(IntermediateDirectory)/platform_enemy_actions_coins_coin.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/actions/coins/coin.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_actions_coins_coin.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_actions_coins_coin.cpp$(DependSuffix): platform/enemy/actions/coins/coin.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_actions_coins_coin.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_actions_coins_coin.cpp$(DependSuffix) -MM platform/enemy/actions/coins/coin.cpp

$(IntermediateDirectory)/platform_enemy_actions_coins_coin.cpp$(PreprocessSuffix): platform/enemy/actions/coins/coin.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_actions_coins_coin.cpp$(PreprocessSuffix) platform/enemy/actions/coins/coin.cpp

$(IntermediateDirectory)/platform_enemy_actions_effect_effect.cpp$(ObjectSuffix): platform/enemy/actions/effect/effect.cpp $(IntermediateDirectory)/platform_enemy_actions_effect_effect.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/actions/effect/effect.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_actions_effect_effect.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_actions_effect_effect.cpp$(DependSuffix): platform/enemy/actions/effect/effect.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_actions_effect_effect.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_actions_effect_effect.cpp$(DependSuffix) -MM platform/enemy/actions/effect/effect.cpp

$(IntermediateDirectory)/platform_enemy_actions_effect_effect.cpp$(PreprocessSuffix): platform/enemy/actions/effect/effect.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_actions_effect_effect.cpp$(PreprocessSuffix) platform/enemy/actions/effect/effect.cpp

$(IntermediateDirectory)/platform_enemy_actions_expletive_slab.cpp$(ObjectSuffix): platform/enemy/actions/expletive/slab.cpp $(IntermediateDirectory)/platform_enemy_actions_expletive_slab.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/actions/expletive/slab.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_actions_expletive_slab.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_actions_expletive_slab.cpp$(DependSuffix): platform/enemy/actions/expletive/slab.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_actions_expletive_slab.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_actions_expletive_slab.cpp$(DependSuffix) -MM platform/enemy/actions/expletive/slab.cpp

$(IntermediateDirectory)/platform_enemy_actions_expletive_slab.cpp$(PreprocessSuffix): platform/enemy/actions/expletive/slab.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_actions_expletive_slab.cpp$(PreprocessSuffix) platform/enemy/actions/expletive/slab.cpp

$(IntermediateDirectory)/platform_enemy_actions_expletive_expletive.cpp$(ObjectSuffix): platform/enemy/actions/expletive/expletive.cpp $(IntermediateDirectory)/platform_enemy_actions_expletive_expletive.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/actions/expletive/expletive.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_actions_expletive_expletive.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_actions_expletive_expletive.cpp$(DependSuffix): platform/enemy/actions/expletive/expletive.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_actions_expletive_expletive.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_actions_expletive_expletive.cpp$(DependSuffix) -MM platform/enemy/actions/expletive/expletive.cpp

$(IntermediateDirectory)/platform_enemy_actions_expletive_expletive.cpp$(PreprocessSuffix): platform/enemy/actions/expletive/expletive.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_actions_expletive_expletive.cpp$(PreprocessSuffix) platform/enemy/actions/expletive/expletive.cpp

$(IntermediateDirectory)/platform_enemy_actions_hp_dots_hp_dots.cpp$(ObjectSuffix): platform/enemy/actions/hp_dots/hp_dots.cpp $(IntermediateDirectory)/platform_enemy_actions_hp_dots_hp_dots.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/actions/hp_dots/hp_dots.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_actions_hp_dots_hp_dots.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_actions_hp_dots_hp_dots.cpp$(DependSuffix): platform/enemy/actions/hp_dots/hp_dots.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_actions_hp_dots_hp_dots.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_actions_hp_dots_hp_dots.cpp$(DependSuffix) -MM platform/enemy/actions/hp_dots/hp_dots.cpp

$(IntermediateDirectory)/platform_enemy_actions_hp_dots_hp_dots.cpp$(PreprocessSuffix): platform/enemy/actions/hp_dots/hp_dots.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_actions_hp_dots_hp_dots.cpp$(PreprocessSuffix) platform/enemy/actions/hp_dots/hp_dots.cpp

$(IntermediateDirectory)/platform_enemy_actions_hp_dots_hp_dot.cpp$(ObjectSuffix): platform/enemy/actions/hp_dots/hp_dot.cpp $(IntermediateDirectory)/platform_enemy_actions_hp_dots_hp_dot.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/actions/hp_dots/hp_dot.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_actions_hp_dots_hp_dot.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_actions_hp_dots_hp_dot.cpp$(DependSuffix): platform/enemy/actions/hp_dots/hp_dot.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_actions_hp_dots_hp_dot.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_actions_hp_dots_hp_dot.cpp$(DependSuffix) -MM platform/enemy/actions/hp_dots/hp_dot.cpp

$(IntermediateDirectory)/platform_enemy_actions_hp_dots_hp_dot.cpp$(PreprocessSuffix): platform/enemy/actions/hp_dots/hp_dot.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_actions_hp_dots_hp_dot.cpp$(PreprocessSuffix) platform/enemy/actions/hp_dots/hp_dot.cpp

$(IntermediateDirectory)/platform_enemy_actions_show_showheal.cpp$(ObjectSuffix): platform/enemy/actions/show/showheal.cpp $(IntermediateDirectory)/platform_enemy_actions_show_showheal.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/actions/show/showheal.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_actions_show_showheal.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_actions_show_showheal.cpp$(DependSuffix): platform/enemy/actions/show/showheal.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_actions_show_showheal.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_actions_show_showheal.cpp$(DependSuffix) -MM platform/enemy/actions/show/showheal.cpp

$(IntermediateDirectory)/platform_enemy_actions_show_showheal.cpp$(PreprocessSuffix): platform/enemy/actions/show/showheal.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_actions_show_showheal.cpp$(PreprocessSuffix) platform/enemy/actions/show/showheal.cpp

$(IntermediateDirectory)/platform_enemy_actions_show_showdamage.cpp$(ObjectSuffix): platform/enemy/actions/show/showdamage.cpp $(IntermediateDirectory)/platform_enemy_actions_show_showdamage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/actions/show/showdamage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_actions_show_showdamage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_actions_show_showdamage.cpp$(DependSuffix): platform/enemy/actions/show/showdamage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_actions_show_showdamage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_actions_show_showdamage.cpp$(DependSuffix) -MM platform/enemy/actions/show/showdamage.cpp

$(IntermediateDirectory)/platform_enemy_actions_show_showdamage.cpp$(PreprocessSuffix): platform/enemy/actions/show/showdamage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_actions_show_showdamage.cpp$(PreprocessSuffix) platform/enemy/actions/show/showdamage.cpp

$(IntermediateDirectory)/platform_enemy_foes_factory_factory.cpp$(ObjectSuffix): platform/enemy/foes/factory/factory.cpp $(IntermediateDirectory)/platform_enemy_foes_factory_factory.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/foes/factory/factory.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_foes_factory_factory.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_foes_factory_factory.cpp$(DependSuffix): platform/enemy/foes/factory/factory.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_foes_factory_factory.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_foes_factory_factory.cpp$(DependSuffix) -MM platform/enemy/foes/factory/factory.cpp

$(IntermediateDirectory)/platform_enemy_foes_factory_factory.cpp$(PreprocessSuffix): platform/enemy/foes/factory/factory.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_foes_factory_factory.cpp$(PreprocessSuffix) platform/enemy/foes/factory/factory.cpp

$(IntermediateDirectory)/platform_enemy_foes_flying_fly_factory.cpp$(ObjectSuffix): platform/enemy/foes/flying/fly_factory.cpp $(IntermediateDirectory)/platform_enemy_foes_flying_fly_factory.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/foes/flying/fly_factory.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_foes_flying_fly_factory.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_foes_flying_fly_factory.cpp$(DependSuffix): platform/enemy/foes/flying/fly_factory.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_foes_flying_fly_factory.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_foes_flying_fly_factory.cpp$(DependSuffix) -MM platform/enemy/foes/flying/fly_factory.cpp

$(IntermediateDirectory)/platform_enemy_foes_flying_fly_factory.cpp$(PreprocessSuffix): platform/enemy/foes/flying/fly_factory.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_foes_flying_fly_factory.cpp$(PreprocessSuffix) platform/enemy/foes/flying/fly_factory.cpp

$(IntermediateDirectory)/platform_enemy_foes_flying_fly.cpp$(ObjectSuffix): platform/enemy/foes/flying/fly.cpp $(IntermediateDirectory)/platform_enemy_foes_flying_fly.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/foes/flying/fly.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_foes_flying_fly.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_foes_flying_fly.cpp$(DependSuffix): platform/enemy/foes/flying/fly.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_foes_flying_fly.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_foes_flying_fly.cpp$(DependSuffix) -MM platform/enemy/foes/flying/fly.cpp

$(IntermediateDirectory)/platform_enemy_foes_flying_fly.cpp$(PreprocessSuffix): platform/enemy/foes/flying/fly.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_foes_flying_fly.cpp$(PreprocessSuffix) platform/enemy/foes/flying/fly.cpp

$(IntermediateDirectory)/platform_enemy_foes_golem_golem.cpp$(ObjectSuffix): platform/enemy/foes/golem/golem.cpp $(IntermediateDirectory)/platform_enemy_foes_golem_golem.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/foes/golem/golem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_foes_golem_golem.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_foes_golem_golem.cpp$(DependSuffix): platform/enemy/foes/golem/golem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_foes_golem_golem.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_foes_golem_golem.cpp$(DependSuffix) -MM platform/enemy/foes/golem/golem.cpp

$(IntermediateDirectory)/platform_enemy_foes_golem_golem.cpp$(PreprocessSuffix): platform/enemy/foes/golem/golem.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_foes_golem_golem.cpp$(PreprocessSuffix) platform/enemy/foes/golem/golem.cpp

$(IntermediateDirectory)/platform_enemy_foes_zombie_zombie.cpp$(ObjectSuffix): platform/enemy/foes/zombie/zombie.cpp $(IntermediateDirectory)/platform_enemy_foes_zombie_zombie.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/foes/zombie/zombie.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_foes_zombie_zombie.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_foes_zombie_zombie.cpp$(DependSuffix): platform/enemy/foes/zombie/zombie.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_foes_zombie_zombie.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_foes_zombie_zombie.cpp$(DependSuffix) -MM platform/enemy/foes/zombie/zombie.cpp

$(IntermediateDirectory)/platform_enemy_foes_zombie_zombie.cpp$(PreprocessSuffix): platform/enemy/foes/zombie/zombie.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_foes_zombie_zombie.cpp$(PreprocessSuffix) platform/enemy/foes/zombie/zombie.cpp

$(IntermediateDirectory)/platform_enemy_foes_robot_robot.cpp$(ObjectSuffix): platform/enemy/foes/robot/robot.cpp $(IntermediateDirectory)/platform_enemy_foes_robot_robot.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/foes/robot/robot.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_foes_robot_robot.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_foes_robot_robot.cpp$(DependSuffix): platform/enemy/foes/robot/robot.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_foes_robot_robot.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_foes_robot_robot.cpp$(DependSuffix) -MM platform/enemy/foes/robot/robot.cpp

$(IntermediateDirectory)/platform_enemy_foes_robot_robot.cpp$(PreprocessSuffix): platform/enemy/foes/robot/robot.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_foes_robot_robot.cpp$(PreprocessSuffix) platform/enemy/foes/robot/robot.cpp

$(IntermediateDirectory)/platform_enemy_foes_vampire_vampire.cpp$(ObjectSuffix): platform/enemy/foes/vampire/vampire.cpp $(IntermediateDirectory)/platform_enemy_foes_vampire_vampire.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/foes/vampire/vampire.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_foes_vampire_vampire.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_foes_vampire_vampire.cpp$(DependSuffix): platform/enemy/foes/vampire/vampire.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_foes_vampire_vampire.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_foes_vampire_vampire.cpp$(DependSuffix) -MM platform/enemy/foes/vampire/vampire.cpp

$(IntermediateDirectory)/platform_enemy_foes_vampire_vampire.cpp$(PreprocessSuffix): platform/enemy/foes/vampire/vampire.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_foes_vampire_vampire.cpp$(PreprocessSuffix) platform/enemy/foes/vampire/vampire.cpp

$(IntermediateDirectory)/platform_enemy_foes_skeleton_skeleton.cpp$(ObjectSuffix): platform/enemy/foes/skeleton/skeleton.cpp $(IntermediateDirectory)/platform_enemy_foes_skeleton_skeleton.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/foes/skeleton/skeleton.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_foes_skeleton_skeleton.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_foes_skeleton_skeleton.cpp$(DependSuffix): platform/enemy/foes/skeleton/skeleton.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_foes_skeleton_skeleton.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_foes_skeleton_skeleton.cpp$(DependSuffix) -MM platform/enemy/foes/skeleton/skeleton.cpp

$(IntermediateDirectory)/platform_enemy_foes_skeleton_skeleton.cpp$(PreprocessSuffix): platform/enemy/foes/skeleton/skeleton.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_foes_skeleton_skeleton.cpp$(PreprocessSuffix) platform/enemy/foes/skeleton/skeleton.cpp

$(IntermediateDirectory)/platform_enemy_foes_snakes_snakes_factory.cpp$(ObjectSuffix): platform/enemy/foes/snakes/snakes_factory.cpp $(IntermediateDirectory)/platform_enemy_foes_snakes_snakes_factory.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/foes/snakes/snakes_factory.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_foes_snakes_snakes_factory.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_foes_snakes_snakes_factory.cpp$(DependSuffix): platform/enemy/foes/snakes/snakes_factory.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_foes_snakes_snakes_factory.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_foes_snakes_snakes_factory.cpp$(DependSuffix) -MM platform/enemy/foes/snakes/snakes_factory.cpp

$(IntermediateDirectory)/platform_enemy_foes_snakes_snakes_factory.cpp$(PreprocessSuffix): platform/enemy/foes/snakes/snakes_factory.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_foes_snakes_snakes_factory.cpp$(PreprocessSuffix) platform/enemy/foes/snakes/snakes_factory.cpp

$(IntermediateDirectory)/platform_enemy_foes_snakes_snakes.cpp$(ObjectSuffix): platform/enemy/foes/snakes/snakes.cpp $(IntermediateDirectory)/platform_enemy_foes_snakes_snakes.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/foes/snakes/snakes.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_foes_snakes_snakes.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_foes_snakes_snakes.cpp$(DependSuffix): platform/enemy/foes/snakes/snakes.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_foes_snakes_snakes.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_foes_snakes_snakes.cpp$(DependSuffix) -MM platform/enemy/foes/snakes/snakes.cpp

$(IntermediateDirectory)/platform_enemy_foes_snakes_snakes.cpp$(PreprocessSuffix): platform/enemy/foes/snakes/snakes.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_foes_snakes_snakes.cpp$(PreprocessSuffix) platform/enemy/foes/snakes/snakes.cpp

$(IntermediateDirectory)/platform_enemy_foes_mines_mine_factory.cpp$(ObjectSuffix): platform/enemy/foes/mines/mine_factory.cpp $(IntermediateDirectory)/platform_enemy_foes_mines_mine_factory.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/foes/mines/mine_factory.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_foes_mines_mine_factory.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_foes_mines_mine_factory.cpp$(DependSuffix): platform/enemy/foes/mines/mine_factory.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_foes_mines_mine_factory.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_foes_mines_mine_factory.cpp$(DependSuffix) -MM platform/enemy/foes/mines/mine_factory.cpp

$(IntermediateDirectory)/platform_enemy_foes_mines_mine_factory.cpp$(PreprocessSuffix): platform/enemy/foes/mines/mine_factory.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_foes_mines_mine_factory.cpp$(PreprocessSuffix) platform/enemy/foes/mines/mine_factory.cpp

$(IntermediateDirectory)/platform_enemy_foes_mines_mine.cpp$(ObjectSuffix): platform/enemy/foes/mines/mine.cpp $(IntermediateDirectory)/platform_enemy_foes_mines_mine.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/foes/mines/mine.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_foes_mines_mine.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_foes_mines_mine.cpp$(DependSuffix): platform/enemy/foes/mines/mine.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_foes_mines_mine.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_foes_mines_mine.cpp$(DependSuffix) -MM platform/enemy/foes/mines/mine.cpp

$(IntermediateDirectory)/platform_enemy_foes_mines_mine.cpp$(PreprocessSuffix): platform/enemy/foes/mines/mine.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_foes_mines_mine.cpp$(PreprocessSuffix) platform/enemy/foes/mines/mine.cpp

$(IntermediateDirectory)/platform_world_weather_rain_rain.cpp$(ObjectSuffix): platform/world/weather/rain/rain.cpp $(IntermediateDirectory)/platform_world_weather_rain_rain.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/weather/rain/rain.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_weather_rain_rain.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_weather_rain_rain.cpp$(DependSuffix): platform/world/weather/rain/rain.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_weather_rain_rain.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_weather_rain_rain.cpp$(DependSuffix) -MM platform/world/weather/rain/rain.cpp

$(IntermediateDirectory)/platform_world_weather_rain_rain.cpp$(PreprocessSuffix): platform/world/weather/rain/rain.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_weather_rain_rain.cpp$(PreprocessSuffix) platform/world/weather/rain/rain.cpp

$(IntermediateDirectory)/platform_world_weather_sun_sun.cpp$(ObjectSuffix): platform/world/weather/sun/sun.cpp $(IntermediateDirectory)/platform_world_weather_sun_sun.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/weather/sun/sun.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_weather_sun_sun.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_weather_sun_sun.cpp$(DependSuffix): platform/world/weather/sun/sun.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_weather_sun_sun.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_weather_sun_sun.cpp$(DependSuffix) -MM platform/world/weather/sun/sun.cpp

$(IntermediateDirectory)/platform_world_weather_sun_sun.cpp$(PreprocessSuffix): platform/world/weather/sun/sun.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_weather_sun_sun.cpp$(PreprocessSuffix) platform/world/weather/sun/sun.cpp

$(IntermediateDirectory)/platform_world_weather_snow_snow.cpp$(ObjectSuffix): platform/world/weather/snow/snow.cpp $(IntermediateDirectory)/platform_world_weather_snow_snow.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/weather/snow/snow.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_weather_snow_snow.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_weather_snow_snow.cpp$(DependSuffix): platform/world/weather/snow/snow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_weather_snow_snow.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_weather_snow_snow.cpp$(DependSuffix) -MM platform/world/weather/snow/snow.cpp

$(IntermediateDirectory)/platform_world_weather_snow_snow.cpp$(PreprocessSuffix): platform/world/weather/snow/snow.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_weather_snow_snow.cpp$(PreprocessSuffix) platform/world/weather/snow/snow.cpp

$(IntermediateDirectory)/platform_world_weather_wind_wind.cpp$(ObjectSuffix): platform/world/weather/wind/wind.cpp $(IntermediateDirectory)/platform_world_weather_wind_wind.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/world/weather/wind/wind.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_world_weather_wind_wind.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_world_weather_wind_wind.cpp$(DependSuffix): platform/world/weather/wind/wind.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_world_weather_wind_wind.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_world_weather_wind_wind.cpp$(DependSuffix) -MM platform/world/weather/wind/wind.cpp

$(IntermediateDirectory)/platform_world_weather_wind_wind.cpp$(PreprocessSuffix): platform/world/weather/wind/wind.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_world_weather_wind_wind.cpp$(PreprocessSuffix) platform/world/weather/wind/wind.cpp

$(IntermediateDirectory)/platform_enemy_foes_checkActivity_cruncher_cruncher.cpp$(ObjectSuffix): platform/enemy/foes/checkActivity/cruncher/cruncher.cpp $(IntermediateDirectory)/platform_enemy_foes_checkActivity_cruncher_cruncher.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/foes/checkActivity/cruncher/cruncher.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_foes_checkActivity_cruncher_cruncher.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_foes_checkActivity_cruncher_cruncher.cpp$(DependSuffix): platform/enemy/foes/checkActivity/cruncher/cruncher.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_foes_checkActivity_cruncher_cruncher.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_foes_checkActivity_cruncher_cruncher.cpp$(DependSuffix) -MM platform/enemy/foes/checkActivity/cruncher/cruncher.cpp

$(IntermediateDirectory)/platform_enemy_foes_checkActivity_cruncher_cruncher.cpp$(PreprocessSuffix): platform/enemy/foes/checkActivity/cruncher/cruncher.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_foes_checkActivity_cruncher_cruncher.cpp$(PreprocessSuffix) platform/enemy/foes/checkActivity/cruncher/cruncher.cpp

$(IntermediateDirectory)/platform_enemy_foes_checkActivity_fireball_fireball.cpp$(ObjectSuffix): platform/enemy/foes/checkActivity/fireball/fireball.cpp $(IntermediateDirectory)/platform_enemy_foes_checkActivity_fireball_fireball.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/foes/checkActivity/fireball/fireball.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_foes_checkActivity_fireball_fireball.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_foes_checkActivity_fireball_fireball.cpp$(DependSuffix): platform/enemy/foes/checkActivity/fireball/fireball.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_foes_checkActivity_fireball_fireball.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_foes_checkActivity_fireball_fireball.cpp$(DependSuffix) -MM platform/enemy/foes/checkActivity/fireball/fireball.cpp

$(IntermediateDirectory)/platform_enemy_foes_checkActivity_fireball_fireball.cpp$(PreprocessSuffix): platform/enemy/foes/checkActivity/fireball/fireball.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_foes_checkActivity_fireball_fireball.cpp$(PreprocessSuffix) platform/enemy/foes/checkActivity/fireball/fireball.cpp

$(IntermediateDirectory)/platform_enemy_foes_checkActivity_lightning_lightning.cpp$(ObjectSuffix): platform/enemy/foes/checkActivity/lightning/lightning.cpp $(IntermediateDirectory)/platform_enemy_foes_checkActivity_lightning_lightning.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/platform/enemy/foes/checkActivity/lightning/lightning.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/platform_enemy_foes_checkActivity_lightning_lightning.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/platform_enemy_foes_checkActivity_lightning_lightning.cpp$(DependSuffix): platform/enemy/foes/checkActivity/lightning/lightning.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/platform_enemy_foes_checkActivity_lightning_lightning.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/platform_enemy_foes_checkActivity_lightning_lightning.cpp$(DependSuffix) -MM platform/enemy/foes/checkActivity/lightning/lightning.cpp

$(IntermediateDirectory)/platform_enemy_foes_checkActivity_lightning_lightning.cpp$(PreprocessSuffix): platform/enemy/foes/checkActivity/lightning/lightning.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/platform_enemy_foes_checkActivity_lightning_lightning.cpp$(PreprocessSuffix) platform/enemy/foes/checkActivity/lightning/lightning.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/



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
Date                   :=13/09/16
CodeLitePath           :=/home/adr/.codelite
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
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
LinkOptions            :=  -lSDL2 -lSDL2_mixer -lsfml-window -lsfml-system -lsfml-graphics
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -std=c++11 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/color.c$(ObjectSuffix) $(IntermediateDirectory)/core.cpp$(ObjectSuffix) $(IntermediateDirectory)/engine.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_music_volume.cpp$(ObjectSuffix) $(IntermediateDirectory)/start_intro.cpp$(ObjectSuffix) $(IntermediateDirectory)/start_loading.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_link_button.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_menu_exit_log.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_menu_log.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/menu_menu_music_button.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_menu_play_button.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_menu_title.cpp$(ObjectSuffix) $(IntermediateDirectory)/templates_chunk.cpp$(ObjectSuffix) $(IntermediateDirectory)/templates_music.cpp$(ObjectSuffix) $(IntermediateDirectory)/templates_sprite.cpp$(ObjectSuffix) $(IntermediateDirectory)/templates_text.cpp$(ObjectSuffix) $(IntermediateDirectory)/play_game_timer.cpp$(ObjectSuffix) $(IntermediateDirectory)/play_play_bg.cpp$(ObjectSuffix) $(IntermediateDirectory)/play_play_exit_log.cpp$(ObjectSuffix) \
	



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix)main.cpp

$(IntermediateDirectory)/color.c$(ObjectSuffix): color.c $(IntermediateDirectory)/color.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/color.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/color.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/color.c$(DependSuffix): color.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/color.c$(ObjectSuffix) -MF$(IntermediateDirectory)/color.c$(DependSuffix) -MM color.c

$(IntermediateDirectory)/color.c$(PreprocessSuffix): color.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/color.c$(PreprocessSuffix)color.c

$(IntermediateDirectory)/core.cpp$(ObjectSuffix): core.cpp $(IntermediateDirectory)/core.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/core.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/core.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/core.cpp$(DependSuffix): core.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/core.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/core.cpp$(DependSuffix) -MM core.cpp

$(IntermediateDirectory)/core.cpp$(PreprocessSuffix): core.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/core.cpp$(PreprocessSuffix)core.cpp

$(IntermediateDirectory)/engine.cpp$(ObjectSuffix): engine.cpp $(IntermediateDirectory)/engine.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/engine.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/engine.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/engine.cpp$(DependSuffix): engine.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/engine.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/engine.cpp$(DependSuffix) -MM engine.cpp

$(IntermediateDirectory)/engine.cpp$(PreprocessSuffix): engine.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/engine.cpp$(PreprocessSuffix)engine.cpp

$(IntermediateDirectory)/menu_music_volume.cpp$(ObjectSuffix): menu/music_volume.cpp $(IntermediateDirectory)/menu_music_volume.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/music_volume.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_music_volume.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_music_volume.cpp$(DependSuffix): menu/music_volume.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_music_volume.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_music_volume.cpp$(DependSuffix) -MM menu/music_volume.cpp

$(IntermediateDirectory)/menu_music_volume.cpp$(PreprocessSuffix): menu/music_volume.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_music_volume.cpp$(PreprocessSuffix)menu/music_volume.cpp

$(IntermediateDirectory)/start_intro.cpp$(ObjectSuffix): start/intro.cpp $(IntermediateDirectory)/start_intro.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/start/intro.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/start_intro.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/start_intro.cpp$(DependSuffix): start/intro.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/start_intro.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/start_intro.cpp$(DependSuffix) -MM start/intro.cpp

$(IntermediateDirectory)/start_intro.cpp$(PreprocessSuffix): start/intro.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/start_intro.cpp$(PreprocessSuffix)start/intro.cpp

$(IntermediateDirectory)/start_loading.cpp$(ObjectSuffix): start/loading.cpp $(IntermediateDirectory)/start_loading.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/start/loading.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/start_loading.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/start_loading.cpp$(DependSuffix): start/loading.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/start_loading.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/start_loading.cpp$(DependSuffix) -MM start/loading.cpp

$(IntermediateDirectory)/start_loading.cpp$(PreprocessSuffix): start/loading.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/start_loading.cpp$(PreprocessSuffix)start/loading.cpp

$(IntermediateDirectory)/menu_link_button.cpp$(ObjectSuffix): menu/link_button.cpp $(IntermediateDirectory)/menu_link_button.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/link_button.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_link_button.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_link_button.cpp$(DependSuffix): menu/link_button.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_link_button.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_link_button.cpp$(DependSuffix) -MM menu/link_button.cpp

$(IntermediateDirectory)/menu_link_button.cpp$(PreprocessSuffix): menu/link_button.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_link_button.cpp$(PreprocessSuffix)menu/link_button.cpp

$(IntermediateDirectory)/menu_menu_exit_log.cpp$(ObjectSuffix): menu/menu_exit_log.cpp $(IntermediateDirectory)/menu_menu_exit_log.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/menu_exit_log.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_menu_exit_log.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_menu_exit_log.cpp$(DependSuffix): menu/menu_exit_log.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_menu_exit_log.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_menu_exit_log.cpp$(DependSuffix) -MM menu/menu_exit_log.cpp

$(IntermediateDirectory)/menu_menu_exit_log.cpp$(PreprocessSuffix): menu/menu_exit_log.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_menu_exit_log.cpp$(PreprocessSuffix)menu/menu_exit_log.cpp

$(IntermediateDirectory)/menu_menu_log.cpp$(ObjectSuffix): menu/menu_log.cpp $(IntermediateDirectory)/menu_menu_log.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/menu_log.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_menu_log.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_menu_log.cpp$(DependSuffix): menu/menu_log.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_menu_log.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_menu_log.cpp$(DependSuffix) -MM menu/menu_log.cpp

$(IntermediateDirectory)/menu_menu_log.cpp$(PreprocessSuffix): menu/menu_log.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_menu_log.cpp$(PreprocessSuffix)menu/menu_log.cpp

$(IntermediateDirectory)/menu_menu_music_button.cpp$(ObjectSuffix): menu/menu_music_button.cpp $(IntermediateDirectory)/menu_menu_music_button.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/menu_music_button.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_menu_music_button.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_menu_music_button.cpp$(DependSuffix): menu/menu_music_button.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_menu_music_button.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_menu_music_button.cpp$(DependSuffix) -MM menu/menu_music_button.cpp

$(IntermediateDirectory)/menu_menu_music_button.cpp$(PreprocessSuffix): menu/menu_music_button.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_menu_music_button.cpp$(PreprocessSuffix)menu/menu_music_button.cpp

$(IntermediateDirectory)/menu_menu_play_button.cpp$(ObjectSuffix): menu/menu_play_button.cpp $(IntermediateDirectory)/menu_menu_play_button.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/menu_play_button.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_menu_play_button.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_menu_play_button.cpp$(DependSuffix): menu/menu_play_button.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_menu_play_button.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_menu_play_button.cpp$(DependSuffix) -MM menu/menu_play_button.cpp

$(IntermediateDirectory)/menu_menu_play_button.cpp$(PreprocessSuffix): menu/menu_play_button.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_menu_play_button.cpp$(PreprocessSuffix)menu/menu_play_button.cpp

$(IntermediateDirectory)/menu_menu_title.cpp$(ObjectSuffix): menu/menu_title.cpp $(IntermediateDirectory)/menu_menu_title.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/menu/menu_title.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_menu_title.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_menu_title.cpp$(DependSuffix): menu/menu_title.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_menu_title.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_menu_title.cpp$(DependSuffix) -MM menu/menu_title.cpp

$(IntermediateDirectory)/menu_menu_title.cpp$(PreprocessSuffix): menu/menu_title.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_menu_title.cpp$(PreprocessSuffix)menu/menu_title.cpp

$(IntermediateDirectory)/templates_chunk.cpp$(ObjectSuffix): templates/chunk.cpp $(IntermediateDirectory)/templates_chunk.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/templates/chunk.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/templates_chunk.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/templates_chunk.cpp$(DependSuffix): templates/chunk.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/templates_chunk.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/templates_chunk.cpp$(DependSuffix) -MM templates/chunk.cpp

$(IntermediateDirectory)/templates_chunk.cpp$(PreprocessSuffix): templates/chunk.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/templates_chunk.cpp$(PreprocessSuffix)templates/chunk.cpp

$(IntermediateDirectory)/templates_music.cpp$(ObjectSuffix): templates/music.cpp $(IntermediateDirectory)/templates_music.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/templates/music.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/templates_music.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/templates_music.cpp$(DependSuffix): templates/music.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/templates_music.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/templates_music.cpp$(DependSuffix) -MM templates/music.cpp

$(IntermediateDirectory)/templates_music.cpp$(PreprocessSuffix): templates/music.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/templates_music.cpp$(PreprocessSuffix)templates/music.cpp

$(IntermediateDirectory)/templates_sprite.cpp$(ObjectSuffix): templates/sprite.cpp $(IntermediateDirectory)/templates_sprite.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/templates/sprite.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/templates_sprite.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/templates_sprite.cpp$(DependSuffix): templates/sprite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/templates_sprite.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/templates_sprite.cpp$(DependSuffix) -MM templates/sprite.cpp

$(IntermediateDirectory)/templates_sprite.cpp$(PreprocessSuffix): templates/sprite.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/templates_sprite.cpp$(PreprocessSuffix)templates/sprite.cpp

$(IntermediateDirectory)/templates_text.cpp$(ObjectSuffix): templates/text.cpp $(IntermediateDirectory)/templates_text.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/templates/text.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/templates_text.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/templates_text.cpp$(DependSuffix): templates/text.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/templates_text.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/templates_text.cpp$(DependSuffix) -MM templates/text.cpp

$(IntermediateDirectory)/templates_text.cpp$(PreprocessSuffix): templates/text.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/templates_text.cpp$(PreprocessSuffix)templates/text.cpp

$(IntermediateDirectory)/play_game_timer.cpp$(ObjectSuffix): play/game_timer.cpp $(IntermediateDirectory)/play_game_timer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/play/game_timer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/play_game_timer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/play_game_timer.cpp$(DependSuffix): play/game_timer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/play_game_timer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/play_game_timer.cpp$(DependSuffix) -MM play/game_timer.cpp

$(IntermediateDirectory)/play_game_timer.cpp$(PreprocessSuffix): play/game_timer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/play_game_timer.cpp$(PreprocessSuffix)play/game_timer.cpp

$(IntermediateDirectory)/play_play_bg.cpp$(ObjectSuffix): play/play_bg.cpp $(IntermediateDirectory)/play_play_bg.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/play/play_bg.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/play_play_bg.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/play_play_bg.cpp$(DependSuffix): play/play_bg.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/play_play_bg.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/play_play_bg.cpp$(DependSuffix) -MM play/play_bg.cpp

$(IntermediateDirectory)/play_play_bg.cpp$(PreprocessSuffix): play/play_bg.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/play_play_bg.cpp$(PreprocessSuffix)play/play_bg.cpp

$(IntermediateDirectory)/play_play_exit_log.cpp$(ObjectSuffix): play/play_exit_log.cpp $(IntermediateDirectory)/play_play_exit_log.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adr/Dokumenty/C++ workspace/Ninja/play/play_exit_log.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/play_play_exit_log.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/play_play_exit_log.cpp$(DependSuffix): play/play_exit_log.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/play_play_exit_log.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/play_play_exit_log.cpp$(DependSuffix) -MM play/play_exit_log.cpp

$(IntermediateDirectory)/play_play_exit_log.cpp$(PreprocessSuffix): play/play_exit_log.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/play_play_exit_log.cpp$(PreprocessSuffix)play/play_exit_log.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/



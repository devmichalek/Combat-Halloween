##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Ninja
ConfigurationName      :=Debug
WorkspacePath          := "/home/adrian/.codelite/Workspace_one"
ProjectPath            := "/home/adrian/.codelite/Workspace_one/Ninja"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Adrian Michalek
Date                   :=03/09/16
CodeLitePath           :="/home/adrian/.codelite"
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
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/sprite.cpp$(ObjectSuffix) $(IntermediateDirectory)/engine.cpp$(ObjectSuffix) $(IntermediateDirectory)/core.cpp$(ObjectSuffix) $(IntermediateDirectory)/link_button.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_play_button.cpp$(ObjectSuffix) $(IntermediateDirectory)/text.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_title.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_music_button.cpp$(ObjectSuffix) $(IntermediateDirectory)/music.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/chunk.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_log.cpp$(ObjectSuffix) $(IntermediateDirectory)/menu_exit_log.cpp$(ObjectSuffix) $(IntermediateDirectory)/loading.cpp$(ObjectSuffix) 



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
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Ninja/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/sprite.cpp$(ObjectSuffix): sprite.cpp $(IntermediateDirectory)/sprite.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Ninja/sprite.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/sprite.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sprite.cpp$(DependSuffix): sprite.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/sprite.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/sprite.cpp$(DependSuffix) -MM "sprite.cpp"

$(IntermediateDirectory)/sprite.cpp$(PreprocessSuffix): sprite.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sprite.cpp$(PreprocessSuffix) "sprite.cpp"

$(IntermediateDirectory)/engine.cpp$(ObjectSuffix): engine.cpp $(IntermediateDirectory)/engine.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Ninja/engine.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/engine.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/engine.cpp$(DependSuffix): engine.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/engine.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/engine.cpp$(DependSuffix) -MM "engine.cpp"

$(IntermediateDirectory)/engine.cpp$(PreprocessSuffix): engine.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/engine.cpp$(PreprocessSuffix) "engine.cpp"

$(IntermediateDirectory)/core.cpp$(ObjectSuffix): core.cpp $(IntermediateDirectory)/core.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Ninja/core.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/core.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/core.cpp$(DependSuffix): core.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/core.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/core.cpp$(DependSuffix) -MM "core.cpp"

$(IntermediateDirectory)/core.cpp$(PreprocessSuffix): core.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/core.cpp$(PreprocessSuffix) "core.cpp"

$(IntermediateDirectory)/link_button.cpp$(ObjectSuffix): link_button.cpp $(IntermediateDirectory)/link_button.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Ninja/link_button.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/link_button.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/link_button.cpp$(DependSuffix): link_button.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/link_button.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/link_button.cpp$(DependSuffix) -MM "link_button.cpp"

$(IntermediateDirectory)/link_button.cpp$(PreprocessSuffix): link_button.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/link_button.cpp$(PreprocessSuffix) "link_button.cpp"

$(IntermediateDirectory)/menu_play_button.cpp$(ObjectSuffix): menu_play_button.cpp $(IntermediateDirectory)/menu_play_button.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Ninja/menu_play_button.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_play_button.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_play_button.cpp$(DependSuffix): menu_play_button.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_play_button.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_play_button.cpp$(DependSuffix) -MM "menu_play_button.cpp"

$(IntermediateDirectory)/menu_play_button.cpp$(PreprocessSuffix): menu_play_button.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_play_button.cpp$(PreprocessSuffix) "menu_play_button.cpp"

$(IntermediateDirectory)/text.cpp$(ObjectSuffix): text.cpp $(IntermediateDirectory)/text.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Ninja/text.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/text.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/text.cpp$(DependSuffix): text.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/text.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/text.cpp$(DependSuffix) -MM "text.cpp"

$(IntermediateDirectory)/text.cpp$(PreprocessSuffix): text.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/text.cpp$(PreprocessSuffix) "text.cpp"

$(IntermediateDirectory)/menu_title.cpp$(ObjectSuffix): menu_title.cpp $(IntermediateDirectory)/menu_title.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Ninja/menu_title.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_title.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_title.cpp$(DependSuffix): menu_title.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_title.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_title.cpp$(DependSuffix) -MM "menu_title.cpp"

$(IntermediateDirectory)/menu_title.cpp$(PreprocessSuffix): menu_title.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_title.cpp$(PreprocessSuffix) "menu_title.cpp"

$(IntermediateDirectory)/menu_music_button.cpp$(ObjectSuffix): menu_music_button.cpp $(IntermediateDirectory)/menu_music_button.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Ninja/menu_music_button.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_music_button.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_music_button.cpp$(DependSuffix): menu_music_button.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_music_button.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_music_button.cpp$(DependSuffix) -MM "menu_music_button.cpp"

$(IntermediateDirectory)/menu_music_button.cpp$(PreprocessSuffix): menu_music_button.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_music_button.cpp$(PreprocessSuffix) "menu_music_button.cpp"

$(IntermediateDirectory)/music.cpp$(ObjectSuffix): music.cpp $(IntermediateDirectory)/music.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Ninja/music.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/music.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/music.cpp$(DependSuffix): music.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/music.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/music.cpp$(DependSuffix) -MM "music.cpp"

$(IntermediateDirectory)/music.cpp$(PreprocessSuffix): music.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/music.cpp$(PreprocessSuffix) "music.cpp"

$(IntermediateDirectory)/chunk.cpp$(ObjectSuffix): chunk.cpp $(IntermediateDirectory)/chunk.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Ninja/chunk.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/chunk.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/chunk.cpp$(DependSuffix): chunk.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/chunk.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/chunk.cpp$(DependSuffix) -MM "chunk.cpp"

$(IntermediateDirectory)/chunk.cpp$(PreprocessSuffix): chunk.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/chunk.cpp$(PreprocessSuffix) "chunk.cpp"

$(IntermediateDirectory)/menu_log.cpp$(ObjectSuffix): menu_log.cpp $(IntermediateDirectory)/menu_log.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Ninja/menu_log.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_log.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_log.cpp$(DependSuffix): menu_log.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_log.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_log.cpp$(DependSuffix) -MM "menu_log.cpp"

$(IntermediateDirectory)/menu_log.cpp$(PreprocessSuffix): menu_log.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_log.cpp$(PreprocessSuffix) "menu_log.cpp"

$(IntermediateDirectory)/menu_exit_log.cpp$(ObjectSuffix): menu_exit_log.cpp $(IntermediateDirectory)/menu_exit_log.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Ninja/menu_exit_log.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/menu_exit_log.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/menu_exit_log.cpp$(DependSuffix): menu_exit_log.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/menu_exit_log.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/menu_exit_log.cpp$(DependSuffix) -MM "menu_exit_log.cpp"

$(IntermediateDirectory)/menu_exit_log.cpp$(PreprocessSuffix): menu_exit_log.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/menu_exit_log.cpp$(PreprocessSuffix) "menu_exit_log.cpp"

$(IntermediateDirectory)/loading.cpp$(ObjectSuffix): loading.cpp $(IntermediateDirectory)/loading.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/.codelite/Workspace_one/Ninja/loading.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/loading.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/loading.cpp$(DependSuffix): loading.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/loading.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/loading.cpp$(DependSuffix) -MM "loading.cpp"

$(IntermediateDirectory)/loading.cpp$(PreprocessSuffix): loading.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/loading.cpp$(PreprocessSuffix) "loading.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/



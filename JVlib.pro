# JVlib.pro
CONFIG += warn_on qt
TARGET = JVlib
FORMS       = JVlib.ui save_dialog/Save_Dialog.ui config/ini_conf.ui
QT += sql
DEFINES += QT_NO_DEBUG
DEFINES += QT_NO_DEBUG_OUTPUT
OBJECTS_DIR = objects
MOC_DIR = objects
QMAKE_CLEAN += asdf
LIBS += -lasound -lkdeui -liniparser
RESOURCES += JVlibForm.qrc
HEADERS	+= JVlibForm.h \
	JV-struct-defs.h \
	State_Table.h \
	system/system.h \
	system/system_slots.h \
	performance/performance.h \
	performance/perf_slots.h \
	tuning/tuning_slots.h \
	EFX/EFX.h \
	EFX/EFX_slots.h	\
	config/ini_conf.h \
	save_dialog/Save_Dialog.h
SOURCES     += main.cpp \
	JVlibForm.cpp \
	menu/create_menu_actions.cpp \
	menu/menubar.cpp \
	menu/menu_slots.cpp \
	system/system.cpp \
	system/system_slots.cpp \
	system/create_sys_actions.cpp \
	system/set_sys_initial.cpp \
	performance/performance.cpp \
	performance/perf_slots.cpp \
	performance/set_perf_initial.cpp \
	parts/parts.cpp \
	parts/set_part_initial.cpp \
	parts/parts_slots.cpp \
	parts/part_1/set_part1_initial.cpp \
	parts/part_1/part_1.cpp \
	parts/part_2/set_part2_initial.cpp \
	parts/part_2/part_2.cpp \
	parts/part_3/set_part3_initial.cpp \
	parts/part_3/part_3.cpp \
	parts/part_4/set_part4_initial.cpp \
	parts/part_4/part_4.cpp \
	parts/part_5/set_part5_initial.cpp \
	parts/part_5/part_5.cpp \
	parts/part_6/set_part6_initial.cpp \
	parts/part_6/part_6.cpp \
	parts/part_7/set_part7_initial.cpp \
	parts/part_7/part_7.cpp \
	parts/part_8/set_part8_initial.cpp \
	parts/part_8/part_8.cpp \
	parts/part_9/set_part9_initial.cpp \
	parts/part_9/part_9.cpp \
	parts/part_10/set_part10_initial.cpp \
	parts/part_10/part_10.cpp \
	parts/part_11/set_part11_initial.cpp \
	parts/part_11/part_11.cpp \
	parts/part_12/set_part12_initial.cpp \
	parts/part_12/part_12.cpp \
	parts/part_13/set_part13_initial.cpp \
	parts/part_13/part_13.cpp \
	parts/part_14/set_part14_initial.cpp \
	parts/part_14/part_14.cpp \
	parts/part_15/set_part15_initial.cpp \
	parts/part_15/part_15.cpp \
	parts/part_16/set_part16_initial.cpp \
	parts/part_16/part_16.cpp \
	EFX/EFX.cpp \
	EFX/EFX_slots.cpp \
	EFX/set_EFX_initial.cpp \
	EFX/displayEFXparms.cpp \
	EFX/EFX01stereoEQ.cpp \
	EFX/EFX02overdrive.cpp \
	EFX/EFX03distortion.cpp \
	EFX/EFX04phaser.cpp \
	EFX/EFX05spectrum.cpp \
	EFX/EFX06enhancer.cpp \
	EFX/EFX07autoWah.cpp \
	EFX/EFX08rotary.cpp \
	EFX/EFX09compressor.cpp \
	EFX/EFX10limiter.cpp \
	EFX/EFX11HexaChorus.cpp \
	EFX/EFX12TremoloChorus.cpp \
	EFX/EFX13Space_D.cpp \
	EFX/EFX14StereoChorus.cpp \
	EFX/EFX15StereoFlanger.cpp \
	EFX/EFX16StepFlanger.cpp \
        EFX/EFX17StereoDelay.cpp \ 
        EFX/EFX18ModulationDelay.cpp \ 
        EFX/EFX19TripleTapDelay.cpp \ 
        EFX/EFX20QuadrupleTapDelay.cpp \ 
        EFX/EFX21TimeControlDelay.cpp \ 
        EFX/EFX22VoicePitchShifter.cpp \ 
        EFX/EFX23FeedbackPitchShifter.cpp \ 
        EFX/EFX24Reverb.cpp \ 
        EFX/EFX25GateReverb.cpp \ 
        EFX/EFX26OverdriveSeriesChorus.cpp \ 
        EFX/EFX27OverdriveSeriesFlanger.cpp \ 
        EFX/EFX28OverdriveSeriesDelay.cpp \ 
        EFX/EFX29DistortionSeriesChorus.cpp \ 
        EFX/EFX30DistortionSeriesFlanger.cpp \ 
        EFX/EFX31DistortionSeriesDelay.cpp \ 
        EFX/EFX32EnhancerSeriesChorus.cpp \ 
        EFX/EFX33EnhancerSeriesFlanger.cpp \ 
        EFX/EFX34EnhancerSeriesDelay.cpp \ 
        EFX/EFX35ChorusSeriesDelay.cpp \ 
        EFX/EFX36FlangerSeriesDelay.cpp \ 
        EFX/EFX37ChorusSeriesFlanger.cpp \ 
        EFX/EFX38ChorusParallelDelay.cpp \ 
        EFX/EFX39FlangerParallelDelay.cpp \ 
        EFX/EFX40ChorusParallelFlanger.cpp \ 
	EFX/EFXdisplayParm1.cpp \
	EFX/EFXdisplayParm2.cpp \
	EFX/EFXdisplayParm3.cpp \
	EFX/EFXdisplayParm4.cpp \
	EFX/EFXdisplayParm5.cpp \
	EFX/EFXdisplayParm6.cpp \
	EFX/EFXdisplayParm7.cpp \
	EFX/EFXdisplayParm8.cpp \
	EFX/EFXdisplayParm9.cpp \
	EFX/EFXdisplayParm10.cpp \
	EFX/EFXdisplayParm11.cpp \
	EFX/EFXdisplayParm12.cpp \
	patch/patch.cpp \
	patch/patch_slots.cpp \
	patch/set_patch_initial.cpp \
	tone/tone.cpp \
	tone/set_tone_initial.cpp \
	tone/tone_slots.cpp \
	toneENV/create_toneENV_actions.cpp \
	toneEFX/set_toneEFX_initial.cpp \
	toneEFX/toneEFX.cpp \
	toneEFX/toneEFX_slots.cpp \
	toneENV/set_toneENV_initial.cpp \
	toneENV/toneENV_slots.cpp \
	save_dialog/save_dialog_slots.cpp \
	save_dialog/save_dialog.cpp \
	tuning/set_tuning_initial.cpp \
	tuning/tuning.cpp \
	tuning/tuning_slots.cpp \
	pitch/set_pitch_initial.cpp \
	pitch/pitch_slots.cpp \
	rhythm/set_rhythm_initial.cpp \
	rhythm/rhythm.cpp \
	rhythm/rhythm_slots.cpp \
	config/ini_conf.cpp \
	playmidi/create_playmidi_actions.cpp \
	playmidi/player.cpp \
	playmidi/file_parser.cpp \
	playmidi/midi_player.cpp

// set_initial.cpp
// for Parts tab, Part_14

#include        "JVlibForm.h"
#include        <QtGui>

void JVlibForm::setPart14_Parms() {
  // set Part 1 controls/displays based on the active area memory contents, 
  // which were just updated from the synth after a Sync button was clicked.
  //  state_table->updates_enabled = false was set by the calling program, do not change it here.
  QString str;
  Part14_Level_select->setValue(active_area->active_performance.perf_part[13].level);
  Part14_Level_select->setStatusTip(str.setNum(active_area->active_performance.perf_part[13].level));
  Part14_Pan_select->setValue(active_area->active_performance.perf_part[13].pan);
  Part14_Pan_select->setStatusTip(str.setNum(active_area->active_performance.perf_part[13].pan));
  Part14_ChorusSend_select->setValue(active_area->active_performance.perf_part[13].chorus_send_level);
  Part14_ChorusSend_select->setStatusTip(str.setNum(active_area->active_performance.perf_part[13].chorus_send_level));
  Part14_ReverbSend_select->setValue(active_area->active_performance.perf_part[13].reverb_send_level);
  Part14_ReverbSend_select->setStatusTip(str.setNum(active_area->active_performance.perf_part[13].reverb_send_level));
  Part14_OutputLevel_select->setValue(active_area->active_performance.perf_part[13].output_level);
  Part14_OutputLevel_select->setStatusTip(str.setNum(active_area->active_performance.perf_part[13].output_level));
  Part14_Transpose_select->setValue(active_area->active_performance.perf_part[13].coarse_tune-48);
  Part14_Transpose_display->display(active_area->active_performance.perf_part[13].coarse_tune-48);
  Part14_TuneAdj_select->setValue(active_area->active_performance.perf_part[13].fine_tune-50);
  Part14_VoiceReserve_select->setValue(active_area->active_performance.perf_common.voice_reserve[0]);
  Part14_LowLimit_select->setValue(active_area->active_performance.perf_part[13].key_lower);
  Part14_HighLimit_select->setValue(active_area->active_performance.perf_part[13].key_upper);
  Part14_ReceiveMidi_enable->setChecked(active_area->active_performance.perf_part[13].MIDI_receive);
  Part14_MidiChannel_select->setValue(active_area->active_performance.perf_part[13].MIDI_channel+1);
  Part14_ReceivePrgChg_enable->setChecked(active_area->active_performance.perf_part[13].receive_program_change);
  Part14_ReceiveVolume_enable->setChecked(active_area->active_performance.perf_part[13].receive_volume);
  Part14_ReceiveHold_enable->setChecked(active_area->active_performance.perf_part[13].receive_hold_1);
  Part14_Output_select->setCurrentIndex(active_area->active_performance.perf_part[13].output);
  Part14_TestTone_switch->setChecked(false);
  
  switch(active_area->active_performance.perf_part[13].patch_group_id) {
    case 0x01:  // User
      Part14_PatchGroup_select->setCurrentIndex(0);
      break;
    case 0x02:  // Exp A
	Part14_PatchGroup_select->setCurrentIndex(1);
	break;
    case 0x03:  // Preset A
	Part14_PatchGroup_select->setCurrentIndex(2);
	break;
    case 0x04:  // Preset B
	Part14_PatchGroup_select->setCurrentIndex(3);
	break;
    case 0x05:  // Preset C
	Part14_PatchGroup_select->setCurrentIndex(4);
	break;
    case 0x06:  // Preset D
	Part14_PatchGroup_select->setCurrentIndex(5);
	break;
    case 0x10:  // Exp B
	Part14_PatchGroup_select->setCurrentIndex(6);
	break;
    case 0x62:  // Exp C
	Part14_PatchGroup_select->setCurrentIndex(7);
	break;
    default:
	Part14_PatchGroup_select->setCurrentIndex(0);
	break;
  }	// end SWITCH
  Part14_SetPatchMax();
  Part14_PatchNumber_select->setValue((active_area->active_performance.perf_part[13].patch_num_high*16) + active_area->active_performance.perf_part[13].patch_num_low+1);
  Part14_PatchName_display->setText(QString::fromAscii(&active_area->active_perf_patch[13].patch_common.name[0],12));
  Part14_LowLimit_display->setText(funcNoteCalc(Part14_LowLimit_select->value()));
  Part14_HighLimit_display->setText(funcNoteCalc(Part14_HighLimit_select->value()));
  
  Part14_ReceivePrgChg_enable->setEnabled(AcceptProgramChg_switch->isChecked());
  Part14_ReceiveVolume_enable->setEnabled(AcceptVolumeChg_switch->isChecked());
  Part14_ReceiveHold_enable->setEnabled(AcceptHold1Chg_switch->isChecked());
}	// end setPart14_Parms

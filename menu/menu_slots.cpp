// menu_slots.cpp
/* Contains:
 * HelpDoc()
 * selectedPort()
 * slotOffline()
 * slotactionWhats_This()
 * slotactionWrite()
 * slotactionCopy()
 * slotDB_Maint()
 * slotConfig()
 * open()
 * save()
 * saveAs()
 * about()
 * on_actionData_Lists_triggered()
 */

#include	"JVlibForm.h"
#include	<QtGui>
#include	"config/ini_conf.h"
#include	"save_dialog/Save_Dialog.h"
#include	"load_dialog/load_dialog.h"
#include	"data_list/data_list.h"

QSqlDatabase JVlibForm::db_mysql;

void JVlibForm::HelpDoc() {
  QProcess process;
  switch(MainTabWidget->currentIndex()) {
    case 0:
      process.startDetached("evince --page-index=66 "+qApp->applicationDirPath() +"/doc/JV-1080_OM.pdf");
      break;
    case 1:
      process.startDetached("evince --page-index=57 "+qApp->applicationDirPath() +"/doc/JV-1080_OM.pdf");
      break;
    case 2:
      process.startDetached("evince --page-index=59 "+qApp->applicationDirPath() +"/doc/JV-1080_OM.pdf");
      break;
    case 3:
      process.startDetached("evince --page-index=42 "+qApp->applicationDirPath() +"/doc/JV-1080_OM.pdf");
      break;
    case 4:
      process.startDetached("evince --page-index=45 "+qApp->applicationDirPath() +"/doc/JV-1080_OM.pdf");
      break;
    case 5:
      process.startDetached("evince --page-index=50 "+qApp->applicationDirPath() +"/doc/JV-1080_OM.pdf");
      break;
    case 6:
      process.startDetached("evince --page-index=51 "+qApp->applicationDirPath() +"/doc/JV-1080_OM.pdf");
      break;
    case 7:
      process.startDetached("evince --page-index=54 "+qApp->applicationDirPath() +"/doc/JV-1080_OM.pdf");
      break;
    case 8:
      process.startDetached("evince --page-index=61 "+qApp->applicationDirPath() +"/doc/JV-1080_OM.pdf");
      break;
    case 9:
      process.startDetached("evince --page-index=53 "+qApp->applicationDirPath() +"/doc/JV-1080_OM.pdf");
      break;
    case 10:
      process.startDetached("evince --page-index=68 "+qApp->applicationDirPath() +"/doc/JV-1080_OM.pdf");
      break;
    default:
      process.startDetached("evince --page-index=20 "+qApp->applicationDirPath() +"/doc/JV-1080_OM.pdf");
      break;
  }
}

void JVlibForm::selectedPort()  {
  menu_Setup->hide();
  QByteArray buf(PortBox->currentText().toAscii(),8);
  strcpy(MIDI_dev, buf.data());
  state_table->jv_connect = true;
  if (on_System_Sync_button_clicked() != EXIT_SUCCESS) {
    action_Offline->setChecked(true);
    System_JV_status->off();
    state_table->jv_connect = false;
    statusbar->showMessage("Failed to load System settings!");
    QMessageBox::critical(this, "JVlib", QString("Failed trying to load System settings.\nIs a valid MIDI port selected?"));
  }
}  // end selectedPort

void JVlibForm::slotOffline(bool checked) {
  state_table->jv_connect = !checked;
  statusbar->showMessage(checked?"Offline":"Online");
  if (!checked) {
    System_JV_status->on();
    on_System_Sync_button_clicked();
  }
  else {
    System_JV_status->off();
    System_Sync_status->off();
    EnablePerf(true);
    EnablePatch(true);
  }
}

void JVlibForm::slotactionWhats_This() {
  QWhatsThis::enterWhatsThisMode ();
}

void JVlibForm::slotactionWrite() {
  if (!state_table->jv_connect) return;	// JV is OFFLINE, just quit now
  // verify the data to be written is valid, else abort
  if (state_table->perf_mode && !state_table->performance_sync) return;
  if (state_table->patch_mode && !state_table->patch_sync) return;
  if (state_table->rhythm_mode && !state_table->rhythm_sync) return;
  // check if we can write to User memory, else abandon this function
  unsigned char oldCh, newCh;
  unsigned char buf[256];
  unsigned char newBuf[5]; // = { 0x10, 0x00, 0x00, 0x00, 0x7F };
  char oneSize[4];
  memset(buf,0,sizeof(buf));
  memset(oneSize,0,4);
  memset(newBuf,0,5);
  buf[0] = 0x10;
  buf[7] = 1;
  oneSize[3] = 1;
  newBuf[0] = 0x10;
  newBuf[4] = 0x7F;
  JVlibForm::sysex_request(buf);
  JVlibForm::sysex_get(&oldCh, oneSize);
  JVlibForm::sysex_update(newBuf, 5);
  JVlibForm::sysex_request(buf);
  JVlibForm::sysex_get(&newCh, oneSize);
  if (newCh == oldCh) {	// did not update
    QMessageBox::critical(this, "Load_Dialog", "Exclusive protect is ON\nUser (permanent) memory cannot be written");
    return;
  }
  else {
    newBuf[4] = oldCh;
    JVlibForm::sysex_update(newBuf, 5);
    JVlibForm::sysex_request(buf);
    JVlibForm::sysex_get(&newCh, oneSize);
    if (newCh != oldCh) { // OOPS, did not replace the original char
      QMessageBox::warning(this, "Load_Dialog", "Unable to undo write testing\nUser 1 Performance name is corrupted");
      return;
    }
  }
  // all good, proceed with writing the User data
  QMessageBox msgBox;
  msgBox.setText("Write current settings to the JV-1080");
  if (state_table->perf_mode)
    msgBox.setInformativeText(QString("Overwrite settings for\nUser Performance %1?") .arg(SysPerfNumber->value() ));
  if (state_table->patch_mode)
    msgBox.setInformativeText(QString("Overwrite settings for\nUser Patch %1?") .arg(SysPatchNumber->value() ));
  if (state_table->rhythm_mode)
    msgBox.setInformativeText(QString("Overwrite settings for\nUser Rhythm %1?") .arg(Rhythm_PatchNumber_select->value() ));
  msgBox.setDetailedText("CAUTION!\nClicking the Apply button will permanently write the current settings to the designated User area. It will overwrite the existing settings for that number.");
  msgBox.setIcon(QMessageBox::Question);
  msgBox.setStandardButtons(QMessageBox::Apply | QMessageBox::Cancel);
  msgBox.setDefaultButton(QMessageBox::Apply);
  int rc = msgBox.exec();
  switch(rc) {
    case QMessageBox::Apply:
      if (QMessageBox::warning(this, "JVlib", "Confirm overwritting the existing settings",QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Ok) == QMessageBox::Cancel) break;
      // write the active_area to the related User area
      puts("Writing current settings");
      this->setCursor(Qt::WaitCursor);
      int pn;
      // write User Patch (1 - 128)
      if (state_table->patch_mode) {
	pn = SysPatchNumber->value()-1;
	// write patch common
	memset(buf,0,sizeof(buf));
	buf[0] = 0x11;	// addr for User Patches
	buf[1] = pn;	// User Patch number to load
	memcpy((void *)&buf[4], &active_area->active_patch_patch.patch_common.name[0],0x48);  // patch common data
	usleep(20000);
	JVlibForm::sysex_update(buf, 0x48+4);
	// write relevant Tones (4)
	for (int x=0;x<4;x++) {
	  buf[2] = 0x10 + (x*2);
	  memcpy((void *)&buf[4], &active_area->active_patch_patch.patch_tone[x].tone, 0x81);
	  usleep(25000);
	  JVlibForm::sysex_update(buf, 0x81+4);
	}
      }	// end Patch mode
      // write User Rhythm set (1 or 2)
      if (state_table->rhythm_mode) {
	pn = Rhythm_PatchNumber_select->value() - 1;
	// write rhythm_common
	memset(buf,0,sizeof(buf));
	buf[0] = 0x10;        // addr for User Rhythms
	buf[1] = 0x40 + pn; // User Rhythm number to load
	memcpy((void *)&buf[4], &active_area->active_rhythm.rhythm_common.name[0], 0x0C);
	usleep(20000);
	JVlibForm::sysex_update(buf, 0x0C+4);
	// write 64 notes
	for (int x=0;x<64;x++) {
	  buf[2] = 0x23 + x;
	  memcpy((void *)&buf[4], &active_area->active_rhythm.rhythm_note[x].tone, 0x3A);
	  usleep(20000);
	  JVlibForm::sysex_update(buf, 0x3A+4);
	}
      }	// end Rhythm mode
      // write User Performance (1 - 32)
      if (state_table->perf_mode) {
	pn = SysPerfNumber->value() - 1;
	// write perf_common
	memset(buf,0,sizeof(buf));
	buf[0] = 0x10;        // addr for User Performances
	buf[1] = pn;
	memcpy((void *)&buf[4], &active_area->active_performance.perf_common.name[0], 0x40);
	usleep(20000);
	JVlibForm::sysex_update(buf, 0x40+4);
	// write synchronized Parts (16)
	for (int x=0;x<16;x++) {
	  buf[2] = 0x10 + x;
	  memcpy((void *)&buf[4], &active_area->active_performance.perf_part[x].MIDI_receive, 0x13);
	  usleep(20000);
	  JVlibForm::sysex_update(buf, 0x13+4);
	}
      }	// end Perf mode
      this->setCursor(Qt::ArrowCursor);
      break;
    case QMessageBox::Cancel:
      // do nothing
      puts("Write cancelled");
      break;
    default:
      // should never happen
      puts("How did we get here?");
      break;
  }	// end switch(rc)
}	// end slotactionWrite

void JVlibForm::slotactionCopy() {
  if (!state_table->jv_connect) return;	// JV is OFFLINE, just quit now
  // verify the data to be written is valid, else abort
  if (state_table->perf_mode && !state_table->performance_sync) return;
  if (state_table->patch_mode && !state_table->patch_sync) return;
  if (state_table->rhythm_mode && !state_table->rhythm_sync) return;
  // all good, proceed with copying the data
  JV_COPY jv_copy;
  jv_copy.exec();
}

void JVlibForm::slotDB_Maint() {
  // NOTE: tbd  
  // Rename, delete an entry, change comment
}

void  JVlibForm::slotConfig() {
  // pop up a text editor dialog box for the configuration file
  INI_CONF ini_conf;
  ini_conf.setData(CFGfile);
  ini_conf.exec();
}

bool JVlibForm::open() {
  if (state_table->db_connect) {
    Load_Dialog load_dialog;
    connect(&load_dialog, SIGNAL(System_Loaded()), this, SLOT(System_Loaded()) );
    connect(&load_dialog, SIGNAL(Tuning_Loaded(int)), this, SLOT(Tuning_Loaded(int)) );
    if (!load_dialog.exec())
      return false;
  }
  else {
    QString fileName = QFileDialog::getOpenFileName(this);
    if (fileName.isEmpty())
      return false;
    loadFile(fileName);
  }
  return true;
}

bool JVlibForm::save() {
  if (state_table->db_connect) {
    Save_Dialog save_dialog;
    if (!save_dialog.exec())
      return false;
  } 
  else {
    if (curFile.isEmpty())
      return saveAs();
    else
      return saveFile(curFile);
  }
  return true;
}

bool JVlibForm::saveAs() {
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

void JVlibForm::about() {
   QMessageBox::about(this, "About JVlib",
            "<center><b>JV-1080</b></center><center>Synthesizer controller and library </center>"
               "<center>Created by Mark Roberson </center>"
               "<center>Copyright 2013, all rights reserved</center>");
}

void JVlibForm::on_actionData_Lists_triggered() {
  Data_List.show();
  Data_List.raise();
  Data_List.activateWindow();
}

/*
 * Copyright 2011-2015. All rights reserved.
 * Distributed under the terms of the MIT license.
 *
 * Author:
 *	Humdinger, humdingerb@gmail.com
 *
 * based on ideas of YAVTD for Haiku
 * Version 1.0 by Leszek Lesner (C) 2011
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Settings.h"
#include "WorkerThread.h"

#include <Button.h>
#include <ColumnListView.h>
#include <ColumnTypes.h>
#include <Directory.h>
#include <FilePanel.h>
#include <Menu.h>
#include <MenuBar.h>
#include <MenuItem.h>
#include <OptionPopUp.h>
#include <String.h>
#include <StringView.h>
#include <TextView.h>
#include <Window.h>

enum {
	statBUFFER			= 'buff',
	statDOWNLOAD		= 'down',
	statFINISH_GET		= 'gfin',
	statFINISH_PLAY		= 'pfin',
	statFINISH_SAVE		= 'sfin',
	statFINISH_UPDATE	= 'ufin',
	statERROR			= 'erro',
	statPLAYING			= 'play',

	msgABORT		= 'abor',
	msgADD			= 'addu',
	msgAUTO			= 'auto',
	msgCLEAN		= 'clen',
	msgCLEARLIST	= 'cler',
	msgEDIT			= 'edit',
	msgFORMAT		= 'form',
	msgPLAY			= 'ypla',
	msgSAVE			= 'esav',
	msgSTART		= 'star',

	FOLDER_SELECT_MESSAGE = 'fsel',
	SELECT_THIS_DIR_MESSAGE = 'sdir'
};


class MainWindow : public BWindow {
public:
						MainWindow();
		void			MessageReceived(BMessage* msg);
		bool			QuitRequested();
		virtual void	FrameResized(float width, float height);
		void			SetURL(BString* url);

private:
		void			_BuildMenu();
		void			_BuildLayout();

		status_t		WatchMonitoredSitesList();
		bool			GetClip(BString url, WorkerThread* wt);
		void			GetTitle(BString url, WorkerThread* wt);
		void			KillThread(char* command);
		void			ResetFlags();
		void			SetStatus(BString text);
		void			URLofFile(entry_ref &ref);

		void			PlayClip();
		void			SaveClip();

private:
		BButton*		fAddButton;
		BButton*		fSaveButton;

		BFilePanel*		fSaveFilePanel;

		BMenuBar*		fMenuBar;
		BMenuItem*		fAutoMenu;
		BMenuItem*		fCleanMenu;
		BMenuItem*		fPlayMenu;
		BMenuItem*		fSaveMenu;
		
		BOptionPopUp*	fFormatOption;

		BString			fClipTitle;
		BString*		fFilename;
		BString*		fSaveDir;
		BString*		fTempDir;
		BString*		fURL;

		BTextView*		fMultiUrlBox;
		BStringView*	fUrlTitle;
		BStringView*	fDownloadsTitle;
		
		BColumnListView*	fDownloadsView;

		bool			fAbortedFlag;
		bool			fGetFlag;
		bool			fGotClipFlag;
		bool			fPlayedFlag;
		bool			fPlayingFlag;
		bool			fSavedFlag;
		bool			fSaveIt;

		Settings		fSettings;
		
		WorkerThread*	fWorkerThread;
};

#endif /* MAINWINDOW_H */

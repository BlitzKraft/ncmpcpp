/***************************************************************************
 *   Copyright (C) 2008 by Andrzej Rybczak   *
 *   electricityispower@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef HAVE_SONG_H
#define HAVE_SONG_H

#include <cstdlib>
#include <string>
#include <sstream>
#include <stdexcept>

#include "misc.h"
#include "libmpdclient.h"

using std::string;

void DefineEmptyTags();

class Song
{
	public:
		Song() : itsHash(0), copyPtr(0), isStream(0), itsGetEmptyFields(0) { itsSong = mpd_newSong(); }
		Song(mpd_Song *, bool = 0);
		Song(const Song &);
		~Song();
		
		string GetFile() const;
		string GetShortFilename() const;
		string GetDirectory() const;
		string GetArtist() const;
		string GetTitle() const;
		string GetAlbum() const;
		string GetTrack() const;
		string GetYear() const;
		string GetGenre() const;
		//string GetName() const { return itsName; }
		string GetComposer() const;
		string GetPerformer() const;
		string GetDisc() const;
		string GetComment() const;
		string GetLength() const;
		long long GetHash() const { return itsHash; }
		int GetTotalLength() const { return itsSong->time < 0 ? 0 : itsSong->time; }
		int GetPosition() const { return itsSong->pos; }
		int GetID() const { return itsSong->id; }
		
		void SetFile(const string &str);
		void SetArtist(const string &str);
		void SetTitle(const string &str);
		void SetAlbum(const string &str);
		void SetTrack(const string &str);
		void SetTrack(int track);
		void SetYear(const string &str);
		void SetYear(int year);
		void SetGenre(const string &str);
		void SetComment(const string &str);
		void SetPosition(int pos);
		
		void SetNewName(string name) { itsNewName = name == GetShortFilename() ? "" : name; }
		string GetNewName() const { return itsNewName; }
		
		void NullMe() { itsSong = 0; }
		void CopyPtr(bool copy) { copyPtr = copy; }
		
		void GetEmptyFields(bool get) { itsGetEmptyFields = get; }
		void Clear();
		bool Empty() const;
		
		Song & operator=(const Song &);
		bool operator==(const Song &) const;
		bool operator!=(const Song &) const;
		bool operator<(const Song &rhs) const;
		
		static string ShowTime(int);
	private:
		mpd_Song *itsSong;
		string itsNewName;
		unsigned itsSlash;
		long long itsHash;
		bool copyPtr;
		bool isStream;
		bool itsGetEmptyFields;
};

#endif


/*
THE COMPUTER CODE CONTAINED HEREIN IS THE SOLE PROPERTY OF PARALLAX
SOFTWARE CORPORATION ("PARALLAX").  PARALLAX, IN DISTRIBUTING THE CODE TO
END-USERS, AND SUBJECT TO ALL OF THE TERMS AND CONDITIONS HEREIN, GRANTS A
ROYALTY-FREE, PERPETUAL LICENSE TO SUCH END-USERS FOR USE BY SUCH END-USERS
IN USING, DISPLAYING,  AND CREATING DERIVATIVE WORKS THEREOF, SO LONG AS
SUCH USE, DISPLAY OR CREATION IS FOR NON-COMMERCIAL, ROYALTY OR REVENUE
FREE PURPOSES.  IN NO EVENT SHALL THE END-USER USE THE COMPUTER CODE
CONTAINED HEREIN FOR REVENUE-BEARING PURPOSES.  THE END-USER UNDERSTANDS
AND AGREES TO THE TERMS HEREIN AND ACCEPTS THE SAME BY USE OF THIS FILE.  
COPYRIGHT 1993-1998 PARALLAX SOFTWARE CORPORATION.  ALL RIGHTS RESERVED.
*/

#include <stdio.h>
#include <stdlib.h>
#include <Errors.h>
#include <Resources.h>
#include <Sound.h>

#include "inferno.h"
#include "texmap.h"		// For Lighting_on
#include "songs.h"
#include "screens.h"
#include "game.h"
#include "player.h"
#include "cfile.h"
#include "segpoint.h"
#include "ai.h"
#include "piggy.h"
#include "wall.h"
#include "joy.h"
#include "halestrm.h"
#include "byteswap.h"
#include "mem.h"
#include "sounds.h"
#include "mono.h"
#include "error.h"
#include "kconfig.h"
#include "redbook.h"
#include "newdemo.h"
#include "macsys.h"

#define _DIGI_SAMPLE_FLAGS (_VOLUME | _PANNING )
#define _DIGI_MAX_VOLUME			256
#define MAX_SOUND_CHANNELS			24
#ifdef MAC_SHAREWARE
#define MAX_MUSIC_CHANNELS			6
Handle Song_handle = NULL;
Handle Midi_handle = NULL;
#else
#define MAX_MUSIC_CHANNELS			0
#endif

int digi_lomem = 0;
int master_save;
int digi_initialized = 0;
ubyte digi_paused = 0;
ubyte digi_cd_started = 0;			// have we started a disc that is not the Descent cd?
int midi_volume = 255;
int digi_volume = _DIGI_MAX_VOLUME;
int digi_midi_song_playing = 0;
int digi_last_midi_song = 0;
int digi_last_midi_song_loop = 0;
int digi_sound_quality =  Q_NORMAL;
int digi_max_channels = MAX_SOUND_CHANNELS;
ushort num_sounds;

extern ubyte Config_master_volume;

// sound object stuff -- used for fans and the boss only??
#define SOF_USED			1 		// Set if this sample is used
#define SOF_PLAYING			2		// Set if this sample is playing on a channel
#define SOF_LINK_TO_OBJ		4		// Sound is linked to a moving object. If object dies, then finishes play and quits.
#define SOF_LINK_TO_POS		8		// Sound is linked to segment, pos
#define SOF_PLAY_FOREVER	16		// Play forever (or until level is stopped), otherwise plays once

#define SOUND_PLAYING			1
#define SOUND_OBJECT_PLAYING	2

typedef struct song_resource {
	short		midi_id;
	ubyte		lead_inst;
	ubyte		buffer_ahead;
	ushort		tempo;
	ushort		pitch_shift;
	ubyte		sound_voices;
	ubyte		max_notes;
	ushort		norm_voices;
} song_resource;

typedef struct sound_object {
	short			signature;		// A unique signature to this sound
	ubyte			flags;			// Used to tell if this slot is used and/or currently playing, and how long.
	fix				max_volume;		// Max volume that this sound is playing at
	fix				max_distance;	// The max distance that this sound can be heard at...
	int				volume;			// Volume that this sound is playing at
	int				pan;				// Pan value that this sound is playing at
	short			handle;			// What handle this sound is playing on.  Valid only if SOF_PLAYING is set.
	short			soundnum;		// The sound number that is playing
	union {	
		struct {
			short			segnum;				// Used if SOF_LINK_TO_POS field is used
			short			sidenum;				
			vms_vector		position;
		} pos;
		struct {
			short			objnum;				// Used if SOF_LINK_TO_OBJ field is used
			short			objsignature;
		} obj;
	} link_type;
} sound_object;

#define MAX_SOUND_OBJECTS 5
sound_object SoundObjects[MAX_SOUND_OBJECTS];
short next_signature=0;

#define SOUND_OFFSET		10000

//short digi_sound_list[MAX_SOUNDS];

#ifdef MAC_SHAREWARE
static short sound_list[] = {
	10000,10001,10002,10003,10004,10005,10006,10007,10008,10009,10010,10011,10012,10013,10014,10015,10016,
	10017,10018,10019,10020,10021,10022,10023,10024,10025,10026,10027,10028,10029,10030,10031,10032,10033,
	10034,10035,10036,10037,10038,10039,10040,10041,10042,10043,10044,10045,10046,10047,10048,10049,10050,
	10051,10052,10053,10054,10055,10056,10057,10058,10059,100100,10061,10062,10063,10064,10065,10066,10067,
	10068,10069,10070,10071,10072,SOUND_END
};
#else
static short sound_list[] = {
	10000,10001,10002,10003,10004,10005,10006,10007,10008,10009,10010,10011,10012,10013,10014,10015,10016,
	10017,10018,10019,10020,10021,10022,10023,10024,10025,10026,10027,10028,10029,10030,10031,10032,10033,
	10034,10035,10036,10037,10038,10039,10040,10041,10042,10043,10044,10045,10046,10047,10048,10049,10050,
	10051,10052,10053,10054,10055,10056,10057,10058,10059,10060,10061,10062,10063,10064,10065,10066,10067,
	10068,10069,10070,10071,10072,10073,10074,10075,10076,10077,10078,10079,10080,10081,10082,10083,10084,
	10085,10086,10087,10088,10089,10090,10091,10092,10093,10094,10095,10096,10097, SOUND_END
};
#endif

void digi_reset_digi_sounds()
{
	int i;

	if ( !digi_initialized ) return;

	EndAllSound();
}

int digi_xlat_sound( int soundno )
{
	if ( soundno < 0 ) return -1;

	if ( use_sounds == 1 )	{
		soundno = AltSounds[soundno];
		if ( soundno == 255 ) return -1;
	}
//	return (int)(digi_sound_list[Sounds[soundno]] + SOUND_OFFSET);
	if (Sounds[soundno] == 255)
		return -1;
		
	return (int)(Sounds[soundno] + SOUND_OFFSET);

}

void digi_play_sample_3d( int sndnum, int angle, int volume, int no_dups )
{
	int vol;
	int i = sndnum, demo_angle;

	if (Newdemo_state == ND_STATE_RECORDING) {
		demo_angle = fixmuldiv(angle, F1_0, 255);
		if (no_dups)
			newdemo_record_sound_3d_once(sndnum, demo_angle, volume);
		else
			newdemo_record_sound_3d(sndnum, demo_angle, volume);
	}
	if (!digi_initialized) return;
	if (digi_paused) {
		digi_resume_all();
		if (digi_paused)
			return;
	}
	if ( sndnum < 0 ) return;
	i = digi_xlat_sound(sndnum);
	if (i == -1) return;

	vol = fixmuldiv(volume, digi_volume, F1_0);
	ChangeSoundVolume( i, vol );
	BeginSound(i, SOUND_RATE_11k);
	ChangeSoundStereoPosition(i, angle);
}

void digi_play_sample( int sndnum, fix max_volume )
{
	OSErr err;
	int i, vol;

	if (Newdemo_state == ND_STATE_RECORDING)
		newdemo_record_sound(sndnum);

	if (!digi_initialized) return;
	if (digi_paused) {
		digi_resume_all();
		if (digi_paused)
			return;
	}
	if ( sndnum < 0 ) return;

	i = digi_xlat_sound(sndnum);
	if (i == -1) return;

	vol = fixmuldiv(max_volume, digi_volume, F1_0);
	ChangeSoundVolume(i, vol );
	err = BeginSound(i, SOUND_RATE_11k);
	ChangeSoundStereoPosition(i, 0);
}

void digi_play_sample_once( int sndnum, fix max_volume )
{
	digi_play_sample( sndnum, F1_0 );
}

void digi_set_digi_volume(int dvolume)
{
	int i;
	
	if ( !digi_initialized ) return;

//	dvolume = fixmuldiv( dvolume, _DIGI_MAX_VOLUME, 0x7fff);
	if ( dvolume > _DIGI_MAX_VOLUME )
		digi_volume = _DIGI_MAX_VOLUME;
	else if ( dvolume < 0 )
		digi_volume = 0;
	else
		digi_volume = dvolume;

	digi_sync_sounds();
}

void digi_stop_current_song()
{
#ifdef MAC_SHAREWARE
	if ( digi_midi_song_playing ) {
		if ( !IsSongDone() )
			EndSong();										// stop the song 
		FreeSong();										// free the resources used.
		ReleaseResource(Midi_handle);
		ReleaseResource(Song_handle);
		Song_handle = NULL;
		Midi_handle = NULL;
		digi_midi_song_playing = 0;
	}
#else
	stop_redbook();
	digi_midi_song_playing = 0;
#endif
}

void digi_play_midi_song(int songnum, int loop )
{
	OSErr err;
	song_resource *song;
	ushort midi_id;

	if (!digi_initialized) return;

	digi_last_midi_song = songnum;
	digi_last_midi_song_loop = loop;

#ifndef MAC_SHAREWARE
	if ( !have_descent_cd ) {
		if ( !cd_playing && !digi_cd_started )
			redbook_start_play();
		digi_cd_started = 1;
		return;
	}
#endif

	digi_stop_current_song();
	
	if (midi_volume < 1)
		return;

#ifdef MAC_SHAREWARE
	Song_handle = GetResource('SONG', songnum);
	if (!Song_handle)
		return;
	song = (song_resource *)(*Song_handle);
	midi_id = song->midi_id;
	Midi_handle = GetResource('Midi', midi_id);
	if (!Midi_handle) {
		ReleaseResource(Song_handle);
		return;
	}
	song->sound_voices = digi_max_channels;
	song->norm_voices = 4 + (digi_max_channels/2);
	err = BeginSongFromMemory(songnum, Song_handle, Midi_handle, loop);
	if (err != noErr)
		return;
#else
	play_redbook_track(songnum, loop);
#endif
	digi_midi_song_playing = 1;
	
}

void digi_set_midi_volume(int n)
{
	int old_volume = midi_volume;
	
	if (!digi_initialized) return;

	if (n < 0)
		midi_volume = 0;
	else if (n > 255)
		midi_volume = 255;
	else
		midi_volume = n;
	
#ifdef MAC_SHAREWARE
	SetSongVolume(midi_volume);
#else
	redbook_set_volume(midi_volume);
#endif
	
	if (!old_volume && midi_volume) {
#ifdef MAC_SHAREWARE
		ChangeSystemVoices(MAX_MUSIC_CHANNELS, 4 + (digi_max_channels/2), digi_max_channels);
#endif
		digi_play_midi_song(digi_last_midi_song, digi_last_midi_song_loop);
	} else if (old_volume && !midi_volume) {
		digi_stop_current_song();
#ifndef MAC_SHAREWARE
		digi_cd_started = 0;
#else
		ChangeSystemVoices(0, digi_max_channels/2, digi_max_channels);
#endif

	}
}

void digi_set_volume(int dvolume, int mvolume)
{
	if (!digi_initialized) return;
	digi_set_digi_volume(dvolume);
	digi_set_midi_volume(mvolume);
}

void digi_set_master_volume( int volume )
{
	if (!digi_initialized) return;

	Config_master_volume = volume;	
	if ( Config_master_volume > 8 )
		Config_master_volume = 8;
	else if ( Config_master_volume < 0 )
		Config_master_volume = 0;
		
	SetMasterVolume( (Config_master_volume*256)/8 );
}

void digi_reset()
{
}

void digi_resume_all()
{
	if (!digi_initialized) return;

	if (digi_paused) {
#ifdef MAC_SHAREWARE
		ResumeMusicOnly();
#else
		redbook_pause(0);
#endif
		digi_paused = 0;
	}
}

void digi_pause_all()
{
	int i;
	
	if (!digi_initialized) return;

	if (!digi_paused) {	
		for (i=0; i<MAX_SOUND_OBJECTS; i++ )	{
			if ( (SoundObjects[i].flags & SOF_USED )	&& (SoundObjects[i].flags & SOF_PLAYING) && (SoundObjects[i].flags && SOF_PLAY_FOREVER) ) {
				EndSound(SoundObjects[i].soundnum);
				SoundObjects[i].flags &= ~SOF_PLAYING;		// Mark sound as not playing
			}
		}
#ifdef MAC_SHAREWARE
		PauseMusicOnly();
#else
		redbook_pause(1);
#endif
		digi_paused = 1;
	}
}

void digi_stop_all()
{
	int i;

	if (!digi_initialized)	return;

	EndAllSound();
	
// reset the sound objects to be unused.  We stopped the sounds above.

	for (i = 0; i < MAX_SOUND_OBJECTS; i++)
		SoundObjects[i].flags = 0;
}

void digi_set_max_channels(int n)
{
	OSErr err;
	song_resource *song;
	
	digi_max_channels	= n;

	if ( digi_max_channels < 1 ) 
		digi_max_channels = 1;
	if ( digi_max_channels > MAX_SOUND_CHANNELS ) 
		digi_max_channels = MAX_SOUND_CHANNELS;

	if ( !digi_initialized ) return;

	if (digi_midi_song_playing)
		digi_stop_current_song();

	if (midi_volume <= 0)
		ChangeSystemVoices(0, digi_max_channels/2, digi_max_channels);
	else
		ChangeSystemVoices(MAX_MUSIC_CHANNELS, 4 + (digi_max_channels/2), digi_max_channels);
	
	if (digi_last_midi_song != 0)
		digi_play_midi_song(digi_last_midi_song, digi_last_midi_song_loop);

	digi_reset_digi_sounds();
}

void digi_start_sound_object(int i)
{
	int vol;

	if (!digi_initialized) return;
	
	vol = fixmuldiv(SoundObjects[i].volume, digi_volume, F1_0);
	ChangeSoundVolume(SoundObjects[i].soundnum, fixmuldiv(SoundObjects[i].volume, digi_volume, F1_0));
	BeginSoundLoop( SoundObjects[i].soundnum, SOUND_RATE_11k, 1, GetSoundLength(SoundObjects[i].soundnum) );
	ChangeSoundStereoPosition(SoundObjects[i].soundnum, SoundObjects[i].pan);
	SoundObjects[i].flags |= SOF_PLAYING;
}

void digi_get_sound_loc( vms_matrix * listener, vms_vector * listener_pos, int listener_seg, vms_vector * sound_pos, int sound_seg, fix max_volume, int *volume, int *pan, fix max_distance )	
{	  
	vms_vector	vector_to_sound;
	fix angle_from_ear, cosang,sinang;
	fix distance;
	fix path_distance;

	*volume = 0;
	*pan = 0;

	if (!digi_initialized) return;
	
	max_distance = (max_distance*5)/4;		// Make all sounds travel 1.25 times as far.

	//	Warning: Made the vm_vec_normalized_dir be vm_vec_normalized_dir_quick and got illegal values to acos in the fang computation.
	distance = vm_vec_normalized_dir_quick( &vector_to_sound, sound_pos, listener_pos );
		
	if (distance < max_distance )	{
		int num_search_segs = f2i(max_distance/20);
		if ( num_search_segs < 1 ) num_search_segs = 1;

		path_distance = find_connected_distance(listener_pos, listener_seg, sound_pos, sound_seg, num_search_segs, WID_RENDPAST_FLAG );
		//path_distance = distance;
		if ( path_distance > -1 )	{
			*volume = max_volume - (path_distance/f2i(max_distance));
			//mprintf( (0, "Sound path distance %.2f, volume is %d / %d\n", f2fl(distance), *volume, max_volume ));
			if (*volume > 0 )	{
				angle_from_ear = vm_vec_delta_ang_norm(&listener->rvec,&vector_to_sound,&listener->uvec);
				fix_sincos(angle_from_ear,&sinang,&cosang);
				//mprintf( (0, "volume is %.2f\n", f2fl(*volume) ));
				if (Config_channels_reversed) cosang *= -1;
				*pan = fixmuldiv(cosang, 255, F1_0);
			} else {
				*volume = 0;
			}
		}
	}																					  
}

int digi_link_sound_to_object( int soundnum, short objnum, int forever, fix max_volume )
{																									// 10 segs away
	return digi_link_sound_to_object2( soundnum, objnum, forever, max_volume, 256*F1_0  );
}

int digi_link_sound_to_pos( int soundnum, short segnum, short sidenum, vms_vector * pos, int forever, fix max_volume )
{
	return digi_link_sound_to_pos2( soundnum, segnum, sidenum, pos, forever, max_volume, F1_0 * 256 );
}

int digi_link_sound_to_object2( int org_soundnum, short objnum, int forever, fix max_volume, fix  max_distance )
{
	int i,volume,pan;
	object * objp;
	int soundnum;

	soundnum = digi_xlat_sound(org_soundnum);
	
	if (!digi_initialized) return -1;
	if ( max_volume < 0 ) return -1;
	if (soundnum < 0 ) return -1;
	if ((objnum<0)||(objnum>Highest_object_index))
		return -1;

	if ( !forever )	{
		// Hack to keep sounds from building up...
		digi_get_sound_loc( &Viewer->orient, &Viewer->pos, Viewer->segnum, &Objects[objnum].pos, Objects[objnum].segnum, max_volume,&volume, &pan, max_distance );
		digi_play_sample_3d( org_soundnum, pan, volume, 0 );
		return -1;
	}

	for (i=0; i<MAX_SOUND_OBJECTS; i++ )
		if (SoundObjects[i].flags==0)
			break;
	
	if (i==MAX_SOUND_OBJECTS) {
		mprintf((1, "Too many sound objects!\n" ));
		return -1;
	}

	SoundObjects[i].signature=next_signature++;
	SoundObjects[i].flags = SOF_USED | SOF_LINK_TO_OBJ;
	if ( forever )
		SoundObjects[i].flags |= SOF_PLAY_FOREVER;
	SoundObjects[i].link_type.obj.objnum = objnum;
	SoundObjects[i].link_type.obj.objsignature = Objects[objnum].signature;
	SoundObjects[i].max_volume = max_volume;
	SoundObjects[i].max_distance = max_distance;
	SoundObjects[i].volume = 0;
	SoundObjects[i].pan = 0;
	SoundObjects[i].soundnum = (short)soundnum;

	objp = &Objects[SoundObjects[i].link_type.obj.objnum];
	digi_get_sound_loc( &Viewer->orient, &Viewer->pos, Viewer->segnum, 
                       &objp->pos, objp->segnum, SoundObjects[i].max_volume,
                       &SoundObjects[i].volume, &SoundObjects[i].pan, SoundObjects[i].max_distance );

	digi_start_sound_object(i);

	return SoundObjects[i].signature;
}

int digi_link_sound_to_pos2( int org_soundnum, short segnum, short sidenum, vms_vector * pos, int forever, fix max_volume, fix max_distance )
{
	int i, volume, pan;
	int soundnum;

	soundnum = digi_xlat_sound(org_soundnum);

	if (!digi_initialized) return -1;
	if ( max_volume < 0 ) return -1;

	if (soundnum < 0 ) return -1;
	if ((segnum<0)||(segnum>Highest_segment_index))
		return -1;

	if ( !forever )	{
		// Hack to keep sounds from building up...
		digi_get_sound_loc( &Viewer->orient, &Viewer->pos, Viewer->segnum, pos, segnum, max_volume, &volume, &pan, max_distance );
		digi_play_sample_3d( org_soundnum, pan, volume, 0 );
		return -1;
	}

	for (i=0; i<MAX_SOUND_OBJECTS; i++ )
		if (SoundObjects[i].flags==0)
			break;
	
	if (i==MAX_SOUND_OBJECTS) {
		mprintf((1, "Too many sound objects!\n" ));
		return -1;
	}

	SoundObjects[i].signature=next_signature++;
	SoundObjects[i].flags = SOF_USED | SOF_LINK_TO_POS;
	if ( forever )
		SoundObjects[i].flags |= SOF_PLAY_FOREVER;
	SoundObjects[i].link_type.pos.segnum = segnum;
	SoundObjects[i].link_type.pos.sidenum = sidenum;
	SoundObjects[i].link_type.pos.position = *pos;
	SoundObjects[i].soundnum = (short)soundnum;
	SoundObjects[i].max_volume = max_volume;
	SoundObjects[i].max_distance = max_distance;
	SoundObjects[i].volume = 0;
	SoundObjects[i].pan = 0;
	digi_get_sound_loc( &Viewer->orient, &Viewer->pos, Viewer->segnum, 
                       &SoundObjects[i].link_type.pos.position, SoundObjects[i].link_type.pos.segnum, SoundObjects[i].max_volume,
                       &SoundObjects[i].volume, &SoundObjects[i].pan, SoundObjects[i].max_distance );
	
	digi_start_sound_object(i);

	return SoundObjects[i].signature;
}

void digi_sync_sounds()
{
	int i;
	int oldvolume, oldpan;
	SndCommand snd_cmd;

	if (!digi_initialized) return;

	for (i=0; i<MAX_SOUND_OBJECTS; i++ )	{
		if ( SoundObjects[i].flags & SOF_USED )	{
			oldvolume = SoundObjects[i].volume;
			oldpan = SoundObjects[i].pan;

			if ( !(SoundObjects[i].flags & SOF_PLAY_FOREVER) )	{
			 	// Check if its done.
				if (SoundObjects[i].flags & SOF_PLAYING) {
					if ( IsThisSoundFXFinished(SoundObjects[i].soundnum) ) {
						SoundObjects[i].flags = 0;	// Mark as dead, so some other sound can use this sound
						continue;		// Go on to next sound...
					}
				}
			}			
		
			if ( SoundObjects[i].flags & SOF_LINK_TO_POS )	{
				digi_get_sound_loc( &Viewer->orient, &Viewer->pos, Viewer->segnum, 
                                &SoundObjects[i].link_type.pos.position, SoundObjects[i].link_type.pos.segnum, SoundObjects[i].max_volume,
                                &SoundObjects[i].volume, &SoundObjects[i].pan, SoundObjects[i].max_distance );

			} else if ( SoundObjects[i].flags & SOF_LINK_TO_OBJ )	{
				object * objp;
	
				objp = &Objects[SoundObjects[i].link_type.obj.objnum];
		
				if ((objp->type==OBJ_NONE) || (objp->signature!=SoundObjects[i].link_type.obj.objsignature))	{
					// The object that this is linked to is dead, so just end this sound if it is looping.
					if ( (SoundObjects[i].flags & SOF_PLAYING)  && (SoundObjects[i].flags & SOF_PLAY_FOREVER))	{
						EndSound(SoundObjects[i].soundnum);
					}
					SoundObjects[i].flags = 0;	// Mark as dead, so some other sound can use this sound
					continue;		// Go on to next sound...
				} else {
					digi_get_sound_loc( &Viewer->orient, &Viewer->pos, Viewer->segnum, 
	                                &objp->pos, objp->segnum, SoundObjects[i].max_volume,
                                   &SoundObjects[i].volume, &SoundObjects[i].pan, SoundObjects[i].max_distance );
				}
			}

			if (oldvolume != SoundObjects[i].volume) 	{
				if ( SoundObjects[i].volume < 1 )	{
					// Sound is too far away, so stop it from playing.
					if ((SoundObjects[i].flags & SOF_PLAYING)&&(SoundObjects[i].flags & SOF_PLAY_FOREVER))	{
						EndSound(SoundObjects[i].soundnum);
						SoundObjects[i].flags &= ~SOF_PLAYING;		// Mark sound as not playing
					}
				} else {
					if (!(SoundObjects[i].flags & SOF_PLAYING))	{
						digi_start_sound_object(i);
					} else {
						int vol;
						
						vol = fixmuldiv(SoundObjects[i].volume, digi_volume,F1_0);
						ChangeSoundVolume(SoundObjects[i].soundnum, fixmuldiv(SoundObjects[i].volume,digi_volume,F1_0) );
					}
				}
			}
				
			if (oldpan != SoundObjects[i].pan) 	{
				if (SoundObjects[i].flags & SOF_PLAYING) {
					ChangeSoundStereoPosition( SoundObjects[i].soundnum, SoundObjects[i].pan );
				}
			}
		}
	}
}

void digi_kill_sound_linked_to_segment( int segnum, int sidenum, int soundnum )
{
	int i,killed;

	soundnum = digi_xlat_sound(soundnum);

	if (!digi_initialized) return;

	killed = 0;

	for (i=0; i<MAX_SOUND_OBJECTS; i++ )	{
		if ( (SoundObjects[i].flags & SOF_USED) && (SoundObjects[i].flags & SOF_LINK_TO_POS) )	{
			if ((SoundObjects[i].link_type.pos.segnum == segnum) && (SoundObjects[i].soundnum==(short)soundnum ) && (SoundObjects[i].link_type.pos.sidenum==sidenum) )	{
				if ( SoundObjects[i].flags & SOF_PLAYING )	{
					EndSound(SoundObjects[i].soundnum);
				}
				SoundObjects[i].flags = 0;	// Mark as dead, so some other sound can use this sound
				killed++;
			}
		}
	}
	// If this assert happens, it means that there were 2 sounds
	// that got deleted. Weird, get John.
	if ( killed > 1 )	{
		mprintf( (1, "ERROR: More than 1 sounds were deleted from seg %d\n", segnum ));
	}
}

void digi_kill_sound_linked_to_object( int objnum )
{
	int i,killed;

	if (!digi_initialized) return;

	killed = 0;

	for (i=0; i<MAX_SOUND_OBJECTS; i++ )	{
		if ( (SoundObjects[i].flags & SOF_USED) && (SoundObjects[i].flags & SOF_LINK_TO_OBJ ) )	{
			if (SoundObjects[i].link_type.obj.objnum == objnum)	{
				if ( SoundObjects[i].flags & SOF_PLAYING )	{
					EndSound(SoundObjects[i].soundnum);
				}
				SoundObjects[i].flags = 0;	// Mark as dead, so some other sound can use this sound
				killed++;
			}
		}
	}
	// If this assert happens, it means that there were 2 sounds
	// that got deleted. Weird, get John.
	if ( killed > 1 )	{
		mprintf( (1, "ERROR: More than 1 sounds were deleted from object %d\n", objnum ));
	}
}


void digi_close()
{
	int i, sound_num;
	
	if (!digi_initialized)
		return;
	digi_stop_current_song();
	SetMasterVolume(master_save);

// free the sounds that we have registered.

	for (i = 0; i < num_sounds; i++) {
		sound_num = digi_xlat_sound(i);
		if (sound_num != -1)
			FreeSound(i);
	}
	ReleaseRegisteredSounds();
	FinisSoundMusicSystem();

	digi_initialized = 0;
}

void digi_init_sounds()
{
	int i;
	
	if (!digi_initialized) return;
	EndAllSound();			// kill off all current sound effect and music
}

void digi_load_sounds()
{
	int i, sound_num;

	if (!digi_initialized) return;	

	if ( RegisterSounds(sound_list, 1) )
		digi_close();
		
// on low memory conditions, we need to release sounds from the registered
// set so the memory can be freed.  The call to RegisterSounds only registers
// them with halestorm.  We will use LoadSound to actually load those sounds that
// we intend to use.

	for (i = 0; i < MAX_SOUNDS; i++) {
		sound_num = digi_xlat_sound(i);
		if (sound_num != -1)
			LoadSound(sound_num);		// load the sound into memory..hales says this is locked high in heap
	}
}

int digi_init()
{
	OSErr err;
//	CFILE *fp;
	int i;

	if (!use_sounds)
		return -1;
		
	num_sounds = (sizeof(sound_list) / sizeof(short)) - 1;
	
	i = MaxVoiceLoad();
	err = InitSoundMusicSystem(MAX_MUSIC_CHANNELS, 4 + (digi_max_channels/2), digi_max_channels, digi_sound_quality);
//	err = InitSoundMusicSystem(MAX_MUSIC_CHANNELS, 10, 16, digi_sound_quality);
	if (err != noErr)
		return -1;
	master_save = GetMasterVolume();
	if (master_save < 0)
		master_save = 0;
	else if ( master_save > 255 )
		master_save = 255;
		
#ifdef MAC_SHAREWARE
	PurgeSongs(1);
	LockSongs(0);
#else
	init_redbook();
#endif

 	digi_initialized = 1;
	
// set volumes and then out of here..

	digi_set_master_volume(Config_master_volume);
	digi_set_volume(digi_volume, midi_volume);
	digi_reset_digi_sounds();
	atexit(digi_close);

	return 0;
}


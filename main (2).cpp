
#include "mbed.h"
#include "SongPlayer.h"
#include <cstdio>
float note[18]= {1568.0,1396.9,1568.0,1396.9,1568.0,1396.9,1568.0,1396.9,1568.0,1396.9,
                 1568.0,1396.9,1568.0,1396.9,1568.0,1396.9,1568.0, 0.0
                };
float duration[18]= {0.48,0.48,0.48,0.48,0.48,0.48,0.48,0.48,0.48,0.48,0.48,0.48,
                     0.48,0.48,0.48,0.48,0.48, 0.0
                    };
Serial blue(p28, p27);
int main()
{
    SongPlayer mySpeaker(p26);
    char bnum;
    while(1) {
        if (blue.getc() == '!') {
            if (blue.getc() == 'B') {
                bnum = blue.getc();
                if (bnum == '1') {
                    mySpeaker.PlaySong(note,duration);
                }
            }
        }       
    }
}


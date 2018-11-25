#pragma once

#include "Note.h"
#include "Octave.h"
#include "Volume.h"
#include "InstrumentId.h"

struct TunePart
{
	Note note;
	Octave octave;
	Volume volume;
	InstrumentId instrument;
};
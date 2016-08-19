#pragma once
//ERROR DWORD must be a simple type or resolve to one... 
// it's literally a typedef'd UNSIGNED LONG.
enum class accepted_infoIDs : unsigned long {
	ifil = 'ifil',
	isng = 'isng',
	inam = 'INAM',

	irom = 'irom',
	iver = 'iver',
	icrd = 'ICRD',
	ieng = 'IENG',
	iprd = 'IPRD',
	icop = 'ICOP',
	icmt = 'ICMT',
	isft = 'ISFT'
};

//specsheet only details one.
enum class accepted_sdtaIDs : unsigned long {
	smpl = 'smpl'
};

enum class accepted_pdtaIDs : unsigned long {
	phdr = 'phdr',
	pbag = 'pbag',
	pmod = 'pmod',
	pgen = 'pgen',
	inst = 'inst',
	ibag = 'ibag',
	imod = 'imod',
	igen = 'igen',
	shdr = 'shdr'
};

enum class accepted_formIDs : unsigned long {
	info = 'INFO',
	sdta = 'sdta',
	pdta = 'pdta'
};

//WEIRD ENDIANNESS THINGS GOING ON,
//so rather than have a function call for byteswapping, why not
//just make a list of byteswapped id's?
enum class bswapped_infoIDs : unsigned long {
	ifil = 'lifi',
	isng = 'gnsi',
	inam = 'MANI',

	irom = 'mori',
	iver = 'revi',
	icrd = 'DRCI',
	ieng = 'GNEI',
	iprd = 'DRPI',
	icop = 'POCI',
	icmt = 'TMCI',
	isft = 'TFSI'
};

enum class bswapped_pdtaIDs : unsigned long {
	phdr = 'rdhp',
	pbag = 'gabp',
	pmod = 'domp',
	pgen = 'negp',
	inst = 'tsni',
	ibag = 'gabi',
	imod = 'domi',
	igen = 'negi',
	shdr = 'rdhs'
};

enum class bswapped_sdtaIDs : unsigned long {
	smpl = 'lpms'
};

enum class byteswapped_formIDs : unsigned long {
	info = 'OFNI',
	sdta = 'atds',
	pdta = 'atdp'
};

enum class SFSampleLink : unsigned short
{
	monoSample = 1,
	rightSample = 2,
	leftSample = 4,
	linkedSample = 8,
	RomMonoSample = 0x8001,
	RomRightSample = 0x8002,
	RomLeftSample = 0x8004,
	RomLinkedSample = 0x8008
};

enum class modTransform{
	lineart = 0,
	abst = 2
};

enum class mod_flags {
	linear = 0,
	concave = 1,
	convex = 2,
	swtch = 3
};

enum class mod_source{
	none = 0,
	note_on_vel = 2,
	note_on_key_num = 3,
	poly_pressure = 10,
	chan_pressure = 13,
	pitch_wheel = 14,
	pitch_wheel_sens = 16,
	link = 127
};

enum class SFModulator
{
	_null = 0,
	none = 0,
	noteOnVelocity = 1,
	noteOnKey = 2,
	polyPressure = 10,
	chnPressure = 13,
	pitchWheel = 14,
	ptchWeelSensivity = 16
};

enum class SFGenerator : short
{
	null = 0,
	startAddrsOffset = 0,
	endAddrsOffset = 1,
	startloopAddrsOffset = 2,
	endloopAddrsOffset = 3,
	startAddrsCoarseOffset = 4,
	modLfoToPitch = 5,
	vibLfoToPitch = 6,
	modEnvToPitch = 7,
	initialFilterFc = 8,
	initialFilterQ = 9,
	modLfoToFilterFc = 10,
	modEnvToFilterFc = 11,
	endAddrsCoarseOffset = 12,
	modLfoToVolume = 13,
	chorusEffectsSend = 15,
	reverbEffectsSend = 16,
	pan = 17,
	delayModLFO = 21,
	freqModLFO = 22,
	delayVibLFO = 23,
	freqVibLFO = 24,
	delayModEnv = 25,
	attackModEnv = 26,
	holdModEnv = 27,
	decayModEnv = 28,
	sustainModEnv = 29,
	releaseModEnv = 30,
	keynumToModEnvHold = 31,
	keynumToModEnvDecay = 32,
	delayVolEnv = 33,
	attackVolEnv = 34,
	holdVolEnv = 35,
	decayVolEnv = 36,
	sustainVolEnv = 37,
	releaseVolEnv = 38,
	keynumToVolEnvHold = 39,
	keynumToVolEnvDecay = 40,
	instrument = 41,
	keyRange = 43,
	velRange = 44,
	startloopAddrsCoarseOffset = 45,
	keynum = 46,
	velocity = 47,
	initialAttenuation = 48,
	endloopAddrsCoarseOffset = 50,
	coarseTune = 51,
	fineTune = 52,
	sampleID = 53,
	sampleModes = 54,
	scaleTuning = 56,
	exclusiveClass = 57,
	overridingRootKey = 58,
	endOper = 60
};

enum class SFTransform
{
	null = 0,
	linear = 0,
	concave = 1,
	convex = 2
};
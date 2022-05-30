#include "stdafx.h"
// includes
#define INITGUID
#include <OBJBASE.H>
#include <stdio.h>
#include <ddraw.h>
#include <dinput.h>
#include <mmsystem.h>
#include <dsound.h>

#define MIN_POS		0.0
#define MAX_POS		50000.0
#define LEFT		1
#define RIGHT		2
#define NVB_SIZE      6
#define STARTBG      1
#define OPTIONSBG      2
#define CREDITSBG      3

#define SafeRelease(x) if (x) { x->Release(); x=NULL;}

int direction=RIGHT;
int select=1;
int clicks=0;
int startbgnum=1;
int rockcnt=0;
double clev=1;
bool bInit=FALSE;
bool bHurt=FALSE;
bool bInvis=FALSE;
bool bFiring=FALSE;
bool bPunch=FALSE;
bool bAnimDone=TRUE;
bool bJump=FALSE;
bool bJumpDone=TRUE;
bool bFall=FALSE;
bool bRun=FALSE;
bool bClimb=FALSE;
bool bRelease=TRUE;
bool bStartLev=FALSE;
bool bScroll=FALSE;
bool bSlant=FALSE;
bool bStart=FALSE;
bool bStep=FALSE;
bool bStartstart=FALSE;
bool bLadder=FALSE;
bool bBlink=FALSE;
bool bBlitMenu=FALSE;
bool bMusic=FALSE;
bool bKeyed=FALSE;
bool bPushD=FALSE;
bool bPushU=FALSE;
DWORD start_time;
DWORD jump_time;
DWORD fall_time;
DWORD run_time;
DWORD blink_time;
DWORD rest_time;
DWORD idle_time;
DWORD cota_time;
DWORD cota_time2;
DWORD spikea_time;
DWORD spikea_time2;
DWORD rocka_time;
DWORD hurt_time;
DWORD invis_time;
RECT rcRect;
RECT rc2Rect;
RECT amRect;
RECT flipRect;
RECT flip2Rect;
RECT normRect;
RECT norm2Rect;
RECT hRect;
RECT h2Rect;
RECT hudRect;
RECT sRect;
RECT s2Rect;
RECT l1Rect;
RECT cotRect;
RECT cotColRect;
RECT ShogoColRect;
RECT cot2Rect;
RECT spikeRect;
RECT spikeColRect;
RECT spike2Rect;
RECT rockRect;
RECT rockColRect;
RECT rock2Rect;

class Character
{
public:
	double health;
	double curammo;
	double ammobullet;
	double ammoenergy;
	double special;
	double x;
	double y;
};

class Enemy
{
public:
	double health;
	int x;
	int y;
	bool doa;
	bool adead;
};

class Projectile
{
public:
	int x;
	int y;
	bool doa;
	bool adead;
};

Character Shogo;
Enemy CotA;
Enemy SpikeA;
Projectile RockA;

// dx pointers
LPDIRECTDRAW7			lpDD=NULL;
LPDIRECTDRAWSURFACE7	lpDDSPrimary=NULL;
LPDIRECTDRAWSURFACE7	lpDDSBack=NULL;

LPDIRECTDRAWSURFACE7	back_surf=NULL;
LPDIRECTDRAWSURFACE7	boss1=NULL;
LPDIRECTDRAWSURFACE7	bossbg=NULL;
LPDIRECTDRAWSURFACE7	lev1=NULL;
LPDIRECTDRAWSURFACE7	lev2=NULL;
LPDIRECTDRAWSURFACE7	load1=NULL;
LPDIRECTDRAWSURFACE7	load2=NULL;
LPDIRECTDRAWSURFACE7	load3=NULL;
LPDIRECTDRAWSURFACE7	load4=NULL;
LPDIRECTDRAWSURFACE7	ShogoStand=NULL;
LPDIRECTDRAWSURFACE7	ShogoIdle=NULL;
LPDIRECTDRAWSURFACE7	ShogoRun1=NULL;
LPDIRECTDRAWSURFACE7	ShogoRun2=NULL;
LPDIRECTDRAWSURFACE7	ShogoRun3=NULL;
LPDIRECTDRAWSURFACE7	ShogoRun4=NULL;
LPDIRECTDRAWSURFACE7	ShogoRun5=NULL;
LPDIRECTDRAWSURFACE7	ShogoRun6=NULL;
LPDIRECTDRAWSURFACE7	ShogoRun7=NULL;
LPDIRECTDRAWSURFACE7	ShogoRun8=NULL;
LPDIRECTDRAWSURFACE7	ShogoRun9=NULL;
LPDIRECTDRAWSURFACE7	ShogoRun10=NULL;
LPDIRECTDRAWSURFACE7	ShogoHit1=NULL;
LPDIRECTDRAWSURFACE7	ShogoHit2=NULL;
LPDIRECTDRAWSURFACE7	ShogoHit3=NULL;
LPDIRECTDRAWSURFACE7	ShogoHit4=NULL;
LPDIRECTDRAWSURFACE7	ShogoJump1=NULL;
LPDIRECTDRAWSURFACE7	ShogoJump2=NULL;
LPDIRECTDRAWSURFACE7	ShogoJump3=NULL;
LPDIRECTDRAWSURFACE7	ShogoJump4=NULL;
LPDIRECTDRAWSURFACE7	ShogoClimb1=NULL;
LPDIRECTDRAWSURFACE7	ShogoClimb2=NULL;
LPDIRECTDRAWSURFACE7	ShogoClimb3=NULL;
LPDIRECTDRAWSURFACE7	ShogoClimb4=NULL;
LPDIRECTDRAWSURFACE7	ShogoM4Run1=NULL;
LPDIRECTDRAWSURFACE7	ShogoM4Run2=NULL;
LPDIRECTDRAWSURFACE7	ShogoM4Run3=NULL;
LPDIRECTDRAWSURFACE7	ShogoM4Run4=NULL;
LPDIRECTDRAWSURFACE7	ShogoM4Run5=NULL;
LPDIRECTDRAWSURFACE7	ShogoM4Run6=NULL;
LPDIRECTDRAWSURFACE7	ShogoM4Run7=NULL;
LPDIRECTDRAWSURFACE7	ShogoM4Run8=NULL;
LPDIRECTDRAWSURFACE7	ShogoInjure1=NULL;
LPDIRECTDRAWSURFACE7	ShogoInjure2=NULL;
LPDIRECTDRAWSURFACE7	ShogoInjure3=NULL;
LPDIRECTDRAWSURFACE7	ShogoFall1=NULL;
LPDIRECTDRAWSURFACE7	ShogoFall2=NULL;
LPDIRECTDRAWSURFACE7	ShogoFall3=NULL;
LPDIRECTDRAWSURFACE7	cot1=NULL;
LPDIRECTDRAWSURFACE7	cot2=NULL;
LPDIRECTDRAWSURFACE7	cot3=NULL;
LPDIRECTDRAWSURFACE7	cot4=NULL;
LPDIRECTDRAWSURFACE7	cot5=NULL;
LPDIRECTDRAWSURFACE7	cot6=NULL;
LPDIRECTDRAWSURFACE7	spike1=NULL;
LPDIRECTDRAWSURFACE7	spike2=NULL;
LPDIRECTDRAWSURFACE7	spike3=NULL;
LPDIRECTDRAWSURFACE7	spike4=NULL;
LPDIRECTDRAWSURFACE7	spike5=NULL;
LPDIRECTDRAWSURFACE7	spike6=NULL;
LPDIRECTDRAWSURFACE7	spike7=NULL;
LPDIRECTDRAWSURFACE7	spike8=NULL;
LPDIRECTDRAWSURFACE7	spike9=NULL;
LPDIRECTDRAWSURFACE7	explosion1=NULL;
LPDIRECTDRAWSURFACE7	explosion2=NULL;
LPDIRECTDRAWSURFACE7	explosion3=NULL;
LPDIRECTDRAWSURFACE7	explosion4=NULL;
LPDIRECTDRAWSURFACE7	explosion5=NULL;
LPDIRECTDRAWSURFACE7	explosion6=NULL;
LPDIRECTDRAWSURFACE7	explosion7=NULL;
LPDIRECTDRAWSURFACE7	explosion8=NULL;
LPDIRECTDRAWSURFACE7	explosion9=NULL;
LPDIRECTDRAWSURFACE7	r1=NULL;
LPDIRECTDRAWSURFACE7	r2=NULL;
LPDIRECTDRAWSURFACE7	r3=NULL;
LPDIRECTDRAWSURFACE7	r4=NULL;
LPDIRECTDRAWSURFACE7	r5=NULL;
LPDIRECTDRAWSURFACE7	r6=NULL;
LPDIRECTDRAWSURFACE7	r7=NULL;
LPDIRECTDRAWSURFACE7	cotexplo1=NULL;
LPDIRECTDRAWSURFACE7	cotexplo2=NULL;
LPDIRECTDRAWSURFACE7	cotexplo3=NULL;
LPDIRECTDRAWSURFACE7	cotexplo4=NULL;
LPDIRECTDRAWSURFACE7	cotexplo5=NULL;
LPDIRECTDRAWSURFACE7	cotexplo6=NULL;
LPDIRECTDRAWSURFACE7	cotexplo7=NULL;
LPDIRECTDRAWSURFACE7	hbar=NULL;
LPDIRECTDRAWSURFACE7	hud=NULL;
LPDIRECTDRAWSURFACE7	sbar=NULL;
LPDIRECTDRAWSURFACE7	ammoico=NULL;
LPDIRECTDRAWSURFACE7	startbg=NULL;
LPDIRECTDRAWSURFACE7	creditsbg=NULL;
LPDIRECTDRAWSURFACE7	start=NULL;
LPDIRECTDRAWSURFACE7	options=NULL;
LPDIRECTDRAWSURFACE7	credits=NULL;
LPDIRECTDRAWSURFACE7	sexit=NULL;
LPDIRECTDRAWSURFACE7	sstart=NULL;
LPDIRECTDRAWSURFACE7	soptions=NULL;
LPDIRECTDRAWSURFACE7	scredits=NULL;
LPDIRECTDRAWSURFACE7	ssexit=NULL;
LPDIRECTDRAWSURFACE7	yokotyp1=NULL;
LPDIRECTDRAWSURFACE7	yokotyp2=NULL;
LPDIRECTDRAWSURFACE7	yokotyp3=NULL;
LPDIRECTDRAWSURFACE7	yokotyp4=NULL;
LPDIRECTDRAWSURFACE7	yokotyp5=NULL;
LPDIRECTDRAWSURFACE7	yokotyp6=NULL;
LPDIRECTDRAWSURFACE7	yokotyp7=NULL;
LPDIRECTDRAWSURFACE7	yokotyp8=NULL;

LPDIRECTINPUT	lpDI;
LPDIRECTINPUTDEVICE lpDIKey;

LPDIRECTSOUND lpDS;
typedef struct VOC_FILE_TYP
        {
        int sample_rate; // sample rate of sound
        int length;      // length of sound data
        LPDIRECTSOUNDBUFFER lpDSBuffer; // ptr to sound buffer
        } VOC_FILE, *VOC_FILE_PTR;

WAVEFORMATEX        pcmwf;          // generic waveformat structure

VOC_FILE work_voc;
VOC_FILE type_voc;
VOC_FILE lev1_voc;
VOC_FILE steps_voc;
VOC_FILE land_voc;
VOC_FILE explo1_voc;
VOC_FILE menu1_voc;
VOC_FILE menu2_voc;
VOC_FILE electric_voc;
DSBUFFERDESC	dsbd;

DWORD KeyColor;

int x_pos=0;
int mapx_pos=0;
int mapendx_pos=640;
int x_min=0;
int x_max=6700;
int backx_pos=0;
int backwidth=640;
int y_pos=210;
int floory=210;


const char *ErrStr=NULL;

const char Err_Reg_Class[]			= "Error Registering Window Class";
const char Err_Create_Win[]			= "Error Creating Window";
const char Err_DirectDrawCreate[]	= "DirectDrawCreate FAILED";
const char Err_Query[]				= "QueryInterface FAILED";
const char Err_Coop[]				= "SetCooperativeLevel FAILED";
const char Err_CreateSurf[]			= "CreateSurface FAILED";
const char Err_LoadBMP[]			= "Error Loading Image";
const char Err_DispMode[]			= "Error Setting Display Mode";
const char Err_LoadImage[]			= "Error Loading Image"; 
const char Err_DirectInputCreate[]  = "DirectInputCreate FAILED";
const char Err_CreateDevice[]			= "Error Creating DI Device"; 
const char Err_SetCoopInput[]			= "Error Setting DI Coop Level";
const char Err_SetDataFormat[]		= "Error Setting Data Format";
const char Err_Acquire[]			= "Error Acquiring Input Device";
const char Err_GetState[]			= "Error Getting Device State";
const char Err_DDERR_ALREADYINITIALIZED[] = "DDERR_ALREADYINITIALIZED"; 
const char Err_DDERR_BLTFASTCANTCLIP[]	= "BLTFASTCANTCLIP";
const char Err_DDERR_CANNOTATTACHSURFACE[]= "CANNOTATTACHSURFACE";
const char Err_DDERR_CANNOTDETACHSURFACE[]= "CANNOTDETACHSURFACE";
const char Err_DDERR_CANTCREATEDC[]		= "CANTCREATEDC";
const char Err_DDERR_CANTDUPLICATE[]		= "CANTDUPLICATE";
const char Err_DDERR_CANTLOCKSURFACE[]	= "CANTLOCKSURFACE";
const char Err_DDERR_CANTPAGELOCK[]		= "CANTPAGELOCK";
const char Err_DDERR_CANTPAGEUNLOCK[]		= "CANTPAGEUNLOCK";
const char Err_DDERR_CLIPPERISUSINGHWND[] = "CLIPPERISUSINGHWD";
const char Err_DDERR_COLORKEYNOTSET[]     = "COLORKEYNOTSET";
const char Err_DDERR_CURRENTLYNOTAVAIL[]  = "CURRENTLYNOTAVAIL";
const char Err_DDERR_DDSCAPSCOMPLEXREQUIRED[] = "DDSCAPSCOMPLEXREQUIRED";
const char Err_DDERR_DCALREADYCREATED[]	= "DCALREADYCREATED";
const char Err_DDERR_DEVICEDOESNTOWNSURFACE[] = "DEVICEDOESNTOWNSURFACE" ;
const char Err_DDERR_DIRECTDRAWALREADYCREATED[] = "DIRECTDRAWALREADYCREATED";
const char Err_DDERR_EXCEPTION[]			= "EXCEPTION";
const char Err_DDERR_EXCLUSIVEMODEALREADYSET[] = "EXCLUSIVEMOVEALREADYSET";
const char Err_DDERR_EXPIRED[]			= "EXPIRED";
const char Err_DDERR_GENERIC[]			= "GENERIC";
const char Err_DDERR_HEIGHTALIGN[]		= "HEIGHTALIGN";
const char Err_DDERR_HWNDALREADYSET[]		= "HWNDALREADYSET";
const char Err_DDERR_HWNDSUBCLASSED[]		= "HWNDSUBCLASSED";
const char Err_DDERR_IMPLICITLYCREATED[]  = "IMPLICITYCREATED";
const char Err_DDERR_INCOMPATIBLEPRIMARY[] = "INCOMPATIBLEPRIMARY";
const char Err_DDERR_INVALIDCAPS[]		= "INVALIDCAPS";
const char Err_DDERR_INVALIDCLIPLIST[]	= "INVALIDCLIPLIST";
const char Err_DDERR_INVALIDDIRECTDRAWGUID[] = "INVALIDDIRECTDRAWGUID";
const char Err_DDERR_INVALIDMODE[]		= "INVALIDMODE";
const char Err_DDERR_INVALIDOBJECT[]		= "INVAIDOBJECT";
const char Err_DDERR_INVALIDPARAMS[]	= "INVALIDPARAMS";
const char Err_DDERR_INVALIDPIXELFORMAT[] = "INVLAIDPIXELFORMAT";
const char Err_DDERR_INVALIDPOSITION[]	= "INVALIDPOSITION";
const char Err_DDERR_INVALIDRECT[]		= "INVALIDRECT";
const char Err_DDERR_INVALIDSTREAM[]		= "INVLAIDSTREAM";
const char Err_DDERR_INVALIDSURFACETYPE[] = "INVALIDSURFACETYPE";
const char Err_DDERR_LOCKEDSURFACES[]		= "LOCKEDSURFACES";
const char Err_DDERR_MOREDATA[]			= "MOREDATA";
const char Err_DDERR_NEWMODE[]			= "NEWMODE";
const char Err_DDERR_NO3D[]				= "NO3D";
const char Err_DDERR_NOALPHAHW[]			= "NOALPHAW";
const char Err_DDERR_NOBLTHW[]			= "NOBLITHW";
const char Err_DDERR_NOCLIPLIST[]			= "NOCLIPLIST";
const char Err_DDERR_NOCLIPPERATTACHED[]	= "NOCLIPPERATTACHED";
const char Err_DDERR_NOCOLORCONVHW[]		= "NOCOLORCONVHW";
const char Err_DDERR_NOCOLORKEY[]			= "NOCOLORKEY";
const char Err_DDERR_NOCOLORKEYHW[]		= "NOCOLORKEYHW";
const char Err_DDERR_NOCOOPERATIVELEVELSET[] = "NOCOOPERATIVELEVELSET";
const char Err_DDERR_NODC[]				= "NODC";
const char Err_DDERR_NODDROPSHW[]			= "NODDROPSHW";
const char Err_DDERR_NODIRECTDRAWHW[]		= "NOIDIRECTDRAWHW";
const char Err_DDERR_NODIRECTDRAWSUPPORT[] = "NODIRECTDRAWSUPPORT";
const char Err_DDERR_NODRIVERSUPPORT[]	= "NODRIVESUPPORT";
const char Err_DDERR_NOEMULATION[]		= "NOEMULATION";
const char Err_DDERR_NOEXCLUSIVEMODE[]	= "NOEXCLUSIVEMODE";
const char Err_DDERR_NOFLIPHW[]			= "NOFLIPHW";
const char Err_DDERR_NOFOCUSWINDOW[]		= "NOFOCUSWINDOW";
const char Err_DDERR_NOGDI[]				= "NOGDI";
const char Err_DDERR_NOHWND[]				= "NOHWND";
const char Err_DDERR_NOMIPMAPHW[]			= "NOMIPMAPHW";
const char Err_DDERR_NOMIRRORHW[]			= "NOMIRRORHW";
const char Err_DDERR_NOMONITORINFORMATION[] = "NOMONITORINFORMATION";
const char Err_DDERR_NONONLOCALVIDMEM[]	= "NONONLOCALVIDEMEM";
const char Err_DDERR_NOOPTIMIZEHW[]		= "NOOPTIMIZEHW";
const char Err_DDERR_NOOVERLAYDEST[]		= "NOOVERLAYDEST";
const char Err_DDERR_NOOVERLAYHW[]		= "NOOVERLAYHW";
const char Err_DDERR_NOPALETTEATTACHED[]	= "NOPALETTEATTACHED";
const char Err_DDERR_NOPALETTEHW[]		= "NOPALETTEHW";
const char Err_DDERR_NORASTEROPHW[]		= "NORASTEROPHW";
const char Err_DDERR_NOROTATIONHW[]		= "NOROTATIONHW";
const char Err_DDERR_NOSTEREOHARDWARE[]	= "NOSTEREOHARDWARE";
const char Err_DDERR_NOSTRETCHHW[]		= "NOSTRETCHHW";
const char Err_DDERR_NOSURFACELEFT[]		= "NOSURFACELEFT";
const char Err_DDERR_NOT4BITCOLOR[]		= "NOT4BITCOLOR";
const char Err_DDERR_NOT4BITCOLORINDEX[]	= "NOT4BITCOLORINDEX";
const char Err_DDERR_NOT8BITCOLOR[]		= "NOT8BITCOLOR";
const char Err_DDERR_NOTAOVERLAYSURFACE[]	= "NOTAOVERLAYSURFACE";
const char Err_DDERR_NOTEXTUREHW[]		= "NOTEXTUREHW";
const char Err_DDERR_NOTFLIPPABLE[]		= "NOTLFIPPABLE";
const char Err_DDERR_NOTFOUND[]			= "NOTFOUND";
const char Err_DDERR_NOTINITIALIZED[]		= "NOTINITIALIZE";
const char Err_DDERR_NOTLOADED[]			= "NOTLOADED";
const char Err_DDERR_NOTLOCKED[]			= "NOTLOCKED";
const char Err_DDERR_NOTPAGELOCKED[]		= "NOTPAGELOCKED";
const char Err_DDERR_NOTPALETTIZED[]		= "NOTPALETTIZED";
const char Err_DDERR_NOVSYNCHW[]			= "NOVSYNCHW";
const char Err_DDERR_NOZBUFFERHW[]		= "NOZBUFFERHW";
const char Err_DDERR_NOZOVERLAYHW[]		= "NOZOVERLAYHW";
const char Err_DDERR_OUTOFCAPS[]			= "OUTOFCAPS";
const char Err_DDERR_OUTOFMEMORY[]		= "OUTOFMEMORY";
const char Err_DDERR_OUTOFVIDEOMEMORY[]	= "OUTOFVIDEOMEMORY";
const char Err_DDERR_OVERLAPPINGRECTS[]	= "OVERLAPPINGRECTS";
const char Err_DDERR_OVERLAYCANTCLIP[]	= "OVERLAYCANTCLIP";
const char Err_DDERR_OVERLAYCOLORKEYONLYONEACTIVE[] = " OVERLAYCOLORKEYONEACTIVE";
const char Err_DDERR_OVERLAYNOTVISIBLE[]  = "OVERLAYNOTVISIBLE";
const char Err_DDERR_PALETTEBUSY[]		= "PALETTEBUSY";
const char Err_DDERR_PRIMARYSURFACEALREADYEXISTS[] = "PRIMARYSURFACEALREADYEXISTS";
const char Err_DDERR_REGIONTOOSMALL[]		= "REGIONTOOSMALL";
const char Err_DDERR_SURFACEALREADYATTACHED[] = "SURFACEALREADYATTACHED";
const char Err_DDERR_SURFACEALREADYDEPENDENT[] = "SURFACEALREADYDEPENDENT";
const char Err_DDERR_SURFACEBUSY[]		= "SURFACEBUSY";
const char Err_DDERR_SURFACEISOBSCURED[]	= "SURFACEISOBSCURED";
const char Err_DDERR_SURFACELOST[]		= "SURFACELOST";
const char Err_DDERR_SURFACENOTATTACHED[] = "SURFACENOTATTACHED";
const char Err_DDERR_TESTFINISHED[]		= "TESTFINISHED";
const char Err_DDERR_TOOBIGHEIGHT[]		= "TOOBIGHEIGHT";
const char Err_DDERR_TOOBIGSIZE[]			= "TOOBIGSIZE";
const char Err_DDERR_TOOBIGWIDTH[]		= "TOOBIGWIDTH";
const char Err_DDERR_UNSUPPORTED[]		= "UNSUPPORTED";
const char Err_DDERR_UNSUPPORTEDFORMAT[]	= "UNSUPPORTEDFORMAT";
const char Err_DDERR_UNSUPPORTEDMASK[]	= "UNSUPPORTEDMASK";
const char Err_DDERR_UNSUPPORTEDMODE[]	= "UNSUPPORTEDMODE";
const char Err_DDERR_VERTICALBLANKINPROGRESS[] = "VERTICALBLANKINPROGRESS";
const char Err_DDERR_VIDEONOTACTIVE[]		= "VIDEONOTACTIVE";
const char Err_DDERR_WASSTILLDRAWING[]	= "WASSTILLDRAWING";
const char Err_DDERR_WRONGMODE[]			= "WRONGMODE";
const char Err_DDERR_XALIGN[]				= "XALIGN";



static char szClass[]="Yokotek";
static char szCaption[]="Yokotek: Free Your Mind";

const char * checkerror(HRESULT ddrval)
{
if (ddrval==DDERR_ALREADYINITIALIZED) ErrStr=Err_DDERR_ALREADYINITIALIZED;
if (ddrval==DDERR_BLTFASTCANTCLIP) ErrStr=Err_DDERR_BLTFASTCANTCLIP;
if (ddrval==DDERR_CANNOTATTACHSURFACE) ErrStr=Err_DDERR_CANNOTATTACHSURFACE;
if (ddrval==DDERR_CANNOTDETACHSURFACE) ErrStr=Err_DDERR_CANNOTDETACHSURFACE;
if (ddrval==DDERR_CANTCREATEDC) ErrStr=Err_DDERR_CANTCREATEDC;
if (ddrval==DDERR_CANTDUPLICATE) ErrStr=Err_DDERR_CANTDUPLICATE;
if (ddrval==DDERR_CANTLOCKSURFACE) ErrStr=Err_DDERR_CANTLOCKSURFACE;
if (ddrval==DDERR_CANTPAGELOCK) ErrStr=Err_DDERR_CANTPAGELOCK;
if (ddrval==DDERR_CANTPAGEUNLOCK) ErrStr=Err_DDERR_CANTPAGEUNLOCK;
if (ddrval==DDERR_CLIPPERISUSINGHWND) ErrStr=Err_DDERR_CLIPPERISUSINGHWND;
if (ddrval==DDERR_COLORKEYNOTSET) ErrStr=Err_DDERR_COLORKEYNOTSET;
if (ddrval==DDERR_CURRENTLYNOTAVAIL) ErrStr=Err_DDERR_CURRENTLYNOTAVAIL;
if (ddrval==DDERR_DDSCAPSCOMPLEXREQUIRED) ErrStr=Err_DDERR_DDSCAPSCOMPLEXREQUIRED;
if (ddrval==DDERR_DCALREADYCREATED) ErrStr=Err_DDERR_DCALREADYCREATED;
if (ddrval==DDERR_DEVICEDOESNTOWNSURFACE)ErrStr=Err_DDERR_DEVICEDOESNTOWNSURFACE;
if (ddrval==DDERR_DIRECTDRAWALREADYCREATED)ErrStr=Err_DDERR_DIRECTDRAWALREADYCREATED;
if (ddrval==DDERR_EXCEPTION)ErrStr=Err_DDERR_EXCEPTION;
if (ddrval==DDERR_EXCLUSIVEMODEALREADYSET)ErrStr=Err_DDERR_EXCLUSIVEMODEALREADYSET;
if (ddrval==DDERR_EXPIRED)ErrStr=Err_DDERR_EXPIRED;
if (ddrval==DDERR_GENERIC)ErrStr=Err_DDERR_GENERIC;
if (ddrval==DDERR_HEIGHTALIGN)ErrStr=Err_DDERR_HEIGHTALIGN;
if (ddrval==DDERR_HWNDALREADYSET)ErrStr=Err_DDERR_HWNDALREADYSET;
if (ddrval==DDERR_HWNDSUBCLASSED)ErrStr=Err_DDERR_HWNDSUBCLASSED;
if (ddrval==DDERR_IMPLICITLYCREATED)ErrStr=Err_DDERR_IMPLICITLYCREATED;
if (ddrval==DDERR_INCOMPATIBLEPRIMARY)ErrStr=Err_DDERR_INCOMPATIBLEPRIMARY;
if (ddrval==DDERR_INVALIDCAPS)ErrStr=Err_DDERR_INVALIDCAPS;
if (ddrval==DDERR_INVALIDCLIPLIST)ErrStr=Err_DDERR_INVALIDCLIPLIST;
if (ddrval==DDERR_INVALIDDIRECTDRAWGUID)ErrStr=Err_DDERR_INVALIDDIRECTDRAWGUID;
if (ddrval==DDERR_INVALIDMODE)ErrStr=Err_DDERR_INVALIDMODE;
if (ddrval==DDERR_INVALIDOBJECT)ErrStr=Err_DDERR_INVALIDOBJECT;
if (ddrval==DDERR_INVALIDPARAMS)ErrStr=Err_DDERR_INVALIDPARAMS;
if (ddrval==DDERR_INVALIDPIXELFORMAT)ErrStr=Err_DDERR_INVALIDPIXELFORMAT;
if (ddrval==DDERR_INVALIDPOSITION)ErrStr=Err_DDERR_INVALIDPOSITION;
if (ddrval==DDERR_INVALIDRECT)ErrStr=Err_DDERR_INVALIDRECT;
if (ddrval==DDERR_INVALIDSTREAM)ErrStr=Err_DDERR_INVALIDSTREAM;
if (ddrval==DDERR_INVALIDSURFACETYPE)ErrStr=Err_DDERR_INVALIDSURFACETYPE;
if (ddrval==DDERR_LOCKEDSURFACES)ErrStr=Err_DDERR_LOCKEDSURFACES;
if (ddrval==DDERR_MOREDATA)ErrStr=Err_DDERR_MOREDATA;
if (ddrval==DDERR_NEWMODE)ErrStr=Err_DDERR_NEWMODE;
if (ddrval==DDERR_NO3D)ErrStr=Err_DDERR_NO3D;
if (ddrval==DDERR_NOALPHAHW)ErrStr=Err_DDERR_NOALPHAHW;
if (ddrval==DDERR_NOBLTHW)ErrStr=Err_DDERR_NOBLTHW;
if (ddrval==DDERR_NOCLIPLIST)ErrStr=Err_DDERR_NOCLIPLIST;
if (ddrval==DDERR_NOCLIPPERATTACHED)ErrStr=Err_DDERR_NOCLIPPERATTACHED;
if (ddrval==DDERR_NOCOLORCONVHW)ErrStr=Err_DDERR_NOCOLORCONVHW;
if (ddrval==DDERR_NOCOLORKEY)ErrStr=Err_DDERR_NOCOLORKEY;
if (ddrval==DDERR_NOCOLORKEYHW)ErrStr=Err_DDERR_NOCOLORKEYHW;
if (ddrval==DDERR_NOCOOPERATIVELEVELSET)ErrStr=Err_DDERR_NOCOOPERATIVELEVELSET;
if (ddrval==DDERR_NODC)ErrStr=Err_DDERR_NODC;
if (ddrval==DDERR_NODDROPSHW)ErrStr=Err_DDERR_NODDROPSHW;
if (ddrval==DDERR_NODIRECTDRAWHW)ErrStr=Err_DDERR_NODIRECTDRAWHW;
if (ddrval==DDERR_NODIRECTDRAWSUPPORT)ErrStr=Err_DDERR_NODIRECTDRAWSUPPORT;
if (ddrval==DDERR_NODRIVERSUPPORT)ErrStr=Err_DDERR_NODRIVERSUPPORT;
if (ddrval==DDERR_NOEMULATION)ErrStr=Err_DDERR_NOEMULATION;
if (ddrval==DDERR_NOEXCLUSIVEMODE)ErrStr=Err_DDERR_NOEXCLUSIVEMODE;
if (ddrval==DDERR_NOFLIPHW)ErrStr=Err_DDERR_NOFLIPHW;
if (ddrval==DDERR_NOFOCUSWINDOW)ErrStr=Err_DDERR_NOFOCUSWINDOW;
if (ddrval==DDERR_NOGDI)ErrStr=Err_DDERR_NOGDI;
if (ddrval==DDERR_NOHWND)ErrStr=Err_DDERR_NOHWND;
if (ddrval==DDERR_NOMIPMAPHW)ErrStr=Err_DDERR_NOMIPMAPHW;
if (ddrval==DDERR_NOMIRRORHW)ErrStr=Err_DDERR_NOMIRRORHW;
if (ddrval==DDERR_NOMONITORINFORMATION)ErrStr=Err_DDERR_NOMONITORINFORMATION;
if (ddrval==DDERR_NONONLOCALVIDMEM)ErrStr=Err_DDERR_NONONLOCALVIDMEM;
if (ddrval==DDERR_NOOPTIMIZEHW)ErrStr=Err_DDERR_NOOPTIMIZEHW;
if (ddrval==DDERR_NOOVERLAYDEST)ErrStr=Err_DDERR_NOOVERLAYDEST;
if (ddrval==DDERR_NOOVERLAYHW)ErrStr=Err_DDERR_NOOVERLAYHW;
if (ddrval==DDERR_NOPALETTEATTACHED)ErrStr=Err_DDERR_NOPALETTEATTACHED;
if (ddrval==DDERR_NOPALETTEHW)ErrStr=Err_DDERR_NOPALETTEHW;
if (ddrval==DDERR_NORASTEROPHW)ErrStr=Err_DDERR_NORASTEROPHW;
if (ddrval==DDERR_NOROTATIONHW)ErrStr=Err_DDERR_NOROTATIONHW;
if (ddrval==DDERR_NOSTEREOHARDWARE)ErrStr=Err_DDERR_NOSTEREOHARDWARE;
if (ddrval==DDERR_NOSTRETCHHW)ErrStr=Err_DDERR_NOSTRETCHHW;
if (ddrval==DDERR_NOSURFACELEFT)ErrStr=Err_DDERR_NOSURFACELEFT;
if (ddrval==DDERR_NOT4BITCOLOR)ErrStr=Err_DDERR_NOT4BITCOLOR;
if (ddrval==DDERR_NOT4BITCOLORINDEX)ErrStr=Err_DDERR_NOT4BITCOLORINDEX;
if (ddrval==DDERR_NOT8BITCOLOR)ErrStr=Err_DDERR_NOT8BITCOLOR;
if (ddrval==DDERR_NOTAOVERLAYSURFACE)ErrStr=Err_DDERR_NOTAOVERLAYSURFACE;
if (ddrval==DDERR_NOTEXTUREHW)ErrStr=Err_DDERR_NOTEXTUREHW;
if (ddrval==DDERR_NOTFLIPPABLE)ErrStr=Err_DDERR_NOTFLIPPABLE;
if (ddrval==DDERR_NOTFOUND)ErrStr=Err_DDERR_NOTFOUND;
if (ddrval==DDERR_NOTINITIALIZED)ErrStr=Err_DDERR_NOTINITIALIZED;
if (ddrval==DDERR_NOTLOADED)ErrStr=Err_DDERR_NOTLOADED;
if (ddrval==DDERR_NOTLOCKED)ErrStr=Err_DDERR_NOTLOCKED;
if (ddrval==DDERR_NOTPAGELOCKED)ErrStr=Err_DDERR_NOTPAGELOCKED;
if (ddrval==DDERR_NOTPALETTIZED)ErrStr=Err_DDERR_NOTPALETTIZED;
if (ddrval==DDERR_NOVSYNCHW)ErrStr=Err_DDERR_NOVSYNCHW;
if (ddrval==DDERR_NOZBUFFERHW)ErrStr=Err_DDERR_NOZBUFFERHW;
if (ddrval==DDERR_NOZOVERLAYHW)ErrStr=Err_DDERR_NOZOVERLAYHW;
if (ddrval==DDERR_OUTOFCAPS)ErrStr=Err_DDERR_OUTOFCAPS;
if (ddrval==DDERR_OUTOFMEMORY)ErrStr=Err_DDERR_OUTOFMEMORY;
if (ddrval==DDERR_OUTOFVIDEOMEMORY)ErrStr=Err_DDERR_OUTOFVIDEOMEMORY;
if (ddrval==DDERR_OVERLAPPINGRECTS)ErrStr=Err_DDERR_OVERLAPPINGRECTS;
if (ddrval==DDERR_OVERLAYCANTCLIP)ErrStr=Err_DDERR_OVERLAYCANTCLIP;
if (ddrval==DDERR_OVERLAYCOLORKEYONLYONEACTIVE)ErrStr=Err_DDERR_OVERLAYCOLORKEYONLYONEACTIVE;
if (ddrval==DDERR_OVERLAYNOTVISIBLE)ErrStr=Err_DDERR_OVERLAYNOTVISIBLE;
if (ddrval==DDERR_PALETTEBUSY)ErrStr=Err_DDERR_PALETTEBUSY;
if (ddrval==DDERR_PRIMARYSURFACEALREADYEXISTS)ErrStr=Err_DDERR_PRIMARYSURFACEALREADYEXISTS;
if (ddrval==DDERR_REGIONTOOSMALL)ErrStr=Err_DDERR_REGIONTOOSMALL;
if (ddrval==DDERR_SURFACEALREADYATTACHED)ErrStr=Err_DDERR_SURFACEALREADYATTACHED;
if (ddrval==DDERR_SURFACEALREADYDEPENDENT)ErrStr=Err_DDERR_SURFACEALREADYDEPENDENT;
if (ddrval==DDERR_SURFACEBUSY)ErrStr=Err_DDERR_SURFACEBUSY;
if (ddrval==DDERR_SURFACEISOBSCURED)ErrStr=Err_DDERR_SURFACEISOBSCURED;
if (ddrval==DDERR_SURFACELOST)ErrStr=Err_DDERR_SURFACELOST;
if (ddrval==DDERR_SURFACENOTATTACHED) ErrStr=Err_DDERR_SURFACENOTATTACHED;
if (ddrval==DDERR_TESTFINISHED) ErrStr=Err_DDERR_TESTFINISHED;
if (ddrval==DDERR_TOOBIGHEIGHT) ErrStr=Err_DDERR_TOOBIGHEIGHT;
if (ddrval==DDERR_TOOBIGSIZE) ErrStr=Err_DDERR_TOOBIGSIZE;
if (ddrval==DDERR_TOOBIGWIDTH) ErrStr=Err_DDERR_TOOBIGWIDTH;
if (ddrval==DDERR_UNSUPPORTED) ErrStr=Err_DDERR_UNSUPPORTED;
if (ddrval==DDERR_UNSUPPORTEDFORMAT) ErrStr=Err_DDERR_UNSUPPORTEDFORMAT;
if (ddrval==DDERR_UNSUPPORTEDMASK) ErrStr=Err_DDERR_UNSUPPORTEDMASK;
if (ddrval==DDERR_UNSUPPORTEDMODE) ErrStr=Err_DDERR_UNSUPPORTEDMODE;
if (ddrval==DDERR_VERTICALBLANKINPROGRESS) ErrStr=Err_DDERR_VERTICALBLANKINPROGRESS;
if (ddrval==DDERR_VIDEONOTACTIVE) ErrStr=Err_DDERR_VIDEONOTACTIVE;
if (ddrval==DDERR_WASSTILLDRAWING) ErrStr=Err_DDERR_WASSTILLDRAWING;
if (ddrval==DDERR_WRONGMODE) ErrStr=Err_DDERR_WRONGMODE;
if (ddrval==DDERR_XALIGN) ErrStr=Err_DDERR_XALIGN;

return ErrStr;
}

///////////////////////////////////////////////////////////////////
LPDIRECTDRAWSURFACE7 bitmap_surface(LPCTSTR file_name)
{
	HDC hdc;
	HBITMAP bit;
	LPDIRECTDRAWSURFACE7 surf;

	// load the interface bitmap

	bit=(HBITMAP) LoadImage(NULL,file_name,IMAGE_BITMAP,0,0,
								LR_DEFAULTSIZE|LR_LOADFROMFILE);
	if (!bit) 

		// failed to load, return failure to caller

		return NULL;

	// get bitmap dimensions

	BITMAP bitmap;
    GetObject( bit, sizeof(BITMAP), &bitmap );
	int surf_width=bitmap.bmWidth;
	int surf_height=bitmap.bmHeight;

	// create surface

	DDSURFACEDESC2 ddsd;
	HRESULT ddrval;
	ZeroMemory(&ddsd,sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT ;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwWidth = surf_width;
	ddsd.dwHeight = surf_height; 

	// attempt to create surface

	ddrval=lpDD->CreateSurface(&ddsd,&surf,NULL);

	if (ddrval!=DD_OK) {
		checkerror(ddrval);
		DeleteObject(bit);
		return NULL;
	} else {
		surf->GetDC(&hdc);

		// generate a compatible DC

		HDC bit_dc=CreateCompatibleDC(hdc);

		// blit the interface to the surface

		SelectObject(bit_dc,bit);
		BitBlt(hdc,0,0,surf_width,surf_height,bit_dc,0,0,SRCCOPY);

		// release the DCs

		surf->ReleaseDC(hdc);
		DeleteDC(bit_dc);
	}

	DeleteObject(bit);
	// return pointer to caller

	return surf;
}

///////////////////////////////////////////////////////////////////
void CleanStart()
{
	work_voc.lpDSBuffer->Stop();
	SafeRelease(yokotyp1);
	SafeRelease(yokotyp2);
	SafeRelease(yokotyp3);
	SafeRelease(yokotyp4);
	SafeRelease(yokotyp5);
	SafeRelease(yokotyp6);
	SafeRelease(yokotyp7);
	SafeRelease(yokotyp8);
	SafeRelease(ssexit);
	SafeRelease(scredits);
	SafeRelease(soptions);
	SafeRelease(sstart);
	SafeRelease(sexit);
	SafeRelease(credits);
	SafeRelease(options);
	SafeRelease(start);
	SafeRelease(creditsbg);
	SafeRelease(startbg);
}

void Cleanup()
{
		// release loaded image surfaces

	SafeRelease(back_surf);
	SafeRelease(lev1);
	SafeRelease(lev2);
	SafeRelease(boss1);
	SafeRelease(bossbg);

	// release DirectDraw interfaces

	SafeRelease(lpDS);
	lpDIKey->Unacquire();
	SafeRelease(lpDIKey);
	SafeRelease(lpDI);
	SafeRelease(lev1);
	SafeRelease(lev2);
	SafeRelease(ShogoHit1);
	SafeRelease(ShogoHit2);
	SafeRelease(ShogoHit3);
	SafeRelease(ShogoHit4);
	SafeRelease(ShogoJump1);
	SafeRelease(ShogoJump2);
	SafeRelease(ShogoJump3);
	SafeRelease(ShogoJump4);
	SafeRelease(ShogoClimb1);
	SafeRelease(ShogoClimb2);
	SafeRelease(ShogoClimb3);
	SafeRelease(ShogoClimb4);
	SafeRelease(hbar);
	SafeRelease(hud);
	SafeRelease(sbar);
	SafeRelease(ammoico);
	SafeRelease(ShogoStand);
	SafeRelease(ShogoIdle);
	SafeRelease(ShogoRun1);
	SafeRelease(ShogoRun2);
	SafeRelease(ShogoRun3);
	SafeRelease(ShogoRun4);
	SafeRelease(ShogoRun5);
	SafeRelease(ShogoRun6);
	SafeRelease(ShogoRun7);
	SafeRelease(ShogoRun8);
	SafeRelease(ShogoRun9);
	SafeRelease(ShogoRun10);
	SafeRelease(ShogoM4Run1);
	SafeRelease(ShogoM4Run2);
	SafeRelease(ShogoM4Run3);
	SafeRelease(ShogoM4Run4);
	SafeRelease(ShogoM4Run5);
	SafeRelease(ShogoM4Run6);
	SafeRelease(ShogoM4Run7);
	SafeRelease(ShogoM4Run8);
	SafeRelease(ShogoInjure1);
	SafeRelease(ShogoInjure2);
	SafeRelease(ShogoInjure3);
	SafeRelease(ShogoFall1);
	SafeRelease(ShogoFall2);
	SafeRelease(ShogoFall3);
	SafeRelease(cot1);
	SafeRelease(cot2);
	SafeRelease(cot3);
	SafeRelease(cot4);
	SafeRelease(cot5);
	SafeRelease(cot6);
	SafeRelease(spike1);
	SafeRelease(spike2);
	SafeRelease(spike3);
	SafeRelease(spike4);
	SafeRelease(spike5);
	SafeRelease(spike6);
	SafeRelease(spike7);
	SafeRelease(spike8);
	SafeRelease(spike9);
	SafeRelease(explosion1);
	SafeRelease(explosion2);
	SafeRelease(explosion3);
	SafeRelease(explosion4);
	SafeRelease(explosion5);
	SafeRelease(explosion6);
	SafeRelease(explosion7);
	SafeRelease(explosion8);
	SafeRelease(explosion9);
	SafeRelease(r1);
	SafeRelease(r2);
	SafeRelease(r3);
	SafeRelease(r4);
	SafeRelease(r5);
	SafeRelease(r6);
	SafeRelease(r7);
	SafeRelease(cotexplo1);
	SafeRelease(cotexplo2);
	SafeRelease(cotexplo3);
	SafeRelease(cotexplo4);
	SafeRelease(cotexplo5);
	SafeRelease(cotexplo6);
	SafeRelease(cotexplo7);
	SafeRelease(lpDDSBack);
	SafeRelease(lpDDSPrimary);
	SafeRelease(lpDD);

	if (ErrStr) {
		MessageBox(NULL, ErrStr, szCaption, MB_OK);
		ErrStr=NULL;
	}
}

/////////////////////////REST////////////////////////////////////////

void rest() {
	rest_time=GetTickCount();

	while ((GetTickCount() - rest_time) < 100) {
		//resting...
	}
}

/////////////////////////////////////////////////////////////////////
LRESULT CALLBACK
WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
		switch (uMsg)
		{
		
		case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0L;

		
		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_ESCAPE:
					DestroyWindow(hWnd);
					break;
					default:
					break;
			}

			default:
				return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
}

///////////////////////////////////////////////////////////////////
int Load_VOC(char *filename,VOC_FILE_PTR voc_data)
{
// this function creates a sound from the send voc_file_ptr
// description and returns a pointer to it

int		index,         // looping var
		data_offset,   // working var
		playback_rate, // temp playback rate
		data_length;   // used to hold data length

ULONG	bytesread = 0; // actual size of total file
HANDLE	file_handle;   // file handle 
UCHAR	*snd_buffer;   // temporary sound buffer to hold voc data

UCHAR	*audio_ptr_1=NULL, // pointer to lock
		*audio_ptr_2=NULL;

DWORD	audio_length_1=0,  // lengths to lock
		audio_length_2=0;

// load the voc file off disk
if (!(file_handle = CreateFile(filename, 
						GENERIC_READ,			// access (read-write) mode 
						0,						// share mode 
					    NULL,					// pointer to security descriptor 
						OPEN_EXISTING,			// how to create 
					    FILE_ATTRIBUTE_NORMAL,	// file attributes 
						NULL					// handle to file with attributes to copy  
						)))
	return(0);

// allocate a large enough temporary buffer (hold 50 secs)
snd_buffer = (UCHAR *)malloc(640000);

// now read in the data
ReadFile(file_handle, snd_buffer, 640000, &bytesread, NULL);

// access all values 
data_offset		= snd_buffer[20];
playback_rate	= (-1000000/(snd_buffer[data_offset+4]-256));
data_length     = ((*(int *)(snd_buffer+data_offset)) >> 8);

// set rate and size in data structure
voc_data->sample_rate  = playback_rate;
voc_data->length       = data_length;

// close the file
CloseHandle(file_handle);

// step three: create the sound buffer and copy voc data into buffer

// set up the format data structure
memset(&pcmwf, 0, sizeof(WAVEFORMATEX));

pcmwf.wFormatTag	= WAVE_FORMAT_PCM;
pcmwf.nChannels		= 1;
pcmwf.nSamplesPerSec= 11025;
pcmwf.nBlockAlign	= 1;
pcmwf.nAvgBytesPerSec = pcmwf.nSamplesPerSec * pcmwf.nBlockAlign;
pcmwf.wBitsPerSample= 8;
pcmwf.cbSize		= 0;

// create the sound buffer
dsbd.dwSize			= sizeof(DSBUFFERDESC);
dsbd.dwFlags		= DSBCAPS_CTRLVOLUME | DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE ;
dsbd.dwBufferBytes	= data_length-NVB_SIZE;
dsbd.lpwfxFormat	= &pcmwf;

if (lpDS->CreateSoundBuffer(&dsbd,&(voc_data->lpDSBuffer),NULL)!=DS_OK)
	return(0);

// copy data into sound buffer
if ((voc_data->lpDSBuffer)->Lock(0,					 
						     data_length-NVB_SIZE,			
						     (void **) &audio_ptr_1, 
						     &audio_length_1,
						     (void **)&audio_ptr_2, 
						     &audio_length_2,
						     DSBLOCK_FROMWRITECURSOR)!=DS_OK)
						     return(0);


// copy first section of circular buffer
memcpy(audio_ptr_1, snd_buffer+data_offset+NVB_SIZE, audio_length_1);

// copy last section of circular buffer
memcpy(audio_ptr_2, (snd_buffer+data_offset+NVB_SIZE+audio_length_1),audio_length_2);

// unlock the buffer
if ((voc_data->lpDSBuffer)->Unlock(audio_ptr_1, 
									audio_length_1, 
									audio_ptr_2, 
									audio_length_2)!=DS_OK)
									return(0);

// release the temp buffer
free(snd_buffer);

// return success
return(1);

} // end Load_Voc
///////////////////////////////////////////////////////////////////
BOOL loadlev1()
{
	RECT rloadbg;

	rloadbg.left = 0; 
	rloadbg.top = 0;
	rloadbg.right = 640; 
	rloadbg.bottom = 480; 
	
	load1=bitmap_surface("load1.bmp");
	if (!load1) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	load2=bitmap_surface("load2.bmp");
	if (!load2) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	load3=bitmap_surface("load3.bmp");
	if (!load3) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	load4=bitmap_surface("load4.bmp");
	if (!load4) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	//blit!
	lpDDSBack->BltFast(0,0,load1,&rloadbg,DDBLTFAST_WAIT);
	lpDDSPrimary->Flip(NULL,DDFLIP_WAIT); 
	rest();


	lpDDSBack->BltFast(0,0,load2,&rloadbg,DDBLTFAST_WAIT);
	lpDDSPrimary->Flip(NULL,DDFLIP_WAIT); 

	back_surf=bitmap_surface("levelbg.bmp");
	if (!back_surf) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	lev1=bitmap_surface("level1.bmp");
	if (!lev1) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	lev2=bitmap_surface("level2.bmp");
	if (!lev2) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	boss1=bitmap_surface("1boss.bmp");
	if (!boss1) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	bossbg=bitmap_surface("bossbg.bmp");
	if (!boss1) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	rest();

	lpDDSBack->BltFast(0,0,load3,&rloadbg,DDBLTFAST_WAIT);
	lpDDSPrimary->Flip(NULL,DDFLIP_WAIT); 

	ShogoStand=bitmap_surface("ShogoStand.bmp");
	if (!ShogoStand) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoIdle=bitmap_surface("ShogoIdle.bmp");
	if (!ShogoIdle) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoHit1=bitmap_surface("ShogoHit1.bmp");
	if (!ShogoHit1) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoHit2=bitmap_surface("ShogoHit2.bmp");
	if (!ShogoHit2) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoHit3=bitmap_surface("ShogoHit3.bmp");
	if (!ShogoHit3) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoHit4=bitmap_surface("ShogoHit4.bmp");
	if (!ShogoHit4) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	ShogoJump1=bitmap_surface("ShogoJump1.bmp");
	if (!ShogoJump1) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoJump2=bitmap_surface("ShogoJump2.bmp");
	if (!ShogoJump2) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoJump3=bitmap_surface("ShogoJump3.bmp");
	if (!ShogoJump3) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoJump4=bitmap_surface("ShogoJump4.bmp");
	if (!ShogoJump4) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoClimb1=bitmap_surface("ShogoClimb1.bmp");
	if (!ShogoClimb1) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoClimb2=bitmap_surface("ShogoClimb2.bmp");
	if (!ShogoClimb2) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoClimb3=bitmap_surface("ShogoClimb3.bmp");
	if (!ShogoClimb3) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoClimb4=bitmap_surface("ShogoClimb4.bmp");
	if (!ShogoClimb4) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoRun1=bitmap_surface("ShogoRun1.bmp");
	if (!ShogoRun1) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoRun2=bitmap_surface("ShogoRun2.bmp");
	if (!ShogoRun2) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoRun3=bitmap_surface("ShogoRun3.bmp");
	if (!ShogoRun3) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoRun4=bitmap_surface("ShogoRun4.bmp");
	if (!ShogoRun4) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoRun5=bitmap_surface("ShogoRun5.bmp");
	if (!ShogoRun5) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoRun6=bitmap_surface("ShogoRun6.bmp");
	if (!ShogoRun6) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoRun7=bitmap_surface("ShogoRun7.bmp");
	if (!ShogoRun7) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	ShogoRun8=bitmap_surface("ShogoRun8.bmp");
	if (!ShogoRun8) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	ShogoRun9=bitmap_surface("ShogoRun9.bmp");
	if (!ShogoRun8) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoRun10=bitmap_surface("ShogoRun10.bmp");
	if (!ShogoRun10) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoInjure1=bitmap_surface("ShogoInjure1.bmp");
	if (!ShogoInjure1) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	ShogoInjure2=bitmap_surface("ShogoInjure2.bmp");
	if (!ShogoInjure2) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoInjure3=bitmap_surface("ShogoInjure3.bmp");
	if (!ShogoInjure3) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoFall1=bitmap_surface("ShogoFall1.bmp");
	if (!ShogoFall1) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	ShogoFall2=bitmap_surface("ShogoFall2.bmp");
	if (!ShogoFall2) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ShogoFall3=bitmap_surface("ShogoFall3.bmp");
	if (!ShogoFall3) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	hbar=bitmap_surface("hbar.bmp");
	if (!hbar) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	hud=bitmap_surface("hud.bmp");
	if (!hud) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	sbar=bitmap_surface("sbar.bmp");
	if (!sbar) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ammoico=bitmap_surface("ammoico.bmp");
	if (!ammoico) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	rest();

	lpDDSBack->BltFast(0,0,load4,&rloadbg,DDBLTFAST_WAIT);
	lpDDSPrimary->Flip(NULL,DDFLIP_WAIT); 

	spike1=bitmap_surface("spike1.bmp");
	if (!spike1) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	spike2=bitmap_surface("spike2.bmp");
	if (!spike2) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	spike3=bitmap_surface("spike3.bmp");
	if (!spike3) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	spike4=bitmap_surface("spike4.bmp");
	if (!spike4) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	spike5=bitmap_surface("spike5.bmp");
	if (!spike5) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	spike6=bitmap_surface("spike6.bmp");
	if (!spike6) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	spike7=bitmap_surface("spike7.bmp");
	if (!spike7) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	spike8=bitmap_surface("spike8.bmp");
	if (!spike8) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	spike9=bitmap_surface("spike9.bmp");
	if (!spike9) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	explosion1=bitmap_surface("explosion1.bmp");
	if (!explosion1) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	explosion2=bitmap_surface("explosion2.bmp");
	if (!explosion2) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	explosion3=bitmap_surface("explosion3.bmp");
	if (!explosion3) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	explosion4=bitmap_surface("explosion4.bmp");
	if (!explosion4) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	explosion5=bitmap_surface("explosion5.bmp");
	if (!explosion5) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	explosion6=bitmap_surface("explosion6.bmp");
	if (!explosion6) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	explosion7=bitmap_surface("explosion7.bmp");
	if (!explosion7) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	explosion8=bitmap_surface("explosion8.bmp");
	if (!explosion8) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	explosion9=bitmap_surface("explosion9.bmp");
	if (!explosion9) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	r1=bitmap_surface("r1.bmp");
	if (!r1) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	r2=bitmap_surface("r2.bmp");
	if (!r2) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	r3=bitmap_surface("r3.bmp");
	if (!r3) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	r4=bitmap_surface("r4.bmp");
	if (!r4) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	r5=bitmap_surface("r5.bmp");
	if (!r5) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	r6=bitmap_surface("r6.bmp");
	if (!r6) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	r7=bitmap_surface("r7.bmp");
	if (!r7) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	cot1=bitmap_surface("cot1.bmp");
	if (!cot1) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	cot2=bitmap_surface("cot2.bmp");
	if (!cot2) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	cot3=bitmap_surface("cot3.bmp");
	if (!cot3) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	cot4=bitmap_surface("cot4.bmp");
	if (!cot4) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	cot5=bitmap_surface("cot5.bmp");
	if (!cot5) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	cot6=bitmap_surface("cot6.bmp");
	if (!cot6) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	cotexplo1=bitmap_surface("cotexplo1.bmp");
	if (!cotexplo1) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	cotexplo2=bitmap_surface("cotexplo2.bmp");
	if (!cotexplo2) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	cotexplo3=bitmap_surface("cotexplo3.bmp");
	if (!cotexplo3) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	cotexplo4=bitmap_surface("cotexplo4.bmp");
	if (!cotexplo4) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	cotexplo5=bitmap_surface("cotexplo5.bmp");
	if (!cotexplo5) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	cotexplo6=bitmap_surface("cotexplo6.bmp");
	if (!cotexplo6) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	cotexplo7=bitmap_surface("cotexplo7.bmp");
	if (!cotexplo7) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	rest();

	DDPIXELFORMAT ddpf;
	ddpf.dwSize=sizeof(ddpf);
	lpDDSPrimary->GetPixelFormat(&ddpf);

	KeyColor = ddpf.dwGBitMask;

	DDCOLORKEY key;
	key.dwColorSpaceLowValue = KeyColor;
	key.dwColorSpaceHighValue = KeyColor;
	ShogoRun1->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoRun2->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoRun3->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoRun4->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoRun5->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoRun6->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoRun7->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoRun8->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoRun9->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoRun10->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoInjure1->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoInjure2->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoInjure3->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoFall1->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoFall2->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoFall3->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoIdle->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoStand->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoHit1->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoHit2->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoHit3->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoHit4->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoJump1->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoJump2->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoJump3->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoJump4->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoClimb1->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoClimb2->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoClimb3->SetColorKey(DDCKEY_SRCBLT, &key);
	ShogoClimb4->SetColorKey(DDCKEY_SRCBLT, &key);
	spike1->SetColorKey(DDCKEY_SRCBLT, &key);
	spike2->SetColorKey(DDCKEY_SRCBLT, &key);
	spike3->SetColorKey(DDCKEY_SRCBLT, &key);
	spike4->SetColorKey(DDCKEY_SRCBLT, &key);
	spike5->SetColorKey(DDCKEY_SRCBLT, &key);
	spike6->SetColorKey(DDCKEY_SRCBLT, &key);
	spike7->SetColorKey(DDCKEY_SRCBLT, &key);
	spike8->SetColorKey(DDCKEY_SRCBLT, &key);
	spike9->SetColorKey(DDCKEY_SRCBLT, &key);
	explosion1->SetColorKey(DDCKEY_SRCBLT, &key);
	explosion2->SetColorKey(DDCKEY_SRCBLT, &key);
	explosion3->SetColorKey(DDCKEY_SRCBLT, &key);
	explosion4->SetColorKey(DDCKEY_SRCBLT, &key);
	explosion5->SetColorKey(DDCKEY_SRCBLT, &key);
	explosion6->SetColorKey(DDCKEY_SRCBLT, &key);
	explosion7->SetColorKey(DDCKEY_SRCBLT, &key);
	explosion8->SetColorKey(DDCKEY_SRCBLT, &key);
	explosion9->SetColorKey(DDCKEY_SRCBLT, &key);
	r1->SetColorKey(DDCKEY_SRCBLT, &key);
	r2->SetColorKey(DDCKEY_SRCBLT, &key);
	r3->SetColorKey(DDCKEY_SRCBLT, &key);
	r4->SetColorKey(DDCKEY_SRCBLT, &key);
	r5->SetColorKey(DDCKEY_SRCBLT, &key);
	r6->SetColorKey(DDCKEY_SRCBLT, &key);
	r7->SetColorKey(DDCKEY_SRCBLT, &key);
	cot1->SetColorKey(DDCKEY_SRCBLT, &key);
	cot2->SetColorKey(DDCKEY_SRCBLT, &key);
	cot3->SetColorKey(DDCKEY_SRCBLT, &key);
	cot4->SetColorKey(DDCKEY_SRCBLT, &key);
	cot5->SetColorKey(DDCKEY_SRCBLT, &key);
	cot6->SetColorKey(DDCKEY_SRCBLT, &key);
	cotexplo1->SetColorKey(DDCKEY_SRCBLT, &key);
	cotexplo2->SetColorKey(DDCKEY_SRCBLT, &key);
	cotexplo3->SetColorKey(DDCKEY_SRCBLT, &key);
	cotexplo4->SetColorKey(DDCKEY_SRCBLT, &key);
	cotexplo5->SetColorKey(DDCKEY_SRCBLT, &key);
	cotexplo6->SetColorKey(DDCKEY_SRCBLT, &key);
	cotexplo7->SetColorKey(DDCKEY_SRCBLT, &key);
	hbar->SetColorKey(DDCKEY_SRCBLT, &key);
	hud->SetColorKey(DDCKEY_SRCBLT, &key);
	sbar->SetColorKey(DDCKEY_SRCBLT, &key);
	ammoico->SetColorKey(DDCKEY_SRCBLT, &key);
	lev1->SetColorKey(DDCKEY_SRCBLT, &key);
	lev2->SetColorKey(DDCKEY_SRCBLT, &key);
	boss1->SetColorKey(DDCKEY_SRCBLT, &key);
	return TRUE;
}

BOOL load_start()
{
	startbg=bitmap_surface("startbg.bmp");
	if (!startbg) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	creditsbg=bitmap_surface("creditsbg.bmp");
	if (!creditsbg) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	start=bitmap_surface("start.bmp");
	if (!start) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	options=bitmap_surface("options.bmp");
	if (!options) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	credits=bitmap_surface("credits.bmp");
	if (!credits) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	sexit=bitmap_surface("exit.bmp");
	if (!sexit) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	sstart=bitmap_surface("sstart.bmp");
	if (!sstart) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	soptions=bitmap_surface("soptions.bmp");
	if (!soptions) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	scredits=bitmap_surface("scredits.bmp");
	if (!scredits) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	ssexit=bitmap_surface("sexit.bmp");
	if (!ssexit) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	yokotyp1=bitmap_surface("yokotek1.bmp");
	if (!sexit) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	yokotyp2=bitmap_surface("yokotek2.bmp");
	if (!sexit) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	yokotyp3=bitmap_surface("yokotek3.bmp");
	if (!sexit) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	yokotyp4=bitmap_surface("yokotek4.bmp");
	if (!sexit) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	yokotyp5=bitmap_surface("yokotek5.bmp");
	if (!sexit) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	yokotyp6=bitmap_surface("yokotek6.bmp");
	if (!sexit) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	yokotyp7=bitmap_surface("yokotek7.bmp");
	if (!sexit) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}
	
	yokotyp8=bitmap_surface("yokotek8.bmp");
	if (!sexit) {
		ErrStr=Err_LoadImage;
		return FALSE;
	}

	DDPIXELFORMAT ddpf;
	ddpf.dwSize=sizeof(ddpf);
	lpDDSPrimary->GetPixelFormat(&ddpf);

	KeyColor = ddpf.dwGBitMask;

	DDCOLORKEY key;
	key.dwColorSpaceLowValue = KeyColor;
	key.dwColorSpaceHighValue = KeyColor;
	creditsbg->SetColorKey(DDCKEY_SRCBLT, &key);
	startbg->SetColorKey(DDCKEY_SRCBLT, &key);
	start->SetColorKey(DDCKEY_SRCBLT, &key);
	options->SetColorKey(DDCKEY_SRCBLT, &key);
	credits->SetColorKey(DDCKEY_SRCBLT, &key);
	sexit->SetColorKey(DDCKEY_SRCBLT, &key);
	sstart->SetColorKey(DDCKEY_SRCBLT, &key);
	soptions->SetColorKey(DDCKEY_SRCBLT, &key);
	scredits->SetColorKey(DDCKEY_SRCBLT, &key);
	ssexit->SetColorKey(DDCKEY_SRCBLT, &key);
	yokotyp1->SetColorKey(DDCKEY_SRCBLT, &key);
	yokotyp2->SetColorKey(DDCKEY_SRCBLT, &key);
	yokotyp3->SetColorKey(DDCKEY_SRCBLT, &key);
	yokotyp4->SetColorKey(DDCKEY_SRCBLT, &key);
	yokotyp5->SetColorKey(DDCKEY_SRCBLT, &key);
	yokotyp6->SetColorKey(DDCKEY_SRCBLT, &key);
	yokotyp7->SetColorKey(DDCKEY_SRCBLT, &key);
	yokotyp8->SetColorKey(DDCKEY_SRCBLT, &key);

}

////////////////////////////////////////////////////////////////////
static BOOL Init(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASS		wc;
	HRESULT         ddrval;
	HRESULT			dirval;
	HRESULT			dsrval;
	DDSURFACEDESC2	ddsd;
	DDSCAPS2		ddscaps;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC) WindowProc;
	wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(DWORD);
    wc.hInstance = hInstance;
    wc.hIcon = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szClass;
	RegisterClass(&wc);

	int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	HWND hWnd;

    hWnd = CreateWindow(szClass,							// class
                        szCaption,							// caption
						WS_VISIBLE|WS_POPUP,				// style 
						0,									// left
						0,									// top
						ScreenWidth,						// width
						ScreenHeight,						// height
                        NULL,								// parent window
                        NULL,								// menu 
                        hInstance,							// instance
                        NULL);								// parms
	
	ShowWindow(hWnd, nCmdShow);
	ShowCursor(FALSE);
    UpdateWindow(hWnd);
	SetFocus(hWnd);

	//DirectDraw
	ddrval=DirectDrawCreateEx(NULL,(VOID**)&lpDD, IID_IDirectDraw7, NULL);
	if (ddrval != DD_OK) {
		checkerror(ddrval);
		return FALSE;
	}

	// set co-op
	ddrval=lpDD->SetCooperativeLevel(hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN | DDSCL_ALLOWREBOOT );
	if (ddrval != DD_OK) {
		checkerror(ddrval);
		return FALSE;
	}

	// display mode
	ddrval=lpDD->SetDisplayMode( 640, 480, 32, 0, 0);
	if (ddrval !=DD_OK) {
		checkerror(ddrval);
		return FALSE;
	}


	// create primary surface with one back buffer
	ZeroMemory(&ddsd,sizeof(ddsd));
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
    ddsd.dwBackBufferCount = 1;
    ddrval=lpDD->CreateSurface( &ddsd, &lpDDSPrimary, NULL );
	if (ddrval!=DD_OK) {
		checkerror(ddrval);
		return FALSE;
	}

	// get back buffer
	ZeroMemory(&ddscaps, sizeof(ddscaps));
	ddscaps.dwCaps=DDSCAPS_BACKBUFFER;
 	ddrval=lpDDSPrimary->GetAttachedSurface(&ddscaps, &lpDDSBack);
	if (ddrval!=DD_OK) {
		checkerror(ddrval);
		return FALSE;
	}

	//Direct Input
	dirval=DirectInputCreate(hInstance, DIRECTINPUT_VERSION, &lpDI, NULL);
	if (dirval!=DI_OK) {
		ErrStr=Err_DirectInputCreate;
		return FALSE;
	}

	//Create Keyboard Device
	dirval=lpDI->CreateDevice(GUID_SysKeyboard, &lpDIKey, NULL);
	if (dirval!=DI_OK) {
		ErrStr=Err_CreateDevice;
		return FALSE;
	}

	//set co-op
	dirval=lpDIKey->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	if (dirval!=DI_OK) {
		ErrStr=Err_SetCoopInput;
		return FALSE;
	}

	//set data format
	dirval=lpDIKey->SetDataFormat(&c_dfDIKeyboard);
	if (dirval!=DI_OK) {
		ErrStr=Err_SetDataFormat;
		return FALSE;
	}
	
	//Acquire data stream from Device
	dirval=lpDIKey->Acquire();
	if (dirval!=DI_OK) {
		ErrStr=Err_Acquire;
		return FALSE;
	}

	//DirectSound
	dsrval=DirectSoundCreate(NULL, &lpDS, NULL);
	//Sound Co-op
	dsrval=lpDS->SetCooperativeLevel(hWnd, DSSCL_NORMAL);

	return TRUE;
}
/////////////////////////////////////////////////////////////////

void startstart()
{
	load_start();
	bStartstart=TRUE;

	Load_VOC("121.VOC",&work_voc);
	Load_VOC("TYPE.VOC",&type_voc);
	Load_VOC("lev1.VOC",&lev1_voc);
	Load_VOC("steps.VOC",&steps_voc);
	Load_VOC("land.VOC",&land_voc);
	Load_VOC("explo1.VOC",&explo1_voc);
	Load_VOC("menu1.VOC",&menu1_voc);
	Load_VOC("menu2.VOC",&menu2_voc);
	Load_VOC("electric.VOC",&electric_voc);
}

void startinput()
{
	UCHAR keystate[256];

	if(lpDIKey->GetDeviceState(256, keystate)!=DI_OK) {ErrStr=Err_GetState;}


	if(keystate[DIK_DOWN] & 0x80)
	{  
		if (bPushD==FALSE)
		{
			select++;
			bPushD=TRUE;
			menu1_voc.lpDSBuffer->Play(0,0,0);
		}
	}
	else { bPushD=FALSE; }

	if(keystate[DIK_UP] & 0x80) 
	{  
		if (bPushU==FALSE)
		{
			select--;
			bPushU=TRUE;
			menu1_voc.lpDSBuffer->Play(0,0,0);
		}
	}
	else { bPushU=FALSE; }
	
	if((keystate[DIK_RETURN] & 0x80) && (select==1) && startbgnum==STARTBG) { bStart=TRUE; menu2_voc.lpDSBuffer->Play(0,0,0); loadlev1(); } 
	if((keystate[DIK_RETURN] & 0x80) && (select==2)) { startbgnum=OPTIONSBG; menu2_voc.lpDSBuffer->Play(0,0,0);} 
	if((keystate[DIK_RETURN] & 0x80) && (select==3)) { startbgnum=CREDITSBG; menu2_voc.lpDSBuffer->Play(0,0,0); rest(); } 
	if((keystate[DIK_RETURN] & 0x80) && (select==4)) { bStart=TRUE; menu2_voc.lpDSBuffer->Play(0,0,0);} 
	if((keystate[DIK_RETURN] & 0x80) && (startbgnum!=STARTBG) && (select!=3)) { startbgnum=STARTBG; menu2_voc.lpDSBuffer->Play(0,0,0); rest(); select=3;} 


	if (select>4) { select=1; }
	if (select<1) { select=4; }
}

void render_start()
{	
	RECT rstartbg;
	RECT rstart;
	RECT roptions;
	RECT rcredits;
	RECT rsexit;
	RECT rytek;

	rstartbg.left = 0; 
	rstartbg.top = 0;
	rstartbg.right = 640; 
	rstartbg.bottom = 480; 
	rstart.left = 0; 
	rstart.top = 0;
	rstart.right = 84; 
	rstart.bottom = 18; 
	roptions.left = 0; 
	roptions.top = 0;
	roptions.right = 120; 
	roptions.bottom = 26; 
	rcredits.left = 0; 
	rcredits.top = 0;
	rcredits.right = 120; 
	rcredits.bottom = 21; 
	rsexit.left = 0; 
	rsexit.top = 0;
	rsexit.right = 66; 
	rsexit.bottom = 21; 
	rytek.left = 0; 
	rytek.top = 0;
	rytek.right = 164; 
	rytek.bottom = 29;

	if (startbgnum==STARTBG) { lpDDSBack->BltFast(0,0,startbg,&rstartbg,DDBLTFAST_WAIT); }
	if (startbgnum==CREDITSBG) { lpDDSBack->BltFast(0,0,creditsbg,&rstartbg,DDBLTFAST_WAIT);  select=1;}

	if (bBlink==FALSE) {
		blink_time=GetTickCount();
		bBlink=TRUE;
	}
	
	if ((GetTickCount() - blink_time > 1500)  && (GetTickCount() - blink_time <=2250))  {
		if (clicks==0) { type_voc.lpDSBuffer->Play(0,0,0); clicks++; }
		lpDDSBack->BltFast(0,0,yokotyp1,&rytek,DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	}

	if ((GetTickCount() - blink_time >2250) && (GetTickCount() - blink_time <=2950)) {
		if (clicks==1) { type_voc.lpDSBuffer->Play(0,0,0); clicks++; }
		lpDDSBack->BltFast(0,0,yokotyp2,&rytek,DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	}
	
	if ((GetTickCount() - blink_time >2950) && (GetTickCount() - blink_time <=3500)) {
		if (clicks==2) { type_voc.lpDSBuffer->Play(0,0,0); clicks++; }
		lpDDSBack->BltFast(0,0,yokotyp3,&rytek,DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	}

	if ((GetTickCount() - blink_time >3500) && (GetTickCount() - blink_time <=4000)) {
		if (clicks==3) { type_voc.lpDSBuffer->Play(0,0,0); clicks++; }
		lpDDSBack->BltFast(0,0,yokotyp4,&rytek,DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	}

	if ((GetTickCount() - blink_time >4000) && (GetTickCount() - blink_time <=4800)) {
		if (clicks==4) { type_voc.lpDSBuffer->Play(0,0,0); clicks++; }
		lpDDSBack->BltFast(0,0,yokotyp5,&rytek,DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	}

	if ((GetTickCount() - blink_time >4800) && (GetTickCount() - blink_time <=5400)) {
		if (clicks==5) { type_voc.lpDSBuffer->Play(0,0,0); clicks++; }
		lpDDSBack->BltFast(0,0,yokotyp6,&rytek,DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	}

	if ((GetTickCount() - blink_time >5400) && (GetTickCount() - blink_time <=6000)) {
		if (clicks==6) { type_voc.lpDSBuffer->Play(0,0,0); clicks++; }
		lpDDSBack->BltFast(0,0,yokotyp7,&rytek,DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
		bBlitMenu=TRUE;
	}

	if ((bBlitMenu==TRUE) && (startbgnum==STARTBG)) {
		if (bMusic==FALSE) { work_voc.lpDSBuffer->Play(0,0,DSBPLAY_LOOPING); bMusic=TRUE; }
		if ((GetTickCount() - blink_time) > 1000) {  
			blink_time=GetTickCount();
		}
		if ((GetTickCount() - blink_time) > 500) {  
			lpDDSBack->BltFast(0,0,yokotyp8,&rytek,DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
		}
		if ((GetTickCount() - blink_time) <= 500) { 
			lpDDSBack->BltFast(0,0,yokotyp7,&rytek,DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
		}
		if (select==1) {
			lpDDSBack->BltFast(280,150,sstart,&rstart,DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
		} else { 
			lpDDSBack->BltFast(280,150,start,&rstart,DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
		}
		if (select==2) {
			lpDDSBack->BltFast(280,200,soptions,&roptions,DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
		} else {
			lpDDSBack->BltFast(280,200,options,&roptions,DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
		}
		if (select==3) {
			lpDDSBack->BltFast(280,250,scredits,&rcredits,DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
		} else {
			lpDDSBack->BltFast(280,250,credits,&rcredits,DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
		}
		if (select==4) {
			lpDDSBack->BltFast(280,300,ssexit,&rsexit,DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
		} else {
			lpDDSBack->BltFast(280,300,sexit,&rsexit,DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
		}
	}

	lpDDSPrimary->Flip(NULL,DDFLIP_WAIT); 

}
/////////////////////////////////////////////////////////////////
void lv1start()
{
	Shogo.health=100;
	Shogo.ammobullet=100;
	Shogo.curammo=Shogo.ammobullet;
	Shogo.special=100;

	cota_time=GetTickCount();
	spikea_time=GetTickCount();
	rocka_time=GetTickCount();

	bStartLev=TRUE;

	CleanStart();

	lev1_voc.lpDSBuffer->Play(0,0,DSBPLAY_LOOPING);

	CotA.x=1120;
	CotA.y=150;
	CotA.health=20;
	CotA.doa=FALSE;
	CotA.adead=FALSE;

	SpikeA.x=5620;
	SpikeA.y=180;
	SpikeA.health=100;
	SpikeA.doa=FALSE;
	SpikeA.adead=FALSE;

	RockA.x=5600;
	RockA.y=220;
}

void level1a()
{
	
	if (Shogo.x<310)
	{
		floory=210;
		x_min=25;
		x_max=6700;
	}
	if ((Shogo.x>=310) && (Shogo.x<863))
	{
		floory=275;
		x_max=6700;
		if (y_pos>210)	x_min=330;
		else x_min=25;
	}
	if ((Shogo.x>=843) && (Shogo.x<910))
	{
		floory=900;
		if (y_pos>275)	x_min=853;
		else x_min=25;
		if (y_pos>275) x_max=900;
		else x_max=6700;
	}
	if ((Shogo.x>=910) && (Shogo.x<1480))
	{
		floory=268;
		x_min=25;
		bLadder=FALSE;
		bClimb=FALSE;
	}
	if ((Shogo.x>=1310) && (Shogo.x<1330))
	{
		floory=268;
		x_min=25;
		if (y_pos>73) { bLadder=TRUE; }
		else { bLadder=FALSE; }

		if (y_pos<268) { bClimb=TRUE; }
	}
	if ((Shogo.x>=1230) && (Shogo.x<1420) && (y_pos<=73))
	{
		floory=73;
		x_min=330;
		bLadder=FALSE;
		bClimb=FALSE;
	}
	if ((Shogo.x>=1480) && (Shogo.x<1600))
	{
		floory=900;
		if (y_pos>268)	x_min=1500;
		else x_min=25;
		if (y_pos>30)	x_max=1580;
		else x_max=6700;
		bLadder=FALSE;
	}
	if ((Shogo.x>=1600) && (Shogo.x<2220))
	{
		floory=30;
		x_min=25;
	}
	if ((Shogo.x>=2220) && (Shogo.x<2820))
	{
		floory=200;
		if (y_pos>30)	x_min=2230;
		else x_min=25;
	}
	if ((Shogo.x>=2820) && (Shogo.x<2960))
	{
		floory=900;
		if (y_pos>200)	x_min=2830;
		else x_min=25;
		if (y_pos>280)	x_max=2950;
		else x_max=6700;
	}
	if ((Shogo.x>=2960) && (Shogo.x<3080))
	{
		floory=280;
		x_min=25;
		if (y_pos>134)	x_max=3070;
		else x_max=6700;
		bSlant=FALSE;
	}
	if ((Shogo.x>=3080) && (Shogo.x<3700))
	{
		int slantx;

		slantx=(Shogo.x-3120);
		floory=134 - (0.19*slantx);
		x_min=25;

		if (bJump==TRUE) bSlant=FALSE;
		else 
		{
			if(bJumpDone==FALSE) bSlant=FALSE;
			else bSlant=TRUE;
		}
	}
	if ((Shogo.x>=3700) && (Shogo.x<4890))
	{
		floory=72;
		x_min=25;
		bSlant=FALSE;
	}
	if ((Shogo.x>=4890) && (Shogo.x<5090))
	{
		int slantx;

		slantx=(Shogo.x-4925);
		floory=120 + (0.32*slantx);
		if (y_pos>72)	x_min=4900 ;
		else x_min=25;

		if (bJump==TRUE) bSlant=FALSE;
		else 
		{
			if(bJumpDone==FALSE) bSlant=FALSE;
			else bSlant=TRUE;
		}
	}
	if ((Shogo.x>=5090) && (Shogo.x<5180))
	{
		floory=900;
		if (y_pos>173)	x_min=5100;
		else x_min=25;
		if (y_pos>173)	x_max=5170;
		else x_max=6700;
		bSlant=FALSE;
	}
	if ((Shogo.x>=5180) && (Shogo.x<5740))
	{
		floory=180;
		x_min=25;
	}
	if (Shogo.x>=5740)
	{
		floory=900;
		if (y_pos>180)	x_min=5750;
		else x_min=25;
	}
	if (Shogo.x>=5750 && y_pos>=550) 
	{
		clev=1.2;
		bScroll=FALSE;
		x_pos=0;
		mapx_pos=0;
		mapendx_pos=640;
		x_min=0;
		x_max=5120;
		backx_pos=0;
		backwidth=640;
		y_pos=0;
		floory=53;
		Shogo.x=0;
	}
}

void level1b()
{
	
	if (Shogo.x<500)
	{
		floory=53;
		x_min=25;
		x_max=8300;
	}

	if ((Shogo.x>=500) && (Shogo.x<640))
	{
		floory=233;
		x_min=510;
	}

	if ((Shogo.x>=640) && (Shogo.x<850))
	{
		floory=900;
		if (y_pos>233)	x_min=650;
		else x_min=25;
		if (y_pos>260)	x_max=840;
		else x_max=8300;
	}

	if ((Shogo.x>=850) && (Shogo.x<1140))
	{
		floory=260;
		x_min=25;
		x_max=8300;
	}
	
	if ((Shogo.x>=1140) && (Shogo.x<1280))
	{
		floory=900;
		if (y_pos>260)	x_min=1150;
		else x_min=25;
		if (y_pos>200 && y_pos<=250) x_max=1270;
		else x_max=8300;
	}
	
	if ((Shogo.x>=1280) && (Shogo.x<1655)) 
	{
		floory=200;
		x_min=25;
		if (y_pos>46 && y_pos<=60) x_max=1645;
		else x_max=8300;
		if (y_pos>250) { floory=900; }
	}

	if ((Shogo.x>=1655) && (Shogo.x<2340)) 
	{
		floory=46;
		x_min=25;
		x_max=8300;
		if (y_pos>60) { floory=900; }
	}

	if ((Shogo.x>=2340) && (Shogo.x<3010)) 
	{
		floory=100;
		if (y_pos>46)	x_min=2350;
		else x_min=25;
		if (y_pos>50)	x_max=3000;
		else x_max=8300;
		bSlant=FALSE;
	}
	
	if ((Shogo.x>=3010) && (Shogo.x<3200)) 
	{
		int slantx;

		slantx=(Shogo.x-3020);
		floory=50 + (0.32*slantx);
		
		x_min=25;
		x_max=8300;

		if (bJump==TRUE) bSlant=FALSE;
		else 
		{
			if(bJumpDone==FALSE) bSlant=FALSE;
			else bSlant=TRUE;
		}
	}

	if ((Shogo.x>=3200) && (Shogo.x<3350)) 
	{
		floory=900;
		if (y_pos>108)	x_min=3210;
		else x_min=25;
		if (y_pos>230)	x_max=3340;
		else x_max=8300;
		bSlant=FALSE;
	}

	if ((Shogo.x>=3350) && (Shogo.x<3720)) 
	{
		floory=230;
		x_min=25;
		if (y_pos>120)	x_max=3710;
		else x_max=8300;
	}

	if ((Shogo.x>=3720) && (Shogo.x<4250)) 
	{
		floory=120;
		x_min=25;
		x_max=8300;
	}
	
	if ((Shogo.x>=4250) && (Shogo.x<4350)) 
	{
		floory=900;
		if (y_pos>120)	x_min=4260;
		else x_min=25;
		if (y_pos>140)	x_max=4340;
		else x_max=8300;
	}
	
	if ((Shogo.x>=4350) && (Shogo.x<4830)) 
	{
		floory=140;
		x_min=25;
		x_max=8300;
	}
	
	if ((Shogo.x>=4830) && (Shogo.x<5330)) 
	{
		floory=233;
		if (y_pos>140)	x_min=4840;
		else x_min=25;
		if (y_pos>100)	x_max=5320;
		else x_max=8300;
	}
	
	if ((Shogo.x>=5330) && (Shogo.x<5890)) 
	{
		floory=100;
		x_min=25;
		x_max=8300;
	}
	
	if ((Shogo.x>=5890) && (Shogo.x<6070)) 
	{
		floory=900;
		if (y_pos>100)	x_min=5900;
		else x_min=25;
		if (y_pos>183 && y_pos<=240) x_max=6060;
		else x_max=8300;
	}

	if ((Shogo.x>=6070) && (Shogo.x<6360)) 
	{
		floory=183;
		x_min=25;
		x_max=8300;
		if (y_pos>240) { floory=900; }
	}

	if ((Shogo.x>=6360) && (Shogo.x<6450)) 
	{
		floory=900;
		if (y_pos>183 && y_pos<=240) x_min=6370;
		else x_min=25;
		if (y_pos>257) x_max=6440;
		else x_max=8300;
	}

	if ((Shogo.x>=6450) && (Shogo.x<6720)) 
	{
		floory=260;
		x_min=25;
		x_max=8300;
	}

	if ((Shogo.x>=6720) && (Shogo.x<8300))
	{
		floory=156;
		if (y_pos>257)	x_min=6760;
		else x_min=25;
		x_max=7980;
		if (y_pos>200) { floory=900; }
	}
	if (Shogo.x>=7980)
	{
		clev=1.3;
		bScroll=FALSE;
		x_pos=30;
		mapx_pos=0;
		mapendx_pos=640;
		x_min=30;
		x_max=520;
		backx_pos=0;
		backwidth=640;
		y_pos=0;
		floory=280;
		Shogo.x=30;
	}
}

void input()
{
	UCHAR keystate[256];

	if(lpDIKey->GetDeviceState(256, keystate)!=DI_OK) {ErrStr=Err_GetState;}

	if(keystate[DIK_K] & 0x80) { Shogo.health--; }
	if(keystate[DIK_S] & 0x80) { Shogo.special--; }
	if((keystate[DIK_UP] & 0x80) && (bLadder==TRUE) && (bHurt==FALSE)) { y_pos=y_pos-4; }
	if((keystate[DIK_RIGHT] & 0x80) && (bFiring==FALSE) && (Shogo.x<x_max) && (bHurt==FALSE)) 
	{  
		direction=RIGHT;
		bRun=TRUE;
		Shogo.x+=10;
		if (bScroll==TRUE) 
		{
			mapx_pos+=10;
			mapendx_pos+=10;	
			backx_pos+=2;
			backwidth+=2;
		}
		else
		{
			x_pos+=10;
			mapx_pos=0;
			mapendx_pos=640;
			backx_pos=0;
			backwidth=640;
		}
	}
	else if((keystate[DIK_LEFT] & 0x80) && (bFiring==FALSE) && (Shogo.x>x_min) && (bHurt==FALSE))
	{  
		direction=LEFT;
		bRun=TRUE;
		Shogo.x-=10;
		if (bScroll==TRUE)
		{
			mapx_pos-=10;
			mapendx_pos-=10;	
			backx_pos-=2;
			backwidth-=2;
		}
		else
		{
			x_pos-=10;
			mapx_pos=0;
			mapendx_pos=640;
			backx_pos=0;
			backwidth=640;
		}
	}
	else bRun=FALSE;
	if((keystate[DIK_SPACE] & 0x80) && (bHurt==FALSE)) { 
		if (bJumpDone==TRUE && bRelease==TRUE) bJump=TRUE; 
		bFall=TRUE; 
		bJumpDone=FALSE; 
		bRelease=FALSE;
	} 
	else { bJump=FALSE; bRelease=TRUE;}
	if((keystate[DIK_LCONTROL] & 0x80) || (keystate[DIK_RCONTROL] & 0x80) && (bHurt==FALSE)) { bFiring=TRUE; bAnimDone=FALSE; }
	else { bFiring=FALSE; bAnimDone=TRUE; bPunch=FALSE; }	
}

void getrect1a()
{
	rcRect.left = backx_pos; 
	rcRect.top = 0;
	rcRect.right = backwidth; 
	rcRect.bottom = 480; 
	l1Rect.left = mapx_pos; 
	l1Rect.top = 0;
	l1Rect.right = mapendx_pos; 
	l1Rect.bottom = 480;
	amRect.left = 0; 
	amRect.top = 0; 
	amRect.right = 24; 
	amRect.bottom = 25; 
	
	cotRect.left=CotA.x-mapx_pos;
	cotRect.top=CotA.y;
	if (cotRect.left>530) cotRect.right=(CotA.x-mapx_pos) + (640-cotRect.left);
	else cotRect.right=(CotA.x-mapx_pos)+110;
	cotRect.bottom=CotA.y+69;

	cotColRect.left=CotA.x-mapx_pos + 25;
	cotColRect.top=CotA.y + 30;
	cotColRect.right=(CotA.x-mapx_pos)+85;
	cotColRect.bottom=CotA.y+59;

	cot2Rect.left=0;
	cot2Rect.top=0;
	if (cotRect.left>530) cot2Rect.right=640-cotRect.left;
	else cot2Rect.right=110;
	cot2Rect.bottom=69;

	spikeRect.left=SpikeA.x-mapx_pos;
	spikeRect.top=SpikeA.y;
	if (spikeRect.left>530) spikeRect.right=(SpikeA.x-mapx_pos) + (640-spikeRect.left);
	else spikeRect.right=(SpikeA.x-mapx_pos)+109;
	spikeRect.bottom=SpikeA.y+107;

	spikeColRect.left=SpikeA.x-mapx_pos + 25;
	spikeColRect.top=SpikeA.y + 30;
	spikeColRect.right=(SpikeA.x-mapx_pos)+85;
	spikeColRect.bottom=SpikeA.y+59;

	spike2Rect.left=0;
	spike2Rect.top=0;
	if (spikeRect.left>530) spike2Rect.right=640-spikeRect.left;
	else spike2Rect.right=109;
	spike2Rect.bottom=107;

	rockRect.left=RockA.x-mapx_pos;
	rockRect.top=RockA.y;
	if (rockRect.left>596) rockRect.right=(RockA.x-mapx_pos) + (640-rockRect.left);
	else rockRect.right=(RockA.x-mapx_pos)+44;
	rockRect.bottom=RockA.y+33;

	rockColRect.left=RockA.x-mapx_pos;
	rockColRect.top=RockA.y;
	rockColRect.right=(RockA.x-mapx_pos)+44;
	rockColRect.bottom=RockA.y+33;

	rock2Rect.left=0;
	rock2Rect.top=0;
	if (rockRect.left>596) rock2Rect.right=640-rockRect.left;
	else rock2Rect.right=44;
	rock2Rect.bottom=33;

	flipRect.left = x_pos-20;
	if (y_pos<0)flipRect.top = 0; 
	else flipRect.top = y_pos;
	flipRect.right = x_pos + 90; 
	if (y_pos>367) flipRect.bottom = 480;
	else flipRect.bottom = y_pos + 117; 
	
	flip2Rect.left = 0;
	if (y_pos<0)flip2Rect.top = -1*y_pos;
	else flip2Rect.top = 0;
	flip2Rect.right = 110; 
	if (y_pos>367) flip2Rect.bottom = 480-y_pos;
	else flip2Rect.bottom = 117; 
	
	normRect.left = x_pos; 
	if (y_pos<0)normRect.top = 0; 
	else normRect.top = y_pos;
	normRect.right = x_pos + 110; 
	if (y_pos>367) normRect.bottom = 480;
	else normRect.bottom = y_pos + 117;
	
	norm2Rect.left = 0; 
	if (y_pos<0) norm2Rect.top = -1*y_pos; 
	else norm2Rect.top = 0;
	norm2Rect.right = 110; 
	if (y_pos>367) norm2Rect.bottom = 480-y_pos;
	else norm2Rect.bottom = 117;
	
	if (direction==LEFT) ShogoColRect.left=x_pos+30;
	else ShogoColRect.left=x_pos+25;
	ShogoColRect.top=y_pos+20;
	if (direction==LEFT) ShogoColRect.right=x_pos + 65;
	else ShogoColRect.right=x_pos + 65;
	ShogoColRect.bottom=y_pos + 100;


	hRect.top=0;
	hRect.bottom=17;
	hRect.left=0;
	if (Shogo.health<0) Shogo.health=0;
	hRect.right=20 + (Shogo.health * 1.3);

	h2Rect.top=4;
	h2Rect.bottom=21;
	h2Rect.left=6;
	if (Shogo.health<0) Shogo.health=0;
	h2Rect.right=26 + (Shogo.health * 1.3);

	hudRect.top=0;
	hudRect.bottom=50;
	hudRect.left=0;
	hudRect.right=640;
		;
	sRect.top=0;
	sRect.bottom=17;
	sRect.left=0;
	if (Shogo.special<0) Shogo.special=0;
	sRect.right=20 + (Shogo.special * 1.3);

	s2Rect.top=21;
	s2Rect.bottom=38;
	s2Rect.left=6;
	s2Rect.right=26 + (Shogo.special * 1.3);
		
}

void renderCotA()
{
	if (GetTickCount() - cota_time > 3600)
	{
		cota_time=GetTickCount();
	}
	else if (GetTickCount() - cota_time <= 150)
	{
		lpDDSBack->Blt(&cotRect,cot1,&cot2Rect, DDBLT_KEYSRC, NULL );
		if (CotA.y<149) CotA.y=149;
		if (CotA.y>151) CotA.y=151;
		CotA.y++;
	}
	else if ((GetTickCount() - cota_time > 150) && (GetTickCount() - cota_time <= 300))
	{
		lpDDSBack->Blt(&cotRect,cot2,&cot2Rect, DDBLT_KEYSRC, NULL );
		if (CotA.y<149) CotA.y=149;
		if (CotA.y>151) CotA.y=151;
		CotA.y--;
	}
	else if ((GetTickCount() - cota_time > 300) && (GetTickCount() - cota_time <= 450))
	{
		lpDDSBack->Blt(&cotRect,cot1,&cot2Rect, DDBLT_KEYSRC, NULL );
		if (CotA.y<149) CotA.y=149;
		if (CotA.y>151) CotA.y=151;
		CotA.y++;
	}
	else if ((GetTickCount() - cota_time > 450) && (GetTickCount() - cota_time <= 600))
	{
		lpDDSBack->Blt(&cotRect,cot2,&cot2Rect, DDBLT_KEYSRC, NULL );
		if (CotA.y<149) CotA.y=149;
		if (CotA.y>151) CotA.y=151;
		CotA.y--;
	}
	else if ((GetTickCount() - cota_time > 600) && (GetTickCount() - cota_time <= 750))
	{
		lpDDSBack->Blt(&cotRect,cot1,&cot2Rect, DDBLT_KEYSRC, NULL );
		if (CotA.y<149) CotA.y=149;
		if (CotA.y>151) CotA.y=151;
		CotA.y++;
	}
	else if ((GetTickCount() - cota_time > 750) && (GetTickCount() - cota_time <= 900))
	{
		lpDDSBack->Blt(&cotRect,cot2,&cot2Rect, DDBLT_KEYSRC, NULL );
		if (CotA.y<149) CotA.y=149;
		if (CotA.y>151) CotA.y=151;
		CotA.y--;
	}
	else if ((GetTickCount() - cota_time > 900) && (GetTickCount() - cota_time <= 1050))
	{
		lpDDSBack->Blt(&cotRect,cot1,&cot2Rect, DDBLT_KEYSRC, NULL );
		if (CotA.y<149) CotA.y=149;
		if (CotA.y>151) CotA.y=151;
		CotA.y++;
	}
	else if ((GetTickCount() - cota_time > 1050) && (GetTickCount() - cota_time <= 1200))
	{
		lpDDSBack->Blt(&cotRect,cot2,&cot2Rect, DDBLT_KEYSRC, NULL );
		if (CotA.y<149) CotA.y=149;
		if (CotA.y>151) CotA.y=151;
		CotA.y--;
	}
	else if ((GetTickCount() - cota_time > 1200) && (GetTickCount() - cota_time <= 1350))
	{
		lpDDSBack->Blt(&cotRect,cot3,&cot2Rect, DDBLT_KEYSRC, NULL );
		CotA.y=CotA.y+12;
		CotA.x=CotA.x-10;
		if (cotRect.left>0 && cotRect.left<640) electric_voc.lpDSBuffer->Play(0,0,0);
	}
	else if ((GetTickCount() - cota_time > 1350) && (GetTickCount() - cota_time <= 1500))
	{
		lpDDSBack->Blt(&cotRect,cot4,&cot2Rect, DDBLT_KEYSRC, NULL );
		CotA.y=CotA.y+12;
		CotA.x=CotA.x-10;
	    if (cotRect.left>0 && cotRect.left<640)	electric_voc.lpDSBuffer->Play(0,0,0);
	}
 	else if ((GetTickCount() - cota_time > 1500) && (GetTickCount() - cota_time <= 1650))
	{
		lpDDSBack->Blt(&cotRect,cot5,&cot2Rect, DDBLT_KEYSRC, NULL );
		CotA.y=CotA.y-12;
		CotA.x=CotA.x-10;
		if (cotRect.left>0 && cotRect.left<640) electric_voc.lpDSBuffer->Play(0,0,0);
	}
	else if ((GetTickCount() - cota_time > 1650) && (GetTickCount() - cota_time <= 1800))
	{
		lpDDSBack->Blt(&cotRect,cot6,&cot2Rect, DDBLT_KEYSRC, NULL );
		CotA.y=CotA.y-12;
		CotA.x=CotA.x-10;
		if (cotRect.left>0 && cotRect.left<640) electric_voc.lpDSBuffer->Play(0,0,0);
	}
	else if ((GetTickCount() - cota_time <= 1800) && (GetTickCount() - cota_time <= 1950))
	{
		lpDDSBack->Blt(&cotRect,cot1,&cot2Rect, DDBLT_KEYSRC, NULL );
		if (CotA.y<149) CotA.y=149;
		if (CotA.y>151) CotA.y=151;
		CotA.y++;
	}
	else if ((GetTickCount() - cota_time > 1950) && (GetTickCount() - cota_time <= 2100))
	{
		lpDDSBack->Blt(&cotRect,cot2,&cot2Rect, DDBLT_KEYSRC, NULL );
		if (CotA.y<149) CotA.y=149;
		if (CotA.y>151) CotA.y=151;
		CotA.y--;
	}
	else if ((GetTickCount() - cota_time > 2100) && (GetTickCount() - cota_time <= 2250))
	{
		lpDDSBack->Blt(&cotRect,cot1,&cot2Rect, DDBLT_KEYSRC, NULL );
		if (CotA.y<149) CotA.y=149;
		if (CotA.y>151) CotA.y=151;
		CotA.y++;
	}
	else if ((GetTickCount() - cota_time > 2250) && (GetTickCount() - cota_time <= 2400))
	{
		lpDDSBack->Blt(&cotRect,cot2,&cot2Rect, DDBLT_KEYSRC, NULL );
		if (CotA.y<149) CotA.y=149;
		if (CotA.y>151) CotA.y=151;
		CotA.y--;
	}
	else if ((GetTickCount() - cota_time > 2400) && (GetTickCount() - cota_time <= 2550))
	{
		lpDDSBack->Blt(&cotRect,cot1,&cot2Rect, DDBLT_KEYSRC, NULL );
		if (CotA.y<149) CotA.y=149;
		if (CotA.y>151) CotA.y=151;
		CotA.y++;
	}
	else if ((GetTickCount() - cota_time > 2550) && (GetTickCount() - cota_time <= 2700))
	{
		lpDDSBack->Blt(&cotRect,cot2,&cot2Rect, DDBLT_KEYSRC, NULL );
		if (CotA.y<149) CotA.y=149;
		if (CotA.y>151) CotA.y=151;
		CotA.y--;
	}
	else if ((GetTickCount() - cota_time > 2700) && (GetTickCount() - cota_time <= 2850))
	{
		lpDDSBack->Blt(&cotRect,cot1,&cot2Rect, DDBLT_KEYSRC, NULL );
		if (CotA.y<149) CotA.y=149;
		if (CotA.y>151) CotA.y=151;
		CotA.y++;
	}
	else if ((GetTickCount() - cota_time > 2850) && (GetTickCount() - cota_time <= 3000))
	{
		lpDDSBack->Blt(&cotRect,cot2,&cot2Rect, DDBLT_KEYSRC, NULL );
		if (CotA.y<149) CotA.y=149;
		if (CotA.y>151) CotA.y=151;
		CotA.y--;
	}
	else if ((GetTickCount() - cota_time > 3000) && (GetTickCount() - cota_time <= 3150))
	{
		lpDDSBack->Blt(&cotRect,cot3,&cot2Rect, DDBLT_KEYSRC, NULL );
		CotA.y=CotA.y+12;
		CotA.x=CotA.x+10;
		if (cotRect.left>0 && cotRect.left<640) electric_voc.lpDSBuffer->Play(0,0,0);
	}
	else if ((GetTickCount() - cota_time > 3150) && (GetTickCount() - cota_time <= 3300))
	{
		lpDDSBack->Blt(&cotRect,cot4,&cot2Rect, DDBLT_KEYSRC, NULL );
		CotA.y=CotA.y+12;
		CotA.x=CotA.x+10;
		if (cotRect.left>0 && cotRect.left<640) electric_voc.lpDSBuffer->Play(0,0,0);
	}
 	else if ((GetTickCount() - cota_time > 3300) && (GetTickCount() - cota_time <= 3450))
	{
		lpDDSBack->Blt(&cotRect,cot5,&cot2Rect, DDBLT_KEYSRC, NULL );
		CotA.y=CotA.y-12;
		CotA.x=CotA.x+10;
		if (cotRect.left>0 && cotRect.left<640) electric_voc.lpDSBuffer->Play(0,0,0);
	}
	else if ((GetTickCount() - cota_time > 3450) && (GetTickCount() - cota_time <= 3600))
	{
		lpDDSBack->Blt(&cotRect,cot6,&cot2Rect, DDBLT_KEYSRC, NULL );
		CotA.y=CotA.y-12;
		CotA.x=CotA.x+10;
		if (cotRect.left>0 && cotRect.left<640) electric_voc.lpDSBuffer->Play(0,0,0);
	}
}

void renderCotADie()
{
	if (CotA.adead==FALSE) { cota_time2 = GetTickCount(); CotA.adead=TRUE; }
	if (GetTickCount() - cota_time2 <= 150)
	{
		lpDDSBack->Blt(&cotRect,cotexplo1,&cot2Rect, DDBLT_KEYSRC, NULL );
		explo1_voc.lpDSBuffer->Play(0,0,0);
	}
	else if ((GetTickCount() - cota_time2 > 150) && (GetTickCount() - cota_time2 <= 300))
	{
		lpDDSBack->Blt(&cotRect,cotexplo2,&cot2Rect, DDBLT_KEYSRC, NULL );
		explo1_voc.lpDSBuffer->Play(0,0,0);
	}
	else if ((GetTickCount() - cota_time2 > 300) && (GetTickCount() - cota_time2 <= 450))
	{
		lpDDSBack->Blt(&cotRect,cotexplo3,&cot2Rect, DDBLT_KEYSRC, NULL );
		explo1_voc.lpDSBuffer->Play(0,0,0);
	}
	else if ((GetTickCount() - cota_time2 > 450) && (GetTickCount() - cota_time2 <= 600))
	{
		lpDDSBack->Blt(&cotRect,cotexplo4,&cot2Rect, DDBLT_KEYSRC, NULL );
		explo1_voc.lpDSBuffer->Play(0,0,0);
	}
	else if ((GetTickCount() - cota_time2 > 600) && (GetTickCount() - cota_time2 <= 750))
	{
		lpDDSBack->Blt(&cotRect,cotexplo5,&cot2Rect, DDBLT_KEYSRC, NULL );
	}
	else if ((GetTickCount() - cota_time2 > 750) && (GetTickCount() - cota_time2 <= 900))
	{
		lpDDSBack->Blt(&cotRect,cotexplo6,&cot2Rect, DDBLT_KEYSRC, NULL );
	}
	else if ((GetTickCount() - cota_time2 > 900) && (GetTickCount() - cota_time2 <= 1050))
	{
		lpDDSBack->Blt(&cotRect,cotexplo7,&cot2Rect, DDBLT_KEYSRC, NULL );
	}
}

void rocketA()
{
	if (GetTickCount() - rocka_time > 400)
	{
		rocka_time=GetTickCount();
		lpDDSBack->Blt(&rockRect,r1,&rock2Rect, DDBLT_KEYSRC, NULL );
		RockA.x-=5;
	}
	else if (GetTickCount() - rocka_time <= 100)
	{
		lpDDSBack->Blt(&rockRect,r1,&rock2Rect, DDBLT_KEYSRC, NULL );
		RockA.x-=5;
	}
	else if ((GetTickCount() - rocka_time > 100) && (GetTickCount() - rocka_time <= 200))
	{
		lpDDSBack->Blt(&rockRect,r2,&rock2Rect, DDBLT_KEYSRC, NULL );
		RockA.x-=5;
	}
	else if ((GetTickCount() - rocka_time > 200) && (GetTickCount() - rocka_time <= 300))
	{
		lpDDSBack->Blt(&rockRect,r3,&rock2Rect, DDBLT_KEYSRC, NULL );
		RockA.x-=5;
	}
	else if ((GetTickCount() - rocka_time > 300) && (GetTickCount() - rocka_time <= 400))
	{
		lpDDSBack->Blt(&rockRect,r4,&rock2Rect, DDBLT_KEYSRC, NULL );
		RockA.x-=5;
	}
}

void renderSpikeA()
{
	if ((Shogo.x<SpikeA.x-200) || (rockcnt>0))
	{
		if (GetTickCount() - spikea_time > 600)
		{
			spikea_time=GetTickCount();
			lpDDSBack->Blt(&spikeRect,spike1,&spike2Rect, DDBLT_KEYSRC, NULL );
			if (SpikeA.y<179) CotA.y=179;
			if (SpikeA.y>181) CotA.y=181;
		}
		else if (GetTickCount() - spikea_time <= 150)
		{
			lpDDSBack->Blt(&spikeRect,spike1,&spike2Rect, DDBLT_KEYSRC, NULL );
			if (SpikeA.y<179) SpikeA.y=179;
			if (SpikeA.y>181) SpikeA.y=181;
			SpikeA.y++;
		}
		else if ((GetTickCount() - spikea_time > 150) && (GetTickCount() - spikea_time <= 300))
		{
			lpDDSBack->Blt(&spikeRect,spike2,&spike2Rect, DDBLT_KEYSRC, NULL );
			if (SpikeA.y<179) SpikeA.y=179;
			if (SpikeA.y>181) SpikeA.y=181;	
			SpikeA.y--;
		}
		else if ((GetTickCount() - spikea_time > 300) && (GetTickCount() - spikea_time <= 450))
		{
			lpDDSBack->Blt(&spikeRect,spike3,&spike2Rect, DDBLT_KEYSRC, NULL );
			if (SpikeA.y<179) SpikeA.y=179;
			if (SpikeA.y>181) SpikeA.y=181;	
			SpikeA.y++;
		}
		else if ((GetTickCount() - spikea_time > 450) && (GetTickCount() - spikea_time <= 600))
		{
			lpDDSBack->Blt(&spikeRect,spike4,&spike2Rect, DDBLT_KEYSRC, NULL );
			if (SpikeA.y<179) SpikeA.y=179;
			if (SpikeA.y>181) SpikeA.y=181;	
			SpikeA.y--;
		}
	}
	else {
		if (GetTickCount() - spikea_time > 850)
		{
			spikea_time=GetTickCount();
			lpDDSBack->Blt(&spikeRect,spike5,&spike2Rect, DDBLT_KEYSRC, NULL );
			if (SpikeA.y<179) CotA.y=179;
			if (SpikeA.y>181) CotA.y=181;
		}
		else if (GetTickCount() - spikea_time <= 150)
		{
			lpDDSBack->Blt(&spikeRect,spike5,&spike2Rect, DDBLT_KEYSRC, NULL );
			if (SpikeA.y<179) SpikeA.y=179;
			if (SpikeA.y>181) SpikeA.y=181;
			SpikeA.y++;
		}
		else if ((GetTickCount() - spikea_time > 150) && (GetTickCount() - spikea_time <= 300))
		{
			lpDDSBack->Blt(&spikeRect,spike6,&spike2Rect, DDBLT_KEYSRC, NULL );
			if (SpikeA.y<179) SpikeA.y=179;
			if (SpikeA.y>181) SpikeA.y=181;	
			SpikeA.y--;
		}
		else if ((GetTickCount() - spikea_time > 300) && (GetTickCount() - spikea_time <= 450))
		{
			lpDDSBack->Blt(&spikeRect,spike7,&spike2Rect, DDBLT_KEYSRC, NULL );
			if (SpikeA.y<179) SpikeA.y=179;
			if (SpikeA.y>181) SpikeA.y=181;	
			SpikeA.y++;
		}
		else if ((GetTickCount() - spikea_time > 450) && (GetTickCount() - spikea_time <= 900))
		{
			lpDDSBack->Blt(&spikeRect,spike8,&spike2Rect, DDBLT_KEYSRC, NULL );
			if (SpikeA.y<179) SpikeA.y=179;
			if (SpikeA.y>181) SpikeA.y=181;	
			SpikeA.y--;
			if (rockcnt==0) { rockcnt++; }
		}
		else if ((GetTickCount() - spikea_time > 900) && (GetTickCount() - spikea_time <= 1000))
		{
			lpDDSBack->Blt(&spikeRect,spike9,&spike2Rect, DDBLT_KEYSRC, NULL );
			if (SpikeA.y<179) SpikeA.y=179;
			if (SpikeA.y>181) SpikeA.y=181;	
			SpikeA.y++;
		}
	}
}

bool Collision_Test(int Coltop, int Colbottom, int Colleft, int Colright, int Shogtop, int Shogbottom, int Shogleft, int Shogright)
{
	if ((Coltop>Shogtop) && (Colleft>Shogleft)
		&& (Coltop<Shogbottom) && (Colleft<Shogright)) 
	{
		return TRUE;
	}
	else if ((Coltop>Shogtop) && (Colright>Shogleft)
		&& (Coltop<Shogbottom) && (Colright<Shogright)) 
	{
		return TRUE;
	}
	else if ((Colbottom>Shogtop) && (Colleft>Shogleft)
		&& (Colbottom<Shogbottom) && (Colleft<Shogright)) 
	{
		return TRUE;
	}
	else if ((Colbottom>Shogtop) && (Colright>Shogleft)
		&& (Colbottom<Shogbottom) && (Colright<Shogright)) 
	{
		return TRUE;
	}

	if ((Shogtop>Coltop) && (Shogleft>Colleft)
		&& (Shogtop<Colbottom) && (Shogleft<Colright)) 
	{
		return TRUE;
	}
	else if ((Shogtop>Coltop) && (Shogright>Colleft)
		&& (Shogtop<Colbottom) && (Shogright<Colright)) 
	{
		return TRUE;
	}
	else if ((Shogbottom>Coltop) && (Shogleft>Colleft)
		&& (Shogbottom<Colbottom) && (Shogleft<Colright)) 
	{
		return TRUE;
	}
	else if ((Shogbottom>Coltop) && (Shogright>Colleft)
		&& (Shogbottom<Colbottom) && (Shogright<Colright)) 
	{
		return TRUE;
	}

	else { return FALSE; }
}


void render_frame()
{
	DDBLTFX ddbltfx;

	ZeroMemory(&ddbltfx,sizeof(ddbltfx));
	ddbltfx.dwSize = sizeof(ddbltfx);
	ddbltfx.dwDDFX=DDBLTFX_MIRRORLEFTRIGHT;
		
	// draw the object to the screen
	if (clev==1)
	{
	lpDDSBack->BltFast(0,0,back_surf,&rcRect,DDBLTFAST_WAIT);
	lpDDSBack->BltFast(0,0,lev1,&l1Rect,DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	}
	else if (clev==1.2)
	{
	lpDDSBack->BltFast(0,0,back_surf,&rcRect,DDBLTFAST_WAIT);
	lpDDSBack->BltFast(0,0,lev2,&l1Rect,DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	}
	else if (clev==1.3)
	{
	lpDDSBack->BltFast(0,0,bossbg,&rcRect,DDBLTFAST_WAIT);
	lpDDSBack->BltFast(0,0,boss1,&l1Rect,DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
	}

	if (bAnimDone==TRUE) start_time = GetTickCount();
	if (bJump==FALSE) jump_time = GetTickCount(); 
	if (bFall==TRUE && bJump==TRUE) fall_time = GetTickCount();
	
	if (bHurt==TRUE && direction==LEFT)
	{
		bStep=FALSE;
		if (GetTickCount() - hurt_time < 100)
		{
			lpDDSBack->Blt(&flipRect,ShogoInjure1,&flip2Rect,DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		}
		else if ((GetTickCount() - hurt_time >= 100) && (GetTickCount() - hurt_time < 200))
		{
			lpDDSBack->Blt(&flipRect,ShogoInjure2,&flip2Rect,DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		}
		else if ((GetTickCount() - hurt_time >= 200) && (GetTickCount() - hurt_time < 300))
		{
			lpDDSBack->Blt(&flipRect,ShogoInjure3,&flip2Rect,DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		}
		else if ((GetTickCount() - hurt_time >= 300) && (GetTickCount() - hurt_time < 400))
		{
			lpDDSBack->Blt(&flipRect,ShogoInjure2,&flip2Rect,DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		}
		else if (GetTickCount() - hurt_time > 400)
		{
			lpDDSBack->Blt(&flipRect,ShogoInjure3,&flip2Rect,DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
			bHurt=FALSE;
		}
	}
	else if (bHurt==TRUE && direction==RIGHT)
	{
		bStep=FALSE;
		if (GetTickCount() - hurt_time < 100)
		{
			lpDDSBack->Blt(&normRect,ShogoInjure1,&norm2Rect, DDBLT_KEYSRC, NULL );
		}
		else if ((GetTickCount() - hurt_time >= 100) && (GetTickCount() - hurt_time < 200))
		{
			lpDDSBack->Blt(&normRect,ShogoInjure2,&norm2Rect, DDBLT_KEYSRC, NULL );
		}
		else if ((GetTickCount() - hurt_time >= 200) && (GetTickCount() - hurt_time < 300))
		{
			lpDDSBack->Blt(&normRect,ShogoInjure3,&norm2Rect, DDBLT_KEYSRC, NULL );
		}
		else if ((GetTickCount() - hurt_time >= 300) && (GetTickCount() - hurt_time < 400))
		{
			lpDDSBack->Blt(&normRect,ShogoInjure2,&norm2Rect, DDBLT_KEYSRC, NULL );
		}
		else if (GetTickCount() - hurt_time > 400)
		{
			lpDDSBack->Blt(&normRect,ShogoInjure3,&norm2Rect, DDBLT_KEYSRC, NULL );
			bHurt=FALSE;
		}
	}
	else if ((bJump==FALSE) && (bLadder==FALSE) && (direction==RIGHT) && (y_pos!=floory) && (bSlant==FALSE))
	{
		bStep=FALSE;
		if (GetTickCount() - fall_time < 100) 
		{	y_pos=y_pos;
			lpDDSBack->Blt(&normRect,ShogoFall1,&norm2Rect, DDBLT_KEYSRC, NULL );
		}
		else if ((GetTickCount() - fall_time >=100) && ((floory-10)>=y_pos)) 
		{
			y_pos=y_pos+14;
			lpDDSBack->Blt(&normRect,ShogoFall2,&norm2Rect, DDBLT_KEYSRC, NULL );
		}
		else if ((GetTickCount() - fall_time >=200) && ((floory-10)>=y_pos)) 
		{
			y_pos=y_pos+14;
			lpDDSBack->Blt(&normRect,ShogoFall3,&norm2Rect, DDBLT_KEYSRC, NULL );
		}
		else {	
			y_pos=floory; 
			if (bJumpDone==FALSE) { land_voc.lpDSBuffer->Play(0,0,0); }
		}
	}
	else if ((bJump==FALSE) && (bLadder==FALSE) && (direction==LEFT) && (y_pos!=floory) && (bSlant==FALSE))
	{
		bStep=FALSE;
		if (GetTickCount() - fall_time < 100) 
		{	y_pos=y_pos;
			lpDDSBack->Blt(&flipRect,ShogoFall1,&flip2Rect,DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		}
		else if ((GetTickCount() - fall_time >=100) && ((floory-10)>=y_pos)) 
		{
			y_pos=y_pos+14;
			lpDDSBack->Blt(&flipRect,ShogoFall2,&flip2Rect,DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		}
		else if ((GetTickCount() - fall_time >=200) && ((floory-10)>=y_pos)) 
		{
			y_pos=y_pos+14;
			lpDDSBack->Blt(&flipRect,ShogoFall3,&flip2Rect,DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		}
		else {	
			y_pos=floory; 
			if (bJumpDone==FALSE) { land_voc.lpDSBuffer->Play(0,0,0); }
		}
	}
	else if (bJump==TRUE && bJumpDone==FALSE && direction==RIGHT)
	{
		bStep=FALSE;
		if (GetTickCount() - jump_time < 60)
		{ 
			y_pos=y_pos-65;
			lpDDSBack->Blt(&normRect,ShogoJump1,&norm2Rect, DDBLT_KEYSRC, NULL );
		}
		else if ((GetTickCount() - jump_time >=60) && (GetTickCount() - jump_time < 120)) 
		{
			y_pos=y_pos-20;
			lpDDSBack->Blt(&normRect,ShogoJump2,&norm2Rect, DDBLT_KEYSRC, NULL );
		}
		else if ((GetTickCount() - jump_time >=120) && (GetTickCount() - jump_time < 180))
		{
			y_pos=y_pos-15;
			lpDDSBack->Blt(&normRect,ShogoJump3,&norm2Rect, DDBLT_KEYSRC, NULL );
		}
		else if ((GetTickCount() - jump_time >=180) && (GetTickCount() - jump_time < 240)) 
		{
			y_pos=y_pos-10;
			lpDDSBack->Blt(&normRect,ShogoJump4,&norm2Rect, DDBLT_KEYSRC, NULL );
		}
		else { 
			bJump=FALSE; 
			lpDDSBack->Blt(&normRect,ShogoJump4,&norm2Rect, DDBLT_KEYSRC, NULL ); 
			jump_time = GetTickCount();
		}
	}
	else if (bJump==TRUE && bJumpDone==FALSE && direction==LEFT)
	{
		bStep=FALSE;
		if (GetTickCount() - jump_time < 60) 
		{ 
			y_pos=y_pos-65; 
			lpDDSBack->Blt(&flipRect,ShogoJump1,&flip2Rect,DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		}
		else if ((GetTickCount() - jump_time >=60) && (GetTickCount() - jump_time < 120)) 
		{
			y_pos=y_pos-20;
			lpDDSBack->Blt(&flipRect,ShogoJump2,&flip2Rect,DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		}
		else if ((GetTickCount() - jump_time >=120) && (GetTickCount() - jump_time < 180)) 
		{
			y_pos=y_pos-15;
			lpDDSBack->Blt(&flipRect,ShogoJump3,&flip2Rect,DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		}
		else if ((GetTickCount() - jump_time >=180) && (GetTickCount() - jump_time < 240))
		{
			y_pos=y_pos-10;
			lpDDSBack->Blt(&flipRect,ShogoJump4,&flip2Rect,DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		}
		else { 
			bJump=FALSE;
			lpDDSBack->Blt(&flipRect,ShogoJump4,&flip2Rect,DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx ); 
			jump_time = GetTickCount();
		}
	}
	else if (bFiring==TRUE && direction==LEFT && bClimb==FALSE) 	
	{
		bStep=FALSE;
		if ((GetTickCount() - start_time < 100) && (bPunch==FALSE))
		{
			lpDDSBack->Blt(&flipRect,ShogoHit1,&flip2Rect,DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
			bPunch=TRUE;
		}
		else if ((GetTickCount() - start_time < 100) && (bPunch==TRUE)) 
		{
			lpDDSBack->Blt(&flipRect,ShogoHit2,&flip2Rect,DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );		
		}
		else if ((GetTickCount() - start_time >= 100) && (GetTickCount() - start_time < 200)) 
		{
			lpDDSBack->Blt(&flipRect,ShogoHit3,&flip2Rect,DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );		
		}
		else if ((GetTickCount() - start_time >= 200) && (GetTickCount() - start_time < 300)) 
		{
			lpDDSBack->Blt(&flipRect,ShogoHit4,&flip2Rect,DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );		
		}
		else if ((GetTickCount() - start_time >= 300) && (GetTickCount() - start_time < 400)) 
		{
			lpDDSBack->Blt(&flipRect,ShogoHit3,&flip2Rect,DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );		
		}
		else {
		start_time= GetTickCount();
		lpDDSBack->Blt(&flipRect,ShogoHit2,&flip2Rect,DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		}
	}
	else if (bFiring==TRUE && direction==RIGHT && bClimb==FALSE) 	
	{
		bStep=FALSE;
		if ((GetTickCount() - start_time < 100) && (bPunch==FALSE))
		{
			lpDDSBack->Blt(&normRect,ShogoHit1,&norm2Rect, DDBLT_KEYSRC, NULL );
			bPunch=TRUE;
		}
		else if ((GetTickCount() - start_time < 100) && (bPunch==TRUE)) 
		{
			lpDDSBack->Blt(&normRect,ShogoHit2,&norm2Rect, DDBLT_KEYSRC, NULL );
		}
		else if ((GetTickCount() - start_time >= 100) && (GetTickCount() - start_time < 200)) 
		{
			lpDDSBack->Blt(&normRect,ShogoHit3,&norm2Rect, DDBLT_KEYSRC, NULL );
		}
		else if ((GetTickCount() - start_time >= 200) && (GetTickCount() - start_time < 300)) 
		{
			lpDDSBack->Blt(&normRect,ShogoHit4,&norm2Rect, DDBLT_KEYSRC, NULL );
		}
		else if ((GetTickCount() - start_time >= 300) && (GetTickCount() - start_time < 400)) 
		{
			lpDDSBack->Blt(&normRect,ShogoHit3,&norm2Rect, DDBLT_KEYSRC, NULL );
		}
		else {
		start_time= GetTickCount();
		lpDDSBack->Blt(&normRect,ShogoHit2,&norm2Rect, DDBLT_KEYSRC, NULL );
		}
	}
	else if (bFiring==FALSE && direction==LEFT && bRun==TRUE && bClimb==FALSE)
	{
		if (bStep==FALSE) {	steps_voc.lpDSBuffer->Play(0,0,DSBPLAY_LOOPING); bStep=TRUE; }

		if (GetTickCount() - run_time < 150)
			lpDDSBack->Blt(&flipRect,ShogoRun1,&flip2Rect, DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		else if ((GetTickCount() - run_time >= 100) && (GetTickCount() - run_time < 200))
			lpDDSBack->Blt(&flipRect,ShogoRun2,&flip2Rect, DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		else if ((GetTickCount() - run_time >= 200) && (GetTickCount() - run_time < 300))
			lpDDSBack->Blt(&flipRect,ShogoRun3,&flip2Rect, DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		else if ((GetTickCount() - run_time >= 300) && (GetTickCount() - run_time < 400))
			lpDDSBack->Blt(&flipRect,ShogoRun4,&flip2Rect, DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		else if ((GetTickCount() - run_time >= 400) && (GetTickCount() - run_time < 500))
			lpDDSBack->Blt(&flipRect,ShogoRun5,&flip2Rect, DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		else if ((GetTickCount() - run_time >= 500) && (GetTickCount() - run_time < 600))
			lpDDSBack->Blt(&flipRect,ShogoRun6,&flip2Rect, DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		else if ((GetTickCount() - run_time >= 600) && (GetTickCount() - run_time < 700))
			lpDDSBack->Blt(&flipRect,ShogoRun7,&flip2Rect, DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		else if ((GetTickCount() - run_time >= 700) && (GetTickCount() - run_time < 800))
			lpDDSBack->Blt(&flipRect,ShogoRun8,&flip2Rect, DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		else if ((GetTickCount() - run_time >= 800) && (GetTickCount() - run_time < 900))
			lpDDSBack->Blt(&flipRect,ShogoRun9,&flip2Rect, DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		else if ((GetTickCount() - run_time >= 900) && (GetTickCount() - run_time < 1000))
			lpDDSBack->Blt(&flipRect,ShogoRun10,&flip2Rect, DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		else if (GetTickCount() - run_time >= 1000)
		{
			run_time = GetTickCount();
			lpDDSBack->Blt(&flipRect,ShogoRun10,&flip2Rect, DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		}
		if (bSlant==TRUE) y_pos=floory;
	}
	else if (bFiring==FALSE && direction==RIGHT && bRun==TRUE && bClimb==FALSE)
	{
		if (bStep==FALSE) {	steps_voc.lpDSBuffer->Play(0,0,DSBPLAY_LOOPING); bStep=TRUE; }

		if (GetTickCount() - run_time < 150)
			lpDDSBack->Blt(&normRect,ShogoRun1,&norm2Rect, DDBLT_KEYSRC, NULL );
		else if ((GetTickCount() - run_time >= 100) && (GetTickCount() - run_time < 200))
			lpDDSBack->Blt(&normRect,ShogoRun2,&norm2Rect, DDBLT_KEYSRC, NULL );
		else if ((GetTickCount() - run_time >= 200) && (GetTickCount() - run_time < 300))
			lpDDSBack->Blt(&normRect,ShogoRun3,&norm2Rect, DDBLT_KEYSRC, NULL );
		else if ((GetTickCount() - run_time >= 300) && (GetTickCount() - run_time < 400))
			lpDDSBack->Blt(&normRect,ShogoRun4,&norm2Rect, DDBLT_KEYSRC, NULL );
		else if ((GetTickCount() - run_time >= 400) && (GetTickCount() - run_time < 500))
			lpDDSBack->Blt(&normRect,ShogoRun5,&norm2Rect, DDBLT_KEYSRC, NULL );
		else if ((GetTickCount() - run_time >= 500) && (GetTickCount() - run_time < 600))
			lpDDSBack->Blt(&normRect,ShogoRun6,&norm2Rect, DDBLT_KEYSRC, NULL );
		else if ((GetTickCount() - run_time >= 600) && (GetTickCount() - run_time < 700))
			lpDDSBack->Blt(&normRect,ShogoRun7,&norm2Rect, DDBLT_KEYSRC, NULL );
		else if ((GetTickCount() - run_time >= 700) && (GetTickCount() - run_time < 800))
			lpDDSBack->Blt(&normRect,ShogoRun8,&norm2Rect, DDBLT_KEYSRC, NULL );
		else if ((GetTickCount() - run_time >= 800) && (GetTickCount() - run_time < 900))
			lpDDSBack->Blt(&normRect,ShogoRun9,&norm2Rect, DDBLT_KEYSRC, NULL );
		else if ((GetTickCount() - run_time >= 900) && (GetTickCount() - run_time < 1000))
			lpDDSBack->Blt(&normRect,ShogoRun10,&norm2Rect, DDBLT_KEYSRC, NULL );
		else if (GetTickCount() - run_time >= 1000)
		{
			run_time = GetTickCount();
			lpDDSBack->Blt(&normRect,ShogoRun10,&norm2Rect, DDBLT_KEYSRC, NULL );
		}
		if (bSlant==TRUE) y_pos=floory;
	}
	else if (bFiring==FALSE && direction==LEFT && bRun==FALSE && bClimb==FALSE)
	{
		bStep=FALSE;
		run_time = GetTickCount();
		
		if (GetTickCount() - idle_time < 500)
			lpDDSBack->Blt(&flipRect,ShogoStand,&flip2Rect, DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		else if ((GetTickCount() - idle_time >= 500)  && (GetTickCount() - idle_time <1000))
			lpDDSBack->Blt(&flipRect,ShogoIdle,&flip2Rect, DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		else if (GetTickCount() - idle_time >= 1000)
		{
			idle_time = GetTickCount();
			lpDDSBack->Blt(&flipRect,ShogoIdle,&flip2Rect, DDBLT_DDFX | DDBLT_KEYSRC, &ddbltfx );
		}
	}
	else if (bFiring==FALSE && direction==RIGHT && bRun==FALSE && bClimb==FALSE)
	{
		bStep=FALSE;
		run_time = GetTickCount();

		if (GetTickCount() - idle_time < 500)
			lpDDSBack->Blt(&normRect,ShogoStand,&norm2Rect, DDBLT_KEYSRC, NULL );
		else if ((GetTickCount() - idle_time >= 500)  && (GetTickCount() - idle_time <1000))
			lpDDSBack->Blt(&normRect,ShogoIdle,&norm2Rect, DDBLT_KEYSRC, NULL );
		else if (GetTickCount() - idle_time >= 1000)
		{
			idle_time = GetTickCount();
			lpDDSBack->Blt(&normRect,ShogoIdle,&norm2Rect, DDBLT_KEYSRC, NULL );
		}
	}
	else if (bClimb==TRUE)
	{
		bStep=FALSE;
		if (y_pos<268 && y_pos>=244)
			lpDDSBack->Blt(&normRect,ShogoClimb1,&norm2Rect, DDBLT_KEYSRC, NULL );
		else if (y_pos<244 && y_pos>=220)
			lpDDSBack->Blt(&normRect,ShogoClimb2,&norm2Rect, DDBLT_KEYSRC, NULL );
		else if (y_pos<220 && y_pos>=196)
			lpDDSBack->Blt(&normRect,ShogoClimb3,&norm2Rect, DDBLT_KEYSRC, NULL );
		else if (y_pos<196 && y_pos>=172)
			lpDDSBack->Blt(&normRect,ShogoClimb4,&norm2Rect, DDBLT_KEYSRC, NULL );
		else if (y_pos<172 && y_pos>=148)
			lpDDSBack->Blt(&normRect,ShogoClimb1,&norm2Rect, DDBLT_KEYSRC, NULL );
		else if (y_pos<148 && y_pos>=124)
			lpDDSBack->Blt(&normRect,ShogoClimb2,&norm2Rect, DDBLT_KEYSRC, NULL );
		else if (y_pos<124 && y_pos>=100)
			lpDDSBack->Blt(&normRect,ShogoClimb3,&norm2Rect, DDBLT_KEYSRC, NULL );
		else if (y_pos<100)
			lpDDSBack->Blt(&normRect,ShogoClimb4,&norm2Rect, DDBLT_KEYSRC, NULL );
	}
	
	if (y_pos==floory) bJumpDone=TRUE;
	
	renderSpikeA();
	if (rockcnt>0) rocketA();

	if (CotA.doa==FALSE)
	{
		renderCotA();
		if (Collision_Test(cotColRect.top, cotColRect.bottom, cotColRect.left, cotColRect.right, ShogoColRect.top, ShogoColRect.bottom, ShogoColRect.left, ShogoColRect.right) && bInvis==FALSE)
		{
			if (bFiring==FALSE)
			{
				Shogo.health-=10;
				bHurt=TRUE;
				bInvis=TRUE;
				invis_time=GetTickCount();
			}
			else if (bFiring==TRUE)
				CotA.health-=10;
		}
	}
	else if (CotA.doa==TRUE)
	{
		renderCotADie();
	}

	if (CotA.health<0) CotA.doa=TRUE;

	if (Collision_Test(rockColRect.top, rockColRect.bottom, rockColRect.left, rockColRect.right, ShogoColRect.top, ShogoColRect.bottom, ShogoColRect.left, ShogoColRect.right) && bInvis==FALSE)
	{
		Shogo.health-=20;
		bHurt=TRUE;
		bInvis=TRUE;
		invis_time=GetTickCount();
	}

	if ((GetTickCount() - invis_time) > 1500)
	{
		bInvis=FALSE;
	}

	if (bStep==FALSE) steps_voc.lpDSBuffer->Stop();
	if (bHurt==FALSE) hurt_time=GetTickCount();

	// flip to the primary surface
	lpDDSBack->Blt(&h2Rect,hbar,&hRect, DDBLT_KEYSRC, NULL );
	lpDDSBack->Blt(&s2Rect,sbar,&sRect, DDBLT_KEYSRC, NULL );
	lpDDSBack->Blt(&hudRect,hud,&hudRect, DDBLT_KEYSRC, NULL );


	lpDDSPrimary->Flip(NULL,DDFLIP_WAIT); 
}

void getrect1b()
{
	rcRect.left = backx_pos; 
	rcRect.top = 0;
	rcRect.right = backwidth; 
	rcRect.bottom = 480; 
	l1Rect.left = mapx_pos; 
	l1Rect.top = 0;
	l1Rect.right = mapendx_pos; 
	l1Rect.bottom = 480;
	amRect.left = 0; 
	amRect.top = 0; 
	amRect.right = 24; 
	amRect.bottom = 25; 

	flipRect.left = x_pos-20;
	if (y_pos<0)flipRect.top = 0; 
	else flipRect.top = y_pos;
	flipRect.right = x_pos + 90; 
	if (y_pos>367) flipRect.bottom = 480;
	else flipRect.bottom = y_pos + 117; 
	
	flip2Rect.left = 0;
	if (y_pos<0)flip2Rect.top = -1*y_pos;
	else flip2Rect.top = 0;
	flip2Rect.right = 110; 
	if (y_pos>367) flip2Rect.bottom = 480-y_pos;
	else flip2Rect.bottom = 117; 
	
	normRect.left = x_pos; 
	if (y_pos<0)normRect.top = 0; 
	else normRect.top = y_pos;
	normRect.right = x_pos + 110; 
	if (y_pos>367) normRect.bottom = 480;
	else normRect.bottom = y_pos + 117;
	
	norm2Rect.left = 0; 
	if (y_pos<0) norm2Rect.top = -1*y_pos; 
	else norm2Rect.top = 0;
	norm2Rect.right = 110; 
	if (y_pos>367) norm2Rect.bottom = 480-y_pos;
	else norm2Rect.bottom = 117;
	
	hRect.top=0;
	hRect.bottom=17;
	hRect.left=0;
	if (Shogo.health<0) Shogo.health=0;
	hRect.right=20 + (Shogo.health * 1.3);

	h2Rect.top=4;
	h2Rect.bottom=21;
	h2Rect.left=6;
	if (Shogo.health<0) Shogo.health=0;
	h2Rect.right=26 + (Shogo.health * 1.3);

	hudRect.top=0;
	hudRect.bottom=50;
	hudRect.left=0;
	hudRect.right=640;
		;
	sRect.top=0;
	sRect.bottom=17;
	sRect.left=0;
	if (Shogo.special<0) Shogo.special=0;
	sRect.right=20 + (Shogo.special * 1.3);

	s2Rect.top=21;
	s2Rect.bottom=38;
	s2Rect.left=6;
	s2Rect.right=26 + (Shogo.special * 1.3);
		
}

//////////////////////////////////////////////////////////SAMU-7/////
void getrect1c()
{
	rcRect.left = backx_pos; 
	rcRect.top = 0;
	rcRect.right = backwidth; 
	rcRect.bottom = 480; 
	l1Rect.left = mapx_pos; 
	l1Rect.top = 0;
	l1Rect.right = mapendx_pos; 
	l1Rect.bottom = 480;
	amRect.left = 0; 
	amRect.top = 0; 
	amRect.right = 24; 
	amRect.bottom = 25; 

	flipRect.left = x_pos-20;
	if (y_pos<0)flipRect.top = 0; 
	else flipRect.top = y_pos;
	flipRect.right = x_pos + 90; 
	if (y_pos>367) flipRect.bottom = 480;
	else flipRect.bottom = y_pos + 117; 
	
	flip2Rect.left = 0;
	if (y_pos<0)flip2Rect.top = -1*y_pos;
	else flip2Rect.top = 0;
	flip2Rect.right = 110; 
	if (y_pos>367) flip2Rect.bottom = 480-y_pos;
	else flip2Rect.bottom = 117; 
	
	normRect.left = x_pos; 
	if (y_pos<0)normRect.top = 0; 
	else normRect.top = y_pos;
	normRect.right = x_pos + 110; 
	if (y_pos>367) normRect.bottom = 480;
	else normRect.bottom = y_pos + 117;
	
	norm2Rect.left = 0; 
	if (y_pos<0) norm2Rect.top = -1*y_pos; 
	else norm2Rect.top = 0;
	norm2Rect.right = 110; 
	if (y_pos>367) norm2Rect.bottom = 480-y_pos;
	else norm2Rect.bottom = 117;
	
	hRect.top=0;
	hRect.bottom=17;
	hRect.left=0;
	if (Shogo.health<0) Shogo.health=0;
	hRect.right=20 + (Shogo.health * 1.3);

	h2Rect.top=4;
	h2Rect.bottom=21;
	h2Rect.left=6;
	if (Shogo.health<0) Shogo.health=0;
	h2Rect.right=26 + (Shogo.health * 1.3);

	hudRect.top=0;
	hudRect.bottom=50;
	hudRect.left=0;
	hudRect.right=640;
		;
	sRect.top=0;
	sRect.bottom=17;
	sRect.left=0;
	if (Shogo.special<0) Shogo.special=0;
	sRect.right=20 + (Shogo.special * 1.3);

	s2Rect.top=21;
	s2Rect.bottom=38;
	s2Rect.left=6;
	s2Rect.right=26 + (Shogo.special * 1.3);
		
}

////////////////////////////////////////////////////////////SAMU-7///

/////////////////////////////////////////////////////////////////////
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	MSG msg;                 // message from queue
	LONGLONG cur_time;       // current time
	BOOL notDone=TRUE;       // flag for thread completion
	DWORD  time_count;    // ms per frame, default if no performance counter
	LONGLONG perf_cnt;       // performance timer frequency
	BOOL perf_flag=FALSE;    // flag determining which timer to use
	LONGLONG next_time=0;    // time to render next frame
	LONGLONG last_time=0;	 // time of previous frame
	double time_elapsed;	 // time since previous frame
	double time_scale;		 // scaling factor for time

	// initialize the application, exit on failure

    if (!Init(hInstance, nCmdShow)) {
		Cleanup();
        return FALSE;
	}

	if (QueryPerformanceFrequency((LARGE_INTEGER *) &perf_cnt)) {
		perf_flag=TRUE;
		time_count=perf_cnt/30;
		QueryPerformanceCounter((LARGE_INTEGER *) &next_time);
		time_scale=1.0/perf_cnt;
	} else {
		next_time=timeGetTime();
		time_scale=0.001;
		time_count=33;
	}

	last_time=next_time;

	// run till completed 

	if (bStartstart==FALSE)
	{
		startstart();
	}

	while (bStart==FALSE)
		{
			startinput();
			render_start();
		}

	while (notDone) { 
		if (PeekMessage( &msg, NULL, 0, 0, PM_REMOVE)) { 
			if (msg.message==WM_QUIT) 
				notDone=FALSE; 
			TranslateMessage(&msg);
			DispatchMessage(&msg); 

		} else {
			if (perf_flag)
				QueryPerformanceCounter((LARGE_INTEGER *) &cur_time);
			else
				cur_time=timeGetTime();

			if (cur_time>next_time) {
				time_elapsed=(cur_time-last_time)*time_scale;
				last_time=cur_time;

				if (bStartLev==FALSE) { lv1start(); }

				input();
				if ((Shogo.x>=320 && Shogo.x<7660) && (clev!=1.3)){ x_pos=320; bScroll=TRUE; }
				if (Shogo.x<320){ bScroll=FALSE; }

				if (clev==1)
				{
					level1a();
					getrect1a();
					render_frame();
				}
				else if (clev==1.2)
				{
					level1b();
					getrect1b();
					render_frame();
				}
				else if (clev==1.3)
				{
					getrect1c();
					render_frame();
				}

					next_time=cur_time + time_count;
			}
		}
	}
	// exit returning final message

    return (msg.wParam);
}

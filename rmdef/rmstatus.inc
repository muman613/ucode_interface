
/////////////////////////////////////////////////////
// BEFORE YOU START CHANGING THIS FILE :
//
// We need to preserve BINARY compatibility between all
// the different modules using the error codes.
// So there are some simple rules when editing this file:
// 
// DO NOT CHANGE THE ORDER OF THE ERRORS.
// DO NOT INSERT NEW ERRORS IN THE MIDDLE OF THE LIST.
// DO NOT DELETE ERRORS.
// ADD NEW ERRORS AT THE END ONLY.
//
// PLEASE !
//
// We need to keep the _numbers_ fixed!
//
///////////////////////////////////////////////////////


//@{
/** no error */
RM_DEFINE_ERROR(OK,6)
//@}

//@{
/** no error, but action is still pending */
RM_DEFINE_ERROR(PENDING,7)
/** used in case of synchronous transfer */
RM_DEFINE_ERROR(XFER_DONE,8)
//@}

//@{
// generic errors 
RM_DEFINE_ERROR(ERROR,9)
RM_DEFINE_ERROR(FATAL,10)
RM_DEFINE_ERROR(NOTIMPLEMENTED,11)
/** if a set-only property is used in get mode for instance */
RM_DEFINE_ERROR(INVALIDMODE,12)
RM_DEFINE_ERROR(DEPRECATED,13)
RM_DEFINE_ERROR(PARAMETER_OUT_OF_RANGE,14)
RM_DEFINE_ERROR(INVALID_PARAMETER,15)
RM_DEFINE_ERROR(ACCESS_VIOLATION,16)
RM_DEFINE_ERROR(INSUFFICIENT_SIZE,17)
RM_DEFINE_ERROR(NOT_FOUND,18)
RM_DEFINE_ERROR(NOT_SUPPORTED,19)
//@}

//@{
/** conceptual errors : no such interface */
RM_DEFINE_ERROR(ERRORNOSUCHINTERFACE,20)
/** conceptual errors : interface with no owner */
RM_DEFINE_ERROR(ERRORINTERFACEWITHNOOWNER,21)
//@}

//@{
/** instance creation error */
RM_DEFINE_ERROR(ERRORCREATEINSTANCE,22)
//@}

//@{
/** other libc errors : out of file descriptors */
RM_DEFINE_ERROR(ERROROUTOFFILEDESCRIPTORS,23)
/** other libc errors : catching too many  ``interrupted system call'' (Linux)*/
RM_DEFINE_ERROR(ERROREINTR,24) // catching too much ``interrupted system call'' (Linux)
//@}

//@{
/** Events errors : fatal event error*/
RM_DEFINE_ERROR(FATALEVENT,25)
//@}

//@{
/** Semaphores errors : fatal semaphore error*/
RM_DEFINE_ERROR(FATALSEMAPHORE,26)
RM_DEFINE_ERROR(SEMAPHORELOCKED,27)
//@}

//@{
/** Semaphores errors : fatal semaphore error*/
RM_DEFINE_ERROR(FATAL_TOS,28)
RM_DEFINE_ERROR(TOS_TIMEOUT,29)
RM_DEFINE_ERROR(TOS_EVENT,30)
//@}

//@{
/** Critical Sections errors : fatal critical section error*/
RM_DEFINE_ERROR(FATALCRITSEC,31)
/** Critical Sections errors : inconsistent critical section call*/
RM_DEFINE_ERROR(FATALINCONSISTENTCRITICALSECTIONCALL,32)
//@}

//@{
/** Condition Variable errors */
RM_DEFINE_ERROR(FATALCONDVAR,33)
//@}

//@{ 
/** Threads errors : create thread error */
RM_DEFINE_ERROR(FATALCREATETHREAD,34)
/** Threads errors : thread table overflow */
RM_DEFINE_ERROR(FATALTHREADTABLEOVERFLOW,35)
//@}

//@{
/** Memory manager errors : given buffer is so small we can't even create the empty layout */
RM_DEFINE_ERROR(FATALBUFFERTOOSMALL,36)
/** Memory manager errors : malloc with zero size */
RM_DEFINE_ERROR(FATALASKEDZEROSIZEMALLOC,37)
/** Memory manager errors : invalid pointer*/
RM_DEFINE_ERROR(FATALINVALIDPOINTER,38)
/** Memory manager errors : memory has been corrupted*/
RM_DEFINE_ERROR(FATALMEMORYCORRUPTED,39)
/** Memory manager errors : out of memory*/
RM_DEFINE_ERROR(FATALOUTOFMEMORY,40)
/** Memory manager errors : memory is not free*/
RM_DEFINE_ERROR(ERRORMEMORYISNOTFREE,41)
//@}

//@{
/** pool object errors */
RM_DEFINE_ERROR(INVALID_NEW,42)
RM_DEFINE_ERROR(INVALID_DELETE,43)
//@}

//@{
/** I/O errors : cannot open file*/
RM_DEFINE_ERROR(ERROROPENFILE,44)
/** I/O errors : cannot close file*/
RM_DEFINE_ERROR(ERRORCLOSEFILE,45)
/** I/O errors : cannot write file*/
RM_DEFINE_ERROR(ERRORWRITEFILE,46)
/** I/O errors : cannot read file*/
RM_DEFINE_ERROR(ERRORREADFILE,47)
/** I/O errors : cannot seek in the file*/
RM_DEFINE_ERROR(ERRORSEEKFILE,48)
/** I/O errors : end of file*/
RM_DEFINE_ERROR(ERRORENDOFFILE,49)
/** I/O errors : file is locked*/
RM_DEFINE_ERROR(ERRORFILELOCKED,50)
/** I/O errors : no directory entry*/
RM_DEFINE_ERROR(ERRORNODIRECTORYENTRY,51)
//@}

//@{
/** dynamic loader errors -- they are recoverable. */
/** dynamic loader errors : cannot open shared library */
RM_DEFINE_ERROR(ERRORDYNAMICLIBOPEN,52)
/** dynamic loader errors : cannot get symbol from shared library */
RM_DEFINE_ERROR(ERRORDYNAMICLIBGETSYMBOL,53)
/** dynamic loader errors : cannot close shared library */
RM_DEFINE_ERROR(ERRORDYNAMICLIBCLOSE,54)
//@}

//@{
/** corelist errors : corelist not valid */
RM_DEFINE_ERROR(FATALCORELISTNOTVALID,55)
//@}

//@{
/** corequeue errors : corequeue not valid */
RM_DEFINE_ERROR(FATALCOREQUEUENOTVALID,56)
//@}

//@{
/** corepool errors : corepool not valid */
RM_DEFINE_ERROR(FATALCOREPOOLNOTVALID,57)
RM_DEFINE_ERROR(FATALCOREPOOLLEAKS,58)
RM_DEFINE_ERROR(FATALCOREPOOLRETURNEDTWICE,59)
RM_DEFINE_ERROR(FATALCOREPOOLISNOTMINE,60)
RM_DEFINE_ERROR(FATALCOREPOOLOVERFLOW,61)
//@}

//@{
/** queue errors : queue not valid */
RM_DEFINE_ERROR(FATALQUEUENOTVALID,62)
//@}

//@{
/** list errors : list not valid */
RM_DEFINE_ERROR(FATALLISTNOTVALID,63)
RM_DEFINE_ERROR(LISTISEMPTY,64)
//@}

//@{
/** packet command css errors. */
RM_DEFINE_ERROR(ERROR_KEYISNOTPRESENT,65)
//@}

//@{
/** graph errors : no graph in driver */
RM_DEFINE_ERROR(ERRORNOGRAPHINDRIVER,66)
/** graph errors : graph is full */
RM_DEFINE_ERROR(ERRORGRAPHFULL,67)
/** graph errors : graph can't be built */
RM_DEFINE_ERROR(ERRORGRAPHMISSINGNODEORMODULE,68)
/** wrong url: */
RM_DEFINE_ERROR(INVALID_URL,69)
/** wrong url prefix or cannot find xml description */
RM_DEFINE_ERROR(UNKNOWN_URL_PREFIX,70)
/** wrong input control or more than 1 input control*/
RM_DEFINE_ERROR(FATAL_INPUT_CONTROL,71)
//@}

//@{
/** object errors : object has been deleted */
RM_DEFINE_ERROR(OBJECTDELETED,72)
//@}

//@{
RM_DEFINE_ERROR(ERRORHARDWARELIBRARY,73)
//@}

//@{
RM_DEFINE_ERROR(VIDEOHASPAUSED,74)
RM_DEFINE_ERROR(ASPECTRATIOCHANGE,75)
RM_DEFINE_ERROR(ACMODECHANGE,76)
RM_DEFINE_ERROR(FETCHCC,77)
RM_DEFINE_ERROR(FETCHDTVCC,78)
RM_DEFINE_ERROR(FATALHARDWAREABSTRACTIONLAYER,79)
//@}

//@{
/** demux node error */
RM_DEFINE_ERROR(DEMUX_CANNOT_DETECT_AUDIO,80)
//@}


//@{
// socket errors
/** socket errors : socket init has failed */
RM_DEFINE_ERROR(ERRORSOCKETINITFAILED,81)
/** socket errors : incorrect version of the socket library */
RM_DEFINE_ERROR(ERRORSOCKETWRONGVERSION,82)
/** socket errors : fatal socket error */
RM_DEFINE_ERROR(FATALSOCKET,83)
//@}

//@{
// string errors
/** string errors : fatal string error */
RM_DEFINE_ERROR(FATALSTRING,84)
//@}

//@{
// AAc decoder errors.
/** AAC decoder errors : buffer too small to decode */
RM_DEFINE_ERROR(BUFFERTOOSMALL,85)
//@}

//@{
// udp errors
/** UDP socket errors : fatal UDP socket error */
RM_DEFINE_ERROR(FATALUDP,86)
//@}

//@{
// MP4 errors
/** MP4 errors : not an MP4 file */
RM_DEFINE_ERROR(ERROR_NOT_MP4,87)
RM_DEFINE_ERROR(MPEG4EOF,88)
//@}

//@{
// DIVX errors
/** DIVX errors : not an DIVX file */
RM_DEFINE_ERROR(ERROR_NOT_DIVX,89)
//@}

//@{
/** need more data to decode/parse something. */
RM_DEFINE_ERROR(NEED_MORE_DATA,90)
//@}

//@{
/** can't rewind stream. for mp3 decoder */
RM_DEFINE_ERROR(CANT_REWIND_STREAM,91)
RM_DEFINE_ERROR(MP3_DECODE_NOTHING,92)
RM_DEFINE_ERROR(MP3_INCOMPLETE_FRAME,93) // For inocmplete frame decoded in player
//@}

//@{
/** shift storage error */
RM_DEFINE_ERROR(SHIFTSTORAGE_FATAL,94)
//@}

//@{
// RMHWACCESS errors
/** something goes wrong with RMhwAccess */
RM_DEFINE_ERROR(HWACCESS_GENERIC_ERROR,95)
/** Hardware library version mismatch */
RM_DEFINE_ERROR(HWACCESS_HWLIB_VERSION_MISMATCH,96)
//@}

//@{
// RMSOCKET errors
/** something goes wrong with RMsocket */
RM_DEFINE_ERROR(CANT_OPEN_SOCKET,97)
//@}

//@{
// RMREMOTE errors
/** something goes wrong with RMremote */
RM_DEFINE_ERROR(ERROR_REMOTE,98)
//@}

//@{
// Properties errors
RM_DEFINE_ERROR(INVALID_PROPERTY_MAINSET,99)
RM_DEFINE_ERROR(INVALID_PROPERTY_SUBSET,100)
RM_DEFINE_ERROR(INVALID_PROPERTY_ID,101)
RM_DEFINE_ERROR(PROPERTY_NOT_SUPPORTED,102)
RM_DEFINE_ERROR(PROPERTY_NOT_SET,103)
//@}

//@{
/** no error, but the samples sent to the decoder contains no video data */
RM_DEFINE_ERROR(OK_HAS_NO_VIDEO,104)
/** Did not complete reading data from device. Try again later. */
RM_DEFINE_ERROR(ERROR_NOT_FINISHED,105)
/** Error reading data from device. Trying to recover. Not Fatal but bad. */
RM_DEFINE_ERROR(ERROR_INVALID_SECTORS,106)
/** Error reading data from device. Cannot recover. Fatal. */
RM_DEFINE_ERROR(ERROR_FATAL_INVALID_SECTORS,107)
/** Requested User Operation not currently allowed. Operation aborted safely. */
RM_DEFINE_ERROR(ERROR_UOP_NOT_ALLOWED,108)
/** Navigation state machine is not in a state where user commands are allowed.
    Call Schedule a few times and try again later. This is not fatal.
*/
RM_DEFINE_ERROR(ERROR_QUEUE_COMMAND,109)
/** Either user parameters to the operation were not valid or device data does
    not allow this operation. Operation is thus aborted. This is not fatal.
*/
RM_DEFINE_ERROR(ERROR_NOT_SET,110)
/** There is no next PGC to jump to. Typically happens when calling
    NextChapter.
*/
RM_DEFINE_ERROR(ERROR_NO_NEXT_PGC,111)
/** There is no prev PGC to jump to. Typically happens when calling
    PrevChapter.
*/
RM_DEFINE_ERROR(ERROR_NO_PREV_PGC,112)
/** No still mode. Typically happens if the user requested a Still_Off and
    no still was active.
*/
RM_DEFINE_ERROR(ERROR_NO_STILL,113)
/** Somehow, device content is not compatible with the current parental level.
    This is a fatal error.
*/
RM_DEFINE_ERROR(ERROR_PARENTAL_CONTROL,114)
/** Bad Command on the DVD device: This is a Fatal error. It means the DVD
    content is invalid.
*/
RM_DEFINE_ERROR(ERROR_BAD_COMMAND,115)
/** Could not find the start of VOBU for PGC. This is a Fatal error. */
RM_DEFINE_ERROR(ERROR_NOT_FOUND,116)
/** No First Play PGC could be found on DVD device. This means it is not
    possible to start playback of the DVD device with user interraction.
*/
RM_DEFINE_ERROR(ERROR_NO_FPPGC,117)
/** The user located Point A but the DVD navigation reached the end of the current PGC
    before the user could locate point B. Repeat AB playback is thus disabled.
*/
RM_DEFINE_ERROR(ERROR_ENDOFTITLE_REPEATA,118)
/** The user requested an operation which requires a different playmode than
    the one currently in effect. The different playmodes are:
	- play normal
	- repeat chapter
	- repeat title
	- playlist
	- repeat a (point a has been choosen, but not point b)
	- repeat ab (point a and b have been choosen and repeat ab is in effect)
    The solution if you get this error, is, obviously, to disable the current playmode.
*/
RM_DEFINE_ERROR(ERROR_WRONG_PLAY_MODE,119)
/** Could not read a navigation pack at a critical moment. This is a fatal error. */
RM_DEFINE_ERROR(ERROR_NAVIGATION_PACK,120)
/** The user requested a menu which does not exist. */
RM_DEFINE_ERROR(ERROR_NO_SUCH_MENU,121)
/** Navigation is in a loop. It has nothing to do. */
RM_DEFINE_ERROR(ERROR_NOTHING_TO_DO,122)
/** DVD Drive is an RPC2 drive and Its region is not set. This is a fatal error. */
RM_DEFINE_ERROR(ERROR_RPC2_NOT_SET,123)
/** DVD Drive is RPC2 and this is not compatible with the user-preferences. */
RM_DEFINE_ERROR(ERROR_RPC2,124)
/** DVD Drive region settings, DVD Disc region settings and DVD Navigation region settings
    are not compatible.
*/
RM_DEFINE_ERROR(ERROR_REGION,125)
/** No disc is present in DVD Drive. This is a fatal error.*/
RM_DEFINE_ERROR(ERROR_NO_DISC_IN_DRIVE,126)
/** User-provided video mode is not valid. This is a fatal error.*/
RM_DEFINE_ERROR(ERROR_VIDEO_MODE,127)
/** DVD navigation is already playing data. It cannot complete the operation requested by the user.*/
RM_DEFINE_ERROR(ERROR_PLAYING_ALREADY,128)
/** DVD navigation is not playing. It cannot complete the operation requested by the user.*/
RM_DEFINE_ERROR(ERROR_NOT_PLAYING,129)
/** DVD navigation is not constructed. It cannot complete the operation requested by the user.*/
RM_DEFINE_ERROR(ERROR_NOT_CONSTRUCTED,130)
/** DVD navigation is not paused. It cannot complete the operation requested by the user.*/
RM_DEFINE_ERROR(ERROR_NOT_PAUSING,131)
//@}


//@{
// PUSH model errors
RM_DEFINE_ERROR(NOBUFFER_AVAILABLE,132)
//@}
//@{

// streaming errors errors
RM_DEFINE_ERROR(FATAL_COREPOOL_CREATION,133)
RM_DEFINE_ERROR(FATAL_THREAD_DESTRUCTION,134)
RM_DEFINE_ERROR(FATAL_THREAD_CREATION,135)
//@}

//@{
// mambo property set/get api
RM_DEFINE_ERROR(INVALID_BOARD_HANDLE,136)
RM_DEFINE_ERROR(INVALID_CHIP_HANDLE,137)
RM_DEFINE_ERROR(INVALID_MODULE_HANDLE,138)
RM_DEFINE_ERROR(INVALID_PROPERTY_HANDLE,139)
//@}

//@{
// streaming error
RM_DEFINE_ERROR(WRONGRTSPANSWER,140)
RM_DEFINE_ERROR(WRONG_RELIABLE_RTP_STATE,141)
RM_DEFINE_ERROR(ERROR_BUFFER_TO_SMALL,142)  
RM_DEFINE_ERROR(ERROR_NOT_VOD,143)  
RM_DEFINE_ERROR(ERROR_STATE,144)    
RM_DEFINE_ERROR(UNSUPPORTED_SPEED,145)    
//@}

//@{
// divx drm errors
RM_DEFINE_ERROR(DRM_UNKNOWN_TYPE,146)
RM_DEFINE_ERROR(DRM_INVALID_KEY,147)
RM_DEFINE_ERROR(DRM_DECRYPTION_FAILED,148)
RM_DEFINE_ERROR(DRM_EXPIRED_RENTAL,149)
RM_DEFINE_ERROR(DRM_UNAUTHORIZED_USER,150)
RM_DEFINE_ERROR(DRM_INVALID_FILE,151)
//@}

//@{
// Hardware library errors
/** For instance, microcode is processing a command and cannot accept another */
RM_DEFINE_ERROR(ERROR_COMMAND_PENDING,152)
/** The application has sent an invalid command */
RM_DEFINE_ERROR(ERROR_INVALID_COMMAND,153)
/** Internal error: the ucode has returned an invalid or unknown message */
RM_DEFINE_ERROR(ERROR_INVALID_MESSAGE,154)
//@}

//@{
// dvd audio errors
/** to differenciate audio only player and video capable players */
RM_DEFINE_ERROR(STATE_NOT_SUPPORTED,155)
/** to deferianciate parameters errors device reader errors */
RM_DEFINE_ERROR(ERROR_PARSER,156)
//@}

//@{
// vcd errors
/** when the playback reach the end of the disc and other disc have to be inserted in the drive. */
RM_DEFINE_ERROR(INSERT_OTHER_DISC,157)
//@}

//@{
// remote control errors
/** when the last key pressed can not be interpret */
RM_DEFINE_ERROR(UNKNOWN_KEY,158)
//@}


//@{
// WMAPROdecoder errors
/** no more data to decode in packet */
RM_DEFINE_ERROR(WMAPRO_NO_MORE_DATA,159)
RM_DEFINE_ERROR(WMAPRO_SKIPFRAME,160)
RM_DEFINE_ERROR(WMAPRO_NO_MORE_SAMPLES,161)
//@}

//@{
// ASF conditions
/** index not available */
RM_DEFINE_ERROR(ASF_WITHOUT_INDEX,162)
/** skip data (WMA only is doing FFWD) */
RM_DEFINE_ERROR(ASF_SKIP_DATA,163)
//@}


//@{
// EOS conditions
/** key processed while waiting for EOS */
RM_DEFINE_ERROR(KEY_WHILE_WAITING_EOS,164)
/** EOS encountered */
RM_DEFINE_ERROR(EOS,165)
//@}

RM_DEFINE_ERROR(TIMEOUT,166)
RM_DEFINE_ERROR(BUSY,167)


//@{
// CCFifo errors
/** Attempt to open CCFifo module whereas it is already open */
RM_DEFINE_ERROR(CCFIFO_ALREADY_OPEN,168)
//@}


//@{
// NeroDigital DRM errors
/** DRM prevents playback */
RM_DEFINE_ERROR(DRM_PREVENTS_PLAYBACK,169)
//@}

//@{
// generic
/** indicates we need to skip data */
RM_DEFINE_ERROR(SKIP_DATA,170)
/** indicates there's no more data available */
RM_DEFINE_ERROR(NO_MORE_DATA, 171)
//@}

//@{
// PCR_DISCONTINUITY errors
/** New discontinuity comes before current one is handled */
RM_DEFINE_ERROR(UNHANDLED_VIDEO_PCR_DISCONTINUITY,172)
RM_DEFINE_ERROR(UNHANDLED_AUDIO_PCR_DISCONTINUITY,173)
//@}



RM_DEFINE_ERROR(AUDIO_CODEC_NOT_SUPPORTED, 174)
RM_DEFINE_ERROR(AUDIO_MODE_NOT_SUPPORTED, 175)
RM_DEFINE_ERROR(VIDEO_CODEC_NOT_SUPPORTED, 176)
RM_DEFINE_ERROR(VIDEO_MODE_NOT_SUPPORTED, 177)
RM_DEFINE_ERROR(UNKNOWN_FILE_FORMAT, 178)
RM_DEFINE_ERROR(NOT_KNOWN, 179)


//@{
// RMRPC2XTASK DRM errors

RM_DEFINE_ERROR(DRM_XSTART_FAILURE,180)
RM_DEFINE_ERROR(DRM_XTASK_SYNC_FAILURE,181)
RM_DEFINE_ERROR(DRM_XTASK_MISMATCH,182)
RM_DEFINE_ERROR(DRM_VERSION_MISMATCH,183)
//@}

RM_DEFINE_ERROR(OVERLAP_64MBYTE,184)
RM_DEFINE_ERROR(XLOAD_DESTINATION_ERROR,185)
RM_DEFINE_ERROR(XLOAD_DECRYPT_ERROR,186)
RM_DEFINE_ERROR(XLOAD_VERIFY_ERROR,187)
RM_DEFINE_ERROR(GUNZIP_ERROR,188)
RM_DEFINE_ERROR(XBIND_WRONGLENGTH,189)

RM_DEFINE_ERROR(NO_ACK, 190)  // did not receive expected ACK, or received NAK, from other end of communication link
RM_DEFINE_ERROR(NO_RESPONSE, 191)  // other end of communication link did not respond
RM_DEFINE_ERROR(REMOTE_ERROR, 192) // remote end of communication link reported an unspecified error

/* Generic DRM related errors
* Each DRM should define what these errors mean in the context of
* their own calls.
*/
/* DRM system cannot write the license, possibly file I/O erro */
RM_DEFINE_ERROR(DRM_CANNOT_WRITE_LICENSE, 193)

/* A file required for DRM playback is missing  */
RM_DEFINE_ERROR(DRM_MISSING_LICENSE_FILE, 194)

/* A network resource error has occured in the DRM layer  */
RM_DEFINE_ERROR(DRM_NETWORK_ERROR, 195)

/* An error with the DRM keys has occurred */
RM_DEFINE_ERROR(DRM_KEY_ERROR, 196)

/* An error occurred because the DRM license denied the operation  */
RM_DEFINE_ERROR(DRM_LICENSE_DENIED, 197)

RM_DEFINE_ERROR(CHECKSUM_MISMATCH, 198)  // checksum did not match, return data anyways

/* xload3 errors */
RM_DEFINE_ERROR(XL3_RSATAMPER,199)
RM_DEFINE_ERROR(XL3_RSAVFAILED,200)
RM_DEFINE_ERROR(XL3_RKLDENIED,201)
RM_DEFINE_ERROR(XL3_SIZEMISMATCH,202)
RM_DEFINE_ERROR(XL3_PADERROR,203)
RM_DEFINE_ERROR(XL3_FAILEDASSERT,204)

/* Generic errors */
RM_DEFINE_ERROR(INSUFFICIENT_ALIGNMENT,205)
RM_DEFINE_ERROR(WRONG_MAGIC,206)
RM_DEFINE_ERROR(UNSUPPORTED,207)
RM_DEFINE_ERROR(SYNTAX_ERROR,208)
RM_DEFINE_ERROR(WRONG_HASH,209)
/* Serial Number Does not match */
RM_DEFINE_ERROR(WRONG_SN, 210)

/* Token Authentication Failed */
RM_DEFINE_ERROR(TOKEN_AUTH, 211)

RM_DEFINE_ERROR(MLC_READERROR,212)

/* XToken Processing Errors */
RM_DEFINE_ERROR(XTOKEN_WRONG_SIZE, 213)
RM_DEFINE_ERROR(XTOKEN_WRONG_MAC0, 214)
RM_DEFINE_ERROR(XTOKEN_WRONG_MAC1, 215)
RM_DEFINE_ERROR(XTOKEN_WRONG_SN, 216)
RM_DEFINE_ERROR(XTOKEN_WRONG_OEMID, 217)
RM_DEFINE_ERROR(XTOKEN_WRONG_TYPE, 218)

RM_DEFINE_ERROR(XL3_RUNAWAY,219)

RM_DEFINE_ERROR(ERROR_CORRUPTED_DATA, 220)

RM_DEFINE_ERROR(XTOKEN_WRONG_PARTNAME, 221)

/* xtask otp OID 0x110 replacement errors */
RM_DEFINE_ERROR(CREATE_ERROR, 222)
RM_DEFINE_ERROR(LOCK_ERROR, 223)
RM_DEFINE_ERROR(READ_ERROR, 224)
RM_DEFINE_ERROR(WRITE_ERROR, 225)
RM_DEFINE_ERROR(UPDATE_ERROR, 226)
RM_DEFINE_ERROR(UPDATE_LOCK_ERROR, 227)
RM_DEFINE_ERROR(UPDATE_READ_ERROR, 228)
RM_DEFINE_ERROR(UPDATE_WRITE_ERROR, 229)

// ConsoleCommands.c
// This is where you add commands:
//		1. Add a protoype
//			static eCommandResult_T ConsoleCommandVer(const char buffer[]);
//		2. Add the command to mConsoleCommandTable
//		    {"ver", &ConsoleCommandVer, HELP("Get the version string")},
//		3. Implement the function, using ConsoleReceiveParam<Type> to get the parameters from the buffer.

#include <string.h>
#include "consoleCommands.h"
#include "console.h"
#include "consoleIo.h"
#include "version.h"


extern uint8_t g_enable_debugging;
extern uint8_t g_enable_debugging_vl53l0x;
extern uint8_t g_enable_debugging_STMC;

#define IGNORE_UNUSED_VARIABLE(x)     if ( &x == &x ) {}

static eCommandResult_T ConsoleCommandComment(const char buffer[]);
static eCommandResult_T ConsoleCommandVer(const char buffer[]);
static eCommandResult_T ConsoleCommandHelp(const char buffer[]);
static eCommandResult_T DebugEnable(const char buffer[]);
static eCommandResult_T DebugDisable(const char buffer[]);
static eCommandResult_T DebugEnableVl53l0x(const char buffer[]);
static eCommandResult_T DebugDisableVl53l0x(const char buffer[]);
static eCommandResult_T DebugEnableSTMC(const char buffer[]);
static eCommandResult_T DebugDisableSTMC(const char buffer[]);
static const sConsoleCommandTable_T mConsoleCommandTable[] =
{
    {";", &ConsoleCommandComment, HELP("Comment! You do need a space after the semicolon. ")},
    {"help", &ConsoleCommandHelp, HELP("Lists the commands available")},
    {"ver", &ConsoleCommandVer, HELP("Get the version string")},
	{"en", &DebugEnable, HELP("Enable debugging over USB CDC")},
	{"dis", &DebugDisable, HELP("Disable debugging over USB CDC")},
	{"enTOF", &DebugEnableVl53l0x, HELP("Enable debugging for the vl53l0x sensor")},
	{"disTOF", &DebugDisableVl53l0x, HELP("Disable debugging for the vl53l0x sensor")},
	{"enSTMC", &DebugEnableSTMC, HELP("Enable debugging for the state machine sensor")},
	{"disSTMC", &DebugDisableSTMC, HELP("Disable debugging for the state machine")},

	CONSOLE_COMMAND_TABLE_END // must be LAST
};

static eCommandResult_T ConsoleCommandComment(const char buffer[])
{
	// do nothing
	DebugEnable(NULL);
	IGNORE_UNUSED_VARIABLE(buffer);
	return COMMAND_SUCCESS;
}

static eCommandResult_T ConsoleCommandHelp(const char buffer[])
{
	uint32_t i;
	uint32_t tableLength;
	eCommandResult_T result = COMMAND_SUCCESS;

    IGNORE_UNUSED_VARIABLE(buffer);

	tableLength = sizeof(mConsoleCommandTable) / sizeof(mConsoleCommandTable[0]);
	for ( i = 0u ; i < tableLength - 1u ; i++ )
	{
		ConsoleIoSendString(mConsoleCommandTable[i].name);
#if CONSOLE_COMMAND_MAX_HELP_LENGTH > 0
		ConsoleIoSendString(" : ");
		ConsoleIoSendString(mConsoleCommandTable[i].help);
#endif // CONSOLE_COMMAND_MAX_HELP_LENGTH > 0
		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}


static eCommandResult_T ConsoleCommandVer(const char buffer[])
{
	eCommandResult_T result = COMMAND_SUCCESS;
    IGNORE_UNUSED_VARIABLE(buffer);
	ConsoleIoSendString(VERSION_STRING);
	ConsoleIoSendString(STR_ENDLINE);
	return result;
}

static eCommandResult_T DebugEnable(const char buffer[])
{
	eCommandResult_T result = COMMAND_SUCCESS;
    IGNORE_UNUSED_VARIABLE(buffer);
    g_enable_debugging = 1;
	ConsoleIoSendString(STR_ENDLINE);
	return result;
}

static eCommandResult_T DebugDisable(const char buffer[])
{
	eCommandResult_T result = COMMAND_SUCCESS;
    IGNORE_UNUSED_VARIABLE(buffer);
    g_enable_debugging = 0;
	return result;
}

static eCommandResult_T DebugEnableVl53l0x(const char buffer[])
{
	eCommandResult_T result = COMMAND_SUCCESS;
    IGNORE_UNUSED_VARIABLE(buffer);
    g_enable_debugging_vl53l0x = 1;
	ConsoleIoSendString(STR_ENDLINE);
	return result;
}

static eCommandResult_T DebugDisableVl53l0x(const char buffer[])
{
	eCommandResult_T result = COMMAND_SUCCESS;
    IGNORE_UNUSED_VARIABLE(buffer);
    g_enable_debugging_vl53l0x = 0;
	return result;
}

static eCommandResult_T DebugEnableSTMC(const char buffer[])
{
    eCommandResult_T result = COMMAND_SUCCESS;
    IGNORE_UNUSED_VARIABLE(buffer);
    g_enable_debugging_STMC = 1;
    ConsoleIoSendString(STR_ENDLINE);
    return result;
}

static eCommandResult_T DebugDisableSTMC(const char buffer[])
{
    eCommandResult_T result = COMMAND_SUCCESS;
    IGNORE_UNUSED_VARIABLE(buffer);
    g_enable_debugging_STMC = 0;
    return result;
}

const sConsoleCommandTable_T* ConsoleCommandsGetTable(void)
{
	return (mConsoleCommandTable);
}



#include <ctype.h>		// iscntrl()
#include <errno.h>		// errno, EAGAIN
#include <stdio.h>		// printf()
#include <stdlib.h>		// atexit(), exit()
#include <termios.h>	// struct termios, ECHO, TCSAFLUSH, tcgetattr(),
						// tcsetattr(), ICANON, ISIG, IXON, IEXTEN, 
						// ICRNL, OPOST, BRKINT, INPCK, ISTRIP, CS8, 
						// VMIN, VTIME
#include <unistd.h>		// read(), STDIN_FILENO, write(), STDOUT_FILENO

// In short, this macro `CTRL_CHR' turns any normal character (e.g. `Q')
// into its corresponding CTRL character (`CTRL-Q'). It exploits the
// way the ASCII table was designed. In the ASCII table the CTRL-Q
// control sequence is exactly the same as the keycode for `Q', except
// that the upper 3 bits are cleared. We need to be able to check for
// this keycode in order to manually exit the program with CTRL-Q, since 
// `normal' signals like CTRL-C and CTRL-D will be turned off when we 
// set the terminal to full-on RAW mode.
#define CTRL_CHR(k) ((k) & 0x1F)

// Used in our exit-function, which is defined before _erasedisp().
// Therefore, _erasedisp() should have a forward declaration:
void rawterm_immediate_erasedisp();

// Alias `struct termios' to canonic_termios, because that's the way
// we're going to use it:
typedef struct termios canonical_termios;
// If you need a full(er) abstraction of a (raw) terminal in which the
// window size, sidemargin, cursor position etc. are kept, you should 
// turn this simple typedef into a struct that contains all those things 
// including the canonical_termios.

// `t' is a so-called `singleton', i.e. a globally available variable 
// of which there can/should be only ONE. The first step in using `t'
// is that it should be initialized. Note that singleton-ness is not 
// strictly enforced in this code. We're just limiting ourselves to 
// using only one instance. In production code, you'd be encouraged 
// to control whether there is only one of these in the entire 
// application/process.
canonical_termios t;

// This is our error reporting (logging) function, that terminates the
// application with an error code. In `real' applications, this exit() 
// function should print to STDERR, not to STDOUT. To print to STDERR, 
// use the `perror()' function from <stdio.h>.
void ragequit(const char *s) {
	rawterm_immediate_erasedisp();
	printf("Error: %s\r\n", s); // still in raw mode
	exit(1); // this will disable raw mode
}

void term_disable_raw_mode() {
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &t) == -1) {
		printf("Error: tcsetattr() failed -- terminal probably still ");
		printf("in raw mode.\r\nPlease restart this terminal emulator");
		printf(" manually.\r\n");
	}
	// This function is ONLY called "@ exit", meaning that after its
	// scope closes, control is passed back to the calling shell/process
}

void term_enable_raw_mode() {
	// First order of business is initializing `t'. To do this,
	// get existing terminal attribs and put them in singleton `t':
	if (tcgetattr(STDIN_FILENO, &t) == -1) {
		ragequit("tcgetattr failed");
	}
	// Register the function `term_disable_raw_mode' by its function
	// pointer to be called "@ exit":
	atexit(term_disable_raw_mode);
	// Create local copy of `t' to configure RAW attributes:
	struct termios raw_termios = t;
	// RTFM for these control flags:
	// https://man7.org/linux/man-pages/man3/termios.3.html
	raw_termios.c_iflag = (tcflag_t)((int)raw_termios.c_iflag & 
							~(BRKINT | ICRNL | INPCK | ISTRIP | IXON));
	raw_termios.c_oflag = (tcflag_t)((int)raw_termios.c_oflag & 
							~(OPOST));
	raw_termios.c_cflag |= (CS8);
	raw_termios.c_lflag = (tcflag_t)((int)raw_termios.c_lflag & 
							~(ECHO | ICANON | IEXTEN | ISIG));
	// VMIN sets the minimum number of bytes of input needed before 
	// read() can return. Setting it to 0 means that read() returns as 
	// soon as there is any input to be read. I.e. immediate response to 
	// character input.
	raw_termios.c_cc[VMIN] = 0;
	// VTIME sets the maximum waiting time before read() returns if 
	// there are no characters (time-out). This makes it non-blocking.
	// Each unit here stands for 100 ms (0.1 s). If read() times out, 
	// it will return 0, meaning 0 bytes were read. This is right in our
	// case because after waiting, there were no (i.e. zero) characters.
	raw_termios.c_cc[VTIME] = 1;
	// Overwrite existing terminal attribs with the above control flags,
	// while keeping the `canonical configuration' stored in `t':
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_termios) == -1) {
		ragequit("tcsetattr failed");
	}
}

int rawterm_read_key() {
	int numread;
	char c;
	// read() returns the number of characters read. 
	// Because we're telling read() to read *up to* 1 character, it 
	// reads AT MOST one character at a time. The only other options are
	// - if no characters are present in STDIN's buffer (0) or
	// - if read fails (-1).
	// So you can blissfully block your entire program here, repeatedly
	// calling read(), while its return value is not exactly 1 character
	while ((numread = (int)read(STDIN_FILENO, &c, 1)) != 1) {
		// EAGAIN does not need to problematic, so if your system
		// throws that error, exclude that from the list of errors that
		// should make the program quit:
		if (numread == -1 && errno != EAGAIN) {
			ragequit("read() in read_key() failed");
		}
	}
	// When you need to start reading escape sequences, this right here
	// is a good spot to check if the character was the escape char and
	// then keep reading the characters that follow it (up to 3 for
	// some key combo's). When you've dissected the sequence, make this
	// function return a number outside of the ASCII table that will
	// later help you identify which sequence was used when handling
	// key presses... use this for identifying the DEL key, ARROW keys,
	// etc.
	return c;
}

// When you're creating a larger RAW-mode application, you should 
// probably buffer your output in a string-that-can-grow-in-memory 
// before updating the terminal screen. 
// This way, you could do every screen update with just one
// write() operation, which is much more efficient.
void rawterm_immediate_erasedisp() {
	// Yes, these strings contain VT-100 commands:
	// https://vt100.net/docs/vt100-ug/chapter3.html#ED
	// Erase display:
	write(STDOUT_FILENO, "\x1B[2J", 4);
	// https://vt100.net/docs/vt100-ug/chapter3.html#CUP
	// Set cursor to row 0, column 0:
	write(STDOUT_FILENO, "\x1B[H", 3);
	// More efficient already would be both commands in one write():
	//write(STDOUT_FILENO, "\x1B[2J\x1B[H", 7);
}

//======================================================================
// gcc -std=c99 -Wall -Wextra -Wpedantic -Wconversion -o rawterm rawterm_starter.c

// Your solution / code for the state machine parts goes here:

// states heb ik voor de lampen gemaakt 
typedef enum _state_{

    NONE_ON,// eerst dit 
    L1_ON,	// 1
    L2_ON,	// 2
    L3_ON,	// 3
    num_states

}lamp_state;

// event heb ik voor de buttons gemaakt
typedef enum _event_{

    BUTTON_P1,	//button 1 (0)
    BUTTON_P2,	//button 2 (1)
    NONE_PRESSED	// teller (3) dus 3 states

}input_event;

//handlers functie pointer
typedef lamp_state (*event_handeler_t)(void);

//struct voor de array
typedef struct
{
    lamp_state state; // eerst state
    input_event event;// dan event
    event_handeler_t handler;//dan functie
    
}state_transition_rule;

//functies voor handler
lamp_state P1_handler(void){

    printf("Button 1 pressed, (L1 ON), event handeld. state (1).\r\n");
    return L1_ON;
}

lamp_state P2_handler(void){

    printf("Button 2 pressed, (L1 ON),event handeld. state (1).\r\n");
    return L1_ON;
}

lamp_state L1_ON_P1_handler(void){

    printf("Button 1 pressed while L1 is ON, turning (L1 OFF) en turning (L2 ON), event handeld. state (2).\r\n");
    return L2_ON;
}

lamp_state L1_ON_P2_handler(void){

    printf("Button 2 pressed while L1 is ON,truning (L1 OFF) en turning (L3 ON), event handeld. state (2).\r\n");
    return L3_ON;
}
lamp_state L2_ON_P1_or_P2_handler(void){

    printf("Button pressed while L2 is ON,Turning (L2 OFF), event handeld. state (3).\r\n");
    return NONE_ON;
}


lamp_state L3_ON_P1_or_P2_handler(void){

    printf("Button pressed while L3 is ON, Turning (L3 OFF), event handeld. state (3).\r\n");
    return NONE_ON;
}

//eerst array is voor button 1
state_transition_rule state_transition_rules[] = {
    {NONE_ON, BUTTON_P1, P1_handler}, //eerst none_on
    {L1_ON, BUTTON_P1, L1_ON_P1_handler},
    {L2_ON, BUTTON_P1, L2_ON_P1_or_P2_handler},
	{L3_ON, BUTTON_P1, L3_ON_P1_or_P2_handler}//als l3_on state is active from array 2 and p1 is clicked this turns it of
    
};

//tweede array is voor button 2
state_transition_rule state_transition_rules2[] = {
    {NONE_ON, BUTTON_P2, P2_handler},
    {L1_ON, BUTTON_P2, L1_ON_P2_handler},
    {L2_ON, BUTTON_P2, L2_ON_P1_or_P2_handler},//als l2_on state is active from array 1 and p2 is clicked this turns it of
    {L3_ON, BUTTON_P2, L3_ON_P1_or_P2_handler}
};





//======================================================================

input_event rawterm_handle_keypress() {
	int k = rawterm_read_key();
    input_event e = NONE_PRESSED;
	switch (k) {
		case CTRL_CHR('q'):
			// When CTRL-Q is pressed
			rawterm_immediate_erasedisp();
			exit(0);
			break;
		case 'z': // handle key voor button 1
			printf("Button 1 pressed, state triggered\r\n");
			e = BUTTON_P1;
			break;
        case 'x': // handle key voor button 2
		    printf("Button 2 pressed, state triggered\r\n");
		    e = BUTTON_P2;
		    break;
		default:
			// When any other key is pressed ...
			if (!iscntrl((char)k)) {
				// ... that is NOT a control sequence (like CTRL-C):
				printf("%c\r\n", (char)k);
			}
			break;
	}
    return e;
}

int main() {
	// term_enable_raw_mode() expects there to be a global variable `t' 
	// of type `struct termios':
	term_enable_raw_mode();
	// After enabling raw mode, ther *terminal* has trasitioned from a 
	// `term' to  a `rawterm', which is reflected in the change in
	// function prefix (NB: `t' holds on to the `canonical' terminal
	// configuration for us, so that it may be restored before exit):
	rawterm_immediate_erasedisp();
    input_event e = NONE_PRESSED;
    lamp_state s = NONE_ON;
    printf("NOW!, OH!, Je bent net thuis, en het is donker in de woonkamer! druk X of Z om licht aan te doen.");
	while (1) {
		// rawterm_handle_keypress() calls the rawterm_read_key() 
		// function, which does not block because we set the timeout 
		// for read() to 100 ms (raw_termios.c_cc[VTIME] = 1;).
		// If it times out, rawterm_read_key() just returns 0 chars
		// and this while just keeps re-iterating until CTRL-Q:
		e = rawterm_handle_keypress();
        if (s < num_states && e < NONE_PRESSED && (state_transition_rules[s].event == e))//eerste if for button 1 array 1
        {
            s = (*state_transition_rules[s].handler)();
        }
		else if (s < num_states && e < NONE_PRESSED && (state_transition_rules2[s].event == e))//tweede if voor button2 array 2
        {
            s = (*state_transition_rules2[s].handler)();
        }
        printf("current state is %d\r\n",(int)s);
        
	}
	return 0;
}

#include <map>
#include <string>

struct GrainfuckSample {
	std::string code;
	std::string info;
	std::string title;
	int winWidth;
	int winHeight;
};

const std::map<std::string, GrainfuckSample> GRAINFUCK_SAMPLES = {
	{
		"HelloWorld",
		{
			"++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.",
			"Prints the classical `Hello World!` and a newline.",
			"Hello World!",
			0, 0
		}
	},
	{
		"ROT13",
		{
			"-,+[                         Read first character and start outer character reading loop\n\
    -[                       Skip forward if character is 0\n\
        >>++++[>++++++++<-]  Set up divisor (32) for division loop\n\
                               (MEMORY LAYOUT: dividend copy remainder divisor quotient zero zero)\n\
        <+<-[                Set up dividend (x minus 1) and enter division loop\n\
            >+>+>-[>>>]      Increase copy and remainder / reduce divisor / Normal case: skip forward\n\
            <[[>+<-]>>+>]    Special case: move remainder back to divisor and increase quotient\n\
            <<<<<-           Decrement dividend\n\
        ]                    End division loop\n\
    ]>>>[-]+                 End skip loop; zero former divisor and reuse space for a flag\n\
    >--[-[<->+++[-]]]<[         Zero that flag unless quotient was 2 or 3; zero quotient; check flag\n\
        ++++++++++++<[       If flag then set up divisor (13) for second division loop\n\
                               (MEMORY LAYOUT: zero copy dividend divisor remainder quotient zero zero)\n\
            >-[>+>>]         Reduce divisor; Normal case: increase remainder\n\
            >[+[<+>-]>+>>]   Special case: increase remainder / move it back to divisor / increase quotient\n\
            <<<<<-           Decrease dividend\n\
        ]                    End division loop\n\
        >>[<+>-]             Add remainder back to divisor to get a useful 13\n\
        >[                   Skip forward if quotient was 0\n\
            -[               Decrement quotient and skip forward if quotient was 1\n\
                -<<[-]>>     Zero quotient and divisor if quotient was 2\n\
            ]<<[<<->>-]>>    Zero divisor and subtract 13 from copy if quotient was 1\n\
        ]<<[<<+>>-]          Zero divisor and add 13 to copy if quotient was 0\n\
    ]                        End outer skip loop (jump to here if ((character minus 1)/32) was not 2 or 3)\n\
    <[-]                     Clear remainder from first division if second division was skipped\n\
    <.[-]                    Output ROT13ed character from copy and clear it\n\
    <-,+                     Read next character\n\
]                            End character reading loop",
			"ROT13 algorithm. Type a word and type the result.",
			"ROT13",
			0, 0
		}
	},
	// Graphical samples
	{
		"Diagonal",
		{
			">>-[<</+>+>-]",
			"Draws a red line through the screen.",
			"Diagonal",
			256, 256
		}
	},
	{
		"Gradient",
		{
			">>>-<<</>>>[<<[-<+>]<+[/->+<]/>>>-]",
			"Draws a lime to black gradient over the screen.",
			"Gradient",
			256, 256
		}
	},
	{
		"GradientReversed",
		{
			">>>-<<</>>>[<<[-<+>]<[/->+<]/-<+>>>>-]",
			"Somewhat an unexpected fail. But still cool",
			"Gradient",
			256, 256
		}
	},
	{
		"GradientBicolor",
		{
			"->->->-<<</>[<-[/-]>>->>+<<<</>-]",
			"Vertical gradient between yellow and cyan (with some fails)",
			"Gradient",
			256, 256
		}
	}
};

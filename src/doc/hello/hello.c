/**
 * \page hello_world Tutorial 2: Creating a "Hello World" SIEGE application
 *
 * \section hello_world_prereqs This tutorial assumes:
 *
 * \li That you have completed the tutorial \"Configuring the build environment
 *	for SIEGE \ref configuring_linux "in Linux" or \ref configuring_windows "in
 *	Windows"\".
 * \li That you have at least the <a href="http://www.libsdl.org">SDL</a>,
 * <a href="http://www.opengl.org">OpenGL</a> and
 * <a href="http://www.freetype.org">FreeType</a> modules and dependencies.
 *
 * \section hello_world_step1 Step 1: Prepairing the folders
 *
 * Before we can begin coding, we'll need a basic tree setup.
 * \li Create a new \b hello folder in the tutorials root directory and copy in
 *	<b>master/include</b> <em>(the folder itself, not its contents)</em>.
 * \li Create a \b build folder inside and copy from the <b>master/build</b>
 *	folder the \b modules folder <em>(which holds the modules required to run
 *	SIEGE)</em>, the <b>data</b> folder <em>(which holds the fonts we'll be
 *	needing)</em> and the libraries <b>libSIEGE.[so/dll]</b> and
 *	<b>libSIEGE.[a/lib]</b> from the \b lib folder.
 * \li Inside the \b hello folder, create a <b>CMakeLists.txt</b> and put into
 * it the following:
 *	\include hello/CMakeLists.txt
 * \li Create an empty <b>main.c</b> file inside of the \b hello folder
 * (we'll be using it in a moment).
 *
 * \section hello_world_step2 Step 2: The minimal running program
 *
 * Now is the time to begin with or own program. Note that all the paths from
 * now on will be relative to the \b hello folder.
 *
 * Open up <b>main.c</b> in an editor of your choice and type this in:
 * \includelineno hello/main_step2.c
 * Compile and run (make sure you're in the \b build folder!):
 * \li In Windows:
 * \code
 * cmake .. -G "MinGW Makefiles"
 * mingw32-make
 * HelloWorld.exe
 * \endcode
 * \li In Linux:
 * \code
 * cmake ..
 * make
 * ./HelloWorld
 * \endcode
 *
 * Congratulations, you've just made your first SIEGE application!
 *
 * Okay, now this may require some step-by-step explanation:
 * \li <b><tt>\ref sgLoadModule "sgLoadModule"("SDL");</tt></b> and
 *	<b><tt>\ref sgLoadModule "sgLoadModule"("OpenGL");</tt></b>\n
 *	This loads in the SDL and the OpenGL module - it tries to open the dynamic
 *	libraries located in the \b modules folder - <b>(lib)SGModule-Name.[so/dll]
 *	</b>, where "Name" is SDL and OpenGL, respectively - exact name of the file
 *	depends on the OS. This should \e always be the first SIEGE function you
 *	call.
 * \li <b><tt>\ref sgInit "sgInit"(640, 480, 32, 0);</tt></b>\n
 *	Initializes SIEGE, in the process opening a 640x480 window, with 32 bits per
 *	pixel. The last argument is used for flags, which can control things like
 *	opening a window in fullscreen (as opposed to the default, windowed mode).
 *	This should \e always be the first SIEGE function you call, with the
 *	exception of <tt>sgLoadModule()</tt>.
 * \li <b><tt>while(\ref sgLoop "sgLoop"(&ret))</tt></b>\n
 *	Runs a single iteration of the SIEGE main loop, handling events and
 *	similar. It returns SG_TRUE if the program is to continue running and
 *	SG_FALSE otherwise. The argument, <tt>\ref SGint "SGint"* ref</tt> is used
 *	as the return value from the <b><tt>main()</tt></b> function. <tt>NULL</tt>
 *	can also be passed instead, indicating that we don't need the value.
 * \li <b><tt>\ref sgWindowSwapBuffers "sgWindowSwapBuffers"();</tt></b>\n
 *	The primary task of this function is obvious - swap the window's back and
 *	front buffers, thus displaying on the screen what we've drawn in the
 *	previous frame (in this case nothing). It also has a not-so-obvious
 *	secondary task: it handles events passed to SIEGE (keyboard, mouse,
 *	joystick, window move/close).
 *	\note If SIEGE is ran via <tt>sgRun()</tt> (more on this in a later
 *		tutorial), then clearing is done automatically.
 * \li <b><tt>\ref sgDrawClear "sgDrawClear"();</tt></b>\n
 *	Clears the screen with a constant black color. There are "overloads"
 *	available, such as <tt>\ref sgDrawClear4f "sgDrawClear4f"(float, float,
 *	float, float)</tt>, which can be used for clearing the screen with a
 *	specific color, but they are out of scope of this tutorial. Note that
 *	clearing has to be done \e after <tt>sgWindowSwapBuffers()</tt> at the end
 *	of the loop iteration, because <tt>sgLoop()</tt> may do some drawing of its
 *	own.
 *		\note Same as above, is SIEGE is ran via <tt>sgRun()</tt>, then
 *		clearing is done automatically.
 * \li <b><tt>\ref sgDeinit "sgDeinit"();</tt></b>\n
 *	This does exactly what it seems to do - cleans up SIEGE's assets in
 *	preparation for game exit. This is required for a graceful shtudown and
 *	should \e always be the last SIEGE function you call - calling the function
 *	too early will most likely make the program crash; not calling it at all
 *	will create a memory leak as SIEGE would not do a cleanup and free its
 *	memory.
 *
 * Our program is currently just a bland black window, however - not very
 * interesting and it could hardly be called a game...
 *
 * \section hello_world_step3 Step 3: Hello, world!
 *
 * Now is the time to actually put something onto the screen. Since this is a
 * hello world example, it would be neat if it displayed "hello, world" in the
 * window.
 *
 * Since we're dealing with fonts now, we'll need to load up another module -
 * in this case, Freetype. Add this line right after the last
 * <b><tt>sgLoadModule()</tt></b>:
 * \code
 * sgLoadModule("Freetype");
 * \endcode
 * This will ensure that the Freetype module (which handles font loading for
 * us) is loaded and ready for use.
 *
 * And just after <b><tt>sgInit()</tt></b>, add:
 * \code
 * sgWindowSetTitle("SIEGE Hello World");
 * SGFont* font = sgFontCreate("data/fonts/DejaVuLGCSans.ttf", 24.0, 127);
 * \endcode
 * Let's see what each does:
 * \li <b><tt>\ref sgWindowSetTitle "sgWindowSetTitle"("SIEGE Hello World!");</tt></b>\n
 *	This one is pretty obvious - it sets the SIEGE window title to
 *	"SIEGE Hello World!".
 * \li <b><tt>\ref SGFont "SGFont"* font = \ref sgFontCreate "sgFontCreate"("data/fonts/DejaVuLGCSans.ttf", 24.0, 127);</tt></b>\n
 *	This creates a new font handle, taking 3 arguments in the process:\n
 *		<tt>"data/fonts/DejaVuLGCSans.ttf"</tt>:
 *			The filename of the font to load.\n
 *		<tt>24.0</tt>:
 *			Size of the font - it is a floating point number, meaning that
 *			sizes such as <tt>10.5</tt> are perfectly fine (though they may
 *			produce more aliasing than integer sizes).\n
 *		<tt>127</tt>:
 *			The number of characters to preload. This preloads characters 0-127
 *			to cover the most used ones - those in the ASCII character set.
 *			Note that SIEGE will load any other characters it needs on-the-fly.
 *
 * We are creating a new font handle, so we'll need to destroy it. At the end,
 * just before <b><tt>sgDeinit()</tt></b>, add the following:
 * \code
 * sgFontDestroy(font);
 * \endcode
 * This handles the destruction, now on to the actual printing...
 *
 * SIEGE is event-based, but events are out of scope of this tutorial. That is
 * why we are going to do things "the old fashioned way" by directly printing
 * the text on the screen from the loop (as opposed to printing from an event
 * handler).
 *
 * At the top of the main loop, just after
 * <b><tt>while(\ref sgLoop "sgLoop"(&ret))</tt></b>, add:
 * \code
 * sgFontPrintCentered(font, sgWindowGetWidth() / 2, sgWindowGetHeight() / 2, "hello, world");
 * \endcode
 *
 * Three new functions are used here:
 * \li <b><tt>\ref sgFontPrintCentered "sgFontPrintCentered"(font, \ref sgWindowGetWidth "sgWindowGetWidth"() / 2, \ref sgWindowGetHeight "sgWindowGetHeight"() / 2, "hello, world");</tt></b>\n
 *	What this function does is pretty obvious. The arguments here are:\n
 *		<tt>font</tt>:
 *			This is the font which will be used for printing\n
 *		<tt>\ref sgWindowGetWidth "sgWindowGetWidth"() / 2,
 *		\ref sgWindowGetHeight "sgWindowGetHeight"() / 2</tt>:
 *			\a x and \a y position of the print. There is another way to get
 *			the window position (see below).\n
 *		<tt>"hello, world", ...</tt>:
 *			The reason I've added the <tt>...</tt> is because the function uses
 *			<tt>printf</tt>-like syntax, meaning that it can take arguments
 *			like <tt>"%d,%d,%d", r, g, b</tt>. There are two other variants of
 *			the function, <b><tt>sgFontPrintCenteredV()</tt></b>, which takes
 *			in a <tt>va_list</tt> and <b><tt>sgFontPrintCenteredT()</tt></b>,
 *			which takes in a simple string. The other two functions call the
 *			"T" variant internally.\n
 * \li <b><tt>\ref sgWindowGetWidth "sgWindowGetWidth"(), \ref sgWindowGetHeight "sgWindowGetHeight"()</tt></b>\n
 *	These two are obvious, but there is a more efficient way of getting the
 *	window size when both width and height are required -
 *	<b><tt>\ref sgWindowGetSize "sgWindowGetSize"(&width, &height)</tt></b>.
 *	The GetSize variant is not used in this tutorial for simplicity purposes,
 *	however.
 *
 * Your source code should now look like this:
 * \includelineno hello/main_step3.c
 *
 * Compile and test... If you've done everything correctly, you should see
 * \"<b>hello, world</b>\" printed in the middle of the screen.
 *
 * \image html hello/HelloWorld.png "Screenshot"
 * \image latex hello/HelloWorld.eps "Screenshot" width=10cm
 *
 * The next tutorial will cover SIEGE's event loop and event handling.
 *
 * \section hello_world_help Help
 *
 * If you need help, see the \ref help "Getting help page".
 *
 */

/**
 * \page configuring_windows Tutorial 1: Configuring the build environment for SIEGE in Windows
 *
 * \section conf_windows_prereqs This tutorial assumes:
 *
 * \li That you have some C programming knowledge
 * \li That you already have a build environment setup
 *	<em>(nevertheless, compiler links are provided for completeness)</em>
 * \li That you know where to put header and library files (for the libraries used by the modules)
 * \li That cmake and other tools (gcc, make...) are in your <b><tt>%PATH%</tt></b>
 *
 * For this tutorial, we'll be using just one specific set of modules - of
 * course, you are free to compile more/others later, should you need them.
 *
 *
 * \section conf_windows_step1 Step 1: Get the tools
 *
 * \subsection conf_windows_step1_need What you will need
 *
 * \subsubsection conf_windows_step1_need_software Software
 * Note that most of these should be available in your distribution's repositories!
 * \li <a href="http://www.cmake.org">CMake</a>,
 *	a cross-platform C/C++ build system
 *		(<a href="http://www.codeblocks.org">Code::Blocks</a> is supported,
 *		but support may soon be removed)
 * \li A Git client (recommended:
 *	<a href="http://code.google.com/p/tortoisegit">TortoiseGit</a>)
 * \li A C compiler (recommended: <a href="http://www.mingw.org">MinGW</a>)
 * \li Optionally, <a href="http://www.doxygen.org">Doxygen</a>,
 *	for building documentation from the source
 *
 * \subsubsection conf_windows_step1_need_libraries Libraries
 * You may have to manually compile some, while others should already be
 * provided as "devel" packages in your distro's repositories
 * \li <a href="http://www.libsdl.org">SDL</a> (windowing and UI)
 * \li <a href="http://www.opengl.org">OpenGL</a> (graphics) -
 *	Exactly which package you need depends on your GPU brand, but you can find
 *	the headers <a href="http://www.opengl.org/registry/#headers">here</a>.
 * \li <a href="http://openil.sourceforge.net">DevIL/OpenIL</a> (image loading)*
 * \li <a href="http://www.freetype.org">FreeType</a> (font loading)*
 * \li <a href="http://connect.creativelabs.com/openal">OpenAL</a> (audio)*
 * \li <a href="http://www.mega-nerd.com/libsndfile">libsndfile</a>
 *	(audio loading)*
 * \li <a href="http://code.google.com/p/chipmunk-physics">Chipmunk</a>
 *	(physics)*
 * \li Currently, there is a module available for
 *	<a href="http://www.glfw.org">GLFW</a>, but it doesn't seem to work
 *	properly in Linux (something is wrong with its libraries) - building of
 *	the module is therefore disabled by default. To enable it, use
 *	<b><tt>mingw32-make edit_cache</tt></b> and enable
 *	<b><tt>BUILD_MOD_GLFW</tt></b>.
 *
 * Note: Items marked with \b * are not absolutely required for a "minimal"
 * application, but the demos will most likely crash, as SIEGE does not yet
 * have a complete failsafe for missing modules (we are working towards it).
 *
 * \subsection conf_windows_step1_paths Directory paths & fetching files from Git
 *
 * Create a path where you want the tutorial files to be. Make sure the path
 * contains no spaces - for the purpose of this tutorial, I am going to put my
 * files into <b>C:\\SIEGETutorial</b> (where ~ is the home folder) - in the
 * instructions, replace this path with wherever you've put/are going to put
 * your files in.
 * \li Create the directory <b>C:\\SIEGETutorial</b>
 * \li Clone the SIEGE repository into \b master:
 *	Right click on the \b SIEGETutorial directory and select <b>Git Clone</b>.
 *	Make sure that the repository is cloned into the \b master directory.
 *	If you're using a console-based client, see
 *	\ref conf_linux_step1_paths "the Linux instructions".
 *	\todo Put this separately into "cloning the repository"
 *
 * \section conf_windows_step2 Step 2: Compiling the modules and SIEGE
 *
 * \li Open up a terminal (console) and go to the \b master folder.
 * \li Create a \b build directory and enter it:
 *	\code
 * mkdir build
 * cd build
 *	\endcode
 * \li Generate the makefiles <em>(note: add <b><tt>-G "<Name>"</tt></b> to
 * generate makefiles for something other than <b><tt>mingw32-make</tt></b> -
 * use <b><tt>cmake</tt></b> with no arguments to see the list of available
 * generators)</em>:
 *	\code
 * cmake .. -G "MinGW Makefiles"
 *	\endcode
 * \li <em>(optional)</em> If you want to build some bindings, use
 *	<b><tt>mingw32-make edit_cache</tt></b> and enable
 *	<b><tt>BUILD_BINDINGS_<name></tt></b>.
 * \li Compile...
 *	\code
 * make
 *	\endcode
 * \li Copy <b>lib/*.dll</b> to <b>.</b> so that the binaries manage to find
 * the SIEGE library: \"<b><tt>copy lib/*.dll .</tt></b>\"
 *	\todo Remove the
 * need to do this
 * \li Run the demos:
 *	\code
 * bin/Demo-Text.exe
 * bin/Demo-Sprite.exe
 * bin/Demo-Physics.exe
 *	\endcode
 *
 * \section conf_windows_help Help
 *
 * * If you need help, see the \ref help "Getting help page".
 */
